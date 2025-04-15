#include <Std_Types.h>
#include <EthSwt_SWIC.h>
#include <Rte_BswUcfg.h>
#include <Spi.h>
#include <LIB.h>
#include "EthSwt_SWIC_Def.h"
#include "EthSwt_SWIC_Spi.h"

#define	swic_Spi_Crc8Cmd(a,b)	swic_Spi_Crc8(a,b,0u)

#define ETHSWT_START_SEC_CONFIG_DATA_PREBUILD
#include <EthSwt_SWIC_MemMap.h>
static const uint8	swic_Spi_CrcOK[]	/* swic_Spi_Crc8({0xFF}, 1, crc)のテーブル:~swic_Spi_Crc[]と同じ */
=	{ 0xFFu, 0xA1u, 0x43u, 0x1Du, 0x9Eu, 0xC0u, 0x22u, 0x7Cu, 0x3Du, 0x63u, 0x81u, 0xDFu, 0x5Cu, 0x02u, 0xE0u, 0xBEu
	, 0x62u, 0x3Cu, 0xDEu, 0x80u, 0x03u, 0x5Du, 0xBFu, 0xE1u, 0xA0u, 0xFEu, 0x1Cu, 0x42u, 0xC1u, 0x9Fu, 0x7Du, 0x23u
	, 0xDCu, 0x82u, 0x60u, 0x3Eu, 0xBDu, 0xE3u, 0x01u, 0x5Fu, 0x1Eu, 0x40u, 0xA2u, 0xFCu, 0x7Fu, 0x21u, 0xC3u, 0x9Du
	, 0x41u, 0x1Fu, 0xFDu, 0xA3u, 0x20u, 0x7Eu, 0x9Cu, 0xC2u, 0x83u, 0xDDu, 0x3Fu, 0x61u, 0xE2u, 0xBCu, 0x5Eu, 0x00u
	, 0xB9u, 0xE7u, 0x05u, 0x5Bu, 0xD8u, 0x86u, 0x64u, 0x3Au, 0x7Bu, 0x25u, 0xC7u, 0x99u, 0x1Au, 0x44u, 0xA6u, 0xF8u
	, 0x24u, 0x7Au, 0x98u, 0xC6u, 0x45u, 0x1Bu, 0xF9u, 0xA7u, 0xE6u, 0xB8u, 0x5Au, 0x04u, 0x87u, 0xD9u, 0x3Bu, 0x65u
	, 0x9Au, 0xC4u, 0x26u, 0x78u, 0xFBu, 0xA5u, 0x47u, 0x19u, 0x58u, 0x06u, 0xE4u, 0xBAu, 0x39u, 0x67u, 0x85u, 0xDBu
	, 0x07u, 0x59u, 0xBBu, 0xE5u, 0x66u, 0x38u, 0xDAu, 0x84u, 0xC5u, 0x9Bu, 0x79u, 0x27u, 0xA4u, 0xFAu, 0x18u, 0x46u
	, 0x73u, 0x2Du, 0xCFu, 0x91u, 0x12u, 0x4Cu, 0xAEu, 0xF0u, 0xB1u, 0xEFu, 0x0Du, 0x53u, 0xD0u, 0x8Eu, 0x6Cu, 0x32u
	, 0xEEu, 0xB0u, 0x52u, 0x0Cu, 0x8Fu, 0xD1u, 0x33u, 0x6Du, 0x2Cu, 0x72u, 0x90u, 0xCEu, 0x4Du, 0x13u, 0xF1u, 0xAFu
	, 0x50u, 0x0Eu, 0xECu, 0xB2u, 0x31u, 0x6Fu, 0x8Du, 0xD3u, 0x92u, 0xCCu, 0x2Eu, 0x70u, 0xF3u, 0xADu, 0x4Fu, 0x11u
	, 0xCDu, 0x93u, 0x71u, 0x2Fu, 0xACu, 0xF2u, 0x10u, 0x4Eu, 0x0Fu, 0x51u, 0xB3u, 0xEDu, 0x6Eu, 0x30u, 0xD2u, 0x8Cu
	, 0x35u, 0x6Bu, 0x89u, 0xD7u, 0x54u, 0x0Au, 0xE8u, 0xB6u, 0xF7u, 0xA9u, 0x4Bu, 0x15u, 0x96u, 0xC8u, 0x2Au, 0x74u
	, 0xA8u, 0xF6u, 0x14u, 0x4Au, 0xC9u, 0x97u, 0x75u, 0x2Bu, 0x6Au, 0x34u, 0xD6u, 0x88u, 0x0Bu, 0x55u, 0xB7u, 0xE9u
	, 0x16u, 0x48u, 0xAAu, 0xF4u, 0x77u, 0x29u, 0xCBu, 0x95u, 0xD4u, 0x8Au, 0x68u, 0x36u, 0xB5u, 0xEBu, 0x09u, 0x57u
	, 0x8Bu, 0xD5u, 0x37u, 0x69u, 0xEAu, 0xB4u, 0x56u, 0x08u, 0x49u, 0x17u, 0xF5u, 0xABu, 0x28u, 0x76u, 0x94u, 0xCAu
	};
