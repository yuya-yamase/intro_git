/* pil_intc_r04-3000-0000-a-v00 */
/************************************************************************************************/
/*																								*/
/*		PIL INTC																				*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#ifndef PIL_INTC_H
#define PIL_INTC_H


/*==============================================================================================*/
/*	include files																				*/
/*==============================================================================================*/

/*==============================================================================================*/
/*	defines / data types / structs / unions	/ macros											*/
/*==============================================================================================*/
#define	INTC_INTC1_CH_NUM		(32)
#define	INTC_INTC2_CH_NUM		(992)
#define	INTC_CH_NUM				(INTC_INTC1_CH_NUM + INTC_INTC2_CH_NUM)

#define INTC_PINT_REG_NUM		((DMA_DTS_CH_NUM/32) * 2)

/*==============================================================================================*/
/*	register type definition																	*/
/*==============================================================================================*/

/* Peripheral Interrupt Function */
typedef struct
{

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
	}unPINT[INTC_PINT_REG_NUM];						/* 0xFF090000-0xFF090020 *//* Peripheral Interrupt Status Register */

	union
	{
		U4		u4Data;
		U2		u2Data[2];
		U1		u1Data[4];
	}unPINTCLR[INTC_PINT_REG_NUM];					/* 0xFF090020-0xFF090040 *//* Peripheral Interrupt Status Clear Register */

}Reg_Intif_Type;

/* Interrupt control 2 */
typedef struct
{

	union
	{
		U2		u2Data;
		U1		u1Data[2];
		struct
		{
			U2		b4EIP		:4;		/* Interrupt priority */
			U2		b1Dummy1	:1;		/* reserved bit */
			U2		xEIOV		:1;		/* Interrupt overflow */
			U2		xEITB		:1;		/* Interrupt vector selection bit */
			U2		xEIMK		:1;		/* Interrupt mask bit */
			U2		b4Dummy2	:4;		/* reserved bit */
			U2		xEIRF		:1;		/* Interrupt request flag */
			U2		b2Dummy3	:2;		/* reserved bit */
			U2		xEICT		:1;		/* Interrupt channel type bit */
		}stBit;
	}unEIC[INTC_CH_NUM];			/* 0 -31 is dummy definition: no access */	/* 0xFFF 80,000 - 0xFFF80800 *//* EI level interrupt control register */

}Reg_Intc2_Type;

/* PINT */
#define		INTC_PINT_REGNO_TCI0_31			(0)		/* PINT register CH0 */
#define		INTC_PINT_REGNO_TCI32_63		(1)		/* PINT register CH1 */
#define		INTC_PINT_REGNO_TCI64_95		(2)		/* PINT register CH2 */
#define		INTC_PINT_REGNO_TCI96_127		(3)		/* PINT register CH3 */
#define		INTC_PINT_REGNO_CCI0_31			(4)		/* PINT register CH4 */
#define		INTC_PINT_REGNO_CCI32_63		(5)		/* PINT register CH5 */
#define		INTC_PINT_REGNO_CCI64_95		(6)		/* PINT register CH6 */
#define		INTC_PINT_REGNO_CCI96_127		(7)		/* PINT register CH7 */

/* EIC */
#define		INTC_EIC_EICT				(BIT15)		/* Interrupt channel type bit */
	#define		INTC_EIC_EICT_EDGE			(0)		/* Edge detection */
	#define		INTC_EIC_EICT_LEVEL			(1)		/* level detection */
#define		INTC_EIC_EIRF				(BIT12)		/* Interrupt request flag */
	#define		INTC_EIC_EIRF_NOINT			(0)		/* No interrupt request (default) */
	#define		INTC_EIC_EIRF_INTREQ		(1)		/* Interrupt requested */
#define		INTC_EIC_EIMK				(BIT7)		/* Interrupt mask bit */
	#define		INTC_EIC_EIMK_ENABLE		(0)		/* Allow Interrupt Handling */
	#define		INTC_EIC_EIMK_DISABLE		(1)		/* Prevent interrupts (default) */
#define		INTC_EIC_EITB				(BIT6)		/* Interrupt vector selection bit */
	#define		INTC_EIC_EITB_DIRECT		(0)		/* Priority-based direct branching */
	#define		INTC_EIC_EITB_TABLE			(1)		/* Table reference method */
#define		INTC_EIC_EIOV				(BIT5)		/* Interrupt overflow bit */
	#define		INTC_EIC_EIOV_NO_OVERFLOW		(0)		/* No overflow */
	#define		INTC_EIC_EIOV_OVERFLOW		(1)		/* Interrupt overflow detection (when edge is detected) */
#define		INTC_EIC_EIP				(BIT3 + BIT2 + BIT1 + BIT0)		/* 16 level interrupt priority */
	#define		INTC_EIC_EIP_LEVEL15	(0x0FU)		/* Interrupt priority level 15 */
#define		INTC_EIC_EIP_0				(BIT0)

/*==============================================================================================*/
/*	struct address definition																	*/
/*==============================================================================================*/
#define		Reg_INTIF		(*(volatile Reg_Intif_Type*)(0xFF090000U))
#define		Reg_INTC2		(*(volatile Reg_Intc2_Type*)(0xFFF80000U))	/* base address at 0xFFF 80,000 instead of 0xFFF80040 */


/*==============================================================================================*/
/*	API Functions																				*/
/*==============================================================================================*/
/************************************************************************************************/
/*	Service name	:	SetInterrupt															*/
/*	Reentrancy		:	Re-entrant																*/
/*	Parameters (in)	:	IntcChannel - (32 - 1023)												*/
/*					:	Ie - Interrupt E/D (OFF:DISABLE/ON:ENABLE)								*/
/*	Return value	:	none																	*/
/*	Caveat			:	Interrupt No. reserved on IntcChannel not allowed						*/
/*					:	EIC register not allowed to operate within category 10% embedded function*/
/*					:	Interrupt numbers bound to other cores are disabled						*/
/************************************************************************************************/
void	Pil_Intc2_SetInterrupt( U2 t_u2IntcChannel, U1 t_u1Ie );

#if ( DMA_CFG_REG_CHK == STD_ON ) 
/************************************************************************************************/
/*	Service name	:	GetInterrupt															*/
/*	Reentrancy		:	Concurrency Safe														*/
/*	Parameters (in)	:	IntcChannel - (32 - 1023)												*/
/*	Return value	:	Interrupt Enable (ON:Enable / OFF:Disable)								*/
/*	Caveat			:																			*/
/************************************************************************************************/
U1		Pil_Intc2_GetInterrupt( U2 t_u2IntcChannel );
#endif


#endif /* PIL_INTC_H */
/*-- End Of File -------------------------------------------------------------------------------*/
