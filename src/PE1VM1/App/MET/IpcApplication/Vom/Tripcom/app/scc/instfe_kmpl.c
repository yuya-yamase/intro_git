/* 2.0.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Instant Fuel Economy for Trip Computer                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define INSTFE_KMPL_C_MAJOR                     (2)
#define INSTFE_KMPL_C_MINOR                     (0)
#define INSTFE_KMPL_C_PATCH                     (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "instfe_kmpl_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((INSTFE_KMPL_C_MAJOR != INSTFE_KMPL_H_MAJOR) || \
     (INSTFE_KMPL_C_MINOR != INSTFE_KMPL_H_MINOR) || \
     (INSTFE_KMPL_C_PATCH != INSTFE_KMPL_H_PATCH))
#error "instfe_kmpl.c and instfe_kmpl.h : source and header files are inconsistent!"
#endif

#if ((INSTFE_KMPL_C_MAJOR != INSTFE_KMPL_CFG_H_MAJOR) || \
     (INSTFE_KMPL_C_MINOR != INSTFE_KMPL_CFG_H_MINOR) || \
     (INSTFE_KMPL_C_PATCH != INSTFE_KMPL_CFG_H_PATCH))
#error "instfe_kmpl.c and instfe_kmpl_cfg_private.h : source and header files are inconsistent!"
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
#define INSTFE_CALCSTS_ACT                    (0x02U)
#define INSTEE_UNIT_LP100KM                   (0x02U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  ST_INSTECON_VAR                         st_s_instfe_var;
static  U1                                      u1_s_instfe_prevsts;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_INSTECON_CNTT                   st_sp_INSTFE_CNTTS_CFG[INSTFE_NUM_CNTTS] = {
    /*  #define INSTFE_CNTT_RX                          (0)     */
    {
        (U2)TRIPCOM_RSTRQBIT_A_UPDTFEHUSD,

        (U1)TRIPCOM_MS_ID_INSTFE_FE,
        (U1)TRIPCOM_MS_ID_INSTFE_FU,
        (U1)TRIPCOM_MS_ID_INSTFE_OC,
        (U1)TRIPCOM_MS_ID_INSTFE_DV,

        (U1)100U,
        (U2)0xFFFDU,
        (U2)0xFFFDU,
        (U2)0xFFFCU
    },
    /*  #define INSTFEC_CNTT_RX                         (1)     */
    {
        (U2)TRIPCOM_RSTRQBIT_A_UPDTFEHUSD,

        (U1)TRIPCOM_MS_ID_INSTFE_FE,
        (U1)TRIPCOM_MS_ID_INSTFE_FU,
        (U1)TRIPCOM_MS_ID_INSTFE_OC,
        (U1)TRIPCOM_MS_ID_INSTFE_DV,

        (U1)10U,
        (U2)0xFFFDU,
        (U2)0xFFFDU,
        (U2)0xFFFCU
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* void            vd_g_InstFeInit(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_InstFeInit(void)
{
    vd_g_InstEconInit(&st_s_instfe_var, &u1_s_instfe_prevsts);
}

/*===================================================================================================================================*/
/* U1              u1_g_InstFeCalcTrnst(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD)                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_InstFeCalcTrnst(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD)
{
    const ST_INSTECON_CNTT *                     stp_t_CNTT;
    U1                                           u1_t_update;
    U1                                           u1_t_snsrsts;
    U2                                           u2_t_jdgbit;


    u1_t_snsrsts = (U1)TRIPCOM_STSBIT_VALID;
    u1_t_update  = (U1)FALSE;
    u2_t_jdgbit = u2_ap_STSFIELD[TRIPCOM_STSFIELD_SNSR] & ((U2)TRIPCOM_SNSRBIT_ODOCNT_UNKNOWN | (U2)TRIPCOM_SNSRBIT_FUELUSD_UNKNOWN);
    if (u2_t_jdgbit != (U2)0U) {
        u1_t_snsrsts  = (U1)TRIPCOM_STSBIT_UNKNOWN;
    }
    u2_t_jdgbit = u2_ap_STSFIELD[TRIPCOM_STSFIELD_SNSR] & ((U2)TRIPCOM_SNSRBIT_ODOCNT_INVALID | (U2)TRIPCOM_SNSRBIT_FUELUSD_INVALID);
    if (u2_t_jdgbit != (U2)0U) {
        u1_t_snsrsts |= (U1)TRIPCOM_STSBIT_INVALID;
    }
    u1_s_instfe_prevsts = st_s_instfe_var.u1_status;

    if (u1_a_CNTTID < (U1)INSTFE_NUM_CNTTS) {
        stp_t_CNTT  = &st_sp_INSTFE_CNTTS_CFG[u1_a_CNTTID];
        u1_t_update = u1_g_InstEconCalcTrnst(stp_t_CNTT, &st_s_instfe_var, u2_ap_STSFIELD, u1_t_snsrsts);
    }

    return (u1_t_update);
}

/*===================================================================================================================================*/
/* void            vd_g_InstFeAccmlt(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD, const U4 * u4_ap_DELTA)                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_InstFeAccmlt(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD, const U4 * u4_ap_DELTA)
{
    const ST_INSTECON_CNTT *                     stp_t_CNTT;
    U4                                           u4_t_fuelusd;
    U4                                           u4_t_odocnt;


    u4_t_fuelusd = u4_ap_DELTA[TRIPCOM_DELTA_DC_FUELUSD_PC];
    u4_t_odocnt  = u4_ap_DELTA[TRIPCOM_DELTA_ANY_ODOCNT_PC];

    if (u1_a_CNTTID < (U1)INSTFE_NUM_CNTTS) {
        stp_t_CNTT  = &st_sp_INSTFE_CNTTS_CFG[u1_a_CNTTID];
        vd_g_InstEconAccmlt(stp_t_CNTT, st_s_instfe_var.u1_ocinit, u4_t_fuelusd, u4_t_odocnt);
    }
}

/*===================================================================================================================================*/
/* void            vd_g_InstFeUpdt(const U1 u1_a_CNTTID)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_InstFeUpdt(const U1 u1_a_CNTTID)
{
    const ST_INSTECON_CNTT *                     stp_t_CNTT;


    if (u1_a_CNTTID < (U1)INSTFE_NUM_CNTTS) {
        stp_t_CNTT  = &st_sp_INSTFE_CNTTS_CFG[u1_a_CNTTID];
        vd_g_InstEconUpdt(stp_t_CNTT, (U1)INSTECON_ENGYTYPE_FUEL);
    }
}

/*===================================================================================================================================*/
/* U1              u1_g_InstFeKmpl(U4 * u4p_a_kmpl)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_InstFeKmpl(U4 * u4p_a_kmpl)
{
    if (u4p_a_kmpl != vdp_PTR_NA) {
        if (st_s_instfe_var.u1_calcstsbit != (U1)INSTFE_CALCSTS_ACT) {
            (*u4p_a_kmpl) = (U4)0U;
        }
        else {
            (*u4p_a_kmpl) = u4_g_TripcomMsGetAccmltVal(st_sp_INSTFE_CNTTS_CFG[INSTFE_CNTT_RX].u1_ms_dspval_id);
        }
    }
    return (st_s_instfe_var.u1_status);
}

/*===================================================================================================================================*/
/* U2              u2_g_InstFeCalcTx(const U1 u1_a_CNTTID, const U1 u1_a_UNIT)                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2              u2_g_InstFeCalcTx(const U1 u1_a_CNTTID, const U1 u1_a_UNIT)
{
    const ST_INSTECON_CNTT *                     stp_t_CNTT;
    U2                                           u2_t_txval;


    u2_t_txval = (U2)TRIPCOM_CANTX_UNKNOWN;

    if (u1_a_CNTTID < (U1)INSTFE_NUM_CNTTS) {
        stp_t_CNTT  = &st_sp_INSTFE_CNTTS_CFG[u1_a_CNTTID];

        if ((st_s_instfe_var.u1_status & (U1)TRIPCOM_STSBIT_INVALID) != (U1)0U) {
            u2_t_txval = (U2)TRIPCOM_CANTX_TIMEOUT;
        }
        else {
            u2_t_txval = u2_g_InstEconCalcTx(stp_t_CNTT, st_s_instfe_var.u1_calcstsbit, u1_a_UNIT, (U1)INSTECON_ENGYTYPE_FUEL);
        }
    }

    return (u2_t_txval);
}

/*===================================================================================================================================*/
/* U2              u2_g_InstFeCalcTx(const U1 u1_a_CNTTID, const U1 u1_a_UNIT)                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2              u2_g_InstFecCalcTx(const U1 u1_a_CNTTID, const U1 u1_a_UNIT)
{
    const ST_INSTECON_CNTT *                     stp_t_CNTT;
    U2                                           u2_t_txval;


    u2_t_txval = (U2)TRIPCOM_CANTX_UNKNOWN;

    if (u1_a_CNTTID < (U1)INSTFE_NUM_CNTTS) {
        stp_t_CNTT  = &st_sp_INSTFE_CNTTS_CFG[u1_a_CNTTID];

        if ((st_s_instfe_var.u1_status & (U1)TRIPCOM_STSBIT_INVALID) != (U1)0U) {
            u2_t_txval = (U2)TRIPCOM_CANTX_TIMEOUT;
        }
        else {
            u2_t_txval = u2_g_InstEconCalcTx(stp_t_CNTT, st_s_instfe_var.u1_calcstsbit, (U1)INSTEE_UNIT_LP100KM, (U1)INSTECON_ENGYTYPE_FUEL);
        }
    }

    return (u2_t_txval);
}

/*===================================================================================================================================*/
/* void            vd_g_InstFeSmooth(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_InstFeSmooth(void)
{
    vd_g_InstEconSmooth(&st_sp_INSTFE_CNTTS_CFG[INSTFE_CNTT_RX], st_s_instfe_var.u1_status, u1_s_instfe_prevsts);
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
/*  1.1.1    07/13/2020  YA       Remove vd_g_InstFeSmooth                                                                           */
/*  2.0.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*                                                                                                                                   */
/*  * HY   = Hidefumi Yoshida, Denso                                                                                                 */
/*  * YA   = Yuhei Aoyama, DensoTechno                                                                                               */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
