#ifndef __USDK_ARGS_H__
#define __USDK_ARGS_H__

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------

#include "usdk.basic.h"

//---------------------------------------------------------------------------
// Marco
//---------------------------------------------------------------------------

#define _STRING(a)  #a    ///< '#' 参数转字符串
#define _LINK(a, b) a##b  ///< '##' 参数连接符

#define __NULL_MACRO(...)

#define __GET_MACRO_ARGS_1(_0, _1, _N, ...)                             _N
#define __GET_MACRO_ARGS_2(_0, _1, _2, _N, ...)                         _N
#define __GET_MACRO_ARGS_3(_0, _1, _2, _3, _N, ...)                     _N
#define __GET_MACRO_ARGS_4(_0, _1, _2, _3, _4, _N, ...)                 _N
#define __GET_MACRO_ARGS_5(_0, _1, _2, _3, _4, _5, _N, ...)             _N
#define __GET_MACRO_ARGS_6(_0, _1, _2, _3, _4, _5, _6, _N, ...)         _N
#define __GET_MACRO_ARGS_7(_0, _1, _2, _3, _4, _5, _6, _7, _N, ...)     _N
#define __GET_MACRO_ARGS_8(_0, _1, _2, _3, _4, _5, _6, _7, _8, _N, ...) _N

/**
 * @brief 取传入宏中的参数个数
 * @note '##' 的作用时当传入参数个数为0时, 会去除其前放的逗号
 *
 *      原理?
 *    COUNT_ARGS(a,b) => __GET_MACRO_ARGS_8(  ,  a,  b,  8,  7  ,6  ,5,  4,  3,  2,  1, 0 )
 *                       __GET_MACRO_ARGS_8(_8, _7, _6, _5, _4, _3, _2, _1, _0, _N, ...)
 *
 *                    =>  _N 对应的 2, 因此该宏的输出为 2
 */
#define COUNT_ARGS(...)                                                 __GET_MACRO_ARGS_8(, ##__VA_ARGS__, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#ifdef __cplusplus
}
#endif

#endif