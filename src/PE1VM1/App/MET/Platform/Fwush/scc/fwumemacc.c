/* 2.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*===================================================================================================================================*/
/*  FW Update Memory Access                                                                                                          */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define FWUMEMACC_C_MAJOR                   (2U)
#define FWUMEMACC_C_MINOR                   (0U)
#define FWUMEMACC_C_PATCH                   (0U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "fwumemacc.h"

#include "MemAcc.h"
#include "crc32.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/* Job status is declared in the header (U1) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions (managed via individual static variables per existing pattern)                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/* Job type and job status */
static U1     u1_s_job_type;
static U1     u1_s_job_status;

/* Erase/Update common parameters */
static U4 u4_s_start_address;      /* Erase/Update: start address */
static U4 u4_s_data_length;        /* Erase: data length, Update: total data length */
static U4 u4_s_expected_crc;       /* Erase/Update: expected CRC value */

/* Update processing parameters */
static U2         u2_s_block_offset;       /* Update: current block offset */
static const U4*  u4p_sp_write_data;        /* Update: write data pointer */
static U2         u2_s_block_counter;      /* Update: written block count */

/* CRC segmented processing (WDG mitigation: split per 16KB) */
static U4 u4_s_crc_result;         /* CRC intermediate result */
static U2 u2_s_crc_offset;         /* CRC checked offset (16KB units) */

/* Error information */
static U1 u1_s_last_error;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/* Job execution tasks (simplified: state machine not required) */
static void vd_s_FwuMemAccEraseTask(void);
static void vd_s_FwuMemAccUpdateTask(void);
static void vd_s_FwuMemAccSwitchTask(void);

/* CRC segmented task (WDG mitigation) */
static void vd_s_FwuMemAccCrcCalc(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions for CRC                                                                                                      */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define FWUMEMACC_CRCCHK_LENGTH  (16384U)  /* CRC split unit: 16KB (WDG mitigation) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*===================================================================================================================================*/
/* void vd_g_FwuMemAccInit(void)                                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_FwuMemAccInit(void)
{
    /* Initialize job type and status */
    u1_s_job_type = (U1)FWUMEMACC_JOB_TYPE_NONE;
    u1_s_job_status = (U1)FWUMEMACC_JOB_STATUS_IDLE;
    
    /* Clear parameters */
    u4_s_start_address = (U4)0U;
    u4_s_data_length = (U4)0U;
    u4_s_expected_crc = (U4)0U;
    u2_s_block_offset = (U2)0U;
    u4p_sp_write_data = (U4 *)vdp_PTR_NA;
    
    /* Clear counters */
    u2_s_block_counter = (U2)0U;
    u4_s_crc_result = (U4)FWUMEMACC_CRC_INIT_VAL;
    u2_s_crc_offset = (U2)0U;
    
    /* Clear error information */
    u1_s_last_error = (U1)FWUMEMACC_ERROR_NONE;
}

/*===================================================================================================================================*/
/* void vd_g_FwuMemAccMainTask(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_FwuMemAccMainTask(void)
{
    /* Execute processing according to job type (simplified: no state machine required) */
    switch (u1_s_job_type) {
        case (U1)FWUMEMACC_JOB_TYPE_ERASE:
            vd_s_FwuMemAccEraseTask();
            break;
        case (U1)FWUMEMACC_JOB_TYPE_UPDATE:
            vd_s_FwuMemAccUpdateTask();
            break;
        case (U1)FWUMEMACC_JOB_TYPE_SWITCH:
            vd_s_FwuMemAccSwitchTask();
            break;
        default:
            /* IDLE: do nothing */
            break;
    }
}

