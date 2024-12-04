/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]      LWH_Callout_Stubs.c
 * [Module]         LWH_integration
 * [Function]       Callouts for LWH
 * [Notes]          Functions are gathered from samples of AUBASS LWH
 ****************************************************************************/

/*----------------------------------------------------------------------------
 *      Headers
 *--------------------------------------------------------------------------*/
#include "SS.h"
#include "ehvm.h"
#include "ehvm_cfg.h"
#include "LWH_Callout_Stubs.h"
#include "LWH_Callout_Stubs_ghs.h"
#include "Ecu_Int.h"
#include "Port.h"
#include "Mcu.h"

#pragma ghs section text = ".text.ehvm.usr"

/*----------------------------------------------------------------------------
 *      Symbols
 *--------------------------------------------------------------------------*/

/* Copied from "user_em.c" (AUBASS LWH) */
/*               | | |                  */
/*               V V V                  */

#define MDP_ERROR_CODE_SAMPLE                       (0x10000090U)
#define VWDT_ERROR_CODE_SAMPLE                      (0x10000100U)
#define HVC_ERROR_CODE_SAMPLE                       (0x10000200U)
#define MM_ACC_ERROR_CODE_SAMPLE                    (0x10000300U)
#define DISABLE_VM_SWITCH_TIMEOUT_ERROR_CODE_SAMPLE (0x10000400U)
#define UC_SPID_ERROR_CODE_SAMPLE                   (0x10000500U)

#define EM_ERROR_HEADDER_SIZE (0x14U)
#define RESET_FLAG_ON         (0x01U)
#define RESET_FLAG_OFF        (0x00U)

#define EM_MESSAGEBUF_INDEX0 (0x00U)
#define EM_MESSAGEBUF_INDEX1 (0x01U)
#define EM_MESSAGEBUF_INDEX2 (0x02U)
#define EM_MESSAGEBUF_INDEX3 (0x03U)
#define EM_MESSAGEBUF_INDEX4 (0x04U)
#define EM_MESSAGEBUF_INDEX5 (0x05U)

#define EM_MESSAGEBUF_DATASIZE_4BYTE  (0x04U)
#define EM_MESSAGEBUF_DATASIZE_12BYTE (0x0CU)

/*               ^ ^ ^                  */
/*               | | |                  */
/* Copied from "user_em.c" (AUBASS LWH) */

/* Copied from "user_port.c" (AUBASS LWH) */
/*                | | |                   */
/*                V V V                   */

#define INT_CMD_IGNITION  (ehvm_uint32_t)(0x00000000U)
#define INT_CMD_WAKEUP    (ehvm_uint32_t)(0x00000001U)
#define INT_CMD_CAN0_INTP (ehvm_uint32_t)(0x00000002U)
#define INT_CMD_CAN8_INTP (ehvm_uint32_t)(0x00000003U)

#define INTREQ_OFF (ehvm_uint32_t)(0x00000000U)
#define INTREQ_ON  (ehvm_uint32_t)(0x00000001U)

#define EHVM_WAKEUP_FACTOR_SIZE_96 ((ehvm_wakeup_factor_size_t)0x00000002U)

#define EHVM_WAKEUP_FACTOR_A0 (0x00U)
#define EHVM_WAKEUP_FACTOR_A1 (0x01U)
#define EHVM_WAKEUP_FACTOR_A2 (0x02U)

#define EHVM_USER_PORT_VAL0  (0x00U)
#define EHVM_USER_PORT_VAL1  (0x01U)
#define EHVM_USER_PORT_VAL2  (0x02U)
#define EHVM_USER_PORT_VAL3  (0x03U)
#define EHVM_USER_PORT_VAL4  (0x04U)
#define EHVM_USER_PORT_VAL6  (0x06U)
#define EHVM_USER_PORT_VAL7  (0x07U)
#define EHVM_USER_PORT_VAL8  (0x08U)
#define EHVM_USER_PORT_VAL11 (0x0BU)
#define EHVM_USER_PORT_VAL15 (0x0FU)

