/* 1.1.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Nvmc : Module Other SNGL                                                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NVMC_MOD_OTH_SNGL_C_MAJOR                (1U)
#define NVMC_MOD_OTH_SNGL_C_MINOR                (1U)
#define NVMC_MOD_OTH_SNGL_C_PATCH                (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include "memcpy_u4.h"

#include "nvmc_mgr_private.h"
#include "nvmc_mod_lib_private.h"

#include "nvmc_mod_oth_sngl_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((NVMC_MOD_OTH_SNGL_C_MAJOR != NVMC_MOD_OTH_SNGL_H_MAJOR) || \
     (NVMC_MOD_OTH_SNGL_C_MINOR != NVMC_MOD_OTH_SNGL_H_MINOR) || \
     (NVMC_MOD_OTH_SNGL_C_PATCH != NVMC_MOD_OTH_SNGL_H_PATCH))
#error "nvmc_mod_oth_sngl.c and nvmc_mod_oth_sngl_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NVMC_MOD_OTH_SNGL_RDNNUM                 (1U)
#define NVMC_MOD_OTH_SNGL_LOST_BIT               (1U)
/* #define NVMC_MOD_OTH_SNGL_BLOCKNUM               (1U) */

#define NVMC_MOD_OTH_MIN_BUFSIZE                 (1U)         /* ( 4byte * 1 ) */

