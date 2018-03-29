#include "input.h"
int input_offset(char input)
{
	int digit=input-'0';
	if (0<digit&&digit<10) {
		// Numpad input handling
		digit--;
		return lin(digit%3-1,1-digit/3);
	} else
		switch (input) {
		case 'h':
			return -1;
		case 'j':
			return WIDTH;
		case 'k':
			return -WIDTH;
		case 'l':
			return 1;
		case 'y':
			return -1-WIDTH;
		case 'u':
			return 1-WIDTH;
		case 'b':
			return -1+WIDTH;
		case 'n':
			return 1+WIDTH;
		default:
			return 0;
		}
}
char generate_input()
{
	return rand()%10+'0';
}
