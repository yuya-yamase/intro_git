/****************************************************************************/
/*【ファイル名】xspi_sub.c                                                  */
/*【モジュール名】XSPIドライバ(サブ処理)                                    */
/****************************************************************************/
/****************************
*		include	files		*
****************************/
#include "xspi_internal.h"

/************************************************************************
*																		*
*				Ｄefine Ｄeclare Ｓection								*
*																		*
************************************************************************/
/****************************
*		variables			*
****************************/
#pragma ghs section bss = XSPI_RAM_SECTION
BF_DRV_SPI_RING		bf_drv_SpiMng_central;			/* XSPI管理情報 */
#pragma ghs section

#ifdef XSPI_DEBUG
uint8	bf_drv_Dbg_ErrInfo_central;				/* デバッグ用エラー情報 */
#endif	/* XSPI_DEBUG */

/****************************
*		prototype			*
****************************/
void	fc_drv_ClearXSpiMng_central( void );						/* XSPI管理情報初期化 */
void	fc_drv_SpiSetErrInfoKind_central( uint8 kind );				/* エラー種別情報設定 */
void	fc_drv_SpiClearErrInfoKind_central( uint8 kind );			/* エラー種別情報クリア */
#ifdef XSPI_DEBUG
void	fc_drv_SpiSetDbgErrInfo_central( uint8 err_info );			/* デバッグ用エラー情報設定 */
#endif	/* XSPI_DEBUG */

uint8	fc_drv_getRcvBufPage_central( void );						/* 受信バッファページ取得 */
uint8	fc_drv_getSndBufPage_central( void );						/* 送信バッファページ取得 */
uint8	fc_drv_ReadBuf_central( uint8* p_addr, uint32 size );		/* 受信データ読み出し */
uint8	fc_drv_WriteBuf_central( const uint8* p_addr, uint32 size );/* 送信データ書き込み */
#if (XSPI_DATA_BUFFER_central != XSPI_DATA_BUFFER_DOUBLE)
void	fc_drv_SpiRcvDpageRenew_central( void );					/* ドライバ受信バッファページ更新(リングバッファ用) */
void	fc_drv_SpiSendDpageRenew_central( void );					/* ドライバ送信バッファページ更新(リングバッファ用) */
#endif /* XSPI_DATA_BUFFER_central */
#if (XSPI_DATA_CHECK_central != XSPI_DATA_CHECK_NONE)
uint8	fc_drv_CheckIntegrityData_central( const uint8* p_frame );	/* 整合性データチェック */
void	fc_drv_AddIntegrityData_central( uint8* p_frame );			/* 整合性データ付加 */
#endif	/* XSPI_DATA_CHECK_central */

/****************************************************************************
*																			*
*		SYMBOL		:	XSPI_MEMSET											*
*																			*
*		DESCRIPTION	:	memset関数(XSPI用)									*
*																			*
*		PARAMETER	:	OUT		:	void*	設定先アドレス					*
*						IN 		:	uint8	設定値							*
*						IN 		:	uint32	設定サイズ						*
*																			*
*						OUT 	:	None									*
*																			*
*						RET 	:	None									*
*																			*
*****************************************************************************/
static void	XSPI_MEMSET_central (
	void * p_dst, uint8 value, uint32 size
)
{
	uint8 *p_udst = (uint8 *)p_dst;
	while (0UL < size)
	{
		size--;
		*p_udst = value;
		p_udst++;
	}
}

/****************************************************************************
*																			*
*		SYMBOL		:	XSPI_MEMCPY											*
*																			*
*		DESCRIPTION	:	memcpy関数(XSPI用)									*
*																			*
*		PARAMETER	:	OUT 	:	void*		コピー先アドレス			*
*						IN		:	const void*	コピー元アドレス			*
*						IN 		:	uint32		コピーサイズ				*
*																			*
*						OUT 	:	None									*
*																			*
*						RET 	:	None									*
*																			*
****************************************************************************/
static	void	XSPI_MEMCPY_central (
	void * p_dst, const void * p_src, uint32 size
)
{
	uint8 *p_usrc = (uint8 *)p_src;
	uint8 *p_udst = (uint8 *)p_dst;
	while (0UL < size)
	{
		size--;
		*p_udst = *p_usrc;
		p_usrc++;
		p_udst++;
	}
}

