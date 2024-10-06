#include "base64.h"
#include <string.h>

static const char base64_table[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

size_t Base64CharLookup(char character) {
    if (character >= 'A' && character <= 'Z')
        return character - 'A';
    if (character >= 'a' && character <= 'z')
        return character - 'a' + 26;
    if (character >= '0' && character <= '9')
        return character - '0' + 52;
    if (character == '+')
        return 62;
    if (character == '/')
        return 63;
    return SIZE_MAX;
}

void Base64Encode(const uint8_t *binary, size_t len, char *buf) {
    size_t encoded_index = 0;
    for (size_t i = 0; i < len; i += 3) {
        uint32_t octet_a = i < len ? binary[i] : 0;
        uint32_t octet_b = (i + 1) < len ? binary[i + 1] : 0;
        uint32_t octet_c = (i + 2) < len ? binary[i + 2] : 0;

        uint32_t combined = (octet_a << 16) | (octet_b << 8) | octet_c;

        buf[encoded_index++] = base64_table[(combined >> 18) & 0x3F];
        buf[encoded_index++] = base64_table[(combined >> 12) & 0x3F];
        buf[encoded_index++] =
            (i + 1) < len ? base64_table[(combined >> 6) & 0x3F] : '=';
        buf[encoded_index++] =
            (i + 2) < len ? base64_table[combined & 0x3F] : '=';
    }
    buf[encoded_index] = '\0';
}

size_t Base64Decode(const char *encoded, uint8_t *buf) {
    size_t len = strlen(encoded);
    size_t decoded_index = 0;

    for (size_t i = 0; i < len; i += 4) {
        uint32_t sextet_a = Base64CharLookup(encoded[i]);
        uint32_t sextet_b = Base64CharLookup(encoded[i + 1]);
        uint32_t sextet_c =
            encoded[i + 2] == '=' ? 0 : Base64CharLookup(encoded[i + 2]);
        uint32_t sextet_d =
            encoded[i + 3] == '=' ? 0 : Base64CharLookup(encoded[i + 3]);

        uint32_t combined =
            (sextet_a << 18) | (sextet_b << 12) | (sextet_c << 6) | sextet_d;

        buf[decoded_index++] = (combined >> 16) & 0xFF;

        if (encoded[i + 2] != '=' || encoded[i + 3] != '=')
            buf[decoded_index++] = (combined >> 8) & 0xFF;
        if (encoded[i + 3] != '=')
            buf[decoded_index++] = combined & 0xFF;
    }
    return decoded_index;
}

size_t Base64CalculateEncodedLen(size_t binary_len) {
    return ((binary_len + 2) / 3) * 4;
}

size_t Base64CalculateDecodedLen(const char *encoded) {
    size_t len = strlen(encoded);
    size_t padding = 0;

    if (len >= 2 && encoded[len - 1] == '=') {
        padding++;
    }
    if (len >= 2 && encoded[len - 2] == '=') {
        padding++;
    }

    return (len / 4) * 3 - padding;
}
