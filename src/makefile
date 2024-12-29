CFLAGS = -Wall --pedantic

all: mine

mine: hashtable.o scoreboard.o main.o
	gcc $(CFLAGS) main.o scoreboard.o hashtable.o -o mine

hashtable.o: hashtable.c hashtable.h
	gcc $(CFLAGS) -c hashtable.c

scoreboard.o: scoreboard.c scoreboard.h hashtable.h
	gcc $(CFLAGS) -c scoreboard.c

main.o: main.c hashtable.h scoreboard.h
	gcc $(CFLAGS) -c main.c

clean:
	del /f /q main.o scoreboard.o hashtable.o mine 2>nul || true
