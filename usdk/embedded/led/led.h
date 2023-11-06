#ifndef __USDK_LED_H__
#define __USDK_LED_H__

#include "usdk.h"

/**
 * @brief LED Control
 */
#define LED_ON()
#define LED_OFF()
#define LED_TGL()  // toggle

/**
 * @brief Tube Segment
 *
 *   +- a -+
 *   f     b
 *   +- g -+
 *   e     c
 *   +- d -+ .dp
 *
 */

#define NEGCOM     0
#define POSCOM     1

RO u8 TubeCodeHex[2][16] = {
  // clang-format off

    // negative common
    { 
    
        /* 0,    1,    2,    3,    4,    5,    6,    7*/
        0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
        /* 8,    9,    A,    b,    C,    d,    E,    F*/
        0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71 
    
    },

    // positive common
    { 
     
        /* 0,    1,    2,    3,    4,    5,    6,    7*/
        0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,
        /* 8,    9,    A,    b,    C,    d,    E,    F*/
        0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E

    },

  // clang-format on
};

INLINE u8 NegAddPoint(u8 n) { return n | 0x80; }
INLINE u8 PosAddPoint(u8 n) { return n - 0x80; }

#endif