#define EHVM_SYSTEM_WAKEUP_FACTOR1_BIT_BATTERY        ((ehvm_wakeup_factor_bit_t)0x00000002U)
#define EHVM_SYSTEM_WAKEUP_FACTOR1_BIT_BATTERY_PE0VM1 ((ehvm_wakeup_factor_bit_t)0x00000004U)
#define EHVM_SYSTEM_WAKEUP_FACTOR1_BIT_IG1            ((ehvm_wakeup_factor_bit_t)0x00000008U)
#define EHVM_SYSTEM_WAKEUP_FACTOR1_BIT_IG2            ((ehvm_wakeup_factor_bit_t)0x00000010U)
#define EHVM_SYSTEM_WAKEUP_FACTOR1_BIT_VCC__PE1VM0    ((ehvm_wakeup_factor_bit_t)0x01000000U)
#define EHVM_SYSTEM_WAKEUP_FACTOR1_BIT_CAN_RX0P       ((ehvm_wakeup_factor_bit_t)0x00000040U)
#define EHVM_SYSTEM_WAKEUP_FACTOR1_BIT_CAN_RX8P       ((ehvm_wakeup_factor_bit_t)0x00004000U)

#define EHVM_SYSTEM_WAKEUP_FACTOR2_BIT_IGNITION ((ehvm_wakeup_factor_bit_t)0x00000010U)
#define EHVM_SYSTEM_WAKEUP_FACTOR2_BIT_WUF1     ((ehvm_wakeup_factor_bit_t)0x00000200U)

#define EHVM_RESET_FACTOR_SOURCE_DEEP_STOP1_BATT    ((ehvm_reset_source_t)0x00000002U)
#define EHVM_RESET_FACTOR_SOURCE_DEEP_STOP2_IG      ((ehvm_reset_source_t)0x00000010U)
#define EHVM_RESET_FACTOR_SOURCE_DEEP_STOP2_WAKEUP1 ((ehvm_reset_source_t)0x00000200U)

/*                ^ ^ ^                   */
/*                | | |                   */
/* Copied from "user_port.c" (AUBASS LWH) */

/*----------------------------------------------------------------------------
 *		Externs
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *		Variables
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *      Prototypes
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *      Codes
 *--------------------------------------------------------------------------*/

/* Copied from "user_callout_hv_init.c" (AUBASS LWH) */
/*                      | | |                        */
/*                      V V V                        */

/*---------------------------------------------------------------------------
  ehvm_user_callout_hv_pre_start
     Callout - HV pre start

  Input     :   none
  Output    :   none
  Return    :   none
  Note  :   none
 ---------------------------------------------------------------------------*/
void ehvm_user_callout_hv_pre_start(void)
{
    /* Modified for Ecu_Boot */
    /* ehvm_user_barr_sync_check_point((ehvm_uint32_t)BARR_SYNC_POINT_2, (ehvm_uint32_t)BARR_SYNC_MODE_ALL_CORES); */
#if (SS_USE_CORE_COUNT >= 2u)
    /* コア間バリア同期 */
    SS_ISeq_syncCores(SS_ISEQ_u2SID_ISEQ_POSTOS_A);
#endif
}

/*---------------------------------------------------------------------------
  ehvm_user_callout_hv_post_shared_init
     Callout - HV pre start

  Input     :   none
  Output    :   none
  Return    :   none
  Note  :   none
 ---------------------------------------------------------------------------*/
void ehvm_user_callout_hv_post_shared_init(void)
{
    /* Modified for Ecu_Boot */
    /* ehvm_user_barr_sync_check_point((ehvm_uint32_t)BARR_SYNC_POINT_3, (ehvm_uint32_t)BARR_SYNC_MODE_ONLY_SLAVE); */
#if (SS_USE_CORE_COUNT >= 2u)
    /* コア間バリア同期 */
    SS_ISeq_syncCores(SS_ISEQ_u2SID_ISEQ_POSTOS_B);
#endif
}

/*                      ^ ^ ^                        */
/*                      | | |                        */
/* Copied from "user_callout_hv_init.c" (AUBASS LWH) */

/* Copied from "user_em.c" (AUBASS LWH) */
/*               | | |                  */
/*               V V V                  */

/*---------------------------------------------------------------------------
  ehvm_em_cbk_make_error_message

  Input     :   errorMessageInfo
  Output    :   messagebuf
  Return    :   none
  Note  :   none
 ---------------------------------------------------------------------------*/
