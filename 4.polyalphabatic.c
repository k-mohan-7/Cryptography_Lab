#include <stdio.h>
#include <string.h>

void vigenereCipher(char *plaintext, char *key, char *ciphertext) {
    int i, j = 0, keyLength = strlen(key);

    for (i = 0; plaintext[i] != '\0'; i++) {
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            ciphertext[i] = ((plaintext[i] - 'a') + (key[j % keyLength] - 'a')) % 26 + 'a';
            j++;
        } else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            ciphertext[i] = ((plaintext[i] - 'A') + (key[j % keyLength] - 'A')) % 26 + 'A';
            j++;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[i] = '\0';
}

int main() {
    char plaintext[100];
    char key[100];
    char ciphertext[100];

    printf("Enter a string: ");
    gets(plaintext);

    printf("Enter the key: ");
    gets(key);

    vigenereCipher(plaintext, key, ciphertext);

    printf("Encrypted message: %s\n", ciphertext);

    return 0;
}
