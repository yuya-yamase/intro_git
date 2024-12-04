/* Reg_ATOM-r04-30300-0000-a-v00 */
/************************************************************************************************/
/*																								*/
/*		ATOM register definition (for microcontroller name)										*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#ifndef	REG_ATOM_H
#define	REG_ATOM_H

/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/
/*==============================================================================================*/
/* data types / structs / unions / macros														*/
/*==============================================================================================*/
#define ATOM_CHANNEL_NUM		((uint8)(8U))
/* Atomch access structure */
typedef struct
{
	uint32				u4AtomRdaddrChx;
	uint32				u4AtomCtrlChx;
	uint32				u4AtomSr0Chx;
	uint32				u4AtomSr1Chx;
	uint32				u4AtomCm0Chx;
	uint32				u4AtomCm1Chx;
	uint32				u4AtomCn0Chx;
	uint32				u4AtomStatChx;
	uint32				u4AtomIrqNotifyChx;
	uint32				u4AtomIrqEnChx;
	uint32				u4AtomIrqForcintChx;
	uint32				u4AtomIrqModeChx;
	uint32				u4Dummy[20];
} Reg_AtomCh_Type;

/* Atom register access structure */
typedef struct
{
	uint32				u4AtomAgcGlbCtrl;
	uint32				u4AtomAgcEndisCtrl;
	uint32				u4AtomAgcEndisStat;
	uint32				u4AtomAgcActTb;
	uint32				u4AtomAgcOutenCtrl;
	uint32				u4AtomAgcOutenStat;
	uint32				u4AtomAgcFupdCtrl;
	uint32				u4AtomAgcInttrig;
} Reg_Atom_Type;
/*==============================================================================================*/
/* defines																						*/
/*==============================================================================================*/
/* ATOM Address base */
#define ATOM0_BASE_ADDRESS				((uint32)(0xFF6E8000U))		/* Base address of ATOM0 */
#define ATOM1_BASE_ADDRESS				((uint32)(0xFF6E8800U))		/* Base address of ATOM1 */
#define ATOM2_BASE_ADDRESS				((uint32)(0xFF6E9000U))		/* ATOM2 base address */
#define ATOM3_BASE_ADDRESS				((uint32)(0xFF6E9800U))		/* ATOM3 base address */

/* ATOM Register Access  */
#define REG_ATOM0			(*(volatile Reg_Atom_Type*)			(ATOM0_BASE_ADDRESS + (uint32)(0x00000040U)))
#define REG_ATOM1			(*(volatile Reg_Atom_Type*)			(ATOM1_BASE_ADDRESS + (uint32)(0x00000040U)))
#define REG_ATOM2			(*(volatile Reg_Atom_Type*)			(ATOM2_BASE_ADDRESS + (uint32)(0x00000040U)))
#define REG_ATOM3			(*(volatile Reg_Atom_Type*)			(ATOM3_BASE_ADDRESS + (uint32)(0x00000040U)))

/* ATOM_CH Register Access  */
#define REG_ATOM0_CH0		(*(volatile Reg_AtomCh_Type*)		(ATOM0_BASE_ADDRESS + (uint32)(0x00000000U)))
#define REG_ATOM0_CH1		(*(volatile Reg_AtomCh_Type*)		(ATOM0_BASE_ADDRESS + (uint32)(0x00000080U)))
#define REG_ATOM0_CH2		(*(volatile Reg_AtomCh_Type*)		(ATOM0_BASE_ADDRESS + (uint32)(0x00000100U)))
#define REG_ATOM0_CH3		(*(volatile Reg_AtomCh_Type*)		(ATOM0_BASE_ADDRESS + (uint32)(0x00000180U)))
#define REG_ATOM0_CH4		(*(volatile Reg_AtomCh_Type*)		(ATOM0_BASE_ADDRESS + (uint32)(0x00000200U)))
#define REG_ATOM0_CH5		(*(volatile Reg_AtomCh_Type*)		(ATOM0_BASE_ADDRESS + (uint32)(0x00000280U)))
#define REG_ATOM0_CH6		(*(volatile Reg_AtomCh_Type*)		(ATOM0_BASE_ADDRESS + (uint32)(0x00000300U)))
#define REG_ATOM0_CH7		(*(volatile Reg_AtomCh_Type*)		(ATOM0_BASE_ADDRESS + (uint32)(0x00000380U)))

