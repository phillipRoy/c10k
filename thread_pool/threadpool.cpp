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
      std::unique_lock<std::mutex> lock(queueMutex);

      condition.wait(lock, [&]{return !jobs.empty() || terminatePool;});

      std::function<void()> job = jobs.front();
      jobs.pop();
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

}
