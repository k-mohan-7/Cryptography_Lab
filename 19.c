#include <stdio.h>
#include <stdint.h>
#include <openssl/des.h>

void printHex(const char* label, const uint8_t* data, size_t len) {
    printf("%s: ", label);
    for (size_t i = 0; i < len; i++) printf("%02X", data[i]);
    printf("\n");
}

int main() {
    DES_cblock key1 = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};
    DES_cblock key2 = {0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10};
    DES_cblock key3 = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    DES_key_schedule ks1, ks2, ks3;
    DES_set_key_checked(&key1, &ks1);
    DES_set_key_checked(&key2, &ks2);
    DES_set_key_checked(&key3, &ks3);

    DES_cblock iv = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, iv_copy;
    memcpy(iv_copy, iv, sizeof(DES_cblock));

    uint8_t plaintext[] = "3DES CBC mode", ciphertext[32], decrypted[32];
    size_t len = (strlen((const char*)plaintext) + 7) / 8 * 8;

    DES_ede3_cbc_encrypt(plaintext, ciphertext, len, &ks1, &ks2, &ks3, &iv_copy, DES_ENCRYPT);
    printHex("Ciphertext", ciphertext, len);

    memcpy(iv_copy, iv, sizeof(DES_cblock));
    DES_ede3_cbc_encrypt(ciphertext, decrypted, len, &ks1, &ks2, &ks3, &iv_copy, DES_DECRYPT);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}
