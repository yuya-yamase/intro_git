/* reg_ecc-r04-3000-0000-a-v04 */
/************************************************************************************************/
/*																								*/
/*		ECC register definition (for RH850U2B)													*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#if 0 // zantei ECCは2月末非対応

/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/
#include	"Std_Types.h"

#include	"errh_reg_ecc.h"

/*==============================================================================================*/
/* prototypes																					*/
/*==============================================================================================*/


/*==============================================================================================*/
/* defines / data types / structs / unions	/ macros											*/
/*==============================================================================================*/

/*==============================================================================================*/
/* constants																					*/
/*==============================================================================================*/
#pragma ghs section rodata=".ERRH_RODATA_CONST"
volatile Reg_Ecc_Ecc7Type* const pcstReg_Ecc7[ECC7_CHANNEL_NUM] = {
			&REG_ECC_E7RC01,
			&REG_ECC_E7RC02,
			&REG_ECC_E7RC03,
			&REG_ECC_E7RC04,
			&REG_ECC_E7FR00,
			&REG_ECC_E7FR01,
			&REG_ECC_E7FR02,
			&REG_ECC_E7GT00,
			&REG_ECC_E7GT01,
			&REG_ECC_E7GT10,
			&REG_ECC_E7GT11,
			&REG_ECC_E7GT20,
			&REG_ECC_E7GT21,
			&REG_ECC_E7GT30,
			&REG_ECC_E7GT31,
			&REG_ECC_E7GT40,
			&REG_ECC_E7GT41,
			&REG_ECC_E7GT50,
			&REG_ECC_E7GT51,
			&REG_ECC_E7GT60,
			&REG_ECC_E7GT61,
			&REG_ECC_E7GT100,
			&REG_ECC_E7GT101,
			&REG_ECC_E7GT102,
			&REG_ECC_E7GT110,
			&REG_ECC_E7GT111,
			&REG_ECC_E7GT112,
			&REG_ECC_E7MS00,
			&REG_ECC_E7MS01,
			&REG_ECC_E7MS02,
			&REG_ECC_E7MS03,
			&REG_ECC_E7MS04,
			&REG_ECC_E7MS05,
			&REG_ECC_E7MS06,
			&REG_ECC_E7MS07,
			&REG_ECC_E7MS08,
			&REG_ECC_E7MS09,
			&REG_ECC_E7MM00,
			&REG_ECC_E7MM01,
			&REG_ECC_E7ES00,
			&REG_ECC_E7ES01,
			&REG_ECC_E7ES02,
			&REG_ECC_E7ES03,
			&REG_ECC_E7ES04,
			&REG_ECC_E7ES05,
			&REG_ECC_E7DF00,
			&REG_ECC_E7DF10
};

volatile Reg_Ecc_Ecc6Type* const pcstReg_Ecc6[ECC6_CHANNEL_NUM] = {
			&REG_ECC_DFE0_DMEM0,
			&REG_ECC_DFE0_DMEM1,
			&REG_ECC_DFE1_DMEM0,
			&REG_ECC_DFE1_DMEM1
};

volatile Reg_Ecc_EccCnt_AType* const pcstReg_A[A_CHANNEL_NUM] = {
			&REG_ECC_ECCCNT_A_CCIB0CL0,
			&REG_ECC_ECCCNT_A_CCIB1CL0,
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
			&REG_ECC_ECCCNT_A_CCIB0CL1,
			&REG_ECC_ECCCNT_A_CCIB1CL1,
#endif
			&REG_ECC_ECCCNT_SA_PE0CL0,
			&REG_ECC_ECCCNT_A_GCFU0CL0,
			&REG_ECC_ECCCNT_SA_PE1CL0,
			&REG_ECC_ECCCNT_A_GCFU1CL0,
#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM > MCU_DUALCORE ) )	/* U2B10かつ3コア構成以上 */
			&REG_ECC_ECCCNT_SA_PE2CL1,
			&REG_ECC_ECCCNT_A_GCFU2CL1,
#endif
			&REG_ECC_ECCCNT_A_X2VCL0,
#if ( ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) && ( MCU_CORE_NUM > MCU_DUALCORE ) )	/* U2B10かつ3コア構成以上 */
			&REG_ECC_ECCCNT_A_X2VCL1,
#endif
			&REG_ECC_ECCCNT_A_BARR,
			&REG_ECC_ECCCNT_A_IPIR,
			&REG_ECC_ECCCNT_A_TPTM,
			&REG_ECC_ECCCNT_A_CRAM,
			&REG_ECC_ECCCNT_A_SG0,
			&REG_ECC_ECCCNT_A_SX2PV,
			&REG_ECC_ECCCNT_A_SX2FX,
			&REG_ECC_ECCCNT_A_FX2SX,
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
			&REG_ECC_ECCCNT_A_EX2FX,
			&REG_ECC_ECCCNT_A_GCFUE,
#endif
			&REG_ECC_ECCCNT_A_GCFUF,
			&REG_ECC_ECCCNT_A_SX2MB,
			&REG_ECC_ECCCNT_A_V2A1,
			&REG_ECC_ECCCNT_A_V2A2,
			&REG_ECC_ECCCNT_A_V2A3,
			&REG_ECC_ECCCNT_A_V2A4,
			&REG_ECC_ECCCNT_A_V2A5,
			&REG_ECC_ECCCNT_A_V2A6,
			&REG_ECC_ECCCNT_A_V2A7,
			&REG_ECC_ECCCNT_A_V2A8,
			&REG_ECC_ECCCNT_A_V2A9,
			&REG_ECC_ECCCNT_A_V2A10,
			&REG_ECC_ECCCNT_A_V2A11
};

