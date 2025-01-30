/* 1.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Hmitripcom                                                                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HMITRIPCOM_C_MAJOR                         (1)
#define HMITRIPCOM_C_MINOR                         (1)
#define HMITRIPCOM_C_PATCH                         (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "hmiproxy_cfg_private.h"
#include "tripcom.h"
#include "avggrph.h"

#include "hmitripcom.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((HMITRIPCOM_C_MAJOR != HMITRIPCOM_H_MAJOR) || \
     (HMITRIPCOM_C_MINOR != HMITRIPCOM_H_MINOR) || \
     (HMITRIPCOM_C_PATCH != HMITRIPCOM_H_PATCH))
#error "hmitripcom.c and hmitripcom.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HMITRIPCOM_GRPHRSTREQ_BIT                (0x00000003U)
#define HMITRIPCOM_GRPHRSTREQ_LSB                (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2   u2_s_hmitripcom_rstbit;
static U2   u2_s_hmitripcom_grphrst;
static U2   u2_s_hmitripcom_to;

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
/*  void    vd_g_HmiTripcomInit(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiTripcomInit(void)
{
    u2_s_hmitripcom_rstbit  = (U2)0U;
    u2_s_hmitripcom_grphrst = (U2)0U;
    u2_s_hmitripcom_to      = (U2)HMIPROXY_TOC_MAX;
}

/*===================================================================================================================================*/
/*  void    vd_g_HmiTripcomMainTask(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiTripcomMainTask(void)
{
    static const U2 u2_s_HMITRIPCOM_TO = (U2)1000U / (U2)50U;
    U1              u1_t_to;

    u1_t_to = u1_g_HmiProxyToc(&u2_s_hmitripcom_to, u2_s_HMITRIPCOM_TO);

    if(u1_t_to == (U1)FALSE){
        vd_g_TripcomRstRq(u2_s_hmitripcom_rstbit);
        vd_g_TripcomGrphRstRq(u2_s_hmitripcom_grphrst);
    }
    u2_s_hmitripcom_rstbit  = (U2)0U;
    u2_s_hmitripcom_grphrst = (U2)0U;
}

/*===================================================================================================================================*/
/*  void  vd_g_HmiTripcomPut(const ST_HMITRIPCOM * stp_a_HMITRIPCOM)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void  vd_g_HmiTripcomPut(const ST_HMITRIPCOM * stp_a_HMITRIPCOM)
{
    u2_s_hmitripcom_to    = (U2)HMIPROXY_TOC_INI;
    if(stp_a_HMITRIPCOM->u2_avg_vehspd_kmph_ta == (U2)0U){
        u2_s_hmitripcom_rstbit |= (U2)TRIPCOM_RSTRQBIT_M_AVGVEHSPD_TA;          /*  AVG_SPD_KMPH_USRRST                 */
    }
    if(stp_a_HMITRIPCOM->u4_avg_fe_kmpl_ta == (U4)0U){
        u2_s_hmitripcom_rstbit |= (U2)TRIPCOM_RSTRQBIT_M_AVGFEHE_TA;            /*  AVG_FE_KMPL_USRRST                  */
    }
    if(stp_a_HMITRIPCOM->u4_avg_ee_kmpl_ta == (U4)0U){
        u2_s_hmitripcom_rstbit |= (U2)TRIPCOM_RSTRQBIT_M_AVGEE_TA;              /*  AVG_EE_KMPL_USRRST                  */
    }
    if(stp_a_HMITRIPCOM->u4_avg_he_kmpkg_ta == (U4)0U){
        u2_s_hmitripcom_rstbit |= (U2)TRIPCOM_RSTRQBIT_M_AVGFEHE_TA;            /*  AVG_HE_KMPL_USRRST                  */
    }
    if(stp_a_HMITRIPCOM->u4_ptsrun_dist_km_lc == (U4)0U){
        u2_s_hmitripcom_rstbit |= (U2)TRIPCOM_RSTRQBIT_M_PTSRUNDIST_LC;         /*  DIST_KM_USRRST                      */
    }
    if(stp_a_HMITRIPCOM->u4_ptsrun_time_hrs_lc== (U4)0U){
        u2_s_hmitripcom_rstbit |= (U2)TRIPCOM_RSTRQBIT_M_PTSRUNTM_LC;           /* DRVTIME_HHHH_USRRST                  */
                                                                                /* DRVTIME_MM_USRRST                    */
                                                                                /* DRVTIME_SS_USRRST                    */
    }
    if(stp_a_HMITRIPCOM->u4_idlstp_time_hrs_lc == (U4)0U){
        u2_s_hmitripcom_rstbit |= (U2)TRIPCOM_RSTRQBIT_M_ECOSTPTM_LC;           /* IDLSTP_HHHH_USRRST                   */
                                                                                /* IDLSTP_MM_USRRST                     */
                                                                                /* IDLSTP_SS_USRRST                     */
    }
    if(stp_a_HMITRIPCOM->u4_save_fs_ml_lc == (U4)0U){
        u2_s_hmitripcom_rstbit |= (U2)TRIPCOM_RSTRQBIT_M_SAVEFS_LC;             /* FUELSAVE_ML_USRRST                   */
    }
    if(stp_a_HMITRIPCOM->u2_avg_vehspd_tr_a == (U2)0U){
        u2_s_hmitripcom_rstbit |= (U2)TRIPCOM_RSTRQBIT_M_AVGVEHSPD_TR_A;        /* TRIPA_AVG_SPD_KMPH_USRRST            */
    }
    if(stp_a_HMITRIPCOM->u4_ptsruntm_tr_a == (U4)0U){
        u2_s_hmitripcom_rstbit |= (U2)TRIPCOM_RSTRQBIT_M_PTSRUNTM_TR_A;         /* TRIPA_DRVTIME_HHHH_USRRST            */
                                                                                /* TRIPA_DRVTIME_MM_USRRST              */
                                                                                /* TRIPA_DRVTIME_SS_USRRST              */
    }
    if(stp_a_HMITRIPCOM->u4_dist_km_tr_a == (U4)0U){
        u2_s_hmitripcom_rstbit |= (U2)TRIPCOM_RSTRQBIT_M_PTSRUNDIST_TR_A;       /* TRIPA_DIST_KM_USRRST                 */
    }
    if(stp_a_HMITRIPCOM->u2_avg_vehspd_tr_b == (U2)0U){
        u2_s_hmitripcom_rstbit |= (U2)TRIPCOM_RSTRQBIT_M_AVGVEHSPD_TR_B;        /* TRIPB_AVG_SPD_KMPH_USRRST            */
    }
    if(stp_a_HMITRIPCOM->u4_ptsruntm_tr_b == (U4)0U){
        u2_s_hmitripcom_rstbit |= (U2)TRIPCOM_RSTRQBIT_M_PTSRUNTM_TR_B;         /* TRIPB_DRVTIME_HHHH_USRRST            */
                                                                                /* TRIPB_DRVTIME_MM_USRRST              */
                                                                                /* TRIPB_DRVTIME_SS_USRRST              */
    }
    if(stp_a_HMITRIPCOM->u4_dist_km_tr_b == (U4)0U){
        u2_s_hmitripcom_rstbit |= (U2)TRIPCOM_RSTRQBIT_M_PTSRUNDIST_TR_B;       /* TRIPB_DIST_KM_USRRST                 */
    }
}
/*===================================================================================================================================*/
/*  void  vd_g_HmiTripcomGrphPut(const U4 * const u4_ap_GRPHRST)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void  vd_g_HmiTripcomGrphPut(const U4 * const u4_ap_GRPHRST)
{
    U4  u4_t_grphrst;
    U1  u1_t_req;

    u2_s_hmitripcom_to    = (U2)HMIPROXY_TOC_INI;
    if(u4_ap_GRPHRST != vdp_PTR_NA){
        u4_t_grphrst = *u4_ap_GRPHRST;
    }
    else{
        u4_t_grphrst = (U4)0U;
    }

    u1_t_req = (U1)(u4_t_grphrst & (U4)HMITRIPCOM_GRPHRSTREQ_BIT);
    if(u1_t_req == (U1)TRUE){
        u2_s_hmitripcom_grphrst |= (U2)TRIPCOM_RSTRQBIT_M_AVGFEHE_ONEM;         /*  AVG_FE_KMPL_1MIN_HIST_CLR           */
    }
    u4_t_grphrst >>= HMITRIPCOM_GRPHRSTREQ_LSB;
    u1_t_req = (U1)(u4_t_grphrst & (U4)HMITRIPCOM_GRPHRSTREQ_BIT);
    if(u1_t_req == (U1)TRUE){
        u2_s_hmitripcom_grphrst |= (U2)TRIPCOM_RSTRQBIT_M_AVGEE_ONEM;           /*  AVG_EE_KMPL_1MIN_HIST_CLR           */
    }
    u4_t_grphrst >>= HMITRIPCOM_GRPHRSTREQ_LSB;
    u1_t_req = (U1)(u4_t_grphrst & (U4)HMITRIPCOM_GRPHRSTREQ_BIT);
    if(u1_t_req == (U1)TRUE){
        u2_s_hmitripcom_grphrst |= (U2)TRIPCOM_RSTRQBIT_M_AVGFEHE_TA;           /*  AVG_FE_KMPL_USRRST_HIST_CLR         */
    }
    u4_t_grphrst >>= HMITRIPCOM_GRPHRSTREQ_LSB;
    u1_t_req = (U1)(u4_t_grphrst & (U4)HMITRIPCOM_GRPHRSTREQ_BIT);
    if(u1_t_req == (U1)TRUE){
        u2_s_hmitripcom_grphrst |= (U2)TRIPCOM_RSTRQBIT_M_AVGEE_TA;             /*  AVG_EE_KMPL_USRRST_HIST_CLR         */
    }
    u4_t_grphrst >>= HMITRIPCOM_GRPHRSTREQ_LSB;
    u1_t_req = (U1)(u4_t_grphrst & (U4)HMITRIPCOM_GRPHRSTREQ_BIT);
    if(u1_t_req == (U1)TRUE){
        u2_s_hmitripcom_rstbit |= (U2)TRIPCOM_RSTRQBIT_M_AVGFEHE_TA;            /*  AVG_FE_KMPL_USRRST_HIST_UPDT        */
    }
    u4_t_grphrst >>= HMITRIPCOM_GRPHRSTREQ_LSB;
    u1_t_req = (U1)(u4_t_grphrst & (U4)HMITRIPCOM_GRPHRSTREQ_BIT);
    if(u1_t_req == (U1)TRUE){
        u2_s_hmitripcom_rstbit |= (U2)TRIPCOM_RSTRQBIT_M_AVGEE_TA;              /*  AVG_EE_KMPL_USRRST_HIST_UPDT        */
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
/*  1.0.0    07/16/2019  TA       New.                                                                                               */
/*  1.1.0    09/02/2020  TA       See hmiproxy.c                                                                                     */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  130D-1   12/12/2022  YK       Added processing to notify Tripcom of AVG_EE_KMPL_USRRST                                           */
/*  19PFv3-1 01/11/2024  TH       Add AvgGrph                                                                                        */
/*                                                                                                                                   */
/*  * TA   = Teruyuki Anjima, Denso                                                                                                  */
/*  * YK   = Yuta kusunoki, Denso Techno                                                                                             */
/*  * TH   = Taisuke Hirakawa, KSE                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
