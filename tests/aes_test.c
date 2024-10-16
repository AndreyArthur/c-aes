#include "../src/aes.h"
#include <assert.h>
#include <stddef.h>

void TestKeyExpansion() {
    uint8_t key[Nk * Nb] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
                            0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
    uint32_t expkey[Nb * (Nr + 1)] = {
        0x2b7e1516, 0x28aed2a6, 0xabf71588, 0x09cf4f3c, 0xa0fafe17, 0x88542cb1,
        0x23a33939, 0x2a6c7605, 0xf2c295f2, 0x7a96b943, 0x5935807a, 0x7359f67f,
        0x3d80477d, 0x4716fe3e, 0x1e237e44, 0x6d7a883b, 0xef44a541, 0xa8525b7f,
        0xb671253b, 0xdb0bad00, 0xd4d1c6f8, 0x7c839d87, 0xcaf2b8bc, 0x11f915bc,
        0x6d88a37a, 0x110b3efd, 0xdbf98641, 0xca0093fd, 0x4e54f70e, 0x5f5fc9f3,
        0x84a64fb2, 0x4ea6dc4f, 0xead27321, 0xb58dbad2, 0x312bf560, 0x7f8d292f,
        0xac7766f3, 0x19fadc21, 0x28d12941, 0x575c006e, 0xd014f9a8, 0xc9ee2589,
        0xe13f0cc8, 0xb6630ca6};
    uint32_t w[Nb * (Nr + 1)];

    KeyExpansion(key, w);

    for (size_t i = 0; i < Nb * (Nr + 1); i++) {
        assert(expkey[i] == w[i]);
    }
}

void TestAddRoundKey() {
    uint8_t input[Nb][Nb] = {{0xdb, 0x13, 0x53, 0x45},
                             {0xf2, 0x0a, 0x22, 0x5c},
                             {0x01, 0x01, 0x01, 0x01},
                             {0xc6, 0xc6, 0xc6, 0xc6}};
    uint32_t key[Nb] = {0xdbf201c6, 0x130a01c6, 0x532201c6, 0x455c01c6};
    uint8_t expected[Nb][Nb] = {{0x00, 0x00, 0x00, 0x00},
                                {0x00, 0x00, 0x00, 0x00},
                                {0x00, 0x00, 0x00, 0x00},
                                {0x00, 0x00, 0x00, 0x00}};
    AddRoundKey(input, key);

    for (size_t i = 0; i < Nb; i++) {
        for (size_t j = 0; j < Nb; j++) {
            assert(input[i][j] == expected[i][j]);
        }
    }
}

void TestSubBytes() {
    uint8_t input[Nb][Nb] = {{0x8e, 0x9f, 0xf1, 0xc6},
                             {0x4d, 0xdc, 0xe1, 0xc7},
                             {0xa1, 0x58, 0xd1, 0xc8},
                             {0xbc, 0x9d, 0xc1, 0xc9}};
    uint8_t expected[Nb][Nb] = {{0x19, 0xdb, 0xa1, 0xb4},
                                {0xe3, 0x86, 0xf8, 0xc6},
                                {0x32, 0x6a, 0x3e, 0xe8},
                                {0x65, 0x5e, 0x78, 0xdd}};
    SubBytes(input);

    for (size_t i = 0; i < Nb; i++) {
        for (size_t j = 0; j < Nb; j++) {
            assert(input[i][j] == expected[i][j]);
        }
    }
}

void TestShiftRows() {
    uint8_t input[Nb][Nb] = {{0x8e, 0x9f, 0x01, 0xc6},
                             {0x4d, 0xdc, 0x01, 0xc6},
                             {0xa1, 0x58, 0x01, 0xc6},
                             {0xbc, 0x9d, 0x01, 0xc6}};
    uint8_t expected[Nb][Nb] = {{0x8e, 0x9f, 0x01, 0xc6},
                                {0xdc, 0x01, 0xc6, 0x4d},
                                {0x01, 0xc6, 0xa1, 0x58},
                                {0xc6, 0xbc, 0x9d, 0x01}};
    ShiftRows(input);

    for (size_t i = 0; i < Nb; i++) {
        for (size_t j = 0; j < Nb; j++) {
            assert(input[i][j] == expected[i][j]);
        }
    }
}

void TestMixColumns() {
    uint8_t input[Nb][Nb] = {{0xdb, 0xf2, 0x01, 0xc6},
                             {0x13, 0x0a, 0x01, 0xc6},
                             {0x53, 0x22, 0x01, 0xc6},
                             {0x45, 0x5c, 0x01, 0xc6}};
    uint8_t expected[Nb][Nb] = {{0x8e, 0x9f, 0x01, 0xc6},
                                {0x4d, 0xdc, 0x01, 0xc6},
                                {0xa1, 0x58, 0x01, 0xc6},
                                {0xbc, 0x9d, 0x01, 0xc6}};
    MixColumns(input);

    for (size_t i = 0; i < Nb; i++) {
        for (size_t j = 0; j < Nb; j++) {
            assert(input[i][j] == expected[i][j]);
        }
    }
}

