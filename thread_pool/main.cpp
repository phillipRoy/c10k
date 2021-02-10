#include "threadpool.hpp"

#include <chrono>
#include <iostream>

void count_really_high() {
    for(unsigned i(0); i < 1000000; i++)
        continue;
    std::cout << "Finish" << std::endl;
}

void threadpool_demo() {
    {
        ThreadPool tp; 
        
        tp.addJob(count_really_high);
        tp.addJob(count_really_high);
        tp.addJob(count_really_high);
        tp.addJob(count_really_high);
  
        tp.addJob(count_really_high);
        tp.addJob(count_really_high);
        tp.addJob(count_really_high);
        tp.addJob(count_really_high);
  
        tp.start(); 
    }
}

void n_thread_demo() {
    std::vector<std::thread> thread_vector;
    for(unsigned i(0); i < 8; i++) {
        thread_vector.emplace_back(count_really_high);
        thread_vector[i].join();
    }
}

int main() {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    
    //n_thread_demo();
    threadpool_demo();
    
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
  
    return 0;
}
