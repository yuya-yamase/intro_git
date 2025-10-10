/* 2.2.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Average Electric Economy for Trip Computer                                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define AVGEE_KMPKWH_C_MAJOR                      (2)
#define AVGEE_KMPKWH_C_MINOR                      (2)
#define AVGEE_KMPKWH_C_PATCH                      (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "avgee_kmpkwh_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((AVGEE_KMPKWH_C_MAJOR != AVGEE_KMPKWH_H_MAJOR) || \
     (AVGEE_KMPKWH_C_MINOR != AVGEE_KMPKWH_H_MINOR) || \
     (AVGEE_KMPKWH_C_PATCH != AVGEE_KMPKWH_H_PATCH))
#error "avgee_kmpkwh.c and avgee_kmpkwh.h : source and header files are inconsistent!"
#endif

#if ((AVGEE_KMPKWH_C_MAJOR != AVGEE_KMPKWH_CFG_H_MAJOR) || \
     (AVGEE_KMPKWH_C_MINOR != AVGEE_KMPKWH_CFG_H_MINOR) || \
     (AVGEE_KMPKWH_C_PATCH != AVGEE_KMPKWH_CFG_H_PATCH))
#error "avgee_kmpkwh.c and avgee_kmpkwh_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define AVGEE_NUM_EVTBIT                      (8U)
#define AVGEE_EVTBIT_CALCTMEXPIRD             (0x01U)
#define AVGEE_EVTBIT_RESET                    (0x02U)
#define AVGEE_EVTBIT_PAUSE                    (0x04U)

#define AVGEE_NUM_CALCSTS                     (2U)
#define AVGEE_CALCSTS_INACT                   (0x00U)
#define AVGEE_CALCSTS_ACT                     (0x01U)

#define AVGEE_ACT_UPDATE                      (0x10U)
#define AVGEE_ACT_VALINIT                     (0x20U)

#define AVGEE_CALCACT_INACT                   (AVGEE_CALCSTS_INACT                                       )
#define AVGEE_CALCACT_INACT_RESET             (AVGEE_CALCSTS_INACT | AVGEE_ACT_UPDATE | AVGEE_ACT_VALINIT)
#define AVGEE_CALCACT_ACT                     (AVGEE_CALCSTS_ACT                                         )
#define AVGEE_CALCACT_ACT_UPDT                (AVGEE_CALCSTS_ACT   | AVGEE_ACT_UPDATE                    )
#define AVGEE_CALCACT_ACT_RESET               (AVGEE_CALCSTS_ACT   | AVGEE_ACT_UPDATE | AVGEE_ACT_VALINIT)

#define AVGEE_ACCMLTRNGEMAX                   (0xE6666665U)
#define AVGEE_ACCMLTUSDMAX                    (0x73333332U)

#define AVGEE_COMPRESS_SFT                    (3U)
#define AVGEE_COMPRESS_DIV                    (8U)

#define AVGEE_RNDHLF_SFT                      (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  ST_AVGECON_VAR                            st_sp_avgee_var[AVGEE_NUM_CNTTS];
static  U1                                        u1_s_avgee_applsts;
static  U4                                        u4_s_avgee_econ_prev_rst;
static  U1                                        u1_s_avgee_econ_init_bk;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1          u1_s_AvgEeOvrfChk(const S4 s4_a_USD, const S4 s4_a_EPUSD);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_AVGECON_CNTT                    st_sp_AVGEE_CNTTS_CFG[AVGEE_NUM_CNTTS]      = {
    /*  #define AVGEE_CNTT_TA                           (0)     */
    {
        (U2)0U,
        (U2)TRIPCOM_RSTRQBIT_M_AVGEE_TA,
        (U2)0U,
        (U2)(10000U / TRIPCOM_TICK),                    /* 10s  */

        (U1)TRIPCOM_MS_ID_AVGEE_TA_EE,
        (U1)TRIPCOM_MS_ID_AVGEE_TA_EU,
        (U1)TRIPCOM_MS_ID_AVGEE_TA_OC,
        (U1)FALSE,

        (U1)FALSE,
        (U2)0xFFFCU,
        (U2)TRIPCOM_CANTX_TIMEOUT,
        (U2)TRIPCOM_CANTX_UNKNOWN,
        (U2)0xFFFDU,
        (U2)100U
    },
    /*  #define AVGEE_CNTT_DC                           (1)     */
    {
        (U2)TRIPCOM_RSTRQBIT_A_DRVCYC,
        (U2)0U,
        (U2)0U,
        (U2)(10000U / TRIPCOM_TICK),                    /* 10s  */

        (U1)TRIPCOM_MS_ID_AVGEE_DC_EE,
        (U1)TRIPCOM_MS_ID_AVGEE_DC_EU,
        (U1)TRIPCOM_MS_ID_AVGEE_DC_OC,
        (U1)FALSE,

        (U1)FALSE,
        (U2)0xFFFDU,
        (U2)TRIPCOM_CANTX_TIMEOUT,
        (U2)TRIPCOM_CANTX_UNKNOWN,
        (U2)0x0000U,
        (U2)100U
    },
    /*  #define AVGEE_CNTT_ONEM                         (2)     */
    {
        (U2)0U,
        (U2)TRIPCOM_RSTRQBIT_M_AVGEE_ONEM,
        (U2)0U,
        (U2)(60000U / TRIPCOM_TICK),                    /* 1min  */

        (U1)TRIPCOM_MS_ID_AVGEE_ONEM_EE,
        (U1)TRIPCOM_MS_ID_AVGEE_ONEM_EU,
        (U1)TRIPCOM_MS_ID_AVGEE_ONEM_OC,
        (U1)TRUE,

        (U1)FALSE,
        (U2)0xFFFCU,
        (U2)TRIPCOM_CANTX_TIMEOUT,
        (U2)TRIPCOM_CANTX_UNKNOWN,
        (U2)0xFFFEU,
        (U2)100U
    },
    /*  #define AVGEE_CNTT_FIVEM                        (3)     */
    {
        (U2)0U,
        (U2)0U,
        (U2)0U,
        (U2)(300000U / TRIPCOM_TICK),                    /* 5min  */

        (U1)TRIPCOM_MS_ID_AVGEE_FIVEM_EE,
        (U1)TRIPCOM_MS_ID_AVGEE_FIVEM_EU,
        (U1)TRIPCOM_MS_ID_AVGEE_FIVEM_OC,
        (U1)TRUE,

        (U1)FALSE,
        (U2)0xFFFCU,
        (U2)TRIPCOM_CANTX_TIMEOUT,
        (U2)TRIPCOM_CANTX_UNKNOWN,
        (U2)0x0000U,
        (U2)100U
    }

};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* void            vd_g_AvgEeInit(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void          vd_g_AvgEeInit(void)
{
    U4          u4_t_loop;

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)AVGEE_NUM_CNTTS; u4_t_loop++) {
        st_sp_avgee_var[u4_t_loop].u2_calctm     = (U2)U2_MAX;
        st_sp_avgee_var[u4_t_loop].u1_calcstsbit = (U1)AVGEE_CALCACT_ACT;
        st_sp_avgee_var[u4_t_loop].u1_initupdt   = (U1)FALSE;
        st_sp_avgee_var[u4_t_loop].u1_rstterm    = (U1)FALSE;
        st_sp_avgee_var[u4_t_loop].u1_rstimmw    = (U1)TRIPCOM_RSTIMMW_UNK;
    }
    
    u1_s_avgee_applsts = (U1)TRIPCOM_STSBIT_UNKNOWN;
    u4_s_avgee_econ_prev_rst = (U4)0U;
    u1_s_avgee_econ_init_bk  = (U1)FALSE;
}

