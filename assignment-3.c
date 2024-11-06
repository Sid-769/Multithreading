#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

typedef struct {
    int start_index;
    int end_index;
    int *primes;
    long segment_sum;  // Sum of primes in this segment
    int segment_count;  // Count of primes in this segment
    int thread_id;      // To identify the thread in the output
} ThreadData;

// Function to check if a number is prime
int is_prime(int number) {
    if (number <= 1) return 0;
    if (number <= 3) return 1;
    if (number % 2 == 0 || number % 3 == 0) return 0;

    for (int i = 5; i <= sqrt(number); i += 6) {
        if (number % i == 0 || number % (i + 2) == 0)
            return 0;
    }
    return 1;
}

// Function to generate primes up to N
void generate_primes_up_to(int N, int primes[], int *count) {
    *count = 0;
    for (int num = 2; num <= N; num++) {
        if (is_prime(num)) {
            primes[*count] = num;
            (*count)++;
        }
    }
}

// Function that each thread will run to calculate segment sum and count
void* calculate_segment_sum(void* arg) {
    ThreadData* data = (ThreadData*) arg;
    data->segment_sum = 0;
    data->segment_count = 0;

    printf("Thread #%d is finding primes from low = %d to high = %d\n", data->thread_id, data->start_index, data->end_index);

    for (int i = data->start_index; i <= data->end_index; i++) {
        data->segment_sum += data->primes[i];
        data->segment_count++;
    }

    printf("Thread #%d Sum is %ld, Count is %d\n", data->thread_id, data->segment_sum, data->segment_count);
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number_of_threads> <max_prime_number>\n", argv[0]);
        return 1;
    }

    int num_threads = atoi(argv[1]);
    int N = atoi(argv[2]);

    if (num_threads <= 0 || N <= 1) {
        fprintf(stderr, "Both number_of_threads and max_prime_number must be positive.\n");
        return 1;
    }

    // Allocate memory for prime numbers array
    int *primes = malloc(sizeof(int) * N);
    int prime_count = 0;
    generate_primes_up_to(N, primes, &prime_count);

    // If there are no primes, exit early
    if (prime_count == 0) {
        printf("No primes found up to %d\n", N);
        free(primes);
        return 0;
    }

    // Create thread data and threads
    pthread_t threads[num_threads];
    ThreadData thread_data[num_threads];

    int segment_size = prime_count / num_threads;
    int remainder = prime_count % num_threads;

    int start = 0;
    for (int i = 0; i < num_threads; i++) {
        thread_data[i].primes = primes;
        thread_data[i].start_index = start;
        thread_data[i].end_index = start + segment_size - 1;
        thread_data[i].thread_id = i;

        // Distribute remainder across first few threads
        if (i < remainder) {
            thread_data[i].end_index++;
        }

        start = thread_data[i].end_index + 1;

        pthread_create(&threads[i], NULL, calculate_segment_sum, (void*)&thread_data[i]);
    }

    // Wait for threads to finish and combine results
    long total_sum = 0;
    int total_count = 0;

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
        total_sum += thread_data[i].segment_sum;
        total_count += thread_data[i].segment_count;
    }

    // Print final grand total
    printf("\nGRAND SUM IS %ld, COUNT IS %d\n", total_sum, total_count);

    // Free allocated memory
    free(primes);
    return 0;
}
