/* 1.5.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Nvmc : Module Other SUM EEP DBL                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NVMC_MOD_OTH_SUM_EEP_DBL_C_MAJOR         (1U)
#define NVMC_MOD_OTH_SUM_EEP_DBL_C_MINOR         (5U)
#define NVMC_MOD_OTH_SUM_EEP_DBL_C_PATCH         (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include "memfill_u4.h"

#include "nvmc_mgr_private.h"
#include "nvmc_mod_lib_private.h"
#include "nvmc_mod_lib_oth_private.h"
#include "nvmc_mod_cfg_private.h"

#include "nvmc_mod_oth_sum_eep_dbl_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((NVMC_MOD_OTH_SUM_EEP_DBL_C_MAJOR != NVMC_MOD_OTH_SUM_EEP_DBL_H_MAJOR) || \
     (NVMC_MOD_OTH_SUM_EEP_DBL_C_MINOR != NVMC_MOD_OTH_SUM_EEP_DBL_H_MINOR) || \
     (NVMC_MOD_OTH_SUM_EEP_DBL_C_PATCH != NVMC_MOD_OTH_SUM_EEP_DBL_H_PATCH))
#error "nvmc_mod_oth_sum_eep_dbl.c and nvmc_mod_oth_sum_eep_dbl_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NVMCMOD_OTHSUM_EEP_DBL_RDNNUM            (2U)
#define NVMCMOD_OTHSUM_EEP_DBL_SHFT              (16U)
#define NVMCMOD_OTHSUM_EEP_DBL_MASK              (0x0000FFFFU)

#define NVMCMOD_OTHSUM_EEP_MIN_BUFSIZE           (2U)                                     /* ( 4byte + SUM(4byte))          */
#define NVMCMOD_OTHSUM_EEP_DBL_BUFSIZE           (NVMC_MOD_LIB_OTHR_MAX_BUFSIZE * NVMCMOD_OTHSUM_EEP_DBL_RDNNUM)

