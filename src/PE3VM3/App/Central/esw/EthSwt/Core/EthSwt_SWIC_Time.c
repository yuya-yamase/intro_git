/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_Time.c                                           */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_Cfg.h>
#include "EthSwt_SWIC_Time.h"
/* -------------------------------------------------------------------------- */
volatile static uint32  S_ETHSWT_TIME;
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Time_Init(void)
{
    S_ETHSWT_TIME = 0;

    return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Time_HiProc(void)
{
    if (S_ETHSWT_TIME > (0xFFFFFFFF - D_ETHSWT_SWIC_PERIOD)) {
        S_ETHSWT_TIME = D_ETHSWT_SWIC_PERIOD - (0xFFFFFFFF - S_ETHSWT_TIME) - 1;
    } else {
        S_ETHSWT_TIME = S_ETHSWT_TIME + D_ETHSWT_SWIC_PERIOD;
    }

    return;
}
/* -------------------------------------------------------------------------- */
uint32 EthSwt_SWIC_Time_Get(void)
{
    return S_ETHSWT_TIME;
}
