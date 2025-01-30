/* 2.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Average Fuel Economy for Trip Computer                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define AVGFE_KMPL_C_MAJOR                      (2)
#define AVGFE_KMPL_C_MINOR                      (1)
#define AVGFE_KMPL_C_PATCH                      (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "avgfe_kmpl_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((AVGFE_KMPL_C_MAJOR != AVGFE_KMPL_H_MAJOR) || \
     (AVGFE_KMPL_C_MINOR != AVGFE_KMPL_H_MINOR) || \
     (AVGFE_KMPL_C_PATCH != AVGFE_KMPL_H_PATCH))
#error "avgfe_kmpl.c and avgfe_kmpl.h : source and header files are inconsistent!"
#endif

#if ((AVGFE_KMPL_C_MAJOR != AVGFE_KMPL_CFG_H_MAJOR) || \
     (AVGFE_KMPL_C_MINOR != AVGFE_KMPL_CFG_H_MINOR) || \
     (AVGFE_KMPL_C_PATCH != AVGFE_KMPL_CFG_H_PATCH))
#error "avgfe_kmpl.c and avgfe_kmpl_cfg_private.h : source and header files are inconsistent!"
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
static  ST_AVGECON_VAR                          st_sp_avgfe_var[AVGFE_NUM_CNTTS];
static  U1                                      u1_s_avgfe_applsts;
static  U4                                      u4_s_avgfe_econ_prev_rst;
static  U1                                      u1_s_avgfe_econ_init_bk;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_AVGECON_CNTT                    st_sp_AVGFE_CNTTS_CFG[AVGFE_NUM_CNTTS]      = {
    /*  #define AVGFE_CNTT_TA                           (0)     */
    {
        (U2)0U,
        (U2)TRIPCOM_RSTRQBIT_M_AVGFEHE_TA,
        (U2)0U,
        (U2)(10000U / TRIPCOM_TICK),                    /* 10s  */

        (U1)TRIPCOM_MS_ID_AVGFE_TA_FE,
        (U1)TRIPCOM_MS_ID_AVGFE_TA_FU,
        (U1)TRIPCOM_MS_ID_AVGFE_TA_OC,
        (U1)FALSE,

        (U1)FALSE,
        (U2)0xFFFCU,
        (U2)TRIPCOM_CANTX_TIMEOUT,
        (U2)TRIPCOM_CANTX_UNKNOWN,
        (U2)0xFFFDU,
        (U2)100U
    },
    /*  #define AVGFE_CNTT_DC                           (1)     */
    {
        (U2)TRIPCOM_RSTRQBIT_A_DRVCYC,
        (U2)0U,
        (U2)0U,
        (U2)(10000U / TRIPCOM_TICK),                    /* 10s  */

        (U1)TRIPCOM_MS_ID_AVGFE_DC_FE,
        (U1)TRIPCOM_MS_ID_AVGFE_DC_FU,
        (U1)TRIPCOM_MS_ID_AVGFE_DC_OC,
        (U1)FALSE,

        (U1)FALSE,
        (U2)0xFFFCU,
        (U2)TRIPCOM_CANTX_TIMEOUT,
        (U2)TRIPCOM_CANTX_UNKNOWN,
        (U2)0x0000U,
        (U2)100U
    },
    /*  #define AVGFE_CNTT_RF                           (2)     */
    {
        (U2)(TRIPCOM_RSTRQBIT_A_FE_RECHRG | TRIPCOM_RSTRQBIT_A_FRCRECHRG),
        (U2)0U,
        (U2)(TRIPCOM_PSRQBIT_A_FE_RECHRG  | TRIPCOM_PSRQBIT_A_FRCRECHRG | TRIPCOM_PSRQBIT_A_EVRUN),
        (U2)(10000U / TRIPCOM_TICK),                    /* 10s  */

        (U1)TRIPCOM_MS_ID_AVGFE_RF_FE,
        (U1)TRIPCOM_MS_ID_AVGFE_RF_FU,
        (U1)TRIPCOM_MS_ID_AVGFE_RF_OC,
        (U1)FALSE,

        (U1)FALSE,
        (U2)0xFFFCU,
        (U2)TRIPCOM_CANTX_TIMEOUT,
        (U2)TRIPCOM_CANTX_UNKNOWN,
        (U2)0x0000U,
        (U2)100U
    },
    /*  #define AVGFE_CNTT_ONEM                         (3)     */
    {
        (U2)0U,
        (U2)TRIPCOM_RSTRQBIT_M_AVGFEHE_ONEM,
        (U2)0U,
        (U2)(60000U / TRIPCOM_TICK),                    /* 60s  */

        (U1)TRIPCOM_MS_ID_AVGFE_ONEM_FE,
        (U1)TRIPCOM_MS_ID_AVGFE_ONEM_FU,
        (U1)TRIPCOM_MS_ID_AVGFE_ONEM_OC,
        (U1)TRUE,

        (U1)FALSE,
        (U2)0xFFFDU,
        (U2)TRIPCOM_CANTX_TIMEOUT,
        (U2)TRIPCOM_CANTX_UNKNOWN,
        (U2)0xFFFEU,
        (U2)100U
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* void            vd_g_AvgFeInit(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_AvgFeInit(void)
{
    vd_g_AvgEconInit(&u1_s_avgfe_applsts, st_sp_avgfe_var, (U4)AVGFE_NUM_CNTTS);
    u4_s_avgfe_econ_prev_rst = (U4)0U;
    u1_s_avgfe_econ_init_bk  = (U1)FALSE;
}

/*===================================================================================================================================*/
/* void            vd_g_AvgFeApplTask(const U2 * u2_ap_STSFIELD)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_AvgFeApplTask(const U2 * u2_ap_STSFIELD)
{
    U2          u2_t_jdgbit;


    u1_s_avgfe_applsts = (U1)TRIPCOM_STSBIT_VALID;
    u2_t_jdgbit = u2_ap_STSFIELD[TRIPCOM_STSFIELD_SNSR] & ((U2)TRIPCOM_SNSRBIT_ODOCNT_UNKNOWN | (U2)TRIPCOM_SNSRBIT_FUELUSD_UNKNOWN);
    if (u2_t_jdgbit != (U2)0U) {
        u1_s_avgfe_applsts  = (U1)TRIPCOM_STSBIT_UNKNOWN;
    }
    u2_t_jdgbit = u2_ap_STSFIELD[TRIPCOM_STSFIELD_SNSR] & ((U2)TRIPCOM_SNSRBIT_ODOCNT_INVALID | (U2)TRIPCOM_SNSRBIT_FUELUSD_INVALID);
    if (u2_t_jdgbit != (U2)0U) {
        u1_s_avgfe_applsts |= (U1)TRIPCOM_STSBIT_INVALID;
    }
}

/*===================================================================================================================================*/
/* U1              u1_g_AvgFeCalcTrnst(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_AvgFeCalcTrnst(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD)
{
    const ST_AVGECON_CNTT *                     stp_t_CNTT;
    ST_AVGECON_VAR *                            stp_t_var;
    U1                                          u1_t_update;


    u1_t_update = (U1)FALSE;
    if (u1_a_CNTTID < (U1)AVGFE_NUM_CNTTS) {
        stp_t_CNTT  = &st_sp_AVGFE_CNTTS_CFG[u1_a_CNTTID];
        stp_t_var   = &st_sp_avgfe_var[u1_a_CNTTID];

        u1_t_update = u1_g_AvgEconCalcTrnst(stp_t_CNTT, stp_t_var, u2_ap_STSFIELD);

        if((u1_a_CNTTID == (U1)AVGFE_CNTT_ONEM) && 
           ((u2_ap_STSFIELD[TRIPCOM_STSFIELD_AUTO_RSTRQ] & (U2)TRIPCOM_RSTRQBIT_A_DRVCYC_OFF) !=(U2)0U)) {
            stp_t_var->u1_initupdt   = (U1)TRUE;
            stp_t_var->u2_calctm     = (U2)0U;
            u1_t_update              = (U1)TRUE;
        }
        if((u1_a_CNTTID == (U1)AVGFE_CNTT_TA) &&
           (stp_t_var->u1_initupdt == (U1)TRUE) && (u1_s_avgfe_econ_init_bk == (U1)FALSE)) {
            u4_s_avgfe_econ_prev_rst = u4_g_TripcomMsGetAccmltVal(stp_t_CNTT->u1_ms_economy_id);
        }
    }

    return (u1_t_update);
}

/*===================================================================================================================================*/
/* void            vd_g_AvgFeAccmlt(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD, const U4 * u4_ap_DELTA)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_AvgFeAccmlt(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD, const U4 * u4_ap_DELTA)
{
    const ST_AVGECON_CNTT *                     stp_t_CNTT;
    U4                                          u4_t_fuelusd;
    U4                                          u4_t_odocnt;
    U2                                          u2_t_jdgbit;


    if (u1_a_CNTTID < (U1)AVGFE_NUM_CNTTS) {
        stp_t_CNTT   = &st_sp_AVGFE_CNTTS_CFG[u1_a_CNTTID];
        u2_t_jdgbit  = (U2)u1_s_avgfe_applsts;
        u2_t_jdgbit |= (u2_ap_STSFIELD[TRIPCOM_STSFIELD_OTHRQ] & stp_t_CNTT->u2_pause);

        u4_t_fuelusd = u4_ap_DELTA[TRIPCOM_DELTA_DC_FUELUSD_PC];
        u4_t_odocnt  = u4_ap_DELTA[TRIPCOM_DELTA_DC_ODOCNT_PC];

        vd_g_AvgEconAccmlt(stp_t_CNTT, st_sp_avgfe_var[u1_a_CNTTID].u1_initupdt, u2_t_jdgbit, u4_t_fuelusd, u4_t_odocnt);
    }
}

/*===================================================================================================================================*/
/* void            vd_g_AvgFeUpdt(const U1 u1_a_CNTTID)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_AvgFeUpdt(const U1 u1_a_CNTTID)
{
    const ST_AVGECON_CNTT *                     stp_t_CNTT;


    if (u1_a_CNTTID < (U1)AVGFE_NUM_CNTTS) {
        stp_t_CNTT = &st_sp_AVGFE_CNTTS_CFG[u1_a_CNTTID];
        vd_g_AvgEconUpdt(stp_t_CNTT, (U1)AVGECON_ENGYTYPE_FUEL);
    }
}
/*===================================================================================================================================*/
/* void            vd_g_AvgFeGrphUpdt(const U1 u1_a_CNTTID)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_AvgFeGrphUpdt(const U1 u1_a_CNTTID)
{
    const ST_AVGECON_CNTT *                     stp_t_CNTT;
    U4                                          u4_t_econ;

    if (u1_a_CNTTID < (U1)AVGFE_NUM_CNTTS) {
        stp_t_CNTT = &st_sp_AVGFE_CNTTS_CFG[u1_a_CNTTID];
        switch(u1_a_CNTTID){
            case (U1)AVGFE_CNTT_TA:
                if((st_sp_avgfe_var[AVGFE_CNTT_TA].u1_initupdt == (U1)TRUE)
                && (u1_s_avgfe_econ_init_bk == (U1)FALSE)){
                    vd_g_AvgGrphUpdt((U1)AVGGRPH_CNTT_TAFE, u4_s_avgfe_econ_prev_rst, (U1)TRUE);
                }
                u1_s_avgfe_econ_init_bk = st_sp_avgfe_var[AVGFE_CNTT_TA].u1_initupdt;
                break;
            case (U1)AVGFE_CNTT_ONEM:
                u4_t_econ  = u4_g_TripcomMsGetAccmltVal(stp_t_CNTT->u1_ms_economy_id);
                if(st_sp_avgfe_var[AVGFE_CNTT_ONEM].u1_initupdt == (U1)FALSE){
                    vd_g_AvgGrphUpdt((U1)AVGGRPH_CNTT_1MFE, u4_t_econ, (U1)FALSE);
                }
                break;
            default:
                /* Do Nothing */
                break;
        }
    }
}

