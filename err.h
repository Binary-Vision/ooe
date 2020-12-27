/*
 *	Error Handling
 *	Copyright
 *		(C) 2020 Onyx
 *
 *	This file is part of OOE (Onyx`s Own Editor)
 *
 */

#include <stdio.h>

void error(const char* error_msg)
{
    perror(error_msg);
}