/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  OEM eXtention of Security                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXSEC_FV_C_MAJOR                            (1U)
#define OXSEC_FV_C_MINOR                            (0U)
#define OXSEC_FV_C_PATCH                            (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxsec_cfg_private.h"
#include "oxsec_fv.h"
#include "ehvm.h"

#if (OXSEC_FV_EN_RW == 1U)
#include "nvmc_mgr.h"
#include "nvmc_mgr_custom.h"
#include "NvM.h"
#include "ehvm_cfg_pe1_vm0.h"
#endif /* #if (OXSEC_FV_EN_RW == 1U) */

#if (OXSEC_FV_EN_SET == 1U)
#include "SecOC.h"
#include "ehvm_cfg_pe0_vm0.h"
#endif /* #if (OXSEC_FV_EN_SET == 1U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((OXSEC_FV_C_MAJOR != OXSEC_H_MAJOR) || \
     (OXSEC_FV_C_MINOR != OXSEC_H_MINOR) || \
     (OXSEC_FV_C_PATCH != OXSEC_H_PATCH))
#error "oxsec_fv.c and oxsec.h : source and header files are inconsistent!"
#endif

#if ((OXSEC_FV_C_MAJOR != OXSEC_FV_H_MAJOR) || \
     (OXSEC_FV_C_MINOR != OXSEC_FV_H_MINOR) || \
     (OXSEC_FV_C_PATCH != OXSEC_FV_H_PATCH))
#error "oxsec_fv.c and oxsec_fv.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Trip counter    */
#define OXSEC_FV_TRIPCNT_SET_LOW       (0x000000FFU)       /* Trip counter ptFV[2] setting definition */
#define OXSEC_FV_TRIPCNT_SET_MID       (0x0000FF00U)       /* Trip counter ptFV[1] setting definition */
#define OXSEC_FV_TRIPCNT_SET_HI        (0x00FF0000U)       /* Trip counter ptFV[0] setting definition */
#define OXSEC_FV_TRIPCNT_MAX           (0x00FFFFFFU)       /* Trip counter Maximum                    */
#define OXSEC_FV_TRIPCNT_NBYTE         (3U)
#define OXSEC_FV_TRIPCNT_NBIT          (24U)

/* FreshnessValue */
#define OXSEC_FV_FV_NBYTE              (7U)
#define OXSEC_FV_FV_NBIT               (56U)

/* vcc */
#define OXSEC_FV_VCC_NBYTE             (8U)
#define OXSEC_FV_VCC_NWORD             (2U)
#define OXSEC_FV_VCC_RX_LP_MAX         (5U)

/* read status */
#define OXSEC_FV_READ_OK               (0U)
#define OXSEC_FV_READ_NG               (1U)


#if (OXSEC_FV_EN_RW == 1U)
#define OXSEC_FV_VCC_TX_CH             (EHVM_TX_VCCID_VCC_OXSEC_TX_VM1)
#endif /* #if (OXSEC_FV_EN_RW == 1U) */

#if (OXSEC_FV_EN_SET == 1U)
#define OXSEC_FV_VCC_RX_CH             (EHVM_RX_VCCID_VCC_OXSEC_TX_VM1)
#endif /* #if (OXSEC_FV_EN_SET == 1U) */


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (OXSEC_FV_EN_RW == 1U)
static U4 u4_s_oxsec_fv_tripcnt;
static U4 u4_s_oxsec_fv_read_status;
#endif /* #if (OXSEC_FV_EN_RW == 1U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (OXSEC_FV_EN_SET == 1U)
static void    vd_s_oXSECFvSet(const U4 u4_a_TRIPCNT, const U4 u4_a_RESULT);
#endif /* #if (OXSEC_FV_EN_SET == 1U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (OXSEC_FV_EN_SET == 1U)
static const U1  u1_s_oXSECFv_TripCounterMax[OXSEC_FV_TRIPCNT_NBYTE] = {
(U1)0xff, (U1)0xff, (U1)0xff
};

static const U1  u1_s_oXSECFv_FreshnessValueMax[OXSEC_FV_FV_NBYTE] = {
(U1)0xff, (U1)0xff, (U1)0xff, (U1)0xff, (U1)0xff, (U1)0xff, (U1)0xff
};
#endif /* #if (OXSEC_FV_EN_SET == 1U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*===================================================================================================================================*/
/*  void    vd_g_oXSECFvInit(void)                                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXSECFvInit(void)
{
#if (OXSEC_FV_EN_RW == 1U)
    u4_s_oxsec_fv_read_status = (U4)OXSEC_FV_READ_NG;
    u4_s_oxsec_fv_tripcnt     = (U4)OXSEC_FV_TRIPCNT_MAX;
#endif /* #if (OXSEC_FV_EN_RW == 1U) */

