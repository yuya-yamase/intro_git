/* Reg_TAUJ-r04-31700-0000-a-v01 */
/************************************************************************************************/
/*																								*/
/*		TAUJ Register definition																*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/
#ifndef	REG_TAUJ_H
#define	REG_TAUJ_H

/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/
#include	"Std_Types.h"
#include	"Mcal_SpalCmn.h"

/*==============================================================================================*/
/*	register type definition																	*/
/*==============================================================================================*/
#define		TAUJ_CHANNEL_NUM		((uint8)(4U))

typedef	struct {
	union {
		uint8	u1Data;
		struct {
			uint8	b2TAUJnTIS		:2;
			uint8	b6Reserved		:6;
		} stBit;
	} unTAUJnCMUR;

	uint8	u1Dummy[3];
} Tauj_TAUJnCMURm_Type;		/* TAUJnCMURm register */

typedef	struct {
	union {
		uint8	u1Data;
		struct {
			uint8	xTAUJnOVF		:1;
			uint8	xReserved1		:1;
			uint8	b2Reserved2		:6;
		} stBit;
	} unTAUJnCSR;

	uint8	u1Dummy[3];
} Tauj_TAUJnCSRm_Type;		/* TAUJnCSRm register */

typedef	struct {
	union {
		uint8	u1Data;
		struct {
			uint8	xTAUJnCLOV		:1;
			uint8	b7Reserved		:7;
		} stBit;
	} unTAUJnCSC;

	uint8	u1Dummy[3];
} Tauj_TAUJnCSCm_Type;		/* TAUJnCSCm register */

typedef	struct {
	union {
		uint16	u2Data;
		struct {
			uint16	xTAUJnMD0		:1;
			uint16	b4TAUJnMD		:4;
			uint16	xReserved1		:1;
			uint16	b2TAUJnCOS		:2;
			uint16	b3TAUJnSTS		:3;
			uint16	xTAUJnMAS		:1;
			uint16	b2TAUJnCCS		:2;
			uint16	b2TAUJnCKS		:2;
		} stBit;
	} unTAUJnCMOR;

	uint8	u1Dummy[2];
} Tauj_TAUJnCMORm_Type;		/* TAUJnCMORm register */

