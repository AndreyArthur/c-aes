CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic

SRC_DIR=src
SRC_SOURCES=$(wildcard $(SRC_DIR)/*.c)

OBJECTS_DIR=objects
SRC_OBJECTS=$(patsubst $(SRC_DIR)/%.c, $(OBJECTS_DIR)/%.o, $(SRC_SOURCES))

TESTS_DIR=tests
TESTS_SOURCES=$(wildcard $(TESTS_DIR)/*.c)

TESTS_OBJECTS=$(patsubst $(TESTS_DIR)/%.c, $(OBJECTS_DIR)/%.o, $(TESTS_SOURCES))

BIN_DIR=bin
TESTS_BINS=$(patsubst $(TESTS_DIR)/%.c, $(BIN_DIR)/%, $(TESTS_SOURCES))
MAIN_BIN=$(BIN_DIR)/main

all: $(MAIN_BIN)

clean:
	rm -rf $(BIN_DIR) $(OBJECTS_DIR)

run: $(MAIN_BIN)
	./$(MAIN_BIN)

test: $(TESTS_BINS)

runtest: $(TESTS_BINS)
	./$(BIN_DIR)/aes_test
	./$(BIN_DIR)/base64_test
	./$(BIN_DIR)/encryption_test

$(SRC_OBJECTS): $(OBJECTS_DIR) $(SRC_SOURCES)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/aes.c -o $(OBJECTS_DIR)/aes.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/base64.c -o $(OBJECTS_DIR)/base64.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/encryption.c -o $(OBJECTS_DIR)/encryption.o

$(TESTS_OBJECTS): $(OBJECTS_DIR) $(TESTS_SOURCES)
	$(CC) $(CFLAGS) -c $(TESTS_DIR)/aes_test.c -o $(OBJECTS_DIR)/aes_test.o
	$(CC) $(CFLAGS) -c $(TESTS_DIR)/base64_test.c -o $(OBJECTS_DIR)/base64_test.o
	$(CC) $(CFLAGS) -c $(TESTS_DIR)/encryption_test.c -o $(OBJECTS_DIR)/encryption_test.o

$(TESTS_BINS): $(BIN_DIR) $(SRC_OBJECTS) $(TESTS_OBJECTS)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/aes_test  $(OBJECTS_DIR)/aes_test.o $(SRC_OBJECTS)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/base64_test  $(OBJECTS_DIR)/base64_test.o $(SRC_OBJECTS)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/encryption_test  $(OBJECTS_DIR)/encryption_test.o $(SRC_OBJECTS)

$(MAIN_BIN): $(BIN_DIR) $(SRC_OBJECTS)
	$(CC) $(CFLAGS) -o $@  main.c $(SRC_OBJECTS)

$(OBJECTS_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@
