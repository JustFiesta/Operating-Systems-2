# Nazwa pliku wykonywalnego
TARGET = env-manager

# Katalog źródeł
SRC_DIR = src

# Pliki źródłowe
SRC = $(SRC_DIR)/env-manager.c

# Flagi kompilatora
CFLAGS = -Wall -Wextra -O2

# Domyślne zadanie: kompilacja programu
all: $(TARGET)

# Kompilacja programu
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $< -o $@

# Uruchamianie programu
run: $(TARGET)
	./$(TARGET)

# Czyszczenie plików wykonywalnych
clean:
	rm -f $(TARGET)

# Phony targets (niezależne od plików w katalogu)
.PHONY: all run clean
