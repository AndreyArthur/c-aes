#include "encryption.h"
#include "aes.h"
#include "base64.h"
#include <string.h>

size_t CalculatePaddedLen(size_t plaintext_len) {
    return plaintext_len % Nb * Nb == 0
               ? plaintext_len + Nb * Nb
               : plaintext_len + (Nb * Nb - plaintext_len % (Nb * Nb));
}

size_t CalculateEncryptedLen(size_t plaintext_len) {
    return Base64CalculateEncodedLen(CalculatePaddedLen(plaintext_len));
}

void StringToKey(char *string, uint8_t key[Nk * Nb]) {
    size_t string_len = strlen(string);
    uint8_t padding = 0;

    for (size_t i = 0; i < Nk * Nb; i++) {
        if (i < string_len) {
            key[i] = string[i];
        } else {
            key[i] = padding;
        }
    }
}

void EncryptString(char *string, char *key_string, char *buf) {
    uint8_t key[Nk * Nb];
    StringToKey(key_string, key);

    uint32_t expanded_key[Nb * (Nr + 1)];
    KeyExpansion(key, expanded_key);

    size_t string_len = strlen(string);
    size_t len = CalculatePaddedLen(string_len);
    uint8_t padding = len - string_len;

    uint8_t plaintext[len];
    for (size_t i = 0; i < len; i++) {
        if (i < string_len) {
            plaintext[i] = string[i];
        } else {
            plaintext[i] = padding;
        }
    }

    uint8_t ciphertext[len];
    for (size_t i = 0; i < len; i += Nb * Nb) {
        Cipher(&plaintext[i], &ciphertext[i], expanded_key);
    }

    Base64Encode(ciphertext, len, buf);
}

size_t GetPaddingIndex(uint8_t *plaintext, size_t len) {
    return len - plaintext[len - 1];
}

void DecryptString(char *string, char *key_string, char *buf) {
    uint8_t key[Nk * Nb];
    StringToKey(key_string, key);

    uint32_t expanded_key[Nb * (Nr + 1)];
    KeyExpansion(key, expanded_key);

    size_t encoded_len = strlen(string);

    uint8_t ciphertext[encoded_len];
    size_t len = Base64Decode(string, ciphertext);

    uint8_t plaintext[len];
    for (size_t i = 0; i < len; i += Nb * Nb) {
        InvCipher(&ciphertext[i], &plaintext[i], expanded_key);
    }

    size_t end = GetPaddingIndex(plaintext, len);

    memcpy(buf, plaintext, end);

    buf[end] = '\0';
}
