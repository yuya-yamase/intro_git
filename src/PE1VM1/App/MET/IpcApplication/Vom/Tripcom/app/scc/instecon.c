/* 2.0.4 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Instant XXXX Economy application core                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define INSTECON_C_MAJOR                        (2)
#define INSTECON_C_MINOR                        (0)
#define INSTECON_C_PATCH                        (4)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "instecon_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((INSTECON_C_MAJOR != INSTECON_H_MAJOR) || \
     (INSTECON_C_MINOR != INSTECON_H_MINOR) || \
     (INSTECON_C_PATCH != INSTECON_H_PATCH))
#error "instecon.c and instecon.h : source and header files are inconsistent!"
#endif

#if ((INSTECON_C_MAJOR != INSTECON_CFG_H_MAJOR) || \
     (INSTECON_C_MINOR != INSTECON_CFG_H_MINOR) || \
     (INSTECON_C_PATCH != INSTECON_CFG_H_PATCH))
#error "instecon.c and instecon_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define INSTECON_NUM_EVTBIT                     (16U)
/* #define INSTECON_EVTBIT_UNKWN                (0x01U) == TRIPCOM_STSBIT_UNKNOWN */
/* #define INSTECON_EVTBIT_INVLD                (0x02U) == TRIPCOM_STSBIT_INVALID */
#define INSTECON_EVTBIT_AUTO_RESET              (0x04U)
#define INSTECON_EVTBIT_AUTO_VEHMV              (0x08U)

#define INSTECON_NUM_CALCSTS                    (3U)
#define INSTECON_CALCSTS_INACT                  (0x00U)
#define INSTECON_CALCSTS_RXONCE                 (0x01U)
#define INSTECON_CALCSTS_ACT                    (0x02U)
#define INSTECON_CALCSTS_FIELD                  (0x0FU)

#define INSTECON_STS_UNKWN                      (0x10U)
#define INSTECON_STS_INVLD                      (0x20U)
#define INSTECON_ACT_INITUPDT                   (0x40U)
#define INSTECON_ACT_OCINIT                     (0x80U)

#define INSTECON_CALCACT_INACT_UNK              (INSTECON_CALCSTS_INACT  | INSTECON_STS_UNKWN |                      INSTECON_ACT_OCINIT  )
#define INSTECON_CALCACT_INACT_INV              (INSTECON_CALCSTS_INACT  |                      INSTECON_STS_INVLD | INSTECON_ACT_OCINIT  )
#define INSTECON_CALCACT_INACT_UNKINV           (INSTECON_CALCSTS_INACT  | INSTECON_STS_UNKWN | INSTECON_STS_INVLD | INSTECON_ACT_OCINIT  )
#define INSTECON_CALCACT_RXONCE                 (INSTECON_CALCSTS_RXONCE | INSTECON_STS_UNKWN                                             )
#define INSTECON_CALCACT_RXONCE_INIT            (INSTECON_CALCSTS_RXONCE | INSTECON_STS_UNKWN                      | INSTECON_ACT_OCINIT  )
#define INSTECON_CALCACT_ACT                    (INSTECON_CALCSTS_ACT                                                                     )
#define INSTECON_CALCACT_ACT_UPDT               (INSTECON_CALCSTS_ACT                                              | INSTECON_ACT_INITUPDT)

#define INSTECON_AVE_VAL_1                      (11U)
#define INSTECON_AVE_VAL_2                      (1U)

#define INSTECON_RNDHLF_SFT                     (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  U4                                    u4_s_econ_dspvalsum;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  U1      u1_s_InstEconMakeEvtbit(const ST_INSTECON_CNTT * stp_a_CNTT, const U2 * u2_ap_STSFIELD);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* void            vd_g_InstEconInit(ST_INSTECON_VAR * stp_a_var, U1 * u1p_a_prevsts)                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_InstEconInit(ST_INSTECON_VAR * stp_a_var, U1 * u1p_a_prevsts)
{
    stp_a_var->u1_calcstsbit = (U1)INSTECON_CALCSTS_INACT;
    stp_a_var->u1_ocinit     = (U1)FALSE;
    stp_a_var->u1_status     = (U1)TRIPCOM_STSBIT_UNKNOWN;
    (* u1p_a_prevsts)        = (U1)TRIPCOM_STSBIT_UNKNOWN;
    u4_s_econ_dspvalsum      = (U4)0U;
}

