CFLAGS = -Wall -Wno-unused-command-line-argument
CC = clang

SRC_DIR = src
SOURCES = $(wildcard $(SRC_DIR)/*.c)

OUT_DIR = bin

.PHONY: all clean

all: $(SOURCES)
	if [ ! -d "$(OUT_DIR)" ]; then mkdir bin; fi
	$(CC) $(CFLAGS) $^ -g -o $(OUT_DIR)/cl2verilog

clean:
	rm -f bin/* src/*.o
