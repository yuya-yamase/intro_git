#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_Core_Cfg.h>
#include <EthSwt_SWIC_init_Cfg.h>
#include "EthSwt_SWIC_Init.h"
#include "EthSwt_SWIC_Reg.h"
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_Init_Setting(uint32 *errFactor)
{
    Std_ReturnType	err = E_OK;
	uint32			idx;
	uint32			val;

    for (idx=0U ; idx < SWIC_TBL_NUM(tbl_list) ; idx++) {		/* リードバック無 */
        err = EthSwt_SWIC_Reg_SetTbl(tbl_list[idx].tbl.tbl, tbl_list[idx].tbl.num, (tbl_list[idx].rst == STD_OFF) ? &val : NULL_PTR, errFactor);
		if (err == E_NOT_OK) { break; }
	}

	return err;
}