ehvm_uint32_t ehvm_em_cbk_make_error_message(
    EhvmConstR ehvm_em_error_msg_t *errorMessageInfo,
    EhvmConstR ehvm_uint32_t        messageSizemax,
    ehvm_uint32_t *EhvmConstR       messagebuf)
{
    ehvm_uint32_t fepc;
    ehvm_uint32_t feic;
    ehvm_uint32_t mcr;
    ehvm_uint32_t mca;
    ehvm_uint32_t mcs;
    ehvm_uint32_t mea;
    ehvm_uint32_t messageSize;

    switch (errorMessageInfo->errorCause)
    {
    case EHVM_EM_ERROR_CAUSE_MDPMIP:
        /* get FEPC */
        fepc = ehvm_em_cbk_getFEPC();
        /* get MEA */
        mea = ehvm_em_cbk_getMEA();

        messagebuf[EM_MESSAGEBUF_INDEX0] = MDP_ERROR_CODE_SAMPLE;
        messagebuf[EM_MESSAGEBUF_INDEX1] = errorMessageInfo->errorInfo_1;
        messagebuf[EM_MESSAGEBUF_INDEX2] = errorMessageInfo->errorInfo_2;
        messagebuf[EM_MESSAGEBUF_INDEX3] = errorMessageInfo->contextId;
        /* set FEPC */
        messagebuf[EM_MESSAGEBUF_INDEX4] = fepc;

        /* set MEA */
        messagebuf[EM_MESSAGEBUF_INDEX5] = mea;

        messageSize = EM_MESSAGEBUF_DATASIZE_12BYTE + EM_ERROR_HEADDER_SIZE;

        break;
    case EHVM_EM_ERROR_CAUSE_VWDT:
        messagebuf[EM_MESSAGEBUF_INDEX0] = VWDT_ERROR_CODE_SAMPLE;
        messagebuf[EM_MESSAGEBUF_INDEX1] = errorMessageInfo->errorInfo_1;
        messagebuf[EM_MESSAGEBUF_INDEX2] = errorMessageInfo->errorInfo_2;
        messagebuf[EM_MESSAGEBUF_INDEX3] = errorMessageInfo->contextId;
        messageSize                      = EM_MESSAGEBUF_DATASIZE_4BYTE + EM_ERROR_HEADDER_SIZE;
        break;
    case EHVM_EM_ERROR_CAUSE_HVC:
        messagebuf[EM_MESSAGEBUF_INDEX0] = HVC_ERROR_CODE_SAMPLE;
        messagebuf[EM_MESSAGEBUF_INDEX1] = errorMessageInfo->errorInfo_1;
        messagebuf[EM_MESSAGEBUF_INDEX2] = errorMessageInfo->errorInfo_2;
        messageSize                      = EM_ERROR_HEADDER_SIZE;
        break;
    case EHVM_EM_ERROR_CAUSE_UC_SPID:
        messagebuf[EM_MESSAGEBUF_INDEX0] = UC_SPID_ERROR_CODE_SAMPLE;
        messagebuf[EM_MESSAGEBUF_INDEX1] = errorMessageInfo->errorInfo_1;
        messagebuf[EM_MESSAGEBUF_INDEX2] = errorMessageInfo->errorInfo_2;
        messageSize                      = EM_ERROR_HEADDER_SIZE;
        break;
    case EHVM_EM_ERROR_CAUSE_MM_ACC:
        mcr = ehvm_em_cbk_getMCR();
        mca = ehvm_em_cbk_getMCA();
        mcs = ehvm_em_cbk_getMCS();

        messagebuf[EM_MESSAGEBUF_INDEX0] = MM_ACC_ERROR_CODE_SAMPLE;
        messagebuf[EM_MESSAGEBUF_INDEX1] = errorMessageInfo->errorInfo_1;
        messagebuf[EM_MESSAGEBUF_INDEX2] = errorMessageInfo->errorInfo_2;
        messagebuf[EM_MESSAGEBUF_INDEX3] = mca;
        messagebuf[EM_MESSAGEBUF_INDEX4] = mcs;
        messagebuf[EM_MESSAGEBUF_INDEX5] = mcr;

        messageSize = EM_MESSAGEBUF_DATASIZE_12BYTE + EM_ERROR_HEADDER_SIZE;

        break;
    case EHVM_EM_ERROR_CAUSE_DISABLE_VM_SWITCH_TIMEOUT:
        messagebuf[EM_MESSAGEBUF_INDEX0] = DISABLE_VM_SWITCH_TIMEOUT_ERROR_CODE_SAMPLE;
        messagebuf[EM_MESSAGEBUF_INDEX1] = errorMessageInfo->errorInfo_1;
        messagebuf[EM_MESSAGEBUF_INDEX2] = errorMessageInfo->errorInfo_2;
        messageSize                      = EM_ERROR_HEADDER_SIZE;
        break;
    default:
        /* get FEPC */
        fepc = ehvm_em_cbk_getFEPC();
        /* get FEIC */
        feic = ehvm_em_cbk_getFEIC();

        messagebuf[EM_MESSAGEBUF_INDEX0] = errorMessageInfo->errorCause;
        messagebuf[EM_MESSAGEBUF_INDEX1] = errorMessageInfo->errorInfo_1;
        messagebuf[EM_MESSAGEBUF_INDEX2] = errorMessageInfo->errorInfo_2;
        messagebuf[EM_MESSAGEBUF_INDEX3] = errorMessageInfo->contextId;
        /* set FEPC */
        messagebuf[EM_MESSAGEBUF_INDEX4] = fepc;
        /* set FEIC */
        messagebuf[EM_MESSAGEBUF_INDEX5] = feic;

        messageSize = EM_MESSAGEBUF_DATASIZE_12BYTE + EM_ERROR_HEADDER_SIZE;
        break;
    }
#ifdef EHVM_API_MEASUREMENT
    messageSize = 80U;
#endif /* EHVM_API_MEASUREMENT */

    return messageSize;
}

