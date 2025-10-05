#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define MAX_SIZE 100

// Function to initialize matrix with random values
void init_matrix(int *matrix, int size) {
    for (int i = 0; i < size * size; i++) {
        matrix[i] = i % 10;  // Simple pattern for reproducibility
    }
}

// Function to multiply two matrices
void multiply_matrices(int *a, int *b, int *result, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i * size + j] = 0;
            for (int k = 0; k < size; k++) {
                result[i * size + j] += a[i * size + k] * b[k * size + j];
            }
        }
    }
}

// Function to print benchmarking results
void print_benchmark(const char *label, int size, int cycles, int time, int instructions) {
    printf("%s %dx%d: Cycles=%d, Time=%d, Instructions=%d\n", 
           label, size, size, cycles, time, instructions);
}

int main() {
    int sizes[] = {10, 20, 30, 50};  // Different matrix sizes
    int num_sizes = 4;
    
    printf("Starting matrix multiplication benchmark...\n");
    
    for (int s = 0; s < num_sizes; s++) {
        int size = sizes[s];
        int total_elements = size * size;
        
        // Allocate matrices
        int *a = malloc(total_elements * sizeof(int));
        int *b = malloc(total_elements * sizeof(int));
        int *result = malloc(total_elements * sizeof(int));
        
        if (!a || !b || !result) {
            printf("Failed to allocate memory for size %d\n", size);
            exit(1);
        }
        
        // Initialize matrices
        init_matrix(a, size);
        init_matrix(b, size);
        
        // Measure before multiplication
        int start_cycles = rdcycle();
        int start_time = rdtime();
        int start_instructions = rdinstret();
        
        // Perform matrix multiplication
        multiply_matrices(a, b, result, size);
        
        // Measure after multiplication
        int end_cycles = rdcycle();
        int end_time = rdtime();
        int end_instructions = rdinstret();
        
        // Calculate differences
        int cycles_used = end_cycles - start_cycles;
        int time_used = end_time - start_time;
        int instructions_used = end_instructions - start_instructions;
        
        // Print results
        print_benchmark("Matrix", size, cycles_used, time_used, instructions_used);
        
        // Free memory
        free(a);
        free(b);
        free(result);
    }
    
    printf("Benchmark completed!\n");
    exit(0);
}