#define NVMC_MOD_OTH_SNGL_8B_BLOCKNUM            (2U)         /* ( 4Byte * 2 ) */
#define NVMC_MOD_OTH_SNGL_12B_BLOCKNUM           (3U)         /* ( 4Byte * 3 ) */
#define NVMC_MOD_OTH_SNGL_16B_BLOCKNUM           (4U)         /* ( 4Byte * 4 ) */
#define NVMC_MOD_OTH_SNGL_20B_BLOCKNUM           (5U)         /* ( 4Byte * 5 ) */
#define NVMC_MOD_OTH_SNGL_24B_BLOCKNUM           (6U)         /* ( 4Byte * 6 ) */
#define NVMC_MOD_OTH_SNGL_28B_BLOCKNUM           (7U)         /* ( 4Byte * 7 ) */
#define NVMC_MOD_OTH_SNGL_32B_BLOCKNUM           (8U)         /* ( 4Byte * 8 ) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1   u1_s_NvmcMod_OthSngl_RdnData(const U1 u1_a_SIZE, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U1   u1_d_NvmcMod_ovr4bBlk8bSgl_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA : Data configuration                                                                          */
/*                  --> *u4_ap_rdnrslt : RDN Data                                                                                    */
/*                  --> *u4_ap_DATA    : Read Buffer                                                                                 */
/*                  --> *u1_ap_STATUS  : Status                                                                                      */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
U1   u1_d_NvmcMod_ovr4bBlk8bSgl_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS)
{
    U1  u1_t_ret;

    u1_t_ret = u1_s_NvmcMod_OthSngl_RdnData((U1)NVMC_MOD_OTH_SNGL_8B_BLOCKNUM, u4_ap_rdnrslt, u4_ap_DATA, u1_ap_STATUS);
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1   u1_d_NvmcMod_ovr4bBlk12bSgl_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA : Data configuration                                                                          */
/*                  --> *u4_ap_rdnrslt : RDN Data                                                                                    */
/*                  --> *u4_ap_DATA    : Read Buffer                                                                                 */
/*                  --> *u1_ap_STATUS  : Status                                                                                      */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
U1   u1_d_NvmcMod_ovr4bBlk12bSgl_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS)
{
    U1  u1_t_ret;

    u1_t_ret = u1_s_NvmcMod_OthSngl_RdnData((U1)NVMC_MOD_OTH_SNGL_12B_BLOCKNUM, u4_ap_rdnrslt, u4_ap_DATA, u1_ap_STATUS);
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1   u1_d_NvmcMod_ovr4bBlk16bSgl_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA : Data configuration                                                                          */
/*                  --> *u4_ap_rdnrslt : RDN Data                                                                                    */
/*                  --> *u4_ap_DATA    : Read Buffer                                                                                 */
/*                  --> *u1_ap_STATUS  : Status                                                                                      */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
U1   u1_d_NvmcMod_ovr4bBlk16bSgl_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS)
{
    U1  u1_t_ret;

    u1_t_ret = u1_s_NvmcMod_OthSngl_RdnData((U1)NVMC_MOD_OTH_SNGL_16B_BLOCKNUM, u4_ap_rdnrslt, u4_ap_DATA, u1_ap_STATUS);
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1   u1_d_NvmcMod_ovr4bBlk20bSgl_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA : Data configuration                                                                          */
/*                  --> *u4_ap_rdnrslt : RDN Data                                                                                    */
/*                  --> *u4_ap_DATA    : Read Buffer                                                                                 */
/*                  --> *u1_ap_STATUS  : Status                                                                                      */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
U1   u1_d_NvmcMod_ovr4bBlk20bSgl_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS)
{
    U1  u1_t_ret;

    u1_t_ret = u1_s_NvmcMod_OthSngl_RdnData((U1)NVMC_MOD_OTH_SNGL_20B_BLOCKNUM, u4_ap_rdnrslt, u4_ap_DATA, u1_ap_STATUS);
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1   u1_d_NvmcMod_ovr4bBlk24bSgl_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA : Data configuration                                                                          */
/*                  --> *u4_ap_rdnrslt : RDN Data                                                                                    */
/*                  --> *u4_ap_DATA    : Read Buffer                                                                                 */
/*                  --> *u1_ap_STATUS  : Status                                                                                      */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
U1   u1_d_NvmcMod_ovr4bBlk24bSgl_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS)
{
    U1  u1_t_ret;

    u1_t_ret = u1_s_NvmcMod_OthSngl_RdnData((U1)NVMC_MOD_OTH_SNGL_24B_BLOCKNUM, u4_ap_rdnrslt, u4_ap_DATA, u1_ap_STATUS);
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1   u1_d_NvmcMod_ovr4bBlk28bSgl_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA : Data configuration                                                                          */
/*                  --> *u4_ap_rdnrslt : RDN Data                                                                                    */
/*                  --> *u4_ap_DATA    : Read Buffer                                                                                 */
/*                  --> *u1_ap_STATUS  : Status                                                                                      */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
U1   u1_d_NvmcMod_ovr4bBlk28bSgl_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS)
{
    U1  u1_t_ret;

    u1_t_ret = u1_s_NvmcMod_OthSngl_RdnData((U1)NVMC_MOD_OTH_SNGL_28B_BLOCKNUM, u4_ap_rdnrslt, u4_ap_DATA, u1_ap_STATUS);
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1   u1_d_NvmcMod_ovr4bBlk32bSgl_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA : Data configuration                                                                          */
/*                  --> *u4_ap_rdnrslt : RDN Data                                                                                    */
/*                  --> *u4_ap_DATA    : Read Buffer                                                                                 */
/*                  --> *u1_ap_STATUS  : Status                                                                                      */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
U1   u1_d_NvmcMod_ovr4bBlk32bSgl_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS)
{
    U1  u1_t_ret;

    u1_t_ret = u1_s_NvmcMod_OthSngl_RdnData((U1)NVMC_MOD_OTH_SNGL_32B_BLOCKNUM, u4_ap_rdnrslt, u4_ap_DATA, u1_ap_STATUS);
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  void   vd_d_NvmcMod_ovr4bBlkSgl_WrD(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u4_ap_writedata : Write Data                                                                                */
/*                  --> u1_a_RDNNUM      : RDN Nunm                                                                                  */
/*                  --> u1_a_BLOCKNUM    : Block Num                                                                                 */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void   vd_d_NvmcMod_ovr4bBlkSgl_WrD(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)
{
    /* Nothing to do */
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
/*  static U1   u1_s_NvmcMod_OthSngl_RdnData(const U1 u1_a_SIZE, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u1_a_SIZE        : Copy Data Size                                                                            */
/*                  --> *u4_ap_rdnrslt   : RDN Data                                                                                  */
/*                  --> *u4_ap_DATA      : Read Buffer                                                                               */
/*                  --> *u1_ap_STATUS    : Read Status                                                                               */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_NvmcMod_OthSngl_RdnData(const U1 u1_a_SIZE, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS)
{
    U1  u1_t_ret;
    U1  u1_t_sts_bit;

    u1_t_ret = (U1)NVMC_MOD_RSLT_NG;
    
    if(u1_a_SIZE < (U1)NVMC_MOD_OTH_MIN_BUFSIZE){
        /* u1_t_ret = (U1)NVMC_MOD_RSLT_NG; */
    }
    else{
        u1_t_sts_bit = u1_d_NvmcMod_Lib_StatusCheck((U1)NVMC_MOD_OTH_SNGL_RDNNUM, u1_a_SIZE, u1_ap_STATUS);
        if(u1_t_sts_bit == (U1)0U){
            vd_g_MemcpyU4(u4_ap_rdnrslt, &u4_ap_DATA[0], (U4)u1_a_SIZE);
            u1_t_ret = (U1)NVMC_MOD_RSLT_OK;
        }
        else if(u1_t_sts_bit == (U1)NVMC_MOD_OTH_SNGL_LOST_BIT){
            u1_t_ret = (U1)NVMC_MOD_RSLT_LOST;
        }
        else{
            /* u1_t_ret = (U1)NVMC_MOD_RSLT_NG; */
        }
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
/*  1.0.0           11/01/2016  HK      New.                                                                                         */
/*  1.0.1           08/22/2017  HK      Fixed AIP3GBSW-146 issue.                                                                    */
/*  1.1.0           09/04/2017  HK      Fixed AIP3GBSW-155 issue (add new module size(24, 28, 32)).                                  */
/*  1.1.1           11/ 8/2023  KN      Improvement : Warning MISRA-C-Rule7.2 was fixed.                                             */
/*                                                                                                                                   */
/*  * HK      = Hayato Kanamori, Denso Create                                                                                        */
/*  * KN      = Keigo Nomura   , Denso Create                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
