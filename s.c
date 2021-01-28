/*
 *	Screen Manangement
 *	Copyright
 *		(C) 2020 Onyx
 *
 *	This file is part of OOE (Onyx`s Own Editor)
 *
 */

#include "types.h"
#include "tty.h"

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

static void scrn_clear_lines(Scrn* scrn_ptr, Vbuf* vbuf_ptr)
{
    for (int y = 0; y <= scrn_ptr->scrn_ws.ws_col; y++)
    {
        char buf[13];	int size = snprintf(buf, sizeof(buf), "\x1b[%d;%dH\x1b[K", scrn_ptr->scrn_ws.ws_row + 1, scrn_ptr->scrn_ws.ws_col + 1);
        vbuf_append(vbuf_ptr, buf, size);
    }
}

static void scrn_draw_win(Win win, Vbuf* vbuf_ptr, bool vertical_bar)
{
    // Set cursor positon to window position
    char window_pos_buffer[10];	int size = snprintf(window_pos_buffer, sizeof(window_pos_buffer), "\x1b[%d;%dH", win.window_coord.y + 1, win.window_coord.x + 1);
    vbuf_append(vbuf_ptr, window_pos_buffer, size);

    // Draw window status bar
    vbuf_append(vbuf_ptr, "\x1b[7m", 4);
    for (int i = 0; i < win.ws.ws_col; i++)
        vbuf_append(vbuf_ptr, " ", 1);

    // Draw Window vertical bar if meets condition
    if (vertical_bar)
        for (int y = 1; y <= win.ws.ws_row; y++)
        {
            char buf[10];	int size = snprintf(buf, sizeof(buf), "\x1b[%d;%dH", y + 1, win.window_coord.x + 1);
            vbuf_append(vbuf_ptr, buf, size);
            vbuf_append(vbuf_ptr, " ", 1);
        }

    vbuf_append(vbuf_ptr, "\x1b[m", 3);
}

void scrn_update(Scrn* scrn_ptr)
{
    Vbuf vbuf = vbuf_init();

    // Hide terminal cursor
    vbuf_append(&vbuf, "\x1b[?25l", 6);

    // Reset terminal cursor
    vbuf_append(&vbuf, "\x1b[H", 3);

    // Draw windows
    for (size_t i = 0; i < scrn_ptr->wins.wins_size; i++)
        scrn_draw_win(scrn_ptr->wins.wins[i], &vbuf, scrn_ptr->wins.wins[i].split_type);
    scrn_clear_lines(scrn_ptr, &vbuf);

    // Position screen cursor
    char cursor_position_buf[10];
    int size = snprintf(cursor_position_buf, sizeof(cursor_position_buf), "\x1b[%d;%dH",
                                            scrn_ptr->cursor_coord.y + 1,
                                            scrn_ptr->cursor_coord.x + 1);
    vbuf_append(&vbuf, cursor_position_buf, size);

    // Show terminal cursor
    vbuf_append(&vbuf, "\x1b[?25h", 6);

    // Write buffer to terminal screen
    write(STDOUT_FILENO, vbuf.data, vbuf.size);

    vbuf_free(&vbuf);
}