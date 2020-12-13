/*
 *	Main File
 *	Copyright
 *		(C) 2020 Onyx
 *
 *	This file is part of OOE (Onyx`s Own Editor)
 *
 */

#include <stdio.h>

#include "types.h"

int main()
{
    Vbuf vbuf = vbuf_init();
    vbuf_append(&vbuf, "hello", 5);
    printf("%s\r\n%d\r\n%d\r\n", vbuf.data, vbuf.size, vbuf.cap);
    vbuf_free(&vbuf);
    return 0;
}