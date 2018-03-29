#include "input.h"
int input_offset(char input)
{
	int digit=input-'0';
	if (0<digit&&digit<10) {
		// Numpad input handling
		digit--;
		return lin(digit%3-1,1-digit/3);
	}
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
	case 'R':
		clear_screen();
		clear_announcements();
		draw_local_area();
		announce_stats(player);
		return input_offset(fgetc(stdin));
	default:
		return 0;
	}
}
char generate_input()
{
	return rand()%10+'0';
}
