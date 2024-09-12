#include <stdio.h>
#include <stdlib.h>

// Modular exponentiation function
unsigned long long mod_exp(unsigned long long base, unsigned long long exp, unsigned long long modulus) {
    unsigned long long result = 1;
    base %= modulus;
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exp >>= 1;
    }
    return result;
}

// Encryption function using RSA
unsigned long long encrypt(unsigned long long character, unsigned long long e, unsigned long long n) {
    return mod_exp(character, e, n);
}

int main() {
    unsigned long long p, q, n, phi, e, character;
    char message[1000];

    // Assign prime numbers
    p = 9973;  // First prime
    q = 9857;  // Second prime
    n = p * q; // Calculate modulus (n)
    e = 65537; // Public exponent

    // Input message from user
    printf("Enter the message (all uppercase letters without spaces): ");
    scanf("%s", message);

    printf("Encrypted message: ");
    
    // Encrypt each character
    for (int i = 0; message[i] != '\0'; i++) {
        character = message[i] - 'A';  // Convert letter to number (A=0, B=1, ..., Z=25)
        unsigned long long encrypted_char = encrypt(character, e, n);
        printf("%llu ", encrypted_char);
    }
    printf("\n");

    return 0;
}