#define NVMCMOD_OTHSUM_EEP_4B_BLOCKNUM           (4U)                                     /* ( 2block + SUM(2block))        */
#define NVMCMOD_OTHSUM_EEP_8B_BLOCKNUM           (6U)                                     /* ( 4block + SUM(2block))        */
#define NVMCMOD_OTHSUM_EEP_12B_BLOCKNUM          (8U)                                     /* ( 6block + SUM(2block))        */
#define NVMCMOD_OTHSUM_EEP_16B_BLOCKNUM          (10U)                                    /* ( 8block + SUM(2block))        */
#define NVMCMOD_OTHSUM_EEP_20B_BLOCKNUM          (12U)                                    /* (10block + SUM(2block))        */
#define NVMCMOD_OTHSUM_EEP_24B_BLOCKNUM          (14U)                                    /* (12block + SUM(2block))        */
#define NVMCMOD_OTHSUM_EEP_28B_BLOCKNUM          (16U)                                    /* (14block + SUM(2block))        */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1   u1_s_NvmcMod_OthSumDbl_EEP_RdnD(const U1 u1_a_SIZE, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS);
static U4   u4_s_NvmcMod_OthSumDbl_EEP_WrD(const U4 * const u4_ap_WRITEDATA, const U1 u1_a_BLOCKNUM, const U1 u1_a_SIZE);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U1 u1_d_NvmcMod_4bSumDbl_EEP_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA : Data configuration                                                                          */
/*                  --> *u4_ap_rdnrslt : Redundancy data                                                                             */
/*                  --> *u4_ap_DATA    : Read Buffer                                                                                 */
/*                  --> *u1_ap_STATUS  : Read Status                                                                                 */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
U1   u1_d_NvmcMod_4bSumDbl_EEP_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS)
{
    U1  u1_t_ret;

    u1_t_ret = u1_s_NvmcMod_OthSumDbl_EEP_RdnD((U1)NVMCMOD_OTHSUM_EEP_4B_BLOCKNUM, u4_ap_rdnrslt, u4_ap_DATA, u1_ap_STATUS);
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1 u1_d_NvmcMod_8bSumDbl_EEP_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA : Data configuration                                                                          */
/*                  --> *u4_ap_rdnrslt : Redundancy data                                                                             */
/*                  --> *u4_ap_DATA    : Read Buffer                                                                                 */
/*                  --> *u1_ap_STATUS  : Read Status                                                                                 */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
U1   u1_d_NvmcMod_8bSumDbl_EEP_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS)
{
    U1  u1_t_ret;

    u1_t_ret = u1_s_NvmcMod_OthSumDbl_EEP_RdnD((U1)NVMCMOD_OTHSUM_EEP_8B_BLOCKNUM, u4_ap_rdnrslt, u4_ap_DATA, u1_ap_STATUS);
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1 u1_d_NvmcMod_12bSumDbl_EEP_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA : Data configuration                                                                          */
/*                  --> *u4_ap_rdnrslt : Redundancy data                                                                             */
/*                  --> *u4_ap_DATA    : Read Buffer                                                                                 */
/*                  --> *u1_ap_STATUS  : Read Status                                                                                 */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
U1   u1_d_NvmcMod_12bSumDbl_EEP_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS)
{
    U1  u1_t_ret;

    u1_t_ret = u1_s_NvmcMod_OthSumDbl_EEP_RdnD((U1)NVMCMOD_OTHSUM_EEP_12B_BLOCKNUM, u4_ap_rdnrslt, u4_ap_DATA, u1_ap_STATUS);
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1 u1_d_NvmcMod_16bSumDbl_EEP_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA : Data configuration                                                                          */
/*                  --> *u4_ap_rdnrslt : Redundancy data                                                                             */
/*                  --> *u4_ap_DATA    : Read Buffer                                                                                 */
/*                  --> *u1_ap_STATUS  : Read Status                                                                                 */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
U1   u1_d_NvmcMod_16bSumDbl_EEP_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS)
{
    U1  u1_t_ret;

    u1_t_ret = u1_s_NvmcMod_OthSumDbl_EEP_RdnD((U1)NVMCMOD_OTHSUM_EEP_16B_BLOCKNUM, u4_ap_rdnrslt, u4_ap_DATA, u1_ap_STATUS);
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1 u1_d_NvmcMod_20bSumDbl_EEP_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA : Data configuration                                                                          */
/*                  --> *u4_ap_rdnrslt : Redundancy data                                                                             */
/*                  --> *u4_ap_DATA    : Read Buffer                                                                                 */
/*                  --> *u1_ap_STATUS  : Read Status                                                                                 */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
U1   u1_d_NvmcMod_20bSumDbl_EEP_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS)
{
    U1  u1_t_ret;

    u1_t_ret = u1_s_NvmcMod_OthSumDbl_EEP_RdnD((U1)NVMCMOD_OTHSUM_EEP_20B_BLOCKNUM, u4_ap_rdnrslt, u4_ap_DATA, u1_ap_STATUS);
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1 u1_d_NvmcMod_24bSumDbl_EEP_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA : Data configuration                                                                          */
/*                  --> *u4_ap_rdnrslt : Redundancy data                                                                             */
/*                  --> *u4_ap_DATA    : Read Buffer                                                                                 */
/*                  --> *u1_ap_STATUS  : Read Status                                                                                 */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
U1   u1_d_NvmcMod_24bSumDbl_EEP_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS)
{
    U1  u1_t_ret;

    u1_t_ret = u1_s_NvmcMod_OthSumDbl_EEP_RdnD((U1)NVMCMOD_OTHSUM_EEP_24B_BLOCKNUM, u4_ap_rdnrslt, u4_ap_DATA, u1_ap_STATUS);
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1 u1_d_NvmcMod_28bSumDbl_EEP_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA : Data configuration                                                                          */
/*                  --> *u4_ap_rdnrslt : Redundancy data                                                                             */
/*                  --> *u4_ap_DATA    : Read Buffer                                                                                 */
/*                  --> *u1_ap_STATUS  : Read Status                                                                                 */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
U1   u1_d_NvmcMod_28bSumDbl_EEP_RdnD(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS)
{
    U1  u1_t_ret;

    u1_t_ret = u1_s_NvmcMod_OthSumDbl_EEP_RdnD((U1)NVMCMOD_OTHSUM_EEP_28B_BLOCKNUM, u4_ap_rdnrslt, u4_ap_DATA, u1_ap_STATUS);
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  void   vd_d_NvmcMod_4bSumDbl_EEP_WrD(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u4_ap_writedata : Write Data                                                                                */
/*                  --> u1_a_RDNNUM      : RDN Nunm                                                                                  */
/*                  --> u1_a_BLOCKNUM    : Block Num                                                                                 */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void   vd_d_NvmcMod_4bSumDbl_EEP_WrD(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)
{
    u4_ap_writedata[0] = u4_s_NvmcMod_OthSumDbl_EEP_WrD(u4_ap_writedata, u1_a_BLOCKNUM, (U1)NVMCMOD_OTHSUM_EEP_4B_BLOCKNUM);
}

/*===================================================================================================================================*/
/*  void   vd_d_NvmcMod_8bSumDbl_EEP_WrD(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u4_ap_writedata : Write Data                                                                                */
/*                  --> u1_a_RDNNUM      : RDN Nunm                                                                                  */
/*                  --> u1_a_BLOCKNUM    : Block Num                                                                                 */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void   vd_d_NvmcMod_8bSumDbl_EEP_WrD(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)
{
    u4_ap_writedata[0] = u4_s_NvmcMod_OthSumDbl_EEP_WrD(u4_ap_writedata, u1_a_BLOCKNUM, (U1)NVMCMOD_OTHSUM_EEP_8B_BLOCKNUM);
}

/*===================================================================================================================================*/
/*  void   vd_d_NvmcMod_12bSumDbl_EEP_WrD(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u4_ap_writedata : Write Data                                                                                */
/*                  --> u1_a_RDNNUM      : RDN Nunm                                                                                  */
/*                  --> u1_a_BLOCKNUM    : Block Num                                                                                 */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void   vd_d_NvmcMod_12bSumDbl_EEP_WrD(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)
{
    u4_ap_writedata[0] = u4_s_NvmcMod_OthSumDbl_EEP_WrD(u4_ap_writedata, u1_a_BLOCKNUM, (U1)NVMCMOD_OTHSUM_EEP_12B_BLOCKNUM);
}

/*===================================================================================================================================*/
/*  void   vd_d_NvmcMod_16bSumDbl_EEP_WrD(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u4_ap_writedata : Write Data                                                                                */
/*                  --> u1_a_RDNNUM      : RDN Nunm                                                                                  */
/*                  --> u1_a_BLOCKNUM    : Block Num                                                                                 */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void   vd_d_NvmcMod_16bSumDbl_EEP_WrD(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)
{
    u4_ap_writedata[0] = u4_s_NvmcMod_OthSumDbl_EEP_WrD(u4_ap_writedata, u1_a_BLOCKNUM, (U1)NVMCMOD_OTHSUM_EEP_16B_BLOCKNUM);
}

/*===================================================================================================================================*/
/*  void   vd_d_NvmcMod_20bSumDbl_EEP_WrD(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u4_ap_writedata : Write Data                                                                                */
/*                  --> u1_a_RDNNUM      : RDN Nunm                                                                                  */
/*                  --> u1_a_BLOCKNUM    : Block Num                                                                                 */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void   vd_d_NvmcMod_20bSumDbl_EEP_WrD(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)
{
    u4_ap_writedata[0] = u4_s_NvmcMod_OthSumDbl_EEP_WrD(u4_ap_writedata, u1_a_BLOCKNUM, (U1)NVMCMOD_OTHSUM_EEP_20B_BLOCKNUM);
}

/*===================================================================================================================================*/
/*  void   vd_d_NvmcMod_24bSumDbl_EEP_WrD(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u4_ap_writedata : Write Data                                                                                */
/*                  --> u1_a_RDNNUM      : RDN Nunm                                                                                  */
/*                  --> u1_a_BLOCKNUM    : Block Num                                                                                 */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void   vd_d_NvmcMod_24bSumDbl_EEP_WrD(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)
{
    u4_ap_writedata[0] = u4_s_NvmcMod_OthSumDbl_EEP_WrD(u4_ap_writedata, u1_a_BLOCKNUM, (U1)NVMCMOD_OTHSUM_EEP_24B_BLOCKNUM);
}

/*===================================================================================================================================*/
/*  void   vd_d_NvmcMod_28bSumDbl_EEP_WrD(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u4_ap_writedata : Write Data                                                                                */
/*                  --> u1_a_RDNNUM      : RDN Nunm                                                                                  */
/*                  --> u1_a_BLOCKNUM    : Block Num                                                                                 */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void   vd_d_NvmcMod_28bSumDbl_EEP_WrD(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)
{
    u4_ap_writedata[0] = u4_s_NvmcMod_OthSumDbl_EEP_WrD(u4_ap_writedata, u1_a_BLOCKNUM, (U1)NVMCMOD_OTHSUM_EEP_28B_BLOCKNUM);
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
/*  static U1   u1_s_NvmcMod_OthSumDbl_EEP_RdnD(const U1 u1_a_SIZE, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u1_a_SIZE        : Data Size                                                                                 */
/*                  --> *u4_ap_rdnrslt   : RDN Data                                                                                  */
/*                  --> *u4_ap_DATA      : Read Buffer                                                                               */
/*                  --> *u1_ap_STATUS    : Read Status                                                                               */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_NvmcMod_OthSumDbl_EEP_RdnD(const U1 u1_a_SIZE, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS)
{
    U4  u4_t_buf[NVMCMOD_OTHSUM_EEP_DBL_BUFSIZE];
    U1  u1_t_nlong;
    U1  u1_t_ret;
    U1  u1_t_sts_bit;

    vd_g_MemfillU4(u4_t_buf, (U4)0U, (U4)NVMCMOD_OTHSUM_EEP_DBL_BUFSIZE);

    u1_t_nlong = u1_a_SIZE * (U1)NVMCMOD_OTHSUM_EEP_DBL_RDNNUM;
    vd_d_NvmcMod_Lib_PackRevU2toU4(&u4_t_buf[0], &u4_ap_DATA[0], (U4)u1_t_nlong);

    u1_t_sts_bit = u1_d_NvmcMod_Lib_StatusCheck((U1)NVMCMOD_OTHSUM_EEP_DBL_RDNNUM, u1_a_SIZE, u1_ap_STATUS);
    u1_t_nlong = u1_a_SIZE >> 1U;
    u1_t_ret = u1_d_NvmcMod_Lib_RdnDblSumData(u1_t_nlong, u4_ap_rdnrslt, &u4_t_buf[0], u1_t_sts_bit);

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U4   u4_s_NvmcMod_OthSumDbl_EEP_WrD(const U4 * const u4_ap_WRITEDATA, const U1 u1_a_BLOCKNUM, const U1 u1_a_SIZE)         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u4_ap_WRITEDATA : Write Data                                                                                */
/*                  --> u1_a_BLOCKNUM    : Block Num                                                                                 */
/*                  --> u1_a_SIZE        : Data Size                                                                                 */
/*  Return:         U4 u4_t_ret : Write Data                                                                                         */
/*===================================================================================================================================*/
static U4   u4_s_NvmcMod_OthSumDbl_EEP_WrD(const U4 * const u4_ap_WRITEDATA, const U1 u1_a_BLOCKNUM, const U1 u1_a_SIZE)
{
    U4  u4_t_ret;
    U1  u1_t_index;
    U1  u1_t_nlong;

    u1_t_nlong = u1_a_SIZE >> 1U;
    if(u1_t_nlong < (U1)NVMCMOD_OTHSUM_EEP_MIN_BUFSIZE){
        u4_t_ret = (U4)0U;
    }
    else{
        u1_t_index = u1_a_BLOCKNUM >> 1U;
        u1_t_nlong--;

        if(u1_t_index == u1_t_nlong){
            u4_t_ret = (U4)0U;
            (void)u1_d_NvmcMod_GetErrDetectCode(u4_ap_WRITEDATA, u1_t_nlong, &u4_t_ret);
        }
        else{
            u4_t_ret = u4_ap_WRITEDATA[u1_t_index];
        }

        if((u1_a_BLOCKNUM & (U1)1U) != (U1)0U){
            u4_t_ret >>= NVMCMOD_OTHSUM_EEP_DBL_SHFT;
        }
        u4_t_ret &= (U4)NVMCMOD_OTHSUM_EEP_DBL_MASK;
    }

    return(u4_t_ret);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version         Date        Author  Change Description                                                                           */
/* ---------------  ----------  ------  -------------------------------------------------------------------------------------------  */
/*  1.0.0           11/20/2015  KM      New.                                                                                         */
/*  1.1.0            2/ 2/2016  KM      Updated from checksum to ErrorDetectCode(CFG).                                               */
/*  1.2.0            2/17/2016  KM      Add 4byte IF.                                                                                */
/*  1.2.1            3/25/2016  KM      Fixed Unit Test issue.                                                                       */
/*  1.2.2            4/ 4/2016  KM      Fixed PCS3-2 issue.                                                                          */
/*  1.2.3            4/11/2016  HK      Fixed function comments.                                                                     */
/*  1.2.4            5/16/2016  HK      Fixed PCS3-2 issue.                                                                          */
/*  1.3.0            5/26/2016  KM      Add 20byte IF.                                                                               */
/*  1.3.1            6/17/2016  KM      Fixed code sonar issue.                                                                      */
/*  1.4.0            11/4/2016  HK      Changed with the small sector correspondence.                                                */
/*  1.4.1           11/10/2016  HK      Fixed AIP3GBSW-7 issue.                                                                      */
/*  1.4.2            8/22/2017  HK      Fixed AIP3GBSW-146 issue.                                                                    */
/*  1.5.0            9/ 4/2017  HK      Fixed AIP3GBSW-155 issue (add new module size(24, 28)).                                      */
/*  1.5.1           11/ 8/2023  KN      Improvement : Warning MISRA-C-Rule7.2 was fixed.                                             */
/*                                                                                                                                   */
/*  * KM      = Kazuyuki Makino, Denso Create                                                                                        */
/*  * HK      = Hayato Kanamori, Denso Create                                                                                        */
/*  * KN      = Keigo Nomura   , Denso Create                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
