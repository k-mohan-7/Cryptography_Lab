#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXT_LENGTH 1000
#define ALPHABET_SIZE 26

// Known English letter frequencies (E -> 12.7%, T -> 9.1%, etc.)
char known_frequencies[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

// Function to analyze the letter frequencies of the ciphertext
void analyze_frequency(const char *ciphertext, int *frequency) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        frequency[i] = 0;
    }
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            frequency[toupper(ciphertext[i]) - 'A']++;
        }
    }
}

// Function to sort and rank letters by frequency in the ciphertext
void rank_by_frequency(int *frequency, char *ranked_letters) {
    int used[ALPHABET_SIZE] = {0};
    
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        int max_freq = -1;
        int max_index = 0;
        
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            if (!used[j] && frequency[j] > max_freq) {
                max_freq = frequency[j];
                max_index = j;
            }
        }
        ranked_letters[i] = 'A' + max_index;
        used[max_index] = 1;
    }
}

// Function to apply the letter substitution based on frequency analysis
void substitute_letters(const char *ciphertext, const char *ranked_ciphertext, const char *ranked_english, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char c = toupper(ciphertext[i]);
            for (int j = 0; j < ALPHABET_SIZE; j++) {
                if (c == ranked_ciphertext[j]) {
                    plaintext[i] = isupper(ciphertext[i]) ? ranked_english[j] : tolower(ranked_english[j]);
                    break;
                }
            }
        } else {
            plaintext[i] = ciphertext[i];  // Non-alphabet characters remain unchanged
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

// Function to print the top N possible plaintexts
void print_top_plaintexts(char ranked_ciphertext[], const char *ciphertext, int top_n) {
    char plaintext[MAX_TEXT_LENGTH];
    
    printf("Top %d Possible Plaintexts:\n", top_n);
    for (int i = 0; i < top_n && i < ALPHABET_SIZE; i++) {
        substitute_letters(ciphertext, ranked_ciphertext, known_frequencies, plaintext);
        printf("Plaintext %d: %s\n", i + 1, plaintext);
        // Rotate the ranked_letters array for different possibilities
        for (int j = 0; j < ALPHABET_SIZE - 1; j++) {
            char temp = known_frequencies[j];
            known_frequencies[j] = known_frequencies[j + 1];
            known_frequencies[j + 1] = temp;
        }
    }
}

int main() {
    char ciphertext[MAX_TEXT_LENGTH];
    int frequency[ALPHABET_SIZE];
    char ranked_letters[ALPHABET_SIZE];
    
    // Input ciphertext from user
    printf("Enter ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';  // Remove newline character

    // Analyze letter frequency
    analyze_frequency(ciphertext, frequency);
    
    // Rank ciphertext letters by frequency
    rank_by_frequency(frequency, ranked_letters);
    
    // Output the top 10 possible plaintexts
    print_top_plaintexts(ranked_letters, ciphertext, 10);
    
    return 0;
}
