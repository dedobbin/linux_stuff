#include <iostream>
#include <cstdlib>
#include <unistd.h>

int main() {
    long page_size = sysconf(_SC_PAGE_SIZE);
    std::cout << "Page size: " << page_size << " bytes\n";

    size_t num_integers = 3 * page_size / sizeof(int);

    int* data = static_cast<int*>(malloc(num_integers * sizeof(int)));

    if (data == nullptr) {
        std::cerr << "Memory allocation failed!\n";
        return 1;
    }

    // Fill with test data
    for (size_t i = 0; i < num_integers; ++i) {
        data[i] = i;
    }

    // Access elements beyond the allocated memory boundaries for UB
    for (size_t i = num_integers - 5; i < num_integers + 2; ++i) {
        std::cout << "Element " << i << ": " << data[i] << std::endl;
    }

    free(data);

    return 0;
}
