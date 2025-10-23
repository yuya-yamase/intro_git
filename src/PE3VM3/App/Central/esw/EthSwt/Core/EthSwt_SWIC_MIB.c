/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_MIB.c                                           */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_Cfg.h>
#include "EthSwt_SWIC_MIB.h"
#include "EthSwt_SWIC_Reg.h"
#include <LIB.h>
#include "EthSwt_SWIC_Time.h"
#include <EthSwt_SWIC_MIB_Cfg.h>
#include <EthSwt_SWIC_initRegCommon.h>
#include "EthSwt_SWIC_STM.h"
#include "EthSwt_SWIC_Define.h"
/* -------------------------------------------------------------------------- */
static struct {
    sint32                              time;
    volatile uint8                      req;
} swicGetMIBTimer;
/* -------------------------------------------------------------------------- */
static Std_ReturnType ethswt_swic_mib_captureAndClear (const uint8 SwitchPortIdx, uint32 * const errFactor);
static Std_ReturnType ethswt_swic_mib_read (uint32 * const errFactor);
static Std_ReturnType ethswt_swic_mib_readPerPort (const uint8 SwitchPortIdx, uint32 * const errFactor);
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_MIB_Init (void)
{
    swicGetMIBTimer.time = 0;
    swicGetMIBTimer.req = STD_ON;

    return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_MIB_TimerUpdate (void)
{
    swicGetMIBTimer.time = swicGetMIBTimer.time + D_ETHSWT_SWIC_PERIOD;
    if (swicGetMIBTimer.time >= D_ETHSWT_SWIC_MIB_GET_CYCLE) {
        swicGetMIBTimer.time = swicGetMIBTimer.time - D_ETHSWT_SWIC_MIB_GET_CYCLE;
        swicGetMIBTimer.req = STD_ON;
    }
    
    return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_MIB_Clear (void)
{
    uint32 mibArray[D_ETHSWT_SWIC_MIB_NUM];
    uint8 idx;

    LIB_memset((uint8*)&mibArray, 0, sizeof(mibArray));

    LIB_DI();
    swicGetMIBTimer.time = 0;
    swicGetMIBTimer.req = STD_ON;
    LIB_EI();

    for (idx = 0u; idx < D_ETHSWT_SWIC_PORT_NUM; idx++) {
        if (G_ETHSWT_SWIC_MIB_VAILD[idx] == STD_ON) {
            ETHSWT_SWIC_MIB_NOTIFY(idx, mibArray);
        }
    }

    return;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_MIB_ReadDiscard (uint32 * const errFactor)
{
    uint8 idx;
    Std_ReturnType	result = E_OK;      /* MIB読み出しポートがない場合は、E_OKで終了させる */

    for (idx = 0u; idx < D_ETHSWT_SWIC_PORT_NUM; idx++) {
        if (G_ETHSWT_SWIC_MIB_VAILD[idx] == STD_ON) {
            result = ethswt_swic_mib_captureAndClear(idx, errFactor);
        }
        if (result != E_OK) {break;}
    }
    
    return result;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_MIB_Action (uint32 * const errFactor)
{
    Std_ReturnType result = E_OK;
    uint8 req;

    LIB_DI();
    req = swicGetMIBTimer.req;
    LIB_EI();

    if(req == STD_ON) {
        LIB_DI();
        swicGetMIBTimer.req = STD_OFF;
        LIB_EI();
        result = ethswt_swic_mib_read(errFactor);
    }

    return result;
}
/* -------------------------------------------------------------------------- */
static Std_ReturnType ethswt_swic_mib_read (uint32 * const errFactor)
{
    Std_ReturnType result = E_NOT_OK;
    uint8 idx;

    for (idx = 0u; idx < D_ETHSWT_SWIC_PORT_NUM; idx++) {
        if (G_ETHSWT_SWIC_MIB_VAILD[idx] == STD_ON) {
            result = ethswt_swic_mib_readPerPort(idx, errFactor);
            if (result == E_NOT_OK) {break;}
        }
    }

    return result;
}
/* -------------------------------------------------------------------------- */
static Std_ReturnType ethswt_swic_mib_readPerPort (const uint8 SwitchPortIdx, uint32 * const errFactor)
{
    Std_ReturnType result;
    uint8 idx;
    uint32 mibArray[D_ETHSWT_SWIC_MIB_NUM];
    uint32 val = 0uL;

    do {
        result = ethswt_swic_mib_captureAndClear(SwitchPortIdx, errFactor);
        if (result != E_OK) {break;}
        for (idx = 0u; idx < D_ETHSWT_SWIC_MIB_NUM; idx++) {
            result = EthSwt_SWIC_Reg_SetTbl(G_ETHSWT_SWIC_MIB_TABLE_LIST[idx].tbl, G_ETHSWT_SWIC_MIB_TABLE_LIST[idx].num, &val, errFactor);
            if (result != E_OK) {break;}
            mibArray[idx] = val;
        }
    } while (0);

    if (result == E_OK) {
        ETHSWT_SWIC_MIB_NOTIFY(SwitchPortIdx, mibArray);
    }

    return result;
}
/* -------------------------------------------------------------------------- */
static Std_ReturnType ethswt_swic_mib_captureAndClear (const uint8 SwitchPortIdx, uint32 * const errFactor)
{
    Std_ReturnType	result;
    uint32			val = 0uL;

    result = EthSwt_SWIC_Reg_SetTbl(G_ETHSWT_SWIC_MIB_SELECT_PORT[SwitchPortIdx].tbl, G_ETHSWT_SWIC_MIB_SELECT_PORT[SwitchPortIdx].num, &val, errFactor);

    return result;
}
