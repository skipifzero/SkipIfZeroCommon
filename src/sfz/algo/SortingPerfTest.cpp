#include "SortingPerfTest.hpp"

namespace sfz {

	// Anonymous functions
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	namespace {
		//using size_t = std::size_t;

		
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

		// Wrappers for sort functions so they can fit test framework
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		template<class T>
		int compare(const void* obj1, const void* obj2) {
			T& tObj1 = *((T*)obj1);
			T& tObj2 = *((T*)obj2);
			if(tObj1 < tObj2) {
				return -1;
			}
			if(tObj1 > tObj2) {
				return 1;
			}
			return 0;
		}

		template<class T>
		void std_qsort(T* array, size_t length) {
			std::qsort(array, length, sizeof(T), compare<T>);
		}

		template<class T>
		void std_sort(T* array, size_t length) {
			std::sort(array, array + length);
		}

		template<class T>
		void std_stable_sort(T* array, size_t length) {
			std::stable_sort(array, array + length);
		}

		/*template<class T>
		void sfz_concurrentQuicksort1Thread(T* array, size_t length) {
			sfz::concurrentQuicksort(array, length, 1);
		}

		template<class T>
		void sfz_concurrentQuicksort2Threads(T* array, size_t length) {
			sfz::concurrentQuicksort(array, length, 2);
		}

		template<class T>
		void sfz_concurrentQuicksort4Threads(T* array, size_t length) {
			sfz::concurrentQuicksort(array, length, 4);
		}

		template<class T>
		void sfz_concurrentQuicksort8Threads(T* array, size_t length) {
			sfz::concurrentQuicksort(array, length, 8);
		}*/


		
		// Test functions
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		template<class T>
		sfz::StopWatch sortArray(T* array, size_t length, void(*sort)(T*,size_t)) {
			sfz::StopWatch clock;
			sort(array, length);
			clock.stop();
			return clock;
		}

		template<class T>
		int isArraySorted(T* array, size_t length) {
			for(size_t i = 0; i < length-1; i++) {
				if(array[i] > array[i+1]) {
					return i;
				}
			}
			return -1;
		}

		template<class T>
		void isArraySortedTest(T* array, size_t length) {
			int i = isArraySorted(array, length);
			if(i != -1) {
				std::cout << "Array NOT SORTED! array[" << i << "] = "
				          << array[i] << ", array[" << i+1 << "] = " << array[i+1] << std::endl;
			}
		}

		template<class T>
		void test(T*(*arrayCreator)(size_t), void(*sort)(T*,size_t), size_t length) {
			T* array = arrayCreator(length);
			printTime(sortArray(array, length, sort));
			isArraySortedTest(array, length);
			delete[] array;
		}

		template<class T>
		void testMany(std::string title, T*(*arrayCreator)(size_t), size_t length) {
			std::cout << title << ", length: " << length << "\n";

			//std::cout << "                  sfz::insertionsort(): ";
			//test(arrayCreator, sfz::insertionsort, length);

			//std::cout << "                      sfz::quicksort():  ";
			//test(arrayCreator, quicksort, length);

			/*std::cout << " sfz::concurrentQuicksort() (1 thread):  ";
			test(arrayCreator, sfz_concurrentQuicksort1Thread, length);

			std::cout << "sfz::concurrentQuicksort() (2 threads):  ";
			test(arrayCreator, sfz_concurrentQuicksort2Threads, length);

			std::cout << "sfz::concurrentQuicksort() (4 threads):  ";
			test(arrayCreator, sfz_concurrentQuicksort4Threads, length);

			std::cout << "sfz::concurrentQuicksort() (8 threads):  ";
			test(arrayCreator, sfz_concurrentQuicksort8Threads, length);*/

			std::cout << "                          std::qsort():  ";
			test(arrayCreator, std_qsort, length);

			std::cout << "                           std::sort():  ";
			test(arrayCreator, std_sort, length);

			std::cout << "                    std::stable_sort():  ";
			test(arrayCreator, std_stable_sort, length);

			std::cout << "\n";
		}

		// Array creation functions
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		int* createArrayWithRandomNumbers(size_t length, int min, int max) {
			std::mt19937_64 ms; //64bit Mersenne Twister
			ms.seed(1337); //We always want the same random numbers, so we always use this seed.
			std::uniform_int_distribution<int> dist{min, max};
			int* array = new int[length];
			for(size_t i = 0; i < length; i++) {
				array[i] = dist(ms);
			}
			return array;
		}

		int* randomNumberArray(size_t length) {
			return createArrayWithRandomNumbers(length, -1000, 1000);
		}

		int* randomNumberArraySparse(size_t length) {
			return createArrayWithRandomNumbers(length, -1000000000, 1000000000);
		}

		int* binaryNumberArray(size_t length) {
			return createArrayWithRandomNumbers(length, 0, 1);
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
	}


	// Visible functions
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *	

	void runSortingPerformanceTest() {
		testMany("### Array with limited random numbers", randomNumberArray, 500000);

		testMany("### Array with sparse random numbers", randomNumberArraySparse, 500000);

		testMany("### Array with binary numbers", binaryNumberArray, 500000);

		testMany("### Array with sorted numbers", sortedNumberArray, 1000000);

		testMany("### Array with reversed sorted numbers", reverseSortedNumberArray, 500000);
	}
}
