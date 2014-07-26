#pragma once
#ifndef SFZ_ALGO_SORTING_HPP
#define SFZ_ALGO_SORTING_HPP

#include <stdexcept>
#include <algorithm> // min, max, partition, rotate, is_sorted, upper_bound
#include <iterator> // iterator_traits, distance
#include <thread>
#include "sfz/util/ScopedThread.hpp"

namespace sfz {
	using std::size_t;
	using std::max;
	using std::min;

	template<typename RandomIt>
	void insertionsort(RandomIt first, RandomIt last);

	template<typename RandomIt>
	void quicksort(RandomIt first, RandomIt last);

	template<typename RandomIt>
	void parallelQuicksort(RandomIt first, RandomIt last, size_t numThreads = std::thread::hardware_concurrency());
}
#include "Sorting.inl"
#endif