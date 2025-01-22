/****************************************************************************/
/*  ファイル名      L3R_Common.h                                            */
/*  モジュール名    共通ヘッダ                                              */
/*  機能            共通ヘッダ                                              */
/*  備考                                                                    */
/*  変更履歴        V1.00   2013.05.13  Y.Kaseda                            */
/*                        新規作成            CGWコーディング規約 V1.00準拠 */
/*                  V1.01   2013.11.19  R.Moriyama                          */
/*                        PF変更対応(DI、EIインターフェースを変更)          */
/*                        RTR_NULLを追加                                    */
/*                  V1.02   2014.04.11  H.Tanaka                            */
/*                        MBQ見直しに伴いRTR_REQ_***を追加                  */
/*                  V1.03   2014.05.06  R.Moriyama                          */
/*                        サッチャム対象フレーム向けのRTR_MSK_1BYTE、       */
/*                        RTR_1BYTE_MAXを追加                               */
/*                  V1.04   2015.01.16  N.Shiraishi                         */
/*                        バスのNM仕様切り替えのための定数を追加            */
/*                  V1.05   2017.03.03  Y.Katayama                          */
/*						  19PF向けにインクルードファイルの変更				*/
/*                  V1.06   2018.05.12  A.Yasui                             */
/*						  デファインの二重定義を解消(CAN FD情報)			*/
/*                  V2.00   2018.05.16  T.Yamamura                          */
/*                        可変化対応 RTR_CANCH_MAXをGW_RTR_config.hへ移動   */
/*                  V2.01   2018/05/21  A.Yasui(FSI)                        */
/*                        中継のCHとPRTCL_BITの命名規則明確化レベルアップ2  */
/*                  V2.02   2018.05.23  T.Yamamura                          */
/*                        可変化対応 RTR_DYNAMC_ID_BUFNOをL3R_GwBuffer_cfg.hへ移動   */
/*                                   RTR_DYNAMC_BUFNOをL3R_GwBuffer_cfg.hへ移動   */
/*                                   RTR_DIAG_BUFNOをL3R_GwBuffer_cfg.hへ移動   */
/*                  V3.00   2018/11/21  Y.Katayama(FSI)                     */
/*                        中継改善(オブジェクト不変）                       */
/*					V5.00	2020/12/07	T.Yamamura(FSI)	[Post19CY] 29Bit対応 */
/****************************************************************************/

#ifndef L3R_COMMON_H
#define L3R_COMMON_H

#include "Std_Types.h"
#include "Os.h"

#include "CS_Can.h"
#include "CS_Can_Cfg.h"

#include "CHM_LogicCh.h"

/*----外部変数宣言･変数名置換マクロ-----------------------------------------*/

#define L3R_SET			(1U)
#define L3R_CLR			(0U)

#define L3R_ON			(1U)
#define L3R_OFF			(0U)

#define L3R_TRUE		(1U)
#define L3R_FALSE		(0U)

#define L3R_E_OK		(0U)
#define L3R_E_NOT_OK	(1U)

#define L3R_REQ_OK		(0U)
#define L3R_REQ_NG		(1U)
#define L3R_REQ_WAIT	(2U)

#define L3R_DI()	SuspendAllInterrupts()
#define L3R_EI()	ResumeAllInterrupts()

#define L3R_sleepNG()		
#define L3R_sleepOK()		
#define L3R_requestWakeup()	

#define L3R_NULL		(NULL_PTR)

/*---- プロトコルbit定義 ---------------------------------------------------*/
#define L3R_PRTCL_BIT_0		(0x0001U)
#define L3R_PRTCL_BIT_1		(0x0002U)
#define L3R_PRTCL_BIT_2		(0x0004U)
#define L3R_PRTCL_BIT_3		(0x0008U)
#define L3R_PRTCL_BIT_4		(0x0010U)
#define L3R_PRTCL_BIT_5		(0x0020U)
#define L3R_PRTCL_BIT_6		(0x0040U)
#define L3R_PRTCL_BIT_7		(0x0080U)
#define L3R_PRTCL_BIT_8		(0x0100U)
#define L3R_PRTCL_BIT_9		(0x0200U)
#define L3R_PRTCL_BIT_10	(0x0400U)
#define L3R_PRTCL_BIT_11	(0x0800U)
#define L3R_PRTCL_BIT_12	(0x1000U)
#define L3R_PRTCL_BIT_13	(0x2000U)
#define L3R_PRTCL_BIT_14	(0x4000U)
#define L3R_PRTCL_BIT_15	(0x8000U)
#define L3R_PRTCL_BIT_NONE	(0x0000U)
#define L3R_PRTCL_BIT_DEF	(0xFFFFU)

/*---- プロトコルbit再定義 -------------------------------------------------*/
#define L3R_PRTCL_BIT_CAN0		L3R_PRTCL_BIT_0
#define L3R_PRTCL_BIT_CAN1		L3R_PRTCL_BIT_1
#define L3R_PRTCL_BIT_CAN2		L3R_PRTCL_BIT_2
#define L3R_PRTCL_BIT_CAN3		L3R_PRTCL_BIT_3
#define L3R_PRTCL_BIT_CAN4		L3R_PRTCL_BIT_4
#define L3R_PRTCL_BIT_CAN5		L3R_PRTCL_BIT_5
#define L3R_PRTCL_BIT_CAN6		L3R_PRTCL_BIT_6
#define L3R_PRTCL_BIT_CAN7		L3R_PRTCL_BIT_7
#define L3R_PRTCL_BIT_CAN8		L3R_PRTCL_BIT_8
#define L3R_PRTCL_BIT_CAN9		L3R_PRTCL_BIT_9
#define L3R_PRTCL_BIT_CAN10		L3R_PRTCL_BIT_10
#define L3R_PRTCL_BIT_CAN11		L3R_PRTCL_BIT_11
#define L3R_PRTCL_BIT_CAN12		L3R_PRTCL_BIT_12
#define L3R_PRTCL_BIT_CAN13		L3R_PRTCL_BIT_13
#define L3R_PRTCL_BIT_CAN14		L3R_PRTCL_BIT_14
#define L3R_PRTCL_BIT_CAN15		L3R_PRTCL_BIT_15

#define L3R_TOTALCH_MAX			(16U)

/*---- CAN フォーマット共通情報 ---------------------------------------------*/
#define L3R_TCOV_CANCOM_BIT				(0xC0000000U)			/* フォーマット判定ビット */
#define L3R_TCOV_MSK_CANCOM				(~L3R_TCOV_CANCOM_BIT)	/* CANFDフレーム/拡張IDビットマスク用 */
#define L3R_TCOV_CANFD_BIT				(0x40000000U)			/* FDフォーマット判定ビット */
#define L3R_TCOV_CANFD_SHIFT_NO			(30U)					/* CANFDフレームを判断するのに必要なシフト数 */
#define L3R_TCOV_EXD_SHIFT_NO			(31U)					/* 拡張フレーム判断するのに必要なシフト数 */

/*---- CAN FD最大データ長 -------------------------------------------------*/
#define L3R_CAN_DATAMAX			(8U)
#define L3R_CANFD_DATAMAX		(64U)	


#endif	/* L3R_COMMON_H */
