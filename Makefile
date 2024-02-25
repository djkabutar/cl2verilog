CFLAGS = -Wall -Wno-unused-command-line-argument -Iinclude
CC = clang

SRC_DIR = src
SOURCES = $(wildcard $(SRC_DIR)/*.c)
SRC_OBJS = $(patsubst $(SRC_DIR)/%.c, $(SRC_DIR)/%.o, $(SOURCES))

TEST_DIR = tests
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.c, $(TEST_DIR)/%.o, $(TEST_SOURCES))

OUT_DIR = bin

.PHONY: all main test clean

all: main test

main: $(SRC_OBJS)
	if [ ! -d "$(OUT_DIR)" ]; then mkdir bin; fi
	$(CC) $(CFLAGS) $^ -g -o $(OUT_DIR)/cl2verilog

test: src/macro_processing.o src/preprocessing.o src/hashfunc.o $(TEST_OBJS)
	if [ ! -d "$(OUT_DIR)" ]; then mkdir bin; fi
	$(CC) $(CFLAGS) $^ -g -o $(OUT_DIR)/test

$(TEST_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f bin/* src/*.o tests/*.o
