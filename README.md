# AES Encryption in C

This is a simple implementation of AES encryption in C, using ECB mode for educational and demonstration purposes. **It should not be used in production environments.**

## Features
- Encrypt and decrypt text using the AES algorithm in ECB mode.
- Example interface in the terminal for easy usage.

## Build Instructions

### Prerequisites
- `gcc` is required to compile the code.
- The project supports Linux, macOS, and Windows.

### How to Build

#### Linux/macOS:
1. Clone the repository or download the source code as a ZIP file.
2. Navigate to the project directory.
3. Run the following command to compile:
   ```bash
   make
   ```
4. Run the program:
   ```bash
   ./bin/main
   ```

#### Windows:
1. Clone the repository or download the source code as a ZIP file.
2. Navigate to the project directory.
3. Run the following command to compile:
   ```bash
   gcc -o .\main.exe .\main.c .\src\aes.c .\src\base64.c .\src\encryption.c
   ```
4. Run the program:
   ```bash
   .\main.exe
   ```

## Usage Example

### Encrypting a Text
```bash
$ ./bin/main
Criptografar ou Descriptografar? [C/D] c
Insira o texto a ser criptografado: The quick brown fox jumps over the lazy dog
Insira a chave: Hello, World!
Seu texto criptografado: dmEj4noX8Qvuavc1KccFynwm3gtmO5CYoU8teQcmuEIPWSszvLWpu7eG844tozjQ
```

### Decrypting a Text
```bash
$ ./bin/main
Criptografar ou Descriptografar? [C/D] d
Insira o texto criptografado: dmEj4noX8Qvuavc1KccFynwm3gtmO5CYoU8teQcmuEIPWSszvLWpu7eG844tozjQ
Insira a chave: Hello, World!
Seu texto original: The quick brown fox jumps over the lazy dog
```

## Notes
- This implementation uses **ECB (Electronic Codebook)** mode, which is not secure for encrypting sensitive data.
- The implementation is designed for educational purposes only.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.
