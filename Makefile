CC = gcc
CFLAGS = -std=c11 -Wall -Werror -I./src/includes/
BIN = ./bin/gb_emu

clean:
	rm $(BIN) ./bin/main.o ./bin/cpu.o ./bin/mbc.o ./bin/rom.o

build : main.o
	$(CC) $(CFLAGS) -o $(BIN) ./bin/main.o ./bin/cpu.o ./bin/mbc.o \
		./bin/rom.o ./bin/instructions.o

main.o: cpu.o mbc.o rom.o
	$(CC) $(CFLAGS) -o ./bin/main.o -c ./src/main.c

cpu.o: instructions.o
	$(CC) $(CFLAGS) -o ./bin/cpu.o -c ./src/cpu.c

instructions.o:
	$(CC) $(CFLAGS) -o ./bin/instructions.o -c ./src/instructions.c

mbc.o:
	$(CC) $(CFLAGS) -o ./bin/mbc.o -c ./src/mbc.c

rom.o:
	$(CC) $(CFLAGS) -o ./bin/rom.o -c ./src/rom.c
