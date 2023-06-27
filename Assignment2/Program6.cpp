#include <iostream>
#include <vector>
#include <fstream>
#include <sys/sysinfo.h>
#include <ctime>

int main() {
    struct sysinfo memInfo;
    sysinfo(&memInfo);

    std::vector<double> cacheSize = {0.5, 0.6, 0.7, 0.8, 0.9, 0.95, 0.99, 1.0, 1.01, 1.1, 1.5, 2, 5, 10, 50};

    for (int i = 0; i < cacheSize.size(); i++) {
        sysinfo(&memInfo);

        long long freeBytes = memInfo.freeram;
        freeBytes *= memInfo.mem_unit;

        long long freePage = memInfo.freeswap;
        freePage *= memInfo.mem_unit;

        long long freeVirtual = memInfo.freeram + memInfo.freeswap;
        freeVirtual *= memInfo.mem_unit;

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
//g++ Program6.cpp -o Program && ./Program
/*
This program measures the performance of memory allocation and access for different cache sizes. It utilizes the demand-paging 
Virtual Memory Manager (VMM) to allocate and manage memory. The program calculates the available physical memory, page file, and 
virtual memory using the sysinfo function from <sys/sysinfo.h>. It then iterates over a vector of cache sizes and performs memory 
allocation and access operations. The program shows Thrashing between 1.1*m and 1.5*m.

For each cache size, the program performs the following steps:

Retrieves the current system memory information using sysinfo.
Calculates the available physical memory, page file, and virtual memory based on the obtained system memory information.
Prints the cache size, available physical memory, page file, and virtual memory.
Measures the execution time using clock() before and after the memory allocation and access operations.
Computes the number of bytes to allocate based on the cache size and available physical memory.
Allocates memory dynamically using new and catches a std::bad_alloc exception if the allocation fails.
Initializes the allocated memory with sequential values.
Performs arithmetic operations on the allocated memory.
Deletes the allocated memory using delete[].
Prints the elapsed time for the memory allocation and access operations.

Time Complexity:
The time complexity of this program is dominated by the memory allocation and access operations. The time complexity of dynamic memory 
allocation using new is O(1), but the actual time taken depends on the size of the allocated memory.
The time complexity of initializing and performing arithmetic operations on the allocated memory is O(n), where n is the number of 
elements in the allocated array.
Overall, the time complexity of the program can be considered as O(n) per cache size iteration, where n is the number of elements in 
the allocated array.

Space Complexity:
The space complexity of this program is primarily determined by the memory allocated dynamically using new. The space complexity depends 
on the size of the allocated memory, which is calculated based on the cache size and available physical memory.
The space complexity of the program can be considered as O(n), where n is the number of elements in the allocated array.
Paging Strategy:

This program utilizes the demand-paging strategy of the Virtual Memory Manager (VMM) to manage memory. The demand-paging strategy loads 
pages into physical memory only when they are accessed by the program. If a page is not currently in physical memory, it is retrieved 
from secondary storage (such as the hard disk) and loaded into a free physical memory page. This process is known as page swapping or page-in.
The specific details of the paging strategy used by the VMM depend on the underlying operating system, but generally, demand-paging is a 
common approach to optimize memory usage and improve performance by efficiently managing available memory resources.

=========================================
Cache Size: 0.5*M
Available Physical Memory: 40084185088   
Available Page File: 10737418240
Available Virtual Memory: 50821603328
Time elapsed: 22.8705 seconds
=========================================
Cache Size: 0.6*M
Available Physical Memory: 40112066560
Available Page File: 10737418240
Available Virtual Memory: 50849484800
Time elapsed: 26.6347 seconds
=========================================
Cache Size: 0.7*M
Available Physical Memory: 40111550464
Available Page File: 10737418240
Available Virtual Memory: 50848968704
Time elapsed: 36.3958 seconds
=========================================
Cache Size: 0.8*M
Available Physical Memory: 40111816704
Available Page File: 10737418240
Available Virtual Memory: 50849234944
Time elapsed: 40.6061 seconds
=========================================
Cache Size: 0.9*M
Available Physical Memory: 40112082944
Available Page File: 10737418240
Available Virtual Memory: 50849501184
Time elapsed: 48.3418 seconds
=========================================
Cache Size: 0.95*M
Available Physical Memory: 40111308800
Available Page File: 10737418240
Available Virtual Memory: 50848727040
Time elapsed: 49.1101 seconds
=========================================
Cache Size: 0.99*M
Available Physical Memory: 40109404160
Available Page File: 10737418240
Available Virtual Memory: 50846822400
Time elapsed: 62.0254 seconds
=========================================
Cache Size: 1*M
Available Physical Memory: 40108384256
Available Page File: 10737418240
Available Virtual Memory: 50845802496
Time elapsed: 138.549 seconds
=========================================
Cache Size: 1.01*M
Available Physical Memory: 37944561664
Available Page File: 10733326336
Available Virtual Memory: 48677888000
Time elapsed: 51.4079 seconds
=========================================
Cache Size: 1.1*M
Available Physical Memory: 40163639296
Available Page File: 10733326336
Available Virtual Memory: 50896965632
Time elapsed: 139.311 seconds
=========================================
Cache Size: 1.5*M
Available Physical Memory: 37934018560
Available Page File: 10732961792
Available Virtual Memory: 48666980352
Failed to allocate memory: std::bad_alloc
=========================================
Cache Size: 2*M
Available Physical Memory: 37932552192
Available Page File: 10732961792
Available Virtual Memory: 48665513984
Failed to allocate memory: std::bad_alloc
=========================================
Cache Size: 5*M
Available Physical Memory: 37932552192
Available Page File: 10732961792
Available Virtual Memory: 48665513984
Failed to allocate memory: std::bad_alloc
=========================================
Cache Size: 10*M
Available Physical Memory: 37932552192
Available Page File: 10732961792
Available Virtual Memory: 48665513984
Failed to allocate memory: std::bad_alloc
=========================================
Cache Size: 50*M
Available Physical Memory: 37932552192
Available Page File: 10732961792
Available Virtual Memory: 48665513984
Failed to allocate memory: std::bad_alloc
*/