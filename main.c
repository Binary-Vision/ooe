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
    Wins wins = wins_init();
    wins_append_empty_win(&wins);
    wins_append_empty_win(&wins);

    wins.wins[0].ws.ws_row = 20;
    wins.wins[0].ws.ws_col = 20;

    wins.wins[0].ws.ws_row = 20;
    wins.wins[0].ws.ws_col = 20;

    printf("%ld;%ld;%d;%d\r\n", wins.wins_cap, wins.wins_size, wins.wins[0].ws.ws_row, wins.wins[0].ws.ws_col);

    wins_free(&wins);
    return 0;
}