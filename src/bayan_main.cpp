// bayan.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "duplicate_searcher.h"
#include "search_arg_builder.h"
#include <time.h>

int main(int argc, char* argv[])
{
	/* Optimisation history
	start: time over 7200s
	fitst try: time 599s, disk 348MB, cpu 9.30
	second try: time 234s, disk 328MB, cpu 3.28
	*/

	flaber::search_arg_builder builder;
	flaber::duplicate_searcher searcher = builder.build(argc, argv);

	time_t timer_before;
	time(&timer_before);

	searcher.start();

	time_t timer_after;
	time(&timer_after);

	std::cout << searcher;

	double seconds = difftime(timer_after,timer_before);
	std::cout << "seconds spent: " << seconds << "\n";

	int n;
	std::cin >> n;
}