/*===================================================================================================================================*/
/*  U1 u1_g_FwuMemAccEraseReq(U4 u4_a_start_adrs, U4 u4_a_length, U4 u4_a_expected_crc)                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U4 u4_a_start_adrs    : Start address                                                                           */
/*                  U4 u4_a_length        : Data length                                                                              */
/*                  U4 u4_a_expected_crc  : Expected CRC value                                                                       */
/*  Return:         U1 : FWUMEMACC_RET_OK / FWUMEMACC_RET_NG                                                                        */
/*===================================================================================================================================*/
U1 u1_g_FwuMemAccEraseReq(U4 u4_a_start_adrs, U4 u4_a_length, U4 u4_a_expected_crc)
{
    U1 u1_t_ret;

    /* Only proceed when not busy */
    u1_t_ret = (U1)FWUMEMACC_RET_NG;
    if (u1_s_job_status == (U1)FWUMEMACC_JOB_STATUS_IDLE ||
        u1_s_job_status == (U1)FWUMEMACC_JOB_STATUS_COMPLETED ||
        u1_s_job_status == (U1)FWUMEMACC_JOB_STATUS_ERROR) {
        /* Parameter validation */
        if ((u4_a_start_adrs != (U4)0U) && (u4_a_length != (U4)0U)) {
            /* Set job request */
            u1_s_job_type = (U1)FWUMEMACC_JOB_TYPE_ERASE;
            u1_s_job_status = (U1)FWUMEMACC_JOB_STATUS_IDLE;  /* task will start it */
            u4_s_start_address = u4_a_start_adrs + (U4)FWUMEMACC_ADRS_INV_OFFSET;
            u4_s_data_length = u4_a_length;
            u4_s_expected_crc = u4_a_expected_crc;
            u1_s_last_error = (U1)FWUMEMACC_ERROR_NONE;

            u1_t_ret = (U1)FWUMEMACC_RET_OK;
        }
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1 u1_g_FwuMemAccUpdateReq(U2 u2_a_block_offset, const U4* u4p_a_write_data)                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U2 u2_a_block_offset  : Block offset                                                                             */
/*                  const U4* u4p_a_write_data : Write data pointer                                                                  */
/*  Return:         U1 : FWUMEMACC_RET_OK / FWUMEMACC_RET_NG                                                                         */
/*===================================================================================================================================*/
U1 u1_g_FwuMemAccUpdateReq(U2 u2_a_block_offset, const U4* u4p_a_write_data)
{
    U1 u1_t_ret;

    /* Only proceed when not busy */
    u1_t_ret = (U1)FWUMEMACC_RET_NG;
    if (u1_s_job_status == (U1)FWUMEMACC_JOB_STATUS_IDLE ||
        u1_s_job_status == (U1)FWUMEMACC_JOB_STATUS_COMPLETED ||
        u1_s_job_status == (U1)FWUMEMACC_JOB_STATUS_ERROR) {
        /* Parameter validation */
        if (u4p_a_write_data != (U4 *)vdp_PTR_NA) {
            /* Check offset sequence */
            if (u2_s_block_counter == u2_a_block_offset) {
                /* Set job request */
                u1_s_job_type = (U1)FWUMEMACC_JOB_TYPE_UPDATE;
                u1_s_job_status = (U1)FWUMEMACC_JOB_STATUS_IDLE;  /* task will start it */
                u2_s_block_offset = u2_a_block_offset;
                u4p_sp_write_data = u4p_a_write_data;
                u1_s_last_error = (U1)FWUMEMACC_ERROR_NONE;

                u1_t_ret = (U1)FWUMEMACC_RET_OK;
            } else {
                u1_s_last_error = (U1)FWUMEMACC_ERROR_OFFSET_MISMATCH;
            }
        }
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1 u1_g_FwuMemAccSwitchReq(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 : FWUMEMACC_RET_OK / FWUMEMACC_RET_NG                                                                        */
/*===================================================================================================================================*/
U1 u1_g_FwuMemAccSwitchReq(void)
{
    U1 u1_t_ret;

    /* Only proceed when not busy */
    u1_t_ret = (U1)FWUMEMACC_RET_NG;
    if (u1_s_job_status == (U1)FWUMEMACC_JOB_STATUS_IDLE ||
        u1_s_job_status == (U1)FWUMEMACC_JOB_STATUS_COMPLETED ||
        u1_s_job_status == (U1)FWUMEMACC_JOB_STATUS_ERROR) {
        /* Set job request */
        u1_s_job_type = (U1)FWUMEMACC_JOB_TYPE_SWITCH;
        u1_s_job_status = (U1)FWUMEMACC_JOB_STATUS_IDLE;  /* task will start it */
        u1_s_last_error = (U1)FWUMEMACC_ERROR_NONE;
        u1_t_ret = (U1)FWUMEMACC_RET_OK;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  void vd_g_FwuMemAccGetStatus(U1* u1p_a_job_type, U1* u1p_a_main_status)                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U1* u1p_a_job_type    : Job type output pointer                                                                  */
/*                  U1* u1p_a_main_status : Main status output pointer                                                               */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_FwuMemAccGetStatus(U1* u1p_a_job_type, U1* u1p_a_main_status)
{
    if (u1p_a_job_type != vdp_PTR_NA) {
        *u1p_a_job_type = u1_s_job_type;
    }
    if (u1p_a_main_status != vdp_PTR_NA) {
        /* Map JobStatus to MainStatus */
        switch (u1_s_job_status) {
            case (U1)FWUMEMACC_JOB_STATUS_IDLE:
                *u1p_a_main_status = (U1)FWUMEMACC_MAIN_STATUS_IDLE;
                break;
            case (U1)FWUMEMACC_JOB_STATUS_ERASE_ACTIVE:
            case (U1)FWUMEMACC_JOB_STATUS_WRITE_ACTIVE:
            case (U1)FWUMEMACC_JOB_STATUS_CRC_ACTIVE:
            case (U1)FWUMEMACC_JOB_STATUS_SWITCH_ACTIVE:
                *u1p_a_main_status = (U1)FWUMEMACC_MAIN_STATUS_ACTIVE;
                break;
            case (U1)FWUMEMACC_JOB_STATUS_COMPLETED:
                *u1p_a_main_status = (U1)FWUMEMACC_MAIN_STATUS_COMPLETED;
                break;
            case (U1)FWUMEMACC_JOB_STATUS_ERROR:
                *u1p_a_main_status = (U1)FWUMEMACC_MAIN_STATUS_ERROR;
                break;
            default:
                *u1p_a_main_status = (U1)FWUMEMACC_MAIN_STATUS_IDLE;
                break;
        }
    }
}

/*===================================================================================================================================*/
/* U1 u1_g_FwuMemAccGetUpdateStatus(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 : Update status (IDLE / IN_PROGRESS / ALL_COMP)                                                               */
/*===================================================================================================================================*/
U1 u1_g_FwuMemAccGetUpdateStatus(void)
{
    U1 u1_t_status;
    U2 u2_t_max_blocks;

    if (u4_s_data_length > (U4)FWUMEMACC_WRITE_LENGTH) {
        u2_t_max_blocks = (U2)(u4_s_data_length / (U4)FWUMEMACC_WRITE_LENGTH);
    } else {
        u2_t_max_blocks = (U2)0U;
    }

    if (u1_s_job_status == (U1)FWUMEMACC_JOB_STATUS_IDLE) {
        u1_t_status = (U1)FWUMEMACC_UPDT_STS_IDLE;
    } else if (u2_s_block_counter >= u2_t_max_blocks) {
        u1_t_status = (U1)FWUMEMACC_UPDT_STS_ALL_COMP;
    } else {
        u1_t_status = (U1)FWUMEMACC_UPDT_STS_IN_PROGRESS;
    }
    
    return (u1_t_status);
}

/*===================================================================================================================================*/
/* U1 u1_g_FwuMemAccGetError(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 : Error information                                                                                           */
/*===================================================================================================================================*/
U1 u1_g_FwuMemAccGetError(void)
{
    return(u1_s_last_error);
}

/*===================================================================================================================================*/
/* U1 u1_g_FwuMemAccGetJobType(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 : Job type                                                                                                    */
/*===================================================================================================================================*/
U1 u1_g_FwuMemAccGetJobType(void)
{
    return(u1_s_job_type);
}

/*===================================================================================================================================*/
/* U1 u1_g_FwuMemAccIsJobActive(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 : TRUE(active) / FALSE(not active)                                                                            */
/*===================================================================================================================================*/
U1 u1_g_FwuMemAccIsJobActive(void)
{
    U1 u1_ret;
    if (u1_s_job_status == (U1)FWUMEMACC_JOB_STATUS_ERASE_ACTIVE ||
        u1_s_job_status == (U1)FWUMEMACC_JOB_STATUS_WRITE_ACTIVE ||
        u1_s_job_status == (U1)FWUMEMACC_JOB_STATUS_CRC_ACTIVE ||
        u1_s_job_status == (U1)FWUMEMACC_JOB_STATUS_SWITCH_ACTIVE) {
        u1_ret = (U1)TRUE;
    } else {
        u1_ret = (U1)FALSE;
    }
    return(u1_ret);
}

/*===================================================================================================================================*/
/*  Task implementations (ERASE/UPDATE/SWITCH/CRC)                                                                                   */
/*===================================================================================================================================*/

/*===================================================================================================================================*/
/* static void vd_s_FwuMemAccEraseTask(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwuMemAccEraseTask(void)
{
    U1 u1_t_job_status;
    U1 u1_t_job_result;
    U1 u1_t_erase_result;
    
    if (u1_s_job_status == (U1)FWUMEMACC_JOB_STATUS_IDLE) {
        /* MemAcc erase request */
        u1_t_erase_result = (U1)MemAcc_Erase((U2)MEMACC_ADDRAREA_1, 
                                              u4_s_start_address, 
                                              u4_s_data_length);
        
        if (u1_t_erase_result == (U1)MEMACC_MEM_OK) {
            /* Erase start succeeded */
            u1_s_job_status = (U1)FWUMEMACC_JOB_STATUS_ERASE_ACTIVE;
        } else {
            /* Erase start failed */
            u1_s_job_status = (U1)FWUMEMACC_JOB_STATUS_ERROR;
            u1_s_last_error = (U1)FWUMEMACC_ERROR_MEMACC_FAILED;
        }
    } else if (u1_s_job_status == (U1)FWUMEMACC_JOB_STATUS_ERASE_ACTIVE) {
        /* Check MemAcc job status */
        u1_t_job_status = (U1)MemAcc_GetJobStatus((U2)MEMACC_ADDRAREA_1);
        
        if (u1_t_job_status == (U1)MEMACC_JOB_IDLE) {
            /* Job completed -> check result */
            u1_t_job_result = (U1)MemAcc_GetJobResult((U2)MEMACC_ADDRAREA_1);
            if (u1_t_job_result == (U1)MEMACC_MEM_OK) {
                /* Erase completed */
                u1_s_job_status = (U1)FWUMEMACC_JOB_STATUS_COMPLETED;
                u1_s_last_error = (U1)FWUMEMACC_ERROR_NONE;
                u2_s_block_counter = (U2)0U;  /* Initialize update counter */
            } else {
                /* Erase failed */
                u1_s_job_status = (U1)FWUMEMACC_JOB_STATUS_ERROR;
                u1_s_last_error = (U1)FWUMEMACC_ERROR_MEMACC_FAILED;
            }
        }
        /* MEMACC_JOB_BUSY: in progress - continue */
    } else {
        /* Do nothing */
    }
}

/*===================================================================================================================================*/
/* static void vd_s_FwuMemAccUpdateTask(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwuMemAccUpdateTask(void)
{
    U1 u1_t_job_status;
    U1 u1_t_job_result;
    U1 u1_t_write_result;
    U4 u4_t_write_address;
    U2 u2_t_max_blocks;
    
    if (u1_s_job_status == (U1)FWUMEMACC_JOB_STATUS_IDLE) {
        /* Start write */
        u4_t_write_address = u4_s_start_address + 
                             ((U4)FWUMEMACC_WRITE_LENGTH * (U4)u2_s_block_offset);
        
        u1_t_write_result = (U1)MemAcc_Write((U2)MEMACC_ADDRAREA_1,
                                              u4_t_write_address,
                                              (U1*)u4p_sp_write_data,
                                              (U4)FWUMEMACC_WRITE_LENGTH);
        
        if (u1_t_write_result == (U1)MEMACC_MEM_OK) {
            /* Write start succeeded */
            u1_s_job_status = (U1)FWUMEMACC_JOB_STATUS_WRITE_ACTIVE;
        } else {
            /* Write start failed */
            u1_s_job_status = (U1)FWUMEMACC_JOB_STATUS_ERROR;
            u1_s_last_error = (U1)FWUMEMACC_ERROR_MEMACC_FAILED;
        }
    } else if (u1_s_job_status == (U1)FWUMEMACC_JOB_STATUS_WRITE_ACTIVE) {
        /* Check MemAcc job status */
        u1_t_job_status = (U1)MemAcc_GetJobStatus((U2)MEMACC_ADDRAREA_1);
        
        if (u1_t_job_status == (U1)MEMACC_JOB_IDLE) {
            /* Job completed -> check result */
            u1_t_job_result = (U1)MemAcc_GetJobResult((U2)MEMACC_ADDRAREA_1);
            if (u1_t_job_result == (U1)MEMACC_MEM_OK) {
                /* Write completed - move to next block */
                if (u2_s_block_counter < (U2)U2_MAX) {
                    u2_s_block_counter++;
                }

                /* All blocks completion check */
                if (u4_s_data_length > (U4)FWUMEMACC_WRITE_LENGTH) {
                    u2_t_max_blocks = (U2)(u4_s_data_length / (U4)FWUMEMACC_WRITE_LENGTH);
                } else {
                    u2_t_max_blocks = (U2)0U;
                }
                if (u2_s_block_counter >= u2_t_max_blocks) {
                    /* All blocks complete -> proceed to CRC verification */
                    u1_s_job_status = (U1)FWUMEMACC_JOB_STATUS_CRC_ACTIVE;
                    u4_s_crc_result = (U4)FWUMEMACC_CRC_INIT_VAL;
                    u2_s_crc_offset = (U2)0U;
                } else {
                    /* Prepare for next block write */
                    u1_s_job_status = (U1)FWUMEMACC_JOB_STATUS_COMPLETED;  /* used to notify block completion */
                }
            } else {
                /* Write failed */
                u1_s_job_status = (U1)FWUMEMACC_JOB_STATUS_ERROR;
                u1_s_last_error = (U1)FWUMEMACC_ERROR_MEMACC_FAILED;
            }
        }
        /* MEMACC_JOB_BUSY: in progress - continue */
    } else if (u1_s_job_status == (U1)FWUMEMACC_JOB_STATUS_CRC_ACTIVE) {
        /* Execute CRC calculation */
        vd_s_FwuMemAccCrcCalc();
    } else{  /* u1_s_job_status == FWUMEMACC_JOB_STATUS_COMPLETED */
        /* Waiting for next block request (wait for UpdateReq from Fwush) */
    }
}

/*===================================================================================================================================*/
/* static void vd_s_FwuMemAccSwitchTask(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwuMemAccSwitchTask(void)
{
    U1 u1_t_job_status;
    U1 u1_t_job_result;
    U1 u1_t_switch_result;
    U1 u1_t_data_dummy;
    U4 u4_t_length_dummy;
    
    u1_t_data_dummy = (U1)0U;
    u4_t_length_dummy = (U4)0U;
    
    if (u1_s_job_status == (U1)FWUMEMACC_JOB_STATUS_IDLE) {
        /* Execute MemAcc HwSpecificService (SWITCHVALIDAREA) */
        u1_t_switch_result = (U1)MemAcc_HwSpecificService(
            (U2)MEMACC_ADDRAREA_1,
            (U4)MEMACC_HWID_CODEFLASH,
            (U4)MEMACC_SRV_ID_SWITCHVALIDAREA,
            &u1_t_data_dummy,
            &u4_t_length_dummy);
        
        if (u1_t_switch_result == (U1)MEMACC_MEM_OK) {
            /* Switch start succeeded */
            u1_s_job_status = (U1)FWUMEMACC_JOB_STATUS_SWITCH_ACTIVE;
        } else {
            /* Switch start failed */
            u1_s_job_status = (U1)FWUMEMACC_JOB_STATUS_ERROR;
            u1_s_last_error = (U1)FWUMEMACC_ERROR_MEMACC_FAILED;
        }
    } else if (u1_s_job_status == (U1)FWUMEMACC_JOB_STATUS_SWITCH_ACTIVE) {
        /* Check MemAcc job status */
        u1_t_job_status = (U1)MemAcc_GetJobStatus((U2)MEMACC_ADDRAREA_1);
        if (u1_t_job_status == (U1)MEMACC_JOB_IDLE) {
            /* Job completed -> check result */
            u1_t_job_result = (U1)MemAcc_GetJobResult((U2)MEMACC_ADDRAREA_1);
            if (u1_t_job_result == (U1)MEMACC_MEM_OK) {
                /* Switch completed */
                u1_s_job_status = (U1)FWUMEMACC_JOB_STATUS_COMPLETED;
                u1_s_last_error = (U1)FWUMEMACC_ERROR_NONE;
            } else {
                /* Switch failed */
                u1_s_job_status = (U1)FWUMEMACC_JOB_STATUS_ERROR;
                u1_s_last_error = (U1)FWUMEMACC_ERROR_MEMACC_FAILED;
            }
        }
        /* MEMACC_JOB_BUSY: in progress - continue */
    } else {
        /* Do nothing */
    }
}

/*===================================================================================================================================*/
/* static void vd_s_FwuMemAccCrcCalc(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_FwuMemAccCrcCalc(void)
{
    U4  u4_t_remaining_length;
    U1* u1p_t_check_start_ptr;
    U1  u1_t_is_final;
    
    if (u1_s_job_status == (U1)FWUMEMACC_JOB_STATUS_CRC_ACTIVE) {
        /* Calculate remaining size */
        u4_t_remaining_length = u4_s_data_length - ((U4)u2_s_crc_offset * (U4)FWUMEMACC_CRCCHK_LENGTH);
        /* On the first call, u2_s_crc_offset = 0 so u4_t_remaining_length > 0                   */
        /* subsequent calls are guarded against negative values by the maximum value guard below */
        
        if (u4_t_remaining_length > (U4)FWUMEMACC_CRCCHK_LENGTH) {
            u1_t_is_final = (U1)FALSE;
        } else {
            u1_t_is_final = (U1)TRUE;
        }
        
        /* Compute CRC (16KB chunks) */
        u1p_t_check_start_ptr = (U1*)(u4_s_start_address + ((U4)u2_s_crc_offset * (U4)FWUMEMACC_CRCCHK_LENGTH));
        u4_s_crc_result = u4_g_Crc32(u4_s_crc_result,
                                      u1p_t_check_start_ptr,
                                      FWUMEMACC_CRCCHK_LENGTH,
                                      u1_t_is_final);
        
        u2_s_crc_offset++;
        
        /* Final chunk check */
        if (u1_t_is_final == (U1)TRUE) {
            /* Compare CRC */
            if (u4_s_crc_result == u4_s_expected_crc) {
                /* CRC OK */
                u1_s_job_status = (U1)FWUMEMACC_JOB_STATUS_COMPLETED;
                u1_s_last_error = (U1)FWUMEMACC_ERROR_NONE;
            } else {
                /* CRC mismatch */
                u1_s_job_status = (U1)FWUMEMACC_JOB_STATUS_ERROR;
                u1_s_last_error = (U1)FWUMEMACC_ERROR_CRC_MISMATCH;
            }
        }
        /* If remaining chunks exist, continue in next MainTask() call */
    }
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    11/18/2025  ST       New.                                                                                               */
/*  2.0.0    02/16/2026  KI       Refactoring - State machine reconstruction and optimization                                        */
/*                                                                                                                                   */
/*                                                                                                                                   */
/* * ST   = Syo Toyoda, KSE                                                                                                          */
/* * KI   = Kanji Ito, Denso Techno                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/
