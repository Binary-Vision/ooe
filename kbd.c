#include "kbd.h"

#undef _OOE_SCRN_H_

#include "types.h"
#include "tty.h"
#include "ws.h"

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define CTRL_KEY(k)	((k) & 0x1F)

static int kbd_read_key() {
  int nread;
  char c;
  while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
    if (nread == -1 && errno != EAGAIN) return -1;
  }
  if (c == '\x1b') {
    char seq[3];
    if (read(STDIN_FILENO, &seq[0], 1) != 1) return '\x1b';
    if (read(STDIN_FILENO, &seq[1], 1) != 1) return '\x1b';
    if (seq[0] == '[') {
      if (seq[1] >= '0' && seq[1] <= '9') {
        if (read(STDIN_FILENO, &seq[2], 1) != 1) return '\x1b';
        if (seq[2] == '~') {
          switch (seq[1]) {
            case '1': return HOME_KEY;
            case '3': return DEL_KEY;
            case '4': return END_KEY;
            case '5': return PAGE_UP;
            case '6': return PAGE_DOWN;
            case '7': return HOME_KEY;
            case '8': return END_KEY;
          }
        }
      } else {
        switch (seq[1]) {
          case 'A': return ARROW_UP;
          case 'B': return ARROW_DOWN;
          case 'C': return ARROW_RIGHT;
          case 'D': return ARROW_LEFT;
          case 'H': return HOME_KEY;
          case 'F': return END_KEY;
        }
      }
    } else if (seq[0] == 'O') {
      switch (seq[1]) {
        case 'H': return HOME_KEY;
        case 'F': return END_KEY;
      }
    }
    return '\x1b';
  } else {
    return c;
  }
}

void scrn_move_cursor(Scrn* scrn_ptr, int key)
{
    switch (key)
    {
    case ARROW_UP:
        if (scrn_ptr->cursor_coord.y != 0)
            scrn_ptr->cursor_coord.y--;
        break;
    case ARROW_DOWN:
        if (scrn_ptr->cursor_coord.y != scrn_ptr->scrn_ws.ws_row - 1)
            scrn_ptr->cursor_coord.y++;
        break;
    case ARROW_LEFT:
        if (scrn_ptr->cursor_coord.x != 0)
            scrn_ptr->cursor_coord.x--;
        break;
    case ARROW_RIGHT:
        if (scrn_ptr->cursor_coord.x != scrn_ptr->scrn_ws.ws_col - 1)
            scrn_ptr->cursor_coord.x++;
        break;
    }
}

void editor_kbd_proc_key(Scrn* scrn_ptr)
{
    int key = kbd_read_key();
    int x = 0, y = 0;
    char buf[300];	int size;

    switch (key)
    {
    case CTRL_KEY('Q'):
        exit(0);
    case CTRL_KEY('T'):
        wsplt_hz(&scrn_ptr->wins, scrn_ptr->cursor_coord.x, scrn_ptr->cursor_coord.y);
        break;
    case CTRL_KEY('O'):
        terminal_get_cursor_position(&y, &x);
        size = snprintf(buf, sizeof(buf), "\x1b[2;2HY %d;X %d    Scrn Y : %d;  Scrn X: %d\x1b[K", y, x, scrn_ptr->cursor_coord.y, scrn_ptr->cursor_coord.x);
        write(STDOUT_FILENO, buf, size);
        size = snprintf(buf, sizeof(buf), "\x1b[3;2HScreen Windows: %ld\x1b[K\x1b[4;2HWindow 1 x:%d \x1b[5;2Hwindow 1 y: %d\x1b[K\x1b[6;2HWindow 1 Width: %d\x1b[K\x1b[7;2HWindow 1 Height: %d\x1b[K\x1b[8;2Hwindow 2 x:%d \x1b[9;2Hwindow 2 y:%d\x1b[K\x1b[10;2HWindow 2 Width: %d\x1b[K\x1b[11;2HWindow 2 Height: %d\x1b[K", scrn_ptr->wins.wins_size,
                                            scrn_ptr->wins.wins[0].window_coord.x + 1,
                                            scrn_ptr->wins.wins[0].window_coord.y + 1,
                                            scrn_ptr->wins.wins[0].ws.ws_col,
                                            scrn_ptr->wins.wins[0].ws.ws_row,
                                            scrn_ptr->wins.wins[1].window_coord.x + 1,
                                            scrn_ptr->wins.wins[1].window_coord.y + 1,
                                            scrn_ptr->wins.wins[1].ws.ws_col,
                                            scrn_ptr->wins.wins[1].ws.ws_row);
        write(STDOUT_FILENO, buf, size);
        int winIndex = retIWin_scrnCursor(&scrn_ptr->wins, y, x);
        size = snprintf(buf, sizeof(buf), "\x1b[12;2HIndex: %d\x1b[K", winIndex);
        write(STDOUT_FILENO, buf, size);
        break;

    case ARROW_UP:
    case ARROW_DOWN:
    case ARROW_LEFT:
    case ARROW_RIGHT:
        scrn_move_cursor(scrn_ptr, key);
    }
}