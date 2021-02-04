/*
 *	Window Splitting
 *	Copyright
 *		(C) 2020 Onyx
 *
 *	This file is part of OOE (Onyx`s Own Editor)
 *
 */

#include "types.h"

int retIWin_scrnCursor(Wins* wins_ptr, const int cursor_y, const int cursor_x)
{
    int winIndex;

    for (size_t i = 0; i < wins_ptr->wins_size; i++)
    {
        // Bounds Checking   
        if (cursor_x >= wins_ptr->wins[i].window_coord.x + 1 &&
            cursor_x <= wins_ptr->wins[i].window_coord.x + wins_ptr->wins[i].ws.ws_col
            && cursor_y >= wins_ptr->wins[i].window_coord.y + 1 &&
            cursor_y <= wins_ptr->wins[i].window_coord.y + wins_ptr->wins[i].ws.ws_row)
            winIndex = i;
    }

    return winIndex;
}