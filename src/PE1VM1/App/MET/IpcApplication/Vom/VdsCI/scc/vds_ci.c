/* 2.4.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Vehicle Driving Support Configuration/Calibration Interface                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDS_CI_C_MAJOR                         (2)
#define VDS_CI_C_MINOR                         (4)
#define VDS_CI_C_PATCH                         (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "vds_ci_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((VDS_CI_C_MAJOR != VDS_CI_H_MAJOR) || \
     (VDS_CI_C_MINOR != VDS_CI_H_MINOR) || \
     (VDS_CI_C_PATCH != VDS_CI_H_PATCH))
#error "vds_ci.c and vds_ci.h : source and header files are inconsistent!"
#endif

#if ((VDS_CI_C_MAJOR != VDS_CI_CFG_H_MAJOR) || \
     (VDS_CI_C_MINOR != VDS_CI_CFG_H_MINOR) || \
     (VDS_CI_C_PATCH != VDS_CI_CFG_H_PATCH))
#error "vds_ci.c and vds_ci_cfg_private.h : source and header files are inconsistent!"
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
static U1                  u1_s_vds_ci_task_cyccnt;

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
/*  void    vd_g_VdsCIInit(void)                                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VdsCIInit(void)
{
    U4                u4_t_lpcnt;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_VDS_CI_NUM_CH; u4_t_lpcnt++){
        st_gp_vds_ci_ch[u4_t_lpcnt].u2_tocnt  = (U2)U2_MAX;
        st_gp_vds_ci_ch[u4_t_lpcnt].u1_req_tx = (U1)VDS_CI_OPT_TX_INA;
        st_gp_vds_ci_ch[u4_t_lpcnt].u1_sel_rx = (U1)VDS_CI_OPT_INA;
    }
    u1_s_vds_ci_task_cyccnt = (U1)VDS_CI_TASK_NUM_SLOT;

    vd_g_VdsCICfgInit();
}
/*===================================================================================================================================*/
/*  void    vd_g_VdsCIMainTask(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VdsCIMainTask(void)
{
    U4                u4_t_lpcnt;

    U2                u2_t_tx_tout;
    U2                u2_t_tcycl;
    U2                u2_t_tslot;
    U2                u2_t_run;
    U1                u1_t_mask;
    U1                u1_t_mmsup;

    vd_g_VdsCICfgMainStart();

    if(u1_s_vds_ci_task_cyccnt >= (U1)VDS_CI_TASK_NUM_SLOT){
        u1_s_vds_ci_task_cyccnt = (U1)0U;
    }

    u2_t_tcycl = (U2)0x0001U << u1_s_vds_ci_task_cyccnt;
    u1_t_mmsup = u1_g_VdsCICfgGetMMEsopt();

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_VDS_CI_NUM_CH; u4_t_lpcnt++){

        u2_t_tx_tout = st_gp_VDS_CI_TRX[u4_t_lpcnt].u2_tx_tout;
        u2_t_tslot   = st_gp_VDS_CI_TRX[u4_t_lpcnt].u2_tslot;
        u1_t_mask    = st_gp_VDS_CI_TRX[u4_t_lpcnt].u1_tx_mask;
        u2_t_run     = u2_t_tslot & u2_t_tcycl;

        if((u1_t_mask == (U1)VDS_CI_TX_MASK_MM_ESOPT) && (u1_t_mmsup == (U1)TRUE)){
            /* Do Nothing */
        }
        else{
            if(st_gp_vds_ci_ch[u4_t_lpcnt].u2_tocnt < (U2)U2_MAX){
                st_gp_vds_ci_ch[u4_t_lpcnt].u2_tocnt++;
            }

            if(u2_t_run != (U2)0U){

                st_gp_vds_ci_ch[u4_t_lpcnt].u1_sel_rx = (*st_gp_VDS_CI_TRX[u4_t_lpcnt].fp_u1_RX)();
                if(st_gp_VDS_CI_TRX[u4_t_lpcnt].u2_tx_tout == (U2)VDS_CI_TYPE_SW){
                    if(st_gp_vds_ci_ch[u4_t_lpcnt].u2_tocnt <= st_gp_VDS_CI_TRX[u4_t_lpcnt].u2_holdtime){
                        /* Do Nothing */
                    }
                    else{
                        (*st_gp_VDS_CI_TRX[u4_t_lpcnt].fp_vd_TX)(st_gp_vds_ci_ch[u4_t_lpcnt].u1_req_tx, (U2)0U);
                    }
                }
                else if(st_gp_vds_ci_ch[u4_t_lpcnt].u2_tocnt >= u2_t_tx_tout){
                    st_gp_vds_ci_ch[u4_t_lpcnt].u2_tocnt  = (U2)0U;
                    st_gp_vds_ci_ch[u4_t_lpcnt].u1_req_tx = (U1)VDS_CI_OPT_INA;
                    (*st_gp_VDS_CI_TRX[u4_t_lpcnt].fp_vd_TX)((U1)VDS_CI_OPT_INA, (U2)U2_MAX);
                }
                else{
                    /* Do Nothing */
                }
            }

            if(st_gp_vds_ci_ch[u4_t_lpcnt].u1_req_tx < (U1)VDS_CI_OPT_UNK){

                u2_t_run = u2_t_tslot & (U2)VDS_CI_TASK_TX_RFRSH;

                if(st_gp_VDS_CI_TRX[u4_t_lpcnt].u2_tx_tout == (U2)VDS_CI_TYPE_SW){
                    if(st_gp_vds_ci_ch[u4_t_lpcnt].u2_tocnt <= st_gp_VDS_CI_TRX[u4_t_lpcnt].u2_holdtime){
                        /* Do Nothing */
                    }
                    else{
                        (*st_gp_VDS_CI_TRX[u4_t_lpcnt].fp_vd_TX)(st_gp_vds_ci_ch[u4_t_lpcnt].u1_req_tx, (U2)0U);
                    }
                }
                else if(st_gp_vds_ci_ch[u4_t_lpcnt].u2_tocnt >= u2_t_tx_tout){
                    st_gp_vds_ci_ch[u4_t_lpcnt].u2_tocnt  = (U2)0U;
                    st_gp_vds_ci_ch[u4_t_lpcnt].u1_req_tx = (U1)VDS_CI_OPT_INA;
                    (*st_gp_VDS_CI_TRX[u4_t_lpcnt].fp_vd_TX)((U1)VDS_CI_OPT_INA, (U2)U2_MAX);
                }
                else if(u2_t_run != (U2)0U){
                    (*st_gp_VDS_CI_TRX[u4_t_lpcnt].fp_vd_TX)(st_gp_vds_ci_ch[u4_t_lpcnt].u1_req_tx,
                                                            st_gp_vds_ci_ch[u4_t_lpcnt].u2_tocnt);
                }
                else{
                    /* Do Nothing */
                }
            }
        }
    }

    u1_s_vds_ci_task_cyccnt++; /* QAC over-detection */

    vd_g_VdsCICfgMainFinish();
}
/*===================================================================================================================================*/
/*  void    vd_g_VdsCIReqTx(const U1 u1_a_CH, const U1 u1_a_OPT)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VdsCIReqTx(const U1 u1_a_CH, const U1 u1_a_OPT)
{
    if(u1_a_CH < u1_g_VDS_CI_NUM_CH){

        if(u1_a_OPT != st_gp_vds_ci_ch[u1_a_CH].u1_req_tx){
            if(st_gp_vds_ci_ch[u1_a_CH].u2_tocnt >= st_gp_VDS_CI_TRX[u1_a_CH].u2_holdtime) {
                (*st_gp_VDS_CI_TRX[u1_a_CH].fp_vd_TX)(u1_a_OPT, (U2)0U);
                st_gp_vds_ci_ch[u1_a_CH].u2_tocnt  = (U2)0U;
            }
        }
        st_gp_vds_ci_ch[u1_a_CH].u1_req_tx = u1_a_OPT;
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_VdsCISelRx(const U1 u1_a_CH)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VdsCISelRx(const U1 u1_a_CH)
{
    U1                u1_t_opt;

    if(u1_a_CH < u1_g_VDS_CI_NUM_CH){
        u1_t_opt = st_gp_vds_ci_ch[u1_a_CH].u1_sel_rx;
    }
    else{
        u1_t_opt = (U1)VDS_CI_OPT_INA;
    }

    return(u1_t_opt);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.1.0     2/25/2020  TN       New.                                                                                               */
/*  1.1.0     7/20/2020  TH       Config for 800B CV-R                                                                               */
/*  2.1.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*  2.2.0    10/06/2022  TA(M)    Change hold time settigns to be configurable.                                                      */
/*                                Change to call fp_vd_TX in the send buffer even if u1_req_tx is 0.                                 */
/*  2.3.0    03/22/2024  SW       Add Transmission mask process for arbitration with Gateway.                                        */
/*  2.4.0     1/30/2025  KO       Setting for BEV System_Consideration_1.                                                            */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * TH   = Takahiro Hirano, Denso Techno                                                                                           */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * SW   = Shun Watanabe, Denso Techno                                                                                             */
/*  * KO   = Kazuto Oishi,  Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
