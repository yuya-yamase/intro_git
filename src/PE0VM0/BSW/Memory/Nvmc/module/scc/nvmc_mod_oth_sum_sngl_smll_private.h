/* 1.1.2 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Nvmc : Module Other SUM SNGL SMLL                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef NVMC_MOD_OTH_SUM_SNGL_SMLL_H
#define NVMC_MOD_OTH_SUM_SNGL_SMLL_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NVMC_MOD_OTH_SUM_SNGL_SMLL_H_MAJOR       (1U)
#define NVMC_MOD_OTH_SUM_SNGL_SMLL_H_MINOR       (1U)
#define NVMC_MOD_OTH_SUM_SNGL_SMLL_H_PATCH       (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Externs                                                                                                        */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1     u1_d_NvmcMod_ovr4bBlk8bSumSglSmll_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS);
U1     u1_d_NvmcMod_ovr4bBlk12bSumSglSmll_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS);
U1     u1_d_NvmcMod_ovr4bBlk16bSumSglSmll_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS);
U1     u1_d_NvmcMod_ovr4bBlk20bSumSglSmll_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS);
U1     u1_d_NvmcMod_ovr4bBlk24bSumSglSmll_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS);
U1     u1_d_NvmcMod_ovr4bBlk28bSumSglSmll_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS);
void   vd_d_NvmcMod_ovr4bBlk8bSumSglSmll_WrD(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM);
void   vd_d_NvmcMod_ovr4bBlk12bSumSglSmll_WrD(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM);
void   vd_d_NvmcMod_ovr4bBlk16bSumSglSmll_WrD(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM);
void   vd_d_NvmcMod_ovr4bBlk20bSumSglSmll_WrD(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM);
void   vd_d_NvmcMod_ovr4bBlk24bSumSglSmll_WrD(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM);
void   vd_d_NvmcMod_ovr4bBlk28bSumSglSmll_WrD(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif /* NVMC_MOD_OTH_SUM_SNGL_SMLL_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see nvmc_mod_oth_sum_sngl_smll.c                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/
