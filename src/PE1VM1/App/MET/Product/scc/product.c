/* 2.1.4 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Product Number                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define PRODUCT_C_MAJOR                          (2)
#define PRODUCT_C_MINOR                          (1)
#define PRODUCT_C_PATCH                          (4)
 
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "product_cfg_private.h"
#include "memfill_u4.h"   /* BEV Diag provisionally *//* Temporary implementation for the ECV phase; will be fixed in a later phase. */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((PRODUCT_C_MAJOR != PRODUCT_H_MAJOR) || \
     (PRODUCT_C_MINOR != PRODUCT_H_MINOR) || \
     (PRODUCT_C_PATCH != PRODUCT_H_PATCH))
#error "product.c and product.h : source and header files are inconsistent!"
#endif

#if ((PRODUCT_C_MAJOR != PRODUCT_CFG_H_MAJOR) || \
     (PRODUCT_C_MINOR != PRODUCT_CFG_H_MINOR) || \
     (PRODUCT_C_PATCH != PRODUCT_CFG_H_PATCH))
#error "product.c and product_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define PRDCT_NVM_NWORD                          (6U)  /* 24 bytes */
#define PRDCT_NVM_WO_ECU_PN                      (0U)
#define PRDCT_NVM_WO_SERI_N                      (3U)

