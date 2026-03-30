# Kompilator
CC = gcc

# Flagi kompilatora (włączone wszystkie ostrzeżenia, standard C11)
CFLAGS = -Wall -Wextra -Wpedantic -std=c11 -g

# Flagi linkera (-lm jest wymagane do funkcji matematycznych np. sqrt z <math.h>)
LDFLAGS = -lm

# Nazwa pliku wynikowego (aplikacji)
TARGET = program_c

# Lista plików źródłowych (.c)
SRCS = main.c io.c layout.c

# Zamiana listy plików .c na listę plików obiektowych .o
OBJS = $(SRCS:.c=.o)

# Domyślny cel kompilacji
.PHONY: all clean

all: $(TARGET)

# Jak zbudować ostateczny program
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Jak kompilować poszczególne pliki .c na pliki .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Reguła do czyszczenia projektu (usuwa pliki .o i plik wykonywalny)
clean:
# Używamy komend Windowsowych (del) lub uniksowych (rm) w zależności od systemu
ifeq ($(OS),Windows_NT)
	del /Q /F *.o $(TARGET).exe 2>nul || true
else
	rm -f $(OBJS) $(TARGET)
endif