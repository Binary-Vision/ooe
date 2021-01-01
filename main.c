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
#include "defs.h"

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
    atexit(scrn_clean_exit);

    terminal_get_window_size(&scrn.scrn_ws.ws_row, &scrn.scrn_ws.ws_col);

    wins_append_empty_win(&scrn.wins);
    wins_append_empty_win(&scrn.wins);

    scrn.wins.wins[0].window_coord.y = 0;
    scrn.wins.wins[0].window_coord.x = 0;
    scrn.wins.wins[0].ws.ws_col = scrn.scrn_ws.ws_col / 2;

    scrn.wins.wins[1].window_coord.y = 0;
    scrn.wins.wins[1].window_coord.x = (scrn.scrn_ws.ws_col / 2);
    scrn.wins.wins[1].ws.ws_col = round_whole((float)scrn.scrn_ws.ws_col / 2.0f);

//    printf("%d;%d;%d\r\n", scrn.scrn_ws.ws_col, scrn.wins.wins[0].ws.ws_col, scrn.wins.wins[1].ws.ws_col);

    while (1)
    {
        scrn_update(&scrn);
        editor_kbd_proc_key();
    }    

    return 0;
}