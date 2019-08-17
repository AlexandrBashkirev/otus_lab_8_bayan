#pragma once

#include "crc_hasher.h"
#include <boost/crc.hpp>
#include <string>

std::string flaber::crc_hasher::hash(char* data, size_t size)
{
	boost::crc_32_type result;
	result.process_bytes(data, size);
	return std::to_string(result.checksum());
}

