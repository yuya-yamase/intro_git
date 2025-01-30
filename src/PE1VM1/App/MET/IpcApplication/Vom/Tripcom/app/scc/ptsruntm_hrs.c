/* 2.0.3 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Powertrain Run Hours for Trip Computer                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define PTSRUNTM_HRS_C_MAJOR                    (2)
#define PTSRUNTM_HRS_C_MINOR                    (0)
#define PTSRUNTM_HRS_C_PATCH                    (3)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "ptsruntm_hrs_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((PTSRUNTM_HRS_C_MAJOR != PTSRUNTM_HRS_H_MAJOR) || \
     (PTSRUNTM_HRS_C_MINOR != PTSRUNTM_HRS_H_MINOR) || \
     (PTSRUNTM_HRS_C_PATCH != PTSRUNTM_HRS_H_PATCH))
#error "ptsruntm_hrs.c and ptsruntm_hrs.h : source and header files are inconsistent!"
#endif

#if ((PTSRUNTM_HRS_C_MAJOR != PTSRUNTM_HRS_CFG_H_MAJOR) || \
     (PTSRUNTM_HRS_C_MINOR != PTSRUNTM_HRS_CFG_H_MINOR) || \
     (PTSRUNTM_HRS_C_PATCH != PTSRUNTM_HRS_CFG_H_PATCH))
#error "ptsruntm_hrs.c and ptsruntm_hrs_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define PTSRUNTM_HRS_CANTX_MAX                  (0x176FU)
#define PTSRUNTM_HRS_99H59M59S                  (359999U)   /* 99:59 = 5999[min] * 60 + 59[sec] = 359999[sec]   */
#define PTSRUNTM_HRS_ROLL_OFST                  (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct {
    U1                                          u1_initupdt;
    U1                                          u1_status;
} ST_PTSRUNTM_VAR;

