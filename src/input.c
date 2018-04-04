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
	// Temporary (?) input handling
	case 'a':
		action_menu();
		return 0;
	case 'R':
		clear_screen();
		clear_announcements();
		draw_local_area();
		announce_stats(player);
		return input_offset(fgetc(stdin));
	case 'D':
		debug_menu();
		return 0;
	case 'm':
		spell_menu(player);
		return 0;
	case 'q':
		quit();
	default:
		return 0;
	}
}
char generate_input()
{
	return rand()%10+'0';
}
