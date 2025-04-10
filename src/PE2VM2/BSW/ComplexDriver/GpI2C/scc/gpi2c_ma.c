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
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1      u1_s_GpI2cMaSeqReschk(const ST_GP_I2C_MA_CTRL * st_ap_CTRL, const U4 u4_a_NQUE);
static void    vd_s_GpI2cMaSeqReset(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl, const U2 u2_a_SEQ);
static void    vd_s_GpI2cMaRwcReset(const ST_GP_I2C_MA_CH * st_ap_CH);
static void    vd_s_GpI2cMaFraTout(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl);
static void    vd_s_GpI2cMaTRxAck(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl);

static U4      u4_s_GpI2cMaQueTryPush(const ST_GP_I2C_MA_CTRL * st_ap_CTRL, const U4 u4_a_NQUE, const U4 u4_a_NREQ);
static void    vd_s_GpI2cMaQuePush(const ST_GP_I2C_MA_REQ * st_ap_REQ, const ST_GP_I2C_MA_CH * st_ap_CH,
                                   const ST_GP_I2C_MA_CTRL * st_ap_CTRL, const U4 u4_a_NEX);
static U4      u4_s_GpI2cMaRwcTotal(const ST_GP_I2C_MA_REQ * const st_ap_REQ, const U4 u4_a_NREQ, const U4 u4_a_SLA);
static void    vd_s_GpI2cMaSeqStart(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl);

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
    U2                          u2_t_seq;
    U1                          u1_t_res;
    U1                          u1_t_act;

    for(u4_t_ch = (U4)0U; u4_t_ch < (U4)u1_g_GP_I2C_MA_NUM_CH; u4_t_ch++){

        st_tp_CH   = &st_gp_GP_I2C_MA_CH[u4_t_ch];
        st_tp_ctrl = &st_gp_gpi2c_ma_ctrl[u4_t_ch];

        u1_t_res   = u1_s_GpI2cMaSeqReschk(st_tp_ctrl, (U4)st_tp_CH->u2_nque);
        u1_t_act   = u1_g_GpI2cMaCfgSlaActvtd((U1)u4_t_ch);
        if(u1_t_act != (U1)TRUE){

            u2_t_seq = st_tp_ctrl->u2_seq;
            if(u2_t_seq < (U2)GP_I2C_MA_SEQ_INA){

                vd_s_GpI2cMaSeqReset(st_tp_CH, st_tp_ctrl, (U2)GP_I2C_MA_SEQ_INA);
                vd_s_GpI2cMaRwcReset(st_tp_CH);
            }
        }
        else if(u1_t_res != (U1)FALSE){

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
/*  U1      u1_g_GpI2cMaReqTRx(const ST_GP_I2C_MA_REQ * const st_ap_REQ, const U2 u2_a_NREQ)                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_GpI2cMaReqTRx(const ST_GP_I2C_MA_REQ * const st_ap_REQ, const U2 u2_a_NREQ)
{
    const ST_GP_I2C_MA_CH *     st_tp_CH;
    ST_GP_I2C_MA_CTRL *         st_tp_ctrl;

    U4                          u4_t_cbf;
    U4                          u4_t_rwc;
    U4                          u4_t_sla;
    U4                          u4_t_nque;

    U4                          u4_t_req_nex;
    U4                          u4_t_rwc_nex;                 /* rwc next      */
    U4                          u4_t_rwc_max;                 /* rwc max       */

    U1                          u1_t_accpt;

    u1_t_accpt = (U1)FALSE;

    if((u2_a_NREQ          >  (U2)0U    ) &&
       (st_ap_REQ          != vdp_PTR_NA) &&
       (st_ap_REQ->u1p_pdu != vdp_PTR_NA)){

        u4_t_cbf = st_ap_REQ->u4_cbf;
        u4_t_rwc = u4_t_cbf & (U4)GP_I2C_MA_CBF_BIT_RWC;
        u4_t_sla = u4_t_cbf >> GP_I2C_MA_CBF_LSB_SLA;
        if((u4_t_rwc >= (U4)GP_I2C_MA_REQ_RWC_MIN ) &&
           (u4_t_sla <  (U4)u1_g_GP_I2C_MA_NUM_SLA)){

            st_tp_CH     = st_gp_GP_I2C_MA_SLA[u4_t_sla].stp_CH;
            u4_t_nque    = (U4)st_tp_CH->u2_nque;

            st_tp_ctrl   = st_gp_GP_I2C_MA_SLA[u4_t_sla].stp_CTRL;
            u4_t_req_nex = u4_s_GpI2cMaQueTryPush(st_tp_ctrl, u4_t_nque, (U4)u2_a_NREQ);
            if(u4_t_req_nex < u4_t_nque){

                u4_t_rwc_nex = (U4)u2_gp_gpi2c_ma_rwc_by_sla[u4_t_sla] + u4_t_rwc;
                if(u2_a_NREQ > (U2)1U){
                    u4_t_rwc_nex += u4_s_GpI2cMaRwcTotal(st_ap_REQ, (U4)u2_a_NREQ, u4_t_sla);
                }

                u4_t_rwc_max = (U4)st_gp_GP_I2C_MA_SLA[u4_t_sla].u2_rwc_max;
                if(u4_t_rwc_nex <= u4_t_rwc_max){

                    vd_s_GpI2cMaQuePush(st_ap_REQ, st_tp_CH, st_tp_ctrl, u4_t_req_nex);

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
    }

    return(u1_t_accpt);
}
/*===================================================================================================================================*/
/*  U2      u2_g_GpI2cMaRwcRembySla(const U1 u1_a_SLA, const U2 u2_a_NREQ)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2      u2_g_GpI2cMaRwcRembySla(const U1 u1_a_SLA, const U2 u2_a_NREQ)
{
    const ST_GP_I2C_MA_CH *     st_tp_CH;
    ST_GP_I2C_MA_CTRL *         st_tp_ctrl;

    U4                          u4_t_nque;
    U4                          u4_t_req_nex;

    U2                          u2_t_rwc_rem;
    U2                          u2_t_rwc_las;
    U2                          u2_t_rwc_max;

    u2_t_rwc_rem = (U2)0U;
    if((u1_a_SLA  < (U4)u1_g_GP_I2C_MA_NUM_SLA) &&
       (u2_a_NREQ > (U2)0U                    )){

        st_tp_CH     = st_gp_GP_I2C_MA_SLA[u1_a_SLA].stp_CH;
        st_tp_ctrl   = st_gp_GP_I2C_MA_SLA[u1_a_SLA].stp_CTRL;

        u4_t_nque    = (U4)st_tp_CH->u2_nque;
        u4_t_req_nex = u4_s_GpI2cMaQueTryPush(st_tp_ctrl, u4_t_nque, (U4)u2_a_NREQ);
        if(u4_t_req_nex < u4_t_nque){

            u2_t_rwc_las = u2_gp_gpi2c_ma_rwc_by_sla[u1_a_SLA];
            u2_t_rwc_max = st_gp_GP_I2C_MA_SLA[u1_a_SLA].u2_rwc_max;
            if(u2_t_rwc_las < u2_t_rwc_max){
                u2_t_rwc_rem = u2_t_rwc_max - u2_t_rwc_las;
            }
        }
    }

    return(u2_t_rwc_rem);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_GpI2cMaSeqReschk(const ST_GP_I2C_MA_CTRL * st_ap_CTRL, const U4 u4_a_NQUE)                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_GpI2cMaSeqReschk(const ST_GP_I2C_MA_CTRL * st_ap_CTRL, const U4 u4_a_NQUE)
{
    U4                          u4_t_req;
    U4                          u4_t_run;
    U4                          u4_t_ack;

    U2                          u2_t_seq;

    U1                          u1_t_res;

    u4_t_req = (U4)st_ap_CTRL->u2_req;
    u4_t_run = (U4)st_ap_CTRL->u2_run;
    u4_t_ack = (U4)st_ap_CTRL->u2_ack;
    u2_t_seq = st_ap_CTRL->u2_seq;
    if((u2_t_seq >  (U2)GP_I2C_MA_SEQ_REQ) ||
       (u4_t_req >= u4_a_NQUE            ) ||
       (u4_t_run >= u4_a_NQUE            ) ||
       (u4_t_ack >= u4_a_NQUE            )){

        u1_t_res = (U1)TRUE;
    }
    else{

        if(u4_t_req >= u4_t_run){                          /* .u2_req       >= .u2_run       */
            u1_t_res  = (U1)GP_I2C_MA_QUE_REQ_GE_RUN;
        }
        else{
            u1_t_res  = (U1)0x00U;
        }
        if(u4_t_run >= u4_t_ack){                          /* .u2_run       >= .u2_ack       */
            u1_t_res |= (U1)GP_I2C_MA_QUE_RUN_GE_ACK;
        }
        if(u4_t_ack > u4_t_req){                           /* .u2_ack       >  .u2_req       */
            u1_t_res |= (U1)GP_I2C_MA_QUE_ACK_GT_REQ;
        }

        u1_t_res = (((U1)U1_MAX ^ (U1)GP_I2C_MA_QUE_CMPR_OK) >> u1_t_res) & (U1)TRUE;
    }

    return(u1_t_res);
}
/*===================================================================================================================================*/
/*  static U4      u4_s_GpI2cMaQueTryPush(const ST_GP_I2C_MA_CTRL * st_ap_CTRL, const U4 u4_a_NQUE, const U4 u4_a_NREQ)              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_GpI2cMaQueTryPush(const ST_GP_I2C_MA_CTRL * st_ap_CTRL, const U4 u4_a_NQUE, const U4 u4_a_NREQ)
{
    U4                          u4_t_nex;
    U4                          u4_t_req;
    U4                          u4_t_run;
    U4                          u4_t_ack;
    U4                          u4_t_max;

    U2                          u2_t_seq;

    U1                          u1_t_ok;

    u4_t_nex = (U4)U4_MAX;

    u4_t_req = (U4)st_ap_CTRL->u2_req;
    u4_t_run = (U4)st_ap_CTRL->u2_run;
    u4_t_ack = (U4)st_ap_CTRL->u2_ack;
    u2_t_seq = st_ap_CTRL->u2_seq;
    if((u4_a_NREQ >= u4_a_NQUE            ) ||
       (u2_t_seq  >  (U2)GP_I2C_MA_SEQ_REQ) ||
       (u4_t_req  >= u4_a_NQUE            ) ||
       (u4_t_run  >= u4_a_NQUE            ) ||
       (u4_t_ack  >= u4_a_NQUE            )){

     /* u4_t_nex = (U4)U4_MAX; */
    }
    else{

        u4_t_max = u4_t_req + (U4)1U;
        if(u4_t_ack > u4_t_req){
            u4_t_max = u4_t_ack - u4_t_max;
        }
        else{
            u4_t_max = (u4_a_NQUE - u4_t_max) + u4_t_ack;
        }

        if(u4_a_NREQ <= u4_t_max){

            u4_t_req += u4_a_NREQ;
            if(u4_t_req >= u4_a_NQUE){
                u4_t_req -= u4_a_NQUE;
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
            vd_g_GpI2cMaIfTRxStart(st_ap_CH);
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
/*  static void    vd_s_GpI2cMaQuePush(const ST_GP_I2C_MA_REQ * st_ap_REQ, const ST_GP_I2C_MA_CH * st_ap_CH,                         */
/*                                     const ST_GP_I2C_MA_CTRL * st_ap_CTRL, const U4 u4_a_NEX)                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_GpI2cMaQuePush(const ST_GP_I2C_MA_REQ * st_ap_REQ, const ST_GP_I2C_MA_CH * st_ap_CH,
                                   const ST_GP_I2C_MA_CTRL * st_ap_CTRL, const U4 u4_a_NEX)
{
    ST_GP_I2C_MA_REQ *          st_tp_que;
    ST_GP_I2C_MA_REQ *          st_tp_dst;

    U4                          u4_t_req;
    U4                          u4_t_nque;

    st_tp_que = st_ap_CH->stp_QUE;
    u4_t_nque = (U4)st_ap_CH->u2_nque;
    u4_t_req  = st_ap_CTRL->u2_req;
    do{

        st_tp_dst = &st_tp_que[u4_t_req];

        st_tp_dst->u1p_pdu = st_ap_REQ->u1p_pdu;
        st_tp_dst->u4_cbf  = st_ap_REQ->u4_cbf;

        st_ap_REQ++;
        u4_t_req++;
        if(u4_t_req >= u4_t_nque){
            u4_t_req = (U4)0U;
        }
    }
    while(u4_t_req != u4_a_NEX);
}
/*===================================================================================================================================*/
/*  static U4      u4_s_GpI2cMaRwcTotal(const ST_GP_I2C_MA_REQ * const st_ap_REQ, const U4 u4_a_NREQ, const U4 u4_a_SLA)             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_GpI2cMaRwcTotal(const ST_GP_I2C_MA_REQ * const st_ap_REQ, const U4 u4_a_NREQ, const U4 u4_a_SLA)
{
    U1 *                        u1_tp_pdu;

    U4                          u4_t_total;
    U4                          u4_t_lpcnt;
    U4                          u4_t_cbf;
    U4                          u4_t_rwc;
    U4                          u4_t_sla;

    u4_t_total = (U4)0U;
    for(u4_t_lpcnt = (U4)1U; u4_t_lpcnt < u4_a_NREQ; u4_t_lpcnt++){

        u1_tp_pdu = st_ap_REQ[u4_t_lpcnt].u1p_pdu;
        u4_t_cbf  = st_ap_REQ[u4_t_lpcnt].u4_cbf;

        u4_t_rwc  = u4_t_cbf & (U4)GP_I2C_MA_CBF_BIT_RWC;
        u4_t_sla  = u4_t_cbf >> GP_I2C_MA_CBF_LSB_SLA;
        if((u1_tp_pdu != vdp_PTR_NA               ) &&
           (u4_t_rwc  >= (U4)GP_I2C_MA_REQ_RWC_MIN) &&
           (u4_t_sla  == u4_a_SLA                 )){

            u4_t_total += u4_t_rwc;
        }
        else{
            u4_t_total  = (U4)GP_I2C_MA_CBF_BIT_RWC * (U4)U2_MAX;
            break;
        }
    }

    return(u4_t_total);
}
/*===================================================================================================================================*/
/*  static void    vd_s_GpI2cMaSeqStart(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_GpI2cMaSeqStart(const ST_GP_I2C_MA_CH * st_ap_CH, ST_GP_I2C_MA_CTRL * st_ap_ctrl)
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
        vd_g_GpI2cMaIfTRxStart(st_ap_CH);
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
