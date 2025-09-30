/* 2.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Average XXXX Economy application core                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define AVGECON_C_MAJOR                         (2)
#define AVGECON_C_MINOR                         (1)
#define AVGECON_C_PATCH                         (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "avgecon_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((AVGECON_C_MAJOR != AVGECON_H_MAJOR) || \
     (AVGECON_C_MINOR != AVGECON_H_MINOR) || \
     (AVGECON_C_PATCH != AVGECON_H_PATCH))
#error "avgecon.c and avgecon.h : source and header files are inconsistent!"
#endif

#if ((AVGECON_C_MAJOR != AVGECON_CFG_H_MAJOR) || \
     (AVGECON_C_MINOR != AVGECON_CFG_H_MINOR) || \
     (AVGECON_C_PATCH != AVGECON_CFG_H_PATCH))
#error "avgecon.c and avgecon_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define AVGECON_NUM_EVTBIT                      (8U)
#define AVGECON_EVTBIT_CALCTMEXPIRD             (0x01U)
#define AVGECON_EVTBIT_RESET                    (0x02U)
#define AVGECON_EVTBIT_PAUSE                    (0x04U)

#define AVGECON_NUM_CALCSTS                     (2U)
#define AVGECON_CALCSTS_INACT                   (0x00U)
#define AVGECON_CALCSTS_ACT                     (0x01U)

#define AVGECON_ACT_UPDATE                      (0x10U)
#define AVGECON_ACT_VALINIT                     (0x20U)

#define AVGECON_CALCACT_INACT                   (AVGECON_CALCSTS_INACT                                           )
#define AVGECON_CALCACT_INACT_RESET             (AVGECON_CALCSTS_INACT | AVGECON_ACT_UPDATE | AVGECON_ACT_VALINIT)
#define AVGECON_CALCACT_ACT                     (AVGECON_CALCSTS_ACT                                             )
#define AVGECON_CALCACT_ACT_UPDT                (AVGECON_CALCSTS_ACT   | AVGECON_ACT_UPDATE                      )
#define AVGECON_CALCACT_ACT_RESET               (AVGECON_CALCSTS_ACT   | AVGECON_ACT_UPDATE | AVGECON_ACT_VALINIT)

#define AVGECON_ACCMLTMAX                       (0xE6666665U)           /*  0xFFFFFFFF*0.9  */
#define AVGECON_COMPRESS_SFT                    (3U)

#define AVGECON_RNDHLF_SFT                      (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1              u1_s_AvgEconImmwRunAct(const ST_AVGECON_CNTT * stp_a_CNTT, const U1 u1_a_UPDT, const U1 u1_a_INIT);
static U1              u1_s_AvgEconImmwRstChk(const ST_AVGECON_CNTT * stp_a_CNTT);
static U2              u2_s_AvgEconResConv(const ST_AVGECON_CNTT * stp_a_CNTT, U4 u4_a_xecon);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* void            vd_g_AvgEconInit(U1 * u1p_a_sts, ST_AVGECON_VAR * st_ap_var, const U4 u4_a_NUM_CNTTS)                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_AvgEconInit(U1 * u1p_a_sts, ST_AVGECON_VAR * st_ap_var, const U4 u4_a_NUM_CNTTS)
{
    U4          u4_t_loop;


    for (u4_t_loop = (U4)0U; u4_t_loop < u4_a_NUM_CNTTS; u4_t_loop++) {
        st_ap_var[u4_t_loop].u2_calctm     = (U2)U2_MAX;
        st_ap_var[u4_t_loop].u1_calcstsbit = (U1)AVGECON_CALCACT_ACT;
        st_ap_var[u4_t_loop].u1_initupdt   = (U1)FALSE;
        st_ap_var[u4_t_loop].u1_rstterm    = (U1)FALSE;
        st_ap_var[u4_t_loop].u1_rstimmw    = (U1)TRIPCOM_RSTIMMW_UNK;
    }

    (*u1p_a_sts) = (U1)TRIPCOM_STSBIT_UNKNOWN;
}

