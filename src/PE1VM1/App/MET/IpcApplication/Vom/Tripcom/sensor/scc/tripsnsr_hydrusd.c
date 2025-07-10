/* 2.2.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Hydrogen used count for Tripcom                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPSNSR_HYDRUSD_C_MAJOR                (2)
#define TRIPSNSR_HYDRUSD_C_MINOR                (2)
#define TRIPSNSR_HYDRUSD_C_PATCH                (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "tripsnsr_cfg_private.h"
#include "tripsnsr_hydrusd.h"
#include "tripcom_private.h"
#include "tripcom_calc.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((TRIPSNSR_HYDRUSD_C_MAJOR != TRIPSNSR_HYDRUSD_H_MAJOR) || \
     (TRIPSNSR_HYDRUSD_C_MINOR != TRIPSNSR_HYDRUSD_H_MINOR) || \
     (TRIPSNSR_HYDRUSD_C_PATCH != TRIPSNSR_HYDRUSD_H_PATCH))
#error "tripsnsr_hydrusd.c and tripsnsr_hydrusd.h : source and header files are inconsistent!"
#endif

#if ((TRIPSNSR_HYDRUSD_C_MAJOR != TRIPSNSR_CFG_H_MAJOR) || \
     (TRIPSNSR_HYDRUSD_C_MINOR != TRIPSNSR_CFG_H_MINOR) || \
     (TRIPSNSR_HYDRUSD_C_PATCH != TRIPSNSR_CFG_H_PATCH))
#error "tripsnsr_hydrusd.c and tripsnsr_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPSNSR_HYDRUSD_LIMIT                  (0x0000FDE8U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct  {
    U2          u2_cond;
    U1          u1_type;
} ST_TRIPSNSR_HYDRUSD_TYPE;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  U4      u4_s_tripsnsr_hydrusd;
static  U2      u2_s_tripsnsr_hydrusd_snsrbit;
static  U1      u1_s_tripsnsr_hydrusd_rxcnt;
static  U1      u1_s_tripsnsr_hydrusd_rxedg;

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
/* void            vd_g_TripsnsrHydrusdInit(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripsnsrHydrusdInit(void)
{
    u4_s_tripsnsr_hydrusd         = (U4)0U;
    u2_s_tripsnsr_hydrusd_snsrbit = (U2)TRIPCOM_SNSRBIT_HYDRUSD_UNKNOWN;
    (void)u1_g_TripsnsrCfgRxCntCNSMH2(&u1_s_tripsnsr_hydrusd_rxcnt);
    u1_s_tripsnsr_hydrusd_rxedg   = (U1)FALSE;
}

/*===================================================================================================================================*/
/* void            vd_g_TripsnsrHydrusdSmplngTask(const U2 u2_a_VEHSYSSTS, const U1 u1_a_PTSSTS)                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripsnsrHydrusdSmplngTask(const U2 u2_a_VEHSYSSTS, const U1 u1_a_PTSSTS)
{
    U4          u4_t_hydr_dlt;
    U1          u1_t_msgsts;
    U1          u1_t_cnsmh;


    u1_s_tripsnsr_hydrusd_rxedg = (U1)FALSE;
    
    if ((u2_a_VEHSYSSTS & (U2)TRIPCOM_VEHSTS_IGON) != (U2)0U) {
        u1_t_msgsts = u1_g_TripsnsrCfgRxCntCNSMH2(&u1_t_cnsmh);
        if (u1_t_msgsts == (U1)TRIPCOM_STSBIT_VALID) {
            if (u1_s_tripsnsr_hydrusd_rxcnt != u1_t_cnsmh) {
                u1_s_tripsnsr_hydrusd_rxedg = (U1)TRUE;
            }
            u1_s_tripsnsr_hydrusd_rxcnt = u1_t_cnsmh;
        }

        u1_t_msgsts = u1_g_TripsnsrCfgGetCNSMH2(&u4_t_hydr_dlt);

        u2_s_tripsnsr_hydrusd_snsrbit = (U2)0U;
        if (((u1_t_msgsts & (U1)TRIPCOM_STSBIT_UNKNOWN) != (U1)0U) ||
            ((u1_a_PTSSTS & (U1)TRIPCOM_STSBIT_UNKNOWN) != (U1)0U)) {

            u2_s_tripsnsr_hydrusd_snsrbit  = (U2)TRIPCOM_SNSRBIT_HYDRUSD_UNKNOWN;
            u4_t_hydr_dlt = (U4)0U;
        }
        if (((u1_t_msgsts & (U1)TRIPCOM_STSBIT_INVALID) != (U1)0U) ||
            ((u1_a_PTSSTS & (U1)TRIPCOM_STSBIT_INVALID) != (U1)0U) ||
            (u4_t_hydr_dlt > (U4)TRIPSNSR_HYDRUSD_LIMIT          )) {

            u2_s_tripsnsr_hydrusd_snsrbit |= (U2)TRIPCOM_SNSRBIT_HYDRUSD_INVALID;
            u4_t_hydr_dlt = (U4)0U;
        }
        if (u1_s_tripsnsr_hydrusd_rxedg != (U1)TRUE) {
            u4_t_hydr_dlt = (U4)0U;
        }

        if ((u2_a_VEHSYSSTS & (U2)TRIPCOM_VEHSTS_DRVCYC) != (U2)0U) {
            u4_s_tripsnsr_hydrusd = u4_g_TripcomCalcAddU4U4(u4_s_tripsnsr_hydrusd, u4_t_hydr_dlt);
        }
    }
}

/*===================================================================================================================================*/
/* U2              u2_g_TripsnsrHydrusdGetDelta(U4 * u4_ap_delta)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2              u2_g_TripsnsrHydrusdGetDelta(U4 * u4_ap_delta)
{
    u4_ap_delta[TRIPCOM_DELTA_DC_HYDRUSD_PC] = u4_s_tripsnsr_hydrusd;
    u4_s_tripsnsr_hydrusd                    = (U4)0U;

    return (u2_s_tripsnsr_hydrusd_snsrbit);
}

/*===================================================================================================================================*/
/* U1              u1_g_TripsnsrFuelusdRxReset(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_TripsnsrHydrusdRxReset(void)
{
    return (u1_s_tripsnsr_hydrusd_rxedg);
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
