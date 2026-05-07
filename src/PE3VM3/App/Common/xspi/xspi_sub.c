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
BF_DRV_SPI		bf_drv_SpiMng	__attribute__((aligned(4)));			/* XSPI管理情報 */

#ifdef XSPI_DEBUG
uint8	bf_drv_Dbg_ErrInfo;				/* デバッグ用エラー情報 */
#endif	/* XSPI_DEBUG */

/****************************
*		prototype			*
****************************/
void	fc_drv_ClearXSpiMng( void );						/* XSPI管理情報初期化 */
void	fc_drv_SpiSetErrInfoKind( uint8 kind );				/* エラー種別情報設定 */
void	fc_drv_SpiClearErrInfoKind( uint8 kind );			/* エラー種別情報クリア */
#ifdef XSPI_DEBUG
void	fc_drv_SpiSetDbgErrInfo( uint8 err_info );			/* デバッグ用エラー情報設定 */
#endif	/* XSPI_DEBUG */

uint8	fc_drv_getRcvBufPage( void );						/* 受信バッファページ取得 */
uint8	fc_drv_getSndBufPage( void );						/* 送信バッファページ取得 */
uint8	fc_drv_ReadBuf( uint32* p_addr, uint32 size );		/* 受信データ読み出し */
uint8	fc_drv_WriteBuf( const uint32* const p_addr, uint32 size );	/* 送信データ書き込み */
#if (XSPI_DATA_BUFFER != XSPI_DATA_BUFFER_DOUBLE)
void	fc_drv_SpiRcvDpageRenew( void );					/* ドライバ受信バッファページ更新(リングバッファ用) */
void	fc_drv_SpiSendDpageRenew( void );					/* ドライバ送信バッファページ更新(リングバッファ用) */
#endif /* XSPI_DATA_BUFFER */
#if (XSPI_DATA_CHECK != XSPI_DATA_CHECK_NONE)
uint8	fc_drv_CheckIntegrityData( const uint32* p_frame );	/* 整合性データチェック */
void	fc_drv_AddIntegrityData( uint32* p_frame );			/* 整合性データ付加 */
#endif	/* XSPI_DATA_CHECK */

