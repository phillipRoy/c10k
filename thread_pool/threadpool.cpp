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
    {
      std::unique_lock<std::mutex> lock(queueMutext);

      condition.wait(lock, []{return !jobs.empty() || terminatePool});

      std::function<void()> job = jobs.front();
      jobs.pop();
    }
    job();
  }
}

void ThreadPool::addJob(std::function<void()> job) {

}

void ThreadPool::start() {

}

void ThreadPool::shutdown() {

}
