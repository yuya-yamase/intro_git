/* Port-r04-303 */
/************************************************************************************************/
/*																								*/
/*		PORT Driver																				*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/
#ifndef PORT_H
#define PORT_H

/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/
#include "Std_Types.h"
#include "Mcal_SpalCmn.h"
#include "McalCommon_lib.h"

#include "Port_Cfg.h"
#include "Port_Type.h"
#include "Port_ModeCfg.h"

/*==============================================================================================*/
/* defines / data types / structs / unions / macros												*/
/*==============================================================================================*/

#if MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A
#if MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_516PIN
#define PORT_ALL_NOT_CONFIG_P0	((uint16)0x1FFFU)	/* Don't set all P0 pins */
#define PORT_ALL_NOT_CONFIG_P1	((uint16)0xFFFFU)	/* Do not set all pins in P1 */
#define PORT_ALL_NOT_CONFIG_P2	((uint16)0xFFFFU)	/* Don't set all pins on P2 */
#define PORT_ALL_NOT_CONFIG_P3	((uint16)0xFFFFU)	/* Do not set all pins on P3 */
#define PORT_ALL_NOT_CONFIG_P4	((uint16)0xFFFFU)	/* Do not set all P4 pins */
#define PORT_ALL_NOT_CONFIG_P5	((uint16)0x005CU)	/* Do not set all P5 pins */
#define PORT_ALL_NOT_CONFIG_P6	((uint16)0xFFFDU)	/* Do not set all P6 pins */
#define PORT_ALL_NOT_CONFIG_P8	((uint16)0x07FFU)	/* Do not set all P8 pins */
#define PORT_ALL_NOT_CONFIG_P9	((uint16)0x01FFU)	/* Do not set all P9 pins */
#define PORT_ALL_NOT_CONFIG_P10	((uint16)0x7FFFU)	/* Do not set all pins on P10 */
#define PORT_ALL_NOT_CONFIG_P11	((uint16)0xFFFFU)	/* Do not set all pins on P11 */
#define PORT_ALL_NOT_CONFIG_P12	((uint16)0x003FU)	/* Do not set all pins on P12 */
#define PORT_ALL_NOT_CONFIG_P17	((uint16)0x007FU)	/* Do not set all pins on P17 */
#define PORT_ALL_NOT_CONFIG_P18	((uint16)0xFFFFU)	/* Do not set all pins on P18 */
#define PORT_ALL_NOT_CONFIG_P19	((uint16)0x003FU)	/* Do not set all pins on P19 */
#define PORT_ALL_NOT_CONFIG_P20	((uint16)0xF7FFU)	/* Do not set all pins on P20 */
#define PORT_ALL_NOT_CONFIG_P21	((uint16)0x30FFU)	/* Do not set all pins on P21 */
#define PORT_ALL_NOT_CONFIG_P22	((uint16)0x001FU)	/* Do not set all pins on P22 */
#define PORT_ALL_NOT_CONFIG_P23	((uint16)0x3FFFU)	/* Do not set all pins on P23 */
#define PORT_ALL_NOT_CONFIG_P24	((uint16)0x3FF0U)	/* Do not set all pins on P24 */
#define PORT_ALL_NOT_CONFIG_JP0	((uint16)0x002FU)	/* JP0 does not set all pins */
#define PORT_ALL_NOT_CONFIG_AP0	((uint16)0xFFFFU)	/* Do not set all pins on AP0 */
#define PORT_ALL_NOT_CONFIG_AP1	((uint16)0x000FU)	/* Do not set all AP1 pins */
#define PORT_ALL_NOT_CONFIG_AP2	((uint16)0xFFFFU)	/* Do not set all AP2 pins */
#define PORT_ALL_NOT_CONFIG_AP3	((uint16)0x000FU)	/* Do not set all AP3 pins */
#define PORT_ALL_NOT_CONFIG_AP4	((uint16)0xFFFFU)	/* Do not set all AP4 pins */
#define PORT_ALL_NOT_CONFIG_AP5	((uint16)0x000FU)	/* Do not set all AP5 pins */
#elif MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_373PIN
#define PORT_ALL_NOT_CONFIG_P0	((uint16)0x1FFFU)	/* Don't set all P0 pins */
#define PORT_ALL_NOT_CONFIG_P1	((uint16)0xFFFFU)	/* Do not set all pins in P1 */
#define PORT_ALL_NOT_CONFIG_P2	((uint16)0xFFFFU)	/* Don't set all pins on P2 */
#define PORT_ALL_NOT_CONFIG_P3	((uint16)0x01FFU)	/* Do not set all pins on P3 */
#define PORT_ALL_NOT_CONFIG_P4	((uint16)0xFFF3U)	/* Do not set all P4 pins */
#define PORT_ALL_NOT_CONFIG_P5	((uint16)0x005CU)	/* Do not set all P5 pins */
#define PORT_ALL_NOT_CONFIG_P6	((uint16)0xFFFDU)	/* Do not set all P6 pins */
#define PORT_ALL_NOT_CONFIG_P8	((uint16)0x03FFU)	/* Do not set all P8 pins */
#define PORT_ALL_NOT_CONFIG_P9	((uint16)0x0000U)	/* Do not set all P9 pins */
#define PORT_ALL_NOT_CONFIG_P10	((uint16)0x7FFFU)	/* Do not set all pins on P10 */
#define PORT_ALL_NOT_CONFIG_P11	((uint16)0xFFFFU)	/* Do not set all pins on P11 */
#define PORT_ALL_NOT_CONFIG_P12	((uint16)0x0000U)	/* Do not set all pins on P12 */
#define PORT_ALL_NOT_CONFIG_P17	((uint16)0x007FU)	/* Do not set all pins on P17 */
#define PORT_ALL_NOT_CONFIG_P18	((uint16)0x0000U)	/* Do not set all pins on P18 */
#define PORT_ALL_NOT_CONFIG_P19	((uint16)0x0000U)	/* Do not set all pins on P19 */
#define PORT_ALL_NOT_CONFIG_P20	((uint16)0x77FFU)	/* Do not set all pins on P20 */
#define PORT_ALL_NOT_CONFIG_P21	((uint16)0x00FFU)	/* Do not set all pins on P21 */
#define PORT_ALL_NOT_CONFIG_P22	((uint16)0x001FU)	/* Do not set all pins on P22 */
#define PORT_ALL_NOT_CONFIG_P23	((uint16)0x0000U)	/* Do not set all pins on P23 */
#define PORT_ALL_NOT_CONFIG_P24	((uint16)0x3FF0U)	/* Do not set all pins on P24 */
#define PORT_ALL_NOT_CONFIG_JP0	((uint16)0x002FU)	/* JP0 does not set all pins */
#define PORT_ALL_NOT_CONFIG_AP0	((uint16)0xFFFFU)	/* Do not set all pins on AP0 */
#define PORT_ALL_NOT_CONFIG_AP1	((uint16)0x000FU)	/* Do not set all AP1 pins */
#define PORT_ALL_NOT_CONFIG_AP2	((uint16)0xFFFFU)	/* Do not set all AP2 pins */
#define PORT_ALL_NOT_CONFIG_AP3	((uint16)0x000FU)	/* Do not set all AP3 pins */
#define PORT_ALL_NOT_CONFIG_AP4	((uint16)0xFFFFU)	/* Do not set all AP4 pins */
#define PORT_ALL_NOT_CONFIG_AP5	((uint16)0x000FU)	/* Do not set all AP5 pins */
#elif ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A6_292PIN ) || ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A8_292PIN )
#define PORT_ALL_NOT_CONFIG_P0	((uint16)0x0000U)	/* Don't set all P0 pins */
#define PORT_ALL_NOT_CONFIG_P1	((uint16)0x0000U)	/* Do not set all pins in P1 */
#define PORT_ALL_NOT_CONFIG_P2	((uint16)0xFFFFU)	/* Don't set all pins on P2 */
#define PORT_ALL_NOT_CONFIG_P3	((uint16)0x01FCU)	/* Do not set all pins on P3 */
#define PORT_ALL_NOT_CONFIG_P4	((uint16)0xFFF3U)	/* Do not set all P4 pins */
#define PORT_ALL_NOT_CONFIG_P5	((uint16)0x005CU)	/* Do not set all P5 pins */
#define PORT_ALL_NOT_CONFIG_P6	((uint16)0xFFFDU)	/* Do not set all P6 pins */
#define PORT_ALL_NOT_CONFIG_P8	((uint16)0x0000U)	/* Do not set all P8 pins */
#define PORT_ALL_NOT_CONFIG_P9	((uint16)0x0000U)	/* Do not set all P9 pins */
#define PORT_ALL_NOT_CONFIG_P10	((uint16)0x7FFFU)	/* Do not set all pins on P10 */
#define PORT_ALL_NOT_CONFIG_P11	((uint16)0x0000U)	/* Do not set all pins on P11 */
#define PORT_ALL_NOT_CONFIG_P12	((uint16)0x0000U)	/* Do not set all pins on P12 */
#define PORT_ALL_NOT_CONFIG_P17	((uint16)0x007FU)	/* Do not set all pins on P17 */
#define PORT_ALL_NOT_CONFIG_P18	((uint16)0x0000U)	/* Do not set all pins on P18 */
#define PORT_ALL_NOT_CONFIG_P19	((uint16)0x0000U)	/* Do not set all pins on P19 */
#define PORT_ALL_NOT_CONFIG_P20	((uint16)0x77FFU)	/* Do not set all pins on P20 */
#define PORT_ALL_NOT_CONFIG_P21	((uint16)0x00FFU)	/* Do not set all pins on P21 */
#define PORT_ALL_NOT_CONFIG_P22	((uint16)0x001FU)	/* Do not set all pins on P22 */
#define PORT_ALL_NOT_CONFIG_P23	((uint16)0x0000U)	/* Do not set all pins on P23 */
#define PORT_ALL_NOT_CONFIG_P24	((uint16)0x3FF0U)	/* Do not set all pins on P24 */
#define PORT_ALL_NOT_CONFIG_JP0	((uint16)0x002FU)	/* JP0 does not set all pins */
#define PORT_ALL_NOT_CONFIG_AP0	((uint16)0xFFFFU)	/* Do not set all pins on AP0 */
#define PORT_ALL_NOT_CONFIG_AP1	((uint16)0x000FU)	/* Do not set all AP1 pins */
#define PORT_ALL_NOT_CONFIG_AP2	((uint16)0xFFFFU)	/* Do not set all AP2 pins */
#define PORT_ALL_NOT_CONFIG_AP3	((uint16)0x000FU)	/* Do not set all AP3 pins */
#define PORT_ALL_NOT_CONFIG_AP4	((uint16)0x001FU)	/* Do not set all AP4 pins */
#define PORT_ALL_NOT_CONFIG_AP5	((uint16)0x0000U)	/* Do not set all AP5 pins */
#endif
#elif MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B
#define PORT_ALL_NOT_CONFIG_JP0	((uint16)0x002FU)	/* JP0 does not set all pins */
#define PORT_ALL_NOT_CONFIG_P00	((uint16)0x00FFU)	/* Do not set all pins on P00 */
#define PORT_ALL_NOT_CONFIG_P02	((uint16)0x07FFU)	/* Do not set all pins on P02 */
#define PORT_ALL_NOT_CONFIG_P10	((uint16)0x01FFU)	/* Do not set all pins on P10 */
#define PORT_ALL_NOT_CONFIG_P11	((uint16)0x07FFU)	/* Do not set all pins on P11 */
#define PORT_ALL_NOT_CONFIG_P12	((uint16)0x03FFU)	/* Do not set all pins on P12 */
#define PORT_ALL_NOT_CONFIG_P13	((uint16)0x000FU)	/* Do not set all pins on P13 */
#define PORT_ALL_NOT_CONFIG_P14	((uint16)0x003FU)	/* Do not set all pins on P14 */
#define PORT_ALL_NOT_CONFIG_P20	((uint16)0x00FFU)	/* Do not set all pins on P20 */
#define PORT_ALL_NOT_CONFIG_P21	((uint16)0x003CU)	/* Do not set all pins on P21 */
#define PORT_ALL_NOT_CONFIG_P22	((uint16)0x3FFFU)	/* Do not set all pins on P22 */
#define PORT_ALL_NOT_CONFIG_P23	((uint16)0x00FFU)	/* Do not set all pins on P23 */
#define PORT_ALL_NOT_CONFIG_P25	((uint16)0x007CU)	/* Do not set all pins on P25 */
#define PORT_ALL_NOT_CONFIG_P27	((uint16)0x0001U)	/* Do not set all pins on P27 */
#define PORT_ALL_NOT_CONFIG_P32	((uint16)0x007FU)	/* Do not set all pins on P32 */
#define PORT_ALL_NOT_CONFIG_P33	((uint16)0x01FFU)	/* Do not set all pins on P33 */
#define PORT_ALL_NOT_CONFIG_P34	((uint16)0x001FU)	/* Do not set all pins on P34 */
#define PORT_ALL_NOT_CONFIG_P37	((uint16)0xFFFFU)	/* Do not set all pins on P37 */
#define PORT_ALL_NOT_CONFIG_P38	((uint16)0xFFFFU)	/* Do not set all pins on P38 */
#define PORT_ALL_NOT_CONFIG_P40	((uint16)0xFFFFU)	/* Do not set all pins on P40 */
#define PORT_ALL_NOT_CONFIG_P41	((uint16)0xFFFFU)	/* Do not set all pins on P41 */
#define PORT_ALL_NOT_CONFIG_P42	((uint16)0xFFFFU)	/* Do not set all pins on P42 */
#define PORT_ALL_NOT_CONFIG_P43	((uint16)0xFFFFU)	/* Do not set all pins on P43 */
#define PORT_ALL_NOT_CONFIG_P44	((uint16)0xFFFFU)	/* Do not set all pins on P44 */
#define PORT_ALL_NOT_CONFIG_P45	((uint16)0xFFFFU)	/* Do not set all pins on P45 */
#define PORT_ALL_NOT_CONFIG_P46	((uint16)0xFFFFU)	/* Do not set all pins on P46 */
#define PORT_ALL_NOT_CONFIG_P47	((uint16)0xFFFFU)	/* Do not set all pins on P47 */
#define PORT_ALL_NOT_CONFIG_P48	((uint16)0xFFFFU)	/* Do not set all pins on P48 */
#define PORT_ALL_NOT_CONFIG_P49	((uint16)0xFFFFU)	/* Do not set all pins on P49 */
#define PORT_ALL_NOT_CONFIG_P50	((uint16)0xFFFFU)	/* Do not set all pins on P50 */
#define PORT_ALL_NOT_CONFIG_P51	((uint16)0xFFFFU)	/* Do not set all pins on P51 */
#define PORT_ALL_NOT_CONFIG_P52	((uint16)0xFFFFU)	/* Do not set all pins on P52 */
#endif

