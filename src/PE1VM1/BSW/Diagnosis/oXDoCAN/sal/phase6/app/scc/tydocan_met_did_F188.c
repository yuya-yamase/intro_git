/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/* TyDoCAN Service Application Layer / DID 0xF188                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_MET_DID_F188_C_MAJOR             (1)
#define TYDOCAN_MET_DID_F188_C_MINOR             (0)
#define TYDOCAN_MET_DID_F188_C_PATCH             (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "oxdocan_saif.h"
#include "tydocan_sal.h"
#include "tydocan_xpn.h"

#include "memcpy_u1.h"
#include "memfill_u1.h"

#if 0    /* BEV Diag provisionally */
#include "product.h"
#endif    /* BEV Diag provisionally */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDC_SOC_LB_NUM                          (4U)       /*LB3-LB6                             */

#define OXDC_SOFT_N_NUM_SOC                      (64U)      /*16Byte * 4(SOC LB NUM)              */
#define OXDC_SOFT_N_NUM_CPU                      (6U)       /*LB1/LB2/LB3/LB4/LB5/LB6             */
#define OXDC_SOFT_N_LENGTH                       (16U)      /*The Length of Software Parts Number */
#define OXDC_SOFT_N_ECUID                        (0x01U)    /*METECU = 0x01 Fixed Value           */

#define OXDC_SOFT_N_LB1                          (3U)       /*Start address of LB1 SOFT NUMBER    */
#define OXDC_SOFT_N_LB2                          (20U)      /*Start address of LB2 SOFT NUMBER    */
#define OXDC_SOFT_N_LB3                          (37U)      /*Start address of LB3 SOFT NUMBER    */
#define OXDC_SOFT_N_LB4                          (54U)      /*Start address of LB4 SOFT NUMBER    */
#define OXDC_SOFT_N_LB5                          (71U)      /*Start address of LB5 SOFT NUMBER    */
#define OXDC_SOFT_N_LB6                          (88U)      /*Start address of LB6 SOFT NUMBER    */

#define OXDC_SOFT_N_LB1_RES13                    (15U)      /*LB1 Reserve Byte 13                 */
#define OXDC_SOFT_N_LB1_RES14                    (16U)      /*LB1 Reserve Byte 14                 */
#define OXDC_SOFT_N_LB1_RES15                    (17U)      /*LB1 Reserve Byte 15                 */
#define OXDC_SOFT_N_LB1_RES16                    (18U)      /*LB1 Reserve Byte 16                 */

#define OXDC_SOFT_N_LB2_RES13                    (32U)      /*LB2 Reserve Byte 13                 */
#define OXDC_SOFT_N_LB2_RES14                    (33U)      /*LB2 Reserve Byte 14                 */
#define OXDC_SOFT_N_LB2_RES15                    (34U)      /*LB2 Reserve Byte 15                 */
#define OXDC_SOFT_N_LB2_RES16                    (35U)      /*LB2 Reserve Byte 16                 */

#define OXDC_SOFT_N_LB3_RES13                    (49U)      /*LB3 Reserve Byte 13                 */
#define OXDC_SOFT_N_LB3_RES14                    (50U)      /*LB3 Reserve Byte 14                 */
#define OXDC_SOFT_N_LB3_RES15                    (51U)      /*LB3 Reserve Byte 15                 */
#define OXDC_SOFT_N_LB3_RES16                    (52U)      /*LB3 Reserve Byte 16                 */

#define OXDC_SOFT_N_LB4_RES13                    (66U)      /*LB4 Reserve Byte 13                 */
#define OXDC_SOFT_N_LB4_RES14                    (67U)      /*LB4 Reserve Byte 14                 */
#define OXDC_SOFT_N_LB4_RES15                    (68U)      /*LB4 Reserve Byte 15                 */
#define OXDC_SOFT_N_LB4_RES16                    (69U)      /*LB4 Reserve Byte 16                 */

#define OXDC_SOFT_N_LB5_RES13                    (83U)      /*LB5 Reserve Byte 13                 */
#define OXDC_SOFT_N_LB5_RES14                    (84U)      /*LB5 Reserve Byte 14                 */
#define OXDC_SOFT_N_LB5_RES15                    (85U)      /*LB5 Reserve Byte 15                 */
#define OXDC_SOFT_N_LB5_RES16                    (86U)      /*LB5 Reserve Byte 16                 */

#define OXDC_SOFT_N_LB6_RES13                    (100U)     /*LB6 Reserve Byte 13                 */
#define OXDC_SOFT_N_LB6_RES14                    (101U)     /*LB6 Reserve Byte 14                 */
#define OXDC_SOFT_N_LB6_RES15                    (102U)     /*LB6 Reserve Byte 15                 */
#define OXDC_SOFT_N_LB6_RES16                    (103U)     /*LB6 Reserve Byte 16                 */

