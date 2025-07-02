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
    volatile Std_ReturnType             getLinkResult;      /* 旧 lnk_err */
    volatile EthTrcv_LinkStateType      linkStatus;         /* 旧 lnk_sts */
    uint8                               linkCheck;          /* 旧 lnk_chk */
    EthTrcv_LinkStateType               expectedLinkStatus; /* 旧 lnk_exp */
    uint16                              linkTime;           /* 旧 lnk_tim */
    uint16                              linkTimeout;        /* 旧 lnk_tmo */
} swicLink[D_ETHSWT_SWIC_PORT_NUM];

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
    LIB_DI();
    swicGetLinkTimer.req    = STD_ON;
    LIB_EI();

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
    Std_ReturnType result = E_OK;
    uint8 idx;
    uint8 req;

    LIB_DI();
    req = swicGetLinkTimer.req;
    LIB_EI();
    
    if(req == STD_ON) {
        LIB_DI();
        swicGetLinkTimer.req = STD_OFF;             /* ここまでにSTD_ONされたとしても、100ms間隔になるため問題なし */
        LIB_EI();
        for (idx = 0u; idx < D_ETHSWT_SWIC_PORT_NUM; idx++) {
            result = swic_Reg_GetLinkState(idx, errFactor);
            if (result == E_NOT_OK) {break;}
        }
    }

    return result;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_Link_FastGet (uint32 * const errFactor)
{
    Std_ReturnType result = E_OK;
    uint8 idx;
    uint16 timeDiff;
    uint16 time;

    for (idx = 0u; idx < D_ETHSWT_SWIC_PORT_NUM; idx++) {
        if (swicLink[idx].linkCheck != STD_ON) { continue; }
        LIB_DI();
        time = EthSwt_SWIC_Time_Get();
        LIB_EI();
        timeDiff = time - swicLink[idx].linkTime;
        if (timeDiff > swicLink[idx].linkTimeout) {
            swicLink[idx].linkCheck = STD_OFF;
        }
        result = swic_Reg_GetLinkState(idx, errFactor);
        if (result == E_NOT_OK) {break;}
    }
    
    return result;
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
    if (SwitchPortIdx < D_ETHSWT_SWIC_PORT_NUM) {
        swicLink[SwitchPortIdx].linkCheck = STD_ON;
        swicLink[SwitchPortIdx].expectedLinkStatus = LinkState;
        LIB_DI();
        swicLink[SwitchPortIdx].linkTime = EthSwt_SWIC_Time_Get();
        LIB_EI();
        swicLink[SwitchPortIdx].linkTimeout = tmo;
    }

    return;
}
/* -------------------------------------------------------------------------- */
static Std_ReturnType swic_Reg_GetLinkState(const uint8 SwitchPortIdx, uint32 * const errFactor)
{
    Std_ReturnType			result = E_OK;
	EthTrcv_LinkStateType	sts;
	result = swic_Reg_GetLink(SwitchPortIdx, &sts, errFactor);
	if (result == E_OK) {
        LIB_DI();
        swicLink[SwitchPortIdx].linkStatus = sts;
        swicLink[SwitchPortIdx].getLinkResult = result;
        LIB_EI();
		if (swicLink[SwitchPortIdx].linkCheck != STD_OFF && sts == swicLink[SwitchPortIdx].expectedLinkStatus) {
            swicLink[SwitchPortIdx].linkCheck = STD_OFF;
        }		
	} else {					/* アクセス失敗はリンク取得結果をE_NOT_OKにする */
        LIB_DI();
        swicLink[SwitchPortIdx].getLinkResult = result;
        LIB_EI();
    }
    return result;
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