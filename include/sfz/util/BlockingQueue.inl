namespace sfz {

	template<typename T>
	BlockingQueue<T>::BlockingQueue() {
		// Do nothing.
	}

	template<typename T>
	BlockingQueue<T>::~BlockingQueue() {
		// Do nothing.
	}

	template<typename T>
	void BlockingQueue<T>::push(const T& element) {
		std::lock_guard<std::mutex> lock{queueMutex};
		queue.push(element);
		queueCond.notify_one();
	} 

	template<typename T>
	T BlockingQueue<T>::pop() {
		std::unique_lock<std::mutex> lock{queueMutex};
		queueCond.wait(lock, [this]() { return !queue.empty(); });
		T poppedObject{std::move(queue.front())};
		queue.pop();
		return std::move(poppedObject);
	}

	template<typename T>
	std::unique_ptr<T> BlockingQueue<T>::tryPop() {
		std::lock_guard<std::mutex> lock{queueMutex};
		if(queue.empty()) {
			return std::move(std::unique_ptr<T>{});
		}
		std::unique_ptr<T> ptr{new T{queue.front()}};
		queue.pop();
		return std::move(ptr);
	}

	template<typename T>
	bool BlockingQueue<T>::empty() const {
		std::lock_guard<std::mutex> lock{queueMutex};
		return queue.empty();
	}
}