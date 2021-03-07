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
#include "ws.h"

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

static void scrn_draw_win(Win win, Vbuf* vbuf_ptr)
{
    char buffer[300];	int size = 0;
    memset(buffer, 0, sizeof(buffer));

    // Set terminal cursor to window position
    size = snprintf(buffer, sizeof(buffer), "\x1b[%d;%dH", win.window_coord.y + 1, win.window_coord.x + 1);
    vbuf_append(vbuf_ptr, buffer, size);

    // Draw window status bar
    if (win.split_type == HORIZONTAL_WINDOW || win.split_type == VERTICAL_WINDOW)
    {
        vbuf_append(vbuf_ptr, "\x1b[7m", 4);

        // Draw window status bar message
        //size = snprintf(buffer, sizeof(buffer), "Height: %d, Width: %d, X: %d, Y: %d", win.ws.ws_row, win.ws.ws_col, win.window_coord.x, win.window_coord.y);
        //vbuf_append(vbuf_ptr, buffer, size);
        char buf[15];	int size = snprintf(buf, sizeof(buf), "X: %d, Y: %d", win.cursor_coord.x, win.cursor_coord.y);
        vbuf_append(vbuf_ptr, buf, size);
        for (int i = 0; i < win.ws.ws_col - size; i++)
            vbuf_append(vbuf_ptr, " ", 1);
        vbuf_append(vbuf_ptr, "\x1b[m", 3);
    
        if (win.split_type == VERTICAL_WINDOW)
        {
            size = snprintf(buffer, sizeof(buffer), "\x1b[%d;%dH", win.window_coord.y + 1, win.window_coord.x + 1);
            vbuf_append(vbuf_ptr, buffer, size);

            // Draw vertical bar
            vbuf_append(vbuf_ptr, "\x1b[7m", 4);
            for (int i = 1; i < win.ws.ws_row; i++)
            {
                size = snprintf(buffer, sizeof(buffer), "\x1b[%d;%dH ", win.window_coord.y + (1 + i), win.window_coord.x + 1);
                vbuf_append(vbuf_ptr, buffer, size);
            }
            vbuf_append(vbuf_ptr, "\x1b[m", 3);
        }
    }
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
        scrn_draw_win(scrn_ptr->wins.wins[i], &vbuf);
    scrn_clear_lines(scrn_ptr, &vbuf);

    // Position screen cursor
    display_WinCursor(&vbuf, scrn_ptr->wins.wins[0].window_coord, scrn_ptr->wins.wins[0].cursor_coord, scrn_ptr->cursor_coord);

    // Show terminal cursor
    vbuf_append(&vbuf, "\x1b[?25h", 6);

    // Write buffer to terminal screen
    write(STDOUT_FILENO, vbuf.data, vbuf.size);

    vbuf_free(&vbuf);
}