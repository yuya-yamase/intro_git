/* 2.2.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Electric Power used count for Tripcom                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPSNSR_INSTEE_C_MAJOR                  (2)
#define TRIPSNSR_INSTEE_C_MINOR                  (2)
#define TRIPSNSR_INSTEE_C_PATCH                  (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "tripsnsr_cfg_private.h"
#include "tripsnsr_instee.h"
#include "tripcom_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((TRIPSNSR_INSTEE_C_MAJOR != TRIPSNSR_INSTEE_H_MAJOR) || \
     (TRIPSNSR_INSTEE_C_MINOR != TRIPSNSR_INSTEE_H_MINOR) || \
     (TRIPSNSR_INSTEE_C_PATCH != TRIPSNSR_INSTEE_H_PATCH))
#error "tripsnsr_instee.c and tripsnsr_instee.h : source and header files are inconsistent!"
#endif

#if ((TRIPSNSR_INSTEE_C_MAJOR != TRIPSNSR_CFG_H_MAJOR) || \
     (TRIPSNSR_INSTEE_C_MINOR != TRIPSNSR_CFG_H_MINOR) || \
     (TRIPSNSR_INSTEE_C_PATCH != TRIPSNSR_CFG_H_PATCH))
#error "tripsnsr_instee.c and tripsnsr_cfg_private.h : source and header files are inconsistent!"
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
static  S4      s4_s_tripsnsr_instee_epusd;
static  U2      u2_s_tripsnsr_instee_snsrbit;
static  U1      u1_s_tripsnsr_instee_updflg_old;
static  U1      u1_s_tripsnsr_instee_rxedg;
static  U1      u1_s_tripsnsr_instee_initrx;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void      vd_s_TripsnsrInsteeJudgeRxSts(const U2 u2_a_VEHSYSSTS, const U1 u1_a_UPDFLG, const S4 s4_a_EP_DLT);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* void            vd_g_TripsnsrInsteeInit(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripsnsrInsteeInit(void)
{
    s4_s_tripsnsr_instee_epusd      = (S4)0;
    u2_s_tripsnsr_instee_snsrbit    = (U2)TRIPCOM_SNSRBIT_INSTEE_UNKNOWN;
    u1_s_tripsnsr_instee_updflg_old = (U1)0U;
    u1_s_tripsnsr_instee_rxedg      = (U1)FALSE;
    u1_s_tripsnsr_instee_initrx     = (U1)FALSE;
}

/*===================================================================================================================================*/
/* void            vd_g_TripsnsrInsteeSmplngTask(const U2 u2_a_VEHSYSSTS, const U1 u1_a_PTSSTS)                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripsnsrInsteeSmplngTask(const U2 u2_a_VEHSYSSTS, const U1 u1_a_PTSSTS)
{
    S4          s4_t_ep_dlt;
    U1          u1_t_msgsts;
    U1          u1_t_updflg;


    if ((u2_a_VEHSYSSTS & (U2)TRIPCOM_VEHSTS_IGON) != (U2)0U) {

        s4_t_ep_dlt = (S4)0;
        u1_t_updflg = (U1)0U;

        u1_t_msgsts  = u1_g_TripsnsrCfgGetEpusd(&s4_t_ep_dlt);
        u1_t_msgsts |= u1_g_TripsnsrCfgGetEpUpdflg(&u1_t_updflg);
        u2_s_tripsnsr_instee_snsrbit = (U2)0U;
        if (((u1_t_msgsts & (U1)TRIPCOM_STSBIT_UNKNOWN) != (U1)0U) ||
            ((u1_a_PTSSTS & (U1)TRIPCOM_STSBIT_UNKNOWN) != (U1)0U)) {

            u2_s_tripsnsr_instee_snsrbit  = (U2)TRIPCOM_SNSRBIT_INSTEE_UNKNOWN;
            s4_t_ep_dlt = (S4)0;
        }
        if (((u1_t_msgsts & (U1)TRIPCOM_STSBIT_INVALID) != (U1)0U) ||
            ((u1_a_PTSSTS & (U1)TRIPCOM_STSBIT_INVALID) != (U1)0U)) {

            u2_s_tripsnsr_instee_snsrbit |= (U2)TRIPCOM_SNSRBIT_INSTEE_INVALID;
            s4_t_ep_dlt = (S4)0;
        }

        u1_s_tripsnsr_instee_rxedg = (U1)FALSE;
        if (u2_s_tripsnsr_instee_snsrbit == (U2)0U) {
            vd_s_TripsnsrInsteeJudgeRxSts(u2_a_VEHSYSSTS, u1_t_updflg, s4_t_ep_dlt);
        }
    }
    else {
        u1_s_tripsnsr_instee_initrx  = (U1)FALSE;
    }
}

/*===================================================================================================================================*/
/* U2              u2_g_TripsnsrInsteeGetDelta(U4 * u4_ap_delta)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2              u2_g_TripsnsrInsteeGetDelta(U4 * u4_ap_delta)
{
    u4_ap_delta[TRIPCOM_DELTA_DC_EPUSD_PC] = (U4)s4_s_tripsnsr_instee_epusd;
    s4_s_tripsnsr_instee_epusd = (S4)0;

    return (u2_s_tripsnsr_instee_snsrbit);
}

/*===================================================================================================================================*/
/* U1              u1_g_TripsnsrInsteeRxReset(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_TripsnsrInsteeRxReset(void)
{
    U1    u1_t_ret;


    u1_t_ret = (U1)0U;
    if (u1_s_tripsnsr_instee_rxedg == (U1)TRUE) {
        u1_t_ret = (U1)TRIPCOM_INSTEE_UPD;
    }
    return (u1_t_ret);
}

/*===================================================================================================================================*/
/* static  void      vd_s_TripsnsrInsteeJudgeRxSts(const U2 u2_a_VEHSYSSTS, const U1 u1_a_UPDFLG, const S4 s4_a_EP_DLT)              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void      vd_s_TripsnsrInsteeJudgeRxSts(const U2 u2_a_VEHSYSSTS, const U1 u1_a_UPDFLG, const S4 s4_a_EP_DLT)
{
    if (u1_s_tripsnsr_instee_initrx != (U1)TRUE) {

        u1_s_tripsnsr_instee_initrx = (U1)TRUE;
    }
    else if (u1_s_tripsnsr_instee_updflg_old != u1_a_UPDFLG) {

        u1_s_tripsnsr_instee_rxedg = (U1)TRUE;
        if ((u2_a_VEHSYSSTS & (U2)TRIPCOM_VEHSTS_DRVCYC) != (U2)0U) {

            s4_s_tripsnsr_instee_epusd += s4_a_EP_DLT;
        }
    }
    else {
        /* Do Nothing */
    }
    u1_s_tripsnsr_instee_updflg_old = u1_a_UPDFLG;
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    03/19/2020  YA       New.                                                                                               */
/*  1.1.0    03/23/2020  YA       Change for 800B CV                                                                                 */
/*  1.1.1    07/27/2020  YA       Change status to be determined only during IG-ON                                                   */
/*  2.0.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*  2.0.2    10/27/2021  TK       QAC supported.                                                                                     */
/*  2.1.0    04/14/2022  TA(M)    See tripcom.c v2.1.1                                                                               */
/*  2.1.1    08/08/2022  YI       See tripsnsr.c v2.1.1                                                                              */
/*  2.2.0    06/23/2025  RS       Change for BEV System_Consideration_2.(tripsnsr_cfg.c v2.1.1 -> v2.2.0.)                           */
/*                                                                                                                                   */
/*  * YA   = Yuhei Aoyama, DensoTechno                                                                                               */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * TK   = Takanori Kuno, Denso Techno                                                                                             */
/*  * YI   = Yoshiki Iwata, NTT Data MSE                                                                                             */
/*  * RS   = Ryuki Sako, Denso Techno                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
