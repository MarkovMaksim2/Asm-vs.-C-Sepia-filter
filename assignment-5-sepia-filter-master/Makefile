.PHONY: build clean

CC=gcc
SRC_DIR=src
INCLUDE_DIR=include
H_FILES=$(wildcard $(INCLUDE_DIR)/*.h)
C_FLAGS=-I $(INCLUDE_DIR) -Wall -Werror
OUT_FILE=obj/program

OBJ_DIR=obj
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(wildcard $(SRC_DIR)/*.c))
OBJ_FILES+= $(patsubst $(SRC_DIR)/%.asm, $(OBJ_DIR)/%.asm.o, $(wildcard $(SRC_DIR)/*.asm))

build: $(OUT_FILE);

$(OUT_FILE): $(OBJ_FILES)
	$(CC) -o $@ $(OBJ_FILES) -no-pie

$(OBJ_DIR)/%.asm.o: $(SRC_DIR)/%.asm
	mkdir -p $(OBJ_DIR)
	nasm -f elf64 -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(H_FILES)
	mkdir -p $(OBJ_DIR)
	$(CC) $(C_FLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR)
