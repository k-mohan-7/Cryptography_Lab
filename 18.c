#include <stdio.h>
#include <stdint.h>
#define SHIFT(key, i) ((key << i) | (key >> (28 - i)))
static const int PC1[] = { 2, 4, 1, 6, 3, 9, 0, 8, 5, 7 }, PC2[] = { 5, 2, 6, 3, 7, 4, 9, 8 };
uint64_t permute(uint64_t input, const int *table, int size) {
 uint64_t result = 0;
 for (int i = 0; i < size; i++) result |= ((input >> (64 - table[i])) & 1) << (size - 1 - i);
 return result;
}
void generate_subkeys(uint64_t key, uint64_t *subkeys) {
 key = permute(key, PC1, 56);
 for (int i = 0; i < 16; i++) subkeys[i] = permute(SHIFT(key, i), PC2, 48);
}
int main() {
 uint64_t subkeys[16];
 generate_subkeys(0x0000FFFFFFFFFFFF, subkeys);
 for (int i = 0; i < 16; i++) printf("K%d: 0x%012llX\n", i + 1, subkeys[i]);
 return 0;
}
