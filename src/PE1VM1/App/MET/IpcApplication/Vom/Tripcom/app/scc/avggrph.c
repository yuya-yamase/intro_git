/* 1.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Make Average XXXX Economy Graph                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define AVGGRPH_C_MAJOR                         (1)
#define AVGGRPH_C_MINOR                         (1)
#define AVGGRPH_C_PATCH                         (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "avggrph_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((AVGGRPH_C_MAJOR != AVGGRPH_H_MAJOR) || \
     (AVGGRPH_C_MINOR != AVGGRPH_H_MINOR) || \
     (AVGGRPH_C_PATCH != AVGGRPH_H_PATCH))
#error "avgecon.c and avgecon.h : source and header files are inconsistent!"
#endif

#if ((AVGGRPH_C_MAJOR != AVGGRPH_CFG_H_MAJOR) || \
     (AVGGRPH_C_MINOR != AVGGRPH_CFG_H_MINOR) || \
     (AVGGRPH_C_PATCH != AVGGRPH_CFG_H_PATCH))
#error "avgecon.c and avgecon_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define AVGGRPH_2BYTE_LSB               (16U)
#define AVGGRPH_2BYTE_MSK               (0x0000FFFFU)
#define AVGGRPH_1BYTE_LSB               (8U)
#define AVGGRPH_1BYTE_MSK               (0x00FFU)
#define AVGGRPH_ECON_MAX                (0xFFFFFFFEU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct {
    const U1   u1_size;
    U4 *       u4p_econ;
    U2 *       u2p_date;
    U1 *       u1p_latest;
    U4 *       u4p_max;
    U1         u1_msid_econ;
    U1         u1_msid_date;
    U1         u1_msid_ltst;
    U1         u1_msid_max;
    U1 *       u1p_rslt;
} ST_AVGGRPH_CNTT;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  U4    u4_s_avggrph_tafe_econ[AVGGRPH_SIZE_TA];
static  U4    u4_s_avggrph_1mfe_econ[AVGGRPH_SIZE_1M];
static  U4    u4_s_avggrph_taee_econ[AVGGRPH_SIZE_TA];
static  U4    u4_s_avggrph_1mee_econ[AVGGRPH_SIZE_1M];

static  U2    u2_s_avggrph_tafe_date[AVGGRPH_SIZE_TA];
static  U2    u2_s_avggrph_taee_date[AVGGRPH_SIZE_TA];

static  U1    u1_s_avggrph_tafe_latest;
static  U1    u1_s_avggrph_1mfe_latest;
static  U1    u1_s_avggrph_taee_latest;
static  U1    u1_s_avggrph_1mee_latest;

static  U4    u4_s_avggrph_tafe_max;
static  U4    u4_s_avggrph_taee_max;

static  U1    u1_s_avggrph_tafe_rslt;
static  U1    u1_s_avggrph_1mfe_rslt;
static  U1    u1_s_avggrph_taee_rslt;
static  U1    u1_s_avggrph_1mee_rslt;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  U1      u1_s_AvgGrphGetRslt(const U1 u1_a_CNTTID, const U1 u1_a_before);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_AVGGRPH_CNTT            st_sp_AVGGRPH_CNTTS_CFG[AVGGRPH_NUM_CNTT]      = {
    /*  #define AVGGRPH_CNTT_TAFE                       (0U)     */
    {
        (U1)AVGGRPH_SIZE_TA,
        &u4_s_avggrph_tafe_econ[0],
        &u2_s_avggrph_tafe_date[0],
        &u1_s_avggrph_tafe_latest,
        &u4_s_avggrph_tafe_max,
        (U1)TRIPCOM_MS_ID_AVGGRPH_TAFE_FE00,
        (U1)TRIPCOM_MS_ID_AVGGRPH_TAFE_DT00,
        (U1)TRIPCOM_MS_ID_AVGGRPH_TAFE_LTST,
        (U1)TRIPCOM_MS_ID_AVGGRPH_TAFE_MAX,
        &u1_s_avggrph_tafe_rslt
    },
    /*  #define AVGGRPH_CNTT_1MFE                       (1U)     */
    {
        (U1)AVGGRPH_SIZE_1M,
        &u4_s_avggrph_1mfe_econ[0],
        vdp_PTR_NA,
        &u1_s_avggrph_1mfe_latest,
        vdp_PTR_NA,
        (U1)TRIPCOM_MS_ID_AVGGRPH_1MFE_FE00,
        (U1)U1_MAX,
        (U1)TRIPCOM_MS_ID_AVGGRPH_1MFE_LTST,
        (U1)U1_MAX,
        &u1_s_avggrph_1mfe_rslt
    },
    /*  #define AVGGRPH_CNTT_TAEE                       (2U)     */
    {
        (U1)AVGGRPH_SIZE_TA,
        &u4_s_avggrph_taee_econ[0],
        &u2_s_avggrph_taee_date[0],
        &u1_s_avggrph_taee_latest,
        &u4_s_avggrph_taee_max,
        (U1)TRIPCOM_MS_ID_AVGGRPH_TAEE_EE00,
        (U1)TRIPCOM_MS_ID_AVGGRPH_TAEE_DT00,
        (U1)TRIPCOM_MS_ID_AVGGRPH_TAEE_LTST,
        (U1)TRIPCOM_MS_ID_AVGGRPH_TAEE_MAX,
        &u1_s_avggrph_taee_rslt
    },
    /*  #define AVGGRPH_CNTT_1MEE                       (3U)     */
    {
        (U1)AVGGRPH_SIZE_1M,
        &u4_s_avggrph_1mee_econ[0],
        vdp_PTR_NA,
        &u1_s_avggrph_1mee_latest,
        vdp_PTR_NA,
        (U1)TRIPCOM_MS_ID_AVGGRPH_1MEE_EE00,
        (U1)U1_MAX,
        (U1)TRIPCOM_MS_ID_AVGGRPH_1MEE_LTST,
        (U1)U1_MAX,
        &u1_s_avggrph_1mee_rslt
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* void            vd_g_AvgGrphBonInit(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_AvgGrphInit(void)
{
    U4                          u4_t_loop;
    U4                          u4_t_loop2;
    const ST_AVGGRPH_CNTT *     st_tp_cfg;
    U1                          u1_t_msid;
    U4                          u4_t_datedata;

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)AVGGRPH_NUM_CNTT; u4_t_loop++) {
        st_tp_cfg = &st_sp_AVGGRPH_CNTTS_CFG[u4_t_loop];
        *(st_tp_cfg->u1p_latest) = (U1)u4_g_TripcomMsGetAccmltVal(st_tp_cfg->u1_msid_ltst);
        for(u4_t_loop2 = (U1)0U; u4_t_loop2 < st_tp_cfg->u1_size; u4_t_loop2++) {
            u1_t_msid = st_tp_cfg->u1_msid_econ + (U1)u4_t_loop2;
            st_tp_cfg->u4p_econ[u4_t_loop2] = u4_g_TripcomMsGetAccmltVal(u1_t_msid);
            if(st_tp_cfg->u2p_date != vdp_PTR_NA){
                u1_t_msid = st_tp_cfg->u1_msid_date + (U1)u4_t_loop2;
                u4_t_datedata = u4_g_TripcomMsGetAccmltVal(u1_t_msid);
                st_tp_cfg->u2p_date[u4_t_loop2] = (U2)(u4_t_datedata & (U4)AVGGRPH_2BYTE_MSK);
            }
        }
        if(st_tp_cfg->u4p_max != vdp_PTR_NA){
            *(st_tp_cfg->u4p_max) = u4_g_TripcomMsGetAccmltVal(st_tp_cfg->u1_msid_max);
        }
    }
}