/*===================================================================================================================================*/
/* U1              u1_g_InstEconCalcTrnst(const ST_INSTECON_CNTT * stp_a_CNTT, ST_INSTECON_VAR * stp_a_var,                          */
/*                                        const U2 * u2_ap_STSFIELD, const U2 u2_a_SNSRSTS)                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_InstEconCalcTrnst(const ST_INSTECON_CNTT * stp_a_CNTT, ST_INSTECON_VAR * stp_a_var,
                                       const U2 * u2_ap_STSFIELD, const U1 u1_a_SNSRSTS)
{
    static  const   U1                          u1_sp2_INSTECON_CALC_STM[INSTECON_NUM_EVTBIT][INSTECON_NUM_CALCSTS]      = {
        {   (U1)INSTECON_CALCACT_INACT_UNK,     (U1)INSTECON_CALCACT_INACT_UNK,     (U1)INSTECON_CALCACT_INACT_UNK      },
        {   (U1)INSTECON_CALCACT_INACT_UNK,     (U1)INSTECON_CALCACT_INACT_UNK,     (U1)INSTECON_CALCACT_INACT_UNK      },
        {   (U1)INSTECON_CALCACT_INACT_INV,     (U1)INSTECON_CALCACT_INACT_INV,     (U1)INSTECON_CALCACT_INACT_INV      },
        {   (U1)INSTECON_CALCACT_INACT_UNKINV,  (U1)INSTECON_CALCACT_INACT_UNKINV,  (U1)INSTECON_CALCACT_INACT_UNKINV   },
        {   (U1)INSTECON_CALCACT_INACT_UNK,     (U1)INSTECON_CALCACT_INACT_UNK,     (U1)INSTECON_CALCACT_INACT_UNK      },
        {   (U1)INSTECON_CALCACT_INACT_UNK,     (U1)INSTECON_CALCACT_INACT_UNK,     (U1)INSTECON_CALCACT_INACT_UNK      },
        {   (U1)INSTECON_CALCACT_INACT_INV,     (U1)INSTECON_CALCACT_INACT_INV,     (U1)INSTECON_CALCACT_INACT_INV      },
        {   (U1)INSTECON_CALCACT_INACT_UNKINV,  (U1)INSTECON_CALCACT_INACT_UNKINV,  (U1)INSTECON_CALCACT_INACT_UNKINV   },
        {   (U1)INSTECON_CALCACT_INACT_UNK,     (U1)INSTECON_CALCACT_RXONCE,        (U1)INSTECON_CALCACT_ACT            },
        {   (U1)INSTECON_CALCACT_INACT_UNK,     (U1)INSTECON_CALCACT_INACT_UNK,     (U1)INSTECON_CALCACT_INACT_UNK      },
        {   (U1)INSTECON_CALCACT_INACT_INV,     (U1)INSTECON_CALCACT_INACT_INV,     (U1)INSTECON_CALCACT_INACT_INV      },
        {   (U1)INSTECON_CALCACT_INACT_UNKINV,  (U1)INSTECON_CALCACT_INACT_INV,     (U1)INSTECON_CALCACT_INACT_INV      },
        {   (U1)INSTECON_CALCACT_RXONCE_INIT,   (U1)INSTECON_CALCACT_ACT_UPDT,      (U1)INSTECON_CALCACT_ACT_UPDT       },
        {   (U1)INSTECON_CALCACT_INACT_UNK,     (U1)INSTECON_CALCACT_INACT_UNK,     (U1)INSTECON_CALCACT_INACT_UNK      },
        {   (U1)INSTECON_CALCACT_INACT_INV,     (U1)INSTECON_CALCACT_INACT_INV,     (U1)INSTECON_CALCACT_INACT_INV      },
        {   (U1)INSTECON_CALCACT_INACT_INV,     (U1)INSTECON_CALCACT_INACT_INV,     (U1)INSTECON_CALCACT_INACT_INV      }
    };
    U1                                          u1_t_update;
    U1                                          u1_t_evtbit;
    U1                                          u1_t_calcact;


    u1_t_evtbit  = u1_a_SNSRSTS | u1_s_InstEconMakeEvtbit(stp_a_CNTT, u2_ap_STSFIELD);

    u1_t_calcact = (U1)INSTECON_CALCACT_INACT_UNK;
    if (stp_a_var->u1_calcstsbit < (U1)INSTECON_NUM_CALCSTS) {
        u1_t_calcact = u1_sp2_INSTECON_CALC_STM[u1_t_evtbit][stp_a_var->u1_calcstsbit];
    }

    stp_a_var->u1_calcstsbit = u1_t_calcact & (U1)INSTECON_CALCSTS_FIELD;
    stp_a_var->u1_status = (U1)TRIPCOM_STSBIT_VALID;
    if ((u1_t_calcact & (U1)INSTECON_STS_UNKWN) != (U1)0U) {
        stp_a_var->u1_status  = (U1)TRIPCOM_STSBIT_UNKNOWN;
    }
    if ((u1_t_calcact & (U1)INSTECON_STS_INVLD) != (U1)0U) {
        stp_a_var->u1_status |= (U1)TRIPCOM_STSBIT_INVALID;
    }
    u1_t_update = (U1)FALSE;
    if ((u1_t_calcact & (U1)INSTECON_ACT_INITUPDT) != (U1)0U) {
        u1_t_update = (U1)TRUE;
    }
    stp_a_var->u1_ocinit = (U1)FALSE;
    if ((u1_t_calcact & (U1)INSTECON_ACT_OCINIT) != (U1)0U) {
        stp_a_var->u1_ocinit = (U1)TRUE;
    }

    return (u1_t_update);
}

/*===================================================================================================================================*/
/* void            vd_g_InstEconAccmlt(const ST_INSTECON_CNTT * stp_a_CNTT,                                                          */
/*                                     const U1 u1_a_ISINIT, const U4 u4_a_USD, const U4 u4_a_ODO)                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_InstEconAccmlt(const ST_INSTECON_CNTT * stp_a_CNTT,
                                    const U1 u1_a_ISINIT, const U4 u4_a_USD, const U4 u4_a_ODO)
{
    U4          u4_t_usd;
    U4          u4_t_odocnt;


    if (u1_a_ISINIT == (U1)TRUE) {
        vd_g_TripcomMsSetAccmltVal(stp_a_CNTT->u1_ms_used_id,   (U4)0U);
        vd_g_TripcomMsSetAccmltVal(stp_a_CNTT->u1_ms_odocnt_id, (U4)0U);
    }
    else {
        u4_t_usd    = u4_a_USD;
        u4_t_odocnt = u4_a_ODO;
        u4_t_odocnt = u4_g_TripcomCalcAddU4U4(u4_t_odocnt, u4_g_TripcomMsGetAccmltVal(stp_a_CNTT->u1_ms_odocnt_id));

        vd_g_TripcomMsSetAccmltVal(stp_a_CNTT->u1_ms_used_id,   u4_t_usd   );
        vd_g_TripcomMsSetAccmltVal(stp_a_CNTT->u1_ms_odocnt_id, u4_t_odocnt);
    }
}

/*===================================================================================================================================*/
/* void            vd_g_InstEconUpdt(const ST_INSTECON_CNTT * stp_a_CNTT, const U1 u1_a_TYPE)                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_InstEconUpdt(const ST_INSTECON_CNTT * stp_a_CNTT, const U1 u1_a_TYPE)
{
    U4                                          u4_t_usd;
    U4                                          u4_t_odocnt;
    U4                                          u4_t_economy;


    u4_t_usd    = u4_g_TripcomMsGetAccmltVal(stp_a_CNTT->u1_ms_used_id  );
    u4_t_odocnt = u4_g_TripcomMsGetAccmltVal(stp_a_CNTT->u1_ms_odocnt_id);

    switch (u1_a_TYPE) {
        case INSTECON_ENGYTYPE_FUEL:
            u4_t_economy = u4_g_TripcomCalcFeKmpl(u4_t_odocnt, u4_t_usd);
            break;
        case INSTECON_ENGYTYPE_HYDR:
            u4_t_economy = u4_g_TripcomCalcHeKmpkg(u4_t_odocnt, u4_t_usd);
            break;
        default:
            u4_t_economy = (U4)0U;
            break;
    }
    vd_g_TripcomMsSetAccmltVal(stp_a_CNTT->u1_ms_economy_id, u4_t_economy);
    vd_g_TripcomMsSetAccmltVal(stp_a_CNTT->u1_ms_odocnt_id,  (U4)0U      );
}

/*===================================================================================================================================*/
/* U2            u2_g_InstEconCalcTx(const ST_INSTECON_CNTT * stp_a_CNTT, const U1 u1_a_STS, const U1 u1_a_UNIT, const U1 u1_a_TYPE) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2              u2_g_InstEconCalcTx(const ST_INSTECON_CNTT * stp_a_CNTT, const U1 u1_a_STS, const U1 u1_a_UNIT, const U1 u1_a_TYPE)
{
    static  U1          (* const                fp_sp_TRIPCOM_CNVT[INSTECON_NUM_ENGYTYPE])
                                                        (U4 * u4p_a_kmpx_to, const U1 u1_a_UNIT, const U1 u1_a_USEAPRXVAL)      = {
        &u1_g_TripcomCalcTxCnvtFE,
        &u1_g_TripcomCalcTxCnvtHE,
        vdp_PTR_NA
    };
    U4          u4_t_xecon;
    U4          u4_t_remain;
    U4          u4_t_rndhlf;
    U2          u2_t_txval;
    U1          u1_t_cnvsts;


    u2_t_txval = stp_a_CNTT->u2_cantx_unknown;

    if (u1_a_STS != (U1)INSTECON_CALCSTS_ACT) {
        u2_t_txval = stp_a_CNTT->u2_cantx_init;
    }
    else {
        u4_t_xecon  = u4_g_TripcomMsGetAccmltVal(stp_a_CNTT->u1_ms_economy_id);
        u1_t_cnvsts = (U1)TRIPCOM_STSBIT_INVALID;
        if ((u1_a_TYPE < (U1)INSTECON_NUM_ENGYTYPE      )  &&
            (fp_sp_TRIPCOM_CNVT[u1_a_TYPE] != vdp_PTR_NA)) {

            u1_t_cnvsts = (fp_sp_TRIPCOM_CNVT[u1_a_TYPE])(&u4_t_xecon, u1_a_UNIT, (U1)FALSE);
        }
        if (u1_t_cnvsts == (U1)TRIPCOM_STSBIT_VALID) {
            u4_t_remain = u4_t_xecon % (U4)(stp_a_CNTT->u1_cantx_resconv);
            u4_t_rndhlf = (U4)(stp_a_CNTT->u1_cantx_resconv) >> INSTECON_RNDHLF_SFT;
            u4_t_xecon /= (U4)(stp_a_CNTT->u1_cantx_resconv);
            if (u4_t_rndhlf < u4_t_remain) {
                u4_t_xecon++;
            }
            u2_t_txval = stp_a_CNTT->u2_cantx_max;
            if (u4_t_xecon < (U4)u2_t_txval) {
                u2_t_txval = (U2)u4_t_xecon;
            }
        }
    }

    return (u2_t_txval);
}

/*===================================================================================================================================*/
/* static  U1      u1_s_InstEconMakeEvtbit(const ST_INSTECON_CNTT * stp_a_CNTT, const U2 * u2_ap_STSFIELD)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_InstEconMakeEvtbit(const ST_INSTECON_CNTT * stp_a_CNTT, const U2 * u2_ap_STSFIELD)
{
    U2          u2_t_cndbit;
    U2          u2_t_jdgbit;
    U1          u1_t_evtbit;


    u1_t_evtbit = (U1)0U;
    u2_t_jdgbit = u2_ap_STSFIELD[TRIPCOM_STSFIELD_AUTO_RSTRQ] & stp_a_CNTT->u2_autoreset;
    if (u2_t_jdgbit != (U2)0U) {
        u1_t_evtbit  = (U1)INSTECON_EVTBIT_AUTO_RESET;
    }
    u2_t_cndbit = (U2)TRIPCOM_VEHSTS_VEHMV | (U2)TRIPCOM_VEHSTS_DRVCYC;
    u2_t_jdgbit = u2_ap_STSFIELD[TRIPCOM_STSFIELD_VSTS] & u2_t_cndbit;
    if (u2_t_jdgbit == u2_t_cndbit) {
        u1_t_evtbit |= (U1)INSTECON_EVTBIT_AUTO_VEHMV;
    }

    return (u1_t_evtbit);
}

/*===================================================================================================================================*/
/* void            vd_g_InstEconSmooth(const ST_INSTECON_CNTT * stp_a_CNTT, const U1 u1_a_STATUS, const U1 u1_a_PREVSTS)             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_InstEconSmooth(const ST_INSTECON_CNTT * stp_a_CNTT, const U1 u1_a_STATUS, const U1 u1_a_PREVSTS)
{
    static const U4 u4_s_INSTFE_DISP_MAX = (U4)2001000U;            /* 2001.000[km/L]  = 0.0[L/100km]  can be displayed              */
    static const U4 u4_s_INSTHE_DISP_MAX = (U4)2001000U;            /* 2001.000[km/kg] = 0.0[kg/100km] can be displayed              */

    U4    u4_t_predspval;
    U4    u4_t_economy;
    U4    u4_t_dspval;


    u4_t_predspval = u4_g_TripcomMsGetAccmltVal(stp_a_CNTT->u1_ms_dspval_id);
    u4_t_economy   = u4_g_TripcomMsGetAccmltVal(stp_a_CNTT->u1_ms_economy_id);

    if (stp_a_CNTT->u1_ms_economy_id == (U1)TRIPCOM_MS_ID_INSTFE_FE) {
        if (u4_t_economy > u4_s_INSTFE_DISP_MAX) {
            u4_t_economy = u4_s_INSTFE_DISP_MAX;
        }
    }
    else {
        if (u4_t_economy > u4_s_INSTHE_DISP_MAX) {
            u4_t_economy = u4_s_INSTHE_DISP_MAX;
        }
    }

    if (u1_a_STATUS == (U1)TRIPCOM_STSBIT_VALID) {

        if ((u4_t_predspval == (U4)0U) || (u1_a_PREVSTS != (U1)TRIPCOM_STSBIT_VALID)) {
            u4_t_dspval          = u4_t_economy;
            u4_s_econ_dspvalsum  = u4_t_economy * (U4)INSTECON_AVE_VAL_1;
            /* The maximum value of u4_t_economy is 2001000.                            */
            /* The value of INSTEE_AVE_VAL_1 is 11,                                     */
            /* so (u4_t_economy * (U4)INSTEE_AVE_VAL_1) is always less than U4_MAX.     */
        }
        else {
            u4_s_econ_dspvalsum  = u4_g_TripcomCalcAddU4U4(u4_s_econ_dspvalsum, u4_t_economy);
            u4_t_dspval          = u4_s_econ_dspvalsum / ((U4)INSTECON_AVE_VAL_1 + (U4)INSTECON_AVE_VAL_2);
            u4_s_econ_dspvalsum -= u4_t_dspval;
            /* The value of u4_t_dspval is u4_s_econ_dspvalsum / (11 + 1),               */
            /* u4_s_dspval is never greater than u4_s_econ_dspvalsum.                    */
        }

        vd_g_TripcomMsSetAccmltVal(stp_a_CNTT->u1_ms_dspval_id, u4_t_dspval);
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
/*  1.0.0    11/07/2018  HY       New.                                                                                               */
/*  1.1.0    03/23/2020  YA       Change for 800B CV                                                                                 */
/*  1.1.1    07/13/2020  YA       Remove vd_g_InstEconSmooth                                                                         */
/*  2.0.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*  2.0.2    10/27/2021  TK       QAC supported.                                                                                     */
/*  2.0.3    08/31/2022  ToK      Fix vd_g_InstEconSmooth                                                                            */
/*  2.0.4    03/10/2023  ToK      Fix vd_g_InstEconSmooth for [24FGM22-21927][24FGM22-22005][24FGM22-22006]                          */
/*                                                            [24FGM22-22012][24FGM22-22010][24FGM22-22011]                          */
/*                                                                                                                                   */
/*  * HY   = Hidefumi Yoshida, Denso                                                                                                 */
/*  * YA   = Yuhei Aoyama, DensoTechno                                                                                               */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * TK   = Takanori Kuno, Denso Techno                                                                                             */
/*  * ToK  = Toru Kamishina, Denso Techno                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/
