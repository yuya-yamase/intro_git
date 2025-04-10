/* Gdn_Dcm_Ucfg_c_00_0004 */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Module Name | Gdn_Dcm_Ucfg.c                                               */
/* Notes       | ツールバージョン：GUARDIAN_218v41_MET_Tool217                */
/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision  Date         By       Description                               */
/*----------------------------------------------------------------------------*/
/*  00_0000   2014/03/dd   DN矢加部 新規作成                                  */
/*  00_0001   2014/09/25   DT       DTCKindのセッションサポート判定を追加     */
/*  00_0002   2018/02/13   AUBASS   リプログ対応                              */
/*  00_0003   2019/12/03   AUBASS   Update                                    */
/*  00_0004   2021/03/09   AUBASS   Update                                    */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/* Header Files                                                               */
/*----------------------------------------------------------------------------*/
#include <Gdn.h>
#include <Gdn_Ucfg.h>

/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/

#if ( GDN_DCM_CANTP_CHANGEPARAMETER_ENABLE == GDN_ON )
#define     Gdn_Dcm_Set_SessionCtrlConfig(index)                               \
{                                                                              \
    (Gdn_Dcm_SesCtrlType)GDN_DCM_SESSIONCTRL_##index                           \
    ,(Gdn_TimeoutValueType)GDN_DCM_P2MAX_TIMECNT_##index                       \
    ,(Gdn_TimeoutValueType)GDN_DCM_P2MAX_ASTER_EX_TIMECNT_##index              \
    ,(gdn_bool)GDN_DCM_S3TIMER_ENABLE_##index                                  \
    ,(gdn_uint8)GDN_DCM_BS_VALUE_PER_SESSION_##index                           \
    ,(gdn_uint8)GDN_DCM_STMIN_VALUE_PER_SESSION_##index                        \
}
#elif ( GDN_DCM_CANTP_CHANGEPARAMETER_ENABLE == GDN_OFF )
#define     Gdn_Dcm_Set_SessionCtrlConfig(index)                               \
{                                                                              \
    (Gdn_Dcm_SesCtrlType)GDN_DCM_SESSIONCTRL_##index                           \
    ,(Gdn_TimeoutValueType)GDN_DCM_P2MAX_TIMECNT_##index                       \
    ,(Gdn_TimeoutValueType)GDN_DCM_P2MAX_ASTER_EX_TIMECNT_##index              \
    ,(gdn_bool)GDN_DCM_S3TIMER_ENABLE_##index                                  \
}
#else
#error "Macro Decralation Error"
#endif

/*----------------------------------------------------------------------------*/
/* Static Variables                                                           */
/*----------------------------------------------------------------------------*/
#define GDN_DCM_START_SEC_VAR
#include <Gdn_Dcm_MemMap.h>

#define GDN_DCM_STOP_SEC_VAR
#include <Gdn_Dcm_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Static Constants                                                           */
/*----------------------------------------------------------------------------*/
#define GDN_DCM_START_SEC_CST
#include <Gdn_Dcm_MemMap.h>

/* セッション状態関連コンフィグレーション項目 */

GdnConst Gdn_Dcm_SessionCtrlConfigType   Gdn_Dcm_SessionCtrlConfig[ GDN_DCM_SESSIONCTRL_SUPPORT_NUM ] = {
    Gdn_Dcm_Set_SessionCtrlConfig(0),
    Gdn_Dcm_Set_SessionCtrlConfig(1)
};


#define GDN_DCM_STOP_SEC_CST
#include <Gdn_Dcm_MemMap.h>

/*-- End Of File -------------------------------------------------------*/

