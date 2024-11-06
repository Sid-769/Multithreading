
Prime Numbers Multithreading Program
=====================================

Overview
--------
This program calculates the count and sum of all prime numbers up to a user-specified maximum (N) using multithreading. 
The task is divided among multiple threads to improve performance.

Features
--------
- **Multithreading**: Utilizes `pthread_create` and `pthread_join` for efficient computation.
- **Command-line Arguments**: Accepts two arguments:
  1. Number of threads.
  2. Maximum number (N) to calculate primes up to.
- **Parallel Computation**: Distributes prime number calculations across threads.
- **Dynamic Range Allocation**: Handles uneven divisions of the range if N isn't evenly divisible by the number of threads.

Example Outputs
---------------

- **Single Thread**:
  ```bash
  ./assignment-3 1 25
  Thread #0 is finding primes from low = 0 to high = 25
  Thread #0 Sum is 100, Count is 9
  GRAND SUM IS 100, COUNT IS 9
  ```

- **Multiple Threads**:
  ```bash
  ./assignment-3 4 25
  Thread #0 is finding primes from low = 0 to high = 7
  Thread #1 is finding primes from low = 7 to high = 14
  Thread #2 is finding primes from low = 14 to high = 21
  Thread #3 is finding primes from low = 21 to high = 25
  GRAND SUM IS 100, COUNT IS 9
  ```

Purpose
-------
- **Learn Multithreading**: Gain experience with data parallelism.
- **OS-Level Programming**: Use system functions effectively (`pthread`).
- **Prime Number Computation**: Implement efficient algorithms for counting and summing primes.

Usage
-----

### Compilation
Use the provided `Makefile`:
```bash
make
```

### Running
Execute the program with the required arguments:
```bash
./assignment-3 <number_of_threads> <max_number>
```

### Requirements
- Ensure compatibility with the **Gaul** computing platform.
- Handles inputs up to `1,000,000`.

Additional Notes
----------------
- **Output Validation**: Can be verified using tools like Wolfram Alpha.
- **Data Types**: Use appropriate types to handle large sums.

Submission Guidelines
---------------------
- Include only the following in your tarball:
  - `assignment-3.c`
  - Screenshots of program output.
  - Supporting files (e.g., Makefile, README).
- Ensure the program compiles and runs on **Gaul**.
