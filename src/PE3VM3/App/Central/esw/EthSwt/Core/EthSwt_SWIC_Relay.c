#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_initRegCommon.h>
#include "EthSwt_SWIC_Relay.h"
#include "EthSwt_SWIC_Reg.h"

#include <EthSwt_SWIC_initRegListSeqInitSeq.h>
#include <EthSwt_SWIC_initRegListSeqBaseT1.h>
#include <EthSwt_SWIC_initRegListSeqPhySwicOff.h>
/* -------------------------------------------------------------------------- */
#define	SWIC_REG_TBL(a)		{(a), SWIC_TBL_NUM(a)}	/* swic_reg_tbl設定用 */
#define	SWIC_TBL_NUM(a)	(sizeof(a)/sizeof((a)[0]))
/* -------------------------------------------------------------------------- */
struct swic_reg_tbl {								/* レジスタテーブル */
	const swic_reg_data_t	*tbl;
	const uint32			num;
};
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_Relay_On(uint32 *errFactor)
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
Std_ReturnType EthSwt_SWIC_Relay_Off(uint32 *errFactor)
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