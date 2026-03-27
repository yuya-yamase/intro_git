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

/* Positive response definition */
#define FWUSH_ACK_OK                            (0x00U)
#define FWUSH_ACK_ROLLBACK_DONE                 (0x01U)
/* Negative response definition */
#define FWUSH_ACK_PROCESSING                    (0x80U)
#define FWUSH_ACK_SEQ_ERR                       (0x81U)
#define FWUSH_ACK_PRECONDITION_ERR              (0x82U)
#define FWUSH_ACK_PROC_START_ERR                (0x83U)
#define FWUSH_ACK_PROC_NG                       (0x84U)
#define FWUSH_ACK_NO_REPRO_TARGET               (0x85U)
#define FWUSH_ACK_LB_ERR                        (0x86U)
#define FWUSH_ACK_OFFSET_JUMP                   (0x87U)
#define FWUSH_ACK_OFFSET_UNCHANGED              (0x88U)
#define FWUSH_ACK_OFFSET_SUBTRACT               (0x89U)
#define FWUSH_ACK_ROLLBACK_PRECOND_ERR          (0x8AU)
#define FWUSH_ACK_ROLLBACK_START_ERR            (0x8BU)
#define FWUSH_ACK_ROLLBACK_NG                   (0x8CU)


/* Request frame offset */
#define FWUSH_REQ_SUBTYPE_OFFSET                (0U)
#define FWUSH_REQ_SEQCNT_OFFSET                 (7U)
#define FWUSH_REQ_PREP_CUR_TARGET_OFFSET        (1U)
#define FWUSH_REQ_PREP_ALL_TARGET_OFFSET        (2U)
#define FWUSH_REQ_PREP_DATA_CRC_OFFSET          (0U)
#define FWUSH_REQ_RUN_BLKOFS_OFFSET             (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/* Main states */
#define FWUSH_MAIN_STATE_MAX                    (6U)
#define FWUSH_MAIN_STATE_PREP                   (0U)           /* Prepare phase */
#define FWUSH_MAIN_STATE_RUN                    (1U)           /* Run phase */
#define FWUSH_MAIN_STATE_VERI                   (2U)           /* Verify phase */
#define FWUSH_MAIN_STATE_ACT                    (3U)           /* Activate phase */
#define FWUSH_MAIN_STATE_VALID                  (4U)           /* Validate phase */
#define FWUSH_MAIN_STATE_FIN                    (5U)           /* Finalize phase */

/* Sub states */
#define FWUSH_SUB_STATE_MAX                     (2U)
#define FWUSH_SUB_STATE_WAITING                 (0U)           /* Waiting for request */
#define FWUSH_SUB_STATE_PROCESSING              (1U)           /* MemAcc job processing */

/* NOTE: ERROR condition is managed via abort_active flag. */
/* NOTE: After ACT completes, transition to ROLLBACK or reset->PREP_WAITING. */

/* Event definitions */
#define FWUSH_EVENT_MAX                         (14U)
#define FWUSH_EVENT_NONE                        (0U)           /* No event */
#define FWUSH_EVENT_NEW_REQUEST                 (1U)           /* New request received */
#define FWUSH_EVENT_MEMACC_SUCCESS              (2U)           /* MemAcc job success (incl. run complete) */
#define FWUSH_EVENT_MEMACC_ERROR                (3U)           /* MemAcc job error */
#define FWUSH_EVENT_INVALID_REQUEST             (4U)           /* Invalid request */
#define FWUSH_EVENT_CANCEL                      (5U)           /* Cancel requested */
#define FWUSH_EVENT_MEMACC_RUN_PARTIAL          (6U)           /* MemAcc run job partial success */
#define FWUSH_EVENT_ROLLBACK                    (7U)           /* Activate job rollback */
#define FWUSH_EVENT_SWITCH_DETECT               (8U)           /* Active area switch detected */
#define FWUSH_EVENT_PREP_ACCEPT                 (9U)           /* Prepare accept event */
#define FWUSH_EVENT_RES_OK                      (10U)          /* OK response only (ACT/VALID accept) */
#define FWUSH_EVENT_RESUME_ACT                  (11U)          /* Resume from Activate (MCU reset with Verify done) */
#define FWUSH_EVENT_RESUME_FIN                  (12U)          /* Resume from Finalize (Prep to Validate completed) */
#define FWUSH_EVENT_FIN_ACCEPT                  (13U)          /* Finalize accept event */

