/****************************************************************************/
/*  ファイル名      L3R_Fail.c                                              */
/*  モジュール名    変換機能(ToyotaCAN専用)                                 */
/*  機能            個別プロトコル情報を共通フォーマットに変換する          */
/*  備考            Toyota向けCANプロトコル専用                             */
/*  変更履歴        V1.00   2013.06.19  Y.Kaseda                            */
/*                        新規作成            CGWコーディング規約 V1.00準拠 */
/*                  V1.01   2013.09.26  Y.tabuchi                           */
/*                        MSG-ID対応、フレーム再構成対応	                */
/*                  V1.02   2013.11.19  R.Moriyama                          */
/*                        MSG-ID対応コンパイルスイッチ導入                  */
/*                        MISRA2004対応                                     */
/*                  V1.03   2014.04.11  H.Tanaka                            */
/*                        MBQ責務見直しに伴いTConverterGet***Data関数の     */
/*                        処理変更                                          */
/*                  V1.04   2014.05.06  R.Moriyama                          */
/*                      ・関数マクロ化に伴い、u1g_ConvertPhysChtoLogicCh、  */
/*                        u1g_ConvertLogicChtoPhysChに名称変更              */
/*                      ・送信ロック時のダイアグフレーム消去の処理を分割    */
/*                      ・バスオフ時のダイアグフレーム消去の処理を分割      */
/*                      ・MSG-ID変換時に制御フレーム判定の条件分岐を追加    */
/*                      ・MISRA2004対応                                     */
/*                  V1.05   2014.05.26  H.Sano                              */
/*                      ・u1g_GW_RTR_TConvertor_GetCanData()、              */
/*                        u1g_GW_RTR_TConvertor_GetDiagData()にRPの範囲チェ */
/*                        ック追加                                          */
/*                  V1.06   2014.06.02  H.Tanaka                            */
/*                        MPU異常時の処理追加                               */
/*                  V1.07   2014.06.04  K.Yokooka                           */
/*                      ・性能改善の為、                                    */
/*                        u2f_GW_RTR_TConvertor_ConverGWHeaderを削除、      */
/*                        u1g_GW_RTR_TConvertor_ReceiveCanData内に移植      */
/*                  V1.08   2014.06.04  R.Moriyama                          */
/*                        MISRA2004対応                                     */
/*                        ・u1g_GW_RTR_TConvertor_ReceiveCanDataの          */
/*                          引数：pu1t_Dataからconstを削除                  */
/*                  V1.09   2014.06.06  K.Yokooka                           */
/*                        バグ管理No.00014620                               */
/*                        ・CANデータ取得要求処理にて、送信先ステータス     */
/*                          がNGの時、送信要求クリアするように変更          */
/*                  V1.10   2014.08.26  S.Matsubara                         */
/*                        課題No.17730                                      */
/*                        ・vdg_GW_RTR_TDiag_ClearChStart関数コールの削除	*/
/*                        ・vdg_GW_RTR_TDiag_ClearChEnd関数名を             */
/*                        ・vdg_GW_RTR_TDiag_ClearChに変更                  */
/*                  V1.11   2015.01.14  N.Shiraishi                         */
/*                        SD-A対応：物理論理chの結合を変更                  */
/*                  V1.20   2015.04.28  H.Tanaka							*/
/*                        SD-A対応：フェールセーフ処理時に呼び出す			*/
/*                        			GateManagerの関数名を変更				*/
/*                  V1.21   2016.02.25  T.Matsumoto							*/
/*						  制御データ中継モード対応							*/
/*                  V1.22   2016.04.01  H.Tanaka							*/
/*						  SD-2対応：MPU異常発生時の処理削除、Gate課題対応	*/
/*                  V1.23   2017.03.03  Y.Katayama							*/
/*						  19PF向け型定義対応								*/
/*						  カットオフ処理、送信フォーマット切り替え処理追加	*/
/*                  V1.24   2017.05.19  Y.Katayama							*/
/*						  中継対象外時の侵入検知対応の処理追加				*/
/*                  V1.25   2018/05/11  A.Yasui(FSI)                        */
/*                        中継のCHとPRTCL_BITの命名規則明確化レベルアップ   */
/*                  V2.00   2018.05.16  T.Yamamura                          */
/*                        ・u1g_GW_RTR_TConvertor_ConvertLogicBitMap()削除  */
/*                        ・GW_RTR_Common.hのインクルード削除               */
/*                        ・L3R_Ids_FltErrFrmInfo.hのインクルード削除       */
/*                  v3.00   2018/08/24  K.Ito(FSI)                          */
/*                          クラス型統一                                    */
/*                  v3.01   2018/09/19  Y.Katayama(FSI)                     */
/*                          送信ロック・バスオフクリア処理追加              */
/*                  v3.02   2018/10/25  T.Yamamura                          */
/*                          コードレベルアップ対応(オブジェクト不変)        */
/*                  v4.00   2018/11/21  Y.Katayama                          */
/*                          中継改善(オブジェクト不変）                     */
/****************************************************************************/
#include "L3R_AutoTCanConvertRule.h"

