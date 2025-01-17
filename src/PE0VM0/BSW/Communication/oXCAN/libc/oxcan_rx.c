/* 1.0.7 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Oem eXtention of CAN Rx                                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_RX_C_MAJOR                         (1U)
#define OXCAN_RX_C_MINOR                         (0U)
#define OXCAN_RX_C_PATCH                         (7U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxcan_rx_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((defined(BSW_BSWM_CS_CFG_FUNC_CS)     ) && \
     (defined(BSW_BSWM_CS_CFG_FUNC_SECOC)  ) && \
     (BSW_BSWM_CS_CFG_FUNC_CS    == BSW_USE) && \
     (BSW_BSWM_CS_CFG_FUNC_SECOC == BSW_USE))
#include "SecOC.h"
#endif /* #if ((defined(BSW_BSWM_CS_CFG_FUNC_CS)  ) && .. */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((OXCAN_RX_C_MAJOR != OXCAN_RX_CFG_H_MAJOR) || \
     (OXCAN_RX_C_MINOR != OXCAN_RX_CFG_H_MINOR) || \
     (OXCAN_RX_C_PATCH != OXCAN_RX_CFG_H_PATCH))
#error "oxcan_rx_cfg.c and oxcan_rx_cfg_private.h : source and header files are inconsistent!"
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
static U4      u4_sp_oxcan_rx_pom_elpsd[OXCAN_RX_NUM_POM];
static U2      u2_s_oxcan_rx_sys_chk;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static        U2      u2_s_oXCANRxToechk(const U1 u1_a_SYSBIT);
static        void    vd_s_oXCANRxBatInit(const ST_OXCAN_RX_CH * st_ap_CH);
static        void    vd_s_oXCANRxstUpdt(const ST_OXCAN_RX_CH * st_ap_CH, const U1 u1_a_SYS_CHK, const U2 u2_a_TOE_BY_CH);
static inline U2      u2_s_oXCANRxPomchk(const U2 u2_a_SYS_CHK, const U4 u4_a_POM_TOUT);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_oXCANRxInit(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANRxInit(void)
{
    U4                        u4_t_lpcnt;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)OXCAN_RX_NUM_POM; u4_t_lpcnt++){
        u4_sp_oxcan_rx_pom_elpsd[u4_t_lpcnt] = (U4)0U;
    }

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_OXCAN_RX_NUM_CH; u4_t_lpcnt++){
        u2_gp_oxcan_rx_nwk_elpsd[u4_t_lpcnt] = (U2)OXCAN_RX_POM_INA;
        u2_gp_oxcan_rx_toe_chk[u4_t_lpcnt]   = (U2)0U;
    }

    u2_s_oxcan_rx_sys_chk = (U2)OXCAN_RX_SYS_NRX_BAT | (U2)OXCAN_RX_SYS_TOE_BAT;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u2_g_OXCAN_RX_NUM_RX; u4_t_lpcnt++){
        st_gp_oxcan_rx_pdu_st[u4_t_lpcnt].u2_rxto_cnt = (U2)OXCAN_RX_RXTO_INI;
        st_gp_oxcan_rx_pdu_st[u4_t_lpcnt].u1_log_rx   = (U1)0U;
        st_gp_oxcan_rx_pdu_st[u4_t_lpcnt].u1_rxev_cnt = (U1)OXCAN_RX_RXEV_CNT_INI;
    }    
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANRxOpemdEvthk(const U1 u1_a_SYSBIT)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANRxOpemdEvthk(const U1 u1_a_SYSBIT)
{
    U4                        u4_t_lpcnt;
    U2                        u2_t_sys_chk;

    u2_t_sys_chk  = (u2_g_oXCANRxCfgSysXgrOn((U2)u1_a_SYSBIT) & (U2)OXCAN_RX_SYS_NRX_XGR) | (U2)u1_a_SYSBIT;
    u2_t_sys_chk |= (U2)(u2_t_sys_chk << OXCAN_RX_SYS_LSB_TOE);
    u2_s_oxcan_rx_sys_chk = u2_t_sys_chk;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_OXCAN_RX_NUM_CH; u4_t_lpcnt++){

        u2_t_sys_chk = (U2)st_gp_OXCAN_RX_BY_CH[u4_t_lpcnt].u2_sys_en & (U2)u1_a_SYSBIT;
        if(u2_t_sys_chk == (U2)0U){
            u2_gp_oxcan_rx_nwk_elpsd[u4_t_lpcnt] = (U2)OXCAN_RX_POM_INA;
        }
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANRxMainTask(const U1 u1_a_SYSBIT)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANRxMainTask(const U1 u1_a_SYSBIT)
{
    const ST_OXCAN_RX_CH *    st_tp_CH;
    U4                        u4_t_ch;

    U2                        u2_t_toe_chk;
    U2                        u2_t_toe_by_ch;

    U2                        u2_t_ch_en;
    U1                        u1_t_rx_en;

    u2_t_toe_chk = u2_s_oXCANRxToechk(u1_a_SYSBIT);
    for(u4_t_ch = (U4)0U; u4_t_ch < (U4)u1_g_OXCAN_RX_NUM_CH; u4_t_ch++){

        st_tp_CH   = &st_gp_OXCAN_RX_BY_CH[u4_t_ch];

        u2_t_ch_en = st_tp_CH->u2_sys_en & (U2)u1_a_SYSBIT;
        if((u2_t_ch_en            != (U2)0U    ) &&
           (st_tp_CH->fp_u1_RX_EN != vdp_PTR_NA)){

            u1_t_rx_en = (*st_tp_CH->fp_u1_RX_EN)((U1)u4_t_ch);
            if(u1_t_rx_en != (U1)TRUE){
                u2_t_ch_en = (U2)0U;
            }
        }

        if(u2_t_ch_en == (U2)0U){

            u2_gp_oxcan_rx_nwk_elpsd[u4_t_ch] = (U2)OXCAN_RX_POM_INA;
        }
        else if(u2_gp_oxcan_rx_nwk_elpsd[u4_t_ch] >= (U2)OXCAN_RX_POM_INA){

            u2_gp_oxcan_rx_nwk_elpsd[u4_t_ch] = (U2)0U;
            vd_s_oXCANRxBatInit(st_tp_CH);
            vd_g_oXCANUsrhkNwToAct((U1)u4_t_ch);
        } 
        else if(u2_gp_oxcan_rx_nwk_elpsd[u4_t_ch] >= (U2)OXCAN_RX_POM_MAX){

            u2_gp_oxcan_rx_nwk_elpsd[u4_t_ch] = (U2)OXCAN_RX_POM_MAX;
        }
        else{

            u2_gp_oxcan_rx_nwk_elpsd[u4_t_ch]++;
        }

        /* -------------------------------------------------------------------------------------------------- */
        /* Attention :                                                                                        */
        /* -------------------------------------------------------------------------------------------------- */
        /* The logical operator ">" is intentionally used in following statement.                             */
        /*                                                                                                    */
        /* if(u2_gp_oxcan_rx_nwk_elpsd[u4_t_ch] >  u2_g_OXCAN_RX_POM_TOUT)                                    */
        /*                                                                                                    */
        /* The reason is why Aubist/CS notifies RX timeout if timeout threshold plus 1 is elapsed since       */
        /* vd_g_VehopemdMainTask is executed after vd_g_oXCANMainPreTask.                                     */
        /* In Aubist/CS, ACC-ON/OFF and IG-ON/OFF detection delays 10 milliseconds                            */
        /* -------------------------------------------------------------------------------------------------- */
        if((u2_gp_oxcan_rx_nwk_elpsd[u4_t_ch] <= (U2)OXCAN_RX_POM_MAX  ) &&
           (u2_gp_oxcan_rx_nwk_elpsd[u4_t_ch] >  u2_g_OXCAN_RX_POM_TOUT)){
            u2_t_toe_by_ch = u2_t_toe_chk | (U2)OXCAN_RX_SYS_TOE_BAT;
        }
        else{
            u2_t_toe_by_ch = u2_t_toe_chk;
        }
        u2_gp_oxcan_rx_toe_chk[u4_t_ch] = u2_t_toe_by_ch;

        vd_s_oXCANRxstUpdt(st_tp_CH, u1_a_SYSBIT, u2_t_toe_by_ch);
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANRxAck(const U1 u1_a_CH, const U2 u2_a_MSG_RX)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANRxAck(const U1 u1_a_CH, const U2 u2_a_MSG_RX)
{
    const U2 *                u2_tp_PDU_BY_RX;

    U2                        u2_t_pdu_rx;
    U2                        u2_t_min;
    U2                        u2_t_max;

    if(u1_a_CH < u1_g_OXCAN_RX_NUM_CH){

        u2_t_min = st_gp_OXCAN_RX_BY_CH[u1_a_CH].u2_msg_min;
        u2_t_max = st_gp_OXCAN_RX_BY_CH[u1_a_CH].u2_msg_max;

        if((u2_a_MSG_RX >= u2_t_min) &&
           (u2_a_MSG_RX <= u2_t_max)){

            u2_tp_PDU_BY_RX = st_gp_OXCAN_RX_BY_CH[u1_a_CH].u2p_PDU_BY_RX;
            u2_t_pdu_rx     = u2_a_MSG_RX - u2_t_min;
            u2_t_pdu_rx     = u2_tp_PDU_BY_RX[u2_t_pdu_rx];
            if(u2_t_pdu_rx < u2_g_OXCAN_RX_NUM_RX){

                st_gp_oxcan_rx_pdu_st[u2_t_pdu_rx].u2_rxto_cnt = (U2)OXCAN_RX_RXTO_INI;
                st_gp_oxcan_rx_pdu_st[u2_t_pdu_rx].u1_log_rx   = (U1)u2_s_oxcan_rx_sys_chk;

                /* -------------------------------------------------------------------------------------------------- */
                /* Attention :                                                                                        */
                /* -------------------------------------------------------------------------------------------------- */
                /* st_gp_oxcan_rx_pdu_st[u2_t_pdu_rx].u1_rxev_cnt is rolling counter. Therefore no max protection     */
                /* is implemented.                                                                                    */
                /* -------------------------------------------------------------------------------------------------- */
                st_gp_oxcan_rx_pdu_st[u2_t_pdu_rx].u1_rxev_cnt++;
            }
        }
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXCANRxEnabled(const U1 u1_a_CH)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXCANRxEnabled(const U1 u1_a_CH)
{
    U1                        u1_t_rxe;

    if((u1_a_CH                              <  u1_g_OXCAN_RX_NUM_CH) &&
       (u2_gp_oxcan_rx_nwk_elpsd[u1_a_CH] <= (U2)OXCAN_RX_POM_MAX)){
        u1_t_rxe = (U1)TRUE;
    }
    else{
        u1_t_rxe = (U1)FALSE;
    }

    return(u1_t_rxe);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXCANRxStat(const U2 u2_a_PDU_RX, const U2 u2_a_SYS_CHK, const U2 u2_a_RXTO_THRSH)                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXCANRxStat(const U2 u2_a_PDU_RX, const U2 u2_a_SYS_CHK, const U2 u2_a_RXTO_THRSH)
{
    U4                        u4_t_pom_tout;

    U2                        u2_t_rx_ena;
    U2                        u2_t_pom_chk;
    U2                        u2_t_rxto_cnt;
    U2                        u2_t_log_rx;

    U1                        u1_t_rx_stat;

    if(u2_a_PDU_RX < u2_g_OXCAN_RX_NUM_RX){

        u2_t_rx_ena = (U2)u1_gp_OXCAN_RX_SYS_BY_RX[u2_a_PDU_RX] & u2_s_oxcan_rx_sys_chk;
        if(u2_t_rx_ena == (U2)0U){
            u1_t_rx_stat = (U1)COM_NO_RX;
        }
        else{

            u4_t_pom_tout = (U4)u2_a_RXTO_THRSH + (U4)u2_g_OXCAN_RX_POM_TOUT;
            u2_t_pom_chk  = u2_s_oXCANRxPomchk(u2_a_SYS_CHK, u4_t_pom_tout);
            u2_t_rxto_cnt = st_gp_oxcan_rx_pdu_st[u2_a_PDU_RX].u2_rxto_cnt;
            if(u2_t_pom_chk == (U2)0U){
                u1_t_rx_stat  = (U1)0x00U;
            }
            else if((u2_t_rxto_cnt <= (U2)OXCAN_RX_RXTO_MAX) &&
                    (u2_t_rxto_cnt >= u2_a_RXTO_THRSH         )){
                u1_t_rx_stat  = ((U1)COM_TIMEOUT | (U1)OXCAN_RX_RXST_TOE);
            }
            else{
                u1_t_rx_stat  = (U1)OXCAN_RX_RXST_TOE;
            }

            u2_t_log_rx  = u2_s_oxcan_rx_sys_chk & u2_a_SYS_CHK;
            u2_t_log_rx &= (U2)st_gp_oxcan_rx_pdu_st[u2_a_PDU_RX].u1_log_rx;
            if(u2_t_log_rx == (U2)0U){
                u1_t_rx_stat |= (U1)COM_NO_RX;
            }
        }
    }
    else{
        u1_t_rx_stat = (U1)COM_NO_RX;
    }

    return(u1_t_rx_stat);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXCANRxEvcnt(const U2 u2_a_PDU_RX)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXCANRxEvcnt(const U2 u2_a_PDU_RX)
{
    U1                        u1_t_rxev_cnt;

    if(u2_a_PDU_RX < u2_g_OXCAN_RX_NUM_RX){
        u1_t_rxev_cnt = st_gp_oxcan_rx_pdu_st[u2_a_PDU_RX].u1_rxev_cnt & (U1)OXCAN_RX_RXEV_CNT_MAX;
    }
    else{
        u1_t_rxev_cnt = (U1)OXCAN_RX_RXEV_CNT_UNK;
    }

    return(u1_t_rxev_cnt);
}
/*===================================================================================================================================*/
/*  U2      u2_g_oXCANRxToechk(const U1 u1_a_CH)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2      u2_g_oXCANRxToechk(const U1 u1_a_CH)
{
    U2                        u2_t_toe_chk;

    if(u1_a_CH < u1_g_OXCAN_RX_NUM_CH){
        u2_t_toe_chk = u2_gp_oxcan_rx_toe_chk[u1_a_CH];
    }
    else{
        u2_t_toe_chk = (U2)0U;
    }

    return(u2_t_toe_chk);
}
#if (OXCAN_RX_STOP_EN == 1U)
/*===================================================================================================================================*/
/*  void vd_g_oXCANRxTimerInit(const U1 u1_a_CH)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_oXCANRxTimerInit(const U1 u1_a_CH)
{
    const ST_OXCAN_RX_CH *st_tp_CH;
    const U2 *u2_tp_PDU_BY_CH;
    U4 u4_t_num_rx;
    U4 u4_t_lpcnt;
    U2 u2_t_pdu_rx;

    st_tp_CH = &st_gp_OXCAN_RX_BY_CH[u1_a_CH];
    u2_tp_PDU_BY_CH = st_tp_CH->u2p_PDU_BY_CH;
    if(u2_tp_PDU_BY_CH != vdp_PTR_NA){
        u4_t_num_rx = (U4)st_tp_CH->u2_num_rx;
        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < u4_t_num_rx; u4_t_lpcnt++){
            u2_t_pdu_rx = u2_tp_PDU_BY_CH[u4_t_lpcnt];
            st_gp_oxcan_rx_pdu_st[u2_t_pdu_rx].u2_rxto_cnt = (U2)OXCAN_RX_RXTO_INI;
            u2_t_pdu_rx += st_gp_OXCAN_RX_BY_CH[u1_a_CH].u2_msg_min;
            Com_ClearTickTime(u2_t_pdu_rx);
        }
    }
}
#endif /* #if (OXCAN_RX_STOP_EN == 1U) */
/*===================================================================================================================================*/
/*  static U2      u2_s_oXCANRxToechk(const U1 u1_a_SYSBIT)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2      u2_s_oXCANRxToechk(const U1 u1_a_SYSBIT)
{
    U4                        u4_t_lpcnt;

    U2                        u2_t_sys_chk;
    U2                        u2_t_pom_chk;
    U2                        u2_t_toc_en;
    U2                        u2_t_toe_chk;

    u2_t_sys_chk  = (u2_g_oXCANRxCfgSysXgrOn((U2)u1_a_SYSBIT) & (U2)OXCAN_RX_SYS_NRX_XGR) | (U2)u1_a_SYSBIT;
    u2_t_sys_chk |= (U2)(u2_t_sys_chk << OXCAN_RX_SYS_LSB_TOE);
    u2_t_pom_chk  = u2_t_sys_chk & u2_s_oxcan_rx_sys_chk;
    u2_t_toe_chk  = (U2)0U;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)OXCAN_RX_NUM_POM; u4_t_lpcnt++){

        u2_t_toc_en = u2_t_pom_chk & u2_sp_OXCAN_RX_POM_CHK[u4_t_lpcnt];
        if(u2_t_toc_en == (U2)0U){
            u4_sp_oxcan_rx_pom_elpsd[u4_t_lpcnt] = (U4)0U;
        }
        else if(u4_sp_oxcan_rx_pom_elpsd[u4_t_lpcnt] < (U4)U4_MAX){
            u4_sp_oxcan_rx_pom_elpsd[u4_t_lpcnt]++;
        }
        else{
            /* no processing */
        }

        /* -------------------------------------------------------------------------------------------------- */
        /* Attention :                                                                                        */
        /* -------------------------------------------------------------------------------------------------- */
        /* The logical operator ">" is intentionally used in following statement.                             */
        /*                                                                                                    */
        /* if(u2_gp_oxcan_rx_nwk_elpsd[u4_t_ch] >  u2_g_OXCAN_RX_POM_TOUT)                                    */
        /*                                                                                                    */
        /* The reason is why Aubist/CS notifies RX timeout if timeout threshold plus 1 is elapsed since       */
        /* vd_g_VehopemdMainTask is executed after vd_g_oXCANMainPreTask.                                     */
        /* In Aubist/CS, ACC-ON/OFF and IG-ON/OFF detection delays 10 milliseconds                            */
        /* -------------------------------------------------------------------------------------------------- */
        if(u4_sp_oxcan_rx_pom_elpsd[u4_t_lpcnt] > (U4)u2_g_OXCAN_RX_POM_TOUT){
            u2_t_toe_chk |= u2_t_toc_en;
        }
    }
    u2_s_oxcan_rx_sys_chk = u2_t_sys_chk;

    return(u2_t_toe_chk);
}
/*===================================================================================================================================*/
/*  static void    vd_s_oXCANRxBatInit(const ST_OXCAN_RX_CH * st_ap_CH)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_oXCANRxBatInit(const ST_OXCAN_RX_CH * st_ap_CH)
{
    const U2 *                u2_tp_PDU_BY_CH;

    U4                        u4_t_lpcnt;
    U4                        u4_t_num_rx;

    U2                        u2_t_pdu_rx;
    U2                        u2_t_bat_rx;

    u2_tp_PDU_BY_CH = st_ap_CH->u2p_PDU_BY_CH;
    u2_t_bat_rx     = st_ap_CH->u2_sys_en & (U2)OXCAN_SYS_BAT;
    if((u2_t_bat_rx     != (U2)0U    ) &&
       (u2_tp_PDU_BY_CH != vdp_PTR_NA)){

        u4_t_num_rx = (U4)st_ap_CH->u2_num_rx;
        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < u4_t_num_rx; u4_t_lpcnt++){

            u2_t_pdu_rx = u2_tp_PDU_BY_CH[u4_t_lpcnt];
            u2_t_bat_rx = (U2)u1_gp_OXCAN_RX_SYS_BY_RX[u2_t_pdu_rx] & (U2)OXCAN_SYS_BAT;
            if(u2_t_bat_rx != (U2)0U){
                st_gp_oxcan_rx_pdu_st[u2_t_pdu_rx].u2_rxto_cnt = (U2)OXCAN_RX_RXTO_INI;
                st_gp_oxcan_rx_pdu_st[u2_t_pdu_rx].u1_log_rx   = (U1)0U;
            }
        }
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_oXCANRxstUpdt(const ST_OXCAN_RX_CH * st_ap_CH, const U1 u1_a_SYS_CHK, const U2 u2_a_TOE_BY_CH)               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_oXCANRxstUpdt(const ST_OXCAN_RX_CH * st_ap_CH, const U1 u1_a_SYS_CHK, const U2 u2_a_TOE_BY_CH)
{
    static const U2           u2_sp_OXCAN_RX_TOE_BY_SYS[] = {
        (U2)0x0000U,        /* 0,   0,   0,   0,   0   : None     */
        (U2)0x0100U,        /* 0,   0,   0,   0,   1   : WKUPMASK */
        (U2)0x0200U,        /* 0,   0,   0,   1,   0   : PONMASK  */
        (U2)0x0100U,        /* 0,   0,   0,   1,   1   : WKUPMASK */
        (U2)0x0400U,        /* 0,   0,   1,   0,   0   : PONMASK  */
        (U2)0x0100U,        /* 0,   0,   1,   0,   1   : WKUPMASK */
        (U2)0x0600U,        /* 0,   0,   1,   1,   0   : PONMASK  */
        (U2)0x0100U,        /* 0,   0,   1,   1,   1   : WKUPMASK */

        (U2)0x0800U,        /* 0,   1,   0,   0,   0   : PONMASK  */
        (U2)0x0100U,        /* 0,   1,   0,   0,   1   : WKUPMASK */
        (U2)0x0a00U,        /* 0,   1,   0,   1,   0   : PONMASK  */
        (U2)0x0100U,        /* 0,   1,   0,   1,   1   : WKUPMASK */
        (U2)0x0c00U,        /* 0,   1,   1,   0,   0   : PONMASK  */
        (U2)0x0100U,        /* 0,   1,   1,   0,   1   : WKUPMASK */
        (U2)0x0e00U,        /* 0,   1,   1,   1,   0   : PONMASK  */
        (U2)0x0100U,        /* 0,   1,   1,   1,   1   : WKUPMASK */

        (U2)0x1000U,        /* 1,   0,   0,   0,   0   : PONMASK  */
        (U2)0x0100U,        /* 1,   0,   0,   0,   1   : WKUPMASK */
        (U2)0x1200U,        /* 1,   0,   0,   1,   0   : PONMASK  */
        (U2)0x0100U,        /* 1,   0,   0,   1,   1   : WKUPMASK */
        (U2)0x1400U,        /* 1,   0,   1,   0,   0   : PONMASK  */
        (U2)0x0100U,        /* 1,   0,   1,   0,   1   : WKUPMASK */
        (U2)0x1600U,        /* 1,   0,   1,   1,   0   : PONMASK  */
        (U2)0x0100U,        /* 1,   0,   1,   1,   1   : WKUPMASK */

        (U2)0x1800U,        /* 1,   1,   0,   0,   0   : PONMASK  */
        (U2)0x0100U,        /* 1,   1,   0,   0,   1   : WKUPMASK */
        (U2)0x1a00U,        /* 1,   1,   0,   1,   0   : PONMASK  */
        (U2)0x0100U,        /* 1,   1,   0,   1,   1   : WKUPMASK */
        (U2)0x1c00U,        /* 1,   1,   1,   0,   0   : PONMASK  */
        (U2)0x0100U,        /* 1,   1,   1,   0,   1   : WKUPMASK */
        (U2)0x1e00U,        /* 1,   1,   1,   1,   0   : PONMASK  */
        (U2)0x0100U         /* 1,   1,   1,   1,   1   : WKUPMASK */
    };

    const U2 *                u2_tp_PDU_BY_CH;

    U4                        u4_t_lpcnt;
    U4                        u4_t_num_rx;

    U2                        u2_t_pdu_rx;
    U2                        u2_t_toc_en;

    U1                        u1_t_sys_chk;

    u2_tp_PDU_BY_CH = st_ap_CH->u2p_PDU_BY_CH;
    if(u2_tp_PDU_BY_CH != vdp_PTR_NA){

        u4_t_num_rx = (U4)st_ap_CH->u2_num_rx;
        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < u4_t_num_rx; u4_t_lpcnt++){

            u2_t_pdu_rx  = u2_tp_PDU_BY_CH[u4_t_lpcnt];
            u1_t_sys_chk = u1_gp_OXCAN_RX_SYS_BY_RX[u2_t_pdu_rx] & u1_a_SYS_CHK;
            if(u1_t_sys_chk == (U1)0U){

                st_gp_oxcan_rx_pdu_st[u2_t_pdu_rx].u2_rxto_cnt = (U2)OXCAN_RX_RXTO_INI;
                st_gp_oxcan_rx_pdu_st[u2_t_pdu_rx].u1_log_rx   = (U1)0U;
            }
            else{

                u2_t_toc_en = u2_sp_OXCAN_RX_TOE_BY_SYS[u1_t_sys_chk] & u2_a_TOE_BY_CH;
                if(u2_t_toc_en == (U2)0U){
                }
                else if(st_gp_oxcan_rx_pdu_st[u2_t_pdu_rx].u2_rxto_cnt >= (U2)OXCAN_RX_RXTO_INI){
                    st_gp_oxcan_rx_pdu_st[u2_t_pdu_rx].u2_rxto_cnt = (U2)0U;
                }
                else if(st_gp_oxcan_rx_pdu_st[u2_t_pdu_rx].u2_rxto_cnt >= (U2)OXCAN_RX_RXTO_MAX){
                    st_gp_oxcan_rx_pdu_st[u2_t_pdu_rx].u2_rxto_cnt = (U2)OXCAN_RX_RXTO_MAX;
                }
                else{
                    st_gp_oxcan_rx_pdu_st[u2_t_pdu_rx].u2_rxto_cnt++;
                }
                st_gp_oxcan_rx_pdu_st[u2_t_pdu_rx].u1_log_rx &= (U1)u2_s_oxcan_rx_sys_chk;
            }
        }
    }
}
/*===================================================================================================================================*/
/*  static inline U2      u2_s_oXCANRxPomchk(const U2 u2_a_SYS_CHK, const U4 u4_a_POM_TOUT)                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline U2      u2_s_oXCANRxPomchk(const U2 u2_a_SYS_CHK, const U4 u4_a_POM_TOUT)
{
    U4                        u4_t_lpcnt;
    U2                        u2_t_pom_chk;

    u2_t_pom_chk = (U2)OXCAN_RX_SYS_TOE_BAT;
    if(u2_a_SYS_CHK > (U2)OXCAN_RX_SYS_TOE_BAT){

        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)OXCAN_RX_NUM_POM; u4_t_lpcnt++){

            /* -------------------------------------------------------------------------------------------------- */
            /* Attention :                                                                                        */
            /* -------------------------------------------------------------------------------------------------- */
            /* The logical operator ">" is intentionally used. The reason is why Aubist/CS notifies RX timeout    */
            /* if timeout threshold plus 1 is elapsed since vd_g_VehopemdMainTask is executed after               */
            /* vd_g_oXCANMainPreTask.                                                                             */
            /* In Aubist/CS, ACC-ON/OFF and IG-ON/OFF detection delays 10 milliseconds                            */
            /* -------------------------------------------------------------------------------------------------- */
            if(u4_sp_oxcan_rx_pom_elpsd[u4_t_lpcnt] > u4_a_POM_TOUT){
                u2_t_pom_chk |= u2_sp_OXCAN_RX_POM_CHK[u4_t_lpcnt];
            }
        }
    }

    u2_t_pom_chk &= (u2_s_oxcan_rx_sys_chk & u2_a_SYS_CHK);

    return(u2_t_pom_chk);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     2/22/2022  HU       ty19epf_ren_d1x_v220_r009 -> ox25epf_ren_d1x_v100_r000, Function Name tycan_comrx -> oxcan_rx.     */
/*  1.0.1     9/27/2022  TM       u2_s_oXCANRxPomchk was implemented.                                                                */
/*  1.0.2    11/16/2022  HU       Bug Fix : u2_s_oxcan_rx_pom_chk was not updated regularly.                                         */
/*  1.0.3    12/13/2022  TM       Aubist/SEC Gen1 -> Gen2.                                                                           */
/*  1.0.4     1/25/2023  TM       Changed to be able to select receiving stops when sending stops.                                   */
/*  1.0.5     5/10/2023  HU       OXCAN_TXRXCTRL_RX_STOP -> OXCAN_RX_STOP_EN                                                         */
/*  1.0.6     1/31/2024  TI       Changed oxcan_usrhk.h include order.                                                               */
/*  1.0.7     2/08/2024  AM       Minor bug fixes.                                                                                   */
/*                                                                                                                                   */
/*  * HU   = Hayato Usui, DENSO                                                                                                      */
/*  * TM   = Takanori Maruyama, DENSO                                                                                                */
/*  * TI   = Tomoko Inuzuka, DENSO                                                                                                   */
/*  * AM   = Atsushi Mizutani, DENSO                                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/
