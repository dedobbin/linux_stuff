#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

#define NUM_THREADS 10

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void worker_thread(int id) {
    // This is the "work"
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::unique_lock<std::mutex> lock(mtx);
    ready = true;

    cv.notify_all();
    
    std::cout << "Worker thread " << id << " finished its work\n";
}

int main() 
{
    std::thread workers[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; ++i) {
        workers[i] = std::thread(worker_thread, i);
    }

    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, []{ return ready; });
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        workers[i].join();
    }

    std::cout << "teh end\n";

    return 0;
}