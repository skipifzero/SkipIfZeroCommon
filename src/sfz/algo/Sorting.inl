namespace sfz {

	// Anonymous helper functions
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	namespace {

		template<typename T>
		T& median(const T& a, const T& b, const T& c) {
			return const_cast<T&>(max(min(a, b), min(max(a, b), c)));
		}

		const size_t INSERTIONSORT_TRESHOLD = 25;

		template<typename RandomIt>
		void quicksortInner(RandomIt first, RandomIt last) {

			auto lastIncl = last-1; // RandomIt to inclusive end of sequence.
			auto intervalLength = last - first;

			// End condition, if there is just one or less elements left then the interval must be correctly sorted.
			if(intervalLength <= 1) {
				return;
			}

			// Does an insertionsort on interval if length is less than the INSERTIONSORT_TRESHOLD constant.
			if(intervalLength < INSERTIONSORT_TRESHOLD) {
				insertionsort(first, last);
				return;
			}

			// Finds the median of first, middle and last (inclusive) elements in sequence. Then selects the median as
			// pivot element and moves it to the end of the sequence.
			auto mid = first + (intervalLength/2);
			swap(median(*lastIncl, *first, *mid), *lastIncl);
			
			// RandomIt to where next smaller and equal elements should be placed.
			auto smallerStore = first;
			auto equalStore = lastIncl-1;
			
			// Places all elements smaller than pivot in beginning of the sequence and all elements equal to the pivot
			// in the end of the sequence.
			for(auto itr = smallerStore; itr <= equalStore; ) {
				if(*itr < *lastIncl) {
					swap(*itr, *smallerStore);
					smallerStore++;
					itr++;
				} else if(*itr > *lastIncl) {
					itr++;
				} else {
					// In this case we don't increment the iterator since the value swapped down has not yet been
					// compared with the pivot element.
					swap(*itr, *equalStore);
					equalStore--;
				}
			}

			// Moves elements equal to pivot to the middle of the sequence.
			auto newEqualStore = smallerStore;
			equalStore++;
			while(equalStore < last) {
				swap(*newEqualStore, *equalStore);
				newEqualStore++;
				equalStore++;
			}

			// Starts new quicksort iterations on the larger and smaller parts of the sequence. Note that we use
			// smallerStore instead of smallerStore-1 since the 'last' iterator should point to the (potentially
			// non-existing) element after the last inclusive element.
			quicksortInner(first, smallerStore);
			quicksortInner(newEqualStore, last);
		}

		template<typename RandomIt>
		struct qsRecursionData {
			qsRecursionData(RandomIt first, RandomIt last) :
				first{first},
				last{last} {
					// Do nothing.
			}
			RandomIt first, last;
		};

		const size_t PARALLELISATION_TRESHOLD = 40000;

		template<typename RandomIt>
		void parallelQuicksortInner(qsRecursionData<RandomIt> data) {
			auto first = data.first;
			auto last = data.last;
			auto lastIncl = last-1; // RandomIt to inclusive end of sequence.
			auto intervalLength = last - first;

			// End condition, if there is just one or less elements left then the interval must be correctly sorted.
			if(intervalLength <= 1) {
				return;
			}

			// Does an insertionsort on interval if length is less than the INSERTIONSORT_TRESHOLD constant.
			if(intervalLength < INSERTIONSORT_TRESHOLD) {
				insertionsort(first, last);
				return;
			}

			// Finds the median of first, middle and last (inclusive) elements in sequence. Then selects the median as
			// pivot element and moves it to the end of the sequence.
			auto mid = first + (intervalLength/2);
			swap(median(*lastIncl, *first, *mid), *lastIncl);
			
			// RandomIt to where next smaller and equal elements should be placed.
			auto smallerStore = first;
			auto equalStore = lastIncl-1;
			
			// Places all elements smaller than pivot in beginning of the sequence and all elements equal to the pivot
			// in the end of the sequence.
			for(auto itr = smallerStore; itr <= equalStore; ) {
				if(*itr < *lastIncl) {
					swap(*itr, *smallerStore);
					smallerStore++;
					itr++;
				} else if(*itr > *lastIncl) {
					itr++;
				} else {
					// In this case we don't increment the iterator since the value swapped down has not yet been
					// compared with the pivot element.
					swap(*itr, *equalStore);
					equalStore--;
				}
			}

			// Moves elements equal to pivot to the middle of the sequence.
			auto newEqualStore = smallerStore;
			equalStore++;
			while(equalStore < last) {
				swap(*newEqualStore, *equalStore);
				newEqualStore++;
				equalStore++;
			}

			// Starts new quicksort iterations on the larger and smaller parts of the sequence. Note that we use
			// smallerStore instead of smallerStore-1 since the 'last' iterator should point to the (potentially
			// non-existing) element after the last inclusive element.
			if(intervalLength < PARALLELISATION_TRESHOLD) {
				quicksortInner(first, smallerStore);
				quicksortInner(newEqualStore, last);
			} else {
				qsRecursionData<RandomIt> lowerBounds{first, smallerStore};
				std::thread lowerThread{[lowerBounds]() {
					parallelQuicksortInner(lowerBounds);
				}};
				qsRecursionData<RandomIt> higherBounds{newEqualStore, last};
				std::thread higherThread{[higherBounds]() {
					parallelQuicksortInner(higherBounds);
				}};
				lowerThread.join();
				higherThread.join();
			}
		}

		/*template<class T>
		struct qsRecursionData {
			WorkerPool<struct qsRecursionData>* workerPool;
			T* array;
			size_t lowIndex, highIndex;
		};

		template<class T>
		void quicksortConcurrent(struct qsRecursionData<T> data) {
			
			T* array = data.array;
			size_t highIndex = data.highIndex;
			size_t lowIndex = data.lowIndex;
			size_t intervalLength = highIndex-lowIndex+1;

			if(intervalLength <= 0) {
				return;
			}

			// Does an insertion sort if length of interval is shorter than treshold.
			if(intervalLength < INSERTIONSORT_TRESHOLD) {
				insertionsort(array + lowIndex, intervalLength);
				return;
			}

			// Finds pivot and moves it to end of array.
			swap(array, pivotMedianOfThreeInPlace(array, lowIndex, highIndex), highIndex);
			T& pivotValue = array[highIndex];

			// The most complicated part, basically what we want to accomplish is splitting the array into three parts.
			// Smaller than pivot, equal to pivot and larger than pivot, in that order. We do this by iterating through
			// the array, moving all smaller elements to the beginning of they array and all equal elements to the end
			// of it.
			int smallerStore = lowIndex-1; // Index to element at top of smaller store
			size_t equalStore = highIndex; // Index to element at bottom of equal store (pivot element).
			for(size_t i = smallerStore+1; i < equalStore; ) {
				// Moves equal element to end of array (lowest in equal store).
				if(array[i] == pivotValue) {
					swap(array, i, --equalStore);
				}
				// Moves smaller element to beginning of array (highest in smaller store).
				else if(array[i] < pivotValue) {
					swap(array, i++, ++smallerStore);
				}
				else {
					i++;
				}
			}

			// Moves equal store to the middle of the array right after smaller store.
			size_t equalMiddleStore = smallerStore + 1; // Index to element at top of new equal store.
			for(size_t i = equalStore; i <= highIndex; i++) {
				swap(array, i, equalMiddleStore++);
			}

			struct qsRecursionData<T> smallerData = data;
			smallerData.highIndex = smallerStore;

			struct qsRecursionData<T> largerData = data;
			largerData.lowIndex = equalMiddleStore;

			data.workerPool->bufferTask(smallerData);
			data.workerPool->bufferTask(largerData);
		}*/
	}

	// Implementation of functions defined in Sorting.hpp
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	
	template<typename RandomIt>
	void quicksort(RandomIt first, RandomIt last) {
		if(last <= first) {
			throw std::invalid_argument("first >= last");
		}
		quicksortInner(first, last);
	}

	template<typename RandomIt>
	void parallelQuicksort(RandomIt first, RandomIt last, const size_t numThreads) {
		if(last <= first) {
			throw std::invalid_argument("first >= last");
		}
		parallelQuicksortInner(qsRecursionData<RandomIt>{first, last});
	}

	template<typename RandomIt>
	void insertionsort(RandomIt first, RandomIt last) {
		if(last <= first) {
			throw std::invalid_argument("first >= last");
		}
		for(size_t i = 1; i < last - first; i++) {
			for(size_t j = i; j > 0 && first[j-1] > first[j]; j--) {
				swap(first[j-1], first[j]);
			}
		}
	}

	/*template<class T>
	void concurrentQuicksort(T* array, const size_t length, const size_t numThreads) {
		if(array == nullptr) {
			throw std::invalid_argument{"Array == nullptr."};
		}
		if(numThreads < 1) {
			throw std::invalid_argument("Must have at least one thread.");
		}
		if(length <= 1) {
			return;
		}
		
		sfz::WorkerPool<struct qsRecursionData<T>> workerPool{quicksortConcurrent<T>, numThreads};
		
		struct qsRecursionData<T> initalData;
		initalData.workerPool = &workerPool;
		initalData.array = array;
		initalData.lowIndex = 0;
		initalData.highIndex = length-1;

		workerPool.bufferTask(initalData);

		workerPool.awaitIdle();
	}*/
}
