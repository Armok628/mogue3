CC=clang
CFLAGS=-lm -g -pedantic
ADD-ONS=

game: game.c src/*
	make headers
	$(CC) game.c src/*.c $(ADD-ONS) $(CFLAGS)
	make clean

headers:
	perl header_gen $(ADD-ONS)

clean:
	rm src/creatures.h src/spawn.c src/items.h

world: worldtest.c src/world.* src/terminal.*
	make headers
	$(CC) worldtest.c src/world.c src/terminal.c $(CFLAGS)
	make clean
