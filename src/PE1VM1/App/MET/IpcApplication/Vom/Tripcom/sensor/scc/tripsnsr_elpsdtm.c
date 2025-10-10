/* 2.1.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Elapsed time count for Tripcom                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPSNSR_ELPSDTM_C_MAJOR                (2)
#define TRIPSNSR_ELPSDTM_C_MINOR                (1)
#define TRIPSNSR_ELPSDTM_C_PATCH                (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "tripsnsr_cfg_private.h"
#include "tripsnsr_elpsdtm.h"
#include "tripcom_private.h"
#include "tripcom_calc.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((TRIPSNSR_ELPSDTM_C_MAJOR != TRIPSNSR_ELPSDTM_H_MAJOR) || \
     (TRIPSNSR_ELPSDTM_C_MINOR != TRIPSNSR_ELPSDTM_H_MINOR) || \
     (TRIPSNSR_ELPSDTM_C_PATCH != TRIPSNSR_ELPSDTM_H_PATCH))
#error "tripsnsr_elpsdtm.c and tripsnsr_elpsdtm.h : source and header files are inconsistent!"
#endif

#if ((TRIPSNSR_ELPSDTM_C_MAJOR != TRIPSNSR_CFG_H_MAJOR) || \
     (TRIPSNSR_ELPSDTM_C_MINOR != TRIPSNSR_CFG_H_MINOR) || \
     (TRIPSNSR_ELPSDTM_C_PATCH != TRIPSNSR_CFG_H_PATCH))
#error "tripsnsr_elpsdtm.c and tripsnsr_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPSNSR_ELPSDTM_NUM_TYPE               (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct  {
    U4          u4_res;
    U2          u2_cond;
    U1          u1_type;
} ST_TRIPSNSR_ELPSDTM_TYPE;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  U4      u4_sp_tripsnsr_elpsd[TRIPSNSR_ELPSDTM_NUM_TYPE];
static  U2      u2_s_tripsnsr_elpsd_snsrbit;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  const   ST_TRIPSNSR_ELPSDTM_TYPE        st_s_TRIPSNSR_ELPSDTM_TYPE[TRIPSNSR_ELPSDTM_NUM_TYPE] = {
    {   (U4)10000U,   (U2)(TRIPCOM_VEHSTS_DRVCYC                        ), (U1)TRIPCOM_DELTA_DC_ELPSD_10MS },
    {   (U4)1000000U, (U2)(TRIPCOM_VEHSTS_DRVCYC                        ), (U1)TRIPCOM_DELTA_DC_ELPSD_SEC  },
    {   (U4)1000000U, (U2)(TRIPCOM_VEHSTS_DRVCYC | TRIPCOM_VEHSTS_ECOSTP), (U1)TRIPCOM_DELTA_IDS_ELPSD_SEC }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* void            vd_g_TripsnsrElpsdtmInit(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripsnsrElpsdtmInit(void)
{
    U4          u4_t_loop;


    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)TRIPSNSR_ELPSDTM_NUM_TYPE; u4_t_loop++) {
        u4_sp_tripsnsr_elpsd[u4_t_loop] = (U4)0U;
    }
    u2_s_tripsnsr_elpsd_snsrbit = (U2)TRIPCOM_SNSRBIT_ELPSDTM_UNKNOWN;

    vd_g_TripsnsrCfgElpsdtmInit();
}

/*===================================================================================================================================*/
/* void            vd_g_TripsnsrElpsdtmSmplngTask(const U2 u2_a_VEHSYSSTS, const U1 u1_a_PTSSTS)                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripsnsrElpsdtmSmplngTask(const U2 u2_a_VEHSYSSTS, const U1 u1_a_PTSSTS)
{
    U4          u4_t_loop;
    U4          u4_t_frt_dlt;
    U2          u2_t_vcond;


    u4_t_frt_dlt = u4_g_TripsnsrCfgElpsdtmGetDlt();

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)TRIPSNSR_ELPSDTM_NUM_TYPE; u4_t_loop++) {
        u2_t_vcond = st_s_TRIPSNSR_ELPSDTM_TYPE[u4_t_loop].u2_cond;

        u2_s_tripsnsr_elpsd_snsrbit = (U2)0U;
        if ((u1_a_PTSSTS & (U1)TRIPCOM_STSBIT_UNKNOWN) != (U1)0U) {
            u2_s_tripsnsr_elpsd_snsrbit  = (U2)TRIPCOM_SNSRBIT_ELPSDTM_UNKNOWN;
            u4_t_frt_dlt = (U4)0U;
        }
        if ((u1_a_PTSSTS & (U1)TRIPCOM_STSBIT_INVALID) != (U1)0U) {
            u2_s_tripsnsr_elpsd_snsrbit |= (U2)TRIPCOM_SNSRBIT_ELPSDTM_INVALID;
            u4_t_frt_dlt = (U4)0U;
        }

        if ((u2_a_VEHSYSSTS & u2_t_vcond) == u2_t_vcond) {
            u4_sp_tripsnsr_elpsd[u4_t_loop] = u4_g_TripcomCalcAddU4U4(u4_sp_tripsnsr_elpsd[u4_t_loop], u4_t_frt_dlt);
        }
    }
}


/*===================================================================================================================================*/
/* U2              u2_g_TripsnsrElpsdtmGetDelta(U4 * u4_ap_delta)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2              u2_g_TripsnsrElpsdtmGetDelta(U4 * u4_ap_delta)
{
    const ST_TRIPSNSR_ELPSDTM_TYPE *            stp_t_TYPE;
    U4                                          u4_t_loop;
    U4                                          u4_t_mul;


    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)TRIPSNSR_ELPSDTM_NUM_TYPE; u4_t_loop++) {
        stp_t_TYPE = &st_s_TRIPSNSR_ELPSDTM_TYPE[u4_t_loop];

        u4_t_mul                         = u4_g_TripcomCalcMulU4U4(stp_t_TYPE->u4_res, u4_g_TRIPSNSR_ELPSDTM_FRT_1US);
        u4_ap_delta[stp_t_TYPE->u1_type] = u4_sp_tripsnsr_elpsd[u4_t_loop] / u4_t_mul;
        u4_sp_tripsnsr_elpsd[u4_t_loop]  = u4_sp_tripsnsr_elpsd[u4_t_loop] % u4_t_mul;
    }

    return (u2_s_tripsnsr_elpsd_snsrbit);
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
