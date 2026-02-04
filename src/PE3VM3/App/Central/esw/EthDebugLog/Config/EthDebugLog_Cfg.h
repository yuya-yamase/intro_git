/* -------------------------------------------------------------------------- */
/* file name   : EthDebugLog_Cfg.h                                            */
/* -------------------------------------------------------------------------- */
#ifndef ETHDEBUGLOG_CFG_H
#define ETHDEBUGLOG_CFG_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
#include <EthDebugLog_StartUp.h>
/* #include <PwrCtrl_Main.h> */
/* -------------------------------------------------------------------------- */
#define D_ETHDEBUGLOG_EVENT_SWICINIT                        (0U)
#define D_ETHDEBUGLOG_EVENT_ETHCHPOWERON                    (1U)
#define D_ETHDEBUGLOG_EVENT_LINKUPREADY                     (2U)
#define D_ETHDEBUGLOG_EVENT_ADCLINKUP                       (3U)
#define D_ETHDEBUGLOG_EVENT_DCMLINKUP                       (4U)
#define D_ETHDEBUGLOG_EVENT_DLCLINKUP                       (5U)
#define D_ETHDEBUGLOG_EVENT_LINUXLINKUP                     (6U)
#define D_ETHDEBUGLOG_EVENT_ANDROIDLINKUP                   (7U)
#define D_ETHDEBUGLOG_EVENT_ACTLON                          (8U)
#define D_ETHDEBUGLOG_EVENT_DLCREADY                        (9U)
#define D_ETHDEBUGLOG_EVENT_NUM                             (10U)

#define EthDebugLog_Nofity_SWICINIT()       /* vd_g_PwrCtrlMainBootLogEthLinkup(PWRCTRL_MAIN_ETH_LINKUP_NODETECT) */

/* -------------------------------------------------------------------------- */
typedef void (*EthDebugLog_InitFunc)(void);
const EthDebugLog_InitFunc G_ETHDEBUGLOG_INITLIST[] = 
{
    EthDebugLog_StartUp_Init
};
#define D_ETHDEBUGLOG_INITFUNC_NUM     (sizeof(G_ETHDEBUGLOG_INITLIST) / sizeof(G_ETHDEBUGLOG_INITLIST[0]))

typedef void (*EthDebugLog_Nofity_Func)();
static const EthDebugLog_Nofity_Func G_ETHDEBUGLOG_NOTIFYLIST[D_ETHDEBUGLOG_EVENT_NUM] =
{
    NULL_PTR                                /*  D_ETHDEBUGLOG_EVENT_SWICINIT        */
,   NULL_PTR                                /*  D_ETHDEBUGLOG_EVENT_ETHCHPOWERON    */
,   EthDebugLog_StartUp_LinkUpReady         /*  D_ETHDEBUGLOG_EVENT_LINKUPREADY     */
,   NULL_PTR                                /*  D_ETHDEBUGLOG_EVENT_ADCLINKUP       */
,   NULL_PTR                                /*  D_ETHDEBUGLOG_EVENT_DCMLINKUP       */
,   NULL_PTR                                /*  D_ETHDEBUGLOG_EVENT_DLCLINKUP       */
,   NULL_PTR                                /*  D_ETHDEBUGLOG_EVENT_LINUXLINKUP     */
,   NULL_PTR                                /*  D_ETHDEBUGLOG_EVENT_ANDROIDLINKUP   */
,   NULL_PTR                                /*  D_ETHDEBUGLOG_EVENT_ACTLON          */
,   NULL_PTR                                /*  D_ETHDEBUGLOG_EVENT_DLCREADY        */
};
/* -------------------------------------------------------------------------- */
#endif/* ETHDEBUGLOG_CFG_H */