#if (OXSEC_FV_EN_SET == 1U)
    (void)ehvm_vcc_clear_channel((U4)OXSEC_FV_VCC_RX_CH);
#endif /* #if (OXSEC_FV_EN_SET == 1U) */

    return;
}

#if (OXSEC_FV_EN_SET == 1U)
/*===================================================================================================================================*/
/*  U1    u1_g_oXSECFvRx(void)                                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1    u1_g_oXSECFvRx(void)
{

    U4    u4_t_lpcnt;
    U4    u4_t_nbyte;
    U4    u4_t_vcc_rxdata[OXSEC_FV_VCC_NWORD];
    U1    u1_t_vcc_ret;
    U1    u1_t_ok;

    u1_t_ok = (U1)FALSE;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)OXSEC_FV_VCC_RX_LP_MAX; u4_t_lpcnt++){

        /* #define E_EHVM_OK                        ((ehvm_std_return_t)0x00U) */
        /* #define E_EHVM_NOT_OK                    ((ehvm_std_return_t)0x01U) */
        /* #define E_EHVM_RECEIVE_QUEUE_EMPTY       ((ehvm_std_return_t)0x03U) */
        /* #define E_EHVM_RECEIVE_OVERWRITE_OCCURS  ((ehvm_std_return_t)0x04U) */
        /* #define E_EHVM_HVC_ACC_DENY              ((ehvm_std_return_t)0x10U) */
        /* #define E_EHVM_MM_ACC_NG                 ((ehvm_std_return_t)0x20U) */
        u1_t_vcc_ret = ehvm_vcc_receive((U4)OXSEC_FV_VCC_RX_CH, &u4_t_vcc_rxdata[0], (U4)OXSEC_FV_VCC_NBYTE, &u4_t_nbyte);
        if(u1_t_vcc_ret == E_EHVM_OK){
            if(u4_t_nbyte == (U4)OXSEC_FV_VCC_NBYTE){
                vd_s_oXSECFvSet(u4_t_vcc_rxdata[0], u4_t_vcc_rxdata[1]);
                u1_t_ok = (U1)TRUE;
            }
        }
        else if(u1_t_vcc_ret == E_EHVM_RECEIVE_OVERWRITE_OCCURS){
            /* do nothing */
        }
        else{
            break;
        }
    }

    return(u1_t_ok);
}

/*===================================================================================================================================*/
/*  static void    vd_s_oXSECFvSet(const U4 u4_a_TRIPCNT, const U4 u4_a_RESULT)                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_oXSECFvSet(const U4 u4_a_TRIPCNT, const U4 u4_a_RESULT)
{
    U4    u4_t_loop_cnt;
    U2    u2_t_fvid;
    U1    u1_t_tripcnt[3];

    if(u4_a_RESULT == (U4)OXSEC_FV_READ_OK){
        /*----------------------------------------------------------*/
        /*   u1_t_tripcnt[0] - u1_t_tripcnt[2]                      */
        /*   MSB                           LSB                      */
        /*----------------------------------------------------------*/
        u1_t_tripcnt[0] = (U1)((u4_a_TRIPCNT & (U4)OXSEC_FV_TRIPCNT_SET_HI) >> 16U);
        u1_t_tripcnt[1] = (U1)((u4_a_TRIPCNT & (U4)OXSEC_FV_TRIPCNT_SET_MID) >> 8U);
        u1_t_tripcnt[2] = (U1)(u4_a_TRIPCNT & (U4)OXSEC_FV_TRIPCNT_SET_LOW);

        for(u4_t_loop_cnt = (U4)0U; u4_t_loop_cnt < (U4)SECOC_AB_BUS_MAX; u4_t_loop_cnt++){
            u2_t_fvid = (U2)SecOC_Ab_BusCollection[u4_t_loop_cnt].Ab_FreshnessValueID;
            (void)SecOC_Ab_FreshnessValueWrite(u2_t_fvid ,&u1_t_tripcnt[0], (U4)OXSEC_FV_TRIPCNT_NBIT);
            /*---------------------------------------------------------------------------------*/
            /* With the current usage, the return value "E_NOT_OK" will never be obtained.     */
            /* The policy is not to judge the return value.                                    */
            /*---------------------------------------------------------------------------------*/
        }

        if(u4_a_TRIPCNT >= (U4)OXSEC_FV_TRIPCNT_MAX){
            vd_g_oXSECCfgTrCntMax();
        }

    }else{
        for(u4_t_loop_cnt = (U4)0U; u4_t_loop_cnt < (U4)SECOC_AB_BUS_MAX; u4_t_loop_cnt++){
            u2_t_fvid = (U2)SecOC_Ab_BusCollection[u4_t_loop_cnt].Ab_FreshnessValueID;
            (void)SecOC_Ab_FreshnessValueWrite(u2_t_fvid ,&u1_s_oXSECFv_TripCounterMax[0], (U4)OXSEC_FV_TRIPCNT_NBIT);
            /*---------------------------------------------------------------------------------*/
            /* With the current usage, the return value "E_NOT_OK" will never be obtained.     */
            /* The policy is not to judge the return value.                                    */
            /*---------------------------------------------------------------------------------*/
        }

        for(u4_t_loop_cnt = (U4)0U; u4_t_loop_cnt < (U4)SECOC_TX_PDU_PROCESSING_MAX; u4_t_loop_cnt++){
            u2_t_fvid = SecOC_TxPduProcessing[u4_t_loop_cnt].FreshnessValueId;
            (void)SecOC_Ab_FreshnessValueWrite(u2_t_fvid ,&u1_s_oXSECFv_FreshnessValueMax[0], (U4)OXSEC_FV_FV_NBIT);
            /*---------------------------------------------------------------------------------*/
            /* With the current usage, the return value "E_NOT_OK" will never be obtained.     */
            /* The policy is not to judge the return value.                                    */
            /*---------------------------------------------------------------------------------*/
        }
    }
    return;
}

