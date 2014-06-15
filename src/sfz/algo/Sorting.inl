namespace sfz {

	// Anonymous helper functions
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	namespace {
			
		// Returns the index to the median of low, mid and high as the pivot value.
		template<class T>
		inline size_t pivotMedianOfThreeInPlace(T* array, size_t low, size_t high) {
			size_t mid = low + ((high-low)/2);

			//Sorts the indexes
			if(array[low] > array[mid]) {
				swap(array[low], array[mid]);
				//swap(array, low, mid);
			}
			if(array[low] > array[high]) {
				swap(array[low], array[high]);
				//swap(array, low, high);
			}
			if(array[mid] > array[high]) {
				swap(array[mid], array[high]);
				//swap(array, mid, high);
			}

			return mid;
		}

		const size_t INSERTIONSORT_TRESHOLD = 7;

		// Internal quicksort recursive loop
		template<class T>
		void quicksort(T* array, size_t lowIndex, size_t highIndex) {

			size_t intervalLength = highIndex-lowIndex+1;

			if(intervalLength <= 0) {
				return;
			}

			// Does an insertion sort if length of interval is shorter than treshold.
			if(intervalLength < INSERTIONSORT_TRESHOLD) {
				//insertionsort(array + lowIndex, intervalLength);
				insertionSort(array + lowIndex, array + lowIndex + intervalLength);
				return;
			}

			// Finds pivot and moves it to end of array.
			//swap(array, pivotMedianOfThreeInPlace(array, lowIndex, highIndex), highIndex);
			swap(array[pivotMedianOfThreeInPlace(array, lowIndex, highIndex)], array[highIndex]);
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
					swap(array[i], array[--equalStore]);
					//swap(array, i, --equalStore);
				}
				// Moves smaller element to beginning of array (highest in smaller store).
				else if(array[i] < pivotValue) {
					swap(array[i++], array[++smallerStore]);
					//swap(array, i++, ++smallerStore);
				}
				else {
					i++;
				}
			}

			// Moves equal store to the middle of the array right after smaller store.
			size_t equalMiddleStore = smallerStore + 1; // Index to element at top of new equal store.
			for(size_t i = equalStore; i <= highIndex; i++) {
				swap(array[i], array[equalMiddleStore++]);
				//swap(array, i, equalMiddleStore++);
			}

			// Recursive call with larger and smaller store part of array.
			quicksort(array, lowIndex, smallerStore);
			quicksort(array, equalMiddleStore, highIndex);
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
	
	/*
	 * Implementation of functions from Sorting.hpp
	 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	 */

	template<typename T>
	void quicksort(T* array, const size_t length) {
		if(array == nullptr) {
			throw std::invalid_argument{"Array == nullptr."};
		}
		if(length <= 1) {
			return;
		}
		quicksort(array, 0, length-1);
	}
	
	template<class T>
	void insertionsort(T* array, const size_t length) {
		for(int i = 0; i < length; i++) {
			int j = i;
			while(j > 0 && array[j-1] > array[j]) {
				swap(array[j - 1], array[j]);
				//swap(array, j-1, j);
				j--;
			}
		}
	}


	template<typename RandomIt>
	void insertionSort(RandomIt first, RandomIt last) {
		insertionsort(first, last - first);
	}

	template<typename RandomIt>
	void quickSort(RandomIt first, RandomIt last) {
		quicksort(first, last - first);
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
