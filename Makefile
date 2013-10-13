.SUFFIXES:
	.SUFFIXES: .c .cpp .o

CFLAGS=-Wall -g
LDFLAGS=-llua -ldl -lsfml-system -lsfml-graphics -lsfml-window

all: main

main: TileMap.o debug.o

clean:
	rm -f bin/*
	rm -f build/*
