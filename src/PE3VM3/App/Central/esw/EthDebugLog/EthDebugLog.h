/* -------------------------------------------------------------------------- */
/* file name   : EthDebugLog.h                                                     */
/* -------------------------------------------------------------------------- */
#ifndef ETHDEBUGLOG_H
#define ETHDEBUGLOG_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
typedef enum {
    E_ETHDEBUGLOG_EV_SWICINIT = 0,
    E_ETHDEBUGLOG_EV_ETHCHPOWERON,
    E_ETHDEBUGLOG_EV_LINKUPREADY,
    E_ETHDEBUGLOG_EV_ADCLINKUP,
    E_ETHDEBUGLOG_EV_DCMLINKUP,
    E_ETHDEBUGLOG_EV_DLCLINKUP,
    E_ETHDEBUGLOG_EV_LINUXLINKUP,
    E_ETHDEBUGLOG_EV_ANDROIDLINKUP,
    E_ETHDEBUGLOG_EV_ACTLON,
    E_ETHDEBUGLOG_EV_DLCREADY,
    E_ETHDEBUGLOG_EV_NUM
} E_ETHDEBUGLOG_EV_LIST;
/* -------------------------------------------------------------------------- */
void EthDebugLog_Init(void);
void EthDebugLog_Notify(const uint32 EventId);
/* -------------------------------------------------------------------------- */
#endif/* ETHDEBUGLOG_H */