#if MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A
#if MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_516PIN
#define PORT_SUPPORT_POS_MASK_P0		((uint16)0x1FFFU)	/* P0 supported pins */
#define PORT_SUPPORT_POS_MASK_P1		((uint16)0xFFFFU)	/* P1 supported pins */
#define PORT_SUPPORT_POS_MASK_P2		((uint16)0xFFFFU)	/* P2 supported pins */
#define PORT_SUPPORT_POS_MASK_P3		((uint16)0xFFFFU)	/* P3 supported pins */
#define PORT_SUPPORT_POS_MASK_P4		((uint16)0xFFFFU)	/* P4 supported pins */
#define PORT_SUPPORT_POS_MASK_P5		((uint16)0x005CU)	/* P5 supported pins */
#define PORT_SUPPORT_POS_MASK_P6		((uint16)0xFFFDU)	/* P6 supported pins */
#define PORT_SUPPORT_POS_MASK_P8		((uint16)0x07FFU)	/* P8 supported pins */
#define PORT_SUPPORT_POS_MASK_P9		((uint16)0x01FFU)	/* P9 supported pins */
#define PORT_SUPPORT_POS_MASK_P10		((uint16)0x7FFFU)	/* P10 supported pins */
#define PORT_SUPPORT_POS_MASK_P11		((uint16)0xFFFFU)	/* P11 supported pins */
#define PORT_SUPPORT_POS_MASK_P12		((uint16)0x003FU)	/* P12 supported pins */
#define PORT_SUPPORT_POS_MASK_P17		((uint16)0x007FU)	/* P17 supported pins */
#define PORT_SUPPORT_POS_MASK_P18		((uint16)0xFFFFU)	/* P18 supported pins */
#define PORT_SUPPORT_POS_MASK_P19		((uint16)0x003FU)	/* P19 supported pins */
#define PORT_SUPPORT_POS_MASK_P20		((uint16)0xF7FFU)	/* P20 supported pins */
#define PORT_SUPPORT_POS_MASK_P21		((uint16)0x30FFU)	/* P21 supported pins */
#define PORT_SUPPORT_POS_MASK_P22		((uint16)0x001FU)	/* P22 supported pins */
#define PORT_SUPPORT_POS_MASK_P23		((uint16)0x3FFFU)	/* P23 supported pins */
#define PORT_SUPPORT_POS_MASK_P24		((uint16)0x3FF0U)	/* P24 supported pins */
#define PORT_SUPPORT_POS_MASK_JP0		((uint16)0x002FU)	/* JP0 is a supported pin */
#define PORT_SUPPORT_POS_MASK_AP0		((uint16)0xFFFFU)	/* AP0 supported pins */
#define PORT_SUPPORT_POS_MASK_AP1		((uint16)0x000FU)	/* AP1 supported pins */
#define PORT_SUPPORT_POS_MASK_AP2		((uint16)0xFFFFU)	/* AP2 supported pins */
#define PORT_SUPPORT_POS_MASK_AP3		((uint16)0x000FU)	/* AP3 supported pins */
#define PORT_SUPPORT_POS_MASK_AP4		((uint16)0xFFFFU)	/* AP4 supported pins */
#define PORT_SUPPORT_POS_MASK_AP5		((uint16)0x000FU)	/* AP5 supported pins */
#elif MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_373PIN
#define PORT_SUPPORT_POS_MASK_P0		((uint16)0x1FFFU)	/* P0 supported pins */
#define PORT_SUPPORT_POS_MASK_P1		((uint16)0x0000U)	/* P1 supported pins */
#define PORT_SUPPORT_POS_MASK_P2		((uint16)0xFFFFU)	/* P2 supported pins */
#define PORT_SUPPORT_POS_MASK_P3		((uint16)0x01FFU)	/* P3 supported pins */
#define PORT_SUPPORT_POS_MASK_P4		((uint16)0xFFF3U)	/* P4 supported pins */
#define PORT_SUPPORT_POS_MASK_P5		((uint16)0x005CU)	/* P5 supported pins */
#define PORT_SUPPORT_POS_MASK_P6		((uint16)0xFFFDU)	/* P6 supported pins */
#define PORT_SUPPORT_POS_MASK_P8		((uint16)0x03FFU)	/* P8 supported pins */
#define PORT_SUPPORT_POS_MASK_P9		((uint16)0x0000U)	/* P9 supported pins */
#define PORT_SUPPORT_POS_MASK_P10		((uint16)0x7FFFU)	/* P10 supported pins */
#define PORT_SUPPORT_POS_MASK_P11		((uint16)0xFFFFU)	/* P11 supported pins */
#define PORT_SUPPORT_POS_MASK_P12		((uint16)0x0000U)	/* P12 supported pins */
#define PORT_SUPPORT_POS_MASK_P17		((uint16)0x007FU)	/* P17 supported pins */
#define PORT_SUPPORT_POS_MASK_P18		((uint16)0x0000U)	/* P18 supported pins */
#define PORT_SUPPORT_POS_MASK_P19		((uint16)0x0000U)	/* P19 supported pins */
#define PORT_SUPPORT_POS_MASK_P20		((uint16)0x77FFU)	/* P20 supported pins */
#define PORT_SUPPORT_POS_MASK_P21		((uint16)0x00FFU)	/* P21 supported pins */
#define PORT_SUPPORT_POS_MASK_P22		((uint16)0x001FU)	/* P22 supported pins */
#define PORT_SUPPORT_POS_MASK_P23		((uint16)0x0000U)	/* P23 supported pins */
#define PORT_SUPPORT_POS_MASK_P24		((uint16)0x3FF0U)	/* P24 supported pins */
#define PORT_SUPPORT_POS_MASK_JP0		((uint16)0x002FU)	/* JP0 is a supported pin */
#define PORT_SUPPORT_POS_MASK_AP0		((uint16)0xFFFFU)	/* AP0 supported pins */
#define PORT_SUPPORT_POS_MASK_AP1		((uint16)0x000FU)	/* AP1 supported pins */
#define PORT_SUPPORT_POS_MASK_AP2		((uint16)0xFFFFU)	/* AP2 supported pins */
#define PORT_SUPPORT_POS_MASK_AP3		((uint16)0x000FU)	/* AP3 supported pins */
#define PORT_SUPPORT_POS_MASK_AP4		((uint16)0xFFFFU)	/* AP4 supported pins */
#define PORT_SUPPORT_POS_MASK_AP5		((uint16)0x000FU)	/* AP5 supported pins */
#elif ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A6_292PIN ) || ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A8_292PIN )
#define PORT_SUPPORT_POS_MASK_P0		((uint16)0x0000U)	/* P0 supported pins */
#define PORT_SUPPORT_POS_MASK_P1		((uint16)0x0000U)	/* P1 supported pins */
#define PORT_SUPPORT_POS_MASK_P2		((uint16)0xFFFFU)	/* P2 supported pins */
#define PORT_SUPPORT_POS_MASK_P3		((uint16)0x01FCU)	/* P3 supported pins */
#define PORT_SUPPORT_POS_MASK_P4		((uint16)0xFFF3U)	/* P4 supported pins */
#define PORT_SUPPORT_POS_MASK_P5		((uint16)0x005CU)	/* P5 supported pins */
#define PORT_SUPPORT_POS_MASK_P6		((uint16)0xFFFDU)	/* P6 supported pins */
#define PORT_SUPPORT_POS_MASK_P8		((uint16)0x0000U)	/* P8 supported pins */
#define PORT_SUPPORT_POS_MASK_P9		((uint16)0x0000U)	/* P9 supported pins */
#define PORT_SUPPORT_POS_MASK_P10		((uint16)0x7FFFU)	/* P10 supported pins */
#define PORT_SUPPORT_POS_MASK_P11		((uint16)0x0000U)	/* P11 supported pins */
#define PORT_SUPPORT_POS_MASK_P12		((uint16)0x0000U)	/* P12 supported pins */
#define PORT_SUPPORT_POS_MASK_P17		((uint16)0x007FU)	/* P17 supported pins */
#define PORT_SUPPORT_POS_MASK_P18		((uint16)0x0000U)	/* P18 supported pins */
#define PORT_SUPPORT_POS_MASK_P19		((uint16)0x0000U)	/* P19 supported pins */
#define PORT_SUPPORT_POS_MASK_P20		((uint16)0x77FFU)	/* P20 supported pins */
#define PORT_SUPPORT_POS_MASK_P21		((uint16)0x00FFU)	/* P21 supported pins */
#define PORT_SUPPORT_POS_MASK_P22		((uint16)0x001FU)	/* P22 supported pins */
#define PORT_SUPPORT_POS_MASK_P23		((uint16)0x0000U)	/* P23 supported pins */
#define PORT_SUPPORT_POS_MASK_P24		((uint16)0x3FF0U)	/* P24 supported pins */
#define PORT_SUPPORT_POS_MASK_JP0		((uint16)0x002FU)	/* JP0 is a supported pin */
#define PORT_SUPPORT_POS_MASK_AP0		((uint16)0xFFFFU)	/* AP0 supported pins */
#define PORT_SUPPORT_POS_MASK_AP1		((uint16)0x000FU)	/* AP1 supported pins */
#define PORT_SUPPORT_POS_MASK_AP2		((uint16)0xFFFFU)	/* AP2 supported pins */
#define PORT_SUPPORT_POS_MASK_AP3		((uint16)0x000FU)	/* AP3 supported pins */
#define PORT_SUPPORT_POS_MASK_AP4		((uint16)0x001FU)	/* AP4 supported pins */
#define PORT_SUPPORT_POS_MASK_AP5		((uint16)0x0000U)	/* AP5 supported pins */
#endif
#elif MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B
#define PORT_SUPPORT_POS_MASK_JP0		((uint16)0x002FU)	/* JP0 supported pins */
#define PORT_SUPPORT_POS_MASK_P00		((uint16)0x00FFU)	/* P00 supported pins */
#define PORT_SUPPORT_POS_MASK_P02		((uint16)0x07FFU)	/* P02 supported pins */
#define PORT_SUPPORT_POS_MASK_P10		((uint16)0x01FFU)	/* P10 supported pins */
#define PORT_SUPPORT_POS_MASK_P11		((uint16)0x07FFU)	/* P11 supported pins */
#define PORT_SUPPORT_POS_MASK_P12		((uint16)0x03FFU)	/* P12 supported pins */
#define PORT_SUPPORT_POS_MASK_P13		((uint16)0x000FU)	/* P13 supported pins */
#define PORT_SUPPORT_POS_MASK_P14		((uint16)0x003FU)	/* P14 supported pins */
#define PORT_SUPPORT_POS_MASK_P20		((uint16)0x00FFU)	/* P20 supported pins */
#define PORT_SUPPORT_POS_MASK_P21		((uint16)0x003CU)	/* P21 supported pins */
#define PORT_SUPPORT_POS_MASK_P22		((uint16)0x3FFFU)	/* P22 supported pins */
#define PORT_SUPPORT_POS_MASK_P23		((uint16)0x00FFU)	/* P23 supported pins */
#define PORT_SUPPORT_POS_MASK_P25		((uint16)0x007CU)	/* P25 supported pins */
#define PORT_SUPPORT_POS_MASK_P27		((uint16)0x0001U)	/* P27 supported pins */
#define PORT_SUPPORT_POS_MASK_P32		((uint16)0x007FU)	/* P32 supported pins */
#define PORT_SUPPORT_POS_MASK_P33		((uint16)0x01FFU)	/* P33 supported pins */
#define PORT_SUPPORT_POS_MASK_P34		((uint16)0x001FU)	/* P34 supported pins */
#define PORT_SUPPORT_POS_MASK_P37		((uint16)0xFFFFU)	/* P37 supported pins */
#define PORT_SUPPORT_POS_MASK_P38		((uint16)0xFFFFU)	/* P38 supported pins */
#define PORT_SUPPORT_POS_MASK_P40		((uint16)0xFFFFU)	/* P40 supported pins */
#define PORT_SUPPORT_POS_MASK_P41		((uint16)0xFFFFU)	/* P41 supported pins */
#define PORT_SUPPORT_POS_MASK_P42		((uint16)0xFFFFU)	/* P42 supported pins */
#define PORT_SUPPORT_POS_MASK_P43		((uint16)0xFFFFU)	/* P43 supported pins */
#define PORT_SUPPORT_POS_MASK_P44		((uint16)0xFFFFU)	/* P44 supported pins */
#define PORT_SUPPORT_POS_MASK_P45		((uint16)0xFFFFU)	/* P45 supported pins */
#define PORT_SUPPORT_POS_MASK_P46		((uint16)0xFFFFU)	/* P46 supported pins */
#define PORT_SUPPORT_POS_MASK_P47		((uint16)0xFFFFU)	/* P47 supported pins */
#define PORT_SUPPORT_POS_MASK_P48		((uint16)0xFFFFU)	/* P48 supported pins */
#define PORT_SUPPORT_POS_MASK_P49		((uint16)0xFFFFU)	/* P49 supported pins */
#define PORT_SUPPORT_POS_MASK_P50		((uint16)0xFFFFU)	/* P50 supported pins */
#define PORT_SUPPORT_POS_MASK_P51		((uint16)0xFFFFU)	/* P51 supported pins */
#define PORT_SUPPORT_POS_MASK_P52		((uint16)0xFFFFU)	/* P52 supported pins */

