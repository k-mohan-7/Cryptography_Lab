#include <stdio.h>

// Function for modular exponentiation
int mod_exp(int base, int exp, int modulus) {
    int result = 1;
    base = base % modulus;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % modulus;
        }
        exp = exp >> 1;
        base = (base * base) % modulus;
    }
    return result;
}

int main() {
    int prime = 23; // Public prime number
    int base = 5;   // Public base (generator)

    int alicePrivateKey = 6; // Alice's private key
    int bobPrivateKey = 15;  // Bob's private key

    // Compute Alice's and Bob's public keys
    int alicePublicKey = mod_exp(base, alicePrivateKey, prime);
    int bobPublicKey = mod_exp(base, bobPrivateKey, prime);

    // Display the public keys
    printf("Alice's Public Key: %d\n", alicePublicKey);
    printf("Bob's Public Key: %d\n", bobPublicKey);

    // Compute shared secrets
    int aliceSharedSecret = mod_exp(bobPublicKey, alicePrivateKey, prime);
    int bobSharedSecret = mod_exp(alicePublicKey, bobPrivateKey, prime);

    // Display the shared secrets (which should match)
    printf("Alice's Shared Secret: %d\n", aliceSharedSecret);
    printf("Bob's Shared Secret: %d\n", bobSharedSecret);

    return 0;
}
