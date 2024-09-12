#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 8 // DES block size in bytes

void print_hex(const uint8_t *data, size_t length) {
    for (size_t i = 0; i < length; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

void pad_data(uint8_t *data, size_t *length) {
    size_t padding_len = BLOCK_SIZE - (*length % BLOCK_SIZE);
    if (padding_len == 0) {
        padding_len = BLOCK_SIZE;
    }
    memset(data + *length, 0, padding_len - 1);
    data[*length + padding_len - 1] = padding_len;
    *length += padding_len;
}

void unpad_data(uint8_t *data, size_t *length) {
    size_t padding_len = data[*length - 1];
    *length -= padding_len;
}

void ecb_encrypt(const uint8_t *plaintext, size_t length, const DES_key_schedule *key_schedule, uint8_t *ciphertext) {
    DES_ecb_encrypt((DES_cblock*)plaintext, (DES_cblock*)ciphertext, key_schedule, DES_ENCRYPT);
}

void ecb_decrypt(const uint8_t *ciphertext, size_t length, const DES_key_schedule *key_schedule, uint8_t *plaintext) {
    DES_ecb_encrypt((DES_cblock*)ciphertext, (DES_cblock*)plaintext, key_schedule, DES_DECRYPT);
}

void cbc_encrypt(const uint8_t *plaintext, size_t length, const DES_key_schedule *key_schedule, const DES_cblock *iv, uint8_t *ciphertext) {
    DES_cblock temp;
    DES_cblock prev = *iv;

    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        // XOR with previous ciphertext block
        for (size_t j = 0; j < BLOCK_SIZE; j++) {
            temp[j] = plaintext[i + j] ^ prev[j];
        }
        DES_ecb_encrypt(&temp, &prev, key_schedule, DES_ENCRYPT);
        memcpy(ciphertext + i, &prev, BLOCK_SIZE);
    }
}

void cbc_decrypt(const uint8_t *ciphertext, size_t length, const DES_key_schedule *key_schedule, const DES_cblock *iv, uint8_t *plaintext) {
    DES_cblock temp;
    DES_cblock prev = *iv;
    DES_cblock current;

    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        DES_ecb_encrypt(ciphertext + i, &current, key_schedule, DES_DECRYPT);
        // XOR with previous ciphertext block
        for (size_t j = 0; j < BLOCK_SIZE; j++) {
            plaintext[i + j] = current[j] ^ prev[j];
        }
        memcpy(&prev, ciphertext + i, BLOCK_SIZE);
    }
}

void cfb_encrypt(const uint8_t *plaintext, size_t length, const DES_key_schedule *key_schedule, DES_cblock *iv, uint8_t *ciphertext) {
    DES_cblock feedback = *iv;
    DES_cblock temp;

    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        DES_ecb_encrypt(&feedback, &temp, key_schedule, DES_ENCRYPT);
        for (size_t j = 0; j < BLOCK_SIZE; j++) {
            ciphertext[i + j] = plaintext[i + j] ^ temp[j];
            feedback[j] = ciphertext[i + j];
        }
    }
}

void cfb_decrypt(const uint8_t *ciphertext, size_t length, const DES_key_schedule *key_schedule, DES_cblock *iv, uint8_t *plaintext) {
    DES_cblock feedback = *iv;
    DES_cblock temp;

    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        DES_ecb_encrypt(&feedback, &temp, key_schedule, DES_ENCRYPT);
        for (size_t j = 0; j < BLOCK_SIZE; j++) {
            plaintext[i + j] = ciphertext[i + j] ^ temp[j];
            feedback[j] = ciphertext[i + j];
        }
    }
}

int main() {
    DES_key_schedule key_schedule;
    DES_cblock key = {0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDE, 0xF1};
    DES_cblock iv = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    DES_set_key(&key, &key_schedule);

    // Example plaintext
    uint8_t plaintext[16] = "Hello, World!";
    size_t length = sizeof(plaintext);
    uint8_t ciphertext[16];
    uint8_t decrypted[16];

    // Padding
    pad_data(plaintext, &length);

    // ECB Mode
    ecb_encrypt(plaintext, length, &key_schedule, ciphertext);
    printf("ECB Ciphertext: ");
    print_hex(ciphertext, length);
    ecb_decrypt(ciphertext, length, &key_schedule, decrypted);
    unpad_data(decrypted, &length);
    printf("ECB Decrypted: ");
    print_hex(decrypted, length);

    // CBC Mode
    cbc_encrypt(plaintext, length, &key_schedule, &iv, ciphertext);
    printf("CBC Ciphertext: ");
    print_hex(ciphertext, length);
    cbc_decrypt(ciphertext, length, &key_schedule, &iv, decrypted);
    unpad_data(decrypted, &length);
    printf("CBC Decrypted: ");
    print_hex(decrypted, length);

    // CFB Mode
    cfb_encrypt(plaintext, length, &key_schedule, &iv, ciphertext);
    printf("CFB Ciphertext: ");
    print_hex(ciphertext, length);
    cfb_decrypt(ciphertext, length, &key_schedule, &iv, decrypted);
    unpad_data(decrypted, &length);
    printf("CFB Decrypted: ");
    print_hex(decrypted, length);

    return 0;
}
