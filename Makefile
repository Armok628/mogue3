CC=clang
CFLAGS=-lm -g -pedantic
ADD-ONS=

game: game.c src/*
	perl header_gen $(ADD-ONS)
	$(CC) game.c src/*.c $(ADD-ONS) $(CFLAGS)
	rm src/creatures.h src/spawn.c src/items.h
