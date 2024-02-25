CFLAGS = -Wall -Wno-unused-command-line-argument -Iinclude
CC = clang

SRC_DIR = src
SOURCES = $(wildcard $(SRC_DIR)/*.c)
SRC_OBJS = $(patsubst $(SRC_DIR)/%.c, $(SRC_DIR)/%.o, $(SOURCES))

OUT_DIR = bin

.PHONY: all clean

all: $(SRC_OBJS)
	if [ ! -d "$(OUT_DIR)" ]; then mkdir bin; fi
	$(CC) $(CFLAGS) $^ -g -o $(OUT_DIR)/cl2verilog

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f bin/* src/*.o
