#include "make_menu.h"


void make_menu(MenuChoice choices[], size_t n_choices)
{	ITEM **my_items;
	int c;				
	MENU *my_menu;
	size_t i;
	//ITEM *cur_item;

	
	my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));

	for(i = 0; i < n_choices; ++i)
	        my_items[i] = new_item(choices[i].name, choices[i].description);
	my_items[n_choices] = (ITEM *)NULL;

	my_menu = new_menu((ITEM **)my_items);
	mvprintw(LINES - 2, 0, "Q to Exit");
	post_menu(my_menu);
	refresh();

	while((c = getch()) != 'q' && c != 'Q')
	{   
		switch(c)
	    {	case KEY_DOWN:
		        menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
			case ENTER_KEY_VALUE:  //curses' KEY_ENTER reffers to numpad ENTER key.
				unpost_menu(my_menu);
				refresh();
				(*(choices[current_item(my_menu)->index].action_func))();
				clear();
				post_menu(my_menu);
				refresh();
				break;	
		}
	}	

	free_item(my_items[0]);
	free_item(my_items[1]);
	free_menu(my_menu);
}