/****************************************************************************/
/**************				ドライバ内部サブ処理				*************/
/****************************************************************************/
/****************************************************************************
*																			*
*		SYMBOL		: fc_drv_ClearXSpiMng									*
*																			*
*		DESCRIPTION	: XSPI管理情報初期化									*
*																			*
*		PARAMETER	: IN  :	None											*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :	None											*
*																			*
****************************************************************************/
void	fc_drv_ClearXSpiMng_central(
	void
)
{
	/* XSPI管理情報初期化 */
	XSPI_MEMSET_central( &bf_drv_SpiMng_central, 0U, sizeof(bf_drv_SpiMng_central) );

	/* [T.B.D]暫定対応 初回データスキップ(初回受信バッファに整合性データ付与) */
#if (XSPI_DATA_CHECK_central != XSPI_DATA_CHECK_NONE)
	fc_drv_AddIntegrityData_central(bf_drv_SpiMng_central.rcv.page[0].dat);
	fc_drv_AddIntegrityData_central(bf_drv_SpiMng_central.rcv.page[1].dat);
#endif	/* XSPI_DATA_CHECK_central */

#if (XSPI_DATA_BUFFER_central == XSPI_DATA_BUFFER_RING)
	/* 送信用ダミーページ情報にデータ確定を設定 */
	bf_drv_SpiMng_central.snd.page[XSPI_SND_PAGE].inf = SND_FRM_DATA_FIX;
#endif	/* XSPI_DATA_BUFFER_central */

#ifdef XSPI_DEBUG
	bf_drv_Dbg_ErrInfo_central = 0U;		/* デバッグ用エラー情報初期化 */
#endif	/* XSPI_DEBUG */
}

/****************************************************************************
*																			*
*		SYMBOL		: fc_drv_SpiSetErrInfoKind								*
*																			*
*		DESCRIPTION	: ドライバ用エラー情報設定								*
*																			*
*		PARAMETER	: IN  :	uint8 kind：エラー種別							*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :	None											*
*																			*
****************************************************************************/
void	fc_drv_SpiSetErrInfoKind_central(
	uint8 kind
)
{
	/* エラー情報に種別をセット */
	bf_drv_SpiMng_central.err_info |= (uint8)(kind & (uint8)XSPI_ERR_MSK_KIND) ;
}

/****************************************************************************
*																			*
*		SYMBOL		: fc_drv_SpiclearErrInfoKind							*
*																			*
*		DESCRIPTION	: ドライバ用エラー情報クリア							*
*																			*
*		PARAMETER	: IN  :	uint8 kind：エラー種別							*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :	None											*
*																			*
****************************************************************************/
void	fc_drv_SpiClearErrInfoKind_central(
	uint8 kind
)
{
	/* エラー情報種別をクリア */
	bf_drv_SpiMng_central.err_info &= (~kind) ;
}

#ifdef XSPI_DEBUG
/****************************************************************************
*																			*
*		SYMBOL		: fc_drv_SpiSetDbgErrInfo								*
*																			*
*		DESCRIPTION	: デバッグ用エラー情報設定処理							*
*																			*
*		PARAMETER	: IN  :	uint8 デバッグ用エラー情報						*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :	None											*
*																			*
****************************************************************************/
void	fc_drv_SpiSetDbgErrInfo_central(
	uint8 err_info
)
{
	/*  デバッグ用エラー情報にエラー情報をセット */
	bf_drv_Dbg_ErrInfo_central |= (uint8)(err_info & (uint8)XSPI_ERR_MSK_DBG);
}
#endif	/* XSPI_DEBUG */

/****************************************************************************/
/**************				バッファ制御処理					*************/
/****************************************************************************/
#if (XSPI_DATA_BUFFER_central == XSPI_DATA_BUFFER_RING)
/****************************************************************************
*																			*
*		SYMBOL		: fc_drv_getRcvBufPage									*
*																			*
*		DESCRIPTION	: 受信バッファページ取得処理（リングバッファ）			*
*																			*
*		PARAMETER	: IN  :	None											*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :													*
*							uint8	受信バッファページ						*
*																			*
****************************************************************************/
uint8 fc_drv_getRcvBufPage_central(
	void
)
{
	uint8 page;

	page = bf_drv_SpiMng_central.rcv.page_drv;

	/* 受信用バッファ空チェック */
	if( bf_drv_SpiMng_central.rcv.page[page].inf != (uint8)RCV_FRM_DATA_NON )
	{	/* 受信用バッファにデータあり（固定アドレスへ受信＆破棄） */
		page = XSPI_RCV_PAGE;
#ifdef XSPI_DEBUG
		fc_drv_SpiSetDbgErrInfo_central( XSPI_ERR_DBG_OVERFLOW );
#endif	/* XSPI_DEBUG */
	}

	/* 受信中バッファページ保存 */
	bf_drv_SpiMng_central.rcv.page_rcv = page;

	return ( page );
}

