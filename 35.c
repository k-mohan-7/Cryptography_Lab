#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function to generate a random key stream
void generate_key_stream(int *key, int length) {
    for (int i = 0; i < length; i++) {
        key[i] = rand() % ALPHABET_SIZE;
    }
}

// Function to encrypt plaintext using the one-time pad Vigenère cipher
void encrypt(const char *plaintext, int *key, int length, char *ciphertext) {
    for (int i = 0; i < length; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            ciphertext[i] = (plaintext[i] - base + key[i]) % ALPHABET_SIZE + base;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[length] = '\0';  // Null-terminate the ciphertext string
}

// Function to decrypt ciphertext using the one-time pad Vigenère cipher
void decrypt(const char *ciphertext, int *key, int length, char *plaintext) {
    for (int i = 0; i < length; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = (ciphertext[i] - base - key[i] + ALPHABET_SIZE) % ALPHABET_SIZE + base;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[length] = '\0';  // Null-terminate the plaintext string
}

int main() {
    srand(time(NULL));  // Seed the random number generator

    // Example plaintext
    char plaintext[] = "HELLO WORLD";
    int length = sizeof(plaintext) - 1;  // Exclude the null terminator

    // Generate key stream
    int key[length];
    generate_key_stream(key, length);

    // Encrypt the plaintext
    char ciphertext[length + 1];  // +1 for null terminator
    encrypt(plaintext, key, length, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    // Decrypt the ciphertext
    char decrypted[length + 1];  // +1 for null terminator
    decrypt(ciphertext, key, length, decrypted);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}
