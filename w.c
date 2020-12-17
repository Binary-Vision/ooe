/*
 *	Window Management
 *	Copyright
 *		(C) 2020 Onyx
 *
 *	This file is part of OOE (Onyx`s Own Editor)
 *
 */

#include "types.h"

Win empty_win()
{
    Win win;

    win.ws.ws_row = win.ws.ws_col = 0;
    win.cursor_coord.x = win.cursor_coord.y = 0;
    win.window_coord.x = win.window_coord.y = 0;

    return win;
}

Win create_win(int height, int width, int row, int col, int cursor_y, int cursor_x)
{
    Win win;

    win.ws.ws_row = height;
    win.ws.ws_col = width;
    win.window_coord.y = row;
    win.window_coord.x = col;
    win.cursor_coord.y = cursor_y;
    win.cursor_coord.x = cursor_x;

    return win;
}