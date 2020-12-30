/*
 *	Screen Manangement
 *	Copyright
 *		(C) 2020 Onyx
 *
 *	This file is part of OOE (Onyx`s Own Editor)
 *
 */

#include "types.h"

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <stddef.h>
#include <unistd.h>

Scrn scrn_empty()
{
    Scrn scrn;

    scrn.wins = wins_init();
    scrn.scrn_ws.ws_row = scrn.scrn_ws.ws_col = 0;
    scrn.cursor_coord.x = scrn.cursor_coord.y = 0;

    return scrn;
}

void scrn_free(Scrn* scrn_ptr)
{
    wins_free(&scrn_ptr->wins);
    scrn_ptr->scrn_ws.ws_row = scrn_ptr->scrn_ws.ws_col = 0;
    scrn_ptr->cursor_coord.x = scrn_ptr->cursor_coord.y = 0;
}

static void scrn_draw_win(Win win, Vbuf* vbuf_ptr)
{
    // Set cursor positon to window position
    char window_pos_buffer[10];	int size = snprintf(window_pos_buffer, sizeof(window_pos_buffer), "\x1b[%d;%dH", win.window_coord.y + 1, win.window_coord.x + 1);
    vbuf_append(vbuf_ptr, window_pos_buffer, size);

    // Draw window status bar
    vbuf_append(vbuf_ptr, "\x1b[7m", 4);
    for (int i = 0; i < win.ws.ws_col; i++)
        vbuf_append(vbuf_ptr, " ", 1);
    vbuf_append(vbuf_ptr, "\x1b[m", 3);
}

void scrn_update(Scrn* scrn)
{
    Vbuf vbuf = vbuf_init();

    // Hide terminal cursor
    vbuf_append(&vbuf, "\x1b[?25l", 6);

    // Reset terminal cursor
    vbuf_append(&vbuf, "\x1b[H", 3);

    // Draw windows
    for (size_t i = 0; i < scrn->wins.wins_size; i++)
        scrn_draw_win(scrn->wins.wins[i], &vbuf);

    // Show terminal cursor
    vbuf_append(&vbuf, "\x1b[?25h", 6);
    write(STDOUT_FILENO, vbuf.data, vbuf.size);

    vbuf_free(&vbuf);
}