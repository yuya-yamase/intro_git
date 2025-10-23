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
static Std_ReturnType ethswt_swic_qci_read (uint32 * const errFactor);
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Qci_Init (void)
{
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
void EthSwt_SWIC_Qci_Clear (void)
{
    LIB_DI();
    swicGetQciTimer.time = 0;
    swicGetQciTimer.req = STD_ON;
    LIB_EI();

    return;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_Qci_ReadDiscard (uint32 * const errFactor)
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
        result = ethswt_swic_qci_read(errFactor);
    }

    return result;
}
/* -------------------------------------------------------------------------- */
static Std_ReturnType ethswt_swic_qci_read (uint32 * const errFactor)
{
    Std_ReturnType	result;
    uint8           idx;
    uint32          val = 0uL;

    for (idx = 0u; idx < D_ETHSWT_SWIC_QCI_ID_NUM; idx++) {
        result = EthSwt_SWIC_Reg_SetTbl(G_ETHSWT_SWIC_MIB_TABLE_LIST[idx].tbl, G_ETHSWT_SWIC_MIB_TABLE_LIST[idx].num, &val, errFactor);
        if (result != E_OK) {break;}
        
        ETHSWT_SWIC_QCI_NOTIFY(idx, val);
    }

    return result;
}
