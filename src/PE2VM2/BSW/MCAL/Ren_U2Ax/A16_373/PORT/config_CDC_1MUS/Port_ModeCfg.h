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
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_1				((uint8)0x00U)
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
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_2				((uint8)0x00U)
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
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_3				((uint8)0x00U)
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
/* P6_6 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_8					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_MODE_8						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_8						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_8					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_8					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_8			((uint8)0x00U)
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
/* P20_1 */
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
/* P20_2 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_10					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_MODE_10						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_10					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_10					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_10					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_10			((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_10				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_10					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_10					((uint8)0x00U)
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
/* P21_0 */
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
/* P21_1 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_12					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_MODE_12						((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_12					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_12					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_12					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_12			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_12				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_12					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_12					((uint8)0x01U)
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
/* P21_2 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_13					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_MODE_13						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_13					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_13					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_13					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_13			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_13				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_13					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_13					((uint8)0x00U)
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
/* P24_4 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_14					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_MODE_14						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_14					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_14					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_14					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_14			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_14				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_14					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_14					((uint8)0x00U)
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
/* P24_5 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_15					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_MODE_15						((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_15					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_15					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_15					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_15			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_15				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_15					((uint8)0x01U)
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
/* P24_6 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_16					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_MODE_16						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_16					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_16					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_16					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_16			((uint8)0x00U)
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
/* P24_10 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_17					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_MODE_17						((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_17					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_17					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_17					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_17			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_17				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_17					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_17					((uint8)0x01U)
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
/* P24_12 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_18					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_MODE_18						((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_18					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_18					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_18					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_18			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_18				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_18					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_18					((uint8)0x01U)
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
/* P24_13 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_19					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_MODE_19						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_19					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_19					((uint8)0x01U)
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
/* P2_10 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_20					((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_MODE_20						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_20					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_20					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_20					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_20			((uint8)0x01U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_20				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_20					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_20					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_20					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_20				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_20			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_20		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_20				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_20				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_20				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_20			((uint8)0x00U)
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
/* P8_0 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_21					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_MODE_21						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_21					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_21					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_21					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_21			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_21				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_21					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_21					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_21					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_21				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_21			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_21		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_21				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_21				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_21				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_21			((uint8)0x00U)
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
/* P8_2 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_22					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_MODE_22						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_22					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_22					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_22					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_22			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_22				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_22					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_22					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_22					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_22				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_22			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_22		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_22				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_22				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_22				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_22			((uint8)0x00U)
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
/* AP5_1 */
/* Pin Assign And Function */
#define	PORT_U2A_MODE_CFG_MODE_CTRL_23					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_MODE_23						((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IP_CTRL_23					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_23					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_CTRL_EXP_23					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_FUNC_CTRL_ADD_EXP_23			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_CTRL_23				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_UP_23					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_PULL_DOWN_23					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_23					((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_IN_BUF_SEL_ADV_23				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_23			((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OPEN_DRAIN_CTRL_EXP_23		((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_DRIVE_STR_CTRL_23				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_UNIV_CHAR_CTRL_23				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_OUT_VAL_INV_23				((uint8)0x00U)
#define	PORT_U2A_MODE_CFG_BI_DIRECTION_CTRL_23			((uint8)0x00U)
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

#define	PORT_MODE_CFG_P2_11_0				((Port_PinModeType)0U)
#define	PORT_MODE_CFG_P2_12_1				((Port_PinModeType)1U)
#define	PORT_MODE_CFG_P2_13_2				((Port_PinModeType)2U)
#define	PORT_MODE_CFG_P2_14_3				((Port_PinModeType)3U)
#define	PORT_MODE_CFG_P4_5_4				((Port_PinModeType)4U)
#define	PORT_MODE_CFG_P4_6_5				((Port_PinModeType)5U)
#define	PORT_MODE_CFG_P4_7_6				((Port_PinModeType)6U)
#define	PORT_MODE_CFG_P4_10_7				((Port_PinModeType)7U)
#define	PORT_MODE_CFG_P6_6_8				((Port_PinModeType)8U)
#define	PORT_MODE_CFG_P20_1_9				((Port_PinModeType)9U)
#define	PORT_MODE_CFG_P20_2_10				((Port_PinModeType)10U)
#define	PORT_MODE_CFG_P21_0_11				((Port_PinModeType)11U)
#define	PORT_MODE_CFG_P21_1_12				((Port_PinModeType)12U)
#define	PORT_MODE_CFG_P21_2_13				((Port_PinModeType)13U)
#define	PORT_MODE_CFG_P24_4_14				((Port_PinModeType)14U)
#define	PORT_MODE_CFG_P24_5_15				((Port_PinModeType)15U)
#define	PORT_MODE_CFG_P24_6_16				((Port_PinModeType)16U)
#define	PORT_MODE_CFG_P24_10_17				((Port_PinModeType)17U)
#define	PORT_MODE_CFG_P24_12_18				((Port_PinModeType)18U)
#define	PORT_MODE_CFG_P24_13_19				((Port_PinModeType)19U)
#define	PORT_MODE_CFG_P2_10_20				((Port_PinModeType)20U)
#define	PORT_MODE_CFG_P8_0_21				((Port_PinModeType)21U)
#define	PORT_MODE_CFG_P8_2_22				((Port_PinModeType)22U)
#define	PORT_MODE_CFG_AP5_1_23				((Port_PinModeType)23U)

#define PORT_MODE_MAX						((Port_PinModeType)24U)

#endif /* PORT_MODE_CFG_H */
/*-- End Of File -------------------------------------------------------------------------------*/
