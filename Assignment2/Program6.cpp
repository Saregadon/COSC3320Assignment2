#include <iostream>
#include <vector>
#include <fstream>
#include <sys/sysinfo.h>
#include <ctime>

int main() {
    struct sysinfo memInfo;
    sysinfo(&memInfo);

    long long freeBytes = memInfo.freeram;
    freeBytes *= memInfo.mem_unit;

    long long freePage = memInfo.freeswap;
    freePage *= memInfo.mem_unit;

    long long freeVirtual = memInfo.freeram + memInfo.freeswap;
    freeVirtual *= memInfo.mem_unit;

    std::vector<double> cacheSize = {0.5, 0.6, 0.7, 0.8, 0.9, 0.95, 0.99, 1.0, 1.01, 1.1, 1.5, 2, 5, 10, 50};

    for (int i = 0; i < cacheSize.size(); i++) {
        std::cout << "=========================================" << std::endl;
        std::cout << "Cache Size: " << cacheSize[i] << "*M" << std::endl;
        std::cout << "Available Physical Memory: " << freeBytes << std::endl;
        std::cout << "Available Page File: " << freePage << std::endl;
        std::cout << "Available Virtual Memory: " << freeVirtual << std::endl;

        clock_t startTime = clock();
        long long numBytes = static_cast<long long>(cacheSize[i] * freeBytes);
        long long arraySize = numBytes / sizeof(int); // assuming int size is 4 bytes
        int* numArray = nullptr;

        try {
            numArray = new int[arraySize];
        } catch (const std::bad_alloc& e) {
            std::cout << "Failed to allocate memory: " << e.what() << std::endl;
            continue;
        }

        for (long long x = 0; x < arraySize; x++) {
            numArray[x] = x;
        }

        for (long long x = 0; x < arraySize; x++) {
            numArray[x] += x;
        }

        delete[] numArray; // release memory

        std::cout << "Time elapsed: " << static_cast<double>(clock() - startTime) / CLOCKS_PER_SEC << " seconds" << std::endl;
    }

    return 0;
}
