/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Variation Defines / Organized Master Unified System Vehicle Information                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef VARDEF_OMUS_CAN_CFG_PRIVATE_H
#define VARDEF_OMUS_CAN_CFG_PRIVATE_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VARDEF_OMUS_CAN_CFG_PRIV_H_MAJOR                 (1)
#define VARDEF_OMUS_CAN_CFG_PRIV_H_MINOR                 (0)
#define VARDEF_OMUS_CAN_CFG_PRIV_H_PATCH                 (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDF_OMUS_CAN_NUM                    (33U)
#define VDF_OMUS_CAN_TSLCLR_B               (0U)
#define VDF_OMUS_CAN_RRCT_B                 (1U)
#define VDF_OMUS_CAN_RLCT_B                 (2U)
#define VDF_OMUS_CAN_LGTR_B                 (3U)
#define VDF_OMUS_CAN_HDCT_B                 (4U)
#define VDF_OMUS_CAN_RPSD_B                 (5U)
#define VDF_OMUS_CAN_LPSD_B                 (6U)
#define VDF_OMUS_CAN_RRDR_B                 (7U)
#define VDF_OMUS_CAN_RRODS_B                (8U)
#define VDF_OMUS_CAN_RCODS_B                (9U)
#define VDF_OMUS_CAN_RLODS_B                (10U)
#define VDF_OMUS_CAN_R2RODS_B               (11U)
#define VDF_OMUS_CAN_R2CODS_B               (12U)
#define VDF_OMUS_CAN_R2LODS_B               (13U)
#define VDF_OMUS_CAN_R3RODS_B               (14U)
#define VDF_OMUS_CAN_R3CODS_B               (15U)
#define VDF_OMUS_CAN_R3LODS_B               (16U)
#define VDF_OMUS_CAN_FBWTH_B                (17U)
#define VDF_OMUS_CAN_METSRT_B               (18U)
#define VDF_OMUS_CAN_METCPD_B               (19U)
#define VDF_OMUS_CAN_OMBINF_B               (20U)
#define VDF_OMUS_CAN_SPMKM_B                (21U)
#define VDF_OMUS_CAN_SPMMPH_B               (22U)
#define VDF_OMUS_CAN_SPMFSP_B               (23U)
#define VDF_OMUS_CAN_DIMFTL_B               (24U)
#define VDF_OMUS_CAN_METCSR_B               (25U)
#define VDF_OMUS_CAN_METCTT_B               (26U)
#define VDF_OMUS_CAN_BRAND_B                (27U)
#define VDF_OMUS_CAN_METSPO_B               (28U)
#define VDF_OMUS_CAN_BDSTL_B                (29U)
#define VDF_OMUS_CAN_FC_SCL_B               (30U)
#define VDF_OMUS_CAN_EC_SCL_B               (31U)
#define VDF_OMUS_CAN_CSWPOS_B               (32U)

#define VDF_OMUS_FF_NRX                     (0xFFU)

#define VDF_OMUS_TSLCLR_B_YL                (0x00U)
#define VDF_OMUS_TSLCLR_B_RD                (0x01U)

#define VDF_OMUS_RRCT_B_OFF                 (0x00U)
#define VDF_OMUS_RRCT_B_ON                  (0x01U)

#define VDF_OMUS_RLCT_B_OFF                 (0x00U)
#define VDF_OMUS_RLCT_B_ON                  (0x01U)

#define VDF_OMUS_LGTR_B_TR                  (0x00U)
#define VDF_OMUS_LGTR_B_BD                  (0x01U)

#define VDF_OMUS_HDCT_B_OFF                 (0x00U)
#define VDF_OMUS_HDCT_B_ON                  (0x01U)

#define VDF_OMUS_RPSD_B_OFF                 (0x00U)
#define VDF_OMUS_RPSD_B_ON                  (0x01U)

#define VDF_OMUS_LPSD_B_OFF                 (0x00U)
#define VDF_OMUS_LPSD_B_ON                  (0x01U)

#define VDF_OMUS_RRDR_B_OFF                 (0x00U)
#define VDF_OMUS_RRDR_B_ON                  (0x01U)

#define VDF_OMUS_RRODS_B_OFF                (0x00U)
#define VDF_OMUS_RRODS_B_ON                 (0x01U)

#define VDF_OMUS_RCODS_B_OFF                (0x00U)
#define VDF_OMUS_RCODS_B_ON                 (0x01U)

#define VDF_OMUS_RLODS_B_OFF                (0x00U)
#define VDF_OMUS_RLODS_B_ON                 (0x01U)

#define VDF_OMUS_R2RODS_B_OFF               (0x00U)
#define VDF_OMUS_R2RODS_B_ON                (0x01U)

#define VDF_OMUS_R2CODS_B_OFF               (0x00U)
#define VDF_OMUS_R2CODS_B_ON                (0x01U)

#define VDF_OMUS_R2LODS_B_OFF               (0x00U)
#define VDF_OMUS_R2LODS_B_ON                (0x01U)

#define VDF_OMUS_R3RODS_B_OFF               (0x00U)
#define VDF_OMUS_R3RODS_B_ON                (0x01U)

#define VDF_OMUS_R3CODS_B_OFF               (0x00U)
#define VDF_OMUS_R3CODS_B_ON                (0x01U)

#define VDF_OMUS_R3LODS_B_OFF               (0x00U)
#define VDF_OMUS_R3LODS_B_ON                (0x01U)

