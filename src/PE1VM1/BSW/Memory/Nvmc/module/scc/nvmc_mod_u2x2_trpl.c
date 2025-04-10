/* 1.2.2 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Nvmc : Module A                                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NVMC_MOD_U2X2_TRPL_C_MAJOR               (1U)
#define NVMC_MOD_U2X2_TRPL_C_MINOR               (2U)
#define NVMC_MOD_U2X2_TRPL_C_PATCH               (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include "trpl_rdndnt.h"

#include "nvmc_mgr_private.h"
#include "nvmc_mod_lib_private.h"

#include "nvmc_mod_u2x2_trpl_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((NVMC_MOD_U2X2_TRPL_C_MAJOR != NVMC_MOD_U2X2_TRPL_H_MAJOR) || \
     (NVMC_MOD_U2X2_TRPL_C_MINOR != NVMC_MOD_U2X2_TRPL_H_MINOR) || \
     (NVMC_MOD_U2X2_TRPL_C_PATCH != NVMC_MOD_U2X2_TRPL_H_PATCH))
#error "nvmc_mod_u2x2_trpl.c and nvmc_mod_u2x2_trpl_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NVMC_MOD_U2X2_TRPL_RDNNUM                (3U)
#define NVMC_MOD_U2X2_TRPL_LOST_BIT_VAL          (7U)
#define NVMC_MOD_U2X2_TRPL_DATA_SIZE             (2U)
#define NVMC_MOD_U2X2_TRPL_DATA_SHFT             (16U)
#define NVMC_MOD_U2X2_TRPL_LOW_MASK              (0x0000FFFFU)
#define NVMC_MOD_U2X2_TRPL_HIGH_MASK             (0xFFFF0000U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1 u1_sp_NVMC_MOD_U2X2_TRPL_NODATA_TBL[NVMC_MOD_U2X2_TRPL_LOST_BIT_VAL] = {
    (U1)0U,  /* 000b */
    (U1)2U,  /* 001b */
    (U1)0U,  /* 010b */
    (U1)4U,  /* 011b */
    (U1)0U,  /* 100b */
    (U1)2U,  /* 101b */
    (U1)0U   /* 110b */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U1 u1_d_NvmcMod_U4LoTrpl_RdnData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA   : Data configuration                                                                        */
