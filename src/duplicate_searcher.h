#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include "i_hasher.h"

using namespace boost::filesystem;

namespace flaber {

	enum hash_type
	{
		crc_hash,
		md5_hash,
	};
	namespace
	{
		struct file_hash_data
		{
			template<typename S>
			file_hash_data(S&& _path) : path(std::forward<S>(_path)) {}

			path path;
			std::list<std::string> hash;

			std::string full_hash()
			{
				std::string tmp;
				for (auto h : hash)
					tmp += h;
				return tmp;
			}
		};
	}
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
		void set_hash_method(hash_type _t);

		void start();
	private:
		bool is_recurcive;
		size_t min_size;
		size_t block_size;
		hash_type hash_type;
		std::list<path> pathes_for_search;
		std::list<path> pathes_for_ignore;
		std::list<boost::regex> file_masks;

		std::shared_ptr<char> buffer;
		std::unique_ptr<i_hasher> hasher;

		std::unordered_map<std::string, file_hash_data> files_hashes;

		using pathes = std::unordered_set<std::string>;
		std::map <std::string, pathes> duplicates;

		bool is_mask_fits(const path& p);
		bool is_ignored(const path& path);
		bool is_same(file_hash_data& lho, file_hash_data& rho);

		std::list<std::string>::iterator readHash(size_t offset,
			ifstream& file_stream,
			flaber::file_hash_data& file_data);
		template<class Iter>
		void add_each_files(path& current_path);
		void add_duplicate(std::string full_hash, std::string path);
		void create_hasher();
		void search_duplicates();
		void search_files_for_check();

		friend std::ostream& operator<< (std::ostream& os, const duplicate_searcher& searcher) {
			for (auto& file_info : searcher.duplicates)
			{
				for (auto& path : file_info.second)
					os << path << std::endl;
				os << std::endl;
			}
			return os;
		}
	};
}
