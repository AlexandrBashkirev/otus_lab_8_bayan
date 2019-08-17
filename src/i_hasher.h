#pragma once
#include <string>

namespace flaber
{
	class i_hasher
	{
	public:
		virtual std::string hash(char* data, size_t size) = 0;
	};
}