#endif /* MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A */

#if MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P0	((uint16)0x01FFU)	/* Do not set SafeState on all pins in P0 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P1	((uint16)0xFFFFU)	/* Do not set SafeState on all pins of P1 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P2	((uint16)0xFFFFU)	/* Do not set SafeState on all pins of P2 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P3	((uint16)0xFFFFU)	/* Do not set SafeState on all pins of P3 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P4	((uint16)0xFFFFU)	/* Do not set SafeState on all pins of P4 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P5	((uint16)0x005CU)	/* Do not set SafeState on all pins of P5 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P6	((uint16)0xFFFDU)	/* Do not set SafeState on all pins of P6 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P8	((uint16)0x07FFU)	/* Do not set SafeState on all pins of P8 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P9	((uint16)0x01FFU)	/* Do not set SafeState on all pins of P9 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P10	((uint16)0x7FFFU)	/* Do not set SafeState on all pins on P10 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P11	((uint16)0xFFFFU)	/* Do not set SafeState on all pins on P11 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P12	((uint16)0x003FU)	/* Do not set SafeState on all pins on P12 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P17	((uint16)0x007FU)	/* Do not set SafeState on all pins on P17 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P18	((uint16)0xFFFFU)	/* Do not set SafeState on all pins on P18 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P19	((uint16)0x003FU)	/* Do not set SafeState on all pins on P19 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P20	((uint16)0xF7FFU)	/* Do not set SafeState on all pins on P20 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P21	((uint16)0x30FFU)	/* Do not set SafeState on all pins on P21 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P22	((uint16)0x001FU)	/* Do not set SafeState on all pins on P22 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P23	((uint16)0x3FFFU)	/* Do not set SafeState on all pins on P23 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P24	((uint16)0x3FF0U)	/* Do not set SafeState on all pins on P24 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_JP0	((uint16)0x0000U)	/* JP0 is judged by a fixed value of 0x0000 because there is no SafeState setting */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_AP0	((uint16)0xFFFFU)	/* Do not set SafeState on all pins in AP0 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_AP1	((uint16)0x000FU)	/* Do not set SafeState on all AP1 pins */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_AP2	((uint16)0xFFFFU)	/* Do not set SafeState on all AP2 pins */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_AP3	((uint16)0x000FU)	/* Do not set SafeState on all AP3 pins */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_AP4	((uint16)0xFFFFU)	/* Do not set SafeState on all AP4 pins */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_AP5	((uint16)0x000FU)	/* Do not set SafeState on all AP5 pins */
#elif MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B
#define PORT_SAFESTATE_ALL_NOT_CONFIG_JP0	((uint16)0x0000U)	/* JP0 is judged by a fixed value of 0x0000 because there is no SafeState setting */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P00	((uint16)0x00FFU)	/* Do not set SafeState on all pins of P00 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P02	((uint16)0x07FFU)	/* Do not set SafeState on all pins of P02 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P10	((uint16)0x01FFU)	/* Do not set SafeState on all pins on P10 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P11	((uint16)0x07FFU)	/* Do not set SafeState on all pins on P11 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P12	((uint16)0x03FFU)	/* Do not set SafeState on all pins on P12 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P13	((uint16)0x000FU)	/* Do not set SafeState on all pins on P13 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P14	((uint16)0x003FU)	/* Do not set SafeState on all pins on P14 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P20	((uint16)0x00FFU)	/* Do not set SafeState on all pins on P20 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P21	((uint16)0x003CU)	/* Do not set SafeState on all pins on P21 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P22	((uint16)0x3FFFU)	/* Do not set SafeState on all pins on P22 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P23	((uint16)0x00FFU)	/* Do not set SafeState on all pins on P23 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P25	((uint16)0x007CU)	/* Do not set SafeState on all pins on P25 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P27	((uint16)0x0001U)	/* Do not set SafeState on all pins on P27 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P32	((uint16)0x007FU)	/* Do not set SafeState on all pins on P32 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P33	((uint16)0x01FFU)	/* Do not set SafeState on all pins on P33 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P34	((uint16)0x001FU)	/* Do not set SafeState on all pins on P34 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P37	((uint16)0xFFFFU)	/* Do not set SafeState on all pins on P37 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P38	((uint16)0xFFFFU)	/* Do not set SafeState on all pins on P38 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P40	((uint16)0xFFFFU)	/* Do not set SafeState on all pins on P40 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P41	((uint16)0xFFFFU)	/* Do not set SafeState on all pins on P41 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P42	((uint16)0xFFFFU)	/* Do not set SafeState on all pins on P42 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P43	((uint16)0xFFFFU)	/* Do not set SafeState on all pins on P43 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P44	((uint16)0xFFFFU)	/* Do not set SafeState on all pins on P44 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P45	((uint16)0xFFFFU)	/* Do not set SafeState on all pins on P45 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P46	((uint16)0xFFFFU)	/* Do not set SafeState on all pins on P46 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P47	((uint16)0xFFFFU)	/* Do not set SafeState on all pins on P47 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P48	((uint16)0xFFFFU)	/* Do not set SafeState on all pins on P48 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P49	((uint16)0xFFFFU)	/* Do not set SafeState on all pins on P49 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P50	((uint16)0xFFFFU)	/* Do not set SafeState on all pins on P50 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P51	((uint16)0xFFFFU)	/* Do not set SafeState on all pins on P51 */
#define PORT_SAFESTATE_ALL_NOT_CONFIG_P52	((uint16)0xFFFFU)	/* Do not set SafeState on all pins on P52 */
#endif

/* Can register supported on port group */
#define PORT_SUPPORT_REGISTER				((uint32)1U)
#define PORT_NOT_SUPPORT_REGISTER			((uint32)0U)

