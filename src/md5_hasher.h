#pragma once

#include "i_hasher.h"

namespace flaber
{
	class md5_hasher : public i_hasher
	{
	public:
		std::string hash(char* data, size_t size);
	};
}
