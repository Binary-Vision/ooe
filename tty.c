/*
 *	TTY Management
 *	Copyright
 *		(C) 2020 Onyx
 *
 *	This file is part of OOE (Onyx`s Own Editor)
 *
 */

#include "tty.h"

#include <unistd.h>
#include <stdlib.h>

int terminal_disable_raw_mode()
{
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &term_ios) == -1)	return -1;
}

static void editor_at_exit()
{
    terminal_disable_raw_mode();
}

int terminal_enable_raw_mode()
{
    if (tcgetattr(STDIN_FILENO, &term_ios) == -1) return -1;;
    atexit(editor_at_exit);
    struct termios raw = orig_termios;
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) return -1;
    return 0;
}