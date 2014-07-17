#pragma once
#ifndef SFZ_UTIL_THREAD_POOL_HPP
#define SFZ_UTIL_THREAD_POOL_HPP

#include <thread>
#include <mutex>
#include <atomic>
#include <functional>
#include <vector>
#include <queue>

#include <iostream>

namespace sfz {
	using std::size_t;
	using std::function;

	template<typename TaskData>
	class ThreadPool {
	public:
		ThreadPool(function<void(TaskData)> taskLogic, const size_t numWorkers = std::thread::hardware_concurrency());
		virtual ~ThreadPool();
		void addTask(TaskData data);
		void awaitIdle();
	private:
		function<void(TaskData)> taskLogic;
		const size_t numWorkers;
		std::vector<std::thread> workers;
		std::queue<TaskData> taskBuffer;
		std::mutex taskBufferMutex;
		std::atomic_size_t idleWorkers;
		volatile std::atomic_bool killSignal, isIdling;
	};
}
#include "ThreadPool.inl"
#endif