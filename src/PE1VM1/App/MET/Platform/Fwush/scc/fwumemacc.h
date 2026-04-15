/* 2.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*===================================================================================================================================*/
/*  FW Update Memory Access                                                                                                          */
/*===================================================================================================================================*/
#ifndef FWUMEMACC_H
#define FWUMEMACC_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define FWUMEMACC_H_MAJOR            (2U)
#define FWUMEMACC_H_MINOR            (0U)
#define FWUMEMACC_H_PATCH            (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "fwumemacc.h"
#include "aip_common.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Return value definitions (replacement for E_OK/E_NOT_OK) */
#define FWUMEMACC_RET_OK                 (0U)            /* success */
#define FWUMEMACC_RET_NG                 (1U)            /* failure */

#define FWUMEMACC_WRITE_LENGTH           (1024U)         /* write block size: 1KB */
#if (FWUMEMACC_WRITE_LENGTH != 1024U)
#error \
    "FWUMEMACC_WRITE_LENGTH must be same with FWUPX_WRI_RUN_DATA_SIZE in PE2VM2 fwupx.h. " \
    "Change with FWUPX_WRI_RUN_DATA_SIZE & this error check value"
#endif
#define FWUMEMACC_CRC_INIT_VAL           (0xFFFFFFFFU)   /* CRC initial value */
#define FWUMEMACC_MAX_RETRY_COUNT        (3U)            /* max retry count */
#define FWUMEMACC_ADRS_INV_OFFSET        (0x02000000U)   /* address conversion offset */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/* Job types */
#define FWUMEMACC_JOB_TYPE_MAX           (4U)
#define FWUMEMACC_JOB_TYPE_NONE          (0U)    /* no job */
#define FWUMEMACC_JOB_TYPE_ERASE         (1U)    /* erase job */
#define FWUMEMACC_JOB_TYPE_UPDATE        (2U)    /* update job */
#define FWUMEMACC_JOB_TYPE_SWITCH        (3U)    /* switch job */

/* Main status (common for all jobs) */
#define FWUMEMACC_MAIN_STATUS_MAX        (5U)
#define FWUMEMACC_MAIN_STATUS_IDLE       (0U)    /* idle */
#define FWUMEMACC_MAIN_STATUS_REQUESTED  (1U)    /* request accepted */
#define FWUMEMACC_MAIN_STATUS_ACTIVE     (2U)    /* active */
#define FWUMEMACC_MAIN_STATUS_COMPLETED  (3U)    /* completed successfully */
#define FWUMEMACC_MAIN_STATUS_ERROR      (4U)    /* error */

/* Job status (internal state machine) */
#define FWUMEMACC_JOB_STATUS_MAX             (7U)
#define FWUMEMACC_JOB_STATUS_IDLE            (0U)
#define FWUMEMACC_JOB_STATUS_ERASE_ACTIVE    (1U)
#define FWUMEMACC_JOB_STATUS_WRITE_ACTIVE    (2U)
#define FWUMEMACC_JOB_STATUS_CRC_ACTIVE      (3U)
#define FWUMEMACC_JOB_STATUS_SWITCH_ACTIVE   (4U)
#define FWUMEMACC_JOB_STATUS_COMPLETED       (5U)
#define FWUMEMACC_JOB_STATUS_ERROR           (6U)

/* Error codes */
#define FWUMEMACC_ERROR_MAX              (7U)
#define FWUMEMACC_ERROR_NONE             (0U)
#define FWUMEMACC_ERROR_INVALID_PARAM    (1U)    /* invalid parameter */
#define FWUMEMACC_ERROR_OFFSET_MISMATCH  (2U)    /* offset mismatch */
#define FWUMEMACC_ERROR_MEMACC_FAILED    (3U)    /* MemAcc API failed */
#define FWUMEMACC_ERROR_CRC_MISMATCH     (4U)    /* CRC mismatch */
#define FWUMEMACC_ERROR_BUSY             (5U)    /* other job active */
#define FWUMEMACC_ERROR_TIMEOUT          (6U)    /* timeout */

/* Update status values */
#define FWUMEMACC_UPDT_STS_IDLE         (0U)    /* No update in progress */
#define FWUMEMACC_UPDT_STS_IN_PROGRESS  (1U)    /* Update in progress (blocks remaining) */
#define FWUMEMACC_UPDT_STS_ALL_COMP     (2U)    /* All blocks completed */

/* Job request structure */
typedef struct {
    U1 job_type;      /* job type */
    U1 is_active;                       /* request active flag */
    
    union {
        /* Erase request parameters */
        struct {
            U4 start_address;
            U4 data_length;
            U4 expected_crc;
        } erase_params;
        
        /* Update request parameters */
        struct {
            U2 block_offset;
            const U4* write_data_ptr;
        } update_params;
        
        /* Switch request parameters */
        struct {
            U1 reserved;  /* no parameters currently */
        } switch_params;
    } params;
} ST_FWUMEMACC_JOB_REQUEST;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/* Initialization */
void vd_g_FwuMemAccInit(void);

/* Main task */
void vd_g_FwuMemAccMainTask(void);

/* Job request APIs (backward compatible) */
U1 u1_g_FwuMemAccEraseReq(U4 u4_a_start_adrs, U4 u4_a_length, U4 u4_a_expected_crc);
U1 u1_g_FwuMemAccUpdateReq(U2 u2_a_block_offset, const U4* u4p_a_write_data);
U1 u1_g_FwuMemAccSwitchReq(void);

/* Unified status get API */
void vd_g_FwuMemAccGetStatus( U1* u1p_a_job_type, U1* u1p_a_main_status);

/* Individual status getters */
U1 u1_g_FwuMemAccGetError(void);
U1 u1_g_FwuMemAccGetJobType(void);
U1 u1_g_FwuMemAccGetUpdateStatus(void);

/* Debug APIs */
U1 u1_g_FwuMemAccIsJobActive(void);

#endif /* FWUMEMACC_H */
/*===================================================================================================================================*/
