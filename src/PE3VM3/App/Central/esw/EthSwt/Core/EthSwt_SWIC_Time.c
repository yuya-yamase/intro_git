/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_Time.c                                           */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_Cfg.h>
#include "EthSwt_SWIC_Time.h"
/* -------------------------------------------------------------------------- */
volatile static uint16  S_ETHSWT_TIME;
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Time_Init(void)
{
    S_ETHSWT_TIME = 0;

    return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Time_HiProc(void)
{
    S_ETHSWT_TIME = S_ETHSWT_TIME + D_ETHSWT_SWIC_PERIOD;

    return;
}
/* -------------------------------------------------------------------------- */
uint16 EthSwt_SWIC_Time_Get(void)
{
    return S_ETHSWT_TIME;
}
