/*
 *	Variable Buffer
 *	Copyright
 *		(C) 2020 Onyx
 *
 *	This file is part of OOE (Onyx`s Own Editor)
 *
 */

#ifndef _OOE_VB_H_
#define _OOE_VB_H_

#include <stddef.h>

struct VBUF
{
    char* data;
    size_t size;
    size_t cap;
};

struct VBUF vbuf_init();
void vbuf_append(struct VBUF*, const char*, const size_t);
void vbuf_free(struct VBUF*);

#endif