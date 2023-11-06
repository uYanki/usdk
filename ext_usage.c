#include "usdk.basic.h"
#include "usdk.dbg.h"
#include "usdk.array.h"

int main()
{
    //> [] 的本质是加法

    u8 idx   = 0;
    u8 arr[] = {0x00, 0x01};

    println("%d", 0 [arr]);             // arr[0]
    println("%d", 1 [arr]);             // arr[1]
    println("%d", 0 [arr + 1]);         // arr[1]
    println("%d", (idx + 0)[arr]);      // arr[0]
    println("%d", (idx + 1)[arr]);      // arr[1]
    println("%d", (idx - 1)[arr + 1]);  // arr[0]

    return 0;
}