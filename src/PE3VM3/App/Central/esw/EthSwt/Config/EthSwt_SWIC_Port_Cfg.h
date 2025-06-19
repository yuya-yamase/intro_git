/* EthSwt_SWIC_Port.c専用ヘッダファイル */

/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_Port_Cfg.h                                       */
/* -------------------------------------------------------------------------- */
#ifndef ETHSWT_SWIC_PORT_CFG_H
#define ETHSWT_SWIC_PORT_CFG_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_Define.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_initRegListSeqInitSeq.h>
#include <EthSwt_SWIC_initRegListSeqBaseT1.h>
#include <EthSwt_SWIC_initRegListSeqPhySwicOff.h>
#include <EthSwt_SWIC_initRegListSeq100BTx.h>
/* -------------------------------------------------------------------------- */
struct swic_reg_tbl {								/* レジスタテーブル */
	const swic_reg_data_t	*tbl;
	const uint32			num;
};

static const struct swic_reg_tbl G_ETHSWT_SWIC_RELAY_ON_TABLE[] =
{
    SWIC_REG_TBL(g_regListSeqRelayOn),
    SWIC_REG_TBL(g_regListSeqP1PhyOn),
    SWIC_REG_TBL(g_regListSeqP2PhyOn),
};

static const struct swic_reg_tbl G_ETHSWT_SWIC_RELAY_OFF_TABLE[] =
{
    SWIC_REG_TBL(g_regListSeqP1PhyOff),
    SWIC_REG_TBL(g_regListSeqP2PhyOff),
    SWIC_REG_TBL(g_regListSeqRelayOff),
    SWIC_REG_TBL(g_regListSeqSet100BTxDown)
};

static const struct swic_reg_tbl G_ETHSWT_SWIC_PHY_ON_TABLE[] =
{   {NULL_PTR                       , 0u                                        }   /* P9：未使用                  */
,   {g_regListSeqP1PhyOn            , SWIC_TBL_NUM(g_regListSeqP1PhyOn)         }	/* P1：ADC 1000BASE-T1         */
,   {g_regListSeqP2PhyOn            , SWIC_TBL_NUM(g_regListSeqP2PhyOn)         }   /* P2：DCM 1000BASE-T1         */
,   {NULL_PTR                       , 0u                                        }	/* P3：未使用                  */
,   {NULL_PTR                       , 0u                                        }   /* P4：未使用                  */
,   {NULL_PTR                       , 0u                                        }	/* P5：SIP SAILSS_RGMII0 RGMII */
,   {g_regListSeqSet100BTxStart     , SWIC_TBL_NUM(g_regListSeqSet100BTxStart)  }	/* P6：DLC 100BASE-TX          */
,   {NULL_PTR                       , 0u                                        }	/* P7：SIP SGMII0 SGMII        */
,   {NULL_PTR                       , 0u                                        }	/* P8：SIP SGMII1 SGMII        */
};

static const struct swic_reg_tbl G_ETHSWT_SWIC_PHY_OFF_TABLE[] =
{   {NULL_PTR                       , 0u                                        }	/* P9：未使用                  */
,   {g_regListSeqP1PhyOff           , SWIC_TBL_NUM(g_regListSeqP1PhyOff)        }	/* P1：ADC 1000BASE-T1         */
,   {g_regListSeqP2PhyOff           , SWIC_TBL_NUM(g_regListSeqP2PhyOff)        }	/* P2：DCM 1000BASE-T1         */
,   {NULL_PTR                       , 0u                                        }	/* P3：未使用                  */
,   {NULL_PTR                       , 0u                                        }	/* P4：未使用                  */
,   {NULL_PTR                       , 0u                                        }	/* P5：SIP SAILSS_RGMII0 RGMII */
,   {g_regListSeqSet100BTxDown      , SWIC_TBL_NUM(g_regListSeqSet100BTxDown)   }	/* P6：DLC 100BASE-TX          */
,   {NULL_PTR                       , 0u                                        }   /* P7：SIP SGMII0 SGMII        */
,   {NULL_PTR                       , 0u                                        }	/* P8：SIP SGMII1 SGMII        */
};
/* -------------------------------------------------------------------------- */
#endif /* ETHSWT_SWIC_PORT_CFG_H */
/* -------------------------------------------------------------------------- */
