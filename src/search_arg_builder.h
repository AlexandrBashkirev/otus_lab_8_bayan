#pragma once
#include "duplicate_searcher.h"

namespace flaber
{
	class search_arg_builder
	{
	public:
		duplicate_searcher build(int argc, char* argv[]);

		
	};

	std::istream& operator>>(std::istream& in, hash_type& hash_type);
}
