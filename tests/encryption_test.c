#include "../src/encryption.h"
#include <assert.h>
#include <string.h>

void TestCalculateEncryptedLen() {
    {
        size_t plaintext_len = 16;
        size_t expected = 44;

        size_t len = CalculateEncryptedLen(plaintext_len);

        assert(expected == len);
    }

    {
        size_t plaintext_len = 15;
        size_t expected = 24;

        size_t len = CalculateEncryptedLen(plaintext_len);

        assert(expected == len);
    }
}

void TestEncryptString() {
    {
        char *plaintext = "Hello, World!";
        char *key = "my 16 byte key that should be truncated";
        char *expected = "/3ek7D0uCfv8G3Ysz84AMQ==";

        size_t len = CalculateEncryptedLen(strlen(plaintext));
        char buf[len + 1];
        EncryptString(plaintext, key, buf);

        assert(strcmp(buf, expected) == 0);
    }

    {
        char *plaintext = "Hello, World!!!!";
        char *key = "my 16 byte key that should be truncated";
        char *expected = "C4je4ynWtGzXsoKFNB6f5V7JsF6NcV36cSqC4a5X9BA=";

        size_t len = CalculateEncryptedLen(strlen(plaintext));
        char buf[len + 1];
        EncryptString(plaintext, key, buf);

        assert(strcmp(buf, expected) == 0);
    }

    {
        char *plaintext = "The quick brown fox jumps over the lazy dog";
        char *key = "pangrampangrampa";
        char *expected =
            "OO83PHdQhv9krl8o85FBTLqKZEIeqLuienw/PCLrLqAfNw6ZPk9wFcuEJnkzZlRr";

        size_t len = CalculateEncryptedLen(strlen(plaintext));
        char buf[len + 1];
        EncryptString(plaintext, key, buf);

        assert(strcmp(buf, expected) == 0);
    }
}

void TestDecryptString() {
    {
        char *ciphertext = "/3ek7D0uCfv8G3Ysz84AMQ==";
        char *key = "my 16 byte key that of course was truncated";
        char *expected = "Hello, World!";

        char buf[strlen(ciphertext)];
        DecryptString(ciphertext, key, buf);

        assert(strcmp(buf, expected) == 0);
    }

    {
        char *ciphertext = "C4je4ynWtGzXsoKFNB6f5V7JsF6NcV36cSqC4a5X9BA=";
        char *expected = "Hello, World!!!!";
        char *key = "my 16 byte key that of course was truncated";

        char buf[strlen(ciphertext)];
        DecryptString(ciphertext, key, buf);

        assert(strcmp(buf, expected) == 0);
    }

    {
        char *ciphertext =
            "OO83PHdQhv9krl8o85FBTLqKZEIeqLuienw/PCLrLqAfNw6ZPk9wFcuEJnkzZlRr";
        char *expected = "The quick brown fox jumps over the lazy dog";
        char *key = "pangrampangrampa";

        char buf[strlen(ciphertext)];
        DecryptString(ciphertext, key, buf);

        assert(strcmp(buf, expected) == 0);
    }
}

int main() {
    TestCalculateEncryptedLen();

    TestEncryptString();
    TestDecryptString();

    return 0;
}
