#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

void xor_bytes(uint8_t *result, const uint8_t *input1, const uint8_t *input2, size_t len) {
    for (size_t i = 0; i < len; i++) {
        result[i] = input1[i] ^ input2[i];
    }
}

void cbc_mac(uint8_t *key, uint8_t *message, size_t msg_len, uint8_t *mac) {
    AES_KEY aes_key;
    uint8_t temp[AES_BLOCK_SIZE];
    
    // Set the AES encryption key (AES-256)
    AES_set_encrypt_key(key, 256, &aes_key);
    
    // Initialize MAC (all zeros)
    memset(mac, 0, AES_BLOCK_SIZE);

    for (size_t i = 0; i < msg_len; i += AES_BLOCK_SIZE) {
        xor_bytes(temp, message + i, mac, AES_BLOCK_SIZE);  // XOR with previous MAC value
        AES_encrypt(temp, mac, &aes_key);                  // Encrypt XOR result
    }
}

int main() {
    uint8_t key[32];
    uint8_t message[32] = "Hello, this is a message block.";  // Example message (32 bytes)
    uint8_t mac[AES_BLOCK_SIZE];
    
    // Generate random 256-bit key
    if (!RAND_bytes(key, sizeof(key))) {
        fprintf(stderr, "Error generating random key\n");
        return 1;
    }
    
    // Compute CBC MAC
    cbc_mac(key, message, sizeof(message), mac);
    
    // Print the CBC MAC
    printf("CBC MAC: ");
    for (int i = 0; i < AES_BLOCK_SIZE; i++) {
        printf("%02x", mac[i]);
    }
    printf("\n");
    
    return 0;
}
