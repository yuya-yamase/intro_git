/* 1.1.2 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Nvmc : Module Other SUM SNGL SMLL                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NVMC_MOD_OTH_SUM_SNGL_SMLL_C_MAJOR       (1U)
#define NVMC_MOD_OTH_SUM_SNGL_SMLL_C_MINOR       (1U)
#define NVMC_MOD_OTH_SUM_SNGL_SMLL_C_PATCH       (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include "memcpy_u4.h"

#include "nvmc_mgr_private.h"
#include "nvmc_mod_lib_private.h"
#include "nvmc_mod_cfg_private.h"

#include "nvmc_mod_oth_sum_sngl_smll_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((NVMC_MOD_OTH_SUM_SNGL_SMLL_C_MAJOR != NVMC_MOD_OTH_SUM_SNGL_SMLL_H_MAJOR) || \
     (NVMC_MOD_OTH_SUM_SNGL_SMLL_C_MINOR != NVMC_MOD_OTH_SUM_SNGL_SMLL_H_MINOR) || \
     (NVMC_MOD_OTH_SUM_SNGL_SMLL_C_PATCH != NVMC_MOD_OTH_SUM_SNGL_SMLL_H_PATCH))
#error "nvmc_mod_oth_sum_sngl_smll.c and nvmc_mod_oth_sum_sngl_smll_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NVMC_MOD_OTH_SUM_SNGL_SMLL_RDNNUM        (1U)
#define NVMC_MOD_OTH_SUM_SNGL_SMLL_LOST_BIT      (1U)

#define NVMC_MOD_OTH_SUM_SNGL_SMLL_MIN_BUFSIZE   (2U)         /* ( 4byte + SUM(4byte))            */

