/*
 *	TTY Management
 *	Copyright
 *		(C) 2020 Onyx
 *
 *	This file is part of OOE (Onyx`s Own Editor)
 *
 */

#ifndef _OOE_TTY_H_
#define _OOE_TTY_H_

#include <sys/termios.h>

struct termios term_ios;

/*
* Disable terminal raw mode
*/
int terminal_disable_raw_mode();

/*
* Enable terminal raw mode
*/
int terminal_enable_raw_mode();

/*
* Get terminal cursor position
*/
int terminal_get_cursor_position(int*, int*);

/*
* Get terminal window size
*/
int terminal_get_window_size(int*, int*);

#endif