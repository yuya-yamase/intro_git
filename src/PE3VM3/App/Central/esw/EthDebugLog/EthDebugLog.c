/* -------------------------------------------------------------------------- */
/* file name   : EthDebugLog.c                                                     */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
#include <EthDebugLog_Cfg.h>
/* -------------------------------------------------------------------------- */
void EthDebugLog_Init(void)
{
    uint32 idx;

    for(idx = 0; idx < D_ETHDEBUGLOG_INITFUNC_NUM; idx++) {
        G_ETHDEBUGLOG_INITLIST[idx]();
    }
    
    return;
}
/* -------------------------------------------------------------------------- */
void EthDebugLog_Notify(const uint32 EventId)
{
    if (EventId < D_ETHDEBUGLOG_EVENT_NUM) {
        if (G_ETHDEBUGLOG_NOTIFYLIST[EventId] != NULL_PTR) {
            G_ETHDEBUGLOG_NOTIFYLIST[EventId]();
        }
    }
    return;
}
/* -------------------------------------------------------------------------- */
