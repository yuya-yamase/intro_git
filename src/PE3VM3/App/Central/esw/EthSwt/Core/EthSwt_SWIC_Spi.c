/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_Spi.c                                            */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
#include <Spi_Ucfg.h>
#include <Spi.h>
/* -------------------------------------------------------------------------- */
#include <LIB.h>
#include <EthSwt_SWIC_initRegCommon.h>
#include "EthSwt_SWIC_Spi.h"
/* -------------------------------------------------------------------------- */
#define	swic_SpiS1_Crc8Cmd(a,b)	swic_SpiS1_Crc8(a,b,0u)
/* -------------------------------------------------------------------------- */
#define ETHSWT_START_SEC_CONFIG_DATA_PREBUILD
#include <EthSwt_SWIC_MemMap.h>
static const uint8	swic_SpiS1_CrcOK[]	/* swic_SpiS1_Crc8({0xFF}, 1, crc)のテーブル:~swic_SpiS1_Crc[]と同じ */
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
}	swic_SpiS1_Err;
static struct {
	uint8				Paddr;				/* cmdに登録しているPaddr */
	uint8				Raddr;				/* cmdに登録しているRaddr */
	uint8				wri;				/* cmdに登録している件数 */
	uint8				rcv;				/* datに登録している件数 */
	Spi_DataBufferType	cmd[64];			/* SPI送信コマンド(3+(3*16)+1バイト) */
	Spi_DataBufferType	rea[64];			/* SPI受信コマンド(3+(3*16)+1バイト) */
	Spi_DataBufferType	dat[64];			/* SPI受信データ  (3+(3*16)+1バイト) */
}	swic_SpiS1_Cmd;
static volatile uint8 swic_SpiS1_RegErr;

#define	ETHSWT_STOP_SEC_VAR_CLEARED
#include <EthSwt_SWIC_MemMap.h>

