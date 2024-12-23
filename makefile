CC = gcc
CFLAGS = -Wall --pedantic
SRC = src/*.c
TARGET = bin/saper

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run:all
	$(TARGET)