typedef	struct {

	/* TAUJnCDRm register */
	uint32	u4TAUJnCDRm[TAUJ_CHANNEL_NUM];

	/* TAUJnCNTm register */
	uint32	u4TAUJnCNTm[TAUJ_CHANNEL_NUM];

	/* TAUJnCMURm register */
	Tauj_TAUJnCMURm_Type	stTAUJnCMURm[TAUJ_CHANNEL_NUM];

	/* TAUJnCSRm register */
	Tauj_TAUJnCSRm_Type	stTAUJnCSRm[TAUJ_CHANNEL_NUM];

	/* TAUJnCSCm register */
	Tauj_TAUJnCSCm_Type	stTAUJnCSCm[TAUJ_CHANNEL_NUM];

	/* TAUJnTE register */
	union {
		uint8	u1Data;
		struct {
			uint8	xTAUJnTE00		:1;
			uint8	xTAUJnTE01		:1;
			uint8	xTAUJnTE02		:1;
			uint8	xTAUJnTE03		:1;
			uint8	b4Reserved		:4;
		} stBit;
	} unTAUJnTE;

	uint8	u1Dummy1[3];

	/* TAUJnTS register */
	union {
		uint8	u1Data;
		struct {
			uint8	xTAUJnTS00		:1;
			uint8	xTAUJnTS01		:1;
			uint8	xTAUJnTS02		:1;
			uint8	xTAUJnTS03		:1;
			uint8	b4Reserved		:4;
		} stBit;
	} unTAUJnTS;

	uint8	u1Dummy2[3];

	/* TAUJnTT Register */
	union {
		uint8	u1Data;
		struct {
			uint8	xTAUJnTT00		:1;
			uint8	xTAUJnTT01		:1;
			uint8	xTAUJnTT02		:1;
			uint8	xTAUJnTT03		:1;
			uint8	b4Reserved		:4;
		} stBit;
	} unTAUJnTT;

	uint8	u1Dummy3[3];

	/* TAUJnTO register */
	union {
		uint8	u1Data;
		struct {
			uint8	xTAUJnTO00		:1;
			uint8	xTAUJnTO01		:1;
			uint8	xTAUJnTO02		:1;
			uint8	xTAUJnTO03		:1;
			uint8	b4Reserved		:4;
		} stBit;
	} unTAUJnTO;

	uint8	u1Dummy4[3];

	/* TAUJnTOE register */
	union {
		uint8	u1Data;
		struct {
			uint8	xTAUJnTOE00		:1;
			uint8	xTAUJnTOE01		:1;
			uint8	xTAUJnTOE02		:1;
			uint8	xTAUJnTOE03		:1;
			uint8	b4Reserved		:4;
		} stBit;
	} unTAUJnTOE;

	uint8	u1Dummy5[3];

	/* TAUJnTOL register */
	union {
		uint8	u1Data;
		struct {
			uint8	xTAUJnTOL00		:1;
			uint8	xTAUJnTOL01		:1;
			uint8	xTAUJnTOL02		:1;
			uint8	xTAUJnTOL03		:1;
			uint8	b4Reserved		:4;
		} stBit;
	} unTAUJnTOL;

	uint8	u1Dummy6[3];

	/* TAUJnRDT register */
	union {
		uint8	u1Data;
		struct {
			uint8	xTAUJnRDT00		:1;
			uint8	xTAUJnRDT01		:1;
			uint8	xTAUJnRDT02		:1;
			uint8	xTAUJnRDT03		:1;
			uint8	b4Reserved		:4;
		} stBit;
	} unTAUJnRDT;

	uint8	u1Dummy7[3];

	/* TAUJnRSF register */
	union {
		uint8	u1Data;
		struct {
			uint8	xTAUJnRSF00		:1;
			uint8	xTAUJnRSF01		:1;
			uint8	xTAUJnRSF02		:1;
			uint8	xTAUJnRSF03		:1;
			uint8	b4Reserved		:4;
		} stBit;
	} unTAUJnRSF;

	uint8	u1Dummy8[3];
	uint8	u1Dummy9[16];

	/* TAUJnCMORm register */
	Tauj_TAUJnCMORm_Type	stTAUJnCMORm[TAUJ_CHANNEL_NUM];

	/* TAUJnTPS register */
	union {
		uint16	u2Data;
		struct {
			uint16	b4TAUJnPRS0		:4;
			uint16	b4TAUJnPRS1		:4;
			uint16	b4TAUJnPRS2		:4;
			uint16	b4TAUJnPRS3		:4;
		} stBit;
	} unTAUJnTPS;

	uint8	u1Dummy10[2];

	/* TAUJnBRS register */
	uint8	u1TAUJnBRS;

	uint8	u1Dummy11[3];

	/* TAUJnTOM register */
	union {
		uint8	u1Data;
		struct {
			uint8	xTAUJnTOM00		:1;
			uint8	xTAUJnTOM01		:1;
			uint8	xTAUJnTOM02		:1;
			uint8	xTAUJnTOM03		:1;
			uint8	b4Reserved		:4;
		} stBit;
	} unTAUJnTOM;

	uint8	u1Dummy12[3];

	/* TAUJnTOC register */
	union {
		uint8	u1Data;
		struct {
			uint8	xTAUJnTOC00		:1;
			uint8	xTAUJnTOC01		:1;
			uint8	xTAUJnTOC02		:1;
			uint8	xTAUJnTOC03		:1;
			uint8	b4Reserved		:4;
		} stBit;
	} unTAUJnTOC;

	uint8	u1Dummy13[3];

	/* TAUJnRDE register */
	union {
		uint8	u1Data;
		struct {
			uint8	xTAUJnRDE00		:1;
			uint8	xTAUJnRDE01		:1;
			uint8	xTAUJnRDE02		:1;
			uint8	xTAUJnRDE03		:1;
			uint8	b4Reserved		:4;
		} stBit;
	} unTAUJnRDE;

	uint8	u1Dummy14[3];

	/* TAUJnRDM register */
	union {
		uint8	u1Data;
		struct {
			uint8	xTAUJnRDM00		:1;
			uint8	xTAUJnRDM01		:1;
			uint8	xTAUJnRDM02		:1;
			uint8	xTAUJnRDM03		:1;
			uint8	b4Reserved		:4;
		} stBit;
	} unTAUJnRDM;

} Reg_Tauj_Type;

