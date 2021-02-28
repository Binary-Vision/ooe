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
        if (cursor_x >= wins_ptr->wins[i].window_coord.x + 1
         && cursor_y >= wins_ptr->wins[i].window_coord.y + 1
         && cursor_x <= wins_ptr->wins[i].window_coord.x + wins_ptr->wins[i].ws.ws_col
         && cursor_y <= wins_ptr->wins[i].window_coord.y + wins_ptr->wins[i].ws.ws_row)
        {
            winIndex = i;
            break;
        }
    }

    return winIndex;
}

void wsplit_vertical(Wins* wins_ptr, const int cursor_y, const int cursor_x)
{
    // Get window width and halve it. Then insert a window after that windows position half of its surface width
    int winIndex = retIWin_scrnCursor(wins_ptr, cursor_y, cursor_x);

    if ((int)(wins_ptr->wins[winIndex].ws.ws_col / 2) < WIN_MIN_COLS && round_whole((float)wins_ptr->wins[winIndex].ws.ws_col / 2) < WIN_MIN_COLS) {
        ;
    } else {
        Win win;
        win.ws.ws_row = wins_ptr->wins[winIndex].ws.ws_row;
        win.ws.ws_col = round_whole((float)wins_ptr->wins[winIndex].ws.ws_col / 2);
        win.split_type = VERTICAL_WINDOW;
        win.window_coord.y = wins_ptr->wins[winIndex].window_coord.y;
        win.window_coord.x = (wins_ptr->wins[winIndex].ws.ws_col / 2) + wins_ptr->wins[winIndex].window_coord.x;
        wins_append_sWin(wins_ptr, win);
        wins_ptr->wins[winIndex].ws.ws_col /= 2;
    }
}

void wsplit_horizontal(Wins* wins_ptr, const int cursor_y, const int cursor_x)
{
    int winIndex = retIWin_scrnCursor(wins_ptr, cursor_y, cursor_x);
    if ((int)(wins_ptr->wins[winIndex].ws.ws_row / 2) < WIN_MIN_ROWS && round_whole((float)wins_ptr->wins[winIndex].ws.ws_row / 2) < WIN_MIN_ROWS) {
        ;
    } else {
        Win win;
        win.ws.ws_row = round_whole((float)wins_ptr->wins[winIndex].ws.ws_row / 2);
        win.ws.ws_col = wins_ptr->wins[winIndex].ws.ws_col;
        win.split_type = HORIZONTAL_WINDOW;
        win.window_coord.y = wins_ptr->wins[winIndex].window_coord.y + (wins_ptr->wins[winIndex].ws.ws_row / 2);
        win.window_coord.x = wins_ptr->wins[winIndex].window_coord.x;

        wins_ptr->wins[winIndex].ws.ws_row /= 2;
        wins_append_sWin(wins_ptr, win);
    }
}