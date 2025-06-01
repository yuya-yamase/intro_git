#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include "EthSwt_BSW_define.h"
#include "EthSwt_SWIC_Core_Cfg.h"
#include "EthSwt_SWIC_Reg.h"
#include "LIB.h"
#include "EthSwt_SWIC_initRegListSeqInitSeq.h"
#include "EthSwt_SWIC_initRegListSeqBaseT1.h"
#include "EthSwt_SWIC_initRegListSeqPhySwicOff.h"
#include "EthSwt_SWIC_initRegListSeq100BTx.h"
/* -------------------------------------------------------------------------- */
#define	SWIC_REG_TBL(a)		{(a), SWIC_TBL_NUM(a)}	/* swic_reg_tbl設定用 */
#define	SWIC_TBL_NUM(a)	(sizeof(a)/sizeof((a)[0]))
/* -------------------------------------------------------------------------- */
struct swic_reg_tbl {								/* レジスタテーブル */
	const swic_reg_data_t	*tbl;
	const uint32			num;
};

static struct {
    Eth_ModeType                mode;
    volatile Eth_ModeType       mode_chg;
    volatile uint8              modeChangeRequest;
    volatile uint8              modeChangeIndication;

} swicPort[D_ETHSWT_SWIC_PORT_NUM];
/* -------------------------------------------------------------------------- */
static Std_ReturnType swic_Reg_SetSwitchPortMode(const uint8 SwitchPortIdx, uint32 * const errFactor);
static Std_ReturnType swic_Reg_SetSwitchPortModeACTIVE(const uint8 SwitchPortIdx, uint32 * const errFactor);
static Std_ReturnType swic_Reg_SetSwitchPortModeDOWN(const uint8 SwitchPortIdx, uint32 * const errFactor);
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Port_Init (void)
{
    uint8   idx;

    for (idx = 0; idx < D_ETHSWT_SWIC_PORT_NUM; idx++) {
        swicPort[idx].mode                  = G_ETHSWT_SWIC_PORT_DEFINE[idx];
        swicPort[idx].mode_chg              = G_ETHSWT_SWIC_PORT_DEFINE[idx];
        swicPort[idx].modeChangeRequest     = STD_OFF;
        swicPort[idx].modeChangeIndication  = STD_OFF;
    }

    return;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_Port_RelayOn(uint32 *errFactor)
{
    static const struct swic_reg_tbl tbl_list[]
    = {
        SWIC_REG_TBL(g_regListSeqRelayOn),
        SWIC_REG_TBL(g_regListSeqP1PhyOn),
        SWIC_REG_TBL(g_regListSeqP2PhyOn),
    };
    
    Std_ReturnType	err = E_OK;
	uint32			idx;
	uint32			val;

    for (idx=0U ; idx < SWIC_TBL_NUM(tbl_list) ; idx++) {
        err = EthSwt_SWIC_Reg_SetTbl(tbl_list[idx].tbl, tbl_list[idx].num, &val , errFactor);
		if (err == E_NOT_OK) { break; }
	}

	return err;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_Port_RelayOff(uint32 *errFactor)
{
    static const struct swic_reg_tbl tbl_list[]
    = {
        SWIC_REG_TBL(g_regListSeqP1PhyOff),
        SWIC_REG_TBL(g_regListSeqP2PhyOff),
        SWIC_REG_TBL(g_regListSeqRelayOff)
    };

    Std_ReturnType	err = E_OK;
	uint32			idx;
	uint32			val;

    for (idx=0U ; idx < SWIC_TBL_NUM(tbl_list) ; idx++) {
        err = EthSwt_SWIC_Reg_SetTbl(tbl_list[idx].tbl, tbl_list[idx].num, &val , errFactor);
		if (err == E_NOT_OK) { break; }
	}

    return err;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_Port_SetSwitchPortMode(const uint8 SwitchPortIdx, const Eth_ModeType PortMode)
{	/* 1msタスク */
	// if (swic_Reg_Inf.sts == ETHSWT_SWIC_STATE_UNINIT)	{ return E_NOT_OK; } /* どの状態でも受け付けるように変更 */
    Std_ReturnType ret;
	if (SwitchPortIdx >= D_ETHSWT_SWIC_PORT_NUM) {
        ret = E_NOT_OK;
    } else {
        ret = E_OK;
        swicPort[SwitchPortIdx].mode_chg	        = PortMode;
	    swicPort[SwitchPortIdx].modeChangeRequest	= STD_ON;	/* 処理前に複数呼ばれた場合は最新が有効 */
    }
	
	return ret;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_Port_Action (uint32 * const errFactor)
{
    Std_ReturnType  ret = E_OK;
    uint8           idx;
    for (idx = 0u; idx < D_ETHSWT_SWIC_PORT_NUM; idx++) {
        if (swicPort[idx].modeChangeRequest != STD_ON) { continue; }
        ret = swic_Reg_SetSwitchPortMode(idx, errFactor);
        if (ret == E_NOT_OK) {break;}
    }

    return ret;
}
/* -------------------------------------------------------------------------- */
static Std_ReturnType swic_Reg_SetSwitchPortMode(const uint8 SwitchPortIdx, uint32 * const errFactor)
{
	Eth_ModeType	PortMode;
	Std_ReturnType	err;
	LIB_DI();
	swicPort[SwitchPortIdx].modeChangeRequest = STD_OFF;	/* 下との間で割り込まれると同じ状態を通知する */
	PortMode = swicPort[SwitchPortIdx].mode_chg;	/* 問題なければ排他不要 */
	LIB_EI();
	if (swicPort[SwitchPortIdx].mode != PortMode) {
		switch (PortMode) {
		default:									/* default */
			break;
		case ETH_MODE_ACTIVE_WITH_WAKEUP_REQUEST:
			PortMode = ETH_MODE_ACTIVE;				/* [SWS_EthSwt_00439] */
			break;
		case ETH_MODE_ACTIVE:
			err = swic_Reg_SetSwitchPortModeACTIVE(SwitchPortIdx, errFactor);
			break;
		case ETH_MODE_DOWN:
			err = swic_Reg_SetSwitchPortModeDOWN(SwitchPortIdx, errFactor);
			// swic_Reg_LinkTimSet(SwitchPortIdx, ETHTRCV_LINK_STATE_DOWN, 1u); /* ETH_MODE_DOWNは反応がいいので確認 */  /* ★ 必要？ */
			break;
		}
	}
    if (err == E_OK) {
        LIB_DI();
        swicPort[SwitchPortIdx].mode = PortMode;
	    swicPort[SwitchPortIdx].modeChangeIndication = STD_ON;
        LIB_EI();
    } else {
        swicPort[SwitchPortIdx].modeChangeRequest = STD_ON;
    }

    return err;
}
/* -------------------------------------------------------------------------- */
static Std_ReturnType swic_Reg_SetSwitchPortModeACTIVE(const uint8 SwitchPortIdx, uint32 * const errFactor)
{
    Std_ReturnType  result;
    uint32          val;
	static const struct swic_reg_tbl phyon_tbl[]
	= { {NULL_PTR                       , 0u                                        }   /* P9：未使用                  */
	  , {g_regListSeqP1PhyOn            , SWIC_TBL_NUM(g_regListSeqP1PhyOn)         }	/* P1：ADC 1000BASE-T1         */
	  , {g_regListSeqP2PhyOn            , SWIC_TBL_NUM(g_regListSeqP2PhyOn)         }   /* P2：DCM 1000BASE-T1         */
	  , {NULL_PTR                       , 0u                                        }	/* P3：未使用                  */
	  , {NULL_PTR                       , 0u                                        }   /* P4：未使用                  */
	  , {NULL_PTR                       , 0u                                        }	/* P5：SIP SAILSS_RGMII0 RGMII */
	  , {g_regListSeqSet100BTxStart     , SWIC_TBL_NUM(g_regListSeqSet100BTxStart)  }	/* P6：DLC 100BASE-TX          */
	  , {NULL_PTR                       , 0u                                        }	/* P7：SIP SGMII0 SGMII        */
	  , {NULL_PTR                       , 0u                                        }	/* P8：SIP SGMII1 SGMII        */
	  };

    result = EthSwt_SWIC_Reg_SetTbl(phyon_tbl[SwitchPortIdx].tbl, phyon_tbl[SwitchPortIdx].num, &val, errFactor);
    
    return result;
}
/* -------------------------------------------------------------------------- */
static Std_ReturnType swic_Reg_SetSwitchPortModeDOWN(const uint8 SwitchPortIdx, uint32 * const errFactor)
{
    Std_ReturnType  result;
    uint32          val;

	static const struct swic_reg_tbl tbl[]
	=	{ {NULL_PTR                     , 0u                                        }	/* P9：未使用                  */
		, {g_regListSeqP1PhyOff         , SWIC_TBL_NUM(g_regListSeqP1PhyOff)        }	/* P1：ADC 1000BASE-T1         */
		, {g_regListSeqP2PhyOff         , SWIC_TBL_NUM(g_regListSeqP2PhyOff)        }	/* P2：DCM 1000BASE-T1         */
		, {NULL_PTR                     , 0u                                        }	/* P3：未使用                  */
		, {NULL_PTR                     , 0u                                        }	/* P4：未使用                  */
		, {NULL_PTR                     , 0u                                        }	/* P5：SIP SAILSS_RGMII0 RGMII */
		, {g_regListSeqSet100BTxDown    , SWIC_TBL_NUM(g_regListSeqSet100BTxDown)   }	/* P6：DLC 100BASE-TX          */
		, {NULL_PTR                     , 0u                                        }   /* P7：SIP SGMII0 SGMII        */
		, {NULL_PTR                     , 0u                                        }	/* P8：SIP SGMII1 SGMII        */
		};

    result = EthSwt_SWIC_Reg_SetTbl(tbl[SwitchPortIdx].tbl, tbl[SwitchPortIdx].num, &val, errFactor);

	return result;
}