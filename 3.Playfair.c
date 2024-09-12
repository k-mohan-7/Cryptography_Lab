#include <stdio.h>
#include <string.h>

void createMatrix(char *key, char matrix[5][5]) {
    int i, j, k = 0, used[26] = {0};

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            while (used[key[k] - 'A'] && k < strlen(key)) {
                k++;
            }
            matrix[i][j] = key[k++];
            used[matrix[i][j] - 'A'] = 1;
        }
    }
}

void playfairCipher(char *plaintext, char matrix[5][5], char *ciphertext) {
    
}

int main() {
    char key[] = "KEYWORD";
    char matrix[5][5];
    char plaintext[] = "HELLO";
    char ciphertext[100];

    createMatrix(key, matrix);
    playfairCipher(plaintext, matrix, ciphertext);

    printf("Encrypted message: %s\n", ciphertext);

    return 0;
}
