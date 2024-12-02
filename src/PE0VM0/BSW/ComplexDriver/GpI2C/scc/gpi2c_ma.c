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
#define GP_I2C_MA_C_MAJOR                        (1)
#define GP_I2C_MA_C_MINOR                        (1)
#define GP_I2C_MA_C_PATCH                        (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "gpi2c_ma_cfg_private.h"
#include "gpi2c_ma_if.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((GP_I2C_MA_C_MAJOR != GP_I2C_MA_H_MAJOR) || \
     (GP_I2C_MA_C_MINOR != GP_I2C_MA_H_MINOR) || \
     (GP_I2C_MA_C_PATCH != GP_I2C_MA_H_PATCH))
#error "gpi2c_ma.c and gpi2c_ma.h : source and header files are inconsistent!"
#endif

#if ((GP_I2C_MA_C_MAJOR != GP_I2C_MA_CFG_H_MAJOR) || \
     (GP_I2C_MA_C_MINOR != GP_I2C_MA_CFG_H_MINOR) || \
     (GP_I2C_MA_C_PATCH != GP_I2C_MA_CFG_H_PATCH))
#error "gpi2c_ma.c and gpi2c_ma_cfg_private.h : source and header files are inconsistent!"
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
#define GP_I2C_MA_ACT_RE_ACK                     (5U)           /* REA->REA */
#define GP_I2C_MA_ACT_RE_NAK                     (6U)           /* REA->RLA */
#define GP_I2C_MA_ACT_RE_ABT                     (7U)           /* REA->RLA */
#define GP_I2C_MA_ACT_RE_FIN                     (8U)           /* RLA->FIN */
#define GP_I2C_MA_ACT_TO_STA                     (9U)           /* FIN->STA */
#define GP_I2C_MA_ACT_TO_REQ                     (10U)          /* FIN->REQ */
#define GP_I2C_MA_ACT_SQ_ABT                     (11U)          /* XXX->FIN */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GP_I2C_MA_ACT_EAS_MAX                    (0x00000003U)
#define GP_I2C_MA_ACT_LSB_SEQ                    (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GP_I2C_MA_QUE_TRY_NO                     (0U)
#define GP_I2C_MA_QUE_TRY_YES                    (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Comparison of st_gp_gpi2c_ma_ctrl[].u2_req and                                        */
/*                                    .u2_run and                                        */
/*                                    .u2_ack                                            */
/*---------------------------------------------------------------------------------------*/
/*                      .u2_req     >= .u2_run    >= .u2_ack       : 110b / bit#6 = 0x40 */
/*                      .u2_run     >= .u2_ack    >  .u2_req       : 011b / bit#3 = 0x08 */
/*                      .u2_ack     >  .u2_req    >= .u2_run       : 101b / bit#5 = 0x20 */
/*---------------------------------------------------------------------------------------*/
/*                      .u2_req + 1 >  .u2_run     >= .u2_ack      : 110b / bit#6 = 0x40 */
/*                      .u2_run     >= .u2_ack     >  .u2_req + 1  : 011b / bit#3 = 0x08 */
/*                      .u2_ack     >  .u2_req + 1 >  .u2_run      : 101b / bit#5 = 0x20 */
/*---------------------------------------------------------------------------------------*/
/*                      .u2_req     >= .u2_run + 1 >  .u2_ack      : 110b / bit#6 = 0x40 */
/*                      .u2_run + 1 >  .u2_ack     >  .u2_req      : 011b / bit#3 = 0x08 */
/*                      .u2_ack     >  .u2_req     >= .u2_run + 1  : 101b / bit#5 = 0x20 */
/*---------------------------------------------------------------------------------------*/
#define GP_I2C_MA_QUE_CMPR_OK                    (0x68U)
#define GP_I2C_MA_QUE_REQ_GT_RUN                 (0x04U)   /* (.u2_req + 1) >  .u2_run       */
#define GP_I2C_MA_QUE_REQ_GE_RUN                 (0x04U)   /* .u2_req       >= .u2_run       */
                                                           /* .u2_req       >= (.u2_run + 1) */
