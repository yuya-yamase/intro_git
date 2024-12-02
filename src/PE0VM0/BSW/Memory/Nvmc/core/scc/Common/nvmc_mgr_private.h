/* 1.7.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Nvmc : Mgr                                                                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef NVMC_MGR_PRIVATE_H
#define NVMC_MGR_PRIVATE_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NVMC_MGR_PRIVATE_H_MAJOR                 (1U)
#define NVMC_MGR_PRIVATE_H_MINOR                 (7U)
#define NVMC_MGR_PRIVATE_H_PATCH                 (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Access type */
#define NVMC_ACS_INAPP                           (0U)     /* Application access            */
#define NVMC_ACS_INNVM                           (1U)     /* NVMC access                   */
#define NVMC_ACS_TYPE_ERR                        (2U)     /* Out of range                  */

/* Single device value */
#define NVMC_SINGLE_DEV_NUM                      (1U)

/* Array index convertion */
#define NVMC_ARRAY_INDEX_SHIFT                   (2U)
#define NVMC_ARRAY_INDEX_MASK                    (0x0003U)

/* Invalid value definition */
#define NVMC_INVALID_BLOCK_ID                    (0xFFFFU)
#define NVMC_REQID_TASK_IDLE                     (0xFFFFU)
#define NVMC_INVALID_RIM_ID                      (0xFFFFU)
#define NVMC_INVALID_REQ_ID                      (0xFFFFU)
#define NVMC_INVALID_CACHE_ID                    (0xFFFFU)

/* Nvmc SIZE */
#define NVMC_SIZE_1BYTE                          (1U)
#define NVMC_SIZE_2BYTE                          (2U)
#define NVMC_SIZE_4BYTE                          (4U)

/* Access type definition */
#define NVMC_ACCSS_TYPE_BIT                      (0x8000U)
#define NVMC_ACCSS_REQ_ID_MASK                   (0x7FFFU)
#define NVMC_ACCSS_TYPE_INNVM                    (0x0000U)
#define NVMC_ACCSS_TYPE_INAPP                    (0x8000U)

/* Data configuration bits */
#define NVMC_SETT_CMN_BON_TIMING_MASK            (0x80U)      /* BON NVM read timing           */
#define NVMC_SETT_CMN_WKUP_COND_MASK             (0x60U)      /* WKUP NVM read condition       */
#define NVMC_SETT_CMN_WKUP_TIMING_MASK           (0x10U)      /* WKUP NVM read timing          */
#define NVMC_SETT_CMN_ERR_SYNC_MASK              (0x08U)      /* Auto cache error correction   */
#define NVMC_SETT_CMN_READONLY_MASK              (0x04U)      /* Read only                     */
/*                                               (0x02U)*/    /* RESERVED                      */
#define NVMC_SETT_CMN_READID_MASK                (0x01U)      /* Indivisual Read cache         */

/* Module attribute bit definition */
#define NVMC_MOD_ATTR_RECOVERABLE_BIT            (0x01U)

/* WKUP NVM read condition */
#define NVMC_SETT_CMN_WKUP_COND_NON              (0x00U)      /* No read                   */
#define NVMC_SETT_CMN_WKUP_COND_EVRY             (0x20U)      /* Every wakeup              */
#define NVMC_SETT_CMN_WKUP_COND_ABNML            (0x40U)      /* On error                  */
/*                                               (0x60U)*/    /* RESERVED                  */

/* Module Result */
#define NVMC_MOD_RSLT_NUM                        (7U)
#define NVMC_MOD_RSLT_OK                         (0U)         /* Normal completion        */
#define NVMC_MOD_RSLT_NG                         (1U)         /* Error completion         */
#define NVMC_MOD_RSLT_NODATA                     (2U)         /* Lost some data           */
#define NVMC_MOD_RSLT_LOST                       (3U)         /* Lost all data            */
#define NVMC_MOD_RSLT_RDN_NG                     (4U)         /* Redundancy data error    */
#define NVMC_MOD_RSLT_RANGEOUT                   (5U)         /* Range out                */
#define NVMC_MOD_RSLT_UNMATCH                    (6U)         /* Write data <> Read data  */

/* Value index definitions */
#define NVMC_DCK_FAIL_VAL_NUM                    (3U)
#define NVMC_DCK_FAIL_VAL_DEF                    (0U)
#define NVMC_DCK_FAIL_VAL_MIN                    (1U)
#define NVMC_DCK_FAIL_VAL_MAX                    (2U)

