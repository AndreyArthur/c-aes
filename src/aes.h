#ifndef AES_H
#define AES_H

#include <stdint.h>

#define Nb 4
#define Nk 4
#define Nr 10

/*
 * \brief Expands AES Key using AES Key Schedule.
 *
 * \param key The key to expand.
 * \param w The expanded key buffer.
 */
void KeyExpansion(uint8_t key[Nk * Nb], uint32_t w[Nb * (Nr + 1)]);

/*
 * \brief Adds the round key to the state with a XOR operation.
 *
 * \param state The state to add the round key to.
 * \param key The round key.
 */
void AddRoundKey(uint8_t state[Nb][Nb], uint32_t key[Nb]);

/*
 * \brief Substitutes the state bytes with the S-Box.
 *
 * \param state The state to substitute.
 */
void SubBytes(uint8_t state[Nb][Nb]);

/*
 * \brief Shifts the rows of the state to the left.
 *
 * \param state The state to shift.
 */
void ShiftRows(uint8_t state[Nb][Nb]);

/*
 * \brief Mix each column of the state with a polynomial.
 *
 * \param state The state to mix.
 */
void MixColumns(uint8_t state[Nb][Nb]);

/*
 * \brief Performs the AES encryption algorithm.
 *
 * \param in The plaintext.
 * \param out The ciphertext buffer.
 * \param w The expanded key.
 */
void Cipher(uint8_t in[Nb * Nb], uint8_t out[Nb * Nb],
            uint32_t w[Nk * (Nr + 1)]);

/*
 * \brief Substitutes the state bytes with the inverse S-Box.
 *
 * \param state The state to substitute.
 */
void InvSubBytes(uint8_t state[Nb][Nb]);

/*
 * \brief Shifts the rows of the state to the right.
 *
 * \param state The state to shift.
 */
void InvShiftRows(uint8_t state[Nb][Nb]);

/*
 * \brief Mixes each column of the state with the inverse polynomial.
 *
 * \param state The state to mix.
 */
void InvMixColumns(uint8_t state[Nb][Nb]);

/*
 * \brief Performs the AES decryption algorithm.
 *
 * \param in The ciphertext.
 * \param out The plaintext buffer.
 * \param w The expanded key.
 */
void InvCipher(uint8_t in[Nb * Nb], uint8_t out[Nb * Nb],
               uint32_t w[Nk * (Nr + 1)]);

#endif