typedef struct {
    U2                                          u2_manualreset;         /* see tripcom.h                                             */
    U2                                          u2_autoreset;           /* see tripcom.h                                             */
    U2                                          u2_unknownvsts;
    U2                                          u2_invalidvsts;
    U1                                          u1_srcch;               /* see tripcom.h                                             */
    U4                                          u4_max;
    U1                                          u1_isrollcnt;
    U1                                          u1_ms_ptsruntm_id;      /* see tripcom_ms.h                                          */
} ST_PTSRUNTM_CNTT;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  ST_PTSRUNTM_VAR                         st_sp_ptsruntm_var[PTSRUNTM_NUM_CNTTS];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void      vd_s_PtsRunTmHandleOvrf(const U4 u4_a_MAX, const U1 u1_a_ROLLCNT, const U4 u4_a_DELTA, U4 * u4_ap_elpsdtm);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_PTSRUNTM_CNTT                   st_sp_PTSRUNTM_CNTTS_CFG[PTSRUNTM_NUM_CNTTS]        = {
    /*  #define PTSRUNTM_CNTT_LC                        (0)         */
    {
        (U2)TRIPCOM_RSTRQBIT_M_PTSRUNTM_LC, /* u2_manualreset     */
        (U2)0U,                             /* u2_autoreset       */
        (U2)0U,                             /* u2_unknownvsts     */
        (U2)0U,                             /* u2_invalidvsts     */
        (U1)TRIPCOM_DELTA_DC_ELPSD_SEC,     /* u1_srcch           */
        (U4)PTSRUNTM_HRS_99H59M59S,         /* u4_max             */
        (U1)TRUE,                           /* u1_isrollcnt       */

        (U1)TRIPCOM_MS_ID_PTSRUNTM_LC_ET    /* u1_ms_ptsruntm_id  */
    },
    /*  #define PTSRUNTM_CNTT_DC                        (1)         */
    {
        (U2)0U,                             /* u2_manualreset     */
        (U2)TRIPCOM_RSTRQBIT_A_DRVCYC,      /* u2_autoreset       */
        (U2)0U,                             /* u2_unknownvsts     */
        (U2)0U,                             /* u2_invalidvsts     */
        (U1)TRIPCOM_DELTA_DC_ELPSD_SEC,     /* u1_srcch           */
        (U4)PTSRUNTM_HRS_99H59M59S,         /* u4_max             */
        (U1)TRUE,                           /* u1_isrollcnt       */

        (U1)TRIPCOM_MS_ID_PTSRUNTM_DC_ET    /* u1_ms_ptsruntm_id  */
    },
    /*  #define PTSRUNTM_CNTT_TR_A                      (2U)        */
    {
        (U2)TRIPCOM_RSTRQBIT_M_PTSRUNTM_TR_A,/* u2_manualreset     */
        (U2)0U,                             /* u2_autoreset       */
        (U2)0U,                             /* u2_unknownvsts     */
        (U2)0U,                             /* u2_invalidvsts     */
        (U1)TRIPCOM_DELTA_DC_ELPSD_SEC,     /* u1_srcch           */
        (U4)PTSRUNTM_HRS_99H59M59S,         /* u4_max             */
        (U1)TRUE,                           /* u1_isrollcnt       */

        (U1)TRIPCOM_MS_ID_PTSRUNTM_TR_A_ET  /* u1_ms_ptsruntm_id  */
    },
    /*  #define PTSRUNTM_CNTT_TR_B                      (3U)        */
    {
        (U2)TRIPCOM_RSTRQBIT_M_PTSRUNTM_TR_B,/* u2_manualreset     */
        (U2)0U,                             /* u2_autoreset       */
        (U2)0U,                             /* u2_unknownvsts     */
        (U2)0U,                             /* u2_invalidvsts     */
        (U1)TRIPCOM_DELTA_DC_ELPSD_SEC,     /* u1_srcch           */
        (U4)PTSRUNTM_HRS_99H59M59S,         /* u4_max             */
        (U1)TRUE,                           /* u1_isrollcnt       */

        (U1)TRIPCOM_MS_ID_PTSRUNTM_TR_B_ET  /* u1_ms_ptsruntm_id  */
    },
    /*  #define ECOSTPTM_CNTT_LC                        (2)         */
    {
        (U2)TRIPCOM_RSTRQBIT_M_ECOSTPTM_LC, /* u2_manualreset     */
        (U2)0U,                             /* u2_autoreset       */
        (U2)TRIPCOM_VEHSTS_ECORUNUNK,       /* u2_unknownvsts     */
        (U2)TRIPCOM_VEHSTS_ECORUNINV,       /* u2_invalidvsts     */
        (U1)TRIPCOM_DELTA_IDS_ELPSD_SEC,    /* u1_srcch           */
        (U4)PTSRUNTM_HRS_99H59M59S,         /* u4_max             */
        (U1)FALSE,                          /* u1_isrollcnt       */

        (U1)TRIPCOM_MS_ID_ECOSTPTM_LC_ET    /* u1_ms_ptsruntm_id  */
    },
    /*  #define ECOSTPTM_CNTT_DC                        (3)         */
    {
        (U2)0U,                             /* u2_manualreset     */
        (U2)TRIPCOM_RSTRQBIT_A_DRVCYC,      /* u2_autoreset       */
        (U2)TRIPCOM_VEHSTS_ECORUNUNK,       /* u2_unknownvsts     */
        (U2)TRIPCOM_VEHSTS_ECORUNINV,       /* u2_invalidvsts     */
        (U1)TRIPCOM_DELTA_IDS_ELPSD_SEC,    /* u1_srcch           */
        (U4)PTSRUNTM_HRS_99H59M59S,         /* u4_max             */
        (U1)FALSE,                          /* u1_isrollcnt       */

        (U1)TRIPCOM_MS_ID_ECOSTPTM_DC_ET    /* u1_ms_ptsruntm_id  */
    },
    /*  #define ECOSTPTM_CNTT_ST                        (4)         */
    {
        (U2)0U,                             /* u2_manualreset     */
        (U2)TRIPCOM_RSTRQBIT_A_ECOSTP,      /* u2_autoreset       */
        (U2)TRIPCOM_VEHSTS_ECORUNUNK,       /* u2_unknownvsts     */
        (U2)TRIPCOM_VEHSTS_ECORUNINV,       /* u2_invalidvsts     */
        (U1)TRIPCOM_DELTA_IDS_ELPSD_SEC,    /* u1_srcch           */
        (U4)PTSRUNTM_HRS_99H59M59S,         /* u4_max             */
        (U1)TRUE,                           /* u1_isrollcnt       */

        (U1)TRIPCOM_MS_ID_ECOSTPTM_ST_ET    /* u1_ms_ptsruntm_id  */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* void            vd_g_PtsRunTmInit(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_PtsRunTmInit(void)
{
    U4          u4_t_loop;


    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)PTSRUNTM_NUM_CNTTS; u4_t_loop++) {
        st_sp_ptsruntm_var[u4_t_loop].u1_initupdt = (U1)FALSE;
        st_sp_ptsruntm_var[u4_t_loop].u1_status   = (U1)TRIPCOM_STSBIT_UNKNOWN;
    }
}

/*===================================================================================================================================*/
/* void            vd_g_PtsRunTmCondChk(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD)                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_PtsRunTmCondChk(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD)
{
    const ST_PTSRUNTM_CNTT *                    stp_t_CNTT;
    ST_PTSRUNTM_VAR *                           stp_t_var;
    U2                                          u2_t_jdgbit;


    if (u1_a_CNTTID < (U1)PTSRUNTM_NUM_CNTTS) {
        stp_t_CNTT = &st_sp_PTSRUNTM_CNTTS_CFG[u1_a_CNTTID];
        stp_t_var  = &st_sp_ptsruntm_var[u1_a_CNTTID];

        stp_t_var->u1_status = (U1)TRIPCOM_STSBIT_VALID;
        u2_t_jdgbit  =  u2_ap_STSFIELD[TRIPCOM_STSFIELD_VSTS] & stp_t_CNTT->u2_unknownvsts;
        u2_t_jdgbit |= (u2_ap_STSFIELD[TRIPCOM_STSFIELD_SNSR] & (U2)TRIPCOM_SNSRBIT_ELPSDTM_UNKNOWN);
        if (u2_t_jdgbit != (U2)0U) {
            stp_t_var->u1_status |= (U1)TRIPCOM_STSBIT_UNKNOWN;
        }
        u2_t_jdgbit  =  u2_ap_STSFIELD[TRIPCOM_STSFIELD_VSTS] & stp_t_CNTT->u2_invalidvsts;
        u2_t_jdgbit |= (u2_ap_STSFIELD[TRIPCOM_STSFIELD_SNSR] & (U2)TRIPCOM_SNSRBIT_ELPSDTM_INVALID);
        if (u2_t_jdgbit != (U2)0U) {
            stp_t_var->u1_status |= (U1)TRIPCOM_STSBIT_INVALID;
        }
    }
}

/*===================================================================================================================================*/
/* U1              u1_g_PtsRunTmCalcTrnst(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD)                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_PtsRunTmCalcTrnst(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD)
{
    const ST_PTSRUNTM_CNTT *                    stp_t_CNTT;
    ST_PTSRUNTM_VAR *                           stp_t_var;
    U2                                          u2_t_jdgbit;


    if (u1_a_CNTTID < (U1)PTSRUNTM_NUM_CNTTS) {
        stp_t_CNTT = &st_sp_PTSRUNTM_CNTTS_CFG[u1_a_CNTTID];
        stp_t_var  = &st_sp_ptsruntm_var[u1_a_CNTTID];

        stp_t_var->u1_initupdt = (U1)FALSE;
        
        u2_t_jdgbit  = u2_ap_STSFIELD[TRIPCOM_STSFIELD_AUTO_RSTRQ] & stp_t_CNTT->u2_autoreset;
    	u2_t_jdgbit |= (u2_ap_STSFIELD[TRIPCOM_STSFIELD_MANUAL_RSTRQ] & stp_t_CNTT->u2_manualreset);
        
        if (u2_t_jdgbit != (U2)0U) {
            stp_t_var->u1_initupdt = (U1)TRUE;
        }
    }

    return ((U1)FALSE);
}

/*===================================================================================================================================*/
/* void            vd_g_PtsRunTmAccmlt(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD, const U4 * u4_ap_DELTA)                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_PtsRunTmAccmlt(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD, const U4 * u4_ap_DELTA)
{
    const ST_PTSRUNTM_CNTT *                    stp_t_CNTT;
    ST_PTSRUNTM_VAR *                           stp_t_var;
    U4                                          u4_t_elpsdtm;
    U1                                          u1_t_ovf;


    if (u1_a_CNTTID < (U1)PTSRUNTM_NUM_CNTTS) {
        stp_t_CNTT = &st_sp_PTSRUNTM_CNTTS_CFG[u1_a_CNTTID];
        stp_t_var  = &st_sp_ptsruntm_var[u1_a_CNTTID];

        if (stp_t_var->u1_initupdt == (U1)TRUE) {
            vd_g_TripcomMsSetAccmltVal(stp_t_CNTT->u1_ms_ptsruntm_id, (U4)0U);
        }
        else if (stp_t_var->u1_status == (U1)TRIPCOM_STSBIT_VALID) {
            u4_t_elpsdtm = u4_g_TripcomMsGetAccmltVal(stp_t_CNTT->u1_ms_ptsruntm_id);

            u1_t_ovf = u1_g_TripcomOvrfChk(u4_t_elpsdtm, u4_ap_DELTA[stp_t_CNTT->u1_srcch], stp_t_CNTT->u4_max);
            if (u1_t_ovf == (U1)TRUE) {
                vd_s_PtsRunTmHandleOvrf(stp_t_CNTT->u4_max, stp_t_CNTT->u1_isrollcnt, u4_ap_DELTA[stp_t_CNTT->u1_srcch], &u4_t_elpsdtm);
            }
            else {
                u4_t_elpsdtm += u4_ap_DELTA[stp_t_CNTT->u1_srcch];
                /* u1_g_TripcomOvrfChk() verified not to exceed U4_MAX.         */
            }

            vd_g_TripcomMsSetAccmltVal(stp_t_CNTT->u1_ms_ptsruntm_id, u4_t_elpsdtm);
        }
        else {
            /* Do Nothing */
        }
    }
}