#define PRDCT_NVM_NW_3                           (3U)
#define PRDCT_NVM_WO_0                           (0U)
#define PRDCT_NVM_WO_1                           (1U)
#define PRDCT_NVM_WO_2                           (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_sp_prdct_nvm_last[PRDCT_NVM_NWORD];
static U1      u1_s_prdct_nvm_syn_cnt;
static U1      u1_s_prdct_las_chk;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static         U1  u1_s_Prdct_NvmSynLast(const U2 u2_a_NID, U4 * u4_ap_last);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U1      u1_g_Product(const U1 u1_a_PN, U1 * u1_ap_pn, const U1 u1_a_NBYTE)                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void  vd_g_ProductInit(void)
{
    U4                        u4_t_lpcnt;
    U1                        u1_t_ecu_chk;
    U1                        u1_t_ser_chk;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)PRDCT_NVM_NWORD; u4_t_lpcnt++){
        u4_sp_prdct_nvm_last[u4_t_lpcnt] = (U4)0U;
    }

    u1_t_ecu_chk = u1_s_Prdct_NvmSynLast(u2_gp_PRDCT_NID_B12[PRDCT_NID_ECU_PN],
                                         &u4_sp_prdct_nvm_last[PRDCT_NVM_WO_ECU_PN]);

    u1_t_ser_chk = u1_s_Prdct_NvmSynLast(u2_gp_PRDCT_NID_B12[PRDCT_NID_SERI_N],
                                           &u4_sp_prdct_nvm_last[PRDCT_NVM_WO_SERI_N]);

    u1_s_prdct_nvm_syn_cnt = (U1)U1_MAX;
    u1_s_prdct_las_chk     = ((U1)(u1_t_ecu_chk << PRDCT_PN_ECU_PN) |
                              (U1)(u1_t_ser_chk << PRDCT_PN_SERI_N) |
                              (U1)((U1)0x01U    << PRDCT_PN_SOFT_N) |
                              (U1)((U1)0x01U    << PRDCT_PN_REL_VN));
}
/*===================================================================================================================================*/
/*  void  vd_g_ProductNvmSynTask(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void  vd_g_ProductNvmSynTask(void)
{
    static const U1           u1_sp_PRODUCT_LAS_CHK[PRDCT_NUM_NID] = {
        (U1)0x01U << PRDCT_PN_ECU_PN,
        (U1)0x01U << PRDCT_PN_SERI_N
    };

    U2                        u2_t_next;
    U2                        u2_t_woff;
    U1                        u1_t_las_chk;

    u2_t_next = (U2)u1_s_prdct_nvm_syn_cnt + (U2)1U;
    if(u2_t_next >= (U2)PRDCT_NUM_NID){
        u2_t_next = (U2)0U;
    }
    u1_s_prdct_nvm_syn_cnt = (U1)u2_t_next;

    u2_t_woff    = u2_t_next * (U2)PRDCT_NVM_NW_3;
    u1_t_las_chk = u1_s_Prdct_NvmSynLast(u2_gp_PRDCT_NID_B12[u2_t_next], &u4_sp_prdct_nvm_last[u2_t_woff]);

    if(u1_t_las_chk == (U1)TRUE){
        u1_t_las_chk = u1_s_prdct_las_chk | u1_sp_PRODUCT_LAS_CHK[u2_t_next];
    }
    else{
        u1_t_las_chk = u1_s_prdct_las_chk & ((U1)U1_MAX ^ u1_sp_PRODUCT_LAS_CHK[u2_t_next]);
    }

    u1_s_prdct_las_chk = ((U1)((U1)0x01U << PRDCT_PN_SOFT_N) |
                          (U1)((U1)0x01U << PRDCT_PN_REL_VN) |
                          u1_t_las_chk);
}
/*===================================================================================================================================*/
/*  U1      u1_g_Product(const U1 u1_a_PN, U1 * u1_ap_pn, const U1 u1_a_NBYTE)                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_Product(const U1 u1_a_PN, U1 * u1_ap_pn, const U1 u1_a_NBYTE)
{
    static const U1           u1_sp_PRDCT_NB_MIN[] = {
        (U1)PRDCT_ECU_PN_NBYTE,
        (U1)PRDCT_SOFT_N_NBYTE,
        (U1)PRDCT_SERI_N_NBYTE,
        (U1)PRDCT_REL_VN_NBYTE
    };

    static const U1 * const   u1p_sp_PRDCT_SRC[] = {
        (const U1 *)&u4_sp_prdct_nvm_last[PRDCT_NVM_WO_ECU_PN],
        &u1_gp_PRDCT_SOFT_N[0],
        (const U1 *)&u4_sp_prdct_nvm_last[PRDCT_NVM_WO_SERI_N],
        &u1_gp_PRDCT_REL_VN[0]
    };

    const U1 *                u1_tp_SRC;

    U4                        u4_t_lpcnt;
    U1                        u1_t_nb_min;
    U1                        u1_t_las_chk;

    if((u1_a_PN  >  (U1)PRDCT_PN_REL_VN) ||
       (u1_ap_pn == vdp_PTR_NA         )){

        u1_t_las_chk = (U1)FALSE;
    }
    else{

        u1_t_las_chk = (u1_s_prdct_las_chk >> u1_a_PN) & (U1)TRUE;

        u1_t_nb_min  = u1_sp_PRDCT_NB_MIN[u1_a_PN];
        if((u1_t_las_chk == (U1)TRUE   ) &&
           (u1_a_NBYTE   >= u1_t_nb_min)){
            u1_tp_SRC = u1p_sp_PRDCT_SRC[u1_a_PN];
            for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_t_nb_min; u4_t_lpcnt++){
                u1_ap_pn[u4_t_lpcnt] = u1_tp_SRC[u4_t_lpcnt];
            }
        }
    }

    return(u1_t_las_chk);
}
/*===================================================================================================================================*/
/*  void      vd_g_Product_LB2_SoftNumber(U1 * u1_ap_pn, const U1 u1_a_NBYTE)                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Product_LB2_SoftNumber(U1 * u1_ap_pn, const U1 u1_a_NBYTE)
{
     if(u1_a_NBYTE == (U1)PRDCT_SOFT_N_CONST_NBYTE){
        u1_ap_pn[PRDCT_SOFT_N_01] = u1_PRDCT_MCUID0001_MCUID1;
        u1_ap_pn[PRDCT_SOFT_N_02] = u1_PRDCT_MCUID0002_MCUID2;
        u1_ap_pn[PRDCT_SOFT_N_03] = u1_PRDCT_MCUID0003_MCUID3;
        u1_ap_pn[PRDCT_SOFT_N_04] = u1_PRDCT_MCUID0004_MCUID4;
        u1_ap_pn[PRDCT_SOFT_N_05] = u1_PRDCT_MCUID0005_MCUID5;
        u1_ap_pn[PRDCT_SOFT_N_06] = u1_PRDCT_MCUID0006_MCUID6;
        u1_ap_pn[PRDCT_SOFT_N_07] = u1_PRDCT_MCUID0007_MCUID7;
        u1_ap_pn[PRDCT_SOFT_N_08] = u1_PRDCT_MCUID0008_MCUID8;
        u1_ap_pn[PRDCT_SOFT_N_09] = u1_PRDCT_MCUID0009_MCUID9;
        u1_ap_pn[PRDCT_SOFT_N_10] = u1_PRDCT_MCUID0010_MCUID10;
        u1_ap_pn[PRDCT_SOFT_N_11] = u1_PRDCT_MCUID0011_MCUID11;
        u1_ap_pn[PRDCT_SOFT_N_12] = u1_PRDCT_MCUID0012_MCUID12;
     }
}
/*===================================================================================================================================*/
/*  static U1      u1_s_Prdct_NvmSynLast(const U2 u2_a_NID, U4 * u4_ap_last)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_Prdct_NvmSynLast(const U2 u2_a_NID, U4 * u4_ap_last)
{
#if 0   /* BEV Diag provisionally *//* Temporary implementation for the ECV phase; will be fixed in a later phase. */
    U4                 u4_tp_src[PRDCT_NVM_NW_3];
    U1                 u1_t_nvm_chk;
    U1                 u1_t_las_chk;

    u1_t_nvm_chk = u1_g_Nvmc_ReadOthrwithSts(u2_a_NID, (U2)PRDCT_NVM_NB_12, (U1 *)&u4_tp_src[0]);
    if((u1_t_nvm_chk <  (U1)NVMC_STATUS_KIND_NG ) &&
       (u1_t_nvm_chk != (U1)NVMC_STATUS_ERRCOMP ) &&
       (u1_t_nvm_chk != (U1)NVMC_STATUS_CACHE_NG)){
        
        u4_ap_last[PRDCT_NVM_WO_0] = u4_tp_src[PRDCT_NVM_WO_0];
        u4_ap_last[PRDCT_NVM_WO_1] = u4_tp_src[PRDCT_NVM_WO_1];
        u4_ap_last[PRDCT_NVM_WO_2] = u4_tp_src[PRDCT_NVM_WO_2];

        u1_t_las_chk = (U1)TRUE;
    }
    else{
        u1_t_las_chk = (U1)FALSE;
    }

    return(u1_t_las_chk);