#define GP_I2C_MA_QUE_RUN_GT_ACK                 (0x02U)   /* (.u2_run + 1) >  .u2_ack       */
#define GP_I2C_MA_QUE_RUN_GE_ACK                 (0x02U)   /* .u2_run       >= .u2_ack       */
#define GP_I2C_MA_QUE_ACK_GT_REQ                 (0x01U)   /* .u2_ack       >  .u2_req       */
                                                           /* .u2_ack       >  (.u2_req + 1) */

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
static U4      u4_s_GpI2cMaQueTryPush(const ST_GP_I2C_MA_CTRL * st_ap_CTRL, const U4 u4_a_NQUE, const U4 u4_a_OPT);
static void    vd_s_GpI2cMaSeqReset(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U2 u2_a_SEQ);
static void    vd_s_GpI2cMaRwcReset(const ST_GP_I2C_MA_CH * st_ap_CH);
static void    vd_s_GpI2cMaFraTout(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl);
static void    vd_s_GpI2cMaTRxAck(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl);

static void    vd_s_GpI2cMaQuePush(const ST_GP_I2C_MA_REQ * st_ap_REQ, ST_GP_I2C_MA_REQ * st_ap_que);

static U4      u4_s_GpI2cMaIRQEas_Opechk(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl);
static U4      u4_s_GpI2cMaIRQEas_Wtcchk(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl); /* Write Tx Count */
static U4      u4_s_GpI2cMaIRQEas_Rrcchk(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl); /* Read Rx Count  */
static U4      u4_s_GpI2cMaIRQEas_Rlachk(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl);
static U4      u4_s_GpI2cMaIRQEas_Reqchk(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl);

