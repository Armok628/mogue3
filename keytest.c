#include "src/terminal.h"
typedef enum {false,true} bool;
int main(int argc,char **argv)
{
	set_canon(false);
	set_cursor_visible(false);
	printf("EOF (^D) to quit.\n ");
	int l=cursor_pos(1,1000),x=l%1000,y=l/1000;
	for (;;) {
		char input=fgetc(stdin);
		move_cursor(x,y);
		clear_line();
		printf("%d",input);
		if (input==4)
			break;
	}
	set_canon(true);
	set_cursor_visible(true);
	putchar('\n');
	return 0;
}
