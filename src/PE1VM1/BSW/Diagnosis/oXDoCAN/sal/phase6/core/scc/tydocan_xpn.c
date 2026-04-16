/* 1.0.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  TyDoCAN Service Application Layer / XXX Product Number                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_XPN_C_MAJOR                      (1)
#define TYDOCAN_XPN_C_MINOR                      (0)
#define TYDOCAN_XPN_C_PATCH                      (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "tydocan_xpn.h"
#include "tydocan_sal.h"
#include "oxdocan_cfg_private.h"
#include "memcpy_u1.h"
#include "memfill_u1.h"
#include "xspi_met_dsal.h"
#include "product.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_XPN_LB3_NBYTE                       (12U)
#define TYDC_XPN_LB4_NBYTE                       (12U)
#define TYDC_XPN_LB5_NBYTE                       (12U)
#define TYDC_XPN_LB6_NBYTE                       (12U)
#define TYDC_XPN_HUD_NBYTE                       (12U)
#define TYDC_XPN_DISP_NBYTE                      (12U)
#define TYDC_XPN_ECU_PN_NBYTE                    (12U)
#define TYDC_XPN_SERI_N_NBYTE                    (10U)
#define TYDC_XPN_HUD_SERI_N_NBYTE                (20U)

#define TYDC_XPN_DIAGON_TOUT                     (5000U / OXDC_MAIN_TICK)  /*  5000ms  */
#define TYDC_XPN_DIAGON_TOUT_MAX                 (0xFFFEU)
#define TYDC_XPN_DIAGON_TOUT_INI                 (0xFFFFU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1                u1_sp_tydc_xpn_lb3[TYDC_XPN_LB3_NBYTE];
static U1                u1_sp_tydc_xpn_lb4[TYDC_XPN_LB4_NBYTE];
static U1                u1_sp_tydc_xpn_lb5[TYDC_XPN_LB5_NBYTE];
static U1                u1_sp_tydc_xpn_lb6[TYDC_XPN_LB6_NBYTE];
static U1                u1_sp_tydc_xpn_hud[TYDC_XPN_HUD_NBYTE];
static U1                u1_sp_tydc_xpn_disp[TYDC_XPN_DISP_NBYTE];
static U1                u1_sp_tydc_xpn_ecu_pn[TYDC_XPN_ECU_PN_NBYTE];
static U1                u1_sp_tydc_xpn_seri_n[TYDC_XPN_SERI_N_NBYTE];
static U1                u1_sp_tydc_xpn_hud_seri_n[TYDC_XPN_HUD_SERI_N_NBYTE];

