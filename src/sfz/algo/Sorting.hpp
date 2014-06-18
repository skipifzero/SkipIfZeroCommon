#pragma once
#ifndef SFZ_ALGO_SORTING_HPP
#define SFZ_ALGO_SORTING_HPP

#include <iostream>
#include <stdexcept>
#include <thread>
#include <mutex>
#include <utility>

namespace sfz {
	using std::size_t;
	using std::swap;

	template<typename RandomIt>
	void quicksort(RandomIt first, RandomIt last);

	template<typename RandomIt>
	void parallelQuicksort(RandomIt first, RandomIt last, const size_t numThreads = std::thread::hardware_concurrency());

	template<typename RandomIt>
	void insertionsort(RandomIt first, RandomIt last);
}
#include "Sorting.inl"
#endif