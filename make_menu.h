#ifndef MAKE_MENU_H
#define MAKE_MENU_H

#include <curses.h>
#include <menu.h>
#include <stdlib.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(*a))
#define CTRLD 	4
typedef struct _MenuChoice
{
    char name[20];
    char description[256];
    void (*action_func)();
} MenuChoice;

void make_menu(MenuChoice choices[], size_t n_choices);

#endif // !MAKE_MENU_H
