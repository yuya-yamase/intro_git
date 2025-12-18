/* 1.0.0 */
/*===================================================================================================================================*/
/*  FW Update Memory Access                                                                                                          */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define FWUMEMACC_C_MAJOR                   (1U)
#define FWUMEMACC_C_MINOR                   (0U)
#define FWUMEMACC_C_PATCH                   (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include "MemAcc.h"
#include "crc32.h"

#include "fwumemacc.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define FWUMEMACC_JOBSTS_NON                (0U)
#define FWUMEMACC_JOBSTS_ERASE              (1U)
#define FWUMEMACC_JOBSTS_UPDATE             (2U)
#define FWUMEMACC_JOBSTS_SWITCH             (3U)

#define FWUMEMACC_ADRS_INV_OFFSET           (0x02000000U)

/* MemAcc Update */
#define FWUMEMACC_WRITE_LENGTH              (1024U)

#define FWUMEMACC_CRCCHK_LENGTH             (16384U)        /* 1Periodic Erase Size : 16kByte */
#define FWUMEMACC_CRCCHK_INIT_VAL           (0xFFFFFFFFU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1                u1_s_fwumemacc_job_sts;

static U1                u1_s_fwumemacc_erase_sts;
static U1                u1_s_fwumemacc_updt_sts;
static U1                u1_s_fwumemacc_switch_sts;

static U2                u2_s_fwumemacc_blkofst_cnt;
static U4                u4_s_fwumemacc_crc_result;
static U2                u2_s_fwumemacc_crcofst_cnt;

static U4                u4_s_fwumemacc_rcv_start_adrs;
static U4                u4_s_fwumemacc_rcv_rprgdat_len;
static U4                u4_s_fwumemacc_rcv_crc_data;
static U2                u2_s_fwumemacc_rcv_blkofst;
static U4*               u4_sp_fwumemacc_rcv_wrt;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1               u1_s_FwuMemAccEraseTask(void);

static U1               u1_s_FwuMemAccUpdateTask(void);
static U1               u1_s_FwuMemAccUpdt_ReqTask(void);
static U1               u1_s_FwuMemAccUpdt_WrtTask(void);
static U1               u1_s_FwuMemAccUpdt_CrcTask(void);
static U1               u1_s_FwuMemAccUpdt_OfstChk(void);