#if (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B)
typedef	struct {

	/* SELB_TAUJ3I Register */
	union {
		uint8	u1Data;
		struct {
			uint8	xSELB_TAUJ3I0	:1;
			uint8	xSELB_TAUJ3I1	:1;
			uint8	b6Reserved		:6;
		} stBit;
	} unSELB_TAUJ3I;

} Reg_Tauj3_SelbType;
#endif

/*==============================================================================================*/
/*	struct address definition																	*/
/*==============================================================================================*/
#if (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A)
	/* TAUJ Address base */
	#define		TAUJ0_BASE_ADR			((uint32)(0xFFBF7000U))
	#define		TAUJ1_BASE_ADR			((uint32)(0xFFBF7200U))
	#define		TAUJ2_BASE_ADR			((uint32)(0xFFE80000U))
	#define		TAUJ3_BASE_ADR			((uint32)(0xFFE81000U))
	/* TAUJ Register Access  */
	#define		REG_TAUJ0				(*(volatile Reg_Tauj_Type*)			TAUJ0_BASE_ADR)
	#define		REG_TAUJ1				(*(volatile Reg_Tauj_Type*)			TAUJ1_BASE_ADR)
	#define		REG_TAUJ2				(*(volatile Reg_Tauj_Type*)			TAUJ2_BASE_ADR)
	#define		REG_TAUJ3				(*(volatile Reg_Tauj_Type*)			TAUJ3_BASE_ADR)

#elif (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B)
	/* TAUJ Address base */
	#define		TAUJ2_BASE_ADR			((uint32)(0xFFE80000U))
	#define		TAUJ3_BASE_ADR			((uint32)(0xFFE81000U))
	#define		TAUJ3_SELB_BASE_ADR		((uint32)(0xFFE81800U))
	/* TAUJ Register Access  */
	#define		REG_TAUJ2				(*(volatile Reg_Tauj_Type*)			TAUJ2_BASE_ADR)
	#define		REG_TAUJ3				(*(volatile Reg_Tauj_Type*)			TAUJ3_BASE_ADR)
	#define		REG_TAUJ3_SELB			(*(volatile Reg_Tauj3_SelbType*)	TAUJ3_SELB_BASE_ADR)

#elif (MCAL_SPAL_TARGET == MCAL_TARGET_RCARS4_G4MH)
	/* [R-Car-ControlDomain]TAUJ Address base */
	#define		TAUJ1_BASE_ADR			((uint32)(0xFFBF7200U))
	#define		TAUJ3_BASE_ADR			((uint32)(0xFFE81000U))
	/* TAUJ Register Access  */
	#define		REG_TAUJ1				(*(volatile Reg_Tauj_Type*)			TAUJ1_BASE_ADR)
	#define		REG_TAUJ3				(*(volatile Reg_Tauj_Type*)			TAUJ3_BASE_ADR)

