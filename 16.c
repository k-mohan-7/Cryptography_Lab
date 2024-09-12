#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define ALPHABET_SIZE 26
#define TOP_PLAINTEXTS 10

const double englishFreq[ALPHABET_SIZE] = {
    0.0817, 0.0149, 0.0278, 0.0425, 0.1270, 0.0223, 0.0202, 0.0609,
    0.0697, 0.0015, 0.0077, 0.0403, 0.0241, 0.0675, 0.0751, 0.0193,
    0.0010, 0.0599, 0.0633, 0.0906, 0.0276, 0.0098, 0.0236, 0.0015,
    0.0197, 0.0007
};

// Function to calculate letter frequencies
void calcFreq(const char *text, double *freq) {
    int total = 0;
    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            freq[tolower(text[i]) - 'a']++;
            total++;
        }
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) freq[i] /= total;
}

// Calculate match score for a frequency comparison
double calcScore(const double *freq) {
    double score = 0.0;
    for (int i = 0; i < ALPHABET_SIZE; i++) score += freq[i] * englishFreq[i];
    return score;
}

// Decrypt function with given shift
void decrypt(const char *cipher, char *plain, int shift) {
    for (int i = 0; cipher[i]; i++) {
        if (isalpha(cipher[i])) {
            char base = isupper(cipher[i]) ? 'A' : 'a';
            plain[i] = (cipher[i] - base - shift + ALPHABET_SIZE) % ALPHABET_SIZE + base;
        } else {
            plain[i] = cipher[i];
        }
    }
    plain[strlen(cipher)] = '\0';
}

int main() {
    const char *ciphertext = "FALSXY XS LSX!";
    double cipherFreq[ALPHABET_SIZE] = {0};
    char plain[strlen(ciphertext) + 1];
    
    calcFreq(ciphertext, cipherFreq);
    printf("Ciphertext: %s\nTop %d plaintexts:\n", ciphertext, TOP_PLAINTEXTS);
    
    for (int shift = 0; shift < ALPHABET_SIZE; shift++) {
        decrypt(ciphertext, plain, shift);
        double plainFreq[ALPHABET_SIZE] = {0};
        calcFreq(plain, plainFreq);
        printf("Shift %d: %s (Score: %.4f)\n", shift, plain, calcScore(plainFreq));
    }
    
    return 0;
}
