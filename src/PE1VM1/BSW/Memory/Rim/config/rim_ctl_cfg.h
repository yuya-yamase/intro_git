/* 1.3.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  RIM : CTL                                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef RIM_CTL_CFG_H
#define RIM_CTL_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RIM_CTL_CFG_H_MAJOR                      (1U)
#define RIM_CTL_CFG_H_MINOR                      (3U)
#define RIM_CTL_CFG_H_PATCH                      (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* RimId */
/* START : ##TOOL_OUT#RIM_ID_MOD_3B_U1## */
#define RIMID_U1_VDF_HCS_ASCEXT                  (0x0000U)
#define RIMID_U1_VDF_DEST_BDB                    (0x0001U)
#define RIMID_U1_VDF_STRG_WHL                    (0x0002U)
#define RIMID_U1_VDF_DST_IDX                     (0x0003U)
#define RIMID_U1_VDF_DST_LAW_IDX                 (0x0004U)
#define RIMID_U1_VDF_MCUID0798                   (0x0005U)
#define RIMID_U1_VDF_MCUID0209                   (0x0006U)
#define RIMID_U1_VDF_MCUID0210                   (0x0007U)
#define RIMID_U1_VDF_MCUID0211                   (0x0008U)
#define RIMID_U1_VDF_MCUID0212                   (0x0009U)
#define RIMID_U1_VDF_MCUID0213                   (0x000AU)
#define RIMID_U1_VDF_MCUID0214                   (0x000BU)
#define RIMID_U1_VDF_MCUID0215                   (0x000CU)
#define RIMID_U1_VDF_MCUID0233                   (0x000DU)
#define RIMID_U1_VDF_MCUID0224                   (0x000EU)
#define RIMID_U1_VDF_MCUID0225                   (0x000FU)
#define RIMID_U1_VDF_MCUID0226                   (0x0010U)
#define RIMID_U1_VDF_MCUID0227                   (0x0011U)
#define RIMID_U1_VDF_MCUID0228                   (0x0012U)
#define RIMID_U1_VDF_MCUID0229                   (0x0013U)
#define RIMID_U1_VDF_MCUID0230                   (0x0014U)
#define RIMID_U1_VDF_MCUID0231                   (0x0015U)
#define RIMID_U1_VDF_MCUID0232                   (0x0016U)
#define RIMID_U1_VDF_MCUID0234                   (0x0017U)
#define RIMID_U1_VDF_MCUID1138                   (0x0018U)
#define RIMID_U1_VDF_MCUID0590                   (0x0019U)
#define RIMID_U1_VDF_MCUID0268                   (0x001AU)
#define RIMID_U1_VDF_MCUID0264                   (0x001BU)
#define RIMID_U1_VDF_MCUID0341                   (0x001CU)
#define RIMID_U1_VDF_MCUID1135                   (0x001DU)
#define RIMID_U1_VDF_MCUID1136                   (0x001EU)
#define RIMID_U1_VDF_MCUID0604                   (0x001FU)
#define RIMID_U1_VDF_MCUID0605                   (0x0020U)
#define RIMID_U1_VDF_MCUID0606                   (0x0021U)
#define RIMID_U1_VDF_MCUID0607                   (0x0022U)
#define RIMID_U1_VDF_MCUID0809                   (0x0023U)
#define RIMID_U1_VDF_MCUID0810                   (0x0024U)
#define RIMID_U1_VDF_MCUID3020                   (0x0025U)
#define RIMID_U1_VDF_MCUID0024                   (0x0026U)
#define RIMID_U1_VDF_MCUID0025                   (0x0027U)
#define RIMID_U1_VDF_MCUID0235                   (0x0028U)
#define RIMID_U1_VDF_MCUID0250                   (0x0029U)
#define RIMID_U1_VDF_MCUID0251                   (0x002AU)
#define RIMID_U1_VDF_MCUID0252                   (0x002BU)
#define RIMID_U1_VDF_MCUID0253                   (0x002CU)
#define RIMID_U1_VDF_MCUID0254                   (0x002DU)
#define RIMID_U1_VDF_MCUID0255                   (0x002EU)
#define RIMID_U1_VDF_MCUID3025                   (0x002FU)
#define RIMID_U1_DREC_TX                         (0x0030U)
#define RIMID_U1_NVMC_DA_DTF_WRI_011             (0x0031U)
#define RIMID_U1_NVMC_ST_DTF_000                 (0x0032U)
#define RIMID_U1_NVMC_ST_DTF_001                 (0x0033U)
#define RIMID_U1_NVMC_ST_DTF_002                 (0x0034U)
#define RIMID_U1_NVMC_ST_DTF_003                 (0x0035U)
#define RIMID_U1_NVMC_ST_DTF_004                 (0x0036U)
#define RIMID_U1_NVMC_ST_DTF_005                 (0x0037U)
#define RIMID_U1_NVMC_ST_DTF_006                 (0x0038U)
#define RIMID_U1_NVMC_ST_DTF_007                 (0x0039U)
#define RIMID_U1_NVMC_ST_DTF_008                 (0x003AU)
#define RIMID_U1_NVMC_ST_DTF_009                 (0x003BU)
#define RIMID_U1_NVMC_ST_DTF_010                 (0x003CU)
#define RIMID_U1_NVMC_ST_DTF_011                 (0x003DU)
#define RIMID_U1_NVMC_ST_DTF_020                 (0x003EU)
#define RIMID_U1_NVMC_ST_DTF_021                 (0x003FU)
#define RIMID_U1_NVMC_ST_DTF_022                 (0x0040U)
#define RIMID_U1_NVMC_ST_DTF_023                 (0x0041U)
#define RIMID_U1_NVMC_ST_DTF_024                 (0x0042U)
#define RIMID_U1_NVMC_ST_DTF_025                 (0x0043U)
#define RIMID_U1_NVMC_ST_DTF_026                 (0x0044U)
#define RIMID_U1_NVMC_ST_DTF_027                 (0x0045U)
#define RIMID_U1_NVMC_ST_DTF_028                 (0x0046U)
#define RIMID_U1_NVMC_ST_DTF_029                 (0x0047U)
#define RIMID_U1_NVMC_ST_DTF_030                 (0x0048U)
#define RIMID_U1_NVMC_ST_DTF_031                 (0x0049U)
#define RIMID_U1_NVMC_ST_DTF_032                 (0x004AU)
#define RIMID_U1_NVMC_ST_DTF_033                 (0x004BU)
#define RIMID_U1_NVMC_ST_DTF_034                 (0x004CU)
#define RIMID_U1_NVMC_ST_DTF_035                 (0x004DU)
#define RIMID_U1_NVMC_ST_DTF_036                 (0x004EU)
#define RIMID_U1_NVMC_ST_DTF_037                 (0x004FU)
#define RIMID_U1_NVMC_ST_DTF_038                 (0x0050U)
#define RIMID_U1_NVMC_ST_DTF_039                 (0x0051U)
#define RIMID_U1_NVMC_ST_DTF_040                 (0x0052U)
#define RIMID_U1_NVMC_ST_DTF_041                 (0x0053U)
#define RIMID_U1_NVMC_ST_DTF_042                 (0x0054U)
#define RIMID_U1_NVMC_ST_DTF_043                 (0x0055U)
#define RIMID_U1_NVMC_ST_DTF_044                 (0x0056U)
#define RIMID_U1_NVMC_ST_DTF_045                 (0x0057U)
#define RIMID_U1_NVMC_ST_DTF_046                 (0x0058U)
#define RIMID_U1_NVMC_ST_DTF_047                 (0x0059U)
#define RIMID_U1_NVMC_ST_DTF_048                 (0x005AU)
/* END : ##TOOL_OUT#RIM_ID_MOD_3B_U1## */
/* START : ##TOOL_OUT#RIM_ID_MOD_3B_U2## */
#define RIMID_U2_VDF_C_CODE                      (0x4000U)
#define RIMID_U2_VDF_MCUID0262                   (0x4001U)
#define RIMID_U2_VDF_MCUID0263                   (0x4002U)
#define RIMID_U2_NVMC_DA_DTF_WRI_009             (0x4003U)
#define RIMID_U2_NVMC_DA_DTF_WRI_010             (0x4004U)
#define RIMID_U2_NVMC_DA_DTF_WRI_020             (0x4005U)
#define RIMID_U2_NVMC_DA_DTF_WRI_021             (0x4006U)
#define RIMID_U2_NVMC_DA_DTF_WRI_022             (0x4007U)
#define RIMID_U2_NVMC_DA_DTF_WRI_023             (0x4008U)
#define RIMID_U2_NVMC_DA_DTF_WRI_024             (0x4009U)
#define RIMID_U2_NVMC_DA_DTF_WRI_025             (0x400AU)
#define RIMID_U2_NVMC_DA_DTF_WRI_026             (0x400BU)
#define RIMID_U2_NVMC_DA_DTF_WRI_027             (0x400CU)
#define RIMID_U2_NVMC_DA_DTF_WRI_028             (0x400DU)
#define RIMID_U2_NVMC_DA_DTF_WRI_029             (0x400EU)
#define RIMID_U2_NVMC_DA_DTF_WRI_030             (0x400FU)
#define RIMID_U2_NVMC_DA_DTF_WRI_031             (0x4010U)
#define RIMID_U2_NVMC_DA_DTF_WRI_032             (0x4011U)
#define RIMID_U2_NVMC_DA_DTF_WRI_033             (0x4012U)
#define RIMID_U2_NVMC_DA_DTF_WRI_034             (0x4013U)
/* END : ##TOOL_OUT#RIM_ID_MOD_3B_U2## */
/* START : ##TOOL_OUT#RIM_ID_MOD_3B_U4## */
#define RIMID_U4_VDF_ESO_W0                      (0x8000U)
#define RIMID_U4_VDF_ESO_W1                      (0x8001U)
#define RIMID_U4_VDF_ESO_W2                      (0x8002U)
#define RIMID_U4_VDF_ESO_W3                      (0x8003U)
#define RIMID_U4_VDF_ESO_W4                      (0x8004U)
#define RIMID_U4_VDF_ESO_W5                      (0x8005U)
#define RIMID_U4_VDF_ESO_W6                      (0x8006U)
#define RIMID_U4_VDF_ESO_W7                      (0x8007U)
#define RIMID_U4_VDF_ESO_W8                      (0x8008U)
#define RIMID_U4_OMAVRCHK_RESULT_01              (0x8009U)
#define RIMID_U4_OMAVRCHK_RESULT_02              (0x800AU)
#define RIMID_U4_TRIPCOM_AVGEE_TA_EE             (0x800BU)
#define RIMID_U4_TRIPCOM_AVGEE_DC_EE             (0x800CU)
#define RIMID_U4_TRIPCOM_EVDTE_OC                (0x800DU)
#define RIMID_U4_TRIPCOM_EVDTE_PCT               (0x800EU)
#define RIMID_U4_TRIPCOM_AVGVEHSPD_TA_SP         (0x800FU)
#define RIMID_U4_TRIPCOM_AVGVEHSPD_DC_SP         (0x8010U)
#define RIMID_U4_TRIPCOM_PTSRUNTM_DC_ET          (0x8011U)
#define RIMID_U4_TRIPCOM_PTSRUNDIST_DC_OC        (0x8012U)
#define RIMID_U4_TRIPCOM_AVGSPD_TR_A_SP          (0x8013U)
#define RIMID_U4_TRIPCOM_AVGSPD_TR_B_SP          (0x8014U)
#define RIMID_U4_TRIPCOM_1MEE_EE00               (0x8015U)
#define RIMID_U4_TRIPCOM_1MEE_EE01               (0x8016U)
#define RIMID_U4_TRIPCOM_1MEE_EE02               (0x8017U)
#define RIMID_U4_TRIPCOM_1MEE_EE03               (0x8018U)
#define RIMID_U4_TRIPCOM_1MEE_EE04               (0x8019U)
#define RIMID_U4_TRIPCOM_1MEE_EE05               (0x801AU)
#define RIMID_U4_TRIPCOM_1MEE_EE06               (0x801BU)
#define RIMID_U4_TRIPCOM_1MEE_EE07               (0x801CU)
#define RIMID_U4_TRIPCOM_1MEE_EE08               (0x801DU)
#define RIMID_U4_TRIPCOM_1MEE_EE09               (0x801EU)
#define RIMID_U4_TRIPCOM_1MEE_EE10               (0x801FU)
#define RIMID_U4_TRIPCOM_1MEE_EE11               (0x8020U)
#define RIMID_U4_TRIPCOM_1MEE_EE12               (0x8021U)
#define RIMID_U4_TRIPCOM_1MEE_EE13               (0x8022U)
#define RIMID_U4_TRIPCOM_1MEE_EE14               (0x8023U)
#define RIMID_U4_TRIPCOM_1MEE_EE15               (0x8024U)
#define RIMID_U4_TRIPCOM_1MEE_EE16               (0x8025U)
#define RIMID_U4_TRIPCOM_1MEE_EE17               (0x8026U)
#define RIMID_U4_TRIPCOM_1MEE_EE18               (0x8027U)
#define RIMID_U4_TRIPCOM_1MEE_EE19               (0x8028U)
#define RIMID_U4_TRIPCOM_1MEE_EE20               (0x8029U)
#define RIMID_U4_TRIPCOM_1MEE_EE21               (0x802AU)
#define RIMID_U4_TRIPCOM_1MEE_EE22               (0x802BU)
#define RIMID_U4_TRIPCOM_1MEE_EE23               (0x802CU)
#define RIMID_U4_TRIPCOM_1MEE_EE24               (0x802DU)
#define RIMID_U4_TRIPCOM_1MEE_EE25               (0x802EU)
#define RIMID_U4_TRIPCOM_1MEE_EE26               (0x802FU)
#define RIMID_U4_TRIPCOM_1MEE_EE27               (0x8030U)
#define RIMID_U4_TRIPCOM_1MEE_EE28               (0x8031U)
#define RIMID_U4_TRIPCOM_1MEE_EE29               (0x8032U)
#define RIMID_U4_TRIPCOM_1MEE_LTST               (0x8033U)
#define RIMID_U4_NVMC_DA_DTF_WRI_000             (0x8034U)
#define RIMID_U4_NVMC_DA_DTF_WRI_001             (0x8035U)
#define RIMID_U4_NVMC_DA_DTF_WRI_002             (0x8036U)
#define RIMID_U4_NVMC_DA_DTF_WRI_003             (0x8037U)
#define RIMID_U4_NVMC_DA_DTF_WRI_004             (0x8038U)
#define RIMID_U4_NVMC_DA_DTF_WRI_005             (0x8039U)
#define RIMID_U4_NVMC_DA_DTF_WRI_006             (0x803AU)
#define RIMID_U4_NVMC_DA_DTF_WRI_007             (0x803BU)
#define RIMID_U4_NVMC_DA_DTF_WRI_008             (0x803CU)
#define RIMID_U4_NVMC_DA_DTF_WRI_035             (0x803DU)
#define RIMID_U4_NVMC_DA_DTF_WRI_036             (0x803EU)
#define RIMID_U4_NVMC_DA_DTF_WRI_037             (0x803FU)
#define RIMID_U4_NVMC_DA_DTF_WRI_038             (0x8040U)
#define RIMID_U4_NVMC_DA_DTF_WRI_039             (0x8041U)
#define RIMID_U4_NVMC_DA_DTF_WRI_040             (0x8042U)
#define RIMID_U4_NVMC_DA_DTF_WRI_041             (0x8043U)
#define RIMID_U4_NVMC_DA_DTF_WRI_042             (0x8044U)
#define RIMID_U4_NVMC_DA_DTF_WRI_043             (0x8045U)
#define RIMID_U4_NVMC_DA_DTF_WRI_044             (0x8046U)
#define RIMID_U4_NVMC_DA_DTF_WRI_045             (0x8047U)
#define RIMID_U4_NVMC_DA_DTF_WRI_046             (0x8048U)
#define RIMID_U4_NVMC_DA_DTF_WRI_047             (0x8049U)
#define RIMID_U4_NVMC_DA_DTF_WRI_048             (0x804AU)
/* END : ##TOOL_OUT#RIM_ID_MOD_3B_U4## */
/* START : ##TOOL_OUT#RIM_ID_MOD_3B_OTR## */
/* END : ##TOOL_OUT#RIM_ID_MOD_3B_OTR## */

