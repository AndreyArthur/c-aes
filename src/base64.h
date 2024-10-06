#ifndef BASE64_H
#define BASE64_H

#include <stddef.h>
#include <stdint.h>

void Base64Encode(const uint8_t *binary, size_t len, char *buf);

size_t Base64Decode(const char *encoded, uint8_t *buf);

size_t Base64CalculateEncodedLen(size_t binary_len);

size_t Base64CalculateDecodedLen(const char *encoded);

#endif
