/*
 *	Keyboard Input
 *	Copyright
 *		(C) 2020 Onyx
 *
 *	This file is part of OOE (Onyx`s Own Editor)
 *
 */

#ifndef _OOE_KBD_H_
#define _OOE_KBD_H_

#include "s.h"

enum editorKeys
{
    KEY_BACKSPACE = 0x7F,
    ESC_KEY = 0x1B,
    ARROW_LEFT = 1000,
    ARROW_RIGHT,
    ARROW_UP,
    ARROW_DOWN,
    DEL_KEY,
    HOME_KEY,
    END_KEY,
    PAGE_UP,
    PAGE_DOWN
};

/*
* Move the screen cursor
*/
void scrn_move_cursor(struct SCRN*, int);

/*
* Process kbd pressed keys relative to editor
*/
void editor_kbd_proc_key(struct SCRN*);

#endif