/* 1.0.0 */
/*===================================================================================================================================*/
/*  FW Update State Handler                                                                                                          */
/*===================================================================================================================================*/

#ifndef FWUSH_H
#define FWUSH_H

#include <Std_Types.h>
#include "fwumemacc.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define FWUSH_H_MAJOR                              (1U)
#define FWUSH_H_MINOR                              (0U)
#define FWUSH_H_PATCH                              (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define FWUSH_REQ_WORD_BYTE                        (4U)
#define FWUSH_REQ_H_WORDS                          (2U)
#define FWUSH_REQ_D_WORDS                          (1U)
#define FWUSH_REQ_H_SIZE                           (FWUSH_REQ_H_WORDS * FWUSH_REQ_WORD_BYTE)
#define FWUSH_RES_WORDS                            (2U)

#define FWUSH_REQ_PREP_DATA_SIZE                   (328U)
#define FWUSH_REQ_RUN_DATA_SIZE                    (1024U)

/* 4-State State Machine Definitions */
#define FWUSH_NUM_STS                              (4U)
#define FWUSH_STS_PREP                             (0U)  /* PREP */
#define FWUSH_STS_RUN                              (1U)  /* RUN */
#define FWUSH_STS_VERI                             (2U)  /* VERI */
#define FWUSH_STS_ACT                              (3U)  /* ACT */

/* Type03h frame markers - Request Subtypes */
#define FWUSH_REQ_SUBTYPE_OFFSET                   (0U)
#define FWUSH_REQ_SUBTYPE_PREP                     (0x01U)  /* Repro Subtype=01h */
#define FWUSH_REQ_SUBTYPE_RUN                      (0x02U)  /* Repro Subtype=02h */
#define FWUSH_REQ_SUBTYPE_VERI                     (0x18U)  /* Misc Subtype=18h */
#define FWUSH_REQ_SUBTYPE_ACT                      (0x37U)  /* Misc Subtype=37h */
#define FWUSH_REQ_SUBTYPE_NA                       (0xFFU)  /* Not Applicable Subtype */

#define FWUSH_MEMACC_STATUS_PREP_IDLE              (FWUMEMACC_ERASE_STS_NON)
#define FWUSH_MEMACC_STATUS_PREP_RUNNING           (FWUMEMACC_ERASE_STS_ACT)
#define FWUSH_MEMACC_STATUS_PREP_SUCCESS           (FWUMEMACC_ERASE_STS_COMP)
#define FWUSH_MEMACC_STATUS_PREP_ERROR             (FWUMEMACC_ERASE_STS_ERR)

#define FWUSH_MEMACC_STATUS_RUN_IDLE               (FWUMEMACC_UPDT_STS_NON)
#define FWUSH_MEMACC_STATUS_RUN_RUNNING            (FWUMEMACC_UPDT_STS_WRITE)
#define FWUSH_MEMACC_STATUS_RUN_SUCCESS_MIDWAY     (FWUMEMACC_UPDT_STS_1B_COMP)
#define FWUSH_MEMACC_STATUS_RUN_CRC_CHECK          (FWUMEMACC_UPDT_STS_CRC)
#define FWUSH_MEMACC_STATUS_RUN_SUCCESS_FINAL      (FWUMEMACC_UPDT_STS_ALL_COMP)
#define FWUSH_MEMACC_STATUS_RUN_ERROR              (FWUMEMACC_UPDT_STS_ERR)

#define FWUSH_MEMACC_STATUS_ACT_IDLE               (FWUMEMACC_SWITCH_STS_NON)
#define FWUSH_MEMACC_STATUS_ACT_RUNNING            (FWUMEMACC_SWITCH_STS_ACT)
#define FWUSH_MEMACC_STATUS_ACT_SUCCESS            (FWUMEMACC_SWITCH_STS_COMP)
#define FWUSH_MEMACC_STATUS_ACT_ERROR              (FWUMEMACC_SWITCH_STS_ERR)

/* Type38h frame markers */
#define FWUSH_ACK_OK                               (0x00U)
#define FWUSH_ACK_NG                               (0x01U)

/* subtype01h  frame markers */
#if 0   /* debug */
#define FWUSH_REQ_PREP_DATA_ADR_OFFSET              (0U)
#define FWUSH_REQ_PREP_DATA_LEN_OFFSET              (4U)
#define FWUSH_REQ_PREP_DATA_CRC_OFFSET              (8U)
#else   /* debug */
#define FWUSH_REQ_PREP_DATA_CRC_OFFSET              (0U)
#endif   /* debug */
/* subtype02h  frame markers */
#define FWUSH_REQ_RUN_BLKOFS_OFFSET                (2U)
#define FWUSH_REQ_RUN_LEN_OFFSET                   (4U)

/* Response data structure offsets */
/* T.B.D. */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void            vd_g_FwushInit(void);
void            vd_g_FwushMainTask(void);

#endif /* FWUSH_H */
/*===================================================================================================================================*/