/****************************************************************************
*																			*
*		SYMBOL		: fc_drv_getSndBufPage									*
*																			*
*		DESCRIPTION	: 送信バッファページ取得処理（リングバッファ）			*
*																			*
*		PARAMETER	: IN  :	None											*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :													*
*							uint8	送信バッファページ						*
*																			*
****************************************************************************/
uint8 fc_drv_getSndBufPage_central(
	void
)
{
	uint8 page;

	page = bf_drv_SpiMng_central.snd.page_drv;

	/* 送信用バッファデータありチェック */
	if( bf_drv_SpiMng_central.snd.page[page].inf != (uint8)SND_FRM_DATA_FIX )
	{	/* 送信用バッファ内にデータセットされていない（固定アドレスを指定して空データ送信） */
		page = XSPI_SND_PAGE;
	}

	/* 送信中バッファページ保存 */
	bf_drv_SpiMng_central.snd.page_send = page;

	return ( page );
}

/****************************************************************************
*																			*
*		SYMBOL		: fc_drv_ReadBuf										*
*																			*
*		DESCRIPTION	: 受信バッファ読み出し(リングバッファ)					*
*																			*
*		PARAMETER	: OUT :	uint8*	読み出しデータアドレス					*
*					  IN  :	uint32	読み出しデータサイズ					*
*																			*
*					  RET :													*
*							uint8	読み出し結果							*
*								XSPI_NG	(0x00)	読み出し失敗	 			*
*								XSPI_OK	(0x01)	読み出し成功	 	 		*
*																			*
****************************************************************************/
uint8	fc_drv_ReadBuf_central(
	uint8* p_addr, uint32 size
)
{
	uint8 result = XSPI_NG;
	uint8* prcv_buf;
	uint8 rcv_inf;
	uint8 page;
	uint8 is_match;

	if ( NULL_PTR != p_addr )
	{
		page = bf_drv_SpiMng_central.rcv.page_task;
		rcv_inf = bf_drv_SpiMng_central.rcv.page[page].inf;

		if (( RCV_FRM_DATA_FIX == rcv_inf ) && ( XSPI_FRM_MAX >= size ))
		{
			prcv_buf = bf_drv_SpiMng_central.rcv.page[page].dat;

#if (XSPI_DATA_CHECK_central != XSPI_DATA_CHECK_NONE)
			is_match = fc_drv_CheckIntegrityData_central( prcv_buf );
#else	/* XSPI_DATA_CHECK_central == XSPI_DATA_CHECK_NONE */
			is_match = XSPI_OK;
#endif	/* XSPI_DATA_CHECK_central */
			if( XSPI_OK == is_match )
			{
				fc_drv_SpiClearErrInfoKind_central( XSPI_ERR_KIND_INTG );

				/* 受信バッファから受信データを読み出し */
				XSPI_MEMCPY_central( p_addr, prcv_buf, size );

				result = XSPI_OK;
			}
			else
			{
				/* FCC不一致 */
				fc_drv_SpiSetErrInfoKind_central( XSPI_ERR_KIND_INTG );
#ifdef XSPI_DEBUG
				fc_drv_SpiSetDbgErrInfo_central( XSPI_ERR_DBG_INTG );
#endif	/* XSPI_DEBUG */
			}

			/* ページデータなしを設定して受信ページ番号を更新 */
			bf_drv_SpiMng_central.rcv.page[page].inf = RCV_FRM_DATA_NON;
			page++;
			page %= (uint8)XSPI_RCV_PAGE;
			bf_drv_SpiMng_central.rcv.page_task = page;
		}
	}

	return( result );
}

/****************************************************************************
*																			*
*		SYMBOL		: fc_drv_WriteBuf										*
*																			*
*		DESCRIPTION	: 送信バッファ書き込み(リングバッファ)					*
*																			*
*		PARAMETER	: OUT :	uint8*	書き込みデータアドレス					*
*					  IN  :	uint32	書き込みデータサイズ					*
*																			*
*					  RET :													*
*							uint8	書き込み結果							*
*								XSPI_NG	(0x00)	書き込み失敗	 			*
*								XSPI_OK	(0x01)	書き込み成功	 	 		*
*																			*
****************************************************************************/
uint8	fc_drv_WriteBuf_central(
	const uint8* p_addr, uint32 size
)
{
	uint8 result = XSPI_NG;
	uint8* psnd_buf;
	uint8 snd_inf;
	uint8 page;

	if ( NULL_PTR != p_addr )
	{
		page = bf_drv_SpiMng_central.snd.page_task;
		snd_inf = bf_drv_SpiMng_central.snd.page[page].inf;

		if (( SND_FRM_DATA_NON == snd_inf ) && ( XSPI_FRM_MAX >= size ))
		{
			psnd_buf = bf_drv_SpiMng_central.snd.page[page].dat;

			/* 送信バッファに送信データを設定 */
			XSPI_MEMCPY_central( psnd_buf, p_addr, size );

			/* ページデータありを設定して送信ページ番号を更新 */
			bf_drv_SpiMng_central.snd.page[page].inf = SND_FRM_DATA_FIX;
			page++;
			page %= (uint8)XSPI_SND_PAGE;
			bf_drv_SpiMng_central.snd.page_task = page;

			result = XSPI_OK;
		}
	}
	return( result );
}

