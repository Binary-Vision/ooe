#include "types.h"

#define SAFE_ALLOC_ADDITIONAL	33

#include <stdlib.h>
#include <memory.h>

Vbuf vbuf_init()
{
    Vbuf vbuf;

    vbuf.data = malloc(SAFE_ALLOC_ADDITIONAL);
    vbuf.size = 0;
    vbuf.cap = SAFE_ALLOC_ADDITIONAL;

    return vbuf;
}

static void vbuf_Realloc(Vbuf* vbuf_ptr, size_t new_Capacity)
{
    char* data = malloc(new_Capacity);
    if (new_Capacity < vbuf_ptr->size)	vbuf_ptr->size = new_Capacity;

    memcpy(data, vbuf_ptr->data, vbuf_ptr->size);
    free(vbuf_ptr->data);

    vbuf_ptr->data = data;
    vbuf_ptr->cap = new_Capacity;
    free(data);
}

void vbuf_append(Vbuf* vbuf_ptr, const char* data, const size_t data_size)
{
    if (vbuf_ptr->size + data_size >= vbuf_ptr->cap)	vbuf_Realloc(vbuf_ptr, vbuf_ptr->size + data_size + SAFE_ALLOC_ADDITIONAL);

    memcpy(&vbuf_ptr->data[vbuf_ptr->size], data, data_size);
    vbuf_ptr->size += data_size;
}

void vbuf_free(Vbuf* vbuf_ptr)
{
    free(vbuf_ptr->data);
    vbuf_ptr->size = 0;
    vbuf_ptr->cap = 0;
}