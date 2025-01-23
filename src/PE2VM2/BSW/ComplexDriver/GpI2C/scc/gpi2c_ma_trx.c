/* 1.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  General Purpose I2C Communication / Master                                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GP_I2C_MA_TRX_C_MAJOR                    (1)
#define GP_I2C_MA_TRX_C_MINOR                    (1)
#define GP_I2C_MA_TRX_C_PATCH                    (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "gpi2c_ma_cfg_private.h"
#include "gpi2c_ma_if.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((GP_I2C_MA_TRX_C_MAJOR != GP_I2C_MA_H_MAJOR) || \
     (GP_I2C_MA_TRX_C_MINOR != GP_I2C_MA_H_MINOR) || \
     (GP_I2C_MA_TRX_C_PATCH != GP_I2C_MA_H_PATCH))
#error "gpi2c_ma_trx.c and gpi2c_ma.h : source and header files are inconsistent!"
#endif

#if ((GP_I2C_MA_TRX_C_MAJOR != GP_I2C_MA_CFG_H_MAJOR) || \
     (GP_I2C_MA_TRX_C_MINOR != GP_I2C_MA_CFG_H_MINOR) || \
     (GP_I2C_MA_TRX_C_PATCH != GP_I2C_MA_CFG_H_PATCH))
#error "gpi2c_ma_trx.c and gpi2c_ma_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GP_I2C_MA_ACT_TO_WRI                     (0U)           /* STA->WRI */
#define GP_I2C_MA_ACT_TO_REA                     (1U)           /* STA->REA */
#define GP_I2C_MA_ACT_WR_NEX                     (2U)           /* WRI->WRI */
#define GP_I2C_MA_ACT_WR_LAS                     (3U)           /* WRI->WEN */
#define GP_I2C_MA_ACT_WR_FIN                     (4U)           /* WEN->FIN */
#define GP_I2C_MA_ACT_WR_STA                     (5U)           /* WEN->STA */
#define GP_I2C_MA_ACT_RE_ACK                     (6U)           /* REA->REA */
#define GP_I2C_MA_ACT_RE_NAK                     (7U)           /* REA->RLA */
#define GP_I2C_MA_ACT_RE_ABT                     (8U)           /* REA->RLA */
#define GP_I2C_MA_ACT_RE_FIN                     (9U)           /* RLA->FIN */
#define GP_I2C_MA_ACT_TO_STA                     (10U)           /* FIN->STA */
#define GP_I2C_MA_ACT_TO_REQ                     (11U)          /* FIN->REQ */
#define GP_I2C_MA_ACT_SQ_ABT                     (12U)          /* XXX->FIN */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GP_I2C_MA_ACT_EAS_MAX                    (0x00000003U)
#define GP_I2C_MA_ACT_LSB_SEQ                    (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GP_I2C_MA_RRC_TO_RLA                     (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_GpI2cMaIRQEas_Opechk(const ST_GP_I2C_MA_CH * st_ap_CH, const ST_GP_I2C_MA_CTRL * st_ap_CTRL);
static U4      u4_s_GpI2cMaIRQEas_Wtcchk(const ST_GP_I2C_MA_CH * st_ap_CH, const ST_GP_I2C_MA_CTRL * st_ap_CTRL); /* Write Tx Count */
static U4      u4_s_GpI2cMaIRQEas_Orschk(const ST_GP_I2C_MA_CH * st_ap_CH, const ST_GP_I2C_MA_CTRL * st_ap_CTRL);
static U4      u4_s_GpI2cMaIRQEas_Rrcchk(const ST_GP_I2C_MA_CH * st_ap_CH, const ST_GP_I2C_MA_CTRL * st_ap_CTRL); /* Read Rx Count  */
static U4      u4_s_GpI2cMaIRQEas_Rlachk(const ST_GP_I2C_MA_CH * st_ap_CH, const ST_GP_I2C_MA_CTRL * st_ap_CTRL);
static U4      u4_s_GpI2cMaIRQEas_Reqchk(const ST_GP_I2C_MA_CH * st_ap_CH, const ST_GP_I2C_MA_CTRL * st_ap_CTRL);

