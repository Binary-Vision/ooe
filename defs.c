/*
 *	Definitions
 *	Copyright
 *		(C) 2020 Onyx
 *
 *	This file is part of OOE (Onyx`s Own Editor)
 *
 */

#include "types.h"

int round_whole(const float f)
{
    if (f - (float)((int)f) >= 0.5)	return (int)f + 1;
    else				return (int)f;
}