/* 2.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Tripcom Non-volatile Memory Interface                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef TRIPCOM_NVMIF_H
#define TRIPCOM_NVMIF_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPCOM_NVMIF_H_MAJOR                        (2)
#define TRIPCOM_NVMIF_H_MINOR                        (1)
#define TRIPCOM_NVMIF_H_PATCH                        (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPCOM_NVMIF_UNK                            (0xffffffffU)

#define TRIPCOM_NVMIF_CH_NUM                         (22U)  /* Caution!: MAX:32 */
#define TRIPCOM_NVMIF_CH_TOFC_FU                     (0U)
#define TRIPCOM_NVMIF_CH_TOFC_OC                     (1U)
#define TRIPCOM_NVMIF_CH_TOEC_EU                     (2U)
#define TRIPCOM_NVMIF_CH_TOEC_OC                     (3U)
#define TRIPCOM_NVMIF_CH_DTE_FE                      (4U)
#define TRIPCOM_NVMIF_CH_TOSP_OC                     (5U)
#define TRIPCOM_NVMIF_CH_TOSP_ET                     (6U)
#define TRIPCOM_NVMIF_CH_TOTM_ET                     (7U)
#define TRIPCOM_NVMIF_CH_TODT_OC                     (8U)
#define TRIPCOM_NVMIF_CH_TOSP_TR_A_SP_OC             (9U)
#define TRIPCOM_NVMIF_CH_TOSP_TR_A_SP_ET             (10U)
#define TRIPCOM_NVMIF_CH_TOSP_TR_B_SP_OC             (11U)
#define TRIPCOM_NVMIF_CH_TOSP_TR_B_SP_ET             (12U)
#define TRIPCOM_NVMIF_CH_TOTM_TR_A_TM_ET             (13U)
#define TRIPCOM_NVMIF_CH_TOTM_TR_B_TM_ET             (14U)
#define TRIPCOM_NVMIF_CH_TODT_TR_A_DT_OC             (15U)
#define TRIPCOM_NVMIF_CH_TODT_TR_B_DT_OC             (16U)
#define TRIPCOM_NVMIF_CH_DTE_ED_FE                   (17U)
#define TRIPCOM_NVMIF_CH_TAFE_LTST                   (18U)
#define TRIPCOM_NVMIF_CH_TAFE_MAX                    (19U)
#define TRIPCOM_NVMIF_CH_TAEE_LTST                   (20U)
#define TRIPCOM_NVMIF_CH_TAEE_MAX                    (21U)


#define TRIPCOM_NVMIF_DIAG_REQ_CMP                   (0x00U)
#define TRIPCOM_NVMIF_DIAG_REQ_WRI                   (0x01U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U4               u4_value;       /* back-up value        */
    U4               u4_wrt_cnt;     /* Nvm write counter    */
    volatile U4      u4_crc32;
}ST_TRIPCOM_NVMDATA;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_TripcomNvmIfRWRqst(const U1 u1_a_CH, const U4 * u4_ap_NEXT);
                                                                  /* if st_ap_NEXT == vdp_PTR_NA, requst to read all records         */

void    vd_g_TripcomNvmIfInit(const U1 u1_a_SYNC);                          /* called by tripcom                                     */
void    vd_g_TripcomNvmIfDiagStart(const U1 u1_a_REQ);                      /* called by tripcom_ms                                  */

void    vd_g_TripcomNvmIfCbkData(const U1 u1_a_CH, const U4 u4_a_DATA_NVM); /* called by tripcom_nvmif                               */
void    vd_g_TripcomNvmIfDiagFinish(const U1 u1_a_RSLT);                    /* called by tripcom_nvmif                               */
void    vd_g_TripcomNvmIfSyncCmplt(void);                                   /* called by tripcom_nvmif                               */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif      /* TRIPCOM_NVMIF_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  tripcom_nvmif.c                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/
