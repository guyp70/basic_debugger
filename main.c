#include <curses.h>
#include "main_menu.h"

int ATTACHED_PROCESSES[256] = {EMPTY_PID_CELL_MARKER};

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
