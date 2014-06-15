#pragma once
#ifndef SFZ_ALGO_SORTING_PERF_TEST_HPP
#define SFZ_ALGO_SORTING_PERF_TEST_HPP

#include <iostream>
#include <string>
#include <random>
#include <cstdlib> //std::qsort()
#include <algorithm> //std::sort(), std::stable_sort()
#include "Sorting.hpp"
#include "../util/StopWatch.hpp"

namespace sfz {
	using std::size_t;

	void runSortingPerformanceTest();
}
#endif