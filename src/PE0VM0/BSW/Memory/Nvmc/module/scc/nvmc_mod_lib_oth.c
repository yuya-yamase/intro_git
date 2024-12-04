/* 1.4.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Nvmc : Module Lib Other                                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NVMC_MOD_LIB_OTH_C_MAJOR                 (1U)
#define NVMC_MOD_LIB_OTH_C_MINOR                 (4U)
#define NVMC_MOD_LIB_OTH_C_PATCH                 (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include "memcpy_u4.h"
#include "memfill_u4.h"

#include "nvmc_mgr.h"
#include "nvmc_mgr_private.h"
#include "nvmc_mod_cfg_private.h"

#include "nvmc_mod_lib_private.h"
#include "nvmc_mod_lib_oth_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((NVMC_MOD_LIB_OTH_C_MAJOR != NVMC_MOD_LIB_OTH_H_MAJOR) || \
     (NVMC_MOD_LIB_OTH_C_MINOR != NVMC_MOD_LIB_OTH_H_MINOR) || \
     (NVMC_MOD_LIB_OTH_C_PATCH != NVMC_MOD_LIB_OTH_H_PATCH))
#error "nvmc_mod_lib_oth.c and nvmc_mod_lib_oth_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NVMC_MOD_LIB_U2_SHFT                     (16U)
#define NVMC_MOD_LIB_U2_MASK                     (0x0000FFFFU)

/* #define NVMC_MOD_LIB_DBL_RDNNUM                  (2U) */
#define NVMC_MOD_LIB_DBL_LOST_BIT_VAL            (3U)
#define NVMC_MOD_LIB_DBL_OK_BIT_VAL              (0x00U)
#define NVMC_MOD_LIB_DBL_2ND_BIT_VAL             (0x01U)
/* #define NVMC_MOD_LIB_DBL_1ST_BIT_VAL             (0x02) */

#define NVMC_MOD_LIB_OTHR_MIN_BUFSIZE            (1U)         /* ( 4byte ) */
#define NVMC_MOD_LIB_OTHR_SUM_MIN_BUFSIZE        (2U)         /* ( 4byte + SUM(4byte)) */

#define NVMC_MOD_LIB_OTHR_MIN_PACKSIZE           (2U)         /* ( U2 * 2 )            */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1   u1_s_NvmcMod_Lib_RdnDblSumNorm(const U1 u1_a_SIZE, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA1, const U4 * const u4_ap_DATA2);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_d_NvmcMod_Lib_PackRevU2toU4(U4 * u4_ap_cpydst, const U4 * u4_ap_CPYSRC, const U4 u4_a_NUM_HALF)                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u4_ap_cpydst : Output Data Pointer                                                                          */
/*                  --> *u4_ap_CPYSRC : Input Data Pointer                                                                           */
/*                  --> u4_a_NUM_HALF : Data Size                                                                                    */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_d_NvmcMod_Lib_PackRevU2toU4(U4 * u4_ap_cpydst, const U4 * u4_ap_CPYSRC, const U4 u4_a_NUM_HALF)
{
    U4         u4_t_cnt;
    U4         u4_t_ndst;
    U4         u4_t_index;

    if(u4_a_NUM_HALF >= (U4)NVMC_MOD_LIB_OTHR_MIN_PACKSIZE){
        u4_t_index = (U4)0U;
        u4_t_ndst = u4_a_NUM_HALF >> 1U;
        for(u4_t_cnt = (U4)0U; u4_t_cnt < u4_t_ndst; u4_t_cnt++){
            u4_ap_cpydst[u4_t_cnt]  = (u4_ap_CPYSRC[u4_t_index] & (U4)NVMC_MOD_LIB_U2_MASK);
            u4_t_index++;
            u4_ap_cpydst[u4_t_cnt] |= u4_ap_CPYSRC[u4_t_index] << NVMC_MOD_LIB_U2_SHFT;
            u4_t_index++;
        }
    }
}