/*===================================================================================================================================*/
/* void            vd_g_AvgEeApplTask(const U2 * u2_ap_STSFIELD)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void          vd_g_AvgEeApplTask(const U2 * u2_ap_STSFIELD)
{
    U2          u2_t_jdgbit;


    u1_s_avgee_applsts = (U1)TRIPCOM_STSBIT_VALID;
    u2_t_jdgbit = u2_ap_STSFIELD[TRIPCOM_STSFIELD_SNSR] & (U2)TRIPCOM_SNSRBIT_AVGEE_UNKNOWN;
    if (u2_t_jdgbit != (U2)0U) {
        u1_s_avgee_applsts  = (U1)TRIPCOM_STSBIT_UNKNOWN;
    }
    u2_t_jdgbit = u2_ap_STSFIELD[TRIPCOM_STSFIELD_SNSR] & (U2)TRIPCOM_SNSRBIT_AVGEE_INVALID;
    if (u2_t_jdgbit != (U2)0U) {
        u1_s_avgee_applsts |= (U1)TRIPCOM_STSBIT_INVALID;
    }
}

/*===================================================================================================================================*/
/* U1              u1_g_AvgEeCalcTrnst(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1            u1_g_AvgEeCalcTrnst(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD)
{
    static  const   U1                          u1_sp2_AVGEE_CALC_STM[AVGEE_NUM_EVTBIT][AVGEE_NUM_CALCSTS]       = {
        {   (U1)AVGEE_CALCACT_ACT_UPDT,         (U1)AVGEE_CALCACT_ACT                       },
        {   (U1)AVGEE_CALCACT_ACT_UPDT,         (U1)AVGEE_CALCACT_ACT_UPDT                  },
        {   (U1)AVGEE_CALCACT_ACT_RESET,        (U1)AVGEE_CALCACT_ACT_RESET                 },
        {   (U1)AVGEE_CALCACT_ACT_RESET,        (U1)AVGEE_CALCACT_ACT_RESET                 },
        {   (U1)AVGEE_CALCACT_INACT,            (U1)AVGEE_CALCACT_INACT                     },
        {   (U1)AVGEE_CALCACT_INACT,            (U1)AVGEE_CALCACT_INACT                     },
        {   (U1)AVGEE_CALCACT_INACT_RESET,      (U1)AVGEE_CALCACT_INACT_RESET               },
        {   (U1)AVGEE_CALCACT_INACT_RESET,      (U1)AVGEE_CALCACT_INACT_RESET               }
    };
    
    const ST_AVGECON_CNTT *                     stp_t_CNTT;
    ST_AVGECON_VAR *                            stp_t_var;
    U1                                          u1_t_update;
    U1                                          u1_t_evtbit;
    U1                                          u1_t_calcact;


    stp_t_CNTT = &st_sp_AVGEE_CNTTS_CFG[u1_a_CNTTID];
    stp_t_var  = &st_sp_avgee_var[u1_a_CNTTID];

    if ((stp_t_var->u2_calctm < (U2)U2_MAX) &&
        ((u2_ap_STSFIELD[TRIPCOM_STSFIELD_VSTS] & (U2)TRIPCOM_VEHSTS_DRVCYC) != (U2)0U)) {

        stp_t_var->u2_calctm++;
    }
    else {
        stp_t_var->u2_calctm = (U2)0U;
    }

    u1_t_evtbit = (U1)0U;
    if (stp_t_var->u2_calctm >= stp_t_CNTT->u2_calc_intrvl) {
        u1_t_evtbit  = (U1)AVGEE_EVTBIT_CALCTMEXPIRD;
    }
    if ((u2_ap_STSFIELD[TRIPCOM_STSFIELD_AUTO_RSTRQ] & stp_t_CNTT->u2_autoreset) != (U2)0U) {
        u1_t_evtbit |= (U1)AVGEE_EVTBIT_RESET;
    }
    if ((u2_ap_STSFIELD[TRIPCOM_STSFIELD_MANUAL_RSTRQ] & stp_t_CNTT->u2_manualreset) != (U2)0U) {
        u1_t_evtbit |= (U1)AVGEE_EVTBIT_RESET;
    }

    if ((u2_ap_STSFIELD[TRIPCOM_STSFIELD_OTHRQ] & stp_t_CNTT->u2_pause) != (U2)0U) {
        u1_t_evtbit |= (U1)AVGEE_EVTBIT_PAUSE;
    }

    u1_t_calcact = (U1)AVGEE_CALCACT_INACT;
    if (stp_t_var->u1_calcstsbit < (U1)AVGEE_NUM_CALCSTS) {
        u1_t_calcact = u1_sp2_AVGEE_CALC_STM[u1_t_evtbit][stp_t_var->u1_calcstsbit];
    }

    u1_t_update = (U1)FALSE;
    if ((u1_t_calcact & (U1)AVGEE_ACT_UPDATE) != (U1)0U) {
        stp_t_var->u2_calctm = (U2)0U;
        u1_t_update = (U1)TRUE;
        stp_t_var->u1_rstterm  = (U1)FALSE;
    }
    stp_t_var->u1_initupdt = (U1)FALSE;
    if ((u1_t_calcact & (U1)AVGEE_ACT_VALINIT) != (U1)0U) {
        stp_t_var->u1_initupdt = (U1)TRUE;
        stp_t_var->u1_rstterm  = (U1)TRUE;
    }

    stp_t_var->u1_calcstsbit = u1_t_calcact & (U1)AVGEE_CALCSTS_ACT;

    if((u1_a_CNTTID == (U1)AVGEE_CNTT_ONEM) && 
       ((u2_ap_STSFIELD[TRIPCOM_STSFIELD_AUTO_RSTRQ] & (U2)TRIPCOM_RSTRQBIT_A_DRVCYC_OFF) !=(U2)0U)) {
        stp_t_var->u1_initupdt   = (U1)TRUE;
        stp_t_var->u2_calctm     = (U2)0U;
        u1_t_update              = (U1)TRUE;
    }
    if((u1_a_CNTTID == (U1)AVGEE_CNTT_TA) &&
       (stp_t_var->u1_initupdt == (U1)TRUE) && (u1_s_avgee_econ_init_bk == (U1)FALSE)) {
        u4_s_avgee_econ_prev_rst = u4_g_TripcomMsGetAccmltVal(stp_t_CNTT->u1_ms_economy_id);
    }

    return (u1_t_update);
}

/*===================================================================================================================================*/
/* void            vd_g_AvgEeAccmlt(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD, const U4 * u4_ap_DELTA)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void          vd_g_AvgEeAccmlt(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD, const U4 * u4_ap_DELTA)
{
    const ST_AVGECON_CNTT *                     stp_t_CNTT;
    S4                                          s4_t_epusd;
    U4                                          u4_t_odocnt;
    S4                                          s4_t_usd;
    U4                                          u4_t_odo;
    U1                                          u1_t_ovf_odo;
    U1                                          u1_t_ovf_usd;
    U4                                          u4_t_sftval;


    if (u1_a_CNTTID < (U1)AVGEE_NUM_CNTTS) {
        stp_t_CNTT   = &st_sp_AVGEE_CNTTS_CFG[u1_a_CNTTID];

        s4_t_epusd   = (S4)u4_ap_DELTA[TRIPCOM_DELTA_DC_INSTEPUSD_PC];
        u4_t_odocnt  = u4_ap_DELTA[TRIPCOM_DELTA_DC_EVRUNDIST_PC];

        if (st_sp_avgee_var[u1_a_CNTTID].u1_initupdt == (U1)TRUE) {
            vd_g_TripcomMsSetAccmltVal(stp_t_CNTT->u1_ms_used_id,   (U4)0U);
            vd_g_TripcomMsSetAccmltVal(stp_t_CNTT->u1_ms_odocnt_id, (U4)0U);
        }
        else if (u1_s_avgee_applsts == (U1)TRIPCOM_STSBIT_VALID) {
            s4_t_usd    = (S4)u4_g_TripcomMsGetAccmltVal(stp_t_CNTT->u1_ms_used_id);
            u4_t_odo    = u4_g_TripcomMsGetAccmltVal(stp_t_CNTT->u1_ms_odocnt_id);

            u1_t_ovf_odo = u1_g_TripcomOvrfChk(u4_t_odo, u4_t_odocnt, (U4)AVGEE_ACCMLTRNGEMAX);
            u1_t_ovf_usd = u1_s_AvgEeOvrfChk(s4_t_usd, s4_t_epusd);
            u4_t_odo += u4_t_odocnt;
            /* The overflow check is performed by the u1_g_TripcomOvrfChk() function, and the overflow is intentionally made.   */
            s4_t_usd += s4_t_epusd;

            if ((u1_t_ovf_odo == (U1)TRUE) || (u1_t_ovf_usd == (U1)TRUE)) {
                u4_t_sftval = (U4)(u4_t_odo >> AVGEE_COMPRESS_SFT);
                u4_t_odo   -= u4_t_sftval;
                /* u4_t_odo is always larger,                                                           */
                /*because u4_t_odo is subtracted from u4_t_odo by AVGECON_COMPRESS_SFT right shifts.    */
                s4_t_usd -= (s4_t_usd / (S4)AVGEE_COMPRESS_DIV);
            }

            vd_g_TripcomMsSetAccmltVal(stp_t_CNTT->u1_ms_used_id,(U4)s4_t_usd);
            vd_g_TripcomMsSetAccmltVal(stp_t_CNTT->u1_ms_odocnt_id,  u4_t_odo);
        }
        else {
             /*  Do Nothing  */
        }
    }
}

