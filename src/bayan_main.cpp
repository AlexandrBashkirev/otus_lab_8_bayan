// bayan.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "duplicate_searcher.h"
#include "search_arg_builder.h"

int main(int argc, char* argv[])
{
	flaber::search_arg_builder builder;
	flaber::duplicate_searcher searcher = builder.build(argc, argv);

	searcher.start();

	std::cout << searcher;
}