#else	/* (MCAL_SPAL_TARGET == MCAL_TARGET_RCARS4_CR52) */
	/* [R-Car-ApplicationDomain]TAUJ Address base */
	#define		TAUJ1_BASE_ADR			((uint32)(0xDFBF7200U))
	#define		TAUJ3_BASE_ADR			((uint32)(0xDFE81000U))
	/* TAUJ Register Access  */
	#define		REG_TAUJ1				(*(volatile Reg_Tauj_Type*)			TAUJ1_BASE_ADR)
	#define		REG_TAUJ3				(*(volatile Reg_Tauj_Type*)			TAUJ3_BASE_ADR)

#endif	/* MCAL_SPAL_TARGET*/

/*----------------------------------------------------------------------------------------------*/
/*	register setting definition																	*/
/*----------------------------------------------------------------------------------------------*/
/* TAUJnTPS register */
#define	TAUJ_TAUJnPRS0		((uint16)(0x0001U))	/* BIT0 */
#define	TAUJ_TAUJnPRS1		((uint16)(0x0010U))	/* BIT4 */
#define	TAUJ_TAUJnPRS2		((uint16)(0x0100U))	/* BIT8 */
#define	TAUJ_TAUJnPRS3		((uint16)(0x1000U))	/* BIT12 */

/* TAUJnCMORm register */
#define	TAUJ_TAUJnMD0		((uint16)(0x0001U))	/* BIT0 */
	#define	TAUJ_TAUJnMD0_DISABLE						((uint16)(0U))
	#define	TAUJ_TAUJnMD0_ENABLE						((uint16)(1U))
#define	TAUJ_TAUJnMD		((uint16)(0x0002U))	/* BIT1 */
	#define	TAUJ_TAUJnMD_INTERVAL_TIMER_MODE			((uint16)(0x00U))
	#define	TAUJ_TAUJnMD_CAPTURE_MODE					((uint16)(0x02U))
	#define	TAUJ_TAUJnMD_ONECOUNT_MODE					((uint16)(0x04U))
	#define	TAUJ_TAUJnMD_CAPTURE_AND_ONECOUNT_MODE		((uint16)(0x06U))
	#define	TAUJ_TAUJnMD_COUNT_CAPTURE_MODE				((uint16)(0x0BU))
	#define	TAUJ_TAUJnMD_GATE_COUNT_MODE				((uint16)(0x0CU))
	#define	TAUJ_TAUJnMD_CAPTURE_AND_GATE_COUNT_MODE	((uint16)(0x0DU))
#define	TAUJ_TAUJnCOS		((uint16)(0x0040U))	/* BIT6 */
#define	TAUJ_TAUJnSTS		((uint16)(0x0100U))	/* BIT8 */
#define	TAUJ_TAUJnMAS		((uint16)(0x0800U))	/* BIT11 */
	#define	TAUJ_TAUJnMAS_SLAVE							((uint16)(0U))
	#define	TAUJ_TAUJnMAS_MASTER						((uint16)(1U))
#define	TAUJ_TAUJnCCS		((uint16)(0x1000U))	/* BIT12 */
#define	TAUJ_TAUJnCKS		((uint16)(0x4000U))	/* BIT14 */
	#define	TAUJ_TAUJnCKS_CK0							((uint16)(0U))
	#define	TAUJ_TAUJnCKS_CK1							((uint16)(1U))
	#define	TAUJ_TAUJnCKS_CK2							((uint16)(2U))
	#define	TAUJ_TAUJnCKS_CK3							((uint16)(3U))

/* TAUJnCSRm register */
#define	TAUJ_TAUJnOVF		((uint8)(0x01U))	/* BIT0 */
	#define	TAUJ_TAUJnOVF_NO_OVERFLOW					((uint8)(0U))
	#define	TAUJ_TAUJnOVF_OVERFLOW						((uint8)(1U))

/* TAUJnCSCm register */
#define	TAUJ_TAUJnCLOV		((uint8)(0x01U))	/* BIT0 */
	#define	TAUJ_TAUJnCLOV_CLEAR_OVERFLOW_FLAG			((uint8)(1U))

