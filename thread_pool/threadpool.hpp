#include <functional>         // std::function
#include <vector>             // std::vector
#include <queue>              // std::queue
#include <thread>             // std::thread
#include <mutex>              // std::mutex
#include <condition_variable> // std::condition_variable

class ThreadPool {
public:
  // -- Declare De/Constructors
  ThreadPool();
  ThreadPool(unsigned int);
  ~ThreadPool();

  // -- Declare Methods
  void jobDispatcher();
  void addJob(std::function<void()>);
  void start();
  void shutdown();

private:
  // -- Setup Storage Structures
  std::vector<std::thread> workers;
  std::queue<std::function<void()>> jobs;
  unsigned int maxThreads;

  // -- Setup Mutexs
  std::mutex queueMutex;
  std::mutex threadPoolMutex;
  std::condition_variable condition;

  // -- Setup State Variables
  bool terminatePool;
  bool stopped;
};