/*===================================================================================================================================*/
/* U1              u1_g_AvgEconCalcTrnst(const ST_AVGECON_CNTT * stp_a_CNTT, ST_AVGECON_VAR * stp_a_var, const U2 * u2_ap_STSFIELD)  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_AvgEconCalcTrnst(const ST_AVGECON_CNTT * stp_a_CNTT, ST_AVGECON_VAR * stp_a_var, const U2 * u2_ap_STSFIELD)
{
    static  const   U1                          u1_sp2_AVGECON_CALC_STM[AVGECON_NUM_EVTBIT][AVGECON_NUM_CALCSTS]       = {
        {   (U1)AVGECON_CALCACT_ACT_UPDT,         (U1)AVGECON_CALCACT_ACT                       },
        {   (U1)AVGECON_CALCACT_ACT_UPDT,         (U1)AVGECON_CALCACT_ACT_UPDT                  },
        {   (U1)AVGECON_CALCACT_ACT_RESET,        (U1)AVGECON_CALCACT_ACT_RESET                 },
        {   (U1)AVGECON_CALCACT_ACT_RESET,        (U1)AVGECON_CALCACT_ACT_RESET                 },
        {   (U1)AVGECON_CALCACT_INACT,            (U1)AVGECON_CALCACT_INACT                     },
        {   (U1)AVGECON_CALCACT_INACT,            (U1)AVGECON_CALCACT_INACT                     },
        {   (U1)AVGECON_CALCACT_INACT_RESET,      (U1)AVGECON_CALCACT_INACT_RESET               },
        {   (U1)AVGECON_CALCACT_INACT_RESET,      (U1)AVGECON_CALCACT_INACT_RESET               }
    };
    U1                                          u1_t_update;
    U1                                          u1_t_evtbit;
    U1                                          u1_t_calcact;


    if ((stp_a_var->u2_calctm < (U2)U2_MAX) &&
        ((u2_ap_STSFIELD[TRIPCOM_STSFIELD_VSTS] & (U2)TRIPCOM_VEHSTS_DRVCYC) != (U2)0U)) {

        stp_a_var->u2_calctm++;
    }
    else {
        stp_a_var->u2_calctm = (U2)0U;
    }

    u1_t_evtbit = (U1)0U;
    if (stp_a_var->u2_calctm >= stp_a_CNTT->u2_calc_intrvl) {
        u1_t_evtbit  = (U1)AVGECON_EVTBIT_CALCTMEXPIRD;
    }
    if ((u2_ap_STSFIELD[TRIPCOM_STSFIELD_AUTO_RSTRQ] & stp_a_CNTT->u2_autoreset) != (U2)0U) {
        u1_t_evtbit |= (U1)AVGECON_EVTBIT_RESET;
    }
    if ((u2_ap_STSFIELD[TRIPCOM_STSFIELD_MANUAL_RSTRQ] & stp_a_CNTT->u2_manualreset) != (U2)0U) {
        u1_t_evtbit |= (U1)AVGECON_EVTBIT_RESET;
    }
    if ((u2_ap_STSFIELD[TRIPCOM_STSFIELD_OTHRQ] & stp_a_CNTT->u2_pause) != (U2)0U) {
        u1_t_evtbit |= (U1)AVGECON_EVTBIT_PAUSE;
    }

    u1_t_calcact = (U1)AVGECON_CALCACT_INACT;
    if (stp_a_var->u1_calcstsbit < (U1)AVGECON_NUM_CALCSTS) {
        u1_t_calcact = u1_sp2_AVGECON_CALC_STM[u1_t_evtbit][stp_a_var->u1_calcstsbit];
    }

    u1_t_update = (U1)FALSE;
    if ((u1_t_calcact & (U1)AVGECON_ACT_UPDATE) != (U1)0U) {
        stp_a_var->u2_calctm = (U2)0U;
        u1_t_update = (U1)TRUE;
        stp_a_var->u1_rstterm  = (U1)FALSE;
    }
    stp_a_var->u1_initupdt = (U1)FALSE;
    if ((u1_t_calcact & (U1)AVGECON_ACT_VALINIT) != (U1)0U) {
        stp_a_var->u1_initupdt = (U1)TRUE;
        stp_a_var->u1_rstterm  = (U1)TRUE;
    }

    stp_a_var->u1_calcstsbit = u1_t_calcact & (U1)AVGECON_CALCSTS_ACT;

    return (u1_t_update);
}

/*===================================================================================================================================*/
/* void            vd_g_AvgEconAccmlt(const ST_AVGECON_CNTT * stp_a_CNTT,                                                            */
/*                                     const U1 u1_a_ISINIT, const U2 u2_a_STSJDG, const U4 u4_a_USD, const U4 u4_a_ODO)             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_AvgEconAccmlt(const ST_AVGECON_CNTT * stp_a_CNTT,
                                    const U1 u1_a_ISINIT, const U2 u2_a_STSJDG, const U4 u4_a_USD, const U4 u4_a_ODO)
{
    U4                                          u4_t_usd;
    U4                                          u4_t_odocnt;
    U1                                          u1_t_ovf;
    U4                                          u4_t_sftval;


    if (u1_a_ISINIT == (U1)TRUE) {
        vd_g_TripcomMsSetAccmltVal(stp_a_CNTT->u1_ms_used_id,   (U4)0U);
        vd_g_TripcomMsSetAccmltVal(stp_a_CNTT->u1_ms_odocnt_id, (U4)0U);
    }
    else if (u2_a_STSJDG == (U2)0U) {
        u4_t_usd    = u4_g_TripcomMsGetAccmltVal(stp_a_CNTT->u1_ms_used_id  );
        u4_t_odocnt = u4_g_TripcomMsGetAccmltVal(stp_a_CNTT->u1_ms_odocnt_id);

        u1_t_ovf  = u1_g_TripcomOvrfChk(u4_t_usd,    u4_a_USD, (U4)AVGECON_ACCMLTMAX);
        u1_t_ovf |= u1_g_TripcomOvrfChk(u4_t_odocnt, u4_a_ODO, (U4)AVGECON_ACCMLTMAX);

        u4_t_usd    += u4_a_USD;
        /* The overflow check is performed by the u1_g_TripcomOvrfChk() function, and the overflow is intentionally made.   */
        u4_t_odocnt += u4_a_ODO;
        /* The overflow check is performed by the u1_g_TripcomOvrfChk() function, and the overflow is intentionally made.   */
        if (u1_t_ovf == (U1)TRUE) {
            u4_t_sftval  = (U4)(u4_t_usd >> AVGECON_COMPRESS_SFT);
            u4_t_usd    -= u4_t_sftval;
            /* u4_t_usd is always larger,                                                               */
            /* because u4_t_usd is subtracted from u4_t_usd by AVGECON_COMPRESS_SFT right shifts.       */
            u4_t_sftval  = (U4)(u4_t_odocnt >> AVGECON_COMPRESS_SFT);
            u4_t_odocnt -= u4_t_sftval;
            /* u4_t_odocnt is always larger,                                                            */
            /* because u4_t_odocnt is subtracted from u4_t_odocnt by AVGECON_COMPRESS_SFT right shifts. */
        }

        vd_g_TripcomMsSetAccmltVal(stp_a_CNTT->u1_ms_used_id,   u4_t_usd   );
        vd_g_TripcomMsSetAccmltVal(stp_a_CNTT->u1_ms_odocnt_id, u4_t_odocnt);
    }
    else {
        /* Do Nothing */
    }
}

