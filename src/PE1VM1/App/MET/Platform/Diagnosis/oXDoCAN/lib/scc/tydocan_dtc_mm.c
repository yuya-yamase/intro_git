/* 1.9.3 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Diagnosis on Can for Toyota MET/HUD based on AUBIST/DEM, DCM                                                                     */
/*  Multi Media Commmunication Failure                                                                                               */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_DTC_MM_C_MAJOR                   (1U)
#define TYDOCAN_DTC_MM_C_MINOR                   (9U)
#define TYDOCAN_DTC_MM_C_PATCH                   (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxdocan_cfg_private.h"
#include "tydocan_dtc_cfg_private.h"
#include "tydocan_dtc_mm_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (TYDOCAN_DTC_MM_C_MAJOR != OXDOCAN_CFG_H_MAJOR)
#error "tydocan_dtc_mm.c and oxdocan_cfg_private.h : source and header files are inconsistent!"
#endif

#if (TYDOCAN_DTC_MM_C_MAJOR != TYDOCAN_DTC_CFG_H_MAJOR)
#error "tydocan_dtc_mm.c and tydocan_dtc_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((TYDOCAN_DTC_MM_C_MAJOR != TYDOCAN_DTC_MM_H_MAJOR) || \
     (TYDOCAN_DTC_MM_C_MINOR != TYDOCAN_DTC_MM_H_MINOR) || \
     (TYDOCAN_DTC_MM_C_PATCH != TYDOCAN_DTC_MM_H_PATCH))
#error "tydocan_dtc_mm.c and tydocan_dtc_mm.h : source and header files are inconsistent!"
#endif

#if ((TYDOCAN_DTC_MM_C_MAJOR != TYDOCAN_DTC_MM_CFG_H_MAJOR) || \
     (TYDOCAN_DTC_MM_C_MINOR != TYDOCAN_DTC_MM_CFG_H_MINOR) || \
     (TYDOCAN_DTC_MM_C_PATCH != TYDOCAN_DTC_MM_CFG_H_PATCH))
#error "tydocan_dtc_mm.c and tydocan_dtc_mm_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_DTC_MM_LSB_SUP_CHK                  (16U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (OXDC_MAIN_TICK != OXCAN_MAIN_TICK)
#error "tydocan_dtc_mm.c : OXDC_MAIN_TICK shall be equal to OXCAN_MAIN_TICK"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4          u4_s_tydc_dtc_mm_log_bk  __attribute__((section(".bss_BACK")));
static U4          u4_s_tydc_dtc_mm_log_rx;
static U4          u4_s_tydc_dtc_mm_acc_elpsd;

static U2          u2_s_tydc_dtc_mm_cyctim;

