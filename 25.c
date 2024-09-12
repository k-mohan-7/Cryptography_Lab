#include <stdio.h>

// Function to calculate the GCD of two numbers
int gcd(int a, int b) {
    while (b) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to calculate the modular inverse
int modInverse(int e, int phi) {
    for (int d = 1; d < phi; d++) {
        if ((e * d) % phi == 1) {
            return d;
        }
    }
    return -1;
}

// Function to perform the common factor attack
int commonFactorAttack(int n, int e, int blocks[], int len) {
    int commonFactor = 0;

    for (int i = 0; i < len; i++) {
        for (int j = i + 1; j < len; j++) {
            if (gcd(blocks[i], n) != 1 && gcd(blocks[j], n) != 1) {
                commonFactor = gcd(blocks[i], n);
                break;
            }
        }
        if (commonFactor) break;
    }

    if (commonFactor) {
        int p = commonFactor;
        int q = n / p;
        int phi = (p - 1) * (q - 1);
        int d = modInverse(e, phi);

        if (d == -1) {
            printf("Modular inverse could not be found.\n");
            return 0;
        }

        printf("Decrypted plaintext blocks: ");
        for (int i = 0; i < len; i++) {
            int plaintext = 1;
            for (int j = 0; j < d; j++) {
                plaintext = (plaintext * blocks[i]) % n;
            }
            printf("%d ", plaintext);
        }
        printf("\n");
    } else {
        printf("No common factor found.\n");
    }
    return 0;
}

int main() {
    int n = 3233; // Modulus
    int e = 17;   // Public exponent
    int blocks[] = {1791, 123, 2509, 1281}; // Encrypted blocks
    int len = sizeof(blocks) / sizeof(blocks[0]);

    commonFactorAttack(n, e, blocks, len);

    return 0;
}
