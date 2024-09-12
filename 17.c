#include <stdio.h>
#include <stdint.h>

static const int IP[] = { 2, 6, 3, 1, 4, 8, 5, 7 };
static const int IP_INV[] = { 4, 1, 3, 5, 7, 2, 8, 6 };
static const uint64_t KEY = 0x133457799BBCDFF1;
static const uint64_t CIPHERTEXT = 0x0123456789ABCDEF;

// Permutation function
uint64_t permute(uint64_t input, const int *table, int size) {
    uint64_t result = 0;
    for (int i = 0; i < size; i++) {
        result |= ((input >> (64 - table[i])) & 1) << (size - 1 - i);
    }
    return result;
}

// Simple DES decryption function
uint64_t des_decrypt(uint64_t ciphertext, uint64_t key) {
    return permute(permute(ciphertext, IP, 64) ^ key, IP_INV, 64);
}

int main() {
    printf("Ciphertext: 0x%016llX\n", CIPHERTEXT);
    printf("Decrypted: 0x%016llX\n", des_decrypt(CIPHERTEXT, KEY));
    return 0;
}
