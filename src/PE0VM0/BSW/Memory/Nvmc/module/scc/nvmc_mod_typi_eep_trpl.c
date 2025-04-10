/* 1.1.2 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Nvmc : Module TYPI EEP TRPL                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NVMC_MOD_TYPI_EEP_TRPL_C_MAJOR           (1U)
#define NVMC_MOD_TYPI_EEP_TRPL_C_MINOR           (1U)
#define NVMC_MOD_TYPI_EEP_TRPL_C_PATCH           (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include "trpl_rdndnt.h"

#include "nvmc_mgr_private.h"
#include "nvmc_mod_lib_private.h"

#include "nvmc_mod_typi_eep_trpl_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((NVMC_MOD_TYPI_EEP_TRPL_C_MAJOR != NVMC_MOD_TYPI_EEP_TRPL_H_MAJOR) || \
     (NVMC_MOD_TYPI_EEP_TRPL_C_MINOR != NVMC_MOD_TYPI_EEP_TRPL_H_MINOR) || \
     (NVMC_MOD_TYPI_EEP_TRPL_C_PATCH != NVMC_MOD_TYPI_EEP_TRPL_H_PATCH))
#error "nvmc_mod_typi_eep_trpl.c and nvmc_mod_typi_eep_trpl_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NVMC_MOD_TYPI_EEP_TRPL_RDNNUM            (3U)
#define NVMC_MOD_TYPI_EEP_TRPL_LOST_BIT_VAL      (7U)
#define NVMC_MOD_TYPI_EEP_TRPL_DATA_SIZE         (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1   u1_s_NvmcMod_TypiTrpl_E_RdnData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS, const U1 u1_a_POS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U1      u1_d_NvmcMod_U2R3Lo_EEP_RdnData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA : Data configuration                                                                          */
/*                  --> *u4_ap_rdnrslt : RDN Data                                                                                    */
/*                  --> *u4_ap_DATA    : Read Buffer                                                                                 */
/*                  --> *u1_ap_STATUS  : Status                                                                                      */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
U1   u1_d_NvmcMod_U2R3Lo_EEP_RdnData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS)
{
    U1  u1_t_ret;

    u1_t_ret = u1_s_NvmcMod_TypiTrpl_E_RdnData(st_ap_CFGDATA, u4_ap_rdnrslt, u4_ap_DATA, u1_ap_STATUS, (U1)NVMC_MOD_LIB_POS_LO);
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_d_NvmcMod_U1R3P2_EEP_RdnData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA : Data configuration                                                                          */
/*                  --> *u4_ap_rdnrslt : RDN Data                                                                                    */
/*                  --> *u4_ap_DATA    : Read Buffer                                                                                 */
/*                  --> *u1_ap_STATUS  : Status                                                                                      */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
U1   u1_d_NvmcMod_U1R3P2_EEP_RdnData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS)
{
    U1  u1_t_ret;

    u1_t_ret = u1_s_NvmcMod_TypiTrpl_E_RdnData(st_ap_CFGDATA, u4_ap_rdnrslt, u4_ap_DATA, u1_ap_STATUS, (U1)NVMC_MOD_LIB_POS_P2);
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_d_NvmcMod_U1R3P1_EEP_RdnData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA : Data configuration                                                                          */
/*                  --> *u4_ap_rdnrslt : RDN Data                                                                                    */
/*                  --> *u4_ap_DATA    : Read Buffer                                                                                 */
/*                  --> *u1_ap_STATUS  : Status                                                                                      */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
U1   u1_d_NvmcMod_U1R3P1_EEP_RdnData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS)
{
    U1  u1_t_ret;

    u1_t_ret = u1_s_NvmcMod_TypiTrpl_E_RdnData(st_ap_CFGDATA, u4_ap_rdnrslt, u4_ap_DATA, u1_ap_STATUS, (U1)NVMC_MOD_LIB_POS_P1);
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  void   vd_d_NvmcMod_U2R3Lo_EEP_WrData(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u4_ap_writedata : Write Data                                                                                */
/*                  --> u1_a_RDNNUM      : RDN Nunm                                                                                  */
/*                  --> u1_a_BLOCKNUM    : Block Num                                                                                 */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void   vd_d_NvmcMod_U2R3Lo_EEP_WrData(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)
{
    U4  u4_t_wdata;

    u4_t_wdata = u4_d_NvmcMod_Lib_ConvDataToMap(u4_ap_writedata[0], (U1)NVMC_MOD_LIB_POS_LO);
    u4_ap_writedata[0] = u4_t_wdata;
}

/*===================================================================================================================================*/
/*  void   vd_d_NvmcMod_U1R3P2_EEP_WrData(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u4_ap_writedata : Write Data                                                                                */
/*                  --> u1_a_RDNNUM      : RDN Nunm                                                                                  */
/*                  --> u1_a_BLOCKNUM    : Block Num                                                                                 */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void   vd_d_NvmcMod_U1R3P2_EEP_WrData(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)
{
    U4  u4_t_wdata;

    u4_t_wdata = u4_d_NvmcMod_Lib_ConvDataToMap(u4_ap_writedata[0], (U1)NVMC_MOD_LIB_POS_P2);
    u4_ap_writedata[0] = u4_t_wdata;
}

/*===================================================================================================================================*/
/*  void   vd_d_NvmcMod_U1R3P1_EEP_WrData(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u4_ap_writedata : Write Data                                                                                */
/*                  --> u1_a_RDNNUM      : RDN Nunm                                                                                  */
/*                  --> u1_a_BLOCKNUM    : Block Num                                                                                 */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void   vd_d_NvmcMod_U1R3P1_EEP_WrData(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)
{
    U4  u4_t_wdata;

    u4_t_wdata = u4_d_NvmcMod_Lib_ConvDataToMap(u4_ap_writedata[0], (U1)NVMC_MOD_LIB_POS_P1);
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
/*  static U1   u1_s_NvmcMod_TypiTrpl_E_RdnData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS, const U1 u1_a_POS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA : Data configuration                                                                          */
/*                  --> *u4_ap_rdnrslt : Redundancy data                                                                             */
/*                  --> *u4_ap_DATA    : Read Buffer                                                                                 */
/*                  --> *u1_ap_STATUS  : Read Status                                                                                 */
/*                  --> u1_a_POS       : Position                                                                                    */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_NvmcMod_TypiTrpl_E_RdnData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS, const U1 u1_a_POS)
{
    static const U1 u1_sp_NVMC_MOD_TYPI_EEP_TRPL_NODATA_TBL[NVMC_MOD_TYPI_EEP_TRPL_LOST_BIT_VAL] = {
        (U1)0U,  /* 000b */
        (U1)1U,  /* 001b */
        (U1)0U,  /* 010b */
        (U1)2U,  /* 011b */
        (U1)0U,  /* 100b */
        (U1)1U,  /* 101b */
        (U1)0U   /* 110b */
    };
    U4  u4_t_mod_type;
    U4  u4_t_rdn[NVMC_MOD_TYPI_EEP_TRPL_RDNNUM];
    U1  u1_t_ret;
    U1  u1_t_sts_bit;
    U1  u1_t_rdn_rslt;
    U1  u1_t_index;

    u1_t_sts_bit = u1_d_NvmcMod_Lib_StatusCheck((U1)NVMC_MOD_TYPI_EEP_TRPL_RDNNUM, (U1)NVMC_MOD_TYPI_EEP_TRPL_DATA_SIZE, u1_ap_STATUS);
    u1_t_ret = (U1)NVMC_MOD_RSLT_NG;
    if(u1_t_sts_bit == (U1)0U){
        for(u1_t_index = (U1)0U; u1_t_index < (U1)NVMC_MOD_TYPI_EEP_TRPL_RDNNUM; u1_t_index++){
            u4_t_rdn[u1_t_index] = u4_d_NvmcMod_Lib_ConvMapToData(u4_ap_DATA[u1_t_index], u1_a_POS);
        }

        u1_t_ret = (U1)NVMC_MOD_RSLT_OK;
        u4_t_mod_type = st_ap_CFGDATA->u4_module_bit_cfg & (U4)NVMC_DATA_ATTR_RDNT_TYPE_MASK;
        if(u4_t_mod_type == (U4)NVMC_DATA_ATTR_RDNT_TYPE_BIT){
            *u4_ap_rdnrslt = u4_g_Majbit(&u4_t_rdn[0]);
        }
        else{
            *u4_ap_rdnrslt = (U4)0U;
            u1_t_rdn_rslt = u1_g_TrplRdndntchk(&u4_t_rdn[0], u4_ap_rdnrslt);
            if(u1_t_rdn_rslt == (U1)0U){
                u1_t_ret = (U1)NVMC_MOD_RSLT_RDN_NG;
                u4_ap_rdnrslt[0] = u4_d_NvmcMod_Lib_GetRdunErrorValue(st_ap_CFGDATA, &u4_t_rdn[0]);
            }
        }
    }
    else if(u1_t_sts_bit < (U1)NVMC_MOD_TYPI_EEP_TRPL_LOST_BIT_VAL){
        u1_t_index = u1_sp_NVMC_MOD_TYPI_EEP_TRPL_NODATA_TBL[u1_t_sts_bit];
        u4_ap_rdnrslt[0] = u4_d_NvmcMod_Lib_ConvMapToData(u4_ap_DATA[u1_t_index], u1_a_POS);
        u1_t_ret = (U1)NVMC_MOD_RSLT_NODATA;
    }
    else if(u1_t_sts_bit == (U1)NVMC_MOD_TYPI_EEP_TRPL_LOST_BIT_VAL){
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
/*  1.0.0            2/ 2/2015  KM      New.                                                                                         */
/*  1.0.1            4/11/2016  HK      Fixed function comments.                                                                     */
/*  1.0.2            5/16/2016  HK      Fixed PCS3-2 issue.                                                                          */
/*  1.1.0            11/3/2016  HK      Changed with the small sector correspondence.                                                */
/*  1.1.1            8/22/2017  HK      Fixed AIP3GBSW-146 issue.                                                                    */
/*  1.1.2           11/ 8/2023  KN      Improvement : Warning MISRA-C-Rule7.2 was fixed.                                             */
/*                                                                                                                                   */
/*  * KM      = Kazuyuki Makino, Denso Create                                                                                        */
/*  * HK      = Hayato Kanamori, Denso Create                                                                                        */
/*  * KN      = Keigo Nomura   , Denso Create                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
