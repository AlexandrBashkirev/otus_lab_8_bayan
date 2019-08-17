#pragma once
#include <boost/filesystem.hpp>
using namespace boost::filesystem;

namespace flaber {

	struct file_hash_data
	{
		template<typename S>
		file_hash_data(S&& _path) : path_to_file(std::forward<S>(_path)) {}

		path path_to_file;
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