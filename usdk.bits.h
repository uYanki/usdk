#ifndef __USDK_BITS_H__
#define __USDK_BITS_H__

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "usdk.basic.h"
#include "usdk.args.h"

#define LINK64(...) __GET_MACRO_ARGS_4(, ##__VA_ARGS__, LINK64_4, __NULL_MACRO, LINK64_2, __NULL_MACRO, __NULL_MACRO)(__VA_ARGS__)

//---------------------------------------------------------------------------

///< write bit (bit-32)
#define WriteBit32(dat, val, stb)                \
    do {                                         \
        (dat) &= ~(1UL << (stb));                \
        (dat) |= (((val) ? 1UL : 0UL) << (stb)); \
    } while (0)

///< write bits (bit-32)
#define WriteBits32(dat, val, stb, len)          \
    do {                                         \
        (dat) &= ~(MASK32(len) << (stb));        \
        (dat) |= (MASK32(len) & (val)) << (stb); \
    } while (0)

///< write bit (bit-64)
#define WriteBit64(dat, val, stb)                  \
    do {                                           \
        (dat) &= ~(1ULL << (stb));                 \
        (dat) |= (((val) ? 1ULL : 0ULL) << (stb)); \
    } while (0)

///< write bits (bit-64)
#define WriteBits64(dat, val, stb, len)          \
    do {                                         \
        (dat) &= ~(MASK64(len) << (stb));        \
        (dat) |= (MASK64(len) & (val)) << (stb); \
    } while (0)

//---------------------------------------------------------------------------

#define LSB0()
#define LSB1()
#define MSB0()
#define MSB1()

// get mask

#define lobit0(x)      (~x & (x + 1))  ///< the rightmost 0-bit. eg: 0101 -> 0010, 1010 -> 0001
#define lobit1(x)      (x & -x)        ///< the rightmost 1-bit. eg: 0101 -> 0001, 1010 -> 0010. notice: x ^ (x & (x - 1)) = x & ~(x - 1) = x & (-x)

#define lobits0(x)     (~x & (x - 1))  ///< the rightmost 0-bits. eg: 0100 -> 0011
// #define lobits0(x)  (~(x | -x))
// #define lobits0(x)  ((x & -x) - 1)

#define lobit1bits0(x) (x ^ (x - 1))  ///< the rightmost 1-bit and the 0-bits behind it. eg: 1010 -> 0011

#define lobits0to1(x)  (x | (x - 1))              ///< the rightmost 0-bits convert to 1-bits. eg: 1010 -> 1011
#define lobits1to0(x)  (((x | (x - 1)) + 1) & x)  ///< the rightmost 0-bits convert to 1-bits. eg: 1010 -> 1000

#if 0  // example

int main()
{
    f32u a;
    f64u b;

    a.all = 1ul << 25;
    b.all = 1ull << 50;

    // get highest bit

    printf("exp = %u,%u\n",
           a.bit.exp - 127,
           b.bit.exp - 1023);

    // => 25,50

    return 0;
}

#endif

//---------------------------------------------------------------------------
// Functions
//---------------------------------------------------------------------------

INLINE u8 bitcnt(u32 x)  ///< number of 1-bit
{
    u32 t = x;

    t = ((t & 0xAAAA) >> 1) + (t & 0x5555);
    t = ((t & 0xCCCC) >> 2) + (t & 0x3333);
    t = ((t & 0xF0F0) >> 4) + (t & 0x0F0F);
    t = ((t & 0xFF00) >> 8) + (t & 0x00FF);

    return t;
}

/**
 * 浮点数 = 尾数 × （ 基数 ^ 阶码 ）, f = m × ( b ^ e )
 *
 *  - 基数 b ：二进制，即 2
 *  - 尾数 m ：用原码表示
 *  - 阶码 e : 用移码表示
 *                   -----------------------------------------
 * ( f32 ) 32-bits : | S (1-bit) | E (8-bits)  | M (23-bits) |
 * ( f64 ) 64-bits : | S (1-bit) | E (11-bits) | M (52-bits) |
 *                   -----------------------------------------
 *  - 符号位 S (0正1负), 尾数 M = m, 阶码 E = e + 127 (32-bits) / 2047 (64-bits)
 *
 * 原理：整数提升为浮点, 取浮点地址并强转整数地址, 取出该值. 去除尾数, 取出移码前的值.
 *
 *  缺陷: 精度有限, 特殊情况下可能出错。
 *
 * - 原因: 处理的数据的有效位数草果为尾数的有些位数。编译器自动对低位进行进位或去位。
 *
 *   eg. u32 -> s32: (进位情况)
 *
 *      0000_0001_1111_1111_1111_1111_1111_1111 ->
 *      0000_0010_0000_0000_0000_0000_0000_0000 ->
 *      ret = 25 -> 相差 1
 *
 *      0111_1111_1111_1111_1111_1111_1100_0000 (2147483584) ->
 *      1000_0000_0000_0000_0000_0000_0000_0000 (2147483648) ->
 *      ret = 31 -> 相差 128
 *
 */

///< the leftmost 1-bit. return pos ( align right ), no mask. eg: 0010_0000 -> 5
INLINE s8 hibit1(u64 n)
{
    if (n == 0) {
        return -1;
    }

#if 0
    f32 b = n;
    return (*((u32*)&b) >> 23 & 255) - 127;
#else
    f64 b = n;
    return ((*(u64*)&b) >> 52 & 2047) - 1023;
#endif
}

#ifdef __cplusplus
}
#endif

#endif