#include <stdio.h>
#include "debugger_menus.h"


MenuChoice main_menu_choices[] = {
                        {"attach", "attach to process", (void(*)()) NULL},
						{"dettach", "dettach from process", (void(*)()) NULL},
						{"debug", "debug attached process", (void(*)()) NULL},
						{"exit", "", (void(*)()) NULL}
                  };

MenuChoice process_menu_choices[] = {
                        {"attach", "attach to process", (void(*)()) NULL},
						{"exit", "", (void(*)()) NULL}
                  };


int main()
{
    make_menu(main_menu_choices, 4);
    return 0;
}