/* Flag-manage bit-position support for each register */
#define PORT_REGISTER_POS_P				((uint32)0x00000001U)	/* Supports P-registers */
#define PORT_REGISTER_POS_PM			((uint32)0x00000002U)	/* Supports PM registers */
#define PORT_REGISTER_POS_PMC			((uint32)0x00000004U)	/* Supports PMC registers */
#define PORT_REGISTER_POS_PFC			((uint32)0x00000008U)	/* Supports PFC registers */
#define PORT_REGISTER_POS_PFCE			((uint32)0x00000010U)	/* Supports PFCE registers */
#define PORT_REGISTER_POS_PFCAE			((uint32)0x00000020U)	/* Supports PFCAE registers */
#if MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B
#define PORT_REGISTER_POS_PFCEAE		((uint32)0x00000040U)	/* Supports PFCEAE registers */
#endif
#define PORT_REGISTER_POS_PINV			((uint32)0x00000080U)	/* Supports PINV registers */
#define PORT_REGISTER_POS_PIBC			((uint32)0x00000100U)	/* Supports the PIBC register */
#define PORT_REGISTER_POS_PBDC			((uint32)0x00000200U)	/* Supports PBDC registers */
#define PORT_REGISTER_POS_PIPC			((uint32)0x00000400U)	/* Supports PIPC registers */
#define PORT_REGISTER_POS_PU			((uint32)0x00000800U)	/* Supports PU registers */
#define PORT_REGISTER_POS_PD			((uint32)0x00001000U)	/* Supports PD register */
#define PORT_REGISTER_POS_PODC			((uint32)0x00002000U)	/* Supports PODC registers */
#define PORT_REGISTER_POS_PODCE			((uint32)0x00004000U)	/* Supports PODCE registers */
#define PORT_REGISTER_POS_PDSC			((uint32)0x00008000U)	/* Supports PDSC registers */
#define PORT_REGISTER_POS_PUCC			((uint32)0x00010000U)	/* Supports PUCC register */
#define PORT_REGISTER_POS_PIS			((uint32)0x00020000U)	/* Supports PIS registers */
#define PORT_REGISTER_POS_PISA			((uint32)0x00040000U)	/* Supports PISA registers */
#if MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B
#define PORT_REGISTER_POS_PEIODC		((uint32)0x00080000U)	/* Supports PEIODC register */
#endif
#define PORT_REGISTER_POS_PSFC			((uint32)0x00100000U)	/* Supports PSFC registers */
#define PORT_REGISTER_POS_PSFTS			((uint32)0x00200000U)	/* Supports PSFTS registers */
#define PORT_REGISTER_POS_PSFTSE		((uint32)0x00400000U)	/* Supports PSFTSE registers */
#if MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B
#define PORT_REGISTER_POS_PSFTSAE		((uint32)0x00800000U)	/* Supports PSFTSAE registers */
#endif

#if MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A
/* Registers supported by P0 */
#define PORT_SUPPORT_REGISTERS_P0		( (uint32)( PORT_REGISTER_POS_P    | PORT_REGISTER_POS_PM    | PORT_REGISTER_POS_PMC | \
													PORT_REGISTER_POS_PFC  | PORT_REGISTER_POS_PFCE  | PORT_REGISTER_POS_PFCAE | \
													PORT_REGISTER_POS_PINV | PORT_REGISTER_POS_PIBC  | PORT_REGISTER_POS_PBDC | \
													PORT_REGISTER_POS_PIPC | PORT_REGISTER_POS_PU    | PORT_REGISTER_POS_PD | \
													PORT_REGISTER_POS_PODC | PORT_REGISTER_POS_PODCE | PORT_REGISTER_POS_PDSC | \
													PORT_REGISTER_POS_PUCC | PORT_REGISTER_POS_PIS   | PORT_REGISTER_POS_PISA | \
													PORT_REGISTER_POS_PSFC | PORT_REGISTER_POS_PSFTS | PORT_REGISTER_POS_PSFTSE ) )

/* Registers supported by P1 (same as P0) */
#define PORT_SUPPORT_REGISTERS_P1		PORT_SUPPORT_REGISTERS_P0

/* Registers supported by P2 (same as P0) */
#define PORT_SUPPORT_REGISTERS_P2		PORT_SUPPORT_REGISTERS_P0

/* Registers supported by P3 (same as P0) */
#define PORT_SUPPORT_REGISTERS_P3		PORT_SUPPORT_REGISTERS_P0

/* Registers supported by P4 (same as P0) */
#define PORT_SUPPORT_REGISTERS_P4		PORT_SUPPORT_REGISTERS_P0

/* Registers supported by P2 (same as P0) */
#define PORT_SUPPORT_REGISTERS_P5		PORT_SUPPORT_REGISTERS_P0

/* Registers supported by P6 (same as P0) */
#define PORT_SUPPORT_REGISTERS_P6		PORT_SUPPORT_REGISTERS_P0

/* Registers supported by P8 */
#define PORT_SUPPORT_REGISTERS_P8		( (uint32)( PORT_REGISTER_POS_P    | PORT_REGISTER_POS_PM    | PORT_REGISTER_POS_PMC | \
													PORT_REGISTER_POS_PFC  | PORT_REGISTER_POS_PFCE  | PORT_REGISTER_POS_PFCAE | \
													PORT_REGISTER_POS_PINV | PORT_REGISTER_POS_PIBC  | PORT_REGISTER_POS_PBDC | \
													/* P8 not PIPC supported */    PORT_REGISTER_POS_PU    | PORT_REGISTER_POS_PD | \
													PORT_REGISTER_POS_PODC | PORT_REGISTER_POS_PODCE | PORT_REGISTER_POS_PDSC | \
													PORT_REGISTER_POS_PUCC | PORT_REGISTER_POS_PIS   | PORT_REGISTER_POS_PISA | \
													PORT_REGISTER_POS_PSFC | PORT_REGISTER_POS_PSFTS | PORT_REGISTER_POS_PSFTSE ) )

/* Registers supported by P9 (same as P0) */
#define PORT_SUPPORT_REGISTERS_P9		PORT_SUPPORT_REGISTERS_P0

/* Registers supported by P10 (same as P0) */
#define PORT_SUPPORT_REGISTERS_P10		PORT_SUPPORT_REGISTERS_P0

/* Registers supported by P11 (same as P0) */
#define PORT_SUPPORT_REGISTERS_P11		PORT_SUPPORT_REGISTERS_P0

/* Registers supported by P12 (same as P0) */
#define PORT_SUPPORT_REGISTERS_P12		PORT_SUPPORT_REGISTERS_P0

/* Registers supported by P17 */
#define PORT_SUPPORT_REGISTERS_P17		( (uint32)( PORT_REGISTER_POS_P    | PORT_REGISTER_POS_PM    | PORT_REGISTER_POS_PMC | \
													PORT_REGISTER_POS_PFC  | PORT_REGISTER_POS_PFCE  | PORT_REGISTER_POS_PFCAE | \
													PORT_REGISTER_POS_PINV | PORT_REGISTER_POS_PIBC  | PORT_REGISTER_POS_PBDC | \
													PORT_REGISTER_POS_PIPC | PORT_REGISTER_POS_PU    | PORT_REGISTER_POS_PD | \
													PORT_REGISTER_POS_PODC | PORT_REGISTER_POS_PODCE | PORT_REGISTER_POS_PDSC | \
													PORT_REGISTER_POS_PUCC | PORT_REGISTER_POS_PIS   | /* P17 not supported by PISA */ \
													PORT_REGISTER_POS_PSFC | PORT_REGISTER_POS_PSFTS | PORT_REGISTER_POS_PSFTSE ) )

/* Registers supported by P18 (same as P0) */
#define PORT_SUPPORT_REGISTERS_P18		PORT_SUPPORT_REGISTERS_P0

/* Registers supported by P19 (same as P0) */
#define PORT_SUPPORT_REGISTERS_P19		PORT_SUPPORT_REGISTERS_P0

/* Registers supported by P20 (same as P0) */
#define PORT_SUPPORT_REGISTERS_P20		PORT_SUPPORT_REGISTERS_P0

/* Registers supported by P21 (same as P0) */
#define PORT_SUPPORT_REGISTERS_P21		PORT_SUPPORT_REGISTERS_P0

/* Registers supported by P22 (same as P0) */
#define PORT_SUPPORT_REGISTERS_P22		PORT_SUPPORT_REGISTERS_P0

/* Registers supported by P23 (same as P0) */
#define PORT_SUPPORT_REGISTERS_P23		PORT_SUPPORT_REGISTERS_P0

/* Registers supported by P24 (same as P 17) */
#define PORT_SUPPORT_REGISTERS_P24		PORT_SUPPORT_REGISTERS_P17

/* Registers supported by JP0 */
#define PORT_SUPPORT_REGISTERS_JP0		( (uint32)( PORT_REGISTER_POS_P    | PORT_REGISTER_POS_PM    | PORT_REGISTER_POS_PMC | \
													PORT_REGISTER_POS_PFC  | PORT_REGISTER_POS_PFCE  | /* JP0 does not support PFCAE */ \
													PORT_REGISTER_POS_PINV | PORT_REGISTER_POS_PIBC  | PORT_REGISTER_POS_PBDC | \
													/* JP0 does not support PIPC */   PORT_REGISTER_POS_PU    | PORT_REGISTER_POS_PD | \
													PORT_REGISTER_POS_PODC | PORT_REGISTER_POS_PODCE | PORT_REGISTER_POS_PDSC | \
													PORT_REGISTER_POS_PUCC | PORT_REGISTER_POS_PIS   | PORT_REGISTER_POS_PISA \
													/* JP0 does not support PSFC */ /* JP0 does not support PSFTS */ /* JP0 does not support PSFTSE */ ) )

/* Registers supported by AP0 */
#define PORT_SUPPORT_REGISTERS_AP0		( (uint32)( PORT_REGISTER_POS_P    | PORT_REGISTER_POS_PM    | /*AP0 does not support PMC */ \
													/* AP0 does not support PFC */ /* AP0 does not support PFCE */ /* AP0 does not support PFCAE */ \
													PORT_REGISTER_POS_PINV | PORT_REGISTER_POS_PIBC  | PORT_REGISTER_POS_PBDC | \
													/* AP0 does not support PIPC */ /* AP0 does not support PU */ /* AP0 does not support PD */ \
													PORT_REGISTER_POS_PODC | PORT_REGISTER_POS_PODCE | PORT_REGISTER_POS_PDSC | \
													/*AP0 not PUCC supported */ /*AP0 not PIS supported */ /*AP0 not PISA supported */ /*AP0 not PISA supported */ \
													PORT_REGISTER_POS_PSFC | PORT_REGISTER_POS_PSFTS | PORT_REGISTER_POS_PSFTSE ) )

/* Registers supported by AP1 (same as AP0) */
#define PORT_SUPPORT_REGISTERS_AP1		PORT_SUPPORT_REGISTERS_AP0

/* Registers supported by AP2 (same as AP0) */
#define PORT_SUPPORT_REGISTERS_AP2		PORT_SUPPORT_REGISTERS_AP0

/* Registers supported by AP3 (same as AP0) */
#define PORT_SUPPORT_REGISTERS_AP3		PORT_SUPPORT_REGISTERS_AP0

/* Registers supported by AP4 (same as AP0) */
#define PORT_SUPPORT_REGISTERS_AP4		PORT_SUPPORT_REGISTERS_AP0

/* Registers supported by AP5 (same as AP0) */
#define PORT_SUPPORT_REGISTERS_AP5		PORT_SUPPORT_REGISTERS_AP0

