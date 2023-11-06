#include "ringbuf.h"

#include <stdio.h>
#include <string.h>

#define abs_delta(v1, v2) ((v1) >= (v2)) ? ((v1) - (v2)) : ((v2) - (v1))

///< regexpr: @e \{(\n.*?)+?\n\} => @e ;\n

bool ringbuf_init(ringbuf_t* ringbuf, u8* buffer, u16 capacity)
{
    if (buffer == nullptr || capacity == 0)
    {
        return false;
    }

    ringbuf->buffer   = buffer;
    ringbuf->capacity = capacity;
    ringbuf->length   = 0;
    ringbuf->seeker   = 0;

    return true;
}

bool ringbuf_is_empty(ringbuf_t* ringbuf)
{
    return ringbuf->length == 0;
}

bool ringbuf_is_full(ringbuf_t* ringbuf)
{
    return ringbuf->length == ringbuf->capacity;
}

bool ringbuf_is_hallfull(ringbuf_t* ringbuf)
{
    return ringbuf->length >= (ringbuf->capacity >> 1);
}

bool ringbuf_readable(ringbuf_t* ringbuf)
{
    return ringbuf->length > 0;
}

bool ringbuf_writable(ringbuf_t* ringbuf)
{
    return ringbuf->length < ringbuf->capacity;
}

void ringbuf_flush(ringbuf_t* ringbuf)
{
    ringbuf->length = 0;
}

u16 ringbuf_get_used(ringbuf_t* ringbuf)
{
    return ringbuf->length;
}

u16 ringbuf_get_free(ringbuf_t* ringbuf)
{
    return ringbuf->capacity - ringbuf->length;
}

u16 ringbuf_get_capacity(ringbuf_t* ringbuf)
{
    return ringbuf->capacity;
}

bool ringbuf_push(ringbuf_t* ringbuf, __IN u8 buffer)
{
    if (ringbuf_writable(ringbuf))
    {
        ringbuf->buffer[(ringbuf->seeker + ringbuf->length++) % ringbuf->capacity] = buffer;
        return true;
    }

    // empty
    return false;
}

bool ringbuf_pop(ringbuf_t* ringbuf, __OUT u8* buffer)
{
    if (ringbuf_readable(ringbuf))
    {
        *buffer = ringbuf->buffer[ringbuf->seeker++];
        --ringbuf->length;
        return true;
    }

    // overflow
    return false;
}

bool ringbuf_push_n(ringbuf_t* ringbuf, __IN u8* buffer, u16 length)
{
    if (buffer == nullptr || length == 0 || ringbuf_get_free(ringbuf) < length)
    {
        return false;
    }

    RO u16 rb_length   = ringbuf->length;
    u8*    rb_buffer   = ringbuf->buffer;
    RO u16 rb_capacity = ringbuf->capacity;
    u16    rb_writer   = (ringbuf->seeker + rb_length) % rb_capacity;

    ringbuf->length += length;

    while (rb_writer < rb_capacity)
    {
        rb_buffer[rb_writer++] = *buffer++;

        if (--length == 0)
        {
            break;
        }
    }

    while (length--)
    {
        *rb_buffer++ = *buffer++;
    }

    return true;
}

bool ringbuf_pop_n(ringbuf_t* ringbuf, __OUT u8* buffer, u16 length)
{
    if (buffer == nullptr || length == 0 || ringbuf_get_used(ringbuf) < length)
    {
        return false;
    }

    u16    rb_reader   = ringbuf->seeker;
    u8*    rb_buffer   = ringbuf->buffer;
    RO u16 rb_capacity = ringbuf->capacity;

    ringbuf->length -= length;
    ringbuf->seeker += length;
    ringbuf->seeker %= rb_capacity;

    while (rb_reader < rb_capacity)
    {
        *buffer++ = rb_buffer[rb_reader++];
        if (--length == 0)
        {
            break;
        }
    }

    while (length--)
    {
        *buffer++ = *rb_buffer++;
    }

    return true;
}

void ringbuf_display(ringbuf_t* ringbuf)
{
    u16 length = ringbuf_get_used(ringbuf);

    // used bytes
    printf("%05dd | ", length);

    // content
    if (length > 0)
    {
        u8*    rb_buffer   = ringbuf->buffer;
        RO u16 rb_capacity = ringbuf->capacity;
        u16    rb_reader   = ringbuf->seeker;

        while (length--)
        {
            printf("%c", rb_buffer[rb_reader]);
            if (++rb_reader == rb_capacity)
            {
                rb_reader = 0;
            }
        }
    }

    // newline
    printf("\n");
}

/// @return -1:fail to match, >=0 success to match, and return the offset of the buffer
s32 ringbuf_match(ringbuf_t* ringbuf, __IN u8* target_buffer, u16 target_length, ringbuf_jumpto_e jumpto)
{
    u16 target_index = 0;

    RO u8* rb_buffer   = ringbuf->buffer;
    RO u16 rb_capacity = ringbuf->capacity;
    u16    rb_length   = ringbuf->length;
    RO u16 rb_seeker   = ringbuf->seeker;
    u16    rb_reader   = ringbuf->seeker;

    while (rb_length--)
    {
        // match
        if (rb_buffer[rb_reader] == target_buffer[target_index])
        {
            if (++target_index == target_length)
            {
                goto success;
            }
        }
        else
        {
            target_index = 0;
        }

        // loopback
        if (++rb_reader == rb_capacity)
        {
            rb_reader = 0;
        }
    }

    // fail
    return -1;

success:
    // success

    if (++rb_reader == rb_capacity)
    {
        rb_reader = 0;
    }

    if (jumpto == RINGBUF_JUMPTO_NONE || jumpto == RINGBUF_JUMPTO_BEFORE)
    {
        if (rb_reader >= target_length)
        {
            rb_reader -= target_length;
        }
        else
        {
            rb_reader = rb_capacity - (target_length - rb_reader);
        }
    }

    if (jumpto != RINGBUF_JUMPTO_NONE)
    {
        if (rb_reader >= rb_seeker)
        {
            ringbuf->length -= rb_reader - rb_seeker;
        }
        else
        {
            ringbuf->length -= rb_capacity - (rb_seeker - rb_reader);
        }

        ringbuf->seeker = rb_reader;
    }

    return rb_reader;
}

/**
 * @param tgtbuf target buffer
 * @param start  start offset (include)
 * @param end    end offset (exclude)
 */
void ringbuf_cutoff(ringbuf_t* ringbuf, __OUT u8* tgtbuf, u16 start, u16 end)
{
    u8*    rb_buffer   = ringbuf->buffer;
    RO u16 rb_capacity = ringbuf->capacity;

    start %= rb_capacity;
    end %= rb_capacity;

    while (start != end)
    {
        *tgtbuf++ = rb_buffer[start];
        if (++start == rb_capacity)
        {
            start = 0;
        }
    }
}
