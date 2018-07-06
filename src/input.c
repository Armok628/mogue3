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
char offset_input(int offset)
{
	switch (offset) {
	case WIDTH-1:
		return '1';
	case WIDTH:
		return '2';
	case WIDTH+1:
		return '3';
	case -1:
		return '4';
	case 1:
		return '6';
	case -WIDTH-1:
		return '7';
	case -WIDTH:
		return '8';
	case -WIDTH+1:
		return '9';
	}
	return '5';
}
char generate_input()
{
	return '0'+rand()%10;
}
