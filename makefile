CC = gcc
CFLAGS = -Wall --pedantic
SRC = src/*.c
TARGET = bin/saper

all: bin
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

bin:
	mkdir -p bin

run: all
	$(TARGET)