/*===================================================================================================================================*/
/* void            vd_g_AvgEeUpdt(const U1 u1_a_CNTTID)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void          vd_g_AvgEeUpdt(const U1 u1_a_CNTTID)
{
    const ST_AVGECON_CNTT *                     stp_t_CNTT;
    U4                                          u4_t_usd;
    U4                                          u4_t_odocnt;
    U4                                          u4_t_economy;



    if (u1_a_CNTTID < (U1)AVGEE_NUM_CNTTS) {
        stp_t_CNTT = &st_sp_AVGEE_CNTTS_CFG[u1_a_CNTTID];

        u4_t_usd    = u4_g_TripcomMsGetAccmltVal(stp_t_CNTT->u1_ms_used_id  );
        u4_t_odocnt = u4_g_TripcomMsGetAccmltVal(stp_t_CNTT->u1_ms_odocnt_id);
        
        if ((S4)u4_t_usd >= (S4)0) {
            u4_t_economy = u4_g_TripcomCalcAvgEeKmpkwh(u4_t_odocnt, u4_t_usd);
        }
        else {
            u4_t_economy = (U4)U4_MAX;
        }
        
        vd_g_TripcomMsSetAccmltVal(stp_t_CNTT->u1_ms_economy_id, u4_t_economy);

        if (stp_t_CNTT->u1_init_after_updt == (U1)TRUE) {
            vd_g_TripcomMsSetAccmltVal(stp_t_CNTT->u1_ms_used_id,   (U4)0U);
            vd_g_TripcomMsSetAccmltVal(stp_t_CNTT->u1_ms_odocnt_id, (U4)0U);
        }
    }
}
/*===================================================================================================================================*/
/* void            vd_g_AvgEeGrphUpdt(const U1 u1_a_CNTTID)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void          vd_g_AvgEeGrphUpdt(const U1 u1_a_CNTTID)
{
    const ST_AVGECON_CNTT *                     stp_t_CNTT;
    U4                                          u4_t_economy;

    if (u1_a_CNTTID < (U1)AVGEE_NUM_CNTTS) {
        stp_t_CNTT = &st_sp_AVGEE_CNTTS_CFG[u1_a_CNTTID];
        switch(u1_a_CNTTID){
            case (U1)AVGEE_CNTT_TA:
                if((st_sp_avgee_var[AVGEE_CNTT_TA].u1_initupdt == (U1)TRUE)
                && (u1_s_avgee_econ_init_bk == (U1)FALSE)){
                    vd_g_AvgGrphUpdt((U1)AVGGRPH_CNTT_TAEE, u4_s_avgee_econ_prev_rst, (U1)TRUE);
                }
                break;
            case (U1)AVGEE_CNTT_ONEM:
                u4_t_economy = u4_g_TripcomMsGetAccmltVal(stp_t_CNTT->u1_ms_economy_id);
                if(st_sp_avgee_var[AVGEE_CNTT_ONEM].u1_initupdt == (U1)FALSE){
                    vd_g_AvgGrphUpdt((U1)AVGGRPH_CNTT_1MEE, u4_t_economy, (U1)FALSE);
                }
                break;
            default:
                /* Do Nothing */
                break;
        }
    }
}