#elif MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B
/* Registers supported by P00 */
#define PORT_SUPPORT_REGISTERS_P00		( (uint32)( PORT_REGISTER_POS_P    | PORT_REGISTER_POS_PM    | PORT_REGISTER_POS_PMC | \
													PORT_REGISTER_POS_PFC  | PORT_REGISTER_POS_PFCE  | PORT_REGISTER_POS_PFCAE | \
													PORT_REGISTER_POS_PFCEAE | \
													PORT_REGISTER_POS_PINV | PORT_REGISTER_POS_PIBC  | PORT_REGISTER_POS_PBDC | \
													PORT_REGISTER_POS_PIPC | PORT_REGISTER_POS_PU    | PORT_REGISTER_POS_PD | \
													PORT_REGISTER_POS_PODC | PORT_REGISTER_POS_PODCE | PORT_REGISTER_POS_PDSC | \
													PORT_REGISTER_POS_PUCC | PORT_REGISTER_POS_PIS   | PORT_REGISTER_POS_PISA | \
													PORT_REGISTER_POS_PEIODC | \
													PORT_REGISTER_POS_PSFC | PORT_REGISTER_POS_PSFTS | PORT_REGISTER_POS_PSFTSE | \
													PORT_REGISTER_POS_PSFTSAE ) )

/* Registers supported by P02 (same as P00) */
#define PORT_SUPPORT_REGISTERS_P02		PORT_SUPPORT_REGISTERS_P00

/* Registers supported by P10 */
#define PORT_SUPPORT_REGISTERS_P10		( (uint32)( PORT_REGISTER_POS_P    | PORT_REGISTER_POS_PM    | PORT_REGISTER_POS_PMC | \
													PORT_REGISTER_POS_PFC  | PORT_REGISTER_POS_PFCE  | PORT_REGISTER_POS_PFCAE | \
													PORT_REGISTER_POS_PFCEAE | \
													PORT_REGISTER_POS_PINV | PORT_REGISTER_POS_PIBC  | PORT_REGISTER_POS_PBDC | \
													PORT_REGISTER_POS_PIPC | PORT_REGISTER_POS_PU    | PORT_REGISTER_POS_PD | \
													PORT_REGISTER_POS_PODC | PORT_REGISTER_POS_PODCE | PORT_REGISTER_POS_PDSC | \
													PORT_REGISTER_POS_PUCC | PORT_REGISTER_POS_PIS   | PORT_REGISTER_POS_PISA | \
													/* P10 not supported by PEIODC */ \
													PORT_REGISTER_POS_PSFC | PORT_REGISTER_POS_PSFTS | PORT_REGISTER_POS_PSFTSE | \
													PORT_REGISTER_POS_PSFTSAE ) )

/* Registers supported by P11 (same as P00) */
#define PORT_SUPPORT_REGISTERS_P11		PORT_SUPPORT_REGISTERS_P00

/* Registers supported by P12 (same as P 10) */
#define PORT_SUPPORT_REGISTERS_P12		PORT_SUPPORT_REGISTERS_P10

/* Registers supported by P13 (same as P 10) */
#define PORT_SUPPORT_REGISTERS_P13		PORT_SUPPORT_REGISTERS_P10

/* Registers supported by P14 (same as P 10) */
#define PORT_SUPPORT_REGISTERS_P14		PORT_SUPPORT_REGISTERS_P10

/* Registers supported by P20 (same as P 10) */
#define PORT_SUPPORT_REGISTERS_P20		PORT_SUPPORT_REGISTERS_P10

/* Registers supported by P21 (same as P00) */
#define PORT_SUPPORT_REGISTERS_P21		PORT_SUPPORT_REGISTERS_P00

/* Registers supported by P22 (same as P00) */
#define PORT_SUPPORT_REGISTERS_P22		PORT_SUPPORT_REGISTERS_P00

/* Registers supported by P23 (same as P00) */
#define PORT_SUPPORT_REGISTERS_P23		PORT_SUPPORT_REGISTERS_P00

/* Registers supported by P25 (same as P 10) */
#define PORT_SUPPORT_REGISTERS_P25		PORT_SUPPORT_REGISTERS_P10

/* Registers supported by P27 */
#define PORT_SUPPORT_REGISTERS_P27		( (uint32)( PORT_REGISTER_POS_P    | PORT_REGISTER_POS_PM    | /* P27 doesn't support PMC */ \
													/* P27 does not support PFC */ /* P27 does not support PFCE */ /* P27 does not support PFCAE */ \
													/* P27 not supported by PFCEAE */ \
													PORT_REGISTER_POS_PINV | PORT_REGISTER_POS_PIBC  | PORT_REGISTER_POS_PBDC | \
													/* P27 does not support PIPC */PORT_REGISTER_POS_PU    | PORT_REGISTER_POS_PD | \
													PORT_REGISTER_POS_PODC | PORT_REGISTER_POS_PODCE | PORT_REGISTER_POS_PDSC | \
													PORT_REGISTER_POS_PUCC | PORT_REGISTER_POS_PIS   | PORT_REGISTER_POS_PISA | \
													/* P27 not supported by PEIODC */ \
													PORT_REGISTER_POS_PSFC | PORT_REGISTER_POS_PSFTS | PORT_REGISTER_POS_PSFTSE | \
													PORT_REGISTER_POS_PSFTSAE ) )

/* Registers supported by P32 (same as P00) */
#define PORT_SUPPORT_REGISTERS_P32		PORT_SUPPORT_REGISTERS_P00

/* Registers supported by P33 (same as P00) */
#define PORT_SUPPORT_REGISTERS_P33		PORT_SUPPORT_REGISTERS_P00

/* Registers supported by P34 (same as P00) */
#define PORT_SUPPORT_REGISTERS_P34		PORT_SUPPORT_REGISTERS_P10

/* Registers supported by P37 */
#define PORT_SUPPORT_REGISTERS_P37		( (uint32)( PORT_REGISTER_POS_P    | PORT_REGISTER_POS_PM    | PORT_REGISTER_POS_PMC | \
													PORT_REGISTER_POS_PFC  | PORT_REGISTER_POS_PFCE  | PORT_REGISTER_POS_PFCAE | \
													PORT_REGISTER_POS_PFCEAE | \
													PORT_REGISTER_POS_PINV | PORT_REGISTER_POS_PIBC  | PORT_REGISTER_POS_PBDC \
													/* P37 not PIPC supported */ /* P37 not PU supported */    /* P37 does not support PD */ \
													/* P37 does not support PODC */ /* P37 does not support PODCE */ /* P37 does not support PDSC */ \
													/* P37 not PUCC supported */ /* P37 not PIS supported */   /* P37 not supported by PISA */ \
													/* P37 not supported by PEIODC */ \
													/* P37 does not support PSFC */ /* P37 does not support PSFTS */ /* P37 does not support PSFTSE */ \
													/* P37 does not support PSFTSAE */ ) )

/* Registers supported by P38 (same as P 37) */
#define PORT_SUPPORT_REGISTERS_P38		PORT_SUPPORT_REGISTERS_P37

/* Registers supported by P40 */
#define PORT_SUPPORT_REGISTERS_P40		( (uint32)( /* P40 not supported */       /* PM not supported on P40 */     PORT_REGISTER_POS_PMC | \
													/* P40 not PFC supported */     /* P40 does not support PFCE */   PORT_REGISTER_POS_PFCAE | \
													/* P40 not supported by PFCEAE */ \
													/* P40 not supported by PINV */   PORT_REGISTER_POS_PIBC   /* P40 not PBDC supported */ \
													/* P40 not PIPC supported */    /* P40 not PU supported */    /* P40 does not support PD */ \
													/* P40 does not support PODC */    /* P40 does not support PODCE *//* P40 does not support PDSC */ \
													/* P40 not PUCC supported */    /* P40 not PIS supported */   /* P40 not supported by PISA */ \
													/* P40 not supported by PEIODC */ \
													/* P40 does not support PSFC */    /* P40 does not support PSFTTS */ /* P40 does not support PSFTSE */ \
													/* P40 does not support PSFTSAE */ ) )

/* Registers supported by P41 */
#define PORT_SUPPORT_REGISTERS_P41		( (uint32)( PORT_REGISTER_POS_P    | PORT_REGISTER_POS_PM    |   /* P41 does not support PMC */ \
													/* P41 not PFC-supported */ /* P41 not PFCE-supported */   /* P41 does not support PFCAE */ \
													/* P41 not supported by PFCEAE */ \
													PORT_REGISTER_POS_PINV | PORT_REGISTER_POS_PIBC  | PORT_REGISTER_POS_PBDC \
													/* P41 not PIPC supported */ /* P41 not PU supported */    /* P41 does not support PD */ \
													/* P41 does not support PODC */ /* P41 does not support PODCE *//* P41 does not support PDSC */ \
													/* P41 not PUCC supported */ /* P41 not PIS supported */   /* P41 not supported by PISA */ \
													/* P41 not supported by PEIODC */ \
													/* P41 does not support PSFC */ /* P41 does not support PSFTS */ /* P41 does not support PSFTSE */ \
													/* P41 does not support PSFTSAE */ ) )

/* Registers supported by P42 (same as P 41) */
#define PORT_SUPPORT_REGISTERS_P42		PORT_SUPPORT_REGISTERS_P41

/* Registers supported by P43 (same as P 41) */
#define PORT_SUPPORT_REGISTERS_P43		PORT_SUPPORT_REGISTERS_P41

/* Registers supported by P44 (same as P 41) */
#define PORT_SUPPORT_REGISTERS_P44		PORT_SUPPORT_REGISTERS_P41

/* Registers supported by P45 (same as P 37) */
#define PORT_SUPPORT_REGISTERS_P45		PORT_SUPPORT_REGISTERS_P37

/* Registers supported by P46 (same as P 37) */
#define PORT_SUPPORT_REGISTERS_P46		PORT_SUPPORT_REGISTERS_P37

/* Registers supported by P47 (same as P 37) */
#define PORT_SUPPORT_REGISTERS_P47		PORT_SUPPORT_REGISTERS_P37

/* Registers supported by P48 (same as P 37) */
#define PORT_SUPPORT_REGISTERS_P48		PORT_SUPPORT_REGISTERS_P37

/* Registers supported by P49 (same as P 37) */
#define PORT_SUPPORT_REGISTERS_P49		PORT_SUPPORT_REGISTERS_P37

/* Registers supported by P50 (same as P 37) */
#define PORT_SUPPORT_REGISTERS_P50		PORT_SUPPORT_REGISTERS_P37

/* Registers supported by P51 (same as P 37) */
#define PORT_SUPPORT_REGISTERS_P51		PORT_SUPPORT_REGISTERS_P37

/* Registers supported by P52 (same as P 37) */
#define PORT_SUPPORT_REGISTERS_P52		PORT_SUPPORT_REGISTERS_P37

/* Registers supported by JP0 */
#define PORT_SUPPORT_REGISTERS_JP0		( (uint32)( PORT_REGISTER_POS_P    | PORT_REGISTER_POS_PM    | PORT_REGISTER_POS_PMC | \
													/* JP0 does not support PFC */   /* JP0 does not support PFCE */    /* JP0 does not support PFCAE */ \
													/* JP0 does not support PFCEAE */ \
													PORT_REGISTER_POS_PINV | PORT_REGISTER_POS_PIBC  | PORT_REGISTER_POS_PBDC | \
													PORT_REGISTER_POS_PIPC | PORT_REGISTER_POS_PU    | PORT_REGISTER_POS_PD | \
													PORT_REGISTER_POS_PODC | PORT_REGISTER_POS_PODCE | PORT_REGISTER_POS_PDSC | \
													PORT_REGISTER_POS_PUCC | PORT_REGISTER_POS_PIS   | PORT_REGISTER_POS_PISA \
													/* JP0 does not support PEIODC */ \
													/* JP0 does not support PSFC */   /* JP0 does not support PSFTS */  /* JP0 does not support PSFTSE */ \
													/* JP0 does not support PSFTSAE */ ) )