/*                  --> *u4_ap_rdnrslt : Redundancy data                                                                             */
/*                  --> *u4_ap_DATA : Read Buffer                                                                                    */
/*                  --> *u1_ap_STATUS : Read Status                                                                                  */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
U1   u1_d_NvmcMod_U4LoTrpl_RdnData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS)
{
    U4  u4_tp_temp[NVMC_MOD_U2X2_TRPL_RDNNUM];
    U4  u4_t_mod_type;
    U1  u1_t_ret;
    U1  u1_t_sts_bit;
    U1  u1_t_index;
    U1  u1_t_cnt;
    U1  u1_t_rdn_rslt;

    u1_t_sts_bit = u1_d_NvmcMod_Lib_StatusCheck((U1)NVMC_MOD_U2X2_TRPL_RDNNUM, (U1)NVMC_MOD_U2X2_TRPL_DATA_SIZE, u1_ap_STATUS);
    u1_t_ret = (U1)NVMC_MOD_RSLT_NG;
    if(u1_t_sts_bit == (U1)0U){
        for(u1_t_cnt = (U1)0U; u1_t_cnt < (U1)NVMC_MOD_U2X2_TRPL_RDNNUM; u1_t_cnt++){
            u1_t_index = u1_t_cnt << 1U;
            u4_tp_temp[u1_t_cnt] = (u4_ap_DATA[u1_t_index] & (U4)NVMC_MOD_U2X2_TRPL_LOW_MASK);
            u1_t_index++;
            u4_tp_temp[u1_t_cnt] |= (u4_ap_DATA[u1_t_index] << NVMC_MOD_U2X2_TRPL_DATA_SHFT);
        }
        u1_t_ret = (U1)NVMC_MOD_RSLT_OK;
        u4_t_mod_type = st_ap_CFGDATA->u4_module_bit_cfg & (U4)NVMC_DATA_ATTR_RDNT_TYPE_MASK;
        if(u4_t_mod_type == (U4)NVMC_DATA_ATTR_RDNT_TYPE_BIT){
            *u4_ap_rdnrslt = u4_g_Majbit(&u4_tp_temp[0]);
        }
        else{
            *u4_ap_rdnrslt = (U4)0U;
            u1_t_rdn_rslt = u1_g_TrplRdndntchk(&u4_tp_temp[0], u4_ap_rdnrslt);
            if(u1_t_rdn_rslt == (U1)0U){
                u1_t_ret = (U1)NVMC_MOD_RSLT_RDN_NG;
                u4_ap_rdnrslt[0] = u4_d_NvmcMod_Lib_GetRdunErrorValue(st_ap_CFGDATA, &u4_tp_temp[0]);
            }
        }
    }
    else if(u1_t_sts_bit < (U1)NVMC_MOD_U2X2_TRPL_LOST_BIT_VAL){
        u1_t_index = u1_sp_NVMC_MOD_U2X2_TRPL_NODATA_TBL[u1_t_sts_bit];
        u4_ap_rdnrslt[0] = (u4_ap_DATA[u1_t_index] & (U4)NVMC_MOD_U2X2_TRPL_LOW_MASK);
        u1_t_index++;
        u4_ap_rdnrslt[0] |= (u4_ap_DATA[u1_t_index] << NVMC_MOD_U2X2_TRPL_DATA_SHFT);
        u1_t_ret = (U1)NVMC_MOD_RSLT_NODATA;
    }
    else if(u1_t_sts_bit == (U1)NVMC_MOD_U2X2_TRPL_LOST_BIT_VAL){
        u1_t_ret = (U1)NVMC_MOD_RSLT_LOST;
    }
    else{
        /* u1_t_ret = (U1)NVMC_MOD_RSLT_NG; */
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  void   vd_d_NvmcMod_U4LoTrpl_WrData(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u4_ap_writedata : Write Data                                                                                */
/*                  --> u1_a_RDNNUM      : RDN Nunm                                                                                  */
/*                  --> u1_a_BLOCKNUM    : Block Num                                                                                 */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void   vd_d_NvmcMod_U4LoTrpl_WrData(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)
{
    U4  u4_t_wdata;

    if((u1_a_BLOCKNUM & (U1)1U) == (U1)0U){
        u4_t_wdata = u4_ap_writedata[0];
    }
    else{
        u4_t_wdata = u4_ap_writedata[0] >> NVMC_MOD_U2X2_TRPL_DATA_SHFT;
    }
    u4_t_wdata &= (U4)NVMC_MOD_U2X2_TRPL_LOW_MASK;
    u4_ap_writedata[0] = u4_t_wdata;
}

/*===================================================================================================================================*/
/*  U1 u1_d_NvmcMod_U4HiTrpl_RdnData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA   : Data configuration                                                                        */
/*                  --> *u4_ap_rdnrslt : Redundancy data                                                                             */
/*                  --> *u4_ap_DATA : Read Buffer                                                                                    */
/*                  --> *u1_ap_STATUS : Read Status                                                                                  */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
U1   u1_d_NvmcMod_U4HiTrpl_RdnData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS)
{
    U4  u4_tp_temp[NVMC_MOD_U2X2_TRPL_RDNNUM];
    U4  u4_t_mod_type;
    U1  u1_t_ret;
    U1  u1_t_sts_bit;
    U1  u1_t_index;
    U1  u1_t_cnt;
    U1  u1_t_rdn_rslt;

    u1_t_sts_bit = u1_d_NvmcMod_Lib_StatusCheck((U1)NVMC_MOD_U2X2_TRPL_RDNNUM, (U1)NVMC_MOD_U2X2_TRPL_DATA_SIZE, u1_ap_STATUS);
    u1_t_ret = (U1)NVMC_MOD_RSLT_NG;
    if(u1_t_sts_bit == (U1)0U){
        for(u1_t_cnt = (U1)0U; u1_t_cnt < (U1)NVMC_MOD_U2X2_TRPL_RDNNUM; u1_t_cnt++){
            u1_t_index = u1_t_cnt << 1U;
            u4_tp_temp[u1_t_cnt] = u4_ap_DATA[u1_t_index] >> NVMC_MOD_U2X2_TRPL_DATA_SHFT;
            u1_t_index++;
            u4_tp_temp[u1_t_cnt] |= (u4_ap_DATA[u1_t_index] & (U4)NVMC_MOD_U2X2_TRPL_HIGH_MASK);
        }
        u1_t_ret = (U1)NVMC_MOD_RSLT_OK;
        u4_t_mod_type = st_ap_CFGDATA->u4_module_bit_cfg & (U4)NVMC_DATA_ATTR_RDNT_TYPE_MASK;
        if(u4_t_mod_type == (U4)NVMC_DATA_ATTR_RDNT_TYPE_BIT){
            *u4_ap_rdnrslt = u4_g_Majbit(&u4_tp_temp[0]);
        }
        else{
            *u4_ap_rdnrslt = (U4)0U;
            u1_t_rdn_rslt = u1_g_TrplRdndntchk(&u4_tp_temp[0], u4_ap_rdnrslt);
            if(u1_t_rdn_rslt == (U1)0U){
                u1_t_ret = (U1)NVMC_MOD_RSLT_RDN_NG;
                u4_ap_rdnrslt[0] = u4_d_NvmcMod_Lib_GetRdunErrorValue(st_ap_CFGDATA, &u4_tp_temp[0]);
            }
        }
    }
    else if(u1_t_sts_bit < (U1)NVMC_MOD_U2X2_TRPL_LOST_BIT_VAL){
        u1_t_index = u1_sp_NVMC_MOD_U2X2_TRPL_NODATA_TBL[u1_t_sts_bit];
        u4_ap_rdnrslt[0] = u4_ap_DATA[u1_t_index] >> NVMC_MOD_U2X2_TRPL_DATA_SHFT;
        u1_t_index++;
        u4_ap_rdnrslt[0] |= (u4_ap_DATA[u1_t_index] & (U4)NVMC_MOD_U2X2_TRPL_HIGH_MASK);
        u1_t_ret = (U1)NVMC_MOD_RSLT_NODATA;
    }
    else if(u1_t_sts_bit == (U1)NVMC_MOD_U2X2_TRPL_LOST_BIT_VAL){
        u1_t_ret = (U1)NVMC_MOD_RSLT_LOST;
    }
    else{
        /* u1_t_ret = (U1)NVMC_MOD_RSLT_NG; */
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  void   vd_d_NvmcMod_U4HiTrpl_WrData(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u4_ap_writedata : Write Data                                                                                */
/*                  --> u1_a_RDNNUM      : RDN Nunm                                                                                  */
/*                  --> u1_a_BLOCKNUM    : Block Num                                                                                 */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void   vd_d_NvmcMod_U4HiTrpl_WrData(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)
{
    U4  u4_t_wdata;

    if((u1_a_BLOCKNUM & (U1)1U) == (U1)0U){
        u4_t_wdata = u4_ap_writedata[0] << NVMC_MOD_U2X2_TRPL_DATA_SHFT;
    }
    else{
        u4_t_wdata = u4_ap_writedata[0];
    }
    u4_t_wdata &= (U4)NVMC_MOD_U2X2_TRPL_HIGH_MASK;
    u4_ap_writedata[0] = u4_t_wdata;
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version         Date        Author  Change Description                                                                           */
/* ---------------  ----------  ------  -------------------------------------------------------------------------------------------  */
/*  1.0.0            8/17/2015  KM      New.                                                                                         */
/*  1.1.0           10/07/2015  MH      Set first data when redundant NG.                                                            */
/*                                      Combined bit redundancy with triple redundancy.                                              */
/*                  10/14/2015  KM      Bug fix.                                                                                     */
/*  1.1.1           10/21/2015  MH      Fixed QAC issue.                                                                             */
/*  1.1.2            5/16/2016  HK      Fixed PCS3-2 issue.                                                                          */
/*  1.2.0            11/3/2016  HK      Changed with the small sector correspondence.                                                */
/*  1.2.1            8/22/2017  HK      Fixed AIP3GBSW-146 issue.                                                                    */
/*  1.2.2           11/ 8/2023  KN      Improvement : Warning MISRA-C-Rule7.2 was fixed.                                             */
/*                                                                                                                                   */
/*  * KM      = Kazuyuki Makino, Denso Create                                                                                        */
/*  * MH      = Masayuki Hattori, Denso                                                                                              */
/*  * HK      = Hayato Kanamori, Denso Create                                                                                        */
/*  * KN      = Keigo Nomura   , Denso Create                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
