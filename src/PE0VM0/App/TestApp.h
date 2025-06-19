/* TestApp_h_v1-0-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | SWC/TESTAPP                                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#pragma once

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "ecy_hsm_service_misc.h"
#include "ecy_hsm_host_proxy.h"
#include "ecy_hsm_csai_shecompat.h"
#include "ecy_hsm_proxy.h"
#include "ecy_hsm_csai.h"
#include "ecy_hsm_csai_sign.h"
#include "ecy_hsm_sessions_params.h"
#include "ecy_hsm_csai_misc.h"
#include "ecy_hsm_csai_error.h"
#include "ecy_hsm_csai_key_exchange.h"
#include "ecy_hsm_she.h"

// #include "IfxStm_reg.h"

#include <SecOC.h>
#include <Crypto_GeneralTypes.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* config */
// #define TESTAPP_ENABLE_SWLIB
#define TESTAPP_ENABLE_CYCURHSM

#define TESTAPP_BSW_VERSION_STR         "AUBIST IIP : Ab-IIP-C019_210035-001_v1-0-0"

//#define TEST_APP_CACHE_BLOCK_SIZE_BYTES (16u)
//#define TEST_APP_HSM_CACHE_ALIGN_ATTR __attribute__((aligned(TEST_APP_CACHE_BLOCK_SIZE_BYTES)))
//#define TEST_APP_GET_TIME(x)						( ( (uint64) STM1_TIM0.U ) + ( ( (uint64) STM1_CAP.U ) << 32 ))

/* Notify Counter */
#define TESTAPP_CALLOUT_VerificationStatusCallout                                 (0U)
#define TESTAPP_CALLOUT_FreshnessValueFailCallout                                 (1U)
#define TESTAPP_CALLOUT_AccumulativeFailCallout                                   (2U)
#define TESTAPP_CALLOUT_FullFVCallout                                             (3U)
#define TESTAPP_CALLOUT_ReportErrorCallout                                        (4U)
#define TESTAPP_CALLOUT_NOTIFY_COUNT                                              (5U)

/* SecOC */
#define TESTAPP_FRESHNESS_VALUE_LENGTH      (7UL) /* 7byte 56bit = TripCntLength(24bit) + MsgCntLength(32bit) */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct TestApp_NotifyCalloutData_t {
    uint32 count; /* Call counter */
    uint32 data;  /* Notify data */
}TestApp_NotifyCalloutData_t;

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void TestApp_Init(void);
void TestApp_MainFunction(void);

/**** End of File ***********************************************************/
