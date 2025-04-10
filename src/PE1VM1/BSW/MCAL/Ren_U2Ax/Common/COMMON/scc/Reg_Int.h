/* Reg_INT-r04-30700-0000-a-v01 */
/************************************************************************************************/
/*																								*/
/*		Standby Controller Register definition													*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#ifndef	REG_INT_H
#define	REG_INT_H

/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/
#include	"Std_Types.h"
#include	"Mcal_SpalCmn.h"

/*==============================================================================================*/
/*	register type definition																	*/
/*==============================================================================================*/
#if (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A)
#define INT_INTC1_CH_NUM			((uint16)(32U))
#define INT_INTC2_CH_NUM			((uint16)(736U))
#define INT_PE_NUM					((uint16)(4U))
#elif (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B)
#define INT_INTC1_CH_NUM			((uint16)(32U))
#define INT_INTC2_CH_NUM			((uint16)(992U))
#define INT_PE_NUM					((uint16)(6U))
#else	/* (MCAL_SPAL_TARGET == MCAL_TARGET_RCARS4_G4MH) */
#define INT_INTC1_CH_NUM			((uint16)(32U))
#define INT_INTC2_CH_NUM			((uint16)(736U))
#define INT_PE_NUM					((uint16)(2U))
#endif
#define INT_INTC2_IMR_NUM			( INT_INTC2_CH_NUM / (uint16)32U )

/* EICn */
typedef struct {
	union {
		uint16	u2Data;
		uint8	u1Data[2];
		struct {
			uint16	b4EIPn			:4;
			uint16	xReserved		:1;
			uint16	xEIOVn			:1;
			uint16	xEITBn			:1;
			uint16	xEIMKn			:1;
			uint16	b4Reserved		:4;
			uint16	xEIRFn			:1;
			uint16	b2Reserved		:2;
			uint16	xEICTn			:1;
		} stBit;
	} unEICn;
} INT_EICn_Type;

/* IMRn */
typedef struct {
	union {
		uint32 u4Data;
		struct {
			uint32	xEIMK0			:1;
			uint32	xEIMK1			:1;
			uint32	xEIMK2			:1;
			uint32	xEIMK3			:1;
			uint32	xEIMK4			:1;
			uint32	xEIMK5			:1;
			uint32	xEIMK6			:1;
			uint32	xEIMK7			:1;
			uint32	xEIMK8			:1;
			uint32	xEIMK9			:1;
			uint32	xEIMK10			:1;
			uint32	xEIMK11			:1;
			uint32	xEIMK12			:1;
			uint32	xEIMK13			:1;
			uint32	xEIMK14			:1;
			uint32	xEIMK15			:1;
			uint32	xEIMK16			:1;
			uint32	xEIMK17			:1;
			uint32	xEIMK18			:1;
			uint32	xEIMK19			:1;
			uint32	xEIMK20			:1;
			uint32	xEIMK21			:1;
			uint32	xEIMK22			:1;
			uint32	xEIMK23			:1;
			uint32	xEIMK24			:1;
			uint32	xEIMK25			:1;
			uint32	xEIMK26			:1;
			uint32	xEIMK27			:1;
			uint32	xEIMK28			:1;
			uint32	xEIMK29			:1;
			uint32	xEIMK30			:1;
			uint32	xEIMK31			:1;
		}stBit;
	} unIMRn;
} INT_IMRn_Type;

/* EIBDn */
typedef struct {
	union {
		uint32 u4Data;
		struct {
			uint32	b3PEID				:3;
			uint32	b5Reserved0			:5;
			uint32	b3GPID				:3;
			uint32	b4Reserved			:4;
			uint32	xGM					:1;
			uint32	b8Reserved			:8;
			uint32	b2BCP				:2;
			uint32	b5Reserved1			:5;
		}stBit;
	} unEIBDn;
} INT_EIBDn_Type;