#define ETHSWT_STOP_SEC_CONFIG_DATA_PREBUILD
#include <EthSwt_SWIC_MemMap.h>

#define	ETHSWT_START_SEC_VAR_CLEARED
#include <EthSwt_SWIC_MemMap.h>
static struct {								/* アクセス異常記憶用 */
	const swic_reg_data_t *volatile	tbl;	/* 異常テーブル */
	volatile uint32					idx;	/* 異常位置 */
	volatile Std_ReturnType			err;	/* E_OK:CRC異常, E_NOT_OK:Spi異常 */
}	swic_Spi_Err;
static struct {
	const swic_reg_data_t	*tbl;	/* cmdに登録しているtbl */
	uint32					idx;	/* cmdに登録しているidx */
	uint8					wri;	/* cmdに登録している件数 */
	uint8					rcv;	/* datに登録している件数 */
	Spi_DataBufferType		cmd[768];/* SPI送信コマンド(3+(3*16)バイト):QAC対策で255件分 */
	Spi_DataBufferType		dat[768];/*SPI受信データ  (3*16バイト):QAC対策で255件分 */
}	swic_Spi_Cmd;

#define	ETHSWT_STOP_SEC_VAR_CLEARED
#include <EthSwt_SWIC_MemMap.h>

#define	ETHSWT_START_SEC_CODE
#include <EthSwt_SWIC_MemMap.h>
void EthSwt_SWIC_Spi_Init(void)
{
	swic_Spi_Err.tbl	= NULL_PTR;
	swic_Spi_Err.idx	= 0u;
	swic_Spi_Err.err	= E_OK;
	swic_Spi_Cmd.tbl	= NULL_PTR;
	swic_Spi_Cmd.idx	= 0u;
	swic_Spi_Cmd.wri	= 0u;
	swic_Spi_Cmd.rcv	= 0u;
}

static Std_ReturnType swic_Spi_SetTblErr(const swic_reg_data_t tbl[], const uint32 idx, const Std_ReturnType err)
{
	swic_Spi_Err.tbl	= tbl;
	swic_Spi_Err.idx	= idx;
	swic_Spi_Err.err	= err;
	return E_NOT_OK;
}