/* read/write_status */
#define NVMC_DCK_ERR_ACT_DEFAULT                 (0x0U)   /* Default value         */
#define NVMC_DCK_ERR_ACT_MIN                     (0x1U)   /* Minimum value         */
#define NVMC_DCK_ERR_ACT_MAX                     (0x2U)   /* Maximum value         */
#define NVMC_DCK_ERR_ACT_LAST                    (0x3U)   /* Previous value        */
#define NVMC_DCK_ERR_ACT_WRITE                   (0x4U)   /* Write value           */
#define NVMC_DCK_ERR_ACT_READ                    (0x5U)   /* Read value            */
/*                                               (0x6U)*/ /* RESERVED              */
/*                                                ....                             */
/*                                               (0xFU)*/ /* RESERVED              */

/* Fail bits location */
#define NVMC_DCK_ACT_NG_SHFT                     (0U)
#define NVMC_DCK_ACT_LOST_SHFT                   (4U)
#define NVMC_DCK_ACT_RDN_NG_SHFT                 (8U)
#define NVMC_DCK_ACT_RANGEOUT_SHFT               (12U)
#define NVMC_DCK_ACT_UNMATCH_SHFT                (16U)
#define NVMC_DCK_ERR_ACT_NUM                     (8U)
#define NVMC_DCK_ACT_MASK                        (0x00000007U)

/* Fail action bits */
#define NVMC_DCK_ACT_BIT_NG                      (0x0000000FU)
#define NVMC_DCK_ACT_BIT_LOST                    (0x000000F0U)
#define NVMC_DCK_ACT_BIT_RDN_NG                  (0x00000F00U)
#define NVMC_DCK_ACT_BIT_RANGEOUT                (0x0000F000U)
#define NVMC_DCK_ACT_BIT_UNMATCH                 (0x000F0000U)

#define NVMC_DATA_ATTR_BIT_PREREAD               (0x20000000U)
#define NVMC_DATA_ATTR_BIT_RECOVERY              (0x40000000U)
#define NVMC_DATA_ATTR_BIT_SIGNED                (0x80000000U)

#define NVMC_DATA_ATTR_RDNT_TYPE_MASK            (0x03000000U)

#define NVMC_DATA_ATTR_RDNT_TYPE_BIT             (0x00000000U)
#define NVMC_DATA_ATTR_RDNT_TYPE_1ST             (0x01000000U)
#define NVMC_DATA_ATTR_RDNT_TYPE_MIN             (0x02000000U)
#define NVMC_DATA_ATTR_RDNT_TYPE_MAX             (0x03000000U)

#define NVMC_BUF_SIZE                            (8U)         /* 8 x 4byte = 32byte */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U2          u2_addr;                            /* NVM lowest address                */
    U2          u2_offset;                          /* Offset                            */
    U2          u2_rimid_wdata;                     /* Rim ID : WriteData                */
    U2          u2_rimid_nvmsts;                    /* Rim ID : Data status              */
    U1          u1_map;                             /* Map pattern                       */
    U1          u1_rangeretry;                      /* Number of Range retry             */
    U1          u1_verifyretry;                     /* Number of Verify retry            */
    U1          u1_mgr_bit_cfg;                     /*  1 : BON read timing              */
                                                    /*  2 : Wakeup Read condition        */
                                                    /*  1 : Wakeup read timing           */
                                                    /*  1 : Auto cache error correction  */
                                                    /*  1 : Read Only                    */
                                                    /*  1 : RESERVED                     */
                                                    /*  1 : Common cache                 */
    U4          u4_module_bit_cfg;                  /* Actions and config                */
    U4          u4_p_val[NVMC_DCK_FAIL_VAL_NUM];    /* Default/Min/Max Values            */
}ST_NVMC_CFGDATA;

