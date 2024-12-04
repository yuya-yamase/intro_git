/* Reg_CMU-r04-30300-0000-a-v00 */
/************************************************************************************************/
/*																								*/
/*		CMU register definition (for microcontroller name)										*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#ifndef	REG_CMU_H
#define	REG_CMU_H

/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/
/*==============================================================================================*/
/* data types / structs / unions / macros														*/
/*==============================================================================================*/
#define CMU_CLOCK_TYPE_NUM		((uint8)(8U))
/* Cmu's register access structure */
typedef struct
{
	uint32				u4CmuClkEn;
	uint32				u4CmuGclkNum;
	uint32				u4CmuGclkDen;
	uint32				u4CmuClkNCtrl[CMU_CLOCK_TYPE_NUM];
	uint32				u4CmuEclk0Num;
	uint32				u4CmuEclk0Den;
	uint32				u4CmuEclk1Num;
	uint32				u4CmuEclk1Den;
	uint32				u4CmuEclk2Num;
	uint32				u4CmuEclk2Den;
	uint32				u4CmuFxclkCtrl;
	uint32				u4CmuGlbCtrl;
	uint32				u4CmuClkCtrl;
} Reg_Cmu_Type;
/*==============================================================================================*/
/* defines																						*/
/*==============================================================================================*/
/* CMU Address base */
#define CMU_BASE_ADDRESS				((uint32)0xFF600300U)		/* CMU base address */

/* CMU Register Access  */
#define REG_CMU							(*(volatile Reg_Cmu_Type*)		CMU_BASE_ADDRESS)

#endif	/* REG_CMU_H */
/*-- End Of File -------------------------------------------------------------------------------*/