/*---------------------------------------------------------------------------
  ehvm_em_cbk_error_handling

  Input     :   peId
                contextId
                errorCause
                databuffer
                lenbytes
  Output    :   none
  Return    :   unsigned int
  Note  :   none
 ---------------------------------------------------------------------------*/
ehvm_uint32_t ehvm_em_cbk_error_handling(
    ehvm_peid_t              peId,
    ehvm_context_id_t        contextId,
    EhvmConstR ehvm_uint32_t errorCause,
    EhvmConstR ehvm_uint32_t *EhvmConstR databuffer,
    EhvmConstR ehvm_uint32_t             lenbytes)
{
    ehvm_uint32_t resetFlag;

    switch (errorCause)
    {
    case EHVM_EM_ERROR_CAUSE_HVC:
    case EHVM_EM_ERROR_CAUSE_MM_ACC:
    case EHVM_EM_ERROR_CAUSE_DISABLE_VM_SWITCH_TIMEOUT:
    case EHVM_EM_ERROR_CAUSE_UC_SPID:
        resetFlag = RESET_FLAG_OFF;
        break;
    default:
        resetFlag = RESET_FLAG_ON;
        break;
    }

    if (errorCause == (ehvm_uint32_t)EHVM_EM_ERROR_CAUSE_SYSERR)
    {
        Ecu_Int_performReset();
    }

    return resetFlag;
}

/*---------------------------------------------------------------------------
  ehvm_em_cbk_transmit_error

  Input     :   contextId
                errorCause
  Output    :   none
  Return    :   none
  Note  :   none
 ---------------------------------------------------------------------------*/
void ehvm_em_cbk_transmit_error(
    ehvm_context_id_t        contextId,
    EhvmConstR ehvm_uint32_t errorCause)
{
    Ecu_Int_performReset();
}

/*               ^ ^ ^                  */
/*               | | |                  */
/* Copied from "user_em.c" (AUBASS LWH) */

/* Copied from "user_hook.c" (AUBASS LWH) */
/*                | | |                   */
/*                V V V                   */

/*---------------------------------------------------------------------------
  ehvm_user_startup_hook_call()
     startup hook function
  Input     :   none
  Output    :   none
  Return    :   none
  Note  :
 ---------------------------------------------------------------------------*/
void ehvm_user_startup_hook_call(void)
{
    return;
}

/*---------------------------------------------------------------------------
  ehvm_user_deep_stop_hook_call_1()
     deep stop hook function
  Input     :   none
  Output    :   none
  Return    :   none
  Note  :
 ---------------------------------------------------------------------------*/
void ehvm_user_deep_stop_hook_call_1(void)
{
    return;
}
/*---------------------------------------------------------------------------
  ehvm_user_deep_stop_hook_call_2()
     deep stop hook function
  Input     :   none
  Output    :   none
  Return    :   none
  Note  :
 ---------------------------------------------------------------------------*/
void ehvm_user_deep_stop_hook_call_2(void)
{
    return;
}
/*---------------------------------------------------------------------------
  ehvm_user_deep_stop_hook_call_3()
     deep stop hook function
  Input     :   none
  Output    :   none
  Return    :   none
  Note  :
 ---------------------------------------------------------------------------*/
#define REG_u4RESFC (*(volatile uint32 *)((uint32)0xFF980C00UL)) /* RESFC */
#define VAL_u4RESFC_CLR  (0x0000F5DDUL) /* R_RESF_CLR */


