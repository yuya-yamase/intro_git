/* 2.0.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Average Hydrogen Economy for Trip Computer                                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define AVGHE_KMPKG_C_MAJOR                     (2)
#define AVGHE_KMPKG_C_MINOR                     (0)
#define AVGHE_KMPKG_C_PATCH                     (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "avghe_kmpkg_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((AVGHE_KMPKG_C_MAJOR != AVGHE_KMPKG_H_MAJOR) || \
     (AVGHE_KMPKG_C_MINOR != AVGHE_KMPKG_H_MINOR) || \
     (AVGHE_KMPKG_C_PATCH != AVGHE_KMPKG_H_PATCH))
#error "avghe_kmpkg.c and avghe_kmpkg.h : source and header files are inconsistent!"
#endif

#if ((AVGHE_KMPKG_C_MAJOR != AVGHE_KMPKG_CFG_H_MAJOR) || \
     (AVGHE_KMPKG_C_MINOR != AVGHE_KMPKG_CFG_H_MINOR) || \
     (AVGHE_KMPKG_C_PATCH != AVGHE_KMPKG_CFG_H_PATCH))
#error "avghe_kmpkg.c and avghe_kmpkg_cfg_private.h : source and header files are inconsistent!"
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
static  ST_AVGECON_VAR                          st_sp_avghe_var[AVGHE_NUM_CNTTS];
static  U1                                      u1_s_avghe_applsts;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_AVGECON_CNTT                    st_sp_AVGHE_CNTTS_CFG[AVGHE_NUM_CNTTS]      = {
    /*  #define AVGHE_CNTT_TA                           (3)     */
    {
        (U2)0U,
        (U2)TRIPCOM_RSTRQBIT_M_AVGFEHE_TA,
        (U2)0U,
        (U2)(10000U / TRIPCOM_TICK),                    /* 10s  */

        (U1)TRIPCOM_MS_ID_AVGHE_TA_HE,
        (U1)TRIPCOM_MS_ID_AVGHE_TA_HU,
        (U1)TRIPCOM_MS_ID_AVGHE_TA_OC,
        (U1)FALSE,

        (U1)FALSE,
        (U2)0xFFFCU,
        (U2)TRIPCOM_CANTX_TIMEOUT,
        (U2)TRIPCOM_CANTX_UNKNOWN,
        (U2)0xFFFDU,
        (U2)10U
    },
    /*  #define AVGHE_CNTT_DC                           (4)     */
    {
        (U2)TRIPCOM_RSTRQBIT_A_DRVCYC,
        (U2)0U,
        (U2)0U,
        (U2)(10000U / TRIPCOM_TICK),                    /* 10s  */

        (U1)TRIPCOM_MS_ID_AVGHE_DC_HE,
        (U1)TRIPCOM_MS_ID_AVGHE_DC_HU,
        (U1)TRIPCOM_MS_ID_AVGHE_DC_OC,
        (U1)FALSE,

        (U1)FALSE,
        (U2)0xFFFDU,
        (U2)TRIPCOM_CANTX_TIMEOUT,
        (U2)TRIPCOM_CANTX_UNKNOWN,
        (U2)0x0000U,
        (U2)10U
    },
    /*  #define AVGHE_CNTT_RF                           (5)     */
    {
        (U2)TRIPCOM_RSTRQBIT_A_FE_RECHRG,
        (U2)0U,
        (U2)TRIPCOM_PSRQBIT_A_FE_RECHRG,
        (U2)(10000U / TRIPCOM_TICK),                    /* 10s  */

        (U1)TRIPCOM_MS_ID_AVGHE_RF_HE,
        (U1)TRIPCOM_MS_ID_AVGHE_RF_HU,
        (U1)TRIPCOM_MS_ID_AVGHE_RF_OC,
        (U1)FALSE,

        (U1)FALSE,
        (U2)0xFFFCU,
        (U2)TRIPCOM_CANTX_TIMEOUT,
        (U2)TRIPCOM_CANTX_UNKNOWN,
        (U2)0x0000U,
        (U2)10U
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* void            vd_g_AvgHeInit(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_AvgHeInit(void)
{
    vd_g_AvgEconInit(&u1_s_avghe_applsts, st_sp_avghe_var, (U4)AVGHE_NUM_CNTTS);
}

/*===================================================================================================================================*/
/* void            vd_g_AvgHeApplTask(const U2 * u2_ap_STSFIELD)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_AvgHeApplTask(const U2 * u2_ap_STSFIELD)
{
    U2          u2_t_jdgbit;


    u1_s_avghe_applsts = (U1)TRIPCOM_STSBIT_VALID;
    u2_t_jdgbit = u2_ap_STSFIELD[TRIPCOM_STSFIELD_SNSR] & ((U2)TRIPCOM_SNSRBIT_ODOCNT_UNKNOWN | (U2)TRIPCOM_SNSRBIT_HYDRUSD_UNKNOWN);
    if (u2_t_jdgbit != (U2)0U) {
        u1_s_avghe_applsts  = (U1)TRIPCOM_STSBIT_UNKNOWN;
    }
    u2_t_jdgbit = u2_ap_STSFIELD[TRIPCOM_STSFIELD_SNSR] & ((U2)TRIPCOM_SNSRBIT_ODOCNT_INVALID | (U2)TRIPCOM_SNSRBIT_HYDRUSD_INVALID);
    if (u2_t_jdgbit != (U2)0U) {
        u1_s_avghe_applsts |= (U1)TRIPCOM_STSBIT_INVALID;
    }
}

/*===================================================================================================================================*/
/* U1              u1_g_AvgHeCalcTrnst(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_AvgHeCalcTrnst(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD)
{
    const ST_AVGECON_CNTT *                     stp_t_CNTT;
    ST_AVGECON_VAR *                            stp_t_var;
    U1                                          u1_t_update;


    u1_t_update = (U1)FALSE;
    if (u1_a_CNTTID < (U1)AVGHE_NUM_CNTTS) {
        stp_t_CNTT  = &st_sp_AVGHE_CNTTS_CFG[u1_a_CNTTID];
        stp_t_var   = &st_sp_avghe_var[u1_a_CNTTID];
        u1_t_update = u1_g_AvgEconCalcTrnst(stp_t_CNTT, stp_t_var, u2_ap_STSFIELD);
    }

    return (u1_t_update);
}

/*===================================================================================================================================*/
/* void            vd_g_AvgHeAccmlt(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD, const U4 * u4_ap_DELTA)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_AvgHeAccmlt(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD, const U4 * u4_ap_DELTA)
{
    const ST_AVGECON_CNTT *                     stp_t_CNTT;
    U4                                          u4_t_hydrusd;
    U4                                          u4_t_odocnt;
    U2                                          u2_t_jdgbit;


    if (u1_a_CNTTID < (U1)AVGHE_NUM_CNTTS) {
        stp_t_CNTT   = &st_sp_AVGHE_CNTTS_CFG[u1_a_CNTTID];
        u2_t_jdgbit  = (U2)u1_s_avghe_applsts;
        u2_t_jdgbit |= (u2_ap_STSFIELD[TRIPCOM_STSFIELD_OTHRQ] & stp_t_CNTT->u2_pause);

        u4_t_hydrusd = u4_ap_DELTA[TRIPCOM_DELTA_DC_HYDRUSD_PC];
        u4_t_odocnt  = u4_ap_DELTA[TRIPCOM_DELTA_DC_ODOCNT_PC];

        vd_g_AvgEconAccmlt(stp_t_CNTT, st_sp_avghe_var[u1_a_CNTTID].u1_initupdt, u2_t_jdgbit, u4_t_hydrusd, u4_t_odocnt);
    }
}

/*===================================================================================================================================*/
/* void            vd_g_AvgHeUpdt(const U1 u1_a_CNTTID)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_AvgHeUpdt(const U1 u1_a_CNTTID)
{
    const ST_AVGECON_CNTT *                     stp_t_CNTT;


    if (u1_a_CNTTID < (U1)AVGHE_NUM_CNTTS) {
        stp_t_CNTT = &st_sp_AVGHE_CNTTS_CFG[u1_a_CNTTID];
        vd_g_AvgEconUpdt(stp_t_CNTT, (U1)AVGECON_ENGYTYPE_HYDR);
    }
}

/*===================================================================================================================================*/
/* U1              u1_g_AvgHeKmpkg(const U1 u1_a_AVG_HE_CH, U4 * u4p_a_kmpkg)                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_AvgHeKmpkg(const U1 u1_a_AVG_HE_CH, U4 * u4p_a_kmpkg)
{
    U1          u1_t_status;


    u1_t_status = (U1)TRIPCOM_STSBIT_INVALID;
    if (u1_a_AVG_HE_CH < (U1)AVGHE_NUM_CNTTS) {
        if (u4p_a_kmpkg != vdp_PTR_NA) {
            (*u4p_a_kmpkg) = u4_g_TripcomMsGetAccmltVal(st_sp_AVGHE_CNTTS_CFG[u1_a_AVG_HE_CH].u1_ms_economy_id);
        }
        u1_t_status = u1_s_avghe_applsts;
    }

    return (u1_t_status);
}

/*===================================================================================================================================*/
/* U2              u2_g_AvgHeCalcTx(const U1 u1_a_CNTTID, const U1 u1_a_UNIT)                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2              u2_g_AvgHeCalcTx(const U1 u1_a_CNTTID, const U1 u1_a_UNIT)
{
    const ST_AVGECON_CNTT *                     stp_t_CNTT;
    U2                                          u2_t_txval;


    u2_t_txval = (U2)TRIPCOM_CANTX_UNKNOWN;

    if (u1_a_CNTTID < (U1)AVGHE_NUM_CNTTS) {
        stp_t_CNTT = &st_sp_AVGHE_CNTTS_CFG[u1_a_CNTTID];

        if ((u1_s_avghe_applsts & (U1)TRIPCOM_STSBIT_INVALID) != (U1)0U) {
            u2_t_txval = stp_t_CNTT->u2_cantx_fail;
        }
        else {
            u2_t_txval = u2_g_AvgEconCalcTx(stp_t_CNTT, st_sp_avghe_var[u1_a_CNTTID].u1_rstterm, u1_a_UNIT, (U1)AVGECON_ENGYTYPE_HYDR);
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
/*                                                                                                                                   */
/*  * HY   = Hidefumi Yoshida, Denso                                                                                                 */
/*  * YA   = Yuhei Aoyama, DensoTechno                                                                                               */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
