CFLAGS = -Wall --pedantic

all: main

main: hashtable.o list.o main.o
	gcc $(CFLAGS) main.o list.o hashtable.o -o main

hashtable.o: hashtable.c hashtable.h
	gcc $(CFLAGS) -c hashtable.c

list.o: list.h hashtable.h
	gcc $(CFLAGS) -c list.c

main.o: main.c hashtable.h scoreboard.h
	gcc $(CFLAGS) -c main.c

clean:
	del /f /q main.o list.o hashtable.o mine 2>nul || true