static void    vd_s_GpI2cMaIRQAct_ToWri(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS);
static void    vd_s_GpI2cMaIRQAct_ToRea(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS);
static void    vd_s_GpI2cMaIRQAct_WrNex(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS);
static void    vd_s_GpI2cMaIRQAct_WrLas(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS);
static void    vd_s_GpI2cMaIRQAct_WrFin(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS);
static void    vd_s_GpI2cMaIRQAct_ReAck(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS);
static void    vd_s_GpI2cMaIRQAct_ReNak(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS);
static void    vd_s_GpI2cMaIRQAct_ReAbt(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS);
static void    vd_s_GpI2cMaIRQAct_ReFin(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS);
static void    vd_s_GpI2cMaIRQAct_ToSta(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS);
static void    vd_s_GpI2cMaIRQAct_ToReq(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS);
static void    vd_s_GpI2cMaIRQAct_SqAbt(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U4 u4_a_EAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static inline void    vd_s_GpI2cMaSeqStart(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_GpI2cMaInit(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GpI2cMaInit(void)
{
    U4                          u4_t_ch;
    U4                          u4_t_sla;

    for(u4_t_ch = (U4)0U; u4_t_ch < (U4)u1_g_GP_I2C_MA_NUM_CH; u4_t_ch++){

        vd_g_GpI2cMaIfDisCh(&st_gp_GP_I2C_MA_CH[u4_t_ch]);

        st_gp_gpi2c_ma_ctrl[u4_t_ch].u2_req = (U2)0U;
        st_gp_gpi2c_ma_ctrl[u4_t_ch].u2_run = (U2)0U;
        st_gp_gpi2c_ma_ctrl[u4_t_ch].u2_ack = (U2)0U;
        st_gp_gpi2c_ma_ctrl[u4_t_ch].u2_frt = (U2)0U;
        st_gp_gpi2c_ma_ctrl[u4_t_ch].u2_rwc = (U2)0U;
        st_gp_gpi2c_ma_ctrl[u4_t_ch].u2_seq = (U2)GP_I2C_MA_SEQ_INA;
    }

    for(u4_t_sla = (U4)0U; u4_t_sla < (U4)u1_g_GP_I2C_MA_NUM_SLA; u4_t_sla++){
        u2_gp_gpi2c_ma_rwc_by_sla[u4_t_sla] = (U2)0U;
    }

    vd_g_GpI2cMaCfgInit();
}
/*===================================================================================================================================*/
/*  void    vd_g_GpI2cMaDeInit(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GpI2cMaDeInit(void)
{
    U4                          u4_t_ch;
    U4                          u4_t_sla;
    U2                          u2_t_seq;

    for(u4_t_ch = (U4)0U; u4_t_ch < (U4)u1_g_GP_I2C_MA_NUM_CH; u4_t_ch++){

        u2_t_seq = st_gp_gpi2c_ma_ctrl[u4_t_ch].u2_seq;
        if(u2_t_seq < (U2)GP_I2C_MA_SEQ_INA){

            vd_g_GpI2cMaIfDisCh(&st_gp_GP_I2C_MA_CH[u4_t_ch]);

            st_gp_gpi2c_ma_ctrl[u4_t_ch].u2_req = (U2)0U;
            st_gp_gpi2c_ma_ctrl[u4_t_ch].u2_run = (U2)0U;
            st_gp_gpi2c_ma_ctrl[u4_t_ch].u2_ack = (U2)0U;
            st_gp_gpi2c_ma_ctrl[u4_t_ch].u2_frt = (U2)0U;
            st_gp_gpi2c_ma_ctrl[u4_t_ch].u2_rwc = (U2)0U;
            st_gp_gpi2c_ma_ctrl[u4_t_ch].u2_seq = (U2)GP_I2C_MA_SEQ_INA;
        }
    }

    for(u4_t_sla = (U4)0U; u4_t_sla < (U4)u1_g_GP_I2C_MA_NUM_SLA; u4_t_sla++){
        u2_gp_gpi2c_ma_rwc_by_sla[u4_t_sla] = (U2)0U;
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_GpI2cMaMainTask(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GpI2cMaMainTask(void)
{
    const ST_GP_I2C_MA_CH *     st_tp_CH;
    ST_GP_I2C_MA_CTRL *         st_tp_ctrl;

    U4                          u4_t_ch;
    U4                          u4_t_nque;
    U4                          u4_t_req;
    U2                          u2_t_seq;
    U1                          u1_t_act;

    for(u4_t_ch = (U4)0U; u4_t_ch < (U4)u1_g_GP_I2C_MA_NUM_CH; u4_t_ch++){

        st_tp_CH   = &st_gp_GP_I2C_MA_CH[u4_t_ch];
        st_tp_ctrl = &st_gp_gpi2c_ma_ctrl[u4_t_ch];

        u4_t_nque  = (U4)st_tp_CH->u2_nque;
        u4_t_req   = u4_s_GpI2cMaQueTryPush(st_tp_ctrl, u4_t_nque, (U4)GP_I2C_MA_QUE_TRY_NO);
        u1_t_act   = u1_g_GpI2cMaCfgSlaActvtd((U1)u4_t_ch);
        if(u1_t_act != (U1)TRUE){

            u2_t_seq = st_tp_ctrl->u2_seq;
            if(u2_t_seq < (U2)GP_I2C_MA_SEQ_INA){

                vd_s_GpI2cMaSeqReset(st_tp_CH, st_tp_ctrl, (U2)GP_I2C_MA_SEQ_INA);
                vd_s_GpI2cMaRwcReset(st_tp_CH);
            }
        }
        else if(u4_t_req >= u4_t_nque){

            vd_s_GpI2cMaSeqReset(st_tp_CH, st_tp_ctrl, (U2)GP_I2C_MA_SEQ_REQ);
            vd_s_GpI2cMaRwcReset(st_tp_CH);
        }
        else{

            vd_s_GpI2cMaFraTout(st_tp_CH, st_tp_ctrl);
            vd_s_GpI2cMaTRxAck(st_tp_CH, st_tp_ctrl);
        }
    }
}
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
        (U1)GP_I2C_MA_ACT_WR_FIN, (U1)GP_I2C_MA_ACT_SQ_ABT, (U1)GP_I2C_MA_ACT_SQ_ABT, (U1)GP_I2C_MA_ACT_SQ_ABT,
        (U1)GP_I2C_MA_ACT_RE_ACK, (U1)GP_I2C_MA_ACT_RE_NAK, (U1)GP_I2C_MA_ACT_RE_ABT, (U1)GP_I2C_MA_ACT_RE_ABT,
        (U1)GP_I2C_MA_ACT_RE_FIN, (U1)GP_I2C_MA_ACT_SQ_ABT, (U1)GP_I2C_MA_ACT_SQ_ABT, (U1)GP_I2C_MA_ACT_SQ_ABT,
        (U1)GP_I2C_MA_ACT_TO_REQ, (U1)GP_I2C_MA_ACT_TO_STA, (U1)GP_I2C_MA_ACT_SQ_ABT, (U1)GP_I2C_MA_ACT_SQ_ABT
    };

    static U4   ( * const       fp_sp_GP_I2C_MA_EAS[])(const ST_GP_I2C_MA_CH * st_ap_CH,
                                                       ST_GP_I2C_MA_CTRL * st_ap_ctrl) = {
        &u4_s_GpI2cMaIRQEas_Opechk,                    /* GP_I2C_MA_SEQ_STA (0U)     */
        &u4_s_GpI2cMaIRQEas_Wtcchk,                    /* GP_I2C_MA_SEQ_WRI (1U)     */
        vdp_PTR_NA,                                    /* GP_I2C_MA_SEQ_WEN (2U)     */
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
        &vd_s_GpI2cMaIRQAct_ReAck,                     /* GP_I2C_MA_ACT_RE_ACK (5U)  */
        &vd_s_GpI2cMaIRQAct_ReNak,                     /* GP_I2C_MA_ACT_RE_NAK (6U)  */
        &vd_s_GpI2cMaIRQAct_ReAbt,                     /* GP_I2C_MA_ACT_RE_ABT (7U)  */
        &vd_s_GpI2cMaIRQAct_ReFin,                     /* GP_I2C_MA_ACT_RE_FIN (8U)  */
        &vd_s_GpI2cMaIRQAct_ToSta,                     /* GP_I2C_MA_ACT_TO_STA (9U)  */
        &vd_s_GpI2cMaIRQAct_ToReq,                     /* GP_I2C_MA_ACT_TO_REQ (10U) */
        &vd_s_GpI2cMaIRQAct_SqAbt                      /* GP_I2C_MA_ACT_SQ_ABT (11U) */
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
/*  U1      u1_g_GpI2cMaReqTRx(const ST_GP_I2C_MA_REQ * st_ap_REQ)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_GpI2cMaReqTRx(const ST_GP_I2C_MA_REQ * st_ap_REQ)
{
    const ST_GP_I2C_MA_CH *     st_tp_CH;
    ST_GP_I2C_MA_CTRL *         st_tp_ctrl;
    ST_GP_I2C_MA_REQ *          st_tp_que;

    U4                          u4_t_rwc_nex;                 /* rwc next      */
    U4                          u4_t_rwc_max;                 /* rwc max       */

    U4                          u4_t_sla;
    U4                          u4_t_nque;
    U4                          u4_t_req_nex;

    U2                          u2_t_req_las;

    U1                          u1_t_accpt;

    u1_t_accpt = (U1)FALSE;

    if((st_ap_REQ          != vdp_PTR_NA) &&
       (st_ap_REQ->u1p_pdu != vdp_PTR_NA)){

        u4_t_rwc_nex = st_ap_REQ->u4_cbf & (U4)GP_I2C_MA_CBF_BIT_RWC;
        u4_t_sla     = st_ap_REQ->u4_cbf >> GP_I2C_MA_CBF_LSB_SLA;
        if((u4_t_rwc_nex >= (U4)GP_I2C_MA_REQ_RWC_MIN ) &&
           (u4_t_sla     <  (U4)u1_g_GP_I2C_MA_NUM_SLA)){

            st_tp_CH      = st_gp_GP_I2C_MA_SLA[u4_t_sla].stp_CH;
            st_tp_ctrl    = st_gp_GP_I2C_MA_SLA[u4_t_sla].stp_CTRL;

            u4_t_nque     = (U4)st_tp_CH->u2_nque;
            u4_t_req_nex  = u4_s_GpI2cMaQueTryPush(st_tp_ctrl, u4_t_nque, (U4)GP_I2C_MA_QUE_TRY_YES);
            u4_t_rwc_nex += (U4)u2_gp_gpi2c_ma_rwc_by_sla[u4_t_sla];
            u4_t_rwc_max  = (U4)st_gp_GP_I2C_MA_SLA[u4_t_sla].u2_rwc_max;
            if((u4_t_req_nex <  u4_t_nque   ) &&
               (u4_t_rwc_nex <= u4_t_rwc_max)){

                u2_t_req_las                        = st_tp_ctrl->u2_req;
                st_tp_que                           = st_tp_CH->stp_QUE;

                vd_s_GpI2cMaQuePush(st_ap_REQ, &st_tp_que[u2_t_req_las]);

                /* ------------------------------------------------------------------------------------- */
                /* Attention :                                                                           */
                /* ------------------------------------------------------------------------------------- */
                /* st_tp_ctrl->u2_req shall be updated after st_ap_REQ is copied to st_tp_que[u2_t_req]. */
                /* Otherwise,  the data race issue could be caused.                                      */
                /* ------------------------------------------------------------------------------------- */
                st_tp_ctrl->u2_req                  = (U2)u4_t_req_nex;
                u2_gp_gpi2c_ma_rwc_by_sla[u4_t_sla] = (U2)u4_t_rwc_nex;

                vd_s_GpI2cMaSeqStart(st_tp_CH, st_tp_ctrl);

                u1_t_accpt = (U1)TRUE;
            }
        }
    }

    return(u1_t_accpt);
}
/*===================================================================================================================================*/
/*  U2      u2_g_GpI2cMaRwcRembySla(const U1 u1_a_SLA)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2      u2_g_GpI2cMaRwcRembySla(const U1 u1_a_SLA)
{
    const ST_GP_I2C_MA_CH *     st_tp_CH;
    ST_GP_I2C_MA_CTRL *         st_tp_ctrl;

    U4                          u4_t_nque;
    U4                          u4_t_req_nex;

    U2                          u2_t_rwc_rem;
    U2                          u2_t_rwc_las;
    U2                          u2_t_rwc_max;

    u2_t_rwc_rem = (U2)0U;
    if(u1_a_SLA < (U4)u1_g_GP_I2C_MA_NUM_SLA){

        st_tp_CH     = st_gp_GP_I2C_MA_SLA[u1_a_SLA].stp_CH;
        st_tp_ctrl   = st_gp_GP_I2C_MA_SLA[u1_a_SLA].stp_CTRL;

        u4_t_nque    = (U4)st_tp_CH->u2_nque;
        u4_t_req_nex = u4_s_GpI2cMaQueTryPush(st_tp_ctrl, u4_t_nque, (U4)GP_I2C_MA_QUE_TRY_YES);

        u2_t_rwc_las = u2_gp_gpi2c_ma_rwc_by_sla[u1_a_SLA];
        u2_t_rwc_max = st_gp_GP_I2C_MA_SLA[u1_a_SLA].u2_rwc_max;
        if((u4_t_req_nex < u4_t_nque   ) &&
           (u2_t_rwc_las < u2_t_rwc_max)){

            u2_t_rwc_rem = u2_t_rwc_max - u2_t_rwc_las;
        }
    }

    return(u2_t_rwc_rem);
}
/*===================================================================================================================================*/
/*  static U4      u4_s_GpI2cMaQueTryPush(const ST_GP_I2C_MA_CTRL * st_ap_CTRL, const U4 u4_a_NQUE, const U4 u4_a_OPT)               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_GpI2cMaQueTryPush(const ST_GP_I2C_MA_CTRL * st_ap_CTRL, const U4 u4_a_NQUE, const U4 u4_a_OPT)
{
    U4                          u4_t_nex;
    U4                          u4_t_req;
    U4                          u4_t_run;
    U4                          u4_t_ack;

    U2                          u2_t_seq;

    U1                          u1_t_ok;

    u4_t_nex = (U4)U4_MAX;

    u4_t_req = (U4)st_ap_CTRL->u2_req;
    u4_t_run = (U4)st_ap_CTRL->u2_run;
    u4_t_ack = (U4)st_ap_CTRL->u2_ack;
    u2_t_seq = st_ap_CTRL->u2_seq;
    if((u2_t_seq >  (U2)GP_I2C_MA_SEQ_REQ) ||
       (u4_t_req >= u4_a_NQUE            ) ||
       (u4_t_run >= u4_a_NQUE            ) ||
       (u4_t_ack >= u4_a_NQUE            )){

     /* u4_t_nex = (U4)U4_MAX; */
    }
    else if(u4_a_OPT == (U4)GP_I2C_MA_QUE_TRY_NO){

        if(u4_t_req >= u4_t_run){                          /* .u2_req       >= .u2_run       */
            u1_t_ok  = (U1)GP_I2C_MA_QUE_REQ_GE_RUN;
        }
        else{
            u1_t_ok  = (U1)0x00U;
        }
        if(u4_t_run >= u4_t_ack){                          /* .u2_run       >= .u2_ack       */
            u1_t_ok |= (U1)GP_I2C_MA_QUE_RUN_GE_ACK;
        }
        if(u4_t_ack > u4_t_req){                           /* .u2_ack       >  .u2_req       */
            u1_t_ok |= (U1)GP_I2C_MA_QUE_ACK_GT_REQ;
        }

        u1_t_ok = ((U1)GP_I2C_MA_QUE_CMPR_OK >> u1_t_ok) & (U1)0x01U;
        if(u1_t_ok != (U1)0U){
            u4_t_nex = u4_t_req;
        }
    }
    else{

        u4_t_req++;
        if(u4_t_req >= u4_a_NQUE){
            u4_t_req = (U4)0U;
        }

        if(u4_t_req > u4_t_run){                           /* (.u2_req + 1) >  .u2_run       */
            u1_t_ok  = (U1)GP_I2C_MA_QUE_REQ_GT_RUN;
        }
        else{
            u1_t_ok  = (U1)0x00U;
        }
        if(u4_t_run >= u4_t_ack){                          /* .u2_run       >= .u2_ack       */
            u1_t_ok |= (U1)GP_I2C_MA_QUE_RUN_GE_ACK;
        }
        if(u4_t_ack > u4_t_req){                           /* .u2_ack       >  (.u2_req + 1) */
            u1_t_ok |= (U1)GP_I2C_MA_QUE_ACK_GT_REQ;
        }

        u1_t_ok = ((U1)GP_I2C_MA_QUE_CMPR_OK >> u1_t_ok) & (U1)0x01U;
        if(u1_t_ok != (U1)0U){
            u4_t_nex = u4_t_req;
        }
    }

    return(u4_t_nex);
}
/*===================================================================================================================================*/
/*  static void    vd_s_GpI2cMaSeqReset(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U2 u2_a_SEQ)         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_GpI2cMaSeqReset(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U2 u2_a_SEQ)
{
    if(u2_a_SEQ > (U2)GP_I2C_MA_SEQ_REQ){
        vd_g_GpI2cMaIfDisCh(st_ap_CH);
    }
    else{
        vd_g_GpI2cMaIfEnaCh(st_ap_CH, (U1)TRUE);
    }

    st_ap_ctrl->u2_req = (U2)0U;
    st_ap_ctrl->u2_run = (U2)0U;
    st_ap_ctrl->u2_ack = (U2)0U;
    st_ap_ctrl->u2_frt = (U2)0U;
    st_ap_ctrl->u2_rwc = (U2)0U;
    st_ap_ctrl->u2_seq = u2_a_SEQ;
}
/*===================================================================================================================================*/
/*  static void    vd_s_GpI2cMaRwcReset(const ST_GP_I2C_MA_CH * st_ap_CH)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_GpI2cMaRwcReset(const ST_GP_I2C_MA_CH * st_ap_CH)
{
    U4                          u4_t_sla;

    for(u4_t_sla = (U4)0U; u4_t_sla < (U4)u1_g_GP_I2C_MA_NUM_SLA; u4_t_sla++){
        if(st_ap_CH == st_gp_GP_I2C_MA_SLA[u4_t_sla].stp_CH){
            u2_gp_gpi2c_ma_rwc_by_sla[u4_t_sla] = (U2)0U;
        }
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_GpI2cMaFraTout(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl)                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_GpI2cMaFraTout(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl)
{
    ST_GP_I2C_MA_REQ *          st_tp_que;

    U4                          u4_t_nque;
    U4                          u4_t_req;
    U4                          u4_t_run;

    U2                          u2_t_elpsd;
    U2                          u2_t_seq;

    u4_t_nque  = (U4)st_ap_CH->u2_nque;
    u4_t_req   = (U4)st_ap_ctrl->u2_req;
    u4_t_run   = (U4)st_ap_ctrl->u2_run;
    u2_t_seq   = st_ap_ctrl->u2_seq;
    u2_t_elpsd = u2_g_GpI2cMaIfFrt() - st_ap_ctrl->u2_frt;
    if((u4_t_run   <  u4_t_nque            ) &&
       (u4_t_req   <  u4_t_nque            ) &&
       (u2_t_seq   <  (U2)GP_I2C_MA_SEQ_REQ) &&
       (u2_t_elpsd >= st_ap_CH->u2_fr_tout )){

        vd_g_GpI2cMaIfResbyFrT(st_ap_CH);                         /* Reset by FrT : Frame Timeout */

        st_tp_que                   = st_ap_CH->stp_QUE;
        st_tp_que[u4_t_run].u4_cbf |= (U4)GP_I2C_MA_ERR_FR_TOUT;

        u4_t_run++;
        if(u4_t_run >= u4_t_nque){
            u4_t_run = (U4)0U;
        }
        st_ap_ctrl->u2_run = (U2)u4_t_run;

        if(u4_t_run != u4_t_req){

            st_ap_ctrl->u2_frt = u2_g_GpI2cMaIfFrt();

         /* ------------------------------------------------------------------------------------- */
         /* Attention :                                                                           */
         /* ------------------------------------------------------------------------------------- */
         /* st_tp_ctrl->u2_rwc is being initialized to 0 or 1 in vd_g_GpI2cMaIRQTRx               */
         /*                                                            ->vd_s_GpI2cMaIRQAct_ToWri */
         /*                                                            ->vd_s_GpI2cMaIRQAct_ToRea */
         /* ------------------------------------------------------------------------------------- */
         /* st_ap_ctrl->u2_rwc = (U2)0U; */
            st_ap_ctrl->u2_seq = (U2)GP_I2C_MA_SEQ_STA;

            vd_g_GpI2cMaIfIRQ_SeqEI(st_ap_CH);
            vd_g_GpI2cMaIfStaTRx(st_ap_CH);
        }
        else{
            st_ap_ctrl->u2_seq = (U2)GP_I2C_MA_SEQ_REQ;
        }
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_GpI2cMaTRxAck(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_GpI2cMaTRxAck(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl)
{
    ST_GP_I2C_MA_REQ *          st_tp_que;

    U4                          u4_t_cbf;
    U4                          u4_t_sla;
    U4                          u4_t_rwc;
    U4                          u4_t_max;

    U2                          u2_t_nque;
    U2                          u2_t_run;
    U2                          u2_t_ack;
    U2                          u2_t_seq;

    st_tp_que = st_ap_CH->stp_QUE;
    u2_t_nque = st_ap_CH->u2_nque;

    u2_t_ack  = st_ap_ctrl->u2_ack;
    u2_t_run  = st_ap_ctrl->u2_run;
    if((u2_t_ack < u2_t_nque) &&
       (u2_t_run < u2_t_nque)){

        while(u2_t_run != u2_t_ack){

            u4_t_cbf = st_tp_que[u2_t_ack].u4_cbf;
            u4_t_sla = u4_t_cbf >> GP_I2C_MA_CBF_LSB_SLA;
            if(u4_t_sla < (U4)u1_g_GP_I2C_MA_NUM_SLA){

                if(st_gp_GP_I2C_MA_SLA[u4_t_sla].fp_vd_ACK != vdp_PTR_NA){
                    (*st_gp_GP_I2C_MA_SLA[u4_t_sla].fp_vd_ACK)(&st_tp_que[u2_t_ack]);
                }

                u4_t_max = (U4)u2_gp_gpi2c_ma_rwc_by_sla[u4_t_sla];
                u4_t_rwc = u4_t_cbf & (U4)GP_I2C_MA_CBF_BIT_RWC;
                if(u4_t_max > u4_t_rwc){
                    u2_gp_gpi2c_ma_rwc_by_sla[u4_t_sla] = (U2)(u4_t_max - u4_t_rwc);
                }
                else{
                    u2_gp_gpi2c_ma_rwc_by_sla[u4_t_sla] = (U2)0U;
                }
            }

            u2_t_ack++;
            if(u2_t_ack >= u2_t_nque){
                u2_t_ack = (U2)0U;
            }
        }
        st_ap_ctrl->u2_ack = u2_t_ack;

        u2_t_seq = st_ap_ctrl->u2_seq;
        if(u2_t_seq >= (U2)GP_I2C_MA_SEQ_REQ){
            vd_s_GpI2cMaRwcReset(st_ap_CH);
        }
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_GpI2cMaQuePush(const ST_GP_I2C_MA_REQ * st_ap_REQ, ST_GP_I2C_MA_REQ * st_ap_que)                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_GpI2cMaQuePush(const ST_GP_I2C_MA_REQ * st_ap_REQ, ST_GP_I2C_MA_REQ * st_ap_que)
{
    st_ap_que->u1p_pdu = st_ap_REQ->u1p_pdu;
    st_ap_que->u4_cbf  = st_ap_REQ->u4_cbf;
}
/*===================================================================================================================================*/
/*  static U4      u4_s_GpI2cMaIRQEas_Opechk(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl)                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_GpI2cMaIRQEas_Opechk(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl)
{
    ST_GP_I2C_MA_REQ *          st_tp_que;
    U1 *                        u1_tp_pdu;

    U4                          u4_t_eas;
    U2                          u2_t_run;

    u2_t_run = st_ap_ctrl->u2_run;
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
/*  static U4      u4_s_GpI2cMaIRQEas_Wtcchk(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl)                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_GpI2cMaIRQEas_Wtcchk(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl)
{
    ST_GP_I2C_MA_REQ *          st_tp_que;
    U4                          u4_t_max;
    U4                          u4_t_rwc;
    U4                          u4_t_eas;

    U2                          u2_t_run;

    u2_t_run = st_ap_ctrl->u2_run;
    if(u2_t_run < st_ap_CH->u2_nque){

        st_tp_que = st_ap_CH->stp_QUE;
        st_tp_que = &st_tp_que[u2_t_run];
        u4_t_max  = (U4)st_tp_que->u4_cbf & (U4)GP_I2C_MA_CBF_BIT_RWC;
        u4_t_rwc  = (U4)st_ap_ctrl->u2_rwc + (U4)1U;
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
/*  static U4      u4_s_GpI2cMaIRQEas_Rrcchk(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl)                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_GpI2cMaIRQEas_Rrcchk(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl)
{
    ST_GP_I2C_MA_REQ *          st_tp_que;
    U4                          u4_t_max;
    U4                          u4_t_rwc;
    U4                          u4_t_eas;

    U2                          u2_t_run;

    u2_t_run = st_ap_ctrl->u2_run;
    if(u2_t_run < st_ap_CH->u2_nque){

        st_tp_que = st_ap_CH->stp_QUE;
        st_tp_que = &st_tp_que[u2_t_run];
        u4_t_max  = (U4)st_tp_que->u4_cbf & (U4)GP_I2C_MA_CBF_BIT_RWC;
        u4_t_rwc  = (U4)st_ap_ctrl->u2_rwc + (U4)GP_I2C_MA_RRC_TO_RLA;
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
/*  static U4      u4_s_GpI2cMaIRQEas_Rlachk(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl)                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_GpI2cMaIRQEas_Rlachk(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl)
{
    ST_GP_I2C_MA_REQ *          st_tp_que;
    U4                          u4_t_max;
    U4                          u4_t_rwc;
    U4                          u4_t_eas;

    U2                          u2_t_run;

    u2_t_run = st_ap_ctrl->u2_run;
    if(u2_t_run < st_ap_CH->u2_nque){

        st_tp_que = st_ap_CH->stp_QUE;
        st_tp_que = &st_tp_que[u2_t_run];
        u4_t_max  = (U4)st_tp_que->u4_cbf & (U4)GP_I2C_MA_CBF_BIT_RWC;
        u4_t_rwc  = (U4)st_ap_ctrl->u2_rwc + (U4)1U;
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
/*  static U4      u4_s_GpI2cMaIRQEas_Reqchk(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl)                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_GpI2cMaIRQEas_Reqchk(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl)
{
    U4                          u4_t_nque;
    U4                          u4_t_req;
    U4                          u4_t_run;
    U4                          u4_t_ack;
    U4                          u4_t_eas;

    U1                          u1_t_ok;

    u4_t_nque = (U4)st_ap_CH->u2_nque;
    u4_t_req  = (U4)st_ap_ctrl->u2_req;
    u4_t_run  = (U4)st_ap_ctrl->u2_run;
    u4_t_ack  = (U4)st_ap_ctrl->u2_ack;

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
    vd_g_GpI2cMaIfFinTRx(st_ap_CH);
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

    vd_g_GpI2cMaIfFinTRx(st_ap_CH);

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

    vd_g_GpI2cMaIfStaTRx(st_ap_CH);
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

    vd_g_GpI2cMaIfFinTRx(st_ap_CH);
    vd_g_GpI2cMaIfReaRx(st_ap_CH, &u1_t_dummy_rx);
}
/*===================================================================================================================================*/
/*  static inline void    vd_s_GpI2cMaSeqStart(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl)                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_GpI2cMaSeqStart(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl)
{
    U2                          u2_t_seq;

    u2_t_seq = st_ap_ctrl->u2_seq;
    if(u2_t_seq == (U2)GP_I2C_MA_SEQ_REQ){

        vd_g_GpI2cMaIfEnaCh(st_ap_CH, (U1)FALSE);

        st_ap_ctrl->u2_frt = u2_g_GpI2cMaIfFrt();
     /* ------------------------------------------------------------------------------------- */
     /* Attention :                                                                           */
     /* ------------------------------------------------------------------------------------- */
     /* st_ap_ctrl->u2_rwc is being initialized to 0 or 1 in vd_g_GpI2cMaIRQTRx               */
     /*                                                            ->vd_s_GpI2cMaIRQAct_ToWri */
     /*                                                            ->vd_s_GpI2cMaIRQAct_ToRea */
     /* ------------------------------------------------------------------------------------- */
     /* st_ap_ctrl->u2_rwc = (U2)0U; */
        st_ap_ctrl->u2_seq = (U2)GP_I2C_MA_SEQ_STA;

        vd_g_GpI2cMaIfIRQ_SeqEI(st_ap_CH);
        vd_g_GpI2cMaIfStaTRx(st_ap_CH);
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
/*  1.1.0    10/10/2024  TN       New.                                                                                               */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
