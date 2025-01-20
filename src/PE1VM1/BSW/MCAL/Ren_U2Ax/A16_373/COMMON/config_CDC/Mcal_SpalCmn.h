/* Common-r04-31700-0000-a-v01 */
/************************************************************************************************/
/*																								*/
/*		MCAL SPAL Common Header																	*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#ifndef	MCAL_SPALCMN_H
#define	MCAL_SPALCMN_H

/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/
#include	"Mcal_CmnCfg.h"

/*==============================================================================================*/
/* defines																						*/
/*==============================================================================================*/
/* Compile switch for target microcontroller */
#define	MCAL_TARGET_RH850U2A		(1U)
#define	MCAL_TARGET_RH850U2B		(2U)
#define	MCAL_TARGET_RCARS4_G4MH		(3U)
#define	MCAL_TARGET_RCARS4_CR52		(4U)
#define	MCAL_TARGET_RCARV4H_CR52	(5U)
#define	MCAL_SPAL_TARGET			(MCAL_TARGET_RH850U2A)

/* pacakge target	*/
#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
#define	MCAL_PKG_U2B24_468PIN		(1u)
#define	MCAL_PKG_U2B24_373PIN		(2u)
#define	MCAL_PKG_U2B20_468PIN		(3u)
#define	MCAL_PKG_U2B20_373PIN		(4u)
#define	MCAL_PKG_U2B10_468PIN		(5u)
#define	MCAL_PKG_U2B10_373PIN		(6u)
#define	MCAL_PKG_U2B10_292PIN		(7u)
#define	MCAL_PKG_U2B6_292PIN		(8u)
#define	MCAL_PKG_TARGET				(MCAL_PKG_U2B6_292PIN)
#endif

/* BIT Value */
#define	BIT0						(0x00000001U)
#define	BIT1						(0x00000002U)
#define	BIT2						(0x00000004U)
#define	BIT3						(0x00000008U)
#define	BIT4						(0x00000010U)
#define	BIT5						(0x00000020U)
#define	BIT6						(0x00000040U)
#define	BIT7						(0x00000080U)
#define	BIT8						(0x00000100U)
#define	BIT9						(0x00000200U)
#define	BIT10						(0x00000400U)
#define	BIT11						(0x00000800U)
#define	BIT12						(0x00001000U)
#define	BIT13						(0x00002000U)
#define	BIT14						(0x00004000U)
#define	BIT15						(0x00008000U)
#define	BIT16						(0x00010000U)
#define	BIT17						(0x00020000U)
#define	BIT18						(0x00040000U)
#define	BIT19						(0x00080000U)
#define	BIT20						(0x00100000U)
#define	BIT21						(0x00200000U)
#define	BIT22						(0x00400000U)
#define	BIT23						(0x00800000U)
#define	BIT24						(0x01000000U)
#define	BIT25						(0x02000000U)
#define	BIT26						(0x04000000U)
#define	BIT27						(0x08000000U)
#define	BIT28						(0x10000000U)
#define	BIT29						(0x20000000U)
#define	BIT30						(0x40000000U)
#define	BIT31						(0x80000000U)

#endif	/* MCAL_SPALCMN_H */
/*-- End Of File -------------------------------------------------------------------------------*/
