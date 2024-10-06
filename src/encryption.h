#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include "aes.h"
#include <stddef.h>

/*
 * \brief Calculates the length of the encrypted string based on the plaintext
 * length.
 *
 * \param plaintext_len: The length of the plaintext.
 *
 * \return The length of the encrypted string.
 */
size_t CalculateEncryptedLen(size_t plaintext_len);

/*
 * \brief Encrypts a string to a base64 ciphertext.
 *
 * \param string The original message.
 * \param key_string The encryption key as string.
 * \param buf The decrypted buffer, the function assumes that it has sufficient
 * length.
 */
void EncryptString(char *string, char *key_string, char *buf);

/*
 * \brief Decrypts an encrypted base64 string.
 *
 * \param string The encrypted base64 string.
 * \param key_string The encryption key as string.
 * \param buf The decrypted buffer, the function assumes that it has sufficient
 * length.
 */
void DecryptString(char *string, char *key_string, char *buf);

#endif