/****************************************************************************
*																			*
*		SYMBOL		: fc_drv_SpiRcvDpageRenew								*
*																			*
*		DESCRIPTION	: ドライバ受信バッファページ更新(リングバッファ用)		*
*																			*
*		PARAMETER	: IN  :	None											*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :	None											*
*																			*
****************************************************************************/
void	fc_drv_SpiRcvDpageRenew_central(
	void
)
{
	uint8 page;

	/* ドライバ受信中バッファページ */
	page = bf_drv_SpiMng_central.rcv.page_rcv;

	if( bf_drv_SpiMng_central.rcv.page_drv == page )
	{	/* 受信バッファ空で新たなデータを受信（固定ページでは無い） */
		bf_drv_SpiMng_central.rcv.page[page].inf = RCV_FRM_DATA_FIX;	/* 受信データあり情報 */

		/* ドライバ用受信バッファページ更新 */
		page++;
		page %= (uint8)XSPI_RCV_PAGE;
		bf_drv_SpiMng_central.rcv.page_drv = page;
	}
}

/****************************************************************************
*																			*
*		SYMBOL		: fc_drv_SpiSendDpageRenew								*
*																			*
*		DESCRIPTION	: ドライバ送信バッファページ更新(リングバッファ用)		*
*																			*
*		PARAMETER	: IN  :	None											*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :	None											*
*																			*
****************************************************************************/
void	fc_drv_SpiSendDpageRenew_central(
	void
)
{
	uint8 page;

	/* ドライバ送信中バッファページ */
	page = bf_drv_SpiMng_central.snd.page_send;

	if( bf_drv_SpiMng_central.snd.page_drv == page )
	{	/* 送信データありを送信（固定ページでは無い） */
		bf_drv_SpiMng_central.snd.page[page].inf = SND_FRM_DATA_NON;	/* 送信データなし情報 */

		/* ドライバ用送信バッファページ更新 */
		page++;
		page %= (uint8)XSPI_SND_PAGE;
		bf_drv_SpiMng_central.snd.page_drv = page;
	}
}

#endif	/* XSPI_DATA_BUFFER_central */

/****************************************************************************/
/**************				整合性データチェック処理			*************/
/****************************************************************************/

/****************************************************************************
*																			*
*		SYMBOL		: fc_drv_Calculation_Sub_Addition						*
*																			*
*		DESCRIPTION	: 加算処理(overflow対応)								*
*																			*
*		PARAMETER	: IN  	:	agvUl_data1 …	加算データ1					*
*							:	agvUl_data2 …	加算データ2		 			*
*																			*
*					  OUT 	:	None										*
*																			*
*					  RET 	:	演算結果									*
*																			*
****************************************************************************/
static	uint32	fc_drv_Calculation_Sub_Addition_central(
	uint32 agvUl_data1, uint32 agvUl_data2
)
{
	uint32	wkvUl_result;
	uint32	wkvUl_data1;
	uint32	wkvUl_data2;

	wkvUl_data1 = agvUl_data1;
	wkvUl_data2 = agvUl_data2;

	/* Over Flowチェック([ULONG_MAX - agvUl_data1 ] vs [wkvUl_data2 ]) */
	if(	(ULONG_MAX - wkvUl_data1 ) >= wkvUl_data2 )
	{	/* -Yes (  >=  )- Over Flowしない時 */
		wkvUl_result = wkvUl_data1 + wkvUl_data2;
	}
	else
	{	/* -No (  <   )- Over Flowする時 */
		if( wkvUl_data1  >= wkvUl_data2 )
		{	/* -Yes (  >=  )- 以上 */
			wkvUl_result = wkvUl_data2 - (ULONG_MAX - wkvUl_data1 + 1UL);
		}
		else
		{	/* -No  (  <   )- 未満 */
			wkvUl_result = wkvUl_data1 - (ULONG_MAX - wkvUl_data2 + 1UL);
		}
	}

	return( wkvUl_result );
}

