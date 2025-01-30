/* 2.1.3 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Seatbelt reminder warning                                                                                                        */
/*  Vehicle status                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SBLT_VCLSTS_C_MAJOR                     (2)
#define SBLT_VCLSTS_C_MINOR                     (1)
#define SBLT_VCLSTS_C_PATCH                     (3)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "sblt_vclsts_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((SBLT_VCLSTS_C_MAJOR != SBLT_VCLSTS_H_MAJOR) || \
     (SBLT_VCLSTS_C_MINOR != SBLT_VCLSTS_H_MINOR) || \
     (SBLT_VCLSTS_C_PATCH != SBLT_VCLSTS_H_PATCH))
#error "sblt_vclsts.c and sblt_vclsts.h : source and header files are inconsistent!"
#endif

#if ((SBLT_VCLSTS_C_MAJOR != SBLT_VCLSTS_CFG_PRIVATE_H_MAJOR) || \
     (SBLT_VCLSTS_C_MINOR != SBLT_VCLSTS_CFG_PRIVATE_H_MINOR) || \
     (SBLT_VCLSTS_C_PATCH != SBLT_VCLSTS_CFG_PRIVATE_H_PATCH))
#error "sblt_vclsts.c and sblt_vclsts_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SBLT_VCLSTS_RSFT_TO                     (300U/SBLTWRN_TICK)

#define SBLT_VCLSTS_SPD_STOP_THSLD              ( 175U)                 /* 1.75 * VEHSPD_1_KMPH */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  U2      u2_s_sblt_vclsts_rsfttm;
static  U1      u1_s_sblt_vclsts_prksts;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  U4      u4_s_SbltVclstsGetSgnl(const U2 u2_a_IGONTMR, const U1 * u1_ap_MSGSTS, const U2 u2_a_SIGMSK);
static  U4      u4_s_SbltVclstsSpdChk(const U2 u2_a_KMPH, const U2 *u2_ap_SPD_THR);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* void            vd_g_SbltVclstsInit(void);                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_SbltVclstsInit(void)
{
    u2_s_sblt_vclsts_rsfttm = (U2)0U;
    u1_s_sblt_vclsts_prksts = (U1)0U;
}

/*===================================================================================================================================*/
/* U4              u4_g_SbltVclsts(const U2 u2_a_IGONTMR, U2 *u2p_a_vclspd, const U1 * u1_ap_MSGSTS)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4              u4_g_SbltVclsts(const U2 u2_a_IGONTMR, const U1 * u1_ap_MSGSTS, const U2 *u2_ap_SPD_THR)
{
    U4                                          u4_t_vclsts;
    U2                                          u2_t_kmph;
    U1                                          u1_t_spdsts;
    U2                                          u2_t_sigmsk;

    u2_t_sigmsk = (U2)(~u2_g_SBLT_VCLSIG_PARKSTS_MSK);

    u2_t_kmph   = (U2)0U;
    u1_t_spdsts = u1_g_VehspdKmphInst(&u2_t_kmph, (U1)TRUE);
    if (u1_t_spdsts != (U1)VEHSPD_STSBIT_VALID) {
        u2_t_kmph = (U2)0U;
    }

    u4_t_vclsts = (U4)0U;
    if (u2_t_kmph <= (U2)SBLT_VCLSTS_SPD_STOP_THSLD) {
        u2_t_sigmsk |= u2_g_SBLT_VCLSIG_PARKSTS_MSK;
    }
    if (u2_a_IGONTMR > (U2)0U) {
        u4_t_vclsts |= (U4)SBLTWRN_VCLSTS_IG_ONSTS;
        if (u2_a_IGONTMR > (U2)SBLTWRN_IGTIM_OVER500JDG) {
            u4_t_vclsts |= (U4)SBLTWRN_VCLSTS_IGTIM_OVER500;
        }

    }

    u4_t_vclsts |= u4_s_SbltVclstsGetSgnl(u2_a_IGONTMR, u1_ap_MSGSTS, u2_t_sigmsk);
    u4_t_vclsts |= u4_s_SbltVclstsSpdChk(u2_t_kmph, u2_ap_SPD_THR);

    if ((u4_t_vclsts & (U4)SBLTWRN_VCLSTS_SHIFT_R) != (U4)0U) {
        if (u2_s_sblt_vclsts_rsfttm < (U2)SBLT_VCLSTS_RSFT_TO) {
            u4_t_vclsts &= (~(U4)SBLTWRN_VCLSTS_SHIFT_R);
        }
        if (u2_s_sblt_vclsts_rsfttm < (U2)U2_MAX) {
            u2_s_sblt_vclsts_rsfttm++;
        }
        else {
            u2_s_sblt_vclsts_rsfttm = (U2)U2_MAX;
        }
    }
    else {
        u2_s_sblt_vclsts_rsfttm = (U2)0U;
    }
    if ((u4_t_vclsts & (U4)SBLTWRN_VCLSTS_PARK) != (U4)0U) {
        if (u1_s_sblt_vclsts_prksts == (U1)FALSE) {
            u4_t_vclsts |= (U4)SBLTWRN_VCLSTS_PARKEDG;
        }
        u1_s_sblt_vclsts_prksts = (U1)TRUE;
    } else {
        if (u1_s_sblt_vclsts_prksts == (U1)TRUE) {
            u4_t_vclsts |= (U4)SBLTWRN_VCLSTS_UNPARKEDG;
        }
        u1_s_sblt_vclsts_prksts = (U1)FALSE;
    }

    return (u4_t_vclsts);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltVclstsSpdChk(const U2 u2_a_KMPH, const U2 *u2_ap_SPD_THR)                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltVclstsSpdChk(const U2 u2_a_KMPH, const U2 *u2_ap_SPD_THR)
{
    static const U4     u4_s_SPD_SFT = (U4)10U;
    U4                  u4_t_vclsts;
    U4                  u4_t_loop;

    u4_t_vclsts = (U4)0U;
    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)SBLTWRN_NUM_SPD; u4_t_loop++) {
        if (u2_a_KMPH >= u2_ap_SPD_THR[u4_t_loop]) {
            u4_t_vclsts |= ((U4)1U << (u4_t_loop + u4_s_SPD_SFT));
            /* The maximum value of u4_t_loop is 4. The value of u4_s_SPD_SFT is 7.         */
            /* so (u4_t_loop + u4_s_SPD_SFT) is always less than U4_MAX.                    */
        }
    }
    return (u4_t_vclsts);
}

