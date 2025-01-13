/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file		L3R_Gate_Ig.h
 * @brief		
 * @details		
 * @note		
 * @date		v1.00   2016/04/01  H.Tanaka    新規作成 
 * @date		v1.01   2017/03/03  Y.Katayama  19PF向け型定義対応 
 * @date		v2.00	2018/11/21	Y.Katayama	中継改善(オブジェクト不変)
 ****************************************************************************/

#ifndef	L3R_GATE_IG_H
#define	L3R_GATE_IG_H


/*----外部変数宣言・変数名置換マクロ-----------------------------------------*/


/*----プロトタイプ宣言------------------------------------------------------*/

#define GW_L3R_START_SEC_CODE
#include "GW_L3R_Memmap.h"
extern uint8 L3R_NGate_Ig_Init(void);
extern uint8 L3R_NGate_Ig_Start(uint8 NetSts);
extern uint8 L3R_NGate_Ig_Stop(uint8 NetSts);
extern uint8 L3R_NGate_Ig_Standby(uint8 NetSts);
extern uint8 L3R_NGate_Ig_Defect(void);
#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"

#endif	/* L3R_GATE_IG_H */