/*===================================================================================================================================*/
/* void            vd_g_AvgGrphUpdt(const U1 u1_a_CNTTID, const U4 u4_a_data, const U1 u1_a_rwrqst)                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_CNTTID:AVGGRPH_CNTT_XXX   u4_a_data:Economy Data                                                            */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_AvgGrphUpdt(const U1 u1_a_CNTTID, const U4 u4_a_data, const U1 u1_a_rwrqst)
{
    U1                          u1_t_next;
    const ST_AVGGRPH_CNTT *     st_tp_cfg;
    U1                          u1_t_msid;
    U1                          u1_t_rx;
    U2                          u2_t_mmdd;

    u1_t_rx = (U1)0U;
    if(u1_a_CNTTID < (U1)AVGGRPH_NUM_CNTT){
        st_tp_cfg = &st_sp_AVGGRPH_CNTTS_CFG[u1_a_CNTTID];
        if((*(st_tp_cfg->u1p_latest) + (U1)1U) < st_tp_cfg->u1_size){
            u1_t_next = *(st_tp_cfg->u1p_latest) + (U1)1U;
        } else {
            u1_t_next = (U1)0U;
        }
        if(u4_a_data > (U4)AVGGRPH_ECON_MAX){
            st_tp_cfg->u4p_econ[u1_t_next] = (U4)AVGGRPH_ECON_MAX;
        }
        else{
            st_tp_cfg->u4p_econ[u1_t_next] = u4_a_data;
        }
        u1_t_msid = st_tp_cfg->u1_msid_econ + u1_t_next;
        vd_g_TripcomMsSetAccmltVal(u1_t_msid, st_tp_cfg->u4p_econ[u1_t_next]);
        if(u1_a_rwrqst == (U1)TRUE){
            vd_g_TripcomMsSetNvmRqst(u1_t_msid);
        }
        if(st_tp_cfg->u2p_date != vdp_PTR_NA){
            (void)Com_ReceiveSignal(ComConf_ComSignal_M_DAY, &u1_t_rx);
            u2_t_mmdd = (((U2)u1_t_rx << YYMMDDWK_LSB_DA) & (U2)YYMMDDWK_BIT_DA);
            (void)Com_ReceiveSignal(ComConf_ComSignal_M_MONTH, &u1_t_rx);
            u2_t_mmdd |= (((U2)u1_t_rx << YYMMDDWK_LSB_MO) & (U2)YYMMDDWK_BIT_MO);
            st_tp_cfg->u2p_date[u1_t_next] = u2_t_mmdd >> YYMMDDWK_LSB_DA;
            u1_t_msid = st_tp_cfg->u1_msid_date + u1_t_next;
            vd_g_TripcomMsSetAccmltVal(u1_t_msid, (U4)(st_tp_cfg->u2p_date[u1_t_next]));
            if(u1_a_rwrqst == (U1)TRUE){
                vd_g_TripcomMsSetNvmRqst(u1_t_msid);
            }
        }
        if(st_tp_cfg->u4p_max != vdp_PTR_NA){
            if((*(st_tp_cfg->u4p_max) < u4_a_data) || (*(st_tp_cfg->u4p_max) == (U4)U4_MAX)){
                *(st_tp_cfg->u4p_max) = u4_a_data;
                vd_g_TripcomMsSetAccmltVal(st_tp_cfg->u1_msid_max, u4_a_data);
                if(u1_a_rwrqst == (U1)TRUE){
                    vd_g_TripcomMsSetNvmRqst(st_tp_cfg->u1_msid_max);
                }
            }
        }
        *(st_tp_cfg->u1p_latest) = u1_t_next;
        vd_g_TripcomMsSetAccmltVal(st_tp_cfg->u1_msid_ltst, (U4)u1_t_next);
        if(u1_a_rwrqst == (U1)TRUE){
            vd_g_TripcomMsSetNvmRqst(st_tp_cfg->u1_msid_ltst);
        }
    }
}

