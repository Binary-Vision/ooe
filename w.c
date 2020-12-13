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
    win.window_coord.x = win.cursor_coord.y = 0;

    return win;
}