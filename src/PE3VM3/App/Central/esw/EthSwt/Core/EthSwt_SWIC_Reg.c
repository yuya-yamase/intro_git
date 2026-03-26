/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_Reg.c                                            */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_initRegCommon.h>
#include <EthSwt_SWIC_Cfg.h>
#include "EthSwt_SWIC_Reg.h"
#include "EthSwt_SWIC_Spi.h"
#include "EthSwt_SWIC_STM.h"
#include "EthSwt_SWIC_Time.h"
#include <EthSwt_SWIC_Define.h>
#include <LIB.h>
/* -------------------------------------------------------------------------- */
static Std_ReturnType swic_Reg_SetTblWriteOFF(const swic_reg_data_t tbl[], const uint32 cnt, const uint32 idx, uint32 * const errFactor);
static Std_ReturnType swic_Reg_SetTblReadON(const swic_reg_data_t tbl[], const uint32 idx, const uint16 mask, const uint16 value, uint32 * const errFactor);
static Std_ReturnType swic_Reg_SetTblReadOFF(const swic_reg_data_t tbl[], const uint32 cnt, const uint32 idx, uint32 * const dat, uint32 * const errFactor);
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_Reg_SetTbl(const swic_reg_data_t tbl[], const uint32 cnt, uint32 * const dat, uint32 * const errFactor)
{
    Std_ReturnType	result = E_OK;
	uint32			idx;

    if (cnt <= 0uL) 		{ return E_OK; }
	if (tbl == NULL_PTR)	{ return E_NOT_OK; }
    EthSwt_SWIC_Spi_ReqInit();
    if (dat != NULL_PTR)	{ *dat = 0u; }
    for (idx=0U; idx < cnt ; idx++) {
        switch (((uint16)tbl[idx].regCtrl << 8) | tbl[idx].surveillance) {
		case ((uint16)REG_CTRL_WRITE << 8) | SURVEILLANCE_ON:									/* リードバック無 */
		case ((uint16)REG_CTRL_WRITE << 8) | SURVEILLANCE_OFF:									/* レジスタ書込み */
			result = swic_Reg_SetTblWriteOFF(tbl, cnt, idx, errFactor);
			break;
		case ((uint16)REG_CTRL_READ << 8) | SURVEILLANCE_ON:									/* レジスタ読出し(監視あり) */
			result = swic_Reg_SetTblReadON(tbl, idx, tbl[idx].mask, tbl[idx].value, errFactor);
			break;
		case ((uint16)REG_CTRL_READ << 8) | SURVEILLANCE_OFF:									/* レジスタ読出し(監視なし)*/
			result = swic_Reg_SetTblReadOFF(tbl, cnt, idx, dat, errFactor);
			break;
		case ((uint16)REG_CTRL_WAIT << 8) | SURVEILLANCE_OFF:									/* WAIT処理 */
			EthSwt_SWIC_Cfg_WaitUS(tbl[idx].value);
			break;
		default:
			result = E_NOT_OK;										/* レジスタアクセス制御にない要求場合 */
			*errFactor = D_ETHSWT_SWIC_ERR_NOPROC;
			break;
		}
		if (result == E_NOT_OK) { break; }
	}
    return result;
}
/* -------------------------------------------------------------------------- */
static Std_ReturnType swic_Reg_SetTblWriteOFF(const swic_reg_data_t tbl[], const uint32 cnt, const uint32 idx, uint32 * const errFactor)
{
	Std_ReturnType	result = E_OK;
	uint32			i;
	Std_ReturnType	checkPwr;

	for (i = 0U ; i < INIT_SEQ_RETRY_CNT ; i++) {
		result = EthSwt_SWIC_Spi_Write(tbl, cnt, idx);
		if (result == E_OK) {
			break;
		}

		checkPwr = EthSwt_SWIC_Cfg_AllowSetRegister();			/* OEM Config */
		if (checkPwr == E_NOT_OK) {
			*errFactor = D_ETHSWT_SWIC_ERR_POWEROFF;
			break;
		}
	}

	if (result == E_NOT_OK && checkPwr == E_OK) {
		*errFactor = D_ETHSWT_SWIC_ERR_CRC;	/* CRCエラーが連続INIT_SEQ_RETRY_CNT続いたとき */
	}
	
	return result;
}
/* -------------------------------------------------------------------------- */
static Std_ReturnType swic_Reg_SetTblReadON(const swic_reg_data_t tbl[], const uint32 idx, const uint16 mask, const uint16 value, uint32 * const errFactor)
{
	Std_ReturnType	result = E_OK;
	uint16			val = 0u;
	uint32			i;
	uint16			cnt = 0u;
	uint32			startTime;
	uint32			pastTime;
	Std_ReturnType	checkPwr;

	startTime = EthSwt_SWIC_Time_GetCurrentTime();

	for (i = 0uL ; i < SWIC_REG_WAIT_L ; i++) {				/* ★ループガードについて要検討 */
		result = EthSwt_SWIC_Spi_ReadSPI(tbl, idx, &val);
		if (result == E_OK) {
			if (((val ^ value) & mask) == 0u) { break; }
			cnt = 0u;										/* 連続3回 */
		}
		else {
			checkPwr = EthSwt_SWIC_Cfg_AllowSetRegister();		/* OEM Config */
			if (checkPwr == E_NOT_OK) {
				*errFactor = D_ETHSWT_SWIC_ERR_POWEROFF;
				break;
			}

			cnt = cnt + (uint16)1;
			if (cnt >= INIT_SEQ_RETRY_CNT) {
				*errFactor = D_ETHSWT_SWIC_ERR_CRC;
				break;
			}
		}

		pastTime = EthSwt_SWIC_Time_GetPastTime(startTime);
		
		if (pastTime > SWIC_REG_WAIT) {
			*errFactor = D_ETHSWT_SWIC_ERR_BUSY;
			 break;
		}
	}
	
	return result;
}
/* -------------------------------------------------------------------------- */
static Std_ReturnType swic_Reg_SetTblReadOFF(const swic_reg_data_t tbl[], const uint32 cnt, const uint32 idx, uint32 * const dat, uint32 * const errFactor)
{
	Std_ReturnType	result = E_OK;
	uint16			val = 0u;
	uint32			i;
	Std_ReturnType	checkPwr = E_OK;

	for (i = 0U ; i < INIT_SEQ_RETRY_CNT ; i++) {
		result = EthSwt_SWIC_Spi_Read(tbl, cnt, idx, &val);
		if (result == E_OK) {
			if (dat != NULL_PTR) {							/* データ取得 */
				*dat = (*dat << 16) | ((uint32)val & (uint32)tbl[idx].mask);
				break;
			}												/* リードバック無効に以降はない */
			if (((val ^ tbl[idx].value) & tbl[idx].mask) == 0u)	{
				break;										/* 一致 */
			} else {
				*errFactor = D_ETHSWT_SWIC_ERR_WRONGVALUE;	/* 読出した値が期待と異なる */
				result = E_NOT_OK;
				break;
			}
		}

		checkPwr = EthSwt_SWIC_Cfg_AllowSetRegister();			/* OEM Config */
		if (checkPwr == E_NOT_OK) {
			*errFactor = D_ETHSWT_SWIC_ERR_POWEROFF;
			break;
		}
	}

	if (result == E_NOT_OK &&
		*errFactor != D_ETHSWT_SWIC_ERR_WRONGVALUE &&
		*errFactor != D_ETHSWT_SWIC_ERR_POWEROFF) {
		*errFactor = D_ETHSWT_SWIC_ERR_CRC;					/* 異常値が読み出しでもなく、電源状態が正常な場合で失敗した場合は、CRC異常で確定 */
	}

	return result;
}
