#include "threadpool.hpp"

// -- Define De/Constructors
ThreadPool::ThreadPool()
  : maxThreads(4)
{}

ThreadPool::ThreadPool(unsigned int numThreads)
  : maxThreads(numThreads)
{}

ThreadPool::~ThreadPool() {
  if(!stopped) {
    shutdown();
  }
}

// -- Define Methods
void ThreadPool::jobDispatcher() {
  while(true) {
      std::function<void()> job;
      {
        std::unique_lock<std::mutex> lock(queueMutex);

        condition.wait(lock, [&]{return !jobs.empty() || terminatePool;});
        
        if (jobs.empty())
            return;
        job = jobs.front();
        
        jobs.pop();
      }
      job();
  }
}

void ThreadPool::addJob(std::function<void()> job) {
  {
    std::unique_lock<std::mutex> lock(queueMutex);
    jobs.push(job);
  }
  condition.notify_one();
}

void ThreadPool::start() {
  for(unsigned x(0); x < maxThreads; x++) {
    workers.emplace_back(&ThreadPool::jobDispatcher, this);
  }
}

void ThreadPool::shutdown() {
    std::unique_lock<std::mutex> lock(threadPoolMutex);
    terminatePool = true;
    
    condition.notify_all();
    
    for(std::thread &every_thread : workers)
        every_thread.join();
        
    workers.clear();
    stopped = true; 
}