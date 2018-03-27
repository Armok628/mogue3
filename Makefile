CC=clang
CFLAGS=-g

game: game.c src/*
	ls src/*.h | sed -n 's/.*\.h/#include \"&\"/p' > game.h
	$(CC) game.c src/*.c $(CFLAGS); rm game.h

world: worldtest.c src/world.* src/terminal.*
	$(CC) worldtest.c src/world.c src/terminal.c $(CFLAGS)
