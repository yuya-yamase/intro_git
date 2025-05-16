/* pil_ecc_r04-3000-0000-a-v03 */
/************************************************************************************************/
/*																								*/
/*		PIL ECC Driver																			*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#if 0	// zantei MPU‚Í2ŒŽ––”ñ‘Î‰ž

/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/
#include	"ErrH_cfg.h"

#include	"pil_ecc.h"

#include	"errh_reg_ecc.h"

/*==============================================================================================*/
/* prototypes																					*/
/*==============================================================================================*/

/*==============================================================================================*/
/* defines / data types / structs / unions / macros												*/
/*==============================================================================================*/

/*==============================================================================================*/
/* constants																					*/
/*==============================================================================================*/

/*==============================================================================================*/
/* variables																					*/
/*==============================================================================================*/

/*==============================================================================================*/
/* functions																					*/
/*==============================================================================================*/
#pragma ghs section text=".ERRH_TEXT_CODE"
/*----------------------------------------------------------------------------------------------*/
/* API Functions																				*/
/*----------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------*/
/* Local RAM Ecc Fatal Error Status Clear Function(Core0)										*/
/* return		: none																			*/
/* parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Ecc_ClearLramPe0EccFatalErrorStatus( void )
{
	REG_ECC_MECCCAP_LR_PE0CL0.unLR0_DSTCLR.u4Data = (U4)ECC_MECCCAP_LR_PE0CL0_DSTCLR_DSTCLR00 * (U4)ECC_MECCCAP_LR_PE0CL0_DSTCLR_CLEAR;
	Bswlib_Sync_Pipeline_4( REG_ECC_MECCCAP_LR_PE0CL0.unLR0_DSTCLR.u4Data );
}

/*----------------------------------------------------------------------------------------------*/
/* Local RAM Ecc Fatal Error Status Clear Function(Core1)										*/
/* return		: none																			*/
/* parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Ecc_ClearLramPe1EccFatalErrorStatus( void )
{
	REG_ECC_MECCCAP_LR_PE1CL0.unLR0_DSTCLR.u4Data = (U4)ECC_MECCCAP_LR_PE1CL0_DSTCLR_DSTCLR00 * (U4)ECC_MECCCAP_LR_PE1CL0_DSTCLR_CLEAR;
	Bswlib_Sync_Pipeline_4( REG_ECC_MECCCAP_LR_PE1CL0.unLR0_DSTCLR.u4Data );
}

#if ( MCU_CORE_NUM > MCU_DUALCORE )
/*----------------------------------------------------------------------------------------------*/
/* Local RAM Ecc Fatal Error Status Clear Function(Core2)										*/
/* return		: none																			*/
/* parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Ecc_ClearLramPe2EccFatalErrorStatus( void )
{
	REG_ECC_MECCCAP_LR_PE2CL1.unLR0_DSTCLR.u4Data = (U4)ECC_MECCCAP_LR_PE2CL1_DSTCLR_DSTCLR00 * (U4)ECC_MECCCAP_LR_PE2CL1_DSTCLR_CLEAR;
	Bswlib_Sync_Pipeline_4( REG_ECC_MECCCAP_LR_PE2CL1.unLR0_DSTCLR.u4Data );
}
#endif

#if ( MCU_CORE_NUM > MCU_TRIPLECORE )
/*----------------------------------------------------------------------------------------------*/
/* Local RAM Ecc Fatal Error Status Clear Function(Core3)										*/
/* return		: none																			*/
/* parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Ecc_ClearLramPe3EccFatalErrorStatus( void )
{
	REG_ECC_MECCCAP_LR_PE3CL1.unLR0_DSTCLR.u4Data = (U4)ECC_MECCCAP_LR_PE3CL1_DSTCLR_DSTCLR00 * (U4)ECC_MECCCAP_LR_PE3CL1_DSTCLR_CLEAR;
	Bswlib_Sync_Pipeline_4( REG_ECC_MECCCAP_LR_PE3CL1.unLR0_DSTCLR.u4Data );
}
#endif

/*----------------------------------------------------------------------------------------------*/
/* Cluster RAM Ecc Fatal Error Status Clear Function											*/
/* return		: none																			*/
/* parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Ecc_ClearCramEccFatalErrorStatus( void )
{
	REG_ECC_MECCCAP_CRAM.unCR_DSTCLR.u4Data = (U4)ECC_MECCCAP_CRAM_CR_DSTCLR_DSTCLR00 * (U4)ECC_MECCCAP_CRAM_CR_DSTCLR_CLEAR;
	Bswlib_Sync_Pipeline_4( REG_ECC_MECCCAP_CRAM.unCR_DSTCLR.u4Data );
}

/*----------------------------------------------------------------------------------------------*/
/* Cluster RAM Ecc Fatal Error Status Get Function												*/
/* return		: Error Detect Status(=0:not error detect, !=0:error detect)					*/
/* parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
ZORN	Pil_Ecc_GetCramEccFatalErrorStatus( void )
{
	return( (ZORN)( (U4)( REG_ECC_MECCCAP_CRAM.unCR_DERSTR.u4Data & ( (U4)ECC_MECCCAP_CRAM_CR_DERSTR_AFEF00 + (U4)ECC_MECCCAP_CRAM_CR_DERSTR_DEDF00 ) ) ) );
}

#pragma ghs section text=default

#endif // zantei MPU‚Í2ŒŽ––”ñ‘Î‰ž
/*-- End Of File -------------------------------------------------------------------------------*/
