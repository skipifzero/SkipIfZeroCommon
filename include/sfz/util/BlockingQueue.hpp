#pragma once
#ifndef SFZ_UTIL_BLOCKING_QUEUE_HPP
#define SFZ_UTIL_BLOCKING_QUEUE_HPP

#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>

namespace sfz {

	template<typename T>
	class BlockingQueue {
	public:
		
		BlockingQueue();

		// No copy constructor.
		BlockingQueue(const BlockingQueue&) = delete;
		
		virtual ~BlockingQueue();
		
		void push(const T& element);

		std::unique_ptr<T> pop();

		std::unique_ptr<T> tryPop();

		bool empty() const;

		// No assignment.
		BlockingQueue& operator= (const BlockingQueue&) = delete;

	private:
		std::queue<T> queue;
		mutable std::mutex queueMutex;
		std::condition_variable queueCond;
	};
}
#include "BlockingQueue.inl"
#endif