/* 2.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Vehicle Power Transmission                                                                                                       */
/*  WCVT-Shift                                                                                                                       */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VPTRAN_CVT_C_MAJOR                      (2)
#define VPTRAN_CVT_C_MINOR                      (1)
#define VPTRAN_CVT_C_PATCH                      (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "vptran_cvt_cfg_private.h"
#include "memfill_u1.h"
#include "memfill_u2.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((VPTRAN_CVT_C_MAJOR != VPTRAN_CVT_H_MAJOR) || \
     (VPTRAN_CVT_C_MINOR != VPTRAN_CVT_H_MINOR) || \
     (VPTRAN_CVT_C_PATCH != VPTRAN_CVT_H_PATCH))
#error "vptran_cvt.c and vptran_cvt.h : source and header files are inconsistent!"
#endif

#if ((VPTRAN_CVT_C_MAJOR != VPTRAN_CVT_CFG_PRIVATE_H_MAJOR) || \
     (VPTRAN_CVT_C_MINOR != VPTRAN_CVT_CFG_PRIVATE_H_MINOR) || \
     (VPTRAN_CVT_C_PATCH != VPTRAN_CVT_CFG_PRIVATE_H_PATCH))
#error "vptran_cvt.c and vptran_cvt_cfg_private.h : source and header files are inconsistent!"
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
static  U2                                      u2_sp_vptran_cvt_val[VPTRAN_NUM_APP];
static  U1                                      u1_s_vptran_cvt_rng_sts;
static  U1                                      u1_s_vptran_cvt_ger_sts;
static  U1                                      u1_s_vptran_cvt_gsi_sts;
static  U1                                      u1_s_vptran_cvt_grs_sts;        /* The signal status of Gear status */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  void    vd_s_VptranCvtGetSgnl(U1 * const u1_ap_signal);
static  void    vd_s_VptranCvtGetStatus(const U4 u4_a_PWRSTS);
static  U2      u2_s_VptranCvtGetSftRng(const U1 u1_a_SIG, const U1 u1_a_TMSIG_STS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define     VPTRAN_CVT_NUM_RNG                  (9U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* void            vd_g_VptranCvtInit(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_VptranCvtInit(void)
{
    vd_g_MemfillU2(&u2_sp_vptran_cvt_val[0], (U2)VPTRAN_OFF, (U4)VPTRAN_NUM_APP);
    u1_s_vptran_cvt_rng_sts   = (U1)VPTRAN_UNKNOWN;
    u1_s_vptran_cvt_ger_sts   = (U1)VPTRAN_UNKNOWN;
    u1_s_vptran_cvt_gsi_sts   = (U1)VPTRAN_UNKNOWN;
    u1_s_vptran_cvt_grs_sts   = (U1)VPTRAN_UNKNOWN;
}

/*===================================================================================================================================*/
/* void            vd_g_VptranCvt(const U4 u4_a_PWRSTS)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_VptranCvt(const U4 u4_a_PWRSTS)
{
    U4                           u4_t_loop;
    U1                           u1_tp_signal[VPTRAN_NUM_APP];

    /*  Signal  */
    vd_g_MemfillU1(&u1_tp_signal[0], (U1)VPTRAN_OFF, (U4)VPTRAN_NUM_APP);

    vd_s_VptranCvtGetStatus(u4_a_PWRSTS);
    vd_s_VptranCvtGetSgnl(&u1_tp_signal[0]);

    /*  Range  */
    u2_sp_vptran_cvt_val[VPTRAN_APP_RNG] = u2_s_VptranCvtGetSftRng(u1_tp_signal[VPTRAN_APP_RNG], u1_s_vptran_cvt_grs_sts);

    /*  Other appl. status */
    for (u4_t_loop = (U4)VPTRAN_APP_GSI; u4_t_loop < (U4)VPTRAN_NUM_APP; u4_t_loop++) {
        u2_sp_vptran_cvt_val[u4_t_loop] = (U2)u1_tp_signal[u4_t_loop];
    }

}

/*===================================================================================================================================*/
/* U1              u1_g_VptranCvtGetSts(const U1 u1_a_APPID, U2 * const u2_ap_value)                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_VptranCvtGetSts(const U1 u1_a_APPID, U2 * const u2_ap_value)
{
    U1      u1_t_status;

    u1_t_status = (U1)VPTRAN_UNKNOWN;
    if((u1_a_APPID   < (U1)VPTRAN_NUM_APP) && 
       (u2_ap_value != vdp_PTR_NA        )){
        (*u2_ap_value) = u2_sp_vptran_cvt_val[u1_a_APPID];
        switch (u1_a_APPID) {
            case (U1)VPTRAN_APP_GSI:
                u1_t_status = u1_s_vptran_cvt_gsi_sts;
                break;
            case (U1)VPTRAN_APP_GR:
                u1_t_status = u1_s_vptran_cvt_ger_sts;
                break;
            default:    /* case VPTRAN_APP_RNG */
                u1_t_status = u1_s_vptran_cvt_rng_sts;
                break;
        }
    }

    return (u1_t_status);
}

