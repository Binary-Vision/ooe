/*
 *	Window Splitting
 *	Copyright
 *		(C) 2020 Onyx
 *
 *	This file is part of OOE (Onyx`s Own Editor)
 *
 */

#include "types.h"
#include "ws.h"

int retIWin_scrnCursor(Wins* wins_ptr, const int cursor_y, const int cursor_x)
{
    int winIndex = -1;

    for (size_t i = 0; i < wins_ptr->wins_size; i++)
    {
        // Bounds Checking
        if (cursor_x >= wins_ptr->wins[i].window_coord.x + 1 && cursor_x <= wins_ptr->wins[i].window_coord.x + wins_ptr->wins[i].ws.ws_col && cursor_y >= wins_ptr->wins[i].window_coord.y + 1 && cursor_y < wins_ptr->wins[i].window_coord.y + wins_ptr->wins[i].ws.ws_col)
            winIndex = i;
    }

    return winIndex;
}

void wsplit_vertical()
{
    // Get window width and halve it. Then insert a window after that windows position half of its surface width
}

void wsplit_horizontal(Wins* wins_ptr, const int cursor_x, const int cursor_y)
{
    // Get window index
    int winIndex = retIWin_scrnCursor(wins_ptr, cursor_x, cursor_y);

    // Get window height, halve it and append a window at new positions.
    Win win = create_win((int)round_whole((float)(wins_ptr->wins[winIndex].ws.ws_row / 2)), wins_ptr->wins[winIndex].ws.ws_col, wins_ptr->wins[winIndex].window_coord.y + (int)round_whole((float)(wins_ptr->wins[winIndex].window_coord.y / 2)), wins_ptr->wins[winIndex].window_coord.x, 0, 0, HORIZONTAL_WINDOW);

    // Change winIndex width, height values
    wins_ptr->wins[winIndex].ws.ws_row /= 2;

    // Append new window to wins_ptr
    wins_append_win(wins_ptr, win.ws.ws_row, win.ws.ws_col, win.window_coord.y, win.window_coord.x, win.cursor_coord.y, win.cursor_coord.x, win.split_type);
}