/********************************
*		table					*
********************************/
#if (XSPI_DATA_CHECK == XSPI_DATA_CHECK_SUM)
static const uint32 tb_drv_payload_size[XSPI_PAYLOAD_NUM] = {
	XSPI_HEADER_SIZE + XSPI_PAYLOAD1_SIZE,	/* size header + payload1 */
#ifndef XSPI_CHECK_SUM_CENTRAL
	XSPI_PAYLOAD2_SIZE,						/* size payload2 */
	XSPI_PAYLOAD3_SIZE						/* size payload3 */
#endif	/* XSPI_CHECK_SUM_CENTRAL */
};
#endif	/* XSPI_DATA_CHECK */

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
static void	XSPI_MEMSET (
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
static	void	XSPI_MEMCPY (
	void * p_dst, const void * p_src, uint32 size
)
{
	uint32 *p_usrc = (uint32 *)p_src;
	uint32 *p_udst = (uint32 *)p_dst;
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
void	fc_drv_ClearXSpiMng(
	void
)
{
	/* XSPI管理情報初期化 */
	XSPI_MEMSET( &bf_drv_SpiMng, 0U, sizeof(bf_drv_SpiMng) );

	/* 暫定対応 初回データスキップ(初回受信バッファに整合性データ付与) */
#if (XSPI_DATA_CHECK != XSPI_DATA_CHECK_NONE)
	fc_drv_AddIntegrityData((uint32 *)bf_drv_SpiMng.rcv.page[0].dat);
	fc_drv_AddIntegrityData((uint32 *)bf_drv_SpiMng.rcv.page[1].dat);
#endif	/* XSPI_DATA_CHECK */

#if (XSPI_DATA_BUFFER == XSPI_DATA_BUFFER_DOUBLE)
	/* 送受信バッファページ情報初期化 */
	bf_drv_SpiMng.snd.page_inf = XSPI_BUF_PAGE_1;
	bf_drv_SpiMng.rcv.page_inf = XSPI_BUF_PAGE_1;
#else	/* XSPI_DATA_BUFFER == XSPI_DATA_BUFFER_RING */
	/* 送信用ダミーページ情報にデータ確定を設定 */
	bf_drv_SpiMng.snd.page[XSPI_SND_PAGE].inf = SND_FRM_DATA_FIX;
#endif	/* XSPI_DATA_BUFFER */

#ifdef XSPI_DEBUG
	bf_drv_Dbg_ErrInfo = 0U;		/* デバッグ用エラー情報初期化 */
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
void	fc_drv_SpiSetErrInfoKind(
	uint8 kind
)
{
	/* エラー情報に種別をセット */
	bf_drv_SpiMng.err_info |= (uint8)(kind & (uint8)XSPI_ERR_MSK_KIND) ;
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
void	fc_drv_SpiClearErrInfoKind(
	uint8 kind
)
{
	/* エラー情報種別をクリア */
	bf_drv_SpiMng.err_info &= (~kind) ;
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
void	fc_drv_SpiSetDbgErrInfo(
	uint8 err_info
)
{
	/*  デバッグ用エラー情報にエラー情報をセット */
	bf_drv_Dbg_ErrInfo |= (uint8)(err_info & (uint8)XSPI_ERR_MSK_DBG);
}
#endif	/* XSPI_DEBUG */

/****************************************************************************/
/**************				バッファ制御処理					*************/
/****************************************************************************/
#if (XSPI_DATA_BUFFER == XSPI_DATA_BUFFER_DOUBLE)

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
uint8 fc_drv_getRcvBufPage(
	void
)
{
	uint8 rcv_inf;

	/* 受信バッファ切り替え */
	rcv_inf = bf_drv_SpiMng.rcv.page_inf & ((uint8)XSPI_BUF_PAGE_LOCK |(uint8)XSPI_BUF_PAGE_1 );
	if( rcv_inf >= XSPI_BUF_PAGE_LOCK )
	{
		fc_drv_SpiClearErrInfoKind( XSPI_ERR_KIND_RX_BUF_OVF );
		rcv_inf ^= ((uint8)XSPI_BUF_PAGE_LOCK |(uint8)XSPI_BUF_PAGE_1 );
		bf_drv_SpiMng.rcv.page_inf = rcv_inf;
	}
	else
	{
		/* 受信バッファオーバーフロー */
		fc_drv_SpiSetErrInfoKind( XSPI_ERR_KIND_RX_BUF_OVF );
#ifdef XSPI_DEBUG
		fc_drv_SpiSetDbgErrInfo( XSPI_ERR_DBG_RX_LOCKED );
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
uint8 fc_drv_getSndBufPage(
	void
)
{
	uint8 snd_inf;

	/* 送信バッファ切り替え */
	snd_inf = bf_drv_SpiMng.snd.page_inf & ((uint8)XSPI_BUF_PAGE_LOCK |(uint8)XSPI_BUF_PAGE_1 );
	if( snd_inf >= XSPI_BUF_PAGE_LOCK )
	{
		snd_inf ^= ((uint8)XSPI_BUF_PAGE_LOCK |(uint8)XSPI_BUF_PAGE_1 );
		bf_drv_SpiMng.snd.page_inf = snd_inf;
	}
	else
	{
#ifdef XSPI_DEBUG
		fc_drv_SpiSetDbgErrInfo( XSPI_ERR_DBG_TX_LOCKED );
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
*		PARAMETER	: OUT :	uint32*	読み出し先頭アドレス					*
*					  IN  :	uint32	読み出しサイズ							*
*																			*
*					  RET :													*
*							uint8	読み出し結果							*
*								XSPI_NG	(0x00)	読み出し失敗	 			*
*								XSPI_OK	(0x01)	読み出し成功	 	 		*
*																			*
****************************************************************************/
uint8	fc_drv_ReadBuf(
	uint32* p_addr, uint32 size
)
{
	uint8 result = XSPI_NG;
	uint32* prcv_buf;
	uint8 rcv_inf;
	uint8 page;
	uint8 is_match;

	if (( NULL_PTR != p_addr ) && ( XSPI_RCV_FRM_MAX >= size ))
	{
		fc_drv_SpiClearErrInfoKind( XSPI_ERR_KIND_ARG );
		rcv_inf = bf_drv_SpiMng.rcv.page_inf & ((uint8)XSPI_BUF_PAGE_LOCK | (uint8)XSPI_BUF_PAGE_1);
		if ( XSPI_BUF_PAGE_LOCK > rcv_inf )
		{
			fc_drv_SpiClearErrInfoKind( XSPI_ERR_KIND_RX_BUF_EMPTY );
			page = rcv_inf ^ (uint8)XSPI_BUF_PAGE_1;
			prcv_buf = (uint32 *)bf_drv_SpiMng.rcv.page[page].dat;

#if (XSPI_DATA_CHECK != XSPI_DATA_CHECK_NONE)
			is_match = fc_drv_CheckIntegrityData( prcv_buf );
#else	/* XSPI_DATA_CHECK == XSPI_DATA_CHECK_NONE */
			is_match = XSPI_OK;
#endif	/* XSPI_DATA_CHECK */
			if( XSPI_OK == is_match )
			{
				fc_drv_SpiClearErrInfoKind( XSPI_ERR_KIND_INTG );

				/* 受信バッファから受信データを読み出し */
				XSPI_MEMCPY( p_addr, prcv_buf, size );
				result = XSPI_OK;
			}
			else
			{
				/* データ整合性エラー */
				fc_drv_SpiSetErrInfoKind( XSPI_ERR_KIND_INTG );
#ifdef XSPI_DEBUG
				fc_drv_SpiSetDbgErrInfo( XSPI_ERR_DBG_INTG );
#endif	/* XSPI_DEBUG */
			}

			bf_drv_SpiMng.rcv.page_inf = ( rcv_inf | (uint8)XSPI_BUF_PAGE_LOCK);
		}
		else
		{
			fc_drv_SpiSetErrInfoKind( XSPI_ERR_KIND_RX_BUF_EMPTY );
		}
	}
	else
	{
		fc_drv_SpiSetErrInfoKind( XSPI_ERR_KIND_ARG );
	}

	return( result );
}

/****************************************************************************
*																			*
*		SYMBOL		: fc_drv_WriteBuf										*
*																			*
*		DESCRIPTION	: 送信バッファ書き込み(ダブルバッファ)					*
*																			*
*		PARAMETER	: OUT :	uint32*	書き込みデータアドレス					*
*					  IN  :	uint32	書き込みデータサイズ					*
*																			*
*					  RET :													*
*							uint8	書き込み結果							*
*								XSPI_NG	(0x00)	書き込み失敗	 			*
*								XSPI_OK	(0x01)	書き込み成功	 	 		*
*																			*
****************************************************************************/
uint8	fc_drv_WriteBuf(
	const uint32* const p_addr, uint32 size
)
{
	uint8 result = XSPI_NG;
	uint32* psnd_buf;
	uint8 page;
	uint8 snd_inf;

	if ( NULL_PTR != p_addr )
	{
		snd_inf = bf_drv_SpiMng.snd.page_inf & ((uint8)XSPI_BUF_PAGE_LOCK | (uint8)XSPI_BUF_PAGE_1);
		if (( XSPI_BUF_PAGE_LOCK > snd_inf ) && ( XSPI_SND_FRM_MAX >= size ))
		{
			page = snd_inf ^ (uint8)XSPI_BUF_PAGE_1;
			psnd_buf = (uint32 *)bf_drv_SpiMng.snd.page[page].dat;

			/* 送信バッファに送信データを設定 */
			XSPI_MEMCPY( psnd_buf, p_addr, size );

			/* 送信バッファをロック */
			bf_drv_SpiMng.snd.page_inf = (snd_inf | (uint8)XSPI_BUF_PAGE_LOCK);
			result = XSPI_OK;
		}
	}

	return( result );
}

#else /* XSPI_DATA_BUFFER == XSPI_DATA_BUFFER_RING */

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
uint8 fc_drv_getRcvBufPage(
	void
)
{
	uint8 page;

	page = bf_drv_SpiMng.rcv.page_drv;
	if ( page > XSPI_RCV_PAGE )
	{
		/* 受信リングバッファクリア */
		XSPI_MEMSET( &bf_drv_SpiMng.rcv, 0U, sizeof(bf_drv_SpiMng.rcv) );

		/* バッファクリア後にページを再取得 */
		page = bf_drv_SpiMng.rcv.page_drv;
	}

	/* 受信用バッファ空チェック */
	if( bf_drv_SpiMng.rcv.page[page].inf != (uint8)RCV_FRM_DATA_NON )
	{	/* 受信用バッファにデータあり（固定アドレスへ受信＆破棄） */
		page = XSPI_RCV_PAGE;

		/* 受信バッファオーバーフロー */
		fc_drv_SpiSetErrInfoKind( XSPI_ERR_KIND_RX_BUF_OVF );
#ifdef XSPI_DEBUG
		fc_drv_SpiSetDbgErrInfo( XSPI_ERR_DBG_OVERFLOW );
#endif	/* XSPI_DEBUG */
	}
	else
	{
		fc_drv_SpiClearErrInfoKind( XSPI_ERR_KIND_RX_BUF_OVF );
	}

	/* 受信中バッファページ保存 */
	bf_drv_SpiMng.rcv.page_rcv = page;

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
uint8 fc_drv_getSndBufPage(
	void
)
{
	uint8 page;

	page = bf_drv_SpiMng.snd.page_drv;
	if ( page > XSPI_SND_PAGE )
	{
		/* 送信リングバッファクリア */
		XSPI_MEMSET( &bf_drv_SpiMng.snd, 0U, sizeof(bf_drv_SpiMng.snd) );

		/* バッファクリア後にページを再取得 */
		page = bf_drv_SpiMng.snd.page_drv;
	}

	/* 送信用バッファデータありチェック */
	if( bf_drv_SpiMng.snd.page[page].inf != (uint8)SND_FRM_DATA_FIX )
	{	/* 送信用バッファ内にデータセットされていない（固定アドレスを指定して空データ送信） */
		page = XSPI_SND_PAGE;
	}

	/* 送信中バッファページ保存 */
	bf_drv_SpiMng.snd.page_send = page;

	return ( page );
}

/****************************************************************************
*																			*
*		SYMBOL		: fc_drv_ReadBuf										*
*																			*
*		DESCRIPTION	: 受信バッファ読み出し(リングバッファ)					*
*																			*
*		PARAMETER	: OUT :	uint32*	読み出しデータアドレス					*
*					  IN  :	uint32	読み出しデータサイズ					*
*																			*
*					  RET :													*
*							uint8	読み出し結果							*
*								XSPI_NG	(0x00)	読み出し失敗	 			*
*								XSPI_OK	(0x01)	読み出し成功	 	 		*
*																			*
****************************************************************************/
uint8	fc_drv_ReadBuf(
	uint32* p_addr, uint32 size
)
{
	uint8 result = XSPI_NG;
	uint32* prcv_buf;
	uint8 rcv_inf;
	uint8 page;
	uint8 is_match;

	if (( NULL_PTR != p_addr ) && ( XSPI_RCV_FRM_MAX >= size ))
	{
		fc_drv_SpiClearErrInfoKind( XSPI_ERR_KIND_ARG );
		page = bf_drv_SpiMng.rcv.page_task;
		if ( page >= XSPI_RCV_PAGE )
		{
			/* 受信リングバッファクリア */
			XSPI_MEMSET( &bf_drv_SpiMng.rcv, 0U, sizeof(bf_drv_SpiMng.rcv) );

			/* バッファクリア後にページを再取得 */
			page = bf_drv_SpiMng.rcv.page_task;
		}
		rcv_inf = bf_drv_SpiMng.rcv.page[page].inf;

		if ( RCV_FRM_DATA_FIX == rcv_inf )
		{
			fc_drv_SpiClearErrInfoKind( XSPI_ERR_KIND_RX_BUF_EMPTY );
			prcv_buf = (uint32 *)bf_drv_SpiMng.rcv.page[page].dat;

#if (XSPI_DATA_CHECK != XSPI_DATA_CHECK_NONE)
			is_match = fc_drv_CheckIntegrityData( prcv_buf );
#else	/* XSPI_DATA_CHECK == XSPI_DATA_CHECK_NONE */
			is_match = XSPI_OK;
#endif	/* XSPI_DATA_CHECK */
			if( XSPI_OK == is_match )
			{
				fc_drv_SpiClearErrInfoKind( XSPI_ERR_KIND_INTG );

				/* 受信バッファから受信データを読み出し */
				XSPI_MEMCPY( p_addr, prcv_buf, size );

				result = XSPI_OK;
			}
			else
			{
				/* FCC不一致 */
				fc_drv_SpiSetErrInfoKind( XSPI_ERR_KIND_INTG );
#ifdef XSPI_DEBUG
				fc_drv_SpiSetDbgErrInfo( XSPI_ERR_DBG_INTG );
#endif	/* XSPI_DEBUG */
			}

			/* ページデータなしを設定して受信ページ番号を更新 */
			bf_drv_SpiMng.rcv.page[page].inf = RCV_FRM_DATA_NON;
			page++;
			page %= (uint8)XSPI_RCV_PAGE;
			bf_drv_SpiMng.rcv.page_task = page;
		}
		else
		{
			fc_drv_SpiSetErrInfoKind( XSPI_ERR_KIND_RX_BUF_EMPTY );
		}
	}
	else
	{
		fc_drv_SpiSetErrInfoKind( XSPI_ERR_KIND_ARG );
	}

	return( result );
}

/****************************************************************************
*																			*
*		SYMBOL		: fc_drv_WriteBuf										*
*																			*
*		DESCRIPTION	: 送信バッファ書き込み(リングバッファ)					*
*																			*
*		PARAMETER	: OUT :	uint32*	書き込みデータアドレス					*
*					  IN  :	uint32	書き込みデータサイズ					*
*																			*
*					  RET :													*
*							uint8	書き込み結果							*
*								XSPI_NG	(0x00)	書き込み失敗	 			*
*								XSPI_OK	(0x01)	書き込み成功	 	 		*
*																			*
****************************************************************************/
uint8	fc_drv_WriteBuf(
	const uint32* const p_addr, uint32 size
)
{
	uint8 result = XSPI_NG;
	uint32* psnd_buf;
	uint8 snd_inf;
	uint8 page;

	if ( NULL_PTR != p_addr )
	{
		page = bf_drv_SpiMng.snd.page_task;

		if ( page >= XSPI_SND_PAGE )
		{
			/* 送信リングバッファクリア */
			XSPI_MEMSET( &bf_drv_SpiMng.snd, 0U, sizeof(bf_drv_SpiMng.snd) );

			/* バッファクリア後にページを再取得 */
			page = bf_drv_SpiMng.snd.page_task;
		}
		snd_inf = bf_drv_SpiMng.snd.page[page].inf;

		if (( SND_FRM_DATA_NON == snd_inf ) && ( XSPI_SND_FRM_MAX >= size ))
		{
			psnd_buf = (uint32 *)bf_drv_SpiMng.snd.page[page].dat;

			/* 送信バッファに送信データを設定 */
			XSPI_MEMCPY( psnd_buf, p_addr, size );

			/* ページデータありを設定して送信ページ番号を更新 */
			bf_drv_SpiMng.snd.page[page].inf = SND_FRM_DATA_FIX;
			page++;
			page %= (uint8)XSPI_SND_PAGE;
			bf_drv_SpiMng.snd.page_task = page;

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
void	fc_drv_SpiRcvDpageRenew(
	void
)
{
	uint8 page;

	/* ドライバ受信中バッファページ */
	page = bf_drv_SpiMng.rcv.page_rcv;

	if( bf_drv_SpiMng.rcv.page_drv == page )
	{	/* 受信バッファ空で新たなデータを受信（固定ページでは無い） */
		bf_drv_SpiMng.rcv.page[page].inf = RCV_FRM_DATA_FIX;	/* 受信データあり情報 */

		/* ドライバ用受信バッファページ更新 */
		page++;
		page %= (uint8)XSPI_RCV_PAGE;
		bf_drv_SpiMng.rcv.page_drv = page;
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
void	fc_drv_SpiSendDpageRenew(
	void
)
{
	uint8 page;

	/* ドライバ送信中バッファページ */
	page = bf_drv_SpiMng.snd.page_send;

	if( bf_drv_SpiMng.snd.page_drv == page )
	{	/* 送信データありを送信（固定ページでは無い） */
		bf_drv_SpiMng.snd.page[page].inf = SND_FRM_DATA_NON;	/* 送信データなし情報 */

		/* ドライバ用送信バッファページ更新 */
		page++;
		page %= (uint8)XSPI_SND_PAGE;
		bf_drv_SpiMng.snd.page_drv = page;
	}
}

#endif	/* XSPI_DATA_BUFFER */

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
static	uint32	fc_drv_Calculation_Sub_Addition(
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

#if (XSPI_DATA_CHECK == XSPI_DATA_CHECK_FCC)
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
static uint32	fc_drv_CalculationFcc(
	const uint32 *p_ulBuf
)
{
	uint32 frame_id, msg_offset;
	uint32 ulfcc, ulfcc_temp;
	uint32 subframe_offset;
	uint8 *pHeader;

	pHeader = (uint8*)&p_ulBuf[0];

	/* Frame Header 上位4byte 下位4byte 加算 */
	ulfcc = fc_drv_Calculation_Sub_Addition( BYTE_SWAP_32(p_ulBuf[0]), BYTE_SWAP_32(p_ulBuf[1]));

	/* Sub Frame 0 上位4byte 下位4byte 加算 */
	ulfcc_temp = fc_drv_Calculation_Sub_Addition( BYTE_SWAP_32(p_ulBuf[2]), BYTE_SWAP_32(p_ulBuf[3]));
	ulfcc = fc_drv_Calculation_Sub_Addition( ulfcc, ulfcc_temp );

	/* 未使用、Sub Frame1～Sub Frame7 上位4byte 下位4byte 加算 */
	for(frame_id = 1UL; frame_id < XSPI_SUB_FRAME_MAX; frame_id++)
	{
		subframe_offset = pHeader[frame_id];

		if( subframe_offset != 0UL )
		{
			msg_offset = ((uint32)subframe_offset * XSPI_SUB_FRAME_UNIT) / sizeof(uint32);
			ulfcc_temp = fc_drv_Calculation_Sub_Addition( BYTE_SWAP_32(p_ulBuf[msg_offset]), BYTE_SWAP_32(p_ulBuf[msg_offset + 1UL]) );
			ulfcc = fc_drv_Calculation_Sub_Addition( ulfcc, ulfcc_temp );
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
*		PARAMETER	: IN  :	uint32*	フレーム先頭アドレス					*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :													*
*							uint8	チェック結果							*
*										XSPI_NG		(0x00)	 異常 			*
*										XSPI_OK		(0x01)	 正常 			*
*																			*
****************************************************************************/
uint8	fc_drv_CheckIntegrityData(
	const uint32* p_frame
)
{
	uint8 ret = XSPI_OK;
	uint32 fcc;
	uint32 fcc_calc;

	/* Calclation FCC */
	fcc = BYTE_SWAP_32(p_frame[XSPI_FCC_LONG_OFFSET]);
	fcc_calc = fc_drv_CalculationFcc(p_frame);

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
*		PARAMETER	: IN  :	uint32*	フレーム先頭アドレス					*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :	None											*
*																			*
****************************************************************************/
void    fc_drv_AddIntegrityData(
    uint32* p_frame
)
{
	uint32 fcc_calc;

	/* Calclation FCC */
	fcc_calc = fc_drv_CalculationFcc(p_frame);
	p_frame[XSPI_FCC_LONG_OFFSET] = BYTE_SWAP_32(fcc_calc);
}

#elif (XSPI_DATA_CHECK == XSPI_DATA_CHECK_SUM)

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
static uint32	fc_drv_CalculationChkSum(
	const uint32 *p_ulbuf, uint32 ulsize
)
{
	uint32 ulsum = 0UL;
	uint32 i;

	for( i = 0UL; i < ulsize; i++ ){
		ulsum = fc_drv_Calculation_Sub_Addition( ulsum, p_ulbuf[i] );
	}

	ulsum ^= (uint32)XSPI_CHKSUM_XOR;

	return( ulsum );
}


/****************************************************************************
*																			*
*		SYMBOL		: fc_drv_CheckIntegrityData								*
*																			*
*		DESCRIPTION	: 整合性データチェック（CheckSum）						*
*																			*
*		PARAMETER	: IN  :	uint32*	フレーム先頭アドレス					*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :													*
*							uint8	チェック結果							*
*										XSPI_NG		(0x00)	 異常 			*
*										XSPI_OK		(0x01)	 正常 			*
*																			*
****************************************************************************/
uint8   fc_drv_CheckIntegrityData(
	const uint32* p_frame
)
{
	uint8 ret = XSPI_OK;
	uint32 chksum = 0UL;
	uint32 chksum_calc = 0UL;
	uint32 offset = 0UL;
	uint32 offset_calc = 0UL;
	uint32 ulsize;
	uint8 i;

	/* Calclation CheckSum */
	for (i = 0U; i < XSPI_PAYLOAD_NUM; i++)
	{
		offset = (XSPI_CHKSUM_LONG_OFFSET + i);
		chksum = p_frame[offset];
		ulsize = tb_drv_payload_size[i] / sizeof(uint32);

		chksum_calc = fc_drv_CalculationChkSum( &p_frame[offset_calc], ulsize );
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
*		PARAMETER	: IN/OUT  :	uint32*	フレーム先頭アドレス				*
*																			*
*					  OUT :	None											*
*																			*
*					  RET :	None											*
*																			*
****************************************************************************/
void    fc_drv_AddIntegrityData(
    uint32* p_frame
)
{
	uint32 chksum_calc = 0UL;
	uint32 offset_add = 0UL;
	uint32 offset_calc = 0UL;
	uint32 ulsize;
	uint8 i;

	/* Calclation CheckSum */
	for (i = 0U; i < XSPI_PAYLOAD_NUM; i++)
	{
		ulsize = tb_drv_payload_size[i] / sizeof(uint32);
		chksum_calc = fc_drv_CalculationChkSum( &p_frame[offset_calc], ulsize );

		offset_add = (XSPI_CHKSUM_LONG_OFFSET + i);
		p_frame[offset_add] = chksum_calc;
		offset_calc += ulsize;
    }
}

#endif	/* XSPI_DATA_CHECK */