#define NVMC_MOD_OTH_SUM_SNGL_SMLL_8B_BLOCKNUM   (3U)         /* ( 4byte * 2 + SUM(4byte))        */
#define NVMC_MOD_OTH_SUM_SNGL_SMLL_12B_BLOCKNUM  (4U)         /* ( 4byte * 3 + SUM(4byte))        */
#define NVMC_MOD_OTH_SUM_SNGL_SMLL_16B_BLOCKNUM  (5U)         /* ( 4byte * 4 + SUM(4byte))        */ 
#define NVMC_MOD_OTH_SUM_SNGL_SMLL_20B_BLOCKNUM  (6U)         /* ( 4byte * 5 + SUM(4byte))        */
#define NVMC_MOD_OTH_SUM_SNGL_SMLL_24B_BLOCKNUM  (7U)         /* ( 4byte * 6 + SUM(4byte))        */
#define NVMC_MOD_OTH_SUM_SNGL_SMLL_28B_BLOCKNUM  (8U)         /* ( 4byte * 7 + SUM(4byte))        */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1     u1_s_NvmcMod_OthSumSnglSmll_RdnData(const U1 u1_a_SIZE, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS);
static void   vd_s_NvmcMod_OthSumSnglSmll_WrData(U4 * const u4_ap_writedata, const U1 u1_a_BLOCKNUM, const U1 u1_a_SIZE);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U1 u1_d_NvmcMod_ovr4bBlk8bSumSglSmll_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA : Data configuration                                                                          */
/*                  --> *u4_ap_rdnrslt : Redundancy data                                                                             */
/*                  --> *u4_ap_DATA    : Read Buffer                                                                                 */
/*                  --> *u1_ap_STATUS  : Read Status                                                                                 */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
U1   u1_d_NvmcMod_ovr4bBlk8bSumSglSmll_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS)
{
    U1  u1_t_ret;

    u1_t_ret = u1_s_NvmcMod_OthSumSnglSmll_RdnData((U1)NVMC_MOD_OTH_SUM_SNGL_SMLL_8B_BLOCKNUM, u4_ap_rdnrslt, u4_ap_DATA, u1_ap_STATUS);
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1 u1_d_NvmcMod_ovr4bBlk12bSumSglSmll_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA : Data configuration                                                                          */
/*                  --> *u4_ap_rdnrslt : Redundancy data                                                                             */
/*                  --> *u4_ap_DATA    : Read Buffer                                                                                 */
/*                  --> *u1_ap_STATUS  : Read Status                                                                                 */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
U1   u1_d_NvmcMod_ovr4bBlk12bSumSglSmll_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS)
{
    U1  u1_t_ret;

    u1_t_ret = u1_s_NvmcMod_OthSumSnglSmll_RdnData((U1)NVMC_MOD_OTH_SUM_SNGL_SMLL_12B_BLOCKNUM, u4_ap_rdnrslt, u4_ap_DATA, u1_ap_STATUS);
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1 u1_d_NvmcMod_ovr4bBlk16bSumSglSmll_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA : Data configuration                                                                          */
/*                  --> *u4_ap_rdnrslt : Redundancy data                                                                             */
/*                  --> *u4_ap_DATA    : Read Buffer                                                                                 */
/*                  --> *u1_ap_STATUS  : Read Status                                                                                 */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
U1   u1_d_NvmcMod_ovr4bBlk16bSumSglSmll_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS)
{
    U1  u1_t_ret;

    u1_t_ret = u1_s_NvmcMod_OthSumSnglSmll_RdnData((U1)NVMC_MOD_OTH_SUM_SNGL_SMLL_16B_BLOCKNUM, u4_ap_rdnrslt, u4_ap_DATA, u1_ap_STATUS);
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1 u1_d_NvmcMod_ovr4bBlk20bSumSglSmll_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA : Data configuration                                                                          */
/*                  --> *u4_ap_rdnrslt : Redundancy data                                                                             */
/*                  --> *u4_ap_DATA    : Read Buffer                                                                                 */
/*                  --> *u1_ap_STATUS  : Read Status                                                                                 */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
U1   u1_d_NvmcMod_ovr4bBlk20bSumSglSmll_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS)
{
    U1  u1_t_ret;

    u1_t_ret = u1_s_NvmcMod_OthSumSnglSmll_RdnData((U1)NVMC_MOD_OTH_SUM_SNGL_SMLL_20B_BLOCKNUM, u4_ap_rdnrslt, u4_ap_DATA, u1_ap_STATUS);
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1 u1_d_NvmcMod_ovr4bBlk24bSumSglSmll_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA : Data configuration                                                                          */
/*                  --> *u4_ap_rdnrslt : Redundancy data                                                                             */
/*                  --> *u4_ap_DATA    : Read Buffer                                                                                 */
/*                  --> *u1_ap_STATUS  : Read Status                                                                                 */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
U1   u1_d_NvmcMod_ovr4bBlk24bSumSglSmll_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS)
{
    U1  u1_t_ret;

    u1_t_ret = u1_s_NvmcMod_OthSumSnglSmll_RdnData((U1)NVMC_MOD_OTH_SUM_SNGL_SMLL_24B_BLOCKNUM, u4_ap_rdnrslt, u4_ap_DATA, u1_ap_STATUS);
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1 u1_d_NvmcMod_ovr4bBlk28bSumSglSmll_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA : Data configuration                                                                          */
/*                  --> *u4_ap_rdnrslt : Redundancy data                                                                             */
/*                  --> *u4_ap_DATA    : Read Buffer                                                                                 */
/*                  --> *u1_ap_STATUS  : Read Status                                                                                 */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
U1   u1_d_NvmcMod_ovr4bBlk28bSumSglSmll_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS)
{
    U1  u1_t_ret;

    u1_t_ret = u1_s_NvmcMod_OthSumSnglSmll_RdnData((U1)NVMC_MOD_OTH_SUM_SNGL_SMLL_28B_BLOCKNUM, u4_ap_rdnrslt, u4_ap_DATA, u1_ap_STATUS);
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  void      vd_d_NvmcMod_ovr4bBlk8bSumSglSmll_WrD(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u4_ap_writedata : Write Data                                                                                */
/*                  --> u1_a_RDNNUM      : RDN Nunm                                                                                  */
/*                  --> u1_a_BLOCKNUM    : Block Num                                                                                 */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void   vd_d_NvmcMod_ovr4bBlk8bSumSglSmll_WrD(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)
{
    vd_s_NvmcMod_OthSumSnglSmll_WrData(u4_ap_writedata, u1_a_BLOCKNUM, (U1)NVMC_MOD_OTH_SUM_SNGL_SMLL_8B_BLOCKNUM);
}

/*===================================================================================================================================*/
/*  void   vd_d_NvmcMod_ovr4bBlk12bSumSglSmll_WrD(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u4_ap_writedata : Write Data                                                                                */
/*                  --> u1_a_RDNNUM      : RDN Nunm                                                                                  */
/*                  --> u1_a_BLOCKNUM    : Block Num                                                                                 */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void   vd_d_NvmcMod_ovr4bBlk12bSumSglSmll_WrD(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)
{
    vd_s_NvmcMod_OthSumSnglSmll_WrData(u4_ap_writedata, u1_a_BLOCKNUM, (U1)NVMC_MOD_OTH_SUM_SNGL_SMLL_12B_BLOCKNUM);
}

/*===================================================================================================================================*/
/*  void   vd_d_NvmcMod_ovr4bBlk16bSumSglSmll_WrD(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u4_ap_writedata : Write Data                                                                                */
/*                  --> u1_a_RDNNUM      : RDN Nunm                                                                                  */
/*                  --> u1_a_BLOCKNUM    : Block Num                                                                                 */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void   vd_d_NvmcMod_ovr4bBlk16bSumSglSmll_WrD(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)
{
    vd_s_NvmcMod_OthSumSnglSmll_WrData(u4_ap_writedata, u1_a_BLOCKNUM, (U1)NVMC_MOD_OTH_SUM_SNGL_SMLL_16B_BLOCKNUM);
}

/*===================================================================================================================================*/
/*  void   vd_d_NvmcMod_ovr4bBlk20bSumSglSmll_WrD(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u4_ap_writedata : Write Data                                                                                */
/*                  --> u1_a_RDNNUM      : RDN Nunm                                                                                  */
/*                  --> u1_a_BLOCKNUM    : Block Num                                                                                 */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void   vd_d_NvmcMod_ovr4bBlk20bSumSglSmll_WrD(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)
{
    vd_s_NvmcMod_OthSumSnglSmll_WrData(u4_ap_writedata, u1_a_BLOCKNUM, (U1)NVMC_MOD_OTH_SUM_SNGL_SMLL_20B_BLOCKNUM);
}

/*===================================================================================================================================*/
/*  void   vd_d_NvmcMod_ovr4bBlk24bSumSglSmll_WrD(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u4_ap_writedata : Write Data                                                                                */
/*                  --> u1_a_RDNNUM      : RDN Nunm                                                                                  */
/*                  --> u1_a_BLOCKNUM    : Block Num                                                                                 */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void   vd_d_NvmcMod_ovr4bBlk24bSumSglSmll_WrD(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)
{
    vd_s_NvmcMod_OthSumSnglSmll_WrData(u4_ap_writedata, u1_a_BLOCKNUM, (U1)NVMC_MOD_OTH_SUM_SNGL_SMLL_24B_BLOCKNUM);
}

/*===================================================================================================================================*/
/*  void   vd_d_NvmcMod_ovr4bBlk28bSumSglSmll_WrD(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u4_ap_writedata : Write Data                                                                                */
/*                  --> u1_a_RDNNUM      : RDN Nunm                                                                                  */
/*                  --> u1_a_BLOCKNUM    : Block Num                                                                                 */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void   vd_d_NvmcMod_ovr4bBlk28bSumSglSmll_WrD(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)
{
    vd_s_NvmcMod_OthSumSnglSmll_WrData(u4_ap_writedata, u1_a_BLOCKNUM, (U1)NVMC_MOD_OTH_SUM_SNGL_SMLL_28B_BLOCKNUM);
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
/*  static U1   u1_s_NvmcMod_OthSumSnglSmll_RdnData(const U1 u1_a_SIZE, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u1_a_SIZE        : Data Size                                                                                 */
/*                  --> *u4_ap_rdnrslt   : RDN Data                                                                                  */
/*                  --> *u4_ap_DATA      : Read Buffer                                                                               */
/*                  --> *u1_ap_STATUS    : Read Status                                                                               */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_NvmcMod_OthSumSnglSmll_RdnData(const U1 u1_a_SIZE, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS)
{
    U4  u4_t_sum;
    U1  u1_t_ret;
    U1  u1_t_nlong;
    U1  u1_t_sts_bit;
    U1  u1_t_chkrslt;

    u1_t_ret = (U1)NVMC_MOD_RSLT_NG;

    if(u1_a_SIZE < (U1)NVMC_MOD_OTH_SUM_SNGL_SMLL_MIN_BUFSIZE){
        /* u1_t_ret = (U1)NVMC_MOD_RSLT_NG; */
    }
    else{
        u1_t_sts_bit = u1_d_NvmcMod_Lib_StatusCheck((U1)NVMC_MOD_OTH_SUM_SNGL_SMLL_RDNNUM, u1_a_SIZE, u1_ap_STATUS);
        if(u1_t_sts_bit == (U1)0U){
            u1_t_nlong = u1_a_SIZE - (U1)1U;
            u4_t_sum = (U4)0U;
            u1_t_chkrslt = u1_d_NvmcMod_GetErrDetectCode(&u4_ap_DATA[0], u1_t_nlong, &u4_t_sum);
            if((u1_t_chkrslt == (U1)TRUE) &&
               (u4_t_sum == u4_ap_DATA[u1_t_nlong])){
                vd_g_MemcpyU4(u4_ap_rdnrslt, &u4_ap_DATA[0], (U4)u1_t_nlong);
                u1_t_ret = (U1)NVMC_MOD_RSLT_OK;
            }
            else{
                /* u1_t_ret = (U1)NVMC_MOD_RSLT_NG; */
            }
        }
        else if(u1_t_sts_bit == (U1)NVMC_MOD_OTH_SUM_SNGL_SMLL_LOST_BIT){
            u1_t_ret = (U1)NVMC_MOD_RSLT_LOST;
        }
        else{
            /* u1_t_ret = (U1)NVMC_MOD_RSLT_NG; */
        }
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static void   vd_s_NvmcMod_OthSumSnglSmll_WrData(U4 * const u4_ap_writedata, const U1 u1_a_BLOCKNUM, const U1 u1_a_SIZE)         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u4_ap_writedata : Write Data                                                                                */
/*                  --> u1_a_BLOCKNUM    : Block Num                                                                                 */
/*                  --> u1_a_SIZE        : Data Size                                                                                 */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void   vd_s_NvmcMod_OthSumSnglSmll_WrData(U4 * const u4_ap_writedata, const U1 u1_a_BLOCKNUM, const U1 u1_a_SIZE)
{
    U4   u4_t_sum;
    U1   u1_t_nlong;

    if(u1_a_SIZE < (U1)NVMC_MOD_OTH_SUM_SNGL_SMLL_MIN_BUFSIZE){
        u4_ap_writedata[0] = (U4)0U; 
    }
    else{
        u4_t_sum = (U4)0U;
        u1_t_nlong = u1_a_SIZE - (U1)1U;
        (void)u1_d_NvmcMod_GetErrDetectCode(u4_ap_writedata, u1_t_nlong, &u4_t_sum);
        u4_ap_writedata[u1_t_nlong] = u4_t_sum;
    }
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version         Date        Author  Change Description                                                                           */
/* ---------------  ----------  ------  -------------------------------------------------------------------------------------------  */
/*  1.0.0           04/14/2017  HK      New.                                                                                         */
/*  1.0.1           08/22/2017  HK      Fixed AIP3GBSW-146 issue.                                                                    */
/*  1.1.0           09/04/2017  HK      Fixed AIP3GBSW-155 issue (add new module size(24, 28)).                                      */
/*  1.1.1           12/01/2017  HK      Fixed AIP3GBSW-222 issue.                                                                    */
/*  1.1.2           11/ 8/2023  KN      Improvement : Warning MISRA-C-Rule7.2 was fixed.                                             */
/*                                                                                                                                   */
/*  * HK      = Hayato Kanamori, Denso Create                                                                                        */
/*  * KN      = Keigo Nomura   , Denso Create                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
