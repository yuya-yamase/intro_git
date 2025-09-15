/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_Qci.c                                           */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_Cfg.h>
#include "EthSwt_SWIC_Qci.h"
#include "EthSwt_SWIC_Reg.h"
#include <LIB.h>
#include <EthSwt_SWIC_Qci_Cfg.h>
#include <EthSwt_SWIC_initRegCommon.h>
#include "EthSwt_SWIC_STM.h"
#include "EthSwt_SWIC_Define.h"
/* -------------------------------------------------------------------------- */
static struct {
    sint32                              time;
    volatile uint8                      req;
} swicGetQciTimer;
/* -------------------------------------------------------------------------- */
static uint32 G_ETHSWT_SWIC_QCI_COUNT[D_ETHSWT_SWIC_QCI_ID_NUM];
/* -------------------------------------------------------------------------- */
static Std_ReturnType ethswt_swic_qci_readQci (uint32 * const errFactor);
static Std_ReturnType ethswt_swic_qci_addVal (uint32 *const num, const swic_reg_data_t tbl[], const uint32 cnt, uint32 * const errFactor);
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Qci_Init (void)
{
    LIB_memset((uint8*)&G_ETHSWT_SWIC_QCI_COUNT, 0, sizeof(G_ETHSWT_SWIC_QCI_COUNT));
    swicGetQciTimer.time = 0;
    swicGetQciTimer.req = STD_ON;

    return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Qci_TimerUpdate (void)
{
    swicGetQciTimer.time = swicGetQciTimer.time + D_ETHSWT_SWIC_PERIOD;
    if (swicGetQciTimer.time >= D_ETHSWT_SWIC_QCI_GET_CYCLE) {
        swicGetQciTimer.time = swicGetQciTimer.time - D_ETHSWT_SWIC_QCI_GET_CYCLE;
        swicGetQciTimer.req = STD_ON;
    }
    
    return;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_Qci_Clear (uint32 * const errFactor)
{
    uint8 idx;
    uint32          val = 0uL;
    Std_ReturnType	result = E_OK;      /* QciëŒè€Ç™Ç»Ç¢èÍçáÇÕÅAE_OKÇ≈èIóπÇ≥ÇπÇÈ */

    do {
        for (idx = 0u; idx < D_ETHSWT_SWIC_QCI_ID_NUM; idx++) {
            result = EthSwt_SWIC_Reg_SetTbl(G_ETHSWT_SWIC_MIB_TABLE_LIST[idx].tbl, G_ETHSWT_SWIC_MIB_TABLE_LIST[idx].num, &val, errFactor);
            if (result != E_OK) {break;}
        }
    } while (0);
    
    return result;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_Qci_Action (uint32 * const errFactor)
{
    Std_ReturnType result = E_OK;
    uint8 req;

    LIB_DI();
    req = swicGetQciTimer.req;
    LIB_EI();

    if(req == STD_ON) {
        LIB_DI();
        swicGetQciTimer.req = STD_OFF;
        LIB_EI();
        result = ethswt_swic_qci_readQci(errFactor);
    }

    return result;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_Qci_Get(uint32 * const QciInfoPtr)
{
    Std_ReturnType ret = E_NOT_OK;
    EthSwt_StateType status;
    status = EthSwt_SWIC_STM_GetStatus();

    do {
        if (status != ETHSWT_STATE_ACTIVE)	            { break; }
        if (QciInfoPtr == NULL_PTR)					{ break; }
        LIB_memcpy((uint8*)QciInfoPtr, (uint8*)&G_ETHSWT_SWIC_QCI_COUNT, sizeof(G_ETHSWT_SWIC_QCI_COUNT));

    } while (0);
	
	return ret;

}
/* -------------------------------------------------------------------------- */
static Std_ReturnType ethswt_swic_qci_readQci (uint32 * const errFactor)
{
    Std_ReturnType	result;
    uint8           idx;

    do {
        for (idx = 0u; idx < D_ETHSWT_SWIC_QCI_ID_NUM; idx++) {
            result = ethswt_swic_qci_addVal(&G_ETHSWT_SWIC_QCI_COUNT[idx], G_ETHSWT_SWIC_MIB_TABLE_LIST[idx].tbl, G_ETHSWT_SWIC_MIB_TABLE_LIST[idx].num, errFactor);
            if (result != E_OK) {break;}
        }
    } while (0);

    return result;
}
/* -------------------------------------------------------------------------- */
static Std_ReturnType ethswt_swic_qci_addVal (uint32 *const num, const swic_reg_data_t tbl[], const uint32 cnt, uint32 * const errFactor)
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
