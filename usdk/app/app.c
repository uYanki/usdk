#include "app.h"

//

static void ecbAppEnter(void* args);
static void ecbAppExit(void* args);

app_cbk_t aAppCbksDef[2] = {ecbAppEnter, ecbAppExit};

//

void AppInit(app_list_t* pAppList)
{
    if (pAppList->nAppIdx >= pAppList->nAppCnt)
    {
        pAppList->nAppIdx = 0;
    }

    if (pAppList->nAppCnt > 0)
    {
        AppCall(pAppList, APP_CBK_ENTER);
    }
}

const char* AppGetCurName(app_list_t* pAppList)
{
    return pAppList->aApps[pAppList->nAppIdx].szName;
}

bool AppCheck(app_list_t* pAppList, app_cbk_e eCbkSel)
{
    return pAppList->nAppIdx == eCbkSel;
}

void AppCall(app_list_t* pAppList, app_cbk_e eCbkSel)
{
    app_attr_t* pApp = &pAppList->aApps[pAppList->nAppIdx];

    if (eCbkSel < pApp->nCbkCnt)
    {
        if (nullptr != pApp->aCbks[eCbkSel])
        {
            (pApp->aCbks[eCbkSel])(pApp->pArgs);
        }
    }
}

bool AppSwitch(app_list_t* pAppList, app_sel_t nAppSel)
{
    if (nAppSel >= pAppList->nAppCnt)
    {
        return false;
    }

    if (nAppSel == pAppList->nAppIdx)
    {
        return true;
    }

    AppCall(pAppList, APP_CBK_EXIT);
    pAppList->nAppIdx = nAppSel;
    AppCall(pAppList, APP_CBK_ENTER);

    return true;
}

static void ecbAppEnter(void* args)
{
    printf("app: %s enter\n", AppGetCurName(&gAppList));
}

static void ecbAppExit(void* args)
{
    printf("app: %s exit\n", AppGetCurName(&gAppList));
}

//-----------------------------------------------------------------------------
//

app_attr_t gApps[] = {
  // [APP_DEFAULT] = {  .szName = "Default", .aCbks = aAppCbks, .nCbkCnt = ARRAY_SIZE(aAppCbks), .pArgs = nullptr},
    [APP_DEFAULT]   = {.szName = "Default",   .aCbks = (app_cbk_t[]){ecbAppEnter, ecbAppExit}, .nCbkCnt = 2, .pArgs = nullptr},
    [APP_OPENLOOP]  = {.szName = "OpenLoop",  .aCbks = (app_cbk_t[]){ecbAppEnter, ecbAppExit}, .nCbkCnt = 2, .pArgs = nullptr},
    [APP_CLOSELOOP] = {.szName = "CloseLoop", .aCbks = (app_cbk_t[]){ecbAppEnter, ecbAppExit}, .nCbkCnt = 2, .pArgs = nullptr},
};

app_list_t gAppList = {.aApps = gApps, .nAppIdx = APP_DEFAULT, .nAppCnt = ARRAY_SIZE(gApps)};

int main()
{
    AppInit(&gAppList);
    AppSwitch(&gAppList, 0);
    AppSwitch(&gAppList, 1);
    AppSwitch(&gAppList, 2);
    return 0;
}