#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include "EthSwt_SWIC_initRegCommon.h"
#include "EthSwt_SWIC_Core_Cfg.h"
#include "EthSwt_SWIC_Spi.h"
#include "EthSwt_SWIC_STM.h"
#include "EthSwt_SWIC_Define.h"
/* -------------------------------------------------------------------------- */
volatile static uint16			timer;

/* -------------------------------------------------------------------------- */
static Std_ReturnType swic_Reg_SetTblWriteOFF(const swic_reg_data_t tbl[], const uint32 cnt, const uint32 idx, uint32 * const errFactor);
static Std_ReturnType swic_Reg_SetTblReadON(const swic_reg_data_t tbl[], const uint32 idx, const uint16 mask, const uint16 value, uint32 * const errFactor);
static Std_ReturnType swic_Reg_SetTblReadOFF(const swic_reg_data_t tbl[], const uint32 cnt, const uint32 idx, uint32 * const dat, uint32 * const errFactor);
static Std_ReturnType swic_Reg_SetTblWriteMask(const swic_reg_data_t tbl[], const uint32 idx, uint16 val, uint32 * const errFactor);
static Std_ReturnType swic_Reg_SetTblReadMask(const swic_reg_data_t tbl[], const uint32 idx, uint16 *const val, uint32 * const errFactor);
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Reg_Init (void)
{
	timer = 0;

	return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Reg_HiProc (void)
{
	timer = timer + D_ETHSWT_SWIC_PERIOD;
	return;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_Reg_SetTbl(const swic_reg_data_t tbl[], const uint32 cnt, uint32 * const dat, uint32 * const errFactor)
{
    Std_ReturnType	ret = E_OK;
	uint32			idx;
	uint16			val = 0U;

    if (cnt <= 0uL) 		{ return E_OK; }
	if (tbl == NULL_PTR)	{ return E_NOT_OK; }
    EthSwt_SWIC_Spi_ReqInit();
    if (dat != NULL_PTR)	{ *dat = 0u; }
    for (idx=0U; idx < cnt ; idx++) {
        switch (((uint16)tbl[idx].regCtrl << 8) | tbl[idx].surveillance) {
		case ((uint16)REG_CTRL_WRITE << 8) | SURVEILLANCE_ON:	/* リードバック無 */
		case ((uint16)REG_CTRL_WRITE << 8) | SURVEILLANCE_OFF:
			ret = swic_Reg_SetTblWriteOFF(tbl, cnt, idx, errFactor);
			break;
		case ((uint16)REG_CTRL_READ << 8) | SURVEILLANCE_ON:
			ret = swic_Reg_SetTblReadON(tbl, idx, tbl[idx].mask, tbl[idx].value, errFactor);
			break;
		case ((uint16)REG_CTRL_READ << 8) | SURVEILLANCE_OFF:
			ret = swic_Reg_SetTblReadOFF(tbl, cnt, idx, dat, errFactor);
			break;
		case ((uint16)REG_CTRL_WRITE_MASK << 8) | SURVEILLANCE_OFF:
			ret = swic_Reg_SetTblWriteMask(tbl, idx, val, errFactor);
			break;
		case ((uint16)REG_CTRL_READ_TMP << 8) | SURVEILLANCE_OFF:
			ret = swic_Reg_SetTblReadMask(tbl, idx, &val, errFactor);
			break;
		default:
			ret = E_NOT_OK;	/* ここの扱いどうするか */
			break;
		}
		if (ret == E_NOT_OK) {
			break;
		}
	}
    return ret;
}
/* -------------------------------------------------------------------------- */

static Std_ReturnType swic_Reg_SetTblWriteOFF(const swic_reg_data_t tbl[], const uint32 cnt, const uint32 idx, uint32 * const errFactor)
{
	Std_ReturnType	err;
	uint32			i;
	for (i = 0U ; i < INIT_SEQ_RETRY_CNT ; i++) {
		err = EthSwt_SWIC_Spi_Write(tbl, cnt, idx);
		if (err == E_OK) {
			break;
		}
	}
	*errFactor = D_ETHSWT_SWIC_REG_FACT_CRC;	/* errFactorに値を入れるが、E_OKの場合は値を見ない */
	return err;
}
/* -------------------------------------------------------------------------- */
static Std_ReturnType swic_Reg_SetTblReadON(const swic_reg_data_t tbl[], const uint32 idx, const uint16 mask, const uint16 value, uint32 * const errFactor)
{
	Std_ReturnType	err;
	uint16			val = 0u;
	uint32			i;
	uint16			cnt = 0u;
	const uint16	getTime = timer;
	for (i=0uL ; i<SWIC_REG_WAIT_L ; i++) {
		uint16	tmo;
		err = EthSwt_SWIC_Spi_ReadSPI(tbl, idx, &val);
		if (err == E_OK) {
			if (((val ^ value) & mask) == 0u) { break; }
			cnt = 0u;							/* 連続3回 */
		}
		else {
			cnt = cnt + (uint16)1;
			if (cnt >= INIT_SEQ_RETRY_CNT) {
				*errFactor = D_ETHSWT_SWIC_REG_FACT_CRC;
				break;
			}
		}
		tmo = timer - getTime;
		if (tmo > SWIC_REG_WAIT) {
			*errFactor = D_ETHSWT_SWIC_REG_FACT_BSY;
			 break;
		}
	}
	return err;
}
/* -------------------------------------------------------------------------- */
static Std_ReturnType swic_Reg_SetTblReadOFF(const swic_reg_data_t tbl[], const uint32 cnt, const uint32 idx, uint32 * const dat, uint32 * const errFactor)
{
	Std_ReturnType	err;
	uint16			val = 0u;
	uint32			i;
	for (i = 0U ; i < INIT_SEQ_RETRY_CNT ; i++) {
		err = EthSwt_SWIC_Spi_Read(tbl, cnt, idx, &val);
		if (err == E_OK) {
			if (dat != NULL_PTR) {	/* データ取得 */
				*dat = (*dat << 16) | ((uint32)val & (uint32)tbl[idx].mask);
				break;
			}						/* リードバック無効に以降はない */
			if (((val ^ tbl[idx].value) & tbl[idx].mask) == 0u)	{ break; }	/* 一致 */
			// *errFactor = D_ETHSWT_SWIC_REG_FACT_INIT;	/* リードバック異常 *//* リードバック無効に以降はないということでコメントアウト*/
			// err = E_NOT_OK; /* リードバック無効に以降はないということでコメントアウト*/
		}
	}

	*errFactor = D_ETHSWT_SWIC_REG_FACT_CRC;	/* errFactorに値を入れるが、E_OKの場合は値を見ない */
	return err;
}
/* -------------------------------------------------------------------------- */
static Std_ReturnType swic_Reg_SetTblWriteMask(const swic_reg_data_t tbl[], const uint32 idx, uint16 val, uint32 * const errFactor)
{
	Std_ReturnType	err;
	uint32			i;
	val ^= val & tbl[idx].mask;
	val |= tbl[idx].value & tbl[idx].mask;
	for (i = 0U ; i < INIT_SEQ_RETRY_CNT ; i++) {
		err = EthSwt_SWIC_Spi_WriteSPI(tbl, idx, val);
		if (err == E_OK) {
			break;
		}
	}
	*errFactor = D_ETHSWT_SWIC_REG_FACT_CRC;	/* errFactorに値を入れるが、E_OKの場合は値を見ない */

	return err;
}
/* -------------------------------------------------------------------------- */
static Std_ReturnType swic_Reg_SetTblReadMask(const swic_reg_data_t tbl[], const uint32 idx, uint16 *const val, uint32 * const errFactor)
{
	Std_ReturnType	err;
	uint32			i;
	for (i = 0U ; i < INIT_SEQ_RETRY_CNT ; i++) {
		err = EthSwt_SWIC_Spi_ReadSPI(tbl, idx, val);
		if (err == E_OK) {
			break;
		}
	}
	*errFactor = D_ETHSWT_SWIC_REG_FACT_CRC;	/* errFactorに値を入れるが、E_OKの場合は値を見ない */
	return err;
}
