/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_XID_STUB_C_MAJOR                 (1U)
#define TYDOCAN_XID_STUB_C_MINOR                 (0U)
#define TYDOCAN_XID_STUB_C_PATCH                 (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "tydocan_sal.h"
#include "oxdocan_saif.h"

#include "memcpy_u1.h"
#include "oxdocan_aubif.h"
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*                                                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
/* stub for tydocan_tmstp.c */
U1      u1_g_OdoKm(U4 * u4p_a_0p001km){return((U1)0);}

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Sample value for wired reprogramming */

U1      u1_g_oXDoCANRebyId_F188(U1 * u1_ap_ans, const U2 u2_a_ELPSD)
{
    static const U1 u1_sp_SW_NUMBER[OXDC_DATA_REA_ANS_NB_F188] = { 1U,                       /* Number of output sw parts number     */
                                                                  16U,                       /* Data Length                          */
                                                                   1U,                       /* ECU ID                               */
                                                                   0x38U,0x33U,0x38U,0x31U,  /* sw parts number 8381G1234510         */
                                                                   0x47U,0x31U,0x32U,0x33U,
                                                                   0x34U,0x35U,0x31U,0x30U,
                                                                   0x00U,0x00U,0x00U,0x00U };/* Digits 13-16 shall be outputted with ASCII 'NULL(00h)' */

    vd_g_MemcpyU1(&u1_ap_ans[0], &u1_sp_SW_NUMBER[0], (U4)OXDC_DATA_REA_ANS_NB_F188);

    return((U1)OXDC_SAL_PROC_FIN);
}

