/* 1.1.2 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Nvmc : Module PACK E3E4                                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NVMC_MOD_PACK_E3E4_C_MAJOR               (1U)
#define NVMC_MOD_PACK_E3E4_C_MINOR               (1U)
#define NVMC_MOD_PACK_E3E4_C_PATCH               (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include "trpl_rdndnt.h"

#include "nvmc_mgr_private.h"
#include "nvmc_mod_lib_private.h"

#include "nvmc_mod_pack_e3e4_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((NVMC_MOD_PACK_E3E4_C_MAJOR != NVMC_MOD_PACK_E3E4_H_MAJOR) || \
     (NVMC_MOD_PACK_E3E4_C_MINOR != NVMC_MOD_PACK_E3E4_H_MINOR) || \
     (NVMC_MOD_PACK_E3E4_C_PATCH != NVMC_MOD_PACK_E3E4_H_PATCH))
#error "nvmc_mod_pack_e3e4.c and nvmc_mod_pack_e3e4_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U1  u1_block;
    U1  u1_shift;
}ST_NVMC_MOD_PACK_E3E4_POS;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NVMC_MOD_PACK_E3E4_RDNNUM                (2U)
#define NVMC_MOD_PACK_E3E4_LOST_BIT_VAL          (3U)
#define NVMC_MOD_PACK_E3E4_DATA_SIZE             (1U)

#define NVMC_MOD_PACK_E3E4_MASK                  (0x000000FFU)
#define NVMC_MOD_PACK_E3E4_SHIFT                 (8U)

#define NVMC_MOD_PACK_E3E4_POS_NUM               (3U)

#define NVMC_MOD_PACK_E3E4__POS_TBL_NUM          (2U)
#define NVMC_MOD_PACK_E3_POS_TBLNO               (0U)
#define NVMC_MOD_PACK_E4_POS_TBLNO               (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1   u1_s_NvmcMod_U1E3E4_RdnData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS, const U1 u1_a_POS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U1      u1_d_NvmcMod_U1E3_RdnData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA : Data configuration                                                                          */
/*                  --> *u4_ap_rdnrslt : RDN Data                                                                                    */
/*                  --> *u4_ap_DATA    : Read Buffer                                                                                 */
/*                  --> *u1_ap_STATUS  : Status                                                                                      */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
U1   u1_d_NvmcMod_U1E3_RdnData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS)
{
    U1  u1_t_ret;

    u1_t_ret = u1_s_NvmcMod_U1E3E4_RdnData(st_ap_CFGDATA, u4_ap_rdnrslt, u4_ap_DATA, u1_ap_STATUS, (U1)NVMC_MOD_PACK_E3_POS_TBLNO);
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_d_NvmcMod_U1E4_RdnData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA : Data configuration                                                                          */
/*                  --> *u4_ap_rdnrslt : RDN Data                                                                                    */
/*                  --> *u4_ap_DATA    : Read Buffer                                                                                 */
/*                  --> *u1_ap_STATUS  : Status                                                                                      */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
U1   u1_d_NvmcMod_U1E4_RdnData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS)
{
    U1  u1_t_ret;

    u1_t_ret = u1_s_NvmcMod_U1E3E4_RdnData(st_ap_CFGDATA, u4_ap_rdnrslt, u4_ap_DATA, u1_ap_STATUS, (U1)NVMC_MOD_PACK_E4_POS_TBLNO);
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  void   vd_d_NvmcMod_U1E3_WrData(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u4_ap_writedata : Write Data                                                                                */
/*                  --> u1_a_RDNNUM      : RDN Nunm                                                                                  */
/*                  --> u1_a_BLOCKNUM    : Block Num                                                                                 */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void   vd_d_NvmcMod_U1E3_WrData(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)
{
    U4  u4_t_wdata;

    u4_t_wdata = u4_ap_writedata[0] & (U4)NVMC_MOD_PACK_E3E4_MASK;
    if(u1_a_RDNNUM == (U1)0U){
        u4_t_wdata |= (u4_t_wdata << NVMC_MOD_PACK_E3E4_SHIFT);
    }
    u4_ap_writedata[0] = u4_t_wdata;
}

/*===================================================================================================================================*/
/*  void   vd_d_NvmcMod_U1E4_WrData(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u4_ap_writedata : Write Data                                                                                */
/*                  --> u1_a_RDNNUM      : RDN Nunm                                                                                  */
/*                  --> u1_a_BLOCKNUM    : Block Num                                                                                 */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void   vd_d_NvmcMod_U1E4_WrData(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)
{
    U4  u4_t_wdata;

    u4_t_wdata = (u4_ap_writedata[0] & (U4)NVMC_MOD_PACK_E3E4_MASK) << NVMC_MOD_PACK_E3E4_SHIFT;
    if(u1_a_RDNNUM != (U1)0U){
        u4_t_wdata |= (u4_ap_writedata[0] & (U4)NVMC_MOD_PACK_E3E4_MASK);
    }
    u4_ap_writedata[0] = u4_t_wdata;
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
/*  static U1   u1_s_NvmcMod_U1E3E4_RdnData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS, const U1 u1_a_POS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA : Data configuration                                                                          */
/*                  --> *u4_ap_rdnrslt : RDN Data                                                                                    */
/*                  --> *u4_ap_DATA    : Read Buffer                                                                                 */
/*                  --> *u1_ap_STATUS  : Status                                                                                      */
/*                  --> u1_a_POS       : position                                                                                    */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_NvmcMod_U1E3E4_RdnData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS, const U1 u1_a_POS)
{
    U4  u4_t_work[NVMC_MOD_PACK_E3E4_POS_NUM];
    U4  u4_t_mod_type;
    U1  u1_t_ret;
    U1  u1_t_sts_bit;
    U1  u1_t_rdn_rslt;
    U1  u1_t_index;
    U1  u1_t_block;
    U1  u1_t_shift;
    U1  u1_t_cnt;
    static const U1 u1_sp_NVMC_MOD_1BIT_TRPL_NODATA_TBL[NVMC_MOD_PACK_E3E4_LOST_BIT_VAL] = {
        (U1)0U,  /* 00b */
        (U1)1U,  /* 01b */
        (U1)0U   /* 10b */
    };

    static const ST_NVMC_MOD_PACK_E3E4_POS  st_sp_NVMC_MOD_PACK_E3E4POS_TBL[NVMC_MOD_PACK_E3E4__POS_TBL_NUM][NVMC_MOD_PACK_E3E4_POS_NUM] = {
        /* Pack E3 */
        {
            {(U1)0U, (U1)8U   },
            {(U1)0U, (U1)0U   },
            {(U1)1U, (U1)0U   }
        },
        /* Pack E4 */
        {
            {(U1)0U, (U1)8U   },
            {(U1)1U, (U1)8U   },
            {(U1)1U, (U1)0U   }
        }
    };

    static const ST_NVMC_MOD_PACK_E3E4_POS  st_sp_NVMC_MOD_PACK_E3E4NOD_TBL[NVMC_MOD_PACK_E3E4__POS_TBL_NUM][NVMC_MOD_PACK_E3E4_RDNNUM] = {
        /* Pack E3 */
        {
            {(U1)0U, (U1)0U   },
            {(U1)1U, (U1)0U   }
        },
        /* Pack E4 */
        {
            {(U1)0U, (U1)8U   },
            {(U1)1U, (U1)0U   }
        }
    };

    u1_t_sts_bit = u1_d_NvmcMod_Lib_StatusCheck((U1)NVMC_MOD_PACK_E3E4_RDNNUM, (U1)NVMC_MOD_PACK_E3E4_DATA_SIZE, u1_ap_STATUS);
    u1_t_ret = (U1)NVMC_MOD_RSLT_NG;
    if(u1_t_sts_bit == (U1)0U){
        for(u1_t_cnt = (U1)0U; u1_t_cnt < (U1)NVMC_MOD_PACK_E3E4_POS_NUM; u1_t_cnt++){
            u1_t_block = st_sp_NVMC_MOD_PACK_E3E4POS_TBL[u1_a_POS][u1_t_cnt].u1_block;
            u1_t_shift = st_sp_NVMC_MOD_PACK_E3E4POS_TBL[u1_a_POS][u1_t_cnt].u1_shift;
            u4_t_work[u1_t_cnt] = (u4_ap_DATA[u1_t_block] >> u1_t_shift) & (U4)NVMC_MOD_PACK_E3E4_MASK;
        }

        u1_t_ret = (U1)NVMC_MOD_RSLT_OK;
        u4_t_mod_type = st_ap_CFGDATA->u4_module_bit_cfg & (U4)NVMC_DATA_ATTR_RDNT_TYPE_MASK;
        if(u4_t_mod_type == (U4)NVMC_DATA_ATTR_RDNT_TYPE_BIT){
            *u4_ap_rdnrslt = u4_g_Majbit(&u4_t_work[0]);
        }
        else{
            *u4_ap_rdnrslt = (U4)0U;
            u1_t_rdn_rslt = u1_g_TrplRdndntchk(&u4_t_work[0], u4_ap_rdnrslt);
            if(u1_t_rdn_rslt == (U1)0U){
                u1_t_ret = (U1)NVMC_MOD_RSLT_RDN_NG;
                u4_ap_rdnrslt[0] = u4_d_NvmcMod_Lib_GetRdunErrorValue(st_ap_CFGDATA, &u4_t_work[0]);
            }
        }
    }
    else if(u1_t_sts_bit < (U1)NVMC_MOD_PACK_E3E4_LOST_BIT_VAL){
        u1_t_index = u1_sp_NVMC_MOD_1BIT_TRPL_NODATA_TBL[u1_t_sts_bit];
        u1_t_block = st_sp_NVMC_MOD_PACK_E3E4NOD_TBL[u1_a_POS][u1_t_index].u1_block;
        u1_t_shift = st_sp_NVMC_MOD_PACK_E3E4NOD_TBL[u1_a_POS][u1_t_index].u1_shift;
        u4_ap_rdnrslt[0] = (u4_ap_DATA[u1_t_block] >> u1_t_shift) & (U4)NVMC_MOD_PACK_E3E4_MASK;
        u1_t_ret = (U1)NVMC_MOD_RSLT_NODATA;
    }
    else if(u1_t_sts_bit == (U1)NVMC_MOD_PACK_E3E4_LOST_BIT_VAL){
        u1_t_ret = (U1)NVMC_MOD_RSLT_LOST;
    }
    else{
        /* u1_t_ret = (U1)NVMC_MOD_RSLT_NG; */
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
/*  1.0.0           10/14/2015  KM      New.                                                                                         */
/*  1.0.1           10/21/2015  KM      Bug fix.                                                                                     */
/*  1.0.2            3/25/2016  KM      Fixed Unit Test issue.                                                                       */
/*  1.0.3            4/11/2016  HK      Fixed function comments.                                                                     */
/*  1.0.4            5/16/2016  HK      Fixed PCS3-2 issue.                                                                          */
/*  1.1.0            11/3/2016  HK      Changed with the small sector correspondence.                                                */
/*  1.1.1            8/22/2017  HK      Fixed AIP3GBSW-146 issue.                                                                    */
/*  1.1.2           11/ 8/2023  KN      Improvement : Warning MISRA-C-Rule7.2 was fixed.                                             */
/*                                                                                                                                   */
/*  * KM      = Kazuyuki Makino, Denso Create                                                                                        */
/*  * HK      = Hayato Kanamori, Denso Create                                                                                        */
/*  * KN      = Keigo Nomura   , Denso Create                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
