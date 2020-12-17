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
    struct WIN*		wins		// Amount of screen windows
    size_t		wins_size;	// Amount of screen windows
    struct WIN_WS	scrn_ws;	// Screen size
    struct COORD	cursor_coord;	// Screen cursor position
};

#endif