/* EthSwt_SWIC_Link.c専用ヘッダファイル */

/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_Link_Cfg.h                                       */
/* -------------------------------------------------------------------------- */
#ifndef ETHSWT_SWIC_LINK_CFG_H
#define ETHSWT_SWIC_LINK_CFG_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include "EthSwt_SWIC_Cfg.h"
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_initRegListSeqGetLink.h>
/* -------------------------------------------------------------------------- */
struct swic_tbl_lnk {
		const swic_reg_data_t	*tbl;
		const uint32			num;
		const uint32			msk;
		const uint32			dat;
};

static const Std_ReturnType G_ETHSWT_SWIC_LINK_VAILD[D_ETHSWT_SWIC_PORT_NUM]
= { STD_ON  /* P1 */
,   STD_ON  /* P2 */
,   STD_OFF /* P3 */
,   STD_OFF /* P4 */
,   STD_OFF /* P5 */
,   STD_ON  /* P6 */
,   STD_ON  /* P7 */
,   STD_ON  /* P8 */
,   STD_OFF /* P9 */
};

static const struct swic_tbl_lnk	G_ETHSWT_SWIC_GET_LINK_TABLE[D_ETHSWT_SWIC_PORT_NUM]
=	{ 
      {&g_regListSeqGetLinkIeee[ 0], 1u, 0x0800u, 0x0800u}	/* P1：ADC 1000BASE-T1         */
    , {&g_regListSeqGetLinkIeee[ 1], 1u, 0x0800u, 0x0800u}	/* P2：DCM 1000BASE-T1         */
    , {NULL_PTR                    , 0u, 0x0000u, 0x0000u}	/* P3：未使用                  */
    , {NULL_PTR                    , 0u, 0x0000u, 0x0000u}	/* P4：未使用                  */
    , {NULL_PTR                    , 0u, 0x0000u, 0x0000u}	/* P5：SIP SAILSS_RGMII0 RGMII */
    , {&g_regListSeqGetLinkIeee[16], 1u, 0x0800u, 0x0800u}	/* P6：DLC 100BASE-TX          */
    , {&g_regListSeqGetLinkIeee[17], 1u, 0x0800u, 0x0800u}	/* P7：SIP SGMII0 SGMII        */
    , {&g_regListSeqGetLinkIeee[18], 1u, 0x0800u, 0x0800u}	/* P8：SIP SGMII1 SGMII        */
    , {NULL_PTR                    , 0u, 0x0000u, 0x0000u}	/* P9：未使用                  */
    };
/* -------------------------------------------------------------------------- */
#endif /* ETHSWT_SWIC_LINK_CFG_H */
/* -------------------------------------------------------------------------- */
