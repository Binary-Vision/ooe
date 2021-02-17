#include "err.h"
#include <stdio.h>

void error(const char* error_msg)
{
    perror(error_msg);
}