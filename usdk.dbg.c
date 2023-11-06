#include "usdk.dbg.h"

void print_binary(RO u8* tag, u64 num, u64 stb, u8 len, RO u8* sep, u8 stp)
{
    if (0 < len && len <= 64) {
        LOGF(tag);
        {
            u8  n   = 0;
            u64 msk = 1ull << (len - 1);
            do {
                LOGF("%c", (num & msk) ? '1' : '0');
                // print one separator per step
                if (++n == stp) {
                    n = 0;
                    if (len -= stp) LOGF("%s", sep);
                }
            } while (msk >>= 1);
        }
    }
}
