#include "input.h"
FILE *replay=NULL;
FILE *record=NULL;
char get_input()
{
	if (!replay)
		replay=stdin;
	char c=fgetc(replay);
	if (feof(replay)) {
		fclose(replay);
		replay=stdin;
		draw_local_area();
		clear_announcements();
		announce_stats(player);
		c=fgetc(replay);
	}
	if (record&&c!='q')
		fputc(c,record);
	return c;
}
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
void chomp(char *s)
{
	for (;*s&&*s!='\n';s++);
	*s='\0';
}
char *string_prompt(char *prompt)
{
	announce("s",prompt);
	set_canon(true);
	set_cursor_visible(true);
	char *input=calloc(WIDTH,1);
	fgets(input,WIDTH,replay?replay:stdin);
	set_canon(false);
	set_cursor_visible(false);
	if (record)
		fputs(input,record);
	chomp(input);
	return input;
}
int int_prompt(char *prompt)
{
	announce("s",prompt);
	set_canon(true);
	set_cursor_visible(true);
	char in[12];
	fgets(in,12,replay?replay:stdin);
	set_canon(false);
	set_cursor_visible(false);
	if (record)
		fputs(in,record);
	return atoi(in);
}
