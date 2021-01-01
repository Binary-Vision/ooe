/*
 *	Screen Manangement
 *	Copyright
 *		(C) 2020 Onyx
 *
 *	This file is part of OOE (Onyx`s Own Editor)
 *
 */

#ifndef _OOE_S_H_
#define _OOE_S_H_

#include "w.h"
#include "defs.h"

#include <stddef.h>

struct SCRN
{
    struct WINS		wins;		// Screen windows
    struct WIN_WS	scrn_ws;	// Screen size
    struct COORD	cursor_coord;	// Screen cursor position
};

/*
* Create an empty screen
*/
struct SCRN scrn_empty();

/*
* Free a screen
*/
void scrn_free(struct SCRN*);

/*
* Clean screen atexit
*/
void scrn_clean();

/*
* Update scrn
*/
void scrn_update(struct SCRN*);

#endif