#include <thread>
#include <vector>
#include <iostream>

// -- Do Something
void uselessOperation() {
  for(unsigned x(0); x < 1000000; x++) {
    continue;
  }
}


int main() {

  // -- Setup for Threading
  const unsigned int CLIENTS = 10000;
  std::vector<std::thread> thread_list;

  // -- Spawn and Join Threads
  for(unsigned x(0); x < CLIENTS; x++) {
    thread_list.emplace_back(uselessOperation);
    thread_list[x].join();
  }

  // -- Free Thread Handles
  thread_list.empty();

  return 0;
}
