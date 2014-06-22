namespace sfz {



	template<typename TaskData>
	ThreadPool<TaskData>::ThreadPool(function<void(TaskData)> taskLogic, const size_t numWorkers) :
		taskLogic{taskLogic},
		numWorkers{numWorkers},
		idleWorkers{numWorkers},
		killSignal{false},
		isIdling{false} {

			//std::cout <<"\n\nThreadPool constructor hello, numWorkers = " << numWorkers << "\n";

			for(size_t i = 0; i < numWorkers; i++) {
				workers.emplace_back( [&]() {

					TaskData data;
					while(!killSignal) {

						bool hasData = false;
						taskBufferMutex.lock();
						
						if(taskBuffer.size() > 0) {
							data = taskBuffer.front();
							taskBuffer.pop();
							hasData = true;
							idleWorkers--;
						}
						
						if(taskBuffer.size() == 0 && idleWorkers == numWorkers) {
							if(!isIdling) {
								//std::cout << "Entering idling state\n";
							}
							isIdling = true;
						}

						taskBufferMutex.unlock();

						if(hasData) {
							//std::cout << "Proccessing data\n";
							taskLogic(data);
							idleWorkers++;
						}
					}
					//std::cout << "Worker killed\n";
				});
			}
	}

	template<typename TaskData>
	ThreadPool<TaskData>::~ThreadPool() {
		killSignal = true;
		for(auto& worker : workers) {
			worker.join();
			//std::cout << "Joined worker\n";
		}
		//std::cout << "ThreadPool destructor success, time: ";
	}

	template<typename TaskData>
	void ThreadPool<TaskData>::addTask(TaskData data) {
		taskBufferMutex.lock();
		isIdling = false;
		taskBuffer.push(data);
		taskBufferMutex.unlock();
	}

	template<typename TaskData>
	void ThreadPool<TaskData>::awaitIdle() {
		while(!isIdling) {
			// Wait.
		}
		//std::cout << "awaitIdle() DONE\n";
	}
}