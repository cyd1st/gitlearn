#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "ring_buffer.h"

int main()
{
    ring_buffer_t *rb = rb_init();
    assert(true == rb_is_empty(rb));

    rb_write(rb, 1);
    assert(false == rb_is_empty(rb));
    // printf("ring buffer size: %d\n", sizeof(rb->buffer));

    rb_write(rb, 2);
    rb_write(rb, 3);
    assert(3 == rb_size(rb));

    int temp = -1;
    rb_read(rb, &temp);
    assert(1 == temp);
    assert(2 == rb_size(rb));

    assert(rb_write(rb, 4));
    assert(true == rb_is_full(rb));
    assert(false == rb_write(rb, 5));
    
    assert(rb_read(rb, &temp));
    assert(rb_write(rb, 6));

    return 0;
}