/* FIBDn */
typedef struct {
	union {
		uint32 u4Data;
		struct {
			uint32	b3PEID				:3;
			uint32	b5Reserved			:5;
			uint32	b3GPID				:3;
			uint32	b4Reserved			:4;
			uint32	xGM					:1;
			uint32	b16Reserved			:16;
		}stBit;
	} unFIBDn;
} INT_FIBDn_Type;

/* EEICn */
typedef struct {
	union {
		uint32 u4Data;
		struct {
			uint32	b6EIPn				:6;
			uint32	b9Reserved			:9;
			uint32	xEIOVn				:1;
			uint32	b6Reserved			:6;
			uint32	xEITBn				:1;
			uint32	xEIMKn				:1;
			uint32	b4Reserved			:4;
			uint32	xEIRFn				:1;
			uint32	b2Reserved			:2;
			uint32	xEICTn				:1;
		}stBit;
	} unEEICn;
} INT_EEICn_Type;

/* EIBG */
typedef struct {
	union {
		uint32 u4Data;
		struct {
			uint32	b6BGPR				:6;
			uint32	b26Reserved			:26;
		}stBit;
	} unEIBG;
} INT_EIBG_Type;

/* FIBG */
typedef struct {
	union {
		uint32 u4Data;
		struct {
			uint32	xBGE				:1;
			uint32	b31Reserved			:31;
		}stBit;
	} unFIBG;
} INT_FIBG_Type;

/* IHVCFG */
typedef struct {
	union {
		uint32 u4Data;
		struct {
			uint32	xIHVE				:1;
			uint32	b31Reserved			:31;
		}stBit;
	} unIHVCFG;
} INT_IHVCFG_Type;

/* I2EIBGm */
typedef struct {
	union {
		uint32 u4Data;
		struct {
			uint32	b6BGPR				:6;
			uint32	b26Reserved			:26;
		}stBit;
	} unI2EIBGm;
} INT_I2EIBGm_Type;

/* TAUD3INTNOSELn */
typedef struct {
	union {
		uint32	u4Data;
		struct {
			uint32	b3INTTAUD30_sel			:3;
			uint32	b3INTTAUD31_sel			:3;
			uint32	b3INTTAUD32_sel			:3;
			uint32	b3INTTAUD33_sel			:3;
			uint32	b3INTTAUD34_sel			:3;
			uint32	xReserved0				:1;
			uint32	b3INTTAUD35_sel			:3;
			uint32	b3INTTAUD36_sel			:3;
			uint32	b3INTTAUD37_sel			:3;
			uint32	b3INTTAUD38_sel			:3;
			uint32	b3INTTAUD39_sel			:3;
			uint32	xReserved1				:1;
		} stBit;
	} unTAUD3INTNOSELn;
} INT_TAUD3INTNOSELn_Type;

/* TAUD3INTNOSEL1 */
typedef struct {
	union {
		uint32	u4Data;
		struct {
			uint32	b3INTTAUD310_sel	:3;
			uint32	b3INTTAUD311_sel	:3;
			uint32	b3INTTAUD312_sel	:3;
			uint32	b3INTTAUD313_sel	:3;
			uint32	b3INTTAUD314_sel	:3;
			uint32	xReserved0			:1;
			uint32	b3INTTAUD315_sel	:3;
			uint32	xReserved1			:13;
		} stBit;
	} unTAUD3INTNOSEL1;
} INT_TAUD3INTNOSEL1_Type;

/* TAUD3INTNOSEL0 - TAUD3INTNOSEL1 register */
typedef	struct {

	/* TAUD3INTNOSEL0 : TAUD3 Interrupt Number Select Register0 */
	INT_TAUD3INTNOSELn_Type	stTaud3Intnosel0;

	/* TAUD3INTNOSEL1 : TAUD3 Interrupt Number Select Register1 */
	INT_TAUD3INTNOSEL1_Type	stTaud3Intnosel1;

} Reg_INTIF_TAUD3INTNOSELn_Type;

