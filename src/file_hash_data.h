#pragma once
#define BOOST_NO_CXX11_SCOPED_ENUMS
#include <boost/filesystem.hpp>
#include "file_hash_iterator.h"

#undef BOOST_NO_CXX11_SCOPED_ENUMS
using namespace boost::filesystem;

namespace flaber {

	struct file_hash_data
	{
		std::string path_to_file;
		size_t file_size;

		template<typename S>
		file_hash_data(size_t _file_size, S&& _path) : 
			path_to_file(std::forward<S>(_path)),
			file_size(_file_size)
		{
			hashes.resize(file_size/);
		}

		std::string full_hash()
		{
			std::string tmp;
			for (auto h : hashes)
				tmp += h;
			return tmp;
		}

		file_hash_iterator begin()
		{
			return flaber::file_hash_iterator(this, 0);
		}

		file_hash_iterator end()
		{
			return flaber::file_hash_iterator(nullptr, size_t.Max);
		}

	private:

		std::ifstream file_stream;
		std::vector<std::string> hashes;
	};
}