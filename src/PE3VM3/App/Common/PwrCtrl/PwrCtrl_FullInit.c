/* PwrCtrl_FullInit_c_v1-0-0                                                */
/****************************************************************************/
/* Copyright (C) 2023 Denso Co.,Ltd. All rights reserved.                   */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | PwrCtrl_FullInit/CODE                                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "PwrCtrl_cfg_private.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define PWRCTRL_FULLINIT_TIME      (5000U / PWRCTRL_CFG_TASK_TIME)    /* 暫定対応 */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
static void vd_s_PwrCtrlFullInitVM2Judge( void );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
static U1 u1_s_PwrCtrl_FullInit_VM2Result;   /* VM2完全初期化結果 */
static U1 u1_s_PwrCtrl_FullInit_McuResult;   /* MCU完全初期化結果 */
static U4 u4_s_PwrCtrl_FullInit_Time;        /* 完全初期化結果処理時間 */

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Functions                                                                */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* Scheduled Functions                                                      */
/****************************************************************************/
/*****************************************************************************
  Function      : vd_g_PwrCtrlFullInitInit
  Description   : 初期化関数
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlFullInitInit( void )
{
    u1_s_PwrCtrl_FullInit_McuResult = (U1)PWRCTRL_FULLINIT_RESULT_NON;
    u1_s_PwrCtrl_FullInit_VM2Result = (U1)PWRCTRL_FULLINIT_RESULT_NON;
    u4_s_PwrCtrl_FullInit_Time = (U4)PWRCTRL_FULLINIT_TIME_INIT;

    return;
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlFullInitSeq
  Description   : 完全初期化シーケンス
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlFullInitSeq( void )
{
    /* VM2完全初期化結果が要求中の場合 */
    if(u1_s_PwrCtrl_FullInit_VM2Result == (U1)PWRCTRL_FULLINIT_RESULT_INPRC)
    {
        /* VM2完全初期化結果判定処理 */
        vd_s_PwrCtrlFullInitVM2Judge();
    }

    /* 【ToDo】VM3初期化結果の判定処理 */

    /* VM2完全初期化結果が要求中の場合 */
    if(u1_s_PwrCtrl_FullInit_VM2Result == (U1)PWRCTRL_FULLINIT_RESULT_INPRC)
    {
        /* MCU完全初期化処理時間がタイムアウトの場合 */
        if(u4_s_PwrCtrl_FullInit_Time >= (U4)PWRCTRL_FULLINIT_TIME)
        {
            u1_s_PwrCtrl_FullInit_McuResult = (U1)PWRCTRL_FULLINIT_RESULT_NG;
            /* VM2完全初期化開始通知データ設定(要求無し) */
            vd_g_PwrCtrlComTxSetInitStart((U1)PWRCTRL_COM_FULLINITSTART_NON);
        }
        else
        {
            u4_s_PwrCtrl_FullInit_Time++;
        }
    }
    /* VM2完全初期化結果が成功の場合 */
    else if(u1_s_PwrCtrl_FullInit_VM2Result == (U1)PWRCTRL_FULLINIT_RESULT_OK)
    {
        u1_s_PwrCtrl_FullInit_McuResult = (U1)PWRCTRL_FULLINIT_RESULT_OK;
    }
    /* VM2完全初期化結果が失敗の場合 */
    else
    {
        u1_s_PwrCtrl_FullInit_McuResult = (U1)PWRCTRL_FULLINIT_RESULT_NG;
    }

    return;
}

/*****************************************************************************
  Function      : vd_s_PwrCtrlFullInitVM2Judge
  Description   : VM2完全初期化結果判定処理
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
static void vd_s_PwrCtrlFullInitVM2Judge( void )
{
    U1 u1_t_vm2result;

    /* VM2完全初期化結果取得処理 */
    u1_t_vm2result = u1_g_PwrCtrlComGetFullInitCompVm2();
    /* VM2完全初期化結果が成功 または VM2初期化結果が失敗の場合 */
    if((u1_t_vm2result == (U1)PWRCTRL_COM_FULLINITCOMP_OK)
     ||(u1_t_vm2result == (U1)PWRCTRL_COM_FULLINITCOMP_NG))
    {
        /* VM2完全初期化結果を更新 */
        u1_s_PwrCtrl_FullInit_VM2Result = u1_t_vm2result;
        /* VM2完全初期化開始通知データ設定(要求無し) */
        vd_g_PwrCtrlComTxSetInitStart((U1)PWRCTRL_COM_FULLINITSTART_NON);
    }

    return;
}

/*****************************************************************************
  Function      : u1_g_PwrCtrlFullInitGetResult
  Description   : MCU完全初期化結果取得関数
  param[in/out] : none
  return        : MCU完全初期化結果
  Note          : none
*****************************************************************************/
U1 u1_g_PwrCtrlFullInitGetResult( void )
{
    return ( u1_s_PwrCtrl_FullInit_McuResult );
}

/*****************************************************************************
  Function      : vd_g_PwrCtrlFullInitStartReq
  Description   : 完全初期化シーケンス実行要求関数
  param[in/out] : none
  return        : none
  Note          : none
*****************************************************************************/
void vd_g_PwrCtrlFullInitStartReq( void )
{
    u1_s_PwrCtrl_FullInit_McuResult = (U1)PWRCTRL_FULLINIT_RESULT_INPRC;
    u1_s_PwrCtrl_FullInit_VM2Result = (U1)PWRCTRL_FULLINIT_RESULT_INPRC;
    u4_s_PwrCtrl_FullInit_Time = (U4)PWRCTRL_FULLINIT_TIME_INIT;

    return;
}

/****************************************************************************/
/* Service API                                                              */
/****************************************************************************/
/**** End of File ***********************************************************/
