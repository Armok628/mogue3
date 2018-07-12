CC=clang
CFLAGS=-lm -g -pedantic
ADD-ONS=

game: game.c src/*
	perl header_gen $(ADD-ONS)
	$(CC) game.c src/*.c $(ADD-ONS) $(CFLAGS)
	rm src/creatures.h src/spawnlist.c src/items.h

world: worldtest.c src/world.* src/terminal.*
	perl header_gen $(ADD-ONS)
	$(CC) worldtest.c src/world.c src/terminal.c $(CFLAGS)
	rm src/creatures.h src/spawnlist.c src/items.h
