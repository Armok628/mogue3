#include "input.h"
int input_offset(char input)
{
	switch (input) {
	case '4':
	case 'h':
		return -1;
	case '2':
	case 'j':
		return WIDTH;
	case '8':
	case 'k':
		return -WIDTH;
	case '6':
	case 'l':
		return 1;
	case '7':
	case 'y':
		return -1-WIDTH;
	case '9':
	case 'u':
		return 1-WIDTH;
	case '1':
	case 'b':
		return -1+WIDTH;
	case '3':
	case 'n':
		return 1+WIDTH;
	default:
		return 0;
	}
}
char generate_input()
{
	static char moves[]="0123456789m";
	static int n_moves=11;
	return moves[rand()%n_moves];
}