#define VDF_OMUS_FBWTH_B_OFF                (0x00U)
#define VDF_OMUS_FBWTH_B_ON                 (0x01U)

#define VDF_OMUS_METSRT_B_1RRSEAT           (0x00U)
#define VDF_OMUS_METSRT_B_1RRSEAT_CTRSEAT   (0x01U)
#define VDF_OMUS_METSRT_B_2RRSEAT           (0x02U)
#define VDF_OMUS_METSRT_B_NORSEAT           (0x03U)

#define VDF_OMUS_METCPD_B_NON               (0x00U)
#define VDF_OMUS_METCPD_B_RIGHT             (0x01U)
#define VDF_OMUS_METCPD_B_LEFT              (0x02U)

#define VDF_OMUS_OMBINF_B_BUTTON_NON        (0x00U)
#define VDF_OMUS_OMBINF_B_BUTTON_1          (0x01U)

#define VDF_OMUS_SPMKM_B_120                (0x01U)
#define VDF_OMUS_SPMKM_B_140                (0x02U)
#define VDF_OMUS_SPMKM_B_160                (0x03U)
#define VDF_OMUS_SPMKM_B_170                (0x04U)
#define VDF_OMUS_SPMKM_B_180                (0x05U)
#define VDF_OMUS_SPMKM_B_200                (0x06U)
#define VDF_OMUS_SPMKM_B_220                (0x07U)
#define VDF_OMUS_SPMKM_B_240                (0x08U)
#define VDF_OMUS_SPMKM_B_260                (0x09U)
#define VDF_OMUS_SPMKM_B_280                (0x0AU)
#define VDF_OMUS_SPMKM_B_360                (0x0BU)

#define VDF_OMUS_SPMMPH_B_120               (0x01U)
#define VDF_OMUS_SPMMPH_B_140               (0x02U)
#define VDF_OMUS_SPMMPH_B_160               (0x03U)
#define VDF_OMUS_SPMMPH_B_170               (0x04U)
#define VDF_OMUS_SPMMPH_B_180               (0x05U)
#define VDF_OMUS_SPMMPH_B_200               (0x06U)
#define VDF_OMUS_SPMMPH_B_220               (0x07U)
#define VDF_OMUS_SPMMPH_B_240               (0x08U)
#define VDF_OMUS_SPMMPH_B_260               (0x09U)
#define VDF_OMUS_SPMMPH_B_280               (0x0AU)
#define VDF_OMUS_SPMMPH_B_360               (0x0BU)

#define VDF_OMUS_SPMFSP_B_NORMAL            (0x00U)
#define VDF_OMUS_SPMFSP_B_FSPORT            (0x01U)

#define VDF_OMUS_DIMFTL_B_FMVSS             (0x00U)
#define VDF_OMUS_DIMFTL_B_OTHER             (0x01U)

#define VDF_OMUS_METCSR_B_FMVSS             (0x00U)
#define VDF_OMUS_METCSR_B_UNR               (0x01U)
#define VDF_OMUS_METCSR_B_CHN               (0x02U)

#define VDF_OMUS_METCTT_B_FMVSS             (0x00U)
#define VDF_OMUS_METCTT_B_UNR               (0x01U)
#define VDF_OMUS_BRAND_B_TOYOTA             (0x01U)
#define VDF_OMUS_BRAND_B_LEXUS              (0x02U)
#define VDF_OMUS_BRAND_B_GR                 (0x03U)
#define VDF_OMUS_BRAND_B_DAIHATSU           (0x04U)
#define VDF_OMUS_BRAND_B_SUZUKI             (0x05U)
#define VDF_OMUS_BRAND_B_MATSUDA            (0x06U)
#define VDF_OMUS_BRAND_B_SUBARU             (0x07U)

#define VDF_OMUS_METSPO_B_NON               (0x00U)
#define VDF_OMUS_METSPO_B_GRS               (0x01U)
#define VDF_OMUS_METSPO_B_GR                (0x02U)
#define VDF_OMUS_METSPO_B_GRMN              (0x03U)
#define VDF_OMUS_METSPO_B_FSPORT            (0x04U)
#define VDF_OMUS_METSPO_B_F                 (0x05U)

#define VDF_OMUS_BDSTL_B_OTHER              (0x00U)
#define VDF_OMUS_BDSTL_B_PICKUP_TRUCK       (0x01U)

#define VDF_OMUS_FC_SCL_B_NO_1              (0x01U)
#define VDF_OMUS_FC_SCL_B_NO_2              (0x02U)
#define VDF_OMUS_FC_SCL_B_NO_3              (0x03U)
#define VDF_OMUS_FC_SCL_B_NO_4              (0x04U)
#define VDF_OMUS_FC_SCL_B_NO_5              (0x05U)
#define VDF_OMUS_FC_SCL_B_NO_6              (0x06U)

#define VDF_OMUS_EC_SCL_B_NO_1              (0x01U)
#define VDF_OMUS_EC_SCL_B_NO_2              (0x02U)
#define VDF_OMUS_EC_SCL_B_NO_3              (0x03U)
#define VDF_OMUS_EC_SCL_B_NO_4              (0x04U)
#define VDF_OMUS_EC_SCL_B_NO_5              (0x05U)
#define VDF_OMUS_EC_SCL_B_NO_6              (0x06U)

#define VDF_OMUS_CSWPOS_B_R_LIT_L_WIP       (0x00U)
#define VDF_OMUS_CSWPOS_B_R_WIP_L_LIT       (0x01U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif /* VARDEF_DEST_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  vardef_dest.c                                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/
