#include "usdk.h"

//---------------------------------------------------------

void FirewareDelay(u32 nWaitTime)
{
    u8 n;
    while (nWaitTime--)
    {
        n = U8_MAX;
        while (n--)
        {
        }
    }
}

//---------------------------------------------------------

/**
 * @brief bubble sort and quick sort
 *
 * @param array  start of target array.
 * @param count array size in elements.
 * @param size  element size in bytes.
 * @param cmp   pointer to a user-supplied routine that compares two array elements
 *              and returns a value that specifies their relationship.
 *
 *      @example s32 compare(RO void* p1, RO void* p2) { return (*(s32*)p1 - *(s32*)p2); }
 *          @retval -1, 0, +1
 *
 * @return N/A
 */

void _bsort(void* array, u32 count, u32 size, sort_cmp_t cmp)
{
    u32 i, j;

    if (size < 2 || count < 2) { return; }

    for (i = 0; i < count - 1; ++i)
    {
        for (j = 0; j < count - i - 1; ++j)
        {
            u8* p1 = (u8*)array + j * size;
            u8* p2 = p1 + size;
            if (cmp(p1, p2) > 0)
            {
                _memswap(p1, p2, size);
            }
        }
    }
}

void _qsort(void* array, u32 count, u32 size, sort_cmp_t cmp)
{
    if (count <= 1)
    {
        return;
    }

    u8* base  = (u8*)array;
    u8* left  = base;
    u8* right = base + (count - 1) * size;
    u8* pivot = base + (count / 2) * size;

    while (left <= right)
    {
        while (cmp(left, pivot) < 0) { left += size; }
        while (cmp(right, pivot) > 0) { right -= size; }
        if (left <= right)
        {
            _memswap(left, right, size);
            left += size;
            right -= size;
        }
    }

    _qsort(base, (right - base) / size + 1, size, cmp);
    _qsort(left, (base + count * size - left) / size, size, cmp);
}

//---------------------------------------------------------

u8 crc8(RO u8* dat, u16 len)
{
    //  x^8 + x^2 + x^1 + 1
    u8 i, crc = 0x00;

    while (len--)
    {
        crc ^= *dat++;
        for (i = 0; i < 8; ++i)
        {
            if (crc & 0x80)
            {
                crc = (crc << 1) ^ 0x07;
            }
            else
            {
                crc <<= 1;
            }
        }
    }

    return crc;
}

u16 crc16(RO u8* dat, u16 len)
{
    // x^16 + x^15 + x^2 + 1

    u16 i, crc = 0xFFFF;

    while (len--)
    {
        crc ^= *dat++;
        for (i = 0; i < 8; ++i)
        {
            if (crc & 0x0001)
            {
                crc = (crc >> 1) ^ 0xA001;
            }
            else
            {
                crc >>= 1;
            }
        }
    }

    return crc;
}

//---------------------------------------------------------

void* _memcpy(void* dest, RO void* src, u32 len)
{
    u8*    dp = dest;
    RO u8* sp = src;
    while (len--) { *dp++ = *sp++; }
    return dest;
}

void* _memmove(void* dest, RO void* src, u32 len)
{
    u8*    dp = dest;
    RO u8* sp = src;
    if (dp < sp)
    {
        while (len--)
        {
            *dp++ = *sp++;
        }
    }
    else if (dp > sp)
    {
        dp += len;
        sp += len;
        while (len--)
        {
            *--dp = *--sp;
        }
    }
    return dest;
}

void* _memset(void* src, u8 chr, u32 len)
{
    u8* p = src;
    while (len--) { *p++ = chr; }
    return src;
}

void _memswap(void* src1, void* src2, u32 len)
{
    u8* p1 = (u8*)src1;
    u8* p2 = (u8*)src2;
    u8  tmp;
    while (len--)
    {
        tmp   = *p1;
        *p1++ = *p2;
        *p2++ = tmp;
    }
}

s32 _memcmp(RO void* src1, RO void* src2, u32 len)
{
    RO u8 *p1 = src1, *p2 = src2;

    while (len--)
    {
        if (*p1 != *p2)
        {
            return (*p1 > *p2) ? 1 : -1;
        }
        ++p1, ++p2;
    }

    return 0;
}

void* _memfrob(void* src, u8 chr, u32 len)
{
    u8* p = src;
    while (len--) { *p++ ^= chr; }
    return src;
}

void* _memchr(RO void* src, u8 chr, u32 len)
{
    RO u8* p = src;

    while (len--)
    {
        if (*p == chr) { return (void*)p; }
        ++p;
    }

    return nullptr;
}

void* _memrchr(RO void* src, u8 chr, u32 len)
{
    RO u8* p = (RO u8*)src + len - 1;

    while (len--)
    {
        if (*p == chr) { return (void*)p; }
        --p;
    }

    return nullptr;
}

