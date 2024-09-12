#include <stdio.h>

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;  
}

char affineDecrypt(char C, int a, int b) {
    int a_inv = modInverse(a, 26);  
    if (a_inv == -1) {
        printf("No modular inverse for a = %d\n", a);
        return '\0';
    }
    return ((a_inv * ((C - 'A') - b + 26)) % 26) + 'A';
}

void breakAffineCipher(char *ciphertext) {
    int possible_a[] = {1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25};  
    int b, a;

    for (int i = 0; i < 12; i++) {
        a = possible_a[i];
        for (b = 0; b < 26; b++) {
            printf("Trying with a = %d, b = %d: ", a, b);
            for (int j = 0; ciphertext[j] != '\0'; j++) {
                printf("%c", affineDecrypt(ciphertext[j], a, b));
            }
            printf("\n");
        }
    }
}

int main() {
    char ciphertext[] = "B...U";  
    printf("Ciphertext: %s\n", ciphertext);
    breakAffineCipher(ciphertext);

    return 0;
}
