#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/dsa.h>
#include <openssl/sha.h>

// Generate a DSA key pair
DSA *generate_dsa_key() {
    DSA *dsa = DSA_new();
    if (DSA_generate_key(dsa, 1024) != 1) {
        fprintf(stderr, "Error generating DSA key\n");
        return NULL;
    }
    return dsa;
}

// Sign a message using DSA
int sign_dsa(DSA *dsa, unsigned char *msg, int msg_len, unsigned char *sig, int *sig_len) {
    return DSA_sign(0, msg, msg_len, sig, sig_len, dsa);
}

// Verify a DSA signature
int verify_dsa(DSA *dsa, unsigned char *msg, int msg_len, unsigned char *sig, int sig_len) {
    return DSA_verify(0, msg, msg_len, sig, sig_len, dsa);
}

int main() {
    unsigned char msg[] = "Hello, world!";
    int msg_len = strlen(msg);

    // Generate a DSA key pair
    DSA *dsa = generate_dsa_key();
    if (!dsa) {
        return 1;
    }

    // Sign the message twice
    unsigned char sig1[512], sig2[512];
    int sig1_len, sig2_len;

    sign_dsa(dsa, msg, msg_len, sig1, &sig1_len);
    sign_dsa(dsa, msg, msg_len, sig2, &sig2_len);

    // Compare the signatures
    if (memcmp(sig1, sig2, sig1_len) == 0) {
        printf("Signatures are identical\n");
    } else {
        printf("Signatures are different\n");
    }

    // Free resources
    DSA_free(dsa);

    return 0;
}