/*===================================================================================================================================*/
/* void            vd_g_AvgGrphReset(const U1 u1_a_CNTTID)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_CNTTID:AVGGRPH_CNTT_XXX                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_AvgGrphReset(const U1 u1_a_CNTTID)
{
    U4                          u4_t_loop;
    const ST_AVGGRPH_CNTT *     st_tp_cfg;
    U1                          u1_t_msid;

    if(u1_a_CNTTID < (U1)AVGGRPH_NUM_CNTT){
        st_tp_cfg = &st_sp_AVGGRPH_CNTTS_CFG[u1_a_CNTTID];
        *(st_tp_cfg->u1p_latest) = (U1)0U;
        for(u4_t_loop = (U4)0U; u4_t_loop < st_tp_cfg->u1_size; u4_t_loop++) {
            st_tp_cfg->u4p_econ[u4_t_loop] = (U4)U4_MAX;
            u1_t_msid = st_tp_cfg->u1_msid_econ + (U1)u4_t_loop;
            vd_g_TripcomMsSetAccmltVal(u1_t_msid, st_tp_cfg->u4p_econ[u4_t_loop]);
            vd_g_TripcomMsSetNvmRqst(u1_t_msid);
            if(st_tp_cfg->u2p_date != vdp_PTR_NA){
                st_tp_cfg->u2p_date[u4_t_loop] = (U2)U2_MAX;
                u1_t_msid = st_tp_cfg->u1_msid_date + (U1)u4_t_loop;
                vd_g_TripcomMsSetAccmltVal(u1_t_msid, (U4)U2_MAX);
                vd_g_TripcomMsSetNvmRqst(u1_t_msid);
            }
        }
        if(st_tp_cfg->u4p_max != vdp_PTR_NA){
            *(st_tp_cfg->u4p_max) = (U4)U4_MAX;
            vd_g_TripcomMsSetAccmltVal(st_tp_cfg->u1_msid_max, (U4)U4_MAX);
            vd_g_TripcomMsSetNvmRqst(st_tp_cfg->u1_msid_max);
        }
        vd_g_TripcomMsSetAccmltVal(st_tp_cfg->u1_msid_ltst, (U4)0U);
        vd_g_TripcomMsSetNvmRqst(st_tp_cfg->u1_msid_ltst);
        vd_g_AvgGrphUpdtRslt();
    }
}

/*===================================================================================================================================*/
/* U4               u4_g_AvgGrphData(const U1 u1_a_CNTTID, U4 * u4_ap_data, U1 * u1_ap_month, U1 * u1_ap_day)                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_CNTTID:AVGGRPH_CNTT_XXX   u4_ap_data:Economy Data   u1_ap_month,u1_ap_day:Date                              */
/*  Return:         u4_t_max:Max                                                                                                     */
/*===================================================================================================================================*/
U4              u4_g_AvgGrphData(const U1 u1_a_CNTTID, U4 * u4_ap_data, U1 * u1_ap_month, U1 * u1_ap_day)
{
    const ST_AVGGRPH_CNTT *     st_tp_cfg;
    U1                          u1_t_idx;
    U4                          u4_t_loop;
    U4                          u4_t_max;

    u4_t_max = (U4)U4_MAX;
    if(u1_a_CNTTID < (U1)AVGGRPH_NUM_CNTT){
        st_tp_cfg = &st_sp_AVGGRPH_CNTTS_CFG[u1_a_CNTTID];
        if(*(st_tp_cfg->u1p_latest) < st_tp_cfg->u1_size){
            u1_t_idx = *(st_tp_cfg->u1p_latest);
            for(u4_t_loop = (U4)0U; u4_t_loop < st_tp_cfg->u1_size; u4_t_loop++) {
                if(u1_t_idx < (st_tp_cfg->u1_size - (U1)1U)){
                    u1_t_idx++;
                } else {
                    u1_t_idx = (U1)0U;
                }
                *u4_ap_data = st_tp_cfg->u4p_econ[u1_t_idx];
                u4_ap_data++;
                if((u1_ap_month != vdp_PTR_NA) && (st_tp_cfg->u2p_date != vdp_PTR_NA)){
                    *u1_ap_month = (U1)((st_tp_cfg->u2p_date[u1_t_idx] & (U2)((U2)AVGGRPH_1BYTE_MSK << AVGGRPH_1BYTE_LSB)) >> AVGGRPH_1BYTE_LSB);
                    u1_ap_month++;
                }
                if((u1_ap_day != vdp_PTR_NA) && (st_tp_cfg->u2p_date != vdp_PTR_NA)){
                    *u1_ap_day = (U1)(st_tp_cfg->u2p_date[u1_t_idx] & (U2)AVGGRPH_1BYTE_MSK);
                    u1_ap_day++;
                }
            }
            if(st_tp_cfg->u4p_max != vdp_PTR_NA){
                u4_t_max = *(st_tp_cfg->u4p_max);
            }
        }
    }
    return(u4_t_max);
}