void TestCipher() {
    uint8_t input[Nb * Nb] = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d,
                              0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};
    uint8_t key[Nk * Nb] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
                            0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
    uint8_t expected[Nb * Nb] = {0x39, 0x25, 0x84, 0x1d, 0x02, 0xdc,
                                 0x09, 0xfb, 0xdc, 0x11, 0x85, 0x97,
                                 0x19, 0x6a, 0x0b, 0x32};

    uint32_t expkey[Nb * (Nr + 1)];
    KeyExpansion(key, expkey);

    uint8_t output[Nb * Nb];
    Cipher(input, output, expkey);

    for (size_t i = 0; i < Nb * Nb; i++) {
        assert(output[i] == expected[i]);
    }
}

void TestInvSubBytes() {
    uint8_t input[Nb][Nb] = {{0x19, 0xdb, 0xa1, 0xb4},
                             {0xe3, 0x86, 0xf8, 0xc6},
                             {0x32, 0x6a, 0x3e, 0xe8},
                             {0x65, 0x5e, 0x78, 0xdd}};
    uint8_t expected[Nb][Nb] = {{0x8e, 0x9f, 0xf1, 0xc6},
                                {0x4d, 0xdc, 0xe1, 0xc7},
                                {0xa1, 0x58, 0xd1, 0xc8},
                                {0xbc, 0x9d, 0xc1, 0xc9}};
    InvSubBytes(input);

    for (size_t i = 0; i < Nb; i++) {
        for (size_t j = 0; j < Nb; j++) {
            assert(input[i][j] == expected[i][j]);
        }
    }
}

void TestInvShiftRows() {
    uint8_t input[Nb][Nb] = {{0x8e, 0x9f, 0x01, 0xc6},
                             {0xdc, 0x01, 0xc6, 0x4d},
                             {0x01, 0xc6, 0xa1, 0x58},
                             {0xc6, 0xbc, 0x9d, 0x01}};
    uint8_t expected[Nb][Nb] = {{0x8e, 0x9f, 0x01, 0xc6},
                                {0x4d, 0xdc, 0x01, 0xc6},
                                {0xa1, 0x58, 0x01, 0xc6},
                                {0xbc, 0x9d, 0x01, 0xc6}};
    InvShiftRows(input);

    for (size_t i = 0; i < Nb; i++) {
        for (size_t j = 0; j < Nb; j++) {
            assert(input[i][j] == expected[i][j]);
        }
    }
}

void TestInvMixColumns() {
    uint8_t input[Nb][Nb] = {{0x8e, 0x9f, 0x01, 0xc6},
                             {0x4d, 0xdc, 0x01, 0xc6},
                             {0xa1, 0x58, 0x01, 0xc6},
                             {0xbc, 0x9d, 0x01, 0xc6}};
    uint8_t expected[Nb][Nb] = {{0xdb, 0xf2, 0x01, 0xc6},
                                {0x13, 0x0a, 0x01, 0xc6},
                                {0x53, 0x22, 0x01, 0xc6},
                                {0x45, 0x5c, 0x01, 0xc6}};
    InvMixColumns(input);

    for (size_t i = 0; i < Nb; i++) {
        for (size_t j = 0; j < Nb; j++) {
            assert(input[i][j] == expected[i][j]);
        }
    }
}

void TestInvCipher() {
    uint8_t input[Nb * Nb] = {0x39, 0x25, 0x84, 0x1d, 0x02, 0xdc, 0x09, 0xfb,
                              0xdc, 0x11, 0x85, 0x97, 0x19, 0x6a, 0x0b, 0x32};
    uint8_t key[Nk * Nb] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
                            0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
    uint8_t expected[Nb * Nb] = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a,
                                 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2,
                                 0xe0, 0x37, 0x07, 0x34};

    uint32_t expkey[Nb * (Nr + 1)];
    KeyExpansion(key, expkey);

    uint8_t output[Nb * Nb];
    InvCipher(input, output, expkey);

    for (size_t i = 0; i < Nb * Nb; i++) {
        assert(output[i] == expected[i]);
    }
}

int main() {
    TestKeyExpansion();

    TestAddRoundKey();

    TestSubBytes();
    TestShiftRows();
    TestMixColumns();
    TestCipher();

    TestInvSubBytes();
    TestInvShiftRows();
    TestInvMixColumns();
    TestInvCipher();

    return 0;
}