/*===================================================================================================================================*/
/* void            vd_g_AvgEconUpdt(const ST_AVGECON_CNTT * stp_a_CNTT, const U1 u1_a_TYPE)                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_AvgEconUpdt(const ST_AVGECON_CNTT * stp_a_CNTT, const U1 u1_a_TYPE)
{
    U4                                          u4_t_usd;
    U4                                          u4_t_odocnt;
    U4                                          u4_t_economy;


    u4_t_usd    = u4_g_TripcomMsGetAccmltVal(stp_a_CNTT->u1_ms_used_id  );
    u4_t_odocnt = u4_g_TripcomMsGetAccmltVal(stp_a_CNTT->u1_ms_odocnt_id);

    switch (u1_a_TYPE) {
        case AVGECON_ENGYTYPE_FUEL:
            u4_t_economy = u4_g_TripcomCalcFeKmpl(u4_t_odocnt, u4_t_usd);
            break;
        case AVGECON_ENGYTYPE_HYDR:
            u4_t_economy = u4_g_TripcomCalcHeKmpkg(u4_t_odocnt, u4_t_usd);
            break;
        default:
            u4_t_economy = (U4)0U;
            break;
    }
    vd_g_TripcomMsSetAccmltVal(stp_a_CNTT->u1_ms_economy_id, u4_t_economy);

    if (stp_a_CNTT->u1_init_after_updt == (U1)TRUE) {
        vd_g_TripcomMsSetAccmltVal(stp_a_CNTT->u1_ms_used_id,   (U4)0U);
        vd_g_TripcomMsSetAccmltVal(stp_a_CNTT->u1_ms_odocnt_id, (U4)0U);
    }
}

/*===================================================================================================================================*/
/* void            vd_g_AvgEconRstImmw(const U1 u1_a_ACTV, const ST_AVGECON_CNTT * stp_a_CNTT, ST_AVGECON_VAR * stp_a_var, const U2 * u2_ap_STSFIELD) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_AvgEconRstImmw(const U1 u1_a_ACTV, const ST_AVGECON_CNTT * stp_a_CNTT, ST_AVGECON_VAR * stp_a_var, const U2 * u2_ap_STSFIELD)
{
    U1                                          u1_t_rstimmw;
    U1                                          u1_t_updt;
    U1                                          u1_t_init;
    U1                                          u1_t_accpt;
    U1                                          u1_t_stsbit;

    u1_t_rstimmw = stp_a_var->u1_rstimmw;

    if((u1_t_rstimmw & (U1)TRIPCOM_RSTIMMW_RUN) == (U1)0U){
        /* TRIPCOM_RSTIMMW_UNK or TRIPCOM_RSTIMMW_(SUC or TRIPCOM_RSTIMMW_FAI */
        if(((u2_ap_STSFIELD[TRIPCOM_STSFIELD_AURST_IMMW] & stp_a_CNTT->u2_autoreset  ) != (U2)0U) ||
           ((u2_ap_STSFIELD[TRIPCOM_STSFIELD_MARST_IMMW] & stp_a_CNTT->u2_manualreset) != (U2)0U)){
            if(u1_a_ACTV == (U1)TRUE){
                u1_t_updt = stp_a_var->u1_initupdt;
                u1_t_init = (U1)FALSE;
            }
            else{
                u1_t_updt = (U1)TRUE;
                u1_t_init = (U1)TRUE;
            }

            u1_t_accpt = u1_s_AvgEconImmwRunAct(stp_a_CNTT, u1_t_updt, u1_t_init);
            if(u1_t_accpt == (U1)TRUE){
                u1_t_rstimmw = (U1)TRIPCOM_RSTIMMW_RUN;
            }
            else{
                u1_t_rstimmw = (U1)TRIPCOM_RSTIMMW_FAI;
            }
        }
    }
    else{
        /* TRIPCOM_RSTIMMW_RUN */
        u1_t_stsbit = u1_s_AvgEconImmwRstChk(stp_a_CNTT);

        if((u1_t_stsbit & (U1)TRIPCOM_MS_NVMSTS_SUC) != (U1)0x00U){
            u1_t_rstimmw = (U1)TRIPCOM_RSTIMMW_SUC;
        }
        else if((u1_t_stsbit & (U1)TRIPCOM_MS_NVMSTS_FAIL) != (U1)0x00U){
            u1_t_rstimmw = (U1)TRIPCOM_RSTIMMW_FAI;
        }
        else{
            /* nothing */
        }
    }
    stp_a_var->u1_rstimmw = u1_t_rstimmw;
}