void ehvm_user_deep_stop_hook_call_3(void)
{
    /* set the clock mask */
    /* set the clock source */
    /* set CPU system clock gear down */

//    Std_ReturnType retVal;

//    retVal = SS_SleepTm_start(5000UL);
//    if (E_OK != retVal)
//    {
//        Ecu_Int_performReset();
//    }
    volatile uint32 u4Dummy;

    REG_u4RESFC = VAL_u4RESFC_CLR;

    u4Dummy = REG_u4RESFC; /* dummy read */
    SS_CpuCore_syncp();    /* syncp */

    // Port_Init(&cstPort_Config[1]);
    Mcu_SetMode(MCU_MODE_DEEPSTOP);

    return;
}

/*                ^ ^ ^                   */
/*                | | |                   */
/* Copied from "user_hook.c" (AUBASS LWH) */

/* Copied from "user_intm.c" (AUBASS LWH) */
/*                | | |                   */
/*                V V V                   */

/*---------------------------------------------------------------------------
  ehvm_intm_ecm_error

  Input     :   none
  Output    :   none
  Return    :   none
  Note  :   none
 ---------------------------------------------------------------------------*/
void ehvm_intm_ecm_error(
    void)
{

    Ecu_Int_performReset();

    return;
}

/*                ^ ^ ^                   */
/*                | | |                   */
/* Copied from "user_intm.c" (AUBASS LWH) */

/* Copied from "user_port.c" (AUBASS LWH) */
/*                | | |                   */
/*                V V V                   */

/*---------------------------------------------------------------------------
  ehvm_user_wakeup_event_init()
     Initialization function for Power On Reset
  Input     :   none
  Output    :   none
  Return    :   none
  Note  :
 ---------------------------------------------------------------------------*/
void ehvm_user_wakeup_event_init(void)
{
    ehvm_reset_factor_t reset_factor;

    /* get reset factor register */
    (void)ehvm_vmm_get_reset_factor_register(&reset_factor); /* no return check required */

    /*-----------------------*/
    /* judge Power On Reset */
    /*-----------------------*/
    if ((reset_factor.category & EHVM_RESET_FACTOR_CATEGORY_POWER_ON_RESET) != (ehvm_reset_category_t)EHVM_RESET_FACTOR_CATEGORY_NONE)
    {
        /* set +B ON to virtual wake-up factor(Mask) */
        (void)ehvm_vmm_enable_wakeup_factor(EHVM_WAKEUP_FACTOR_A0, (ehvm_wakeup_factor_bit_t)(EHVM_SYSTEM_WAKEUP_FACTOR1_BIT_BATTERY / (ehvm_uint32_t)EHVM_USER_PORT_VAL2)); /* no return check required */

        /* set +B ON to virtual wake-up factor */
        (void)ehvm_vmm_set_wakeup_factor(EHVM_WAKEUP_FACTOR_A0, (ehvm_wakeup_factor_bit_t)(EHVM_SYSTEM_WAKEUP_FACTOR1_BIT_BATTERY / (ehvm_uint32_t)EHVM_USER_PORT_VAL2)); /* no return check required */
    }

    /*------------------------*/
    /* judge Deep Stop Reset */
    /*------------------------*/
    if ((reset_factor.category & EHVM_RESET_FACTOR_CATEGORY_DEEP_STOP) != (ehvm_reset_category_t)EHVM_RESET_FACTOR_CATEGORY_NONE)
    {
        /* set +B ON to virtual wake-up factor(Mask) */
        (void)ehvm_vmm_enable_wakeup_factor(EHVM_WAKEUP_FACTOR_A0, (ehvm_wakeup_factor_bit_t)(EHVM_SYSTEM_WAKEUP_FACTOR1_BIT_BATTERY / (ehvm_uint32_t)EHVM_USER_PORT_VAL2)); /* no return check required */

        /* set +B ON to virtual wake-up factor */
        (void)ehvm_vmm_set_wakeup_factor(EHVM_WAKEUP_FACTOR_A0, (ehvm_wakeup_factor_bit_t)(EHVM_SYSTEM_WAKEUP_FACTOR1_BIT_BATTERY / (ehvm_uint32_t)EHVM_USER_PORT_VAL2)); /* no return check required */
    }

#if defined(EHVM_TARGET_S4)
    ehvm_user_rcar4_s4_wakeup_event_init(reset_factor);
#endif /* ( EHVM_TARGET_S4 ) */

    return;
}

/*                ^ ^ ^                   */
/*                | | |                   */
/* Copied from "user_port.c" (AUBASS LWH) */