#define REG_ATOM1_CH0		(*(volatile Reg_AtomCh_Type*)		(ATOM1_BASE_ADDRESS + (uint32)(0x00000000U)))
#define REG_ATOM1_CH1		(*(volatile Reg_AtomCh_Type*)		(ATOM1_BASE_ADDRESS + (uint32)(0x00000080U)))
#define REG_ATOM1_CH2		(*(volatile Reg_AtomCh_Type*)		(ATOM1_BASE_ADDRESS + (uint32)(0x00000100U)))
#define REG_ATOM1_CH3		(*(volatile Reg_AtomCh_Type*)		(ATOM1_BASE_ADDRESS + (uint32)(0x00000180U)))
#define REG_ATOM1_CH4		(*(volatile Reg_AtomCh_Type*)		(ATOM1_BASE_ADDRESS + (uint32)(0x00000200U)))
#define REG_ATOM1_CH5		(*(volatile Reg_AtomCh_Type*)		(ATOM1_BASE_ADDRESS + (uint32)(0x00000280U)))
#define REG_ATOM1_CH6		(*(volatile Reg_AtomCh_Type*)		(ATOM1_BASE_ADDRESS + (uint32)(0x00000300U)))
#define REG_ATOM1_CH7		(*(volatile Reg_AtomCh_Type*)		(ATOM1_BASE_ADDRESS + (uint32)(0x00000380U)))

#define REG_ATOM2_CH0		(*(volatile Reg_AtomCh_Type*)		(ATOM2_BASE_ADDRESS + (uint32)(0x00000000U)))
#define REG_ATOM2_CH1		(*(volatile Reg_AtomCh_Type*)		(ATOM2_BASE_ADDRESS + (uint32)(0x00000080U)))
#define REG_ATOM2_CH2		(*(volatile Reg_AtomCh_Type*)		(ATOM2_BASE_ADDRESS + (uint32)(0x00000100U)))
#define REG_ATOM2_CH3		(*(volatile Reg_AtomCh_Type*)		(ATOM2_BASE_ADDRESS + (uint32)(0x00000180U)))
#define REG_ATOM2_CH4		(*(volatile Reg_AtomCh_Type*)		(ATOM2_BASE_ADDRESS + (uint32)(0x00000200U)))
#define REG_ATOM2_CH5		(*(volatile Reg_AtomCh_Type*)		(ATOM2_BASE_ADDRESS + (uint32)(0x00000280U)))
#define REG_ATOM2_CH6		(*(volatile Reg_AtomCh_Type*)		(ATOM2_BASE_ADDRESS + (uint32)(0x00000300U)))
#define REG_ATOM2_CH7		(*(volatile Reg_AtomCh_Type*)		(ATOM2_BASE_ADDRESS + (uint32)(0x00000380U)))

#define REG_ATOM3_CH0		(*(volatile Reg_AtomCh_Type*)		(ATOM3_BASE_ADDRESS + (uint32)(0x00000000U)))
#define REG_ATOM3_CH1		(*(volatile Reg_AtomCh_Type*)		(ATOM3_BASE_ADDRESS + (uint32)(0x00000080U)))
#define REG_ATOM3_CH2		(*(volatile Reg_AtomCh_Type*)		(ATOM3_BASE_ADDRESS + (uint32)(0x00000100U)))
#define REG_ATOM3_CH3		(*(volatile Reg_AtomCh_Type*)		(ATOM3_BASE_ADDRESS + (uint32)(0x00000180U)))
#define REG_ATOM3_CH4		(*(volatile Reg_AtomCh_Type*)		(ATOM3_BASE_ADDRESS + (uint32)(0x00000200U)))
#define REG_ATOM3_CH5		(*(volatile Reg_AtomCh_Type*)		(ATOM3_BASE_ADDRESS + (uint32)(0x00000280U)))
#define REG_ATOM3_CH6		(*(volatile Reg_AtomCh_Type*)		(ATOM3_BASE_ADDRESS + (uint32)(0x00000300U)))
#define REG_ATOM3_CH7		(*(volatile Reg_AtomCh_Type*)		(ATOM3_BASE_ADDRESS + (uint32)(0x00000380U)))

#endif	/* REG_ATOM_H */
/*-- End Of File -------------------------------------------------------------------------------*/