volatile Reg_Ecc_EccCnt_D_V2AnWType* const pcstReg_V2AnW[V2ANW_CHANNEL_NUM] = {
			&REG_ECC_ECCCNT_D_V2A1W,
			&REG_ECC_ECCCNT_D_V2A2W,
			&REG_ECC_ECCCNT_D_V2A3W,
			&REG_ECC_ECCCNT_D_V2A4W,
			&REG_ECC_ECCCNT_D_V2A5W,
			&REG_ECC_ECCCNT_D_V2A6W,
			&REG_ECC_ECCCNT_D_V2A7W,
			&REG_ECC_ECCCNT_D_V2A8W,
			&REG_ECC_ECCCNT_D_V2A9W,
			&REG_ECC_ECCCNT_D_V2A10W,
			&REG_ECC_ECCCNT_D_V2A11W
};

volatile Reg_Ecc_PbnEccType* const pcstReg_PbnEcc[PBNECC_CHANNEL_NUM] = {
			&REG_ECC_PB1ECC,
			&REG_ECC_PB2ECC,
			&REG_ECC_PB3ECC,
			&REG_ECC_PB4ECC,
			&REG_ECC_PB5ECC,
			&REG_ECC_PB6ECC,
			&REG_ECC_PB7ECC,
			&REG_ECC_PB8ECC,
			&REG_ECC_PB9ECC,
			&REG_ECC_PB10ECC,
			&REG_ECC_PB11ECC
};

volatile Reg_Ecc_HbnEccType* const pcstReg_HbnEcc[HBNECC_CHANNEL_NUM] = {
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 ) 
			&REG_ECC_HB90MECC,
			&REG_ECC_HB90SECC,
#endif
			&REG_ECC_HB92MECC,
			&REG_ECC_HB92SECC,
			&REG_ECC_HB94SECC,
			&REG_ECC_HB97MECC,
			&REG_ECC_HB98MECC,
#if ( MCU_TYPE_SERIES == MCU_RH850U2B6 )
			&REG_ECC_HB911MECC,
			&REG_ECC_HB912MECC
#endif
};

volatile Reg_Ecc_BeccCap_V2AnType* const pcstReg_V2an[V2AN_CHANNEL_NUM] = {
			&REG_ECC_BECCCAP_V2A1,
			&REG_ECC_BECCCAP_V2A2,
			&REG_ECC_BECCCAP_V2A3,
			&REG_ECC_BECCCAP_V2A4,
			&REG_ECC_BECCCAP_V2A5,
			&REG_ECC_BECCCAP_V2A6,
			&REG_ECC_BECCCAP_V2A7,
			&REG_ECC_BECCCAP_V2A8,
			&REG_ECC_BECCCAP_V2A9,
			&REG_ECC_BECCCAP_V2A10,
			&REG_ECC_BECCCAP_V2A11
};

#pragma ghs section rodata=default

/*==============================================================================================*/
/* variables																					*/
/*==============================================================================================*/

/*==============================================================================================*/
/* functions																					*/
/*==============================================================================================*/

/*----------------------------------------------------------------------------------------------*/
/* API Functions																				*/
/*----------------------------------------------------------------------------------------------*/



#endif // zantei ECCは2月末非対応
/*-- End Of File -------------------------------------------------------------------------------*/
