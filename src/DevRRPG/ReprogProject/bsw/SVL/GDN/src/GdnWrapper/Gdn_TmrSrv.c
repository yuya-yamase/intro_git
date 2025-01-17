/* Gdn_TmrSrv_c_01_0001 */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Module Name | タイマサービス(GURADIAN内作成タイマサービス使用時用)         */
/* Notes       | 本ファイルはGUARDIANのタイマーサービス処理のWrapperであり、  */
/*             | BSWにタイマサービスが備わっていない製品用ファイルである。    */
/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision  Date         By       Description                               */
/*----------------------------------------------------------------------------*/
/*  01_0000   2014/12/16   DN野田   新規作成                                  */
/*  01_0001   2018/02/13   AUBASS   初期設定処理を追加                        */
/*                                  RAM小容量マイコン向け対応                 */
/*  01_0002   2022/06/07   AUBASS   Update                                    */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/* Header Files                                                               */
/*----------------------------------------------------------------------------*/
#include <Gdn_Types.h>
#include <Gdn_Ucfg.h>
#include "Gdn_Std_Lib.h"
#include "Gdn_TmrSrv.h"
#include <Std_Types.h>
#include <Tm.h>
#include <EcuM.h>

/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/* msec→usec変換 */
#define GDN_TMRSRV_MSEC_TO_USEC  (1000U)

/* APIID */
#define GDN_TMRSRV_API_ID_INIT           (0x00U)
#define GDN_TMRSRV_API_ID_SETTIMER       (0x01U)
#define GDN_TMRSRV_API_ID_RELEASETIMER   (0x02U)
#define GDN_TMRSRV_API_ID_MAINFUNCTION   (0x03U)

/* エラー要因 */
#define GDN_TMRSRV_E_TIMER_HANDLE       (0x00U)

/* 最大差分時間 */
#define GDN_TMRSRV_MAXTIMESPAN    (0xFFFFFFFFUL)

/*----------------------------------------------------------------------------*/
/* Local Types                                                                */
/*----------------------------------------------------------------------------*/
typedef struct {
    Tm_PredefTimer1us32bitType TimerInstance;
    gdn_uint32  Count;
    gdn_uint16  SetData;
    gdn_uint8   AlarmStatus;
} Gdn_TmrSrv_AlarmDataType;

/*----------------------------------------------------------------------------*/
/* Internal Function Prototypes                                               */
/*----------------------------------------------------------------------------*/
static void Gdn_TmrSrv_ReportError
(
    gdn_uint8 ApiId,
    gdn_uint8 ErrorId
);

/*----------------------------------------------------------------------------*/
/* Static Variables                                                           */
/*----------------------------------------------------------------------------*/
#define GDN_WRAPPER_START_SEC_VAR
#include <Gdn_Wrapper_MemMap.h>

static Gdn_TmrSrv_AlarmDataType    Gdn_TmrSrv_AlarmData[ GDN_TMRSRV_MaxIdCnt ];

#define GDN_WRAPPER_STOP_SEC_VAR
#include <Gdn_Wrapper_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Static Constants                                                           */
/*----------------------------------------------------------------------------*/
#define GDN_WRAPPER_START_SEC_CST
#include <Gdn_Wrapper_MemMap.h>

#define GDN_WRAPPER_STOP_SEC_CST
#include <Gdn_Wrapper_MemMap.h>

/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define GDN_WRAPPER_START_SEC_CODE
#include <Gdn_Wrapper_MemMap.h>

/******************************************************************************/
/* Function Name | Gdn_TmrSrv_SetTimer                                        */
/* Description   | タイマの設定(開始)処理                                     */
/******************************************************************************/
FUNC(void, GDN_TMRSRV_CODE_SLOW) Gdn_TmrSrv_SetTimer
(
    VAR(Gdn_TimerIdType, AUTOMATIC) TimerId,
    VAR(Gdn_TimeoutValueType, AUTOMATIC) TimeoutValue,
    VAR(gdn_uint16, AUTOMATIC) Synchronizer
)
{
    VAR(Std_ReturnType, AUTOMATIC) TimerStartRet;  /* API戻り値格納用 */

    /* タイマ開始時間取得 */
    TimerStartRet = Tm_ResetTimer1us32bit(&Gdn_TmrSrv_AlarmData[ TimerId ].TimerInstance);
    /* タイマ開始時間の取得結果判定 */
    if( (Std_ReturnType)E_OK == TimerStartRet )
    {
        Gdn_TmrSrv_AlarmData[ TimerId ].Count = (gdn_uint32)TimeoutValue * (gdn_uint32)GDN_TMRSRV_MSEC_TO_USEC; /* no wrap around */
        Gdn_TmrSrv_AlarmData[ TimerId ].SetData = Synchronizer;
        Gdn_TmrSrv_AlarmData[ TimerId ].AlarmStatus = (gdn_uint8)GDN_ON;
    }
    else
    {
        /* エラー通知 */
        Gdn_TmrSrv_ReportError(GDN_TMRSRV_API_ID_SETTIMER,GDN_TMRSRV_E_TIMER_HANDLE);
    }
}

