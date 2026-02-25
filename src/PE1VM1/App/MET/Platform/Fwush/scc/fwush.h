/* 2.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/* FW Update State Handler                                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef FWUSH_H
#define FWUSH_H
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define FWUSH_H_MAJOR                       (2U)
#define FWUSH_H_MINOR                       (0U)
#define FWUSH_H_PATCH                       (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "fwumemacc.h"
#include "aip_common.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Request frame definition */
#define FWUSH_REQ_WORD_BYTE                     (4U)
#define FWUSH_REQ_H_WORDS                       (2U)
#define FWUSH_REQ_D_WORDS                       (1U)
#define FWUSH_REQ_H_SIZE                        (FWUSH_REQ_H_WORDS * FWUSH_REQ_WORD_BYTE)
#define FWUSH_RES_WORDS                         (2U)

/* Response definition */
#define FWUSH_ACK_OK                            (0x00U)
#define FWUSH_ACK_NG                            (0x01U)

/* Request frame offset */
#define FWUSH_REQ_SUBTYPE_OFFSET                (0U)
#define FWUSH_REQ_SEQCNT_OFFSET                 (7U)
#define FWUSH_REQ_PREP_DATA_CRC_OFFSET          (0U)
#define FWUSH_REQ_RUN_BLKOFS_OFFSET             (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions - Phase 2: State Machine                                                                                        */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/* Main states */
#define FWUSH_MAIN_STATE_MAX                    (5U)
#define FWUSH_MAIN_STATE_PREP                   (0U)           /* Prepare phase */
#define FWUSH_MAIN_STATE_RUN                    (1U)           /* Run phase */
#define FWUSH_MAIN_STATE_VERI                   (2U)           /* Verify phase */
#define FWUSH_MAIN_STATE_ACT                    (3U)           /* Activate phase */
#define FWUSH_MAIN_STATE_ROLLBACK               (4U)           /* Rollback phase (when special flag present) */

/* Sub states */
#define FWUSH_SUB_STATE_MAX                     (2U)
#define FWUSH_SUB_STATE_WAITING                 (0U)           /* Waiting for request */
#define FWUSH_SUB_STATE_PROCESSING              (1U)           /* MemAcc job processing */

/* NOTE: ERROR condition is managed via abort_active flag. */
/* NOTE: After ACT completes, transition to ROLLBACK or reset->PREP_WAITING. */

/* Event definitions (with CANCEL support) */
#define FWUSH_EVENT_MAX                         (11U)
#define FWUSH_EVENT_NONE                        (0U)           /* No event */
#define FWUSH_EVENT_NEW_REQUEST                 (1U)           /* New request received */
#define FWUSH_EVENT_SAME_REQUEST                (2U)           /* Same request received (continue) */
#define FWUSH_EVENT_MEMACC_SUCCESS              (3U)           /* MemAcc job success */
#define FWUSH_EVENT_MEMACC_PROGRESS             (4U)           /* MemAcc job in progress */
#define FWUSH_EVENT_MEMACC_ERROR                (5U)           /* MemAcc job error */
#define FWUSH_EVENT_INVALID_REQUEST             (6U)           /* Invalid request */
#define FWUSH_EVENT_CANCEL                      (7U)           /* Cancel requested */
#define FWUSH_EVENT_MEMACC_RUN_PARTIAL          (8U)           /* MemAcc run job partial success */
#define FWUSH_EVENT_MEMACC_RUN_COMPLETE         (9U)           /* MemAcc run job complete */
#define FWUSH_EVENT_MEMACC_ACT_ROLLBACK         (10U)          /* MemAcc activate job rollback */

/* Request subtypes */
#define FWUSH_REQ_SUBTYPE_NA                    (0xFFU)        /* Not Applicable */
#define FWUSH_REQ_SUBTYPE_PREP                  (0x01U)        /* Prepare */
#define FWUSH_REQ_SUBTYPE_RUN                   (0x02U)        /* Run */
#define FWUSH_REQ_SUBTYPE_VERI                  (0x18U)        /* Verify */
#define FWUSH_REQ_SUBTYPE_ACT                   (0x37U)        /* Activate */
#define FWUSH_REQ_SUBTYPE_CANCEL                (0xFEU)        /* Cancel (reserved for future) */

/* Response subtypes */
#define FWUSH_RESP_SUBTYPE_NA                    (0xFFU)        /* Not Applicable */
#define FWUSH_RESP_SUBTYPE_PREP                  (0x07U)        /* Prepare */
#define FWUSH_RESP_SUBTYPE_RUN                   (0x17U)        /* Run */
#define FWUSH_RESP_SUBTYPE_VERI                  (0x19U)        /* Verify */
#define FWUSH_RESP_SUBTYPE_ACT                   (0x38U)        /* Activate */


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/* main functions */
void vd_g_FwushInit(void);
void vd_g_FwushMainTask(void);

#endif /* FWUSH_H */
/*===================================================================================================================================*/