/* INTC1 */
typedef struct {
	/* EICn */
	INT_EICn_Type	stEIC[INT_INTC1_CH_NUM];
	uint8	u1Dummy0[176];
	
	/* IMR0 */
	INT_IMRn_Type	stIMR;
	uint8	u1Dummy1[12];
	
	/* EIBDn */
	INT_EIBDn_Type	stEIBD[INT_INTC1_CH_NUM];
	uint8	u1Dummy2[64];
	
	/* FIBD */
	INT_FIBDn_Type	stFIBD;
	uint8	u1Dummy3[60];
	
	/* EEICn */
	INT_EEICn_Type	stEEIC[INT_INTC1_CH_NUM];
	
	/* EIBG */
	INT_EIBG_Type	stEIBG;
	uint8	u1Dummy4[60];
	
	/* FIBG */
	INT_FIBG_Type	stFIBG;
	uint8	u1Dummy5[44];
	
	/* IHVCFG */
	INT_IHVCFG_Type	stIHVCFG;
	
} Reg_INTC1_Type;


/* INTC2 */
#if (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A)
typedef struct {
	/* EICn */
	INT_EICn_Type		stEIC[INT_INTC2_CH_NUM];
	uint8	u1Dummy0[2624];
	
	/* IMRn */
	INT_IMRn_Type		stIMR[INT_INTC2_IMR_NUM];
	uint8	u1Dummy1[3972];
	
	/* I2EIBGm */
	INT_I2EIBGm_Type	stI2EIBG[INT_PE_NUM];
	uint8	u1Dummy2[16];
	
	/* EIBDn */
	INT_EIBDn_Type		stEIBD[INT_INTC2_CH_NUM];
	uint8	u1Dummy3[5248];
	
	/* EEICn */
	INT_EEICn_Type		stEEIC[INT_INTC2_CH_NUM];
	
} Reg_INTC2_Type;

#elif (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B)
typedef struct {
	/* EICn */
	INT_EICn_Type		stEIC[INT_INTC2_CH_NUM];
	uint8	u1Dummy0[2112];
	
	/* IMRn */
	INT_IMRn_Type		stIMR[INT_INTC2_IMR_NUM];
	uint8	u1Dummy1[3940];
	
	/* I2EIBGm */
	INT_I2EIBGm_Type	stI2EIBG[INT_PE_NUM];
	uint8	u1Dummy2[8];
	
	/* EIBDn */
	INT_EIBDn_Type		stEIBD[INT_INTC2_CH_NUM];
	uint8	u1Dummy3[4224];
	
	/* EEICn */
	INT_EEICn_Type		stEEIC[INT_INTC2_CH_NUM];
	
} Reg_INTC2_Type;

#else	/* (MCAL_SPAL_TARGET == MCAL_TARGET_RCARS4_G4MH) */
typedef struct {
	/* EICn */
	INT_EICn_Type		stEIC[INT_INTC2_CH_NUM];

} Reg_INTC2_Type;

#endif


/*==============================================================================================*/
/*	struct address definition																	*/
/*==============================================================================================*/
#if (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A)
#define	INTC1_PE0_BASE_ADR		((uint32)(0xFFFC4000U))
#define	INTC1_PE1_BASE_ADR		((uint32)(0xFFFC8000U))
#define	INTC1_PE2_BASE_ADR		((uint32)(0xFFFCC000U))
#define	INTC1_PE3_BASE_ADR		((uint32)(0xFFFD0000U))
#define	INTC2_BASE_ADR			((uint32)(0xFFF80000U))

#elif (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B)
#define	INTC1_PE0_BASE_ADR		((uint32)(0xFFFC4000U))
#define	INTC1_PE1_BASE_ADR		((uint32)(0xFFFC8000U))
#define	INTC1_PE2_BASE_ADR		((uint32)(0xFFFCC000U))
#define	INTC1_PE3_BASE_ADR		((uint32)(0xFFFD0000U))
#define	INTC1_PE4_BASE_ADR		((uint32)(0xFFFD4000U))
#define	INTC1_PE5_BASE_ADR		((uint32)(0xFFFD8000U))
#define	INTC2_BASE_ADR			((uint32)(0xFFF80000U))

