#ifndef MAKE_MENU_H
#define MAKE_MENU_H

#include <curses.h>
#include <menu.h>
#include <stdlib.h>
#include "utils.h"


#define CTRLD 	4
#define ENTER_KEY_VALUE '\n'
typedef struct _MenuChoice
{
    char name[20];
    char description[256];
    void (*action_func)();
} MenuChoice;

void make_menu(MenuChoice choices[], size_t n_choices);

#endif // !MAKE_MENU_H
