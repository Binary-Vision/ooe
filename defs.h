/*
 *	Definitions
 *	Copyright
 *		(C) 2020 Onyx
 *
 *	This file is part of OOE (Onyx`s Own Editor)
 *
 *	Many files part of the source code of the editor may need to use multiple structures and implementable functions.
 *	Best to keep it in one file header file to avoid recursive inclusion.
 */

#ifndef _OOE_DEFS_H_
#define _OOE_DEFS_H_
 
struct COORD
{
    int x;
    int y;
};

/*
* Simple 1dp rounding function
*/
int round_whole(const float);

#endif