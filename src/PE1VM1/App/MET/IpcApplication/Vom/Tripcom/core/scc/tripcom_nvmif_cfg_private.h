/* 2.1.2 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Tripcom Non-volatile Memory Interface                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef TRIPCOM_NVMIF_CFG_H
#define TRIPCOM_NVMIF_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPCOM_NVMIF_CFG_H_MAJOR                    (2)
#define TRIPCOM_NVMIF_CFG_H_MINOR                    (1)
#define TRIPCOM_NVMIF_CFG_H_PATCH                    (2)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "crc32.h"
#include "nvmc_mgr.h"
#include "tripcom_nvmif.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPCOM_NVMIF_NUM_REC                        (6U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPCOM_NVMIF_BLO_NBYTE_2                    (2U)
#define TRIPCOM_NVMIF_BLO_NBYTE_4                    (4U)
#define TRIPCOM_NVMIF_BLO_NBYTE_12                   (12U)

#define TRIPCOM_NVMIF_RW_DAT_NUM                     (2U)
#define TRIPCOM_NVMIF_RW_DAT_LAST                    (0U)
#define TRIPCOM_NVMIF_RW_DAT_RDBK                    (1U)

#define TRIPCOM_NVMIF_NBYTE_CRC_32                   (4U)

#define TRIPCOM_NVMIF_DEF_TYPE_NUM                   (2U)
#define TRIPCOM_NVMIF_DEF_TYPE_ZERO                  (0U)
#define TRIPCOM_NVMIF_DEF_TYPE_MAX                   (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u4_g_TripcomNvmIfCrc32(u1p, u4)              (u4_g_Crc32((U4)0x5aa5a55aU, (u1p), (u4), (U1)FALSE))

#define vd_g_TripcomNvmIfRWAct()                     (vd_g_Nvmc_SetAcsReq(u2_g_TRIPCOM_NVMIF_NVMCID_DATA, (U1)TRUE))
#define vd_g_TripcomNvmIfRWDeAct()                   (vd_g_Nvmc_SetAcsReq(u2_g_TRIPCOM_NVMIF_NVMCID_DATA, (U1)FALSE))

#define vd_g_TripcomNvmIfWriteBlock(m,b,w,l)         ((void)u1_g_Nvmc_WriteBlock((m),(b),(w),(l)))
#define vd_g_TripcomNvmIfReadBlock(m,b)              ((void)u1_g_Nvmc_ReadBlock((m),(b)))
#define u1_g_TripcomNvmIfSyncBlock(m,b,r,l)          (u1_g_Nvmc_ReadDrctBlock((m),(b),(r),(l)))

#define TRIPCOM_NVMIF_REQ_TYPE_READ                  (NVMC_REQUEST_TYPE_READ)
#define TRIPCOM_NVMIF_JOB_RESULT_OK                  (NVMC_RESULT_OK)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    const U2 *       u2p_BLOCK;        /* block identifier. the size shall be equal to u1_num_rec * u1_rec_nblock */
    U1               u1_num_rec;       /* number of record                                                        */
    U1               u1_rec_nblock;    /* number of blocks per record                                             */
    U1               u1_blo_nbyte;     /* number of bytes per block                                               */
    U1               u1_dev_idx;       /* see NVMC_DEV_TYPE_XXX in nvm_mgr_cfg.h                                  */
}ST_TRIPCOM_NVMIF_REC_DATA;

typedef struct{
    U1               u1_rec_idx;       /* record index to be read and written     */
    U1               u1_rec_mrk;       /* record index marker                     */
    U1               u1_rec_chk;       /* record check result / counter           */
    U1               u1_blo_cnt;       /* block counter                           */

    U2               u2_rw_ctrl;       /* read/write control state                */
    U2               u2_rtry_cnt;      /* read/write retry counter                */

    volatile U4      u4_crc32;         /* crc32 code                              */
}ST_TRIPCOM_NVMIF_RW_CTRL;

typedef struct{
    U2               u2_len;
    U1               u1_pos_in;
    U1               u1_pos_out;
}ST_TRIPCOM_NVMIF_FIFO_CTRL;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const ST_TRIPCOM_NVMIF_REC_DATA  st_g_TRIPCOM_NVMIF_REC_DATA;
extern const U2                         u2_g_TRIPCOM_NVMIF_NVMCID_DATA;
extern const U1                         u1_g_TRIPCOM_NVMIF_DEF_TYPE[TRIPCOM_NVMIF_CH_NUM];

#endif      /* TRIPCOM_NVMIF_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  tripcom_nvmif.c                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/
