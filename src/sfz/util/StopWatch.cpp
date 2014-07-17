#include "sfz/util/StopWatch.hpp"

namespace sfz {

	StopWatch::StopWatch() {
		start();
	}

	void StopWatch::start() {
		hasTime = false;
		startTime = std::chrono::high_resolution_clock::now();
	}

	void StopWatch::stop() {
		hasTime = true;
		stopTime = std::chrono::high_resolution_clock::now();
	}

	std::chrono::seconds StopWatch::getTimeSeconds() {
		if(!hasTime) {
			stopTime = std::chrono::high_resolution_clock::now();
		}
		return std::chrono::duration_cast<std::chrono::seconds>(stopTime - startTime);
	}
	
	std::chrono::milliseconds StopWatch::getTimeMilliSeconds() {
		if(!hasTime) {
			stopTime = std::chrono::high_resolution_clock::now();
		}
		return std::chrono::duration_cast<std::chrono::milliseconds>(stopTime - startTime);
	}
	
	std::chrono::nanoseconds StopWatch::getTimeNanoSeconds() {
		if(!hasTime) {
			stopTime = std::chrono::high_resolution_clock::now();
		}
		return std::chrono::duration_cast<std::chrono::nanoseconds>(stopTime - startTime);
	}
}