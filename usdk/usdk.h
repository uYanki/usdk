#ifndef __USDK_DEFS_H__
#define __USDK_DEFS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "conf.h"

#include "usdk.basic.h"

#define __private static
#define __public

#define INLINE static inline

//---------------------------------------------------------------------------
// Types
//

//---------------------------------------------------------

typedef void (*lpfnCbk0_t)(void);
// typedef bool_e (*lpfnCbk_t)(void* arg);

/**
 * number = 0x1234
 *
 *      低地址  高地址
 * 大端   0x12   0x34
 * 小端   0x34   0x12
 *
 */

typedef enum {
    ENDIAN_BIG,     ///< 高位在低地址
    ENDIAN_LITTLE,  ///< 低位在高地址
} endian_e;

typedef enum {
    UINT_FORMAT_BIN = 0,  // binary
    UINT_FORMAT_DEC = 1,  // decimal
    UINT_FORMAT_HEX = 2,  // hexadecimal
    UINT_FORMAT_BCD = 3,
} uint_fmt_e;

//---------------------------------------------------------------------------
// Constants
//

INLINE s32 sign(s32 n)
{
    return (n >> 31) | ((u32)(-n) >> 31);
}

//---------------------------------------------------------------------------
// Functions
//

INLINE f32 _floor(f32 x) { return (f32)((s32)x - (x < 0.0f && x != (s32)x)); }         ///< 向下取整
INLINE f32 _ceil(f32 x) { return (f32)((s32)x + (x > 0.0f && x != (s32)x)); }          ///< 向上取整
INLINE f32 _round(f32 x) { return (x >= 0.0f) ? _floor(x + 0.5f) : _ceil(x - 0.5f); }  ///< 四舍五入

//---------------------------------------------------------------------------
// Components
//

//---------------------------------------------------------
///< @defgroup memory

/**
 * @param dest: destination
 * @param src:  source
 */

void* _memset(void* src, u8 chr, u32 len);
void* _memcpy(void* dest, RO void* src, u32 len);
void* _memmove(void* dest, RO void* src, u32 len);
void  _memswap(void* src1, void* src2, u32 len);

s32 _memcmp(RO void* src1, RO void* src2, u32 len);

void* _memxor(void* src, u8 chr, u32 len);      ///< 异或
void* _memlchr(RO void* src, u8 chr, u32 len);  ///< 顺找
void* _memrchr(RO void* src, u8 chr, u32 len);  ///< 倒找

void _mem_lshift(void* ptr, u16 len, u16 shift);
void _mem_rshift(void* ptr, u16 len, u16 shift);

//---------------------------------------------------------
///< @defgroup sort

typedef s32 (*sort_cmp_t)(RO void*, RO void*);

///< swap elements when function ('cmp') return value is greater than 0
void _bsort(void* array, u32 count, u32 size, sort_cmp_t cmp);  // bubble
void _qsort(void* array, u32 count, u32 size, sort_cmp_t cmp);  // quick

//---------------------------------------------------------
///< @defgroup crc (http://www.ip33.com/crc.html)

u8  crc8(RO u8* dat, u16 len);
u16 crc16(RO u8* dat, u16 len);

//---------------------------------------------------------
///< @defgroup string

#if CONFIG_MODULE_STRING

typedef const char* cstr;

INLINE char _islower(char c) { return ('a' <= c && c <= 'z'); }
INLINE char _isupper(char c) { return ('A' <= c && c <= 'Z'); }

INLINE int _isalpha(char c) { return _islower(c) || _isupper(c); }

///< is binary number
INLINE bool _isbdigit(char c) { return (c == '0' || c == '1'); }
///< is decimal number
INLINE bool _isdigit(char c) { return ('0' <= c && c <= '9'); }
///< is hexadecimal number
INLINE bool _isxdigit(char c) { return (_isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')); }
///< is blank character
INLINE bool _isspace(char c) { return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v'); }

s32 _str2dec(__IN RO u8* str);                  ///< ascii to decimal integer
u32 _str2hex(__IN RO u8* str);                  ///< ascii to hexadecimal integer
f32 _str2flt(__IN RO u8* str);                  ///< ascii to real
u8* _int2str(__OUT u8* str, s32 num, u8 base);  ///< integers from 2 to 36 bases convert to ascii

u32 _strlen(RO u8* str);                                ///< calculate the length of a string
s32 _strcmp(RO u8* str1, RO u8* str2);                  ///< compare the size of two strings
u8* _strcpy(u8* dest, RO u8* src);                      ///< copy the source string to the destination string
u8* _strncpy(u8* dest, RO u8* src, u32 len);            ///< copy the first n characters of the source string to the destination string
u8* _strcat(u8* dest, RO u8* src);                      ///< append the source string to the end of the destination string
u8* _strstr(RO u8* str, RO u8* substr);                 ///< find the position of a substring in a string
u8* _substr(u8* dest, RO u8* src, u32 start, u32 len);  ///< take n characters from a string starting at a certain position

u8* _strlwr(RO u8* str);  ///< lower
u8* _strupr(RO u8* str);  ///< upper

#endif

//---------------------------------------------------------
///< @defgroup math

f32 _sqrt(f32 n);
f32 _polynomial(f32 x, f32 b[], u8 n);

// clang-format off

#if 1
INLINE f32 _square(f32 n) { return n * n; }
INLINE f32 _cube(f32 n) { return n * n * n; }
#else
#define _square(x) ({ (x) * (x); })
#define _cube(x)   ({ (x) * (x) * (x); })
#endif

// clang-format on

//---------------------------------------------------------
///< @defgroup byte swap

INLINE u16 _bswap16(u16 x)
{
    return ((x & 0xFF00) >> 8) |
           ((x & 0x00FF) << 8);
}

INLINE u32 _bswap32(u32 x)
{
    return ((x & 0xFF000000) >> 24) |
           ((x & 0x00FF0000) >> 8) |
           ((x & 0x0000FF00) << 8) |
           ((x & 0x000000FF) << 24);
}

INLINE u64 _bswap64(u64 x)
{
    return ((x & 0xFF00000000000000) >> 56) |
           ((x & 0x00FF000000000000) >> 40) |
           ((x & 0x0000FF0000000000) >> 24) |
           ((x & 0x000000FF00000000) >> 8) |
           ((x & 0x00000000FF000000) << 8) |
           ((x & 0x0000000000FF0000) << 24) |
           ((x & 0x000000000000FF00) << 48) |
           ((x & 0x00000000000000FF) << 56);
}

//---------------------------------------------------------
///< @defgroup error check

#if CONFIG_USE_FULL_ASSERT
/**
 * @brief  The assert_param macro is used for function's parameters check.
 * @param  expr: If expr is false, it calls assert_failed function which reports
 *         the name of the source file and the source line number of the call
 *         that failed. If expr is true, it returns no value.
 * @retval None
 */
#define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t*)__FILE__, __LINE__))
void assert_failed(uint8_t* file, uint32_t line);
#else
#define assert_param(expr) ((void)0)
#endif

#ifdef __cplusplus
}
#endif

#endif