/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_Time.c                                           */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_Cfg.h>
#include "EthSwt_SWIC_Time.h"
#include "EthSwt_SWIC_Define.h"
#include <LIB.h>
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
    S_ETHSWT_TIME += D_ETHSWT_SWIC_PERIOD;      /* 最大値に達した場合、ラップアラウンドする */

    return;
}
/* -------------------------------------------------------------------------- */
uint32 EthSwt_SWIC_Time_GetCurrentTime(void)
{
    uint32 current;

    LIB_DI();
    current = S_ETHSWT_TIME;
    LIB_EI();

    return current;
}
/* -------------------------------------------------------------------------- */
uint32 EthSwt_SWIC_Time_GetPastTime(uint32 start)
{
    uint32 current;
    uint32 past;

    LIB_DI();
    current = S_ETHSWT_TIME;
    LIB_EI();

    if (start <= current)
    {
        past = current - start;
    }
    else
    {
        past = (0xFFFFFFFFU - start) + current + 1U;
    }

    return past;
}
