#ifndef __USDK_CONF_H__
#define __USDK_CONF_H__

#define CONFIG_USING_STDIO_PRINTF 1
#define CONFIG_USING_USDK_PRINTF  0

#if CONFIG_USING_STDIO_PRINTF
#include <stdio.h>
#define CONFIG_STDIO_PRINTF_TXCHAR(ch)
#define println(fmt, ...) printf(fmt "\n", ##__VA_ARGS__)
// #define println(fmt, ...) printf(fmt "\r\n", ##__VA_ARGS__)
#endif

#if CONFIG_USING_USDK_PRINTF
#include "usdk.printf.h"
#define CONFIG_USDK_PRINTF_TXCHAR(ch)
// "void usdk_putchar(char ch){}"
#endif

#define CONFIG_DEBUG_PRINTF printf

#endif