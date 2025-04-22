/* ErrH-r04-3000-0200-b-v00 */
/************************************************************************************************/
/*																								*/
/*		ErrH Driver																				*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/
#include	"Std_Types.h"
#include	"Mcal_SpalCmn.h"
#include	"bswlib.h"

#include	"ErrH_cfg.h"
#include	"ErrH_Bist.h"

/*==============================================================================================*/
/* prototypes																					*/
/*==============================================================================================*/

/*==============================================================================================*/
/* defines / data types / structs / unions / macros												*/
/*==============================================================================================*/
#define		ERRH_BIST_REGNUM				(38)					/* BISTレジスタ数 */
#define		u4ERRH_BIST_INVALID_VALUE		((U4)0x00000000U)		/* レジスタ値無効 */

/*==============================================================================================*/
/* constants																					*/
/*==============================================================================================*/
#pragma ghs section rodata=".ERRH_RODATA_CONST"
static const U4 cu4ErrH_Bist_RegTbl[ERRH_BIST_REGNUM] = {
	(U4)&(REG_BIST_BIST.unLBISTREF1.u4Data),
	(U4)&(REG_BIST_BIST.unLBISTREF2.u4Data),
	(U4)&(REG_BIST_BIST.unMBISTREF1.u4Data),
	(U4)&(REG_BIST_BIST.unMBISTREF2.u4Data),
	(U4)&(REG_BIST_BIST.unMBISTREF3.u4Data),
	(U4)&(REG_BIST_BIST.unLBISTSIG1.u4Data),
	(U4)&(REG_BIST_BIST.unLBISTSIG2.u4Data),
	(U4)&(REG_BIST_BIST.unMBISTSIG1.u4Data),
	(U4)&(REG_BIST_BIST.unMBISTSIG2.u4Data),
	(U4)&(REG_BIST_BIST.unMBISTSIG3.u4Data),
	(U4)&(REG_BIST_BIST.u4MBIST1FTAG0),
	(U4)&(REG_BIST_BIST.u4MBIST1FTAG1),
	(U4)&(REG_BIST_BIST.u4MBIST1FTAG2),
	(U4)&(REG_BIST_BIST.u4MBIST1FTAG3),
	(U4)&(REG_BIST_BIST.u4MBIST1FTAG4),
	(U4)&(REG_BIST_BIST.u4MBIST1FTAG5),
	(U4)&(REG_BIST_BIST.u4MBIST1FTAG6),
	(U4)&(REG_BIST_BIST.u4MBIST1FTAG7),
	(U4)&(REG_BIST_BIST.u4MBIST2FTAG0),
	(U4)&(REG_BIST_BIST.u4MBIST2FTAG1),
	(U4)&(REG_BIST_BIST.u4MBIST2FTAG2),
	(U4)&(REG_BIST_BIST.u4MBIST3FTAG0),
	(U4)&(REG_BIST_BIST.u4MBIST1ECC0),
	(U4)&(REG_BIST_BIST.u4MBIST1ECC1),
	(U4)&(REG_BIST_BIST.u4MBIST1ECC2),
	(U4)&(REG_BIST_BIST.u4MBIST1ECC3),
	(U4)&(REG_BIST_BIST.u4MBIST1ECC4),
	(U4)&(REG_BIST_BIST.u4MBIST1ECC5),
	(U4)&(REG_BIST_BIST.u4MBIST1ECC6),
	(U4)&(REG_BIST_BIST.u4MBIST1ECC7),
	(U4)&(REG_BIST_BIST.u4MBIST2ECC0),
	(U4)&(REG_BIST_BIST.u4MBIST2ECC1),
	(U4)&(REG_BIST_BIST.u4MBIST2ECC2),
	(U4)&(REG_BIST_BIST.u4MBIST3ECC0),
	(U4)&(REG_BIST_BIST.unBSEQ0ST.u4Data),
	(U4)&(REG_BIST_BIST.unBISTST.u4Data),
	(U4)&(REG_BIST_BIST.unBSEQ0SEL.u4Data),
	(U4)&(REG_BIST_SYSCTRL.unBSEQ0CTL.u4Data)
};
#pragma ghs section rodata=default

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
/* BIST Register Value Get Function																*/
/* return		: Register Value																*/
/* parameters	: Register No																	*/
/*----------------------------------------------------------------------------------------------*/
U4	ErrH_Bist_GetBistRegValue( U1 t_u1RegNo )
{
	U4				t_u4RegValue;

	t_u4RegValue =  u4ERRH_BIST_INVALID_VALUE;	/* レジスタ値無効で初期化 */

	if ( t_u1RegNo < (U1)ERRH_BIST_REGNUM ) 
	{
		t_u4RegValue = *(volatile U4 *)cu4ErrH_Bist_RegTbl[t_u1RegNo];
	}

	return ( t_u4RegValue );
}

/*----------------------------------------------------------------------------------------------*/
/* Scheduled / Event Functions																	*/
/*----------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------*/
/* Local Functions																				*/
/*----------------------------------------------------------------------------------------------*/

#pragma ghs section text=default
/*-- End Of File -------------------------------------------------------------------------------*/