typedef struct{
    const   U2                  * const     u2_p_NO;                                                                                       /* Access type table                 */
    const   ST_NVMC_CFGDATA     * const     st_p_CFGDATA;                                                                                  /* Data configuration table          */
            U2                              u2_id_num;                                                                                     /* Number of IDs                     */
            U2                              u2_innvm_num;                                                                                  /* Number of data accessed by NVMC   */
            U2                              u2_rd_timeout;                                                                                 /* Read Timeout(LSB:20ms)            */
            U2                              u2_wr_timeout;                                                                                 /* Write Timeout(LSB:20ms)           */
            U2                              u2_syncrd_timeout;                                                                             /* SyncRead Timeout(LSB:Times)       */
            U2                              u2_suspend_timeout;                                                                            /* Suspend Timeout(LSB:20ms)         */
            U2                              u2_rimid_initid;                                                                               /* Rim ID : Proccessing ID           */
            U2                              u2_rimid_req;                                                                                  /* Rim ID : Request bit              */
            U2                              u2_t_buf_base;                                                                                 /* Read buffer base index            */
            U2                              u2_t_write_sts_base;                                                                           /* Write status base index           */
            U2                              u2_recovery_req_id;                                                                            /* Recovery request NVMC id          */
            U2                              u2_rimid_recovery_proc;                                                                        /* Rim ID : Proccessign ID of Recovery */
            U2                              u2_rimid_next_write_rdnno;                                                                     /* Rim ID : Next Write Rdn No        */
            U1                              u1_use_bufsize;                                                                                /* NVMACS : Use buf size             */
            U1                              u1_busyretry;                                                                                  /* Number of read retry              */
            U1                              u1_wr_retry;                                                                                   /* Number of write retry             */
            U1                              u1_recover_retry;                                                                              /* Number of recovery retry          */
            U1                              u1_dev_num;                                                                                    /* Device ID                         */
            void (              * const     fp_p_vd_execution_func)(void);                                                                 /* Driver execution task function    */
            U1   (              * const     fp_p_u1_read_block)(const U2 u2_a_BLOCKID);                                                    /* Read request function             */
            U1   (              * const     fp_p_u1_write_block)(const U2 u2_a_BLOCKID, const U1 * const u1_ap_DATA, const U2 u2_a_SIZE);  /* Write request function            */
            U1   (              * const     fp_p_u1_erase_block)(const U2 u2_a_BLOCKID);                                                   /* Erase request function            */
            U1   (              * const     fp_p_u1_read_direct)(const U2 u2_a_BLOCKID, U1 * u1_ap_data, const U2 u2_a_SIZE);              /* Direct read request function      */
            U1   (              * const     fp_p_u1_is_idle)(void);                                                                        /* Idle check function               */
}ST_NVMC_DEVICE_CFG;

typedef struct{
    U1   ( * const    fp_p_u1_GetRdnRead)(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS);
    U1   ( * const    fp_p_u1_GetRdnPreRead)(const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS, const U1 u1_a_BLOCKNUM);
    void ( * const    fp_p_vd_GetRdnWrite)(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM);
    U1              u1_datasize;
    U1              u1_blocknum;
    U1              u1_blocksize;
    U1              u1_wordbuf_num;
    U1              u1_rdnnum;
    U1              u1_attr;
}ST_NVMC_MODULE_CFG;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Externs                                                                                                        */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_d_Nvmc_TickTime(U2 *u2_ap_timer, const U2 u2_a_TIMEOUT);

void    vd_d_Nvmc_SetAcsReqSub(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const U2 u2_a_DATAID, const U1 u1_a_MODE);
U1      u1_d_Nvmc_GetAcsReqSub(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const U2 u2_a_DATAID);
U2      u2_d_Nvmc_GetAcsReqNo(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG);
U1      u1_d_Nvmc_GetDataTblNo(const ST_NVMC_DEVICE_CFG * const st_ap_DEVICE_CFG, const U2 u2_a_DATAID, U2 * u2_ap_no);

U1      u1_d_Nvmc_GetRimData(const U2 u2_a_RIMID, U4 * u4_ap_data, const U2 u2_a_SIZE);
U1      u1_d_Nvmc_SetRimData(const U2 u2_a_RIMID, const U4 * const u4_ap_DATA, const U2 u2_a_SIZE);
void    vd_d_Nvmc_ConvPtrU4toU1(U4 * u4_ap_data, const U2 u2_a_NUMBYTE);
void    vd_d_Nvmc_ConvPtrU1toU4(U4 * u4_ap_cpydst, const U1 * const u1_ap_CPYSRC, const U2 u2_a_NUMBYTE);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif /* NVMC_MGR_PRIVATE_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see nvmc_mgr.c                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