#else   /* BEV Diag provisionally *//* Temporary implementation for the ECV phase; will be fixed in a later phase. */
    vd_g_MemfillU4(&u4_ap_last[0], (U4)U4_MAX, (U4)PRDCT_NVM_NW_3);

    return((U1)TRUE);
#endif  /* BEV Diag provisionally *//* Temporary implementation for the ECV phase; will be fixed in a later phase. */
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     4/24/2020  TN       New.                                                                                               */
/*  1.1.0     8/12/2020  YW       DID 0xF181 Software Number : Move ECU Number from NVM to CodeFlash.                                */
/*  2.0.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*  2.1.1     9/14/2022  MY       PRDCT_ECU_PN_NBYTE 10 -> 12.                                                                       */
/*  2.1.2     2/23/2024  TK       Add function vd_g_Product_LB2_SoftNumber for Phase6Diag                                            */
/*  2.1.3     4/18/2024  TN(DT)   Change for MET19PFV3-21081.                                                                        */
/*  2.1.4     6/27/2024  TN(DT)   Delete Calibration Guard Process.                                                                  */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  BEV-1     3/26/2026  NY       Temporary implementation for the ECV phase.                                                        */
/*                                                                                                                                   */
/*  * TN     = Takashi Nagai, DENSO                                                                                                  */
/*  * YW     = Yuta Wanibe, DENSO TECHNO                                                                                             */
/*  * TA(M)  = Teruyuki Anjima, NTT Data MSE                                                                                         */
/*  * MY     = Mizuki Yamasaki, DENSO TECHNO                                                                                         */
/*  * TK     = Toru Kamishina, DENSO TECHNO                                                                                          */
/*  * TN(DT) = Tetsushi Nakano, DENSO TECHNO                                                                                         */
/*  * NY     = Nobuhiro Yoshiyasu, DENSO TECHNO                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/
