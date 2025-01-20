/* 1.2.8 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Nvmc : Data Checker                                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NVMC_DCK_C_MAJOR                         (1U)
#define NVMC_DCK_C_MINOR                         (2U)
#define NVMC_DCK_C_PATCH                         (8U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include "memfill_u1.h"
#include "memfill_u4.h"

#include "nvmc_mgr_private.h"

#include "nvmc_dck_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((NVMC_DCK_C_MAJOR != NVMC_DCK_H_MAJOR) || \
     (NVMC_DCK_C_MINOR != NVMC_DCK_H_MINOR) || \
     (NVMC_DCK_C_PATCH != NVMC_DCK_H_PATCH))
#error "nvmc_dck.c and nvmc_dck_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct
{
    U1  u1_ret;
    U1  u1_data_loc;
}ST_NVMC_DCK_ACT;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NVMC_DCK_ACT_BIT_SHFT_MAX                (32U)
#define NVMC_DCK_ACT_OK_DATA_SHFT                (0xFFU)
#define NVMC_DCK_FAIL_VAL_NON                    (0xFFU)
#define NVMC_DCK_SUPPORT_SIZE_MAX                (NVMC_SIZE_4BYTE)

#define NVMC_DCK_ARRAY_INDEX_MASK                (3U)
#define NVMC_DCK_ARRAY_INDEX_SHIFT               (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_NVMC_DCK_ACT st_sp_NVMC_DCK_ACT_TBL[NVMC_DCK_ERR_ACT_NUM] = {
    {(U1)NVMC_DCK_RSLT_NG,          (U1)NVMC_DCK_FAIL_VAL_DEF   },      /* NVMC_DCK_ERR_ACT_DEFAULT  */
    {(U1)NVMC_DCK_RSLT_NG,          (U1)NVMC_DCK_FAIL_VAL_MIN   },      /* NVMC_DCK_ERR_ACT_MIN      */
    {(U1)NVMC_DCK_RSLT_NG,          (U1)NVMC_DCK_FAIL_VAL_MAX   },      /* NVMC_DCK_ERR_ACT_MAX      */
    {(U1)NVMC_DCK_RSLT_NG_LAST,     (U1)NVMC_DCK_FAIL_VAL_NON   },      /* NVMC_DCK_ERR_ACT_LAST     */
    {(U1)NVMC_DCK_RSLT_NG_WRDATA,   (U1)NVMC_DCK_FAIL_VAL_NON   },      /* NVMC_DCK_ERR_ACT_WRITE    */
    {(U1)NVMC_DCK_RSLT_NG,          (U1)NVMC_DCK_FAIL_VAL_NON   },      /* NVMC_DCK_ERR_ACT_READ     */
    {(U1)NVMC_DCK_RSLT_NG,          (U1)NVMC_DCK_FAIL_VAL_DEF   },      /* Reserved                  */
    {(U1)NVMC_DCK_RSLT_NG,          (U1)NVMC_DCK_FAIL_VAL_DEF   }       /* Reserved                  */
};

static const U1             u1_sp_NVMC_DCK_ACT_BIT_LOC[NVMC_MOD_RSLT_NUM] = {
    (U1)NVMC_DCK_ACT_OK_DATA_SHFT,              /* NVMC_MOD_RSLT_OK          */
    (U1)NVMC_DCK_ACT_NG_SHFT,                   /* NVMC_MOD_RSLT_NG          */
    (U1)NVMC_DCK_ACT_OK_DATA_SHFT,              /* NVMC_MOD_RSLT_NODATA      */
    (U1)NVMC_DCK_ACT_LOST_SHFT,                 /* NVMC_MOD_RSLT_LOST        */
    (U1)NVMC_DCK_ACT_RDN_NG_SHFT,               /* NVMC_MOD_RSLT_RDN_NG      */
    (U1)NVMC_DCK_ACT_RANGEOUT_SHFT,             /* NVMC_MOD_RSLT_RANGEOUT    */
    (U1)NVMC_DCK_ACT_UNMATCH_SHFT               /* NVMC_MOD_RSLT_UNMATCH     */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1   u1_s_Nvmc_DCK_ChkTypiSizeData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_databuf, const U1 u1_a_SIZE, const U1 u1_a_STATUS);
