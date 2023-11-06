#ifndef __APP_H__
#define __APP_H__

#include "./usdk.h"

#define ARRAY_SIZE(arr) sizeof(arr) / sizeof(*arr)
#include <stdint.h>
#include <stdbool.h>

#define nullptr 0
#include "stdio.h"

//

#define APP_DEFAULT   0
#define APP_OPENLOOP  1
#define APP_CLOSELOOP 2

typedef void (*app_cbk_t)(void*);

typedef enum {
    // system callback
    APP_CBK_ENTER,
    APP_CBK_EXIT,
    _app_sys_cbk_cnt,
    // user callback
    APP_CBK_ISR = _app_sys_cbk_cnt,
    APP_CBK_CYCLE,
    // ...
} app_cbk_e;

typedef uint8_t app_sel_t;

typedef struct {
    const char* szName;
    app_cbk_t*  aCbks;  // array
    uint8_t     nCbkCnt;
    void*       pArgs;
} app_attr_t;

typedef struct {
    app_attr_t* aApps;  // array
    app_sel_t   nAppIdx;
    app_sel_t   nAppCnt;
} app_list_t;

extern app_cbk_t aAppCbksDef[2];

void        AppInit(app_list_t* pAppList);
void        AppCall(app_list_t* pAppList, app_cbk_e eCbkSel);
bool        AppSwitch(app_list_t* pAppList, app_sel_t nAppSel);
void        AppCheck(app_list_t* pAppList, app_cbk_e eCbkSel);
const char* AppGetCurName(app_list_t* pAppList);

#endif  // !__APP_H__