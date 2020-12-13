/*
 *	Window Management
 *	Copyright
 *		(C) 2020 Onyx
 *
 *	This file is part of OOE (Onyx`s Own Editor)
 *
 */

#ifndef _OOE_W_H_
#define _OOE_W_H_

#include "defs.h"

struct WIN_WS
{
    int ws_row;
    int ws_col;
};

struct WIN
{
    struct WIN_WS	ws;		// Window Size
    struct COORD	cursor_coord;	// Cursor position
    struct COORD	window_coord;	// Window position
};

struct WIN empty_win();

#endif