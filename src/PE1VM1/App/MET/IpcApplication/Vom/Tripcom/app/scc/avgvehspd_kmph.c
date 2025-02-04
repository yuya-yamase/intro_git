/* 2.0.4 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Average Vehicle Speed for Trip Computer                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define AVGVEHSPD_KMPH_C_MAJOR                  (2)
#define AVGVEHSPD_KMPH_C_MINOR                  (0)
#define AVGVEHSPD_KMPH_C_PATCH                  (4)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "avgvehspd_kmph_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((AVGVEHSPD_KMPH_C_MAJOR != AVGVEHSPD_KMPH_H_MAJOR) || \
     (AVGVEHSPD_KMPH_C_MINOR != AVGVEHSPD_KMPH_H_MINOR) || \
     (AVGVEHSPD_KMPH_C_PATCH != AVGVEHSPD_KMPH_H_PATCH))
#error "avgvsp_kmph.c and avgvsp_kmph.h : source and header files are inconsistent!"
#endif

#if ((AVGVEHSPD_KMPH_C_MAJOR != AVGVEHSPD_KMPH_CFG_H_MAJOR) || \
     (AVGVEHSPD_KMPH_C_MINOR != AVGVEHSPD_KMPH_CFG_H_MINOR) || \
     (AVGVEHSPD_KMPH_C_PATCH != AVGVEHSPD_KMPH_CFG_H_PATCH))
#error "avgvsp_kmph.c and avgvsp_kmph_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define AVGVEHSPD_NUM_EVTBIT                    (4U)
#define AVGVEHSPD_EVTBIT_CALCTMEXPIRD           (0x01U)
#define AVGVEHSPD_EVTBIT_RESET                  (0x02U)

#define AVGVEHSPD_ACT_UPDATE                    (0x10U)
#define AVGVEHSPD_ACT_VALINIT                   (0x20U)

#define AVGVEHSPD_CALCACT_ACT                   (0U                                          )
#define AVGVEHSPD_CALCACT_ACT_UPDT              (AVGVEHSPD_ACT_UPDATE                        )
#define AVGVEHSPD_CALCACT_ACT_RESET             (AVGVEHSPD_ACT_UPDATE | AVGVEHSPD_ACT_VALINIT)

#define AVGVEHSPD_ACCMLTMAX                     (0xE6666665U)           /*  0xFFFFFFFF*0.9  */
#define AVGVEHSPD_COMPRESS_SFT                  (3U)

#define AVGVEHSPD_RESCONV                       (10U)
#define AVGVEHSPD_RESOLUTION                    (10U)
#define AVGVEHSPD_RNDHLF_SFT                    (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct {
    U2                                          u2_calctm;
    U1                                          u1_initupdt;
} ST_AVGVEHSPD_VAR;

