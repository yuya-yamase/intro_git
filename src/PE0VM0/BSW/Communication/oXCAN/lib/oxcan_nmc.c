/* 2.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  OEM eXtention of CAN : Network Management Coordination                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_NMC_C_MAJOR                        (2U)
#define OXCAN_NMC_C_MINOR                        (0U)
#define OXCAN_NMC_C_PATCH                        (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxcan_nmc_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((OXCAN_NMC_C_MAJOR != OXCAN_LIB_NMC_H_MAJOR) || \
     (OXCAN_NMC_C_MINOR != OXCAN_LIB_NMC_H_MINOR) || \
     (OXCAN_NMC_C_PATCH != OXCAN_LIB_NMC_H_PATCH))
#error "oxcan_nmc.c and oxcan_lib.h : source and header files are inconsistent!"
#endif

#if ((OXCAN_NMC_C_MAJOR != OXCAN_NMC_CFG_H_MAJOR) || \
     (OXCAN_NMC_C_MINOR != OXCAN_NMC_CFG_H_MINOR) || \
     (OXCAN_NMC_C_PATCH != OXCAN_NMC_CFG_H_PATCH))
#error "oxcan_nmc.c and oxcan_nmc_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_NMC_SDL_MIN                        (8U)

#define OXCAN_NMC_TOC_HA_RX                      (0U)
#define OXCAN_NMC_TOC_HA_CY                      (1U)

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
static void    vd_s_oXCANNmcRelayCh(void);
static void    vd_s_oXCANNmcCoPncRx(const U1 * const u1_ap_COCH, const U4 u4_a_NUM_COCH, U4 * u4_ap_cop_rx);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_oXCANNmcInit(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANNmcInit(void)
{
    U4 *                       u4_tp_log_rx;
    U2 *                       u2_tp_toc_rx;
    U4                         u4_t_lpcnt;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_OXCAN_NMC_NUM_CH; u4_t_lpcnt++){

        u4_tp_log_rx = st_gp_OXCAN_NMC_CH[u4_t_lpcnt].u4p_log_rx;
        if(u4_tp_log_rx != vdp_PTR_NA){

            u2_tp_toc_rx = (U2 *)u4_tp_log_rx;
            u2_tp_toc_rx[OXCAN_NMC_TOC_HA_RX]    = (U2)OXCAN_NMC_RXTO_MAX;
            u2_tp_toc_rx[OXCAN_NMC_TOC_HA_CY]    = (U2)OXCAN_NMC_RXTO_INI;

            u4_tp_log_rx[OXCAN_NMC_LOG_RX_INS_L] = (U4)0U;
            u4_tp_log_rx[OXCAN_NMC_LOG_RX_INS_H] = (U4)0U;
            u4_tp_log_rx[OXCAN_NMC_LOG_RX_LAS_L] = (U4)0U;
            u4_tp_log_rx[OXCAN_NMC_LOG_RX_LAS_H] = (U4)0U;
        }
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANNmcRxAck(const U1 u1_a_CH, const U1 * const u1_ap_SDU_RX, const U4 u4_a_DLEN)                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANNmcRxAck(const U1 u1_a_CH, const U1 * const u1_ap_SDU_RX, const U4 u4_a_DLEN)
{
    const ST_OXCAN_NMC_CH *    st_tp_CH;
    const U4 *                 u4_tp_PNC_RX;

    U4 *                       u4_tp_log_rx;
    U2 *                       u2_tp_toc_rx;
    U1 *                       u1_tp_byte;

    U4                         u4_tp_word[OXCAN_NMC_PNC_RX_NWORD];
    U4                         u4_t_lpcnt;
    U2                         u2_t_type;

    if((u1_a_CH   <  u1_g_OXCAN_NMC_NUM_CH) &&
       (u4_a_DLEN >= (U4)OXCAN_NMC_SDL_MIN)){

        st_tp_CH     = &st_gp_OXCAN_NMC_CH[u1_a_CH];

        u4_tp_log_rx = st_tp_CH->u4p_log_rx;
        u4_tp_PNC_RX = st_tp_CH->u4p_PNC_RX;
        u2_t_type    = st_tp_CH->u2_type;
        if((u4_tp_log_rx == vdp_PTR_NA            ) ||
           (u4_tp_PNC_RX == vdp_PTR_NA            ) ||
           (u2_t_type    >  (U2)OXCAN_NMC_TYPE_NPN)){
            /* do nothing */
        }
        else if(u2_t_type == (U2)OXCAN_NMC_TYPE__PN){

            u1_tp_byte = (U1 *)&u4_tp_word[OXCAN_NMC_PNC_RX_L];
            for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)OXCAN_NMC_SDL_MIN; u4_t_lpcnt++){
                u1_tp_byte[u4_t_lpcnt] = u1_ap_SDU_RX[u4_t_lpcnt];
            }

            u4_tp_log_rx[OXCAN_NMC_LOG_RX_INS_L] |= u4_tp_word[OXCAN_NMC_PNC_RX_L];
            u4_tp_log_rx[OXCAN_NMC_LOG_RX_INS_H] |= u4_tp_word[OXCAN_NMC_PNC_RX_H];

            u2_tp_toc_rx = (U2 *)u4_tp_log_rx;
            u2_tp_toc_rx[OXCAN_NMC_TOC_HA_RX] = (U2)OXCAN_NMC_RXTO_INI;
        }
        else{
            u4_tp_log_rx[OXCAN_NMC_LOG_RX_INS_L] = u4_tp_PNC_RX[OXCAN_NMC_PNC_RX_L];
            u4_tp_log_rx[OXCAN_NMC_LOG_RX_INS_H] = u4_tp_PNC_RX[OXCAN_NMC_PNC_RX_H];

            u2_tp_toc_rx = (U2 *)u4_tp_log_rx;
            u2_tp_toc_rx[OXCAN_NMC_TOC_HA_RX] = (U2)OXCAN_NMC_RXTO_INI;
        }
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANNmcCoord(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANNmcCoord(void)
{
    const ST_OXCAN_NMC_CH *    st_tp_CH;

    U4 *                       u4_tp_log_rx;
    U2 *                       u2_tp_toc;

    U4                         u4_t_lpcnt;
    U2                         u2_t_rxd;
    U2                         u2_t_cyc;
    U4                         u2_t_tout;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_OXCAN_NMC_NUM_CH; u4_t_lpcnt++){

        st_tp_CH     = &st_gp_OXCAN_NMC_CH[u4_t_lpcnt];
        u4_tp_log_rx = st_tp_CH->u4p_log_rx;
        if(u4_tp_log_rx != vdp_PTR_NA){

            u2_tp_toc = (U2 *)u4_tp_log_rx;
            u2_t_rxd  = u2_tp_toc[OXCAN_NMC_TOC_HA_RX];
            u2_t_cyc  = u2_tp_toc[OXCAN_NMC_TOC_HA_CY];
            if(u2_t_rxd > (U2)OXCAN_NMC_RXTO_MAX){
                u2_t_rxd = (U2)0U;
            }
            else if(u2_t_rxd >= (U2)OXCAN_NMC_RXTO_MAX){
             /* u2_t_rxd = (U2)OXCAN_NMC_RXTO_MAX; */
            }
            else{
                u2_t_rxd++;
            }

            u2_t_tout = st_tp_CH->u2_rx_tout;
            if(u2_t_rxd >= u2_t_tout){

                u4_tp_log_rx[OXCAN_NMC_LOG_RX_INS_L] = (U4)0U;
                u4_tp_log_rx[OXCAN_NMC_LOG_RX_INS_H] = (U4)0U;
                u4_tp_log_rx[OXCAN_NMC_LOG_RX_LAS_L] = (U4)0U;
                u4_tp_log_rx[OXCAN_NMC_LOG_RX_LAS_H] = (U4)0U; 

                u2_t_cyc = (U2)OXCAN_NMC_RXTO_INI;
            }
            else if(u2_t_cyc >= u2_t_tout){

                u4_tp_log_rx[OXCAN_NMC_LOG_RX_LAS_L] = u4_tp_log_rx[OXCAN_NMC_LOG_RX_INS_L];
                u4_tp_log_rx[OXCAN_NMC_LOG_RX_LAS_H] = u4_tp_log_rx[OXCAN_NMC_LOG_RX_INS_H];

                u4_tp_log_rx[OXCAN_NMC_LOG_RX_INS_L] = (U4)0U;
                u4_tp_log_rx[OXCAN_NMC_LOG_RX_INS_H] = (U4)0U;

                u2_t_cyc = (U2)1U;
            }
            else{ 

                u2_t_cyc++;
            }
            u2_tp_toc[OXCAN_NMC_TOC_HA_RX] = u2_t_rxd; 
            u2_tp_toc[OXCAN_NMC_TOC_HA_CY] = u2_t_cyc;
        }
    }

    vd_s_oXCANNmcRelayCh();
}
/*===================================================================================================================================*/
/*  static void    vd_s_oXCANNmcRelayCh(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_oXCANNmcRelayCh(void)
{
    const ST_OXCAN_NMC_CH *    st_tp_CH;
    const U4 *                 u4_tp_PNC_RX;
    const U1 *                 u1_tp_COCH;

    U4 *                       u4_tp_log_rx;

    U4                         u4_t_lpcnt;
    U4                         u4_t_num_coch;

    U4                         u4_tp_cop_rx[OXCAN_NMC_PNC_RX_NWORD]; /* Co-PNC Rx */
    U4                         u4_t_pnc_lo;
    U4                         u4_t_pnc_hi;
    U4                         u4_t_npn_wk;

    U2                         u2_t_type;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_OXCAN_NMC_NUM_CH; u4_t_lpcnt++){

        st_tp_CH      = &st_gp_OXCAN_NMC_CH[u4_t_lpcnt];

        u4_tp_log_rx  = st_tp_CH->u4p_log_rx;
        u4_tp_PNC_RX  = st_tp_CH->u4p_PNC_RX;
        u1_tp_COCH    = st_tp_CH->u1p_COCH;
        u2_t_type     = st_tp_CH->u2_type;
        u4_t_num_coch = (U4)st_tp_CH->u2_num_coch;
        if((u4_tp_log_rx  == vdp_PTR_NA            ) ||
           (u4_tp_PNC_RX  == vdp_PTR_NA            ) ||
           (u1_tp_COCH    == vdp_PTR_NA            ) ||
           (u2_t_type     >  (U2)OXCAN_NMC_TYPE_NPN) ||
           (u4_t_num_coch == (U4)0U                )){

            /* do nothing */
        }
        else{

            vd_s_oXCANNmcCoPncRx(u1_tp_COCH, u4_t_num_coch, &u4_tp_cop_rx[OXCAN_NMC_PNC_RX_L]);

            u4_t_pnc_lo = u4_tp_cop_rx[OXCAN_NMC_PNC_RX_L] & u4_tp_PNC_RX[OXCAN_NMC_PNC_RX_L];
            u4_t_pnc_hi = u4_tp_cop_rx[OXCAN_NMC_PNC_RX_H] & u4_tp_PNC_RX[OXCAN_NMC_PNC_RX_H];
            u4_t_npn_wk = u4_t_pnc_lo | u4_t_pnc_hi;
            if(u2_t_type == (U2)OXCAN_NMC_TYPE__PN){
                (void)ComM_SetCoPncAwake((U1)u4_t_lpcnt, u4_t_pnc_lo, u4_t_pnc_hi);
            }
            else if(u4_t_npn_wk != (U4)0U){
                (void)ComM_RequestComMode((U1)st_tp_CH->u2_npn_uh, (U1)COMM_FULL_COMMUNICATION);
            }
            else{
                (void)ComM_RequestComMode((U1)st_tp_CH->u2_npn_uh, (U1)COMM_NO_COMMUNICATION);
            }
        }
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_oXCANNmcCoPncRx(const U1 * const u1_ap_COCH, const U4 u4_a_NUM_COCH, U4 * u4_ap_cop_rx)                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_oXCANNmcCoPncRx(const U1 * const u1_ap_COCH, const U4 u4_a_NUM_COCH, U4 * u4_ap_cop_rx)
{
    U4 *                       u4_tp_log_rx;

    U4                         u4_t_lpcnt;
    U4                         u4_t_pnc_lo;
    U4                         u4_t_pnc_hi;
    U1                         u1_t_coch;

    u4_t_pnc_lo = (U4)0U;
    u4_t_pnc_hi = (U4)0U;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < u4_a_NUM_COCH; u4_t_lpcnt++){

        u1_t_coch    = u1_ap_COCH[u4_t_lpcnt];
        u4_tp_log_rx = st_gp_OXCAN_NMC_CH[u1_t_coch].u4p_log_rx;
        if(u4_tp_log_rx != vdp_PTR_NA){
            u4_t_pnc_lo |= (u4_tp_log_rx[OXCAN_NMC_LOG_RX_INS_L] | u4_tp_log_rx[OXCAN_NMC_LOG_RX_LAS_L]);
            u4_t_pnc_hi |= (u4_tp_log_rx[OXCAN_NMC_LOG_RX_INS_H] | u4_tp_log_rx[OXCAN_NMC_LOG_RX_LAS_H]);
        }
    }

    u4_ap_cop_rx[OXCAN_NMC_PNC_RX_L] = u4_t_pnc_lo;
    u4_ap_cop_rx[OXCAN_NMC_PNC_RX_H] = u4_t_pnc_hi;
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  2.0.0     6/11/2025  TN       New                                                                                                */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, DENSO                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/


