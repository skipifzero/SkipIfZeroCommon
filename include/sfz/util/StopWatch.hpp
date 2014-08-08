#pragma once
#ifndef SFZ_UTIL_STOP_WATCH_HPP
#define SFZ_UTIL_STOP_WATCH_HPP

#include <chrono>

namespace sfz {

	/**
	 * @brief Utility class for measuring time intervals.
	 * 
	 * A simple class implemented using the standard library that helps measuring time intervals with the highest
	 * precision available.
	 *
	 * @author Peter Hillerström <peter@hstroem.se>
	 * @date 2014-06-07
	 */
	class StopWatch final {
	public:

		/**
		 * @brief Creates a new StopWatch, automatically calls start().
		 * @see StopWatch::start()
		 */
		StopWatch();
		~StopWatch() = default;

		/**
		 * @brief Starts the StopWatch.
		 * Sets the start time to current time.
		 */
		void start();
		
		/**
		 * @brief Stops the StopWatch.
		 * Sets the stop time to current time. After this function has been called the StopWatch will return the time
		 * between the start time and stop time until it has been stopped or started again.
		 */
		void stop();
		
		/**
		 * @brief Returns the time in seconds.
		 * If the StopWatch has been stopped (and not started since) this function will return the time between the
		 * latest start and stop times. Otherwise it will return the time between latest start and current time.
		 * @return time in seconds
		 */
		std::chrono::seconds getTimeSeconds();
		
		/**
		 * @brief Returns the time in milliseconds.
		 * If the StopWatch has been stopped (and not started since) this function will return the time between the
		 * latest start and stop times. Otherwise it will return the time between latest start and current time.
		 * @return time in milliseconds
		 */
		std::chrono::milliseconds getTimeMilliSeconds();
		
		/**
		 * @brief Returns the time in nanoseconds.
		 * If the StopWatch has been stopped (and not started since) this function will return the time between the
		 * latest start and stop times. Otherwise it will return the time between latest start and current time.
		 * @return time in nanoseconds
		 */
		std::chrono::nanoseconds getTimeNanoSeconds();
	
	private:
		bool hasTime;
		std::chrono::high_resolution_clock::time_point startTime, stopTime;
	};
}
#endif