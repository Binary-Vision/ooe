/*
 *	Error Handling
 *	Copyright
 *		(C) 2020 Onyx
 *
 *	This file is part of OOE (Onyx`s Own Editor)
 *
 */

#ifndef _OOE_ERR_H_
#define _OOE_ERR_H_

#include <stdio.h>

void error(const char* error_msg)
{
    perror(error_msg);
}

#endif