// 数据往低地址移动
void _mem_lshift(void* ptr, u16 len, u16 shift)
{
    u8* src = (u8*)ptr;
    u8* dst = src + shift;

    while (len-- > shift)
    {
        *src++ = *dst++;
    }

    while (shift-- > 0)
    {
        *src++ = 0;
    }
}

// 数据往高地址移动
void _mem_rshift(void* ptr, u16 len, u16 shift)
{
    u8* src = (u8*)ptr + len - 1;
    u8* dst = src + shift;

    while (len-- > shift)
    {
        *(dst + len) = *(src + len);
    }

    while (shift-- > 0)
    {
        *(dst + shift) = 0;
    }
}

//---------------------------------------------------------

s32 _str2dec(__IN RO u8* str)
{
    u8  sig = 1;
    s32 ret = 0;

    while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
    {
        ++str;
    }

    if (*str == '-')
    {
        sig = 0;
        ++str;
    }
    else if (*str == '+')
    {
        ++str;
    }

    while (*str >= '0' && *str <= '9')
    {
        ret = ret * 10 + (*str++ - '0');
    }

    return sig ? ret : -ret;
}

u32 _str2hex(__IN RO u8* str)
{
    u8  num;
    u32 ret = 0;

    while (*str)
    {
        if ('0' <= *str && *str <= '9')
        {
            num = *str - '0';
        }
        else if ('a' <= *str && *str <= 'f')
        {
            num = *str - 'a' + 10;
        }
        else if ('A' <= *str && *str <= 'F')
        {
            num = *str - 'A' + 10;
        }
        else
        {
            break;
        }
        ret *= 16;
        ret += num;
        ++str;
    }

    return ret;
}

f32 _str2flt(__IN RO u8* str)
{
    u8  sig   = 1;
    f32 ret   = 0.0;
    f32 power = 1.0;

    while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
    {
        ++str;
    }

    if (*str == '-')
    {
        sig = 0;
        ++str;
    }
    else if (*str == '+')
    {
        ++str;
    }

    while (*str >= '0' && *str <= '9')
    {
        ret *= 10.0;
        ret += (*str++ - '0');
    }

    if (*str == '.')
    {
        str++;
        while (*str >= '0' && *str <= '9')
        {
            ret *= 10.0;
            ret += (*str++ - '0');
            power *= 10.0;
        }
    }

    return (sig ? ret : -ret) / power;
}

u8* _int2str(__OUT u8* str, s32 num, u8 base)
{
    if (base < 2 || base > 36)
    {
        *str = '\0';
        return str;
    }

    u8 *p = str, *q = str;

    u8  tmp;
    u32 rem;  // remainder
    u32 val = (num < 0) ? -num : num;

    do {
        rem = val % base;
#if 0
        // *p++ = "0123456789abcdefghijklmnopqrstuvwxyz"[rem];
        *p++ = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[rem];
#else
        // *p++ = (rem < 10) ? (rem + '0') : (rem - 10 + 'a');
        *p++ = (rem < 10) ? (rem + '0') : (rem - 10 + 'A');
#endif
        val /= base;
    } while (val != 0);

    // negative
    if (num < 0) { *p++ = '-'; }

    // endwith '0'
    *p-- = '\0';

    // reverse string
    while (q < p)
    {
        tmp  = *q;
        *q++ = *p;
        *p-- = tmp;
    }

    return str;
}

u32 _strlen(RO u8* str)
{
    RO u8* p = str;
    while (*++p) {}
    return (p - str);
}

s32 _strcmp(RO u8* str1, RO u8* str2)
{
    for (; *str1 == *str2 && *str1; str1++, str2++) {}
    return (*str1 - *str2);
}

u8* _strcpy(u8* dest, RO u8* src)
{
    u8* p = dest;
    while ((*p++ = *src++)) {}
    return dest;
}

u8* _strcat(u8* dest, RO u8* src)
{
    u8* p = dest;
    while (*dest++) {}
    while ((*dest++ = (u8)*src++)) {}
    return p;
}

u8* _strstr(RO u8* str, RO u8* substr)
{
    for (; *str; ++str)
    {
        RO u8 *p1 = str, *p2 = substr;
        while (*p1 && *p2 && *p1 == *p2) { ++p1, ++p2; }
        if (!*p2)
        {
            return (u8*)str;
        }
    }
    return nullptr;
}

u8* _strncpy(u8* dest, RO u8* src, u32 len)
{
    u8* p = dest;
    while ((len-- > 0) && (*dest++ = *src++)) {}
    while ((len-- > 0)) { *dest++ = '\0'; }
    return p;
}

u8* _substr(u8* dest, RO u8* src, u32 start, u32 len)
{
    RO u8 *p = src + start, *ret = dest;

    while (*p && len--) { *dest++ = *p++; }
    *dest = '\0';

    return (u8*)ret;
}

