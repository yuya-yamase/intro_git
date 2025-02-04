/* Fee_Dfc_Ram.c v1-1-0                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/DFC/RAM/CODE                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Fee.h>

#include "../inc/Fee_Dfc_Ram.h"

#include "../inc/Fee_ExConst.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define FEE_START_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>

VAR(uint32, FEE_VAR_NO_INIT) Fee_DrvWrap_State;                   /* 上位層へ返すステータス */
VAR(uint32, FEE_VAR_NO_INIT) Fee_DrvWrap_WrittenAdr;              /* 上位層へ返す最終書込みレコードの先頭アドレス */
VAR(uint32, FEE_VAR_NO_INIT) Fee_Dfc_BlankCheckEndAdr;
VAR(uint32, FEE_VAR_NO_INIT) Fee_Dfc_MaxBlankCheckNum;
VAR(uint32, FEE_VAR_NO_INIT) Fee_DrvWrap_BlankCheck_State;        /* ブランクチェック状態 */

#if ( FEE_USE_REDUNDANCY_RAM == STD_ON )
/* Redundancy Data */
VAR(uint32, FEE_VAR_NO_INIT) Fee_DrvWrap_StateSub;
VAR(uint32, FEE_VAR_NO_INIT) Fee_DrvWrap_WrittenAdrSub;
VAR(uint32, FEE_VAR_NO_INIT) Fee_Dfc_BlankCheckEndAdrSub;
VAR(uint32, FEE_VAR_NO_INIT) Fee_Dfc_MaxBlankCheckNumSub;
VAR(uint32, FEE_VAR_NO_INIT) Fee_DrvWrap_BlankCheck_StateSub;
#endif /* FEE_USE_REDUNDANCY_RAM == STD_ON */

#define FEE_STOP_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/08/19                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
