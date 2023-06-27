#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

int main() {
    std::vector<int> n = {16, 64, 256, 1024, 4096, 16384};
    int next = 0;

    while (next < 6) {
        int a, b, x;

        // Initialize Matrix M with size n x n
        std::vector<std::vector<int>> M(n[next], std::vector<int>(n[next], 0));

        long long m = 1000000000LL; // m = 1,000,000,000
        clock_t timer = clock();

        // Perform the calculation by adding random numbers from 1-100
        for (long long i = 0; i < m; i++) {
            x = rand() % 100 + 1;   // Generate random number between 1 and 100
            b = rand() % n[next];   // Generate random index for column
            a = rand() % n[next];   // Generate random index for row
            M[a][b] += x;           // Add the random number to the matrix at (a, b)
        }

        timer = clock() - timer;
        printf("Clock time for n size %d: %.2f seconds\n", n[next], static_cast<float>(timer) / CLOCKS_PER_SEC);

        next++;
    }

    next = 0;
    while (next < 6) {
        int a, b, x;

        // Initialize Matrix M with size n x n
        std::vector<std::vector<int>> M(n[next], std::vector<int>(n[next], 0));

        long long m = 10000000000LL; // m = 10,000,000,000
        clock_t timer = clock();

        // Perform the calculation by adding random numbers from 1-100
        for (long long i = 0; i < m; i++) {
            x = rand() % 100 + 1;   // Generate random number between 1 and 100
            b = rand() % n[next];   // Generate random index for column
            a = rand() % n[next];   // Generate random index for row
            M[a][b] += x;           // Add the random number to the matrix at (a, b)
        }

        timer = clock() - timer;
        printf("Clock time for n size %d: %.2f seconds\n", n[next], static_cast<float>(timer) / CLOCKS_PER_SEC);

        next++;
    }

    return 0;
}

/*
g++ Program4.cpp -o Program && ./Program 

Time Complexity:

Initialization of Matrix M: The initialization of the matrix has a time complexity of O(n^2), where n is the size of the matrix. 
This occurs twice in the program, once for each loop.
Matrix Calculation Loop: The loop iterates m (1,000,000,000 or 10,000,000,000) times. Inside the loop, the operations performed 
are constant time operations (e.g., modulus, addition). Therefore, the time complexity of this loop is O(m).
Overall, the time complexity of the program is O(n^2 + m), where n is the matrix size and m is the loop iteration count.

Space Complexity:

Initialization of Matrix M: The space complexity of initializing the matrix is O(n^2), where n is the size of the matrix. This 
occurs twice in the program, once for each loop.
Additional variables: The program uses additional variables a, b, x to store temporary values. These variables have constant space 
complexity and do not depend on the input size.
Overall, the space complexity of the program is O(n^2), where n is the matrix size. The space required for additional variables is 
negligible.

Run 1:
Clock time for n size 16: 44.43 seconds
Clock time for n size 64: 44.19 seconds
Clock time for n size 256: 44.90 seconds
Clock time for n size 1024: 50.58 seconds
Clock time for n size 4096: 132.98 seconds
Clock time for n size 16384: 172.71 seconds
Clock time for n size 16: 445.92 seconds
Clock time for n size 64: 443.95 seconds
Clock time for n size 256: 451.49 seconds
Clock time for n size 1024: 551.72 seconds
Clock time for n size 4096: 1270.71 seconds
Clock time for n size 16384: 1442.67 seconds

Run 2:
Clock time for n size 16: 44.38 seconds
Clock time for n size 64: 44.45 seconds
Clock time for n size 256: 44.87 seconds
Clock time for n size 1024: 51.77 seconds
Clock time for n size 4096: 128.98 seconds
Clock time for n size 16384: 169.11 seconds
Clock time for n size 16: 443.04 seconds
Clock time for n size 64: 444.40 seconds
Clock time for n size 256: 453.97 seconds
Clock time for n size 1024: 517.82 seconds
Clock time for n size 4096: 1260.69 seconds
Clock time for n size 16384: 1461.18 seconds

Run 3:
Clock time for n size 16: 44.69 seconds
Clock time for n size 64: 44.92 seconds
Clock time for n size 256: 45.44 seconds
Clock time for n size 1024: 52.76 seconds
Clock time for n size 4096: 131.49 seconds
Clock time for n size 16384: 171.96 seconds
Clock time for n size 16: 445.59 seconds
Clock time for n size 64: 445.99 seconds
Clock time for n size 256: 452.49 seconds
Clock time for n size 1024: 591.03 seconds
Clock time for n size 4096: 1298.84 seconds
Clock time for n size 16384: 1509.25 seconds
*/