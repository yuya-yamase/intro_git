#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_Core_Cfg.h>
#include "EthSwt_SWIC_Link.h"
#include "EthSwt_SWIC_Reg.h"
#include "EthSwt_SWIC_STM.h"
#include <EthSwt_SWIC_Link_Cfg.h>
/* -------------------------------------------------------------------------- */
static struct {
    volatile Std_ReturnType             getLinkResult;      /* 旧 lnk_err */
    volatile EthTrcv_LinkStateType      linkStatus;         /* 旧 lnk_sts */
    uint8                               linkCheck;          /* 旧 lnk_chk */
    EthTrcv_LinkStateType               expectedLinkStatus; /* 旧 lnk_exp */
    uint16                              linkTime;           /* 旧 lnk_tim */
    uint16                              linkTimeout;        /* 旧 lnk_tmo */
} swicLink[D_ETHSWT_SWIC_PORT_NUM];

volatile static uint16                  timer;

static struct {
    sint32                              time;
    volatile uint8                      req;
} swicGetLinkTimer;

/* -------------------------------------------------------------------------- */
static void ethswt_swic_link_Set(const uint8 SwitchPortIdx, const EthTrcv_LinkStateType LinkState, const uint16 tmo);
static Std_ReturnType swic_Reg_GetLinkState(const uint8 SwitchPortIdx, uint32 * const errFactor);
static Std_ReturnType swic_Reg_GetLink(const uint8 SwitchPortIdx, EthTrcv_LinkStateType *const LinkStatePtr, uint32 * const errFactor);
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Link_Init (void)
{
    uint8   idx;

    timer                   = 0;

    for (idx = 0; idx < D_ETHSWT_SWIC_PORT_NUM; idx++) {
        swicLink[idx].getLinkResult         = E_NOT_OK;
        swicLink[idx].linkStatus            = ETHTRCV_LINK_STATE_DOWN;
        swicLink[idx].linkCheck             = STD_OFF;
        swicLink[idx].expectedLinkStatus    = ETHTRCV_LINK_STATE_DOWN;
        swicLink[idx].linkTime              = 0;
        swicLink[idx].linkTimeout           = 0;
        if (G_ETHSWT_SWIC_PORT_DEFINE[idx] == ETH_MODE_ACTIVE) {
            ethswt_swic_link_Set(idx, ETHTRCV_LINK_STATE_ACTIVE, D_ETHSWT_SWIC_LINK_FAST_GET_TMO);
        }
    }
    swicGetLinkTimer.time   = 0;
    swicGetLinkTimer.req    = STD_ON;

    return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Link_HiProc (void)
{
    timer = timer + D_ETHSWT_SWIC_PERIOD;
	return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Link_Clear (void)
{
    uint8   idx;
    for (idx = 0; idx < D_ETHSWT_SWIC_PORT_NUM; idx++) {
        swicLink[idx].getLinkResult = E_NOT_OK;
        if (swicLink[idx].linkCheck == STD_ON) {
            swicLink[idx].linkTime = timer;
        }
    }
    swicGetLinkTimer.time   = 0;
    swicGetLinkTimer.req    = STD_ON;

    return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Link_ClearGetLinkResult (void)
{
    uint8   idx;
    for (idx = 0; idx < D_ETHSWT_SWIC_PORT_NUM; idx++) {
        swicLink[idx].getLinkResult = E_NOT_OK;
    }

    return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Link_TimerUpdate (void)
{
    swicGetLinkTimer.time = swicGetLinkTimer.time + D_ETHSWT_SWIC_PERIOD;
    if (swicGetLinkTimer.time >= D_ETHSWT_SWIC_LINK_GET_CYCLE) {
        swicGetLinkTimer.time = swicGetLinkTimer.time - D_ETHSWT_SWIC_LINK_GET_CYCLE;
        swicGetLinkTimer.req = STD_ON;
    }
    
    return;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_Link_Action (uint32 * const errFactor)
{
    Std_ReturnType ret = E_OK;
    uint8 idx;

    if (swicGetLinkTimer.req == STD_ON) {
        swicGetLinkTimer.req = STD_OFF;
        for (idx = 0u; idx < D_ETHSWT_SWIC_PORT_NUM; idx++) {
            ret = swic_Reg_GetLinkState(idx, errFactor);
            if (ret == E_NOT_OK) {break;}
        }
    }

    return ret;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_Link_FastGet (uint32 * const errFactor)
{
    Std_ReturnType ret = E_OK;
    uint8 idx;
    uint16 timeout;

    for (idx = 0u; idx < D_ETHSWT_SWIC_PORT_NUM; idx++) {
        if (swicLink[idx].linkCheck != STD_ON) { continue; }
        timeout = timer - swicLink[idx].linkTime;
        if (timeout > swicLink[idx].linkTimeout) {
            swicLink[idx].linkCheck = STD_OFF;
        }
        ret = swic_Reg_GetLinkState(idx, errFactor);
        if (ret == E_NOT_OK) {break;}
    }
    
    return ret;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_Link_GetLinkState(const uint8 SwitchPortIdx, EthTrcv_LinkStateType * const LinkStatePtr)
{
    Std_ReturnType ret = E_NOT_OK;
    EthSwt_StateType status;
    status = EthSwt_SWIC_STM_GetStatus();

    do {
        if (status != ETHSWT_STATE_ACTIVE)	            { break; }
        if (SwitchPortIdx >= D_ETHSWT_SWIC_PORT_NUM)	{ break; }
        if (LinkStatePtr == NULL_PTR)					{ break; }
        *LinkStatePtr = swicLink[SwitchPortIdx].linkStatus;
        ret = swicLink[SwitchPortIdx].getLinkResult;
    } while (0);
	
	return ret;
}
/* -------------------------------------------------------------------------- */
static void ethswt_swic_link_Set(const uint8 SwitchPortIdx, const EthTrcv_LinkStateType LinkState, const uint16 tmo)
{
    /* ★MODE_DOWN時も呼ばれるはず */
    if (SwitchPortIdx < D_ETHSWT_SWIC_PORT_NUM) {
        swicLink[SwitchPortIdx].linkCheck = STD_ON;
        swicLink[SwitchPortIdx].expectedLinkStatus = LinkState;
        swicLink[SwitchPortIdx].linkTime = timer;
        swicLink[SwitchPortIdx].linkTimeout = tmo;
    }

    return;
}
/* -------------------------------------------------------------------------- */
static Std_ReturnType swic_Reg_GetLinkState(const uint8 SwitchPortIdx, uint32 * const errFactor)
{
    Std_ReturnType			err;
	EthTrcv_LinkStateType	sts;
	err = swic_Reg_GetLink(SwitchPortIdx, &sts, errFactor);
	if (err == E_OK) {
        swicLink[SwitchPortIdx].linkStatus = sts;
        swicLink[SwitchPortIdx].getLinkResult = err;
		if (swicLink[SwitchPortIdx].linkCheck != STD_OFF && sts == swicLink[SwitchPortIdx].expectedLinkStatus) {
            swicLink[SwitchPortIdx].linkCheck = STD_OFF;
        }		
	} else {					/* アクセス失敗はリンク取得結果をE_NOT_OKにする */
        swicLink[SwitchPortIdx].getLinkResult = err;
    }
    return err;
}
/* -------------------------------------------------------------------------- */
static Std_ReturnType swic_Reg_GetLink(const uint8 SwitchPortIdx, EthTrcv_LinkStateType *const LinkStatePtr, uint32 * const errFactor)
{
	Std_ReturnType	result = E_NOT_OK;
	uint32			val = 0uL;
    do {
        if (SwitchPortIdx >= (sizeof(G_ETHSWT_SWIC_GET_LINK_TABLE)/sizeof(G_ETHSWT_SWIC_GET_LINK_TABLE[0])))	{ break; }
        if (LinkStatePtr == NULL_PTR)			{ break; }
        result = EthSwt_SWIC_Reg_SetTbl(G_ETHSWT_SWIC_GET_LINK_TABLE[SwitchPortIdx].tbl, G_ETHSWT_SWIC_GET_LINK_TABLE[SwitchPortIdx].num, &val, errFactor);
        if (result == E_OK) {
            *LinkStatePtr = ((val & G_ETHSWT_SWIC_GET_LINK_TABLE[SwitchPortIdx].msk) == G_ETHSWT_SWIC_GET_LINK_TABLE[SwitchPortIdx].dat) ? ETHTRCV_LINK_STATE_ACTIVE : ETHTRCV_LINK_STATE_DOWN;
        }
    } while(0);

	return result;
}