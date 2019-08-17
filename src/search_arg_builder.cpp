#include <boost/program_options.hpp>
#include "search_arg_builder.h"
#include <iostream>

flaber::duplicate_searcher flaber::search_arg_builder::build(int argc, char* argv[])
{
	namespace po = boost::program_options;

	hash_method hash_type = hash_method::md5_hash;
	bool is_recurcive;
	size_t min_size;
	size_t block_size;
	std::vector<std::string> pathes_for_search;
	std::vector<std::string> pathes_for_ignore;
	std::vector<std::string> file_masks;

	flaber::duplicate_searcher searcher;

	po::options_description desc("Allowed options");
	desc.add_options()
		("help,h", "produce help message")
		("search,s", po::value(&pathes_for_search), "directories for search")
		("ignore,i", po::value(&pathes_for_ignore), "directories for ignore")
		("file_mask", po::value(&file_masks), "mask for search")
		("min-size,m", po::value(&min_size)->default_value(1), "min file size")
		("recursive,r", po::bool_switch(&is_recurcive)->default_value(true), "recursive search")
		("block-size,b", po::value(&block_size)->default_value(1024), "block size for hash")
		("hash", po::value(&hash_type)->default_value(hash_method::md5_hash), "hash type (crc32/md5)")
		;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("help") || vm.count("h")) {
		std::cout << desc << "\n";
		exit(0);
	}

	searcher.set_block_size(block_size);
	searcher.set_is_recurcive(is_recurcive);
	searcher.set_min_file_size(min_size);
	searcher.set_hash_method(hash_type);

	for (auto& p : file_masks)
		searcher.add_file_mask(p);

	for (auto& p : pathes_for_ignore)
		searcher.add_ignore_path(p);

	for (auto& p : pathes_for_search)
		searcher.add_search_path(p);

	return searcher;
}

std::istream& flaber::operator>>(std::istream& in, flaber::hash_method& hash_type) {
	std::string token;
	in >> token;
	if (token == "crc32")
		hash_type = flaber::hash_method::crc_hash;
	else if (token == "md5")
		hash_type = flaber::hash_method::md5_hash;
	else
		assert("wrong hash type");
	return in;
}