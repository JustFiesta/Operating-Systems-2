# Nazwa pliku wykonywalnego
TARGET = resource-monitor

# Katalogi
SRC_DIR = src
OBJ_DIR = obj
TEST_DIR = tests

# Pliki źródłowe
SRC = $(SRC_DIR)/resource-monitor.c
OBJ = $(OBJ_DIR)/resource-monitor.o

# Kompilator i flagi
CC = gcc
# Flagi podstawowe
CFLAGS = -Wall # -Wall (wszystkie ostrzeżenia)
# Flagi optymalizacji
CFLAGS += -O2
# Flagi bezpieczeństwa
CFLAGS += -fstack-protector-all -D_FORTIFY_SOURCE=2
# Flagi standardu
CFLAGS += -std=c11

# Flagi dla wersji debug
DEBUG_FLAGS = -g -DDEBUG

# Domyślne zadanie: kompilacja programu
all: dirs $(TARGET)

# Tworzenie potrzebnych katalogów
dirs:
	mkdir -p $(OBJ_DIR)

# Kompilacja programu
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@

# Kompilacja obiektów
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Wersja debug
debug: CFLAGS += $(DEBUG_FLAGS)
debug: clean all

# Uruchamianie programu
run: $(TARGET)
	./$(TARGET)

# Target do testów
test: $(TARGET)
	@echo "Running tests..."
	@if [ -d "$(TEST_DIR)" ]; then \
		for test in $(TEST_DIR)/*.sh; do \
			if [ -f "$$test" ]; then \
				echo "\nRunning $$test:"; \
				bash "$$test"; \
			fi \
		done \
	else \
		echo "No tests directory found."; \
	fi

# Sprawdzanie poprawności kodu
check: $(SRC)
	cppcheck --enable=all --suppress=missingIncludeSystem $(SRC)

# Czyszczenie plików wykonywalnych i obiektów
clean:
	rm -f $(TARGET)
	rm -rf $(OBJ_DIR)

# Instalacja (opcjonalne)
install: $(TARGET)
	install -d $(DESTDIR)/usr/local/bin
	install -m 755 $(TARGET) $(DESTDIR)/usr/local/bin

# Pomoc
help:
	@echo "Available targets:"
	@echo "  all     : Build the program (default)"
	@echo "  debug   : Build with debug information"
	@echo "  run     : Build and run the program"
	@echo "  test    : Run test suite"
	@echo "  check   : Run static code analysis"
	@echo "  clean   : Remove built files"
	@echo "  install : Install the program"
	@echo "  help    : Show this help message"

# Phony targets
.PHONY: all dirs debug run test check clean install help