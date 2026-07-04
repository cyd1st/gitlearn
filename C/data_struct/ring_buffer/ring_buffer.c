#include "ring_buffer.h"
#include <stdbool.h>
#include <stdlib.h>

ring_buffer_t *rb_init()
{
    ring_buffer_t *rb = (ring_buffer_t *)malloc(sizeof(ring_buffer_t));
    rb->header = 0;
    rb->tail = 0;
    return rb;
}

bool rb_is_full(ring_buffer_t *rb) { return (rb->tail + 1 % BUFFER_SIZE == rb->header); }

bool rb_is_empty(ring_buffer_t *rb) { return rb->header == rb->tail; }

bool rb_read(ring_buffer_t *rb, int *byte)
{
    if (rb_is_empty(rb)) {
        return false;
    }

    *byte = rb->buffer[rb->header];
    rb->header = (rb->header + 1) % BUFFER_SIZE;
    return true;
}

bool rb_write(ring_buffer_t *rb, int byte)
{
    if (rb_is_full(rb)) {
        return false;
    }

    rb->buffer[rb->tail] = byte;
    rb->tail = (rb->tail + 1) % BUFFER_SIZE;
    return true;
}

int rb_size(ring_buffer_t *rb) { return (rb->tail - rb->header + BUFFER_SIZE) % BUFFER_SIZE; }