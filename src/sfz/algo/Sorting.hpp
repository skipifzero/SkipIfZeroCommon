#pragma once
#ifndef SFZ_ALGO_SORTING_HPP
#define SFZ_ALGO_SORTING_HPP

#include <iostream>
#include <stdexcept>
#include <thread>
#include <mutex>

namespace sfz {
	using size_t = std::size_t;

	const size_t INSERTIONSORT_TRESHOLD = 7;

	template<class T>
	void quicksort(T* array, const size_t length);
	
	template<class T>
	void insertionsort(T* array, const size_t length);

	//template<class T>
	//void concurrentQuicksort(T* array, const size_t length, const size_t numThreads = std::thread::hardware_concurrency());
}
#include "Sorting.inl"
#endif