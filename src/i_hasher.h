#pragma once
#include <string>

namespace flaber
{
	enum hash_method
	{
		crc_hash,
		md5_hash,
	};

	class i_hasher
	{
	public:
		virtual std::string hash(char* data, size_t size) = 0;
	};
}
