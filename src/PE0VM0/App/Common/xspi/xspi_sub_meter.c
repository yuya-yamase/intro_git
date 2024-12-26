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
BF_DRV_SPI_DOUBLE		bf_drv_SpiMng_meter;			/* XSPI管理情報 */
#pragma ghs section

#ifdef XSPI_DEBUG
uint8	bf_drv_Dbg_ErrInfo_meter;				/* デバッグ用エラー情報 */
#endif	/* XSPI_DEBUG */

/****************************
*		prototype			*
****************************/
void	fc_drv_ClearXSpiMng_meter( void );						/* XSPI管理情報初期化 */
void	fc_drv_SpiSetErrInfoKind_meter( uint8 kind );				/* エラー種別情報設定 */
void	fc_drv_SpiClearErrInfoKind_meter( uint8 kind );			/* エラー種別情報クリア */
#ifdef XSPI_DEBUG
void	fc_drv_SpiSetDbgErrInfo_meter( uint8 err_info );			/* デバッグ用エラー情報設定 */
#endif	/* XSPI_DEBUG */

uint8	fc_drv_getRcvBufPage_meter( void );						/* 受信バッファページ取得 */
uint8	fc_drv_getSndBufPage_meter( void );						/* 送信バッファページ取得 */
uint8	fc_drv_ReadBuf_meter( uint8* p_addr, uint32 size );		/* 受信データ読み出し */
uint8	fc_drv_WriteBuf_meter( const uint8* p_addr, uint32 size );/* 送信データ書き込み */
#if (XSPI_DATA_CHECK_meter != XSPI_DATA_CHECK_NONE)
uint8	fc_drv_CheckIntegrityData_meter( const uint8* p_frame );	/* 整合性データチェック */
void	fc_drv_AddIntegrityData_meter( uint8* p_frame );			/* 整合性データ付加 */
#endif	/* XSPI_DATA_CHECK_meter */