#endif

#if MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B
/* PULVSEL address */
#define PORT_PULVSEL5_CHANGEABLE			((uint16)0x0000U)		/* Arguments for macro */
#define PORT_PULVSEL5_ALL_UNCONFIG			((uint16)0x000FU)		/* All bits "Do not set" judgment */
#endif

/* PCR bit position */
#define PORT_PCR_PINV_BIT					((uint8)30U)
#define PORT_PCR_PODC_BIT					((uint8)28U)
#define PORT_PCR_PODCE_BIT					((uint8)27U)
#define PORT_PCR_PUCC_BIT					((uint8)25U)
#define PORT_PCR_PDSC_BIT					((uint8)24U)
#define PORT_PCR_PISA_BIT					((uint8)22U)
#define PORT_PCR_PIS_BIT					((uint8)20U)
#define PORT_PCR_PU_BIT						((uint8)19U)
#define PORT_PCR_PD_BIT						((uint8)18U)
#define PORT_PCR_PBDC_BIT					((uint8)17U)
#define PORT_PCR_PIBC_BIT					((uint8)16U)
#if MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B
#define PORT_PCR_PEIODC_BIT					((uint8)15U)
#endif
#define PORT_PCR_P_BIT						((uint8)12U)
#define PORT_PCR_PMC_BIT					((uint8)6U)
#define PORT_PCR_PIPC_BIT					((uint8)5U)
#define PORT_PCR_PM_BIT						((uint8)4U)
#if MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B
#define PORT_PCR_PFCEAE_BIT					((uint8)3U)
#endif
#define PORT_PCR_PFCAE_BIT					((uint8)2U)
#define PORT_PCR_PFCE_BIT					((uint8)1U)
#define PORT_PCR_PFC_BIT					((uint8)0U)

#define PORT_PCR_BIT_OFF					((uint32)0U)
#define PORT_PCR_BIT_ON						((uint32)1U)

/* Mask to check Pin Mode */
#define PORT_PCR_INPUT_MODE					( ( PORT_PCR_BIT_ON  << PORT_PCR_PM_BIT  ) )
#define PORT_PCR_PMC_MASK					( ( PORT_PCR_BIT_ON  << PORT_PCR_PMC_BIT ) )
#define PORT_PCR_GPIO_MODE					( ( PORT_PCR_BIT_OFF << PORT_PCR_PMC_BIT ) )
#define PORT_PCR_ALT_MODE					( ( PORT_PCR_BIT_ON  << PORT_PCR_PMC_BIT ) )

#define PORT_PCR_PM_PMC_MASK				( ( PORT_PCR_BIT_ON  << PORT_PCR_PM_BIT ) | ( PORT_PCR_BIT_ON  << PORT_PCR_PMC_BIT ) )
#define PORT_PCR_GPIO_OUT_MODE				( ( PORT_PCR_BIT_OFF << PORT_PCR_PM_BIT ) | ( PORT_PCR_BIT_OFF << PORT_PCR_PMC_BIT ) )
#define PORT_PCR_ALT_IN_MODE				( ( PORT_PCR_BIT_ON  << PORT_PCR_PM_BIT ) | ( PORT_PCR_BIT_ON  << PORT_PCR_PMC_BIT ) )


/* Mask to check a register bit value */
#define PORT_PCR_INCHRA_MASK				( ( PORT_PCR_BIT_ON << PORT_PCR_PU_BIT   ) | ( PORT_PCR_BIT_ON << PORT_PCR_PD_BIT    ) | ( PORT_PCR_BIT_ON << PORT_PCR_PIS_BIT  ) | ( PORT_PCR_BIT_ON << PORT_PCR_PISA_BIT ) )
#define PORT_PCR_OUTCHRA_MASK				( ( PORT_PCR_BIT_ON << PORT_PCR_PODC_BIT ) | ( PORT_PCR_BIT_ON << PORT_PCR_PODCE_BIT ) | ( PORT_PCR_BIT_ON << PORT_PCR_PDSC_BIT ) | ( PORT_PCR_BIT_ON << PORT_PCR_PUCC_BIT ) )
#define PORT_APCR_OUTCHRA_MASK				( ( PORT_PCR_BIT_ON << PORT_PCR_PODC_BIT ) | ( PORT_PCR_BIT_ON << PORT_PCR_PODCE_BIT ) | ( PORT_PCR_BIT_ON << PORT_PCR_PDSC_BIT ) )
#define PORT_PCR_INOUTCHRA_MASK				( ( PORT_PCR_INCHRA_MASK | PORT_PCR_OUTCHRA_MASK ) )
#define PORT_PCR_P_MASK						( ( PORT_PCR_BIT_ON << PORT_PCR_P_BIT    ) )
#define PORT_PCR_PM_MASK					( ( PORT_PCR_BIT_ON << PORT_PCR_PM_BIT   ) )
#define PORT_PCR_PINV_MASK					( ( PORT_PCR_BIT_ON << PORT_PCR_PINV_BIT ) )
#define PORT_PCR_PIPC_MASK					( ( PORT_PCR_BIT_ON << PORT_PCR_PIPC_BIT ) )
#define PORT_PCR_PIBC_MASK					( ( PORT_PCR_BIT_ON << PORT_PCR_PIBC_BIT ) )
#define PORT_PCR_PM_PIBC_BIT				( ( PORT_PCR_BIT_ON << PORT_PCR_PIBC_BIT ) | ( PORT_PCR_BIT_ON << PORT_PCR_PM_BIT ) )

/* Mask to calculate a Alternative Mode register value */
#if MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A
#define PORT_PCR_ALTREG_MASK				( PORT_PCR_BIT_ON | ( PORT_PCR_BIT_ON << PORT_PCR_PFCE_BIT ) | ( PORT_PCR_BIT_ON << PORT_PCR_PFCAE_BIT ) )	/* PFC  on PCR is bit0 so shift is unnecessary */
#else
#define PORT_PCR_ALTREG_MASK				( PORT_PCR_BIT_ON | ( PORT_PCR_BIT_ON << PORT_PCR_PFCE_BIT ) | ( PORT_PCR_BIT_ON << PORT_PCR_PFCAE_BIT ) | ( PORT_PCR_BIT_ON << PORT_PCR_PFCEAE_BIT ) )	/* PFC  on PCR is bit0 so shift is unnecessary */
#endif

/* Mask to calculate Alternative Mode registers value of Jtag Port */
#if MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A
#define PORT_JPCR_ALTREG_MASK				( PORT_PCR_BIT_ON | ( PORT_PCR_BIT_ON << PORT_PCR_PFCE_BIT ))	/* JPFC  on PCR is bit0 so shift is unnecessary */
#endif

/* Mode Control */
#define PORT_ALL_PIN_GPIO_MODE				((uint16)0x0000U)

/* I/O mode is selected by the peripheral function*/
#define PORT_ALL_PIN_UNCONFIG				((uint16)0xFFFFU)
#define PORT_ALL_PIN_DIRECT_IO_MODE			((uint16)0xFFFFU)

/* Input Buffer Disable/Enable */
#define PORT_INPUT_BUF_PORT_DISABLE			((uint16)0x0000U)		/* Disable Input Buffer */
#define PORT_INPUT_BUF_PIN_DISABLE			((uint8)0U)				/* Disable Input Buffer */
#define PORT_INPUT_BUF_PIN_ENABLE			((uint8)1U)				/* Enable Input Buffer */

/* Noise Filter */
#define PORT_NOISE_FILTER_REG_NO_ADDR 		((uint32)0x00000000U)	/* Value to check address of register for noise filter setting */
#define PORT_NOISE_FILTER_INVALID_MASK		((uint16)0xFFFFU)		/* Invalid mask value */
#define PORT_DIGITAL_NOISE_FILTER_WAIT_MAX	((uint32)39U)			/* Wait Max Time for Digital Noise Filter is Enable(us) */
#define PORT_ANALOG_NOISE_FILTER_WAIT_MAX	((uint32)1U)			/* Wait Max Time for Analog Noise Filter is Enable(us) */

#define PORT_DNFACTL_NFSTS_BIT				((uint8)5U)
#define PORT_DNFACTL_NFSTS_KIND_NUM 		((uint8)4U)
#define PORT_DNFACTL_PRS_KIND_NUM 			((uint8)8U)
#define PORT_DNFACTL_NFSTS_BITMASK 			((uint8)0x60)			/* NFSTS[6:5] Bit Mask */
#define PORT_DNFACTL_PRS_BITMASK 			((uint8)0x07)			/* PRS[2:0] Bit Mask */

#define	PORT_NOISE_FILTER_SAMPLING_CLOCK_80	((uint8)80U)
#define	PORT_NOISE_FILTER_SAMPLING_CLOCK_40	((uint8)40U)
#define	PORT_NOISE_FILTER_SAMPLING_CLOCK_10	((uint8)10U)

#define PORT_CLK_TYPE_CLK_LSB 				PORT_NOISE_FILTER_SAMPLING_CLOCK_40
#define PORT_CLK_TYPE_CLKA_TAUJ 			PORT_NOISE_FILTER_SAMPLING_CLOCK_80
#define PORT_CLK_TYPE_CLKA_ADC 				PORT_NOISE_FILTER_SAMPLING_CLOCK_40
#define PORT_CLK_TYPE_CLKA_LPS 				PORT_NOISE_FILTER_SAMPLING_CLOCK_10

#if MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A
#define PORT_CLK_TYPE_CLK_HSB 				PORT_NOISE_FILTER_SAMPLING_CLOCK_80
#define PORT_CLK_TYPE_CLK_ADC 				PORT_NOISE_FILTER_SAMPLING_CLOCK_40
#elif MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B
#define PORT_CLK_TYPE_CLKC_HSB				PORT_NOISE_FILTER_SAMPLING_CLOCK_80
#endif

#define PORT_NOISEFILTERKIND_DIGITAL		((uint8)0U)
#define PORT_NOISEFILTERKIND_ANALOG			((uint8)1U)
#define PORT_NOISEFILTERKIND_BOTH			((uint8)2U)

#define PORT_FCLACTL_RESET_VALUE			((uint8)0U)
#define PORT_DNFACTL_RESET_VALUE			((uint8)0U)

/* LVDS */
#define PORT_LVDS_INVALID					((uint32)0x00000000U)	/* LVDS disabled */
#define PORT_LVDS_INVALID_DIRECTION			((uint16)0xFFFFU)		/* Invalid input/output direction in LVDS */

#define PORT_LVDS_TARGET_PORT		((uint8)1U)		/* PORT Covered by LVDS */
#define PORT_LVDS_NOT_TARGET_PORT	((uint8)0U)		/* PORT not covered by LVDS */

