#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdbool.h>

#define BUFFER_SIZE 4

typedef struct {
    int buffer[BUFFER_SIZE];
    int header; // read
    int tail;   // write
} ring_buffer_t;

ring_buffer_t *rb_init();

bool rb_is_full(ring_buffer_t *rb);

bool rb_is_empty(ring_buffer_t *rb);

bool rb_read(ring_buffer_t *rb, int *byte);

bool rb_write(ring_buffer_t *rb, int byte);

int rb_size(ring_buffer_t *rb);

#endif // RING_BUFFER_H