/* Gdn_TmrSrv_h_00_0003 */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Module Name | タイマサービス（ヘッダー）                                   */
/* Notes       | 本ファイルはGUARDIANのタイマーサービス処理のWrapperであり、  */
/*             | BSWにタイマサービスが備わっていない製品用ファイルである。    */
/*             | ツールバージョン：GUARDIAN_218v41_MET_Tool217                */
/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision  Date         By       Description                               */
/*----------------------------------------------------------------------------*/
/*  00_0000   2014/05/15   DN毛     テンプレートの新規作成                    */
/*  00_0001   2014/12/16   DN野田   製品共通関数部分の分離                    */
/*  00_0002   2018/02/13   AUBASS   タイマID、初期設定処理(Prototypes)の追加  */
/*  00_0003   2019/12/03   AUBASS   Update                                    */
/******************************************************************************/
#ifndef GDN_TMRSRV_H
#define GDN_TMRSRV_H

/*----------------------------------------------------------------------------*/
/* Header Files                                                               */
/*----------------------------------------------------------------------------*/
#include <Gdn_Types.h>

/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/* ユーザ定義のタイマID */
#define GDN_TMRSRV_ID_CANTP_0      ((Gdn_TimerIdType)0U)
#define GDN_TMRSRV_ID_CANTP_1      ((Gdn_TimerIdType)1U)
#define GDN_TMRSRV_ID_CANTP_2      ((Gdn_TimerIdType)2U)
#define GDN_TMRSRV_ID_CANTP_3      ((Gdn_TimerIdType)3U)
#define GDN_TMRSRV_ID_DCP_0        ((Gdn_TimerIdType)4U)
#define GDN_TMRSRV_ID_DCP_1        ((Gdn_TimerIdType)5U)
#define GDN_TMRSRV_ID_DCP_2        ((Gdn_TimerIdType)6U)

/* タイマID数 */
#define GDN_TMRSRV_MaxIdCnt        (7U)

/* タスク種別 */
#define GDN_TMRSRV_ASYNC_TimeOut   (0U)

/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef void (*Gdn_TmrSrv_NotificationType) ( Gdn_TimerIdType TimerId, gdn_uint16 Synchronizer );

typedef struct {
    Gdn_TimerIdType             TimerId;    /* タイマID     */
    gdn_uint8                   Priority;   /* タスク優先度 */
    Gdn_TmrSrv_NotificationType CallDst;    /* 通知先関数   */
} Gdn_TmrSrv_NotificationTblType;


/*----------------------------------------------------------------------------*/
/* Variables                                                                  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define GDN_WRAPPER_START_SEC_CST
#include <Gdn_Wrapper_MemMap.h>

extern GdnConst Gdn_TmrSrv_NotificationTblType  gdn_tmrsrv_NotificationTable[ GDN_TMRSRV_MaxIdCnt ];

#define GDN_WRAPPER_STOP_SEC_CST
#include <Gdn_Wrapper_MemMap.h>

/******************************************************************************/
/* External Function Prototypes                                               */
/******************************************************************************/
/******************************************************************************/
/* Function Name | Gdn_TmrSrv_SetTimer                                        */
/* Description   | タイマの設定(開始)処理                                     */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) TimerId      : タイマID                               */
/*               | (in) TimeoutValue : タイムアウト値（LSB:1, UNIT:ms)        */
/*               | (in) Synchronizer : ユーザ任意の値                         */
/* Return Value  | なし                                                       */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
FUNC(void, GDN_TMRSRV_CODE_SLOW) Gdn_TmrSrv_SetTimer
(
    VAR(Gdn_TimerIdType, AUTOMATIC) TimerId,
    VAR(Gdn_TimeoutValueType, AUTOMATIC) TimeoutValue,
    VAR(gdn_uint16, AUTOMATIC) Synchronizer
);

/******************************************************************************/
/* Function Name | Gdn_TmrSrv_ReleaseTimer                                    */
/* Description   | タイマの解放(停止)処理                                     */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) TimerId      : タイマID                               */
/* Return Value  | なし                                                       */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
FUNC(void, GDN_TMRSRV_CODE_SLOW) Gdn_TmrSrv_ReleaseTimer
(
    VAR(Gdn_TimerIdType, AUTOMATIC) TimerId
);

/******************************************************************************/
/* Function Name | Gdn_TmrSrv_MainFunction                                    */
/* Description   | タイマメイン処理                                           */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | (in) タイマ優先度：タイマサービス発火処理タイミング判定    */
/* Return Value  | なし                                                       */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
FUNC(void, GDN_TMRSRV_CODE_SLOW) Gdn_TmrSrv_MainFunction
(
    VAR(gdn_uint8, AUTOMATIC) TimerPriority
);

/******************************************************************************/
/* Function Name | Gdn_TmrSrv_Init                                            */
/* Description   | 初期設定処理                                               */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameter(s)  | なし                                                       */
/* Return Value  | なし                                                       */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
FUNC(void, GDN_TMRSRV_CODE_SLOW) Gdn_TmrSrv_Init (void);

#endif /* GDN_TMRSRV_H */
/**** End of File *************************************************************/

