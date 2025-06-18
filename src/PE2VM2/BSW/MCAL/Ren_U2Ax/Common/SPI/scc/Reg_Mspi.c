/* Reg_Mspi-r04-3000-0100-a-v00 */
/************************************************************************************************/
/*																								*/
/*		MSPI register definition (for RH850U2B)													*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

/*==============================================================================================*/
/*	include files																				*/
/*==============================================================================================*/
#include	"Std_Types.h"

#include	"Reg_Mspi.h"

/*==============================================================================================*/
/*	prototypes																					*/
/*==============================================================================================*/

/*==============================================================================================*/
/*	defines / data types / structs / unions / macros											*/
/*==============================================================================================*/

/*==============================================================================================*/
/*	constants																					*/
/*==============================================================================================*/

#pragma ghs section rodata=".SPI_RODATA_CONST"
volatile Reg_Mspi_UnitType* const cpstReg_Mspi[MSPI_UNIT_NUM] = {
	(&REG_MSPI0),
	(&REG_MSPI1),
	(&REG_MSPI2),
	(&REG_MSPI3),
	(&REG_MSPI4),
	(&REG_MSPI5)
#if ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_373PIN ) 
	,(&REG_MSPI6)
	,(&REG_MSPI7)
	,(&REG_MSPI8)
#endif

};

volatile Reg_Mspi_IntfType* const cpstReg_MspiIntf[MSPI_UNIT_NUM] = {
	(&REG_MSPI0INTF),
	(&REG_MSPI1INTF),
	(&REG_MSPI2INTF),
	(&REG_MSPI3INTF),
	(&REG_MSPI4INTF),
	(&REG_MSPI5INTF)
#if ( MCAL_PKG_U2A_TARGET == MCAL_PKG_U2A16_373PIN ) 
	,(&REG_MSPI6INTF)
	,(&REG_MSPI7INTF)
	,(&REG_MSPI8INTF)
#endif
};
#pragma ghs section rodata=default

/*-- End Of File -------------------------------------------------------------------------------*/
