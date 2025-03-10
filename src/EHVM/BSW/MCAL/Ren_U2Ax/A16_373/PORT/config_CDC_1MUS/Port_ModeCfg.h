/* Port-r04-301 */
/************************************************************************************************/
/*                                                                                              */
/*     PORT Driver                                                                              */
/*                                                                                              */
/*      Copyright : DENSO CORPORATION                                                           */
/*                                                                                              */
/************************************************************************************************/
#ifndef PORT_MODE_CFG_H
#define PORT_MODE_CFG_H

/*==============================================================================================*/
/* defines / data types / structs / unions / macros                                             */
/*==============================================================================================*/

extern CONST(Port_SetPinModeType, PORT_CONST) cstPort_SetPinMode[];

/* SetPinMode Config */
/* P2_11 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_0					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_MODE_0						((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_0						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_0					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_0					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_0			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_0					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_0						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_0					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_0					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_0				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_0				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_0			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_0				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_0				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_0					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_0			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_0						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_0					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_0				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_0					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_0		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_0					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_0			((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_0				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_0					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_0				((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_0					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_0			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_0				(0U)
/* P2_12 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_1					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_MODE_1						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_1						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_1					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_1					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_1			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_1					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_1						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_1					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_1					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_1				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_1				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_1			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_1				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_1				((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_1					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_1			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_1						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_1					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_1				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_1					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_1		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_1					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_1			((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_1				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_1					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_1				((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_1					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_1			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_1				(0U)
/* P2_13 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_2					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_MODE_2						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_2						((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_2					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_2					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_2			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_2					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_2						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_2					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_2					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_2				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_2				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_2			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_2				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_2				((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_2					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_2			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_2						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_2					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_2				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_2					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_2		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_2					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_2			((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_2				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_2					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_2				((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_2					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_2			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_2				(0U)
/* P2_14 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_3					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_MODE_3						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_3						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_3					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_3					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_3			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_3					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_3						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_3					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_3					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_3				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_3				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_3			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_3				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_3				((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_3					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_3			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_3						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_3					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_3				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_3					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_3		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_3					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_3			((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_3				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_3					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_3				((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_3					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_3			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_3				(0U)
/* P4_5 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_4					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_MODE_4						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_4						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_4					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_4					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_4			((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_4					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_4						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_4					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_4					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_4				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_4				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_4			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_4				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_4				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_4					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_4			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_4						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_4					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_4				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_4					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_4		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_4					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_4			((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_4				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_4					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_4				((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_4					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_4			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_4				(0U)
/* P4_6 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_5					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_MODE_5						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_5						((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_5					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_5					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_5			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_5					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_5						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_5					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_5					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_5				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_5				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_5			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_5				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_5				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_5					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_5			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_5						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_5					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_5				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_5					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_5		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_5					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_5			((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_5				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_5					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_5				((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_5					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_5			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_5				(0U)
/* P4_7 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_6					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_MODE_6						((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_6						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_6					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_6					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_6			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_6					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_6						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_6					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_6					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_6				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_6				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_6			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_6				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_6				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_6					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_6			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_6						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_6					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_6				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_6					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_6		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_6					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_6			((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_6				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_6					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_6				((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_6					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_6			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_6				(0U)
/* P4_10 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_7					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_MODE_7						((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_7						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_7					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_7					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_7			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_7					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_7						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_7					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_7					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_7				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_7				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_7			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_7				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_7				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_7					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_7			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_7						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_7					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_7				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_7					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_7		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_7					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_7			((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_7				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_7					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_7				((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_7					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_7			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_7				(0U)
/* P20_1 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_8					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_MODE_8						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_8						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_8					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_8					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_8			((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_8					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_8						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_8					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_8					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_8				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_8				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_8			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_8				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_8				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_8					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_8			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_8						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_8					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_8				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_8					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_8		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_8					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_8			((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_8				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_8					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_8				((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_8					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_8			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_8				(0U)
/* P20_2 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_9					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_MODE_9						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_9						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_9					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_9					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_9			((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_9					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_9						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_9					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_9					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_9				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_9				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_9			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_9				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_9				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_9					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_9			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_9						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_9					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_9				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_9					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_9		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_9					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_9			((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_9				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_9					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_9				((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_9					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_9			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_9				(0U)
/* P21_0 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_10					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_MODE_10						((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_10					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_10					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_10					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_10			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_10				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_10					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_10					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_10					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_10				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_10			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_10		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_10				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_10				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_10				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_10			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_10						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_10					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_10				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_10					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_10		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_10					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_10		((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_10			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_10				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_10			((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_10					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_10			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_10			(0U)
/* P21_1 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_11					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_MODE_11						((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_11					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_11					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_11					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_11			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_11				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_11					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_11					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_11					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_11				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_11			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_11		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_11				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_11				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_11				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_11			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_11						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_11					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_11				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_11					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_11		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_11					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_11		((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_11			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_11				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_11			((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_11					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_11			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_11			(0U)
/* P21_2 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_12					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_MODE_12						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_12					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_12					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_12					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_12			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_12				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_12					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_12					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_12					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_12				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_12			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_12		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_12				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_12				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_12				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_12			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_12						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_12					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_12				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_12					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_12		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_12					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_12		((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_12			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_12				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_12			((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_12					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_12			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_12			(0U)
/* P24_10 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_13					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_MODE_13						((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_13					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_13					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_13					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_13			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_13				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_13					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_13					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_13					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_13				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_13			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_13		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_13				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_13				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_13				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_13			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_13						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_13					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_13				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_13					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_13		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_13					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_13		((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_13			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_13				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_13			((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_13					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_13			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_13			(0U)
/* P24_12 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_14					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_MODE_14						((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_14					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_14					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_14					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_14			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_14				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_14					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_14					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_14					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_14				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_14			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_14		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_14				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_14				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_14				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_14			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_14						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_14					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_14				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_14					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_14		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_14					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_14		((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_14			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_14				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_14			((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_14					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_14			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_14			(0U)
/* P24_13 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_15					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_MODE_15						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_15					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_15					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_15					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_15			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_15				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_15					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_15					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_15					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_15				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_15			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_15		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_15				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_15				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_15				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_15			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_15						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_15					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_15				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_15					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_15		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_15					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_15		((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_15			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_15				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_15			((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_15					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_15			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_15			(0U)
/* P2_10 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_16					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_MODE_16						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_16					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_16					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_16					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_16			((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_16				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_16					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_16					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_16					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_16				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_16			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_16		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_16				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_16				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_16				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_16			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_16						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_16					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_16				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_16					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_16		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_16					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_16		((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_16			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_16				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_16			((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_16					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_16			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_16			(0U)
/* P8_0 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_17					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_MODE_17						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_17					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_17					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_17					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_17			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_17				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_17					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_17					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_17					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_17				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_17			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_17		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_17				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_17				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_17				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_17			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_17						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_17					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_17				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_17					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_17		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_17					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_17		((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_17			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_17				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_17			((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_17					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_17			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_17			(0U)
/* P8_2 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_18					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_MODE_18						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_18					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_18					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_18					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_18			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_18				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_18					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_18					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_18					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_18				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_18			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_18		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_18				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_18				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_18				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_18			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_18						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_18					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_18				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_18					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_18		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_18					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_18		((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_18			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_18				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_18			((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_18					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_18			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_18			(0U)
/* AP5_1 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_19					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_MODE_19						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_19					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_19					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_19					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_19			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_19				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_19					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_19					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_19					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_19				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_19			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_19		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_19				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_19				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_19				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_19			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_19						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_19					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_19				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_19					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_19		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_19					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_19		((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_19			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_19				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_19			((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_19					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_19			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_19			(0U)
/* P10_0 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_20					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_MODE_20						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_20					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_20					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_20					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_20			((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_20				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_20					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_20					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_20					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_20				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_20			((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_20		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_20				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_20				((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_20				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_20			((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_PORT_20						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_20					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_20				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_20					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_20		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_20					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_20		((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_20			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_20				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_20			((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_20					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_20			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_20			(0U)
/* P10_1 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_21					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_MODE_21						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_21					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_21					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_21					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_21			((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_21				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_21					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_21					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_21					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_21				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_21			((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_21		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_21				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_21				((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_21				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_21			((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_PORT_21						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_21					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_21				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_21					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_21		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_21					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_21		((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_21			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_21				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_21			((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_21					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_21			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_21			(0U)
/* P22_3 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_22					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_MODE_22						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_22					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_22					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_22					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_22			((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_22				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_22					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_22					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_22					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_22				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_22			((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_22		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_22				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_22				((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_22				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_22			((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_PORT_22						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_22					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_22				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_22					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_22		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_22					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_22		((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_22			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_22				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_22			((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_22					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_22			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_22			(0U)
/* P22_4 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_23					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_MODE_23						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_23					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_23					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_23					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_23			((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_23				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_23					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_23					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_23					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_23				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_23			((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_23		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_23				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_23				((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_23				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_23			((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_PORT_23						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_23					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_23				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_23					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_23		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_23					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_23		((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_23			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_23				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_23			((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_23					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_23			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_23			(0U)
/* P10_0 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_24					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_MODE_24						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_24					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_24					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_24					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_24			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_24				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_24					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_24					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_24					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_24				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_24			((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_24		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_24				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_24				((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_24				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_24			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_24						((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_24					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_24				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_24					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_24		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_24					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_24		((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_24			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_24				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_24			((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_24					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_24			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_24			(0U)
/* P10_1 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_25					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_MODE_25						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_25					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_25					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_25					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_25			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_25				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_25					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_25					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_25					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_25				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_25			((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_25		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_25				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_25				((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_25				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_25			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_25						((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_25					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_25				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_25					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_25		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_25					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_25		((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_25			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_25				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_25			((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_25					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_25			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_25			(0U)
/* P22_3 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_26					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_MODE_26						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_26					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_26					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_26					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_26			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_26				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_26					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_26					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_26					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_26				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_26			((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_26		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_26				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_26				((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_26				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_26			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_26						((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_26					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_26				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_26					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_26		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_26					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_26		((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_26			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_26				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_26			((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_26					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_26			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_26			(0U)
/* P22_4 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_27					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_MODE_27						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_27					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_27					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_27					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_27			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_27				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_27					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_27					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_27					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_27				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_27			((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_27		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_27				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_27				((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_27				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_27			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_27						((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_27					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_27				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_27					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_27		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_27					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_27		((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_27			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_27				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_27			((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_27					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_27			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_27			(0U)
/* P2_10 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_28					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_MODE_28						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_28					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_28					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_28					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_28			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_28				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_28					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_28					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_28					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_28				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_28			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_28		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_28				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_28				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_28				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_28			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_28						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_28					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_28				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_28					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_28		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_28					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_28		((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_28			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_28				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_28			((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_28					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_28			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_28			(0U)
/* P2_11 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_29					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_MODE_29						((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_29					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_29					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_29					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_29			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_29				((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_PULL_UP_29					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_29					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_29					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_29				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_29			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_29		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_29				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_29				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_29				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_29			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_29						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_29					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_29				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_29					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_29		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_29					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_29		((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_29			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_29				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_29			((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_29					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_29			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_29			(0U)
/* P2_12 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_30					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_MODE_30						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_30					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_30					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_30					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_30			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_30				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_30					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_30					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_30					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_30				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_30			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_30		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_30				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_30				((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_30				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_30			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_30						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_30					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_30				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_30					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_30		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_30					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_30		((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_30			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_30				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_30			((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_30					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_30			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_30			(0U)
/* P2_13 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_31					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_MODE_31						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_31					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_31					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_31					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_31			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_31				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_31					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_31					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_31					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_31				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_31			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_31		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_31				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_31				((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_31				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_31			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_31						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_31					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_31				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_31					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_31		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_31					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_31		((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_31			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_31				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_31			((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_31					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_31			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_31			(0U)
/* P2_14 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_32					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_MODE_32						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_32					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_32					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_32					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_32			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_32				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_32					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_32					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_32					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_32				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_32			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_32		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_32				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_32				((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_32				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_32			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_32						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_32					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_32				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_32					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_32		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_32					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_32		((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_32			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_32				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_32			((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_32					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_32			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_32			(0U)
/* P4_5 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_33					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_MODE_33						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_33					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_33					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_33					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_33			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_33				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_33					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_33					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_33					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_33				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_33			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_33		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_33				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_33				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_33				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_33			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_33						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_33					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_33				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_33					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_33		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_33					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_33		((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_33			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_33				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_33			((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_33					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_33			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_33			(0U)
/* P4_6 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_34					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_MODE_34						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_34					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_34					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_34					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_34			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_34				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_34					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_34					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_34					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_34				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_34			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_34		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_34				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_34				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_34				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_34			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_34						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_34					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_34				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_34					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_34		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_34					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_34		((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_34			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_34				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_34			((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_34					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_34			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_34			(0U)
/* P4_7 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_35					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_MODE_35						((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_35					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_35					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_35					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_35			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_35				((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_PULL_UP_35					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_35					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_35					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_35				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_35			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_35		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_35				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_35				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_35				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_35			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_35						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_35					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_35				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_35					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_35		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_35					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_35		((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_35			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_35				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_35			((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_35					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_35			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_35			(0U)
/* P4_10 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_36					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_MODE_36						((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_36					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_36					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_36					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_36			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_36				((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_PULL_UP_36					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_36					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_36					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_36				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_36			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_36		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_36				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_36				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_36				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_36			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_36						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_36					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_36				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_36					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_36		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_36					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_36		((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_36			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_36				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_36			((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_36					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_36			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_36			(0U)
/* P20_1 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_37					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_MODE_37						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_37					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_37					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_37					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_37			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_37				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_37					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_37					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_37					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_37				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_37			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_37		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_37				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_37				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_37				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_37			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_37						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_37					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_37				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_37					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_37		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_37					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_37		((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_37			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_37				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_37			((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_37					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_37			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_37			(0U)
/* P20_2 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_38					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_MODE_38						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_38					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_38					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_38					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_38			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_38				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_38					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_38					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_38					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_38				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_38			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_38		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_38				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_38				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_38				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_38			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_38						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_38					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_38				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_38					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_38		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_38					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_38		((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_38			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_38				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_38			((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_38					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_38			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_38			(0U)
/* P21_0 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_39					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_MODE_39						((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_39					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_39					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_39					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_39			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_39				((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_PULL_UP_39					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_39					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_39					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_39				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_39			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_39		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_39				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_39				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_39				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_39			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_39						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_39					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_39				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_39					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_39		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_39					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_39		((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_39			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_39				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_39			((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_39					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_39			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_39			(0U)
/* P21_1 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_40					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_MODE_40						((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_40					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_40					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_40					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_40			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_40				((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_PULL_UP_40					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_40					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_40					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_40				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_40			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_40		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_40				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_40				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_40				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_40			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_40						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_40					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_40				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_40					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_40		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_40					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_40		((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_40			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_40				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_40			((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_40					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_40			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_40			(0U)
/* P21_2 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_41					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_MODE_41						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_41					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_41					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_41					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_41			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_41				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_41					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_41					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_41					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_41				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_41			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_41		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_41				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_41				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_41				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_41			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_41						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_41					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_41				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_41					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_41		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_41					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_41		((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_41			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_41				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_41			((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_41					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_41			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_41			(0U)
/* P24_10 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_42					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_MODE_42						((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_42					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_42					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_42					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_42			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_42				((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_PULL_UP_42					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_42					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_42					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_42				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_42			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_42		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_42				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_42				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_42				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_42			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_42						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_42					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_42				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_42					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_42		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_42					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_42		((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_42			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_42				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_42			((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_42					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_42			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_42			(0U)
/* P24_12 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_43					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_MODE_43						((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_43					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_43					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_43					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_43			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_43				((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_PULL_UP_43					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_43					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_43					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_43				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_43			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_43		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_43				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_43				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_43				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_43			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_43						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_43					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_43				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_43					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_43		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_43					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_43		((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_43			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_43				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_43			((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_43					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_43			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_43			(0U)
/* P24_13 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_44					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_MODE_44						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_44					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_44					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_44					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_44			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_44				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_44					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_44					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_44					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_44				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_44			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_44		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_44				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_44				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_44				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_44			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_44						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_44					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_44				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_44					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_44		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_44					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_44		((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_44			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_44				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_44			((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_44					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_44			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_44			(0U)
/* P2_6 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_45					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_MODE_45						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_45					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_45					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_45					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_45			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_45				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_45					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_45					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_45					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_45				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_45			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_45		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_45				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_45				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_45				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_45			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_45						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_45					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_45				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_45					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_45		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_45					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_45		((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_45			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_45				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_45			((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_45					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_45			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_45			(0U)
/* P2_8 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_46					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_MODE_46						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_46					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_46					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_46					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_46			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_46				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_46					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_46					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_46					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_46				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_46			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_46		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_46				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_46				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_46				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_46			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_46						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_46					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_46				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_46					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_46		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_46					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_46		((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_46			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_46				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_46			((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_46					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_46			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_46			(0U)
/* P21_3 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_47					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_MODE_47						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_47					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_47					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_47					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_47			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_47				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_47					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_47					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_47					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_47				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_47			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_47		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_47				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_47				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_47				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_47			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_47						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PORT_NOT_47					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_VOLTAGE_47				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_LVDS_USE_47					((uint8)0x00U)

/* Noise Filter */
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_ENABLE_47		((uint16)0x0000U)
#define	PORT_U2A_MODE_CFG_FLT_CTRL_47					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DIG_NOISE_ELIM_CTRL_47		((uint8)0x00U)

