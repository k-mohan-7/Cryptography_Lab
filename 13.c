#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 100

int charToNum(char c) { return toupper(c) - 'A'; }
char numToChar(int num) { return num + 'A'; }

void encryptHill(char *text, int *keyMatrix, int keySize) {
    int textLen = strlen(text), encrypted[MAX_LEN] = {0};
    for (int i = 0; i < textLen; i += keySize)
        for (int j = 0; j < keySize; j++) {
            int sum = 0;
            for (int k = 0; k < keySize; k++)
                sum += keyMatrix[j * keySize + k] * charToNum(text[i + k]);
            encrypted[i + j] = sum % 26;
        }
    for (int i = 0; i < textLen; i++) text[i] = numToChar(encrypted[i]);
}

int main() {
    char plaintext[MAX_LEN];
    int keySize, keyMatrix[MAX_LEN * MAX_LEN];

    printf("Enter plaintext: ");
    gets(plaintext);
    printf("Enter key size: ");
    scanf("%d", &keySize);
    printf("Enter key matrix:\n");
    for (int i = 0; i < keySize * keySize; i++) scanf("%d", &keyMatrix[i]);

    int textLen = strlen(plaintext), padding = keySize - (textLen % keySize);
    if (padding < keySize) memset(plaintext + textLen, 'X', padding), plaintext[textLen + padding] = '\0';

    encryptHill(plaintext, keyMatrix, keySize);
    printf("Encrypted text: %s\n", plaintext);
    return 0;
}
