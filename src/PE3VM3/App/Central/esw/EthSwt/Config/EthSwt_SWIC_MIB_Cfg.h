/* EthSwt_SWIC_MIB.c専用ヘッダファイル */

/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_MIB_Cfg.h                                        */
/* -------------------------------------------------------------------------- */
#ifndef ETHSWT_SWIC_MIB_CFG_H
#define ETHSWT_SWIC_MIB_CFG_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include "EthSwt_SWIC_Cfg.h"
#include <EthSwt_SWIC_Define.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_initRegListSeqMib.h>
/* -------------------------------------------------------------------------- */
struct swic_reg_tbl {								/* レジスタテーブル */
	const swic_reg_data_t	*tbl;
	const uint32			num;
};

static const Std_ReturnType G_ETHSWT_SWIC_MIB_VAILD[D_ETHSWT_SWIC_PORT_NUM]
= { STD_ON  /* P1 */
,   STD_ON  /* P2 */
,   STD_OFF /* P3 */
,   STD_OFF /* P4 */
,   STD_ON  /* P5 */
,   STD_ON  /* P6 */
,   STD_ON  /* P7 */
,   STD_ON  /* P8 */
,   STD_OFF /* P9 */
};

static const struct swic_reg_tbl G_ETHSWT_SWIC_MIB_SELECT_PORT[D_ETHSWT_SWIC_PORT_NUM]
= { {&g_regListSeqSelectPort[ 0], 2u} /* P1 */
  , {&g_regListSeqSelectPort[ 2], 2u} /* P2 */
  , {&g_regListSeqSelectPort[ 4], 2u} /* P3 */
  , {&g_regListSeqSelectPort[ 6], 2u} /* P4 */
  , {&g_regListSeqSelectPort[ 8], 2u} /* P5 */
  , {&g_regListSeqSelectPort[10], 2u} /* P6 */
  , {&g_regListSeqSelectPort[12], 2u} /* P7 */
  , {&g_regListSeqSelectPort[14], 2u} /* P8 */
  , {&g_regListSeqSelectPort[16], 2u} /* P9 */
};

static const struct swic_reg_tbl G_ETHSWT_SWIC_MIB_TABLE_LIST[D_ETHSWT_SWIC_PORT_NUM]
= { {g_regListSeqMibInFCSErr,     SWIC_TBL_NUM(g_regListSeqMibInFCSErr)     }           /* InFCSErr */
  , {g_regListSeqMibInDiscards,   SWIC_TBL_NUM(g_regListSeqMibInDiscards)   }           /* InDiscards */
  , {g_regListSeqMibInFiltered,   SWIC_TBL_NUM(g_regListSeqMibInFiltered)   }           /* InFiltered */
  , {g_regListSeqMibInOverSize,   SWIC_TBL_NUM(g_regListSeqMibInOverSize)   }           /* InOverSize */
  , {g_regListSeqMibInUnderSize,  SWIC_TBL_NUM(g_regListSeqMibInUnderSize)  }           /* InUnderSize */
  , {g_regListSeqMibTcamCnt0,     SWIC_TBL_NUM(g_regListSeqMibTcamCnt0)     }           /* Tcam0 */
  , {g_regListSeqMibTcamCnt1,     SWIC_TBL_NUM(g_regListSeqMibTcamCnt1)     }           /* Tcam1 */
  , {g_regListSeqMibTcamCnt2,     SWIC_TBL_NUM(g_regListSeqMibTcamCnt2)     }           /* Tcam2 */
  , {g_regListSeqMibTcamCnt3,     SWIC_TBL_NUM(g_regListSeqMibTcamCnt3)     }           /* Tcam3 */
};
/* -------------------------------------------------------------------------- */
#endif /* ETHSWT_SWIC_MIB_CFG_H */
/* -------------------------------------------------------------------------- */
