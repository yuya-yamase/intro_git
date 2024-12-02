/* 1.4.6 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Nvmc : Module Lib                                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NVMC_MOD_LIB_C_MAJOR                     (1U)
#define NVMC_MOD_LIB_C_MINOR                     (4U)
#define NVMC_MOD_LIB_C_PATCH                     (6U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "nvmc_mgr_cfg_private.h"   /* #include "aip_common.h"               */
                                    /* #include "nvmc_mgr_private.h"         */
                                    /* #include "nvmc_mgr.h"                 */
                                    /* #include "nvmc_mgr_cfg.h"             */
                                    /* #include "nvmc_mgr_acstask_private.h" */
                                    /* #include "rim_ctl.h"                  */
                                    /* #include "rim_ctl_cfg.h"              */
#include "nvmc_mod_lib_private.h"

#include "trpl_rdndnt.h"
#include "bitcnt.h"


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((NVMC_MOD_LIB_C_MAJOR != NVMC_MOD_LIB_H_MAJOR) || \
     (NVMC_MOD_LIB_C_MINOR != NVMC_MOD_LIB_H_MINOR) || \
     (NVMC_MOD_LIB_C_PATCH != NVMC_MOD_LIB_H_PATCH))
#error "nvmc_mod_lib.c and nvmc_mod_lib_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U4  u4_mask;
    U1  u1_shift;
}ST_NVMC_LIB_POSITION;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NVMC_MOD_LIB_1ST_DATA                    (0U)
#define NVMC_MOD_LIB_2ND_DATA                    (1U)
#define NVMC_MOD_LIB_3RD_DATA                    (2U)
#define NVMC_MOD_LIB_DATA_SIZE                   (3U)

#define NVMC_MOD_LIB_7BIT_MASK                   (0x0000007FU)
#define NVMC_MOD_LIB_7BIT_ON_NUM                 (4U)

#define NVMC_MOD_LIB_3BIT_SIGN_BITVAL            (8U)
#define NVMC_MOD_LIB_3BIT_SIGN_SHIFT             (5U)
#define NVMC_MOD_LIB_3BIT_ABS_MASK               (0x1FU)
#define NVMC_MOD_LIB_3BIT_SIGN_MASK              (0xE0U)

#define NVMC_MOD_LIB_TRPL_RDN_NUM                (3U)