/*===================================================================================================================================*/
/* void            vd_g_AvgEeRstImmw(const U1 u1_a_ACTV, const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_AvgEeRstImmw(const U1 u1_a_ACTV, const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD)
{
    const ST_AVGECON_CNTT *                     stp_t_CNTT;
    ST_AVGECON_VAR *                            stp_t_var;

    if (u1_a_CNTTID < (U1)AVGEE_NUM_CNTTS) {
        stp_t_CNTT = &st_sp_AVGEE_CNTTS_CFG[u1_a_CNTTID];
        stp_t_var  = &st_sp_avgee_var[u1_a_CNTTID];
        vd_g_AvgEconRstImmw(u1_a_ACTV, stp_t_CNTT, stp_t_var, u2_ap_STSFIELD);
    }
}

/*===================================================================================================================================*/
/* U1              u1_g_AvgEeKmpkwh(const U1 u1_a_AVG_EE_CH, U4 * u4p_a_kmpkwh)                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1            u1_g_AvgEeKmpkwh(const U1 u1_a_AVG_EE_CH, U4 * u4p_a_kmpkwh)
{
    U1          u1_t_status;


    u1_t_status = (U1)TRIPCOM_STSBIT_INVALID;
    if (u1_a_AVG_EE_CH < (U1)AVGEE_NUM_CNTTS) {
        if (u4p_a_kmpkwh != vdp_PTR_NA) {
            (*u4p_a_kmpkwh) = u4_g_TripcomMsGetAccmltVal(st_sp_AVGEE_CNTTS_CFG[u1_a_AVG_EE_CH].u1_ms_economy_id);
        }
        u1_t_status = u1_s_avgee_applsts;
    }

    return (u1_t_status);
}

/*===================================================================================================================================*/
/* U1              u1_g_AvgEeRstImmwRslt(const U1 u1_a_AVG_EE_CH)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_AvgEeRstImmwRslt(const U1 u1_a_AVG_EE_CH)
{
    U1                                          u1_t_rslt;

    u1_t_rslt = (U1)TRIPCOM_RSTIMMW_UNK;
    if (u1_a_AVG_EE_CH < (U1)AVGEE_NUM_CNTTS) {
        u1_t_rslt = st_sp_avgee_var[u1_a_AVG_EE_CH].u1_rstimmw;
    }

    return(u1_t_rslt);
}

/*===================================================================================================================================*/
/* U2              u2_g_AvgEeCalcTx(const U1 u1_a_CNTTID, const U1 u1_a_UNIT)                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2            u2_g_AvgEeCalcTx(const U1 u1_a_CNTTID, const U1 u1_a_UNIT)
{
    const ST_AVGECON_CNTT *                     stp_t_CNTT;
    U2                                          u2_t_txval;


    u2_t_txval = (U2)TRIPCOM_CANTX_UNKNOWN;

    if (u1_a_CNTTID < (U1)AVGFE_NUM_CNTTS) {
        stp_t_CNTT = &st_sp_AVGEE_CNTTS_CFG[u1_a_CNTTID];

        if ((u1_s_avgee_applsts & (U1)TRIPCOM_STSBIT_INVALID) != (U1)0U) {
            u2_t_txval = stp_t_CNTT->u2_cantx_fail;
        }
        else {
            u2_t_txval = u2_g_AvgEconCalcTx(stp_t_CNTT, st_sp_avgee_var[u1_a_CNTTID].u1_rstterm, u1_a_UNIT, (U1)AVGECON_ENGYTYPE_ELPW);
        }
    }

    return (u2_t_txval);
}

/*===================================================================================================================================*/
/* static  U1    u1_s_AvgEeOvrfChk(const S4 s4_a_USD, const S4 s4_a_EPUSD)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1    u1_s_AvgEeOvrfChk(const S4 s4_a_USD, const S4 s4_a_EPUSD)
{
    U4          u4_t_abs_epusd;
    U4          u4_t_abs_usd;
    U1          u1_t_ovf;


    if ((s4_a_EPUSD > (S4)0) && (s4_a_USD > (S4)0)) {
        u1_t_ovf = u1_g_TripcomOvrfChk((U4)s4_a_USD, (U4)s4_a_EPUSD, (U4)AVGEE_ACCMLTUSDMAX);
    }
    else if ((s4_a_EPUSD < (S4)0) && (s4_a_USD < (S4)0)) {
        u4_t_abs_usd   = (U4)(S4)((S4)0 - s4_a_USD);
        u4_t_abs_epusd = (U4)(S4)((S4)0 - s4_a_EPUSD);
        u1_t_ovf       = u1_g_TripcomOvrfChk(u4_t_abs_usd, u4_t_abs_epusd, (U4)AVGEE_ACCMLTUSDMAX);
    }
    else {
        u1_t_ovf = (U1)FALSE;
    }

    return (u1_t_ovf);
}

/*===================================================================================================================================*/
/* void            vd_g_AvgEePostTask(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_AvgEePostTask(void)
{
    u1_s_avgee_econ_init_bk = st_sp_avgee_var[AVGEE_CNTT_TA].u1_initupdt;
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    03/20/2020  YA       New.                                                                                               */
/*  1.0.1    10/07/2020  YA       Change for 800B CV-R.                                                                              */
/*  2.0.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*  2.0.2    10/27/2021  TK       QAC supported.                                                                                     */
/*  2.0.3    02/25/2022  TA(M)    Delete call vd_g_AvgEeUpdt((U1)AVGEE_CNTT_TA) at vd_g_AvgEeInit                                    */
/*  2.1.0    01/10/2024  TH       for 19PFv3  Add AvgGrph                                                                            */
/*  2.2.0    02/18/2025  MaO(M)   Add privacy data delete/result API                                                                 */
/*  2.2.1    04/22/2025  KM       Bug fix ： Change update timing of u1_s_avgee_econ_init_bk                                          */
/*                                                                                                                                   */
/*  * YA   = Yuhei Aoyama, DensoTechno                                                                                               */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * TK   = Takanori Kuno, Denso Techno                                                                                             */
/*  * TH   = Taisuke Hirakawa, KSE                                                                                                   */
/*  * MaO(M) = Masayuki Okada, NTT Data MSE                                                                                          */
/*  * KM   = Kazuma Miyazawa, Denso Techno                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
