#include <iostream>
#include <vector>
#include <chrono>

constexpr int PAGE_SIZE = 4096; // Assuming a page size of 4KB

void sequentialAccess(const std::vector<int>& data) {
    int sum = 0;
    for (size_t i = 0; i < data.size(); ++i) {
        sum += data[i];
    }
    std::cout << "Sequential access sum: " << sum << std::endl;
}

void randomAccess(const std::vector<int>& data) {
    int sum = 0;
    for (size_t i = 0; i < data.size(); ++i) {
        size_t index = (13 * i) % data.size();
        sum += data[index];
    }
    std::cout << "Random access sum: " << sum << std::endl;
}

int main() {
    constexpr int NUM_ELEMENTS = 90000000;
    std::vector<int> data(NUM_ELEMENTS, 1); 

    auto start = std::chrono::high_resolution_clock::now();
    sequentialAccess(data);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> sequentialTime = end - start;
    std::cout << "Sequential access time: " << sequentialTime.count() << " seconds\n";

    start = std::chrono::high_resolution_clock::now();
    randomAccess(data);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> randomTime = end - start;
    std::cout << "Random access time: " << randomTime.count() << " seconds\n";

    return 0;
}