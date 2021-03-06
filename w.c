/*
 *	Window Management
 *	Copyright
 *		(C) 2020 Onyx
 *
 *	This file is part of OOE (Onyx`s Own Editor)
 *
 */

#include "types.h"

#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

#define WINS_SAFE_SIZE	3

Win empty_win()
{
    Win win;

    win.ws.ws_row = win.ws.ws_col = 0;
    win.cursor_coord.x = win.cursor_coord.y = 0;
    win.window_coord.x = win.window_coord.y = 0;
    win.split_type = UNASSIGNED;

    return win;
}

Win create_win(int height, int width, int row, int col, int cursor_y, int cursor_x, short split_type)
{
    Win win;

    win.ws.ws_row = height;
    win.ws.ws_col = width;
    win.window_coord.y = row;
    win.window_coord.x = col;
    win.cursor_coord.y = cursor_y;
    win.cursor_coord.x = cursor_x;
    win.split_type = split_type;

    return win;
}

Wins wins_init()
{
    Wins wins;

    wins.wins = malloc(sizeof(Win) * WINS_SAFE_SIZE);
    wins.wins_size = 0;
    wins.wins_cap = WINS_SAFE_SIZE;
    wins.winIndex = 0;

    return wins;
}

static void wins_Realloc(Wins* wins_ptr, size_t new_Capacity)
{
    Win* wins = malloc(sizeof(Win) * new_Capacity);
    if (new_Capacity < wins_ptr->wins_size)	wins_ptr->wins_size = new_Capacity;

    for (size_t i = 0; i < wins_ptr->wins_size; i++)
        wins[i] = wins_ptr->wins[i];
    free(wins_ptr->wins);

    wins_ptr->wins = wins;
    wins_ptr->wins_cap = new_Capacity;
}

void wins_append_empty_win(Wins* wins_ptr)
{
    if (wins_ptr->wins_size + 1 >= wins_ptr->wins_cap)	wins_Realloc(wins_ptr, wins_ptr->wins_size + ((wins_ptr->wins_size + 1) - wins_ptr->wins_cap) + WINS_SAFE_SIZE);

    wins_ptr->wins[wins_ptr->wins_size] = empty_win();
    wins_ptr->wins_size++;
}

void wins_append_win(Wins* wins_ptr, int height, int width, int row, int col, int cursor_y, int cursor_x, short split_type)
{
    wins_append_empty_win(wins_ptr);
    wins_ptr->wins[wins_ptr->wins_size - 1] = create_win(height, width, row, col, cursor_y, cursor_x, split_type);
}

void wins_append_sWin(Wins* wins_ptr, Win win)
{
    wins_append_empty_win(wins_ptr);
    wins_ptr->wins[wins_ptr->wins_size - 1] = win;
}

void wins_free(Wins* wins)
{
    free(wins->wins);
    wins->wins_size = 0;
    wins->wins_cap = 0;
}

void display_WinCursor(Vbuf* vbuf_ptr, Coord win_coord, Coord win_cursor_coord, Coord scrn_cursor_coord)
{
    scrn_cursor_coord.y = win_coord.y + win_cursor_coord.y;
    scrn_cursor_coord.x = win_coord.x + win_cursor_coord.x;

    char cursor_buf[10];
    int size = snprintf(cursor_buf, sizeof(cursor_buf), "\x1b[%d;%dH", scrn_cursor_coord.y + 1, scrn_cursor_coord.x + 1);
    vbuf_append(vbuf_ptr, cursor_buf, size);
}