/*===================================================================================================================================*/
/* U1              u1_g_PtsRunTmHrs(const U1 u1_a_PTSRUN_TM_CH, U4 * u4p_a_hhmmss)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_PtsRunTmHrs(const U1 u1_a_PTSRUN_TM_CH, U4 * u4p_a_hhmmss)
{
    U1          u1_t_status;
    U4          u4_t_second;


    u1_t_status = (U1)TRIPCOM_STSBIT_INVALID;
    if (u1_a_PTSRUN_TM_CH < (U1)PTSRUNTM_NUM_CNTTS) {
        u4_t_second = u4_g_TripcomMsGetAccmltVal(st_sp_PTSRUNTM_CNTTS_CFG[u1_a_PTSRUN_TM_CH].u1_ms_ptsruntm_id);
        if (u4p_a_hhmmss != vdp_PTR_NA) {
            (*u4p_a_hhmmss) = u4_g_SecondsToHhmmss(u4_t_second);
        }
        u1_t_status = st_sp_ptsruntm_var[u1_a_PTSRUN_TM_CH].u1_status;
    }

    return (u1_t_status);
}

/*===================================================================================================================================*/
/* U2              u2_g_PtsRunTmCalcTx(const U1 u1_a_CNTTID, const U1 u1_a_UNIT)                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2              u2_g_PtsRunTmCalcTx(const U1 u1_a_CNTTID, const U1 u1_a_UNIT)
{
    const ST_PTSRUNTM_CNTT *                    stp_t_CNTT;
    U4                                          u4_t_tmcnt;
    U2                                          u2_t_txval;


    u2_t_txval = (U2)TRIPCOM_CANTX_UNKNOWN;

    if (u1_a_CNTTID < (U1)PTSRUNTM_NUM_CNTTS) {
        if ((st_sp_ptsruntm_var[u1_a_CNTTID].u1_status & (U1)TRIPCOM_STSBIT_INVALID) != (U1)0U) {
            u2_t_txval = (U2)TRIPCOM_CANTX_TIMEOUT;
        }
        else {
            stp_t_CNTT = &st_sp_PTSRUNTM_CNTTS_CFG[u1_a_CNTTID];

            u4_t_tmcnt  = u4_g_TripcomMsGetAccmltVal(stp_t_CNTT->u1_ms_ptsruntm_id);
            u4_t_tmcnt /= (U4)TRIPCOM_ELPSDTM_MI_TO_SE;
            u2_t_txval  = (U2)PTSRUNTM_HRS_CANTX_MAX;
            if (u4_t_tmcnt < (U4)u2_t_txval) {
                u2_t_txval = (U2)u4_t_tmcnt;
            }
        }
    }

    return (u2_t_txval);
}

/*===================================================================================================================================*/
/* static  void    vd_s_PtsRunTmHandleOvrf(const U4 u4_a_MAX, const U1 u1_a_ROLLCNT, const U4 u4_a_DELTA, U4 * u4_ap_elpsdtm)        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void      vd_s_PtsRunTmHandleOvrf(const U4 u4_a_MAX, const U1 u1_a_ROLLCNT, const U4 u4_a_DELTA, U4 * u4_ap_elpsdtm)
{
    U4          u4_t_tmcnt;

    u4_t_tmcnt = (*u4_ap_elpsdtm);
    if (u1_a_ROLLCNT == (U1)TRUE) {
        u4_t_tmcnt = u4_a_DELTA - ((u4_a_MAX + (U4)PTSRUNTM_HRS_ROLL_OFST) - u4_t_tmcnt);
        /* For processing for roll count.       */
    }
    else {
        u4_t_tmcnt = u4_a_MAX;
    }

    (*u4_ap_elpsdtm) = u4_t_tmcnt;
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
/*  1.0.1    03/19/2020  YA       Change for 800B CV                                                                                 */
/*  2.0.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*  2.0.2    10/25/2021  TA(M)    Supports TripA and TripB.                                                                          */
/*  2.0.3    10/27/2021  TK       QAC supported.                                                                                     */
/*                                                                                                                                   */
/*  * HY   = Hidefumi Yoshida, Denso                                                                                                 */
/*  * YA   = Yuhei Aoyama, DensoTechno                                                                                               */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * TK   = Takanori Kuno, Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
