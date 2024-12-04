/* 1.2.3 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Nvmc : Module SIGN3BIT SNGL                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NVMC_MOD_SIGN3BIT_SNGL_C_MAJOR           (1U)
#define NVMC_MOD_SIGN3BIT_SNGL_C_MINOR           (2U)
#define NVMC_MOD_SIGN3BIT_SNGL_C_PATCH           (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include "nvmc_mgr_private.h"
#include "nvmc_mod_lib_private.h"

#include "nvmc_mod_sign3bit_sngl_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((NVMC_MOD_SIGN3BIT_SNGL_C_MAJOR != NVMC_MOD_SIGN3BIT_SNGL_H_MAJOR) || \
     (NVMC_MOD_SIGN3BIT_SNGL_C_MINOR != NVMC_MOD_SIGN3BIT_SNGL_H_MINOR) || \
     (NVMC_MOD_SIGN3BIT_SNGL_C_PATCH != NVMC_MOD_SIGN3BIT_SNGL_H_PATCH))
#error "nvmc_mod_sign3bit_sngl.c and nvmc_mod_sign3bit_sngl_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NVMC_MOD_SIGN3BIT_SNGL_RDNNUM            (1U)
#define NVMC_MOD_SIGN3BIT_SNGL_LOST_BIT_VAL      (1U)
#define NVMC_MOD_SIGN3BIT_SNGL_DATA_SIZE         (1U)

#define NVMC_MOD_SIGN3BIT_SNGL_SHIFT_P1          (0U)
#define NVMC_MOD_SIGN3BIT_SNGL_SHIFT_P2          (8U)

#define NVMC_MOD_SIGN3BIT_SNGL_READMASK          (0x000000FFU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1   u1_s_NvmcMod_S4R1_RdnData(U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS, const U1 u1_a_SHIFT);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U1      u1_d_NvmcMod_S1R1P1_RdnData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA : Data configuration                                                                          */
/*                  --> *u4_ap_rdnrslt : RDN Data                                                                                    */
/*                  --> *u4_ap_DATA    : Read Buffer                                                                                 */
/*                  --> *u1_ap_STATUS  : Status                                                                                      */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
U1   u1_d_NvmcMod_S1R1P1_RdnData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS)
{
    U1  u1_t_ret;

    u1_t_ret = u1_s_NvmcMod_S4R1_RdnData(u4_ap_rdnrslt, u4_ap_DATA, u1_ap_STATUS, (U1)NVMC_MOD_SIGN3BIT_SNGL_SHIFT_P1);
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_d_NvmcMod_S1R1P2_RdnData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA : Data configuration                                                                          */
/*                  --> *u4_ap_rdnrslt : RDN Data                                                                                    */
/*                  --> *u4_ap_DATA    : Read Buffer                                                                                 */
/*                  --> *u1_ap_STATUS  : Status                                                                                      */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
U1   u1_d_NvmcMod_S1R1P2_RdnData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS)
{
    U1  u1_t_ret;

    u1_t_ret = u1_s_NvmcMod_S4R1_RdnData(u4_ap_rdnrslt, u4_ap_DATA, u1_ap_STATUS, (U1)NVMC_MOD_SIGN3BIT_SNGL_SHIFT_P2);
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  void   vd_d_NvmcMod_S1R1P1_WrData(const U4 *u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u4_ap_writedata : Write Data                                                                                */
/*                  --> u1_a_RDNNUM      : RDN Nunm                                                                                  */
/*                  --> u1_a_BLOCKNUM    : Block Num                                                                                 */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void   vd_d_NvmcMod_S1R1P1_WrData(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)
{
    U4  u4_t_wdata;

    u4_t_wdata = (U4)u1_d_NvmcMod_Lib_Get3BitSign((S1)u4_ap_writedata[0]);

    u4_ap_writedata[0] = u4_t_wdata;
}

/*===================================================================================================================================*/
/*  void   vd_d_NvmcMod_S1R1P2_WrData(const U4 *u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u4_ap_writedata : Write Data                                                                                */
/*                  --> u1_a_RDNNUM      : RDN Nunm                                                                                  */
/*                  --> u1_a_BLOCKNUM    : Block Num                                                                                 */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void   vd_d_NvmcMod_S1R1P2_WrData(U4 * const u4_ap_writedata, const U1 u1_a_RDNNUM, const U1 u1_a_BLOCKNUM)
{
    U4  u4_t_wdata;

    u4_t_wdata = (U4)u1_d_NvmcMod_Lib_Get3BitSign((S1)u4_ap_writedata[0]);
    u4_t_wdata <<= NVMC_MOD_SIGN3BIT_SNGL_SHIFT_P2;

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
/*  static U1   u1_s_NvmcMod_S4R1_RdnData(U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS, const U1 u1_a_SHIFT) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u4_ap_rdnrslt : RDN Data                                                                                    */
/*                  --> *u4_ap_DATA    : Read Buffer                                                                                 */
/*                  --> *u1_ap_STATUS  : Status                                                                                      */
/*                  --> u1_a_SHIFT     : Shift                                                                                       */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_NvmcMod_S4R1_RdnData(U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS, const U1 u1_a_SHIFT)
{
    U1  u1_t_ret;
    U1  u1_t_sts_bit;
    U1  u1_t_work;

    u1_t_sts_bit = u1_d_NvmcMod_Lib_StatusCheck((U1)NVMC_MOD_SIGN3BIT_SNGL_RDNNUM, (U1)NVMC_MOD_SIGN3BIT_SNGL_DATA_SIZE, u1_ap_STATUS);
    u1_t_ret = (U1)NVMC_MOD_RSLT_NG;
    if(u1_t_sts_bit == (U1)0U){
        u1_t_work = (U1)(u4_ap_DATA[0] >> u1_a_SHIFT);
        u4_ap_rdnrslt[0] = (U4)((U1)s1_d_NvmcMod_Lib_Major3BitSign(u1_t_work));
        u1_t_ret = (U1)NVMC_MOD_RSLT_OK;
    }
    else if(u1_t_sts_bit == (U1)NVMC_MOD_SIGN3BIT_SNGL_LOST_BIT_VAL){
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
/*  1.0.1            4/11/2016  HK      Fixed function comments.                                                                     */
/*  1.1.0            4/15/2016  KM      Added 3BitSign write Function.                                                               */
/*  1.1.1            5/16/2016  HK      Fixed PCS3-2 issue.                                                                          */
/*  1.2.0            11/3/2016  HK      Changed with the small sector correspondence.                                                */
/*  1.2.1            8/22/2017  HK      Fixed AIP3GBSW-146 issue.                                                                    */
/*  1.2.2            9/16/2021  TN      QAC warnings were fixed.                                                                     */
/*  1.2.3           11/ 8/2023  KN      Improvement : Warning MISRA-C-Rule7.2 was fixed.                                             */
/*                                                                                                                                   */
/*  * KM      = Kazuyuki Makino, Denso Create                                                                                        */
/*  * HK      = Hayato Kanamori, Denso Create                                                                                        */
/*  * TN      = Takashi Nagai, Denso                                                                                                 */
/*  * KN      = Keigo Nomura   , Denso Create                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
