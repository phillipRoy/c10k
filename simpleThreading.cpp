#include <thread>
#include <vector>

// -- Do Something
void uselessOperation() {
  const int a(2), b(2);
  a + b;
}


int main() {

  // -- Setup for Threading
  const unsigned int CLIENTS = 10000;
  std::vector<std::thread> thread_list;

  // -- Spawn and Join Threads
  for(unsigned x(0); x < CLIENTS; x++) {
    std::thread a(uselessOperation);
    a.join();
    thread_list.push_back(a);
  }

  // -- Free Thread Handles
  thread_list.empty();
  return 0;
}
