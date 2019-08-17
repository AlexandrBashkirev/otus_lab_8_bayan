#pragma once
#include "duplicate_searcher.h"
#include "md5_hasher.h"
#include "crc_hasher.h"
#include <iostream>

using namespace flaber;

void duplicate_searcher::add_search_path(std::string& _path)
{
	pathes_for_search.emplace_back(_path);
}
void duplicate_searcher::add_ignore_path(std::string& _path)
{
	pathes_for_ignore.emplace_back(_path);
}
void duplicate_searcher::add_file_mask(std::string& _mask)
{
	file_masks.emplace_back(_mask);
}
void duplicate_searcher::set_is_recurcive(bool _is_recurcive) {
	is_recurcive = _is_recurcive;
}
void duplicate_searcher::set_min_file_size(size_t _min_size) {
	min_size = _min_size;
}
void duplicate_searcher::set_block_size(size_t _block_size) {
	block_size = _block_size;
}
void duplicate_searcher::set_hash_method(flaber::hash_type _t)
{
	hash_type = _t;
}

void duplicate_searcher::start()
{
	buffer = std::shared_ptr<char>(new char[block_size], [](char *p) { delete[] p; });
	create_hasher();

	search_files_for_check();
	search_duplicates();
}

void duplicate_searcher::search_duplicates() {
	auto first = files_hashes.begin();
	auto last = files_hashes.end();
	for (; first != last; ++first) {
		auto in_first = first;

		for (++in_first; in_first != last; ++in_first) {
			if (is_same(first->second, in_first->second))
			{
				add_duplicate(first->second.full_hash(), first->first);
				add_duplicate(in_first->second.full_hash(), in_first->first);
			}
		}
	}
}
void duplicate_searcher::search_files_for_check() {
	if (pathes_for_search.empty())
		pathes_for_search.emplace_back(".");

	for (auto current_path : pathes_for_search)
	{
		if (is_recurcive)
			add_each_files<recursive_directory_iterator>(current_path);
		else
			add_each_files<directory_iterator>(current_path);
	}
}
template<class Iter>
void duplicate_searcher::add_each_files(path& current_path)
{
	Iter it{ current_path };
	while (it != Iter{}) {
		if (!is_directory(*it) &&
			!is_ignored(it->path()) &&
			is_mask_fits(it->path()) &&
			file_size(it->path()) >= min_size &&
			files_hashes.find(it->path().string()) == files_hashes.end())
			files_hashes.insert(std::pair<std::string, file_hash_data>(it->path().string(), file_hash_data( it->path())));
		++it;
	}
}
void duplicate_searcher::add_duplicate(std::string full_hash, std::string path)
{
	auto it = duplicates.insert(std::pair<std::string, std::unordered_set<std::string>>(full_hash, std::unordered_set<std::string>())).first;

	it->second.insert(path);
}
void duplicate_searcher::create_hasher()
{
	switch (hash_type)
	{
	case hash_type::crc_hash:
		hasher = std::make_unique<crc_hasher>();
		break;
	case hash_type::md5_hash:
		hasher = std::make_unique<md5_hasher>();
		break;
	default:
		hasher = std::make_unique<md5_hasher>();
		break;
	}
}

bool duplicate_searcher::is_mask_fits(const path& p) {
	if (file_masks.empty())
		return true;
	
	static boost::smatch unusedResult;
	for (const auto& fmRegexp : file_masks) {
		if (boost::regex_match(p.filename().string(), unusedResult, fmRegexp)) 
			return true;
	}
	return false;
}
bool duplicate_searcher::is_ignored(const path& path)
{
	for (auto ignore_path : pathes_for_ignore)
		if (path.string().find(ignore_path.string()) == 0)
			return true;
	return false;
}
bool duplicate_searcher::is_same(file_hash_data& lho, file_hash_data& rho)
{
	if (file_size(lho.path) != file_size(rho.path))
		return false;

	auto files_size = file_size(lho.path);
	size_t block_count = files_size / block_size + 1;

	auto firstL = lho.hash.begin();
	auto firstR = rho.hash.begin();

	ifstream l_file_stream;
	ifstream r_file_stream;
	
	for (size_t i = 0; i < block_count; ++i)
	{
		if (firstL == lho.hash.end())
			firstL = readHash(i, l_file_stream, lho);

		if (firstR == rho.hash.end())
			firstR = readHash(i, r_file_stream, rho);
		
		if (firstL->find(*firstR) != 0)
			return false;

		++firstL;
		++firstR;
	}
	
	return true;
}

std::list<std::string>::iterator duplicate_searcher::readHash(size_t offset,
	ifstream& file_stream, 
	file_hash_data& file_data)
{
	if (!file_stream.is_open())
		file_stream.open(file_data.path.string(), std::ios::in | std::ios::binary | std::ios::ate);

	file_stream.seekg(offset * block_size, std::ios_base::beg);
	std::memset(buffer.get(), 0, block_size);
	file_stream.read(buffer.get(), block_size);

	return file_data.hash.insert(file_data.hash.end(), hasher->hash(buffer.get(), block_size));
}
