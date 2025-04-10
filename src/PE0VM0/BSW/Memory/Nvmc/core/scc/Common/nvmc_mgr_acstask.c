/* 1.4.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Nvmc : Mgr AcsTask                                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NVMC_MGR_ACSTASK_C_MAJOR                 (1U)
#define NVMC_MGR_ACSTASK_C_MINOR                 (4U)
#define NVMC_MGR_ACSTASK_C_PATCH                 (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "nvmc_mgr_cfg_private.h"   /* #include "aip_common.h"               */
                                    /* #include "nvmc_mgr_private.h"         */
                                    /* #include "nvmc_mgr.h"                 */
                                    /* #include "nvmc_mgr_cfg.h"             */
                                    /* #include "nvmc_mgr_acstask_private.h" */
                                    /* #include "rim_ctl.h"                  */
                                    /* #include "rim_ctl_cfg.h"              */

#include "memfill_u1.h"
#include "memfill_u4.h"
#include "memcpy_u4.h"
#include "lsbsrch.h"

#include "rim_func_private.h"
#include "nvmc_dck_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((NVMC_MGR_ACSTASK_C_MAJOR != NVMC_MGR_ACSTASK_PRIVATE_H_MAJOR) || \
     (NVMC_MGR_ACSTASK_C_MINOR != NVMC_MGR_ACSTASK_PRIVATE_H_MINOR) || \
     (NVMC_MGR_ACSTASK_C_PATCH != NVMC_MGR_ACSTASK_PRIVATE_H_PATCH))
#error "nvmc_mgr_acstask.c and nvmc_mgr_acstask_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Read all data */
#define NVMC_READ_REDN_DATA_READING              (0U)
#define NVMC_READ_REDN_DATA_COMPLETE             (1U)
#define NVMC_READ_REDN_DATA_ERROR                (2U)
#define NVMC_READ_REDN_DATA_NODATA               (3U)

/* RIM access function target label */
#define NVMC_RW_TARGET_NON                       (0x00U)
#define NVMC_RW_TARGET_READ                      (0x01U)
#define NVMC_RW_TARGET_WRITE                     (0x02U)
/* #define NVMC_RW_TARGET_BOTH                      (NVMC_RW_TARGET_READ | NVMC_RW_TARGET_WRITE) */
#define NVMC_RW_TARGET_BOTH                      (0x03U)

/* RAM set logic label */
#define NVMC_SET_DATA_INDEX_SIZE                 (8U)
#define NVMC_SET_DATA_INDEX_MASK                 (0x07U)
#define NVMC_SET_DATA_INDEX_ID_BIT               (0x01U)
#define NVMC_SET_DATA_SET_PRM_NUM                (2U)
#define NVMC_SET_DATA_SET_PRM_OFFSET             (0U)
#define NVMC_SET_DATA_SET_PRM_DATA_NUM           (1U)

/* Read action index */
#define NVMC_READ_SEQ_NUM                        (4U)
#define NVMC_READ_SEQ_READING                    (0U)     /* Reading                   */
#define NVMC_READ_SEQ_CMPLT                      (1U)     /* Normal completion         */
#define NVMC_READ_SEQ_ERR_CMPLT                  (2U)     /* Error completion          */
#define NVMC_READ_SEQ_RAMNG_CMPLT                (3U)     /* RAM Error                 */

/* Read action table index */
#define NVMC_READ_ACT_ACT_NUM                    (2U)
#define NVMC_READ_ACT_ACT_NEXT_STATE             (0U)
#define NVMC_READ_ACT_ACT_RAM_UPDATE             (1U)

/* Write action index */
#define NVMC_WRITE_SEQ_DATA_NUM                  (5U)
#define NVMC_WRITE_SEQ_DATA_WRITING              (0U)
#define NVMC_WRITE_SEQ_DATA_VERIFY               (1U)
#define NVMC_WRITE_SEQ_DATA_COMPLETE             (2U)
#define NVMC_WRITE_SEQ_DATA_FAIL                 (3U)
#define NVMC_WRITE_SEQ_DATA_RAM_NG               (4U)

/* Write action table index */
#define NVMC_WRITE_ACT_ACT_NUM                   (2U)
#define NVMC_WRITE_ACT_ACT_NEXT_STATE            (0U)
#define NVMC_WRITE_ACT_ACT_RAM_UPDATE            (1U)

/* Recovery sequence label */
#define NVMC_RECOVERY_UNNECESARY                 (0U)
#define NVMC_RECOVERY_FOUND_LOST_DATA            (1U)
#define NVMC_RECOVERY_READ_AGAIN                 (2U)

#define NVMC_RECOVERY_STS_END                    (0xFFU)

/* Init Action label */
#define NVMC_INIT_ACT_NON                        (0U)     /* No read                       */
#define NVMC_INIT_ACT_READ_IMMDT                 (1U)     /* Read in initialization        */
#define NVMC_INIT_ACT_READ_LATER                 (2U)     /* Read after initialization     */
#define NVMC_INIT_ACT_RAMERR                     (3U)     /* Find RAM error but no read    */

/* RDN,STEP NO */
#define NVMC_RDNNO_BITLEN_MAX                    (8U)
#define NVMC_RDNNO_MAX                           (0xFFU)
#define NVMC_STEPNO_MAX                          (0xFFU)

#define NVMC_RDNNO_PREREAD                       (0U)

/* NEXT RDN NO */
#define NVMC_NEXTRDNNO_READ_NODATA               (0U)
#define NVMC_NEXTRDNNO_READ_OK                   (1U)
#define NVMC_NEXTRDNNO_MAX                       (1U)
#define NVMC_NEXTRDNNO_EXE_PREREAD               (0xFFU)

/* Result NG Size */
#define NVMC_NG_INVALID_SIZE                     (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2   u2_s_Nvmc_SearchInitNextID(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, U2 u2_a_nvmc_id, const U1 u1_a_WAKE_TYPE);
static U1   u1_s_Nvmc_GetWkupInitAct(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const U1 u1_a_WAKE_TYPE);
static U1   u1_s_Nvmc_GetAct_WkupCondNon(const ST_NVMC_CFGDATA * const st_ap_CFGDATA);
static U1   u1_s_Nvmc_GetAct_WkupCondAbnml(const ST_NVMC_CFGDATA * const st_ap_CFGDATA);

static U1   u1_s_Nvmc_InitReadSeq(const U1 u1_a_DEVICE, const U1 u1_a_WAKE_TYPE);
static void vd_s_Nvmc_InitDriverExecution(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, ST_NVMC_READ_BUF * st_ap_read_buf);

static U1   u1_s_Nvmc_SetData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const U4 * const u4_ap_DATA, const U1 u1_a_TARGET);

static void vd_s_Nvmc_AcsTask_NvmTrans(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const U2 u2_a_DATAID);
static void vd_s_Nvmc_AcsTask_Request(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const U2 u2_a_DATAID);

static U1   u1_s_Nvmc_AcsAppData(const U2 u2_a_NO);
static void vd_s_Nvmc_InitChgRequest(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const U2 u2_a_NO);
static U1   u1_s_Nvmc_AcsNvmRequest(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const U2 u2_a_NO);

static U1   u1_s_Nvmc_AcsNvmReadTrans(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const U2 u2_a_DATAID, const ST_NVMC_CFGDATA * const st_ap_CFGDATA);
static U1   u1_s_Nvmc_AcsNvmReadErrJudge(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_buf, const U1 u1_a_RDNSTS);

static U1   u1_s_Nvmc_ReadRednData(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const ST_NVMC_MODULE_CFG * const st_ap_MODULE_CFG);
static U1   u1_s_Nvmc_AcsNvmReadAct(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const U4 * const u4_ap_DATA, const U1 u1_a_ACT);

static U1   u1_s_Nvmc_AcsNvmWriteTrans(const ST_NVMC_DEVICE_CFG * st_ap_DEVICE_CFG, const U2 u2_a_DATAID, const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const U2 u2_a_NO);
static void vd_s_Nvmc_AcsNvmPreReadTrans(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const U2 u2_a_NO);
static U1   u1_s_Nvmc_PreReadRednData(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const ST_NVMC_MODULE_CFG * const st_ap_MODULE_CFG);
static void vd_s_Nvmc_AcsNvmWritingTrans(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const U2 u2_a_NO);
static U1   u1_s_Nvmc_AcsNvmVerifyTrans(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const U2 u2_a_DATAID, const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const U2 u2_a_NO);
static U1   u1_s_Nvmc_AcsNvmVerifyErrJudge(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_buf, const U1 u1_a_RDNSTS, ST_NVMC_WRITE_STS *st_ap_write_sts);
static U1   u1_s_Nvmc_AcsNvmWriteAct(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const U4 * const u4_ap_DATA, const U1 u1_a_ACT);

static U1   u1_s_Nvmc_IsExecPreRead(const  ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const ST_NVMC_WRITE_STS * const st_ap_WRITE_STS);
static U1   u1_s_Nvmc_ChkPreRead(const ST_NVMC_CFGDATA * const st_ap_CFGDATA);
static U1   u1_s_Nvmc_GetWriteRdnNo(const  ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const ST_NVMC_WRITE_STS * const st_ap_WRITE_STS);
static void vd_s_Nvmc_AddWriteRdnNo(const  ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const ST_NVMC_CFGDATA * const st_ap_CFGDATA, ST_NVMC_WRITE_STS *st_ap_write_sts);

static void vd_s_Nvmc_ClrNvmReadSts(ST_NVMC_READ_STS *st_ap_read_sts, const U2 u2_a_START_POS, const U2 u2_a_BUFSIZE);
static void vd_s_Nvmc_ClrNvmWriteSts(ST_NVMC_WRITE_STS *st_ap_write_sts);

static U1   u1_s_Nvmc_AcsNvmReadReq(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const ST_NVMC_CFGDATA * const  st_ap_CFGDATA, const ST_NVMC_READ_STS * const st_ap_READ_STS);
static U1   u1_s_Nvmc_ReadBlockReq(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const U2 u2_a_BLOCKID, ST_NVMC_READ_BUF * st_ap_temp_read_buf);

static U1   u1_s_Nvmc_AcsNvmWriteReq(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const ST_NVMC_WRITE_STS * const st_ap_WRITE_STS);
static U1 u1_s_Nvmc_WriteBlockReq(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const U2 u2_a_BLOCKID, const U1 * const u1_ap_DATA, ST_NVMC_WRITE_BUF * st_ap_temp_write_buf, const U2 u2_a_SIZE);

static U2   u2_s_Nvmc_GetBlockIdOffset(const U2 u2_a_OFFSET, const U1 u1_a_RDNNO, const U1 u1_a_STEP);

static U1   u1_s_Nvmc_SetReadBuffer(const U1 u1_a_DEVICE, const U1 u1_a_RESULT, const U1 * const u1_ap_DATA, const U2 u2_a_NUMBYTE);
static U1   u1_s_Nvmc_SetWriteBuffer(const U1 u1_a_DEVICE, const U1 u1_a_RESULT);
static void vd_s_Nvmc_InAppJobFinishHook(const U2 u2_a_NO, const U2 u2_a_BLOCKID, const U1 u1_a_REQUEST_TYPE, const U1 u1_a_RESULT, const U1 * const u1_ap_DATA, const U2 u2_a_SIZE);

