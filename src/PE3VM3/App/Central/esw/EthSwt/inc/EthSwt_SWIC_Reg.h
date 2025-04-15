#ifndef ETHSWT_SWIC_REG_H
#define ETHSWT_SWIC_REG_H
#include <Std_Types.h>
#include "EthSwt_BSW_define.h"		/* C-DC MCUにはBSW ETHが載っていないため、代わりに定義 */

#define ETHSWT_SWIC_REG_FACT_CRC	(0x0002uL)	/* CRC異常 */
#define ETHSWT_SWIC_REG_FACT_BSY	(0x0004uL)	/* BSY待ち */
#define ETHSWT_SWIC_REG_FACT_SPI	(0x0008uL)	/* CRC異常→SPI異常 */
#define ETHSWT_SWIC_REG_FACT_INIT	(0x0010uL)	/* 初期化でレジスタ/テーブル化け */
#define ETHSWT_SWIC_REG_FACT_SWIC	(0x0020uL)	/* SWIC内部エラー */

void EthSwt_SWIC_Reg_Init(void);
Std_ReturnType EthSwt_SWIC_Reg_SetSwitchPortMode(const uint8 SwitchPortIdx, const Eth_ModeType PortMode);
Std_ReturnType EthSwt_SWIC_Reg_GetLinkState(const uint8 SwitchPortIdx, EthTrcv_LinkStateType *const LinkStatePtr);

#endif /* ETHSWT_SWIC_REG_H */
