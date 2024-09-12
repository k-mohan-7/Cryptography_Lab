#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 26

void decrypt(char *text, int shift) {
    for (int i = 0; text[i]; i++) 
        if (isalpha(text[i])) 
            text[i] = isupper(text[i]) ? (text[i] - 'A' - shift + SIZE) % SIZE + 'A'
                                       : (text[i] - 'a' - shift + SIZE) % SIZE + 'a';
}

int findShift(int *freq) {
    int shift = 0;
    for (int i = 1; i < SIZE; i++) 
        if (freq[i] > freq[shift]) shift = i;
    return (SIZE - shift) % SIZE;
}

int main() {
    char text[1000]; int freq[SIZE] = {0}, shift;
    printf("Enter ciphertext: "), fgets(text, sizeof(text), stdin);

    for (int i = 0; text[i]; i++) 
        if (isalpha(text[i])) freq[tolower(text[i]) - 'a']++;

    shift = findShift(freq);
    for (int i = 0; i < 10; i++) 
        decrypt(text, shift), printf("%d. %s\n", i + 1, text);
}