/* START : ##TOOL_OUT#RIM_ID_MOD_1B2C_U1## */
/* END : ##TOOL_OUT#RIM_ID_MOD_1B2C_U1## */
/* START : ##TOOL_OUT#RIM_ID_MOD_1B2C_U2## */
/* END : ##TOOL_OUT#RIM_ID_MOD_1B2C_U2## */
/* START : ##TOOL_OUT#RIM_ID_MOD_1B2C_U4## */
/* END : ##TOOL_OUT#RIM_ID_MOD_1B2C_U4## */

/* START : ##TOOL_OUT#RIM_ID_MOD_1B_U1## */
#define RIMID_U1_MCST_USRNUM_D                   (0x0400U)
#define RIMID_U1_ILLUMI_LOUNGE                   (0x0401U)
#define RIMID_U1_NVMC_ST_DTF_012                 (0x0402U)
#define RIMID_U1_NVMC_ST_DTF_013                 (0x0403U)
#define RIMID_U1_NVMC_ST_DTF_014                 (0x0404U)
#define RIMID_U1_NVMC_ST_DTF_015                 (0x0405U)
#define RIMID_U1_NVMC_ST_DTF_016                 (0x0406U)
#define RIMID_U1_NVMC_ST_DTF_017                 (0x0407U)
#define RIMID_U1_NVMC_ST_DTF_018                 (0x0408U)
#define RIMID_U1_NVMC_ST_DTF_019                 (0x0409U)
#define RIMID_U1_NVMC_ST_DTF_049                 (0x040AU)
#define RIMID_U1_NVMC_ST_DTF_050                 (0x040BU)
/* END : ##TOOL_OUT#RIM_ID_MOD_1B_U1## */
/* START : ##TOOL_OUT#RIM_ID_MOD_1B_U2## */
/* END : ##TOOL_OUT#RIM_ID_MOD_1B_U2## */
/* START : ##TOOL_OUT#RIM_ID_MOD_1B_U4## */
#define RIMID_U4_NVMC_ERROR_LOG                  (0x8400U)
/* END : ##TOOL_OUT#RIM_ID_MOD_1B_U4## */
/* START : ##TOOL_OUT#RIM_ID_MOD_1B_OTR## */
#define RIMID_OTR_NVMC_DA_DTF_WRI_012            (0xC400U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_013            (0xC401U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_014            (0xC402U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_015            (0xC403U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_016            (0xC404U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_017            (0xC405U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_018            (0xC406U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_019            (0xC407U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_049            (0xC408U)
#define RIMID_OTR_NVMC_DA_DTF_WRI_050            (0xC409U)
/* END : ##TOOL_OUT#RIM_ID_MOD_1B_OTR## */

/* START : ##TOOL_OUT#RIM_ID_MOD_3C_U1## */
#define RIMID_U1_NVMC_NEXT_W_RDNNO_DTF           (0x0600U)
/* END : ##TOOL_OUT#RIM_ID_MOD_3C_U1## */
/* START : ##TOOL_OUT#RIM_ID_MOD_3C_U2## */
#define RIMID_U2_NVMC_INITID_DTF                 (0x4600U)
#define RIMID_U2_NVMC_RECOVERY_DTF               (0x4601U)
/* END : ##TOOL_OUT#RIM_ID_MOD_3C_U2## */
/* START : ##TOOL_OUT#RIM_ID_MOD_3C_U4## */
#define RIMID_U4_NVMC_REQ_DTF0                   (0x8600U)
#define RIMID_U4_NVMC_REQ_DTF1                   (0x8601U)
/* END : ##TOOL_OUT#RIM_ID_MOD_3C_U4## */
/* START : ##TOOL_OUT#RIM_ID_MOD_3C_OTR## */
/* END : ##TOOL_OUT#RIM_ID_MOD_3C_OTR## */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Externs                                                                                                        */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif /* RIM_CTL_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see rim_ctl.c                                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/
