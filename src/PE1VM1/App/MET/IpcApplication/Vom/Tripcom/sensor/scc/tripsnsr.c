/* 2.2.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Control sensors for Tripcom                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPSNSR_C_MAJOR                        (2)
#define TRIPSNSR_C_MINOR                        (2)
#define TRIPSNSR_C_PATCH                        (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "tripsnsr_cfg_private.h"

#include "tripcom_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((TRIPSNSR_C_MAJOR != TRIPSNSR_H_MAJOR) || \
     (TRIPSNSR_C_MINOR != TRIPSNSR_H_MINOR) || \
     (TRIPSNSR_C_PATCH != TRIPSNSR_H_PATCH))
#error "tripsnsr.c and tripsnsr.h : source and header files are inconsistent!"
#endif

#if ((TRIPSNSR_C_MAJOR != TRIPSNSR_CFG_H_MAJOR) || \
     (TRIPSNSR_C_MINOR != TRIPSNSR_CFG_H_MINOR) || \
     (TRIPSNSR_C_PATCH != TRIPSNSR_CFG_H_PATCH))
#error "tripsnsr.c and tripsnsr_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPSNSR_ECOMODE_IDLSTP                 (0x03U)
#define TRIPSNSR_ECORUNSTS_CNVT                 (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  U2      u2_s_tripsnsr_drvcyc_sts;
static  U2      u2_s_tripsnsr_vehsyssts;
static  U1      u1_s_tripsnsr_rxrst;
static  U1      u1_s_tripsnsr_ptssts;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  U2      u2_s_TripsnsrMakeVehstsbit(void);
static  void    vd_s_TripsnsrSnpshtDelta(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* void            vd_g_TripsnsrInit(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripsnsrInit(void)
{
    U4          u4_t_loop;


    u2_s_tripsnsr_drvcyc_sts = (U2)0U;
    u2_s_tripsnsr_vehsyssts  = (U2)0U;
    u1_s_tripsnsr_rxrst      = (U1)0U;
    u1_s_tripsnsr_ptssts     = (U1)TRIPCOM_STSBIT_UNKNOWN;
    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)TRIPSNSR_NUM_SNSR; u4_t_loop++) {
        if (st_gp_TRIPSNSR_CNTTS_CFG[u4_t_loop].fp_vd_TRIPSNSR_INIT != vdp_PTR_NA) {
            (st_gp_TRIPSNSR_CNTTS_CFG[u4_t_loop].fp_vd_TRIPSNSR_INIT)();
        }
    }
}

/*===================================================================================================================================*/
/* void            vd_g_TripsnsrSmplngTask(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripsnsrSmplngTask(void)
{
    U4          u4_t_loop;


    u2_s_tripsnsr_vehsyssts = u2_s_TripsnsrMakeVehstsbit();

    if ((u2_s_tripsnsr_vehsyssts & (U2)TRIPCOM_VEHSTS_IGON) != (U2)0U) {
        u1_s_tripsnsr_ptssts = u1_g_TripsnsrCfgGetPtsSts();
    }
    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)TRIPSNSR_NUM_SNSR; u4_t_loop++) {
        if (st_gp_TRIPSNSR_CNTTS_CFG[u4_t_loop].fp_vd_TRIPSNSR_SMPLNG_TASK != vdp_PTR_NA) {
            (st_gp_TRIPSNSR_CNTTS_CFG[u4_t_loop].fp_vd_TRIPSNSR_SMPLNG_TASK)(u2_s_tripsnsr_vehsyssts, u1_s_tripsnsr_ptssts);
        }
    }

    vd_s_TripsnsrSnpshtDelta();
}

/*===================================================================================================================================*/
/* U2              u2_g_TripsnsrDeltaChk(U4 *u4_ap_delta)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2              u2_g_TripsnsrDeltaChk(U4 *u4_ap_delta)
{
    U4          u4_t_loop;
    U2          u2_t_snsrbit;


    u2_t_snsrbit = (U2)0U;
    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)TRIPSNSR_NUM_SNSR; u4_t_loop++) {
        if (st_gp_TRIPSNSR_CNTTS_CFG[u4_t_loop].fp_u2_TRIPSNSR_DELTA_CHK != vdp_PTR_NA) {
            u2_t_snsrbit |= (st_gp_TRIPSNSR_CNTTS_CFG[u4_t_loop].fp_u2_TRIPSNSR_DELTA_CHK)(u4_ap_delta);
        }
    }

    return (u2_t_snsrbit);
}

/*===================================================================================================================================*/
/* U1              u1_g_TripsnsrResetChk(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_TripsnsrResetChk(void)
{
    U1          u1_t_rxrst;


    u1_t_rxrst = u1_s_tripsnsr_rxrst;
    u1_s_tripsnsr_rxrst = (U1)0U;

    return (u1_t_rxrst);
}

/*===================================================================================================================================*/
/* U2              u2_g_TripsnsrVehstsChk(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2              u2_g_TripsnsrVehstsChk(void)
{
    return (u2_s_tripsnsr_vehsyssts);
}

/*===================================================================================================================================*/
/* static  U2      u2_s_TripsnsrMakeVehstsbit(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U2      u2_s_TripsnsrMakeVehstsbit(void)
{
    U2          u2_t_vehmode;
    U1          u1_t_igsts;
    U1          u1_t_signal;
    U1          u1_t_ecosts;
    U1          u1_t_vehsts;
    U2          u2_t_kmph;
    U1          u1_t_spdsts;


    u2_t_vehmode = (U2)0U;

    u1_t_vehsts = u1_g_TripsnsrAccOn();
    if (u1_t_vehsts == (U1)TRUE) {
        u2_t_vehmode = (U2)TRIPCOM_VEHSTS_ACCON;
    }

    u1_t_igsts = u1_g_TripsnsrIgnOn();
    if (u1_t_igsts == (U1)TRUE) {
        u2_t_vehmode |= (U2)TRIPCOM_VEHSTS_IGON;

        u1_t_vehsts = u1_g_TripsnsrPtsOn();
        if (u1_t_vehsts == (U1)TRUE) {
            u2_s_tripsnsr_drvcyc_sts = (U2)TRIPCOM_VEHSTS_DRVCYC;
        }
    }
    else {
        u2_s_tripsnsr_drvcyc_sts = (U2)0U;
    }
    u2_t_vehmode |= u2_s_tripsnsr_drvcyc_sts;

    u1_t_ecosts = u1_g_TripsnsrCfgEcoMode();
    u1_t_signal = (U1)0U;
    if (u1_t_ecosts == (U1)TRUE) {
        u1_t_vehsts = u1_g_TripsnsrCfgGetECOMODE3(&u1_t_signal);
        u2_t_vehmode |= (U2)((U2)u1_t_vehsts << TRIPSNSR_ECORUNSTS_CNVT);
    }
    else {
        u2_t_vehmode |= (U2)TRIPCOM_VEHSTS_ECORUNINV;
    }

    if (((u2_t_vehmode & (U2)(TRIPCOM_VEHSTS_ECORUNUNK | TRIPCOM_VEHSTS_ECORUNINV)) == (U2)0U) &&
        (u1_t_signal == (U1)TRIPSNSR_ECOMODE_IDLSTP)) {

        u2_t_vehmode |= (U2)TRIPCOM_VEHSTS_ECOSTP;
    }
    
    u2_t_kmph   = (U2)0U;
    u1_t_spdsts = u1_g_TripsnsrVspKmph(&u2_t_kmph);
    if (u1_t_spdsts != (U1)0U) {
        u2_t_kmph = (U2)0U;
    }
    if (u2_t_kmph > (U2)TRIPSNSR_VEH_STOP_THSLD) {
        u2_t_vehmode |= (U2)TRIPCOM_VEHSTS_VEHMV;
    }


    return (u2_t_vehmode);
}

/*===================================================================================================================================*/
/* static  void    vd_s_TripsnsrSnpshtDelta(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_TripsnsrSnpshtDelta(void)
{
    U4          u4_t_loop;
    U1          u1_t_resetbit;


    u1_t_resetbit = (U1)0U;
    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)TRIPSNSR_NUM_SNSR; u4_t_loop++) {
        if (st_gp_TRIPSNSR_CNTTS_CFG[u4_t_loop].fp_u1_TRIPSNSR_RESET != vdp_PTR_NA) {
            u1_t_resetbit |= (st_gp_TRIPSNSR_CNTTS_CFG[u4_t_loop].fp_u1_TRIPSNSR_RESET)();
        }
    }

    if (((u1_t_resetbit & (U1)TRIPCOM_INSTFEHE_UPD) != (U1)0U) ||
        ((u1_t_resetbit & (U1)TRIPCOM_INSTEE_UPD  ) != (U1)0U)) {
        vd_g_TripsnsrOdocntSnpshtDelta(u1_t_resetbit);
        u1_s_tripsnsr_rxrst = u1_t_resetbit;
    }
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
/*  2.1.1    08/08/2022  YI       Add vd_g_TripsnsrCfgEvDtePIEVE06.                                                                  */
/*  2.2.0    06/23/2025  RS       Change for BEV System_Consideration_2.(tripsnsr_cfg.c v2.1.1 -> v2.2.0.)                           */
/*                                                                                                                                   */
/*  * HY   = Hidefumi Yoshida, Denso                                                                                                 */
/*  * YA   = Yuhei Aoyama, DensoTechno                                                                                               */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * TK   = Takanori Kuno, Denso Techno                                                                                             */
/*  * YI   = Yoshiki Iwata, NTT Data MSE                                                                                             */
/*  * RS   = Ryuki Sako, Denso Techno                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
