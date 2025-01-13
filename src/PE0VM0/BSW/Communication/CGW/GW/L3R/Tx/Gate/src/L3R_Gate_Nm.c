/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file		L3R_Gate_Nm.c
 * @brief		
 * @details		
 * @note		
 * @date		v1.00   2016/04/01  H.Tanaka    新規作成 
 * @date		v1.01   2017/03/03  Y.Katayama  19PF向け型定義対応 
 * @date		v1.02   2018/10/25  T.Yamamura  コードレベルアップ対応(オブジェクト不変)
 * @date		v2.00	2018/11/21	Y.Katayama	中継改善(オブジェクト不変)
 ****************************************************************************/
#include "Std_Types.h"
#include "L3R_GateManager.h"
#include "L3R_Gate_Nm.h"



#define GW_L3R_START_SEC_CODE
#include "GW_L3R_Memmap.h"
/*************************************************************************//**
 * @fn			uint8 L3R_NGate_Nm_Init(void)
 * @brief		初期化処理
 * @details		初期化処理を行う
 * @param		なし
 * @return		NMバス状態
 * @retval		L3R_GM_NS_STANDBY	通信待機
 * @attention 	なし
 * @note		リセットorウェイクアップ初期化時に呼び出される
 ****************************************************************************/
uint8 L3R_NGate_Nm_Init(void)
{
	return L3R_GM_NS_STANDBY;
}


/*************************************************************************//**
 * @fn			uint8 L3R_NGate_Nm_Start(uint8 NetSts)
 * @brief		NMバス状態判定(通信開始)
 * @details		NMバス状態判定(通信開始)を行う
 * @param[in]	NetSts	ネットワークステータス
 * @return		NMバス状態
 * @retval		L3R_GM_NS_STANDBY	通信待機
 * @retval		L3R_GM_NS_START		通信開始
 * @retval		L3R_GM_NS_STOP		通信停止
 * @attention 	なし
 * @note		定期更新で通信"開始"条件成立時に呼び出される
 ****************************************************************************/
uint8 L3R_NGate_Nm_Start(uint8 NetSts)
{
	uint8 Rtn;
	
	switch(NetSts){
		case L3R_GM_NS_STANDBY:
		case L3R_GM_NS_STOP:
			Rtn = L3R_GM_NS_START;
			break;
		default:
			Rtn = NetSts;
			break;
	}

	return Rtn;
}


/*************************************************************************//**
 * @fn			uint8 L3R_NGate_Nm_Stop(uint8 NetSts)
 * @brief		NMバス状態判定(通信停止)
 * @details		NMバス状態判定(通信停止)を行う
 * @param[in]	NetSts	ネットワークステータス
 * @return		NMバス状態
 * @retval		L3R_GM_NS_STANDBY	通信待機
 * @retval		L3R_GM_NS_START		通信開始
 * @retval		L3R_GM_NS_STOP		通信停止
 * @attention 	なし
 * @note		定期更新で通信"停止"条件成立時に呼び出される
 ****************************************************************************/
uint8 L3R_NGate_Nm_Stop(uint8 NetSts)
{
	uint8 Rtn;
	
	switch(NetSts) {
		case L3R_GM_NS_START:
			Rtn = L3R_GM_NS_STOP;
			break;
		default:
			Rtn = NetSts;
			break;
	}

	return Rtn;
}


/*************************************************************************//**
 * @fn			uint8 L3R_NGate_Nm_Standby(uint8 NetSts)
 * @brief		ウェイクアップ時処理
 * @details		ウェイクアップ時処理を行う
 * @param[in]	NetSts	ネットワークステータス
 * @return		NMバス状態
 * @retval		L3R_GM_NS_STANDBY	通信待機
 * @retval		L3R_GM_NS_START		通信開始
 * @retval		L3R_GM_NS_STOP		通信停止
 * @attention 	なし
 * @note		ウェイクアップ条件成立時に呼び出される
 ****************************************************************************/
uint8 L3R_NGate_Nm_Standby(uint8 NetSts)
{
	uint8 Rtn;
	
	switch(NetSts) {
		case L3R_GM_NS_STOP:
			Rtn = L3R_GM_NS_STANDBY;
			break;
		default:
			Rtn = NetSts;
			break;
	}

	return Rtn;
}


/*************************************************************************//**
 * @fn			uint8 L3R_NGate_Nm_Defect(void)
 * @brief		異常時処理
 * @details		異常時処理を行う
 * @param		なし
 * @return		NMバス状態
 * @retval		L3R_GM_NS_STOP		通信停止
 * @attention 	なし
 * @note		異常値("Start nor Standby nor Stop" 状態)検出時に呼び出される
 ****************************************************************************/
uint8 L3R_NGate_Nm_Defect(void)
{
	return L3R_GM_NS_STOP;
}


#define GW_L3R_STOP_SEC_CODE
#include "GW_L3R_Memmap.h"
