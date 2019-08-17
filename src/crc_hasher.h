#pragma once

#include "i_hasher.h"

namespace flaber
{
	class crc_hasher : public i_hasher
	{
	public:
		std::string hash(char* data, size_t size);
	};
}
