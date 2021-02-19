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
        if (cursor_x >= wins_ptr->wins[i].window_coord.x + 1 && cursor_x <= wins_ptr->wins[i].window_coord.x + wins_ptr->wins[i].ws.ws_col)
            if (cursor_y >= wins_ptr->wins[i].window_coord.y + 1 && cursor_y <= wins_ptr->wins[i].window_coord.y + wins_ptr->wins[i].ws.ws_row)
                winIndex = i;
    }

    return winIndex;
}

void wsplit_vertical()
{
    // Get window width and halve it. Then insert a window after that windows position half of its surface width
}

void wsplit_horizontal(Wins* wins_ptr, const int cursor_y, const int cursor_x)
{
    int winIndex = retIWin_scrnCursor(wins_ptr, cursor_y, cursor_x);
/*    // Create new window that is half the rows of winIndex
    Win win = create_win((int)round_whole((float)(wins_ptr->wins[winIndex].ws.ws_row / 2)), wins_ptr->wins[winIndex].ws.ws_col,  wins_ptr->wins[winIndex].window_coord.y + (int)round_whole((float)(wins_ptr->wins[winIndex].window_coord.y / 2)), wins_ptr->wins[winIndex].window_coord.x, 0, 0, HORIZONTAL_WINDOW);

    wins_ptr->wins[winIndex].ws.ws_row /= 2;
    wins_append_sWin(wins_ptr, win);
    wins_ptr->wins[wins_ptr->wins_size - 1].split_type = HORIZONTAL_WINDOW;*/
    wins_ptr->wins[winIndex].ws.ws_row /= 2;
}