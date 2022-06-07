#include "main_menu.h"

int ATTACHED_PROCESSES[256] = {0};

int main()
{
	initscr();
	cbreak();
	//noecho();
	keypad(stdscr, TRUE);

    main_menu();

    endwin();
    return 0;
}
