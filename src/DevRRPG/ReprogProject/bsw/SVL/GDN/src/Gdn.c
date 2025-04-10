/* Gdn_c_01_0004 */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Module Name | GUARDIAN共通処理                                             */
/* Notes       |                                                              */
/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision  Date         By       Description                               */
/*----------------------------------------------------------------------------*/
/*  00_0000   2014/07/03   DN 毛    新規作成                                  */
/*  00_0001   2014/11/12   DN 毛    DCMスリープ状態取得処理を追加             */
/*  01_0000   2015/10/30   DT       IUMPR情報消去実施をユーザー入力で切り替え */
/*  01_0001   2015/11/13   DT       MM汎用版対応                              */
/*  01_0002   2015/11/23   DC       マルチコア対応                            */
/*  01_0003   2018/02/13   AUBASS   リプログ対応                              */
/*  01_0004   2019/12/03   AUBASS   Update                                    */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/* Header Files                                                               */
/*----------------------------------------------------------------------------*/
#include <Gdn.h>
#include <Gdn_LocalNotification.h>

/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
    #if ( GDN_CMPSELECT_PDUR != GDN_ON )
#define Gdn_PduR_Init()
    #endif

    #if ( GDN_CMPSELECT_CANTP != GDN_ON )
#define Gdn_CanTp_Init()
#define Gdn_CanTp_MainFunction()
#define Gdn_CanTp_Shutdown()
    #endif

    #if ( GDN_CMPSELECT_DCM_DSP != GDN_ON )
#define Gdn_Dcm_Init()
#define Gdn_Dcm_MainFunction()
#define Gdn_Dcm_Shutdown()
    #endif

/*----------------------------------------------------------------------------*/
/* Local Types                                                                */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Internal Function Prototypes                                               */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Static Constants                                                           */
/*----------------------------------------------------------------------------*/
#define GDN_START_SEC_CST
#include <Gdn_MemMap.h>

#define GDN_STOP_SEC_CST
#include <Gdn_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Static Variables                                                           */
/*----------------------------------------------------------------------------*/
#define GDN_START_SEC_VAR
#include <Gdn_MemMap.h>

#define GDN_STOP_SEC_VAR
#include <Gdn_MemMap.h>

/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define GDN_START_SEC_CODE
#include <Gdn_MemMap.h>

/******************************************************************************/
/* Function Name | Gdn_Init                                                   */
/* Description   | 初期化処理                                                 */
/******************************************************************************/
FUNC(void, GDN_CODE_SLOW) Gdn_Init (void)
{
    Gdn_TmrSrv_Init();
    Gdn_EvtDistributor_Init();
    Gdn_CanTp_Init();
    Gdn_PduR_Init();
    Gdn_Dcm_Init();
}

/******************************************************************************/
/* Function Name | Gdn_MainFunction                                           */
/* Description   | 定周期処理                                                 */
/* Re-entrancy   | Reentrant                                                  */
/* Parameters    | -                                                          */
/* Return Value  | -                                                          */
/* Notes         | -                                                          */
/******************************************************************************/
FUNC(void, GDN_CODE_SLOW) Gdn_MainFunction (void)
{
    Gdn_Dcm_MainFunction();
#if ( (REPROG_CFG_ETH_USE == STD_OFF) && (REPROG_CFG_CXPI_USE == STD_OFF) )
    Gdn_Rte_DequeueEvent_TimeOut( GDN_DEQUEUENUM_TIMEOUT );
#endif
}

/******************************************************************************/
/* Function Name | Gdn_Time                                                   */
/* Description   | 1ms周期処理                                                */
/* Re-entrancy   | Reentrant                                                  */
/* Parameters    | -                                                          */
/* Return Value  | -                                                          */
/* Notes         | -                                                          */
/******************************************************************************/
FUNC(void, GDN_CODE_SLOW) Gdn_Time (void)
{
    Gdn_Dcm_Time();
    Gdn_CanTp_MainFunction();
    Gdn_TmrSrv_MainFunction( GDN_TMRSRV_ASYNC_TimeOut );
#if ( (REPROG_CFG_ETH_USE == STD_ON) || (REPROG_CFG_CXPI_USE == STD_ON) )
    Gdn_Rte_DequeueEvent_TimeOut( GDN_DEQUEUENUM_TIMEOUT );
#endif
}

/******************************************************************************/
/* Function Name | Gdn_Shutdown                                               */
/* Description   | 終了処理                                                   */
/******************************************************************************/
FUNC(void, GDN_CODE_SLOW) Gdn_Shutdown (void)
{
    Gdn_Dcm_Shutdown();
    Gdn_CanTp_Shutdown();
}

#define GDN_STOP_SEC_CODE
#include <Gdn_MemMap.h>

/**** End of File *************************************************************/
