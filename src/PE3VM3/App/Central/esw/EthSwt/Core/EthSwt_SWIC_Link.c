/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_Link.c                                           */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_Cfg.h>
#include "EthSwt_SWIC_Link.h"
#include "EthSwt_SWIC_Reg.h"
#include "EthSwt_SWIC_STM.h"
#include <EthSwt_SWIC_Link_Cfg.h>
#include <LIB.h>
#include "EthSwt_SWIC_Time.h"
/* -------------------------------------------------------------------------- */
static struct {
    volatile Std_ReturnType             getLinkResult;
    volatile EthTrcv_LinkStateType      linkState;
} S_ETHSWT_SWIC_LINK[D_ETHSWT_SWIC_PORT_NUM];   /* ÉäÉìÉNèÛë‘éÊìæÇëzíËÇµÇƒRAMéùÇø */

static struct {
    sint32                              time;
    volatile uint8                      req;
} S_ETHSWT_SWIC_LINK_TIMER;

/* -------------------------------------------------------------------------- */
static Std_ReturnType ethswt_swic_link_read(uint32 * const errFactor);
static Std_ReturnType ethswt_swic_link_readPerPort(const uint8 SwitchPortIdx, uint32 * const errFactor);
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Link_Init (void)
{
    uint8 idx;

    S_ETHSWT_SWIC_LINK_TIMER.time = 0;
    S_ETHSWT_SWIC_LINK_TIMER.req = STD_ON;

    for (idx = 0u; idx < D_ETHSWT_SWIC_PORT_NUM; idx++) {
        S_ETHSWT_SWIC_LINK[idx].getLinkResult = E_NOT_OK;
        S_ETHSWT_SWIC_LINK[idx].linkState = ETHTRCV_LINK_STATE_DOWN;
    }

    return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Link_TimerUpdate (void)
{
    S_ETHSWT_SWIC_LINK_TIMER.time = S_ETHSWT_SWIC_LINK_TIMER.time + D_ETHSWT_SWIC_PERIOD;
    if (S_ETHSWT_SWIC_LINK_TIMER.time >= D_ETHSWT_SWIC_LINK_GET_CYCLE) {
        S_ETHSWT_SWIC_LINK_TIMER.time = S_ETHSWT_SWIC_LINK_TIMER.time - D_ETHSWT_SWIC_LINK_GET_CYCLE;
        S_ETHSWT_SWIC_LINK_TIMER.req = STD_ON;
    }
    
    return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Link_Clear (void)
{
    uint8 idx;

    LIB_DI();
    S_ETHSWT_SWIC_LINK_TIMER.time = 0;
    S_ETHSWT_SWIC_LINK_TIMER.req = STD_ON;

    for (idx = 0u; idx < D_ETHSWT_SWIC_PORT_NUM; idx++) {
        S_ETHSWT_SWIC_LINK[idx].getLinkResult = E_NOT_OK;
        S_ETHSWT_SWIC_LINK[idx].linkState = ETHTRCV_LINK_STATE_DOWN;
    }
    LIB_EI();

    for (idx = 0u; idx < D_ETHSWT_SWIC_PORT_NUM; idx++) {
        if (G_ETHSWT_SWIC_LINK_VAILD[idx] == STD_ON) {
            ETHSWT_SWIC_LINK_NOTIFY(idx, E_NOT_OK, ETHTRCV_LINK_STATE_DOWN);
        }
    }
    
    return;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_Link_Action (uint32 * const errFactor)
{
    Std_ReturnType result = E_OK;
    uint8 req;

    LIB_DI();
    req = S_ETHSWT_SWIC_LINK_TIMER.req;
    LIB_EI();
    
    if(req == STD_ON) {
        LIB_DI();
        S_ETHSWT_SWIC_LINK_TIMER.req = STD_OFF; 
        LIB_EI();
        result = ethswt_swic_link_read(errFactor);
    }

    return result;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_Link_Get(const uint8 SwitchPortIdx, EthTrcv_LinkStateType * const LinkStatePtr)
{
    Std_ReturnType ret = E_NOT_OK;
    EthSwt_StateType status;
    status = EthSwt_SWIC_STM_GetStatus();

    do {
        if (status != ETHSWT_STATE_ACTIVE)	            { break; }
        if (SwitchPortIdx >= D_ETHSWT_SWIC_PORT_NUM)	{ break; }
        if (LinkStatePtr == NULL_PTR)					{ break; }
        *LinkStatePtr = S_ETHSWT_SWIC_LINK[SwitchPortIdx].linkState;
        ret = S_ETHSWT_SWIC_LINK[SwitchPortIdx].getLinkResult;
    } while (0);
	
	return ret;
}
/* -------------------------------------------------------------------------- */
static Std_ReturnType ethswt_swic_link_read(uint32 * const errFactor)
{
    Std_ReturnType result = E_NOT_OK;
    uint8 idx;
    
    for (idx = 0u; idx < D_ETHSWT_SWIC_PORT_NUM; idx++) {
        if (G_ETHSWT_SWIC_LINK_VAILD[idx] == STD_ON) {
            result = ethswt_swic_link_readPerPort(idx, errFactor);
            if (result == E_NOT_OK) {break;}
        }
    }

    return result;
}
/* -------------------------------------------------------------------------- */
static Std_ReturnType ethswt_swic_link_readPerPort(const uint8 SwitchPortIdx, uint32 * const errFactor)
{
    Std_ReturnType	        result;
    EthTrcv_LinkStateType   state;
	uint32			        val = 0uL;

    result = EthSwt_SWIC_Reg_SetTbl(G_ETHSWT_SWIC_GET_LINK_TABLE[SwitchPortIdx].tbl, G_ETHSWT_SWIC_GET_LINK_TABLE[SwitchPortIdx].num, &val, errFactor);

    if (result == E_OK) {
        state = ((val & G_ETHSWT_SWIC_GET_LINK_TABLE[SwitchPortIdx].msk) == G_ETHSWT_SWIC_GET_LINK_TABLE[SwitchPortIdx].dat) ? ETHTRCV_LINK_STATE_ACTIVE : ETHTRCV_LINK_STATE_DOWN;
        LIB_DI();
        S_ETHSWT_SWIC_LINK[SwitchPortIdx].getLinkResult = result;
        S_ETHSWT_SWIC_LINK[SwitchPortIdx].linkState = state;
        LIB_EI();

        ETHSWT_SWIC_LINK_NOTIFY(SwitchPortIdx, result, state);
    }

	return result;
}
