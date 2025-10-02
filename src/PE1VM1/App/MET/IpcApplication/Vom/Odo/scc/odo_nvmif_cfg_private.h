/* 2.0.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Odo Non-volatile Memory Interface                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef ODO_NVMIF_CFG_H
#define ODO_NVMIF_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ODO_NVMIF_CFG_H_MAJOR                    (2)
#define ODO_NVMIF_CFG_H_MINOR                    (0)
#define ODO_NVMIF_CFG_H_PATCH                    (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "crc32.h"
#include "nvmc_mgr.h"
#include "odo_nvmif.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ODO_NVMIF_TRIP_NUM_REC                   (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ODO_NVMIF_BLO_NBYTE_2                    (2U)
#define ODO_NVMIF_BLO_NBYTE_4                    (4U)
#define ODO_NVMIF_BLO_NBYTE_12                   (12U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u4_g_OdoNvmIfCrc32(u1p, u4)              (u4_g_Crc32((U4)0x5aa5a55aU, (u1p), (u4), (U1)FALSE))

#define vd_g_OdoNvmIfOdoRWAct()                  (vd_g_Nvmc_SetAcsReq(u2_g_ODO_NVMIF_NVMCID_ODO_KM, (U1)TRUE))
#define vd_g_OdoNvmIfOdoRWDeAct()                (vd_g_Nvmc_SetAcsReq(u2_g_ODO_NVMIF_NVMCID_ODO_KM, (U1)FALSE))
#define vd_g_OdoNvmIfTripRWAct()                 (vd_g_Nvmc_SetAcsReq(u2_g_ODO_NVMIF_NVMCID_TRIP_KM, (U1)TRUE))
#define vd_g_OdoNvmIfTripRWDeAct()               (vd_g_Nvmc_SetAcsReq(u2_g_ODO_NVMIF_NVMCID_TRIP_KM, (U1)FALSE))

#define vd_g_OdoNvmIfWriteBlock(m,b,w,l)         ((void)u1_g_Nvmc_WriteBlock((m),(b),(w),(l)))
#define vd_g_OdoNvmIfReadBlock(m,b)              ((void)u1_g_Nvmc_ReadBlock((m),(b)))
#define u1_g_OdoNvmIfSyncBlock(m,b,r,l)          (u1_g_Nvmc_ReadDrctBlock((m),(b),(r),(l)))

#define ODO_NVMIF_REQ_TYPE_READ                  (NVMC_REQUEST_TYPE_READ)
#define ODO_NVMIF_JOB_RESULT_OK                  (NVMC_RESULT_OK)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    const U2 *       u2p_BLOCK;      /* block identifier. the size shall be equal to u1_num_rec * u1_rec_nblock */ 
    U1               u1_num_rec;     /* number of record                                                        */
    U1               u1_rec_nblock;  /* number of blocks per record                                             */
    U1               u1_blo_nbyte;   /* number of bytes per block                                               */ 
    U1               u1_dev_idx;     /* see NVMC_DEV_TYPE_XXX in nvm_mgr_cfg.h                                  */
}ST_ODO_NVMIF_REC_KM;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* U4      u4_g_OdoNvmIfCrc32(const U1 * u1_ap_BLOCK, const U4 u4_a_BLOCK_LEN); */

/* void    vd_g_OdoNvmIfOdoRWAct(void);                                         */
/* void    vd_g_OdoNvmIfOdoRWDeAct(void);                                       */

/* void    vd_g_OdoNvmIfTripRWAct(void);                                        */
/* void    vd_g_OdoNvmIfTripRWDeAct(void);                                      */

/* void    vd_g_OdoNvmIfWriteBlock(const U1 u1_a_DEVICE,                        */
/*                                 const U2 u2_a_BLOCKID,                       */
/*                                 const U1 * const u1_ap_DATA,                 */
/*                                 const U2 u2_a_SIZE);                         */
/* void    vd_g_OdoNvmIfReadBlock(const U1 u1_a_DEVICE, const U2 u2_a_BLOCKID); */
/* U1      u1_g_OdoNvmIfSyncBlock(const U1 u1_a_DEVICE,                         */
/*                                const U2 u2_a_BLOCKID,                        */
/*                                U1 * u1_ap_data,                              */
/*                                const U2 u2_a_SIZE);                          */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const ST_ODO_NVMIF_REC_KM  st_g_ODO_NVMIF_REC_ODO_KM;
extern const U2                   u2_g_ODO_NVMIF_NVMCID_ODO_KM;

extern const ST_ODO_NVMIF_REC_KM  st_g_ODO_NVMIF_REC_TRIP_KM;
extern const U2                   u2_g_ODO_NVMIF_NVMCID_TRIP_KM;

#endif      /* ODO_NVMIF_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  odo_nvmif.c                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
