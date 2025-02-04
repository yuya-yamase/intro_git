/* 2.1.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  ODO sensor count for Tripcom                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPSNSR_ODOCNT_C_MAJOR                 (2)
#define TRIPSNSR_ODOCNT_C_MINOR                 (1)
#define TRIPSNSR_ODOCNT_C_PATCH                 (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "tripcom_cfg_private.h"
#include "tripsnsr_cfg_private.h"
#include "tripsnsr_odocnt.h"
#include "tripcom_private.h"
#include "tripcom_calc.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((TRIPSNSR_ODOCNT_C_MAJOR != TRIPSNSR_ODOCNT_H_MAJOR) || \
     (TRIPSNSR_ODOCNT_C_MINOR != TRIPSNSR_ODOCNT_H_MINOR) || \
     (TRIPSNSR_ODOCNT_C_PATCH != TRIPSNSR_ODOCNT_H_PATCH))
#error "tripsnsr_odocnt.c and tripsnsr_odocnt.h : source and header files are inconsistent!"
#endif

#if ((TRIPSNSR_ODOCNT_C_MAJOR != TRIPSNSR_CFG_H_MAJOR) || \
     (TRIPSNSR_ODOCNT_C_MINOR != TRIPSNSR_CFG_H_MINOR) || \
     (TRIPSNSR_ODOCNT_C_PATCH != TRIPSNSR_CFG_H_PATCH))
#error "tripsnsr_odocnt.c and tripsnsr_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPSNSR_ODOCNT_NUM_TYPE                (5U)
#define TRIPSNSR_ODOCNT_TYPE_DC_PC              (0U)
#define TRIPSNSR_ODOCNT_TYPE_DC_KM              (1U)
#define TRIPSNSR_ODOCNT_TYPE_ANY_PC             (2U)
#define TRIPSNSR_ODOCNT_TYPE_EV_PC              (3U)
#define TRIPSNSR_ODOCNT_TYPE_DC_W_EMGF_PC       (4U)

#define TRIPSNSR_ODOCNT_M_PER_KM                (1000U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  U4      u4_sp_tripsnsr_odocnt[TRIPSNSR_ODOCNT_NUM_TYPE];
static  U2      u2_s_tripsnsr_odocnt_snsrbit;
static  U4      u4_s_tripsnsr_odo_inst;
static  U4      u4_s_tripsnsr_odocnt_dlt_any;
static  U4      u4_s_tripsnsr_odocnt_dlt_ev;
static  U1      u1_s_tripsnsr_odo_stsbit;
static  U2      u2_s_tripsnsr_odocnt_w_emgf_snsrbit;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void     vd_s_TripsnsrOdocntEMGFSmplngTask(const U2 u2_a_VEHSYSSTS, const U1 u1_a_PTSSTS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* void            vd_g_TripsnsrOdocntInit(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripsnsrOdocntInit(void)
{
    U4          u4_t_loop;


    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)TRIPSNSR_ODOCNT_NUM_TYPE; u4_t_loop++) {
        u4_sp_tripsnsr_odocnt[u4_t_loop] = (U4)0U;
    }
    u2_s_tripsnsr_odocnt_snsrbit = (U2)TRIPCOM_SNSRBIT_ODOCNT_UNKNOWN;
    u4_s_tripsnsr_odo_inst       = (U4)0U;
    u4_s_tripsnsr_odocnt_dlt_any = (U4)0U;
    u4_s_tripsnsr_odocnt_dlt_ev  = (U4)0U;
    u1_s_tripsnsr_odo_stsbit     = (U1)TRIPCOM_STSBIT_UNKNOWN;
    u2_s_tripsnsr_odocnt_w_emgf_snsrbit = (U2)TRIPCOM_SNSRBIT_DTEED_ODOCNT_UNKNOWN;
}

/*===================================================================================================================================*/
/* void            vd_g_TripsnsrOdocntSmplngTask(const U2 u2_a_VEHSYSSTS, const U1 u1_a_PTSSTS)                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripsnsrOdocntSmplngTask(const U2 u2_a_VEHSYSSTS, const U1 u1_a_PTSSTS)
{
    U4          u4_t_odocount_mul;
    U4          u4_t_odo_inst;

    u4_t_odo_inst = u4_s_tripsnsr_odo_inst;
    if ((u2_a_VEHSYSSTS & (U2)TRIPCOM_VEHSTS_IGON) != (U2)0U) {
        u2_s_tripsnsr_odocnt_snsrbit = (U2)0U;
        if (((u1_s_tripsnsr_odo_stsbit & (U1)TRIPCOM_STSBIT_UNKNOWN) != (U1)0U) ||
            ((u1_a_PTSSTS              & (U1)TRIPCOM_STSBIT_UNKNOWN) != (U1)0U)) {

            u2_s_tripsnsr_odocnt_snsrbit = (U2)TRIPCOM_SNSRBIT_ODOCNT_UNKNOWN;
            u4_t_odo_inst       = (U4)0U;
        }
        if (((u1_s_tripsnsr_odo_stsbit & (U1)TRIPCOM_STSBIT_INVALID) != (U1)0U) ||
            ((u1_a_PTSSTS              & (U1)TRIPCOM_STSBIT_INVALID) != (U1)0U)) {

            u2_s_tripsnsr_odocnt_snsrbit |= (U2)TRIPCOM_SNSRBIT_ODOCNT_INVALID;
            u4_t_odo_inst        = (U4)0U;
        }

        if ((u2_a_VEHSYSSTS & (U2)TRIPCOM_VEHSTS_DRVCYC) != (U2)0U) {
            u4_sp_tripsnsr_odocnt[TRIPSNSR_ODOCNT_TYPE_DC_PC]  = u4_g_TripcomCalcAddU4U4(u4_sp_tripsnsr_odocnt[TRIPSNSR_ODOCNT_TYPE_DC_PC],  u4_t_odo_inst              );
            u4_t_odocount_mul                                  = u4_g_TripcomCalcMulU4U4(u4_t_odo_inst,                                     (U4)TRIPSNSR_ODOCNT_M_PER_KM);
            u4_sp_tripsnsr_odocnt[TRIPSNSR_ODOCNT_TYPE_DC_KM]  = u4_g_TripcomCalcAddU4U4(u4_sp_tripsnsr_odocnt[TRIPSNSR_ODOCNT_TYPE_DC_KM],  u4_t_odocount_mul          );
            u4_sp_tripsnsr_odocnt[TRIPSNSR_ODOCNT_TYPE_ANY_PC] = u4_g_TripcomCalcAddU4U4(u4_sp_tripsnsr_odocnt[TRIPSNSR_ODOCNT_TYPE_ANY_PC], u4_t_odo_inst              );
            u4_sp_tripsnsr_odocnt[TRIPSNSR_ODOCNT_TYPE_EV_PC]  = u4_g_TripcomCalcAddU4U4(u4_sp_tripsnsr_odocnt[TRIPSNSR_ODOCNT_TYPE_EV_PC],  u4_t_odo_inst              );
        }
        vd_s_TripsnsrOdocntEMGFSmplngTask(u2_a_VEHSYSSTS, u1_a_PTSSTS);
    }
    else {
        u4_s_tripsnsr_odo_inst = (U4)0U;
    }
}
/*===================================================================================================================================*/
/* static void     vd_s_TripsnsrOdocntEMGFSmplngTask(const U2 u2_a_VEHSYSSTS, const U1 u1_a_PTSSTS)                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_TripsnsrOdocntEMGFSmplngTask(const U2 u2_a_VEHSYSSTS, const U1 u1_a_PTSSTS)
{
    U1          u1_t_emgf;
    U1          u1_t_msgsts;
    U4          u4_t_odo_inst;

    u1_t_emgf   = (U1)0U;
    u1_t_msgsts = u1_g_TripcomCfgGetEMGF(&u1_t_emgf);
    u2_s_tripsnsr_odocnt_w_emgf_snsrbit = (U2)0U;

    u4_t_odo_inst = u4_s_tripsnsr_odo_inst;
    if (((u1_s_tripsnsr_odo_stsbit & (U1)TRIPCOM_STSBIT_UNKNOWN) != (U1)0U) ||
        ((u1_a_PTSSTS              & (U1)TRIPCOM_STSBIT_UNKNOWN) != (U1)0U) ||
        ((u1_t_msgsts              & (U1)TRIPCOM_STSBIT_UNKNOWN) != (U1)0U)) {

        u2_s_tripsnsr_odocnt_w_emgf_snsrbit = (U2)TRIPCOM_SNSRBIT_DTEED_ODOCNT_UNKNOWN;
        u4_t_odo_inst       = (U4)0U;
    }
    if (((u1_s_tripsnsr_odo_stsbit & (U1)TRIPCOM_STSBIT_INVALID) != (U1)0U) ||
        ((u1_a_PTSSTS              & (U1)TRIPCOM_STSBIT_INVALID) != (U1)0U) ||
        ((u1_t_msgsts              & (U1)TRIPCOM_STSBIT_INVALID) != (U1)0U)) {

        u2_s_tripsnsr_odocnt_w_emgf_snsrbit |= (U2)TRIPCOM_SNSRBIT_DTEED_ODOCNT_INVALID;
        u4_t_odo_inst        = (U4)0U;
    }

    if (((u2_a_VEHSYSSTS & (U2)TRIPCOM_VEHSTS_DRVCYC) != (U2)0U) ||
        (u1_t_emgf                                    == (U1)1U)){
        u4_sp_tripsnsr_odocnt[TRIPSNSR_ODOCNT_TYPE_DC_W_EMGF_PC]  = u4_g_TripcomCalcAddU4U4(u4_sp_tripsnsr_odocnt[TRIPSNSR_ODOCNT_TYPE_DC_W_EMGF_PC],  u4_t_odo_inst      );
    }

}

/*===================================================================================================================================*/
/* U2              u2_g_TripsnsrOdocntGetDelta(U4 * u4_ap_delta)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2              u2_g_TripsnsrOdocntGetDelta(U4 * u4_ap_delta)
{
    u4_ap_delta[TRIPCOM_DELTA_DC_ODOCNT_PC]           = u4_sp_tripsnsr_odocnt[TRIPSNSR_ODOCNT_TYPE_DC_PC];
    u4_sp_tripsnsr_odocnt[TRIPSNSR_ODOCNT_TYPE_DC_PC] = (U4)0U;

    u4_ap_delta[TRIPCOM_DELTA_DC_ODOCNT_KM]           = u4_sp_tripsnsr_odocnt[TRIPSNSR_ODOCNT_TYPE_DC_KM] / (U4)TRIPCOM_ODOCNT_PC_PER_KM;
    u4_sp_tripsnsr_odocnt[TRIPSNSR_ODOCNT_TYPE_DC_KM] = u4_sp_tripsnsr_odocnt[TRIPSNSR_ODOCNT_TYPE_DC_KM] % (U4)TRIPCOM_ODOCNT_PC_PER_KM;

    u4_ap_delta[TRIPCOM_DELTA_ANY_ODOCNT_PC]          = u4_s_tripsnsr_odocnt_dlt_any;
    u4_s_tripsnsr_odocnt_dlt_any                      = (U4)0U;

    u4_ap_delta[TRIPCOM_DELTA_EV_ODOCNT_PC]           = u4_s_tripsnsr_odocnt_dlt_ev;
    u4_s_tripsnsr_odocnt_dlt_ev                       = (U4)0U;

    return (u2_s_tripsnsr_odocnt_snsrbit);
}
/*===================================================================================================================================*/
/* U2              u2_g_TripsnsrOdocntEmgfGetDelta(U4 * u4_ap_delta)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2              u2_g_TripsnsrOdocntEmgfGetDelta(U4 * u4_ap_delta)
{
    u4_ap_delta[TRIPCOM_DELTA_DC_ODOCNT_W_EMGF_PC]           = u4_sp_tripsnsr_odocnt[TRIPSNSR_ODOCNT_TYPE_DC_W_EMGF_PC];
    u4_sp_tripsnsr_odocnt[TRIPSNSR_ODOCNT_TYPE_DC_W_EMGF_PC] = (U4)0U;

    return ((U2)0U);/* u2_s_tripsnsr_odocnt_w_emgf_snsrbit is notified by u2_g_TripsnsrOdocntEmgfSts */
}
/*===================================================================================================================================*/
/* U2              u2_g_TripsnsrOdocntEmgfSts(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2              u2_g_TripsnsrOdocntEmgfSts(void)
{
    return(u2_s_tripsnsr_odocnt_w_emgf_snsrbit);
}
/*===================================================================================================================================*/
/* void            vd_g_TripsnsrOdocntSnpshtDelta(const U1 u1_a_RESETBIT)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripsnsrOdocntSnpshtDelta(const U1 u1_a_RESETBIT)
{
    if ((u1_a_RESETBIT & (U1)TRIPCOM_INSTFEHE_UPD) != (U1)0U) {
        u4_s_tripsnsr_odocnt_dlt_any                       = u4_sp_tripsnsr_odocnt[TRIPSNSR_ODOCNT_TYPE_ANY_PC];
        u4_sp_tripsnsr_odocnt[TRIPSNSR_ODOCNT_TYPE_ANY_PC] = (U4)0U;
    }
    
    if ((u1_a_RESETBIT & (U1)TRIPCOM_INSTEE_UPD) != (U1)0U) {
        u4_s_tripsnsr_odocnt_dlt_ev                       = u4_sp_tripsnsr_odocnt[TRIPSNSR_ODOCNT_TYPE_EV_PC];
        u4_sp_tripsnsr_odocnt[TRIPSNSR_ODOCNT_TYPE_EV_PC] = (U4)0U;
    }
}

/*===================================================================================================================================*/
/* void            vd_g_TripsnsrGetOdoInst(const U4 u4_a_ODO_INST, const U1 u1_a_STSBIT)                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripsnsrGetOdoInst(const U4 u4_a_ODO_INST, const U1 u1_a_STSBIT)
{
    u4_s_tripsnsr_odo_inst   = u4_a_ODO_INST;
    u1_s_tripsnsr_odo_stsbit = u1_a_STSBIT;
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