U1      u1_g_oXDoCANRebyId_F191(U1 * u1_ap_ans, const U2 u2_a_ELPSD)
{
    static const U1 u1_sp_HW_NUMBER[OXDC_DATA_REA_ANS_NB_F191] = { 1U,                        /* Number of output ECU parts number   */
                                                                  12U,                        /* Data Length                         */
                                                                   1U,                        /* ECU ID                              */
                                                                   0x38U,0x33U,0x38U,0x30U,   /* ECU parts number 8380030A80G0       */
                                                                   0x30U,0x33U,0x30U,0x41U,
                                                                   0x38U,0x30U,0x47U,0x30U };

    vd_g_MemcpyU1(&u1_ap_ans[0], &u1_sp_HW_NUMBER[0], (U4)OXDC_DATA_REA_ANS_NB_F191);

    return((U1)OXDC_SAL_PROC_FIN);
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/



/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_oXDoCANDtcTrchk_U1807(const U2 u2_a_ELPSD){return((U1)OXDC_DTC_TR_N_A);}
U1      u1_g_oXDoCANDtcTrchk_B1510(const U2 u2_a_ELPSD){return((U1)OXDC_DTC_TR_N_A);}
U1      u1_g_oXDoCANDtcTrchk_B1511(const U2 u2_a_ELPSD){return((U1)OXDC_DTC_TR_N_A);}
U1      u1_g_oXDoCANDtcTrchk_B1518(const U2 u2_a_ELPSD){return((U1)OXDC_DTC_TR_N_A);}
U1      u1_g_oXDoCANDtcTrchk_B1519(const U2 u2_a_ELPSD){return((U1)OXDC_DTC_TR_N_A);}
U1      u1_g_oXDoCANDtcTrchk_B151A(const U2 u2_a_ELPSD){return((U1)OXDC_DTC_TR_N_A);}
U1      u1_g_oXDoCANDtcTrchk_U2A00(const U2 u2_a_ELPSD){return((U1)OXDC_DTC_TR_N_A);}
U1      u1_g_oXDoCANDtcTrchk_U2A01(const U2 u2_a_ELPSD){return((U1)OXDC_DTC_TR_N_A);}
U1      u1_g_oXDoCANDtcTrchk_U2A16(const U2 u2_a_ELPSD){return((U1)OXDC_DTC_TR_N_A);}
U1      u1_g_oXDoCANDtcTrchk_U2A17(const U2 u2_a_ELPSD){return((U1)OXDC_DTC_TR_N_A);}
U1      u1_g_oXDoCANDtcTrchk_U2A12(const U2 u2_a_ELPSD){return((U1)OXDC_DTC_TR_N_A);}
U1      u1_g_oXDoCANDtcTrchk_U2A13(const U2 u2_a_ELPSD){return((U1)OXDC_DTC_TR_N_A);}
U1      u1_g_oXDoCANDtcTrchk_U2303(const U2 u2_a_ELPSD){return((U1)OXDC_DTC_TR_N_A);}
U1      u1_g_oXDoCANDtcTrchk_U2302(const U2 u2_a_ELPSD){return((U1)OXDC_DTC_TR_N_A);}
U1      u1_g_oXDoCANDtcTrchk_U2300(const U2 u2_a_ELPSD){return((U1)OXDC_DTC_TR_N_A);}
U1      u1_g_oXDoCANDtcTrchk_U2301(const U2 u2_a_ELPSD){return((U1)OXDC_DTC_TR_N_A);}
U1      u1_g_oXDoCANDtcTrchk_B2E01(const U2 u2_a_ELPSD){return((U1)OXDC_DTC_TR_N_A);}
U1      u1_g_oXDoCANDtcTrchk_B2E02(const U2 u2_a_ELPSD){return((U1)OXDC_DTC_TR_N_A);}
U1      u1_g_oXDoCANDtcTrchk_B2E03(const U2 u2_a_ELPSD){return((U1)OXDC_DTC_TR_N_A);}
U1      u1_g_oXDoCANDtcTrchk_B2E04(const U2 u2_a_ELPSD){return((U1)OXDC_DTC_TR_N_A);}
U1      u1_g_oXDoCANDtcTrchk_B2E05(const U2 u2_a_ELPSD){return((U1)OXDC_DTC_TR_N_A);}
U1      u1_g_oXDoCANDtcTrchk_B2E06(const U2 u2_a_ELPSD){return((U1)OXDC_DTC_TR_N_A);}
U1      u1_g_oXDoCANDtcTrchk_B2E07(const U2 u2_a_ELPSD){return((U1)OXDC_DTC_TR_N_A);}
U1      u1_g_oXDoCANDtcTrchk_B2E08(const U2 u2_a_ELPSD){return((U1)OXDC_DTC_TR_N_A);}
U1      u1_g_oXDoCANDtcTrchk_B2E12(const U2 u2_a_ELPSD){return((U1)OXDC_DTC_TR_N_A);}
U1      u1_g_oXDoCANDtcTrchk_B2E15(const U2 u2_a_ELPSD){return((U1)OXDC_DTC_TR_N_A);}
U1      u1_g_oXDoCANDtcTrchk_B2E20(const U2 u2_a_ELPSD){return((U1)OXDC_DTC_TR_N_A);}
U1      u1_g_oXDoCANDtcTrchk_B2E22(const U2 u2_a_ELPSD){return((U1)OXDC_DTC_TR_N_A);}
U1      u1_g_oXDoCANDtcTrchk_B2E23(const U2 u2_a_ELPSD){return((U1)OXDC_DTC_TR_N_A);}
U1      u1_g_oXDoCANDtcTrchk_B2E24(const U2 u2_a_ELPSD){return((U1)OXDC_DTC_TR_N_A);}
U1      u1_g_oXDoCANDtcTrchk_B2E25(const U2 u2_a_ELPSD){return((U1)OXDC_DTC_TR_N_A);}
U1      u1_g_oXDoCANDtcTrchk_B2E26(const U2 u2_a_ELPSD){return((U1)OXDC_DTC_TR_N_A);}
U1      u1_g_oXDoCANDtcTrchk_B2E27(const U2 u2_a_ELPSD){return((U1)OXDC_DTC_TR_N_A);}
U1      u1_g_oXDoCANDtcTrchk_B2E28(const U2 u2_a_ELPSD){return((U1)OXDC_DTC_TR_N_A);}
U1      u1_g_oXDoCANDtcTrchk_B2E29(const U2 u2_a_ELPSD){return((U1)OXDC_DTC_TR_N_A);}
U1      u1_g_oXDoCANDtcTrchk_B2E30(const U2 u2_a_ELPSD){return((U1)OXDC_DTC_TR_N_A);}

/*----------------------------------------------------------------------------------------------------------------------------------*/
/* U1      u1_g_TyDoCANEsiTRx_00000000(const U1 * u1_ap_REQ_RX, U1 * u1_ap_ans_tx, const U2 u2_a_ELPSD){return((U1)OXDC_SAL_PROC_FIN);} */


/*----------------------------------------------------------------------------------------------------------------------------------*/
uint8   u1_g_oXDoCANAubIfSpeed(uint8 * u1_ap_speed){return((Std_ReturnType)E_OK);}
uint8   u1_g_oXDoCANAubIfEcuPower(uint8 * u1_ap_ecupower){return((Std_ReturnType)E_OK);}
uint8   u1_g_oXDoCANAubIfAirTemp(uint8 * u1_ap_temp){return((Std_ReturnType)E_OK);}
uint8   u1_g_oXDoCANAubIfPowertrainSts(uint8 * u1_ap_ptsts){return((Std_ReturnType)E_OK);}
uint8   u1_g_oXDoCANAubIfNmWkf(uint8 * u1_ap_wkf){return((Std_ReturnType)E_OK);}
uint8   u1_g_oXDoCANAubIfNmSngf(uint8 * u1_ap_sngf){return((Std_ReturnType)E_OK);}
uint8   u1_g_oXDoCANAubIfEcuWkf(uint8 * u1_ap_wkf){return((Std_ReturnType)E_OK);}
uint8   u1_g_oXDoCANAubIfEcuSngf(uint8 * u1_ap_sngf){return((Std_ReturnType)E_OK);}
uint8   u1_g_oXDoCANAubIfNmGblWkf(uint8 * u1_ap_wkf){return((Std_ReturnType)E_OK);}
uint8   u1_g_oXDoCANAubIfNmGblSngf(uint8 * u1_ap_sngf){return((Std_ReturnType)E_OK);}
uint8   u1_g_oXDoCANAubIfMacUVHst(uint8 * u1_ap_hst){return((Std_ReturnType)E_OK);}
uint8   u1_g_oXDoCANAubIfEncUVHst(uint8 * u1_ap_hst){return((Std_ReturnType)E_OK);}
uint8   u1_g_oXDoCANAubIfSocTemp(uint8 * u1_ap_temp){return((Std_ReturnType)E_OK);}
uint8   u1_g_oXDoCANAubIfIvtCoolTemp(uint8 * u1_ap_temp){return((Std_ReturnType)E_OK);}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     5/ 9/2019  TN       New.                                                                                               */
/*                                                                                                                                   */
/*  * TN = Takashi Nagai, DENSO                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/
