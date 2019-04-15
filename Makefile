CC = gcc
CFLAGS = -Wall -std=gnu99

build: main.o functions.o
	$(CC) $^ $(CFLAGS) -o 2048 -lncurses

main.o: main.c
	$(CC) $^ $(CFLAGS) -c

functions.o: functions.c
	$(CC) $^ $(CFLAGS) -c

run: 2048
	./2048

clean:
	rm -f main.o functions.o 2048