/* job progress */
#define FWUSH_PROGRESS_INIT                     (0x00U)        /* Before reprog start */
#define FWUSH_PROGRESS_ACT_DONE                 (0x01U)        /* Activate complete */
#define FWUSH_PROGRESS_VALIDATE_DONE            (0x02U)        /* Validate complete */
#define FWUSH_PROGRESS_FINALIZE_DONE            (0x04U)        /* Finalize complete */
#define FWUSH_PROGRESS_CANCEL_DONE              (0x08U)        /* Cancel complete */
#define FWUSH_PROGRESS_ROLLBACK_DONE            (0x10U)        /* Rollback complete */

/* Request subtypes */
#define FWUSH_REQ_SUBTYPE_NA                    (0xFFU)        /* Not Applicable */
#define FWUSH_REQ_SUBTYPE_PREP                  (0x01U)        /* Prepare */
#define FWUSH_REQ_SUBTYPE_RUN                   (0x02U)        /* Run */
#define FWUSH_REQ_SUBTYPE_VERI                  (0x18U)        /* Verify */
#define FWUSH_REQ_SUBTYPE_CANCEL                (0x27U)        /* Cancel */
#define FWUSH_REQ_SUBTYPE_ACT                   (0x37U)        /* Activate */
#define FWUSH_REQ_SUBTYPE_VALID                 (0x47U)        /* Validate */
#define FWUSH_REQ_SUBTYPE_FIN                   (0x57U)        /* Finalize */

/* Response subtypes */
#define FWUSH_RESP_SUBTYPE_NA                   (0xFFU)        /* Not Applicable */
#define FWUSH_RESP_SUBTYPE_PREP                 (0x07U)        /* Prepare */
#define FWUSH_RESP_SUBTYPE_RUN                  (0x17U)        /* Run */
#define FWUSH_RESP_SUBTYPE_VERI                 (0x19U)        /* Verify */
#define FWUSH_RESP_SUBTYPE_CANCEL               (0x28U)        /* Cancel */
#define FWUSH_RESP_SUBTYPE_ACT                  (0x38U)        /* Activate */
#define FWUSH_RESP_SUBTYPE_VALID                (0x48U)        /* Validate */
#define FWUSH_RESP_SUBTYPE_FIN                  (0x58U)        /* Finalize */

/* Flash status values */
#define FWUSH_FSWA_STS_AREA0                    (0x00000000U)    /* Area 0 Active */
#define FWUSH_FSWA_STS_AREA1                    (0x00000001U)    /* Area 1 Active */
#define FWUSH_FSWA_STS_INIT                     (0xFFFFFFFFU)    /* read error */
#define FWUSH_FSWA_READ_POS                     (0x000000FFU)    /* Read Position */
#define FWUSH_SWAS_VALID                        (0x00U)          /* Valid */
#define FWUSH_VERI_LB_STAT_INIT                 (0x0000U)        /* LB Init */
#define FWUSH_VERI_LB_NONE                      (0x00U)          /* LB none */
#define FWUSH_VERI_LB1                          (0x01U)          /* LB1 define bit */
#define FWUSH_VERI_LB2                          (0x02U)          /* LB2 define bit */

#define FWUSH_CHECK_VA_MATCH                    (0x00U)          /* Valid Area match */
#define FWUSH_CHECK_VA_UNMATCH                  (0x01U)          /* Valid Area unmatch */
#define FWUSH_CHECK_VA_ERROR                    (0xFFU)          /* Valid Area read error */


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/* main functions */
void vd_g_FwushInit(void);
void vd_g_FwushMainTask(void);

#endif /* FWUSH_H */
/*===================================================================================================================================*/
