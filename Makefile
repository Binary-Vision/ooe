CC = gcc
CC_FILES = *.c
CC_FLAGS = -Wall -Wextra -pedantic -std=c99 -fsanitize=address -g

EXEC = ooe

BUILD_CMD = $(CC) $(CC_FILES) -o $(EXEC) $(CC_FLAGS)

build:
	$(BUILD_CMD)