#endif /* #if (OXSEC_FV_EN_SET == 1U) */

#if (OXSEC_FV_EN_RW == 1U)
/*===================================================================================================================================*/
/*  void    vd_g_oXSECFvRead(const U4 u4_a_BOOTCAUSE)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXSECFvRead(const U4 u4_a_BOOTCAUSE)
{

    U4    u4_tp_word[OXSEC_FV_VCC_NWORD];
    U1    u1_t_rslt;
    U4    u4_t_data;
    U4    u4_t_Pstate;
    
    
    if(u4_a_BOOTCAUSE == (U4)OXSEC_BOOT_CAUSE_BON){
        u4_t_Pstate = (U4)NVMC_CPR_POWER_STATE_B_ON;
    }else{
        u4_t_Pstate = (U4)NVMC_CPR_POWER_STATE_NOT_B_ON;
    }
    u1_t_rslt = u1_g_Nvmc_CustomPreReadU4((U2)NVMCID_U4_BSW_SECOC_TRIP_CNT, &u4_t_data, u4_t_Pstate);
    
    if(u1_t_rslt != (U1)NVMC_CPR_DTF_READ_FAIL){
        u4_s_oxsec_fv_read_status = (U4)OXSEC_FV_READ_OK;

        if(u4_t_data < (U4)OXSEC_FV_TRIPCNT_MAX){
            u4_t_data++;
            u4_s_oxsec_fv_tripcnt = u4_t_data;
        } else {
            u4_s_oxsec_fv_tripcnt = (U4)1U;
        }
    }else{
        u4_s_oxsec_fv_read_status = (U4)OXSEC_FV_READ_NG;
        u4_s_oxsec_fv_tripcnt = (U4)OXSEC_FV_TRIPCNT_MAX;
    }
    
    u4_tp_word[0] = u4_s_oxsec_fv_tripcnt;
    u4_tp_word[1] = u4_s_oxsec_fv_read_status;
    
    (void)ehvm_vcc_transmit((U4)OXSEC_FV_VCC_TX_CH, (U4 *)&u4_tp_word, (U4)OXSEC_FV_VCC_NBYTE);

    return;
}

/*===================================================================================================================================*/
/*  void    vd_g_oXSECFvWrite(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXSECFvWrite(void)
{
    if(u4_s_oxsec_fv_read_status != (U4)OXSEC_FV_READ_NG){
        vd_g_Nvmc_WriteU4((U2)NVMCID_U4_BSW_SECOC_TRIP_CNT, u4_s_oxsec_fv_tripcnt);
    }
    return;
}
#endif /* #if (OXSEC_FV_EN_RW == 1U) */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     3/10/2026  KT       New                                                                                                */
/*                                                                                                                                   */
/*  * KT   = Kazuya Takayama, DENSO CREATE                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