#define	ETHSWT_START_SEC_CODE
#include <EthSwt_SWIC_MemMap.h>
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Spi_Init(void)
{
	swic_SpiS1_Err.tbl	= NULL_PTR;
	swic_SpiS1_Err.idx	= 0u;
	swic_SpiS1_Err.err	= E_OK;
	swic_SpiS1_Cmd.Paddr= 0u;
	swic_SpiS1_Cmd.Raddr= 0u;
	swic_SpiS1_Cmd.wri	= 0u;
	swic_SpiS1_Cmd.rcv	= 0u;
	LIB_memset(swic_SpiS1_Cmd.rea, 0u, sizeof(swic_SpiS1_Cmd.rea));	/* データ部分を0クリアしておく */
	swic_SpiS1_RegErr	= STD_OFF;
}
/* -------------------------------------------------------------------------- */
static Std_ReturnType swic_SpiS1_SetTblErr(const swic_reg_data_t tbl[], const uint32 idx, const Std_ReturnType err)
{
	swic_SpiS1_Err.tbl	= tbl;
	swic_SpiS1_Err.idx	= idx;
	swic_SpiS1_Err.err	= err;
	return E_NOT_OK;
}
/* -------------------------------------------------------------------------- */
static uint8 swic_SpiS1_Crc8(const uint8 msg[], const uint32 len, const uint8 val)
{
	static const uint8	swic_SpiS1_Crc[]
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
		crc = swic_SpiS1_Crc[crc ^ msg[i]];
	}
	return ~crc;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Spi_ReqInit(void)
{
	swic_SpiS1_Cmd.Paddr= 0u;
	swic_SpiS1_Cmd.Raddr= 0u;
	swic_SpiS1_Cmd.wri	= 0u;
	swic_SpiS1_Cmd.rcv	= 0u;
}
/* -------------------------------------------------------------------------- */
static Std_ReturnType swic_SpiS1_Req1(const Spi_DataBufferType *const cmd, Spi_DataBufferType *const dat, const Spi_NumberOfDataType len)
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
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_Spi_WriteSPI(const swic_reg_data_t tbl[], const uint32 idx, const uint16 SndData)
{
	const uint8		Paddr = tbl[idx].devAddr;
	const uint8		Raddr = tbl[idx].regAddr;
	Std_ReturnType	err;
	uint8			crc;
	swic_SpiS1_Cmd.wri		= 0u;
	swic_SpiS1_Cmd.rcv		= 0u;
	swic_SpiS1_Cmd.cmd[0]	= (uint8)0xB0u;	/* W:1,M:0,L:1,S:1,MC:x */
	swic_SpiS1_Cmd.cmd[1]	= (uint8)((Paddr >> 3) & 0x03u);
	swic_SpiS1_Cmd.cmd[2]	= (uint8)((Paddr << 5) | (Raddr & 0x1Fu));
	swic_SpiS1_Cmd.cmd[3]	= (uint8)(SndData >> 8);
	swic_SpiS1_Cmd.cmd[4]	= (uint8)(SndData);
	crc = swic_SpiS1_Crc8Cmd(swic_SpiS1_Cmd.cmd, 5u);
	swic_SpiS1_Cmd.cmd[5]	= crc;
	swic_SpiS1_Cmd.cmd[6]	= 0x00u;
	err = swic_SpiS1_Req1(swic_SpiS1_Cmd.cmd, swic_SpiS1_Cmd.dat, 7);
	if (err == E_OK) {
		if (swic_SpiS1_Cmd.dat[6] == swic_SpiS1_CrcOK[crc])	{ return err; }
	}
    return swic_SpiS1_SetTblErr(tbl, idx, err);
}
/* -------------------------------------------------------------------------- */
static uint8 swic_SpiS1_WriteCnt(const swic_reg_data_t tbl[], const uint32 cnt, const uint32 idx)
{
	const uint8	Paddr = tbl[idx].devAddr;
	const uint8	Raddr = tbl[idx].regAddr;
	uint8		wri = 0u;
	uint32		off;
	for (off=idx ; off < cnt ; off++) {					/* 件数取得 */
		if (tbl[off].devAddr != Paddr)					{ break; }
		if (tbl[off].regAddr != (Raddr + wri))			{ break; }
		if (tbl[off].regCtrl != REG_CTRL_WRITE)			{ break; }
		if (tbl[off].surveillance != SURVEILLANCE_OFF)	{ break; }
		wri = wri + (uint8)1;
		if (wri >= (uint8)16)							{ break; }
	}
	return wri;
}
/* -------------------------------------------------------------------------- */
static Std_ReturnType swic_SpiS1_WriteDat(const uint8 Paddr, const uint8 Raddr)
{
	uint8	wri;
	if (swic_SpiS1_Cmd.Paddr != Paddr)	{ return E_NOT_OK; }
	if (swic_SpiS1_Cmd.Raddr >= Raddr)	{ return E_NOT_OK; }	/* 同じ要求は再書き込みする */
	wri = Raddr - swic_SpiS1_Cmd.Raddr;
	if (swic_SpiS1_Cmd.wri <= wri)		{ return E_NOT_OK; }
	return E_OK;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_Spi_Write(const swic_reg_data_t tbl[], const uint32 cnt, const uint32 idx)
{
	const uint8				Paddr = tbl[idx].devAddr;
	const uint8				Raddr = tbl[idx].regAddr;
	Std_ReturnType			err;
	uint8					wri, i;
	Spi_NumberOfDataType	len;
	uint8					crc;
	err = swic_SpiS1_WriteDat(Paddr, Raddr);
	if (err == E_OK)	{ return err; }
	wri = swic_SpiS1_WriteCnt(tbl, cnt, idx);
	if (wri < 2u)		{ return EthSwt_SWIC_Spi_WriteSPI(tbl, idx, tbl[idx].value); }
	swic_SpiS1_Cmd.wri		= 0u;
	swic_SpiS1_Cmd.rcv		= 0u;
	swic_SpiS1_Cmd.cmd[0]	= (uint8)(0xF0u | (wri & 0x0Fu));	/* W:1,M:x,L:1,S:1,MC:x */
	swic_SpiS1_Cmd.cmd[1]	= (uint8)((Paddr >> 3) & 0x03u);
	swic_SpiS1_Cmd.cmd[2]	= (uint8)((Paddr << 5) | (Raddr & 0x1Fu));
	crc = swic_SpiS1_Crc8Cmd(swic_SpiS1_Cmd.cmd, 3u);
	len = 3u;
	for (i=0u ; i<wri ; i++) {
		const uint16	SndData = tbl[(sint32)idx + (sint32)i].value;	/* [QAC対策](sint32) */
		swic_SpiS1_Cmd.cmd[len]								= (uint8)(SndData >> 8);
		swic_SpiS1_Cmd.cmd[len + (Spi_NumberOfDataType)1]	= (uint8)(SndData);
		crc = swic_SpiS1_Crc8(&swic_SpiS1_Cmd.cmd[len], 2u, crc);
		swic_SpiS1_Cmd.cmd[len + (Spi_NumberOfDataType)2]	= crc;
		len = len + (Spi_NumberOfDataType)3;
	}
	swic_SpiS1_Cmd.cmd[len] = 0x00u;
	err = swic_SpiS1_Req1(swic_SpiS1_Cmd.cmd, swic_SpiS1_Cmd.dat, len + (Spi_NumberOfDataType)1);
	if (err == E_OK) {
		if (swic_SpiS1_Cmd.dat[len] == swic_SpiS1_CrcOK[crc]) {
			swic_SpiS1_Cmd.Paddr= Paddr;
			swic_SpiS1_Cmd.Raddr= Raddr;
			swic_SpiS1_Cmd.wri	= wri;
			return err;
		}
	}
    return swic_SpiS1_SetTblErr(tbl, idx, err);
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_Spi_ReadSPI(const swic_reg_data_t tbl[], const uint32 idx, uint16 *const RcvData)
{
	const uint8			Paddr = tbl[idx].devAddr;
	const uint8			Raddr = tbl[idx].regAddr;
	Spi_DataBufferType	cmd[8];
	Std_ReturnType		err;
	uint8				crc;
	swic_SpiS1_Cmd.wri	= 0u;
	swic_SpiS1_Cmd.rcv	= 0u;
	cmd[0]				= 0x30u;				/* W:0,M:0,L:1,S:1,MC:0 */
	cmd[1]				= (uint8)((Paddr >> 3) & 0x03u);
	cmd[2]				= (uint8)((Paddr << 5) | (Raddr & 0x1Fu));
	cmd[3]				= 0x00u;
	cmd[4]				= 0x00u;
	cmd[5]				= 0x00u;
	err = swic_SpiS1_Req1(cmd, swic_SpiS1_Cmd.dat, 6u);
	if (err == E_OK) {
		crc = swic_SpiS1_Crc8Cmd(cmd, 3u);
		crc = swic_SpiS1_Crc8(&swic_SpiS1_Cmd.dat[3], 2u, crc);
		if (swic_SpiS1_Cmd.dat[5] == crc) {
			*RcvData = (uint16)(((uint32)swic_SpiS1_Cmd.dat[3] << 8) | (uint32)swic_SpiS1_Cmd.dat[4]);
			return err;
		}
	}
    return swic_SpiS1_SetTblErr(tbl, idx, err);
}
/* -------------------------------------------------------------------------- */
static uint8 swic_SpiS1_ReadCnt(const swic_reg_data_t tbl[], const uint32 cnt, const uint32 idx)
{
	const uint8	Paddr = tbl[idx].devAddr;
	const uint8	Raddr = tbl[idx].regAddr;
	uint8		rcv = 0u;
	uint32		off;
	for (off=idx ; off < cnt ; off++) {					/* 件数取得 */
		if (tbl[off].devAddr != Paddr)					{ break; }
		if (tbl[off].regAddr != (Raddr + rcv))			{ break; }
		if (tbl[off].regCtrl != REG_CTRL_READ)			{ break; }
		if (tbl[off].surveillance != SURVEILLANCE_OFF)	{ break; }
		rcv = rcv + (uint8)1;
		if (rcv >= (uint8)16)							{ break; }
	}
	return rcv;
}
/* -------------------------------------------------------------------------- */
static Std_ReturnType swic_Spi_ReadDat(const uint8 Paddr, const uint8 Raddr, uint16 *const RcvData)
{
	uint8	rcv;
	sint32	off;
	uint8	crc;
	if (swic_SpiS1_Cmd.Paddr != Paddr)		{ return E_NOT_OK; }
	if (swic_SpiS1_Cmd.Raddr >= Raddr)		{ return E_NOT_OK; }	/* 同じ要求は再読み込みする */
	rcv = Raddr - swic_SpiS1_Cmd.Raddr;
	if (swic_SpiS1_Cmd.rcv <= rcv)			{ return E_NOT_OK; }
	off = ((sint32)rcv * 3L) + 3L;
	crc = swic_SpiS1_Crc8(&swic_SpiS1_Cmd.dat[off], 2u, swic_SpiS1_Cmd.dat[off - 1L]);	/* 2個目以降のみ */
	if (swic_SpiS1_Cmd.dat[off + 2L] != crc){ return E_NOT_OK; }
	if (RcvData != NULL_PTR) {
		*RcvData = (uint16)(((uint32)swic_SpiS1_Cmd.dat[off] << 8) | (uint32)swic_SpiS1_Cmd.dat[off + 1L]);
	}
	return E_OK;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_Spi_Read(const swic_reg_data_t tbl[], const uint32 cnt, const uint32 idx, uint16 *const RcvData)
{
	const uint8		Paddr = tbl[idx].devAddr;
	const uint8		Raddr = tbl[idx].regAddr;
	Std_ReturnType	err;
	uint8			rcv;
	uint8			crc;
	err = swic_Spi_ReadDat(Paddr, Raddr, RcvData);
	if (err == E_OK)	{ return err; }
	rcv = swic_SpiS1_ReadCnt(tbl, cnt, idx);
	if (rcv < 2u)		{ return EthSwt_SWIC_Spi_ReadSPI(tbl, idx, RcvData); }	/* 値待ちを考慮しバッファしない */
	swic_SpiS1_Cmd.wri		= 0u;
	swic_SpiS1_Cmd.rcv		= 0u;
	swic_SpiS1_Cmd.rea[0]	= (uint8)(0x70u | (rcv & 0x0Fu));	/* W:0,M:x,L:1,S:1,MC:x */
	swic_SpiS1_Cmd.rea[1]	= (uint8)((Paddr >> 3) & 0x03u);
	swic_SpiS1_Cmd.rea[2]	= (uint8)((Paddr << 5) | (Raddr & 0x1Fu));
	err = swic_SpiS1_Req1(swic_SpiS1_Cmd.rea, swic_SpiS1_Cmd.dat, (rcv * (uint16)3) + (uint16)3);
	if (err == E_OK) {
		swic_SpiS1_Cmd.Paddr= Paddr;
		swic_SpiS1_Cmd.Raddr= Raddr;
		swic_SpiS1_Cmd.rcv	= rcv;
		crc = swic_SpiS1_Crc8Cmd(swic_SpiS1_Cmd.rea, 3u);
		crc = swic_SpiS1_Crc8(&swic_SpiS1_Cmd.dat[3], 2u, crc);
		if (swic_SpiS1_Cmd.dat[5] == crc) {
			*RcvData = (uint16)(((uint32)swic_SpiS1_Cmd.dat[3] << 8) | (uint32)swic_SpiS1_Cmd.dat[4]);
			return err;
		}
	}
    return swic_SpiS1_SetTblErr(tbl, idx, err);
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_SpiRegChkNotify(uint32 status)
{
	(void)status;
	
	swic_SpiS1_RegErr = STD_ON;
	
	return;
}
/* -------------------------------------------------------------------------- */
uint8 EthSwt_SWIC_Spi_GetSpiRegErr(void)
{
	uint8 ret = swic_SpiS1_RegErr;
	swic_SpiS1_RegErr = STD_OFF;
	return ret;
}
#define	ETHSWT_STOP_SEC_CODE
#include <EthSwt_SWIC_MemMap.h>
