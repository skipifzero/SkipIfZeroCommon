#include "ScopedThread.hpp"

namespace sfz {

	ScopedThread::ScopedThread(std::thread t) :
		thread{std::move(t)} {
			if(!thread.joinable()) {
				throw std::invalid_argument{"Thread not joinable."};
			}
	}

	ScopedThread::~ScopedThread() {
		thread.join();
	}

	std::thread::id ScopedThread::getID() const {
		return thread.get_id();
	}
}