namespace sfz {

	// Anonymous helper functions
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	namespace {

		template<typename T>
		T& median(const T& a, const T& b, const T& c) {
			return const_cast<T&>(max(min(a, b), min(max(a, b), c)));
		}

		template<typename RandomIt>
		auto findPivot(RandomIt first, RandomIt last) -> typename std::iterator_traits<RandomIt>::value_type& {
			RandomIt mid = first + (std::distance(first, last)/2);
			return median(*(last-1), *first, *mid);
		}

		const size_t INSERTIONSORT_TRESHOLD = 15;

		template<typename RandomIt>
		void quicksortInner(RandomIt first, RandomIt last) {
			using T = typename std::iterator_traits<RandomIt>::value_type;
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
			
			// Partitions the sequence and places all elements smaller than the pivot in the beginning of the sequence and
			// all elements larger than the pivot in the end of the sequence. The 'midFirst' iterator will point to the
			// first element equal to the pivot, the 'midLast' iterator will point to the first large element after the
			// last equal element.
			T pivot = findPivot(first, last);
			RandomIt midFirst = std::partition(first, last, [&pivot](const T& element) { return element < pivot; });
			RandomIt midLast = std::partition(midFirst, last, [&pivot](const T& element) { return element <= pivot; });
		 	
			quicksortInner(first, midFirst);
			quicksortInner(midLast, last);
		}

		template<typename RandomIt>
		struct QSRecursionData {
			QSRecursionData() :
				threadPool{nullptr} {
					// Do nothing.
			}
			QSRecursionData(RandomIt first, RandomIt last, ThreadPool<QSRecursionData<RandomIt>>& threadPool) :
				first{first},
				last{last},
				threadPool{&threadPool} {
					// Do nothing.
			}
			QSRecursionData(const QSRecursionData<RandomIt>& qsRecursionData) :
				first{qsRecursionData.first},
				last{qsRecursionData.last},
				threadPool{qsRecursionData.threadPool} {
					// Do nothing.
			}
			RandomIt first, last;
			ThreadPool<QSRecursionData>* threadPool;
		};

		template<typename RandomIt>
		void parallelQuicksortInner(QSRecursionData<RandomIt> data) {
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
			QSRecursionData<RandomIt> lowerBounds{first, smallerStore, *data.threadPool};
			data.threadPool->addTask(lowerBounds);
			QSRecursionData<RandomIt> higherBounds{newEqualStore, last, *data.threadPool};
			data.threadPool->addTask(higherBounds);
		}
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
	void parallelQuicksort(RandomIt first, RandomIt last) {
		size_t numThreads = std::thread::hardware_concurrency();
		// If no information on how many cores is available we can probably assume that the machine is old with no
		// hardware concurrency. So we set the number of threads to 1.
		if(numThreads == 0) {
			numThreads = 1;
		}
		parallelQuicksort(first, last, numThreads);
	}

	template<typename RandomIt>
	void parallelQuicksort(RandomIt first, RandomIt last, const size_t numThreads) {
		if(last <= first) {
			throw std::invalid_argument("first >= last");
		}
		ThreadPool<QSRecursionData<RandomIt>> threadPool{parallelQuicksortInner<RandomIt>, numThreads};
		QSRecursionData<RandomIt> initalData{first, last, threadPool};
		threadPool.addTask(initalData);
		threadPool.awaitIdle();
	}

	template<typename RandomIt>
	void insertionsort(RandomIt first, RandomIt last) {
		if(last <= first) {
			throw std::invalid_argument("first >= last");
		}
		// For some reason this is needed if we want fast performance on already sorted arrays.
		if(std::is_sorted(first,last)) {
			return;
		}
		for(auto itr = first; itr < last; itr++) {
			auto insertionPoint = std::upper_bound(first, itr, *itr); // Itr to first element greater than *itr
			std::rotate(insertionPoint, itr, itr+1);
		}
	}
}