#define	INTSEL_INTSTT_BASE_ADR	((uint32)(0xFF090800U))
#define TAUD3INTNOSEL0_ADR		(INTSEL_INTSTT_BASE_ADR + 0x30U)
#define TAUD3INTNOSEL1_ADR		(INTSEL_INTSTT_BASE_ADR + 0x34U)

#else	/* (MCAL_SPAL_TARGET == MCAL_TARGET_RCARS4_G4MH) */
#define	INTC1_PE0_BASE_ADR		((uint32)(0xFFFC4000U))
#define	INTC1_PE1_BASE_ADR		((uint32)(0xFFFC8000U))
#define	INTC2_BASE_ADR			((uint32)(0xFFF80000U))

#endif

/* Register Access  */
#if (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A)
#define REG_INTC1_PE0		(*(volatile Reg_INTC1_Type*)		INTC1_PE0_BASE_ADR)
#define REG_INTC1_PE1		(*(volatile Reg_INTC1_Type*)		INTC1_PE1_BASE_ADR)
#define REG_INTC1_PE2		(*(volatile Reg_INTC1_Type*)		INTC1_PE2_BASE_ADR)
#define REG_INTC1_PE3		(*(volatile Reg_INTC1_Type*)		INTC1_PE3_BASE_ADR)
#elif (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B)
#define REG_INTC1_PE0		(*(volatile Reg_INTC1_Type*)		INTC1_PE0_BASE_ADR)
#define REG_INTC1_PE1		(*(volatile Reg_INTC1_Type*)		INTC1_PE1_BASE_ADR)
#define REG_INTC1_PE2		(*(volatile Reg_INTC1_Type*)		INTC1_PE2_BASE_ADR)
#define REG_INTC1_PE3		(*(volatile Reg_INTC1_Type*)		INTC1_PE3_BASE_ADR)
#define REG_INTC1_PE4		(*(volatile Reg_INTC1_Type*)		INTC1_PE4_BASE_ADR)
#define REG_INTC1_PE5		(*(volatile Reg_INTC1_Type*)		INTC1_PE5_BASE_ADR)
#define	REG_INTIF_TAUD3SEL	(*(volatile Reg_INTIF_TAUD3INTNOSELn_Type*)TAUD3INTNOSEL0_ADR)
#else	/* (MCAL_SPAL_TARGET == MCAL_TARGET_RCARS4_G4MH) */
#define REG_INTC1_PE0		(*(volatile Reg_INTC1_Type*)		INTC1_PE0_BASE_ADR)
#define REG_INTC1_PE1		(*(volatile Reg_INTC1_Type*)		INTC1_PE1_BASE_ADR)
#endif

#define REG_INTC2			(*(volatile Reg_INTC2_Type*)		INTC2_BASE_ADR)


/*----------------------------------------------------------------------------------------------*/
/*	register setting definition																	*/
/*----------------------------------------------------------------------------------------------*/
/* EICn Register EIMKn  */
#define	EIC_EIMK_ENABLE		((uint16)(0U))				/* Interrupt processing is enabled */
#define	EIC_EIMK_DISABLE	((uint16)(1U))				/* Interrupt processing is disabled */

#define	INT_EICnEIMKn_INT_DISABLE	((uint8)(0x80U))	/* Interrupt processing is disabled(8bit control) */

/* EICn Register EIRFn */
#define	EIC_EIRF_CLEAR		((uint16)(0U))				/* No interrupt request */
#define	EIC_EIRF_ENABLE		((uint16)(1U))				/* Interrupt request present */

/*  TAUD3INTNOSELn Register */
#define	INTIF_TAUD3INTNOSEL_DISABLE		((uint32)(0U))
#define	INTIF_TAUD3INTNOSEL_SEL_0		((uint32)(1U))
#define	INTIF_TAUD3INTNOSEL_SEL_1		((uint32)(2U))
#define	INTIF_TAUD3INTNOSEL_SEL_2		((uint32)(4U))

#endif	/* REG_INT_H */
/*-- End Of File -------------------------------------------------------------------------------*/
