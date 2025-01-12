CC = gcc
# CFLAGS = -Wall --pedantic
TARGET = bin/saper
TEST_TARGET = bin/tests

# Kompilacja głównej aplikacji
all: prepare $(TARGET)

$(TARGET): src/main.c src/lib/board.c src/lib/scoreboard.c src/lib/game.c
	$(CC) $(CFLAGS) src/main.c src/lib/board.c src/lib/scoreboard.c src/lib/game.c -o $(TARGET) -I src/include

# Przygotowanie katalogów
prepare:
	mkdir -p bin
	mkdir -p data
	touch data/scoreboard.txt
	chmod 777 data
	chmod 666 data/scoreboard.txt

# Kompilacja testów
$(TEST_TARGET): src/test/test_board.c src/lib/board.c src/lib/scoreboard.c src/lib/game.c
	$(CC) $(CFLAGS) src/test/test_board.c src/lib/board.c src/lib/scoreboard.c src/lib/game.c -o $(TEST_TARGET) -I src/include

# Uruchamianie testów
test: $(TEST_TARGET)
	$(TEST_TARGET)

# Uruchamianie programu
run: $(TARGET)
	$(TARGET)

# Czyszczenie plików binarnych i danych
clean:
	rm -rf bin
clean-scores:
	rm -rf data/scoreboard.txt