#define PORT_LVDSCTRL_LVDSCTRL_NOT_MASK		((uint32)0x00000000U)		/* Not mask */
#define PORT_LVDSCTRL_LVDSCTRL0_MASK		((uint32)0x00000001U)		/* 0-bit mask */
#define PORT_LVDSCTRL_LVDSCTRL1_MASK		((uint32)0x00000002U)		/* 1-bit mask */
#define PORT_LVDSCTRL_LVDSCTRL3_MASK		((uint32)0x00000008U)		/* 3-Bit Mask */
#define PORT_LVDSCTRL_LVDSCTRL4_MASK		((uint32)0x00000010U)		/* 4-Bit Mask */
#define PORT_LVDSCTRL_LVDSCTRL5_MASK		((uint32)0x00000020U)		/* 5-bit mask */
#define PORT_LVDSCTRL_LVDSCTRL16_MASK		((uint32)0x00010000U)		/* 16-bit mask */
#define PORT_LVDSCTRL_LVDSCTRL17_MASK		((uint32)0x00020000U)		/* 17-bit mask */
#define PORT_LVDSCTRL_LVDSCTRL20_MASK		((uint32)0x00100000U)		/* 20-bit mask */
#define PORT_LVDSCTRL_LVDSCTRL0_SHIFT		((uint8)0U)					/* 0-bit shift */
#define PORT_LVDSCTRL_LVDSCTRL1_SHIFT		((uint8)1U)					/* 1-bit shift */
#define PORT_LVDSCTRL_LVDSCTRL3_SHIFT		((uint8)3U)					/* 3-bit shift */
#define PORT_LVDSCTRL_LVDSCTRL4_SHIFT		((uint8)4U)					/* 4-bit shift */
#define PORT_LVDSCTRL_LVDSCTRL5_SHIFT		((uint8)5U)					/* 5-bit shift */
#define PORT_LVDSCTRL_LVDSCTRL16_SHIFT		((uint8)16U)				/* 16 bit shift */
#define PORT_LVDSCTRL_LVDSCTRL17_SHIFT		((uint8)17U)				/* 17 bit shift */
#define PORT_LVDSCTRL_LVDSCTRL20_SHIFT		((uint8)20U)				/* 20 bit shift */
#define PORT_LVDS_INIT_VAL					((uint16)0xFFFFU)			/* Initial variable */
#define PORT_LVDS_INPUT						((uint16)0x0003U)			/* Input pin */
#define PORT_LVDS_OUTPUT					((uint16)0x0000U)			/* Output pin */
#define PORT_LVDS_PORT2						((uint8)2U)					/* PORT2 */
#define PORT_LVDS_PORT4						((uint8)4U)					/* PORT4 */
#define PORT_LVDS_PORT10					((uint8)10U)				/* PORT10 */
#define PORT_LVDS_PORT25					((uint8)25U)				/* PORT25 */

#define PORT_LVDS_PORT10_DIR_MASK_0TO1		((uint16)0x0003U)	/* Port10 0 bit and 1st bit mask */
#define PORT_LVDS_PORT10_DIR_MASK_2TO3		((uint16)0x000CU)	/* Port10 2 bit and 3 bit mask */
#define PORT_LVDS_PORT10_DIR_MASK_4TO5		((uint16)0x0030U)	/* Port10 4 and 5 bit mask */
#define PORT_LVDS_PORT25_DIR_MASK_3TO4		((uint16)0x0018U)	/* Port25 3 and 4 bit mask */
#define PORT_LVDS_PORT25_DIR_MASK_5TO6		((uint16)0x0060U)	/* Port25 5-bit and 6-bit mask */

#define PORT_LVDS_PORT10_DIR_SHIFT_0TO1		((uint8)0U)		/* Port10 0 bit shift */
#define PORT_LVDS_PORT10_DIR_SHIFT_2TO3		((uint8)2U)		/* 2 bit shift of Port10 */
#define PORT_LVDS_PORT10_DIR_SHIFT_4TO5		((uint8)4U)		/* 4 bit shift of Port10 */
#define PORT_LVDS_PORT13_DIR_SHIFT_0TO1		((uint8)0U)		/* Port1# 0-bit shift */
#define PORT_LVDS_PORT13_DIR_SHIFT_2TO3		((uint8)2U)		/* 2 bit shift of Port13 */
#define PORT_LVDS_PORT14_DIR_SHIFT_4TO5		((uint8)4U)		/* 4 bit shift of Port14 */
#define PORT_LVDS_PORT21_DIR_SHIFT_2TO3		((uint8)2U)		/* 2 bit shift of Port21 */
#define PORT_LVDS_PORT21_DIR_SHIFT_4TO5		((uint8)4U)		/* 4 bit shift of Port21 */
#define PORT_LVDS_PORT24_DIR_SHIFT_4TO5		((uint8)4U)		/* 4 bit shift of Port24 */
#define PORT_LVDS_PORT24_DIR_SHIFT_6TO7		((uint8)6U)		/* 6 bit shift of Port24 */
#define PORT_LVDS_PORT25_DIR_SHIFT_3TO4		((uint8)3U)		/* 3 bit shift of Port25 */
#define PORT_LVDS_PORT25_DIR_SHIFT_5TO6		((uint8)5U)		/* 5 bit shift of Port25 */
#define PORT_LVDS_PORT25_DIR_SHIFT_12TO13	((uint8)12U)	/* 12 bit shift of Port25 */
#define PORT_LVDS_PORT25_DIR_SHIFT_14TO15	((uint8)14U)	/* 14 bit shift of Port25 */

#define PORT_LVDS_PORT2_DIRECTION_MASK_PIN_10_TO_11		((uint16)0x0C00U)		/* Port2 10 bit and 11 bit mask */
#define PORT_LVDS_PORT2_DIRECTION_MASK_PIN_12_TO_13 	((uint16)0x3000U)		/* Port2 12 bit and 13 bit mask */
#define PORT_LVDS_PORT2_DIRECTION_MASK_PIN_14_TO_15		((uint16)0xC000U)		/* Port2 14 bit and 15 bit mask */
#define PORT_LVDS_PORT4_DIRECTION_MASK_PIN_5_TO_6		((uint16)0x0060U)		/* 5-bit and 6-bit mask for Port4 */
#define PORT_LVDS_PORT4_DIRECTION_MASK_PIN_7_TO_8		((uint16)0x0180U)		/* Port4 7- and 8-bit mask */
#define PORT_LVDS_PORT4_DIRECTION_MASK_PIN_9_TO_10		((uint16)0x0600U)		/* Port4 9 and 10 bit mask */
#define PORT_LVDS_PORT2_DIRECTION_SHIFT_PIN_10_TO_11	((uint8)10U)			/* 10 bit shift of Port2 */
#define PORT_LVDS_PORT2_DIRECTION_SHIFT_PIN_12_TO_13 	((uint8)12U)			/* 12 bit shift of Port2 */
#define PORT_LVDS_PORT2_DIRECTION_SHIFT_PIN_14_TO_15	((uint8)14U)			/* 14 bit shift of Port2 */
#define PORT_LVDS_PORT4_DIRECTION_SHIFT_PIN_5_TO_6		((uint8)5U)				/* 5-bit shift of Port4 */
#define PORT_LVDS_PORT4_DIRECTION_SHIFT_PIN_7_TO_8		((uint8)7U)				/* 7-bit shift of Port4 */
#define PORT_LVDS_PORT4_DIRECTION_SHIFT_PIN_9_TO_10		((uint8)9U)				/* Port4 9-bit shift */
#define PORT_LVDS_BIT_MASK_VOLTAGE_LVDSCTRLA			((uint32)0x00110000U)	/* bit position for voltage control of LVDSCTRLA */
#define PORT_LVDS_BIT_MASK_VOLTAGE_LVDSCTRLB			((uint32)0x00110000U)	/* bit position to control voltage of LVDSCTRLB */
#if MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B
#define PORT_LVDS_BIT_MASK_VOLTAGE_LVDSCTRLC			((uint32)0x00010000U)	/* bit position to control LVDSCTRLC voltage */
#define PORT_LVDS_BIT_MASK_VOLTAGE_LVDSCTRLD			((uint32)0x00010000U)	/* bit position to control voltage of LVDSCTRLD */
#endif

/* Safe State */
#define PORT_SAFESTATE_FUNC_PORTGROUP_DISABLE		((uint16)0x0000U)
#define PORT_SAFESTATE_FUNC_DISABLE					(0U)	/* SafeState disabled */
#define PORT_SAFESTATE_FUNC_ENABLE					(1U)	/* SafeState enabled  */

/* Pin number */
#define PORT_PIN0							((uint16)0U)		/* Pin 0 */
#define PORT_PIN1							((uint16)1U)		/* Pin 1 */
#define PORT_PIN2							((uint16)2U)		/* Pin 2 */
#define PORT_PIN3							((uint16)3U)		/* Pin 3 */
#define PORT_PIN4							((uint16)4U)		/* Pin 4 */
#define PORT_PIN5							((uint16)5U)		/* Pin 5 */
#define PORT_PIN6							((uint16)6U)		/* Pin 6 */
#define PORT_PIN7							((uint16)7U)		/* Pin 7 */
#define PORT_PIN8							((uint16)8U)		/* Pin 8 */
#define PORT_PIN9							((uint16)9U)		/* Pin 9 */
#define PORT_PIN10							((uint16)10U)		/* Pin 10 */
#define PORT_PIN11							((uint16)11U)		/* Pin 11 */
#define PORT_PIN12							((uint16)12U)		/* Pin 12 */
#define PORT_PIN13							((uint16)14U)		/* Pin 13 */
#define PORT_PIN14							((uint16)14U)		/* Pin 14 */
#define PORT_PIN15							((uint16)15U)		/* Pin 15 */

/* Changeable */
#define PORT_PIN_CHANGEABLE					((uint16)0x0001U)
#define PORT_PIN_UNCHANGEABLE				((uint16)0x0000U)

/* Setting required */
#define PORT_SETTING						(0U)

/* Flags for Port_SetiPinMode */
#define PORT_SET_MODE_FLAG_ON				((uint8)1U)		/* Flag for setting mode */
#define PORT_SET_NOISE_FILTER_FLAG_ON		((uint8)1U)		/* Flag for setting noise filter */
#define PORT_SET_SAFESTATE_FLAG_ON			((uint8)1U)		/* Flag for SafeState settings */

#define PORT_WRITE_ONE						((uint8)1U)		/* for macro functions */
#define PORT_JUDGE_ZERO						((uint8)0U)		/* for macro functions */

/* Port Group All Pin No Change */
#define PORT_NORMAL_GROUP_PIN_ALL_NO_CHANGE		((uint16)0xFFFFU)
#define PORT_JTAG_GROUP_PIN_ALL_NO_CHANGE		((uint8)0xFFU)

/* Macro */
#define PORT_REG_WRITE_UINT8(addr, val, num)	\
do { \
	if ( (uint8)( val ) > PORT_JUDGE_ZERO ) \
	{ \
		(*(volatile uint8*)( addr ) |= (uint8)( PORT_WRITE_ONE << ( num ) ) ); \
	} \
	else \
	{ \
		(*(volatile uint8*)( addr ) &= ~( (uint8)( PORT_WRITE_ONE << ( num ) ) ) ); \
	} \
} while ( 0 )		/* addr for 1-byte variable: register address num: pin number val: value to determine whether to set or drop the specified bit */

