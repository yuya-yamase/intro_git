#include <Std_Types.h>
#include <EthSwt_StubDriver.h>
#include <EthSwt_SWIC_PWR.h>

volatile static uint8 EthSwt_StartReq = STD_OFF;
volatile static uint8 EthSwt_StopReq = STD_OFF;
volatile static Std_ReturnType EthSwt_EthChPwr = STD_OFF;

void EthSwt_StubDriver_LoProc (void)
{
    if (EthSwt_StartReq == STD_ON)
    {
        EthSwt_StartReq = STD_OFF;
        EthSwt_SWIC_PWR_PowerOnReq();
    }

    if (EthSwt_StopReq == STD_ON)
    {
        EthSwt_StopReq = STD_OFF;
        EthSwt_SWIC_PWR_PowerOffReq();
    }

    return;
}

Std_ReturnType u1_g_VISPwrGetEthChPwr (void)
{
    return EthSwt_EthChPwr;
}