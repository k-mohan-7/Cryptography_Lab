#include <stdio.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function to encrypt a single character using affine Caesar cipher
char affine_encrypt(char p, int a, int b) {
    if (!isalpha(p)) return p;  // Non-alphabetic characters are not encrypted

    // Convert character to uppercase
    p = toupper(p);
    // Apply affine cipher formula
    return (char)(((a * (p - 'A') + b) % ALPHABET_SIZE) + 'A');
}

// Function to decrypt a single character using affine Caesar cipher
char affine_decrypt(char c, int a, int b) {
    if (!isalpha(c)) return c;  // Non-alphabetic characters are not decrypted

    // Convert character to uppercase
    c = toupper(c);
    // Calculate modular multiplicative inverse of a
    int a_inv = 0;
    for (int i = 1; i < ALPHABET_SIZE; i++) {
        if ((a * i) % ALPHABET_SIZE == 1) {
            a_inv = i;
            break;
        }
    }

    // Apply affine cipher decryption formula
    return (char)(((a_inv * ((c - 'A') - b + ALPHABET_SIZE)) % ALPHABET_SIZE) + 'A');
}

int main() {
    char plaintext[] = "HELLO";
    char ciphertext[sizeof(plaintext)];
    char decryptedtext[sizeof(plaintext)];

    // Affine cipher parameters
    int a = 5;  // Must be coprime with ALPHABET_SIZE (26)
    int b = 8;

    // Encrypt the plaintext
    for (int i = 0; plaintext[i] != '\0'; i++) {
        ciphertext[i] = affine_encrypt(plaintext[i], a, b);
    }
    ciphertext[sizeof(plaintext) - 1] = '\0'; // Null-terminate the string

    // Decrypt the ciphertext
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        decryptedtext[i] = affine_decrypt(ciphertext[i], a, b);
    }
    decryptedtext[sizeof(plaintext) - 1] = '\0'; // Null-terminate the string

    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);
    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}
