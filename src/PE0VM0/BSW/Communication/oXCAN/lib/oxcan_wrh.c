/* 2.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  OEM eXtention of CAN : Network Wake-up Request Handler                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_WRH_C_MAJOR                        (2U)
#define OXCAN_WRH_C_MINOR                        (0U)
#define OXCAN_WRH_C_PATCH                        (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxcan_wrh_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((OXCAN_WRH_C_MAJOR != OXCAN_LIB_WRH_H_MAJOR) || \
     (OXCAN_WRH_C_MINOR != OXCAN_LIB_WRH_H_MINOR) || \
     (OXCAN_WRH_C_PATCH != OXCAN_LIB_WRH_H_PATCH))
#error "oxcan_wrh.c and oxcan_lib.h : source and header files are inconsistent!"
#endif

#if ((OXCAN_WRH_C_MAJOR != OXCAN_WRH_CFG_H_MAJOR) || \
     (OXCAN_WRH_C_MINOR != OXCAN_WRH_CFG_H_MINOR) || \
     (OXCAN_WRH_C_PATCH != OXCAN_WRH_CFG_H_PATCH))
#error "oxcan_wrh.c and oxcan_wrh_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_WRQH_NUM_CTRL                      (3U)
#define OXCAN_WRQH_CTRL_STA                      (0U)           /* network communication is being started and wait for net awaken */
#define OXCAN_WRQH_CTRL_RUN                      (1U)           /* network communication is in run                                */
#define OXCAN_WRQH_CTRL_WFR                      (2U)           /* wait for wake-up request                                       */

#define OXCAN_WRQH_EAS_REQ_WK                    (0x03U)
#define OXCAN_WRQH_EAS_REQ_SS                    (0x01U)        /* Wakeup Request : Solid State    */
#define OXCAN_WRQH_EAS_REQ_ET                    (0x02U)        /* Wakeup Request : Event Triggerd */
#define OXCAN_WRQH_EAS_TIMEOUT                   (0x04U)
#define OXCAN_WRQH_EAS_NET_RUN                   (0x08U)

#define OXCAN_WRQH_ACT_TO_STA                    (0U)
#define OXCAN_WRQH_ACT_TO_RUN                    (1U)
#define OXCAN_WRQH_ACT_STA                       (2U)
#define OXCAN_WRQH_ACT_RUN                       (3U)
#define OXCAN_WRQH_ACT_TO_WFR                    (4U)

#define OXCAN_WRQH_ACT_LSB_CTRL                  (4U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4                       u4_s_oxcan_wrh_wrq_act;
static U2                       u2_s_oxcan_wrh_vom_tocnt;
static U2                       u2_s_oxcan_wrh_pwr_tocnt;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_oXCANWrhReqbyVom(const U4 u4_a_SYS_ACT);

static U4      u4_s_oXCANWrhReqbyRqh(const U4 u4_a_SYS_ACT, U4 * u4_ap_wrq_act);

