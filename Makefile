CC=clang
CFLAGS=-g

game: game.c src/*
	ls src/*.h | sed -n 's/.*\.h/#include \"&\"/p' > game.h
	$(CC) game.c src/*.c $(CFLAGS); rm game.h
