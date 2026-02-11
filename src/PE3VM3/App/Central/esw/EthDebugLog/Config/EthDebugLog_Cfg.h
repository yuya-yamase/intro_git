/* EthDebugLog.c専用ヘッダファイル */

/* -------------------------------------------------------------------------- */
/* file name   : EthDebugLog_Cfg.h                                            */
/* -------------------------------------------------------------------------- */
#ifndef ETHDEBUGLOG_CFG_H
#define ETHDEBUGLOG_CFG_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
#include <EthDebugLog.h>
#include <EthDebugLog_StartUp.h>
/* -------------------------------------------------------------------------- */
typedef void (*EthDebugLog_InitFunc)(void);
const EthDebugLog_InitFunc G_ETHDEBUGLOG_INITLIST[] = 
{
    EthDebugLog_StartUp_Init
};
#define D_ETHDEBUGLOG_INITFUNC_NUM     (sizeof(G_ETHDEBUGLOG_INITLIST) / sizeof(G_ETHDEBUGLOG_INITLIST[0]))

typedef void (*EthDebugLog_Nofity_Func)(void);
static const EthDebugLog_Nofity_Func G_ETHDEBUGLOG_NOTIFYLIST[E_ETHDEBUGLOG_EV_NUM] =
{
    NULL_PTR                                /*  E_ETHDEBUGLOG_EV_SWICINIT        */
,   NULL_PTR                                /*  E_ETHDEBUGLOG_EV_ETHCHPOWERON    */
,   EthDebugLog_StartUp_LinkUpReady         /*  E_ETHDEBUGLOG_EV_LINKUPREADY     */
,   NULL_PTR                                /*  E_ETHDEBUGLOG_EV_ADCLINKUP       */
,   NULL_PTR                                /*  E_ETHDEBUGLOG_EV_DCMLINKUP       */
,   NULL_PTR                                /*  E_ETHDEBUGLOG_EV_DLCLINKUP       */
,   NULL_PTR                                /*  E_ETHDEBUGLOG_EV_LINUXLINKUP     */
,   NULL_PTR                                /*  E_ETHDEBUGLOG_EV_ANDROIDLINKUP   */
,   NULL_PTR                                /*  E_ETHDEBUGLOG_EV_ACTLON          */
,   NULL_PTR                                /*  E_ETHDEBUGLOG_EV_DLCREADY        */
};
/* -------------------------------------------------------------------------- */
#endif/* ETHDEBUGLOG_CFG_H */
