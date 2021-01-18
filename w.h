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

#include <stdbool.h>
#include <stddef.h>

#define VERTICAL_WINDOW		0
#define HORIZONTAL_WINDOW	1
#define VERTICAL_BAR_WINDOW	3

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

    int			split_type;	// Vertical or horizontal window
};

struct WINS
{
    struct WIN*		wins;           // Windows
    size_t              wins_size;      // Amount of screen windows
    size_t              wins_cap;       // Capacity of windows
};

/*** Win Routines ***/

/*
* Create an empty window
*/
struct WIN empty_win();

/*
* Create a window with values
*/
struct WIN create_win(int, int, int, int, int, int);

/*** Wins Routines ***/
/*
* Initialize a Wins instance
*/
struct WINS wins_init();

/*
* Append an empty Win to Wins
*/
void wins_append_empty_win(struct WINS*);

/*
* Append a Win to Wins
*/
void wins_append_win(struct WINS*, int, int, int, int, int, int);

/*
* Free Wins
*/
void wins_free(struct WINS* wins);

#endif