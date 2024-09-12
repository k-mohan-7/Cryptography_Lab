#include <stdio.h>
#include <string.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}


char affineEncrypt(char p, int a, int b) {
    return ((a * (p - 'A') + b) % 26) + 'A';
}

int main() {
    int a = 5; 
    int b = 8;
    char plaintext[] = "HELLO";
    char ciphertext[100];

    if (gcd(a, 26) != 1) {
        printf("a is not coprime with 26\n");
        return -1;
    }

    for (int i = 0; i < strlen(plaintext); i++) {
        ciphertext[i] = affineEncrypt(plaintext[i], a, b);
    }
    ciphertext[strlen(plaintext)] = '\0';

    printf("Encrypted message: %s\n", ciphertext);

    return 0;
}
