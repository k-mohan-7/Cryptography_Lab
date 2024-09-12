#include <stdio.h>
#include <string.h>

void encrypt(const char *text, const int *key, char *result) {
    for (int i = 0; text[i] != '\0'; i++)
        result[i] = (text[i] - 'A' + key[i]) % 26 + 'A';
    result[strlen(text)] = '\0';
}

void decrypt(const char *text, const int *key, char *result) {
    for (int i = 0; text[i] != '\0'; i++)
        result[i] = (text[i] - 'A' - key[i] + 26) % 26 + 'A';
    result[strlen(text)] = '\0';
}

int main() {
    const char *plaintext = "SENDMOREMONEY";
    int key[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    char ciphertext[strlen(plaintext) + 1];
    char decryptedText[strlen(plaintext) + 1];

    encrypt(plaintext, key, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    decrypt(ciphertext, key, decryptedText);
    printf("Decrypted Text: %s\n", decryptedText);

    return 0;
}