static U1      u1_s_oXCANWrhRqhTout(const ST_OXCAN_WRH_RQH * st_ap_RQH, const U2 u2_a_ELPSD, const U2 u2_a_CTRL);
static U4      u4_s_oXCANWrhRqhAct(const U2 u2_a_ACT, ST_OXCAN_WRH_HCH * st_ap_hch);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_oXCANWrhInit(const U1 u1_a_RST_INIT)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANWrhInit(const U1 u1_a_RST_INIT)
{
    U4                 u4_t_hch;

    u4_s_oxcan_wrh_wrq_act   = (U4)0U;
    u2_s_oxcan_wrh_vom_tocnt = (U2)U2_MAX;

    for(u4_t_hch = (U4)0U; u4_t_hch < (U4)u1_g_OXCAN_WRH_NUM_RQH; u4_t_hch++){
        st_gp_oxcan_wrh_hch[u4_t_hch].u4_req   = (U4)0U;
        st_gp_oxcan_wrh_hch[u4_t_hch].u2_elpsd = (U2)U2_MAX;
        st_gp_oxcan_wrh_hch[u4_t_hch].u2_ctrl  = (U2)OXCAN_WRQH_CTRL_WFR;
    }

    if(u1_a_RST_INIT == (U1)TRUE){
        u2_s_oxcan_wrh_pwr_tocnt = (U2)0U;
    }else{
        u2_s_oxcan_wrh_pwr_tocnt = (U2)U2_MAX;    
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANWrhMainTask(const U4 u4_a_SYS_ACT)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANWrhMainTask(const U4 u4_a_SYS_ACT)
{
    U4                 u4_t_req_by_net;
    U4                 u4_t_req_by_vom;
    U4                 u4_t_wrqbit;

    u4_t_req_by_net = u4_g_oXCANWrhCfgReqbyDcm();
    if(u4_t_req_by_net != (U4)0U){
        u4_t_wrqbit  = (U4)OXCAN_WRH_WRQBIT_DCM;
    }
    else{
        u4_t_wrqbit  = (U4)0U;
    }

    u4_t_req_by_vom = u4_s_oXCANWrhReqbyVom(u4_a_SYS_ACT);
    if(u4_t_req_by_vom != (U4)0){
        u4_t_wrqbit |= (U4)OXCAN_WRH_WRQBIT_VOM;
    }
    u4_t_req_by_net |= u4_t_req_by_vom;
    u4_t_req_by_net |= u4_s_oXCANWrhReqbyRqh(u4_a_SYS_ACT, &u4_t_wrqbit);

    if(u2_s_oxcan_wrh_pwr_tocnt < u2_g_OXCAN_WRH_PWR_TOUT){
        u4_t_req_by_net |= u4_g_OXCAN_WRH_REQ_BY_PWR;
        u4_t_wrqbit |= (U4)OXCAN_WRH_WRQBIT_PWR;
        u2_s_oxcan_wrh_pwr_tocnt++;
    }else{
        u2_s_oxcan_wrh_pwr_tocnt = (U2)U2_MAX;
    }

    u4_s_oxcan_wrh_wrq_act = u4_t_wrqbit;

    vd_g_oXCANWrhCfgReqbyNet(u4_t_req_by_net);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXCANWrhShtdwnOk(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXCANWrhShtdwnOk(void)
{
    U1                 u1_t_ok;

    if(u4_s_oxcan_wrh_wrq_act == (U4)0U){
        u1_t_ok = (U1)TRUE;
    }
    else{
        u1_t_ok = (U1)FALSE;
    }

    return(u1_t_ok);
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANWrhReqHch(const U1 u1_a_HCH, const U4 u4_a_REQ)                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANWrhReqHch(const U1 u1_a_HCH, const U4 u4_a_REQ)
{
    if(u1_a_HCH < u1_g_OXCAN_WRH_NUM_RQH){
        st_gp_oxcan_wrh_hch[u1_a_HCH].u4_req = u4_a_REQ | u4_g_OXCAN_WRH_LOG_REQ_EX;
    }
}
/*===================================================================================================================================*/
/*  U4      u4_g_oXCANWrhWRQstd(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4      u4_g_oXCANWrhWRQstd(void)
{
    return(u4_s_oxcan_wrh_wrq_act);
}
/*===================================================================================================================================*/
/*  static U4      u4_s_oXCANWrhReqbyVom(const U4 u4_a_SYS_ACT)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_oXCANWrhReqbyVom(const U4 u4_a_SYS_ACT)
{
    U4                 u4_t_tor;
    U4                 u4_t_req;

    u4_t_tor = u4_a_SYS_ACT & u4_g_OXCAN_WRH_TOR_BY_VOM;
    if(u4_t_tor != (U4)0U){
        u2_s_oxcan_wrh_vom_tocnt = (U2)0U;
    }
    else if(u2_s_oxcan_wrh_vom_tocnt >= (U2)U2_MAX){
     /* u2_s_oxcan_wrh_vom_tocnt = (U2)U2_MAX; */
    }
    else{
        u2_s_oxcan_wrh_vom_tocnt++;
    }

    if(u2_s_oxcan_wrh_vom_tocnt >= u2_g_OXCAN_WRH_VOM_TOUT){
        u4_t_req = (U4)0U;
    }
    else{
        u4_t_req = u4_g_OXCAN_WRH_REQ_BY_VOM;
    }

    return(u4_t_req);
}
/*===================================================================================================================================*/
/*  static U4      u4_s_oXCANWrhReqbyRqh(const U4 u4_a_SYS_ACT, U4 * u4_ap_wrq_act)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         AppAwake Event Pattern                                                                                           */
/*===================================================================================================================================*/
static U4      u4_s_oXCANWrhReqbyRqh(const U4 u4_a_SYS_ACT, U4 * u4_ap_wrq_act)
{
    static const U1             u1_sp_OXCAN_WRQH_ACT[] = {
        /* #define OXCAN_WRQH_CTRL_STA (0U) */
        (U1)OXCAN_WRQH_ACT_TO_WFR, (U1)OXCAN_WRQH_ACT_STA,    (U1)OXCAN_WRQH_ACT_TO_WFR, (U1)OXCAN_WRQH_ACT_TO_STA,
        (U1)OXCAN_WRQH_ACT_TO_WFR, (U1)OXCAN_WRQH_ACT_TO_WFR, (U1)OXCAN_WRQH_ACT_TO_WFR, (U1)OXCAN_WRQH_ACT_TO_STA,
        (U1)OXCAN_WRQH_ACT_TO_WFR, (U1)OXCAN_WRQH_ACT_TO_RUN, (U1)OXCAN_WRQH_ACT_TO_WFR, (U1)OXCAN_WRQH_ACT_TO_RUN,
        (U1)OXCAN_WRQH_ACT_TO_WFR, (U1)OXCAN_WRQH_ACT_TO_RUN, (U1)OXCAN_WRQH_ACT_TO_WFR, (U1)OXCAN_WRQH_ACT_TO_RUN,

        /* #define OXCAN_WRQH_CTRL_RUN (1U) */
        (U1)OXCAN_WRQH_ACT_TO_WFR, (U1)OXCAN_WRQH_ACT_TO_WFR, (U1)OXCAN_WRQH_ACT_TO_WFR, (U1)OXCAN_WRQH_ACT_TO_STA,
        (U1)OXCAN_WRQH_ACT_TO_WFR, (U1)OXCAN_WRQH_ACT_TO_WFR, (U1)OXCAN_WRQH_ACT_TO_WFR, (U1)OXCAN_WRQH_ACT_TO_STA,
        (U1)OXCAN_WRQH_ACT_TO_WFR, (U1)OXCAN_WRQH_ACT_RUN,    (U1)OXCAN_WRQH_ACT_TO_WFR, (U1)OXCAN_WRQH_ACT_TO_RUN,
        (U1)OXCAN_WRQH_ACT_TO_WFR, (U1)OXCAN_WRQH_ACT_TO_WFR, (U1)OXCAN_WRQH_ACT_TO_WFR, (U1)OXCAN_WRQH_ACT_TO_RUN,

        /* #define OXCAN_WRQH_CTRL_WFR (2U) */
        (U1)OXCAN_WRQH_ACT_TO_WFR, (U1)OXCAN_WRQH_ACT_TO_WFR, (U1)OXCAN_WRQH_ACT_TO_WFR, (U1)OXCAN_WRQH_ACT_TO_STA,
        (U1)OXCAN_WRQH_ACT_TO_WFR, (U1)OXCAN_WRQH_ACT_TO_WFR, (U1)OXCAN_WRQH_ACT_TO_WFR, (U1)OXCAN_WRQH_ACT_TO_STA,
        (U1)OXCAN_WRQH_ACT_TO_WFR, (U1)OXCAN_WRQH_ACT_TO_WFR, (U1)OXCAN_WRQH_ACT_TO_WFR, (U1)OXCAN_WRQH_ACT_TO_RUN,
        (U1)OXCAN_WRQH_ACT_TO_WFR, (U1)OXCAN_WRQH_ACT_TO_WFR, (U1)OXCAN_WRQH_ACT_TO_WFR, (U1)OXCAN_WRQH_ACT_TO_RUN
    };

    const ST_OXCAN_WRH_RQH *    st_tp_RQH;
    ST_OXCAN_WRH_HCH *          st_tp_hch;

    U4                          u4_t_gli;

    U4                          u4_t_req_by_net;
    U4                          u4_t_wrqbit;
    U4                          u4_t_hch;
    U4                          u4_t_req;
    U4                          u4_t_net;
    U4                          u4_t_run;
    U4                          u4_t_req_by_hch;

    U2                          u2_t_elpsd;
    U2                          u2_t_ctrl;
    U2                          u2_t_act;

    U1                          u1_t_eas;

    u4_t_req_by_net = (U4)0U;
    u4_t_wrqbit     = (U4)0U;
    for(u4_t_hch = (U4)0U; u4_t_hch < (U4)u1_g_OXCAN_WRH_NUM_RQH; u4_t_hch++){

        st_tp_RQH = &st_gp_OXCAN_WRH_RQH[u4_t_hch];
        st_tp_hch = &st_gp_oxcan_wrh_hch[u4_t_hch];
        u4_t_net  = st_tp_RQH->u4_sys_net;

        u2_t_ctrl = st_tp_hch->u2_ctrl;
        if(u2_t_ctrl >= (U2)OXCAN_WRQH_NUM_CTRL){

            u2_t_act = (U2)OXCAN_WRQH_ACT_TO_WFR;
        }
        else{

            /* ------------------------------------------------------------------------------------- */
            u4_t_gli = u4_g_oXCANWrh_IRQ_DI();

            u4_t_req          = st_tp_hch->u4_req;
            st_tp_hch->u4_req = u4_t_req & u4_t_net;

            vd_g_oXCANWrh_IRQ_EI(u4_t_gli);
            /* ------------------------------------------------------------------------------------- */

            u4_t_net  = u4_t_req & u4_t_net;
            u4_t_req &= u4_g_OXCAN_WRH_LOG_REQ_EX;
            if(u4_t_net == (U4)0U){
                u1_t_eas = (U1)0U;
            }
            else if(u4_t_req != (U4)0U){
                u1_t_eas = (U1)OXCAN_WRQH_EAS_REQ_WK;
            }
            else{
                u1_t_eas = (U1)OXCAN_WRQH_EAS_REQ_SS;
            }

            u2_t_elpsd = st_tp_hch->u2_elpsd;
            if(u2_t_elpsd < (U2)U2_MAX){
                u2_t_elpsd++;
                st_tp_hch->u2_elpsd = u2_t_elpsd;
            }

            u1_t_eas |= u1_s_oXCANWrhRqhTout(st_tp_RQH, u2_t_elpsd, u2_t_ctrl);
            u4_t_run  = u4_a_SYS_ACT & u4_t_net;
            if(u4_t_run == u4_t_net){
                u1_t_eas |= (U1)OXCAN_WRQH_EAS_NET_RUN;
            }

            u2_t_act = (u2_t_ctrl << OXCAN_WRQH_ACT_LSB_CTRL) + (U2)u1_t_eas;
            u2_t_act = (U2)u1_sp_OXCAN_WRQH_ACT[u2_t_act];
        }
        u4_t_req_by_hch  = u4_s_oXCANWrhRqhAct(u2_t_act, st_tp_hch);
        u4_t_req_by_net |= (u4_t_req_by_hch & u4_t_net);
        u4_t_wrqbit     |= (u4_t_req_by_hch & ((U4)0x00000001U << u4_t_hch));
    }

    (*u4_ap_wrq_act) |= u4_t_wrqbit;

    return(u4_t_req_by_net);
}
/*===================================================================================================================================*/
/*  U1      u1_s_oXCANWrhRqhTout(const ST_OXCAN_WRH_RQH * st_ap_RQH, const U2 u2_a_ELPSD, const U2 u2_a_CTRL)                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_oXCANWrhRqhTout(const ST_OXCAN_WRH_RQH * st_ap_RQH, const U2 u2_a_ELPSD, const U2 u2_a_CTRL)
{
    U2                          u2_t_tout;
    U1                          u1_t_eas;

    if(u2_a_CTRL == (U2)OXCAN_WRQH_CTRL_STA){
        u2_t_tout = st_ap_RQH->u2_tout_sta;
    }
    else if(u2_a_CTRL == (U2)OXCAN_WRQH_CTRL_RUN){
        u2_t_tout = st_ap_RQH->u2_tout_run;
    }
    else{
        u2_t_tout = (U2)0U;
    }

    if(u2_a_ELPSD >= u2_t_tout){
        u1_t_eas = (U1)OXCAN_WRQH_EAS_TIMEOUT;
    }
    else{
        u1_t_eas = (U1)0U;
    }

    return(u1_t_eas);
}
/*===================================================================================================================================*/
/*  static U4      u4_s_oXCANWrhRqhAct(const U2 u2_a_ACT, ST_OXCAN_WRH_HCH * st_ap_hch)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_oXCANWrhRqhAct(const U2 u2_a_ACT, ST_OXCAN_WRH_HCH * st_ap_hch)
{
    U4                 u4_t_req;

    switch(u2_a_ACT){
        case OXCAN_WRQH_ACT_TO_STA:
            st_ap_hch->u2_elpsd = (U2)0U;
            st_ap_hch->u2_ctrl  = (U2)OXCAN_WRQH_CTRL_STA;
            u4_t_req            = (U4)U4_MAX;
            break;
        case OXCAN_WRQH_ACT_TO_RUN:
            st_ap_hch->u2_elpsd = (U2)1U;
            st_ap_hch->u2_ctrl  = (U2)OXCAN_WRQH_CTRL_RUN;
            u4_t_req            = (U4)U4_MAX;
            break;
        case OXCAN_WRQH_ACT_STA:
         /* st_ap_hch->u2_ctrl  = (U2)OXCAN_WRQH_CTRL_STA; */
            u4_t_req            = (U4)U4_MAX;
            break;
        case OXCAN_WRQH_ACT_RUN:
         /* st_ap_hch->u2_ctrl  = (U2)OXCAN_WRQH_CTRL_RUN; */
            u4_t_req            = (U4)U4_MAX;
            break;
        case OXCAN_WRQH_ACT_TO_WFR:
        default:
            st_ap_hch->u2_elpsd = (U2)U2_MAX;
            st_ap_hch->u2_ctrl  = (U2)OXCAN_WRQH_CTRL_WFR;
            u4_t_req            = (U4)0U;
            break;
    }

    return(u4_t_req);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  2.0.0     2/28/2025  TN       oxcan_nmwk v1.0.2 -> oxcan_wrh v2.0.0.                                                             */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, DENSO                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/


