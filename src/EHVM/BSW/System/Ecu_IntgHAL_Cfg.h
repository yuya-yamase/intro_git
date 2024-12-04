/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		Ecu_IntgHAL_Cfg.h
 * [Module]			Int
 * [Function]		Int
 * [Notes]			None
 ****************************************************************************/

#ifndef ECU_INTGHAL_CFG_H
#define ECU_INTGHAL_CFG_H

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *		Types
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *		Symbols
 *--------------------------------------------------------------------------*/

// 起動要因判定
#define MSK_u4WUF0_A0_TMR (0x00000000UL)
#define MSK_u4WUF0_A1_TMR (0x00000000UL)
#define MSK_u4WUF0_A2_TMR (0x00000080UL) /* TAUJ3_0WUFビット番号 A2 BIT07 */

#define MSK_u4WUF0_A0_ANY (0x00000000UL)
#define MSK_u4WUF0_A1_ANY (0x00000000UL)
#define MSK_u4WUF0_A2_ANY (0x00000000UL)

// FPU初期設定
#define VAL_u4FPSR ((int)0x00220000)

#define ECU_INTG_ST_RESET_BY_SS      (0U) 
#define ECU_INTG_ST_RESET_BY_ECU_ARB (1U) 
#define ECU_INTG_ST_RESET_BY_SYSERR  (2U) 
#define ECU_INTG_ST_RESET_BY_FETRAP  (3U) 
#define ECU_INTG_ST_RESET_BY_TRAP0   (4U) 
#define ECU_INTG_ST_RESET_BY_TRAP1   (5U) 
#define ECU_INTG_ST_RESET_BY_RIE     (6U) 
#define ECU_INTG_ST_RESET_BY_FPE_FXE (7U) 
#define ECU_INTG_ST_RESET_BY_UCPOP   (8U) 
#define ECU_INTG_ST_RESET_BY_MIP_MDP (9U) 
#define ECU_INTG_ST_RESET_BY_PIE     (10U) 
#define ECU_INTG_ST_RESET_BY_MAE     (11U) 
#define ECU_INTG_ST_RESET_BY_FENMI   (12U) 
#define ECU_INTG_ST_RESET_BY_FEINT   (13U) 
#define ECU_INTG_ST_RESET_BY_FACTORY (14U) 

#define ECU_INTG_ST_RESET_BY_UNKNOWN (31U)

#endif /* ECU_INTGHAL_CFG_H */