static U1               u1_s_FwuMemAccSwitchTask(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_FwuMemAccInit(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_FwuMemAccInit(void)
{
    u1_s_fwumemacc_job_sts = (U1)FWUMEMACC_JOBSTS_NON;

    u1_s_fwumemacc_erase_sts = (U1)FWUMEMACC_ERASE_STS_NON;
    u1_s_fwumemacc_updt_sts = (U1)FWUMEMACC_UPDT_STS_NON;
    u1_s_fwumemacc_switch_sts = (U1)FWUMEMACC_SWITCH_STS_NON;

    u2_s_fwumemacc_blkofst_cnt = (U2)0U;
    u4_s_fwumemacc_crc_result = (U4)FWUMEMACC_CRCCHK_INIT_VAL;
    u2_s_fwumemacc_crcofst_cnt = (U2)0U;

    u4_s_fwumemacc_rcv_start_adrs = (U4)0U;
    u4_s_fwumemacc_rcv_rprgdat_len = (U4)0U;
    u4_s_fwumemacc_rcv_crc_data = (U4)0U;
    u2_s_fwumemacc_rcv_blkofst = (U2)0U;
    u4_sp_fwumemacc_rcv_wrt = (U4)0U;
}

/*===================================================================================================================================*/
/*  void    vd_g_FwuMemAccMainTask(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_FwuMemAccMainTask(void)
{
    U1  u1_t_end;

    u1_t_end = (U1)FALSE;

    switch(u1_s_fwumemacc_job_sts){
        case (U1)FWUMEMACC_JOBSTS_ERASE:
            u1_t_end = u1_s_FwuMemAccEraseTask();
            break;
        case (U1)FWUMEMACC_JOBSTS_UPDATE:
            u1_t_end = u1_s_FwuMemAccUpdateTask();
            break;
        case (U1)FWUMEMACC_JOBSTS_SWITCH:
            u1_t_end = u1_s_FwuMemAccSwitchTask();
            break;
        default:
            /* Do nothing */
        break;
    }

    if(u1_t_end == (U1)TRUE){
        u1_s_fwumemacc_job_sts = (U1)FWUMEMACC_JOBSTS_NON;
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_FwuMemAccEraseReqTrg(const U4 u4_a_CRC_DATA)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_FwuMemAccEraseReqTrg(const U4 u4_a_START_ADRS, const U4 u4_a_RPRGDAT_LEN, const U4 u4_a_CRC_DATA)
{
    u1_s_fwumemacc_job_sts = (U1)FWUMEMACC_JOBSTS_ERASE;
    u1_s_fwumemacc_erase_sts = (U1)FWUMEMACC_ERASE_STS_NON;

    u4_s_fwumemacc_rcv_start_adrs = u4_a_START_ADRS + (U4)FWUMEMACC_ADRS_INV_OFFSET;
    u4_s_fwumemacc_rcv_rprgdat_len = u4_a_RPRGDAT_LEN;
    u4_s_fwumemacc_rcv_crc_data = u4_a_CRC_DATA;
}

/*===================================================================================================================================*/
/*  void    vd_g_FwuMemAccUpdateReqTrg(const U2 u2_a_BLK_OFFSET, const U4* u4_ap_WRT_DATA)                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_FwuMemAccUpdateReqTrg(const U2 u2_a_BLK_OFFSET, const U4* u4_ap_WRT_DATA)
{
    u1_s_fwumemacc_job_sts = (U1)FWUMEMACC_JOBSTS_UPDATE;
    u1_s_fwumemacc_updt_sts = (U1)FWUMEMACC_UPDT_STS_NON;

    u2_s_fwumemacc_rcv_blkofst = u2_a_BLK_OFFSET;
    u4_sp_fwumemacc_rcv_wrt = u4_ap_WRT_DATA;
}

/*===================================================================================================================================*/
/*  void    vd_g_FwuMemAccSwitchReqTrg(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_FwuMemAccSwitchReqTrg(void)
{
    u1_s_fwumemacc_job_sts = (U1)FWUMEMACC_JOBSTS_SWITCH;
    u1_s_fwumemacc_switch_sts = (U1)FWUMEMACC_SWITCH_STS_NON;
}

/*===================================================================================================================================*/
/*  U1    u1_g_FwuMemAccEraseSts(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_FwuMemAccEraseSts(void)
{
    return(u1_s_fwumemacc_erase_sts);
}

/*===================================================================================================================================*/
/*  U1    u1_g_FwuMemAccUpdateSts(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_FwuMemAccUpdateSts(void)
{
    return(u1_s_fwumemacc_updt_sts);
}

/*===================================================================================================================================*/
/*  U1    u1_g_FwuMemAccSwitchSts(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_FwuMemAccSwitchSts(void)
{
    return(u1_s_fwumemacc_switch_sts);
}

/*===================================================================================================================================*/
/*  static U1 u1_s_FwuMemAccEraseTask(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_FwuMemAccEraseTask(void)
{
    U1  u1_t_ret;
    U1  u1_t_jobsts;
    U1  u1_t_erasests;
    U1  u1_t_jobrslt;

    u1_t_ret = (U1)FALSE;

    u1_t_jobsts = (U1)MemAcc_GetJobStatus((U2)MEMACC_ADDRAREA_1);
    if(u1_t_jobsts == (U1)MEMACC_JOB_IDLE){
        if(u1_s_fwumemacc_erase_sts == (U1)FWUMEMACC_ERASE_STS_NON){
            u1_t_erasests = (U1)MemAcc_Erase((U2)MEMACC_ADDRAREA_1, u4_s_fwumemacc_rcv_start_adrs, u4_s_fwumemacc_rcv_rprgdat_len);
            if(u1_t_erasests == (U1)E_OK){
                u1_s_fwumemacc_erase_sts = (U1)FWUMEMACC_ERASE_STS_ACT;
                /* u1_t_ret = (U1)FALSE; */
            }
            else{
                u1_s_fwumemacc_erase_sts = (U1)FWUMEMACC_ERASE_STS_ERR;
                u1_t_ret = (U1)TRUE;
            }
        }
        else{
            u1_t_jobrslt = (U1)MemAcc_GetJobResult((U2)MEMACC_ADDRAREA_1);
            if(u1_t_jobrslt == (U1)MEMACC_MEM_OK){
                u2_s_fwumemacc_blkofst_cnt = (U2)0U;

                u1_s_fwumemacc_erase_sts = (U1)FWUMEMACC_ERASE_STS_COMP;
                u1_t_ret = (U1)TRUE;
            }
            else{
                u1_s_fwumemacc_erase_sts = (U1)FWUMEMACC_ERASE_STS_ERR;
                u1_t_ret = (U1)TRUE;
            }
        }
    }
    else{
        u1_s_fwumemacc_erase_sts = (U1)FWUMEMACC_ERASE_STS_ACT;
        /* u1_t_ret = (U1)FALSE; */
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1 u1_s_FwuMemAccUpdateTask(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_FwuMemAccUpdateTask(void)
{
    U1  u1_t_ret;

    u1_t_ret = (U1)FALSE;

    switch(u1_s_fwumemacc_updt_sts){
        case (U1)FWUMEMACC_UPDT_STS_NON:
            u1_t_ret = u1_s_FwuMemAccUpdt_ReqTask();
            break;
        case (U1)FWUMEMACC_UPDT_STS_WRITE:
            u1_t_ret = u1_s_FwuMemAccUpdt_WrtTask();
            break;
        case (U1)FWUMEMACC_UPDT_STS_CRC:
            u1_t_ret = u1_s_FwuMemAccUpdt_CrcTask();
            break;
        default:
            /* Do nothing */
            /* u1_t_ret = (U1)FALSE; */
            break;
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1 u1_s_FwuMemAccUpdt_ReqTask(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_FwuMemAccUpdt_ReqTask(void)
{
    U1  u1_t_ret;
    U1  u1_t_offsetchk;
    U1  u1_t_jobsts;
    U4  u4_t_tgt_address;
    U1  u1_t_wrtsts;

    u1_t_ret = (U1)FALSE;

    u1_t_offsetchk = u1_s_FwuMemAccUpdt_OfstChk();
    if(u1_t_offsetchk == (U1)TRUE){
         u1_t_jobsts = (U1)MemAcc_GetJobStatus((U2)MEMACC_ADDRAREA_1);
        if(u1_t_jobsts == (U1)MEMACC_JOB_IDLE){
            u4_t_tgt_address = u4_s_fwumemacc_rcv_start_adrs + ((U4)FWUMEMACC_WRITE_LENGTH * (U4)u2_s_fwumemacc_rcv_blkofst);
            u1_t_wrtsts = (U1)MemAcc_Write((U2)MEMACC_ADDRAREA_1, u4_t_tgt_address, (U1 *)u4_sp_fwumemacc_rcv_wrt, (U4)FWUMEMACC_WRITE_LENGTH);
            if(u1_t_wrtsts == (U1)E_OK){
                u1_s_fwumemacc_updt_sts = (U1)FWUMEMACC_UPDT_STS_WRITE;
                /* u1_t_ret = (U1)FALSE; */
            }
            else{
                u1_s_fwumemacc_updt_sts = (U1)FWUMEMACC_UPDT_STS_ERR;
                u1_t_ret = (U1)TRUE;
            }
        }
        else{
            u1_s_fwumemacc_updt_sts = (U1)FWUMEMACC_UPDT_STS_ERR;
            u1_t_ret = (U1)TRUE;
        }
    }
    else{
        u1_s_fwumemacc_updt_sts = (U1)FWUMEMACC_UPDT_STS_ERR;
        u1_t_ret = (U1)TRUE;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1 u1_s_FwuMemAccUpdt_WrtTask(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_FwuMemAccUpdt_WrtTask(void)
{
    U1  u1_t_ret;
    U1  u1_t_jobsts;
    U1  u1_t_jobrslt;
    U1  u1_t_offsetchk;
    U2  u2_t_blkofst_max;

    u1_t_ret = (U1)FALSE;

    u1_t_jobsts = (U1)MemAcc_GetJobStatus((U2)MEMACC_ADDRAREA_1);
    if(u1_t_jobsts == (U1)MEMACC_JOB_IDLE){
        u1_t_jobrslt = (U1)MemAcc_GetJobResult((U2)MEMACC_ADDRAREA_1);
        if(u1_t_jobrslt == (U1)MEMACC_MEM_OK){
            u1_t_offsetchk = u1_s_FwuMemAccUpdt_OfstChk();
            if(u1_t_offsetchk == (U1)TRUE){
                u2_t_blkofst_max = (U2)(u4_s_fwumemacc_rcv_rprgdat_len / (U4)FWUMEMACC_WRITE_LENGTH) - (U2)1U;
                if(u2_s_fwumemacc_rcv_blkofst < u2_t_blkofst_max){
                    u2_s_fwumemacc_blkofst_cnt++;

                    u1_s_fwumemacc_updt_sts = (U1)FWUMEMACC_UPDT_STS_1B_COMP;
                    u1_t_ret = (U1)TRUE;
                }
                else{
                    u4_s_fwumemacc_crc_result = (U4)FWUMEMACC_CRCCHK_INIT_VAL;
                    u2_s_fwumemacc_crcofst_cnt = (U2)0U;

                    u1_s_fwumemacc_updt_sts = (U1)FWUMEMACC_UPDT_STS_CRC;
                    /* u1_t_ret = (U1)FALSE; */
                }
            }
            else{
                u1_s_fwumemacc_updt_sts = (U1)FWUMEMACC_UPDT_STS_ERR;
                u1_t_ret = (U1)TRUE;
            }
        }
        else{
            u1_s_fwumemacc_updt_sts = (U1)FWUMEMACC_UPDT_STS_ERR;
            u1_t_ret = (U1)TRUE;
        }
    }
    else{
        u1_s_fwumemacc_updt_sts = (U1)FWUMEMACC_UPDT_STS_WRITE;
        /* u1_t_ret = (U1)FALSE; */
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1 u1_s_FwuMemAccUpdt_CrcTask(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_FwuMemAccUpdt_CrcTask(void)
{
    U1  u1_t_ret;
    U1* u1_tp_crc_data;
    U2  u2_t_crcchk_max;

    u1_t_ret = (U1)FALSE;

    u2_t_crcchk_max = (U2)(u4_s_fwumemacc_rcv_rprgdat_len / (U4)FWUMEMACC_CRCCHK_LENGTH) - (U2)1U;
    if(u2_s_fwumemacc_crcofst_cnt < u2_t_crcchk_max){
        u1_tp_crc_data = (U1*)(u4_s_fwumemacc_rcv_start_adrs + ((U4)FWUMEMACC_CRCCHK_LENGTH * (U4)u2_s_fwumemacc_crcofst_cnt));
        u4_s_fwumemacc_crc_result = u4_g_Crc32(u4_s_fwumemacc_crc_result, u1_tp_crc_data, (U4)FWUMEMACC_CRCCHK_LENGTH, (U1)FALSE);

        u2_s_fwumemacc_crcofst_cnt++;

        u1_s_fwumemacc_updt_sts = (U1)FWUMEMACC_UPDT_STS_CRC;
        /* u1_t_ret = (U1)FALSE; */
    }
    else{
        u1_tp_crc_data = (U1*)(u4_s_fwumemacc_rcv_start_adrs + ((U4)FWUMEMACC_CRCCHK_LENGTH * (U4)u2_s_fwumemacc_crcofst_cnt));
        u4_s_fwumemacc_crc_result = u4_g_Crc32(u4_s_fwumemacc_crc_result, u1_tp_crc_data, (U4)FWUMEMACC_CRCCHK_LENGTH, (U1)TRUE);

        if(u4_s_fwumemacc_crc_result == u4_s_fwumemacc_rcv_crc_data){
            u1_s_fwumemacc_updt_sts = (U1)FWUMEMACC_UPDT_STS_ALL_COMP;
            u1_t_ret = (U1)TRUE;
        }
        else{
            u1_s_fwumemacc_updt_sts = (U1)FWUMEMACC_UPDT_STS_ERR;
            u1_t_ret = (U1)TRUE;
        }
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1 u1_s_FwuMemAccUpdt_OfstChk(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_FwuMemAccUpdt_OfstChk(void)
{
    U1  u1_t_ret;
    U2  u2_t_blkofst_max;

    u1_t_ret = (U1)FALSE;

    u2_t_blkofst_max = (U2)(u4_s_fwumemacc_rcv_rprgdat_len / (U4)FWUMEMACC_WRITE_LENGTH);
    if(u2_s_fwumemacc_rcv_blkofst < u2_t_blkofst_max){
        if(u2_s_fwumemacc_rcv_blkofst == u2_s_fwumemacc_blkofst_cnt){
            u1_t_ret = (U1)TRUE;
        }
        else{
            /* u1_t_ret = (U1)FALSE; */
        }
    }
    else{
        /* u1_t_ret = (U1)FALSE; */
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1 u1_s_FwuMemAccSwitchTask(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_FwuMemAccSwitchTask(void)
{
    U1  u1_t_ret;
    U1  u1_t_jobsts;
    U1  u1_t_jobrslt;
    U1  u1_t_srvsts;
    U1  u1_t_dataptr;
    U4  u4_t_lengthptr;

    u1_t_ret = (U1)FALSE;
    u1_t_dataptr = (U1)0U;
    u4_t_lengthptr = (U4)0U;

    u1_t_jobsts = (U1)MemAcc_GetJobStatus((U2)MEMACC_ADDRAREA_1);
    if(u1_t_jobsts == (U1)MEMACC_JOB_IDLE){
        if(u1_s_fwumemacc_switch_sts == (U1)FWUMEMACC_SWITCH_STS_NON){
            u1_t_srvsts = (U1)MemAcc_HwSpecificService((U2)MEMACC_ADDRAREA_1, (U4)MEMACC_HWID_CODEFLASH, (U4)MEMACC_SRV_ID_SWITCHVALIDAREA, &u1_t_dataptr, &u4_t_lengthptr);
            if(u1_t_srvsts == (U1)E_OK){
                u1_s_fwumemacc_switch_sts = (U1)FWUMEMACC_SWITCH_STS_ACT;
                /* u1_t_ret = (U1)FALSE; */
            }
            else{
                u1_s_fwumemacc_switch_sts = (U1)FWUMEMACC_SWITCH_STS_ERR;
                u1_t_ret = (U1)TRUE;
            }
        }
        else{
            u1_t_jobrslt = (U1)MemAcc_GetJobResult((U2)MEMACC_ADDRAREA_1);
            if(u1_t_jobrslt == (U1)MEMACC_MEM_OK){
                u1_s_fwumemacc_switch_sts = (U1)FWUMEMACC_SWITCH_STS_COMP;
                u1_t_ret = (U1)TRUE;
            }
            else{
                u1_s_fwumemacc_switch_sts = (U1)FWUMEMACC_SWITCH_STS_ERR;
                u1_t_ret = (U1)TRUE;
            }
        }
    }
    else{
        u1_s_fwumemacc_switch_sts = (U1)FWUMEMACC_SWITCH_STS_ACT;
        /* u1_t_ret = (U1)FALSE; */
    }

    return(u1_t_ret);
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
/*                                                                                                                                   */
/*                                                                                                                                   */
/* * ST   = Syo Toyoda                                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/