static U1          u1_sp_tydc_dtc_mm_tr_chk[TYDC_DTC_MM_NUM_RX];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1      u1_s_TydcDtcMMPduRx(const ST_TYDC_DTC_COM_RX * st_ap_COM_RX, const U2 u2_a_AOM_TOUT, const U1 u1_a_IF_BIT);
static U1      u1_s_TydcDtcMMRxTOchk_B132X(const U4 u4_a_SUP, const U4 u4_a_UNK, const U4 u4_a_RXTO);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANDtcMMInit(const U1 u1_a_BR_INIT)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANDtcMMInit(const U1 u1_a_BR_INIT)
{
    U4                         u4_t_lpcnt;

    if(u1_a_BR_INIT == (U1)FALSE){

        u4_s_tydc_dtc_mm_log_rx = u4_s_tydc_dtc_mm_log_bk;

        u1_sp_tydc_dtc_mm_tr_chk[TYDC_DTC_MM_RX_B1321] = (U1)OXDC_DTC_TR_UNK;
   }
    else{

        u4_s_tydc_dtc_mm_log_bk = (U4)0U;
        u4_s_tydc_dtc_mm_log_rx = (U4)0U;

        u1_sp_tydc_dtc_mm_tr_chk[TYDC_DTC_MM_RX_B1321] = (U1)OXDC_DTC_TR_N_A;
    }

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_TYDC_DTC_MM_NUM_PDU_RX; u4_t_lpcnt++){
        u2_gp_tydc_dtc_mm_rxc_st[u4_t_lpcnt] = (U2)0U;
        u1_gp_tydc_dtc_mm_rx_cnt[u4_t_lpcnt] = (U1)OXCAN_RXD_EVC_UNK;
    }

    u4_s_tydc_dtc_mm_acc_elpsd  = (U4)0U;
    u2_s_tydc_dtc_mm_cyctim     = (U2)U2_MAX;
}
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANDtcMMMainTask(const U1 u1_a_EOM, const U2 u2_a_TSLOT)                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANDtcMMMainTask(const U1 u1_a_EOM, const U2 u2_a_TSLOT)
{
    static const U1            u1_s_TYDC_DTC_MM_IF_BIT = (U1)0x00U;  /* bit#0  B1321 */

    U4                         u4_t_lpcnt;

    U2                         u2_t_smpl_chk;
    U1                         u1_t_sup_chk;
    U1                         u1_t_if_bit;
    U1                         u1_t_tr_chk;
    U1                         u1_t_acc_on;

    u2_s_tydc_dtc_mm_cyctim++;  /* u2_s_tydc_dtc_mm_cyctim is rolling counter so wrap-around is initentional */

    u1_t_if_bit = u1_s_TYDC_DTC_MM_IF_BIT;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)TYDC_DTC_MM_NUM_RX; u4_t_lpcnt++){

        u2_t_smpl_chk = u2_a_TSLOT & st_gp_TYDC_DTC_MM_RX[u4_t_lpcnt].u2_smpl_tslot;
        if(u2_t_smpl_chk != (U2)0U){

            u1_t_tr_chk = u1_s_TydcDtcMMPduRx(&st_gp_TYDC_DTC_MM_RX[u4_t_lpcnt],
                                              u2_gp_TYDC_DTC_MM_AOM_TOUT[u4_t_lpcnt],
                                              (u1_t_if_bit & (U1)0x01U));
            if(st_gp_TYDC_DTC_MM_RX[u4_t_lpcnt].fp_u1_SUP != vdp_PTR_NA){
                u1_t_sup_chk = (*st_gp_TYDC_DTC_MM_RX[u4_t_lpcnt].fp_u1_SUP)();
                if(u1_t_sup_chk != (U1)TRUE){
                    u1_t_tr_chk = (U1)OXDC_DTC_TR_N_A;
                }
            }

            u1_sp_tydc_dtc_mm_tr_chk[u4_t_lpcnt] = u1_t_tr_chk;
        }

        u1_t_if_bit >>= 1U;
    }
    u4_s_tydc_dtc_mm_log_bk = u4_s_tydc_dtc_mm_log_rx;

    u1_t_acc_on = u1_g_TyDoCANDtcMMCfgAccOn(u1_a_EOM);
    if(u1_t_acc_on != (U1)TRUE){
        u4_s_tydc_dtc_mm_acc_elpsd = (U4)0U;
    }
    else if(u4_s_tydc_dtc_mm_acc_elpsd < (U4)U4_MAX){
        u4_s_tydc_dtc_mm_acc_elpsd++;
    }
    else{
        /* Do Nothing */
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANDtcTrchk_B1321(const U2 u2_a_ELPSD)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDtcTrchk_B1321(const U2 u2_a_ELPSD)
{
    return(u1_sp_tydc_dtc_mm_tr_chk[TYDC_DTC_MM_RX_B1321]);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_TydcDtcMMPduRx(const ST_TYDC_DTC_COM_RX * st_ap_COM_RX, const U2 u2_a_AOM_TOUT, const U1 u1_a_IF_BIT)        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_TydcDtcMMPduRx(const ST_TYDC_DTC_COM_RX * st_ap_COM_RX, const U2 u2_a_AOM_TOUT, const U1 u1_a_IF_BIT)
{
    static U1 ( * const        fp_sp_u1_TYDC_DTC_MM_RXTO_CHK[])(const U4 u4_a_SUP, const U4 u4_a_UNK, const U4 u4_a_RXTO) = {
        &u1_s_TydcDtcMMRxTOchk_B132X
    };

    const ST_TYDC_DTC_PDU_RX * st_tp_PDU_RX;

    U4                         u4_t_lpcnt;
    U4                         u4_t_lpend;
    U4                         u4_t_log_bit;
    U4                         u4_t_sup_chk;
    U4                         u4_t_unk_chk;
    U4                         u4_t_rxto_chk;
    U4                         u4_t_aom_tout;

    U2                         u2_t_rxc_inc;

    U1                         u1_t_rxc_nex;
    U1                         u1_t_rxc_las;

    U1                         u1_t_rx_stat;

    u4_t_lpcnt    = (U4)st_ap_COM_RX->u1_pdu_begin;
    u4_t_lpend    = u4_t_lpcnt + (U4)st_ap_COM_RX->u1_num_pdu;
    if(u4_t_lpend > (U4)u1_g_TYDC_DTC_MM_NUM_PDU_RX){
        u4_t_lpend = (U4)u1_g_TYDC_DTC_MM_NUM_PDU_RX;
    }

    u4_t_log_bit  = (U4)0x00000001U << st_ap_COM_RX->u1_log_bit;
    u4_t_sup_chk  = (U4)0U;
    u4_t_unk_chk  = (U4)0U;
    u4_t_rxto_chk = (U4)0U;

    while(u4_t_lpcnt < u4_t_lpend){

        st_tp_PDU_RX = &st_gp_TYDC_DTC_MM_PDU_RX[u4_t_lpcnt];

        u1_t_rxc_nex = u1_g_oXCANRxdEvcnt(st_tp_PDU_RX->u2_pdu_idx);
        u1_t_rxc_las = u1_gp_tydc_dtc_mm_rx_cnt[u4_t_lpcnt];
        if((u1_t_rxc_nex >  (U1)OXCAN_RXD_EVC_MAX) ||
           (u1_t_rxc_las >  (U1)OXCAN_RXD_EVC_MAX)){

            u2_gp_tydc_dtc_mm_rxc_st[u4_t_lpcnt] = u2_s_tydc_dtc_mm_cyctim;
            u1_gp_tydc_dtc_mm_rx_cnt[u4_t_lpcnt] = u1_t_rxc_nex;
        }
        else{

            u2_t_rxc_inc = (U2)((U2)u1_t_rxc_nex - (U2)u1_t_rxc_las) & (U2)OXCAN_RXD_EVC_MAX;
            if(u2_t_rxc_inc >= st_tp_PDU_RX->u2_rxc_min){
                u4_s_tydc_dtc_mm_log_rx |= ((u4_t_log_bit << TYDC_DTC_MM_LSB_SUP_CHK) | u4_t_log_bit);
            }

            u2_t_rxc_inc = u2_s_tydc_dtc_mm_cyctim - u2_gp_tydc_dtc_mm_rxc_st[u4_t_lpcnt];
            if(u2_t_rxc_inc >= st_tp_PDU_RX->u2_rxc_cyc){
                u2_gp_tydc_dtc_mm_rxc_st[u4_t_lpcnt] = u2_s_tydc_dtc_mm_cyctim;
                u1_gp_tydc_dtc_mm_rx_cnt[u4_t_lpcnt] = u1_t_rxc_nex;
            }
        }

        u1_t_rx_stat  = u1_g_oXCANRxdStat(st_tp_PDU_RX->u2_pdu_idx, st_tp_PDU_RX->u2_sys_chk, st_tp_PDU_RX->u2_rx_tout);
        u4_t_aom_tout = (U4)st_tp_PDU_RX->u2_rx_tout + (U4)u2_a_AOM_TOUT;
        if((u1_t_rx_stat               < (U1)OXCAN_RX_RXST_TOE) ||
           (u4_s_tydc_dtc_mm_acc_elpsd < u4_t_aom_tout        )){
            u4_t_unk_chk  |= u4_t_log_bit;
        }
        else if(u1_t_rx_stat >= ((U1)OXCAN_RX_RXST_TOE | (U1)COM_TIMEOUT)){
            u4_t_rxto_chk |= u4_t_log_bit;
        }
        else{
            /* Do nothing */
        }

        u4_t_sup_chk  |= u4_t_log_bit;
        u4_t_log_bit <<= 1U;
        u4_t_lpcnt++;
    }

    u4_t_sup_chk &= (u4_s_tydc_dtc_mm_log_rx >> TYDC_DTC_MM_LSB_SUP_CHK);

    return((*fp_sp_u1_TYDC_DTC_MM_RXTO_CHK[u1_a_IF_BIT])(u4_t_sup_chk, u4_t_unk_chk, u4_t_rxto_chk));
}
/*===================================================================================================================================*/
/*  static U1      u1_s_TydcDtcMMRxTOchk_B132X(const U4 u4_a_SUP, const U4 u4_a_UNK, const U4 u4_a_RXTO)                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_TydcDtcMMRxTOchk_B132X(const U4 u4_a_SUP, const U4 u4_a_UNK, const U4 u4_a_RXTO)
{
    U4                         u4_t_unk_chk;
    U4                         u4_t_rxto_chk;
    U1                         u1_t_tr_chk;

    u4_t_unk_chk  = u4_a_SUP & u4_s_tydc_dtc_mm_log_rx;
    u4_t_rxto_chk = u4_a_RXTO & u4_t_unk_chk;
    u4_s_tydc_dtc_mm_log_rx &= ((U4)U4_MAX ^ u4_t_rxto_chk);

    if(u4_a_SUP == (U4)0U){
        u1_t_tr_chk = (U1)OXDC_DTC_TR_N_A;
    }
    else if(u4_t_unk_chk == (U4)0U){
        u1_t_tr_chk = (U1)OXDC_DTC_TR_UNK;
    }
    else if(u4_t_rxto_chk == (U4)0U){
        u1_t_tr_chk = (U1)OXDC_DTC_TR_INA;
    }
    else{
        u1_t_tr_chk = (U1)OXDC_DTC_TR_ACT;
    }

    return(u1_t_tr_chk);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     8/ 8/2019  TN       New.                                                                                               */
/*  1.1.0    10/17/2019  TN       The inital value of u1_gp_tydc_dtc_mm_rx_cnt[] was changed from TYCAN_COMRX_RXEV_CNT_INIT to       */
/*                                TYCAN_COMRX_RXEV_CNT_INACT.                                                                        */
/*  1.2.0    11/ 8/2019  TN       Bug Fix : DTC detection was performed even though the condition was not met.                       */
/*  1.3.0    11/22/2019  TN       Improvement : The bit mask was performed because of the change in u1_g_TyCANComrxRxStat.           */
/*  1.4.0     2/24/2020  HK       Bug Fix : Reference array was changed from st_gp_TYDC_DTC_PDU_RX to st_gp_TYDC_DTC_MM_PDU_RX.      */
/*  1.5.0     9/ 4/2020  TN       Improvement : u1_g_TyDoCANDtcMMCfgAccOn() -> u1_g_TyDoCANDtcMMCfgAccOn(U1)                         */
/*  1.6.0    12/22/2020  TN       ST_TYDC_DTC_PDU_RX.u2_rxc_min was defined in order to support CXPI.                                */
/*  1.7.0     2/19/2021  TN       ST_TYDC_DTC_PDU_RX.u2_rxc_cyc was defined in order to CXPI Rx timeout activiation                  */
/*                                DTC B129D, B129E were supported.                                                                   */
/*  1.8.0     3/12/2021  TN       u2_sp_TYDC_DTC_MM_LOG_MASK[] and u2_gp_TYDC_DTC_MM_AOM_TOUT[] were defined for B129D/B129E.        */
/*  1.9.0     4/ 2/2021  TN       u1_s_TydcDtcMMTrchk_B129X and u1_s_TydcDtcMMTrchk_B132X were implemented.                          */
/*                       HK       QAC warnigs were fixed.                                                                            */
/*  1.9.1     6/ 9/2021  TN       QAC warnigs were fixed.                                                                            */
/*  1.9.2     9/ 9/2021  TN       NULL->vdp_PTR_NA.                                                                                  */
/*                       HK       QAC warnigs were fixed.                                                                            */
/*  1.9.3    11/23/2023  TI       B129D, B129E, and B1326 were deleted.                                                              */
/*                                                                                                                                   */
/*  * TN = Takashi Nagai, DENSO                                                                                                      */
/*  * HK = Hayato Kanamori, DENSO Create                                                                                             */
/*  * TI = Tomoko Inuzuka, DENSO                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
