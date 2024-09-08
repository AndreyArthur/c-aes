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

all: $(SRC_OBJECTS)

clean:
	rm -rf $(BIN_DIR) $(OBJECTS_DIR)

test: $(TESTS_BINS)

runtest: $(TESTS_BINS)
	./$(BIN_DIR)/aes_test

$(SRC_OBJECTS): $(OBJECTS_DIR) $(SRC_SOURCES)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/aes.c -o $(OBJECTS_DIR)/aes.o

$(TESTS_OBJECTS): $(OBJECTS_DIR) $(TESTS_SOURCES)
	$(CC) $(CFLAGS) -c $(TESTS_DIR)/aes_test.c -o $(OBJECTS_DIR)/aes_test.o

$(TESTS_BINS): $(BIN_DIR) $(SRC_OBJECTS) $(TESTS_OBJECTS)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/aes_test  $(OBJECTS_DIR)/aes_test.o $(SRC_OBJECTS)

$(OBJECTS_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@