typedef struct {
    U2                                          u2_autoreset;           /* see tripcom.h                                             */
    U2                                          u2_manualreset;         /* see tripcom.h                                             */
    U2                                          u2_calc_intrvl;         /* Caution : 0 is special value for this configuration       */
                                                                        /* when u2_calcintvl = 0, periodic updt will not be          */
                                                                        /* called.                                                   */
    U1                                          u1_ms_vehspd_id;        /* see tripcom_ms.h                                          */
    U1                                          u1_ms_elpsdtm_id;       /* see tripcom_ms.h                                          */
    U1                                          u1_ms_odocnt_id;        /* see tripcom_ms.h                                          */

    U2                                          u2_cantx_max;           /* Range max property for cantx value                        */
} ST_AVGVEHSPD_CNTT;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  ST_AVGVEHSPD_VAR                        st_sp_avgvehspd_var[AVGVEHSPD_NUM_CNTTS];
static  U1                                      u1_s_avgvehspd_applsts;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_AVGVEHSPD_CNTT                  st_sp_AVGVEHSPD_CNTTS_CFG[AVGVEHSPD_NUM_CNTTS]      = {
    /*  #define AVGVEHSPD_CNTT_TA                       (0)     */
    {
        (U2)0U,
        (U2)TRIPCOM_RSTRQBIT_M_AVGVEHSPD_TA,
        (U2)(10000U / TRIPCOM_TICK),                    /* 10s  */

        (U1)TRIPCOM_MS_ID_AVGVEHSPD_TA_SP,
        (U1)TRIPCOM_MS_ID_AVGVEHSPD_TA_ET,
        (U1)TRIPCOM_MS_ID_AVGVEHSPD_TA_OC,

        (U2)0xFFFDU
    },
    /*  #define AVGVEHSPD_CNTT_DC                       (1)     */
    {
        (U2)TRIPCOM_RSTRQBIT_A_DRVCYC,
        (U2)0U,
        (U2)(10000U / TRIPCOM_TICK),                    /* 10s  */

        (U1)TRIPCOM_MS_ID_AVGVEHSPD_DC_SP,
        (U1)TRIPCOM_MS_ID_AVGVEHSPD_DC_ET,
        (U1)TRIPCOM_MS_ID_AVGVEHSPD_DC_OC,

        (U2)0xFFFDU
    },
    /*  #define AVGVEHSPD_CNTT_TR_A                     (2)     */
    {
        (U2)0U,
        (U2)TRIPCOM_RSTRQBIT_M_AVGVEHSPD_TR_A,
        (U2)(10000U / TRIPCOM_TICK),                    /* 10s  */

        (U1)TRIPCOM_MS_ID_AVGVEHSPD_TR_A_SP,
        (U1)TRIPCOM_MS_ID_AVGVEHSPD_TR_A_ET,
        (U1)TRIPCOM_MS_ID_AVGVEHSPD_TR_A_OC,

        (U2)0xFFFDU
    },
    /*  #define AVGVEHSPD_CNTT_TR_B                     (3)     */
    {
        (U2)0U,
        (U2)TRIPCOM_RSTRQBIT_M_AVGVEHSPD_TR_B,
        (U2)(10000U / TRIPCOM_TICK),                    /* 10s  */

        (U1)TRIPCOM_MS_ID_AVGVEHSPD_TR_B_SP,
        (U1)TRIPCOM_MS_ID_AVGVEHSPD_TR_B_ET,
        (U1)TRIPCOM_MS_ID_AVGVEHSPD_TR_B_OC,

        (U2)0xFFFDU
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* void            vd_g_AvgVehspdInit(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_AvgVehspdInit(void)
{
    U4          u4_t_loop;


    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)AVGVEHSPD_NUM_CNTTS; u4_t_loop++) {
        st_sp_avgvehspd_var[u4_t_loop].u2_calctm     = (U2)U2_MAX;
        st_sp_avgvehspd_var[u4_t_loop].u1_initupdt   = (U1)FALSE;
    }
    u1_s_avgvehspd_applsts = (U1)TRIPCOM_STSBIT_UNKNOWN;
}

/*===================================================================================================================================*/
/* void            vd_g_AvgVehspdApplTask(const U2 * u2_ap_STSFIELD)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_AvgVehspdApplTask(const U2 * u2_ap_STSFIELD)
{
    U2          u2_t_jdgbit;


    u1_s_avgvehspd_applsts = (U1)TRIPCOM_STSBIT_VALID;
    u2_t_jdgbit  = u2_ap_STSFIELD[TRIPCOM_STSFIELD_SNSR] & (U2)TRIPCOM_SNSRBIT_ODOCNT_UNKNOWN;
    if (u2_t_jdgbit != (U2)0U) {
        u1_s_avgvehspd_applsts  = (U1)TRIPCOM_STSBIT_UNKNOWN;
    }
    u2_t_jdgbit  = u2_ap_STSFIELD[TRIPCOM_STSFIELD_SNSR] & (U2)TRIPCOM_SNSRBIT_ODOCNT_INVALID;
    if (u2_t_jdgbit != (U2)0U) {
        u1_s_avgvehspd_applsts |= (U1)TRIPCOM_STSBIT_INVALID;
    }
}

/*===================================================================================================================================*/
/* U1              u1_g_AvgVehspdCalcTrnst(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD)                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_AvgVehspdCalcTrnst(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD)
{
    static  const   U1                          u1_sp_AVGVEHSPD_CALC_STM[AVGVEHSPD_NUM_EVTBIT]  = {
        (U1)AVGVEHSPD_CALCACT_ACT,
        (U1)AVGVEHSPD_CALCACT_ACT_UPDT,
        (U1)AVGVEHSPD_CALCACT_ACT_RESET,
        (U1)AVGVEHSPD_CALCACT_ACT_RESET
    };
    const ST_AVGVEHSPD_CNTT *                   stp_t_CNTT;
    ST_AVGVEHSPD_VAR *                          stp_t_var;
    U1                                          u1_t_update;
    U1                                          u1_t_evtbit;
    U1                                          u1_t_calcact;


    u1_t_update = (U1)FALSE;
    if (u1_a_CNTTID < (U1)AVGVEHSPD_NUM_CNTTS) {
        stp_t_CNTT = &st_sp_AVGVEHSPD_CNTTS_CFG[u1_a_CNTTID];
        stp_t_var  = &st_sp_avgvehspd_var[u1_a_CNTTID];

        if ((stp_t_var->u2_calctm < (U2)U2_MAX) &&
            ((u2_ap_STSFIELD[TRIPCOM_STSFIELD_VSTS] & (U2)TRIPCOM_VEHSTS_DRVCYC) != (U2)0U)) {

            stp_t_var->u2_calctm++;
        }
        else {
            stp_t_var->u2_calctm = (U2)0U;
        }

        u1_t_evtbit = (U1)0U;
        if (stp_t_var->u2_calctm >= stp_t_CNTT->u2_calc_intrvl) {
            u1_t_evtbit  = (U1)AVGVEHSPD_EVTBIT_CALCTMEXPIRD;
        }
        if ((u2_ap_STSFIELD[TRIPCOM_STSFIELD_AUTO_RSTRQ] & stp_t_CNTT->u2_autoreset) != (U2)0U) {
            u1_t_evtbit |= (U1)AVGVEHSPD_EVTBIT_RESET;
        }
        if ((u2_ap_STSFIELD[TRIPCOM_STSFIELD_MANUAL_RSTRQ] & stp_t_CNTT->u2_manualreset) != (U2)0U) {
            u1_t_evtbit |= (U1)AVGVEHSPD_EVTBIT_RESET;
        }

        u1_t_calcact = u1_sp_AVGVEHSPD_CALC_STM[u1_t_evtbit];

        if ((u1_t_calcact & (U1)AVGVEHSPD_ACT_UPDATE) != (U1)0U) {
            stp_t_var->u2_calctm = (U2)0U;
            u1_t_update = (U1)TRUE;
        }
        stp_t_var->u1_initupdt = (U1)FALSE;
        if ((u1_t_calcact & (U1)AVGVEHSPD_ACT_VALINIT) != (U1)0U) {
            stp_t_var->u1_initupdt = (U1)TRUE;
        }
    }

    return (u1_t_update);
}

/*===================================================================================================================================*/
/* void            vd_g_AvgVehspdAccmlt(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD, const U4 * u4_ap_DELTA)                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_AvgVehspdAccmlt(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD, const U4 * u4_ap_DELTA)
{
    const ST_AVGVEHSPD_CNTT *                   stp_t_CNTT;
    ST_AVGVEHSPD_VAR *                          stp_t_var;
    U4                                          u4_t_elpsdtm;
    U4                                          u4_t_odocnt;
    U1                                          u1_t_ovf;
    U4                                          u4_t_sftval;


    if (u1_a_CNTTID < (U1)AVGVEHSPD_NUM_CNTTS) {
        stp_t_CNTT = &st_sp_AVGVEHSPD_CNTTS_CFG[u1_a_CNTTID];
        stp_t_var  = &st_sp_avgvehspd_var[u1_a_CNTTID];

        if (stp_t_var->u1_initupdt == (U1)TRUE) {
            vd_g_TripcomMsSetAccmltVal(stp_t_CNTT->u1_ms_elpsdtm_id, (U4)0U);
            vd_g_TripcomMsSetAccmltVal(stp_t_CNTT->u1_ms_odocnt_id,  (U4)0U);
        }
        else if (u1_s_avgvehspd_applsts == (U1)TRIPCOM_STSBIT_VALID) {
            u4_t_elpsdtm = u4_g_TripcomMsGetAccmltVal(stp_t_CNTT->u1_ms_elpsdtm_id);
            u4_t_odocnt  = u4_g_TripcomMsGetAccmltVal(stp_t_CNTT->u1_ms_odocnt_id );

            u1_t_ovf  = u1_g_TripcomOvrfChk(u4_t_elpsdtm, u4_ap_DELTA[TRIPCOM_DELTA_DC_ELPSD_10MS], (U4)AVGVEHSPD_ACCMLTMAX);
            u1_t_ovf |= u1_g_TripcomOvrfChk(u4_t_odocnt,  u4_ap_DELTA[TRIPCOM_DELTA_DC_ODOCNT_PC],  (U4)AVGVEHSPD_ACCMLTMAX);

            u4_t_elpsdtm += u4_ap_DELTA[TRIPCOM_DELTA_DC_ELPSD_10MS];
            /* The overflow check is performed by the u1_g_TripcomOvrfChk() function, and the overflow is intentionally made.   */
            u4_t_odocnt  += u4_ap_DELTA[TRIPCOM_DELTA_DC_ODOCNT_PC];
            /* The overflow check is performed by the u1_g_TripcomOvrfChk() function, and the overflow is intentionally made.   */
            if (u1_t_ovf == (U1)TRUE) {
                u4_t_sftval   = (U4)(u4_t_elpsdtm >> AVGVEHSPD_COMPRESS_SFT);
                u4_t_elpsdtm -= u4_t_sftval;
                /* u4_t_elpsdtm is always larger,                                                               */
                /*because u4_t_elpsdtm is subtracted from u4_t_elpsdtm by AVGVEHSPD_COMPRESS_SFT right shifts.  */
                u4_t_sftval   = (U4)(u4_t_odocnt >> AVGVEHSPD_COMPRESS_SFT);
                u4_t_odocnt  -= u4_t_sftval;
                /* u4_t_odocnt is always larger,                                                                */
                /*because u4_t_odocnt is subtracted from u4_t_odocnt by AVGVEHSPD_COMPRESS_SFT right shifts.    */
            }

            vd_g_TripcomMsSetAccmltVal(stp_t_CNTT->u1_ms_elpsdtm_id, u4_t_elpsdtm);
            vd_g_TripcomMsSetAccmltVal(stp_t_CNTT->u1_ms_odocnt_id,  u4_t_odocnt );
        }
        else {
            /* Do Nothing */
        }
    }
}

