/* -------------------------------------------------------------------------- */
/* file name   : EthDebugLog_StartUp.c                                        */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
#include <EthDebugLog_Cfg.h>
/* -------------------------------------------------------------------------- */
static uint32 G_StartUp_LinkUpReady_Notify;
/* -------------------------------------------------------------------------- */
void EthDebugLog_StartUp_Init(void)
{
    G_StartUp_LinkUpReady_Notify = STD_OFF;
    
    return;
}
/* -------------------------------------------------------------------------- */
void EthDebugLog_StartUp_LinkUpReady(void)
{
    if (G_StartUp_LinkUpReady_Notify != STD_ON) {
        G_StartUp_LinkUpReady_Notify = STD_ON;
        EthDebugLog_Nofity_SWICINIT();
    }

    return;
}
/* -------------------------------------------------------------------------- */
