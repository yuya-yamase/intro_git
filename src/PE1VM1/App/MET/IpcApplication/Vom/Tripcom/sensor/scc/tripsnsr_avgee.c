/* 2.1.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Instantaneous Electric Power used and EV Distance count for Avarage Electric Ecoomy                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPSNSR_AVGEE_C_MAJOR                (2)
#define TRIPSNSR_AVGEE_C_MINOR                (1)
#define TRIPSNSR_AVGEE_C_PATCH                (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "tripsnsr_cfg_private.h"
#include "tripsnsr_avgee.h"
#include "tripcom_private.h"
#include "tripcom_calc.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((TRIPSNSR_AVGEE_C_MAJOR != TRIPSNSR_AVGEE_H_MAJOR) || \
     (TRIPSNSR_AVGEE_C_MINOR != TRIPSNSR_AVGEE_H_MINOR) || \
     (TRIPSNSR_AVGEE_C_PATCH != TRIPSNSR_AVGEE_H_PATCH))
#error "tripsnsr_avgee.c and tripsnsr_avgee.h : source and header files are inconsistent!"
#endif

#if ((TRIPSNSR_AVGEE_C_MAJOR != TRIPSNSR_CFG_H_MAJOR) || \
     (TRIPSNSR_AVGEE_C_MINOR != TRIPSNSR_CFG_H_MINOR) || \
     (TRIPSNSR_AVGEE_C_PATCH != TRIPSNSR_CFG_H_PATCH))
#error "tripsnsr_avgee.c and tripsnsr_cfg_private.h : source and header files are inconsistent!"
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
static  S4      s4_s_tripsnsr_avgee_epusd;
static  U4      u4_s_tripsnsr_avgee_evdist;
static  U1      u1_s_tripsnsr_avgee_updflg_old;
static  U1      u1_s_tripsnsr_avgee_initrx;
static  U2      u2_s_tripsnsr_avgee_snsrbit;

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
/* void            vd_g_TripsnsrAvgeeInit(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripsnsrAvgeeInit(void)
{
    s4_s_tripsnsr_avgee_epusd      = (S4)0;
    u4_s_tripsnsr_avgee_evdist     = (U4)0U;
    u1_s_tripsnsr_avgee_updflg_old = (U1)0U;
    u1_s_tripsnsr_avgee_initrx     = (U1)FALSE;
    u2_s_tripsnsr_avgee_snsrbit    = (U2)TRIPCOM_SNSRBIT_AVGEE_UNKNOWN;
}

/*===================================================================================================================================*/
/* void            vd_g_TripsnsrAvgeeSmplngTask(const U2 u2_a_VEHSYSSTS, const U1 u1_a_PTSSTS)                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripsnsrAvgeeSmplngTask(const U2 u2_a_VEHSYSSTS, const U1 u1_a_PTSSTS)
{
    U1             u1_t_msgsts;
    S4             s4_t_insepusd;
    U1             u1_t_updtflg;
    U4             u4_t_evdist;
    
    
    s4_t_insepusd = (S4)0;
    u1_t_updtflg  = (U1)0U;
    u4_t_evdist   = (U4)0U;
    
    if ((u2_a_VEHSYSSTS & (U2)TRIPCOM_VEHSTS_IGON) != (U2)0U) {

        u1_t_msgsts  = u1_g_TripsnsrCfgGetInsEpusd(&s4_t_insepusd);
        u1_t_msgsts |= u1_g_TripsnsrCfgGetInsUpdtflg(&u1_t_updtflg);
        u1_t_msgsts |= u1_g_TripsnsrCfgGetInsEvdist(&u4_t_evdist);
        
        u2_s_tripsnsr_avgee_snsrbit = (U2)0U;

        if (((u1_t_msgsts & (U1)TRIPCOM_STSBIT_INVALID) != (U1)0U) ||
            ((u1_a_PTSSTS & (U1)TRIPCOM_STSBIT_INVALID) != (U1)0U)) {

            u2_s_tripsnsr_avgee_snsrbit |= (U2)TRIPCOM_SNSRBIT_AVGEE_INVALID;
            s4_t_insepusd = (S4)0;
            u4_t_evdist   = (U4)0U;
            u1_t_updtflg  = u1_s_tripsnsr_avgee_updflg_old;
        }
        if (((u1_t_msgsts & (U1)TRIPCOM_STSBIT_UNKNOWN) != (U1)0U) ||
            ((u1_a_PTSSTS & (U1)TRIPCOM_STSBIT_UNKNOWN) != (U1)0U)) {

            u2_s_tripsnsr_avgee_snsrbit |= (U2)TRIPCOM_SNSRBIT_AVGEE_UNKNOWN;
            s4_t_insepusd = (S4)0;
            u4_t_evdist   = (U4)0U;
            u1_t_updtflg  = u1_s_tripsnsr_avgee_updflg_old;
        }

        if (u2_s_tripsnsr_avgee_snsrbit == (U2)0U) {
            if (u1_s_tripsnsr_avgee_initrx != (U1)TRUE) {

                u1_s_tripsnsr_avgee_updflg_old = u1_t_updtflg;
                u1_s_tripsnsr_avgee_initrx     = (U1)TRUE;
            }
            if (u1_t_updtflg != u1_s_tripsnsr_avgee_updflg_old) {

                u1_s_tripsnsr_avgee_updflg_old = u1_t_updtflg;
                if  ((u2_a_VEHSYSSTS & (U2)TRIPCOM_VEHSTS_DRVCYC) != (U2)0U) {

                    s4_s_tripsnsr_avgee_epusd  += s4_t_insepusd;
                    u4_s_tripsnsr_avgee_evdist = u4_g_TripcomCalcAddU4U4(u4_s_tripsnsr_avgee_evdist, u4_t_evdist);
                }
            }
        }
    }
    else {
        u1_s_tripsnsr_avgee_initrx  = (U1)FALSE;
    }

}

/*===================================================================================================================================*/
/* U2              u2_g_TripsnsrAvgeeGetDelta(U4 * u4_ap_delta)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2              u2_g_TripsnsrAvgeeGetDelta(U4 * u4_ap_delta)
{
    u4_ap_delta[TRIPCOM_DELTA_DC_INSTEPUSD_PC] = (U4)s4_s_tripsnsr_avgee_epusd;
    s4_s_tripsnsr_avgee_epusd = (S4)0;

    u4_ap_delta[TRIPCOM_DELTA_DC_EVRUNDIST_PC] = u4_s_tripsnsr_avgee_evdist;
    u4_s_tripsnsr_avgee_evdist = (U4)0U;

    return (u2_s_tripsnsr_avgee_snsrbit);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    03/18/2020  YA       New.                                                                                               */
/*  1.1.0    03/23/2020  YA       Change for 800B CV                                                                                 */
/*  1.1.1    07/27/2020  YA       Change status to be determined only during IG-ON                                                   */
/*  2.0.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*  2.0.2    10/27/2021  TK       QAC supported.                                                                                     */
/*  2.1.0    04/14/2022  TA(M)    See tripcom.c v2.1.1                                                                               */
/*  2.1.1    08/08/2022  YI       See tripsnsr.c v2.1.1                                                                              */
/*                                                                                                                                   */
/*  * YA   = Yuhei Aoyama, DensoTechno                                                                                               */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * TK   = Takanori Kuno, Denso Techno                                                                                             */
/*  * YI   = Yoshiki Iwata, NTT Data MSE                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
