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

}

void ThreadPool::addJob(std::function<void()> job) {

}

void ThreadPool::start() {

}

void ThreadPool::shutdown() {

}
