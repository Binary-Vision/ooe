#include "kbd.h"
#include "types.h"
#include "tty.h"
#include "ws.h"
#include "err.h"

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
//#include <stdio.h>

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
    char buf[300];	int size;
    int y = 0, x = 0;	int winIndex;

    switch (key)
    {
    case CTRL_KEY('Q'):
        exit(0);
    case CTRL_KEY('T'):
    case CTRL_KEY('O'):
        if (terminal_get_cursor_position(&y, &x) == -1)
            error("terminal_get_cursor_position");
        winIndex = retIWin_scrnCursor(&scrn_ptr->wins, y, x);
        size = snprintf(buf, sizeof(buf), "\x1b[2;1H%d", winIndex);
        write(STDOUT_FILENO, buf, size);
        break;

    case ARROW_UP:
    case ARROW_DOWN:
    case ARROW_LEFT:
    case ARROW_RIGHT:
        scrn_move_cursor(scrn_ptr, key);
    }
}