static uint8 swic_Spi_Crc8(const uint8 msg[], const uint32 len, const uint8 val)
{
	static const uint8	swic_Spi_Crc[]
	=	{ 0x00u, 0x5Eu, 0xBCu, 0xE2u, 0x61u, 0x3Fu, 0xDDu, 0x83u, 0xC2u, 0x9Cu, 0x7Eu, 0x20u, 0xA3u, 0xFDu, 0x1Fu, 0x41u
		, 0x9Du, 0xC3u, 0x21u, 0x7Fu, 0xFCu, 0xA2u, 0x40u, 0x1Eu, 0x5Fu, 0x01u, 0xE3u, 0xBDu, 0x3Eu, 0x60u, 0x82u, 0xDCu
		, 0x23u, 0x7Du, 0x9Fu, 0xC1u, 0x42u, 0x1Cu, 0xFEu, 0xA0u, 0xE1u, 0xBFu, 0x5Du, 0x03u, 0x80u, 0xDEu, 0x3Cu, 0x62u
		, 0xBEu, 0xE0u, 0x02u, 0x5Cu, 0xDFu, 0x81u, 0x63u, 0x3Du, 0x7Cu, 0x22u, 0xC0u, 0x9Eu, 0x1Du, 0x43u, 0xA1u, 0xFFu
		, 0x46u, 0x18u, 0xFAu, 0xA4u, 0x27u, 0x79u, 0x9Bu, 0xC5u, 0x84u, 0xDAu, 0x38u, 0x66u, 0xE5u, 0xBBu, 0x59u, 0x07u
		, 0xDBu, 0x85u, 0x67u, 0x39u, 0xBAu, 0xE4u, 0x06u, 0x58u, 0x19u, 0x47u, 0xA5u, 0xFBu, 0x78u, 0x26u, 0xC4u, 0x9Au
		, 0x65u, 0x3Bu, 0xD9u, 0x87u, 0x04u, 0x5Au, 0xB8u, 0xE6u, 0xA7u, 0xF9u, 0x1Bu, 0x45u, 0xC6u, 0x98u, 0x7Au, 0x24u
		, 0xF8u, 0xA6u, 0x44u, 0x1Au, 0x99u, 0xC7u, 0x25u, 0x7Bu, 0x3Au, 0x64u, 0x86u, 0xD8u, 0x5Bu, 0x05u, 0xE7u, 0xB9u
		, 0x8Cu, 0xD2u, 0x30u, 0x6Eu, 0xEDu, 0xB3u, 0x51u, 0x0Fu, 0x4Eu, 0x10u, 0xF2u, 0xACu, 0x2Fu, 0x71u, 0x93u, 0xCDu
		, 0x11u, 0x4Fu, 0xADu, 0xF3u, 0x70u, 0x2Eu, 0xCCu, 0x92u, 0xD3u, 0x8Du, 0x6Fu, 0x31u, 0xB2u, 0xECu, 0x0Eu, 0x50u
		, 0xAFu, 0xF1u, 0x13u, 0x4Du, 0xCEu, 0x90u, 0x72u, 0x2Cu, 0x6Du, 0x33u, 0xD1u, 0x8Fu, 0x0Cu, 0x52u, 0xB0u, 0xEEu
		, 0x32u, 0x6Cu, 0x8Eu, 0xD0u, 0x53u, 0x0Du, 0xEFu, 0xB1u, 0xF0u, 0xAEu, 0x4Cu, 0x12u, 0x91u, 0xCFu, 0x2Du, 0x73u
		, 0xCAu, 0x94u, 0x76u, 0x28u, 0xABu, 0xF5u, 0x17u, 0x49u, 0x08u, 0x56u, 0xB4u, 0xEAu, 0x69u, 0x37u, 0xD5u, 0x8Bu
		, 0x57u, 0x09u, 0xEBu, 0xB5u, 0x36u, 0x68u, 0x8Au, 0xD4u, 0x95u, 0xCBu, 0x29u, 0x77u, 0xF4u, 0xAAu, 0x48u, 0x16u
		, 0xE9u, 0xB7u, 0x55u, 0x0Bu, 0x88u, 0xD6u, 0x34u, 0x6Au, 0x2Bu, 0x75u, 0x97u, 0xC9u, 0x4Au, 0x14u, 0xF6u, 0xA8u
		, 0x74u, 0x2Au, 0xC8u, 0x96u, 0x15u, 0x4Bu, 0xA9u, 0xF7u, 0xB6u, 0xE8u, 0x0Au, 0x54u, 0xD7u, 0x89u, 0x6Bu, 0x35u
		};
    uint8	crc = ~val;
	uint32	i;
	for (i=0u ; i<len ; i++) {
		crc = swic_Spi_Crc[crc ^ msg[i]];
	}
	return ~crc;
}
void EthSwt_SWIC_Spi_ReqInit(void)
{
	swic_Spi_Cmd.tbl	= NULL_PTR;
	swic_Spi_Cmd.idx	= 0u;
	swic_Spi_Cmd.wri	= 0u;
	swic_Spi_Cmd.rcv	= 0u;
}
static Std_ReturnType swic_Spi_ReqWR(const Spi_DataBufferType *const cmd, const Spi_NumberOfDataType len, Spi_DataBufferType *const dat, const Spi_NumberOfDataType siz)
{
	Std_ReturnType		err;
	Spi_SeqResultType	rslt;
	(void)Spi_SetupEB((Spi_ChannelType)SPI_COMA_ID_ETHSW, cmd, dat, len);	/* [CodeSonar対応]Spi_SetupEBはE_OKしか返さない */
	err = Spi_SyncTransmit((Spi_SequenceType)SPI_COMA_SEQID_ETHSW);
	if (err != E_OK)		{ return E_NOT_OK; }
	rslt = Spi_GetSequenceResult((Spi_SequenceType)SPI_COMA_SEQID_ETHSW);
	if (rslt != SPI_SEQ_OK) { return E_NOT_OK; }
	return E_OK;
}
Std_ReturnType EthSwt_SWIC_Spi_WriteSPI(const swic_reg_data_t tbl[], const uint32 idx, const uint16 SndData)
{
	const uint32		devAddr = tbl[idx].devAddr;
	const uint32		regAddr = tbl[idx].regAddr;
	Std_ReturnType		err;
	uint8				crc;
	Spi_DataBufferType	dat = 0u;
	swic_Spi_Cmd.wri	= 0u;
	swic_Spi_Cmd.rcv	= 0u;
	swic_Spi_Cmd.cmd[0]	= (uint8)0xB0u;	/* W:1,M:0,L:1,S:1,MC:x */
	swic_Spi_Cmd.cmd[1]	= (uint8)((devAddr >> 3) & 0x03u);
	swic_Spi_Cmd.cmd[2]	= (uint8)((devAddr << 5) | (regAddr & 0x1Fu));
	swic_Spi_Cmd.cmd[3]	= (uint8)(SndData >> 8);
	swic_Spi_Cmd.cmd[4]	= (uint8)(SndData);
	crc = swic_Spi_Crc8Cmd(swic_Spi_Cmd.cmd, 5u);
	swic_Spi_Cmd.cmd[5]	= crc;
	err = swic_Spi_ReqWR(swic_Spi_Cmd.cmd, 6u, &dat, 1u);
	if (err == E_OK) {
		if (dat == swic_Spi_CrcOK[crc])	{ return err; }
	}
	return swic_Spi_SetTblErr(tbl, idx, err);
}
static Std_ReturnType swic_Spi_Write(const swic_reg_data_t tbl[], const uint8 wri, const uint32 idx)
{
	const uint32			devAddr = tbl[idx].devAddr;
	const uint32			regAddr = tbl[idx].regAddr;
	Std_ReturnType			err;
	uint8					i;
	Spi_NumberOfDataType	len;
	uint8					crc;
	Spi_DataBufferType		dat = 0u;
	swic_Spi_Cmd.wri	= 0u;
	swic_Spi_Cmd.rcv	= 0u;
	swic_Spi_Cmd.cmd[0]	= (uint8)(0xF0u | wri);	/* W:1,M:x,L:1,S:1,MC:x [残りbitは1にするのでwriはそのまま]*/
	swic_Spi_Cmd.cmd[1]	= (uint8)((devAddr >> 3) & 0x03u);
	swic_Spi_Cmd.cmd[2]	= (uint8)((devAddr << 5) | (regAddr & 0x1Fu));
	crc = swic_Spi_Crc8Cmd(swic_Spi_Cmd.cmd, 3u);
	len = 3u;
	for (i=0u ; i<wri ; i++) {
		const uint16	SndData = tbl[(sint32)idx + (sint32)i].value;	/* [QAC対策](sint32) */
		swic_Spi_Cmd.cmd[len]							= (uint8)(SndData >> 8);
		swic_Spi_Cmd.cmd[len + (Spi_NumberOfDataType)1]	= (uint8)(SndData);
		crc = swic_Spi_Crc8(&swic_Spi_Cmd.cmd[len], 2u, crc);
		swic_Spi_Cmd.cmd[len + (Spi_NumberOfDataType)2]	= crc;
		len = len + (Spi_NumberOfDataType)3;
	}
	err = swic_Spi_ReqWR(swic_Spi_Cmd.cmd, len, &dat, 1u);
	if (err == E_OK) {
		if (dat == swic_Spi_CrcOK[crc])	{
			swic_Spi_Cmd.tbl	= tbl;
			swic_Spi_Cmd.idx	= idx;
			swic_Spi_Cmd.wri	= wri;
			return err;
		}
	}
	return swic_Spi_SetTblErr(tbl, idx, err);
}
static uint8 swic_Spi_WriteCnt(const swic_reg_data_t tbl[], const uint32 cnt, const uint32 idx)
{
	const uint8	devAddr = tbl[idx].devAddr;
	const uint8	regAddr = tbl[idx].regAddr;
	uint8		wri = 0u;
	uint32		off;
	for (off=idx ; off < cnt ; off++) {					/* 件数取得 */
		if (tbl[off].devAddr != devAddr)				{ break; }
		if (tbl[off].regAddr != (regAddr + wri))		{ break; }
		if (tbl[off].regCtrl != REG_CTRL_WRITE)			{ break; }
/*		if (tbl[off].surveillance != SURVEILLANCE_OFF)	{ break; }	リードバックしないので同じ動作 */
		wri = wri + (uint8)1;
		if (wri >= (uint8)16)							{ break; }
	}
	return wri;
}
Std_ReturnType EthSwt_SWIC_Spi_Write(const swic_reg_data_t tbl[], const uint32 cnt, const uint32 idx)
{
	uint8	wri;
	if (tbl == swic_Spi_Cmd.tbl) {
		if (idx > swic_Spi_Cmd.idx) {	/* 同じ要求は再書き込みする */
			const sint32	pos = (sint32)idx - (sint32)swic_Spi_Cmd.idx;
			if (pos < (sint32)swic_Spi_Cmd.wri) { return E_OK; }
		}
	}
	wri = swic_Spi_WriteCnt(tbl, cnt, idx);
	if (wri < 2u) { return EthSwt_SWIC_Spi_WriteSPI(tbl, idx, tbl[idx].value); }
	return swic_Spi_Write(tbl, wri, idx);
}
Std_ReturnType EthSwt_SWIC_Spi_ReadSPI(const swic_reg_data_t tbl[], const uint32 idx, uint16 *const RcvData)
{
	const uint32		devAddr = tbl[idx].devAddr;
	const uint32		regAddr = tbl[idx].regAddr;
	Spi_DataBufferType	cmd[4];
	Std_ReturnType		err;
	uint8				crc;
	swic_Spi_Cmd.wri	= 0u;
	swic_Spi_Cmd.rcv	= 0u;
	cmd[0]				= 0x30u;				/* W:0,M:0,L:1,S:1,MC:0 */
	cmd[1]				= (uint8)((devAddr >> 3) & 0x03u);
	cmd[2]				= (uint8)((devAddr << 5) | (regAddr & 0x1Fu));
	err = swic_Spi_ReqWR(cmd, 3u, swic_Spi_Cmd.dat, 3u);
	if (err == E_OK) {
		crc = swic_Spi_Crc8Cmd(cmd, 3u);
		crc = swic_Spi_Crc8(swic_Spi_Cmd.dat, 2u, crc);
		if (swic_Spi_Cmd.dat[2] == crc) {
			*RcvData = (uint16)(((uint32)swic_Spi_Cmd.dat[0] << 8) | (uint32)swic_Spi_Cmd.dat[1]);
			return err;
		}
	}
	return swic_Spi_SetTblErr(tbl, idx, err);
}
static Std_ReturnType swic_Spi_Read(const swic_reg_data_t tbl[], const uint8 rcv, const uint32 idx, uint16 *const RcvData)
{
	const uint32		devAddr = tbl[idx].devAddr;
	const uint32		regAddr = tbl[idx].regAddr;
	Spi_DataBufferType	cmd[4];
	Std_ReturnType		err;
	uint8				crc;
	swic_Spi_Cmd.wri	= 0u;
	swic_Spi_Cmd.rcv	= 0u;
	cmd[0]				= (uint8)(0x70u | (rcv & 0x0Fu));	/* W:0,M:x,L:1,S:1,MC:x */
	cmd[1]				= (uint8)((devAddr >> 3) & 0x03u);
	cmd[2]				= (uint8)((devAddr << 5) | (regAddr & 0x1Fu));
	err = swic_Spi_ReqWR(cmd, 3u, swic_Spi_Cmd.dat, rcv * (uint16)3);
	if (err == E_OK) {
		swic_Spi_Cmd.tbl	= tbl;
		swic_Spi_Cmd.idx	= idx;
		swic_Spi_Cmd.rcv	= rcv;
		crc = swic_Spi_Crc8Cmd(cmd, 3u);
		crc = swic_Spi_Crc8(swic_Spi_Cmd.dat, 2u, crc);
		if (swic_Spi_Cmd.dat[2] == crc) {
			*RcvData = (uint16)(((uint32)swic_Spi_Cmd.dat[0] << 8) | (uint32)swic_Spi_Cmd.dat[1]);
			return err;
		}
	}
	return swic_Spi_SetTblErr(tbl, idx, err);
}
static uint8 swic_Spi_ReadCnt(const swic_reg_data_t tbl[], const uint32 cnt, const uint32 idx)
{
	const uint8	devAddr = tbl[idx].devAddr;
	const uint8	regAddr = tbl[idx].regAddr;
	uint8		rcv = 0u;
	uint32		off;
	for (off=idx ; off < cnt ; off++) {					/* 件数取得 */
		if (tbl[off].devAddr != devAddr)				{ break; }
		if (tbl[off].regAddr != (regAddr + rcv))		{ break; }
		if (tbl[off].regCtrl != REG_CTRL_READ)			{ break; }
		if (tbl[off].surveillance != SURVEILLANCE_OFF)	{ break; }
		rcv = rcv + (uint8)1;
		if (rcv >= (uint8)16)							{ break; }
	}
	return rcv;
}
Std_ReturnType EthSwt_SWIC_Spi_Read(const swic_reg_data_t tbl[], const uint32 cnt, const uint32 idx, uint16 *const RcvData)
{
	uint8	rcv;
	if (tbl == swic_Spi_Cmd.tbl) {
		if (idx > swic_Spi_Cmd.idx) {	/* 同じ要求は再読み込みする */
			const sint32	pos = (sint32)idx - (sint32)swic_Spi_Cmd.idx;
			if (pos < (sint32)swic_Spi_Cmd.rcv) {
				const sint32	off = (sint32)(uint8)pos * 3L;
				uint8			crc;
				crc = swic_Spi_Crc8(&swic_Spi_Cmd.dat[off], 2u, swic_Spi_Cmd.dat[off - 1L]);	/* 2個目以降のみ */
				if (swic_Spi_Cmd.dat[off + 2L] == crc) {
					*RcvData = (uint16)(((uint32)swic_Spi_Cmd.dat[off] << 8) | (uint32)swic_Spi_Cmd.dat[off + 1L]);
					return E_OK;
				}
			}
		}
	}
	rcv = swic_Spi_ReadCnt(tbl, cnt, idx);
	if (rcv < 2u) { return EthSwt_SWIC_Spi_ReadSPI(tbl, idx, RcvData); }	/* 値待ちを考慮しバッファしない */
	return swic_Spi_Read(tbl, rcv, idx, RcvData);
}
#define	ETHSWT_STOP_SEC_CODE
#include <EthSwt_SWIC_MemMap.h>