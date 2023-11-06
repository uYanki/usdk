#include <stdio.h>

// cmd 上的颜色变量（非 PowerShell）

///-------------------------------
/// @brief foreground colors

// basic
#define Fore_Black         "30"
#define Fore_Red           "31"
#define Fore_Green         "32"
#define Fore_Yellow        "33"
#define Fore_Blue          "34"
#define Fore_Magenta       "35"  // 品红
#define Fore_Cyan          "36"
#define Fore_White         "37"

// extra
#define Fore_Dark_Gray     "90"
#define Fore_Light_Red     "91"
#define Fore_Light_Green   "92"
#define Fore_Light_Yellow  "93"
#define Fore_Light_Blue    "94"
#define Fore_Light_Magenta "95"
#define Fore_Light_Cyan    "96"  // 青色
#define Fore_Light_White   "97"

///-------------------------------
/// @brief background colors

// basic
#define Back_Black         "40"
#define Back_Red           "41"
#define Back_Green         "42"
#define Back_Yellow        "43"
#define Back_Blue          "44"
#define Back_Magenta       "45"
#define Back_Cyan          "46"
#define Back_White         "47"

// extra
#define Back_Dark_Gray     "100"
#define Back_Light_Red     "101"
#define Back_Light_Green   "102"
#define Back_Light_Yellow  "103"
#define Back_Light_Blue    "104"
#define Back_Light_Magenta "105"
#define Back_Light_Cyan    "106"
#define Back_Light_White   "107"

///-------------------------------
/// @brief option settings

#define Opts_Reset         "0"  // 重置
#define Opts_Bold          "1"  // 加粗
#define Opts_Fuzzy         "2"  // 模糊
#define Opts_Italic        "3"  // 斜体
#define Opts_Underscore    "4"  // 下划线
#define Opts_Blink         "5"  // 闪烁
#define Opts_FastBlink     "6"  // 快闪(快速闪烁)
#define Opts_Reverse       "7"  // 反显
#define Opts_Concealed     "8"  // 消隐
#define Opts_Strikethrough "9"  // 删除线

///-------------------------------
/// @brief console

#define __FmtCat__         ";"  // connect

#define FmtSet(fmt)        "\x1b[" fmt "m"
#define FmtRst()           FmtSet(Opts_Reset)  // 黑底白字

///-------------------------------

#include <stdio.h>

int main(int argc, char* argv[])
{
    system("color 0");

    FmtRst();

    printf(FmtSet("0;94") "hello 0" FmtRst() "\n");
    printf(FmtSet("1;94") "hello 1" FmtRst() "\n");
    printf(FmtSet("1;94") "hello 2" FmtRst() "\n");
    printf(FmtSet("3;94") "hello 3" FmtRst() "\n");
    printf(FmtSet("4;94") "hello 4" FmtRst() "\n");
    printf(FmtSet("5;94") "hello 5" FmtRst() "\n");
    printf(FmtSet("6;94") "hello 6" FmtRst() "\n");
    printf(FmtSet("7;94") "hello 7" FmtRst() "\n");
    printf(FmtSet("8;94") "hello 8" FmtRst() "\n");
    printf(FmtSet("9;94") "hello 9" FmtRst() "\n");

    return 0;
}