#if (XSPI_DATA_CHECK_central == XSPI_DATA_CHECK_FCC)
/****************************************************************************
*																			*
*		SYMBOL		: fc_drv_CalculationFcc									*
*																			*
*		DESCRIPTION	: FCC計算処理											*
*																			*
*		PARAMETER	: IN  :	uint32*	バッファアドレス						*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :	計算結果（FCCの１の補数）						*
*																			*
****************************************************************************/
static uint32	fc_drv_CalculationFcc_central(
	const uint32 *p_ulBuf
)
{
	uint32 frame_id, msg_offset;
	uint32 ulfcc, ulfcc_temp;
	uint32 subframe_offset;
	uint8 *pHeader;

	pHeader = (uint8*)&p_ulBuf[0];

	/* Frame Header 上位4byte 下位4byte 加算 */
	ulfcc = fc_drv_Calculation_Sub_Addition_central( BYTE_SWAP_32(p_ulBuf[0]), BYTE_SWAP_32(p_ulBuf[1]));

	/* Sub Frame 0 上位4byte 下位4byte 加算 */
	ulfcc_temp = fc_drv_Calculation_Sub_Addition_central( BYTE_SWAP_32(p_ulBuf[2]), BYTE_SWAP_32(p_ulBuf[3]));
	ulfcc = fc_drv_Calculation_Sub_Addition_central( ulfcc, ulfcc_temp );

	/* 未使用、Sub Frame1～Sub Frame7 上位4byte 下位4byte 加算 */
	for(frame_id = 1UL; frame_id < XSPI_SUB_FRAME_MAX_central; frame_id++)
	{
		subframe_offset = pHeader[frame_id];

		if( subframe_offset != 0UL )
		{
			msg_offset = ((uint32)subframe_offset * XSPI_SUB_FRAME_UNIT_central) / sizeof(uint32);
			ulfcc_temp = fc_drv_Calculation_Sub_Addition_central( BYTE_SWAP_32(p_ulBuf[msg_offset]), BYTE_SWAP_32(p_ulBuf[msg_offset + 1UL]) );
			ulfcc = fc_drv_Calculation_Sub_Addition_central( ulfcc, ulfcc_temp );
		}
	}

	return( ulfcc );
}

/****************************************************************************
*																			*
*		SYMBOL		: fc_drv_CheckIntegrityData								*
*																			*
*		DESCRIPTION	: 整合性データチェック（FCC）							*
*																			*
*		PARAMETER	: IN  :	uint8*	フレーム先頭アドレス					*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :													*
*							uint8	チェック結果							*
*										XSPI_NG		(0x00)	 異常 			*
*										XSPI_OK		(0x01)	 正常 			*
*																			*
****************************************************************************/
uint8	fc_drv_CheckIntegrityData_central(
	const uint8* p_frame
)
{
	uint8 ret = XSPI_OK;
	uint32 fcc;
	uint32 fcc_calc;
	uint32 *p_lframe;

	p_lframe = (uint32*)&p_frame[0];

	/* Calclation FCC */
	fcc = BYTE_SWAP_32(p_lframe[XSPI_FCC_LONG_OFFSET_central]);
	fcc_calc = fc_drv_CalculationFcc_central(p_lframe);

	if( fcc != fcc_calc ){
		ret = XSPI_NG;
	}

	return( ret );
}

/****************************************************************************
*																			*
*		SYMBOL		: fc_drv_AddIntegrityData								*
*																			*
*		DESCRIPTION	: 整合性データ付加（FCC）								*
*																			*
*		PARAMETER	: IN  :	uint8*	フレーム先頭アドレス					*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :	None											*
*																			*
****************************************************************************/
void    fc_drv_AddIntegrityData_central(
    uint8* p_frame
)
{
	uint32 fcc_offset;
	uint32 fcc_calc;

	/* Calclation FCC */
	fcc_offset = XSPI_FCC_OFFSET_central;
	fcc_calc = fc_drv_CalculationFcc_central((uint32*)p_frame);
	p_frame[fcc_offset  ] = BYTE_SWAP4(fcc_calc);
	p_frame[fcc_offset+1UL] = BYTE_SWAP3(fcc_calc);
	p_frame[fcc_offset+2UL] = BYTE_SWAP2(fcc_calc);
	p_frame[fcc_offset+3UL] = BYTE_SWAP1(fcc_calc);
}

#endif	/* XSPI_DATA_CHECK_central */