static U1   u1_s_Nvmc_DCK_ChkOtherSizeData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_databuf, const U1 u1_a_SIZE, const U1 u1_a_STATUS);
static U1   u1_s_Nvmc_DCK_ChkRange(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const U4 u4_a_DATA, const U1 u1_a_SIZE);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_d_Nvmc_DCK_SetDefaultData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_data, const U1 u1_a_SIZE)           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> st_ap_CFGDATA  : Data configuraiton                                                                          */
/*                  --> *u4_ap_data    : Data Pointer                                                                                */
/*                  --> u1_a_SIZE      : Size                                                                                        */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_d_Nvmc_DCK_SetDefaultData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_data, const U1 u1_a_SIZE)
{
    if(u1_a_SIZE <= (U1)NVMC_DCK_SUPPORT_SIZE_MAX){
        /* Even if size is 0, default value is set. */
        /* This case would not happen and u4_ap_data is not valid even if size is zero. */
        *u4_ap_data = st_ap_CFGDATA->u4_p_val[NVMC_DCK_FAIL_VAL_DEF];
    }
    else{
        vd_g_MemfillU1((U1 *)u4_ap_data, (U1)0U, (U4)u1_a_SIZE);         /* QAC : Intentional pointer cast */
    }
}

/*===================================================================================================================================*/
/*  U1      u1_d_Nvmc_DCK_ChkReadData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_databuf, const U1 u1_a_SIZE, const U1 u1_a_STATUS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> st_ap_CFGDATA  : Data configuraiton                                                                          */
/*                  --> *u4_ap_databuf : Data Pointer                                                                                */
/*                  --> u1_a_SIZE      : Size                                                                                        */
/*                  --> u1_a_STATUS    : Status                                                                                      */
/*  Return:         U1 u1_t_ret : Status                                                                                             */
/*===================================================================================================================================*/
U1      u1_d_Nvmc_DCK_ChkReadData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_databuf, const U1 u1_a_SIZE, const U1 u1_a_STATUS)
{
    U1  u1_t_ret;

    if(u1_a_SIZE <= (U1)NVMC_DCK_SUPPORT_SIZE_MAX){
        u1_t_ret = u1_s_Nvmc_DCK_ChkTypiSizeData(st_ap_CFGDATA, u4_ap_databuf, u1_a_SIZE, u1_a_STATUS);
    }
    else{
        u1_t_ret = u1_s_Nvmc_DCK_ChkOtherSizeData(st_ap_CFGDATA, u4_ap_databuf, u1_a_SIZE, u1_a_STATUS);
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_d_Nvmc_DCK_ChkDataRange(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const U4 * const u4_ap_DATA, const U1 u1_a_SIZE) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> st_ap_CFGDATA : Data configuraiton                                                                           */
/*                  --> u4_ap_DATA    : Data                                                                                         */
/*                  --> u1_a_SIZE     : Size                                                                                         */
/*  Return:         U1 u1_t_ret : TRUE / FALSE                                                                                       */
/*===================================================================================================================================*/
U1      u1_d_Nvmc_DCK_ChkDataRange(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const U4 * const u4_ap_DATA, const U1 u1_a_SIZE)
{
    U1                  u1_t_ret;

    u1_t_ret = (U1)TRUE;                /* Default is TRUE for other size type. */
    if(u1_a_SIZE <= (U1)NVMC_DCK_SUPPORT_SIZE_MAX){
        u1_t_ret = u1_s_Nvmc_DCK_ChkRange(st_ap_CFGDATA, u4_ap_DATA[0], u1_a_SIZE);
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
/*  static U1   u1_s_Nvmc_DCK_ChkTypiSizeData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_databuf, const U1 u1_a_SIZE, const U1 u1_a_STATUS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> st_ap_CFGDATA  : Data configuraiton                                                                          */
/*                  --> *u4_ap_databuf : Data Pointer                                                                                */
/*                  --> u1_a_SIZE      : Size                                                                                        */
/*                  --> u1_a_STATUS    : Status                                                                                      */
/*  Return:         U1 u1_t_ret : Status                                                                                             */
/*===================================================================================================================================*/
static U1   u1_s_Nvmc_DCK_ChkTypiSizeData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_databuf, const U1 u1_a_SIZE, const U1 u1_a_STATUS)
{
    U4  u4_t_act;
    U1  u1_t_ret;
    U1  u1_t_rslt;
    U1  u1_t_bit_shft;
    U1  u1_t_data_type;

    u1_t_ret = (U1)NVMC_DCK_RSLT_NG;
    if(u1_a_STATUS < (U1)NVMC_MOD_RSLT_NUM){
        u1_t_bit_shft = u1_sp_NVMC_DCK_ACT_BIT_LOC[u1_a_STATUS];
        if(u1_t_bit_shft < (U1)NVMC_DCK_ACT_BIT_SHFT_MAX){
            u4_t_act = (st_ap_CFGDATA->u4_module_bit_cfg >> u1_t_bit_shft) & (U4)NVMC_DCK_ACT_MASK;
            if(u4_t_act == (U4)NVMC_DCK_ERR_ACT_READ){
                u1_t_rslt = u1_s_Nvmc_DCK_ChkRange(st_ap_CFGDATA, *u4_ap_databuf, u1_a_SIZE);
                if(u1_t_rslt != (U1)TRUE){
                    u4_t_act = (st_ap_CFGDATA->u4_module_bit_cfg >> NVMC_DCK_ACT_RANGEOUT_SHFT) & (U4)NVMC_DCK_ACT_MASK;
                }
            }
            u1_t_ret = st_sp_NVMC_DCK_ACT_TBL[u4_t_act].u1_ret;
            u1_t_data_type = st_sp_NVMC_DCK_ACT_TBL[u4_t_act].u1_data_loc;
            if(u1_t_data_type < (U1)NVMC_DCK_FAIL_VAL_NUM){
                u4_ap_databuf[0] = st_ap_CFGDATA->u4_p_val[u1_t_data_type];
            }
            else if(u1_t_data_type == (U1)NVMC_DCK_FAIL_VAL_NON){
                /* No update u4_ap_databuf */
            }
            else{
                /* In case of undefined value */
                u4_ap_databuf[0] = st_ap_CFGDATA->u4_p_val[NVMC_DCK_FAIL_VAL_DEF];
            }
        }
        else{
            u1_t_ret = (U1)NVMC_DCK_RSLT_OK;
            /* No update u4_ap_databuf */
        }
    }
    else{
        u4_ap_databuf[0] = st_ap_CFGDATA->u4_p_val[NVMC_DCK_FAIL_VAL_DEF];
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1   u1_s_Nvmc_DCK_ChkOtherSizeData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_databuf, const U1 u1_a_SIZE, const U1 u1_a_STATUS) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> st_ap_CFGDATA  : Data configuraiton                                                                          */
/*                  --> *u4_ap_databuf : Data Pointer                                                                                */
/*                  --> u1_a_SIZE      : Size                                                                                        */
/*                  --> u1_a_STATUS    : Status                                                                                      */
/*  Return:         U1 u1_t_ret : Status                                                                                             */
/*===================================================================================================================================*/
static U1   u1_s_Nvmc_DCK_ChkOtherSizeData(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, U4 * u4_ap_databuf, const U1 u1_a_SIZE, const U1 u1_a_STATUS)
{
    U4  u4_t_fill_size;
    U4  u4_t_act;
    U1  u1_t_ret;
    U1  u1_t_bit_shft;
    U1  u1_t_data_type;
    U1  u1_t_clear_data;

    u1_t_clear_data = (U1)FALSE;
    u1_t_ret = (U1)NVMC_DCK_RSLT_NG;
    if(u1_a_STATUS < (U1)NVMC_MOD_RSLT_NUM){
        u1_t_bit_shft = u1_sp_NVMC_DCK_ACT_BIT_LOC[u1_a_STATUS];
        if(u1_t_bit_shft < (U1)NVMC_DCK_ACT_BIT_SHFT_MAX){
            u4_t_act = (st_ap_CFGDATA->u4_module_bit_cfg >> u1_t_bit_shft) & (U4)NVMC_DCK_ACT_MASK;
            u1_t_ret = st_sp_NVMC_DCK_ACT_TBL[u4_t_act].u1_ret;
            u1_t_data_type = st_sp_NVMC_DCK_ACT_TBL[u4_t_act].u1_data_loc;
            if(u1_t_data_type != (U1)NVMC_DCK_FAIL_VAL_NON){
                u1_t_clear_data = (U1)TRUE;
            }
        }
        else{
            u1_t_ret = (U1)NVMC_DCK_RSLT_OK;
            /* No update u4_ap_databuf */
        }
    }
    else{
        u1_t_clear_data = (U1)TRUE;
    }
    if(u1_t_clear_data == (U1)TRUE){
        u4_t_fill_size = ((U4)u1_a_SIZE + (U4)NVMC_DCK_ARRAY_INDEX_MASK) >> NVMC_DCK_ARRAY_INDEX_SHIFT;
        vd_g_MemfillU4(u4_ap_databuf, (U4)0U, u4_t_fill_size);
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1   u1_s_Nvmc_DCK_ChkRange(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const U4 u4_a_DATA, const U1 u1_a_SIZE)          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> st_ap_CFGDATA   : Data configuraiton                                                                         */
/*                  --> u4_a_DATA       : Checked Data                                                                               */
/*                  --> u1_a_SIZE       : Size                                                                                       */
/*  Return:         U1 u1_t_ret : TRUE (Withing the range) / FALSE (Out of range)                                                    */
/*===================================================================================================================================*/
static U1   u1_s_Nvmc_DCK_ChkRange(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const U4 u4_a_DATA, const U1 u1_a_SIZE)
{
    const   U4  *   u4_tp_range_val;
            S4      s4_t_work;
            U4      u4_t_signed;
            U1      u1_t_ret;

    u1_t_ret = (U1)TRUE;
    u4_tp_range_val = &(st_ap_CFGDATA->u4_p_val[0]);
    u4_t_signed = st_ap_CFGDATA->u4_module_bit_cfg & (U4)NVMC_DATA_ATTR_BIT_SIGNED;
    if(u4_t_signed == (U4)0U){
        /* Unsigned data */
        if(
            (u4_tp_range_val[NVMC_DCK_FAIL_VAL_MIN] > u4_a_DATA) ||
            (u4_tp_range_val[NVMC_DCK_FAIL_VAL_MAX] < u4_a_DATA)
        ){
            u1_t_ret = (U1)FALSE;
        }
    }
    else{
        /* Signed data */
        switch(u1_a_SIZE){
            case NVMC_SIZE_1BYTE:
                s4_t_work = (S4)((S1)u4_a_DATA);
                break;
            case NVMC_SIZE_2BYTE:
                s4_t_work = (S4)((S2)u4_a_DATA);
                break;
            case NVMC_SIZE_4BYTE:
                s4_t_work = (S4)u4_a_DATA;
                break;
            default:
                s4_t_work = (S4)u4_a_DATA;
                u1_t_ret = (U1)FALSE;
                break;
        }
        if(
            ((S4)(u4_tp_range_val[NVMC_DCK_FAIL_VAL_MIN]) > s4_t_work) ||
            ((S4)(u4_tp_range_val[NVMC_DCK_FAIL_VAL_MAX]) < s4_t_work)
        ){
            u1_t_ret = (U1)FALSE;
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
/*  1.0.0            8/31/2015  KM      New.                                                                                         */
/*  1.1.0            9/29/2015  KM      Support other size                                                                           */
/*  1.2.0           10/ 7/2015  KM      Update & Bug fix.                                                                            */
/*  1.2.1           10/21/2015  KM      Bug fix.                                                                                     */
/*  1.2.2            1/ 8/2016  KM      vd_d_Nvmc_DCK_SetErrData() name was changed to vd_d_Nvmc_DCK_SetDefaultData().               */
/*                                      u1_d_Nvmc_DCK_ChkDataRange() name was changed to u1_s_Nvmc_DCK_ChkRange().                   */
/*  1.2.3            4/11/2016  HK      Fixed function comments.                                                                     */
/*  1.2.4            4/12/2016  KM      Deleted unnecessary include.                                                                 */
/*  1.2.5            5/16/2016  HK      Fixed PCS3-2 issue.                                                                          */
/*  1.2.6           11/10/2016  HK      Fixed AIP3GBSW-10 issue.                                                                     */
/*  1.2.7            8/22/2017  HK      Fixed AIP3GBSW-146 issue.                                                                    */
/*  1.2.8           11/ 8/2023  KN      Improvement : Warning MISRA-C-Rule7.2 was fixed.                                             */
/*                                                                                                                                   */
/*  * KM      = Kazuyuki Makino, Denso Create                                                                                        */
/*  * HK      = Hayato Kanamori, Denso Create                                                                                        */
/*  * KN      = Keigo Nomura   , Denso Create                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