/*===================================================================================================================================*/
/* U1              u1_g_AvgFeKmpl(const U1 u1_a_AVG_FE_CH, U4 * u4p_a_kmpl)                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_AvgFeKmpl(const U1 u1_a_AVG_FE_CH, U4 * u4p_a_kmpl)
{
    U1          u1_t_status;


    u1_t_status = (U1)TRIPCOM_STSBIT_INVALID;
    if (u1_a_AVG_FE_CH < (U1)AVGFE_NUM_CNTTS) {
        if (u4p_a_kmpl != vdp_PTR_NA) {
            (*u4p_a_kmpl) = u4_g_TripcomMsGetAccmltVal(st_sp_AVGFE_CNTTS_CFG[u1_a_AVG_FE_CH].u1_ms_economy_id);
        }
        u1_t_status = u1_s_avgfe_applsts;
    }

    return (u1_t_status);
}

/*===================================================================================================================================*/
/* U2              u2_g_AvgFeCalcTx(const U1 u1_a_CNTTID, const U1 u1_a_UNIT)                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2              u2_g_AvgFeCalcTx(const U1 u1_a_CNTTID, const U1 u1_a_UNIT)
{
    const ST_AVGECON_CNTT *                     stp_t_CNTT;
    U2                                          u2_t_txval;


    u2_t_txval = (U2)TRIPCOM_CANTX_UNKNOWN;

    if (u1_a_CNTTID < (U1)AVGFE_NUM_CNTTS) {
        stp_t_CNTT = &st_sp_AVGFE_CNTTS_CFG[u1_a_CNTTID];

        if ((u1_s_avgfe_applsts & (U1)TRIPCOM_STSBIT_INVALID) != (U1)0U) {
            u2_t_txval = stp_t_CNTT->u2_cantx_fail;
        }
        else {
            u2_t_txval = u2_g_AvgEconCalcTx(stp_t_CNTT, st_sp_avgfe_var[u1_a_CNTTID].u1_rstterm, u1_a_UNIT, (U1)AVGECON_ENGYTYPE_FUEL);
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
/*  1.1.0    03/19/2020  YA       Change for 800B CV                                                                                 */
/*  1.1.1    10/07/2020  YA       Change for 800B CV-R.                                                                              */
/*  2.0.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*  2.0.2    02/25/2022  TA(M)    Delete call vd_g_AvgFeUpdt((U1)AVGFE_CNTT_TA) at vd_g_AvgFeInit                                    */
/*  2.1.0    01/10/2024  TH       for 19PFv3  Add AvgGrph                                                                            */
/*                                                                                                                                   */
/*  * HY   = Hidefumi Yoshida, Denso                                                                                                 */
/*  * YA   = Yuhei Aoyama, DensoTechno                                                                                               */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * TH   = Taisuke Hirakawa, KSE                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