#include "L3R_config.h"
#include "L3R_Router.h"
#include "L3R_DiagQueRouter.h"
#include "L3R_DynamicQueRouter.h"
#include "L3R_GateManager.h"
#include "L3R_LIB.h"

#include "L3R_canmbq_main.h"

#include "L3R_Fail.h"

/*---マクロ定義------------------------------------------------------------*/

/*----外部変数宣言----------------------------------------------------------*/
#define GW_L3R_START_SEC_NBVA_ZI
#include "GW_L3R_Memmap.h"
uint16 L3R_Fail_FailChBit;			/* フェール発生CH情報 */
#define GW_L3R_STOP_SEC_NBVA_ZI
#include "GW_L3R_Memmap.h"

/*----プロトタイプ宣言------------------------------------------------------*/


#define GW_L3R_START_SEC_CODE
#include "GW_L3R_Memmap.h"
/****************************************************************************/
/*  関数名          void L3R_Fail_Init(void)                                */
/*  処理名          Fail 初期化処理                                         */
/*  機能説明        フェール発生CH情報を初期化する                          */
/*  引数            なし                                                    */
/*  返値            なし                                                    */
/****************************************************************************/
void L3R_Fail_Init(void)
{
	L3R_Fail_FailChBit = L3R_LOG_BIT_NULL;
}

/****************************************************************************/
/*  関数名          void L3R_Fail_MainTask(void)                            */
/*  処理名          Fail 5msタスク処理                                      */
/*  機能説明        フェール発生CH情報を初期化する                          */
/*  引数            なし                                                    */
/*  返値            なし                                                    */
/****************************************************************************/
void L3R_Fail_MainTask(void)
{
	/* フェール発生CH情報初期化 */
	L3R_Fail_FailChBit = L3R_LOG_BIT_NULL;

	return;
}

/****************************************************************************/
/*  関数名          void L3R_Fail_SendLockNotify(uint8 u1t_PhysCh)          */
/*  処理名          送信ロック検出処理                                      */
/*  機能説明        送信ロック検出時のGW処理を実施する                      */
/*  引数            該当Ch(uint8)                                           */
/*  返値            なし                                                    */
/****************************************************************************/
void L3R_Fail_SendLockNotify(uint8 ch)
{
	L3R_DI();
	L3R_Fail_SetFailChBit(ch);
	L3R_EI();
	
	L3R_GateM_Fail(L3R_GM_FAIL_SENDLOCK, ch);
	(void)CANMBQ_ClrSndQueAllWithBuffer(ch);
	QueRouter_ClearCh(&diagQueRouter, ch);
	QueRouter_ClearCh(&dynamicQueRouter, ch);
	
	L3R_DI();
	L3R_Fail_ClrFailChBit();
	L3R_EI();
	return;
}

/****************************************************************************/
/*  関数名          void L3R_Fail_BusoffNotify(uint8 u1t_PhysCh)            */
/*  処理名          バスオフ検出処理                                        */
/*  機能説明        バスオフ検出時のGW処理を実施する                        */
/*  引数            該当Ch(uint8)                                           */
/*  返値            なし                                                    */
/****************************************************************************/
void L3R_Fail_BusoffNotify(uint8 ch)
{	
	L3R_DI();
	L3R_Fail_SetFailChBit(ch);
	L3R_EI();
	
	L3R_GateM_Fail(L3R_GM_FAIL_BUSOFF, ch);
	(void)CANMBQ_ClrSndQueAllWithBuffer(ch);
	QueRouter_ClearCh(&diagQueRouter, ch);
	QueRouter_ClearCh(&dynamicQueRouter, ch);
	
	L3R_DI();
	L3R_Fail_ClrFailChBit();
	L3R_EI();
	return ;
}

#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"
