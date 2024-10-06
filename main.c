#include "src/base64.h"
#include "src/encryption.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void ReadLine(char *buf, size_t end) {
    size_t i = 0;
    bool newline = false;
    while (i <= end && !newline) {
        char current = getchar();
        if (current == '\n') {
            buf[i] = '\0';
            newline = true;
        } else {
            buf[i] = current;
            i++;
        }
    }
    buf[end] = '\0';

    while (!newline) {
        char current = getchar();
        if (current == '\n') {
            newline = true;
        }
    }
}

void Encrypt() {
    char plaintext[513];
    printf("Insira o texto a ser criptografado: ");
    ReadLine(plaintext, 512);

    char key[17];
    printf("Insira a chave: ");
    ReadLine(key, 16);

    size_t len = CalculateEncryptedLen(strlen(plaintext));
    char buf[len + 1];
    EncryptString(plaintext, key, buf);

    printf("Seu texto criptografado: %s\n", buf);
}

void Decrypt() {
    char ciphertext[1025];
    printf("Insira o texto criptografado: ");
    ReadLine(ciphertext, 1024);

    char key[17];
    printf("Insira a chave: ");
    ReadLine(key, 16);

    char buf[strlen(ciphertext)];
    DecryptString(ciphertext, key, buf);

    printf("Seu texto original: %s\n", buf);
}

int main() {
    char option = '\0';
    while (option != 'C' && option != 'c' && option != 'D' && option != 'd') {
        char buf[3];
        printf("Criptografar ou Descriptografar? [C/D] ");
        ReadLine(buf, 2);

        if (strlen(buf) > 1) {
            continue;
        }

        option = buf[0];

        switch (option) {
        case 'C':
            Encrypt();
            break;
        case 'c':
            Encrypt();
            break;
        case 'D':
            Decrypt();
            break;
        case 'd':
            Decrypt();
            break;
        default:
            break;
        }
    }

    return 0;
}
