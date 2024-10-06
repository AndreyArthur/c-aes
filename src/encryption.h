#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include "aes.h"
#include <stddef.h>

size_t CalculateEncryptedLen(size_t plaintext_len);

void EncryptString(char *string, char *key_string, char *buf);

void DecryptString(char *string, char *key_string, char *buf);

#endif