/*===================================================================================================================================*/
/* U2           u2_g_AvgEconCalcTx(const ST_AVGECON_CNTT * stp_a_CNTT, const U1 u1_a_RSTTRM, const U1 u1_a_UNIT, const U1 u1_a_TYPE) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2              u2_g_AvgEconCalcTx(const ST_AVGECON_CNTT * stp_a_CNTT, const U1 u1_a_RSTTRM, const U1 u1_a_UNIT, const U1 u1_a_TYPE)
{
    static  U1          (* const                fp_sp_TRIPCOM_CNVT[AVGECON_NUM_ENGYTYPE])
                                                        (U4 * u4p_a_kmpx_to, const U1 u1_a_UNIT, const U1 u1_a_USEAPRXVAL)      = {
        &u1_g_TripcomCalcTxCnvtFE,
        &u1_g_TripcomCalcTxCnvtHE,
        &u1_g_TripcomCalcTxCnvtAvgEE
    };
    U4          u4_t_xecon;
    U2          u2_t_txval;
    U1          u1_t_cnvsts;


    u2_t_txval = stp_a_CNTT->u2_cantx_unknown;

    if (u1_a_RSTTRM == (U1)TRUE) {
        u2_t_txval = stp_a_CNTT->u2_cantx_rstinit;
    }
    else {
        u4_t_xecon  = u4_g_TripcomMsGetAccmltVal(stp_a_CNTT->u1_ms_economy_id);
        u1_t_cnvsts = (U1)TRIPCOM_STSBIT_INVALID;
        if ((u1_a_TYPE < (U1)AVGECON_NUM_ENGYTYPE       )  &&
            (fp_sp_TRIPCOM_CNVT[u1_a_TYPE] != vdp_PTR_NA)) {

            u1_t_cnvsts = (fp_sp_TRIPCOM_CNVT[u1_a_TYPE])(&u4_t_xecon, u1_a_UNIT, stp_a_CNTT->u1_cantx_aprx);
        }
        if (u1_t_cnvsts == (U1)TRIPCOM_STSBIT_VALID) {
            u2_t_txval = u2_s_AvgEconResConv(stp_a_CNTT, u4_t_xecon);
        }
    }

    return (u2_t_txval);
}

/*===================================================================================================================================*/
/* static U1       u1_s_AvgEconImmwRunAct(const ST_AVGECON_CNTT * stp_a_CNTT, const U1 u1_a_UPDT, const U1 u1_a_INIT)                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_AvgEconImmwRunAct(const ST_AVGECON_CNTT * stp_a_CNTT, const U1 u1_a_UPDT, const U1 u1_a_INIT)
{
    U1                                          u1_t_accpt;
    U1                                          u1_t_rslt_a;
    U1                                          u1_t_rslt_b;
    U1                                          u1_t_rslt_c;

    u1_t_accpt = (U1)FALSE;

    if(u1_a_UPDT == (U1)TRUE){
        u1_t_rslt_a = u1_g_TripcomMsGetNvmRslt(stp_a_CNTT->u1_ms_economy_id);
        u1_t_rslt_b = u1_g_TripcomMsGetNvmRslt(stp_a_CNTT->u1_ms_used_id   );
        u1_t_rslt_c = u1_g_TripcomMsGetNvmRslt(stp_a_CNTT->u1_ms_odocnt_id );

        if((u1_t_rslt_a != (U1)TRIPCOM_MS_NVMSTS_WAIT) &&
           (u1_t_rslt_b != (U1)TRIPCOM_MS_NVMSTS_WAIT) &&
           (u1_t_rslt_c != (U1)TRIPCOM_MS_NVMSTS_WAIT)){
            if(u1_a_INIT == (U1)TRUE){
                vd_g_TripcomMsSetAccmltVal(stp_a_CNTT->u1_ms_economy_id, (U4)0U);
                vd_g_TripcomMsSetAccmltVal(stp_a_CNTT->u1_ms_used_id,    (U4)0U);
                vd_g_TripcomMsSetAccmltVal(stp_a_CNTT->u1_ms_odocnt_id,  (U4)0U);
            }

            vd_g_TripcomMsSetNvmRqst(stp_a_CNTT->u1_ms_economy_id);
            vd_g_TripcomMsSetNvmRqst(stp_a_CNTT->u1_ms_used_id   );
            vd_g_TripcomMsSetNvmRqst(stp_a_CNTT->u1_ms_odocnt_id );

            u1_t_accpt = (U1)TRUE;
        }
    }
    return(u1_t_accpt);
}

/*===================================================================================================================================*/
/* static U1       u1_s_AvgEconImmwRstChk(const ST_AVGECON_CNTT * stp_a_CNTT)                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_AvgEconImmwRstChk(const ST_AVGECON_CNTT * stp_a_CNTT)
{
    U1                                          u1_t_tmpbit;
    U1                                          u1_t_stsbit;
    U1                                          u1_t_sucbit;
    U1                                          u1_t_faibit;

    u1_t_stsbit = u1_g_TripcomMsGetNvmRslt(stp_a_CNTT->u1_ms_economy_id);

    u1_t_tmpbit = u1_g_TripcomMsGetNvmRslt(stp_a_CNTT->u1_ms_used_id);
    u1_t_sucbit = (U1)((u1_t_stsbit & u1_t_tmpbit) & (U1)TRIPCOM_MS_NVMSTS_SUC);
    u1_t_faibit = (U1)((u1_t_stsbit | u1_t_tmpbit) & (U1)TRIPCOM_MS_NVMSTS_FAIL);
    u1_t_stsbit = u1_t_sucbit | u1_t_faibit;

    u1_t_tmpbit = u1_g_TripcomMsGetNvmRslt(stp_a_CNTT->u1_ms_odocnt_id);
    u1_t_sucbit = (U1)((u1_t_stsbit & u1_t_tmpbit) & (U1)TRIPCOM_MS_NVMSTS_SUC);
    u1_t_faibit = (U1)((u1_t_stsbit | u1_t_tmpbit) & (U1)TRIPCOM_MS_NVMSTS_FAIL);
    u1_t_stsbit = u1_t_sucbit | u1_t_faibit;

    return(u1_t_stsbit);
}

/*===================================================================================================================================*/
/* static  U2      u2_s_AvgEconResConv(const ST_AVGECON_CNTT * stp_a_CNTT, U4 u4_a_xecon)                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U2      u2_s_AvgEconResConv(const ST_AVGECON_CNTT * stp_a_CNTT, U4 u4_a_xecon)
{
    U2          u2_t_ret;
    U4          u4_t_remain;
    U4          u4_t_rndhlf;

    u4_t_remain = u4_a_xecon % (U4)(stp_a_CNTT->u2_cantx_resconv);
    u4_t_rndhlf = (U4)(stp_a_CNTT->u2_cantx_resconv) >> AVGECON_RNDHLF_SFT;
    u4_a_xecon /= (U4)(stp_a_CNTT->u2_cantx_resconv);
    if (u4_t_rndhlf < u4_t_remain) {
        u4_a_xecon++;
    }
    u2_t_ret = stp_a_CNTT->u2_cantx_max;
    if (u4_a_xecon < (U4)u2_t_ret) {
        u2_t_ret = (U2)u4_a_xecon;
    }

    return (u2_t_ret);
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
/*  1.0.2    10/07/2020  YA       Change for 800B CV-R                                                                               */
/*  2.0.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*  2.0.2    10/27/2021  TK       QAC supported.                                                                                     */
/*  2.1.0    02/18/2025  MaO(M)   Add privacy data delete/result API                                                                 */
/*                                                                                                                                   */
/*  * HY   = Hidefumi Yoshida, Denso                                                                                                 */
/*  * YA   = Yuhei Aoyama, DensoTechno                                                                                               */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * TK   = Takanori Kuno, Denso Techno                                                                                             */
/*  * MaO(M) = Masayuki Okada, NTT Data MSE                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/
