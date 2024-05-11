#include <iostream>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

int main() {
    const size_t SIZE = 4096;
    int* shared_memory = static_cast<int*>(mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0));

    if (shared_memory == MAP_FAILED) {
        std::cerr << "failed to create shared memory\n";
        return 1;
    }

    *shared_memory = 5;
    pid_t pid = fork();

    if (pid == -1) {
        std::cerr << "fork failed\n";
        return 1;
    }

    if (pid == 0) {
        std::cout << "child process started\n";

        ++(*shared_memory);
        std::cout << "child: " << *shared_memory << std::endl;

        exit(0);
    } else {
        // Wait for the child process to die
        wait(NULL);
        std::cout << "parent: " << *shared_memory << std::endl;
    }

    if (munmap(shared_memory, SIZE) == -1) {
        std::cerr << "failed to unmap shared memory\n";
        return 1;
    }

    return 0;
}