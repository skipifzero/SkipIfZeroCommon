#include <iostream>
#include <string>
#include <random>
#include <cstdlib> // std::qsort()
#include <algorithm> // std::sort(), std::stable_sort()
#include "sfz/algo/Sorting.hpp"
#include "sfz/util/StopWatch.hpp"

// Printing functions
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
template<typename T>
void printArray(T* array, size_t length, bool limited = true, size_t elementsToShow = 100) {
	for(size_t i = 0; i < (limited ? (elementsToShow < length ? elementsToShow : length) : length); i++) {
		std::cout << i << ":\t" << array[i] << std::endl;
	}
	std::cout << std::endl;
}

void printTime(sfz::StopWatch clock) {
	std::cout << clock.getTimeMilliSeconds().count() << "ms, " << clock.getTimeNanoSeconds().count() % 1000000
	          << "ns" << std::endl;
}

// Array creators
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
int* arrayWithRandomNumbers(size_t length, int min, int max) {
	std::mt19937_64 ms; // 64bit Mersenne Twister
	// We always use the same seed, this is crucial for the fairness of the tests. This ensures that each time
	// the function is called with the same parameters the resulting array will contain the same numbers.
	ms.seed(1337);
	std::uniform_int_distribution<int> dist{min, max};
	int* array = new int[length];
	for(size_t i = 0; i < length; i++) {
		array[i] = dist(ms);
	}
	return array;
}

int* denseRandomNumberArray(size_t length) {
	return arrayWithRandomNumbers(length, -static_cast<int>(length)/5, static_cast<int>(length)/5);
}

int* sparseRandomNumberArray(size_t length) {
	return arrayWithRandomNumbers(length, -static_cast<int>(length)*5, static_cast<int>(length)*5);
}

int* binaryNumberArray(size_t length) {
	return arrayWithRandomNumbers(length, 0, 1);
}

int* sortedNumberArray(size_t length) {
	int* array = new int[length];
	for(size_t i = 0; i < length; i++) {
		array[i] = i;
	}
	return array;
}

int* reverseSortedNumberArray(size_t length) {
	int* array = new int[length];
	for(size_t i = 0; i < length; i++) {
		array[i] = length-i;
	}
	return array;
}

// Wrappers for sort functions so they can fit test framework
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
template<typename T>
int compare(const void* obj1, const void* obj2) {
	T val1 = *reinterpret_cast<const T*>(obj1);
	T val2 = *reinterpret_cast<const T*>(obj2);
	if(val1 < val2) {
		return -1;
	}
	if(val1 > val2) {
		return 1;
	}
	return 0;
}

template<typename T>
void std_qsort(T* first, T* last) {
	std::qsort(first, last - first, sizeof(T), compare<T>);
}

template<typename RandomIt, size_t N>
void sfz_parallelQuicksort(RandomIt first, RandomIt last) {
	sfz::parallelQuicksort(first, last, N);
}

// Test functions
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
template<typename T>
bool isArraySortedTest(T* array, size_t length) {
	for(size_t i = 0; i < length-1; i++) {
		if(array[i] > array[i+1]) {
			std::cout << "Array NOT SORTED! array[" << i << "] = "
			          << array[i] << ", array[" << i+1 << "] = " << array[i+1] << std::endl;
			return false;
		}
	}
	return true;
}

template<typename T>
void testOneSort(T*(*arrayCreator)(size_t), size_t length, void(*sortFunc)(T*,T*)) {
	auto array = arrayCreator(length);
	sfz::StopWatch clock;
	sortFunc(array, array + length);
	clock.stop();
	printTime(clock);
	isArraySortedTest(array, length);
	//printArray(array, length, true, 20);
	delete[] array;
}

template<typename T>
void testAllSorts(std::string title, T*(*arrayCreator)(size_t), size_t length) {
	std::cout << title << ", length: " << length << "\n";
	
	std::cout << "                     sfz::insertionsort():  ";
	testOneSort(arrayCreator, length, sfz::insertionsort<T*>);

	std::cout << "                         sfz::quicksort():  ";
	testOneSort(arrayCreator, length, sfz::quicksort<T*>);

	std::cout << "      sfz::parallelQuicksort() (1 thread):  ";
	testOneSort(arrayCreator, length, sfz_parallelQuicksort<T*,1>);

	std::cout << "     sfz::parallelQuicksort() (2 threads):  ";
	testOneSort(arrayCreator, length, sfz_parallelQuicksort<T*,2>);

	std::cout << "     sfz::parallelQuicksort() (4 threads):  ";
	testOneSort(arrayCreator, length, sfz_parallelQuicksort<T*,4>);

	std::cout << "     sfz::parallelQuicksort() (8 threads):  ";
	testOneSort(arrayCreator, length, sfz_parallelQuicksort<T*,8>);

	std::cout << "                             std::qsort():  ";
	testOneSort(arrayCreator, length, std_qsort);

	std::cout << "                              std::sort():  ";
	testOneSort(arrayCreator, length, std::sort<T*>);

	std::cout << "                       std::stable_sort():  ";
	testOneSort(arrayCreator, length, std::stable_sort<T*>);

	std::cout << std::endl;
}

// Main
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
int main() {
	testAllSorts("### Array with dense random numbers", denseRandomNumberArray, 300000);

	testAllSorts("### Array with sparse random numbers", sparseRandomNumberArray, 300000);

	testAllSorts("### Array with binary numbers", binaryNumberArray, 300000);

	testAllSorts("### Array with sorted numbers", sortedNumberArray, 3000000);

	testAllSorts("### Array with reversed sorted numbers", reverseSortedNumberArray, 100000);
	
	return 0;
}
