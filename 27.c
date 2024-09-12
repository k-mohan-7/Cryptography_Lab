#include <stdio.h>
#include <stdint.h>

// Function for modular exponentiation
uint64_t mod_pow(uint64_t base, uint64_t exponent, uint64_t modulus) {
    uint64_t result = 1;
    base = base % modulus;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        exponent >>= 1;
        base = (base * base) % modulus;
    }
    return result;
}

int main() {
    uint64_t n = 12345678901;   // Example modulus
    uint64_t e = 65537;         // Public exponent
    uint64_t d = 123456789;     // Private exponent
    int i;

    char message[] = "HELLO";
    int message_length = sizeof(message) - 1;

    // Original message
    printf("Original Message: %s\n", message);

    // Encryption process
    printf("Encrypted Message: ");
    uint64_t encrypted_message[message_length];
    for (i = 0; i < message_length; i++) {
        encrypted_message[i] = mod_pow(message[i] - 'A', e, n);  // Encrypt each character
        printf("%llu ", encrypted_message[i]);
    }
    printf("\n");

    // Decryption process
    printf("Decrypted Message: ");
    for (i = 0; i < message_length; i++) {
        uint64_t decrypted = mod_pow(encrypted_message[i], d, n) + 'A';  // Decrypt each character
        printf("%c", (char)decrypted);
    }
    printf("\n");

    return 0;
}
