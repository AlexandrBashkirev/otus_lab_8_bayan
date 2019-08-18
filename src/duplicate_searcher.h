#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>
#define BOOST_NO_CXX11_SCOPED_ENUMS
#include <boost/filesystem.hpp>
#undef BOOST_NO_CXX11_SCOPED_ENUMS
#include <boost/regex.hpp>
#include "i_hasher.h"
#include "file_hash_data.h"
#include <iostream>
#include <fstream>

using namespace boost::filesystem;

namespace flaber {

	class duplicate_searcher
	{
	public:

		duplicate_searcher() : is_recurcive(true), min_size(1), block_size(1024) {};

		void add_search_path(std::string& _path);
		void add_ignore_path(std::string& _path);
		void add_file_mask(std::string& _mask);
		void set_is_recurcive(bool _is_recurcive);
		void set_min_file_size(size_t _min_size);
		void set_block_size(size_t _block_size);
		void set_hash_method(hash_method _t);

		void start();
	private:
		bool is_recurcive;
		size_t min_size;
		size_t block_size;
		hash_method hash_type;
		std::list<path> pathes_for_search;
		std::list<path> pathes_for_ignore;
		std::list<boost::regex> file_masks;

		std::shared_ptr<char> buffer;
		std::unique_ptr<i_hasher> hasher;

		std::unordered_map<std::string, file_hash_data> files_hashes;

		using pathes = std::unordered_set<std::string>;
		std::map <std::string, pathes> duplicates;

		bool is_mask_fits(const path& p);
		bool is_ignored(const path& path_to_file);
		bool is_same(file_hash_data& lho, file_hash_data& rho);

		std::list<std::string>::iterator readHash(size_t offset,
			std::ifstream& file_stream,
			flaber::file_hash_data& file_data);
		template<class Iter>
		void add_each_files(path& current_path);
		void add_duplicate(std::string full_hash, std::string path_to_file);
		void create_hasher();
		void search_duplicates();
		void search_files_for_check();

		friend std::ostream& operator<< (std::ostream& os, const duplicate_searcher& searcher) {
			for (auto& file_info : searcher.duplicates)
			{
				for (auto& path_to_file : file_info.second)
					os << path_to_file << std::endl;
				os << std::endl;
			}
			return os;
		}
	};
}