/*===================================================================================================================================*/
/*  U1   u1_d_NvmcMod_Lib_RdnDblData(const U1 u1_a_SIZE, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 u1_a_STS_BIT)     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u1_a_SIZE      : Data Size                                                                                   */
/*                  --> *u4_ap_rdnrslt : RDN Data Pointer                                                                            */
/*                  --> *u4_ap_DATA    : Read Buffer                                                                                 */
/*                  --> u1_a_STS_BIT   : Status bit                                                                                  */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
U1   u1_d_NvmcMod_Lib_RdnDblData(const U1 u1_a_SIZE, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 u1_a_STS_BIT)
{
    U2  u2_t_index;
    U1  u1_t_ret;

    u1_t_ret = (U1)NVMC_MOD_RSLT_NG;
    
    if(u1_a_SIZE < (U1)NVMC_MOD_LIB_OTHR_MIN_BUFSIZE){
        /* u1_t_ret = (U1)NVMC_MOD_RSLT_NG; */
    }
    else{
        if(u1_a_STS_BIT == (U1)NVMC_MOD_LIB_DBL_OK_BIT_VAL){
            vd_g_MemcpyU4(u4_ap_rdnrslt, &u4_ap_DATA[0], (U4)u1_a_SIZE);
            u1_t_ret = (U1)NVMC_MOD_RSLT_OK;
        }
        else if(u1_a_STS_BIT < (U1)NVMC_MOD_LIB_DBL_LOST_BIT_VAL){
            u2_t_index = (U2)0U;
            if(u1_a_STS_BIT == (U1)NVMC_MOD_LIB_DBL_2ND_BIT_VAL){
                u2_t_index = (U2)u1_a_SIZE;
            }
            vd_g_MemcpyU4(u4_ap_rdnrslt, &u4_ap_DATA[u2_t_index], (U4)u1_a_SIZE);
            u1_t_ret = (U1)NVMC_RESULT_NODATA;
        }
        else if(u1_a_STS_BIT == (U1)NVMC_MOD_LIB_DBL_LOST_BIT_VAL){
            u1_t_ret = (U1)NVMC_MOD_RSLT_LOST;
        }
        else{
            /* u1_t_ret = (U1)NVMC_MOD_RSLT_NG; */
        }
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1   u1_d_NvmcMod_Lib_RdnDblSumData(const U1 u1_a_SIZE, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 u1_a_STS_BIT)  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u1_a_SIZE      : Data Size                                                                                   */
/*                  --> *u4_ap_rdnrslt : RDN Data Pointer                                                                            */
/*                  --> *u4_ap_DATA    : Read Buffer                                                                                 */
/*                  --> u1_a_STS_BIT   : Status bit                                                                                  */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
U1   u1_d_NvmcMod_Lib_RdnDblSumData(const U1 u1_a_SIZE, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA, const U1 u1_a_STS_BIT)
{
    U4  u4_t_sum;
    U2  u2_t_index;
    U1  u1_t_ret;
    U1  u1_t_nlong;
    U1  u1_t_chkrslt;

    u1_t_ret = (U1)NVMC_MOD_RSLT_NG;

    if(u1_a_SIZE < (U1)NVMC_MOD_LIB_OTHR_SUM_MIN_BUFSIZE){
        /* u1_t_ret = (U1)NVMC_MOD_RSLT_NG; */
    }
    else{
        if(u1_a_STS_BIT == (U1)NVMC_MOD_LIB_DBL_OK_BIT_VAL){
            u1_t_ret = u1_s_NvmcMod_Lib_RdnDblSumNorm(u1_a_SIZE, u4_ap_rdnrslt, &u4_ap_DATA[0], &u4_ap_DATA[u1_a_SIZE]);
        }
        else if(u1_a_STS_BIT < (U1)NVMC_MOD_LIB_DBL_LOST_BIT_VAL){
            u2_t_index = (U2)0U;
            if(u1_a_STS_BIT == (U1)NVMC_MOD_LIB_DBL_2ND_BIT_VAL){
                u2_t_index = (U2)u1_a_SIZE;
            }

            u1_t_nlong = u1_a_SIZE - (U1)1U;
            u4_t_sum = (U4)0U;
            u1_t_chkrslt = u1_d_NvmcMod_GetErrDetectCode(&u4_ap_DATA[u2_t_index], u1_t_nlong, &u4_t_sum);
            if((u1_t_chkrslt == (U1)TRUE) &&
               (u4_t_sum == u4_ap_DATA[(u2_t_index + (U2)u1_a_SIZE) - (U2)1U])){
                vd_g_MemcpyU4(u4_ap_rdnrslt, &u4_ap_DATA[u2_t_index], (U4)u1_t_nlong);
                u1_t_ret = (U1)NVMC_RESULT_NODATA;
            }
            else{
                /* u1_t_ret = (U1)NVMC_MOD_RSLT_NG; */
            }
        }
        else if(u1_a_STS_BIT == (U1)NVMC_MOD_LIB_DBL_LOST_BIT_VAL){
            u1_t_ret = (U1)NVMC_MOD_RSLT_LOST;
        }
        else{
            /* u1_t_ret = (U1)NVMC_MOD_RSLT_NG; */
        }
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1   u1_d_NvmcMod_Lib_PreRdnOthr_DTF(const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS, const U1 u1_a_BLOCKNUM)         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u4_ap_DATA    : Read Buffer                                                                                 */
/*                  --> *u1_ap_STATUS  : Status                                                                                      */
/*                  --> u1_a_BLOCKNUM  : Block Num                                                                                   */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
U1   u1_d_NvmcMod_Lib_PreRdnOthr_DTF(const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS, const U1 u1_a_BLOCKNUM)
{
    U4  u4_t_chkcode;
    U1  u1_t_ret;
    U1  u1_t_sts_bit;
    U1  u1_t_nlong;
    U1  u1_t_chkrslt;

    u1_t_ret = (U1)NVMC_MOD_RSLT_NG;

    if(u1_a_BLOCKNUM < (U1)NVMC_MOD_LIB_OTHR_SUM_MIN_BUFSIZE){
        /* u1_t_ret = (U1)NVMC_MOD_RSLT_NG; */
    }
    else{
        u1_t_sts_bit = u1_d_NvmcMod_Lib_StatusCheck((U1)1U, u1_a_BLOCKNUM, u1_ap_STATUS);
        if(u1_t_sts_bit == (U1)0U){
            u1_t_nlong = u1_a_BLOCKNUM - (U1)1U;
            u4_t_chkcode = (U4)0U;
            u1_t_chkrslt = u1_d_NvmcMod_GetErrDetectCode(&u4_ap_DATA[0], u1_t_nlong, &u4_t_chkcode);
            if((u1_t_chkrslt == (U1)TRUE) &&
               (u4_t_chkcode == u4_ap_DATA[u1_t_nlong])){
                u1_t_ret = (U1)NVMC_MOD_RSLT_OK;
            }
            else{
                u1_t_ret = (U1)NVMC_MOD_RSLT_NODATA;
            }
        }
        else if(u1_t_sts_bit == (U1)1U){
            u1_t_ret = (U1)NVMC_MOD_RSLT_NODATA;
        }
        else{
            /* u1_t_ret = (U1)NVMC_MOD_RSLT_NG; */
        }
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1   u1_d_NvmcMod_Lib_PreRdnOthr_EEP(const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS, const U1 u1_a_BLOCKNUM)         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u4_ap_DATA    : Read Buffer                                                                                 */
/*                  --> *u1_ap_STATUS  : Status                                                                                      */
/*                  --> u1_a_BLOCKNUM  : Block Num                                                                                   */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
U1   u1_d_NvmcMod_Lib_PreRdnOthr_EEP(const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS, const U1 u1_a_BLOCKNUM)
{
    U4  u4_t_buf[NVMC_MOD_LIB_OTHR_MAX_BUFSIZE];
    U4  u4_t_chkcode;
    U1  u1_t_ret;
    U1  u1_t_sts_bit;
    U1  u1_t_nlong;
    U1  u1_t_chkrslt;

    u1_t_ret = (U1)NVMC_MOD_RSLT_NG;
    vd_g_MemfillU4(u4_t_buf, (U4)0U, (U4)NVMC_MOD_LIB_OTHR_MAX_BUFSIZE);

    u1_t_nlong = u1_a_BLOCKNUM >> 1U;
    if(u1_t_nlong < (U1)NVMC_MOD_LIB_OTHR_SUM_MIN_BUFSIZE){
        /* u1_t_ret = (U1)NVMC_MOD_RSLT_NG; */
    }
    else{
        u1_t_sts_bit = u1_d_NvmcMod_Lib_StatusCheck((U1)1U, u1_a_BLOCKNUM, u1_ap_STATUS);
        if(u1_t_sts_bit == (U1)0U){
            vd_d_NvmcMod_Lib_PackRevU2toU4(&u4_t_buf[0], &u4_ap_DATA[0], (U4)u1_a_BLOCKNUM);

            u1_t_nlong--;
            u4_t_chkcode = (U4)0U;
            u1_t_chkrslt = u1_d_NvmcMod_GetErrDetectCode(&u4_t_buf[0], u1_t_nlong, &u4_t_chkcode);
            if((u1_t_chkrslt == (U1)TRUE) &&
               (u4_t_chkcode == u4_t_buf[u1_t_nlong])){
                u1_t_ret = (U1)NVMC_MOD_RSLT_OK;
            }
            else{
                u1_t_ret = (U1)NVMC_MOD_RSLT_NODATA;
            }
        }
        else if(u1_t_sts_bit == (U1)1U){
            u1_t_ret = (U1)NVMC_MOD_RSLT_NODATA;
        }
        else{
            /* u1_t_ret = (U1)NVMC_MOD_RSLT_NG; */
        }
    }

    return(u1_t_ret);
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
/*  static U1   u1_s_NvmcMod_Lib_RdnDblSumNorm(const U1 u1_a_SIZE, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA1, const U4 * const u4_ap_DATA2) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u1_a_SIZE      : Data Size                                                                                   */
/*                  --> *u4_ap_rdnrslt : RDN Data Pointer                                                                            */
/*                  --> *u4_ap_DATA1   : Read Buffer                                                                                 */
/*                  --> *u4_ap_DATA2   : Read Buffer                                                                                 */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_NvmcMod_Lib_RdnDblSumNorm(const U1 u1_a_SIZE, U4 * u4_ap_rdnrslt, const U4 * const u4_ap_DATA1, const U4 * const u4_ap_DATA2)
{
    U4  u4_t_sum;
    U1  u1_t_ret;
    U1  u1_t_nlong;
    U1  u1_t_chkrslt;

    u1_t_ret = (U1)NVMC_MOD_RSLT_NG;

    /* It is not necessary to check the range of u1_a_SIZE because caller check it. */
    u1_t_nlong = u1_a_SIZE - (U1)1U;
    u4_t_sum = (U4)0U;
    u1_t_chkrslt = u1_d_NvmcMod_GetErrDetectCode(&u4_ap_DATA1[0], u1_t_nlong, &u4_t_sum);
    if((u1_t_chkrslt == (U1)TRUE) &&
       (u4_t_sum == u4_ap_DATA1[u1_t_nlong])){

        vd_g_MemcpyU4(u4_ap_rdnrslt, u4_ap_DATA1, (U4)u1_t_nlong);
        u1_t_ret = (U1)NVMC_MOD_RSLT_OK;
    }
    else{
        u4_t_sum = (U4)0U;
        u1_t_chkrslt = u1_d_NvmcMod_GetErrDetectCode(&u4_ap_DATA2[0], u1_t_nlong, &u4_t_sum);
        if((u1_t_chkrslt == (U1)TRUE) &&
           (u4_t_sum == u4_ap_DATA2[u1_t_nlong])){

            vd_g_MemcpyU4(u4_ap_rdnrslt, u4_ap_DATA2, (U4)u1_t_nlong);
            u1_t_ret = (U1)NVMC_MOD_RSLT_OK;
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
/*  1.0.0           11/20/2015  KM      New.                                                                                         */
/*  1.1.0           11/25/2015  KS      The Other module with Checksum was supported.                                                */
/*  1.1.1           12/10/2015  KM      Fixed code sonar issue.                                                                      */
/*  1.2.0            2/ 4/2016  KM      Added PreRead Process.                                                                       */
/*                                      Deleted Other triple redundant.                                                              */
/*                                      Updated from checksum to ErrorDetectCode(CFG).                                               */
/*  1.2.1            2/23/2016  KM      Added PreRead Process for EEPROM.                                                            */
/*  1.2.2            3/25/2016  KM      Fixed Unit Test issue.                                                                       */
/*  1.2.3            4/ 4/2016  KM      Fixed PCS3-2 issue.                                                                          */
/*  1.2.4            4/11/2016  HK      Fixed function comments.                                                                     */
/*  1.2.5            4/12/2016  KM      Deleted unnecessary include.                                                                 */
/*  1.2.6            5/16/2016  HK      Fixed PCS3-2 issue.                                                                          */
/*  1.2.7            5/26/2016  KM      Updated OTHR_MAX_BUFSIZE(20byte).                                                            */
/*  1.2.8            6/17/2016  KM      Fixed code sonar issue.                                                                      */
/*  1.3.0            11/3/2016  HK      Changed with the small sector correspondence.                                                */
/*  1.4.0            9/ 4/2017  HK      Fixed AIP3GBSW-155 issue (update buffer size).                                               */
/*  1.4.1           11/ 8/2023  KN      Improvement : Warning MISRA-C-Rule7.2 was fixed.                                             */
/*                                                                                                                                   */
/*  * KM      = Kazuyuki Makino, Denso Create                                                                                        */
/*  * KS      = Kenichi Sakai, Denso Create                                                                                          */
/*  * HK      = Hayato Kanamori, Denso Create                                                                                        */
/*  * KN      = Keigo Nomura   , Denso Create                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
