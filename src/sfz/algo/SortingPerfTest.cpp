#include "SortingPerfTest.hpp"

namespace sfz {

	// Anonymous functions
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	namespace {		

		// Printing functions
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		template<class T>
		void printArray(T* array, size_t length, bool limited = true, size_t elementsToShow = 100) {
			for(size_t i = 0; i < (limited ? (elementsToShow < length ? elementsToShow : length) : length); i++) {
				std::cout << i << ":\t" << array[i] << std::endl;
			}
			std::cout << std::endl;
		}

		void printTime(StopWatch clock) {
			std::cout << clock.getTimeMilliSeconds().count() << "ms, " << clock.getTimeNanoSeconds().count() % 1000000 << "ns" << std::endl;
		}

		// Array creators
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		int* arrayWithRandomNumbers(size_t length, int min, int max) {
			std::mt19937_64 ms; // 64bit Mersenne Twister
			ms.seed(1337); // We always want the same random numbers, so we always use this seed.
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
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		template<typename T>
		int compare(const void* obj1, const void* obj2) {
			int val1 = *reinterpret_cast<const int*>(obj1);
			int val2 = *reinterpret_cast<const int*>(obj2);
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

		// Test functions
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		template<typename T>
		void isArraySortedTest(T* array, size_t length) {
			for(size_t i = 0; i < length-1; i++) {
				if(array[i] > array[i+1]) {
					std::cout << "Array NOT SORTED! array[" << i << "] = "
					          << array[i] << ", array[" << i+1 << "] = " << array[i+1] << std::endl;
					return;
				}
			}
		}

		template<typename T>
		void testOneSort(T*(*arrayCreator)(size_t), size_t length, void(*sortFunc)(T*,T*)) {
			auto array = arrayCreator(length);
			sfz::StopWatch clock;
			sortFunc(array, array + length);
			clock.stop();
			printTime(clock);
			isArraySortedTest(array, length);
			delete[] array;
		}

		template<typename T>
		void testAllSorts(std::string title, T*(*arrayCreator)(size_t), size_t length) {
			std::cout << title << ", length: " << length << "\n";
			std::cout << "                  sfz::insertionsort(): ";
			testOneSort(arrayCreator, length, insertionsort<T*>);

			std::cout << "                      sfz::quicksort():  ";
			testOneSort(arrayCreator, length, quicksort<T*>);

			std::cout << "                          std::qsort():  ";
			testOneSort(arrayCreator, length, std_qsort);

			std::cout << "                           std::sort():  ";
			testOneSort(arrayCreator, length, std::sort<T*>);

			std::cout << "                    std::stable_sort():  ";
			testOneSort(arrayCreator, length, std::stable_sort<T*>);

			std::cout << std::endl;
		}
	}

	// Visible functions
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *	

	void runSortingPerformanceTest() {
		testAllSorts("### Array with dense random numbers", denseRandomNumberArray, 50000);

		testAllSorts("### Array with sparse random numbers", sparseRandomNumberArray, 50000);

		testAllSorts("### Array with binary numbers", binaryNumberArray, 50000);

		testAllSorts("### Array with sorted numbers", sortedNumberArray, 100000);

		testAllSorts("### Array with reversed sorted numbers", reverseSortedNumberArray, 50000);
	}
}