/*===================================================================================================================================*/
/* void            vd_g_AvgGrphUpdtRslt(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_AvgGrphUpdtRslt(void)
{
    U4                          u4_t_loop;
    U4                          u4_t_loop2;
    const ST_AVGGRPH_CNTT *     st_tp_cfg;
    U1                          u1_t_msid;
    U1                          u1_t_rslt;

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)AVGGRPH_NUM_CNTT; u4_t_loop++) {
        u1_t_rslt = (U1)TRIPCOM_MS_NVMSTS_SUC;
        st_tp_cfg = &st_sp_AVGGRPH_CNTTS_CFG[u4_t_loop];
        for(u4_t_loop2 = (U4)0U; u4_t_loop2 < (U4)(st_tp_cfg->u1_size); u4_t_loop2++) {
            u1_t_msid = st_tp_cfg->u1_msid_econ + (U1)u4_t_loop2;
            u1_t_rslt = u1_s_AvgGrphGetRslt(u1_t_msid, u1_t_rslt);
            if(st_tp_cfg->u2p_date != vdp_PTR_NA){
                u1_t_msid = st_tp_cfg->u1_msid_date + (U1)u4_t_loop2;
                u1_t_rslt = u1_s_AvgGrphGetRslt(u1_t_msid, u1_t_rslt);
            }
        }
        if(st_tp_cfg->u4p_max != vdp_PTR_NA){
            u1_t_rslt = u1_s_AvgGrphGetRslt(st_tp_cfg->u1_msid_max, u1_t_rslt);
        }
        u1_t_rslt = u1_s_AvgGrphGetRslt(st_tp_cfg->u1_msid_ltst, u1_t_rslt);

        if((u1_t_rslt & (U1)TRIPCOM_MS_NVMSTS_FAIL) != (U1)0U){
            *(st_tp_cfg->u1p_rslt) = (U1)TRIPCOM_MS_NVMSTS_FAIL;
        }
        else if((u1_t_rslt & (U1)TRIPCOM_MS_NVMSTS_SUC) != (U1)0U){
            *(st_tp_cfg->u1p_rslt) = (U1)TRIPCOM_MS_NVMSTS_SUC;
        }
        else{
            *(st_tp_cfg->u1p_rslt) = (U1)TRIPCOM_MS_NVMSTS_NON;
        }
    }
}

/*===================================================================================================================================*/
/* static U1       u1_s_AvgGrphGetRslt(const U1 u1_a_CNTTID)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_CNTTID:AVGGRPH_CNTT_XXX                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_AvgGrphGetRslt(const U1 u1_a_CNTTID, const U1 u1_a_before)
{
    U1                          u1_t_temp;
    U1                          u1_t_rslt;

    u1_t_rslt  = u1_a_before;
    u1_t_temp  = u1_g_TripcomMsGetNvmRslt(u1_a_CNTTID);
    u1_t_rslt |= (U1)(u1_t_temp & (U1)TRIPCOM_MS_NVMSTS_FAIL);
    u1_t_rslt &= (U1)(u1_t_temp & (U1)TRIPCOM_MS_NVMSTS_SUC);

    return(u1_t_rslt);
}

/*===================================================================================================================================*/
/* U1              u1_g_AvgGrphRslt(const U1 u1_a_CNTTID)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_CNTTID:AVGGRPH_CNTT_XXX                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_AvgGrphRslt(const U1 u1_a_CNTTID)
{
    U1                          u1_t_rslt;

    u1_t_rslt = (U1)TRIPCOM_MS_NVMSTS_NON;
    if(u1_a_CNTTID < (U1)AVGGRPH_NUM_CNTT){
        u1_t_rslt = *(st_sp_AVGGRPH_CNTTS_CFG[u1_a_CNTTID].u1p_rslt);
    }
    return(u1_t_rslt);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    12/19/2023  TH       New.                                                                                               */
/*  1.1.0    05/08/2025  MN       Change for BEV PreCV.                                                                              */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/* BEV-1     05/08/2025  MN       Change for BEV PreCV.(MET-M_CLKCTL-CSTD-0-/MET-M_CAL-CSTD-0-)                                      */
/*                                                                                                                                   */
/*  * TH   = Taisuke Hirakawa, KSE                                                                                                   */
/*  * MN   = Mikiya Negishi, KSE                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
