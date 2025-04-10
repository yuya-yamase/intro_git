/* Gdn_TmrSrv_Ucfg_c_00_0004 */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Module Name | タイマサービス（コンフィグ）                                 */
/* Notes       | 本ファイルはGUARDIANのタイマーサービス処理のWrapperであり、  */
/*             | BSWにタイマサービスが備わっていない製品用ファイルである。    */
/*             | ツールバージョン：GUARDIAN_218v41_MET_Tool217                */
/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision  Date         By       Description                               */
/*----------------------------------------------------------------------------*/
/*  00_0000   2014/05/15   DN毛     テンプレートの新規作成                    */
/*  00_0001   2014/10/10   DN矢加部 GDN_TMRSRV_ID_DCP_0,1,2の通知関数変更     */
/*  00_0002   2014/12/16   DN野田   製品共通関数部分の分離                    */
/*  00_0003   2018/02/13   AUBASS   コンフィグ定義変更                        */
/*  00_0004   2019/12/03   AUBASS   Update                                    */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/* Header Files                                                               */
/*----------------------------------------------------------------------------*/
#include <Gdn.h>
#include <Gdn_Ucfg.h>

#include "Gdn_TmrSrv.h"

/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Local Types                                                                */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Internal Function Prototypes                                               */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Static Variables                                                           */
/*----------------------------------------------------------------------------*/
#define GDN_WRAPPER_START_SEC_VAR
#include <Gdn_Wrapper_MemMap.h>

#define GDN_WRAPPER_STOP_SEC_VAR
#include <Gdn_Wrapper_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Static Constants                                                           */
/*----------------------------------------------------------------------------*/
#define GDN_WRAPPER_START_SEC_CST
#include <Gdn_Wrapper_MemMap.h>

GdnConst Gdn_TmrSrv_NotificationTblType gdn_tmrsrv_NotificationTable[GDN_TMRSRV_MaxIdCnt] = {
        /* タイマID */          /* タスク種別 */        /* 通知先関数   */
    {   GDN_TMRSRV_ID_CANTP_0 , GDN_TMRSRV_ASYNC_TimeOut , &Gdn_CanTp_TimeoutIndication              },
    {   GDN_TMRSRV_ID_CANTP_1 , GDN_TMRSRV_ASYNC_TimeOut , &Gdn_CanTp_TimeoutIndication              },
    {   GDN_TMRSRV_ID_CANTP_2 , GDN_TMRSRV_ASYNC_TimeOut , &Gdn_CanTp_TimeoutIndication              },
    {   GDN_TMRSRV_ID_CANTP_3 , GDN_TMRSRV_ASYNC_TimeOut , &Gdn_CanTp_TimeoutIndication              },
    {   GDN_TMRSRV_ID_DCP_0   , GDN_TMRSRV_ASYNC_TimeOut , &Gdn_Dcm_TimeoutIndication                },
    {   GDN_TMRSRV_ID_DCP_1   , GDN_TMRSRV_ASYNC_TimeOut , &Gdn_Dcm_TimeoutIndication                },
    {   GDN_TMRSRV_ID_DCP_2   , GDN_TMRSRV_ASYNC_TimeOut , &Gdn_Dcm_TimeoutIndication                }
};

#define GDN_WRAPPER_STOP_SEC_CST
#include <Gdn_Wrapper_MemMap.h>

/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define GDN_WRAPPER_START_SEC_CODE
#include <Gdn_Wrapper_MemMap.h>

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define GDN_WRAPPER_STOP_SEC_CODE
#include <Gdn_Wrapper_MemMap.h>

/**** End of File *************************************************************/

