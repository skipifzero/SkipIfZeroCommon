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

	/**
	 * @brief Sorts the elements in interval [first, last).
	 * Sorts the elements using insertionsort. Insertionsort usually performs really well on already sorted arrays,
	 * while this implementation doesn't perform badly it's not instant like you might expect. If performance is
	 * important in this scenario you might want to check if the sequence is sorted using std::is_sorted beforehand.
	 * @throws std::invalid_argument if last <= first
	 * @param first the RandomAccessIterator to the first (inclusive) element in the sequence
	 * @param last the RandomAccessIterator to the last (exclusive) element in the sequence
	 */
	template<typename RandomIt>
	void insertionsort(RandomIt first, RandomIt last);

	/**
	 * @brief Sorts the elements in interval [first, last).
	 * Sorts the elements using quicksort.
	 * @throws std::invalid_argument if last <= first
	 * @param first the RandomAccessIterator to the first (inclusive) element in the sequence
	 * @param last the RandomAccessIterator to the last (exclusive) element in the sequence
	 */
	template<typename RandomIt>
	void quicksort(RandomIt first, RandomIt last);

	/**
	 * @brief Sorts the elements in interval [first, last).
	 * Sorts the elements in parallel using quicksort. This function is currently "broken", it will correctly sort the
	 * sequence, but it will not perform better than a standard quicksort. The reason for this is still unclear, but
	 * I suspect std::partition might already be parallely implemented.
	 * @throws std::invalid_argument if last <= first
	 * @param first the RandomAccessIterator to the first (inclusive) element in the sequence
	 * @param last the RandomAccessIterator to the last (exclusive) element in the sequence
	 */
	template<typename RandomIt>
	void parallelQuicksort(RandomIt first, RandomIt last, size_t numThreads = std::thread::hardware_concurrency());
}
#include "Sorting.inl"
#endif