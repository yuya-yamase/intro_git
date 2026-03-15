/* 2.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  OEM eXtention of CAN : Rx Detection                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_RXD_C_MAJOR                        (2U)
#define OXCAN_RXD_C_MINOR                        (0U)
#define OXCAN_RXD_C_PATCH                        (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxcan_rxd_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((OXCAN_RXD_C_MAJOR != OXCAN_LIB_RXD_H_MAJOR) || \
     (OXCAN_RXD_C_MINOR != OXCAN_LIB_RXD_H_MINOR) || \
     (OXCAN_RXD_C_PATCH != OXCAN_LIB_RXD_H_PATCH))
#error "oxcan_rxd.c and oxcan_lib.h : source and header files are inconsistent!"
#endif

#if ((OXCAN_RXD_C_MAJOR != OXCAN_RXD_CFG_H_MAJOR) || \
     (OXCAN_RXD_C_MINOR != OXCAN_RXD_CFG_H_MINOR) || \
     (OXCAN_RXD_C_PATCH != OXCAN_RXD_CFG_H_PATCH))
#error "oxcan_rxd.c and oxcan_rxd_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (BSW_BSWM_CS_CFG_MSGDELIVER != BSW_BSWM_CS_MSGDELIVER_MIDDLE) 
#error "oxcan.c : BSW_BSWM_CS_CFG_MSGDELIVER shall be configured to BSW_BSWM_CS_MSGDELIVER_MIDDLE" 
#endif /* #if (BSW_BSWM_CS_CFG_MSGDELIVER != BSW_BSWM_CS_MSGDELIVER_MIDDLE)  */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_oxcan_rxd_sys_act;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_oXCANRxdTocUpdt(const U4 u4_a_SYS_ACT, const U4 u4_a_TOC_EN);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static inline U4      u4_s_oXCANRxdToechk(const U4 u4_a_TOUT);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_oXCANRxdInit(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANRxdInit(void)
{
    U4                        u4_t_lpcnt;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u2_g_OXCAN_RXD_NUM_PDU; u4_t_lpcnt++){
        st_gp_oxcan_rxd_pdu_st[u4_t_lpcnt].u4_log_rx = (U4)0U;
        st_gp_oxcan_rxd_pdu_st[u4_t_lpcnt].u2_to_cnt = (U2)0U;
        st_gp_oxcan_rxd_pdu_st[u4_t_lpcnt].u2_ev_cnt = (U2)OXCAN_RXD_EVC_INI;
    }

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_OXCAN_RXD_NUM_POM; u4_t_lpcnt++){
        u4_gp_oxcan_rxd_pom_elpsd[u4_t_lpcnt] = (U4)0U;
    }

    u4_s_oxcan_rxd_sys_act = (U4)0U;
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANRxdSysEvhk(const U4 u4_a_SYS_ACT, const U4 u4_a_ECU_ACT)                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANRxdSysEvhk(const U4 u4_a_SYS_ACT, const U4 u4_a_ECU_ACT)
{
    U4                        u4_t_lpcnt;
    U4                        u4_t_sys_bit;
    U4                        u4_t_sys_chk;
    U4                        u4_t_toc_en;

    u4_t_sys_chk = (U4)0U;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_OXCAN_RXD_NUM_POM; u4_t_lpcnt++){

        u4_t_sys_bit  = u4_gp_OXCAN_RXD_SYS_BY_POM[u4_t_lpcnt];
        u4_t_sys_chk |= u4_t_sys_bit;
        u4_t_toc_en   = u4_a_ECU_ACT & u4_t_sys_bit;
        if(u4_t_toc_en == (U4)0U){
            u4_gp_oxcan_rxd_pom_elpsd[u4_t_lpcnt] = (U4)0U;
        }
    }
    u4_s_oxcan_rxd_sys_act = u4_a_SYS_ACT & u4_t_sys_chk;
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANRxdMainTask(const U4 u4_a_SYS_ACT, const U4 u4_a_ECU_ACT)                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANRxdMainTask(const U4 u4_a_SYS_ACT, const U4 u4_a_ECU_ACT)
{
    U4                        u4_t_tout;
    U4                        u4_t_toc_en;

    U4                        u4_t_lpcnt;
    U4                        u4_t_bit;
    U4                        u4_t_chk;
    U4                        u4_t_act;

    u4_t_tout   = (U4)u2_g_OXCAN_RXD_POM_TOUT;
    u4_t_toc_en = (U4)0U;
    u4_t_chk    = (U4)0U;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_OXCAN_RXD_NUM_POM; u4_t_lpcnt++){

        u4_t_bit  = u4_gp_OXCAN_RXD_SYS_BY_POM[u4_t_lpcnt];
        u4_t_chk |= u4_t_bit;
        u4_t_act  = u4_a_ECU_ACT & u4_t_bit;
        if(u4_t_act == (U4)0U){
            u4_gp_oxcan_rxd_pom_elpsd[u4_t_lpcnt] = (U4)0U;
        }
        else if(u4_gp_oxcan_rxd_pom_elpsd[u4_t_lpcnt] < (U4)U4_MAX){
            u4_gp_oxcan_rxd_pom_elpsd[u4_t_lpcnt]++;
        }
        else{
            /* no processing */
        }

        /* -------------------------------------------------------------------------------------------------- */
        /* Attention :                                                                                        */
        /* -------------------------------------------------------------------------------------------------- */
        /* The logical operator ">" is intentionally used in following statement.                             */
        /*                                                                                                    */
        /* if(u4_gp_oxcan_rxd_pom_elpsd[u4_t_lpcnt] > u4_t_tout)                                              */
        /* -------------------------------------------------------------------------------------------------- */
        if(u4_gp_oxcan_rxd_pom_elpsd[u4_t_lpcnt] > u4_t_tout){
            u4_t_toc_en |= u4_t_bit;
        }
    }

    u4_t_act               = u4_a_SYS_ACT & u4_t_chk;
    u4_s_oxcan_rxd_sys_act = u4_t_act;

    vd_s_oXCANRxdTocUpdt(u4_t_act, u4_t_toc_en);
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANRxdPduAck(const U1 u1_a_GR, const U2 u2_a_PDU_ACK)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANRxdPduAck(const U1 u1_a_GR, const U2 u2_a_PDU_ACK)
{
    const ST_OXCAN_RXD_ACK *  st_tp_ACK;
    const U2 *                u2_tp_RXD;

    U2                        u2_t_min;
    U2                        u2_t_max;
    U2                        u2_t_rxd;

    if(u1_a_GR < u1_g_OXCAN_RXD_NUM_GR){

        st_tp_ACK = &st_gp_OXCAN_RXD_ACK_BY_GR[u1_a_GR];
        u2_t_min  = st_tp_ACK->u2_ack_min;
        u2_t_max  = st_tp_ACK->u2_ack_max;

        if((u2_a_PDU_ACK >= u2_t_min) &&
           (u2_a_PDU_ACK <= u2_t_max)){

            u2_tp_RXD = st_tp_ACK->u2p_RXD_BY_ACK;
            u2_t_rxd  = u2_a_PDU_ACK - u2_t_min;
            u2_t_rxd  = u2_tp_RXD[u2_t_rxd];
            if(u2_t_rxd < u2_g_OXCAN_RXD_NUM_PDU){

                st_gp_oxcan_rxd_pdu_st[u2_t_rxd].u4_log_rx = u4_s_oxcan_rxd_sys_act;
                st_gp_oxcan_rxd_pdu_st[u2_t_rxd].u2_to_cnt = (U2)0U;

                /* -------------------------------------------------------------------------------------------------- */
                /* Attention :                                                                                        */
                /* -------------------------------------------------------------------------------------------------- */
                /* st_gp_oxcan_rxd_pdu_st[u2_t_rxd].u2_ev_cnt is rolling counter. Therefore no max protection         */
                /* is implemented.                                                                                    */
                /* -------------------------------------------------------------------------------------------------- */
                st_gp_oxcan_rxd_pdu_st[u2_t_rxd].u2_ev_cnt++;
            }
        }
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXCANRxdStat(const U2 u2_a_RXD, const U4 u4_a_SYS_CHK, const U2 u2_a_RXTO_THRSH)                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXCANRxdStat(const U2 u2_a_RXD, const U4 u4_a_SYS_CHK, const U2 u2_a_RXTO_THRSH)
{
    U4                        u4_t_rec_en;
    U4                        u4_t_log_rx;
    U4                        u4_t_net_en;
    U4                        u4_t_tout;
    U4                        u4_t_tom_en;

    U2                        u2_t_to_cnt;

    U1                        u1_t_rx_st;

    u1_t_rx_st = (U1)COM_NO_RX;
    if(u2_a_RXD < u2_g_OXCAN_RXD_NUM_PDU){

        u4_t_rec_en  = u4_gp_OXCAN_RXD_SYS_BY_PDU[u2_a_RXD] & u4_a_SYS_CHK;
        u4_t_rec_en &= u4_s_oxcan_rxd_sys_act;
        if(u4_t_rec_en != (U4)0U){

            u4_t_log_rx = st_gp_oxcan_rxd_pdu_st[u2_a_RXD].u4_log_rx & u4_t_rec_en;
            if(u4_t_log_rx != (U4)0U){
                u1_t_rx_st = (U1)0U;
            }

            u4_t_net_en = u4_t_rec_en & u4_g_OXCAN_RXD_SYS_NET;
            u4_t_tout   = (U4)u2_a_RXTO_THRSH + (U4)u2_g_OXCAN_RXD_POM_TOUT;
            u4_t_tom_en = u4_s_oXCANRxdToechk(u4_t_tout) & u4_t_rec_en;
            u2_t_to_cnt = st_gp_oxcan_rxd_pdu_st[u2_a_RXD].u2_to_cnt;
            if(u4_t_net_en != (U4)0U){

                if(u4_t_tom_en != (U4)0U){
                    u1_t_rx_st |= (U1)OXCAN_RXD_TOM_EN;
                }

                if(u2_t_to_cnt >= u2_a_RXTO_THRSH){
                    u1_t_rx_st |= (U1)COM_TIMEOUT;
                }
            }
            else if(u4_t_tom_en == (U4)0U){
                /* do nothing */
            }
            else if(u2_t_to_cnt >= u2_a_RXTO_THRSH){
                u1_t_rx_st |= ((U1)OXCAN_RXD_TOM_EN | (U1)COM_TIMEOUT);
            }
            else{
                u1_t_rx_st |= (U1)OXCAN_RXD_TOM_EN;
            }
        }
    }

    return(u1_t_rx_st);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXCANRxdEvcnt(const U2 u2_a_PDU_RXD)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXCANRxdEvcnt(const U2 u2_a_RXD)
{
    U2                        u2_t_ev_cnt;

    if(u2_a_RXD < u2_g_OXCAN_RXD_NUM_PDU){
        u2_t_ev_cnt = st_gp_oxcan_rxd_pdu_st[u2_a_RXD].u2_ev_cnt & (U2)OXCAN_RXD_EVC_MAX;
    }
    else{
        u2_t_ev_cnt = (U2)OXCAN_RXD_EVC_UNK;
    }

    return((U1)u2_t_ev_cnt);
}
/*===================================================================================================================================*/
/*  static void    vd_s_oXCANRxdTocUpdt(const U4 u4_a_SYS_ACT, const U4 u4_a_TOC_EN)                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_oXCANRxdTocUpdt(const U4 u4_a_SYS_ACT, const U4 u4_a_TOC_EN)
{
    U4                        u4_t_lpcnt;
    U4                        u4_t_rec_en;
    U4                        u4_t_toc_en;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u2_g_OXCAN_RXD_NUM_PDU; u4_t_lpcnt++){

        u4_t_rec_en = u4_gp_OXCAN_RXD_SYS_BY_PDU[u4_t_lpcnt] & u4_a_SYS_ACT;
        u4_t_toc_en = u4_a_TOC_EN & u4_t_rec_en;
        if(u4_t_rec_en == (U4)0U){
            st_gp_oxcan_rxd_pdu_st[u4_t_lpcnt].u4_log_rx = (U4)0U;
            st_gp_oxcan_rxd_pdu_st[u4_t_lpcnt].u2_to_cnt = (U2)0U;
        }
        else if((u4_t_toc_en                                  == (U4)0U    ) ||
                (st_gp_oxcan_rxd_pdu_st[u4_t_lpcnt].u2_to_cnt >= (U2)U2_MAX)){
            st_gp_oxcan_rxd_pdu_st[u4_t_lpcnt].u4_log_rx &= u4_a_SYS_ACT;
        }
        else{
            st_gp_oxcan_rxd_pdu_st[u4_t_lpcnt].u4_log_rx &= u4_a_SYS_ACT;
            st_gp_oxcan_rxd_pdu_st[u4_t_lpcnt].u2_to_cnt++;
        }
    }
}
/*===================================================================================================================================*/
/*  static inline U4      u4_s_oXCANRxdToechk(const U4 u4_a_TOUT)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline U4      u4_s_oXCANRxdToechk(const U4 u4_a_TOUT)
{
    U4                        u4_t_lpcnt;
    U4                        u4_t_toc_en;

    u4_t_toc_en = (U4)0U;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_OXCAN_RXD_NUM_POM; u4_t_lpcnt++){

        if(u4_gp_oxcan_rxd_pom_elpsd[u4_t_lpcnt] >= u4_a_TOUT){
            u4_t_toc_en |= u4_gp_OXCAN_RXD_SYS_BY_POM[u4_t_lpcnt];
        }
    }

    return(u4_t_toc_en);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  2.0.0     2/28/2025  TN       oxcan_rx v1.0.7 -> oxcan_rxd v2.0.0 was re-designed for Toyota BEVStep3.                           */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, DENSO                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
