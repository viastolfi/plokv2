BUILD = build
SRC = src

CS = \
	$(SRC)/main.c \
	$(SRC)/lexer.c

OBJ = \
	$(BUILD)/main.o \
	$(BUILD)/lexer.o

CC = gcc
CFLAGS = -Wall -Wextra -std=c99

.PHONY: all clean

all: $(BUILD)/plok

$(BUILD)/plok: $(OBJ)
	$(CC) -o $@ $^

$(BUILD)/%.o: $(SRC)/%.c
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD)

