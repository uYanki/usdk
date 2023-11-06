#ifndef __RINGBUF_H__
#define __RINGBUF_H__

#include "usdk.h"

//---------------------------------------------------------
// structure
//

typedef struct {
    u8* buffer;
    u16 capacity;
    u16 length;
    u16 seeker;  // reader
    // u16 writer;
} ringbuf_t;

typedef enum {
    RINGBUF_JUMPTO_NONE,
    RINGBUF_JUMPTO_BEFORE,
    RINGBUF_JUMPTO_AFTER,
} ringbuf_jumpto_e;

//---------------------------------------------------------
// function
//

#define ringbuf_push_str(ringbuf, string) ringbuf_push_n(ringbuf, (u8*)string, strlen(string))

inline bool ringbuf_init(ringbuf_t* ringbuf, u8* buffer, u16 capacity);

inline bool ringbuf_is_empty(ringbuf_t* ringbuf);
inline bool ringbuf_is_full(ringbuf_t* ringbuf);
inline bool ringbuf_is_hallfull(ringbuf_t* ringbuf);

inline bool ringbuf_readable(ringbuf_t* ringbuf);
inline bool ringbuf_writable(ringbuf_t* ringbuf);

inline void ringbuf_flush(ringbuf_t* ringbuf);

inline u16 ringbuf_get_used(ringbuf_t* ringbuf);
inline u16 ringbuf_get_free(ringbuf_t* ringbuf);
inline u16 ringbuf_get_capacity(ringbuf_t* ringbuf);

inline bool ringbuf_push(ringbuf_t* ringbuf, __IN u8 buffer);
inline bool ringbuf_pop(ringbuf_t* ringbuf, __OUT u8* buffer);

inline bool ringbuf_push_n(ringbuf_t* ringbuf, __IN u8* buffer, u16 length);
inline bool ringbuf_pop_n(ringbuf_t* ringbuf, __OUT u8* buffer, u16 length);

void ringbuf_display(ringbuf_t* ringbuf);

s32 ringbuf_match(ringbuf_t* ringbuf, __IN u8* tgtbuf, u16 tgtlen, ringbuf_jumpto_e jumpto);

void ringbuf_cutoff(ringbuf_t* ringbuf, __OUT u8* tgtbuf, u16 start, u16 end);

#endif