#include "../src/base64.h"
#include <assert.h>
#include <string.h>

void TestBase64Encode() {
    {
        uint8_t binary[15] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
                              0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee};
        char *expected = "ABEiM0RVZneImaq7zN3u";

        char buf[32];
        Base64Encode(binary, 15, buf);

        assert(strlen(buf) == strlen(expected));
        assert(strcmp(expected, buf) == 0);
    }

    {
        uint8_t binary[14] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66,
                              0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd};
        char *expected = "ABEiM0RVZneImaq7zN0=";

        char buf[32];
        Base64Encode(binary, 14, buf);

        assert(strlen(buf) == strlen(expected));
        assert(strcmp(expected, buf) == 0);
    }

    {
        uint8_t binary[16] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
                              0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
        char *expected = "ABEiM0RVZneImaq7zN3u/w==";

        char buf[32];
        Base64Encode(binary, 16, buf);

        assert(strlen(buf) == strlen(expected));
        assert(strcmp(expected, buf) == 0);
    }
}

void TestBase64Decode() {
    {
        char *encoded = "ABEiM0RVZneImaq7zN3u";
        uint8_t expected[15] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
                                0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee};

        uint8_t buf[15];
        size_t len = Base64Decode(encoded, buf);

        assert(memcmp(expected, buf, 15) == 0);
        assert(len == 15);
    }

    {
        char *encoded = "ABEiM0RVZneImaq7zN0=";
        uint8_t expected[14] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66,
                                0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd};

        uint8_t buf[14];
        size_t len = Base64Decode(encoded, buf);

        assert(memcmp(expected, buf, 14) == 0);
        assert(len == 14);
    }

    {
        char *encoded = "ABEiM0RVZneImaq7zN3u/w==";
        uint8_t expected[16] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
                                0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};

        uint8_t buf[16];
        size_t len = Base64Decode(encoded, buf);

        assert(memcmp(expected, buf, 16) == 0);
        assert(len == 16);
    }
}

void TestBase64CalculateEncodedLen() {
    {
        uint8_t binary[15] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
                              0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee};
        size_t expected = 20;

        size_t len = Base64CalculateEncodedLen(15);

        char buf[32];
        Base64Encode(binary, 15, buf);

        assert(strlen(buf) == len);
        assert(len == expected);
    }

    {
        uint8_t binary[14] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66,
                              0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd};
        size_t expected = 20;

        size_t len = Base64CalculateEncodedLen(14);

        char buf[32];
        Base64Encode(binary, 14, buf);

        assert(strlen(buf) == len);
        assert(len == expected);
    }

    {
        uint8_t binary[16] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
                              0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
        size_t expected = 24;

        size_t len = Base64CalculateEncodedLen(16);

        char buf[32];
        Base64Encode(binary, 16, buf);

        assert(strlen(buf) == len);
        assert(len == expected);
    }
}

void TestBase64CalculateDecodedLen() {
    {
        char *encoded = "ABEiM0RVZneImaq7zN3u";
        size_t expected = 15;

        size_t len = Base64CalculateDecodedLen(encoded);

        uint8_t buf[15];
        size_t actual_len = Base64Decode(encoded, buf);

        assert(len == actual_len);
        assert(actual_len == expected);
    }

    {
        char *encoded = "ABEiM0RVZneImaq7zN0=";
        size_t expected = 14;

        size_t len = Base64CalculateDecodedLen(encoded);

        uint8_t buf[14];
        size_t actual_len = Base64Decode(encoded, buf);

        assert(len == actual_len);
        assert(actual_len == expected);
    }

    {
        char *encoded = "ABEiM0RVZneImaq7zN3u/w==";
        size_t expected = 16;

        size_t len = Base64CalculateDecodedLen(encoded);

        uint8_t buf[16];
        size_t actual_len = Base64Decode(encoded, buf);

        assert(len == actual_len);
        assert(actual_len == expected);
    }
}

int main() {
    TestBase64Encode();
    TestBase64Decode();

    TestBase64CalculateEncodedLen();
    TestBase64CalculateDecodedLen();

    return 0;
}