static void    vd_s_GpI2cMaIRQAct_ToWri(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS);
static void    vd_s_GpI2cMaIRQAct_ToRea(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS);
static void    vd_s_GpI2cMaIRQAct_WrNex(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS);
static void    vd_s_GpI2cMaIRQAct_WrLas(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS);
static void    vd_s_GpI2cMaIRQAct_WrFin(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS);
static void    vd_s_GpI2cMaIRQAct_WrSta(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS);
static void    vd_s_GpI2cMaIRQAct_ReAck(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS);
static void    vd_s_GpI2cMaIRQAct_ReNak(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS);
static void    vd_s_GpI2cMaIRQAct_ReAbt(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS);
static void    vd_s_GpI2cMaIRQAct_ReFin(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS);
static void    vd_s_GpI2cMaIRQAct_ToSta(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS);
static void    vd_s_GpI2cMaIRQAct_ToReq(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS);
static void    vd_s_GpI2cMaIRQAct_SqAbt(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_GpI2cMaIRQTRx(const U1 u1_a_MA_CH)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GpI2cMaIRQTRx(const U1 u1_a_MA_CH)
{
    static const U1             u1_sp_GP_I2C_MA_SEQ[] = {
        (U1)GP_I2C_MA_ACT_TO_WRI, (U1)GP_I2C_MA_ACT_TO_REA, (U1)GP_I2C_MA_ACT_SQ_ABT, (U1)GP_I2C_MA_ACT_SQ_ABT,
        (U1)GP_I2C_MA_ACT_WR_NEX, (U1)GP_I2C_MA_ACT_WR_LAS, (U1)GP_I2C_MA_ACT_SQ_ABT, (U1)GP_I2C_MA_ACT_SQ_ABT,
        (U1)GP_I2C_MA_ACT_WR_FIN, (U1)GP_I2C_MA_ACT_WR_STA, (U1)GP_I2C_MA_ACT_SQ_ABT, (U1)GP_I2C_MA_ACT_SQ_ABT,
        (U1)GP_I2C_MA_ACT_RE_ACK, (U1)GP_I2C_MA_ACT_RE_NAK, (U1)GP_I2C_MA_ACT_RE_ABT, (U1)GP_I2C_MA_ACT_RE_ABT,
        (U1)GP_I2C_MA_ACT_RE_FIN, (U1)GP_I2C_MA_ACT_SQ_ABT, (U1)GP_I2C_MA_ACT_SQ_ABT, (U1)GP_I2C_MA_ACT_SQ_ABT,
        (U1)GP_I2C_MA_ACT_TO_REQ, (U1)GP_I2C_MA_ACT_TO_STA, (U1)GP_I2C_MA_ACT_SQ_ABT, (U1)GP_I2C_MA_ACT_SQ_ABT
    };

    static U4   ( * const       fp_sp_GP_I2C_MA_EAS[])(const ST_GP_I2C_MA_CH * st_ap_CH,
                                                       const ST_GP_I2C_MA_CTRL * st_ap_CTRL) = {
        &u4_s_GpI2cMaIRQEas_Opechk,                    /* GP_I2C_MA_SEQ_STA (0U)     */
        &u4_s_GpI2cMaIRQEas_Wtcchk,                    /* GP_I2C_MA_SEQ_WRI (1U)     */
        &u4_s_GpI2cMaIRQEas_Orschk,                    /* GP_I2C_MA_SEQ_WEN (2U)     */
        &u4_s_GpI2cMaIRQEas_Rrcchk,                    /* GP_I2C_MA_SEQ_REA (3U)     */
        &u4_s_GpI2cMaIRQEas_Rlachk,                    /* GP_I2C_MA_SEQ_RLA (4U)     */
        &u4_s_GpI2cMaIRQEas_Reqchk                     /* GP_I2C_MA_SEQ_FIN (5U)     */
    };

    static void ( * const       fp_sp_GP_I2C_MA_ACT[])(const ST_GP_I2C_MA_CH * st_ap_CH,
                                                       ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS) = {
        &vd_s_GpI2cMaIRQAct_ToWri,                     /* GP_I2C_MA_ACT_TO_WRI (0U)  */
        &vd_s_GpI2cMaIRQAct_ToRea,                     /* GP_I2C_MA_ACT_TO_REA (1U)  */
        &vd_s_GpI2cMaIRQAct_WrNex,                     /* GP_I2C_MA_ACT_WR_NEX (2U)  */
        &vd_s_GpI2cMaIRQAct_WrLas,                     /* GP_I2C_MA_ACT_WR_LAS (3U)  */
        &vd_s_GpI2cMaIRQAct_WrFin,                     /* GP_I2C_MA_ACT_WR_FIN (4U)  */
        &vd_s_GpI2cMaIRQAct_WrSta,                     /* GP_I2C_MA_ACT_WR_STA (5U)  */
        &vd_s_GpI2cMaIRQAct_ReAck,                     /* GP_I2C_MA_ACT_RE_ACK (6U)  */
        &vd_s_GpI2cMaIRQAct_ReNak,                     /* GP_I2C_MA_ACT_RE_NAK (7U)  */
        &vd_s_GpI2cMaIRQAct_ReAbt,                     /* GP_I2C_MA_ACT_RE_ABT (8U)  */
        &vd_s_GpI2cMaIRQAct_ReFin,                     /* GP_I2C_MA_ACT_RE_FIN (9U)  */
        &vd_s_GpI2cMaIRQAct_ToSta,                     /* GP_I2C_MA_ACT_TO_STA (10U) */
        &vd_s_GpI2cMaIRQAct_ToReq,                     /* GP_I2C_MA_ACT_TO_REQ (11U) */
        &vd_s_GpI2cMaIRQAct_SqAbt                      /* GP_I2C_MA_ACT_SQ_ABT (12U) */
    };

    const ST_GP_I2C_MA_CH *     st_tp_CH;
    ST_GP_I2C_MA_CTRL *         st_tp_ctrl;

    U4                          u4_t_eas;
    U4                          u4_t_act;

    U2                          u2_t_seq;

    if(u1_a_MA_CH < u1_g_GP_I2C_MA_NUM_CH){

        st_tp_CH   = &st_gp_GP_I2C_MA_CH[u1_a_MA_CH];
        st_tp_ctrl = &st_gp_gpi2c_ma_ctrl[u1_a_MA_CH];

        u2_t_seq   = st_tp_ctrl->u2_seq;
        if(u2_t_seq > (U2)GP_I2C_MA_SEQ_FIN){
            u2_t_seq = (U2)GP_I2C_MA_SEQ_FIN;
            u4_t_eas = u4_g_GpI2cMaIfIRQst(st_tp_CH, u2_t_seq) | (U4)GP_I2C_MA_ERR_SEQ_UNK;
        }
        else{
            u4_t_eas = u4_g_GpI2cMaIfIRQst(st_tp_CH, u2_t_seq);
        }

        if(fp_sp_GP_I2C_MA_EAS[u2_t_seq] != vdp_PTR_NA){
            u4_t_eas |= (*fp_sp_GP_I2C_MA_EAS[u2_t_seq])(st_tp_CH, st_tp_ctrl);
        }

        u4_t_act = ((U4)u2_t_seq << GP_I2C_MA_ACT_LSB_SEQ) + (u4_t_eas & (U4)GP_I2C_MA_ACT_EAS_MAX);
        u4_t_act = (U4)u1_sp_GP_I2C_MA_SEQ[u4_t_act];
        (*fp_sp_GP_I2C_MA_ACT[u4_t_act])(st_tp_CH, st_tp_ctrl, u4_t_eas);
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_GpI2cMaIRQDmaRx(const U1 u1_a_MA_CH)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GpI2cMaIRQDmaRx(const U1 u1_a_MA_CH)
{
#if (GP_I2C_MA_RWC_DMA_REA >= 4U)
    const ST_GP_I2C_MA_CH *     st_tp_CH;
    ST_GP_I2C_MA_CTRL *         st_tp_ctrl;
    U4                          u4_t_eas;
    U4                          u4_t_dma;
    U2                          u2_t_seq;

    if(u1_a_MA_CH < u1_g_GP_I2C_MA_NUM_CH){

        st_tp_CH   = &st_gp_GP_I2C_MA_CH[u1_a_MA_CH];
        st_tp_ctrl = &st_gp_gpi2c_ma_ctrl[u1_a_MA_CH];

        u2_t_seq   = st_tp_ctrl->u2_seq;
        if(u2_t_seq == (U2)GP_I2C_MA_SEQ_REA){

            u4_t_eas = u4_s_GpI2cMaIRQEas_Rrcchk(st_tp_CH, st_tp_ctrl);
            u4_t_dma = u4_g_GpI2cMaIfDmaRxchk(st_tp_CH);
            if(u4_t_dma == (U4)GP_I2C_MA_EAS_REA_RUN){
                /* do nothing */
            }
            else if(u4_t_eas != (U4)GP_I2C_MA_EAS_RWC_MAX){

                u4_t_dma = (u4_t_eas | (U4)GP_I2C_MA_ERR_RWC_UNK) | u4_t_dma;
                vd_s_GpI2cMaIRQAct_ReAbt(st_tp_CH, st_tp_ctrl, u4_t_dma);
            }
            else if(u4_t_dma != (U4)0U){

                vd_s_GpI2cMaIRQAct_ReAbt(st_tp_CH, st_tp_ctrl, u4_t_dma);
            }
            else{

                vd_s_GpI2cMaIRQAct_ReNak(st_tp_CH, st_tp_ctrl, u4_t_dma);
            }

            vd_g_GpI2cMaIfIRQ_ReaEI(st_tp_CH);
        }
    }
#endif /* #if (GP_I2C_MA_RWC_DMA_REA >= 4U) */
}
/*===================================================================================================================================*/
/*  static U4      u4_s_GpI2cMaIRQEas_Opechk(const ST_GP_I2C_MA_CH * st_ap_CH, const ST_GP_I2C_MA_CTRL * st_ap_CTRL)                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_GpI2cMaIRQEas_Opechk(const ST_GP_I2C_MA_CH * st_ap_CH, const ST_GP_I2C_MA_CTRL * st_ap_CTRL)
{
    ST_GP_I2C_MA_REQ *          st_tp_que;
    U1 *                        u1_tp_pdu;

    U4                          u4_t_eas;
    U2                          u2_t_run;

    u2_t_run = st_ap_CTRL->u2_run;
    if(u2_t_run < st_ap_CH->u2_nque){

        st_tp_que = st_ap_CH->stp_QUE;
        u1_tp_pdu = st_tp_que[u2_t_run].u1p_pdu;
        if(u1_tp_pdu != vdp_PTR_NA){
            u4_t_eas  = (U4)u1_tp_pdu[0U] & (U4)GP_I2C_MA_EAS_OPE_REA;
        }
        else{
            u4_t_eas = (U4)GP_I2C_MA_ERR_PDU_UNK | (U4)GP_I2C_MA_EAS_SEQ_ABT;
        }
    }
    else{
        u4_t_eas = (U4)GP_I2C_MA_ERR_REQ_UNK | (U4)GP_I2C_MA_EAS_SEQ_ABT;
    }

    return(u4_t_eas);
}
/*===================================================================================================================================*/
/*  static U4      u4_s_GpI2cMaIRQEas_Wtcchk(const ST_GP_I2C_MA_CH * st_ap_CH, const ST_GP_I2C_MA_CTRL * st_ap_CTRL)                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_GpI2cMaIRQEas_Wtcchk(const ST_GP_I2C_MA_CH * st_ap_CH, const ST_GP_I2C_MA_CTRL * st_ap_CTRL)
{
    ST_GP_I2C_MA_REQ *          st_tp_que;
    U4                          u4_t_max;
    U4                          u4_t_rwc;
    U4                          u4_t_eas;

    U2                          u2_t_run;

    u2_t_run = st_ap_CTRL->u2_run;
    if(u2_t_run < st_ap_CH->u2_nque){

        st_tp_que = st_ap_CH->stp_QUE;
        st_tp_que = &st_tp_que[u2_t_run];
        u4_t_max  = (U4)st_tp_que->u4_cbf & (U4)GP_I2C_MA_CBF_BIT_RWC;
        u4_t_rwc  = (U4)st_ap_CTRL->u2_rwc + (U4)1U;
        if(u4_t_rwc > u4_t_max){
            u4_t_eas = (U4)GP_I2C_MA_ERR_RWC_UNK | (U4)GP_I2C_MA_EAS_SEQ_ABT;
        }
        else if(u4_t_rwc >= u4_t_max){
            u4_t_eas = (U4)GP_I2C_MA_EAS_RWC_MAX;
        }
        else{
            u4_t_eas = (U4)0U;
        }
    }
    else{
        u4_t_eas = (U4)GP_I2C_MA_ERR_REQ_UNK | (U4)GP_I2C_MA_EAS_SEQ_ABT;
    }

    return(u4_t_eas);
}
/*===================================================================================================================================*/
/*  static U4      u4_s_GpI2cMaIRQEas_Orschk(const ST_GP_I2C_MA_CH * st_ap_CH, const ST_GP_I2C_MA_CTRL * st_ap_CTRL)                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_GpI2cMaIRQEas_Orschk(const ST_GP_I2C_MA_CH * st_ap_CH, const ST_GP_I2C_MA_CTRL * st_ap_CTRL)
{
    ST_GP_I2C_MA_REQ *          st_tp_que;

    U4                          u4_t_nque;
    U4                          u4_t_req;
    U4                          u4_t_run;
    U4                          u4_t_ack;
    U4                          u4_t_eas;

    U1                          u1_t_ok;

    u4_t_nque = (U4)st_ap_CH->u2_nque;
    u4_t_req  = (U4)st_ap_CTRL->u2_req;
    u4_t_run  = (U4)st_ap_CTRL->u2_run;
    u4_t_ack  = (U4)st_ap_CTRL->u2_ack;

    if((u4_t_req < u4_t_nque) &&
       (u4_t_run < u4_t_nque) &&
       (u4_t_ack < u4_t_nque)){

        u4_t_run++;
        if(u4_t_run >= u4_t_nque){
            u4_t_run = (U4)0U;
        }

        if(u4_t_req > u4_t_run){                           /* .u2_req       >  (.u2_run + 1) */
            u1_t_ok  = (U1)GP_I2C_MA_QUE_REQ_GT_RUN;
            u4_t_eas = (U4)GP_I2C_MA_EAS_REQ_NEX;
         }
        else if(u4_t_req >= u4_t_run){                     /* .u2_req       >= (.u2_run + 1) */
            u1_t_ok  = (U1)GP_I2C_MA_QUE_REQ_GE_RUN;
            u4_t_eas = (U4)0U;

        }
        else{
            u1_t_ok  = (U1)0U;
            u4_t_eas = (U4)GP_I2C_MA_EAS_REQ_NEX;
         }
        if(u4_t_run > u4_t_ack){                           /* (.u2_run + 1) >  .u2_ack       */
            u1_t_ok |= (U1)GP_I2C_MA_QUE_RUN_GT_ACK;
        }
        if(u4_t_ack > u4_t_req){                           /* .u2_ack       >  .u2_req       */
            u1_t_ok |= (U1)GP_I2C_MA_QUE_ACK_GT_REQ;
        }

        u4_t_eas  &= ((U4)GP_I2C_MA_QUE_CMPR_OK >> u1_t_ok);
        st_tp_que  = st_ap_CH->stp_QUE;
        u4_t_eas  &= (st_tp_que[u4_t_run].u4_cbf >> GP_I2C_MA_CBF_LSB_RSR);
    }
    else{
        u4_t_eas = (U4)0U;
    }

    return(u4_t_eas);
}
/*===================================================================================================================================*/
/*  static U4      u4_s_GpI2cMaIRQEas_Rrcchk(const ST_GP_I2C_MA_CH * st_ap_CH, const ST_GP_I2C_MA_CTRL * st_ap_CTRL)                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_GpI2cMaIRQEas_Rrcchk(const ST_GP_I2C_MA_CH * st_ap_CH, const ST_GP_I2C_MA_CTRL * st_ap_CTRL)
{
    ST_GP_I2C_MA_REQ *          st_tp_que;
    U4                          u4_t_max;
    U4                          u4_t_rwc;
    U4                          u4_t_eas;

    U2                          u2_t_run;

    u2_t_run = st_ap_CTRL->u2_run;
    if(u2_t_run < st_ap_CH->u2_nque){

        st_tp_que = st_ap_CH->stp_QUE;
        st_tp_que = &st_tp_que[u2_t_run];
        u4_t_max  = (U4)st_tp_que->u4_cbf & (U4)GP_I2C_MA_CBF_BIT_RWC;
        u4_t_rwc  = (U4)st_ap_CTRL->u2_rwc + (U4)GP_I2C_MA_RRC_TO_RLA;
        if(u4_t_rwc > u4_t_max){
            u4_t_eas = (U4)GP_I2C_MA_ERR_RWC_UNK | (U4)GP_I2C_MA_EAS_SEQ_ABT;
        }
        else if(u4_t_rwc >= u4_t_max){
            u4_t_eas = (U4)GP_I2C_MA_EAS_RWC_MAX;
        }
        else{
            u4_t_eas = (U4)0U;
        }
    }
    else{
        u4_t_eas = (U4)GP_I2C_MA_ERR_REQ_UNK | (U4)GP_I2C_MA_EAS_SEQ_ABT;
    }

    return(u4_t_eas);
}
/*===================================================================================================================================*/
/*  static U4      u4_s_GpI2cMaIRQEas_Rlachk(const ST_GP_I2C_MA_CH * st_ap_CH, const ST_GP_I2C_MA_CTRL * st_ap_CTRL)                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_GpI2cMaIRQEas_Rlachk(const ST_GP_I2C_MA_CH * st_ap_CH, const ST_GP_I2C_MA_CTRL * st_ap_CTRL)
{
    ST_GP_I2C_MA_REQ *          st_tp_que;
    U4                          u4_t_max;
    U4                          u4_t_rwc;
    U4                          u4_t_eas;

    U2                          u2_t_run;

    u2_t_run = st_ap_CTRL->u2_run;
    if(u2_t_run < st_ap_CH->u2_nque){

        st_tp_que = st_ap_CH->stp_QUE;
        st_tp_que = &st_tp_que[u2_t_run];
        u4_t_max  = (U4)st_tp_que->u4_cbf & (U4)GP_I2C_MA_CBF_BIT_RWC;
        u4_t_rwc  = (U4)st_ap_CTRL->u2_rwc + (U4)1U;
        if(u4_t_rwc == u4_t_max){
            u4_t_eas = (U4)0U;
        }
        else{
            u4_t_eas = (U4)GP_I2C_MA_ERR_RWC_UNK | (U4)GP_I2C_MA_EAS_SEQ_ABT;
        }
    }
    else{
        u4_t_eas = (U4)GP_I2C_MA_ERR_REQ_UNK | (U4)GP_I2C_MA_EAS_SEQ_ABT;
    }

    return(u4_t_eas);
}
/*===================================================================================================================================*/
/*  static U4      u4_s_GpI2cMaIRQEas_Reqchk(const ST_GP_I2C_MA_CH * st_ap_CH, const ST_GP_I2C_MA_CTRL * st_ap_CTRL)                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_GpI2cMaIRQEas_Reqchk(const ST_GP_I2C_MA_CH * st_ap_CH, const ST_GP_I2C_MA_CTRL * st_ap_CTRL)
{
    U4                          u4_t_nque;
    U4                          u4_t_req;
    U4                          u4_t_run;
    U4                          u4_t_ack;
    U4                          u4_t_eas;

    U1                          u1_t_ok;

    u4_t_nque = (U4)st_ap_CH->u2_nque;
    u4_t_req  = (U4)st_ap_CTRL->u2_req;
    u4_t_run  = (U4)st_ap_CTRL->u2_run;
    u4_t_ack  = (U4)st_ap_CTRL->u2_ack;

    if((u4_t_req < u4_t_nque) &&
       (u4_t_run < u4_t_nque) &&
       (u4_t_ack < u4_t_nque)){

        u4_t_run++;
        if(u4_t_run >= u4_t_nque){
            u4_t_run = (U4)0U;
        }

        if(u4_t_req > u4_t_run){                           /* .u2_req       >  (.u2_run + 1) */
            u1_t_ok  = (U1)GP_I2C_MA_QUE_REQ_GT_RUN;
            u4_t_eas = (U4)GP_I2C_MA_EAS_REQ_NEX;
        }
        else if(u4_t_req >= u4_t_run){                     /* .u2_req       >= (.u2_run + 1) */
            u1_t_ok  = (U1)GP_I2C_MA_QUE_REQ_GE_RUN;
            u4_t_eas = (U4)0U;
        }
        else{
            u1_t_ok  = (U1)0U;
            u4_t_eas = (U4)GP_I2C_MA_EAS_REQ_NEX;
        }
        if(u4_t_run > u4_t_ack){                           /* (.u2_run + 1) >  .u2_ack       */
            u1_t_ok |= (U1)GP_I2C_MA_QUE_RUN_GT_ACK;
        }
        if(u4_t_ack > u4_t_req){                           /* .u2_ack       >  .u2_req       */
            u1_t_ok |= (U1)GP_I2C_MA_QUE_ACK_GT_REQ;
        }

        u1_t_ok = ((U1)GP_I2C_MA_QUE_CMPR_OK >> u1_t_ok) & (U1)0x01U;
        if(u1_t_ok == (U1)0U){
            u4_t_eas = (U4)GP_I2C_MA_ERR_REQ_UNK;          /* GP_I2C_MA_EAS_SEQ_ABT NOT set  */
        }
    }
    else{

        u4_t_eas = (U4)GP_I2C_MA_ERR_REQ_UNK;              /* GP_I2C_MA_EAS_SEQ_ABT NOT set  */
    }

    return(u4_t_eas);
}
/*===================================================================================================================================*/
/*  static void    vd_s_GpI2cMaIRQAct_ToWri(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS)     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
#if (GP_I2C_MA_RWC_DMA_WRI >= 2U)
static void    vd_s_GpI2cMaIRQAct_ToWri(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS)
{
    ST_GP_I2C_MA_REQ *          st_tp_que;
    U1 *                        u1_tp_pdu;
    U2                          u2_t_max;
    U2                          u2_t_run;

    st_ap_ctrl->u2_frt = u2_g_GpI2cMaIfFrt();

    st_tp_que          = st_ap_CH->stp_QUE;
    u2_t_run           = st_ap_ctrl->u2_run;
    u1_tp_pdu          = st_tp_que[u2_t_run].u1p_pdu;

    if(st_ap_CH->u1_dma_ch < u1_g_GP_I2C_MA_DMA_NUM_CH){
        u2_t_max       = (U2)st_tp_que[u2_t_run].u4_cbf & (U2)GP_I2C_MA_CBF_BIT_RWC;
    }
    else{
        u2_t_max       = (U2)0U;
    }

    if(u2_t_max >= (U2)GP_I2C_MA_RWC_DMA_WRI){

     /* ------------------------------------------------------------------------------------- */
     /* Attention :                                                                           */
     /* ------------------------------------------------------------------------------------- */
     /* The following statement is being skipped in order to reduce the throughput.           */
     /* ------------------------------------------------------------------------------------- */
     /* st_ap_ctrl->u2_rwc = u2_t_max; */
        st_ap_ctrl->u2_seq = (U2)GP_I2C_MA_SEQ_WEN;

        vd_g_GpI2cMaIfDmaTxAct(st_ap_CH, &u1_tp_pdu[1U], (u2_t_max - (U2)1U));
        vd_g_GpI2cMaIfIRQ_SeqEI(st_ap_CH);
    }
    else{

        st_ap_ctrl->u2_rwc = (U2)1U;               /* st_ap_ctrl->u2_rwc is being initialized to 1 */
        st_ap_ctrl->u2_seq = (U2)GP_I2C_MA_SEQ_WRI;

        vd_g_GpI2cMaIfIRQ_WriEI(st_ap_CH);
    }

    vd_g_GpI2cMaIfWriTx(st_ap_CH, &u1_tp_pdu[0U]);
}
#else
/*===================================================================================================================================*/
static void    vd_s_GpI2cMaIRQAct_ToWri(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS)
{
    ST_GP_I2C_MA_REQ *          st_tp_que;
    U1 *                        u1_tp_pdu;
    U2                          u2_t_run;

    st_ap_ctrl->u2_frt = u2_g_GpI2cMaIfFrt();

    st_ap_ctrl->u2_rwc = (U2)1U;                  /* st_ap_ctrl->u2_rwc is being initialized to 1 */
    st_ap_ctrl->u2_seq = (U2)GP_I2C_MA_SEQ_WRI;

    vd_g_GpI2cMaIfIRQ_WriEI(st_ap_CH);

    st_tp_que          = st_ap_CH->stp_QUE;
    u2_t_run           = st_ap_ctrl->u2_run;
    u1_tp_pdu          = st_tp_que[u2_t_run].u1p_pdu;
    vd_g_GpI2cMaIfWriTx(st_ap_CH, &u1_tp_pdu[0U]);
}
#endif /* #if (GP_I2C_MA_RWC_DMA_WRI >= 2U) */
/*===================================================================================================================================*/
/*  static void    vd_s_GpI2cMaIRQAct_ToRea(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS)     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_GpI2cMaIRQAct_ToRea(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS)
{
    ST_GP_I2C_MA_REQ *          st_tp_que;
    U1 *                        u1_tp_pdu;
    U2                          u2_t_run;

    st_ap_ctrl->u2_frt = u2_g_GpI2cMaIfFrt();

    st_ap_ctrl->u2_rwc = (U2)0U;                  /* st_ap_ctrl->u2_rwc is being initialized to 0 */
    st_ap_ctrl->u2_seq = (U2)GP_I2C_MA_SEQ_REA;

    vd_g_GpI2cMaIfIRQ_ReaEI(st_ap_CH);

    st_tp_que          = st_ap_CH->stp_QUE;
    u2_t_run           = st_ap_ctrl->u2_run;
    u1_tp_pdu          = st_tp_que[u2_t_run].u1p_pdu;
    vd_g_GpI2cMaIfWriTx(st_ap_CH, &u1_tp_pdu[0U]);
}
/*===================================================================================================================================*/
/*  static void    vd_s_GpI2cMaIRQAct_WrNex(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS)     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_GpI2cMaIRQAct_WrNex(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS)
{
    ST_GP_I2C_MA_REQ *          st_tp_que;
    U1 *                        u1_tp_pdu;
    U2                          u2_t_rwc;
    U2                          u2_t_run;

    st_ap_ctrl->u2_frt = u2_g_GpI2cMaIfFrt();

    u2_t_rwc           = st_ap_ctrl->u2_rwc;
    st_ap_ctrl->u2_rwc = u2_t_rwc + (U2)1U;
 /* ------------------------------------------------------------------------------------- */
 /* Attention :                                                                           */
 /* ------------------------------------------------------------------------------------- */
 /* The following statement is being skipped in order to reduce the throughput.           */
 /* ------------------------------------------------------------------------------------- */
 /* st_ap_ctrl->u2_seq = (U2)GP_I2C_MA_SEQ_WRI; */

    st_tp_que          = st_ap_CH->stp_QUE;
    u2_t_run           = st_ap_ctrl->u2_run;
    u1_tp_pdu          = st_tp_que[u2_t_run].u1p_pdu;
    vd_g_GpI2cMaIfWriTx(st_ap_CH, &u1_tp_pdu[u2_t_rwc]);
}
/*===================================================================================================================================*/
/*  static void    vd_s_GpI2cMaIRQAct_WrLas(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS)     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_GpI2cMaIRQAct_WrLas(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS)
{
    ST_GP_I2C_MA_REQ *          st_tp_que;
    U1 *                        u1_tp_pdu;
    U2                          u2_t_rwc;
    U2                          u2_t_run;

    st_ap_ctrl->u2_frt = u2_g_GpI2cMaIfFrt();

    u2_t_rwc           = st_ap_ctrl->u2_rwc;
 /* ------------------------------------------------------------------------------------- */
 /* Attention :                                                                           */
 /* ------------------------------------------------------------------------------------- */
 /* The following statement is being skipped in order to reduce the throughput.           */
 /* ------------------------------------------------------------------------------------- */
 /* st_ap_ctrl->u2_rwc = u2_t_rwc + (U2)1U; */
    st_ap_ctrl->u2_seq = (U2)GP_I2C_MA_SEQ_WEN;

    vd_g_GpI2cMaIfIRQ_SeqEI(st_ap_CH);

    st_tp_que           = st_ap_CH->stp_QUE;
    u2_t_run            = st_ap_ctrl->u2_run;
    u1_tp_pdu           = st_tp_que[u2_t_run].u1p_pdu;
    vd_g_GpI2cMaIfWriTx(st_ap_CH, &u1_tp_pdu[u2_t_rwc]);
}
/*===================================================================================================================================*/
/*  static void    vd_s_GpI2cMaIRQAct_WrFin(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS)     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_GpI2cMaIRQAct_WrFin(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS)
{
    st_ap_ctrl->u2_frt = u2_g_GpI2cMaIfFrt();
    st_ap_ctrl->u2_seq = (U2)GP_I2C_MA_SEQ_FIN;
    vd_g_GpI2cMaIfTRxFinish(st_ap_CH);
}
/*===================================================================================================================================*/
/*  static void    vd_s_GpI2cMaIRQAct_WrSta(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS)     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_GpI2cMaIRQAct_WrSta(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS)
{
    U4                          u4_t_run;

    u4_t_run = (U4)st_ap_ctrl->u2_run + (U4)1U;
    if(u4_t_run >= (U4)st_ap_CH->u2_nque){
        u4_t_run = (U4)0U;
    }
    st_ap_ctrl->u2_run = (U2)u4_t_run;

    st_ap_ctrl->u2_frt = u2_g_GpI2cMaIfFrt();
    st_ap_ctrl->u2_seq = (U2)GP_I2C_MA_SEQ_STA;
    vd_g_GpI2cMaIfTRxRepeat(st_ap_CH);
}
/*===================================================================================================================================*/
/*  static void    vd_s_GpI2cMaIRQAct_ReAck(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS)     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
#if (GP_I2C_MA_RWC_DMA_REA >= 4U)
static void    vd_s_GpI2cMaIRQAct_ReAck(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS)
{
    ST_GP_I2C_MA_REQ *          st_tp_que;
    U1 *                        u1_tp_pdu;
    U2                          u2_t_rwc;
    U2                          u2_t_max;
    U2                          u2_t_run;
    U1                          u1_t_dummy_rx;

    st_ap_ctrl->u2_frt = u2_g_GpI2cMaIfFrt();

 /* ------------------------------------------------------------------------------------- */
 /* Attention :                                                                           */
 /* ------------------------------------------------------------------------------------- */
 /* The following statement is being skipped in order to reduce the throughput.           */
 /* ------------------------------------------------------------------------------------- */
 /* st_ap_ctrl->u2_seq = (U2)GP_I2C_MA_SEQ_REA; */

    st_tp_que          = st_ap_CH->stp_QUE;
    u2_t_run           = st_ap_ctrl->u2_run;
    u1_tp_pdu          = st_tp_que[u2_t_run].u1p_pdu;

    if(st_ap_CH->u1_dma_ch < u1_g_GP_I2C_MA_DMA_NUM_CH){
        u2_t_max       = (U2)st_tp_que[u2_t_run].u4_cbf & (U2)GP_I2C_MA_CBF_BIT_RWC;
    }
    else{
        u2_t_max       = (U2)0U;
    }

    u2_t_rwc           = st_ap_ctrl->u2_rwc;
    if(u2_t_rwc > (U2)0U){

        st_ap_ctrl->u2_rwc = u2_t_rwc + (U2)1U;

        vd_g_GpI2cMaIfReaRx(st_ap_CH, &u1_tp_pdu[u2_t_rwc]);
    }
    else if(u2_t_max >= (U2)GP_I2C_MA_RWC_DMA_REA){

        st_ap_ctrl->u2_rwc = u2_t_max - (U2)GP_I2C_MA_RRC_TO_RLA;

        u2_t_max           = u2_t_max - ((U2)GP_I2C_MA_RRC_TO_RLA + (U2)1U);
        vd_g_GpI2cMaIfDmaRxAct(st_ap_CH, &u1_tp_pdu[1U], u2_t_max);

        vd_g_GpI2cMaIfResp_Ack(st_ap_CH);
        vd_g_GpI2cMaIfIRQ_SeqEI(st_ap_CH);
        vd_g_GpI2cMaIfReaRx(st_ap_CH, &u1_t_dummy_rx);
    }
    else{

        st_ap_ctrl->u2_rwc = u2_t_rwc + (U2)1U;

        vd_g_GpI2cMaIfResp_Ack(st_ap_CH);
        vd_g_GpI2cMaIfReaRx(st_ap_CH, &u1_t_dummy_rx);
    }
}
#else
/*===================================================================================================================================*/
static void    vd_s_GpI2cMaIRQAct_ReAck(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS)
{
    ST_GP_I2C_MA_REQ *          st_tp_que;
    U1 *                        u1_tp_pdu;
    U2                          u2_t_rwc;
    U2                          u2_t_run;
    U1                          u1_t_dummy_rx;

    st_ap_ctrl->u2_frt = u2_g_GpI2cMaIfFrt();

    u2_t_rwc           = st_ap_ctrl->u2_rwc;
    st_ap_ctrl->u2_rwc = u2_t_rwc + (U2)1U;
 /* ------------------------------------------------------------------------------------- */
 /* Attention :                                                                           */
 /* ------------------------------------------------------------------------------------- */
 /* The following statement is being skipped in order to reduce the throughput.           */
 /* ------------------------------------------------------------------------------------- */
 /* st_ap_ctrl->u2_seq = (U2)GP_I2C_MA_SEQ_REA; */

    if(u2_t_rwc > (U2)0U){

        st_tp_que = st_ap_CH->stp_QUE;
        u2_t_run  = st_ap_ctrl->u2_run;
        u1_tp_pdu = st_tp_que[u2_t_run].u1p_pdu;
        vd_g_GpI2cMaIfReaRx(st_ap_CH, &u1_tp_pdu[u2_t_rwc]);
    }
    else{

        vd_g_GpI2cMaIfResp_Ack(st_ap_CH);
        vd_g_GpI2cMaIfReaRx(st_ap_CH, &u1_t_dummy_rx);
    }
}
#endif /* #if (GP_I2C_MA_RWC_DMA_REA >= 4U) */
/*===================================================================================================================================*/
/*  static void    vd_s_GpI2cMaIRQAct_ReNak(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS)     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_GpI2cMaIRQAct_ReNak(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS)
{
    ST_GP_I2C_MA_REQ *          st_tp_que;
    U1 *                        u1_tp_pdu;
    U2                          u2_t_rwc;
    U2                          u2_t_run;
    U1                          u1_t_dummy_rx;

    st_ap_ctrl->u2_frt = u2_g_GpI2cMaIfFrt();

    u2_t_rwc           = st_ap_ctrl->u2_rwc;
    st_ap_ctrl->u2_rwc = u2_t_rwc + (U2)1U;
    st_ap_ctrl->u2_seq = (U2)GP_I2C_MA_SEQ_RLA;

    vd_g_GpI2cMaIfRespNack(st_ap_CH);

    if(u2_t_rwc > (U2)0U){

        st_tp_que = st_ap_CH->stp_QUE;
        u2_t_run  = st_ap_ctrl->u2_run;
        u1_tp_pdu = st_tp_que[u2_t_run].u1p_pdu;
        vd_g_GpI2cMaIfReaRx(st_ap_CH, &u1_tp_pdu[u2_t_rwc]);
    }
    else{

        vd_g_GpI2cMaIfReaRx(st_ap_CH, &u1_t_dummy_rx);
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_GpI2cMaIRQAct_ReAbt(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS)     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_GpI2cMaIRQAct_ReAbt(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS)
{
    ST_GP_I2C_MA_REQ *          st_tp_que;
    U2                          u2_t_run;
    U1                          u1_t_dummy_rx;

#if ((GP_I2C_MA_RWC_DMA_WRI >= 2U) || (GP_I2C_MA_RWC_DMA_REA >= 4U))
    if(st_ap_CH->u1_dma_ch < u1_g_GP_I2C_MA_DMA_NUM_CH){
        vd_g_GpI2cMaIfDmaDeAct(st_ap_CH);
    }
#endif /* #if ((GP_I2C_MA_RWC_DMA_WRI >= 2U) || (GP_I2C_MA_RWC_DMA_REA >= 4U)) */

    if(u4_a_EAS < (U4)GP_I2C_MA_ERR_REQ_UNK){
        st_tp_que                   = st_ap_CH->stp_QUE;
        u2_t_run                    = st_ap_ctrl->u2_run;
        st_tp_que[u2_t_run].u4_cbf |= (u4_a_EAS & (U4)GP_I2C_MA_CBF_BIT_ERR);
    }

    /* ------------------------------------------------------------------------------------- */
    /* Attention :                                                                           */
    /* ------------------------------------------------------------------------------------- */
    /* There is possibility that TRx sequence abort could be repeated unless all of error is */
    /* resolved. As the result, dead lock might be caused.                                   */
    /* Thus, free-run timer is NOT captured at here so that frame timeout can be detected in */
    /* vd_g_GpI2cMaMainTask.                                                                 */
    /* ------------------------------------------------------------------------------------- */
 /* st_ap_ctrl->u2_frt = u2_g_GpI2cMaIfFrt(); */
    st_ap_ctrl->u2_rwc = (U2)GP_I2C_MA_CBF_BIT_RWC;
    st_ap_ctrl->u2_seq = (U2)GP_I2C_MA_SEQ_RLA;

    vd_g_GpI2cMaIfRespNack(st_ap_CH);
    vd_g_GpI2cMaIfReaRx(st_ap_CH, &u1_t_dummy_rx);
}
/*===================================================================================================================================*/
/*  static void    vd_s_GpI2cMaIRQAct_ReFin(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS)     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_GpI2cMaIRQAct_ReFin(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS)
{
    ST_GP_I2C_MA_REQ *          st_tp_que;
    U1 *                        u1_tp_pdu;
    U2                          u2_t_rwc;
    U2                          u2_t_run;

    st_ap_ctrl->u2_frt = u2_g_GpI2cMaIfFrt();

    u2_t_rwc           = st_ap_ctrl->u2_rwc;
 /* ------------------------------------------------------------------------------------- */
 /* Attention :                                                                           */
 /* ------------------------------------------------------------------------------------- */
 /* The following statement is being skipped in order to reduce the throughput.           */
 /* ------------------------------------------------------------------------------------- */
 /* st_ap_ctrl->u2_rwc = u2_t_rwc + (U2)1U; */
    st_ap_ctrl->u2_seq = (U2)GP_I2C_MA_SEQ_FIN;

    vd_g_GpI2cMaIfTRxFinish(st_ap_CH);

    st_tp_que          = st_ap_CH->stp_QUE;
    u2_t_run           = st_ap_ctrl->u2_run;
    u1_tp_pdu          = st_tp_que[u2_t_run].u1p_pdu;
    vd_g_GpI2cMaIfReaRx(st_ap_CH, &u1_tp_pdu[u2_t_rwc]);
}
/*===================================================================================================================================*/
/*  static void    vd_s_GpI2cMaIRQAct_ToSta(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS)     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_GpI2cMaIRQAct_ToSta(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS)
{
    ST_GP_I2C_MA_REQ *          st_tp_que;

    U4                          u4_t_run;

    u4_t_run = (U4)st_ap_ctrl->u2_run;
    if(u4_a_EAS >= (U4)GP_I2C_MA_ERR_FR_TOUT){
        st_tp_que                   = st_ap_CH->stp_QUE;
        st_tp_que[u4_t_run].u4_cbf |= ((U4)u4_a_EAS & (U4)GP_I2C_MA_CBF_BIT_ERR);
    }

    u4_t_run++;
    if(u4_t_run >= (U4)st_ap_CH->u2_nque){
        u4_t_run = (U4)0U;
    }
    st_ap_ctrl->u2_run = (U2)u4_t_run;

    st_ap_ctrl->u2_frt = u2_g_GpI2cMaIfFrt();
 /* ------------------------------------------------------------------------------------- */
 /* Attention :                                                                           */
 /* ------------------------------------------------------------------------------------- */
 /* The following statement is being skipped in order to reduce the throughput.           */
 /* st_tp_ctrl->u2_rwc is being initialized to 0 or 1 in vd_g_GpI2cMaIRQTRx               */
 /*                                                            ->vd_s_GpI2cMaIRQAct_ToWri */
 /*                                                            ->vd_s_GpI2cMaIRQAct_ToRea */
 /* ------------------------------------------------------------------------------------- */
 /* st_ap_ctrl->u2_rwc = (U2)0U; */
    st_ap_ctrl->u2_seq = (U2)GP_I2C_MA_SEQ_STA;