#define PORT_REG_WRITE_UINT16(addr, val, num)	\
do { \
	if ( (uint8)( val ) > PORT_JUDGE_ZERO ) \
	{ \
		(*(volatile uint16*)( addr ) |= ( (uint16)( (uint16)PORT_WRITE_ONE << ( num ) ) ) ); \
	} \
	else \
	{ \
		(*(volatile uint16*)( addr ) &= ~( (uint16)( (uint16)PORT_WRITE_ONE << ( num ) ) ) ); \
	} \
} while ( 0 )		/* addr for 2-byte variable: register address num: pin number val: value to determine whether to set or drop the specified bit */

#define PORT_REG_WRITE_ZERO_UINT16(addr, num)	\
do { \
		(*(volatile uint16*)( addr ) &= ~( (uint16)( (uint16)PORT_WRITE_ONE << ( num ) ) ) ); \
} while ( 0 ) /* addr for 2-byte variable: register address num: pin number val: value only drop the specified bit */

#define PORT_REG_WRITE_UINT32(addr, val, num)	\
do { \
	if ( (uint8)( val ) > PORT_JUDGE_ZERO ) \
	{ \
		(*(volatile uint32*)( addr ) |= ( (uint32)( (uint32)PORT_WRITE_ONE << ( num ) ) ) ); \
	} \
	else \
	{ \
		(*(volatile uint32*)( addr ) &= ~( (uint32)( (uint32)PORT_WRITE_ONE << ( num ) ) ) ); \
	} \
} while ( 0 )		/* addr for 4-byte variable: register address num: pin number val: value to determine whether to stand or drop the specified bit */

#if PORT_CFG_REG_CHK == STD_ON
#define PORT_REGCHK_OK							((uint32)0x00000000U)
#define PORT_REGCHK_NG							((uint32)0x00000001U)
#define PORT_REGCHK_REFRESH_SUCCESS				((uint32)0x00000002U)
#define PORT_REGCHK_REFRESH_IMPOSSIBLE			((uint32)0x00000004U)
#define PORT_REGCHK_REFRESH_FAILED				((uint32)0x00000008U)

#endif /* (PORT_CFG_REG_CHK == STD_ON) */

extern CONST(Port_NoiseFilterRegType, PORT_CONST) cstPort_NoiseFilterRegAddr[PORT_NOISE_FILTER_FUNC_FILTERNUMMAX];
/* Port_Configuration */
extern CONST(Port_ConfigType, PORT_CONST) cstPort_Config[];

/*==============================================================================================*/
/* functions																					*/
/*==============================================================================================*/
#define PORT_START_SEC_CODE_GLOBAL
#include "Port_MemMap.h"

/*----------------------------------------------------------------------------------------------*/
/* API Functions																				*/
/*----------------------------------------------------------------------------------------------*/
/************************************************************************************************/
/* Service name		:	Port_SetConfigPtr														*/
/* Reentrancy		:	Non Re-entrant															*/
/* Parameters(in)	:	ConfigPtr - Pointer to configuration set								*/
/* Return value		:	none																	*/
/* Limitation		:	none																	*/
/************************************************************************************************/
FUNC(void, PORT_CODE) Port_SetConfigPtr( P2CONST(Port_ConfigType, AUTOMATIC, PORT_APPL_CONST) ConfigPtr );

/************************************************************************************************/
/* Service name		:	Port_Init																*/
/* Reentrancy		:	Non Re-entrant															*/
/* Parameters(in)	:	ConfigPtr - Pointer to configuration set								*/
/* Return value		:	none																	*/
/* Limitation		:	none																	*/
/************************************************************************************************/
FUNC(void, PORT_CODE) Port_Init( P2CONST(Port_ConfigType, AUTOMATIC, PORT_APPL_CONST) ConfigPtr );

/************************************************************************************************/
/* Service name		:	Port_SetPinDirection													*/
/* Reentrancy		:	Re-entrant for different pin											*/
/* Parameters(in)	:	Pin - Port pin ID number												*/
/* Parameters(in)	:	Direction - Port pin direction											*/
/* Return value		:	none																	*/
/* Limitation		:	This function must be called after executing Port_Init().				*/
/*						Additionally, in any VM where Port_Init() has not been executed,		*/
/*						please call this function after calling Port_SetConfigPointer().		*/
/*					:	Do not call this API with a pin whose both of							*/
/*						Direction Changeable and Mode Changeable are set to 1.					*/
/************************************************************************************************/
FUNC(void, PORT_CODE) Port_SetPinDirection( CONST(Port_PinType, AUTOMATIC) Pin, CONST(Port_PinDirectionType, AUTOMATIC) Direction );

/************************************************************************************************/
/* Service name		:	Port_RefreshPortDirection												*/
/* Reentrancy		:	Non Re-entrant															*/
/* Parameters(in)	:	none																	*/
/* Return value		:	none																	*/
/* Limitation		:	This function must be called after executing Port_Init().				*/
/*						Additionally, in any VM where Port_Init() has not been executed,		*/
/*						please call this function after calling Port_SetConfigPointer().		*/
/************************************************************************************************/
FUNC(void, PORT_CODE) Port_RefreshPortDirection( void );

/********************************************************************************/
/* Function Name       : Port_SetPinMode                                        */
/* Description         : Sets the port pin mode.                                */
/* Input Parameters    : Pin: Port Pin ID number                                */
/*                     : Mode: New Port Pin mode to be set on port pin.         */
/* InOut Parameters    : None                                                   */
/* Output Parameters   : None                                                   */
/* Return parameter    : void                                                   */
/********************************************************************************/
FUNC(void, PORT_CODE) Port_SetPinMode( CONST(Port_PinType, AUTOMATIC) Pin, CONST(Port_PinModeType, AUTOMATIC) Mode );

#if (PORT_CFG_REG_CHK == STD_ON)
/************************************************************************************************/
/* Service name		:	Port_Regchk_All															*/
/* Reentrancy		:	Non Re-entrant															*/
/* Parameters(in)	:	none																	*/
/* Return value		:	Check Result															*/
/* Limitation		:	This function must be called after executing Port_Init().				*/
/*						Additionally, in any VM where Port_Init() has not been executed,		*/
/*						please call this function after calling Port_SetConfigPointer().		*/
/************************************************************************************************/
FUNC(uint32, PORT_CODE) Port_Regchk_All( void );

/************************************************************************************************/
/* Service name		:	Port_Regchk_Pin															*/
/* Reentrancy		:	Re-entrant for different pin											*/
/* Parameters(in)	:	Pin - Port pin ID number												*/
/* Return value		:	Check Result															*/
/* Limitation		:	This function must be called with a pin whose Mode Changeable and 		*/
/*						Direction Changeable are set to 0, and also not set as Unconfig.		*/
/************************************************************************************************/
FUNC(uint32, PORT_CODE) Port_Regchk_Pin( CONST(Port_PinType, AUTOMATIC) Pin );

/************************************************************************************************/
/* Service name		:	Port_Regchk_NoiseFilter													*/
/* Reentrancy		:	Non Re-entrant															*/
/* Parameters(in)	:	Func - Noise Filter function											*/
/* Return value		:	Check Result															*/
/* Limitation		:	Specify a NoiseFilter function	whose									*/
/*						setting is not changed by PortSePinMode(), and also not set as Unconfig.*/
/************************************************************************************************/
FUNC(uint32, PORT_CODE) Port_Regchk_NoiseFilter( CONST(Port_NoiseFilterFunc, AUTOMATIC) Func );

/************************************************************************************************/
/* Service name		:	Port_Regchk_PinMode														*/
/* Reentrancy		:	Non Re-entrant															*/
/* Parameters(in)	:	Pin - Port pin ID number												*/
/* Parameters(in)	:	Mode - Port Pin mode to be set on port pin.								*/
/* Return value		:	Check Result															*/
/* Limitation		:	This function must be called after executing Port_SetPinMode().			*/
/*						The argument "Mode" must be it after set by Port_SetPinMode().			*/
/************************************************************************************************/
FUNC(uint32, PORT_CODE) Port_Regchk_PinMode( CONST(Port_PinType, AUTOMATIC) Pin, CONST(Port_PinModeType, AUTOMATIC) Mode );

/************************************************************************************************/
/* Service name		:	Port_Regchk_PinDirection												*/
/* Reentrancy		:	Non Re-entrant															*/
/* Parameters(in)	:	Pin - Port pin ID number												*/
/* Parameters(in)	:	Direction - Port pin direction											*/
/* Return value		:	Check Result															*/
/* Limitation		:	This function must be called after executing Port_SetPinDirection(),	*/
/*					:	and called with a pin whose Mode Changeable is set to 0 and				*/
/*						Direction Changeable is set to 1.										*/
/************************************************************************************************/
FUNC(uint32, PORT_CODE) Port_Regchk_PinDirection( CONST(Port_PinType, AUTOMATIC) Pin, CONST(Port_PinDirectionType, AUTOMATIC) Direction );

/************************************************************************************************/
/* Service name		:	Port_Regchk_NoiseFilterMode												*/
/* Reentrancy		:	Non Re-entrant															*/
/* Parameters(in)	:	Mode - Port Pin mode to be set on port pin.								*/
/* Return value		:	Check Result															*/
/* Limitation		:	This function must be called after executing Port_SetPinMode().			*/
/*						The argument "Mode" must be it already set by Port_SetPinMode().		*/
/************************************************************************************************/
FUNC(uint32, PORT_CODE) Port_Regchk_NoiseFilterMode( CONST(Port_PinModeType, AUTOMATIC) Mode );

#if (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A)
#if (PORT_CFG_REL_IO_BUF_HOLD_STATE == STD_ON)
/************************************************************************************************/
/* Service name		:	Port_Regchk_IOHOLD														*/
/* Reentrancy		:	Non Re-entrant															*/
/* Parameters(in)	:	none																	*/
/* Return value		:	Check Result															*/
/* Limitation		:	This function must be called after executing Port_Init().				*/
/*						Additionally, in any VM where Port_Init() has not been executed,		*/
/*						please call this function after calling Port_SetConfigPointer().		*/
/************************************************************************************************/
FUNC(uint32, PORT_CODE) Port_Regchk_IOHOLD( void );
#endif /* (PORT_CFG_REL_IO_BUF_HOLD_STATE == STD_ON) */
#endif /* (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A) */

/************************************************************************************************/
/* Service name		:	Port_Regchk_ECM															*/
/* Reentrancy		:	Non Re-entrant															*/
/* Parameters(in)	:	none																	*/
/* Return value		:	Check Result															*/
/* Limitation		:	This function must be called after executing Port_Init().				*/
/*						Additionally, in any VM where Port_Init() has not been executed,		*/
/*						please call this function after calling Port_SetConfigPointer().		*/
/************************************************************************************************/
FUNC(uint32, PORT_CODE) Port_Regchk_ECM( void );

#if (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B)
/************************************************************************************************/
/* Service name		:	Port_Regchk_PULVSEL														*/
/* Reentrancy		:	Non Re-entrant															*/
/* Parameters(in)	:	none																	*/
/* Return value		:	Check Result															*/
/* Limitation		:	This function must be called after executing Port_Init().				*/
/*						Additionally, in any VM where Port_Init() has not been executed,		*/
/*						please call this function after calling Port_SetConfigPointer().		*/
/************************************************************************************************/
FUNC(uint32, PORT_CODE) Port_Regchk_PULVSEL( void );
#endif /* (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B) */

#endif /* PORT_CFG_REG_CHK == STD_ON */

#define PORT_STOP_SEC_CODE_GLOBAL
#include "Port_MemMap.h"

#endif /* PORT_H */
/*-- End Of File -------------------------------------------------------------------------------*/
