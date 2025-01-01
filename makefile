CC = gcc
CFLAGS = -Wall --pedantic
SRC = src/*.c
TARGET = bin/saper

all: prepare bin
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

prepare:
	mkdir -p bin
	mkdir -p data
	touch data/scoreboard.txt
	chmod 777 data
	chmod 666 data/scoreboard.txt

bin:
	mkdir -p bin

run: all
	$(TARGET)

clean:
	rm -rf bin
	rm -rf data/scoreboard.txt