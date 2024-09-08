#ifndef AES_H
#define AES_H

#include <stdint.h>

#define Nb 4
#define Nk 4
#define Nr 10

void KeyExpansion(uint8_t key[Nb * Nb], uint32_t w[Nb * (Nr + 1)]);

void AddRoundKey(uint8_t state[Nb][Nb], uint32_t key[Nb]);

void SubBytes(uint8_t state[Nb][Nb]);

void ShiftRows(uint8_t state[Nb][Nb]);

void MixColumns(uint8_t state[Nb][Nb]);

void Cipher(uint8_t in[Nb * Nb], uint8_t out[Nb * Nb],
            uint32_t w[Nk * (Nr + 1)]);

void InvSubBytes(uint8_t state[Nb][Nb]);

void InvShiftRows(uint8_t state[Nb][Nb]);

void InvMixColumns(uint8_t state[Nb][Nb]);

void InvCipher(uint8_t in[Nb * Nb], uint8_t out[Nb * Nb],
               uint32_t w[Nk * (Nr + 1)]);

#endif
