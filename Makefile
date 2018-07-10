CC=clang
CFLAGS=-lm -g -pedantic

game: game.c src/*
	perl gen_spawnlist
	$(CC) game.c src/*.c $(CFLAGS)
	rm src/creatures.h src/spawnlist.c

world: worldtest.c src/world.* src/terminal.*
	$(CC) worldtest.c src/world.c src/terminal.c $(CFLAGS)