/*===================================================================================================================================*/
/* static  U4      u4_s_SbltVclstsGetSgnl(const U2 u2_a_IGONTMR, const U1 * u1_ap_MSGSTS, const U2 u2_a_SIGMSK)                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U4      u4_s_SbltVclstsGetSgnl(const U2 u2_a_IGONTMR, const U1 * u1_ap_MSGSTS, const U2 u2_a_SIGMSK)
{
    U4                                          u4_t_vclsts;
    U4                                          u4_t_loop;
    U2                                          u2_t_tmpsig;
    U1                                          u1_t_sgnl;
    const   ST_SBLT_VCLSIG_SGNLCFG *            stp_t_CFG;

    u2_t_tmpsig = (U2)0U;
    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)u1_g_SBLT_VCLSTS_NUM_SGNL; u4_t_loop++) {
        stp_t_CFG   = &st_gp_SBLT_VCLSIG_SGNLCFG[u4_t_loop];

        switch (u1_ap_MSGSTS[stp_t_CFG->u1_msghndlr]) {
            case SBLTWRN_VALID:
                if (u2_a_IGONTMR > (U2)(stp_t_CFG->u1_mskperiod)) {
                    u1_t_sgnl = (*stp_t_CFG->fp_SGNL)() & stp_t_CFG->u1_rngmsk;
                }
                else {
                    u1_t_sgnl = stp_t_CFG->u1_initval;
                }
                break;
            case SBLTWRN_INVALID:
                u1_t_sgnl = stp_t_CFG->u1_failval;
                break;
            /* case SBLTWRN_UNKNOWN: */
            default:
                u1_t_sgnl = stp_t_CFG->u1_initval;
                break;
        }
        u2_t_tmpsig |= (U2)((U4)u1_t_sgnl << u4_t_loop);
    }
    u2_t_tmpsig &= u2_a_SIGMSK;

    u4_t_vclsts = (U4)0U;
    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)SBLT_VCLSTS_NUM_APP; u4_t_loop++) {
        if ((u2_sp_SBLT_VCLSIG_MSKCFG[u4_t_loop] & u2_t_tmpsig) != (U2)0U) {
            u4_t_vclsts |= ((U4)1U << u4_t_loop);
        }
    }

    return (u4_t_vclsts);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    04/12/2018  HY       New.                                                                                               */
/*  1.0.1    09/19/2018  YI       Fix static analysis comment.                                                                       */
/*  2.0.0    10/08/2020  KK       MET-B_SEAREM-CSTD-1-03-A-C2                                                                        */
/*  2.1.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*  2.1.2    10/25/2021  TK       QAC supported.                                                                                     */
/*  2.1.3    02/28/2024  TH       for 19PFv3.                                                                                        */
/*                                                                                                                                   */
/*  * HY   = Hidefumi Yoshida, Denso                                                                                                 */
/*  * YI   = Yoshiki  Iwata,   Denso                                                                                                 */
/*  * KK   = Kohei Kato,       Denso Techno                                                                                          */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * TK   = Takanori Kuno, Denso Techno                                                                                             */
/*  * TH   = Taisuke Hirakawa, KSE                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