#define OXDC_F188_LB3_LEN                        (12U)
#define OXDC_F188_LB4_LEN                        (12U)
#define OXDC_F188_LB5_LEN                        (12U)
#define OXDC_F188_LB6_LEN                        (12U)

#define OXDC_F188_UNKNOWN                        (0x3FU)
#define OXDC_F188_INVALID                        (0xFFU)
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
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANRebyId_F188(U1 * u1_ap_ans, const U2 u2_a_ELPSD)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANRebyId_F188(U1 * u1_ap_ans, const U2 u2_a_ELPSD)
{
#if 0    /* BEV Diag provisionally */
    U1                     u1_tp_pn_tx[OXDC_DATA_REA_ANS_NB_F188];
    U1                     u1_t_xpn_sts;

    vd_g_MemfillU1(u1_tp_pn_tx, (U1)OXDC_F188_INVALID, (U4)OXDC_DATA_REA_ANS_NB_F188);
    u1_tp_pn_tx[0]  = (U1)OXDC_SOFT_N_NUM_CPU;
    u1_tp_pn_tx[1]  = (U1)OXDC_SOFT_N_LENGTH;

    /*MCU Software Number Set */
    u1_tp_pn_tx[2]  = (U1)OXDC_SOFT_N_ECUID;            /* OXDC_SOFT_N_LB1 - 1 */

    (void)u1_g_Product((U1)PRDCT_PN_SOFT_N, &u1_tp_pn_tx[OXDC_SOFT_N_LB1], (U1)PRDCT_SOFT_N_NBYTE);

    u1_tp_pn_tx[OXDC_SOFT_N_LB1_RES13] = (U1)0U;
    u1_tp_pn_tx[OXDC_SOFT_N_LB1_RES14] = (U1)0U;
    u1_tp_pn_tx[OXDC_SOFT_N_LB1_RES15] = (U1)0U;
    u1_tp_pn_tx[OXDC_SOFT_N_LB1_RES16] = (U1)0U;

    u1_tp_pn_tx[19]  = (U1)OXDC_SOFT_N_ECUID;           /* OXDC_SOFT_N_LB2 - 1 */
    vd_g_Product_LB2_SoftNumber(&u1_tp_pn_tx[OXDC_SOFT_N_LB2], (U1)PRDCT_SOFT_N_CONST_NBYTE);

    u1_tp_pn_tx[OXDC_SOFT_N_LB2_RES13] = (U1)0U;
    u1_tp_pn_tx[OXDC_SOFT_N_LB2_RES14] = (U1)0U;
    u1_tp_pn_tx[OXDC_SOFT_N_LB2_RES15] = (U1)0U;
    u1_tp_pn_tx[OXDC_SOFT_N_LB2_RES16] = (U1)0U;

    /*SOC Software Number Set */
    u1_tp_pn_tx[36]  = (U1)OXDC_SOFT_N_ECUID;           /* OXDC_SOFT_N_LB3 - 1 */
    u1_tp_pn_tx[53]  = (U1)OXDC_SOFT_N_ECUID;           /* OXDC_SOFT_N_LB4 - 1 */
    u1_tp_pn_tx[70]  = (U1)OXDC_SOFT_N_ECUID;           /* OXDC_SOFT_N_LB5 - 1 */
    u1_tp_pn_tx[87]  = (U1)OXDC_SOFT_N_ECUID;           /* OXDC_SOFT_N_LB6 - 1 */

    u1_t_xpn_sts = u1_g_TyDoCANXpnTx((U1)TYDC_XPN_RX_LB3, &u1_tp_pn_tx[OXDC_SOFT_N_LB3], (U1)TYDC_XPN_NB_LB3);
    if(u1_t_xpn_sts == (U1)TYDC_XPN_UNKNOWN){
        vd_g_MemfillU1(&u1_tp_pn_tx[OXDC_SOFT_N_LB3], (U1)OXDC_F188_UNKNOWN, (U4)OXDC_F188_LB3_LEN);
    }
    else if(u1_t_xpn_sts == (U1)TYDC_XPN_INVALID){
        vd_g_MemfillU1(&u1_tp_pn_tx[OXDC_SOFT_N_LB3], (U1)OXDC_F188_INVALID, (U4)OXDC_F188_LB3_LEN);
    }
    else{
        /* Do Nothing */
    }

    u1_tp_pn_tx[OXDC_SOFT_N_LB3_RES13] = (U1)0U;
    u1_tp_pn_tx[OXDC_SOFT_N_LB3_RES14] = (U1)0U;
    u1_tp_pn_tx[OXDC_SOFT_N_LB3_RES15] = (U1)0U;
    u1_tp_pn_tx[OXDC_SOFT_N_LB3_RES16] = (U1)0U;

    u1_t_xpn_sts = u1_g_TyDoCANXpnTx((U1)TYDC_XPN_RX_LB4, &u1_tp_pn_tx[OXDC_SOFT_N_LB4], (U1)TYDC_XPN_NB_LB4);
    if(u1_t_xpn_sts == (U1)TYDC_XPN_UNKNOWN){
        vd_g_MemfillU1(&u1_tp_pn_tx[OXDC_SOFT_N_LB4], (U1)OXDC_F188_UNKNOWN, (U4)OXDC_F188_LB4_LEN);
    }
    else if(u1_t_xpn_sts == (U1)TYDC_XPN_INVALID){
        vd_g_MemfillU1(&u1_tp_pn_tx[OXDC_SOFT_N_LB4], (U1)OXDC_F188_INVALID, (U4)OXDC_F188_LB4_LEN);
    }
    else{
        /* Do Nothing */
    }

    u1_tp_pn_tx[OXDC_SOFT_N_LB4_RES13] = (U1)0U;
    u1_tp_pn_tx[OXDC_SOFT_N_LB4_RES14] = (U1)0U;
    u1_tp_pn_tx[OXDC_SOFT_N_LB4_RES15] = (U1)0U;
    u1_tp_pn_tx[OXDC_SOFT_N_LB4_RES16] = (U1)0U;

    u1_t_xpn_sts = u1_g_TyDoCANXpnTx((U1)TYDC_XPN_RX_LB5, &u1_tp_pn_tx[OXDC_SOFT_N_LB5], (U1)TYDC_XPN_NB_LB5);
    if(u1_t_xpn_sts == (U1)TYDC_XPN_UNKNOWN){
        vd_g_MemfillU1(&u1_tp_pn_tx[OXDC_SOFT_N_LB5], (U1)OXDC_F188_UNKNOWN, (U4)OXDC_F188_LB5_LEN);
    }
    else if(u1_t_xpn_sts == (U1)TYDC_XPN_INVALID){
        vd_g_MemfillU1(&u1_tp_pn_tx[OXDC_SOFT_N_LB5], (U1)OXDC_F188_INVALID, (U4)OXDC_F188_LB5_LEN);
    }
    else{
        /* Do Nothing */
    }
    u1_tp_pn_tx[OXDC_SOFT_N_LB5_RES13] = (U1)0U;
    u1_tp_pn_tx[OXDC_SOFT_N_LB5_RES14] = (U1)0U;
    u1_tp_pn_tx[OXDC_SOFT_N_LB5_RES15] = (U1)0U;
    u1_tp_pn_tx[OXDC_SOFT_N_LB5_RES16] = (U1)0U;

    u1_t_xpn_sts = u1_g_TyDoCANXpnTx((U1)TYDC_XPN_RX_LB6, &u1_tp_pn_tx[OXDC_SOFT_N_LB6], (U1)TYDC_XPN_NB_LB6);
    if(u1_t_xpn_sts == (U1)TYDC_XPN_UNKNOWN){
        vd_g_MemfillU1(&u1_tp_pn_tx[OXDC_SOFT_N_LB6], (U1)OXDC_F188_UNKNOWN, (U4)OXDC_F188_LB6_LEN);
    }
    else if(u1_t_xpn_sts == (U1)TYDC_XPN_INVALID){
        vd_g_MemfillU1(&u1_tp_pn_tx[OXDC_SOFT_N_LB6], (U1)OXDC_F188_INVALID, (U4)OXDC_F188_LB6_LEN);
    }
    else{
        /* Do Nothing */
    }
    u1_tp_pn_tx[OXDC_SOFT_N_LB6_RES13] = (U1)0U;
    u1_tp_pn_tx[OXDC_SOFT_N_LB6_RES14] = (U1)0U;
    u1_tp_pn_tx[OXDC_SOFT_N_LB6_RES15] = (U1)0U;
    u1_tp_pn_tx[OXDC_SOFT_N_LB6_RES16] = (U1)0U;

    vd_g_MemcpyU1(u1_ap_ans, &u1_tp_pn_tx[0], (U4)OXDC_DATA_REA_ANS_NB_F188);

    return((U1)OXDC_SAL_PROC_FIN);
#else    /* BEV Diag provisionally */
    return((U1)OXDC_SAL_PROC_NR_22);
#endif    /* BEV Diag provisionally */
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     1/30/2024  TK       New.                                                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/* 19PFv3-1   1/08/2025  TeN      Change for TRS_UDS-DA.5.1.46.                                                                      */
/*                                                                                                                                   */
/*  * TK  = Toru Kamishina, Denso Techno                                                                                             */
/*  * TeN = Tetsuhsi Nakanao, Denso Techno                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
