#ifndef ETHSWT_SWIC_LOG_H
#define ETHSWT_SWIC_LOG_H
#if 0    /* VN-HILSとしては不要なため無効化 */
#include <Std_Types.h>

#define ETHSWT_SWIC_RESET_TRIP_NUM			(3u)	/* SWICリセット記録情報数(3トリップ) */
#define ETHSWT_SWIC_RESET_NUM				(3u)	/* ログを残すために必要なSWICリセット回数 */

#define ETHSWT_SWIC_LOG_EV_NUM				(4u)		/* イベント数 */
#define ETHSWT_SWIC_LOG_EV_RESET			(0u)		/* イベント:SWIC異常リセット */
#define ETHSWT_SWIC_LOG_EV_ACTIVE			(1u)		/* イベント:SWIC ACTIVE遷移 */
#define ETHSWT_SWIC_LOG_EV_3TIMES			(2u)		/* イベント:SWIC異常リセット3回 */
#define ETHSWT_SWIC_LOG_EV_SLEEP			(3u)		/* イベント:スリープ */
#define ETHSWT_SWIC_LOG_ST_NUM				(3u)		/* 状態数 */
#define ETHSWT_SWIC_LOG_ST_NORMAL			(0u)		/* 状態:正常 */
#define ETHSWT_SWIC_LOG_ST_RESET			(1u)		/* 状態:リセット継続 */
#define ETHSWT_SWIC_LOG_ST_END				(2u)		/* 状態:終了 */

/* リセット要因 */
#define ETHSWT_SWIC_REG_FACT_PMIC	(0x0001uL)	/* CRC異常→EtherPMIC OFF検出 */
#endif    /* VN-HILSとしては不要なため無効化 */
#define ETHSWT_SWIC_REG_FACT_CRC	(0x0002uL)	/* CRC異常 */
#define ETHSWT_SWIC_REG_FACT_BSY	(0x0004uL)	/* BSY待ち */
#define ETHSWT_SWIC_REG_FACT_SPI	(0x0008uL)	/* CRC異常→SPI異常 */
#define ETHSWT_SWIC_REG_FACT_INIT	(0x0010uL)	/* 初期化でレジスタ/テーブル化け */
#define ETHSWT_SWIC_REG_FACT_SWIC	(0x0020uL)	/* SWIC内部エラー */
#if 0    /* VN-HILSとしては不要なため無効化 */
#define ETHSWT_SWIC_REG_FACT_GPIO	(0x0040uL)	/* SWICリセット検出 */
#define ETHSWT_SWIC_REG_FACT_CMD	(0x1000uL)	/* EthSwt_SWIC_Reg_Resetコマンド */

void EthSwt_SWIC_Log_Wakeup(void);
void EthSwt_SWIC_Log_Reset(uint32 fact);
void EthSwt_SWIC_Log_Active(void);
#endif    /* VN-HILSとしては不要なため無効化 */
#endif /* ETHSWT_SWIC_LOG_H */
