/*
 *	Screen Manangement
 *	Copyright
 *		(C) 2020 Onyx
 *
 *	This file is part of OOE (Onyx`s Own Editor)
 *
 */

#include "types.h"

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <stddef.h>
#include <unistd.h>

Scrn scrn_empty()
{
    Scrn scrn;

    scrn.scrn_ws.ws_row = scrn.scrn_ws.ws_col = 0;
    scrn.cursor_coord.x = scrn.cursor_coord.y = 0;

    return scrn;
}

void scrn_free(Scrn* scrn_ptr)
{
}