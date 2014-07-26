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
			size_t intervalLength = last - first;

			// End condition, if there is just one or less elements left then the interval must be correctly sorted.
			if(intervalLength <= 1) {
				return;
			}

			// Does an insertionsort on interval if length is less than the INSERTIONSORT_TRESHOLD constant.
			if(intervalLength < INSERTIONSORT_TRESHOLD) {
				insertionsort(first, last);
				return;
			}
			
			// Partitions the sequence and places all elements smaller than the pivot in the beginning of the sequence
			// and all elements larger than the pivot in the end of the sequence. The 'midFirst' iterator will point
			// to the first element equal to the pivot, the 'midLast' iterator will point to the first large element
			// after the last equal element.
			T pivot = findPivot(first, last);
			RandomIt midFirst = std::partition(first, last, [&pivot](const T& element) { return element < pivot; });
			RandomIt midLast = std::partition(midFirst, last, [&pivot](const T& element) { return element <= pivot; });
		 	
			quicksortInner(first, midFirst);
			quicksortInner(midLast, last);
		}

		const size_t PARALLELIZATION_TRESHOLD = 25000;

		template<typename RandomIt>
		void parallelQuicksortInner(RandomIt first, RandomIt last, size_t threadsLeft) {
			using T = typename std::iterator_traits<RandomIt>::value_type;
			size_t intervalLength = last - first;

			// End condition, if there is just one or less elements left then the interval must be correctly sorted.
			if(intervalLength <= 1) {
				return;
			}

			// Does an insertionsort on interval if length is less than the INSERTIONSORT_TRESHOLD constant.
			if(intervalLength < INSERTIONSORT_TRESHOLD) {
				insertionsort(first, last);
				return;
			}
			
			// Partitions the sequence and places all elements smaller than the pivot in the beginning of the sequence
			// and all elements larger than the pivot in the end of the sequence. The 'midFirst' iterator will point
			// to the first element equal to the pivot, the 'midLast' iterator will point to the first large element
			// after the last equal element.
			T pivot = findPivot(first, last);
			RandomIt midFirst = std::partition(first, last, [&pivot](const T& element) { return element < pivot; });
			RandomIt midLast = std::partition(midFirst, last, [&pivot](const T& element) { return element <= pivot; });
		 	
		 	// Computes in parallel if there are threads left and interval is longer than the threshold constant. The
		 	// amount of threads created might actually be larger than the specified numThreads parameter due to the 
		 	// way this is implemented.
			if(threadsLeft < 1 || intervalLength < PARALLELIZATION_TRESHOLD) {
				parallelQuicksortInner(first, midFirst, threadsLeft);
		 		parallelQuicksortInner(midLast, last, threadsLeft);
			} else {
				//sfz::ScopedThread{std::thread{parallelQuicksortInner<RandomIt>, first, midFirst, threadsLeft-1}};
				//parallelQuicksortInner(midLast, last, threadsLeft-1);
				sfz::ScopedThread{std::thread{parallelQuicksortInner<RandomIt>, first, midFirst, threadsLeft-2}};
				sfz::ScopedThread{std::thread{parallelQuicksortInner<RandomIt>, midLast, last, threadsLeft-2}};
			}
		}
	}

	// Implementation of functions defined in Sorting.hpp
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	
	template<typename RandomIt>
	void insertionsort(RandomIt first, RandomIt last) {
		if(last <= first) {
			throw std::invalid_argument("first >= last");
		}
		for(auto itr = first; itr < last; itr++) {
			auto insertionPoint = std::upper_bound(first, itr, *itr); // Itr to first element greater than *itr
			std::rotate(insertionPoint, itr, itr+1);
		}
	}

	template<typename RandomIt>
	void quicksort(RandomIt first, RandomIt last) {
		if(last <= first) {
			throw std::invalid_argument("first >= last");
		}
		quicksortInner(first, last);
	}

	template<typename RandomIt>
	void parallelQuicksort(RandomIt first, RandomIt last, size_t numThreads) {
		if(last <= first) {
			throw std::invalid_argument("first >= last");
		}
		// If no information on how many cores is available we can probably assume that the machine is old with no
		// hardware concurrency. So we set the number of threads to 1.
		if(numThreads == 0) {
			numThreads = 1;
		}
		parallelQuicksortInner(first, last, numThreads);
	}
}