/* TAUJnTS register */
#define	TAUJ_TAUJnTS0		((uint8)(0x01U))	/* BIT0 */
#define	TAUJ_TAUJnTS1		((uint8)(0x02U))	/* BIT1 */
#define	TAUJ_TAUJnTS2		((uint8)(0x04U))	/* BIT2 */
#define	TAUJ_TAUJnTS3		((uint8)(0x08U))	/* BIT3 */
	#define	TAUJ_TAUJnTSm_NO_FUNCTION					((uint8)(0x00U))
	#define	TAUJ_TAUJnTSm_ENABLES_OPERATION				((uint8)(0x01U))

/* TAUJnTE register */
#define	TAUJ_TAUJnTE0		((uint8)(0x01U))	/* BIT0 */
#define	TAUJ_TAUJnTE1		((uint8)(0x02U))	/* BIT1 */
#define	TAUJ_TAUJnTE2		((uint8)(0x04U))	/* BIT2 */
#define	TAUJ_TAUJnTE3		((uint8)(0x08U))	/* BIT3 */
	#define	TAUJ_TAUJnTEm_OPERATION_DISABLED			((uint8)(0U))
	#define	TAUJ_TAUJnTEm_OPERATION_ENABLED				((uint8)(1U))

/* TAUJnTT Register */
#define	TAUJ_TAUJnTT0		((uint8)(0x01U))	/* BIT0 */
#define	TAUJ_TAUJnTT1		((uint8)(0x02U))	/* BIT1 */
#define	TAUJ_TAUJnTT2		((uint8)(0x04U))	/* BIT2 */
#define	TAUJ_TAUJnTT3		((uint8)(0x08U))	/* BIT3 */
	#define	TAUJ_TAUJnTTm_NO_FUNCTION					((uint8)(0x00U))
	#define	TAUJ_TAUJnTTm_STOPS_OPERATION				((uint8)(0x01U))

/* TAUJnRDE register */
#define	TAUJ_TAUJnRDE0		((uint8)(0x01U))	/* BIT0 */
#define	TAUJ_TAUJnRDE1		((uint8)(0x02U))	/* BIT1 */
#define	TAUJ_TAUJnRDE2		((uint8)(0x04U))	/* BIT2 */
#define	TAUJ_TAUJnRDE3		((uint8)(0x08U))	/* BIT3 */
	#define	TAUJ_TAUJnRDE_DISABLES_REWRITE				((uint8)(0U))
	#define	TAUJ_TAUJnRDE_ENABLED_REWRITE				((uint8)(1U))

/* TAUJnRDM register */
#define	TAUJ_TAUJnRDM0		((uint8)(0x01U))	/* BIT0 */
#define	TAUJ_TAUJnRDM1		((uint8)(0x02U))	/* BIT1 */
#define	TAUJ_TAUJnRDM2		((uint8)(0x04U))	/* BIT2 */
#define	TAUJ_TAUJnRDM3		((uint8)(0x08U))	/* BIT3 */
	#define	TAUJ_TAUJnRDMm_MASTER_START					((uint8)(0U))
	#define	TAUJ_TAUJnRDMm_NO_FUNC						((uint8)(1U))

/* TAUJnRDT register */
#define	TAUJ_TAUJnRDT0		((uint8)(0x01U))	/* BIT0 */
#define	TAUJ_TAUJnRDT1		((uint8)(0x02U))	/* BIT1 */
#define	TAUJ_TAUJnRDT2		((uint8)(0x04U))	/* BIT2 */
#define	TAUJ_TAUJnRDT3		((uint8)(0x08U))	/* BIT3 */
	#define	TAUJ_TAUJnRDTm_NO_FUNC						((uint8)(0U))
	#define	TAUJ_TAUJnRDTm_REWRITE_ENABLE				((uint8)(1U))

