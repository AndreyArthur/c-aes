#ifndef BASE64_H
#define BASE64_H

#include <stddef.h>
#include <stdint.h>

/*
 * \brief Encodes binary data to base64.
 *
 * \param binary The binary data to encode.
 * \param len The length of the binary data.
 * \param buf The buffer to store the encoded data.
 */
void Base64Encode(const uint8_t *binary, size_t len, char *buf);

/*
 * \brief Decodes base64 string to binary.
 *
 * \param encoded The base64 string to decode.
 * \param buf The buffer to store the decoded data, the function assumes that it
 * has sufficient length.
 *
 * \return The length of the decoded data.
 */
size_t Base64Decode(const char *encoded, uint8_t *buf);

/*
 * \brief Calculates the length of the base64 encoded string based on the binary
 * data length
 *
 * \param binary_len The length of the binary data.
 *
 * \return The length of the base64 encoded string.
 */
size_t Base64CalculateEncodedLen(size_t binary_len);

/*
 * \brief Calculates the length of the binary data based on the base64 encoded
 *
 * \param encoded The base64 encoded string.
 *
 * \return The length of the binary data.
 */
size_t Base64CalculateDecodedLen(const char *encoded);

#endif
