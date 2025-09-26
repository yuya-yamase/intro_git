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
static S_ETHSWT_SWIC_MIB_COUNT G_ETHSWT_SWIC_MIB_LIST[D_ETHSWT_SWIC_PORT_NUM][D_ETHSWT_SWIC_MIB_NUM];

/* -------------------------------------------------------------------------- */
static Std_ReturnType ethswt_swic_mib_captureAndClear (const uint8 SwitchPortIdx, uint32 * const errFactor);
static Std_ReturnType ethswt_swic_mib_readMIB (const uint8 SwitchPortIdx, uint32 * const errFactor);
static Std_ReturnType ethswt_swic_mib_addVal (uint32 *const num, const swic_reg_data_t tbl[], const uint32 cnt, uint32 * const errFactor);
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_MIB_Init (void)
{
    LIB_memset((uint8*)&G_ETHSWT_SWIC_MIB_LIST, 0, sizeof(G_ETHSWT_SWIC_MIB_LIST));
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
    LIB_DI();
    LIB_memset((uint8*)&G_ETHSWT_SWIC_MIB_LIST, 0, sizeof(G_ETHSWT_SWIC_MIB_LIST));
    swicGetMIBTimer.time = 0;
    swicGetMIBTimer.req = STD_ON;
    LIB_EI();
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthtSwt_SWIC_MIB_ReadDiscard (uint32 * const errFactor)
{
    uint8 idx;
    Std_ReturnType	result = E_OK;      /* MIB読み出しポートがない場合は、E_OKで終了させる */

    for (idx = 0u; idx < D_ETHSWT_SWIC_PORT_NUM; idx++) {
        if (G_ETHSWT_SWIC_MIB_VAILD[idx] == STD_ON) {
            result = ethswt_swic_mib_captureAndClear(idx, errFactor);
        }
    }
    
    return result;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_MIB_Action (uint32 * const errFactor)
{
    Std_ReturnType result = E_OK;
    uint8 idx;
    uint8 req;

    LIB_DI();
    req = swicGetMIBTimer.req;
    LIB_EI();

    if(req == STD_ON) {
        LIB_DI();
        swicGetMIBTimer.req = STD_OFF;
        LIB_EI();
        for (idx = 0u; idx < D_ETHSWT_SWIC_PORT_NUM; idx++) {
            if (G_ETHSWT_SWIC_MIB_VAILD[idx] == STD_ON) {
                result = ethswt_swic_mib_readMIB(idx, errFactor);
                if (result == E_NOT_OK) {break;}
            }
        }
    }

    return result;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_MIB_Get(uint8 SwitchPortIdx, uint32 Mib, S_ETHSWT_SWIC_MIB_COUNT *MibCountPtr)
{
    Std_ReturnType ret = E_NOT_OK;
    EthSwt_StateType status;
    status = EthSwt_SWIC_STM_GetStatus();

    do {
        if (status != ETHSWT_STATE_ACTIVE)	            { break; }
        if (SwitchPortIdx >= D_ETHSWT_SWIC_PORT_NUM)	{ break; }
        if (Mib >= D_ETHSWT_SWIC_MIB_NUM)               { break; }
        if (MibCountPtr == NULL_PTR)					{ break; }
        MibCountPtr->IngressCount = G_ETHSWT_SWIC_MIB_LIST[SwitchPortIdx][Mib].IngressCount;
        G_ETHSWT_SWIC_MIB_LIST[SwitchPortIdx][Mib].IngressCount = 0;
        MibCountPtr->EgressCount = G_ETHSWT_SWIC_MIB_LIST[SwitchPortIdx][Mib].EgressCount;
        G_ETHSWT_SWIC_MIB_LIST[SwitchPortIdx][Mib].EgressCount = 0;
        
        ret = E_OK;

    } while (0);
	
	return ret;
}
/* -------------------------------------------------------------------------- */
static Std_ReturnType ethswt_swic_mib_captureAndClear (const uint8 SwitchPortIdx, uint32 * const errFactor)
{
    Std_ReturnType	result;
    uint32			val = 0uL;

    result = EthSwt_SWIC_Reg_SetTbl(G_ETHSWT_SWIC_MIB_SELECT_PORT[SwitchPortIdx].tbl, G_ETHSWT_SWIC_MIB_SELECT_PORT[SwitchPortIdx].num, &val, errFactor);

    return result;
}
/* -------------------------------------------------------------------------- */
static Std_ReturnType ethswt_swic_mib_readMIB (const uint8 SwitchPortIdx, uint32 * const errFactor)
{
    Std_ReturnType	result;
    uint8           idx;

    do {
        result = ethswt_swic_mib_captureAndClear(SwitchPortIdx, errFactor);
        if (result != E_OK) {break;}
        for (idx = 0u; idx < D_ETHSWT_SWIC_MIB_NUM; idx++) {
            result = ethswt_swic_mib_addVal(&G_ETHSWT_SWIC_MIB_LIST[SwitchPortIdx][idx].IngressCount, G_ETHSWT_SWIC_MIB_TABLE_LIST[idx].tbl, G_ETHSWT_SWIC_MIB_TABLE_LIST[idx].num, errFactor);
            if (result != E_OK) {break;}
        }
    } while (0);

    return result;
}
/* -------------------------------------------------------------------------- */
static Std_ReturnType ethswt_swic_mib_addVal (uint32 *const num, const swic_reg_data_t tbl[], const uint32 cnt, uint32 * const errFactor)
{
    Std_ReturnType  result;
    uint32          val = 0uL;
    
    result = EthSwt_SWIC_Reg_SetTbl(tbl, cnt, &val, errFactor);
    if (result == E_OK) {
        LIB_DI();
        *num = (((~0uL) - *num) >= val) ? *num + val : ~0uL;
        LIB_EI();
    }
    
    return result;
}
