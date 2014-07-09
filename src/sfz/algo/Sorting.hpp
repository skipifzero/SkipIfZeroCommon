#pragma once
#ifndef SFZ_ALGO_SORTING_HPP
#define SFZ_ALGO_SORTING_HPP

#include <iostream>
#include <stdexcept>
#include <thread>
//#include <mutex>
#include <algorithm> // min, max, partition, rotate, is_sorted, upper_bound
#include <utility> // swap
#include <iterator> // iterator_traits, distance
#include "../util/ThreadPool.hpp"

namespace sfz {
	using std::size_t;
	using std::swap;
	using std::max;
	using std::min;

	template<typename RandomIt>
	void quicksort(RandomIt first, RandomIt last);

	template<typename RandomIt>
	void parallelQuicksort(RandomIt first, RandomIt last);

	template<typename RandomIt>
	void parallelQuicksort(RandomIt first, RandomIt last, size_t numThreads);

	template<typename RandomIt>
	void insertionsort(RandomIt first, RandomIt last);
}
#include "Sorting.inl"
#endif