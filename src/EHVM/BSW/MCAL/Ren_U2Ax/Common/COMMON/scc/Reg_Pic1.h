/* Reg_PIC1-r04-30300-0000-a-v01 */
/************************************************************************************************/
/*																								*/
/*		PIC1 Register definition																*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/
#ifndef REG_PIC1_H
#define REG_PIC1_H

/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/
#include	"Std_Types.h"
#include	"Mcal_SpalCmn.h"

/*==============================================================================================*/
/*	register type definition																	*/
/*==============================================================================================*/
/* Number of PIC1TAUDxSEL registers */
#if (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A)
#define PIC1_MAX_TAUDSEL				(2U) /* TAUD0-TAUD1 */
#define PIC1_MAX_SELB					(1U) /* TAUD2 */
#else	/* (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B) */
#define PIC1_MAX_TAUDSEL				(4U) /* TAUD0-TAUD3 */
#define PIC1_MAX_SELB					(0U) /* Non */
#endif

/* Number of Input settings in PIC1TAUDxSEL register */
#define PIC1_MAX_PIC_SELECT			(8U) /* Register width(32bit) / 1Config(4bit) */

/* 1Config bitwidth */
#define PIC_INPUT_CONFIG_BIT_WIDTH			(4U)
#define PIC_INPUT_SIGNAL_CONFIG_BIT_WIDTH	((uint16)2U)


/* PIC1TAUDnSEL */
typedef struct {
	union {
		uint32	u4Data;
		struct {
			uint32	xPIC1TAUDnIN00			:1;
			uint32	xPIC1TAUDnIN01			:1;
			uint32	xPIC1TAUDnIN02			:1;
			uint32	xPIC1TAUDnIN03			:1;
			uint32	xPIC1TAUDnIN20			:1;
			uint32	xPIC1TAUDnIN21			:1;
			uint32	xPIC1TAUDnIN22			:1;
			uint32	xPIC1TAUDnIN23			:1;
			uint32	xPIC1TAUDnIN40			:1;
			uint32	xPIC1TAUDnIN41			:1;
			uint32	xPIC1TAUDnIN42			:1;
			uint32	xPIC1TAUDnIN43			:1;
			uint32	xPIC1TAUDnIN60			:1;
			uint32	xPIC1TAUDnIN61			:1;
			uint32	xPIC1TAUDnIN62			:1;
			uint32	xPIC1TAUDnIN63			:1;
			uint32	xPIC1TAUDnIN80			:1;
			uint32	xPIC1TAUDnIN81			:1;
			uint32	xPIC1TAUDnIN82			:1;
			uint32	xPIC1TAUDnIN83			:1;
			uint32	xPIC1TAUDnIN100			:1;
			uint32	xPIC1TAUDnIN101			:1;
			uint32	xPIC1TAUDnIN102			:1;
			uint32	xPIC1TAUDnIN103			:1;
			uint32	xPIC1TAUDnIN120			:1;
			uint32	xPIC1TAUDnIN121			:1;
			uint32	xPIC1TAUDnIN122			:1;
			uint32	xPIC1TAUDnIN123			:1;
			uint32	xPIC1TAUDnIN140			:1;
			uint32	xPIC1TAUDnIN141			:1;
			uint32	xPIC1TAUDnIN142			:1;
			uint32	xPIC1TAUDnIN143			:1;
		}stBit;
	} unTAUDnSEL;
} Pic1_TAUDnSEL_Type;


#if (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A)
/* PIC1SELB_TAUD2I */
typedef struct {
	union {
		uint16	u2Data;
		struct {
			uint32	xSELBTAUD2I0			:1;
			uint32	xSELBTAUD2I1			:1;
			uint32	xSELBTAUD2I2			:1;
			uint32	xSELBTAUD2I3			:1;
			uint32	xSELBTAUD2I4			:1;
			uint32	xSELBTAUD2I5			:1;
			uint32	xSELBTAUD2I6			:1;
			uint32	xSELBTAUD2I7			:1;
			uint32	xSELBTAUD2I8			:1;
			uint32	xSELBTAUD2I9			:1;
			uint32	xSELBTAUD2I10			:1;
			uint32	xSELBTAUD2I11			:1;
			uint32	xSELBTAUD2I12			:1;
			uint32	xSELBTAUD2I13			:1;
			uint32	xSELBTAUD2I14			:1;
			uint32	xSELBTAUD2I15			:1;
		}stBit;
	} unSelbTaud2I;
	
	uint8	u1Dummy[2];
} Pic1_SelbTaud2I_Type;


#endif	/* (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A) */


/*==============================================================================================*/
/*	struct address definition																	*/
/*==============================================================================================*/
/* PIC Address base */
#if (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A)
#define PIC1_BASE_ADR				((uint32)(0xFFBFAF00U))
#define PIC1_SELB_TAUD2I_ADR		((uint32)(0xFFBF6800U))
#define PIC1_TAUD0SEL_ADR			((PIC1_BASE_ADR + 0x78U))
#define PIC1_TAUD1SEL_ADR			((PIC1_BASE_ADR + 0x7CU))
#define PIC1_TAUD2SEL_ADR			(PIC1_SELB_TAUD2I_ADR)
#else	/* (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B) */
#define PIC10_BASE_ADR				((uint32)(0xFFBFAF00U))
#define PIC11_BASE_ADR				((uint32)(0xFFBFB000U))
#define PIC1_TAUD0SEL_ADR			((PIC10_BASE_ADR + 0x78U))
#define PIC1_TAUD1SEL_ADR			((PIC10_BASE_ADR + 0x7CU))
#define PIC1_TAUD2SEL_ADR			((PIC11_BASE_ADR + 0x78U))
#define PIC1_TAUD3SEL_ADR			((PIC11_BASE_ADR + 0x7CU))
#endif


/*----------------------------------------------------------------------------------------------*/
/*	register setting definition																	*/
/*----------------------------------------------------------------------------------------------*/



#endif /* REG_PIC1_H  */
/*-- End Of File -------------------------------------------------------------------------------*/
