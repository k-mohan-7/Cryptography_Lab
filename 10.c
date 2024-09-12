#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

// The Playfair Cipher Key matrix
char keyMatrix[SIZE][SIZE] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};

// Function to find the position of a character in the matrix
void findPosition(char ch, int *row, int *col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (keyMatrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Encrypting the Playfair Cipher
void encryptPlayfair(char *plaintext, char *ciphertext) {
    int i = 0;
    while (plaintext[i] != '\0') {
        char first = toupper(plaintext[i]);
        char second = toupper(plaintext[i + 1]);

        int row1, col1, row2, col2;
        findPosition(first, &row1, &col1);
        findPosition(second, &row2, &col2);

        if (row1 == row2) {
            // Same row, move right
            ciphertext[i] = keyMatrix[row1][(col1 + 1) % SIZE];
            ciphertext[i + 1] = keyMatrix[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {
            // Same column, move down
            ciphertext[i] = keyMatrix[(row1 + 1) % SIZE][col1];
            ciphertext[i + 1] = keyMatrix[(row2 + 1) % SIZE][col2];
        } else {
            // Rectangle, swap columns
            ciphertext[i] = keyMatrix[row1][col2];
            ciphertext[i + 1] = keyMatrix[row2][col1];
        }
        i += 2;
    }
    ciphertext[i] = '\0';  // Null-terminate the ciphertext string
}

int main() {
    char plaintext[] = "MUSTSEEYOUOVERCADOGANWEST";
    char ciphertext[256];

    encryptPlayfair(plaintext, ciphertext);

    printf("Encrypted Message: %s\n", ciphertext);
    return 0;
}
