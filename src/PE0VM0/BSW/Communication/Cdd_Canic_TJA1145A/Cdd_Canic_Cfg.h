/* Cdd_Canic-r03-5000-0100-a */
/************************************************************************************************/
/*																								*/
/*		CAN Transceiver IC Communication Driver (TJA1145A)										*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#ifndef	CDD_CANIC_CFG_H
#define	CDD_CANIC_CFG_H

/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/
#include    "Os.h"

/*==============================================================================================*/
/* defines / data types / structs / unions / macros												*/
/*==============================================================================================*/

#define		CDD_CANIC_CFG_IC_NUM				(1)

#define		CDD_CANIC_CFG_SEC_RAM0				(CDD_SEC_B_LRAM0_CPU0)
#define		CDD_CANIC_CFG_SEC_ROM0				(CDD_SEC_C_LROM0_CPU0_CFG)
#define		CDD_CANIC_CFG_SEC_PRG0				(CDD_SEC_P_LROM0_CPU0)

#define		CDD_CANIC_CFG_IC0_GETSPINLOCK()		SuspendAllInterrupts()
#define		CDD_CANIC_CFG_IC0_RELEASESPINLOCK()	ResumeAllInterrupts()

#endif	/* CDD_CANIC_CFG_H */
/*-- End Of File -------------------------------------------------------------------------------*/

