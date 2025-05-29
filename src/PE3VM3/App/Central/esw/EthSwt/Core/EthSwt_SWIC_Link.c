#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include "EthSwt_SWIC_Link.h"
#include "EthSwt_SWIC_Core_Cfg.h"
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
static void swic_Reg_GetLinkState(const uint8 SwitchPortIdx);
static Std_ReturnType swic_Reg_GetLink(const uint8 SwitchPortIdx, EthTrcv_LinkStateType *const LinkStatePtr);
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
        if (G_ETHSWT_SWIC_PORT_MODE[idx] == ETH_MODE_ACTIVE) {
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
Std_ReturnType EthSwt_SWIC_Link_CheckAction (void)
{
    Std_ReturnType ret = E_NOT_OK;

    if (swicGetLinkTimer.req == STD_ON) {
        swicGetLinkTimer.req = STD_OFF;
        ret = E_OK;
    }

    return ret;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_Link_Action (uint32 * const errFactor)
{
    
    return E_OK;
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
// static void swic_Reg_GetLinkState(const uint8 SwitchPortIdx)
// {
    // Std_ReturnType			err;
	// EthTrcv_LinkStateType	sts;
	// err = swic_Reg_GetLink(SwitchPortIdx, &sts);
	// if (err == E_OK) {	/* アクセス失敗時は更新しない(前回値) */
	// 	swic_Reg_Mode[SwitchPortIdx].lnk_sts = sts;
	// 	swic_Reg_Mode[SwitchPortIdx].lnk_err = err;
	// 	if (swic_Reg_Mode[SwitchPortIdx].lnk_chk == STD_OFF){ return; }
	// 	if (sts != swic_Reg_Mode[SwitchPortIdx].lnk_exp)	{ return; }
	// }					/* アクセス失敗は確認を止める */
	// swic_Reg_Mode[SwitchPortIdx].lnk_chk = STD_OFF;
// }

// static Std_ReturnType swic_Reg_GetLink(const uint8 SwitchPortIdx, EthTrcv_LinkStateType *const LinkStatePtr)
// {
    // struct swic_tbl_lnk {
	// 	const swic_reg_data_t	*tbl;
	// 	const uint32			num;
	// 	const uint32			msk;
	// 	const uint32			dat;
	// };
	// static const struct swic_tbl_lnk	tbl[]
	// =	{ {&g_regListSeqGetLinkIeee[26], 1u, 0x0800u, 0x0800u}	/* P9：未使用                  */
	// 	, {&g_regListSeqGetLinkIeee[ 0], 1u, 0x0800u, 0x0800u}	/* P1：ADC 1000BASE-T1         */
	// 	, {&g_regListSeqGetLinkIeee[ 1], 1u, 0x0800u, 0x0800u}	/* P2：DCM 1000BASE-T1         */
	// 	, {&g_regListSeqGetLinkIeee[ 2], 7u, 0x0004u, 0x0004u}	/* P3：未使用                  */
	// 	, {&g_regListSeqGetLinkIeee[ 9], 7u, 0x0004u, 0x0004u}	/* P4：未使用                  */
	// 	, {&g_regListSeqGetLinkIeee[16], 7u, 0x0004u, 0x0004u}	/* P5：SIP SAILSS_RGMII0 RGMII */
	// 	, {&g_regListSeqGetLinkIeee[23], 1u, 0x0800u, 0x0800u}	/* P6：DLC 100BASE-TX          */
	// 	, {&g_regListSeqGetLinkIeee[24], 1u, 0x0800u, 0x0800u}	/* P7：SIP SGMII0 SGMII        */
	// 	, {&g_regListSeqGetLinkIeee[25], 1u, 0x0800u, 0x0800u}	/* P8：SIP SGMII1 SGMII        */
	// 	};

	// Std_ReturnType	err;
	// uint32			val = 0uL;
	// if (SwitchPortIdx >= SWIC_TBL_NUM(tbl))	{ return E_NOT_OK; }
	// if (LinkStatePtr == NULL_PTR)			{ return E_NOT_OK; }
	// err = swic_Reg_SetTbl(tbl[SwitchPortIdx].tbl, tbl[SwitchPortIdx].num, &val);
	// if (err == E_OK) {
	// 	*LinkStatePtr = ((val & tbl[SwitchPortIdx].msk) == tbl[SwitchPortIdx].dat) ? ETHTRCV_LINK_STATE_ACTIVE : ETHTRCV_LINK_STATE_DOWN;
	// }
	// return err;
// }