#define NVMC_MOD_LIB_POS_NUM                     (7U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4   u4_s_NvmcMod_Lib_GetMaxData(const U4 * const u4_ap_DATA, const U1 u1_a_SIZE, const U4 u4_a_SIGN);
static U4   u4_s_NvmcMod_Lib_GetMinData(const U4 * const u4_ap_DATA, const U1 u1_a_SIZE, const U4 u4_a_SIGN);
static void vd_s_NvmcMod_Lib_ConvrtSignedData(const U4 * const u4_ap_DATA, S4 * s4_ap_conv_data, const U1 u1_a_SIZE);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_NVMC_LIB_POSITION  st_dp_NVMC_LIB_POSITION_TBL[NVMC_MOD_LIB_POS_NUM] = {
    {(U4)0xFFFFFFFFU,    (U1)0U   },  /* NVMC_MOD_LIB_POS_ALL */
    {(U4)0x0000FFFFU,    (U1)0U   },  /* NVMC_MOD_LIB_POS_LO  */
    {(U4)0x0000FFFFU,    (U1)16U  },  /* NVMC_MOD_LIB_POS_HI  */
    {(U4)0x000000FFU,    (U1)0U   },  /* NVMC_MOD_LIB_POS_P1  */
    {(U4)0x000000FFU,    (U1)8U   },  /* NVMC_MOD_LIB_POS_P2  */
    {(U4)0x000000FFU,    (U1)16U  },  /* NVMC_MOD_LIB_POS_P3  */
    {(U4)0x000000FFU,    (U1)24U  }   /* NVMC_MOD_LIB_POS_P4  */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U1      u1_d_NvmcMod_Lib_StatusCheck(const U1 u1_a_RDN_NUM, const U1 u1_a_SIZE, const U1 * const u1_ap_STATUS)                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u1_a_RDN_NUM  : RDN num                                                                                      */
/*                  --> u1_a_SIZE     : Data Size                                                                                    */
/*                  --> *u1_ap_STATUS : Read Status                                                                                  */
/*  Return:         U1 u1_t_sts_bit   : Sts                                                                                          */
/*===================================================================================================================================*/
U1   u1_d_NvmcMod_Lib_StatusCheck(const U1 u1_a_RDN_NUM, const U1 u1_a_SIZE, const U1 * const u1_ap_STATUS)
{
    U2  u2_t_num;
    U2  u2_t_size_num;
    U1  u1_t_sts_bit;
    U1  u1_t_data_sts;
    U1  u1_t_rdn;

    if(u1_a_SIZE > (U1)0U){
        u1_t_sts_bit = (U1)0U;
        u2_t_num = (U2)0U;
        u2_t_size_num = (U2)0U;
        for(u1_t_rdn = (U1)0U; u1_t_rdn < u1_a_RDN_NUM; u1_t_rdn++){
            u2_t_size_num += (U2)u1_a_SIZE;
            do{
                u1_t_data_sts = u1_ap_STATUS[u2_t_num];
                if(u1_t_data_sts == (U1)NVMC_RESULT_OK){
                    /* Nothing to do */
                }
                else if(u1_t_data_sts == (U1)NVMC_RESULT_NODATA){
                    u1_t_sts_bit |= (U1)((U1)1U << u1_t_rdn);
                }
                else{
                    u1_t_sts_bit = (U1)NVMC_MOD_LIB_STS_NG;
                    break;
                }
                u2_t_num++;
            }while(u2_t_num < u2_t_size_num);
        }
    }
    else{
        u1_t_sts_bit = (U1)NVMC_MOD_LIB_STS_NG;
    }
    return(u1_t_sts_bit);
}

/*===================================================================================================================================*/
/*  U4   u4_d_NvmcMod_Lib_GetRdunErrorValue(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const U4 * const u4_ap_DATA)                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_CFGDATA   : Data configuration                                                                        */
/*                  --> *u4_ap_DATA      : Original data                                                                             */
/*  Return:         U4 u4_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
U4   u4_d_NvmcMod_Lib_GetRdunErrorValue(const ST_NVMC_CFGDATA * const st_ap_CFGDATA, const U4 * const u4_ap_DATA)
{
    U4  u4_t_ret;
    U4  u4_t_def_type;
    U4  u4_t_sign;
    U1  u1_t_module;
    U1  u1_t_size;

    u4_t_def_type = st_ap_CFGDATA->u4_module_bit_cfg & (U4)NVMC_DATA_ATTR_RDNT_TYPE_MASK;
    /* In the case of RDNT_TYPE_BIT, this function is not executed. */
    /* Because it does not redundant error.                         */
    if(u4_t_def_type == (U4)NVMC_DATA_ATTR_RDNT_TYPE_1ST){
        /* To use the first data */
        u4_t_ret = u4_ap_DATA[NVMC_MOD_LIB_1ST_DATA];
    }
    else{
        u4_t_sign = st_ap_CFGDATA->u4_module_bit_cfg & (U4)NVMC_DATA_ATTR_BIT_SIGNED;
        u1_t_module = st_ap_CFGDATA->u1_map;
        u1_t_size = (U1)NVMC_SIZE_4BYTE;
        if(u1_t_module < u1_d_NVMC_MODULE_NUM){
            u1_t_size = st_dp_NVMC_MODULE_CFG[u1_t_module].u1_datasize;
        }

        if(u4_t_def_type == (U4)NVMC_DATA_ATTR_RDNT_TYPE_MIN){
            /* To use the min data */
            u4_t_ret = u4_s_NvmcMod_Lib_GetMinData(u4_ap_DATA, u1_t_size, u4_t_sign);
        }
        else{
            /* Other case          */
            /* To use the max data */
            u4_t_ret = u4_s_NvmcMod_Lib_GetMaxData(u4_ap_DATA, u1_t_size, u4_t_sign);
        }
    }
    return(u4_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_d_NvmcMod_Lib_Major7Bit(const U4 u4_a_DATA)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u4_a_DATA  : Data                                                                                            */
/*  Return:         U1 u1_t_ret : 1bit Data(TRUE / FALSE)                                                                            */
/*===================================================================================================================================*/
U1   u1_d_NvmcMod_Lib_Major7Bit(const U4 u4_a_DATA)
{
    U4  u4_t_temp;
    U1  u1_t_ret;
    U1  u1_t_bit;

    u4_t_temp = u4_a_DATA & (U4)NVMC_MOD_LIB_7BIT_MASK;
    u1_t_bit = u1_g_BitCnt(u4_t_temp);

    u1_t_ret = (U1)FALSE;
    if(u1_t_bit >= (U1)NVMC_MOD_LIB_7BIT_ON_NUM){
        u1_t_ret = (U1)TRUE;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  S1      s1_d_NvmcMod_Lib_Major3BitSign(const U1 u1_a_DATA)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u1_a_DATA  : Data                                                                                            */
/*  Return:         S1 s1_t_ret : S1 Data                                                                                            */
/*===================================================================================================================================*/
S1   s1_d_NvmcMod_Lib_Major3BitSign(const U1 u1_a_DATA)
{
    static const S1 s1_sp_NVMC_MOD_LIB_3BSIGN_TBL[NVMC_MOD_LIB_3BIT_SIGN_BITVAL] = {
        (S1)-1, /* 000b */
        (S1)-1, /* 001b */
        (S1)-1, /* 010b */
        (S1)1,  /* 011b */
        (S1)-1, /* 100b */
        (S1)1,  /* 101b */
        (S1)1,  /* 110b */
        (S1)1   /* 111b */
    };
    S1  s1_t_ret;
    S1  s1_t_sign;
    U1  u1_t_temp;

    s1_t_ret = (S1)((U1)(u1_a_DATA & (U1)NVMC_MOD_LIB_3BIT_ABS_MASK));

    u1_t_temp = u1_a_DATA >> NVMC_MOD_LIB_3BIT_SIGN_SHIFT;
    s1_t_sign = s1_sp_NVMC_MOD_LIB_3BSIGN_TBL[u1_t_temp];
    s1_t_ret *= s1_t_sign;

    return(s1_t_ret);
}

/*===================================================================================================================================*/
/*  U1   u1_d_NvmcMod_Lib_Get3BitSign(const S1 s1_a_DATA)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> s1_a_DATA  : Data                                                                                            */
/*  Return:         U1 u1_t_ret : 3BitSign Data                                                                                      */
/*===================================================================================================================================*/
U1   u1_d_NvmcMod_Lib_Get3BitSign(const S1 s1_a_DATA)
{
    U1  u1_t_ret;

    if(s1_a_DATA < (S1)0){
        u1_t_ret  = (U1)(-s1_a_DATA);
        u1_t_ret &= (U1)NVMC_MOD_LIB_3BIT_ABS_MASK;     /* Sign bit Clear(minus)    */
    }
    else{
        u1_t_ret  = (U1)s1_a_DATA;
        u1_t_ret |= (U1)NVMC_MOD_LIB_3BIT_SIGN_MASK;    /* Sign bit Set(plus)       */
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  S1      s1_d_NvmcMod_Lib_DblRdn_Sign(const S1 * const s1_ap_DATA)                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> s1_ap_DATA  : Data                                                                                           */
/*  Return:         S1 s1_t_ret : S1 Data                                                                                            */
/*===================================================================================================================================*/
S1   s1_d_NvmcMod_Lib_DblRdn_Sign(const S1 * const s1_ap_DATA)
{
    S1  s1_t_ret;
    S1  s1_t_temp;
    U1  u1_t_abs1;
    U1  u1_t_abs2;

    s1_t_ret  = s1_ap_DATA[NVMC_MOD_LIB_1ST_DATA];
    s1_t_temp = s1_ap_DATA[NVMC_MOD_LIB_2ND_DATA];
    if(s1_t_ret != s1_t_temp){
        if(s1_t_ret < (S1)0){
            u1_t_abs1 = (U1)(-s1_t_ret);
        }
        else{
            u1_t_abs1 = (U1)s1_t_ret;
        }
        if(s1_t_temp < (S1)0){
            u1_t_abs2 = (U1)(-s1_t_temp);
        }
        else{
            u1_t_abs2 = (U1)s1_t_temp;
        }

        if(
            ((u1_t_abs1 == u1_t_abs2) && (s1_t_ret < (S1)0)) ||
            (u1_t_abs1 > u1_t_abs2)
        ){
            s1_t_ret = s1_t_temp;
        }
    }

    return(s1_t_ret);
}

/*===================================================================================================================================*/
/*  S1      s1_d_NvmcMod_Lib_TrplRdn_Sign(const S1 * const s1_ap_DATA)                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> s1_ap_DATA  : Data                                                                                           */
/*  Return:         S1 s1_t_ret : S1 Data                                                                                            */
/*===================================================================================================================================*/
S1   s1_d_NvmcMod_Lib_TrplRdn_Sign(const S1 * const s1_ap_DATA)
{
    U4  u4_t_rdn[NVMC_MOD_LIB_TRPL_RDN_NUM];
    U4  u4_t_temp;
    S1  s1_t_ret;
    U1  u1_t_abs[NVMC_MOD_LIB_TRPL_RDN_NUM];
    U1  u1_t_cnt;
    U1  u1_t_rdn_rslt;
    U1  u1_t_min;

    for(u1_t_cnt = (U1)0U; u1_t_cnt < (U1)NVMC_MOD_LIB_TRPL_RDN_NUM; u1_t_cnt++){
        u4_t_rdn[u1_t_cnt] = (U4)((U1)s1_ap_DATA[u1_t_cnt]);
    }

    u1_t_rdn_rslt = u1_g_TrplRdndntchk(&u4_t_rdn[0], &u4_t_temp);
    if(u1_t_rdn_rslt != (U1)0U){
        s1_t_ret = (S1)u4_t_temp;
    }
    else{
        for(u1_t_cnt = (U1)0U; u1_t_cnt < (U1)NVMC_MOD_LIB_TRPL_RDN_NUM; u1_t_cnt++){
            if(s1_ap_DATA[u1_t_cnt] < (S1)0){
                u1_t_abs[u1_t_cnt] = (U1)(-s1_ap_DATA[u1_t_cnt]);
            }
            else{
                u1_t_abs[u1_t_cnt] = (U1)s1_ap_DATA[u1_t_cnt];
            }
        }

        u1_t_min = (U1)NVMC_MOD_LIB_1ST_DATA;
        if(
            ((u1_t_abs[u1_t_min] == u1_t_abs[NVMC_MOD_LIB_2ND_DATA]) && (s1_ap_DATA[u1_t_min] < (S1)0)) ||
            (u1_t_abs[u1_t_min] > u1_t_abs[NVMC_MOD_LIB_2ND_DATA])
        ){
            u1_t_min = (U1)NVMC_MOD_LIB_2ND_DATA;
        }
        if(
            ((u1_t_abs[u1_t_min] == u1_t_abs[NVMC_MOD_LIB_3RD_DATA]) && (s1_ap_DATA[u1_t_min] < (S1)0)) ||
            (u1_t_abs[u1_t_min] > u1_t_abs[NVMC_MOD_LIB_3RD_DATA])
        ){
            u1_t_min = (U1)NVMC_MOD_LIB_3RD_DATA;
        }

        s1_t_ret = (S1)u4_t_rdn[u1_t_min];
    }

    return(s1_t_ret);
}

/*===================================================================================================================================*/
/*  U4   u4_d_NvmcMod_Lib_ConvMapToData(const U4 u4_a_DATA, const U1 u1_a_POS)                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u4_a_DATA  : Data                                                                                            */
/*  Arguments:      --> u1_a_POS   : Position                                                                                        */
/*  Return:         U4 u4_t_ret : Shift                                                                                              */
/*===================================================================================================================================*/
U4   u4_d_NvmcMod_Lib_ConvMapToData(const U4 u4_a_DATA, const U1 u1_a_POS)
{
    U4  u4_t_ret;
    U4  u4_t_mask;
    U1  u1_t_index;
    U1  u1_t_shift;

    u1_t_index = (U1)NVMC_MOD_LIB_POS_ALL;
    if(u1_a_POS < (U1)NVMC_MOD_LIB_POS_NUM){
        u1_t_index = u1_a_POS;
    }

    u1_t_shift = st_dp_NVMC_LIB_POSITION_TBL[u1_t_index].u1_shift;
    u4_t_mask  = st_dp_NVMC_LIB_POSITION_TBL[u1_t_index].u4_mask;

    u4_t_ret = (u4_a_DATA >> u1_t_shift) & u4_t_mask;

    return(u4_t_ret);
}

/*===================================================================================================================================*/
/*  U4   u4_d_NvmcMod_Lib_ConvDataToMap(const U4 u4_a_DATA, const U1 u1_a_POS)                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u4_a_DATA : Data                                                                                             */
/*  Arguments:      --> u1_a_POS   : Position                                                                                        */
/*  Return:         U4 u4_t_ret : Shift                                                                                              */
/*===================================================================================================================================*/
U4   u4_d_NvmcMod_Lib_ConvDataToMap(const U4 u4_a_DATA, const U1 u1_a_POS)
{
    U4  u4_t_ret;
    U4  u4_t_mask;
    U1  u1_t_index;
    U1  u1_t_shift;

    u1_t_index = (U1)NVMC_MOD_LIB_POS_ALL;
    if(u1_a_POS < (U1)NVMC_MOD_LIB_POS_NUM){
        u1_t_index = u1_a_POS;
    }

    u1_t_shift = st_dp_NVMC_LIB_POSITION_TBL[u1_t_index].u1_shift;
    u4_t_mask  = st_dp_NVMC_LIB_POSITION_TBL[u1_t_index].u4_mask;

    u4_t_ret = (u4_a_DATA & u4_t_mask) << u1_t_shift;

    return(u4_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_d_NvmcMod_Lib_PreRdnData(const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS, const U1 u1_a_BLOCKNUM)          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u4_ap_DATA    : Read Buffer                                                                                 */
/*                  --> *u1_ap_STATUS  : Status                                                                                      */
/*                  --> u1_a_BLOCKNUM  : Block Num                                                                                   */
/*  Return:         U1 u1_t_ret : Sts                                                                                                */
/*===================================================================================================================================*/
U1   u1_d_NvmcMod_Lib_PreRdnData(const U4 * const u4_ap_DATA, const U1 * const u1_ap_STATUS, const U1 u1_a_BLOCKNUM)
{
    U1  u1_t_ret;
    U1  u1_t_sts_bit;

    u1_t_ret = (U1)NVMC_MOD_RSLT_NG;

    u1_t_sts_bit = u1_d_NvmcMod_Lib_StatusCheck((U1)1U, u1_a_BLOCKNUM, u1_ap_STATUS);
    if(u1_t_sts_bit == (U1)0U){
        u1_t_ret = (U1)NVMC_MOD_RSLT_OK;
    }
    else if(u1_t_sts_bit == (U1)1U){
        u1_t_ret = (U1)NVMC_MOD_RSLT_NODATA;
    }
    else{
        /* u1_t_ret = (U1)NVMC_MOD_RSLT_NG; */
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
/*  static U4   u4_s_NvmcMod_Lib_GetMaxData(const U4 * const u4_ap_DATA, const U1 u1_a_SIZE, const U4 u4_a_SIGN)                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u4_ap_DATA     : Original data                                                                              */
/*                  --> u1_a_SIZE       : Size                                                                                       */
/*                  --> u4_a_SIGN       : Sign                                                                                       */
/*  Return:         U4 u4_t_ret : Max Value                                                                                          */
/*===================================================================================================================================*/
static U4   u4_s_NvmcMod_Lib_GetMaxData(const U4 * const u4_ap_DATA, const U1 u1_a_SIZE, const U4 u4_a_SIGN)
{
    U4  u4_t_ret;
    S4  s4_tp_data[NVMC_MOD_LIB_DATA_SIZE];
    S4  s4_t_temp_ret;

    if(u4_a_SIGN != (U4)0U){
        vd_s_NvmcMod_Lib_ConvrtSignedData(u4_ap_DATA, s4_tp_data, u1_a_SIZE);

        s4_t_temp_ret = s4_tp_data[NVMC_MOD_LIB_1ST_DATA];
        if(s4_t_temp_ret < s4_tp_data[NVMC_MOD_LIB_2ND_DATA]){
            s4_t_temp_ret = s4_tp_data[NVMC_MOD_LIB_2ND_DATA];
        }
        if(s4_t_temp_ret < s4_tp_data[NVMC_MOD_LIB_3RD_DATA]){
            s4_t_temp_ret = s4_tp_data[NVMC_MOD_LIB_3RD_DATA];
        }

        u4_t_ret = (U4)s4_t_temp_ret;
    }
    else{
        u4_t_ret = u4_ap_DATA[NVMC_MOD_LIB_1ST_DATA];
        if(u4_t_ret < u4_ap_DATA[NVMC_MOD_LIB_2ND_DATA]){
            u4_t_ret = u4_ap_DATA[NVMC_MOD_LIB_2ND_DATA];
        }
        if(u4_t_ret < u4_ap_DATA[NVMC_MOD_LIB_3RD_DATA]){
            u4_t_ret = u4_ap_DATA[NVMC_MOD_LIB_3RD_DATA];
        }
    }

    return(u4_t_ret);
}

/*===================================================================================================================================*/
/*  static U4   u4_s_NvmcMod_Lib_GetMinData(const U4 * const u4_ap_DATA, const U1 u1_a_SIZE, const U4 u4_a_SIGN)                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u4_ap_DATA     : Original data                                                                              */
/*                  --> u1_a_SIZE       : Size                                                                                       */
/*                  --> u4_a_SIGN       : Sign                                                                                       */
/*  Return:         U4 u4_t_ret : Min Value                                                                                          */
/*===================================================================================================================================*/
static U4   u4_s_NvmcMod_Lib_GetMinData(const U4 * const u4_ap_DATA, const U1 u1_a_SIZE, const U4 u4_a_SIGN)
{
    U4  u4_t_ret;
    S4  s4_tp_data[NVMC_MOD_LIB_DATA_SIZE];
    S4  s4_t_temp_ret;

    if(u4_a_SIGN != (U4)0U){
        vd_s_NvmcMod_Lib_ConvrtSignedData(u4_ap_DATA, s4_tp_data, u1_a_SIZE);

        s4_t_temp_ret = s4_tp_data[NVMC_MOD_LIB_1ST_DATA];
        if(s4_t_temp_ret > s4_tp_data[NVMC_MOD_LIB_2ND_DATA]){
            s4_t_temp_ret = s4_tp_data[NVMC_MOD_LIB_2ND_DATA];
        }
        if(s4_t_temp_ret > s4_tp_data[NVMC_MOD_LIB_3RD_DATA]){
            s4_t_temp_ret = s4_tp_data[NVMC_MOD_LIB_3RD_DATA];
        }

        u4_t_ret = (U4)s4_t_temp_ret;
    }
    else{
        u4_t_ret = u4_ap_DATA[NVMC_MOD_LIB_1ST_DATA];
        if(u4_t_ret > u4_ap_DATA[NVMC_MOD_LIB_2ND_DATA]){
            u4_t_ret = u4_ap_DATA[NVMC_MOD_LIB_2ND_DATA];
        }
        if(u4_t_ret > u4_ap_DATA[NVMC_MOD_LIB_3RD_DATA]){
            u4_t_ret = u4_ap_DATA[NVMC_MOD_LIB_3RD_DATA];
        }
    }

    return(u4_t_ret);
}

/*===================================================================================================================================*/
/*  static void vd_s_NvmcMod_Lib_ConvrtSignedData(const U4 * const u4_ap_DATA, S4 * s4_ap_conv_data, const U1 u1_a_SIZE)             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u4_ap_DATA     : Original data                                                                              */
/*                  --> s4_ap_conv_data : Converted data                                                                             */
/*                  --> u1_a_SIZE       : Size                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_NvmcMod_Lib_ConvrtSignedData(const U4 * const u4_ap_DATA, S4 * s4_ap_conv_data, const U1 u1_a_SIZE)
{
    switch(u1_a_SIZE)
    {
        case NVMC_SIZE_1BYTE:
            s4_ap_conv_data[NVMC_MOD_LIB_1ST_DATA] = (S4)((S1)u4_ap_DATA[NVMC_MOD_LIB_1ST_DATA]);
            s4_ap_conv_data[NVMC_MOD_LIB_2ND_DATA] = (S4)((S1)u4_ap_DATA[NVMC_MOD_LIB_2ND_DATA]);
            s4_ap_conv_data[NVMC_MOD_LIB_3RD_DATA] = (S4)((S1)u4_ap_DATA[NVMC_MOD_LIB_3RD_DATA]);
            break;
        case NVMC_SIZE_2BYTE:
            s4_ap_conv_data[NVMC_MOD_LIB_1ST_DATA] = (S4)((S2)u4_ap_DATA[NVMC_MOD_LIB_1ST_DATA]);
            s4_ap_conv_data[NVMC_MOD_LIB_2ND_DATA] = (S4)((S2)u4_ap_DATA[NVMC_MOD_LIB_2ND_DATA]);
            s4_ap_conv_data[NVMC_MOD_LIB_3RD_DATA] = (S4)((S2)u4_ap_DATA[NVMC_MOD_LIB_3RD_DATA]);
            break;
        /* case NVMC_SIZE_4BYTE: */
        default:
            s4_ap_conv_data[NVMC_MOD_LIB_1ST_DATA] = (S4)u4_ap_DATA[NVMC_MOD_LIB_1ST_DATA];
            s4_ap_conv_data[NVMC_MOD_LIB_2ND_DATA] = (S4)u4_ap_DATA[NVMC_MOD_LIB_2ND_DATA];
            s4_ap_conv_data[NVMC_MOD_LIB_3RD_DATA] = (S4)u4_ap_DATA[NVMC_MOD_LIB_3RD_DATA];
            break;
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
/*  1.0.0            8/17/2015  KM      New.                                                                                         */
/*  1.1.0           10/07/2015  MH      Added new function for calcurate minimum and maximum data.                                   */
/*  1.2.0           10/14/2015  KM      ADD Major7Bit, Major3BitSign                                                                 */
/*  1.2.1           10/20/2015  MH      Fixed s1_d_NvmcMod_Lib_TrplRdn_Sign logic issue.                                             */
/*  1.2.2           10/21/2015  KM      Bug fix.                                                                                     */
/*                              MH      Fixed QAC issue.                                                                             */
/*  1.2.3           10/22/2015  KM      Fixed QAC issue.                                                                             */
/*  1.2.4           11/18/2015  KS      The unnecessary function prottypes were deleted.                                             */
/*  1.2.5           11/19/2015  KM      Delete vd_d_NvmcMod_Lib_MemcpyRevU4.                                                         */
/*                                      Move vd_d_NvmcMod_Lib_PackRevU2toU4 to nvmc_mod_lib_oth.c.                                   */
/*  1.3.0            2/ 1/2016  KM      Added PreRead Process.                                                                       */
/*  1.3.1            3/24/2016  KM      Deleted NVMC_MOD_LIB_3BIT_SIGN_MASK.                                                         */
/*  1.3.2            3/25/2016  KM      Fixed Unit Test issue.                                                                       */
/*  1.3.3            3/28/2016  KM      Merged Version 1.3.1 and 1.3.2.                                                              */
/*  1.3.4            4/ 4/2016  KM      Fixed PCS3-2 issue.                                                                          */
/*  1.3.5            4/11/2016  HK      Fixed function comments.                                                                     */
/*  1.4.0            4/15/2016  KM      Added 3BitSign write Function.                                                               */
/*  1.4.1            4/18/2016  KM      Fixed u1_d_NvmcMod_Lib_Get3BitSign comments.                                                 */
/*  1.4.2            5/16/2016  HK      Fixed PCS3-2 issue.                                                                          */
/*  1.4.3            6/14/2016  KM      Fixed s1_d_NvmcMod_Lib_DblRdn_Sign and s1_d_NvmcMod_Lib_TrplRdn_Sign logic.                  */
/*  1.4.4           11/10/2016  HK      Fixed AIP3GBSW-6 issue.                                                                      */
/*  1.4.5            9/14/2021  TN      NULL -> vdp_PTR_NA.                                                                          */
/*  1.4.6           11/ 8/2023  KN      Improvement : Warning MISRA-C-Rule7.2 was fixed.                                             */
/*                                                                                                                                   */
/*  * TN      = Takashi Nagai, Denso                                                                                                 */
/*  * KM      = Kazuyuki Makino, Denso Create                                                                                        */
/*  * MH      = Masayuki Hattori, Denso                                                                                              */
/*  * HK      = Hayato Kanamori, Denso Create                                                                                        */
/*  * KN      = Keigo Nomura   , Denso Create                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
