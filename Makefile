.SUFFIXES:
.SUFFIXES: .c .cpp .o

CFLAGS=-Wall -g
CPPFLAGS=-Wall -g
LDFLAGS=-llua -ldl -lsfml-system -lsfml-graphics -lsfml-window

all: main

main: TileMap.o TileLayer.o debug.o

clean:
	rm -f *.o
