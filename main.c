/*
 *	Main File
 *	Copyright
 *		(C) 2020 Onyx
 *
 *	This file is part of OOE (Onyx`s Own Editor)
 *
 */

#include <stdio.h>

#include "types.h"
#include "tty.h"
#include <unistd.h>

int roundt(float f)
{
    int round = (int)f;
    if (f - (float)round >= 0.5)	round = (int)f + 1;
    return round;
}

int main()
{
    terminal_enable_raw_mode();
    Scrn scrn = scrn_empty();
    terminal_get_window_size(&scrn.scrn_ws.ws_row, &scrn.scrn_ws.ws_col);

    wins_append_empty_win(&scrn.wins);
    scrn.wins.wins[0].window_coord.y = 20;
    scrn.wins.wins[0].window_coord.x = 0;
    scrn.wins.wins[0].ws.ws_col = scrn.scrn_ws.ws_col / 2;;
    
    scrn_update(&scrn);
    sleep(3);

    scrn_free(&scrn);

    return 0;
}