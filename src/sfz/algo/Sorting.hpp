#pragma once
#ifndef SFZ_ALGO_SORTING_HPP
#define SFZ_ALGO_SORTING_HPP

#include <iostream>
#include <stdexcept>
#include <thread>
#include <mutex>

namespace sfz {
	using std::size_t;

	template<typename RandomIt>
	void quickSort(RandomIt first, RandomIt last);

	template<typename RandomIt>
	void parallelQuickSort(RandomIt first, RandomIt last, const size_t numThreads = std::thread::hardware_concurrency());

	template<typename RandomIt>
	void insertionSort(RandomIt first, RandomIt last);
}
#include "Sorting.inl"
#endif