static U2                u2_s_tydc_xpn_rx_sts;
static U2                u2_s_tydc_xpn_dgon_cnt;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANXpnInit(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANXpnInit(void)
{
    vd_g_MemfillU1(u1_sp_tydc_xpn_lb3,    (U1)0U, (U4)TYDC_XPN_LB3_NBYTE);
    vd_g_MemfillU1(u1_sp_tydc_xpn_lb4,    (U1)0U, (U4)TYDC_XPN_LB4_NBYTE);
    vd_g_MemfillU1(u1_sp_tydc_xpn_lb5,    (U1)0U, (U4)TYDC_XPN_LB5_NBYTE);
    vd_g_MemfillU1(u1_sp_tydc_xpn_lb6,    (U1)0U, (U4)TYDC_XPN_LB6_NBYTE);
    vd_g_MemfillU1(u1_sp_tydc_xpn_hud,    (U1)0U, (U4)TYDC_XPN_HUD_NBYTE);
    vd_g_MemfillU1(u1_sp_tydc_xpn_disp,   (U1)0U, (U4)TYDC_XPN_DISP_NBYTE);
    vd_g_MemfillU1(u1_sp_tydc_xpn_ecu_pn, (U1)0U, (U4)TYDC_XPN_ECU_PN_NBYTE);
    vd_g_MemfillU1(u1_sp_tydc_xpn_seri_n, (U1)0U, (U4)TYDC_XPN_SERI_N_NBYTE);
    vd_g_MemfillU1(u1_sp_tydc_xpn_hud_seri_n, (U1)0U, (U4)TYDC_XPN_HUD_SERI_N_NBYTE);

    u2_s_tydc_xpn_rx_sts    = (U2)0U;
    u2_s_tydc_xpn_dgon_cnt  = (U2)TYDC_XPN_DIAGON_TOUT_INI;
}

/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANXpnMainTask(const U1 u1_a_EOM)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANXpnMainTask(const U1 u1_a_EOM)
{
    U1                         u1_t_diag_on;

    u1_t_diag_on = u1_a_EOM & (U1)OXDC_EOM_DIAG_ON;
    if(u1_t_diag_on != (U1)0U){
        if(u2_s_tydc_xpn_dgon_cnt < (U2)TYDC_XPN_DIAGON_TOUT_MAX){
            u2_s_tydc_xpn_dgon_cnt++;
        }
        else if(u2_s_tydc_xpn_dgon_cnt >= (U2)TYDC_XPN_DIAGON_TOUT_INI){
            u2_s_tydc_xpn_dgon_cnt  = (U2)0U;
        }
        else {
            /* Do Nothing */
        }
    }
    else{
        vd_g_TyDoCANXpnInit();
    }

    if(u2_s_tydc_xpn_dgon_cnt < (U2)TYDC_XPN_DIAGON_TOUT){
        u2_s_tydc_xpn_rx_sts  = (U2)((u1_g_XSpiSpnRx((U1)XSPI_SPN_RX_LB3, 
                                    &u1_sp_tydc_xpn_lb3[0], 
                                    (U1)XSPI_SPN_NB_LB3) & (U1)TRUE)) <<  TYDC_XPN_RX_LB3;

        u2_s_tydc_xpn_rx_sts |= (U2)((u1_g_XSpiSpnRx((U1)XSPI_SPN_RX_LB4, 
                                    &u1_sp_tydc_xpn_lb4[0], 
                                    (U1)XSPI_SPN_NB_LB4) & (U1)TRUE)) <<  TYDC_XPN_RX_LB4;

        u2_s_tydc_xpn_rx_sts |= (U2)((u1_g_XSpiSpnRx((U1)XSPI_SPN_RX_LB5, 
                                    &u1_sp_tydc_xpn_lb5[0], 
                                    (U1)XSPI_SPN_NB_LB5) & (U1)TRUE)) <<  TYDC_XPN_RX_LB5;

        u2_s_tydc_xpn_rx_sts |= (U2)((u1_g_XSpiSpnRx((U1)XSPI_SPN_RX_LB6, 
                                    &u1_sp_tydc_xpn_lb6[0], 
                                    (U1)XSPI_SPN_NB_LB6) & (U1)TRUE)) <<  TYDC_XPN_RX_LB6;

        u2_s_tydc_xpn_rx_sts |= (U2)((u1_g_XSpiSpnRx((U1)XSPI_SPN_RX_HUD, 
                                    &u1_sp_tydc_xpn_hud[0], 
                                    (U1)XSPI_SPN_NB_HUD) & (U1)TRUE)) <<  TYDC_XPN_RX_HUD;

        u2_s_tydc_xpn_rx_sts |= (U2)((u1_g_XSpiSpnRx((U1)XSPI_SPN_RX_DISP, 
                                    &u1_sp_tydc_xpn_disp[0], 
                                    (U1)XSPI_SPN_NB_DISP) & (U1)TRUE)) <<  TYDC_XPN_RX_DISP;

        u2_s_tydc_xpn_rx_sts |= (U2)((u1_g_Product((U1)PRDCT_PN_ECU_PN,
                                    &u1_sp_tydc_xpn_ecu_pn[0], 
                                    (U1)PRDCT_ECU_PN_NBYTE) & (U1)TRUE)) <<  TYDC_XPN_RX_ECU_PN;

        u2_s_tydc_xpn_rx_sts |= (U2)((u1_g_Product((U1)PRDCT_PN_SERI_N, 
                                    &u1_sp_tydc_xpn_seri_n[0], 
                                    (U1)PRDCT_SERI_N_NBYTE) & (U1)TRUE)) <<  TYDC_XPN_RX_SERI_N;

        u2_s_tydc_xpn_rx_sts |= (U2)((u1_g_XSpiSpnRx((U1)XSPI_SPN_RX_HUD_SERI_N,
                                    &u1_sp_tydc_xpn_hud_seri_n[0], 
                                    (U1)XSPI_SPN_NB_HUD_SERI_N) & (U1)TRUE)) <<  TYDC_XPN_RX_HUD_SERI_N;

    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANXpnTx(const U1 u1_a_XPN, U1 * u1_ap_xpn, const U1 u1_a_NBYTE)                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANXpnTx(const U1 u1_a_XPN, U1 * u1_ap_xpn, const U1 u1_a_NBYTE)
{
    static const U1           u1_sp_TYDC_XPN_NB_MIN[] = {
        (U1)TYDC_XPN_NB_LB3,
        (U1)TYDC_XPN_NB_LB4,
        (U1)TYDC_XPN_NB_LB5,
        (U1)TYDC_XPN_NB_LB6,
        (U1)TYDC_XPN_NB_HUD,
        (U1)TYDC_XPN_NB_DISP,
        (U1)TYDC_XPN_NB_ECU_PN,
        (U1)TYDC_XPN_NB_SERI_N,
        (U1)TYDC_XPN_NB_HUD_SERI_N
    };

    static const U1 * const   u1p_sp_TYDC_XPN_SRC[] = {
        (const U1 *)&u1_sp_tydc_xpn_lb3,
        (const U1 *)&u1_sp_tydc_xpn_lb4,
        (const U1 *)&u1_sp_tydc_xpn_lb5,
        (const U1 *)&u1_sp_tydc_xpn_lb6,
        (const U1 *)&u1_sp_tydc_xpn_hud,
        (const U1 *)&u1_sp_tydc_xpn_disp,
        (const U1 *)&u1_sp_tydc_xpn_ecu_pn,
        (const U1 *)&u1_sp_tydc_xpn_seri_n,
        (const U1 *)&u1_sp_tydc_xpn_hud_seri_n
    };

    const U1 *                u1_tp_SRC;
    U1                        u1_t_nb_min;
    U1                        u1_t_sts_chk;
    U1                        u1_t_ret;

    if((u1_a_XPN  >  (U1)TYDC_XPN_RX_HUD_SERI_N) ||
       (u1_ap_xpn == vdp_PTR_NA         )){
        
        u1_t_ret = (U1)TYDC_XPN_INVALID;

    }
    else{

        u1_t_sts_chk = (U1)((u2_s_tydc_xpn_rx_sts >> u1_a_XPN) & (U2)TRUE);
        u1_t_nb_min  = u1_sp_TYDC_XPN_NB_MIN[u1_a_XPN];

        if((u1_t_sts_chk == (U1)TRUE) &&
           (u1_a_NBYTE   >= u1_t_nb_min)){

            u1_tp_SRC = u1p_sp_TYDC_XPN_SRC[u1_a_XPN];
            vd_g_MemcpyU1(u1_ap_xpn, &u1_tp_SRC[0], (U4)u1_t_nb_min);
            u1_t_ret = (U1)TYDC_XPN_VALID;

        }
        else if((u2_s_tydc_xpn_dgon_cnt <  (U2)TYDC_XPN_DIAGON_TOUT    ) ||
                (u2_s_tydc_xpn_dgon_cnt >= (U2)TYDC_XPN_DIAGON_TOUT_INI)){

            u1_t_ret = (U1)TYDC_XPN_UNKNOWN;
            
        }
        else{
        
            u1_t_ret = (U1)TYDC_XPN_INVALID;

        }
    }
    
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    01/08/2025  TeN      New.                                                                                               */
/*  1.0.1    03/28/2025  TeN      Change the timeout duration from 5000ms to 10000ms.                                                */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  BEV-1    03/26/2026  NY       Added logic related to DID-F1A0.                                                                   */
/*                                Change the timeout duration from 10000ms to 5000ms.                                                */
/*  BEV-2    04/02/2026  TK       Change EOM monitoring target from IGN to Diag Power.                                               */
/*                                                                                                                                   */
/*  * TeN = Tetsushi Nakano, DENSO-TECHNO                                                                                            */
/*  * NY  = Nobuhiro Yoshiyasu, DENSO-TECHNO                                                                                         */
/*  * TK  = Tamao Kamiya, Denso Techno                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/