/*===================================================================================================================================*/
/* void            vd_g_AvgVehspdUpdt(const U1 u1_a_CNTTID)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_AvgVehspdUpdt(const U1 u1_a_CNTTID)
{
    const ST_AVGVEHSPD_CNTT *                   stp_t_CNTT;
    U4                                          u4_t_elpsdtm;
    U4                                          u4_t_odocnt;
    U4                                          u4_t_spd;


    if (u1_a_CNTTID < (U1)AVGVEHSPD_NUM_CNTTS) {
        stp_t_CNTT = &st_sp_AVGVEHSPD_CNTTS_CFG[u1_a_CNTTID];

        u4_t_elpsdtm = u4_g_TripcomMsGetAccmltVal(stp_t_CNTT->u1_ms_elpsdtm_id);
        u4_t_odocnt  = u4_g_TripcomMsGetAccmltVal(stp_t_CNTT->u1_ms_odocnt_id);

        u4_t_spd = u4_g_TripcomCalcVehspdKmph(u4_t_odocnt, u4_t_elpsdtm);
        vd_g_TripcomMsSetAccmltVal(stp_t_CNTT->u1_ms_vehspd_id, u4_t_spd);
    }
}

/*===================================================================================================================================*/
/* U1              u1_g_AvgVehspdKmph(const U1 u1_a_AVG_VEHSPD_CH, U2 * u2p_a_kmph)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_AvgVehspdKmph(const U1 u1_a_AVG_VEHSPD_CH, U2 * u2p_a_kmph)
{
    U1          u1_t_status;
    U4          u4_t_value;


    u1_t_status = (U1)TRIPCOM_STSBIT_INVALID;
    if (u1_a_AVG_VEHSPD_CH < (U1)AVGVEHSPD_NUM_CNTTS) {
        u4_t_value = u4_g_TripcomMsGetAccmltVal(st_sp_AVGVEHSPD_CNTTS_CFG[u1_a_AVG_VEHSPD_CH].u1_ms_vehspd_id);
        if (u4_t_value > (U4)U2_MAX) {
            u4_t_value = (U4)U2_MAX;
        }
        if (u2p_a_kmph != vdp_PTR_NA) {
            (*u2p_a_kmph) = (U2)u4_t_value;
        }
        u1_t_status = u1_s_avgvehspd_applsts;
    }

    return (u1_t_status);
}

/*===================================================================================================================================*/
/* U2              u2_g_AvgVehspdCalcTx(const U1 u1_a_CNTTID, const U1 u1_a_UNIT)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2              u2_g_AvgVehspdCalcTx(const U1 u1_a_CNTTID, const U1 u1_a_UNIT)
{
    const ST_AVGVEHSPD_CNTT *                   stp_t_CNTT;
    U4                                          u4_t_speed;
    U2                                          u2_t_txval;
    U1                                          u1_t_cnvsts;


    u2_t_txval = (U2)TRIPCOM_CANTX_UNKNOWN;

    if (u1_a_CNTTID < (U1)AVGVEHSPD_NUM_CNTTS) {
        if ((u1_s_avgvehspd_applsts & (U1)TRIPCOM_STSBIT_INVALID) != (U1)0U) {
            u2_t_txval = (U2)TRIPCOM_CANTX_TIMEOUT;
        }
        else {
            stp_t_CNTT  = &st_sp_AVGVEHSPD_CNTTS_CFG[u1_a_CNTTID];
            u4_t_speed  = u4_g_TripcomMsGetAccmltVal(stp_t_CNTT->u1_ms_vehspd_id);
            u1_t_cnvsts = u1_g_TripcomCalcTxCnvtSpeed(&u4_t_speed, u1_a_UNIT);
            if (u1_t_cnvsts == (U1)TRIPCOM_STSBIT_VALID) {
                u4_t_speed  = u4_g_TripcomCalcAddU4U4((u4_t_speed / (U4)AVGVEHSPD_RESCONV), ((U4)AVGVEHSPD_RESOLUTION >> AVGVEHSPD_RNDHLF_SFT));
                u4_t_speed  = u4_g_TripcomCalcSubU4U4(u4_t_speed, (u4_t_speed % (U4)AVGVEHSPD_RESOLUTION));

                u2_t_txval = stp_t_CNTT->u2_cantx_max;
                if (u4_t_speed < (U4)u2_t_txval) {
                    u2_t_txval = (U2)u4_t_speed;
                }
            }
        }
    }

    return (u2_t_txval);
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
/*  2.0.4    02/25/2022  TA(M)    Delete call vd_g_AvgVehspdUpdt((U1)AVGVEHSPD_CNTT_TA) at vd_g_AvgVehspdInit                        */
/*                                                                                                                                   */
/*  * HY   = Hidefumi Yoshida, Denso                                                                                                 */
/*  * YA   = Yuhei Aoyama, DensoTechno                                                                                               */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