/* TAUJnRSF register */
#define	TAUJ_TAUJnRSF0		((uint8)(0x01U))	/* BIT0 */
#define	TAUJ_TAUJnRSF1		((uint8)(0x02U))	/* BIT1 */
#define	TAUJ_TAUJnRSF2		((uint8)(0x04U))	/* BIT2 */
#define	TAUJ_TAUJnRSF3		((uint8)(0x08U))	/* BIT3 */
	#define	TAUJ_TAUJnRSFm_REWRITE_COMPLETED			((uint8)(0U))
	#define	TAUJ_TAUJnRSFm_WAITS_REWRITE				((uint8)(1U))

/* TAUJnTOE register */
#define	TAUJ_TAUJnTOE0		((uint8)(0x01U))	/* BIT0 */
#define	TAUJ_TAUJnTOE1		((uint8)(0x02U))	/* BIT1 */
#define	TAUJ_TAUJnTOE2		((uint8)(0x04U))	/* BIT2 */
#define	TAUJ_TAUJnTOE3		((uint8)(0x08U))	/* BIT3 */
	#define	TAUJ_TAUJnTOEm_DISABLE						((uint8)(0U))
	#define	TAUJ_TAUJnTOEm_ENABLE						((uint8)(1U))

/* TAUJnTO register */
#define	TAUJ_TAUJnTO0		((uint8)(0x01U))	/* BIT0 */
#define	TAUJ_TAUJnTO1		((uint8)(0x02U))	/* BIT1 */
#define	TAUJ_TAUJnTO2		((uint8)(0x04U))	/* BIT2 */
#define	TAUJ_TAUJnTO3		((uint8)(0x08U))	/* BIT3 */
	#define	TAUJ_TAUJnTOm_LOW							((uint8)(0U))
	#define	TAUJ_TAUJnTOm_HIGH							((uint8)(1U))

/* TAUJnTOM register */
#define	TAUJ_TAUJnTOM0		((uint8)(0x01U))	/* BIT0 */
#define	TAUJ_TAUJnTOM1		((uint8)(0x02U))	/* BIT1 */
#define	TAUJ_TAUJnTOM2		((uint8)(0x04U))	/* BIT2 */
#define	TAUJ_TAUJnTOM3		((uint8)(0x08U))	/* BIT3 */
	#define	TAUJ_TAUJnTOMm_INDEPENDENT					((uint8)(0U))
	#define	TAUJ_TAUJnTOMm_SYNCHRONOUS					((uint8)(1U))

/* TAUJnTOC register */
#define	TAUJ_TAUJnTOC0		((uint8)(0x01U))	/* BIT0 */
#define	TAUJ_TAUJnTOC1		((uint8)(0x02U))	/* BIT1 */
#define	TAUJ_TAUJnTOC2		((uint8)(0x04U))	/* BIT2 */
#define	TAUJ_TAUJnTOC3		((uint8)(0x08U))	/* BIT3 */
	#define	TAUJ_TAUJnTOCm_MODE1						((uint8)(0U))
	#define	TAUJ_TAUJnTOCm_NO_FUNC						((uint8)(1U))

/* TAUJnTOL register */
#define	TAUJ_TAUJnTOL0		((uint8)(0x01U))	/* BIT0 */
#define	TAUJ_TAUJnTOL1		((uint8)(0x02U))	/* BIT1 */
#define	TAUJ_TAUJnTOL2		((uint8)(0x04U))	/* BIT2 */
#define	TAUJ_TAUJnTOL3		((uint8)(0x08U))	/* BIT3 */
	#define	TAUJ_TAUJnTOLm_POSITIVE						((uint8)(0U))
	#define	TAUJ_TAUJnTOLm_NEGATIVE						((uint8)(1U))

#endif	/* REG_TAUJ_H */
/*-- End Of File -------------------------------------------------------------------------------*/
