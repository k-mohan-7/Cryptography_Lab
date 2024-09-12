#include <stdio.h>
typedef unsigned char byte;

void print_hex(byte *data, int length) {
    for (int i = 0; i < length; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

void generate_subkeys(byte *initial_key, int block_size, byte *subkey1, byte *subkey2) {
    byte L[block_size / 8];
    byte const_Rb = (block_size == 64) ? 0x1B : 0x87;  // Rb for 64-bit or 128-bit block size
    byte carry;

    // Initialize L with the initial key
    for (int i = 0; i < block_size / 8; i++) {
        L[i] = initial_key[i];
    }

    // Calculate subkey1
    // Perform left shift on L
    carry = (L[0] & 0x80) ? 1 : 0;
    for (int i = 0; i < block_size / 8; i++) {
        L[i] = (L[i] << 1) | carry;
        carry = (L[i] & 0x80) ? 1 : 0;
    }
    if (carry) {
        L[0] ^= const_Rb;  // XOR with Rb if there was a carry
    }
    for (int i = 0; i < block_size / 8; i++) {
        subkey1[i] = L[i];
    }

    // Calculate subkey2
    // Perform another left shift on L
    carry = (L[0] & 0x80) ? 1 : 0;
    for (int i = 0; i < block_size / 8; i++) {
        L[i] = (L[i] << 1) | carry;
        carry = (L[i] & 0x80) ? 1 : 0;
    }
    if (carry) {
        L[0] ^= const_Rb;  // XOR with Rb if there was a carry
    }
    for (int i = 0; i < block_size / 8; i++) {
        subkey2[i] = L[i];
    }
}

int main() {
    // Set block size (64 or 128 bits)
    int block_size = 128;
    byte initial_key[block_size / 8] = {0};  // Initialize key data here
    byte subkey1[block_size / 8];
    byte subkey2[block_size / 8];

    // Initialize initial_key with your key data here
    for (int i = 0; i < block_size / 8; i++) {
        initial_key[i] = i;  // Example key initialization
    }

    generate_subkeys(initial_key, block_size, subkey1, subkey2);

    printf("Subkey 1: ");
    print_hex(subkey1, block_size / 8);
    printf("Subkey 2: ");
    print_hex(subkey2, block_size / 8);

    return 0;
}