/*===================================================================================================================================*/
/* static void     vd_s_VptranCvtGetStatus(const U4 u4_a_PWRSTS)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_VptranCvtGetStatus(const U4 u4_a_PWRSTS)
{
    if ((u4_a_PWRSTS & (U4)VPTRAN_PWRSTSBIT_IGON) != (U4)0U) {
        u1_s_vptran_cvt_rng_sts   = u1_g_VptranCvtCfgGetMsgStsRNG();
        u1_s_vptran_cvt_ger_sts   = u1_g_VptranCvtCfgGetMsgStsGR();
        u1_s_vptran_cvt_gsi_sts   = u1_g_VptranCvtCfgGetMsgStsGSI();
        u1_s_vptran_cvt_grs_sts   = u1_g_VptranCvtCfgGetMsgStsGRSts();
    } else {
        u1_s_vptran_cvt_rng_sts   = (U1)VPTRAN_UNKNOWN;
        u1_s_vptran_cvt_ger_sts   = (U1)VPTRAN_UNKNOWN;
        u1_s_vptran_cvt_gsi_sts   = (U1)VPTRAN_UNKNOWN;
        u1_s_vptran_cvt_grs_sts   = (U1)VPTRAN_UNKNOWN;
    }
}

/*===================================================================================================================================*/
/* static  void    vd_s_VptranCvtGetSgnl(U1 * const u1_ap_signal)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_VptranCvtGetSgnl(U1 * const u1_ap_signal)
{
    static  const  U1     u1_s_RNG_MSK      = (U1)0x0FU;
    static  const  U1     u1_s_GSI_MSK      = (U1)0x03U;
    static  const  U1     u1_s_GSI_SFT      = (U1)1U;
    static  const  U1     u1_s_GEARMET_MSK  = (U1)0x0FU;
    static  const  U1     u1_s_BGEAR_MSK    = (U1)0x0FU;
    static  const  U1     u1_s_SFTSTS_MSK   = (U1)0x03U;
    static  const  U1     u1_s_SFTSTS_SFT   = (U1)4U;

    U1 u1_t_gearmet;
    U1 u1_t_bgear;

    u1_ap_signal[VPTRAN_APP_RNG]    = u1_g_VptranCvtCfgGetSFTMET();
    u1_ap_signal[VPTRAN_APP_RNG]   &= u1_s_RNG_MSK;
    u1_ap_signal[VPTRAN_APP_RNG]   |= (U1)((u1_g_VptranCvtCfgGetSFTBLNK() & u1_s_SFTSTS_MSK) << u1_s_SFTSTS_SFT);

    u1_ap_signal[VPTRAN_APP_GSI]    = u1_g_VptranCvtCfgGetBSILUP();
    u1_ap_signal[VPTRAN_APP_GSI]   |= (U1)(u1_g_VptranCvtCfgGetBSILDN() << u1_s_GSI_SFT);
    u1_ap_signal[VPTRAN_APP_GSI]   &= u1_s_GSI_MSK;

    u1_t_gearmet                    = u1_g_VptranCvtCfgGetGEARMET();
    u1_t_gearmet                   &= u1_s_GEARMET_MSK;
    u1_t_bgear                      = u1_g_VptranCvtCfgGetBGEAR();
    u1_t_bgear                     &= u1_s_BGEAR_MSK;

    if(u1_t_gearmet != (U1)0U){
        u1_ap_signal[VPTRAN_APP_GR] = u1_t_gearmet;
    }else{
        u1_ap_signal[VPTRAN_APP_GR] = u1_t_bgear ;
    }
}

/*===================================================================================================================================*/
/* static  U2      u2_s_VptranCvtGetSftRng(const U1 u1_a_SIG, const U1 u1_a_TMSIG_STS)                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U2      u2_s_VptranCvtGetSftRng(const U1 u1_a_SIG, const U1 u1_a_TMSIG_STS)
{
    static const    U2          u2_sp_SFTMET_TBL[VPTRAN_CVT_NUM_RNG] = {
        (U2)VPTRAN_OFF,         /* SFT_MET = 0000b */
        (U2)VPTRAN_RNG_P_ON,    /* SFT_MET = 0001b */
        (U2)VPTRAN_RNG_R_ON,    /* SFT_MET = 0010b */
        (U2)VPTRAN_RNG_N_ON,    /* SFT_MET = 0011b */
        (U2)VPTRAN_RNG_D_ON,    /* SFT_MET = 0100b */
        (U2)VPTRAN_RNG_B_ON,    /* SFT_MET = 0101b */
        (U2)VPTRAN_RNG_M_ON,    /* SFT_MET = 0110b */
        (U2)VPTRAN_RNG_S_ON,    /* SFT_MET = 0111b */
        (U2)VPTRAN_RNG_SD_ON    /* SFT_MET = 1000b */
                                /* SFT_MET = Other than above: VPTRAN_OFF */
    };
    static const    U1          u1_s_SIG_MSK            = (U1)0x0FU;
    static const    U1          u1_s_STS_MSK            = (U1)0x30U;
    static const    U1          u1_s_STS_CLTENGAGING    = (U1)0x10U;
    static const    U1          u1_s_STS_HOT_TMFLUID    = (U1)0x20U;

    U2      u2_t_rng;
    U1      u1_t_sft;
    U1      u1_t_sftmet;

    u1_t_sftmet = (u1_a_SIG & u1_s_SIG_MSK);
    if (u1_t_sftmet < (U1)VPTRAN_CVT_NUM_RNG) {
        u2_t_rng = u2_sp_SFTMET_TBL[u1_t_sftmet];
    } else {
        u2_t_rng = (U2)VPTRAN_OFF;
    }

    if (u1_a_TMSIG_STS != (U1)0U) {
        u1_t_sft = (U1)0U;
    } else {
        u1_t_sft = u1_a_SIG & u1_s_STS_MSK;
    }
    
    if (u1_t_sft == u1_s_STS_CLTENGAGING) {
        u2_t_rng |= (U2)VPTRAN_STS_CLATCHENGAGE;
    } else if (u1_t_sft == u1_s_STS_HOT_TMFLUID) {
        u2_t_rng |= (U2)VPTRAN_STS_OILWRN;
    } else {
        /* Do Nothing */
    }

    return (u2_t_rng);
}


/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    02/13/2020  KK       New. (MET-D_SFTPOS-CSTD-0-00-A-C0)                                                                 */
/*  2.0.0    10/05/2021  TA(M)    Addition of communication status for GSI(u1_g_VptranCvtCfgGetMsgStsGSI)                            */
/*  2.0.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*  2.1.0    12/19/2023  GM       19PFv3 CV Change                                                                                   */
/*                                                                                                                                   */
/*  * KK   = Kohei Kato,       DENSO TECHNO                                                                                          */
/*  * TA(M)= Teruyuki Anjima,  NTT Data MSE                                                                                          */
/*  * GM   = Glen Monteposo  , DTPH                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/
