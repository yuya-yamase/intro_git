/* -------------------------------------------------------------------------- */
/* file name   : EthDebugLog_StartUp.c                                        */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
#include <EthDebugLog_Cfg.h>
/* -------------------------------------------------------------------------- */
static uint32 G_StartUp_Notified[E_ETHDEBUGLOG_EV_NUM];
/* -------------------------------------------------------------------------- */
void EthDebugLog_StartUp_Init(void)
{
    uint32  idx;

    for(idx = 0u; idx < E_ETHDEBUGLOG_EV_NUM; idx++) {
        G_StartUp_Notified[idx] = STD_OFF;
    }
    
    return;
}
/* -------------------------------------------------------------------------- */
void EthDebugLog_StartUp_LinkUpReady(void)
{
    const uint32    idx = E_ETHDEBUGLOG_EV_LINKUPREADY;

    if (G_StartUp_Notified[idx] != STD_ON) {
        G_StartUp_Notified[idx] = STD_ON;
        EthDebugLog_Nofity_SWICINIT();
    }

    return;
}
/* -------------------------------------------------------------------------- */
