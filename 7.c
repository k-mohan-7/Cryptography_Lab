#include <stdio.h>
#include <string.h>

#define TEXT_LENGTH 256

void decrypt(char ciphertext[], char mapping[], char *plaintext) {
    int i, j;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        char c = ciphertext[i];
        if (c >= 'A' && c <= 'Z') {
            plaintext[i] = mapping[c - 'A'];
        } else if (c >= 'a' && c <= 'z') {
            plaintext[i] = mapping[c - 'a'];
        } else {
            plaintext[i] = c;  
        }
    }
    plaintext[i] = '\0';
}

int main() {
    char ciphertext[TEXT_LENGTH] = "53†‡‡305))6*;4826)4‡.)4‡;806*;48†8¶60))85;]8††83(88)5††46(;88*96?;8)‡(;485);5‡2:‡(4956*2(5*4)8¶8;4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48‡85;4)485†8¶";
    char mapping[26] = "etaoinshrdlucmfwypvbgkjqxz";  
    char plaintext[TEXT_LENGTH];

    decrypt(ciphertext, mapping, plaintext);
    
    printf("Decrypted message: %s\n", plaintext);
    return 0;
}
