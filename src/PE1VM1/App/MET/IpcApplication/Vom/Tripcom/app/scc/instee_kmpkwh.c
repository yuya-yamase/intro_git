/* 2.0.3 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Instant Electric Economy for Trip Computer                                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define INSTEE_KMPKWH_C_MAJOR                     (2)
#define INSTEE_KMPKWH_C_MINOR                     (0)
#define INSTEE_KMPKWH_C_PATCH                     (3)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "instee_kmpkwh_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((INSTEE_KMPKWH_C_MAJOR != INSTEE_KMPKWH_H_MAJOR) || \
     (INSTEE_KMPKWH_C_MINOR != INSTEE_KMPKWH_H_MINOR) || \
     (INSTEE_KMPKWH_C_PATCH != INSTEE_KMPKWH_H_PATCH))
#error "instee_kmpkwh.c and instee_kmpkwh.h : source and header files are inconsistent!"
#endif

#if ((INSTEE_KMPKWH_C_MAJOR != INSTEE_KMPKWH_CFG_H_MAJOR) || \
     (INSTEE_KMPKWH_C_MINOR != INSTEE_KMPKWH_CFG_H_MINOR) || \
     (INSTEE_KMPKWH_C_PATCH != INSTEE_KMPKWH_CFG_H_PATCH))
#error "instee_kmpkwh.c and instee_kmpkwh_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define INSTEE_NUM_EVTBIT                     (16U)
/* #define INSTEE_EVTBIT_UNKWN                (0x01U) == TRIPCOM_STSBIT_UNKNOWN */
/* #define INSTEE_EVTBIT_INVLD                (0x02U) == TRIPCOM_STSBIT_INVALID */
#define INSTEE_EVTBIT_AUTO_RESET              (0x04U)
#define INSTEE_EVTBIT_AUTO_VEHMV              (0x08U)

#define INSTEE_NUM_CALCSTS                    (3U)
#define INSTEE_CALCSTS_INACT                  (0x00U)
#define INSTEE_CALCSTS_RXONCE                 (0x01U)
#define INSTEE_CALCSTS_ACT                    (0x02U)
#define INSTEE_CALCSTS_FIELD                  (0x0FU)

#define INSTEE_STS_UNKWN                      (0x10U)
#define INSTEE_STS_INVLD                      (0x20U)
#define INSTEE_ACT_INITUPDT                   (0x40U)
#define INSTEE_ACT_OCINIT                     (0x80U)

#define INSTEE_CALCACT_INACT_UNK              (INSTEE_CALCSTS_INACT  | INSTEE_STS_UNKWN |                    INSTEE_ACT_OCINIT                       )
#define INSTEE_CALCACT_INACT_INV              (INSTEE_CALCSTS_INACT  |                    INSTEE_STS_INVLD | INSTEE_ACT_OCINIT                       )
#define INSTEE_CALCACT_INACT_UNKINV           (INSTEE_CALCSTS_INACT  | INSTEE_STS_UNKWN | INSTEE_STS_INVLD | INSTEE_ACT_OCINIT                       )
#define INSTEE_CALCACT_RXONCE                 (INSTEE_CALCSTS_RXONCE | INSTEE_STS_UNKWN                                                              )
#define INSTEE_CALCACT_RXONCE_INIT            (INSTEE_CALCSTS_RXONCE | INSTEE_STS_UNKWN                    | INSTEE_ACT_OCINIT                       )
#define INSTEE_CALCACT_ACT                    (INSTEE_CALCSTS_ACT                                                                                    )
#define INSTEE_CALCACT_ACT_UPDT               (INSTEE_CALCSTS_ACT                                                               | INSTEE_ACT_INITUPDT)
#define INSTEE_CALCACT_ACT_PIEVSTS0           (INSTEE_CALCSTS_ACT    |                                       INSTEE_ACT_OCINIT  | INSTEE_ACT_INITUPDT)

#define INSTEE_AVE_VAL_1                      (11U)
#define INSTEE_AVE_VAL_2                      (1U)

