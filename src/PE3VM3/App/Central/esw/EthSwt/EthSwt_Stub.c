#include <Std_Types.h>
#include <EthSwt_Stub.h>
#include <EthSwt_SWIC_PWR.h>

volatile static uint8 EthSwt_Stub_StartReq = STD_OFF;
volatile static uint8 EthSwt_Stub_StopReq = STD_OFF;

void EthSwt_Stub_LoProc (void)
{
    if (EthSwt_Stub_StartReq == STD_ON)
    {
        EthSwt_Stub_StartReq = STD_OFF;
        EthSwt_SWIC_PWR_PowerOnReq();
    }

    if (EthSwt_Stub_StopReq == STD_ON)
    {
        EthSwt_Stub_StopReq = STD_OFF;
        EthSwt_SWIC_PWR_PowerOffReq();
    }

    return;
}