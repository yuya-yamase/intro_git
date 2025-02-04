/* 2.1.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Fuel used count for Tripcom                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPSNSR_FUELUSD_C_MAJOR                (2)
#define TRIPSNSR_FUELUSD_C_MINOR                (1)
#define TRIPSNSR_FUELUSD_C_PATCH                (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "tripcom_cfg_private.h"
#include "tripsnsr_cfg_private.h"
#include "tripsnsr_fuelusd.h"
#include "tripcom_private.h"
#include "tripcom_calc.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((TRIPSNSR_FUELUSD_C_MAJOR != TRIPSNSR_FUELUSD_H_MAJOR) || \
     (TRIPSNSR_FUELUSD_C_MINOR != TRIPSNSR_FUELUSD_H_MINOR) || \
     (TRIPSNSR_FUELUSD_C_PATCH != TRIPSNSR_FUELUSD_H_PATCH))
#error "tripsnsr_fuelusd.c and tripsnsr_fuelusd.h : source and header files are inconsistent!"
#endif

#if ((TRIPSNSR_FUELUSD_C_MAJOR != TRIPSNSR_CFG_H_MAJOR) || \
     (TRIPSNSR_FUELUSD_C_MINOR != TRIPSNSR_CFG_H_MINOR) || \
     (TRIPSNSR_FUELUSD_C_PATCH != TRIPSNSR_CFG_H_PATCH))
#error "tripsnsr_fuelusd.c and tripsnsr_cfg_private.h : source and header files are inconsistent!"
#endif

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
static  U4      u4_s_tripsnsr_fuelusd;
static  U2      u2_s_tripsnsr_fuelusd_snsrbit;
static  U1      u1_s_tripsnsr_fuelusd_rxcnt;
static  U1      u1_s_tripsnsr_fuelusd_rxedg;
static  U4      u4_s_tripsnsr_fuelusd_w_emgf;
static  U2      u2_s_tripsnsr_fuelusd_w_emgf_snsrbit;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void     vd_s_TripsnsrFuelusdEMGFSmplngTask(const U2 u2_a_VEHSYSSTS, const U1 u1_a_PTSSTS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* void            vd_g_TripsnsrFuelusdInit(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripsnsrFuelusdInit(void)
{
    u4_s_tripsnsr_fuelusd         = (U4)0U;
    u2_s_tripsnsr_fuelusd_snsrbit = (U2)TRIPCOM_SNSRBIT_FUELUSD_UNKNOWN;
    (void)u1_g_TripsnsrCfgRxCntBFC(&u1_s_tripsnsr_fuelusd_rxcnt);
    u1_s_tripsnsr_fuelusd_rxedg   = (U1)FALSE;
    u4_s_tripsnsr_fuelusd_w_emgf         = (U4)0U;
    u2_s_tripsnsr_fuelusd_w_emgf_snsrbit = (U2)TRIPCOM_SNSRBIT_DTEED_FUELUSD_UNKNOWN;
}

/*===================================================================================================================================*/
/* void            vd_g_TripsnsrFuelusdSmplngTask(const U2 u2_a_VEHSYSSTS, const U1 u1_a_PTSSTS)                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripsnsrFuelusdSmplngTask(const U2 u2_a_VEHSYSSTS, const U1 u1_a_PTSSTS)
{
    U4          u4_t_fuel_dlt;
    U1          u1_t_msgsts;
    U1          u1_t_bfcrc;


    u1_s_tripsnsr_fuelusd_rxedg = (U1)FALSE;
    
    if ((u2_a_VEHSYSSTS & (U2)TRIPCOM_VEHSTS_IGON) != (U2)0U) {
        u1_t_msgsts = u1_g_TripsnsrCfgRxCntBFC(&u1_t_bfcrc);
        if (u1_t_msgsts == (U1)TRIPCOM_STSBIT_VALID) {
            if (u1_s_tripsnsr_fuelusd_rxcnt != u1_t_bfcrc) {
                u1_s_tripsnsr_fuelusd_rxedg = (U1)TRUE;
            }
            u1_s_tripsnsr_fuelusd_rxcnt = u1_t_bfcrc;
        }
        u4_t_fuel_dlt = (U4)0U;
        u1_t_msgsts   = u1_g_TripsnsrCfgGetBFC(&u4_t_fuel_dlt);

        u2_s_tripsnsr_fuelusd_snsrbit = (U2)0U;
        if (((u1_t_msgsts & (U1)TRIPCOM_STSBIT_UNKNOWN) != (U1)0U) ||
            ((u1_a_PTSSTS & (U1)TRIPCOM_STSBIT_UNKNOWN) != (U1)0U)) {

            u2_s_tripsnsr_fuelusd_snsrbit  = (U2)TRIPCOM_SNSRBIT_FUELUSD_UNKNOWN;
            u4_t_fuel_dlt = (U4)0U;
        }
        if (((u1_t_msgsts & (U1)TRIPCOM_STSBIT_INVALID) != (U1)0U) ||
            ((u1_a_PTSSTS & (U1)TRIPCOM_STSBIT_INVALID) != (U1)0U)) {

            u2_s_tripsnsr_fuelusd_snsrbit |= (U2)TRIPCOM_SNSRBIT_FUELUSD_INVALID;
            u4_t_fuel_dlt = (U4)0U;
        }
        if (u1_s_tripsnsr_fuelusd_rxedg != (U1)TRUE) {
            u4_t_fuel_dlt = (U4)0U;
        }
        if((u1_t_msgsts & (U1)TRIPCOM_STSBIT_UNKNOWN) != (U1)0U){
            u2_s_tripsnsr_fuelusd_snsrbit |= (U2)TRIPCOM_SNSRBIT_B_FC_UNKNOWN;
        }
        if((u1_t_msgsts & (U1)TRIPCOM_STSBIT_INVALID) != (U1)0U){
            u2_s_tripsnsr_fuelusd_snsrbit |= (U2)TRIPCOM_SNSRBIT_B_FC_INVALID;
        }

        if ((u2_a_VEHSYSSTS & (U2)TRIPCOM_VEHSTS_DRVCYC) != (U2)0U) {
            u4_s_tripsnsr_fuelusd = u4_g_TripcomCalcAddU4U4(u4_s_tripsnsr_fuelusd, u4_t_fuel_dlt);
        }
        vd_s_TripsnsrFuelusdEMGFSmplngTask(u2_a_VEHSYSSTS, u1_a_PTSSTS);

    }
}
/*===================================================================================================================================*/
/* static void     vd_s_TripsnsrFuelusdEMGFSmplngTask(const U2 u2_a_VEHSYSSTS, const U1 u1_a_PTSSTS)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_TripsnsrFuelusdEMGFSmplngTask(const U2 u2_a_VEHSYSSTS, const U1 u1_a_PTSSTS)
{
    U4          u4_t_fuel_dlt;
    U1          u1_t_emgf;
    U1          u1_t_msgsts_emgf;
    U1          u1_t_msgsts_bfc;

    u1_t_emgf        = (U1)0U;
    u1_t_msgsts_emgf = u1_g_TripcomCfgGetEMGF(&u1_t_emgf);
    u4_t_fuel_dlt    = (U4)0U;
    u1_t_msgsts_bfc  = u1_g_TripsnsrCfgGetBFC(&u4_t_fuel_dlt);

    u2_s_tripsnsr_fuelusd_w_emgf_snsrbit = (U2)0U;
    if (((u1_t_msgsts_bfc  & (U1)TRIPCOM_STSBIT_UNKNOWN) != (U1)0U) ||
        ((u1_t_msgsts_emgf & (U1)TRIPCOM_STSBIT_UNKNOWN) != (U1)0U) ||
        ((u1_a_PTSSTS      & (U1)TRIPCOM_STSBIT_UNKNOWN) != (U1)0U)) {

        u2_s_tripsnsr_fuelusd_w_emgf_snsrbit  = (U2)TRIPCOM_SNSRBIT_DTEED_FUELUSD_UNKNOWN;
        u4_t_fuel_dlt = (U4)0U;
    }
    if (((u1_t_msgsts_bfc  & (U1)TRIPCOM_STSBIT_INVALID) != (U1)0U) ||
        ((u1_t_msgsts_emgf & (U1)TRIPCOM_STSBIT_INVALID) != (U1)0U) ||
        ((u1_a_PTSSTS      & (U1)TRIPCOM_STSBIT_INVALID) != (U1)0U)) {

        u2_s_tripsnsr_fuelusd_w_emgf_snsrbit |= (U2)TRIPCOM_SNSRBIT_DTEED_FUELUSD_INVALID;
        u4_t_fuel_dlt = (U4)0U;
    }
    if (u1_s_tripsnsr_fuelusd_rxedg != (U1)TRUE) {
        u4_t_fuel_dlt = (U4)0U;
    }
    if((u1_t_msgsts_bfc & (U1)TRIPCOM_STSBIT_UNKNOWN) != (U1)0U){
        u2_s_tripsnsr_fuelusd_w_emgf_snsrbit |= (U2)TRIPCOM_SNSRBIT_DTEED_B_FC_UNKNOWN;
    }
    if((u1_t_msgsts_bfc & (U1)TRIPCOM_STSBIT_INVALID) != (U1)0U){
        u2_s_tripsnsr_fuelusd_w_emgf_snsrbit |= (U2)TRIPCOM_SNSRBIT_DTEED_B_FC_INVALID;
    }

    if (((u2_a_VEHSYSSTS & (U2)TRIPCOM_VEHSTS_DRVCYC) != (U2)0U) ||
        (u1_t_emgf                                    == (U1)1U)){
        u4_s_tripsnsr_fuelusd_w_emgf = u4_g_TripcomCalcAddU4U4(u4_s_tripsnsr_fuelusd_w_emgf, u4_t_fuel_dlt);
    }

}
/*===================================================================================================================================*/
/* U2              u2_g_TripsnsrFuelusdGetDelta(U4 * u4_ap_delta)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2              u2_g_TripsnsrFuelusdGetDelta(U4 * u4_ap_delta)
{
    u4_ap_delta[TRIPCOM_DELTA_DC_FUELUSD_PC] = u4_s_tripsnsr_fuelusd;
    u4_s_tripsnsr_fuelusd = (U4)0U;

    return (u2_s_tripsnsr_fuelusd_snsrbit);
}
/*===================================================================================================================================*/
/* U2              u2_g_TripsnsrFuelusdEmgfGetDelta(U4 * u4_ap_delta)                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2              u2_g_TripsnsrFuelusdEmgfGetDelta(U4 * u4_ap_delta)
{
    u4_ap_delta[TRIPCOM_DELTA_DC_FUELUSD_W_EMGF_PC] = u4_s_tripsnsr_fuelusd_w_emgf;
    u4_s_tripsnsr_fuelusd_w_emgf = (U4)0U;

    return ((U2)0U);/* u2_s_tripsnsr_fuelusd_w_emgf_snsrbit is notified by u2_g_TripsnsrFuelusdEmgfSts */
}
/*===================================================================================================================================*/
/* U2              u2_g_TripsnsrFuelusdEmgfSts(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2              u2_g_TripsnsrFuelusdEmgfSts(void)
{
    return (u2_s_tripsnsr_fuelusd_w_emgf_snsrbit);
}
/*===================================================================================================================================*/
/* U1              u1_g_TripsnsrFuelusdRxReset(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_TripsnsrFuelusdRxReset(void)
{
    U1 u1_t_ret;


    u1_t_ret = (U1)0U;
    if (u1_s_tripsnsr_fuelusd_rxedg == (U1)TRUE) {
        u1_t_ret = (U1)TRIPCOM_INSTFEHE_UPD;
    }

    return (u1_t_ret);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    11/07/2018  HY       New.                                                                                               */
/*  1.1.0    03/23/2020  YA       Change for 800B CV                                                                                 */
/*  1.1.1    07/27/2020  YA       Change status to be determined only during IG-ON                                                   */
/*  2.0.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*  2.0.2    10/27/2021  TK       QAC supported.                                                                                     */
/*  2.1.0    04/14/2022  TA(M)    See tripcom.c v2.1.1                                                                               */
/*  2.1.1    08/08/2022  YI       See tripsnsr.c v2.1.1                                                                              */
/*                                                                                                                                   */
/*  * HY   = Hidefumi Yoshida, Denso                                                                                                 */
/*  * YA   = Yuhei Aoyama, DensoTechno                                                                                               */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * TK   = Takanori Kuno, Denso Techno                                                                                             */
/*  * YI   = Yoshiki Iwata, NTT Data MSE                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
