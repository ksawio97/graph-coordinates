# Kompilator
CC = gcc

# Flagi kompilatora (włączone wszystkie ostrzeżenia, standard C11)
CFLAGS = -Wall -Wextra -Wpedantic -std=gnu11 -g

# Flagi linkera (-lm jest wymagane do funkcji matematycznych np. sqrt z <math.h>)
LDFLAGS = -lm

SRC_DIR := ./src
BUILD_DIR := ./build
BIN_DIR := ./bin
# Nazwa pliku wynikowego (aplikacji)
TARGET = program_c

# Lista plików źródłowych (.c)
SRCS = main.c io.c layout.c

# gdzie umieszczone są pliki (.c - SRC_FILES) (.o - OBJ_FILES) (program - BIN_DIR)
SRC_FILES := $(addprefix $(SRC_DIR)/,$(SRCS))
OBJ_FILES := $(addprefix $(BUILD_DIR)/,$(SRCS:.c=.o))
TARGET := $(BIN_DIR)/app

# Domyślny cel kompilacji
.PHONY: all clean

all: $(TARGET)

# Jak zbudować ostateczny program
$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ_FILES) $(LDFLAGS)

# Jak kompilować poszczególne pliki .c na pliki .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Reguła do czyszczenia projektu (usuwa pliki .o i plik wykonywalny)
clean:
# Używamy komend Windowsowych (del) lub uniksowych (rm) w zależności od systemu
ifeq ($(OS),Windows_NT)
	del /Q /F *.o $(TARGET).exe 2>nul || true
else
	rm -f $(OBJS) $(TARGET)
endif
