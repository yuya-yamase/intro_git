#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include "EthSwt_SWIC_initRegCommon.h"
#include "EthSwt_SWIC_Spi.h"
#include "EthSwt_SWIC_STM.h"
/* -------------------------------------------------------------------------- */
static Std_ReturnType swic_Reg_SetTblWriteOFF(const Std_ReturnType ret, const swic_reg_data_t tbl[], const uint32 cnt, const uint32 idx);



Std_ReturnType EthSwt_SWIC_Reg_SetTbl(const swic_reg_data_t tbl[], const uint32 cnt, uint32 * const dat)
{
    Std_ReturnType	ret = E_OK;
	uint32			idx;
	uint16			val = 0U;
    Std_ReturnType  checkUninit = STD_OFF;

    if (cnt <= 0uL) 		{ return E_OK; }
	if (tbl == NULL_PTR)	{ return E_NOT_OK; }
    EthSwt_SWIC_Spi_ReqInit();
    if (dat != NULL_PTR)	{ *dat = 0u; }
    for (idx=0U; idx < cnt ; idx++) {
        checkUninit = EthSwt_SWIC_STM_CheckUninit();
        if (checkUninit == STD_ON) {return E_NOT_OK;}               /* モビコンと違う箇所 */
        // switch (((uint16)tbl[idx].regCtrl << 8) | tbl[idx].surveillance) {
		// case ((uint16)REG_CTRL_WRITE << 8) | SURVEILLANCE_ON:	/* リードバック無 */
		// case ((uint16)REG_CTRL_WRITE << 8) | SURVEILLANCE_OFF:
		// 	ret = swic_Reg_SetTblWriteOFF(ret, tbl, cnt, idx);
		// 	break;
		// case ((uint16)REG_CTRL_READ << 8) | SURVEILLANCE_ON:
		// 	ret = swic_Reg_SetTblReadON(ret, tbl, idx, tbl[idx].mask, tbl[idx].value);
		// 	break;
		// case ((uint16)REG_CTRL_READ << 8) | SURVEILLANCE_OFF:
		// 	ret = swic_Reg_SetTblReadOFF(ret, tbl, cnt, idx, dat);
		// 	break;
		// case ((uint16)REG_CTRL_WRITE_MASK << 8) | SURVEILLANCE_OFF:
		// 	ret = swic_Reg_SetTblWriteMask(ret, tbl, idx, val);
		// 	break;
		// case ((uint16)REG_CTRL_READ_TMP << 8) | SURVEILLANCE_OFF:
		// 	ret = swic_Reg_SetTblReadMask(ret, tbl, idx, &val);
		// 	break;
		// default:
		// 	ret = swic_Reg_SetTblErr(tbl, idx, 0u);
		// 	break;
		}

    return ret;
}
/* -------------------------------------------------------------------------- */