/* Safe State */
#define	PORT_U2A_MODE_CFG_SAFE_STATE_CTRL_47			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_47				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_ERR_TRG_SEL_EXP_47			((uint8)0x00U)

/* Change Flag */
#define	PORT_U2A_MODE_CFG_MODE_FLAG_47					(1U)
#define	PORT_U2A_MODE_CFG_NOISE_FILTER_FLAG_47			(0U)
#define	PORT_U2A_MODE_CFG_SAFE_STATE_FLAG_47			(0U)

#define	PORT_MODE_CFG_P2_11_MSPI0SI				((Port_PinModeType)0U)
#define	PORT_MODE_CFG_P2_12_MSPI0SC				((Port_PinModeType)1U)
#define	PORT_MODE_CFG_P2_13_MSPI0SO				((Port_PinModeType)2U)
#define	PORT_MODE_CFG_P2_14_MSPI0CSS0				((Port_PinModeType)3U)
#define	PORT_MODE_CFG_P4_5_CXP11TX				((Port_PinModeType)4U)
#define	PORT_MODE_CFG_P4_6_MSPI2SO				((Port_PinModeType)5U)
#define	PORT_MODE_CFG_P4_7_MSPI2SC				((Port_PinModeType)6U)
#define	PORT_MODE_CFG_P4_10_MSPI2SI				((Port_PinModeType)7U)
#define	PORT_MODE_CFG_P20_1_TAUD1O1				((Port_PinModeType)8U)
#define	PORT_MODE_CFG_P20_2_TAUD1O2				((Port_PinModeType)9U)
#define	PORT_MODE_CFG_P21_0_MSPI4SC				((Port_PinModeType)10U)
#define	PORT_MODE_CFG_P21_1_MSPI4SI				((Port_PinModeType)11U)
#define	PORT_MODE_CFG_P21_2_MSPI4SO				((Port_PinModeType)12U)
#define	PORT_MODE_CFG_P24_10_MSPI3SC				((Port_PinModeType)13U)
#define	PORT_MODE_CFG_P24_12_MSPI3SI				((Port_PinModeType)14U)
#define	PORT_MODE_CFG_P24_13_MSPI3SO				((Port_PinModeType)15U)
#define	PORT_MODE_CFG_P2_10_CXP10TX				((Port_PinModeType)16U)
#define	PORT_MODE_CFG_P8_0_DO_LO				((Port_PinModeType)17U)
#define	PORT_MODE_CFG_P8_2_DO_LO				((Port_PinModeType)18U)
#define	PORT_MODE_CFG_AP5_1_DO_LO				((Port_PinModeType)19U)
#define	PORT_MODE_CFG_P10_0_RIIC0SDA				((Port_PinModeType)20U)
#define	PORT_MODE_CFG_P10_1_RIIC0SCL				((Port_PinModeType)21U)
#define	PORT_MODE_CFG_P22_3_RIIC1SDA				((Port_PinModeType)22U)
#define	PORT_MODE_CFG_P22_4_RIIC1SCL				((Port_PinModeType)23U)
#define	PORT_MODE_CFG_P10_0_DO_OD_HI				((Port_PinModeType)24U)
#define	PORT_MODE_CFG_P10_1_DO_OD_HI				((Port_PinModeType)25U)
#define	PORT_MODE_CFG_P22_3_DO_OD_HI				((Port_PinModeType)26U)
#define	PORT_MODE_CFG_P22_4_DO_OD_HI				((Port_PinModeType)27U)
#define	PORT_MODE_CFG_P2_10_DO_LO				((Port_PinModeType)28U)
#define	PORT_MODE_CFG_P2_11_DI				((Port_PinModeType)29U)
#define	PORT_MODE_CFG_P2_12_DO_LO				((Port_PinModeType)30U)
#define	PORT_MODE_CFG_P2_13_DO_LO				((Port_PinModeType)31U)
#define	PORT_MODE_CFG_P2_14_DO_LO				((Port_PinModeType)32U)
#define	PORT_MODE_CFG_P4_5_DO_LO				((Port_PinModeType)33U)
#define	PORT_MODE_CFG_P4_6_DO_LO				((Port_PinModeType)34U)
#define	PORT_MODE_CFG_P4_7_DI				((Port_PinModeType)35U)
#define	PORT_MODE_CFG_P4_10_DI				((Port_PinModeType)36U)
#define	PORT_MODE_CFG_P20_1_DO_LO				((Port_PinModeType)37U)
#define	PORT_MODE_CFG_P20_2_DO_LO				((Port_PinModeType)38U)
#define	PORT_MODE_CFG_P21_0_DI				((Port_PinModeType)39U)
#define	PORT_MODE_CFG_P21_1_DI				((Port_PinModeType)40U)
#define	PORT_MODE_CFG_P21_2_DO_LO				((Port_PinModeType)41U)
#define	PORT_MODE_CFG_P24_10_DI				((Port_PinModeType)42U)
#define	PORT_MODE_CFG_P24_12_DI				((Port_PinModeType)43U)
#define	PORT_MODE_CFG_P24_13_DO_LO				((Port_PinModeType)44U)
#define	PORT_MODE_CFG_P2_6_DO_LO				((Port_PinModeType)45U)
#define	PORT_MODE_CFG_P2_8_DO_LO				((Port_PinModeType)46U)
#define	PORT_MODE_CFG_P21_3_DO_LO				((Port_PinModeType)47U)

#define PORT_MODE_MAX						((Port_PinModeType)48U)

#endif /* PORT_MODE_CFG_H */
/*-- End Of File -------------------------------------------------------------------------------*/