#define INSTEE_RNDHLF_SFT                     (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct {
    U1                                          u1_calcstsbit;
    U1                                          u1_ocinit;
    U1                                          u1_status;
} ST_INSTEE_VAR;

typedef struct {
    U2                                          u2_autoreset;           /* see tripcom.h                                             */
    U1                                          u1_ms_economy_id;       /* see tripcom_ms.h                                          */
    U1                                          u1_ms_used_id;          /* see tripcom_ms.h                                          */
    U1                                          u1_ms_odocnt_id;        /* see tripcom_ms.h                                          */
    U1                                          u1_ms_dspval_id;        /* see tripcom_ms.h                                          */

    U1                                          u1_cantx_resconv;       /* Multiplier to convert resolution                          */
    U2                                          u2_cantx_unknown;       /* Unit is not defined                                       */
    U2                                          u2_cantx_init;          /* Init value for vehicle stopped                            */
    U2                                          u2_cantx_max;           /* Range max property for cantx value                        */
} ST_INSTEE_CNTT;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  ST_INSTEE_VAR                         st_s_instee_var;
static  U1                                    u1_s_instee_prevsts;
static  U4                                    u4_s_dspvalsum;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  U1      u1_s_InstEeMakeEvtbit(const ST_INSTEE_CNTT * stp_a_CNTT, const U2 * u2_ap_STSFIELD);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_INSTEE_CNTT                   st_s_INSTEE_CNTTS_CFG = {
    /*  #define INSTEE_CNTT_RX                          (0)     */
    (U2)TRIPCOM_RSTRQBIT_A_UPDTEEUSD,

    (U1)TRIPCOM_MS_ID_INSTEE_EE,
    (U1)TRIPCOM_MS_ID_INSTEE_EU,
    (U1)TRIPCOM_MS_ID_INSTEE_OC,
    (U1)TRIPCOM_MS_ID_INSTEE_DV,

    (U1)100U,
    (U2)0xFFFDU,
    (U2)0xFFFDU,
    (U2)0xFFFCU
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* void            vd_g_InstEeInit(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void          vd_g_InstEeInit(void)
{
    st_s_instee_var.u1_calcstsbit = (U1)INSTEE_CALCSTS_INACT;
    st_s_instee_var.u1_ocinit     = (U1)FALSE;
    st_s_instee_var.u1_status     = (U1)TRIPCOM_STSBIT_UNKNOWN;
    u1_s_instee_prevsts           = (U1)TRIPCOM_STSBIT_UNKNOWN;
    u4_s_dspvalsum                = (U4)0U;
}

/*===================================================================================================================================*/
/* U1              u1_g_InstEeCalcTrnst(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD)                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1            u1_g_InstEeCalcTrnst(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD)
{
    static  const   U1                          u1_sp2_INSTEE_CALC_STM[INSTEE_NUM_EVTBIT][INSTEE_NUM_CALCSTS]      = {
        {   (U1)INSTEE_CALCACT_INACT_UNK,     (U1)INSTEE_CALCACT_INACT_UNK,     (U1)INSTEE_CALCACT_INACT_UNK      },
        {   (U1)INSTEE_CALCACT_INACT_UNK,     (U1)INSTEE_CALCACT_INACT_UNK,     (U1)INSTEE_CALCACT_INACT_UNK      },
        {   (U1)INSTEE_CALCACT_INACT_INV,     (U1)INSTEE_CALCACT_INACT_INV,     (U1)INSTEE_CALCACT_INACT_INV      },
        {   (U1)INSTEE_CALCACT_INACT_UNKINV,  (U1)INSTEE_CALCACT_INACT_UNKINV,  (U1)INSTEE_CALCACT_INACT_UNKINV   },
        {   (U1)INSTEE_CALCACT_INACT_UNK,     (U1)INSTEE_CALCACT_INACT_UNK,     (U1)INSTEE_CALCACT_INACT_UNK      },
        {   (U1)INSTEE_CALCACT_INACT_UNK,     (U1)INSTEE_CALCACT_INACT_UNK,     (U1)INSTEE_CALCACT_INACT_UNK      },
        {   (U1)INSTEE_CALCACT_INACT_INV,     (U1)INSTEE_CALCACT_INACT_INV,     (U1)INSTEE_CALCACT_INACT_INV      },
        {   (U1)INSTEE_CALCACT_INACT_UNKINV,  (U1)INSTEE_CALCACT_INACT_UNKINV,  (U1)INSTEE_CALCACT_INACT_UNKINV   },
        {   (U1)INSTEE_CALCACT_INACT_UNK,     (U1)INSTEE_CALCACT_RXONCE,        (U1)INSTEE_CALCACT_ACT            },
        {   (U1)INSTEE_CALCACT_INACT_UNK,     (U1)INSTEE_CALCACT_INACT_UNK,     (U1)INSTEE_CALCACT_INACT_UNK      },
        {   (U1)INSTEE_CALCACT_INACT_INV,     (U1)INSTEE_CALCACT_INACT_INV,     (U1)INSTEE_CALCACT_INACT_INV      },
        {   (U1)INSTEE_CALCACT_INACT_UNKINV,  (U1)INSTEE_CALCACT_INACT_INV,     (U1)INSTEE_CALCACT_INACT_INV      },
        {   (U1)INSTEE_CALCACT_RXONCE_INIT,   (U1)INSTEE_CALCACT_ACT_UPDT,      (U1)INSTEE_CALCACT_ACT_UPDT       },
        {   (U1)INSTEE_CALCACT_INACT_UNK,     (U1)INSTEE_CALCACT_INACT_UNK,     (U1)INSTEE_CALCACT_INACT_UNK      },
        {   (U1)INSTEE_CALCACT_INACT_INV,     (U1)INSTEE_CALCACT_INACT_INV,     (U1)INSTEE_CALCACT_INACT_INV      },
        {   (U1)INSTEE_CALCACT_INACT_INV,     (U1)INSTEE_CALCACT_INACT_INV,     (U1)INSTEE_CALCACT_INACT_INV      }
    };
    const ST_INSTEE_CNTT *                      stp_t_CNTT;
    ST_INSTEE_VAR *                             stp_t_var;
    U1                                          u1_t_update;
    U1                                          u1_t_evtbit;
    U1                                          u1_t_calcact;
    U1                                          u1_t_snsrsts;
    U2                                          u2_t_jdgbit;
    U1                                          u1_t_pievsts;


    stp_t_CNTT = &st_s_INSTEE_CNTTS_CFG;
    stp_t_var = &st_s_instee_var;
    u1_t_pievsts = (U1)0U;

    u1_t_snsrsts = u1_g_TripcomGetPIEVSTS(&u1_t_pievsts);
    
    u2_t_jdgbit = u2_ap_STSFIELD[TRIPCOM_STSFIELD_SNSR] & ((U2)TRIPCOM_SNSRBIT_ODOCNT_UNKNOWN | (U2)TRIPCOM_SNSRBIT_INSTEE_UNKNOWN);
    if (u2_t_jdgbit != (U2)0U) {
        u1_t_snsrsts |= (U1)TRIPCOM_STSBIT_UNKNOWN;
    }
    u2_t_jdgbit = u2_ap_STSFIELD[TRIPCOM_STSFIELD_SNSR] & ((U2)TRIPCOM_SNSRBIT_ODOCNT_INVALID | (U2)TRIPCOM_SNSRBIT_INSTEE_INVALID);
    if (u2_t_jdgbit != (U2)0U) {
        u1_t_snsrsts |= (U1)TRIPCOM_STSBIT_INVALID;
    }

    u1_t_evtbit  = u1_t_snsrsts | u1_s_InstEeMakeEvtbit(stp_t_CNTT, u2_ap_STSFIELD);

    u1_t_calcact = (U1)INSTEE_CALCACT_INACT_UNK;
    if (stp_t_var->u1_calcstsbit < (U1)INSTEE_NUM_CALCSTS) {
        u1_t_calcact = u1_sp2_INSTEE_CALC_STM[u1_t_evtbit][stp_t_var->u1_calcstsbit];
    }


    stp_t_var->u1_calcstsbit = u1_t_calcact & (U1)INSTEE_CALCSTS_FIELD;
    u1_s_instee_prevsts = stp_t_var->u1_status;
    
    if ((u1_t_pievsts == (U1)0U) && (stp_t_var->u1_calcstsbit == (U1)INSTEE_CALCSTS_ACT)) {
        u1_t_calcact = (U1)INSTEE_CALCACT_ACT_PIEVSTS0;
    }

    stp_t_var->u1_status = (U1)TRIPCOM_STSBIT_VALID;
    if ((u1_t_calcact & (U1)INSTEE_STS_UNKWN) != (U1)0U) {
        stp_t_var->u1_status  = (U1)TRIPCOM_STSBIT_UNKNOWN;
    }
    if ((u1_t_calcact & (U1)INSTEE_STS_INVLD) != (U1)0U) {
        stp_t_var->u1_status |= (U1)TRIPCOM_STSBIT_INVALID;
    }
    u1_t_update = (U1)FALSE;
    if ((u1_t_calcact & (U1)INSTEE_ACT_INITUPDT) != (U1)0U) {
        u1_t_update = (U1)TRUE;
    }
    stp_t_var->u1_ocinit = (U1)FALSE;
    if ((u1_t_calcact & (U1)INSTEE_ACT_OCINIT) != (U1)0U) {
        stp_t_var->u1_ocinit = (U1)TRUE;
    }

    return (u1_t_update);
}

/*===================================================================================================================================*/
/* void            vd_g_InstEeAccmlt(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD, const U4 * u4_ap_DELTA)                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void          vd_g_InstEeAccmlt(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD, const U4 * u4_ap_DELTA)
{
    U4          u4_t_usd;
    U4          u4_t_odocnt;


    if (st_s_instee_var.u1_ocinit == (U1)TRUE) {
        vd_g_TripcomMsSetAccmltVal(st_s_INSTEE_CNTTS_CFG.u1_ms_used_id,   (U4)0U);
        vd_g_TripcomMsSetAccmltVal(st_s_INSTEE_CNTTS_CFG.u1_ms_odocnt_id, (U4)0U);
    }
    else {
        u4_t_usd    = u4_ap_DELTA[TRIPCOM_DELTA_DC_EPUSD_PC];
        u4_t_odocnt = u4_ap_DELTA[TRIPCOM_DELTA_EV_ODOCNT_PC];
        u4_t_odocnt = u4_g_TripcomCalcAddU4U4(u4_t_odocnt, u4_g_TripcomMsGetAccmltVal(st_s_INSTEE_CNTTS_CFG.u1_ms_odocnt_id));

        vd_g_TripcomMsSetAccmltVal(st_s_INSTEE_CNTTS_CFG.u1_ms_used_id,   u4_t_usd   );
        vd_g_TripcomMsSetAccmltVal(st_s_INSTEE_CNTTS_CFG.u1_ms_odocnt_id, u4_t_odocnt);
    }
}

/*===================================================================================================================================*/
/* void            vd_g_InstEeUpdt(const U1 u1_a_CNTTID)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void          vd_g_InstEeUpdt(const U1 u1_a_CNTTID)
{
    U4                                          u4_t_usd;
    U4                                          u4_t_odocnt;
    U4                                          u4_t_economy;


    u4_t_usd    = u4_g_TripcomMsGetAccmltVal(st_s_INSTEE_CNTTS_CFG.u1_ms_used_id  );
    u4_t_odocnt = u4_g_TripcomMsGetAccmltVal(st_s_INSTEE_CNTTS_CFG.u1_ms_odocnt_id);

    if ((S4)u4_t_usd >= (S4)0) {
        u4_t_economy = u4_g_TripcomCalcInstEeKmpkwh(u4_t_odocnt, u4_t_usd);
    }
    else {
        u4_t_economy = (U4)U4_MAX;
    }

    vd_g_TripcomMsSetAccmltVal(st_s_INSTEE_CNTTS_CFG.u1_ms_economy_id, u4_t_economy);
    vd_g_TripcomMsSetAccmltVal(st_s_INSTEE_CNTTS_CFG.u1_ms_odocnt_id,  (U4)0U      );
}

/*===================================================================================================================================*/
/* U1            u1_g_InstEeKmpkwh(U4 * u4p_a_kmpkwh)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1            u1_g_InstEeKmpkwh(U4 * u4p_a_kmpkwh)
{
    if (u4p_a_kmpkwh != vdp_PTR_NA) {
        if (st_s_instee_var.u1_calcstsbit != (U1)INSTEE_CALCSTS_ACT) {
            (*u4p_a_kmpkwh) = (U4)0U;
        }
        else {
            (*u4p_a_kmpkwh) = u4_g_TripcomMsGetAccmltVal(st_s_INSTEE_CNTTS_CFG.u1_ms_dspval_id);
        }
    }
    return (st_s_instee_var.u1_status);
}

/*===================================================================================================================================*/
/* U2              u2_g_InstEeCalcTx(const U1 u1_a_CNTTID, const U1 u1_a_UNIT)                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2            u2_g_InstEeCalcTx(const U1 u1_a_CNTTID, const U1 u1_a_UNIT)
{

    const ST_INSTEE_CNTT *                      stp_t_CNTT;
    ST_INSTEE_VAR *                             stp_t_var;
    U4                                          u4_t_xecon;
    U4                                          u4_t_remain;
    U4                                          u4_t_rndhlf;
    U2                                          u2_t_txval;
    U1                                          u1_t_cnvsts;


    stp_t_CNTT = &st_s_INSTEE_CNTTS_CFG;
    stp_t_var = &st_s_instee_var;

    u2_t_txval = stp_t_CNTT->u2_cantx_unknown;
    
    if ((stp_t_var->u1_status & (U1)TRIPCOM_STSBIT_INVALID) != (U1)0U) {
        u2_t_txval = (U2)TRIPCOM_CANTX_TIMEOUT;
    }
    else {
        if (stp_t_var->u1_calcstsbit != (U1)INSTEE_CALCSTS_ACT) {
            u2_t_txval = stp_t_CNTT->u2_cantx_init;
        }
        else {
            u4_t_xecon  = u4_g_TripcomMsGetAccmltVal(stp_t_CNTT->u1_ms_economy_id);
            u1_t_cnvsts = u1_g_TripcomCalcTxCnvtInstEE(&u4_t_xecon, u1_a_UNIT, (U1)FALSE);
            if (u1_t_cnvsts == (U1)TRIPCOM_STSBIT_VALID) {
                u4_t_remain = u4_t_xecon % (U4)(stp_t_CNTT->u1_cantx_resconv);
                u4_t_rndhlf = (U4)(stp_t_CNTT->u1_cantx_resconv) >> INSTEE_RNDHLF_SFT;
                u4_t_xecon /= (U4)(stp_t_CNTT->u1_cantx_resconv);
                if (u4_t_rndhlf < u4_t_remain) {
                    u4_t_xecon++;
                }
                u2_t_txval = stp_t_CNTT->u2_cantx_max;
                if (u4_t_xecon < (U4)u2_t_txval) {
                    u2_t_txval = (U2)u4_t_xecon;
                }
            }
        }
    }
    return (u2_t_txval);
}

/*===================================================================================================================================*/
/* static  U1      u1_s_InstEeMakeEvtbit(const ST_INSTEE_CNTT * stp_a_CNTT, const U2 * u2_ap_STSFIELD)                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_InstEeMakeEvtbit(const ST_INSTEE_CNTT * stp_a_CNTT, const U2 * u2_ap_STSFIELD)
{
    U2          u2_t_cndbit;
    U2          u2_t_jdgbit;
    U1          u1_t_evtbit;


    u1_t_evtbit = (U1)0U;
    u2_t_jdgbit = u2_ap_STSFIELD[TRIPCOM_STSFIELD_AUTO_RSTRQ] & stp_a_CNTT->u2_autoreset;
    if (u2_t_jdgbit != (U2)0U) {
        u1_t_evtbit  = (U1)INSTEE_EVTBIT_AUTO_RESET;
    }
    u2_t_cndbit = (U2)TRIPCOM_VEHSTS_VEHMV | (U2)TRIPCOM_VEHSTS_DRVCYC;
    u2_t_jdgbit = u2_ap_STSFIELD[TRIPCOM_STSFIELD_VSTS] & u2_t_cndbit;
    if (u2_t_jdgbit == u2_t_cndbit) {
        u1_t_evtbit |= (U1)INSTEE_EVTBIT_AUTO_VEHMV;
    }

    return (u1_t_evtbit);
}

/*===================================================================================================================================*/
/* void            vd_g_InstEeSmooth(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_InstEeSmooth(void)
{
    static const U4 u4_s_INSTEE_DISP_MAX = (U4)2001000U;                /* 2001[km/kWh] = 0.0[kWh/100km] can be displayed            */

    U4    u4_t_predspval;
    U4    u4_t_economy;
    U4    u4_t_dspval;

    u4_t_predspval = u4_g_TripcomMsGetAccmltVal(st_s_INSTEE_CNTTS_CFG.u1_ms_dspval_id);
    u4_t_economy   = u4_g_TripcomMsGetAccmltVal(st_s_INSTEE_CNTTS_CFG.u1_ms_economy_id);

    if (u4_t_economy > u4_s_INSTEE_DISP_MAX){
        u4_t_economy = u4_s_INSTEE_DISP_MAX;
    }

    if (st_s_instee_var.u1_status == (U1)TRIPCOM_STSBIT_VALID) {

        if ((u4_t_predspval == (U4)0U) || (u1_s_instee_prevsts != (U1)TRIPCOM_STSBIT_VALID)) {
            u4_t_dspval     = u4_t_economy;
            u4_s_dspvalsum  = u4_t_economy * (U4)INSTEE_AVE_VAL_1;
            /* The maximum value of u4_t_economy is 2001000.                            */
            /* The value of INSTEE_AVE_VAL_1 is 11,                                     */
            /* so (u4_t_economy * (U4)INSTEE_AVE_VAL_1) is always less than U4_MAX.     */
        }
        else {
            u4_s_dspvalsum  = u4_g_TripcomCalcAddU4U4(u4_s_dspvalsum, u4_t_economy);
            u4_t_dspval     = u4_s_dspvalsum / ((U4)INSTEE_AVE_VAL_1 + (U4)INSTEE_AVE_VAL_2);
            u4_s_dspvalsum -= u4_t_dspval;
            /* The value of u4_t_dspval is u4_s_dspvalsum / (11 + 1),                   */
            /* u4_s_dspval is never greater than u4_s_dspvalsum.                        */
        }

        vd_g_TripcomMsSetAccmltVal(st_s_INSTEE_CNTTS_CFG.u1_ms_dspval_id, u4_t_dspval);
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
/*  1.0.0    03/23/2020  YA       New.                                                                                               */
/*  1.0.1    07/22/2020  YA       Add guard control to prevent overflow                                                              */
/*  1.0.2    10/07/2020  YA       Change for 800B CV-R.                                                                              */
/*  1.1.0    08/06/2021  YS       Improve smoothing caluculation logic at vd_g_InstEeSmooth.                                         */
/*  2.0.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*  2.0.2    10/27/2021  TK       QAC supported.                                                                                     */
/*  2.0.3    03/10/2023  ToK      Fix vd_g_InstEeSmooth for [24FGM22-21927][24FGM22-22005][24FGM22-22006]                            */
/*                                                          [24FGM22-22012][24FGM22-22010][24FGM22-22011]                            */
/*                                                                                                                                   */
/*  * YA   = Yuhei Aoyama, DensoTechno                                                                                               */
/*  * YS   = Yosuke Sugimoto, DensoTechno                                                                                            */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * TK   = Takanori Kuno, Denso Techno                                                                                             */
/*  * ToK  = Toru Kamishina, Denso Techno                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/
