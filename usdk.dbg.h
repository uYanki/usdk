#ifndef __USDK_DEBUG_H__
#define __USDK_DEBUG_H__

#include "usdk.basic.h"

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include <stdio.h>

#include "usdk.conf.h"
#include "usdk.basic.h"

//---------------------------------------------------------------------------
// Configurations
//---------------------------------------------------------------------------

#define LOGF(fmt, ...) CONFIG_DEBUG_PRINTF(fmt, ##__VA_ARGS__)

//---------------------------------------------------------------------------
// Marcos
//---------------------------------------------------------------------------

#define LV_ERR         0  ///< error
#define LV_WRN         1  ///< warning
#define LV_INFO        2  ///< info
#define LV_DBG         3  ///< debug

#if 0

#define LOG()
#define LOGE(fmt, ...) LOG()
#define LOGW(fmt, ...) LOG()
#define LOGI(fmt, ...) LOG()
#define LOGD(fmt, ...) LOG()

#endif

//---------------------------------------------------------------------------
// Marcos
//---------------------------------------------------------------------------

/**
 * @brief print binary
 * @example DEBUG_PRINT_ARRAY("arr: ", " %d", arr, ARRAY_SIZE(arr));
 */
#define DEBUG_PRINT_BINARY                print_binary
#define DEBUG_PRINT_BINARY_FAST(tag, num) print_binary(tag, num, 0, 8 * sizeof(num), "'", 4)
void print_binary(RO u8* tag, u64 num, u64 stb, u8 len, RO u8* sep, RO u8 stp);

/**
 * @brief print array
 * @example DEBUG_PRINT_ARRAY("arr: ", " %d", arr, ARRAY_SIZE(arr));
 */
#define DEBUG_PRINT_ARRAY(tag, fmt, arr, len)  \
    do {                                       \
        u16 i;                                 \
        CONFIG_DEBUG_PRINTF(tag);              \
        for (i = 0; i < len - 1; ++i)          \
            CONFIG_DEBUG_PRINTF(fmt, arr[i]);  \
        CONFIG_DEBUG_PRINTF(fmt "\n", arr[i]); \
    } while (0)

#ifdef __cplusplus
}
#endif

#endif