u8* _strlwr(RO u8* str)
{
    u8* s = (u8*)str;
    while (*s)
    {
        if (*s >= 'A' && *s <= 'Z')
        {
            *s |= ' ';  // 0x20
        }
        ++s;
    }
    return (u8*)str;
}

u8* _strupr(RO u8* str)
{
    u8* s = (u8*)str;
    while (*s != '\0')
    {
        if (*s >= 'a' && *s <= 'z')
        {
            *s &= ~' ';  // 0x20
        }
        ++s;
    }
    return (u8*)str;
}

//---------------------------------------------------------

#if 0  // example

#define STR(x) #x

    s32   i;
    f32 d;

    RO u8* p = STR(-0b1000#5432);

    getNumber(&p, &i, &d);

#endif

__private u8 _str2num(RO u8* buffer, s32* result, u8 base)
{
    u8 limits[3];
    u8 length = 0;

    if (base > 36)
    {
        goto exit;
    }

    limits[0] = (base < 10) ? ('0' + base) : '9';
    limits[1] = 'a' + base - 11;
    limits[2] = 'A' + base - 11;

    *result = 0;

    while (*buffer)
    {
        if (INCLOSE(*buffer, '0', limits[0]))
        {
            *result *= base;
            *result += *buffer - '0';
        }
        else if (INCLOSE(*buffer, 'a', limits[1]))
        {
            *result *= base;
            *result += *buffer - 'a';
        }
        else if (INCLOSE(*buffer, 'A', limits[2]))
        {
            *result *= base;
            *result += *buffer - 'A';
        }
        else
        {
            break;
        }

        ++length;
        ++buffer;
    }

exit:

    return length;
}

bool getNumber(RO u8** buffer, s32* integer, f32* decimal)
{
    // https://www.sojson.com/hexconvert.html
    // support format (e.g): 0b101,0777,-0xABCD,6#0101,16#5A5A,-0x10#5A5A,...

    RO u8* ptr = *buffer;

    u8 sign, base, len;

    // 符号

    switch (*ptr)
    {
        case '-':
            ++ptr;
            sign = 0;
            break;
        case '+':
            ++ptr;
        case '0' ... '9':
            sign = 1;
            break;
        default:
            return false;
    }

    // 进制

    switch (*ptr)
    {
        default:
        case '\0': {
            return false;
        }
        case '0': {
            switch (*++ptr)
            {
                default:
                case '\0': {
                    // dec
                    *integer = 0;
                    *decimal = 0;
                    // base = 10;
                    goto exit;
                }
                case 'b':
                case 'B': {
                    // bin
                    ++ptr;
                    base = _isbdigit(*ptr) ? 2 : 10;
                    break;
                }
                case 'x':
                case 'X': {
                    // hex
                    ++ptr;
                    base = _isxdigit(*ptr) ? 16 : 10;
                    break;
                }
                case '0' ... '7': {
                    // oct
                    base = 8;
                    break;
                }
            }
            break;
        }
        case '1' ... '9': {
            // dec
            base = 10;
            break;
        }
    }

    // 整数部分

    {
        ptr += _str2num(ptr, (u32*)integer, base);

        if (*ptr == '#')
        {
            base = *integer;

            if ((len = _str2num(++ptr, (u32*)integer, base)) == 0)
            {
                // error format
                return false;
            }

            ptr += len;
        }

        if (sign == 0)  // neg
        {
            *integer = -*integer;
        }
    }

    // 小数部分

    {
        if (decimal != NULL && *ptr == '.')
        {
            u32 tmp;

            if ((len = _str2num(++ptr, &tmp, base)) == 0)
            {
                // error format
                return false;
            }

            ptr += len;

            //

            *decimal = tmp;

            while (len--)
            {
                *decimal /= base;
            }
        }
    }

exit:

#if 0

    if (decimal == NULL)
    {
        printf("%d\n", *integer);
    }
    else
    {
        printf("%f\n", *integer + *decimal);
    }

#endif

    *buffer = ptr;

    return true;
}

//---------------------------------------------------------

f32 _sqrt(f32 n)
{
    f32 x;
    s32 i;

    i = (*(s32*)&n);
    i >>= 1;
    i = 0x5f375a86 - i;
    x = *(f32*)&i;
    x *= (3.0f - n * x * x);
    x *= 0.5f;
    x *= n;

    return x;
}

/**
 * @brief y = b0 + b1 * x^1 + b2 * x^2 ... bn * x^n
 */
f32 _polynomial(f32 x, f32 b[], u8 n)
{
    u8  i;
    f32 y  = 0;
    f32 xn = 1;
    for (i = 0; i < n; ++i)
    {
        y += b[i] * xn;
        xn *= x;
    }

    return y;
}

//---------------------------------------------------------

#if CONFIG_USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(u8* file, s32 line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}
#endif