#if ((GP_I2C_MA_RWC_DMA_WRI >= 2U) || (GP_I2C_MA_RWC_DMA_REA >= 4U))
    if(st_ap_CH->u1_dma_ch < u1_g_GP_I2C_MA_DMA_NUM_CH){
        vd_g_GpI2cMaIfDmaDeAct(st_ap_CH);
    }
#endif /* #if ((GP_I2C_MA_RWC_DMA_WRI >= 2U) || (GP_I2C_MA_RWC_DMA_REA >= 4U)) */

    vd_g_GpI2cMaIfTRxStart(st_ap_CH);
}
/*===================================================================================================================================*/
/*  static void    vd_s_GpI2cMaIRQAct_ToReq(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS)     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_GpI2cMaIRQAct_ToReq(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS)
{
    ST_GP_I2C_MA_REQ *          st_tp_que;

    U4                          u4_t_run;

#if ((GP_I2C_MA_RWC_DMA_WRI >= 2U) || (GP_I2C_MA_RWC_DMA_REA >= 4U))
    if(st_ap_CH->u1_dma_ch < u1_g_GP_I2C_MA_DMA_NUM_CH){
        vd_g_GpI2cMaIfDmaDeAct(st_ap_CH);
    }
#endif /* #if ((GP_I2C_MA_RWC_DMA_WRI >= 2U) || (GP_I2C_MA_RWC_DMA_REA >= 4U)) */

    vd_g_GpI2cMaIfIRQ_DI(st_ap_CH);

    if(u4_a_EAS >= (U4)GP_I2C_MA_ERR_REQ_UNK){

        st_ap_ctrl->u2_seq = (U2)GP_I2C_MA_SEQ_INA;
    }
    else{

        u4_t_run = (U4)st_ap_ctrl->u2_run;
        if(u4_a_EAS >= (U4)GP_I2C_MA_ERR_FR_TOUT){
            st_tp_que                   = st_ap_CH->stp_QUE;
            st_tp_que[u4_t_run].u4_cbf |= ((U4)u4_a_EAS & (U4)GP_I2C_MA_CBF_BIT_ERR);
        }

        u4_t_run++;
        if(u4_t_run >= (U4)st_ap_CH->u2_nque){
            u4_t_run = (U4)0U;
        }

        st_ap_ctrl->u2_run = (U2)u4_t_run;
     /* ------------------------------------------------------------------------------------- */
     /* Attention :                                                                           */
     /* ------------------------------------------------------------------------------------- */
     /* The following two lines are being skipped in order to reduce the throughput.          */
     /* st_tp_ctrl->u2_rwc is being initialized to 0 or 1 in vd_g_GpI2cMaIRQTRx               */
     /*                                                            ->vd_s_GpI2cMaIRQAct_ToWri */
     /*                                                            ->vd_s_GpI2cMaIRQAct_ToRea */
     /* ------------------------------------------------------------------------------------- */
     /* st_ap_ctrl->u2_frt = u2_g_GpI2cMaIfFrt(); */
     /* st_ap_ctrl->u2_rwc = (U2)0U; */
        st_ap_ctrl->u2_seq = (U2)GP_I2C_MA_SEQ_REQ;
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_GpI2cMaIRQAct_SqAbt(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS)     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_GpI2cMaIRQAct_SqAbt(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS)
{
    ST_GP_I2C_MA_REQ *          st_tp_que;

    U2                          u2_t_run;
    U1                          u1_t_dummy_rx;

#if ((GP_I2C_MA_RWC_DMA_WRI >= 2U) || (GP_I2C_MA_RWC_DMA_REA >= 4U))
    if(st_ap_CH->u1_dma_ch < u1_g_GP_I2C_MA_DMA_NUM_CH){
        vd_g_GpI2cMaIfDmaDeAct(st_ap_CH);
    }
#endif /* #if ((GP_I2C_MA_RWC_DMA_WRI >= 2U) || (GP_I2C_MA_RWC_DMA_REA >= 4U)) */

    /* ------------------------------------------------------------------------------------- */
    /* Attention :                                                                           */
    /* ------------------------------------------------------------------------------------- */
    /* st_ap_ctrl->u2_run is not tested if st_ap_ctrl->u2_seq is equal to GP_I2C_MA_SEQ_WEN. */
    /* Thus, st_ap_ctrl->u2_run is tested at here.                                           */
    /* ------------------------------------------------------------------------------------- */
    u2_t_run = st_ap_ctrl->u2_run;
    if(u2_t_run < st_ap_CH->u2_nque){
        st_tp_que                   = st_ap_CH->stp_QUE;
        st_tp_que[u2_t_run].u4_cbf |= (u4_a_EAS & (U4)GP_I2C_MA_CBF_BIT_ERR);
    }

    /* ------------------------------------------------------------------------------------- */
    /* Attention :                                                                           */
    /* ------------------------------------------------------------------------------------- */
    /* There is possibility that TRx sequence abort could be repeated unless all of error is */
    /* resolved. As the result, dead lock might be caused.                                   */
    /* Thus, free-run timer is NOT captured at here so that frame timeout can be detected in */
    /* vd_g_GpI2cMaMainTask.                                                                 */
    /* ------------------------------------------------------------------------------------- */
 /* st_ap_ctrl->u2_frt = u2_g_GpI2cMaIfFrt(); */
    st_ap_ctrl->u2_seq = (U2)GP_I2C_MA_SEQ_FIN;

    vd_g_GpI2cMaIfTRxFinish(st_ap_CH);
    vd_g_GpI2cMaIfReaRx(st_ap_CH, &u1_t_dummy_rx);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.1.0    10/10/2024  TN       New.                                                                                               */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