static U1   u1_s_Nvmc_AcsNvmRecoveryTrans(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const U2 u2_a_NO);
static U1   u1_s_Nvmc_GetRdnRecovery(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, U2 * u2_ap_offset);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U1      u1_g_Nvmc_BonRead(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1      u1_g_Nvmc_BonRead(void)
{
    U1  u1_t_ret;
    U1  u1_t_device;

    u1_t_ret = (U1)FALSE;
    for(u1_t_device = (U1)0U; u1_t_device < u1_d_NVMC_DEVICE_TYPE_NUM; u1_t_device++){
        u1_t_ret |= u1_s_Nvmc_InitReadSeq(u1_t_device, (U1)NVMC_INIT_SEQ_READ_TYPE_BON);
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_g_Nvmc_WkupRead(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1      u1_g_Nvmc_WkupRead(void)
{
    U1  u1_t_ret;
    U1  u1_t_device;

    u1_t_ret = (U1)FALSE;
    for(u1_t_device = (U1)0U; u1_t_device < u1_d_NVMC_DEVICE_TYPE_NUM; u1_t_device++){
        u1_t_ret |= u1_s_Nvmc_InitReadSeq(u1_t_device, (U1)NVMC_INIT_SEQ_READ_TYPE_WAKE);
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_g_Nvmc_ReadBlock(const U1 u1_a_DEVICE, const U2 u2_a_BLOCKID)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u1_a_DEVICE  : DEVICE                                                                                        */
/*                  --> u2_a_BLOCKID : BlockId                                                                                       */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1      u1_g_Nvmc_ReadBlock(const U1 u1_a_DEVICE, const U2 u2_a_BLOCKID)
{
    U1  u1_t_ret;

    u1_t_ret = (U1)FALSE;
    if(u1_a_DEVICE < u1_d_NVMC_DEVICE_TYPE_NUM){
        u1_t_ret = u1_s_Nvmc_ReadBlockReq(&st_dp_NVMC_DEVICE_CFG[u1_a_DEVICE], u2_a_BLOCKID, &st_sp_nvmc_temp_read_buf[u1_a_DEVICE]);
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_g_Nvmc_WriteBlock(const U1 u1_a_DEVICE, const U2 u2_a_BLOCKID, const U1 * const u1_ap_DATA, const U2 u2_a_SIZE)       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u1_a_DEVICE  : DEVICE                                                                                        */
/*                  --> u2_a_BLOCKID : BlockId                                                                                       */
/*                  --> *u1_ap_DATA  : Write Data                                                                                    */
/*                  --> u2_a_SIZE    : Data Size                                                                                     */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1      u1_g_Nvmc_WriteBlock(const U1 u1_a_DEVICE, const U2 u2_a_BLOCKID, const U1 * const u1_ap_DATA, const U2 u2_a_SIZE)
{
    U1  u1_t_ret;

    u1_t_ret = (U1)FALSE;
    if(u1_ap_DATA != vdp_PTR_NA){
        if(u1_a_DEVICE < u1_d_NVMC_DEVICE_TYPE_NUM){
            u1_t_ret = u1_s_Nvmc_WriteBlockReq(&st_dp_NVMC_DEVICE_CFG[u1_a_DEVICE], u2_a_BLOCKID, u1_ap_DATA, &st_sp_nvmc_temp_write_buf[u1_a_DEVICE], u2_a_SIZE);
        }
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_g_Nvmc_EraseBlock(const U1 u1_a_DEVICE, const U2 u2_a_BLOCKID)                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u1_a_DEVICE : DEVICE                                                                                         */
/*                  --> u2_a_BLOCKID : BlockId                                                                                       */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1      u1_g_Nvmc_EraseBlock(const U1 u1_a_DEVICE, const U2 u2_a_BLOCKID)
{
    const       ST_NVMC_DEVICE_CFG  *   st_tp_DEVICE_CFG;
                ST_NVMC_WRITE_BUF   *   st_tp_temp_write_buf;
                U1                      u1_t_ret;
    volatile    U2                      u2_t_read_sync;

    u1_t_ret = (U1)FALSE;
    if(u1_a_DEVICE < u1_d_NVMC_DEVICE_TYPE_NUM){
        st_tp_DEVICE_CFG = &st_dp_NVMC_DEVICE_CFG[u1_a_DEVICE];
        if(st_tp_DEVICE_CFG->fp_p_u1_erase_block != vdp_PTR_NA){
            st_tp_temp_write_buf = &st_sp_nvmc_temp_write_buf[u1_a_DEVICE];
            st_tp_temp_write_buf->u2_blockid = (U2)NVMC_INVALID_BLOCK_ID;
            u2_t_read_sync = st_tp_temp_write_buf->u2_blockid;                      /* Dummy read for memory sync */
            st_tp_temp_write_buf->u1_writests = (U1)NVMC_RESULT_NON;
            st_tp_temp_write_buf->u2_timer = st_tp_DEVICE_CFG->u2_wr_timeout;
            st_tp_temp_write_buf->u2_blockid = u2_a_BLOCKID;                        /* Write last */
            u1_t_ret = (st_tp_DEVICE_CFG->fp_p_u1_erase_block)(u2_a_BLOCKID);
            if(u1_t_ret != (U1)TRUE){
                st_tp_temp_write_buf->u2_blockid = (U2)NVMC_INVALID_BLOCK_ID;
                st_tp_temp_write_buf->u1_writests = (U1)NVMC_RESULT_NG;
            }
        }
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_g_Nvmc_ReadDrctBlock(const U1 u1_a_DEVICE, const U2 u2_a_BLOCKID, U1 * u1_ap_data, const U2 u2_a_SIZE)                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u1_a_DEVICE  : DEVICE                                                                                        */
/*                  --> u2_a_BLOCKID : BlockId                                                                                       */
/*                  --> *u1_ap_data  : Read Data Pointer                                                                             */
/*                  --> u2_a_SIZE    : Data Size                                                                                     */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1      u1_g_Nvmc_ReadDrctBlock(const U1 u1_a_DEVICE, const U2 u2_a_BLOCKID, U1 * u1_ap_data, const U2 u2_a_SIZE)
{
    const   ST_NVMC_DEVICE_CFG  *   st_tp_DEVICE_CFG;
            U1                      u1_t_ret;

    u1_t_ret = (U1)NVMC_RESULT_NG;
    if(u1_a_DEVICE < u1_d_NVMC_DEVICE_TYPE_NUM){
        st_tp_DEVICE_CFG = &st_dp_NVMC_DEVICE_CFG[u1_a_DEVICE];
        if(st_tp_DEVICE_CFG->fp_p_u1_read_direct != vdp_PTR_NA){
            u1_t_ret = (st_tp_DEVICE_CFG->fp_p_u1_read_direct)(u2_a_BLOCKID, u1_ap_data, u2_a_SIZE);
        }
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_g_Nvmc_SuspendAcs(const U1 u1_a_DEVICE)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u1_a_DEVICE : DEVICE                                                                                         */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1      u1_g_Nvmc_SuspendAcs(const U1 u1_a_DEVICE)
{
    U1  u1_t_ret;
    U1  u1_t_num;
    U1  u1_t_cnt;

    u1_t_ret = (U1)TRUE;

    if(u1_a_DEVICE == (U1)NVMC_DEVICE_TYPE_ALL){
        u1_t_cnt = (U1)0U;
        u1_t_num = u1_d_NVMC_DEVICE_TYPE_NUM;
    }
    else if(u1_a_DEVICE < u1_d_NVMC_DEVICE_TYPE_NUM){
        u1_t_cnt = u1_a_DEVICE;
        u1_t_num = u1_t_cnt + (U1)NVMC_SINGLE_DEV_NUM;
    }
    else{
        u1_t_cnt = (U1)U1_MAX;
        u1_t_num = (U1)0U;
    }

    while(u1_t_cnt < u1_t_num){
        if(u2_dp_nvmc_proc_id[u1_t_cnt] == (U2)NVMC_REQID_TASK_IDLE){
            u1_dp_nvmc_suspend_req[u1_t_cnt] = (U1)FALSE;
            u2_dp_nvmc_suspend_timer[u1_t_cnt] = st_dp_NVMC_DEVICE_CFG[u1_t_cnt].u2_suspend_timeout;
        }
        else{
            u1_dp_nvmc_suspend_req[u1_t_cnt] = (U1)TRUE;
            u1_t_ret = (U1)FALSE;
        }

        u1_t_cnt++;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_g_Nvmc_IsSuspendAcs(const U1 u1_a_DEVICE)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u1_a_DEVICE : DEVICE                                                                                         */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1      u1_g_Nvmc_IsSuspendAcs(const U1 u1_a_DEVICE)
{
    U1  u1_t_ret;

    u1_t_ret = (U1)FALSE;

    if(u1_a_DEVICE < u1_d_NVMC_DEVICE_TYPE_NUM){
        if(
            (u1_dp_nvmc_suspend_req[u1_a_DEVICE]   == (U1)TRUE) ||
            (u2_dp_nvmc_suspend_timer[u1_a_DEVICE] != (U2)0U)
        ){
            u1_t_ret = (U1)TRUE;
        }
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  void    vd_g_Nvmc_JobFinishHook(const U1 u1_a_DEVICE, const U2 u2_a_BLOCKID, const U1 u1_a_REQUEST_TYPE, const U1 u1_a_RESULT, const U1 * const u1_ap_DATA, const U2 u2_a_NUM_BYTE)  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u1_a_DEVICE       : Device                                                                                   */
/*                  --> u2_a_BLOCKID      : Block ID                                                                                 */
/*                  --> u1_a_REQUEST_TYPE : Request Type                                                                             */
/*                  --> u1_a_RESULT       : Result                                                                                   */
/*                  --> *u1_ap_DATA       : Data                                                                                     */
/*                  --> u2_a_NUM_BYTE     : Data Size                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Nvmc_JobFinishHook(const U1 u1_a_DEVICE, const U2 u2_a_BLOCKID, const U1 u1_a_REQUEST_TYPE, const U1 u1_a_RESULT, const U1 * const u1_ap_DATA, const U2 u2_a_NUM_BYTE)
{
    const       ST_NVMC_DEVICE_CFG  *   st_tp_DEVICE_CFG;
    volatile    U2                  *   u2_tp_req_block_id;
                U2                      u2_t_nvmc_id;
                U2                      u2_t_no;
                U1                      u1_t_acsway;
                U1                      u1_t_rslt;

    if(u1_a_DEVICE < u1_d_NVMC_DEVICE_TYPE_NUM){
        st_tp_DEVICE_CFG = &st_dp_NVMC_DEVICE_CFG[u1_a_DEVICE];

        if(u2_a_BLOCKID != (U2)NVMC_INVALID_BLOCK_ID){
            u2_t_nvmc_id = u2_dp_nvmc_proc_id[u1_a_DEVICE];
            u1_t_acsway = u1_d_Nvmc_GetDataTblNo(st_tp_DEVICE_CFG, u2_t_nvmc_id, &u2_t_no);
            if(u1_a_REQUEST_TYPE == (U1)NVMC_REQUEST_TYPE_READ){
                u2_tp_req_block_id = &(st_sp_nvmc_temp_read_buf[u1_a_DEVICE].u2_blockid);
                if(*u2_tp_req_block_id == u2_a_BLOCKID){
                    *u2_tp_req_block_id = (U2)NVMC_INVALID_BLOCK_ID;
                    u1_t_rslt = u1_s_Nvmc_SetReadBuffer(u1_a_DEVICE, u1_a_RESULT, u1_ap_DATA, u2_a_NUM_BYTE);
                    if(u1_t_acsway == (U1)NVMC_ACS_INAPP){
                        /* Call hook function of application access */
                        vd_s_Nvmc_InAppJobFinishHook(u2_t_no, u2_a_BLOCKID, u1_a_REQUEST_TYPE, u1_t_rslt, u1_ap_DATA, u2_a_NUM_BYTE);
                    }
                }
            }
            else if(
                (u1_a_REQUEST_TYPE == (U1)NVMC_REQUEST_TYPE_WRITE) ||
                (u1_a_REQUEST_TYPE == (U1)NVMC_REQUEST_TYPE_ERASE)
            ){
                u2_tp_req_block_id = &(st_sp_nvmc_temp_write_buf[u1_a_DEVICE].u2_blockid);
                if(*u2_tp_req_block_id == u2_a_BLOCKID){
                    *u2_tp_req_block_id = (U2)NVMC_INVALID_BLOCK_ID;
                    u1_t_rslt = u1_s_Nvmc_SetWriteBuffer(u1_a_DEVICE, u1_a_RESULT);
                    if(u1_t_acsway == (U1)NVMC_ACS_INAPP){
                        /* Call hook function of application access */
                        vd_s_Nvmc_InAppJobFinishHook(u2_t_no, u2_a_BLOCKID, u1_a_REQUEST_TYPE, u1_t_rslt, u1_ap_DATA, u2_a_NUM_BYTE);
                    }
                }
            }
            else{
                /* Nothing to do */
            }
        }
    }
}

/*===================================================================================================================================*/
/*  void    vd_d_Nvmc_AcsTaskRamInit(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_d_Nvmc_AcsTaskRamInit(void)
{
    const   ST_NVMC_DEVICE_CFG  *   st_tp_DEVICE_CFG;
            ST_NVMC_READ_BUF    *   st_tp_read_buf;
            ST_NVMC_WRITE_BUF   *   st_tp_write_buf;
            ST_NVMC_READ_STS    *   st_tp_read_sts;
            ST_NVMC_WRITE_STS   *   st_tp_write_base;
            ST_NVMC_WRITE_STS   *   st_tp_write_sts;
            U2                      u2_t_cnt;
            U2                      u2_t_rimid;
            U1                      u1_t_device;

    for(u1_t_device = (U1)0U; u1_t_device < u1_d_NVMC_DEVICE_TYPE_NUM; u1_t_device++){
        st_tp_DEVICE_CFG = &st_dp_NVMC_DEVICE_CFG[u1_t_device];

        u2_dp_nvmc_suspend_timer[u1_t_device] = (U2)0U;
        u1_dp_nvmc_suspend_req[u1_t_device] = (U1)FALSE;
        (void)u1_g_Rim_WriteU2withStatus(st_tp_DEVICE_CFG->u2_rimid_initid, (U2)0U);
        u2_dp_nvmc_proc_id[u1_t_device] = (U2)NVMC_REQID_TASK_IDLE;

        u2_t_rimid = st_tp_DEVICE_CFG->u2_rimid_recovery_proc;
        if(u2_t_rimid != (U2)NVMC_INVALID_RIM_ID){
            (void)u1_g_Rim_WriteU2withStatus(u2_t_rimid, (U2)0U);
            vd_d_Nvmc_SetAcsReqSub(st_tp_DEVICE_CFG, st_tp_DEVICE_CFG->u2_recovery_req_id, (U1)FALSE);
        }
        u1_dp_nvmc_recovery_retry[u1_t_device] = (U1)0U;

        st_tp_read_sts = &st_sp_nvmc_read_sts[u1_t_device];
        vd_s_Nvmc_ClrNvmReadSts(st_tp_read_sts, st_tp_DEVICE_CFG->u2_t_buf_base, (U2)0U);    /* Read buffers are not clear here. */
        st_tp_read_sts->u1_rangeretry = (U1)0U;
        st_tp_write_base = &st_sp_nvmc_write_sts[st_tp_DEVICE_CFG->u2_t_write_sts_base];
        for(u2_t_cnt = (U2)0U; u2_t_cnt < st_tp_DEVICE_CFG->u2_innvm_num; u2_t_cnt++){
            st_tp_write_sts = &st_tp_write_base[u2_t_cnt];
            vd_s_Nvmc_ClrNvmWriteSts(st_tp_write_sts);
            st_tp_write_sts->u1_verifyretry = (U1)0U;
        }
        (void)u1_g_Rim_WriteU1withStatus(st_tp_DEVICE_CFG->u2_rimid_next_write_rdnno, (U1)NVMC_NEXTRDNNO_EXE_PREREAD);

        st_tp_read_buf = &st_sp_nvmc_temp_read_buf[u1_t_device];
        st_tp_read_buf->u1_readsts = (U1)NVMC_RESULT_NON;
        st_tp_read_buf->u2_timer = (U2)0U;
        st_tp_read_buf->u2_blockid = (U2)NVMC_INVALID_BLOCK_ID;
        st_tp_read_buf->u2_req_size = (U2)NVMC_NG_INVALID_SIZE;
        vd_g_MemfillU4(st_tp_read_buf->u4_buf, (U4)0U, (U4)NVMC_BUF_SIZE);

        st_tp_write_buf = &st_sp_nvmc_temp_write_buf[u1_t_device];
        st_tp_write_buf->u1_writests = (U1)NVMC_RESULT_NON;
        st_tp_write_buf->u2_timer = (U2)0U;
        st_tp_write_buf->u2_blockid = (U2)NVMC_INVALID_BLOCK_ID;
    }
    for(u2_t_cnt = (U2)0U; u2_t_cnt < (U2)u1_d_NVMC_READ_BUF_SIZE; u2_t_cnt++){
        u4_dp_nvmc_read_data_buf[u2_t_cnt] = (U4)0U;
        u1_dp_nvmc_read_status_buf[u2_t_cnt] = (U1)NVMC_RESULT_NON;
    }
}

/*===================================================================================================================================*/
/*  void    vd_d_Nvmc_SearchInitID(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const U1 u1_a_WAKE_TYPE)                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> st_ap_DEVICE_CFG : DEVICE Pointer                                                                            */
/*                  --> u1_a_WAKE_TYPE   : Wakeup Type                                                                               */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_d_Nvmc_SearchInitID(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const U1 u1_a_WAKE_TYPE)
{
    U2  u2_t_data_id;

    u2_t_data_id = u2_s_Nvmc_SearchInitNextID(st_ap_DEVICE_CFG, (U2)0U, u1_a_WAKE_TYPE);
    (void)u1_g_Rim_WriteU2withStatus(st_ap_DEVICE_CFG->u2_rimid_initid, u2_t_data_id);
    u2_dp_nvmc_proc_id[st_ap_DEVICE_CFG->u1_dev_num] = u2_t_data_id;
}

/*===================================================================================================================================*/
/*  void    vd_d_Nvmc_InitNvmWriteSts(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const U2 u2_a_NO)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> st_ap_DEVICE_CFG : DEVICE Pointer                                                                            */
/*                  --> u2_a_NO          : TBL No                                                                                    */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_d_Nvmc_InitNvmWriteSts(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const U2 u2_a_NO)
{
    ST_NVMC_WRITE_STS   *   st_tp_write_sts;

    st_tp_write_sts = &st_sp_nvmc_write_sts[(u2_a_NO + st_ap_DEVICE_CFG->u2_t_write_sts_base)];

    vd_s_Nvmc_ClrNvmWriteSts(st_tp_write_sts);
    st_tp_write_sts->u1_verifyretry = (U1)0U;
}


/*===================================================================================================================================*/
/*  void    vd_d_Nvmc_ChkDeviceTimer(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_d_Nvmc_ChkDeviceTimer(void)
{
    const   ST_NVMC_DEVICE_CFG  *   st_tp_DEVICE_CFG;
            ST_NVMC_READ_BUF    *   st_tp_read_buf;
            ST_NVMC_WRITE_BUF   *   st_tp_write_buf;
            U2                      u2_t_block_id;
            U1                      u1_t_device;
            U1                      u1_t_rslt;
            U1                      u1_t_data;

    u1_t_data = (U1)0U;
    for(u1_t_device = (U1)0U; u1_t_device < u1_d_NVMC_DEVICE_TYPE_NUM; u1_t_device++){
        st_tp_DEVICE_CFG = &st_dp_NVMC_DEVICE_CFG[u1_t_device];
        /* Check Read Timeout */
        st_tp_read_buf = &st_sp_nvmc_temp_read_buf[u1_t_device];
        u1_t_rslt = u1_d_Nvmc_TickTime(&(st_tp_read_buf->u2_timer), st_tp_DEVICE_CFG->u2_rd_timeout);
        u2_t_block_id = st_tp_read_buf->u2_blockid;
        if(
            (u1_t_rslt == (U1)TRUE) &&
            (u2_t_block_id != (U2)NVMC_INVALID_BLOCK_ID)
        ){
            vd_g_Nvmc_JobFinishHook(u1_t_device, u2_t_block_id, (U1)NVMC_REQUEST_TYPE_READ, (U1)NVMC_RESULT_NG, &u1_t_data, (U2)0U);
        }
        /* Check Write Timeout */
        st_tp_write_buf = &st_sp_nvmc_temp_write_buf[u1_t_device];
        u1_t_rslt = u1_d_Nvmc_TickTime(&(st_tp_write_buf->u2_timer), st_tp_DEVICE_CFG->u2_wr_timeout);
        u2_t_block_id = st_tp_write_buf->u2_blockid;
        if(
            (u1_t_rslt == (U1)TRUE) &&
            (u2_t_block_id != (U2)NVMC_INVALID_BLOCK_ID)
        ){
            vd_g_Nvmc_JobFinishHook(u1_t_device, u2_t_block_id, (U1)NVMC_REQUEST_TYPE_WRITE, (U1)NVMC_RESULT_NG, &u1_t_data, (U2)0U);
        }
        /* Check Suspend Timer */
        (void)u1_d_Nvmc_TickTime(&u2_dp_nvmc_suspend_timer[u1_t_device], st_tp_DEVICE_CFG->u2_suspend_timeout);
    }
}


/*===================================================================================================================================*/
/*  void    vd_d_Nvmc_AcsTask(const U1 u1_a_DEVICE)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u1_a_DEVICE : DEVICE                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_d_Nvmc_AcsTask(const U1 u1_a_DEVICE)
{
    const       ST_NVMC_DEVICE_CFG  *   st_tp_DEVICE_CFG;
                U2                      u2_t_req_id;
                U1                      u1_t_is_idle;

    st_tp_DEVICE_CFG = &st_dp_NVMC_DEVICE_CFG[u1_a_DEVICE];
    u1_t_is_idle = st_tp_DEVICE_CFG->fp_p_u1_is_idle();
    if(u1_t_is_idle == (U1)TRUE){
        u2_t_req_id = (U2)NVMC_REQID_TASK_IDLE;
        (void)u1_g_Rim_ReadU2withStatus(st_tp_DEVICE_CFG->u2_rimid_initid, &u2_t_req_id);
        vd_s_Nvmc_AcsTask_NvmTrans(st_tp_DEVICE_CFG, u2_t_req_id);

        if(u2_dp_nvmc_suspend_timer[u1_a_DEVICE] == (U2)0U){
            vd_s_Nvmc_AcsTask_Request(st_tp_DEVICE_CFG, u2_t_req_id);

            if(u1_dp_nvmc_suspend_req[u1_a_DEVICE] == (U1)TRUE){
                if(u2_dp_nvmc_proc_id[u1_a_DEVICE] == (U2)NVMC_REQID_TASK_IDLE){
                    u2_dp_nvmc_suspend_timer[u1_a_DEVICE] = st_tp_DEVICE_CFG->u2_suspend_timeout;
                    u1_dp_nvmc_suspend_req[u1_a_DEVICE] = (U1)FALSE;
                }
            }
        }
    }
}


/*===================================================================================================================================*/
/*  void    vd_d_Nvmc_Recovery(const U1 u1_a_DEVICE)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u1_a_DEVICE       : Device                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_d_Nvmc_Recovery(const U1 u1_a_DEVICE)
{
    const   ST_NVMC_DEVICE_CFG  *   st_tp_DEVICE_CFG;
    const   ST_NVMC_CFGDATA     *   st_tp_CFGDATA;
            U2                      u2_t_proc_no;
            U1                      u1_t_rslt;
            U1                      u1_t_recoverable;
            U1                      u1_t_map_ptrn;

    st_tp_DEVICE_CFG = &st_dp_NVMC_DEVICE_CFG[u1_a_DEVICE];

    u2_t_proc_no = (U2)NVMC_INVALID_CACHE_ID;
    (void)u1_g_Rim_ReadU2withStatus(st_tp_DEVICE_CFG->u2_rimid_recovery_proc, &u2_t_proc_no);
    u1_t_rslt = u1_d_Nvmc_IsRecoveryEnable();
    if(
        (u1_t_rslt == (U1)TRUE) &&
        (u2_t_proc_no < st_tp_DEVICE_CFG->u2_innvm_num)
    ){
        do{
            u1_t_recoverable = (U1)0U;
            st_tp_CFGDATA = &((st_tp_DEVICE_CFG->st_p_CFGDATA)[u2_t_proc_no]);
            u1_t_map_ptrn = st_tp_CFGDATA->u1_map;
            if(u1_t_map_ptrn < u1_d_NVMC_MODULE_NUM){
                u1_t_recoverable = st_dp_NVMC_MODULE_CFG[u1_t_map_ptrn].u1_attr;
                u1_t_recoverable &= (U1)NVMC_MOD_ATTR_RECOVERABLE_BIT;
            }
            if(
                (u1_t_recoverable != (U1)0U) &&
                ((st_tp_CFGDATA->u4_module_bit_cfg & (U4)NVMC_DATA_ATTR_BIT_RECOVERY) != (U4)0U)
            ){
                u1_t_rslt = u1_s_Nvmc_AcsNvmRecoveryTrans(st_tp_DEVICE_CFG, st_tp_CFGDATA, u2_t_proc_no);
                if(u1_t_rslt == (U1)TRUE){
                    u1_dp_nvmc_recovery_retry[u1_a_DEVICE] = (U1)0U;
                    u2_t_proc_no++;
                }
                break;
            }
            u2_t_proc_no++;
        }while(u2_t_proc_no < st_tp_DEVICE_CFG->u2_innvm_num);
        (void)u1_g_Rim_WriteU2withStatus(st_tp_DEVICE_CFG->u2_rimid_recovery_proc, u2_t_proc_no);
    }
    else{
        vd_d_Nvmc_SetAcsReqSub(st_tp_DEVICE_CFG, st_tp_DEVICE_CFG->u2_recovery_req_id, (U1)FALSE);
    }
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Static Functions                                                                                                                 */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*===================================================================================================================================*/
/*  static U2   u2_s_Nvmc_SearchInitNextID(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, U2 u2_a_nvmc_id, const U1 u1_a_WAKE_TYPE) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> st_ap_DEVICE_CFG : DEVICE Pointer                                                                            */
/*                  --> u2_a_nvmc_id     : NvmcId                                                                                    */
/*                  --> u1_a_WAKE_TYPE   : Wakeup Type                                                                               */
/*  Return:         U2 u2_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
static U2   u2_s_Nvmc_SearchInitNextID(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, U2 u2_a_nvmc_id, const U1 u1_a_WAKE_TYPE)
{
    const   ST_NVMC_CFGDATA     *   st_tp_CFGDATA;
            ST_NVMC_READ_STS    *   st_tp_read_sts;
            U2                      u2_t_in_id;
            U2                      u2_t_ret;
            U1                      u1_t_access_type;
            U1                      u1_t_act;
            U1                      u1_t_map_ptrn;

    u2_t_ret = (U2)NVMC_REQID_TASK_IDLE;
    while(u2_a_nvmc_id < st_ap_DEVICE_CFG->u2_id_num){
        u2_t_in_id = (U2)0U;
        u1_t_access_type = u1_d_Nvmc_GetDataTblNo(st_ap_DEVICE_CFG, u2_a_nvmc_id, &u2_t_in_id);
        if(u1_t_access_type != (U1)NVMC_ACS_INNVM){
            if(u2_a_nvmc_id != st_ap_DEVICE_CFG->u2_recovery_req_id){
                /* Clear request bit */
                vd_d_Nvmc_SetAcsReqSub(st_ap_DEVICE_CFG, u2_a_nvmc_id, (U1)FALSE);
            }
        }
        else{
            st_tp_CFGDATA = &((st_ap_DEVICE_CFG->st_p_CFGDATA)[u2_t_in_id]);
            u1_t_act = u1_s_Nvmc_GetWkupInitAct(st_tp_CFGDATA, u1_a_WAKE_TYPE);
            if(u1_t_act == (U1)NVMC_INIT_ACT_READ_IMMDT){
                u2_t_ret = u2_a_nvmc_id;
                (void)u1_g_Rim_WriteU1withStatus(st_tp_CFGDATA->u2_rimid_nvmsts, (U1)NVMC_STATUS_READING);
                u1_t_map_ptrn = st_tp_CFGDATA->u1_map;
                if(u1_t_map_ptrn < u1_d_NVMC_MODULE_NUM){
                    st_tp_read_sts = &st_sp_nvmc_read_sts[st_ap_DEVICE_CFG->u1_dev_num];
                    vd_s_Nvmc_ClrNvmReadSts(st_tp_read_sts, st_ap_DEVICE_CFG->u2_t_buf_base, (U2)st_ap_DEVICE_CFG->u1_use_bufsize);
                    st_tp_read_sts->u1_rangeretry = (U1)0U;
                }
                break;
            }
            else if(u1_t_act == (U1)NVMC_INIT_ACT_READ_LATER){
                /* Change status to Reading */
                (void)u1_g_Rim_WriteU1withStatus(st_tp_CFGDATA->u2_rimid_nvmsts, (U1)NVMC_STATUS_READING);
            }
            else if(u1_t_act == (U1)NVMC_INIT_ACT_RAMERR){
                /* Set status to NG and clear request bit */
                (void)u1_g_Rim_WriteU1withStatus(st_tp_CFGDATA->u2_rimid_nvmsts, (U1)NVMC_STATUS_CACHE_NG);
                vd_d_Nvmc_SetAcsReqSub(st_ap_DEVICE_CFG, u2_a_nvmc_id, (U1)FALSE);
            }
            else{
                /* Clear request bit */
                vd_d_Nvmc_SetAcsReqSub(st_ap_DEVICE_CFG, u2_a_nvmc_id, (U1)FALSE);
            }
        }
        u2_a_nvmc_id++;
    }
    return(u2_t_ret);
}

/*===================================================================================================================================*/
/*  static U1   u1_s_Nvmc_GetWkupInitAct(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const U1 u1_a_WAKE_TYPE)                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA : CFG DATA                                                                                    */
/*                  --> u1_a_WAKE_TYPE : Wakeup Type                                                                                 */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
static U1   u1_s_Nvmc_GetWkupInitAct(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const U1 u1_a_WAKE_TYPE)
{
    U1  u1_t_ret;

    if(u1_a_WAKE_TYPE == (U1)NVMC_INIT_SEQ_READ_TYPE_BON){
        if((st_ap_CFGDATA->u1_mgr_bit_cfg & (U1)NVMC_SETT_CMN_BON_TIMING_MASK) != (U1)0U){
            u1_t_ret = (U1)NVMC_INIT_ACT_READ_LATER;
        }
        else{
            u1_t_ret = (U1)NVMC_INIT_ACT_READ_IMMDT;
        }
    }
    else{
        switch(st_ap_CFGDATA->u1_mgr_bit_cfg & (U1)NVMC_SETT_CMN_WKUP_COND_MASK){
            case NVMC_SETT_CMN_WKUP_COND_EVRY:
                u1_t_ret = (U1)NVMC_INIT_ACT_READ_IMMDT;
                break;

            case NVMC_SETT_CMN_WKUP_COND_ABNML:
                u1_t_ret = u1_s_Nvmc_GetAct_WkupCondAbnml(st_ap_CFGDATA);
                break;

            case NVMC_SETT_CMN_WKUP_COND_NON:
            default:
                u1_t_ret = u1_s_Nvmc_GetAct_WkupCondNon(st_ap_CFGDATA);
                break;
        }
        if(
            (u1_t_ret == (U1)NVMC_INIT_ACT_READ_IMMDT) &&
            ((st_ap_CFGDATA->u1_mgr_bit_cfg & (U1)NVMC_SETT_CMN_WKUP_TIMING_MASK) != (U1)0U)
        ){
            u1_t_ret = (U1)NVMC_INIT_ACT_READ_LATER;
        }
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1   u1_s_Nvmc_GetAct_WkupCondNon(const ST_NVMC_CFGDATA * const st_ap_CFGDATA)                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA : CFG DATA                                                                                    */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
static U1   u1_s_Nvmc_GetAct_WkupCondNon(const ST_NVMC_CFGDATA * const st_ap_CFGDATA)
{
    U1  u1_t_ret;
    U1  u1_t_sts;

    u1_t_ret = (U1)NVMC_INIT_ACT_NON;
    u1_t_sts = (U1)NVMC_STATUS_CACHE_NG;
    (void)u1_g_Rim_ReadU1withStatus(st_ap_CFGDATA->u2_rimid_nvmsts, &u1_t_sts);
    if(
        (u1_t_sts == (U1)NVMC_STATUS_COMP) ||
        (u1_t_sts == (U1)NVMC_STATUS_ERRCOMP)
    ){
        /* u1_t_ret = (U1)NVMC_INIT_ACT_NON; */
    }
    else if(
        (u1_t_sts == (U1)NVMC_STATUS_READING) ||
        (u1_t_sts == (U1)NVMC_STATUS_WRITING)
    ){
        u1_t_ret = (U1)NVMC_INIT_ACT_READ_IMMDT;
    }
    else{
        if((st_ap_CFGDATA->u1_mgr_bit_cfg & (U1)NVMC_SETT_CMN_ERR_SYNC_MASK) != (U1)0U){
            u1_t_ret = (U1)NVMC_INIT_ACT_READ_IMMDT;
        }
        else{
            u1_t_ret = (U1)NVMC_INIT_ACT_RAMERR;
        }
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1   u1_s_Nvmc_GetAct_WkupCondAbnml(const ST_NVMC_CFGDATA * const st_ap_CFGDATA)                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA : CFG DATA                                                                                    */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
static U1   u1_s_Nvmc_GetAct_WkupCondAbnml(const ST_NVMC_CFGDATA * const st_ap_CFGDATA)
{
    U4  u4_tp_rbuf[NVMC_BUF_SIZE];
    U4  u4_tp_wbuf[NVMC_BUF_SIZE];
    U2  u2_t_rimid;
    U2  u2_t_size;
    U2  u2_t_index;
    U2  u2_t_array_size;
    U1  u1_t_ret;
    U1  u1_t_rslt;
    U1  u1_t_sts;
    U1  u1_t_compare_ok;
    U1  u1_t_map_ptrn;

    u1_t_sts = (U1)NVMC_STATUS_CACHE_NG;
    u1_t_map_ptrn = st_ap_CFGDATA->u1_map;
    u2_t_size = (U2)0U;
    if(u1_t_map_ptrn < u1_d_NVMC_MODULE_NUM){
        u2_t_size = (U2)st_dp_NVMC_MODULE_CFG[u1_t_map_ptrn].u1_datasize;
    }
    u1_t_rslt = u1_g_Rim_ReadU1withStatus(st_ap_CFGDATA->u2_rimid_nvmsts, &u1_t_sts);
    if(u1_t_sts != (U1)NVMC_STATUS_COMP){
        u1_t_rslt |= (U1)RIM_RESULT_KIND_NG;
    }
    else if(u2_t_size == (U2)0U){
        /* For failsafe, set RIM OK to return NVMC_INIT_ACT_NON. */
        u1_t_rslt = (U1)RIM_RESULT_KIND_OK;
    }
    else{
        u2_t_rimid = st_ap_CFGDATA->u2_rimid_wdata;
        u2_t_array_size = (u2_t_size + (U2)NVMC_ARRAY_INDEX_MASK) >> NVMC_ARRAY_INDEX_SHIFT;
        u2_t_index = u2_t_array_size - (U2)1U;       /* No underflow */
        u4_tp_wbuf[u2_t_index] = (U4)0U;
        u1_t_rslt |= u1_d_Nvmc_GetRimData(u2_t_rimid, u4_tp_wbuf, u2_t_size);
        if((st_ap_CFGDATA->u1_mgr_bit_cfg & (U1)NVMC_SETT_CMN_READID_MASK) != (U1)0U){
            u2_t_rimid++;
            u4_tp_rbuf[u2_t_index] = (U4)0U;
            u1_t_rslt |= u1_d_Nvmc_GetRimData(u2_t_rimid, u4_tp_rbuf, u2_t_size);
            if((u1_t_rslt & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
                u1_t_compare_ok = u1_d_Rim_CompareOther(u4_tp_wbuf, u4_tp_rbuf, u2_t_array_size);
                if(u1_t_compare_ok == (U1)FALSE){
                    u1_t_rslt |= (U1)RIM_RESULT_KIND_NG;
                }
            }
        }
    }
    u1_t_ret = (U1)NVMC_INIT_ACT_NON;
    if((u1_t_rslt & (U1)RIM_RESULT_KIND_MASK) != (U1)RIM_RESULT_KIND_OK){
        u1_t_ret = (U1)NVMC_INIT_ACT_READ_IMMDT;
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1 u1_s_Nvmc_InitReadSeq(const U1 u1_a_DEVICE, const U1 u1_a_WAKE_TYPE)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u1_a_DEVICE    : Device                                                                                      */
/*                  --> u1_a_WAKE_TYPE : Wakeup Type                                                                                 */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
static U1 u1_s_Nvmc_InitReadSeq(const U1 u1_a_DEVICE, const U1 u1_a_WAKE_TYPE)
{
    const   ST_NVMC_DEVICE_CFG  *   st_tp_DEVICE_CFG;
    const   ST_NVMC_CFGDATA     *   st_tp_CFGDATA;
            ST_NVMC_READ_STS    *   st_tp_read_sts;
            ST_NVMC_READ_BUF    *   st_tp_read_buf;
            U2                      u2_t_data_id;
            U2                      u2_t_cache_id;
            U1                      u1_t_access_type;
            U1                      u1_t_ret;
            U1                      u1_t_read_rsult;
            U1                      u1_t_data_sts;

    u1_t_ret = (U1)FALSE;
    st_tp_DEVICE_CFG = &st_dp_NVMC_DEVICE_CFG[u1_a_DEVICE];
    u2_t_data_id = (U2)0U;
    (void)u1_g_Rim_ReadU2withStatus(st_tp_DEVICE_CFG->u2_rimid_initid, &u2_t_data_id);
    if(u2_t_data_id < st_tp_DEVICE_CFG->u2_id_num){
        u2_t_cache_id = (U2)0U;
        u1_t_data_sts = (U1)NVMC_STATUS_CACHE_NG;
        u1_t_access_type = u1_d_Nvmc_GetDataTblNo(st_tp_DEVICE_CFG, u2_t_data_id, &u2_t_cache_id);
        if(u1_t_access_type == (U1)NVMC_ACS_INNVM){
            st_tp_CFGDATA = &((st_tp_DEVICE_CFG->st_p_CFGDATA)[u2_t_cache_id]);
            if(st_tp_CFGDATA->u1_map < u1_d_NVMC_MODULE_NUM){
                st_tp_read_sts = &st_sp_nvmc_read_sts[u1_a_DEVICE];
                u1_t_read_rsult = u1_s_Nvmc_AcsNvmReadReq(st_tp_DEVICE_CFG, st_tp_CFGDATA, st_tp_read_sts);
                st_tp_read_buf = &st_sp_nvmc_temp_read_buf[u1_a_DEVICE];
                if(u1_t_read_rsult == (U1)TRUE){
                    /* Overwrite timer for initial read */
                    st_tp_read_buf->u2_timer = st_tp_DEVICE_CFG->u2_syncrd_timeout;
                }
                /* Execute driver task and check timer. */
                vd_s_Nvmc_InitDriverExecution(st_tp_DEVICE_CFG, &st_tp_read_buf[0]);
                u1_t_data_sts = u1_s_Nvmc_AcsNvmReadTrans(st_tp_DEVICE_CFG, u2_t_data_id, st_tp_CFGDATA);
                /* Set status */
                if(u1_t_data_sts != (U1)NVMC_STATUS_READING){
                    (void)u1_g_Rim_WriteU1withStatus(st_tp_CFGDATA->u2_rimid_nvmsts, u1_t_data_sts);
                }
            }
            else{
                u1_t_data_sts = (U1)NVMC_STATUS_ERRCOMP;
            }
        }
        if(u1_t_data_sts != (U1)NVMC_STATUS_READING){
            /* Clear request bit */
            vd_d_Nvmc_SetAcsReqSub(st_tp_DEVICE_CFG, u2_t_data_id, (U1)FALSE);
            /* Search Next ID */
            u2_t_data_id++;
            u2_t_data_id = u2_s_Nvmc_SearchInitNextID(st_tp_DEVICE_CFG, u2_t_data_id, u1_a_WAKE_TYPE);
            (void)u1_g_Rim_WriteU2withStatus(st_tp_DEVICE_CFG->u2_rimid_initid, u2_t_data_id);
            u2_dp_nvmc_proc_id[u1_a_DEVICE] = u2_t_data_id;
            if(u2_t_data_id < st_tp_DEVICE_CFG->u2_id_num){
                u1_t_ret = (U1)TRUE;
            }
        }
        else{
            u1_t_ret = (U1)TRUE;
        }
    }
    else{
        u2_dp_nvmc_proc_id[u1_a_DEVICE] = (U2)NVMC_REQID_TASK_IDLE;
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static void vd_s_Nvmc_InitDriverExecution(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, ST_NVMC_READ_BUF * st_ap_read_buf)  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> st_ap_DEVICE_CFG : DEVICE Pointer                                                                            */
/*                  --> *st_ap_read_buf  : Read Buffer                                                                               */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Nvmc_InitDriverExecution(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, ST_NVMC_READ_BUF * st_ap_read_buf)
{
    U1  u1_t_is_idle;
    U1  u1_t_rslt;

    u1_t_is_idle = st_ap_DEVICE_CFG->fp_p_u1_is_idle();
    while(u1_t_is_idle == (U1)FALSE){
        u1_t_rslt = u1_d_Nvmc_TickTime(&(st_ap_read_buf->u2_timer), st_ap_DEVICE_CFG->u2_syncrd_timeout);
        if(u1_t_rslt == (U1)TRUE){
            /* st_ap_read_buf->u2_timer = (U2)0U; */                            /* The variable is cleared in u1_d_Nvmc_TickTime */
            st_ap_read_buf->u1_readsts = (U1)NVMC_RESULT_NG;
            break;
        }
        st_ap_DEVICE_CFG->fp_p_vd_execution_func();
        u1_t_is_idle = st_ap_DEVICE_CFG->fp_p_u1_is_idle();
    }
}


/*===================================================================================================================================*/
/*  static U1   u1_s_Nvmc_SetData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const U4 * const u4_ap_DATA, const U1 u1_a_TARGET)    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA : CFG DATA                                                                                    */
/*                  --> *u4_ap_DATA    : Data Pointer                                                                                */
/*                  --> u1_a_TARGET    : Target                                                                                      */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
static U1   u1_s_Nvmc_SetData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const U4 * const u4_ap_DATA, const U1 u1_a_TARGET)
{
    static const U1 u1_sp_NVMC_SET_DATA_PRM_TBL[NVMC_SET_DATA_INDEX_SIZE][NVMC_SET_DATA_SET_PRM_NUM] = {
        {(U1)0U,     (U1)0U},             /* No data access    */
        {(U1)0U,     (U1)0U},             /* No data access    */
        {(U1)0U,     (U1)1U},             /* Read data access  */
        {(U1)1U,     (U1)1U},             /* Read data access  */
        {(U1)0U,     (U1)1U},             /* Write data access */
        {(U1)0U,     (U1)1U},             /* Write data access */
        {(U1)0U,     (U1)1U},             /* Both data access  */
        {(U1)0U,     (U1)2U}              /* Both data access  */
    };
    U2  u2_t_rimid;
    U2  u2_t_size;
    U1  u1_t_rslt;
    U1  u1_t_num;
    U1  u1_t_index;
    U1  u1_t_ret;
    U1  u1_t_map_ptrn;

    u1_t_ret = (U1)TRUE;
    u1_t_map_ptrn = st_ap_CFGDATA->u1_map;
    if(u1_t_map_ptrn < u1_d_NVMC_MODULE_NUM){
        u2_t_size = (U2)(st_dp_NVMC_MODULE_CFG[u1_t_map_ptrn].u1_datasize);
        u1_t_index = u1_a_TARGET << 1U;
        if((st_ap_CFGDATA->u1_mgr_bit_cfg & (U1)NVMC_SETT_CMN_READID_MASK) != (U1)0U){
            u1_t_index |= (U1)NVMC_SET_DATA_INDEX_ID_BIT;
        }
        u1_t_index &= (U1)NVMC_SET_DATA_INDEX_MASK;
        u2_t_rimid = st_ap_CFGDATA->u2_rimid_wdata;
        u2_t_rimid += u1_sp_NVMC_SET_DATA_PRM_TBL[u1_t_index][NVMC_SET_DATA_SET_PRM_OFFSET];
        u1_t_num = u1_sp_NVMC_SET_DATA_PRM_TBL[u1_t_index][NVMC_SET_DATA_SET_PRM_DATA_NUM];
        u1_t_rslt = (U1)0U;
        while(u1_t_num > (U1)0U){
            u1_t_rslt |= u1_d_Nvmc_SetRimData(u2_t_rimid, u4_ap_DATA, u2_t_size);
            u1_t_num--;
            u2_t_rimid++;
        }
        u1_t_rslt &= (U1)RIM_RESULT_KIND_MASK;
        if(u1_t_rslt != (U1)RIM_RESULT_KIND_OK){
            u1_t_ret = (U1)FALSE;
        }
    }

    return(u1_t_ret);
}


/*===================================================================================================================================*/
/*  static void vd_s_Nvmc_AcsTask_NvmTrans(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const U2 u2_a_DATAID)                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> st_ap_DEVICE_CFG : DEVICE                                                                                    */
/*                  --> u2_a_DATAID      : DATA ID                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Nvmc_AcsTask_NvmTrans(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const U2 u2_a_DATAID)
{
    const   ST_NVMC_CFGDATA     *   st_tp_CFGDATA;
            U2                      u2_t_cache_id;
            U1                      u1_t_nvmsts_old;
            U1                      u1_t_nvmsts;
            U1                      u1_t_acsway;

    u1_t_acsway = u1_d_Nvmc_GetDataTblNo(st_ap_DEVICE_CFG, u2_a_DATAID, &u2_t_cache_id);
    if(u1_t_acsway == (U1)NVMC_ACS_INNVM){
        st_tp_CFGDATA = &((st_ap_DEVICE_CFG->st_p_CFGDATA)[u2_t_cache_id]);
        u1_t_nvmsts_old = (U1)NVMC_STATUS_NG;
        (void)u1_g_Rim_ReadU1withStatus(st_tp_CFGDATA->u2_rimid_nvmsts, &u1_t_nvmsts_old);
        u1_t_nvmsts = u1_t_nvmsts_old;
        if(st_tp_CFGDATA->u1_map >= u1_d_NVMC_MODULE_NUM){
            u1_t_nvmsts = (U1)NVMC_STATUS_ERRCOMP;
        }
        switch(u1_t_nvmsts){
            case NVMC_STATUS_READING:
                u1_t_nvmsts = u1_s_Nvmc_AcsNvmReadTrans(st_ap_DEVICE_CFG, u2_a_DATAID, st_tp_CFGDATA);
                break;
            case NVMC_STATUS_WRITING:
                u1_t_nvmsts = u1_s_Nvmc_AcsNvmWriteTrans(st_ap_DEVICE_CFG, u2_a_DATAID, st_tp_CFGDATA, u2_t_cache_id);
                break;
            case NVMC_STATUS_COMP:
            case NVMC_STATUS_ERRCOMP:
            case NVMC_STATUS_CACHE_NG:
                break;
            case NVMC_STATUS_NG:
            default:
                u1_t_nvmsts = (U1)NVMC_STATUS_CACHE_NG;
                break;
        }
        if(u1_t_nvmsts_old != u1_t_nvmsts){
            (void)u1_g_Rim_WriteU1withStatus(st_tp_CFGDATA->u2_rimid_nvmsts, u1_t_nvmsts);
        }
        if((u1_t_nvmsts != (U1)NVMC_STATUS_READING) &&
           (u1_t_nvmsts != (U1)NVMC_STATUS_WRITING)){
            vd_d_Nvmc_SetAcsReqSub(st_ap_DEVICE_CFG, u2_a_DATAID, (U1)FALSE);
            (void)u1_g_Rim_WriteU2withStatus(st_ap_DEVICE_CFG->u2_rimid_initid, (U2)NVMC_REQID_TASK_IDLE);
        }
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_Nvmc_AcsTask_Request(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const U2 u2_a_DATAID)                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> st_ap_DEVICE_CFG : DEVICE                                                                                    */
/*                  --> u2_a_DATAID      : DATA ID                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Nvmc_AcsTask_Request(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const U2 u2_a_DATAID)
{
    U2  u2_t_reqid_new;
    U2  u2_t_cache_id;
    U1  u1_t_req;
    U1  u1_t_keep_req;
    U1  u1_t_acsway;

    u1_t_keep_req = (U1)FALSE;

    if(u1_dp_nvmc_suspend_req[st_ap_DEVICE_CFG->u1_dev_num] == (U1)TRUE){
        u1_t_req = u1_d_Nvmc_GetAcsReqSub(st_ap_DEVICE_CFG, u2_dp_nvmc_proc_id[st_ap_DEVICE_CFG->u1_dev_num]);
        if(u1_t_req == (U1)TRUE){
            u2_t_reqid_new = u2_dp_nvmc_proc_id[st_ap_DEVICE_CFG->u1_dev_num];
        }
        else{
            u2_t_reqid_new = (U2)NVMC_REQID_TASK_IDLE;
        }
    }
    else{
        u2_t_reqid_new = u2_d_Nvmc_GetAcsReqNo(st_ap_DEVICE_CFG);
    }

    u1_t_acsway = u1_d_Nvmc_GetDataTblNo(st_ap_DEVICE_CFG, u2_t_reqid_new, &u2_t_cache_id);
    if(u1_t_acsway >= (U1)NVMC_ACS_TYPE_ERR){                       /* Error access */
        /* u1_t_keep_req = (U1)FALSE; */
    }
    else{
        if(u2_a_DATAID != u2_t_reqid_new){
            vd_s_Nvmc_InitChgRequest(st_ap_DEVICE_CFG, u2_t_cache_id);
            u2_dp_nvmc_proc_id[st_ap_DEVICE_CFG->u1_dev_num] = u2_t_reqid_new;
        }
        if(u1_t_acsway == (U1)NVMC_ACS_INAPP){                      /* Accessed by application */
            u1_t_keep_req = u1_s_Nvmc_AcsAppData(u2_t_cache_id);
        }
        else{
            /* In case of u1_t_acsway == (U1)NVMC_ACS_INNVM */
            u1_t_keep_req = u1_s_Nvmc_AcsNvmRequest(st_ap_DEVICE_CFG, u2_t_cache_id);
        }
    }
    if(u1_t_keep_req == (U1)FALSE){
        vd_d_Nvmc_SetAcsReqSub(st_ap_DEVICE_CFG, u2_t_reqid_new, (U1)FALSE);
        u2_t_reqid_new = (U2)NVMC_REQID_TASK_IDLE;
    }
    if(u2_a_DATAID != u2_t_reqid_new){
        (void)u1_g_Rim_WriteU2withStatus(st_ap_DEVICE_CFG->u2_rimid_initid, u2_t_reqid_new);
    }
    u2_dp_nvmc_proc_id[st_ap_DEVICE_CFG->u1_dev_num] = u2_t_reqid_new;
}

/*===================================================================================================================================*/
/*  static U1   u1_s_Nvmc_AcsAppData(const U2 u2_a_NO)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_NO     : TBL No                                                                                         */
/*  Return:         U1 u1_t_ret : Status                                                                                             */
/*===================================================================================================================================*/
static U1   u1_s_Nvmc_AcsAppData(const U2 u2_a_NO)
{
    U1          u1_t_ret;

    u1_t_ret = (U1)FALSE;
    if(u2_a_NO < (U2)u1_d_NVMC_APP_ACS_NUM){
        if(st_NVMC_APP_FUNC_TABLE[u2_a_NO].fp_p_vd_acs_func != vdp_PTR_NA){
            (*st_NVMC_APP_FUNC_TABLE[u2_a_NO].fp_p_vd_acs_func)();
            u1_t_ret = (U1)TRUE;
        }
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static void vd_s_Nvmc_InitChgRequest(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const U2 u2_a_NO)                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> st_ap_DEVICE_CFG : DEVICE                                                                                    */
/*                  --> u2_a_NO      : TBL No                                                                                        */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Nvmc_InitChgRequest(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const U2 u2_a_NO)
{
    const       ST_NVMC_CFGDATA     *   st_tp_CFGDATA;
                ST_NVMC_READ_STS    *   st_tp_read_sts;
    volatile    U2                      u2_t_read_sync;
                U1                      u1_t_map_ptrn;

    st_tp_CFGDATA = &((st_ap_DEVICE_CFG->st_p_CFGDATA)[u2_a_NO]);
    st_tp_read_sts = &st_sp_nvmc_read_sts[st_ap_DEVICE_CFG->u1_dev_num];
    st_tp_read_sts->u1_rangeretry = (U1)0U;

    u1_t_map_ptrn = st_tp_CFGDATA->u1_map;
    if(u1_t_map_ptrn < u1_d_NVMC_MODULE_NUM){
        vd_s_Nvmc_ClrNvmReadSts(st_tp_read_sts, st_ap_DEVICE_CFG->u2_t_buf_base, (U2)st_ap_DEVICE_CFG->u1_use_bufsize);
        (void)u1_g_Rim_WriteU1withStatus(st_ap_DEVICE_CFG->u2_rimid_next_write_rdnno, (U1)NVMC_NEXTRDNNO_EXE_PREREAD);
    }
    u1_dp_nvmc_recovery_retry[st_ap_DEVICE_CFG->u1_dev_num] = (U1)0U;
    st_sp_nvmc_temp_read_buf[st_ap_DEVICE_CFG->u1_dev_num].u2_blockid = (U2)NVMC_INVALID_BLOCK_ID;
    st_sp_nvmc_temp_write_buf[st_ap_DEVICE_CFG->u1_dev_num].u2_blockid = (U2)NVMC_INVALID_BLOCK_ID;
    u2_t_read_sync = st_sp_nvmc_temp_write_buf[st_ap_DEVICE_CFG->u1_dev_num].u2_blockid;        /* Dummy read for memory sync */
    /* Temp buffer shall be cleared before this line. */
}

/*===================================================================================================================================*/
/*  static U1   u1_s_Nvmc_AcsNvmRequest(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const U2 u2_a_NO)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> st_ap_DEVICE_CFG : DEVICE                                                                                    */
/*                  --> u2_a_NO          : TBL No                                                                                    */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
static U1   u1_s_Nvmc_AcsNvmRequest(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const U2 u2_a_NO)
{
    const   ST_NVMC_CFGDATA     *   st_tp_CFGDATA;
    const   ST_NVMC_MODULE_CFG  *   st_tp_MODULE_CFG;
            ST_NVMC_READ_STS    *   st_tp_read_sts;
            ST_NVMC_WRITE_STS   *   st_tp_write_sts;
            U1                      u1_t_nvmsts;
            U1                      u1_t_ret;
            U1                      u1_t_reqsts;
            U1                      u1_t_nvmsts_old;
            U1                      u1_t_map_ptrn;
            U1                      u1_t_rdnbit;
            U1                      u1_t_preread;

    st_tp_CFGDATA = &((st_ap_DEVICE_CFG->st_p_CFGDATA)[u2_a_NO]);
    st_tp_read_sts = &st_sp_nvmc_read_sts[st_ap_DEVICE_CFG->u1_dev_num];
    st_tp_write_sts = &st_sp_nvmc_write_sts[(u2_a_NO + st_ap_DEVICE_CFG->u2_t_write_sts_base)];
    u1_t_nvmsts = (U1)NVMC_STATUS_CACHE_NG;
    (void)u1_g_Rim_ReadU1withStatus(st_tp_CFGDATA->u2_rimid_nvmsts, &u1_t_nvmsts);
    u1_t_nvmsts_old = u1_t_nvmsts;
    u1_t_map_ptrn = st_tp_CFGDATA->u1_map;
    if(u1_t_map_ptrn < u1_d_NVMC_MODULE_NUM){
        st_tp_MODULE_CFG = &st_dp_NVMC_MODULE_CFG[u1_t_map_ptrn];
    }
    else{
        u1_t_nvmsts = (U1)NVMC_STATUS_ERRCOMP;
    }
    u1_t_ret = (U1)TRUE;
    switch(u1_t_nvmsts){
        case NVMC_STATUS_READING:
            (void)u1_s_Nvmc_AcsNvmReadReq(st_ap_DEVICE_CFG, st_tp_CFGDATA, st_tp_read_sts);
            break;
        case NVMC_STATUS_WRITING:
            u1_t_preread = u1_s_Nvmc_IsExecPreRead(st_ap_DEVICE_CFG, st_tp_CFGDATA, st_tp_write_sts);
            u1_t_rdnbit = (U1)((U1)0x01U << st_tp_MODULE_CFG->u1_rdnnum) - (U1)1U;
            if(u1_t_preread == (U1)TRUE){
                /* Read request(PreRead) */
                st_tp_read_sts->u1_rdnno = (U1)NVMC_RDNNO_PREREAD;
                (void)u1_s_Nvmc_AcsNvmReadReq(st_ap_DEVICE_CFG, st_tp_CFGDATA, st_tp_read_sts);
            }
            else if(st_tp_write_sts->u1_rdnno < u1_t_rdnbit){
                /* Write request */
                u1_t_reqsts = u1_s_Nvmc_AcsNvmWriteReq(st_ap_DEVICE_CFG, st_tp_CFGDATA, st_tp_write_sts);
                if(u1_t_reqsts != (U1)TRUE){
                    u1_t_ret = (U1)FALSE;
                    u1_t_nvmsts = (U1)NVMC_STATUS_CACHE_NG;
                }
            }
            else{
                /* Read request(Verify) */
                (void)u1_s_Nvmc_AcsNvmReadReq(st_ap_DEVICE_CFG, st_tp_CFGDATA, st_tp_read_sts);
            }
            break;
        case NVMC_STATUS_COMP:
        case NVMC_STATUS_ERRCOMP:
            u1_t_ret = (U1)FALSE;
            break;
        case NVMC_STATUS_CACHE_NG:
        default:
            u1_t_ret = (U1)FALSE;
            u1_t_nvmsts = (U1)NVMC_STATUS_CACHE_NG;
            break;
    }
    /* Even if configuration of auto error correction is active, error correction does not work in routine.  */
    /* The reason is that this could cause unlimited execution.                                              */
    if(u1_t_nvmsts_old != u1_t_nvmsts){
        (void)u1_g_Rim_WriteU1withStatus(st_tp_CFGDATA->u2_rimid_nvmsts, u1_t_nvmsts);
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1 u1_s_Nvmc_AcsNvmReadTrans(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const U2 u2_a_DATAID, const ST_NVMC_CFGDATA * const st_ap_CFGDATA) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> st_ap_DEVICE_CFG : DEVICE                                                                                    */
/*                  --> u2_a_DATAID      : DATA ID                                                                                   */
/*                  --> *st_ap_CFGDATA   : CFG DATA                                                                                  */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
static U1 u1_s_Nvmc_AcsNvmReadTrans(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG,
                                    const U2 u2_a_DATAID,
                                    const ST_NVMC_CFGDATA * const st_ap_CFGDATA)
{
    U4                            u4_tp_buf[NVMC_BUF_SIZE];
    const ST_NVMC_MODULE_CFG *    st_tp_MODULE_CFG;
    U2                            u2_t_req_id;
    U2                            u2_t_buf_pos;
    U2                            u2_t_nvmc_id;
    U1                            u1_t_ret;
    U1                            u1_t_act;
    U1                            u1_t_rdnsts;
    U1                            u1_t_read_sts;
    U1                            u1_t_range_ok;
    U1                            u1_t_map_ptrn;
    U1                            u1_t_size;
    U1                           u1_t_last_index;

    u1_t_map_ptrn    = st_ap_CFGDATA->u1_map;
    st_tp_MODULE_CFG = &st_dp_NVMC_MODULE_CFG[u1_t_map_ptrn];
    u1_t_size        = st_tp_MODULE_CFG->u1_datasize;
    u1_t_read_sts    = u1_s_Nvmc_ReadRednData(st_ap_DEVICE_CFG, st_tp_MODULE_CFG);
    if(u1_t_read_sts == (U1)NVMC_READ_REDN_DATA_READING){

     /* u1_t_rdnsts = (U1)NVMC_MOD_RSLT_OK; QAC warning#2983 */
        u1_t_act    = (U1)NVMC_READ_SEQ_READING;

        vd_g_MemfillU4(&u4_tp_buf[0], (U4)0U, (U4)NVMC_BUF_SIZE);
    }
    else if(u1_t_size == (U1)0U){

        u1_t_rdnsts = (U1)NVMC_MOD_RSLT_OK;
        u1_t_act    = (U1)NVMC_READ_SEQ_RAMNG_CMPLT;

        vd_g_MemfillU4(&u4_tp_buf[0], (U4)0U, (U4)NVMC_BUF_SIZE);
    }
    else{

        u1_t_last_index = (u1_t_size + (U1)NVMC_ARRAY_INDEX_MASK) >> NVMC_ARRAY_INDEX_SHIFT;
        u1_t_last_index--;                          /* No underflow */
        u4_tp_buf[u1_t_last_index] = (U4)0U;
        vd_d_Nvmc_DCK_SetDefaultData(st_ap_CFGDATA, &u4_tp_buf[0], u1_t_size);
        if(u1_t_read_sts == (U1)NVMC_READ_REDN_DATA_COMPLETE){

            u2_t_buf_pos = st_ap_DEVICE_CFG->u2_t_buf_base;
            u1_t_rdnsts  = st_tp_MODULE_CFG->fp_p_u1_GetRdnRead(st_ap_CFGDATA,
                                                                u4_tp_buf,
                                                                &u4_dp_nvmc_read_data_buf[u2_t_buf_pos],
                                                                &u1_dp_nvmc_read_status_buf[u2_t_buf_pos]);
        }
        else{

            u1_t_rdnsts  = (U1)NVMC_MOD_RSLT_NG;
        }

        /* Recovery check */
        if(u1_t_rdnsts == (U1)NVMC_MOD_RSLT_NODATA){

            u2_t_req_id = st_ap_DEVICE_CFG->u2_recovery_req_id;
            if(u2_t_req_id != (U2)NVMC_INVALID_REQ_ID){
                u1_dp_nvmc_recovery_retry[st_ap_DEVICE_CFG->u1_dev_num] = (U1)0U;
                vd_d_Nvmc_SetAcsReqSub(st_ap_DEVICE_CFG, u2_t_req_id, (U1)TRUE);
            }

            u1_t_range_ok = u1_d_Nvmc_DCK_ChkDataRange(st_ap_CFGDATA, u4_tp_buf, u1_t_size);
            if(u1_t_range_ok == (U1)FALSE){
                u1_t_rdnsts = (U1)NVMC_MOD_RSLT_RANGEOUT;
            }
        }
        /* Range check */
        else if(u1_t_rdnsts == (U1)NVMC_MOD_RSLT_OK){

            u1_t_range_ok = u1_d_Nvmc_DCK_ChkDataRange(st_ap_CFGDATA, u4_tp_buf, u1_t_size);
            if(u1_t_range_ok == (U1)FALSE){
                u1_t_rdnsts = (U1)NVMC_MOD_RSLT_RANGEOUT;
            }
        }
        else{
            /* do nothing */
        }

        /* Error Judgement */
        u1_t_act = u1_s_Nvmc_AcsNvmReadErrJudge(st_ap_DEVICE_CFG, st_ap_CFGDATA, &u4_tp_buf[0], u1_t_rdnsts);
    }

    u1_t_ret = u1_s_Nvmc_AcsNvmReadAct(st_ap_CFGDATA, u4_tp_buf, u1_t_act);

    if((u1_t_act    != (U1)NVMC_READ_SEQ_READING) &&
       (u1_t_rdnsts != (U1)NVMC_MOD_RSLT_OK     )){

        u2_t_nvmc_id = (U2)((U2)st_ap_DEVICE_CFG->u1_dev_num << NVMC_ID_DEVICE_SHIFT) | u2_a_DATAID;
        vd_d_Nvmc_ReadErrorHook(u2_t_nvmc_id, u1_t_ret, u1_t_rdnsts);
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1 u1_s_Nvmc_AcsNvmReadErrJudge(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_buf, const U1 u1_a_RDNSTS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> st_ap_DEVICE_CFG : DEVICE                                                                                    */
/*                  --> *st_ap_CFGDATA   : CFG DATA                                                                                  */
/*                  --> *u4_ap_buf       : buffer                                                                                    */
/*                  --> u1_a_RDNSTS      : Rdn Status                                                                                */
/*  Return:         U1 u1_t_act : Result action index                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_Nvmc_AcsNvmReadErrJudge(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_buf, const U1 u1_a_RDNSTS)
{
    const   ST_NVMC_MODULE_CFG  *   st_tp_MODULE_CFG;
            ST_NVMC_READ_STS    *   st_tp_read_sts;
            U2                      u2_t_data_rim_id;
            U1                      u1_t_act;
            U1                      u1_t_errsts;
            U1                      u1_t_map_ptrn;
            U1                      u1_t_data_rim_sts;
            U1                      u1_t_size;

    u1_t_map_ptrn = st_ap_CFGDATA->u1_map;
    /* It is not necessary to check the range of u1_t_map_ptrn because caller check it. */
    st_tp_MODULE_CFG = &st_dp_NVMC_MODULE_CFG[u1_t_map_ptrn];
    st_tp_read_sts = &st_sp_nvmc_read_sts[st_ap_DEVICE_CFG->u1_dev_num];
    u1_t_size = st_tp_MODULE_CFG->u1_datasize;
    /* It is not necessary to check the range of u1_t_size because caller check it. */

    u1_t_act = (U1)NVMC_READ_SEQ_READING;
    /* Error Judgement */
    if(
        (u1_a_RDNSTS == (U1)NVMC_MOD_RSLT_OK) ||
        (u1_a_RDNSTS == (U1)NVMC_MOD_RSLT_NODATA)
    ){
        u1_t_act = (U1)NVMC_READ_SEQ_CMPLT;
    }
    else if(
        (u1_a_RDNSTS != (U1)NVMC_MOD_RSLT_LOST) &&
        (st_tp_read_sts->u1_rangeretry < st_ap_CFGDATA->u1_rangeretry)
    ){
        (st_tp_read_sts->u1_rangeretry)++;
        vd_s_Nvmc_ClrNvmReadSts(st_tp_read_sts, st_ap_DEVICE_CFG->u2_t_buf_base, (U2)st_ap_DEVICE_CFG->u1_use_bufsize);
        /* u1_t_act = (U1)NVMC_READ_SEQ_READING; */
    }
    else{
        u1_t_errsts = u1_d_Nvmc_DCK_ChkReadData(st_ap_CFGDATA, u4_ap_buf, u1_t_size, u1_a_RDNSTS);
        u1_t_act = (U1)NVMC_READ_SEQ_ERR_CMPLT;
        if(u1_t_errsts == (U1)NVMC_DCK_RSLT_NG_LAST){
            u2_t_data_rim_id = st_ap_CFGDATA->u2_rimid_wdata;
            u2_t_data_rim_id += ((U2)(st_ap_CFGDATA->u1_mgr_bit_cfg) & (U2)NVMC_SETT_CMN_READID_MASK);
            u1_t_data_rim_sts = u1_d_Nvmc_GetRimData(u2_t_data_rim_id, u4_ap_buf, (U2)u1_t_size);
            if((u1_t_data_rim_sts & (U1)RIM_RESULT_KIND_MASK) != (U1)RIM_RESULT_KIND_OK){
                vd_d_Nvmc_DCK_SetDefaultData(st_ap_CFGDATA, &u4_ap_buf[0], u1_t_size);
                u1_t_act = (U1)NVMC_READ_SEQ_RAMNG_CMPLT;
            }
        }
        else if(u1_t_errsts == (U1)NVMC_DCK_RSLT_NG_WRDATA){
            u2_t_data_rim_id = st_ap_CFGDATA->u2_rimid_wdata;
            u1_t_data_rim_sts = u1_d_Nvmc_GetRimData(u2_t_data_rim_id, u4_ap_buf, (U2)u1_t_size);
            if((u1_t_data_rim_sts & (U1)RIM_RESULT_KIND_MASK) != (U1)RIM_RESULT_KIND_OK){
                vd_d_Nvmc_DCK_SetDefaultData(st_ap_CFGDATA, &u4_ap_buf[0], u1_t_size);
                u1_t_act = (U1)NVMC_READ_SEQ_RAMNG_CMPLT;
            }
        }
        else{
            /* u1_t_act = (U1)NVMC_READ_SEQ_ERR_CMPLT; */
        }
    }

    return(u1_t_act);
}

/*===================================================================================================================================*/
/*  static U1   u1_s_Nvmc_ReadRednData(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const ST_NVMC_MODULE_CFG * const st_ap_MODULE_CFG) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> st_ap_DEVICE_CFG : DEVICE                                                                                    */
/*                  --> st_ap_MODULE_CFG : Module                                                                                    */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
static U1   u1_s_Nvmc_ReadRednData(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const ST_NVMC_MODULE_CFG * const st_ap_MODULE_CFG)
{
    ST_NVMC_READ_STS    *   st_tp_read_sts;
    ST_NVMC_READ_BUF    *   st_tp_temp_read_buf;
    U2                      u2_t_pos;
    U1                      u1_t_ret;
    U1                      u1_t_tempsts;

    st_tp_read_sts = &st_sp_nvmc_read_sts[st_ap_DEVICE_CFG->u1_dev_num];
    st_tp_temp_read_buf = &st_sp_nvmc_temp_read_buf[st_ap_DEVICE_CFG->u1_dev_num];
    st_tp_temp_read_buf->u2_blockid = (U2)NVMC_INVALID_BLOCK_ID;
    u1_t_tempsts = st_tp_temp_read_buf->u1_readsts;
    /* Range check */
    if(
        (st_tp_read_sts->u1_step >= st_ap_MODULE_CFG->u1_blocknum) ||
        (st_tp_read_sts->u1_rdnno >= st_ap_MODULE_CFG->u1_rdnnum)
    ){
        st_tp_read_sts->u1_step = (U1)0U;
        st_tp_read_sts->u1_rdnno = (U1)0U;
        u1_t_tempsts = (U1)NVMC_RESULT_NG;
    }

    u1_t_ret = (U1)NVMC_READ_REDN_DATA_READING;
    if(
        ((u1_t_tempsts == (U1)NVMC_RESULT_OK) &&
        ((U2)st_ap_MODULE_CFG->u1_blocksize == st_tp_temp_read_buf->u2_req_size)) ||
        (u1_t_tempsts == (U1)NVMC_RESULT_NODATA)
    ){
        /* Normal Completion */
        (st_tp_read_sts->u1_busyretry) = (U1)0U;
        u2_t_pos = ((((U2)(st_tp_read_sts->u1_rdnno)) * ((U2)(st_ap_MODULE_CFG->u1_blocknum))) + ((U2)(st_tp_read_sts->u1_step))) * ((U2)(st_ap_MODULE_CFG->u1_wordbuf_num));
        u2_t_pos += st_ap_DEVICE_CFG->u2_t_buf_base;
        vd_g_MemcpyU4(&u4_dp_nvmc_read_data_buf[u2_t_pos], st_tp_temp_read_buf->u4_buf, (U4)st_ap_MODULE_CFG->u1_wordbuf_num);
        vd_g_MemfillU1(&u1_dp_nvmc_read_status_buf[u2_t_pos], u1_t_tempsts, (U4)st_ap_MODULE_CFG->u1_wordbuf_num);
        (st_tp_read_sts->u1_step)++;
        if(st_tp_read_sts->u1_step < st_ap_MODULE_CFG->u1_blocknum){
            /* Not complete reading data size */
            /* u1_t_ret = (U1)NVMC_READ_REDN_DATA_READING; */
        }
        else{
            /* Completed reading data size */
            (st_tp_read_sts->u1_rdnno)++;
            if(st_tp_read_sts->u1_rdnno < st_ap_MODULE_CFG->u1_rdnnum){
                /* Not complete reading redundancy data */
                st_tp_read_sts->u1_step = (U1)0U;
                /* u1_t_ret = (U1)NVMC_READ_REDN_DATA_READING; */
            }
            else{
                /* Completed reading all data */
                u1_t_ret = (U1)NVMC_READ_REDN_DATA_COMPLETE;
            }
        }
    }
    else{
        /* Read Error */
        if(st_tp_read_sts->u1_busyretry >= st_ap_DEVICE_CFG->u1_busyretry){
            /* Retry error */
            u1_t_ret = (U1)NVMC_READ_REDN_DATA_ERROR;
        }
        else{
            /* Read again */
            (st_tp_read_sts->u1_busyretry)++;
            /* u1_t_ret = (U1)NVMC_READ_REDN_DATA_READING; */
        }
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1   u1_s_Nvmc_AcsNvmReadAct(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const U4 * const u4_ap_DATA, const U1 u1_a_ACT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA : CFG DATA                                                                                    */
/*                  --> u4_a_DATA      : Data                                                                                        */
/*                  --> u1_a_ACT       : action                                                                                      */
/*  Return:         U1 u1_t_nvmsts : Sts                                                                                             */
/*===================================================================================================================================*/
static U1   u1_s_Nvmc_AcsNvmReadAct(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const U4 * const u4_ap_DATA, const U1 u1_a_ACT)
{
    static const U1 u1_sp_NVMC_READ_ACT_TBL[NVMC_READ_SEQ_NUM][NVMC_READ_ACT_ACT_NUM] = {
        {(U1)NVMC_STATUS_READING,   (U1)NVMC_RW_TARGET_NON      },  /* NVMC_READ_SEQ_READING          */
        {(U1)NVMC_STATUS_COMP,      (U1)NVMC_RW_TARGET_BOTH     },  /* NVMC_READ_SEQ_CMPLT            */
        {(U1)NVMC_STATUS_ERRCOMP,   (U1)NVMC_RW_TARGET_BOTH     },  /* NVMC_READ_SEQ_ERR_CMPLT        */
        {(U1)NVMC_STATUS_CACHE_NG,  (U1)NVMC_RW_TARGET_BOTH     }   /* NVMC_READ_SEQ_RAMNG_CMPLT      */
    };
    U1  u1_t_nvmsts;
    U1  u1_t_rslt;
    U1  u1_t_data_update;

    u1_t_nvmsts = (U1)NVMC_STATUS_CACHE_NG;
    if(u1_a_ACT < (U1)NVMC_READ_SEQ_NUM){
        u1_t_nvmsts = u1_sp_NVMC_READ_ACT_TBL[u1_a_ACT][NVMC_READ_ACT_ACT_NEXT_STATE];
        u1_t_data_update = u1_sp_NVMC_READ_ACT_TBL[u1_a_ACT][NVMC_READ_ACT_ACT_RAM_UPDATE];
        if(u1_t_data_update != (U1)NVMC_RW_TARGET_NON){
            u1_t_rslt = u1_s_Nvmc_SetData(st_ap_CFGDATA, u4_ap_DATA, u1_t_data_update);
            if(u1_t_rslt != (U1)TRUE){
                u1_t_nvmsts = (U1)NVMC_STATUS_CACHE_NG;
            }
        }
    }
    /* Even if u1_t_nvmsts = (U1)NVMC_STATUS_CACHE_NG, it is not necessary to read NVM data. */
    return(u1_t_nvmsts);
}

/*===================================================================================================================================*/
/*  static U1   u1_s_Nvmc_AcsNvmWriteTrans(const ST_NVMC_DEVICE_CFG * st_ap_DEVICE_CFG, const U2 u2_a_DATAID, const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const U2 u2_a_NO) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> st_ap_DEVICE_CFG : DEVICE                                                                                    */
/*                  --> u2_a_DATAID      : DATA ID                                                                                   */
/*                  --> *st_ap_CFGDATA   : CFG DATA                                                                                  */
/*                  --> u2_a_NO          : TBL No                                                                                    */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
static U1   u1_s_Nvmc_AcsNvmWriteTrans(const ST_NVMC_DEVICE_CFG * st_ap_DEVICE_CFG, const U2 u2_a_DATAID, const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const U2 u2_a_NO)
{
    const   ST_NVMC_MODULE_CFG  *   st_tp_MODULE_CFG;
            ST_NVMC_WRITE_STS   *   st_tp_write_sts;
            U1                      u1_t_ret;
            U1                      u1_t_map_ptrn;
            U1                      u1_t_rdnbit;
            U1                      u1_t_preread;

    u1_t_map_ptrn = st_ap_CFGDATA->u1_map;
    /* It is not necessary to check the range of u1_t_map_ptrn because caller check it. */
    st_tp_MODULE_CFG = &st_dp_NVMC_MODULE_CFG[u1_t_map_ptrn];
    st_tp_write_sts = &st_sp_nvmc_write_sts[(u2_a_NO + st_ap_DEVICE_CFG->u2_t_write_sts_base)];

    u1_t_preread = u1_s_Nvmc_IsExecPreRead(st_ap_DEVICE_CFG, st_ap_CFGDATA, st_tp_write_sts);
    u1_t_rdnbit = (U1)((U1)0x01U << st_tp_MODULE_CFG->u1_rdnnum) - (U1)1U;
    if(u1_t_preread == (U1)TRUE){
        vd_s_Nvmc_AcsNvmPreReadTrans(st_ap_DEVICE_CFG, st_ap_CFGDATA, u2_a_NO);
        u1_t_ret = (U1)NVMC_STATUS_WRITING;
    }
    else if(st_tp_write_sts->u1_rdnno < u1_t_rdnbit){
        vd_s_Nvmc_AcsNvmWritingTrans(st_ap_DEVICE_CFG, st_ap_CFGDATA, u2_a_NO);
        u1_t_ret = (U1)NVMC_STATUS_WRITING;
    }
    else{
        /* Read status */
        u1_t_ret = u1_s_Nvmc_AcsNvmVerifyTrans(st_ap_DEVICE_CFG, u2_a_DATAID, st_ap_CFGDATA, u2_a_NO);
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static void vd_s_Nvmc_AcsNvmPreReadTrans(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const U2 u2_a_NO) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> st_ap_DEVICE_CFG : DEVICE                                                                                    */
/*                  --> *st_ap_CFGDATA   : CFG DATA                                                                                  */
/*                  --> u2_a_NO          : TBL No                                                                                    */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Nvmc_AcsNvmPreReadTrans(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const U2 u2_a_NO)
{
    const   ST_NVMC_MODULE_CFG  *   st_tp_MODULE_CFG;
            ST_NVMC_WRITE_STS   *   st_tp_write_sts;
            ST_NVMC_READ_STS    *   st_tp_read_sts;
            U2                      u2_t_buf_pos;
            U1                      u1_t_rdnsts;
            U1                      u1_t_read_sts;
            U1                      u1_t_map_ptrn;

    u1_t_map_ptrn = st_ap_CFGDATA->u1_map;
    /* It is not necessary to check the range of u1_t_map_ptrn because caller check it. */
    st_tp_MODULE_CFG = &st_dp_NVMC_MODULE_CFG[u1_t_map_ptrn];
    u1_t_read_sts = u1_s_Nvmc_PreReadRednData(st_ap_DEVICE_CFG, st_tp_MODULE_CFG);

    if(st_tp_MODULE_CFG->fp_p_u1_GetRdnPreRead == vdp_PTR_NA){
        (void)u1_g_Rim_WriteU1withStatus(st_ap_DEVICE_CFG->u2_rimid_next_write_rdnno, (U1)0U);
    }
    else if(u1_t_read_sts == (U1)NVMC_READ_REDN_DATA_READING){
    }
    else if(u1_t_read_sts == (U1)NVMC_READ_REDN_DATA_NODATA){
        (void)u1_g_Rim_WriteU1withStatus(st_ap_DEVICE_CFG->u2_rimid_next_write_rdnno, (U1)NVMC_NEXTRDNNO_READ_NODATA);
    }
    else{
        u1_t_rdnsts = (U1)NVMC_MOD_RSLT_NG;
        if(u1_t_read_sts == (U1)NVMC_READ_REDN_DATA_COMPLETE){
            u2_t_buf_pos = st_ap_DEVICE_CFG->u2_t_buf_base;
            u1_t_rdnsts = st_tp_MODULE_CFG->fp_p_u1_GetRdnPreRead(&u4_dp_nvmc_read_data_buf[u2_t_buf_pos], &u1_dp_nvmc_read_status_buf[u2_t_buf_pos], st_tp_MODULE_CFG->u1_blocknum);
        }

        if(u1_t_rdnsts == (U1)NVMC_MOD_RSLT_OK){
            (void)u1_g_Rim_WriteU1withStatus(st_ap_DEVICE_CFG->u2_rimid_next_write_rdnno, (U1)NVMC_NEXTRDNNO_READ_OK);
        }
        else if(u1_t_rdnsts == (U1)NVMC_MOD_RSLT_NODATA){
            (void)u1_g_Rim_WriteU1withStatus(st_ap_DEVICE_CFG->u2_rimid_next_write_rdnno, (U1)NVMC_NEXTRDNNO_READ_NODATA);
        }
        else{
            /* PreRead Error*/
            st_tp_write_sts = &st_sp_nvmc_write_sts[(u2_a_NO + st_ap_DEVICE_CFG->u2_t_write_sts_base)];
            st_tp_read_sts = &st_sp_nvmc_read_sts[st_ap_DEVICE_CFG->u1_dev_num];

            vd_s_Nvmc_ClrNvmReadSts(st_tp_read_sts, st_ap_DEVICE_CFG->u2_t_buf_base, (U2)st_ap_DEVICE_CFG->u1_use_bufsize);

            if(st_tp_write_sts->u1_verifyretry < st_ap_CFGDATA->u1_verifyretry){
                (st_tp_write_sts->u1_verifyretry)++;
                vd_s_Nvmc_ClrNvmWriteSts(st_tp_write_sts);
                (void)u1_g_Rim_WriteU1withStatus(st_ap_DEVICE_CFG->u2_rimid_next_write_rdnno, (U1)NVMC_NEXTRDNNO_EXE_PREREAD);
            }
            else{
                st_tp_read_sts->u1_rangeretry = (U1)0U;
                st_tp_write_sts->u1_rdnno = (U1)NVMC_RDNNO_MAX;
                st_tp_write_sts->u1_step = (U1)NVMC_STEPNO_MAX;
            }
        }
    }
}

/*===================================================================================================================================*/
/*  static U1   u1_s_Nvmc_PreReadRednData(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const ST_NVMC_MODULE_CFG * const st_ap_MODULE_CFG) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> st_ap_DEVICE_CFG : DEVICE                                                                                    */
/*                  --> st_ap_MODULE_CFG : Module                                                                                    */
/*  Return:         U1 u1_t_ret : Read Sts                                                                                           */
/*===================================================================================================================================*/
static U1   u1_s_Nvmc_PreReadRednData(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const ST_NVMC_MODULE_CFG * const st_ap_MODULE_CFG)
{
    ST_NVMC_READ_STS    *   st_tp_read_sts;
    ST_NVMC_READ_BUF    *   st_tp_temp_read_buf;
    U2                      u2_t_pos;
    U1                      u1_t_ret;
    U1                      u1_t_tempsts;

    st_tp_read_sts = &st_sp_nvmc_read_sts[st_ap_DEVICE_CFG->u1_dev_num];
    st_tp_temp_read_buf = &st_sp_nvmc_temp_read_buf[st_ap_DEVICE_CFG->u1_dev_num];
    st_tp_temp_read_buf->u2_blockid = (U2)NVMC_INVALID_BLOCK_ID;
    u1_t_tempsts = st_tp_temp_read_buf->u1_readsts;
    /* Range check */
    if(st_tp_read_sts->u1_step >= st_ap_MODULE_CFG->u1_blocknum){
        st_tp_read_sts->u1_step = (U1)0U;
        u1_t_tempsts = (U1)NVMC_RESULT_NG;
    }

    u1_t_ret = (U1)NVMC_READ_REDN_DATA_READING;
    if(u1_t_tempsts == (U1)NVMC_RESULT_NODATA){
        u1_t_ret = (U1)NVMC_READ_REDN_DATA_NODATA;
    }
    else if(
        (u1_t_tempsts == (U1)NVMC_RESULT_OK) &&
        ((U2)st_ap_MODULE_CFG->u1_blocksize == st_tp_temp_read_buf->u2_req_size)
    ){
        /* Normal Completion */
        (st_tp_read_sts->u1_busyretry) = (U1)0U;
        u2_t_pos = (U2)st_tp_read_sts->u1_step * (U2)st_ap_MODULE_CFG->u1_wordbuf_num;
        u2_t_pos += st_ap_DEVICE_CFG->u2_t_buf_base;
        vd_g_MemcpyU4(&u4_dp_nvmc_read_data_buf[u2_t_pos], st_tp_temp_read_buf->u4_buf, (U4)st_ap_MODULE_CFG->u1_wordbuf_num);
        vd_g_MemfillU1(&u1_dp_nvmc_read_status_buf[u2_t_pos], u1_t_tempsts, (U4)st_ap_MODULE_CFG->u1_wordbuf_num);
        (st_tp_read_sts->u1_step)++;
        if(st_tp_read_sts->u1_step < st_ap_MODULE_CFG->u1_blocknum){
            /* Not complete reading data size */
            /* u1_t_ret = (U1)NVMC_READ_REDN_DATA_READING; */
        }
        else{
            /* Completed reading all data */
            u1_t_ret = (U1)NVMC_READ_REDN_DATA_COMPLETE;
        }
    }
    else{
        /* Read Error */
        if(st_tp_read_sts->u1_busyretry >= st_ap_DEVICE_CFG->u1_busyretry){
            /* Retry error */
            u1_t_ret = (U1)NVMC_READ_REDN_DATA_ERROR;
        }
        else{
            /* Read again */
            (st_tp_read_sts->u1_busyretry)++;
            /* u1_t_ret = (U1)NVMC_READ_REDN_DATA_READING; */
        }
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static void vd_s_Nvmc_AcsNvmWritingTrans(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const U2 u2_a_NO) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> st_ap_DEVICE_CFG : DEVICE                                                                                    */
/*                  --> *st_ap_CFGDATA   : CFG DATA                                                                                  */
/*                  --> u2_a_NO          : TBL No                                                                                    */
/*  Return:             -                                                                                                            */
/*===================================================================================================================================*/
static void vd_s_Nvmc_AcsNvmWritingTrans(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const U2 u2_a_NO)
{
    const   ST_NVMC_MODULE_CFG  *   st_tp_MODULE_CFG;
            ST_NVMC_WRITE_STS   *   st_tp_write_sts;
            ST_NVMC_WRITE_BUF   *   st_tp_temp_write_buf;
            ST_NVMC_READ_STS    *   st_tp_read_sts;
            U1                      u1_t_tempsts;
            U1                      u1_t_map_ptrn;
            U1                      u1_t_rdnbit;

    u1_t_map_ptrn = st_ap_CFGDATA->u1_map;
    /* It is not necessary to check the range of u1_t_map_ptrn because caller check it. */
    st_tp_MODULE_CFG = &st_dp_NVMC_MODULE_CFG[u1_t_map_ptrn];
    st_tp_write_sts = &st_sp_nvmc_write_sts[(u2_a_NO + st_ap_DEVICE_CFG->u2_t_write_sts_base)];
    st_tp_read_sts = &st_sp_nvmc_read_sts[st_ap_DEVICE_CFG->u1_dev_num];
    st_tp_temp_write_buf = &st_sp_nvmc_temp_write_buf[st_ap_DEVICE_CFG->u1_dev_num];

    /* As read sequence, step and redn should be checked to avoid unexpected write */
    st_tp_temp_write_buf->u2_blockid = (U2)NVMC_INVALID_BLOCK_ID;
    u1_t_tempsts = st_tp_temp_write_buf->u1_writests;
    if(u1_t_tempsts == (U1)NVMC_RESULT_OK){
        /* Normal completion */
        (st_tp_write_sts->u1_step)++;
        if(st_tp_write_sts->u1_step < st_tp_MODULE_CFG->u1_blocknum){
            /* Not complete writing data size */
            st_tp_write_sts->u1_writeretry = (U1)0U;
        }
        else{
            /* Completed writing data size */
            vd_s_Nvmc_AddWriteRdnNo(st_ap_DEVICE_CFG, st_ap_CFGDATA, st_tp_write_sts);

            u1_t_rdnbit = (U1)((U1)0x01 << st_tp_MODULE_CFG->u1_rdnnum) - (U1)1U;
            if(st_tp_write_sts->u1_rdnno < u1_t_rdnbit){
                /* Not complete writing dundancy data */
                st_tp_write_sts->u1_step = (U1)0U;
                st_tp_write_sts->u1_writeretry = (U1)0U;
            }
            else{
                /* Completed writing data size */
                /* Clear all read data buffer */
                vd_s_Nvmc_ClrNvmReadSts(st_tp_read_sts, st_ap_DEVICE_CFG->u2_t_buf_base, (U2)st_ap_DEVICE_CFG->u1_use_bufsize);
                st_tp_read_sts->u1_rangeretry = (U1)0U;
                /* Set verify step. */
                st_tp_write_sts->u1_rdnno = (U1)NVMC_RDNNO_MAX;
                st_tp_write_sts->u1_step = (U1)NVMC_STEPNO_MAX;
            }
        }
    }
    else{
        if(st_tp_write_sts->u1_writeretry >= st_ap_DEVICE_CFG->u1_wr_retry){
            /* Write fail */
            vd_s_Nvmc_ClrNvmReadSts(st_tp_read_sts, st_ap_DEVICE_CFG->u2_t_buf_base, (U2)st_ap_DEVICE_CFG->u1_use_bufsize);

            if(st_tp_write_sts->u1_verifyretry < st_ap_CFGDATA->u1_verifyretry){
                /* In range retry, write from first. */
                (st_tp_write_sts->u1_verifyretry)++;
                vd_s_Nvmc_ClrNvmWriteSts(st_tp_write_sts);
                (void)u1_g_Rim_WriteU1withStatus(st_ap_DEVICE_CFG->u2_rimid_next_write_rdnno, (U1)NVMC_NEXTRDNNO_EXE_PREREAD);
            }
            else{
                st_tp_read_sts->u1_rangeretry = (U1)0U;
                st_tp_write_sts->u1_rdnno = (U1)NVMC_RDNNO_MAX;
                st_tp_write_sts->u1_step = (U1)NVMC_STEPNO_MAX;
            }
        }
        else{
            /* Retry */
            st_tp_write_sts->u1_writeretry++;
        }
    }
}

/*===================================================================================================================================*/
/*  static U1   u1_s_Nvmc_AcsNvmVerifyTrans(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG,                                       */
/*                                          const U2 u2_a_DATAID,                                                                    */
/*                                          const ST_NVMC_CFGDATA * const st_ap_CFGDATA,                                             */
/*                                          const U2 u2_a_NO)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> st_ap_DEVICE_CFG : DEVICE                                                                                    */
/*                  --> u2_a_DATAID      : DATA ID                                                                                   */
/*                  --> *st_ap_CFGDATA   : CFG DATA                                                                                  */
/*                  --> u2_a_NO          : TBL No                                                                                    */
/*  Return:         U1 u1_t_ret : Verify Sts                                                                                         */
/*===================================================================================================================================*/
static U1   u1_s_Nvmc_AcsNvmVerifyTrans(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG,
                                        const U2 u2_a_DATAID,
                                        const ST_NVMC_CFGDATA * const st_ap_CFGDATA,
                                        const U2 u2_a_NO)
{
    const ST_NVMC_MODULE_CFG *    st_tp_MODULE_CFG;

    ST_NVMC_WRITE_STS *           st_tp_write_sts;

    U4                            u4_tp_buf[NVMC_BUF_SIZE];
    U4                            u4_tp_wrdata[NVMC_BUF_SIZE];

    U2                            u2_t_buf_pos;
    U2                            u2_t_array_size;
    U2                            u2_t_last_index;
    U2                            u2_t_data_size;
    U2                            u2_t_data_rim_id;
    U2                            u2_t_nvmc_id;

    U1                            u1_t_ret;
    U1                            u1_t_act;
    U1                            u1_t_rdnsts;
    U1                            u1_t_data_rim_sts;
    U1                            u1_t_read_sts;
    U1                            u1_t_compare_ok;
    U1                            u1_t_map_ptrn;

    u1_t_map_ptrn    = st_ap_CFGDATA->u1_map;
    st_tp_MODULE_CFG = &st_dp_NVMC_MODULE_CFG[u1_t_map_ptrn];
    u2_t_data_size   = (U2)(st_tp_MODULE_CFG->u1_datasize);
    u1_t_read_sts    = u1_s_Nvmc_ReadRednData(st_ap_DEVICE_CFG, st_tp_MODULE_CFG);
    if(u1_t_read_sts == (U1)NVMC_READ_REDN_DATA_READING){

     /* u1_t_rdnsts = (U1)NVMC_MOD_RSLT_OK; QAC warning#2983 */
        u1_t_act    = (U1)NVMC_WRITE_SEQ_DATA_VERIFY;

        vd_g_MemfillU4(&u4_tp_buf[0], (U4)0U, (U4)NVMC_BUF_SIZE);
    }
    else if(u2_t_data_size == (U2)0U){

        u1_t_rdnsts = (U1)NVMC_MOD_RSLT_OK;
        u1_t_act    = (U1)NVMC_WRITE_SEQ_DATA_RAM_NG;

        vd_g_MemfillU4(&u4_tp_buf[0], (U4)0U, (U4)NVMC_BUF_SIZE);
    }
    else{

        u2_t_array_size = (u2_t_data_size + (U2)NVMC_ARRAY_INDEX_MASK) >> NVMC_ARRAY_INDEX_SHIFT;
        u2_t_last_index = u2_t_array_size - (U2)1U;                          /* No underflow */

        u4_tp_buf[u2_t_last_index] = (U4)0U;
        vd_d_Nvmc_DCK_SetDefaultData(st_ap_CFGDATA, &u4_tp_buf[0], (U1)u2_t_data_size);

        if(u1_t_read_sts == (U1)NVMC_READ_REDN_DATA_COMPLETE){
            u2_t_buf_pos = st_ap_DEVICE_CFG->u2_t_buf_base;
            u1_t_rdnsts  = st_tp_MODULE_CFG->fp_p_u1_GetRdnRead(st_ap_CFGDATA,
                                                                u4_tp_buf,
                                                                &u4_dp_nvmc_read_data_buf[u2_t_buf_pos],
                                                                &u1_dp_nvmc_read_status_buf[u2_t_buf_pos]);
        }
        else{
            u1_t_rdnsts  = (U1)NVMC_MOD_RSLT_NG;
        }

        u4_tp_wrdata[u2_t_last_index] = (U4)0U;
        u2_t_data_rim_id              = st_ap_CFGDATA->u2_rimid_wdata;
        u1_t_data_rim_sts             = u1_d_Nvmc_GetRimData(u2_t_data_rim_id,
                                                             u4_tp_wrdata,
                                                             u2_t_data_size) & (U1)RIM_RESULT_KIND_MASK;
        if(u1_t_data_rim_sts != (U1)RIM_RESULT_KIND_OK){

            vd_d_Nvmc_DCK_SetDefaultData(st_ap_CFGDATA, &u4_tp_buf[0], (U1)u2_t_data_size); /* Set Default Data to u4_tp_buf. */
            u1_t_act = (U1)NVMC_WRITE_SEQ_DATA_RAM_NG;
        }
        else{

            if((u1_t_rdnsts == (U1)NVMC_MOD_RSLT_OK    ) ||
               (u1_t_rdnsts == (U1)NVMC_MOD_RSLT_NODATA) ||
               (u1_t_rdnsts == (U1)NVMC_MOD_RSLT_RDN_NG)){

                u1_t_compare_ok = u1_d_Rim_CompareOther(u4_tp_buf, u4_tp_wrdata, u2_t_array_size);
                if(u1_t_compare_ok == (U1)FALSE){
                    u1_t_rdnsts = (U1)NVMC_MOD_RSLT_UNMATCH;
                }
            }
            st_tp_write_sts = &st_sp_nvmc_write_sts[(u2_a_NO + st_ap_DEVICE_CFG->u2_t_write_sts_base)];
            /* Error Judgement */
            u1_t_act        = u1_s_Nvmc_AcsNvmVerifyErrJudge(st_ap_DEVICE_CFG, st_ap_CFGDATA,
                                                             &u4_tp_buf[0],
                                                             u1_t_rdnsts,
                                                             st_tp_write_sts);
        }
    }

    u1_t_ret = u1_s_Nvmc_AcsNvmWriteAct(st_ap_CFGDATA, u4_tp_buf, u1_t_act);

    if((u1_t_act    != (U1)NVMC_WRITE_SEQ_DATA_WRITING) &&
       (u1_t_act    != (U1)NVMC_WRITE_SEQ_DATA_VERIFY ) &&
       (u1_t_rdnsts != (U1)NVMC_MOD_RSLT_OK           )){

        u2_t_nvmc_id = (U2)((U2)st_ap_DEVICE_CFG->u1_dev_num << NVMC_ID_DEVICE_SHIFT) | u2_a_DATAID;
        vd_d_Nvmc_WriteErrorHook(u2_t_nvmc_id, u1_t_ret, u1_t_rdnsts);
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1   u1_s_Nvmc_AcsNvmVerifyErrJudge(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_buf, const U1 u1_a_RDNSTS, ST_NVMC_WRITE_STS *st_ap_write_sts) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> st_ap_DEVICE_CFG : DEVICE                                                                                    */
/*                  --> *st_ap_CFGDATA   : CFG DATA                                                                                  */
/*                  --> *u4_ap_buf       : buffer                                                                                    */
/*                  --> u1_a_RDNSTS      : Rdn Status                                                                                */
/*                  --> *st_ap_write_sts : Write Sts                                                                                 */
/*  Return:         U1 u1_t_act : Result                                                                                             */
/*===================================================================================================================================*/
static U1   u1_s_Nvmc_AcsNvmVerifyErrJudge(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_buf, const U1 u1_a_RDNSTS, ST_NVMC_WRITE_STS *st_ap_write_sts)
{
    const   ST_NVMC_MODULE_CFG  *   st_tp_MODULE_CFG;
            ST_NVMC_READ_STS    *   st_tp_read_sts;
            U2                      u2_t_data_rim_id;
            U1                      u1_t_act;
            U1                      u1_t_errsts;
            U1                      u1_t_data_rim_sts;
            U1                      u1_t_map_ptrn;
            U1                      u1_t_size;

    u1_t_map_ptrn = st_ap_CFGDATA->u1_map;
    /* It is not necessary to check the range of u1_t_map_ptrn because caller check it. */
    st_tp_MODULE_CFG = &st_dp_NVMC_MODULE_CFG[u1_t_map_ptrn];
    u1_t_size = st_tp_MODULE_CFG->u1_datasize;
    /* It is not necessary to check the range of u1_t_size because caller check it. */

    u1_t_act = (U1)NVMC_WRITE_SEQ_DATA_WRITING;
    /* Error Judgement */
    if(u1_a_RDNSTS == (U1)NVMC_MOD_RSLT_OK){
        u1_t_act = (U1)NVMC_WRITE_SEQ_DATA_COMPLETE;
    }
    else if(st_ap_write_sts->u1_verifyretry < st_ap_CFGDATA->u1_verifyretry){
        st_tp_read_sts = &st_sp_nvmc_read_sts[st_ap_DEVICE_CFG->u1_dev_num];

        vd_s_Nvmc_ClrNvmReadSts(st_tp_read_sts, st_ap_DEVICE_CFG->u2_t_buf_base, (U2)st_ap_DEVICE_CFG->u1_use_bufsize);

        (st_ap_write_sts->u1_verifyretry)++;
        vd_s_Nvmc_ClrNvmWriteSts(st_ap_write_sts);
        (void)u1_g_Rim_WriteU1withStatus(st_ap_DEVICE_CFG->u2_rimid_next_write_rdnno, (U1)NVMC_NEXTRDNNO_EXE_PREREAD);
        /* u1_t_act = (U1)NVMC_WRITE_SEQ_DATA_WRITING; */
    }
    else{
        u1_t_errsts = u1_d_Nvmc_DCK_ChkReadData(st_ap_CFGDATA, u4_ap_buf, u1_t_size, u1_a_RDNSTS);
        u1_t_act = (U1)NVMC_WRITE_SEQ_DATA_FAIL;
        if(u1_t_errsts == (U1)NVMC_DCK_RSLT_NG_LAST){
            u2_t_data_rim_id = st_ap_CFGDATA->u2_rimid_wdata;
            u2_t_data_rim_id += ((U2)(st_ap_CFGDATA->u1_mgr_bit_cfg) & (U2)NVMC_SETT_CMN_READID_MASK);
            u1_t_data_rim_sts = u1_d_Nvmc_GetRimData(u2_t_data_rim_id, u4_ap_buf, (U2)u1_t_size);
            if((u1_t_data_rim_sts & (U1)RIM_RESULT_KIND_MASK) != (U1)RIM_RESULT_KIND_OK){
                vd_d_Nvmc_DCK_SetDefaultData(st_ap_CFGDATA, &u4_ap_buf[0], u1_t_size);
                u1_t_act = (U1)NVMC_WRITE_SEQ_DATA_RAM_NG;
            }
        }
        else if(u1_t_errsts == (U1)NVMC_DCK_RSLT_NG_WRDATA){
            u2_t_data_rim_id = st_ap_CFGDATA->u2_rimid_wdata;
            u1_t_data_rim_sts = u1_d_Nvmc_GetRimData(u2_t_data_rim_id, u4_ap_buf, (U2)u1_t_size);
            if((u1_t_data_rim_sts & (U1)RIM_RESULT_KIND_MASK) != (U1)RIM_RESULT_KIND_OK){
                vd_d_Nvmc_DCK_SetDefaultData(st_ap_CFGDATA, &u4_ap_buf[0], u1_t_size);
                u1_t_act = (U1)NVMC_WRITE_SEQ_DATA_RAM_NG;
            }
        }
        else{
            /* Use u4_ap_databuf read buffer without changing. */
        }
    }

    return(u1_t_act);
}

/*===================================================================================================================================*/
/*  static U1   u1_s_Nvmc_AcsNvmWriteAct(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const U4 * const u4_ap_DATA, const U1 u1_a_ACT)*/
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA : CFG DATA                                                                                    */
/*                  --> u4_ap_DATA     : Data                                                                                        */
/*                  --> u1_a_ACT       : action                                                                                      */
/*  Return:         U1 u1_t_nvmsts : Sts                                                                                             */
/*===================================================================================================================================*/
static U1   u1_s_Nvmc_AcsNvmWriteAct(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const U4 * const u4_ap_DATA, const U1 u1_a_ACT)
{
    static const U1 u1_sp_NVMC_WRITE_ACT_TBL[NVMC_WRITE_SEQ_DATA_NUM][NVMC_WRITE_ACT_ACT_NUM] = {
        {(U1)NVMC_STATUS_WRITING,   (U1)NVMC_RW_TARGET_NON      },      /* NVMC_WRITE_SEQ_DATA_WRITING       */
        {(U1)NVMC_STATUS_WRITING,   (U1)NVMC_RW_TARGET_NON      },      /* NVMC_WRITE_SEQ_DATA_VERIFY        */
        {(U1)NVMC_STATUS_COMP,      (U1)NVMC_RW_TARGET_READ     },      /* NVMC_WRITE_SEQ_DATA_COMPLETE      */
        {(U1)NVMC_STATUS_ERRCOMP,   (U1)NVMC_RW_TARGET_BOTH     },      /* NVMC_WRITE_SEQ_DATA_FAIL          */
        {(U1)NVMC_STATUS_CACHE_NG,  (U1)NVMC_RW_TARGET_BOTH     }       /* NVMC_WRITE_SEQ_DATA_RAM_NG        */
    };
    U1  u1_t_nvmsts;
    U1  u1_t_rslt;
    U1  u1_t_data_update;

    u1_t_nvmsts = (U1)NVMC_STATUS_CACHE_NG;
    if(u1_a_ACT < (U1)NVMC_WRITE_SEQ_DATA_NUM){
        u1_t_nvmsts = u1_sp_NVMC_WRITE_ACT_TBL[u1_a_ACT][NVMC_WRITE_ACT_ACT_NEXT_STATE];
        u1_t_data_update = u1_sp_NVMC_WRITE_ACT_TBL[u1_a_ACT][NVMC_WRITE_ACT_ACT_RAM_UPDATE];
        if(u1_t_data_update != (U1)NVMC_RW_TARGET_NON){
            u1_t_rslt = u1_s_Nvmc_SetData(st_ap_CFGDATA, u4_ap_DATA, u1_t_data_update);
            if(u1_t_rslt != (U1)TRUE){
                u1_t_nvmsts = (U1)NVMC_STATUS_CACHE_NG;
            }
        }
    }
    return(u1_t_nvmsts);
}

/*===================================================================================================================================*/
/*  static U1   u1_s_Nvmc_IsExecPreRead(const  ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const ST_NVMC_WRITE_STS * const st_ap_WRITE_STS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> st_ap_DEVICE_CFG : DEVICE                                                                                    */
/*                  --> *st_ap_CFGDATA   : CFG DATA                                                                                  */
/*                  --> *st_ap_WRITE_STS : STS Pointer                                                                               */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
static U1   u1_s_Nvmc_IsExecPreRead(const  ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const ST_NVMC_WRITE_STS * const st_ap_WRITE_STS)
{
    U1  u1_t_ret;
    U1  u1_t_preread;
    U1  u1_t_next_rdnno;

    u1_t_ret = (U1)FALSE;
    if(st_ap_WRITE_STS->u1_rdnno == (U1)0U){
        u1_t_preread = u1_s_Nvmc_ChkPreRead(st_ap_CFGDATA);
        if(u1_t_preread == (U1)TRUE){
            u1_t_next_rdnno = (U1)NVMC_NEXTRDNNO_EXE_PREREAD;
            (void)u1_g_Rim_ReadU1withStatus(st_ap_DEVICE_CFG->u2_rimid_next_write_rdnno, &u1_t_next_rdnno);
            if(u1_t_next_rdnno > (U1)NVMC_NEXTRDNNO_MAX){
                u1_t_ret = (U1)TRUE;
            }
        }
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1   u1_s_Nvmc_ChkPreRead(const ST_NVMC_CFGDATA * const st_ap_CFGDATA)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA   : CFG DATA                                                                                  */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
static U1   u1_s_Nvmc_ChkPreRead(const ST_NVMC_CFGDATA * const st_ap_CFGDATA)
{
    const   ST_NVMC_MODULE_CFG          *   st_tp_MODULE_CFG;
            U1                              u1_t_ret;
            U1                              u1_t_map_ptrn;

    u1_t_ret = (U1)FALSE;

    u1_t_map_ptrn = st_ap_CFGDATA->u1_map;
    if(u1_t_map_ptrn < u1_d_NVMC_MODULE_NUM){
        st_tp_MODULE_CFG = &st_dp_NVMC_MODULE_CFG[u1_t_map_ptrn];

        if(((st_ap_CFGDATA->u4_module_bit_cfg & (U4)NVMC_DATA_ATTR_BIT_PREREAD) != (U4)0U) &&
           (st_tp_MODULE_CFG->fp_p_u1_GetRdnPreRead != vdp_PTR_NA)){
            u1_t_ret = (U1)TRUE;
        }
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1   u1_s_Nvmc_GetWriteRdnNo(const  ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const ST_NVMC_WRITE_STS * const st_ap_WRITE_STS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> st_ap_DEVICE_CFG : DEVICE                                                                                    */
/*                  --> *st_ap_CFGDATA   : CFG DATA                                                                                  */
/*                  --> *st_ap_WRITE_STS : STS Pointer                                                                               */
/*  Return:         U1 u1_t_ret : RdnNo                                                                                              */
/*===================================================================================================================================*/
static U1   u1_s_Nvmc_GetWriteRdnNo(const  ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const ST_NVMC_WRITE_STS * const st_ap_WRITE_STS)
{
    U4  u4_t_bit;
    U1  u1_t_ret;
    U1  u1_t_preread;
    U1  u1_t_bitpos;
    U1  u1_t_no;

    u1_t_ret = (U1)NVMC_RDNNO_MAX;

    if(st_ap_WRITE_STS->u1_rdnno == (U1)0U){
        u1_t_preread = u1_s_Nvmc_ChkPreRead(st_ap_CFGDATA);
        if(u1_t_preread != (U1)TRUE){
            u1_t_ret = (U1)0U;
        }
        else{
            u1_t_no = (U1)NVMC_NEXTRDNNO_EXE_PREREAD;
            (void)u1_g_Rim_ReadU1withStatus(st_ap_DEVICE_CFG->u2_rimid_next_write_rdnno, &u1_t_no);
            if(u1_t_no <= (U1)NVMC_NEXTRDNNO_MAX){
                u1_t_ret = u1_t_no;
            }
        }
    }
    else{
        u4_t_bit = ~((U4)st_ap_WRITE_STS->u1_rdnno);
        u1_t_bitpos = u1_g_LsbSrch(u4_t_bit);
        if(u1_t_bitpos < (U1)NVMC_RDNNO_BITLEN_MAX){
            u1_t_ret = u1_t_bitpos;
        }
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static void vd_s_Nvmc_AddWriteRdnNo(const  ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const ST_NVMC_CFGDATA * const st_ap_CFGDATA, ST_NVMC_WRITE_STS *st_ap_write_sts) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> st_ap_DEVICE_CFG : DEVICE                                                                                    */
/*                  --> *st_ap_CFGDATA   : CFG DATA                                                                                  */
/*                  --> *st_ap_write_sts : STS Pointer                                                                               */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Nvmc_AddWriteRdnNo(const  ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const ST_NVMC_CFGDATA * const st_ap_CFGDATA, ST_NVMC_WRITE_STS *st_ap_write_sts)
{
    U1  u1_t_preread;
    U1  u1_t_bit;
    U1  u1_t_no;

    u1_t_bit = (U1)NVMC_RDNNO_MAX;

    if(st_ap_write_sts->u1_rdnno == (U1)0U){
        u1_t_preread = u1_s_Nvmc_ChkPreRead(st_ap_CFGDATA);
        if(u1_t_preread != (U1)TRUE){
            u1_t_bit = (U1)0x01U;
        }
        else{
            u1_t_no = (U1)NVMC_NEXTRDNNO_EXE_PREREAD;
            (void)u1_g_Rim_ReadU1withStatus(st_ap_DEVICE_CFG->u2_rimid_next_write_rdnno, &u1_t_no);
            if(u1_t_no <= (U1)NVMC_NEXTRDNNO_MAX){
                u1_t_bit = (U1)0x01 << u1_t_no;
            }
        }
    }
    else if(st_ap_write_sts->u1_rdnno < (U1)NVMC_RDNNO_MAX){
        u1_t_bit = st_ap_write_sts->u1_rdnno;
        u1_t_bit |= (u1_t_bit + (U1)1U);
    }
    else{
        /* u1_t_bit = (U1)NVMC_RDNNO_MAX; */
    }

    st_ap_write_sts->u1_rdnno = u1_t_bit;
}

/*===================================================================================================================================*/
/*  static void vd_s_Nvmc_ClrNvmReadSts(ST_NVMC_READ_STS *st_ap_read_sts, const U2 u2_a_START_POS, const U2 u2_a_BUFSIZE)            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_read_sts : STS Pointer                                                                                */
/*                  --> u2_a_START_POS  : Start position                                                                             */
/*                  --> u2_a_BUFSIZE    : Buffer Size                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Nvmc_ClrNvmReadSts(ST_NVMC_READ_STS *st_ap_read_sts, const U2 u2_a_START_POS, const U2 u2_a_BUFSIZE)
{
    U4  *   u4_tp_data;
    U1  *   u1_tp_status;
    U2      u2_t_cnt;

    st_ap_read_sts->u1_rdnno = (U1)0U;
    st_ap_read_sts->u1_step = (U1)0U;
    st_ap_read_sts->u1_busyretry = (U1)0U;

    u4_tp_data = &u4_dp_nvmc_read_data_buf[u2_a_START_POS];
    u1_tp_status = &u1_dp_nvmc_read_status_buf[u2_a_START_POS];
    for(u2_t_cnt = (U2)0U; u2_t_cnt < u2_a_BUFSIZE; u2_t_cnt++){
        u4_tp_data[u2_t_cnt] = (U4)0U;
        u1_tp_status[u2_t_cnt] = (U1)NVMC_RESULT_NON;
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_Nvmc_ClrNvmWriteSts(ST_NVMC_WRITE_STS *st_ap_write_sts)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_write_sts : STS Pointer                                                                               */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Nvmc_ClrNvmWriteSts(ST_NVMC_WRITE_STS *st_ap_write_sts)
{
    st_ap_write_sts->u1_rdnno = (U1)0U;
    st_ap_write_sts->u1_step = (U1)0U;
    st_ap_write_sts->u1_writeretry = (U1)0U;
}

/*===================================================================================================================================*/
/*  static U1   u1_s_Nvmc_AcsNvmReadReq(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const ST_NVMC_CFGDATA * const  st_ap_CFGDATA, const ST_NVMC_READ_STS * const st_ap_READ_STS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> st_ap_DEVICE_CFG : DEVICE                                                                                    */
/*                  --> *st_ap_CFGDATA   : CFG DATA                                                                                  */
/*                  --> st_ap_READ_STS   : Read Status                                                                               */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
static U1   u1_s_Nvmc_AcsNvmReadReq(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const ST_NVMC_CFGDATA * const  st_ap_CFGDATA, const ST_NVMC_READ_STS * const st_ap_READ_STS)
{
    const   ST_NVMC_MODULE_CFG          *   st_tp_MODULE_CFG;
            U2                              u2_t_blockid;
            U1                              u1_t_ret;
            U1                              u1_t_map_ptrn;

    u1_t_map_ptrn = st_ap_CFGDATA->u1_map;
    /* It is not necessary to check the range of u1_t_map_ptrn because caller check it. */
    st_tp_MODULE_CFG = &st_dp_NVMC_MODULE_CFG[u1_t_map_ptrn];
    u1_t_ret = (U1)FALSE;
    if(
        (st_ap_READ_STS->u1_step < st_tp_MODULE_CFG->u1_blocknum) &&
        (st_ap_READ_STS->u1_rdnno < st_tp_MODULE_CFG->u1_rdnnum)
    ){
        u2_t_blockid  = st_ap_CFGDATA->u2_addr;
        u2_t_blockid += u2_s_Nvmc_GetBlockIdOffset(st_ap_CFGDATA->u2_offset, st_ap_READ_STS->u1_rdnno, st_ap_READ_STS->u1_step);
        u1_t_ret = u1_s_Nvmc_ReadBlockReq(st_ap_DEVICE_CFG, u2_t_blockid, &st_sp_nvmc_temp_read_buf[st_ap_DEVICE_CFG->u1_dev_num]);
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1   u1_s_Nvmc_ReadBlockReq(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const U2 u2_a_BLOCKID, ST_NVMC_READ_BUF * st_ap_temp_read_buf) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> st_ap_DEVICE_CFG     : DEVICE                                                                                */
/*                  --> u2_a_BLOCKID         : Block ID                                                                              */
/*                  --> *st_ap_temp_read_buf : Read Buffer                                                                           */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
static U1   u1_s_Nvmc_ReadBlockReq(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const U2 u2_a_BLOCKID, ST_NVMC_READ_BUF * st_ap_temp_read_buf)
{
    volatile    U2  u2_t_read_sync;
                U1  u1_t_ret;

    st_ap_temp_read_buf->u2_blockid = (U2)NVMC_INVALID_BLOCK_ID;
    u2_t_read_sync = st_ap_temp_read_buf->u2_blockid;                       /* Dummy read for memory sync */
    st_ap_temp_read_buf->u2_timer = st_ap_DEVICE_CFG->u2_rd_timeout;
    vd_g_MemfillU4(st_ap_temp_read_buf->u4_buf, (U4)0U, (U4)NVMC_BUF_SIZE);
    st_ap_temp_read_buf->u1_readsts = (U1)NVMC_RESULT_NON;
    st_ap_temp_read_buf->u2_blockid = u2_a_BLOCKID;                         /* Write last */
#if ((defined(__AIP_DEBUG_SIM__)) && (__AIP_DEBUG_SIM__==1U))
    st_ap_temp_read_buf->u1_readsts = (U1)NVMC_RESULT_OK;
    u1_t_ret = (U1)TRUE;
#else
    u1_t_ret = (st_ap_DEVICE_CFG->fp_p_u1_read_block)(u2_a_BLOCKID);
    if(u1_t_ret != (U1)TRUE){
        st_ap_temp_read_buf->u2_blockid = (U2)NVMC_INVALID_BLOCK_ID;
        st_ap_temp_read_buf->u1_readsts = (U1)NVMC_RESULT_NG;
    }
    else{
        /* do nothing */
    }
#endif /* #if ((defined(__AIP_DEBUG_SIM__)) && (__AIP_DEBUG_SIM__==1U)) */
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1   u1_s_Nvmc_AcsNvmWriteReq(const  ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const ST_NVMC_WRITE_STS * const st_ap_WRITE_STS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> st_ap_DEVICE_CFG : DEVICE                                                                                    */
/*                  --> *st_ap_CFGDATA   : CFG DATA                                                                                  */
/*                  --> st_ap_WRITE_STS  : Write Status                                                                              */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
static U1   u1_s_Nvmc_AcsNvmWriteReq(const  ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const ST_NVMC_WRITE_STS * const st_ap_WRITE_STS)
{
    const ST_NVMC_MODULE_CFG *          st_tp_MODULE_CFG;

    U4                                  u4_tp_data[NVMC_BUF_SIZE];

    U2                                  u2_t_blockid;
    U2                                  u2_t_data_size;
    U2                                  u2_t_last_index;

    U1                                  u1_t_ret;
    U1                                  u1_t_rimsts;
    U1                                  u1_t_map_ptrn;
    U1                                  u1_t_rdnno;

    vd_g_MemfillU4(u4_tp_data, (U4)0U, (U4)NVMC_BUF_SIZE); /* Codesonar Red Warning : Uninitialized Variable Fix */

    u1_t_map_ptrn = st_ap_CFGDATA->u1_map;
    /* It is not necessary to check the range of u1_t_map_ptrn because caller check it. */
    st_tp_MODULE_CFG = &st_dp_NVMC_MODULE_CFG[u1_t_map_ptrn];
    u2_t_data_size = (U2)(st_tp_MODULE_CFG->u1_datasize);
    if(u2_t_data_size != (U2)0U){
        u2_t_last_index = (u2_t_data_size + (U2)NVMC_ARRAY_INDEX_MASK) >> NVMC_ARRAY_INDEX_SHIFT;
        u2_t_last_index = u2_t_last_index - (U2)1U;                          /* No underflow */
        u4_tp_data[u2_t_last_index] = (U4)0U;
        u1_t_rimsts = u1_d_Nvmc_GetRimData(st_ap_CFGDATA->u2_rimid_wdata, u4_tp_data, u2_t_data_size);
    }
    else{
        u1_t_rimsts = (U1)RIM_RESULT_KIND_NG_PRM;
    }
    u1_t_ret = (U1)FALSE;
    if((u1_t_rimsts & (U1)RIM_RESULT_KIND_MASK) != (U1)RIM_RESULT_KIND_OK){
        /* u1_t_ret = (U1)FALSE; */
    }
    else if(st_tp_MODULE_CFG->fp_p_vd_GetRdnWrite != vdp_PTR_NA){
        u1_t_rdnno = u1_s_Nvmc_GetWriteRdnNo(st_ap_DEVICE_CFG, st_ap_CFGDATA, st_ap_WRITE_STS);
        if(
            (st_ap_WRITE_STS->u1_step < st_tp_MODULE_CFG->u1_blocknum) &&
            (u1_t_rdnno < st_tp_MODULE_CFG->u1_rdnnum)
        ){

            st_tp_MODULE_CFG->fp_p_vd_GetRdnWrite(u4_tp_data, u1_t_rdnno, st_ap_WRITE_STS->u1_step);
            vd_d_Nvmc_ConvPtrU4toU1(u4_tp_data, (U2)st_tp_MODULE_CFG->u1_blocksize);

            u2_t_blockid  = st_ap_CFGDATA->u2_addr;
            u2_t_blockid += u2_s_Nvmc_GetBlockIdOffset(st_ap_CFGDATA->u2_offset, u1_t_rdnno, st_ap_WRITE_STS->u1_step);
            (void)u1_s_Nvmc_WriteBlockReq(st_ap_DEVICE_CFG,
                                          u2_t_blockid,
                                          (const U1 *)u4_tp_data,
                                          &st_sp_nvmc_temp_write_buf[st_ap_DEVICE_CFG->u1_dev_num],
                                          (U2)st_tp_MODULE_CFG->u1_blocksize);
            u1_t_ret = (U1)TRUE;
        }
    }
    else{
        /* u1_t_ret = (U1)FALSE; */
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1 u1_s_Nvmc_WriteBlockReq(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG,                                             */
/*                                    const U2 u2_a_BLOCKID,                                                                         */
/*                                    const U1 * const u1_ap_DATA,                                                                   */
/*                                    ST_NVMC_WRITE_BUF * st_ap_temp_write_buf,                                                      */
/*                                    const U2 u2_a_SIZE)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> st_ap_DEVICE_CFG      : DEVICE                                                                               */
/*                  --> u2_a_BLOCKID          : Block ID                                                                             */
/*                  --> *u1_ap_DATA           : Data                                                                                 */
/*                  --> *st_ap_temp_write_buf : Write Buffer                                                                         */
/*                  --> u2_a_SIZE             : Data Size                                                                            */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
static U1 u1_s_Nvmc_WriteBlockReq(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG,
                                  const U2 u2_a_BLOCKID,
                                  const U1 * const u1_ap_DATA,
                                  ST_NVMC_WRITE_BUF * st_ap_temp_write_buf,
                                  const U2 u2_a_SIZE)
{
    volatile    U2  u2_t_read_sync;
                U1  u1_t_ret;

    st_ap_temp_write_buf->u2_blockid = (U2)NVMC_INVALID_BLOCK_ID;
    u2_t_read_sync = st_ap_temp_write_buf->u2_blockid;                      /* Dummy read for memory sync */
    st_ap_temp_write_buf->u2_timer = st_ap_DEVICE_CFG->u2_wr_timeout;
    st_ap_temp_write_buf->u1_writests = (U1)NVMC_RESULT_NON;
    st_ap_temp_write_buf->u2_blockid = u2_a_BLOCKID;                        /* Write last */
    u1_t_ret = (st_ap_DEVICE_CFG->fp_p_u1_write_block)(u2_a_BLOCKID, u1_ap_DATA, u2_a_SIZE);
    if(u1_t_ret != (U1)TRUE){
        st_ap_temp_write_buf->u2_blockid = (U2)NVMC_INVALID_BLOCK_ID;
        st_ap_temp_write_buf->u1_writests = (U1)NVMC_RESULT_NG;
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U2   u2_s_Nvmc_GetBlockIdOffset(const U2 u2_a_OFFSET, const U1 u1_a_RDNNO, const U1 u1_a_STEP)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_OFFSET : Offset                                                                                         */
/*                  --> u1_a_RDNNO  : RDN No                                                                                         */
/*                  --> u1_a_STEP   : Step                                                                                           */
/*  Return:         U2 u2_t_offset : Offset                                                                                          */
/*===================================================================================================================================*/
static U2   u2_s_Nvmc_GetBlockIdOffset(const U2 u2_a_OFFSET, const U1 u1_a_RDNNO, const U1 u1_a_STEP)
{
    U2  u2_t_offset;

    /* OFFSET = (Number of Redundancy * Offset) + Number of step */
    u2_t_offset = ((U2)u1_a_RDNNO * u2_a_OFFSET) + (U2)u1_a_STEP;

    return(u2_t_offset);
}


/*===================================================================================================================================*/
/*  static U1 u1_s_Nvmc_SetReadBuffer(const U1 u1_a_DEVICE, const U1 u1_a_RESULT, const U1 * const u1_ap_DATA, const U2 u2_a_NUMBYTE) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u1_a_DEVICE     : DEVICE                                                                                     */
/*                  --> u1_a_RESULT     : Result                                                                                     */
/*                  --> *u1_ap_DATA     : Data                                                                                       */
/*                  --> u2_a_NUMBYTE    : Byte size of data                                                                          */
/*  Return:         U1 u1_t_rslt : Result                                                                                            */
/*===================================================================================================================================*/
static U1   u1_s_Nvmc_SetReadBuffer(const U1 u1_a_DEVICE, const U1 u1_a_RESULT, const U1 * const u1_ap_DATA, const U2 u2_a_NUMBYTE)
{
    ST_NVMC_READ_BUF    *   st_tp_read_buf;
    U1                      u1_t_rslt;

    /* Range of u1_a_DEVICE shall be checked in caller */
    st_tp_read_buf = &st_sp_nvmc_temp_read_buf[u1_a_DEVICE];

    if(u1_a_RESULT == (U1)NVMC_RESULT_OK){
        if(u2_a_NUMBYTE <= (U2)(NVMC_BUF_SIZE * NVMC_SIZE_4BYTE)){
            st_tp_read_buf->u2_req_size = u2_a_NUMBYTE;
            vd_d_Nvmc_ConvPtrU1toU4(st_tp_read_buf->u4_buf, u1_ap_DATA, u2_a_NUMBYTE);
            u1_t_rslt = u1_a_RESULT;
        }
        else{
            st_tp_read_buf->u2_req_size = (U2)NVMC_NG_INVALID_SIZE;
            u1_t_rslt = (U1)NVMC_RESULT_NG;
        }
    }
    else{
        st_tp_read_buf->u2_req_size = (U2)NVMC_NG_INVALID_SIZE;
        u1_t_rslt = u1_a_RESULT;
    }
    st_tp_read_buf->u1_readsts = u1_t_rslt;
    
    return(u1_t_rslt);
}

/*===================================================================================================================================*/
/*  static U1 u1_s_Nvmc_SetWriteBuffer(const U1 u1_a_DEVICE, const U1 u1_a_RESULT)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u1_a_DEVICE  : DEVICE                                                                                        */
/*                  --> u1_a_RESULT  : Result                                                                                        */
/*  Return:         U1 u1_t_rslt : Result                                                                                            */
/*===================================================================================================================================*/
static U1   u1_s_Nvmc_SetWriteBuffer(const U1 u1_a_DEVICE, const U1 u1_a_RESULT)
{
    ST_NVMC_WRITE_BUF   *   st_tp_write_buf;
    U1                      u1_t_rslt;

    /* Range of u1_a_DEVICE shall be checked in caller */

    st_tp_write_buf = &st_sp_nvmc_temp_write_buf[u1_a_DEVICE];
    st_tp_write_buf->u1_writests = u1_a_RESULT;
    
    u1_t_rslt = u1_a_RESULT;

    return(u1_t_rslt);
}

/*===================================================================================================================================*/
/*  static void vd_s_Nvmc_InAppJobFinishHook(const U2 u2_a_NO, const U2 u2_a_BLOCKID, const U1 u1_a_REQUEST_TYPE, const U1 u1_a_RESULT, const U1 * const u1_ap_DATA, const U2 u2_a_SIZE) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_NO           : TBL No                                                                                   */
/*                  --> u2_a_BLOCKID      : Block ID                                                                                 */
/*                  --> u1_a_REQUEST_TYPE : Request Type                                                                             */
/*                  --> u1_a_RESULT       : Result                                                                                   */
/*                  --> *u1_ap_DATA       : Data                                                                                     */
/*                  --> u2_a_SIZE         : Data Size                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Nvmc_InAppJobFinishHook(const U2 u2_a_NO, const U2 u2_a_BLOCKID, const U1 u1_a_REQUEST_TYPE, const U1 u1_a_RESULT, const U1 * const u1_ap_DATA, const U2 u2_a_SIZE)
{
    if(u2_a_NO < (U2)u1_d_NVMC_APP_ACS_NUM){
        if(st_NVMC_APP_FUNC_TABLE[u2_a_NO].fp_p_vd_hook != vdp_PTR_NA){
            (*st_NVMC_APP_FUNC_TABLE[u2_a_NO].fp_p_vd_hook)(u2_a_BLOCKID, u1_a_REQUEST_TYPE, u1_a_RESULT, u1_ap_DATA, u2_a_SIZE);
        }
    }
}

/*===================================================================================================================================*/
/*  static U1   u1_s_Nvmc_AcsNvmRecoveryTrans(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const U2 u2_a_NO) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> st_ap_DEVICE_CFG : DEVICE                                                                                    */
/*                  --> *st_ap_CFGDATA   : CFG DATA                                                                                  */
/*                  --> u2_a_NO          : TBL No                                                                                    */
/*  Return:         U1 u1_t_ret : TRUE / FALSE                                                                                       */
/*===================================================================================================================================*/
static U1   u1_s_Nvmc_AcsNvmRecoveryTrans(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const U2 u2_a_NO)
{
    const   ST_NVMC_MODULE_CFG  *   st_tp_MODULE_CFG;
            ST_NVMC_READ_STS    *   st_tp_read_sts;
            U1                  *   u1_tp_recovery_sts;
            U4                      u4_tp_writedata[NVMC_BUF_SIZE];
            U2                      u2_t_blockid;
            U2                      u2_t_offset;
            U1                      u1_t_ret;
            U1                      u1_t_sts;
            U1                      u1_t_rslt;
            U1                      u1_t_map_ptrn;

    u1_tp_recovery_sts = &u1_dp_nvmc_recovery_retry[st_ap_DEVICE_CFG->u1_dev_num];
    st_tp_read_sts     = &st_sp_nvmc_read_sts[st_ap_DEVICE_CFG->u1_dev_num];
    u1_t_map_ptrn      = st_ap_CFGDATA->u1_map;
    if(u1_t_map_ptrn >= u1_d_NVMC_MODULE_NUM){

        *u1_tp_recovery_sts = (U1)NVMC_RECOVERY_STS_END;
    }
    else if(*u1_tp_recovery_sts == (U1)0U){

        /* Has not read requested */
        (*u1_tp_recovery_sts)++;
        vd_s_Nvmc_ClrNvmReadSts(st_tp_read_sts, st_ap_DEVICE_CFG->u2_t_buf_base, (U2)st_ap_DEVICE_CFG->u1_use_bufsize);
    }
    else if(*u1_tp_recovery_sts <= st_ap_DEVICE_CFG->u1_recover_retry){

        st_tp_MODULE_CFG = &st_dp_NVMC_MODULE_CFG[u1_t_map_ptrn];
        u1_t_sts         = u1_s_Nvmc_ReadRednData(st_ap_DEVICE_CFG, st_tp_MODULE_CFG);
        if(u1_t_sts == (U1)NVMC_READ_REDN_DATA_COMPLETE){

            vd_g_MemfillU4(u4_tp_writedata, (U4)0U, (U4)NVMC_BUF_SIZE);  /* Codesonar Red Warning : Uninitialized Variable Fix */

            u2_t_offset = (U2)0U;
            u1_t_rslt   = u1_s_Nvmc_GetRdnRecovery(st_ap_DEVICE_CFG, st_ap_CFGDATA, u4_tp_writedata, &u2_t_offset);
            /* ALL OK or All lost, then no need to recovery */
            if(u1_t_rslt == (U1)NVMC_RECOVERY_UNNECESARY){

                *u1_tp_recovery_sts = (U1)NVMC_RECOVERY_STS_END;
            }
            /* Found any lost data */
            else if(u1_t_rslt == (U1)NVMC_RECOVERY_FOUND_LOST_DATA){

                u2_t_blockid = st_ap_CFGDATA->u2_addr + u2_t_offset;

                vd_d_Nvmc_ConvPtrU4toU1(u4_tp_writedata, (U2)st_tp_MODULE_CFG->u1_blocksize);
                (void)u1_s_Nvmc_WriteBlockReq(st_ap_DEVICE_CFG, u2_t_blockid,
                                              (const U1*)u4_tp_writedata,
                                              &st_sp_nvmc_temp_write_buf[st_ap_DEVICE_CFG->u1_dev_num],
                                              (U2)st_tp_MODULE_CFG->u1_blocksize);

                (*u1_tp_recovery_sts)++;
                vd_s_Nvmc_ClrNvmReadSts(st_tp_read_sts, st_ap_DEVICE_CFG->u2_t_buf_base, (U2)st_ap_DEVICE_CFG->u1_use_bufsize);
            }
            /* Other fail, then retry from first */
            else{

                (*u1_tp_recovery_sts)++;
                vd_s_Nvmc_ClrNvmReadSts(st_tp_read_sts, st_ap_DEVICE_CFG->u2_t_buf_base, (U2)st_ap_DEVICE_CFG->u1_use_bufsize);
            }
        }
        else if(u1_t_sts == (U1)NVMC_READ_REDN_DATA_ERROR){
            /* Read fail */
            (*u1_tp_recovery_sts)++;
            vd_s_Nvmc_ClrNvmReadSts(st_tp_read_sts, st_ap_DEVICE_CFG->u2_t_buf_base, (U2)st_ap_DEVICE_CFG->u1_use_bufsize);
        }
        else{
            /* Other case, then keep going */
        }
    }
    else{
        /* Retry out */
        *u1_tp_recovery_sts = (U1)NVMC_RECOVERY_STS_END;
    }

    u1_t_ret = (U1)FALSE;
    if(*u1_tp_recovery_sts > st_ap_DEVICE_CFG->u1_recover_retry){
        /* No more retry */
        u1_t_ret = (U1)TRUE;
    }
    else{
        (void)u1_s_Nvmc_AcsNvmReadReq(st_ap_DEVICE_CFG, st_ap_CFGDATA, st_tp_read_sts);
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1   u1_s_Nvmc_GetRdnRecovery(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 *u4_ap_rdnrslt, U2 *u2_ap_offset) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_DEVICE_CFG : DEVICE                                                                                   */
/*                  --> *st_ap_CFGDATA    : CFG DATA                                                                                 */
/*                  --> *u4_ap_rdnrslt    : RDN Data                                                                                 */
/*                  --> *u2_ap_offset     : Recovery Data Offset                                                                     */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_Nvmc_GetRdnRecovery(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 *u4_ap_rdnrslt, U2 *u2_ap_offset)
{
    const   ST_NVMC_MODULE_CFG  *   st_tp_MODULE_CFG;
            U4                  *   u4_tp_data_buf;
            U1                  *   u1_tp_status_buf;
            U4                  *   u4_tp_writedata;
            U2                      u2_t_pos;
            U2                      u2_t_vanish_offset;
            U2                      u2_t_base_size;
            U1                      u1_t_ret;
            U1                      u1_t_block;
            U1                      u1_t_rdn;
            U1                      u1_t_sts;
            U1                      u1_t_cnt_lost;
            U1                      u1_t_map_ptrn;
            U1                      u1_t_rdnnum;

    u1_t_rdnnum = (U1)0U;
    u1_t_map_ptrn = st_ap_CFGDATA->u1_map;
    if(u1_t_map_ptrn < u1_d_NVMC_MODULE_NUM){
        st_tp_MODULE_CFG = &st_dp_NVMC_MODULE_CFG[u1_t_map_ptrn];
        u1_t_rdnnum = st_tp_MODULE_CFG->u1_rdnnum;
    }
    u1_t_ret = (U1)NVMC_RECOVERY_UNNECESARY;
    if(u1_t_rdnnum <= (U1)1U){
        /* No redundancy data, cannot recover */
        /* u1_t_ret = (U1)NVMC_RECOVERY_UNNECESARY; */
    }
    else{
        u2_t_pos = st_ap_DEVICE_CFG->u2_t_buf_base;
        u4_tp_data_buf = &u4_dp_nvmc_read_data_buf[u2_t_pos];
        u1_tp_status_buf = &u1_dp_nvmc_read_status_buf[u2_t_pos];
        u4_tp_writedata = &u4_tp_data_buf[u2_t_pos];
        u1_t_block = (U1)0U;
        u2_t_base_size = (U2)st_tp_MODULE_CFG->u1_rdnnum * (U2)st_tp_MODULE_CFG->u1_blocknum * (U2)st_tp_MODULE_CFG->u1_wordbuf_num;
        do{
            u2_t_pos = u2_t_base_size + (((U2)u1_t_block) * ((U2)(st_tp_MODULE_CFG->u1_wordbuf_num)));
            u1_t_rdn = st_tp_MODULE_CFG->u1_rdnnum;
            u2_t_vanish_offset = (U2)0U;
            u1_t_cnt_lost = (U1)0U;
            do{
                u2_t_pos -= (U2)st_tp_MODULE_CFG->u1_blocknum * (U2)st_tp_MODULE_CFG->u1_wordbuf_num;
                u1_t_rdn--;
                u1_t_sts = u1_tp_status_buf[u2_t_pos];
                if(u1_t_sts == (U1)NVMC_RESULT_OK){
                    u4_tp_writedata = &u4_tp_data_buf[u2_t_pos];
                }
                else if(u1_t_sts == (U1)NVMC_RESULT_NODATA){
                    u2_t_vanish_offset = u2_s_Nvmc_GetBlockIdOffset(st_ap_CFGDATA->u2_offset, u1_t_rdn, u1_t_block);
                    u1_t_cnt_lost++;
                }
                else{
                    u1_t_ret = (U1)NVMC_RECOVERY_READ_AGAIN;
                    u1_t_cnt_lost = (U1)0U;
                    u1_t_rdn = (U1)0U;
                }
            }while(u1_t_rdn > (U1)0U);
            if(u1_t_cnt_lost == (U1)0U){
                /* All read data are valid or read fail is found  */
                /* No update u1_t_ret and check next data. */
            }
            else if(u1_t_cnt_lost < st_tp_MODULE_CFG->u1_rdnnum){
                /* Some lost data are found. */
                vd_g_MemcpyU4(u4_ap_rdnrslt, u4_tp_writedata, (U4)st_tp_MODULE_CFG->u1_wordbuf_num);
                *u2_ap_offset = u2_t_vanish_offset;
                u1_t_ret = (U1)NVMC_RECOVERY_FOUND_LOST_DATA;
                break;
            }
            else{
                /* Lost all data */
                /* No update u1_t_ret and check next data. */
            }
            u1_t_block++;
        }while(u1_t_block < st_tp_MODULE_CFG->u1_blocknum);
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version         Date        Author  Change Description                                                                           */
/* ---------------  ----------  ------  -------------------------------------------------------------------------------------------  */
/*  1.0.0           12/16/2015   KM      New.                                                                                        */
/*  1.0.1            1/ 8/2016   KM      Supported debug simulatior.                                                                 */
/*                                       vd_d_Nvmc_DCK_SetErrData() name was changed to vd_d_Nvmc_DCK_SetDefaultData().              */
/*  1.0.2            1/22/2016   KM      Fixed Error log.                                                                            */
/*  1.1.0            2/ 4/2016   KM      Added PreRead Process.                                                                      */
/*  1.1.1            3/25/2016   KM      Fixed Unit Test issue.                                                                      */
/*  1.1.2            4/ 4/2016   KM      Fixed PCS3-2 issue.                                                                         */
/*  1.1.3            4/11/2016   HK      Fixed function comments.                                                                    */
/*  1.1.4            4/12/2016   KM      Deleted unnecessary include.                                                                */
/*                                       Fixed u1_s_Nvmc_AcsNvmRecoveryTrans                                                         */
/*  1.1.5            4/18/2016   KM      Added BlockId Invalid check to vd_g_Nvmc_JobFinishHook.                                     */
/*  1.1.6            4/11/2016   HK      Fixed PCS3-2 issue.                                                                         */
/*  1.1.7            5/30/2016   KM      Fixed ReadSts Clear Timming.                                                                */
/*  1.2.0            10/28/2016  HK      Changed with the small sector correspondence.                                               */
/*                                       Fixed AIP3GBSW-10 issue.                                                                    */
/*  1.2.1            11/25/2016  HK      Fixed vd_g_Nvmc_JobFinishHook.                                                              */
/*  1.2.2            12/07/2016  HK      Fixed AIP3GBSW-26, 27, 36 issue.                                                            */
/*  1.2.3             9/14/2021  TN      NULL -> vdp_PTR_NA.                                                                         */
/*  1.3.0            10/ 4/2021  TN      QAC warning#2972 were fixed.                                                                */
/*                   10/ 7/2021  TN      Codesonar Red Warning : Uninitialized Variable were fixed.                                  */
/*  1.4.0            20/ 2/2023  KM      Fixed SuspendAcs.                                                                           */
/*                                       vd_g_Nvmc_SuspendAcs() -> u1_g_Nvmc_SuspendAcs().                                           */
/*                                       Added u1_g_Nvmc_IsSuspendAcs().                                                             */
/*  1.4.1            11/ 8/2023  KN      Improvement : Warning MISRA-C-Rule7.2 and Waning MISRA-C-Rule15.7 was fixed.                */
/*                                                                                                                                   */
/*  * TN      = Takashi Nagai, Denso                                                                                                 */
/*  * KM      = Kazuyuki Makino, Denso Create                                                                                        */
/*  * HK      = Hayato Kanamori, Denso Create                                                                                        */
/*  * KN      = Keigo Nomura   , Denso Create                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
