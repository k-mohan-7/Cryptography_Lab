#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MATRIX_SIZE 3  // Size of the key matrix (3x3 for this example)

// Function to find the modular inverse of a number
int mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}

// Function to calculate the determinant of a 3x3 matrix
int determinant(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    int det = matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) -
              matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +
              matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
    return det % 26;
}

// Function to calculate the cofactor matrix of a 3x3 matrix
void cofactor(int matrix[MATRIX_SIZE][MATRIX_SIZE], int cofactor_matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    cofactor_matrix[0][0] = (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) % 26;
    cofactor_matrix[0][1] = -(matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) % 26;
    cofactor_matrix[0][2] = (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]) % 26;

    cofactor_matrix[1][0] = -(matrix[0][1] * matrix[2][2] - matrix[0][2] * matrix[2][1]) % 26;
    cofactor_matrix[1][1] = (matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0]) % 26;
    cofactor_matrix[1][2] = -(matrix[0][0] * matrix[2][1] - matrix[0][1] * matrix[2][0]) % 26;

    cofactor_matrix[2][0] = (matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1]) % 26;
    cofactor_matrix[2][1] = -(matrix[0][0] * matrix[1][2] - matrix[0][2] * matrix[1][0]) % 26;
    cofactor_matrix[2][2] = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) % 26;
}

// Function to transpose a 3x3 matrix
void transpose(int matrix[MATRIX_SIZE][MATRIX_SIZE], int transpose_matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            transpose_matrix[i][j] = matrix[j][i];
        }
    }
}

// Function to find the inverse of a 3x3 matrix modulo 26
void inverse_matrix(int matrix[MATRIX_SIZE][MATRIX_SIZE], int inverse_matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    int det = determinant(matrix);
    int inv_det = mod_inverse(det, 26);

    int cofactor_matrix[MATRIX_SIZE][MATRIX_SIZE];
    cofactor(matrix, cofactor_matrix);

    int adjugate_matrix[MATRIX_SIZE][MATRIX_SIZE];
    transpose(cofactor_matrix, adjugate_matrix);

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            inverse_matrix[i][j] = (adjugate_matrix[i][j] * inv_det) % 26;
            if (inverse_matrix[i][j] < 0) inverse_matrix[i][j] += 26;
        }
    }
}

// Function to encrypt a 3-letter block using Hill cipher
void encrypt_block(int plaintext_block[MATRIX_SIZE], int key[MATRIX_SIZE][MATRIX_SIZE], int ciphertext_block[MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        ciphertext_block[i] = 0;
        for (int j = 0; j < MATRIX_SIZE; j++) {
            ciphertext_block[i] += key[i][j] * plaintext_block[j];
        }
        ciphertext_block[i] %= 26;
    }
}

// Function to decrypt a 3-letter block using Hill cipher
void decrypt_block(int ciphertext_block[MATRIX_SIZE], int key_inverse[MATRIX_SIZE][MATRIX_SIZE], int plaintext_block[MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        plaintext_block[i] = 0;
        for (int j = 0; j < MATRIX_SIZE; j++) {
            plaintext_block[i] += key_inverse[i][j] * ciphertext_block[j];
        }
        plaintext_block[i] %= 26;
        if (plaintext_block[i] < 0) plaintext_block[i] += 26;
    }
}

// Function to convert plaintext string to numerical blocks
void text_to_block(char *text, int block[MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        block[i] = text[i] - 'A';
    }
}

// Function to convert numerical blocks to text
void block_to_text(int block[MATRIX_SIZE], char *text) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        text[i] = block[i] + 'A';
    }
    text[MATRIX_SIZE] = '\0';
}

int main() {
    int key[MATRIX_SIZE][MATRIX_SIZE] = {{6, 24, 1}, {13, 16, 10}, {20, 17, 15}};
    int key_inverse[MATRIX_SIZE][MATRIX_SIZE];

    char plaintext[MATRIX_SIZE + 1] = "ACT";
    char ciphertext[MATRIX_SIZE + 1];

    int plaintext_block[MATRIX_SIZE], ciphertext_block[MATRIX_SIZE];

    // Encrypt the plaintext
    text_to_block(plaintext, plaintext_block);
    encrypt_block(plaintext_block, key, ciphertext_block);
    block_to_text(ciphertext_block, ciphertext);

    printf("Ciphertext: %s\n", ciphertext);

    // Compute the inverse of the key matrix
    inverse_matrix(key, key_inverse);

    // Decrypt the ciphertext
    text_to_block(ciphertext, ciphertext_block);
    decrypt_block(ciphertext_block, key_inverse, plaintext_block);
    block_to_text(plaintext_block, plaintext);

    printf("Decrypted Plaintext: %s\n", plaintext);

    return 0;
}
