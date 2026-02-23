/* EthDebugLog_StartUp.c専用ヘッダファイル */

/* -------------------------------------------------------------------------- */
/* file name   : EthDebugLog_StartUp_Cfg.h                                    */
/* -------------------------------------------------------------------------- */
#ifndef ETHDEBUGLOG_STARTUP_CFG_H
#define ETHDEBUGLOG_STARTUP_CFG_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
#include <PwrCtrl_Main.h>
/* -------------------------------------------------------------------------- */

#define EthDebugLog_Nofity_SWICINIT()           vd_g_PwrCtrlMainBootLogEthLinkup(PWRCTRL_MAIN_ETH_LINKUP_DETECT)

/* -------------------------------------------------------------------------- */
#endif/* ETHDEBUGLOG_STARTUP_CFG_H */
