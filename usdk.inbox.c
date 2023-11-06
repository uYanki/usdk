#include "usdk.inbox.h"
#include "usdk.string.h"

s32 gcd(s32 a, s32 b)
{
    // 辗转相除法

    s32 r;
    while (b != 0) {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

s32 lcm(s32 a, s32 b)
{
    return a / gcd(a, b) * b;
}

s32 isPrime(s32 n)
{
    s32 i;
    if (n < 2) return 0;
    for (i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

u8 isPalindromeString(RO u8* str)
{
    u32 len = _strlen(str), i;
    for (i = 0; i < len / 2; i++) {
        if (str[i] != str[len - i - 1]) {
            return 0;  // no
        }
    }
    return 1;  // yes
}

u8 isPalindromeNumber(s32 num)
{
    // mun: reversed num

    s32 mun = 0, t;

    for (t = num; t != 0; t /= 10) {
        mun *= 10;
        mun += t % 10;
    }

    return num == mun;
}