/******************************************************************************/
/* Function Name | Gdn_TmrSrv_ReleaseTimer                                    */
/* Description   | タイマの解放(停止)処理                                     */
/******************************************************************************/
FUNC(void, GDN_TMRSRV_CODE_SLOW) Gdn_TmrSrv_ReleaseTimer
(
    VAR(Gdn_TimerIdType, AUTOMATIC) TimerId
)
{
    Gdn_TmrSrv_AlarmData[ TimerId ].AlarmStatus = (gdn_uint8)GDN_OFF;
}

/******************************************************************************/
/* Function Name | Gdn_TmrSrv_MainFunction                                    */
/* Description   | タイマメイン処理                                           */
/******************************************************************************/
FUNC(void, GDN_TMRSRV_CODE_SLOW) Gdn_TmrSrv_MainFunction
(
    VAR(gdn_uint8, AUTOMATIC) TimerPriority
)
{
    gdn_sint32 TimerId;
    VAR(Std_ReturnType, AUTOMATIC) GetTimeRet;             /* API戻り値格納用 */
    VAR(gdn_uint32, AUTOMATIC) TimeSpan;              /* タイマ差分時間格納用 */

    Gdn_DI();
    for( TimerId = 0; TimerId < (gdn_sint32)GDN_TMRSRV_MaxIdCnt; TimerId++ )
    {
        if( Gdn_TmrSrv_AlarmData[ TimerId ].AlarmStatus != (gdn_uint8)GDN_OFF )
        {
            if( TimerPriority == gdn_tmrsrv_NotificationTable[ TimerId ].Priority )
            {
                /* 最大差分時間にて初期値設定 */
                TimeSpan = GDN_TMRSRV_MAXTIMESPAN;
                /* タイマ経過時間取得 */
                GetTimeRet = Tm_GetTimeSpan1us32bit(&Gdn_TmrSrv_AlarmData[ TimerId ].TimerInstance, &TimeSpan);
                /* タイマ経過時間取得結果確認 */
                if( (Std_ReturnType)E_OK == GetTimeRet )
                {
                    /* 差分時間とタイマ値を比較 */
                    if( TimeSpan >= Gdn_TmrSrv_AlarmData[ TimerId ].Count )
                    {
                        Gdn_TmrSrv_AlarmData[ TimerId ].AlarmStatus = (gdn_uint8)GDN_OFF;
                        gdn_tmrsrv_NotificationTable[ TimerId ].CallDst( (Gdn_TimerIdType)TimerId,
                            Gdn_TmrSrv_AlarmData[ TimerId ].SetData );
                    }
                }
                else
                {
                    /* エラー通知 */
                    Gdn_TmrSrv_ReportError(GDN_TMRSRV_API_ID_MAINFUNCTION,GDN_TMRSRV_E_TIMER_HANDLE);
                }
            }
        }
    }
    Gdn_EI();
}

/******************************************************************************/
/* Function Name | Gdn_TmrSrv_Init                                            */
/* Description   | 初期設定処理                                               */
/******************************************************************************/
FUNC(void, GDN_TMRSRV_CODE_SLOW) Gdn_TmrSrv_Init (void)
{
    gdn_uint32 TimerId;

    for( TimerId = 0UL; TimerId < (gdn_uint32)GDN_TMRSRV_MaxIdCnt; TimerId++ )
    {
        Gdn_TmrSrv_AlarmData[ TimerId ].TimerInstance.StartPoint = 0x00000000UL;
        Gdn_TmrSrv_AlarmData[ TimerId ].Count = 0x00000000UL;
        Gdn_TmrSrv_AlarmData[ TimerId ].SetData = 0x0000U;
        Gdn_TmrSrv_AlarmData[ TimerId ].AlarmStatus = GDN_OFF;
    }
}

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/******************************************************************************/
/* Function Name | Gdn_TmrSrv_ReportError                                     */
/* Description   | エラー情報通知処理                                         */
/* Preconditions |                                                            */
/* Parameters    | [IN] ApiId   : Api ID                                      */
/*               | [IN] ErrorId : Error ID                                    */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static void Gdn_TmrSrv_ReportError
(
    gdn_uint8 ApiId,
    gdn_uint8 ErrorId
)
{
    EcuM_ErrorType ErrorInfo;

    ErrorInfo.ModuleId = ECUM_MODULE_GDNTMRSRV;
    ErrorInfo.ApiId = ApiId;
    ErrorInfo.ErrorId = ErrorId;
    EcuM_ReportError(&ErrorInfo);

    return;
}

#define GDN_WRAPPER_STOP_SEC_CODE
#include <Gdn_Wrapper_MemMap.h>

/**** End of File *************************************************************/
