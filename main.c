/*
 *	Main File
 *	Copyright
 *		(C) 2020 Onyx
 *
 *	This file is part of OOE (Onyx`s Own Editor)
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "tty.h"
#include "kbd.h"
//#include "defs.h"

#include <signal.h>

Scrn* scrn_clean_ptr = NULL;

void scrn_clean_exit()
{
    if (scrn_clean_ptr != NULL)
        scrn_free(scrn_clean_ptr);
}

int main()
{
    terminal_enable_raw_mode();
    Scrn scrn = scrn_empty();
    scrn_clean_ptr = &scrn;
    atexit(scrn_clean_exit);

    terminal_get_window_size(&scrn.scrn_ws.ws_row, &scrn.scrn_ws.ws_col);

    wins_append_win(&scrn.wins, scrn.scrn_ws.ws_row, scrn.scrn_ws.ws_col, 0, 0, 0, 0, HORIZONTAL_WINDOW);
//    wins_append_win(&scrn.wins, scrn.scrn_ws.ws_row / 2, scrn.scrn_ws.ws_col / 2, 0, 0, 0, 0, HORIZONTAL_WINDOW);
//    wins_append_win(&scrn.wins, scrn.scrn_ws.ws_row / 2, round_whole((float)scrn.scrn_ws.ws_col / 2), 0, (int)(scrn.scrn_ws.ws_col / 2), 0, 0, VERTICAL_WINDOW);
//    wins_append_win(&scrn.wins, scrn.scrn_ws.ws_row / 2, scrn.scrn_ws.ws_col / 2, scrn.scrn_ws.ws_row / 2, 0, 0, 0, HORIZONTAL_WINDOW);
//    wins_append_win(&scrn.wins, round_whole((float)scrn.scrn_ws.ws_row / 2), round_whole((float)scrn.scrn_ws.ws_col / 2), (int)(scrn.scrn_ws.ws_row / 2), (int)(scrn.scrn_ws.ws_col / 2), 0, 0, VERTICAL_WINDOW);

    while (1)
    {
        scrn_update(&scrn);
        editor_kbd_proc_key(&scrn);
    }

    return 0;
}