/********************************
*		table					*
********************************/
#if (XSPI_DATA_CHECK_meter == XSPI_DATA_CHECK_SUM)
static const uint32 tb_drv_payload_size_meter[XSPI_PAYLOAD_NUM_meter] = {
	XSPI_HEADER_SIZE_meter + XSPI_PAYLOAD1_SIZE_meter,	/* size header + payload1 */
	XSPI_PAYLOAD2_SIZE_meter,						/* size payload2 */
	XSPI_PAYLOAD3_SIZE_meter						/* size payload3 */
};
#endif	/* XSPI_DATA_CHECK_meter */

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
static void	XSPI_MEMSET_meter (
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
static	void	XSPI_MEMCPY_meter (
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
void	fc_drv_ClearXSpiMng_meter(
	void
)
{
	/* XSPI管理情報初期化 */
	XSPI_MEMSET_meter( &bf_drv_SpiMng_meter, 0U, sizeof(bf_drv_SpiMng_meter) );

	/* [T.B.D]暫定対応 初回データスキップ(初回受信バッファに整合性データ付与) */
#if (XSPI_DATA_CHECK_meter != XSPI_DATA_CHECK_NONE)
	fc_drv_AddIntegrityData_meter(bf_drv_SpiMng_meter.rcv.page[0].dat);
	fc_drv_AddIntegrityData_meter(bf_drv_SpiMng_meter.rcv.page[1].dat);
#endif	/* XSPI_DATA_CHECK_meter */

#if (XSPI_DATA_BUFFER_meter == XSPI_DATA_BUFFER_DOUBLE)
	/* 送受信バッファページ情報初期化 */
	bf_drv_SpiMng_meter.snd.page_inf = XSPI_BUF_PAGE_1;
	bf_drv_SpiMng_meter.rcv.page_inf = XSPI_BUF_PAGE_1;
#endif	/* XSPI_DATA_BUFFER_meter */

#ifdef XSPI_DEBUG
	bf_drv_Dbg_ErrInfo_meter = 0U;		/* デバッグ用エラー情報初期化 */
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
void	fc_drv_SpiSetErrInfoKind_meter(
	uint8 kind
)
{
	/* エラー情報に種別をセット */
	bf_drv_SpiMng_meter.err_info |= (uint8)(kind & (uint8)XSPI_ERR_MSK_KIND) ;
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
void	fc_drv_SpiClearErrInfoKind_meter(
	uint8 kind
)
{
	/* エラー情報種別をクリア */
	bf_drv_SpiMng_meter.err_info &= (~kind) ;
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
void	fc_drv_SpiSetDbgErrInfo_meter(
	uint8 err_info
)
{
	/*  デバッグ用エラー情報にエラー情報をセット */
	bf_drv_Dbg_ErrInfo_meter |= (uint8)(err_info & (uint8)XSPI_ERR_MSK_DBG);
}
#endif	/* XSPI_DEBUG */

/****************************************************************************/
/**************				バッファ制御処理					*************/
/****************************************************************************/
#if (XSPI_DATA_BUFFER_meter == XSPI_DATA_BUFFER_DOUBLE)

/****************************************************************************
*																			*
*		SYMBOL		: fc_drv_getRcvBufPage									*
*																			*
*		DESCRIPTION	: 受信バッファページ取得処理（ダブルバッファ）			*
*																			*
*		PARAMETER	: IN  :	None											*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :													*
*							uint8	受信バッファページ						*
*																			*
****************************************************************************/
uint8 fc_drv_getRcvBufPage_meter(
	void
)
{
	uint8 rcv_inf;

	/* 受信バッファ切り替え */
	rcv_inf = bf_drv_SpiMng_meter.rcv.page_inf & ((uint8)XSPI_BUF_PAGE_LOCK |(uint8)XSPI_BUF_PAGE_1 );
	if( rcv_inf >=XSPI_BUF_PAGE_LOCK )
	{
		rcv_inf ^= ((uint8)XSPI_BUF_PAGE_LOCK |(uint8)XSPI_BUF_PAGE_1 );
		bf_drv_SpiMng_meter.rcv.page_inf = rcv_inf;
	}
	else
	{
#ifdef XSPI_DEBUG
		fc_drv_SpiSetDbgErrInfo_meter( XSPI_ERR_DBG_RX_LOCKED );
#endif	/* XSPI_DEBUG */
	}

	return (rcv_inf & XSPI_BUF_PAGE_1);
}

/****************************************************************************
*																			*
*		SYMBOL		: fc_drv_getSndBufPage									*
*																			*
*		DESCRIPTION	: 送信バッファページ取得処理（ダブルバッファ）			*
*																			*
*		PARAMETER	: IN  :	None											*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :													*
*							uint8	送信バッファページ						*
*																			*
****************************************************************************/
uint8 fc_drv_getSndBufPage_meter(
	void
)
{
	uint8 snd_inf;

	/* 送信バッファ切り替え */
	snd_inf = bf_drv_SpiMng_meter.snd.page_inf & ((uint8)XSPI_BUF_PAGE_LOCK |(uint8)XSPI_BUF_PAGE_1 );
	if( snd_inf >= XSPI_BUF_PAGE_LOCK )
	{
		snd_inf ^= ((uint8)XSPI_BUF_PAGE_LOCK |(uint8)XSPI_BUF_PAGE_1 );
		bf_drv_SpiMng_meter.snd.page_inf = snd_inf;
	}
	else
	{
#ifdef XSPI_DEBUG
		fc_drv_SpiSetDbgErrInfo_meter( XSPI_ERR_DBG_TX_LOCKED );
#endif	/* XSPI_DEBUG */
	}

	return (snd_inf & XSPI_BUF_PAGE_1);
}

/****************************************************************************
*																			*
*		SYMBOL		: fc_drv_ReadBuf										*
*																			*
*		DESCRIPTION	: 受信バッファ読み出し(ダブルバッファ)					*
*																			*
*		PARAMETER	: OUT :	uint8*	読み出し先頭アドレス					*
*					  IN  :	uint32	読み出しサイズ							*
*																			*
*					  RET :													*
*							uint8	読み出し結果							*
*								XSPI_NG	(0x00)	読み出し失敗	 			*
*								XSPI_OK	(0x01)	読み出し成功	 	 		*
*																			*
****************************************************************************/
uint8	fc_drv_ReadBuf_meter(
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
		rcv_inf = bf_drv_SpiMng_meter.rcv.page_inf & ((uint8)XSPI_BUF_PAGE_LOCK | (uint8)XSPI_BUF_PAGE_1);
		if (( XSPI_BUF_PAGE_LOCK > rcv_inf ) && ( XSPI_FRM_MAX >= size ))
		{
			page = rcv_inf ^ (uint8)XSPI_BUF_PAGE_1;
			prcv_buf = bf_drv_SpiMng_meter.rcv.page[page].dat;

#if (XSPI_DATA_CHECK_meter != XSPI_DATA_CHECK_NONE)
			is_match = fc_drv_CheckIntegrityData_meter( prcv_buf );
#else	/* XSPI_DATA_CHECK_meter == XSPI_DATA_CHECK_NONE */
			is_match = XSPI_OK;
#endif	/* XSPI_DATA_CHECK_meter */
			if( XSPI_OK == is_match )
			{
				fc_drv_SpiClearErrInfoKind_meter( XSPI_ERR_KIND_INTG );

				/* 受信バッファから受信データを読み出し */
				XSPI_MEMCPY_meter( p_addr, prcv_buf, size );
				result = XSPI_OK;
			}
			else
			{
				/* データ整合性エラー */
				fc_drv_SpiSetErrInfoKind_meter( XSPI_ERR_KIND_INTG );
#ifdef XSPI_DEBUG
				fc_drv_SpiSetDbgErrInfo_meter( XSPI_ERR_DBG_INTG );
#endif	/* XSPI_DEBUG */
			}

			bf_drv_SpiMng_meter.rcv.page_inf = ( rcv_inf | (uint8)XSPI_BUF_PAGE_LOCK);
		}
	}

	return( result );
}

/****************************************************************************
*																			*
*		SYMBOL		: fc_drv_WriteBuf										*
*																			*
*		DESCRIPTION	: 送信バッファ書き込み(ダブルバッファ)					*
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
uint8	fc_drv_WriteBuf_meter(
	const uint8* p_addr, uint32 size
)
{
	uint8 result = XSPI_NG;
	uint8* psnd_buf;
	uint8 page;
	uint8 snd_inf;

	if ( NULL_PTR != p_addr )
	{
		snd_inf = bf_drv_SpiMng_meter.snd.page_inf & ((uint8)XSPI_BUF_PAGE_LOCK | (uint8)XSPI_BUF_PAGE_1);
		if (( XSPI_BUF_PAGE_LOCK > snd_inf ) && ( XSPI_FRM_MAX >= size ))
		{
			page = snd_inf ^ (uint8)XSPI_BUF_PAGE_1;
			psnd_buf = bf_drv_SpiMng_meter.snd.page[page].dat;

			/* 送信バッファに送信データを設定 */
			XSPI_MEMCPY_meter( psnd_buf, p_addr, size );

			/* 送信バッファをロック */
			bf_drv_SpiMng_meter.snd.page_inf = (snd_inf | (uint8)XSPI_BUF_PAGE_LOCK);
			result = XSPI_OK;
		}
	}

	return( result );
}

#endif	/* XSPI_DATA_BUFFER_meter */

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
static	uint32	fc_drv_Calculation_Sub_Addition_meter(
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

#if (XSPI_DATA_CHECK_meter == XSPI_DATA_CHECK_SUM)
/****************************************************************************
*																			*
*		SYMBOL		: fc_drv_CalculationChkSum								*
*																			*
*		DESCRIPTION	: CheckSum計算処理										*
*																			*
*		PARAMETER	: IN  :	uint32*	バッファアドレス						*
*							uint32	バッファサイズ							*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :	計算結果（CheckSum値）							*
*																			*
****************************************************************************/
static uint32	fc_drv_CalculationChkSum_meter(
	const uint32 *p_ulbuf, uint32 ulsize
)
{
	uint32 ulsum = 0UL;
	uint32 i;

	for( i = 0UL; i < ulsize; i++ ){
		ulsum = fc_drv_Calculation_Sub_Addition_meter( ulsum, p_ulbuf[i] );
	}

	ulsum ^= (uint32)XSPI_CHKSUM_XOR_meter;

	return( ulsum );
}


/****************************************************************************
*																			*
*		SYMBOL		: fc_drv_CheckIntegrityData								*
*																			*
*		DESCRIPTION	: 整合性データチェック（CheckSum）						*
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
uint8   fc_drv_CheckIntegrityData_meter(
	const uint8* p_frame
)
{
	uint8 ret = XSPI_OK;
	uint32 chksum = 0UL;
	uint32 chksum_calc = 0UL;
	uint32 offset = 0UL;
	uint32 offset_calc = 0UL;
	uint32 *p_lframe;
	uint32 ulsize;
	uint8 i;

	p_lframe = (uint32*)&p_frame[0];

	/* Calclation CheckSum */
	for (i = 0U; i < XSPI_PAYLOAD_NUM_meter; i++)
	{
		offset = (XSPI_CHKSUM_LONG_OFFSET_meter + i);
		chksum = p_lframe[offset];
		ulsize = tb_drv_payload_size_meter[i] / sizeof(uint32);

		chksum_calc = fc_drv_CalculationChkSum_meter( &p_lframe[offset_calc], ulsize );
		if (chksum_calc != chksum)
		{
			ret = XSPI_NG;
			break;
		}

		offset_calc += ulsize;
	}

	return( ret );
}

/****************************************************************************
*																			*
*		SYMBOL		: fc_drv_AddIntegrityData								*
*																			*
*		DESCRIPTION	: 整合性データ付加（CheckSum）							*
*																			*
*		PARAMETER	: IN/OUT  :	フレーム先頭アドレス						*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :	None											*
*																			*
****************************************************************************/
void    fc_drv_AddIntegrityData_meter(
    uint8* p_frame
)
{
	uint32 chksum_calc = 0UL;
	uint32 offset_add = 0UL;
	uint32 offset_calc = 0UL;
	uint32 *p_lframe;
	uint32 ulsize;
	uint8 i;

	p_lframe = (uint32*)&p_frame[0];

	/* Calclation CheckSum */
	for (i = 0U; i < XSPI_PAYLOAD_NUM_meter; i++)
	{
		ulsize = tb_drv_payload_size_meter[i] / sizeof(uint32);
		chksum_calc = fc_drv_CalculationChkSum_meter( &p_lframe[offset_calc], ulsize );

		offset_add = (XSPI_CHKSUM_LONG_OFFSET_meter + i);
		p_lframe[offset_add] = chksum_calc;
		offset_calc += ulsize;
    }
}

#endif	/* XSPI_DATA_CHECK_meter */
