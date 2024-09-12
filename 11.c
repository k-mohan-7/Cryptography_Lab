#include <stdio.h>

// Function to calculate factorial
unsigned long long factorial(int n) {
    if (n == 0 || n == 1) return 1;
    return n * factorial(n - 1);
}

int main() {
    int n = 25;
    unsigned long long total_keys = factorial(n);
    
    printf("Total possible Playfair keys (25!): %llu\n", total_keys);

    // Assuming some keys give identical results, approximately reduce by half
    unsigned long long unique_keys = total_keys / 2;

    printf("Effectively unique keys: %llu\n", unique_keys);

    return 0;
}
