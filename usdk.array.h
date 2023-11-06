#ifndef __USDK_ARRAY_H__
#define __USDK_ARRAY_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 下标运算符`[]`的本质: 加法
 *
 *  u8 idx   = 0;
 *  u8 arr[] = {0x00, 0x01};
 *
 *  println("%d", 0 [arr]);             // arr[0]
 *  println("%d", 1 [arr]);             // arr[1]
 *  println("%d", 0 [arr + 1]);         // arr[1]
 *  println("%d", (idx + 0)[arr]);      // arr[0]
 *  println("%d", (idx + 1)[arr]);      // arr[1]
 *  println("%d", (idx - 1)[arr + 1]);  // arr[0]
 *
 */

//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "usdk.basic.h"
#include <stdarg.h>

//---------------------------------------------------------------------------
// Types
//---------------------------------------------------------------------------

#define arr_s8_t  s8[]
#define arr_s16_t s16[]
#define arr_s32_t s32[]
#define arr_s64_t s64[]

#define arr_u8_t  u8[]
#define arr_u16_t u16[]
#define arr_u32_t u32[]
#define arr_u64_t u64[]

#define arr_f32_t f32[]
#define arr_f64_t f64[]

// eg: println("%d", (arr_u8_t){0x00, 0x01}[idx]);

//---------------------------------------------------------------------------
// Enums
//---------------------------------------------------------------------------

// data type
typedef enum {
    DATA_TYPE_S8,
    DATA_TYPE_S16,
    DATA_TYPE_S32,
    DATA_TYPE_S64,
    DATA_TYPE_U8,
    DATA_TYPE_U16,
    DATA_TYPE_U32,
    DATA_TYPE_U64,
    DATA_TYPE_F32,
    DATA_TYPE_F64,
    DATA_TYPE_STR,  // string
} type_e;

//---------------------------------------------------------------------------
// Structures
//---------------------------------------------------------------------------

typedef struct {
    str    header;
    str    format;
    void*  array;
    type_e type;
} csv_col_t;

//---------------------------------------------------------------------------
// Function
//---------------------------------------------------------------------------

bool_e arr2csv(str filename, csv_col_t columns[], u16 rows, u16 cols);

f32  array_sum(f32* arr, u16 cnt);
void array_offset(f32* arr, u16 cnt, f32 offset);
void array_scale(f32* arr, u16 cnt, f32 scale);

#ifdef __cplusplus
}
#endif

#endif