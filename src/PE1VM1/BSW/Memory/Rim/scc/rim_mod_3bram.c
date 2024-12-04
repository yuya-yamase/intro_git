/* 1.3.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  RIM : MODULE_3BRAM                                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RIM_MOD_3BRAM_C_MAJOR                    (1U)
#define RIM_MOD_3BRAM_C_MINOR                    (3U)
#define RIM_MOD_3BRAM_C_PATCH                    (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "rim_ctl_cfg_private.h"
#include "rim_func_private.h"

#include "rim_mod_3bram_private.h"
#include "rim_mod_3bram_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((RIM_MOD_3BRAM_C_MAJOR != RIM_MOD_3BRAM_H_MAJOR) || \
     (RIM_MOD_3BRAM_C_MINOR != RIM_MOD_3BRAM_H_MINOR) || \
     (RIM_MOD_3BRAM_C_PATCH != RIM_MOD_3BRAM_H_PATCH))
#error "rim_mod_3bram.c and rim_mod_3bram_private.h : source and header files are inconsistent!"
#endif

#if ((RIM_MOD_3BRAM_C_MAJOR != RIM_MOD_3BRAM_CFG_PRIVATE_H_MAJOR) || \
     (RIM_MOD_3BRAM_C_MINOR != RIM_MOD_3BRAM_CFG_PRIVATE_H_MINOR) || \
     (RIM_MOD_3BRAM_C_PATCH != RIM_MOD_3BRAM_CFG_PRIVATE_H_PATCH))
#error "rim_mod_3bram.c and rim_mod_3bram_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U4 *   u4p_las_mai;
    U4 *   u4p_las_m_1;
    U4 *   u4p_las_m_2;

    U4 *   u4p_nex_mai;
    U4 *   u4p_nex_m_1;
    U4 *   u4p_nex_m_2;

    U4 *   u4p_sum_mai;
    U4 *   u4p_sum_m_1;
    U4 *   u4p_sum_m_2;
}ST_RIM_3BR_WK;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RIM_MOD_3BRAM_ERR_DATA_MAIN              (0xFFFFFFFFU)
#define RIM_MOD_3BRAM_ERR_DATA_MIRR1             (0x55555555U)
#define RIM_MOD_3BRAM_ERR_DATA_MIRR2             (0xAAAAAAAAU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RIM_MOD_3BRAM_WKU_MAI                    (0x04U)
#define RIM_MOD_3BRAM_WKU_M_1                    (0x02U)
#define RIM_MOD_3BRAM_WKU_M_2                    (0x01U)
#define RIM_MOD_3BRAM_WKU_ALL                    (0x07U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (__RIM_MOD_3BRAM_OTHER_USE__ == TRUE)
static U4            u4_sp_rim_3b_cpb_mai[RIM_MOD_3BRAM_OTHER_ID_MAXSIZE];
static U4            u4_sp_rim_3b_cpb_m_1[RIM_MOD_3BRAM_OTHER_ID_MAXSIZE];
static U4            u4_sp_rim_3b_cpb_m_2[RIM_MOD_3BRAM_OTHER_ID_MAXSIZE];
#endif  /* #if (__RIM_MOD_3BRAM_OTHER_USE__ == TRUE) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (__RIM_MOD_3BRAM_OTHER_USE__ == TRUE)
static void    vd_s_RimMod_3BRam_WkupInitOtr(const U4 u4_a_DATA_ID);

static void    vd_s_Rim_3BR_Wkuini_000(ST_RIM_3BR_WK * st_ap_3br_wk, const U2 u2_a_NLONG);
static void    vd_s_Rim_3BR_Wkuini_001(ST_RIM_3BR_WK * st_ap_3br_wk, const U2 u2_a_NLONG);
static void    vd_s_Rim_3BR_Wkuini_010(ST_RIM_3BR_WK * st_ap_3br_wk, const U2 u2_a_NLONG);
static void    vd_s_Rim_3BR_Wkuini_011(ST_RIM_3BR_WK * st_ap_3br_wk, const U2 u2_a_NLONG);
static void    vd_s_Rim_3BR_Wkuini_100(ST_RIM_3BR_WK * st_ap_3br_wk, const U2 u2_a_NLONG);
static void    vd_s_Rim_3BR_Wkuini_101(ST_RIM_3BR_WK * st_ap_3br_wk, const U2 u2_a_NLONG);
static void    vd_s_Rim_3BR_Wkuini_110(ST_RIM_3BR_WK * st_ap_3br_wk, const U2 u2_a_NLONG);

static U1      u1_s_RimMod_3BRam_WkupInitChk(const ST_RIM_3BR_WK * st_ap_3BR_WK, const U2 u2_a_NLONG);
static U1      u1_s_Rim_3BR_Wkuchk_011(const ST_RIM_3BR_WK * st_ap_3BR_WK, const U2 u2_a_NLONG);
static U1      u1_s_Rim_3BR_Wkuchk_101(const ST_RIM_3BR_WK * st_ap_3BR_WK, const U2 u2_a_NLONG);
static U1      u1_s_Rim_3BR_Wkuchk_110(const ST_RIM_3BR_WK * st_ap_3BR_WK, const U2 u2_a_NLONG);
static U1      u1_s_Rim_3BR_Wkuchk_111(const ST_RIM_3BR_WK * st_ap_3BR_WK, const U2 u2_a_NLONG);
#endif  /* #if (__RIM_MOD_3BRAM_OTHER_USE__ == TRUE) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static inline U2    u2_s_RimMod_3B_RId(const U2 u2_a_SIZE, const U2 u2_a_DATAID);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_d_RimMod_3BOth_Init(const U1 u1_a_WUI)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_d_RimMod_3BOth_Init(const U1 u1_a_WUI)
{
#if (__RIM_MOD_3BRAM_OTHER_USE__ == TRUE)
    U4                       u4_t_lpcnt;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)RIM_MOD_3BRAM_OTHER_ID_MAXSIZE; u4_t_lpcnt++){
        u4_sp_rim_3b_cpb_mai[u4_t_lpcnt] = (U4)0U;
        u4_sp_rim_3b_cpb_m_1[u4_t_lpcnt] = (U4)0U;
        u4_sp_rim_3b_cpb_m_2[u4_t_lpcnt] = (U4)0U;
    }

    if(u1_a_WUI == (U1)TRUE){
        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u2_d_RIM_MOD_3BRAM_OTR_ID_NUM; u4_t_lpcnt++){
            vd_s_RimMod_3BRam_WkupInitOtr(u4_t_lpcnt);
        }
    }
#endif  /* #if (__RIM_MOD_3BRAM_OTHER_USE__ == TRUE) */
}

/*===================================================================================================================================*/
/*  U1 u1_d_RimMod_3BRam_ReadU4(const U2 u2_a_ID, U4 *u4_ap_data)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_ID     : RimId                                                                                          */
/*                  --> *u4_ap_data : Read Data Pointer                                                                              */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1 u1_d_RimMod_3BRam_ReadU4(const U2 u2_a_ID, U4 *u4_ap_data)
{
    U2                       u2_t_rimsize;
    U2                       u2_t_dataid;
    U1                       u1_t_ret;

    u1_t_ret = (U1)RIM_RESULT_NG_PRM_ID;

    u2_t_rimsize = u2_g_RIM_GET_RIMSIZE(u2_a_ID);
    u2_t_dataid  = u2_a_ID & u2_d_RIM_MOD_3BRAM_DATA_ID_MASK;

    if(u2_t_rimsize == (U2)RIMID_RIMSIZE_1BYTE){
#if (__RIM_MOD_3BRAM_U1_USE__ == TRUE)
        if(u2_t_dataid < u2_d_RIM_MOD_3BRAM_U1_ID_NUM){
            u1_t_ret = u1_d_Rim_MajorityU1Data(u4_ap_data,
                                               &u1_dp_rimmod_3b_byte_main[u2_t_dataid],
                                               &u1_dp_rimmod_3b_byte_mirr1[u2_t_dataid],
                                               &u1_dp_rimmod_3b_byte_mirr2[u2_t_dataid]);
        }
        else{
            /* PRM:RIMID Error(DataId Error) */
        }
#endif  /* #if (__RIM_MOD_3BRAM_U1_USE__ == TRUE) */
    }
    else if(u2_t_rimsize == (U2)RIMID_RIMSIZE_2BYTE){
#if (__RIM_MOD_3BRAM_U2_USE__ == TRUE)
        if(u2_t_dataid < u2_d_RIM_MOD_3BRAM_U2_ID_NUM){
            u1_t_ret = u1_d_Rim_MajorityU2Data(u4_ap_data,
                                               &u2_dp_rimmod_3b_half_main[u2_t_dataid],
                                               &u2_dp_rimmod_3b_half_mirr1[u2_t_dataid],
                                               &u2_dp_rimmod_3b_half_mirr2[u2_t_dataid]);
        }
        else{
            /* PRM:RIMID Error(DataId Error) */
        }
#endif  /* #if (__RIM_MOD_3BRAM_U2_USE__ == TRUE) */
    }
    else if(u2_t_rimsize == (U2)RIMID_RIMSIZE_4BYTE){
#if (__RIM_MOD_3BRAM_U4_USE__ == TRUE)
        if(u2_t_dataid < u2_d_RIM_MOD_3BRAM_U4_ID_NUM){
            u1_t_ret = u1_d_Rim_MajorityU4Data(u4_ap_data,
                                               &u4_dp_rimmod_3b_word_main[u2_t_dataid],
                                               &u4_dp_rimmod_3b_word_mirr1[u2_t_dataid],
                                               &u4_dp_rimmod_3b_word_mirr2[u2_t_dataid]);
        }
        else{
            /* PRM:RIMID Error(DataId Error) */
        }
#endif  /* #if (__RIM_MOD_3BRAM_U4_USE__ == TRUE) */
    }
    else{
        /* PRM:RIMID Error(SIZE Error) */
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1 u1_d_RimMod_3BRam_WriteU4(const U2 u2_a_ID, const U4 u4_a_DATA)                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_ID   : RimId                                                                                            */
/*                  --> u4_a_DATA : Write Data                                                                                       */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1 u1_d_RimMod_3BRam_WriteU4(const U2 u2_a_ID, const U4 u4_a_DATA)
{
    U2                       u2_t_rimsize;
    U2                       u2_t_dataid;
    U1                       u1_t_ret;

    u1_t_ret = (U1)RIM_RESULT_NG_PRM_ID;

    u2_t_rimsize = u2_g_RIM_GET_RIMSIZE(u2_a_ID);
    u2_t_dataid  = u2_a_ID & u2_d_RIM_MOD_3BRAM_DATA_ID_MASK;

    if(u2_t_rimsize == (U2)RIMID_RIMSIZE_1BYTE){
#if (__RIM_MOD_3BRAM_U1_USE__ == TRUE)
        if(u2_t_dataid < u2_d_RIM_MOD_3BRAM_U1_ID_NUM){
            u1_dp_rimmod_3b_byte_main[u2_t_dataid]  = (U1)u4_a_DATA;
            u1_dp_rimmod_3b_byte_mirr1[u2_t_dataid] = (U1)u4_a_DATA;
            u1_dp_rimmod_3b_byte_mirr2[u2_t_dataid] = (U1)u4_a_DATA;

            u1_t_ret = (U1)RIM_RESULT_OK;
        }
        else{
            /* PRM:RIMID Error(DataId Error) */
        }
#endif  /* #if (__RIM_MOD_3BRAM_U1_USE__ == TRUE) */
    }
    else if(u2_t_rimsize == (U2)RIMID_RIMSIZE_2BYTE){
#if (__RIM_MOD_3BRAM_U2_USE__ == TRUE)
        if(u2_t_dataid < u2_d_RIM_MOD_3BRAM_U2_ID_NUM){
            u2_dp_rimmod_3b_half_main[u2_t_dataid]  = (U2)u4_a_DATA;
            u2_dp_rimmod_3b_half_mirr1[u2_t_dataid] = (U2)u4_a_DATA;
            u2_dp_rimmod_3b_half_mirr2[u2_t_dataid] = (U2)u4_a_DATA;

            u1_t_ret = (U1)RIM_RESULT_OK;
        }
        else{
            /* PRM:RIMID Error(DataId Error) */
        }
#endif  /* #if (__RIM_MOD_3BRAM_U2_USE__ == TRUE) */
    }
    else if(u2_t_rimsize == (U2)RIMID_RIMSIZE_4BYTE){
#if (__RIM_MOD_3BRAM_U4_USE__ == TRUE)
        if(u2_t_dataid < u2_d_RIM_MOD_3BRAM_U4_ID_NUM){
            u4_dp_rimmod_3b_word_main[u2_t_dataid]  = u4_a_DATA;
            u4_dp_rimmod_3b_word_mirr1[u2_t_dataid] = u4_a_DATA;
            u4_dp_rimmod_3b_word_mirr2[u2_t_dataid] = u4_a_DATA;

            u1_t_ret = (U1)RIM_RESULT_OK;
        }
        else{
            /* PRM:RIMID Error(DataId Error) */
        }
#endif  /* #if (__RIM_MOD_3BRAM_U4_USE__ == TRUE) */
    }
    else{
        /* PRM:RIMID Error(SIZE Error) */
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1 u1_d_RimMod_3BRam_ReadOther(const U2 u2_a_ID, const U2 u2_a_NBYTE, U1 *u1_ap_data)                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_ID     : RimId                                                                                          */
/*                  --> u2_a_NBYTE  : Size                                                                                           */
/*                  --> *u1_ap_data : Read Data Pointer                                                                              */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1 u1_d_RimMod_3BRam_ReadOther(const U2 u2_a_ID, const U2 u2_a_NBYTE, U1 *u1_ap_data)
{
#if (__RIM_MOD_3BRAM_OTHER_USE__ == TRUE)
    U4 *                     u4_tp_br_mai;
    U4 *                     u4_tp_br_m_1;
    U4 *                     u4_tp_br_m_2;

    U4                       u4_t_lpcnt;

    U2                       u2_t_dataid;
    U2                       u2_t_index;
    U2                       u2_t_nlong;

    U1                       u1_t_major;
    U1                       u1_t_ret;

    u2_t_dataid = u2_a_ID & u2_d_RIM_MOD_3BRAM_DATA_ID_MASK;
    if(u2_t_dataid >= u2_d_RIM_MOD_3BRAM_OTR_ID_NUM){
        /* PRM:RIMID Error(DataId Error) */
        u1_t_ret = (U1)RIM_RESULT_NG_PRM_ID;
    }
    else if(u2_a_NBYTE != st_d_RIM_MOD_3BRAM_OTR_SZ_CFG[u2_t_dataid].u2_size){
        /* PRM:Size Error */
        u1_t_ret = (U1)RIM_RESULT_NG_PRM_SIZE;
    }
    else{

        u2_t_index   = st_d_RIM_MOD_3BRAM_OTR_SZ_CFG[u2_t_dataid].u2_index;
        u2_t_nlong   = u2_d_RIM_CHGSIZE_U1_TO_U4(u2_a_NBYTE);

        u4_tp_br_mai = &u4_dp_rimmod_3b_oth_main[u2_t_index];
        u4_tp_br_m_1 = &u4_dp_rimmod_3b_oth_mirr1[u2_t_index];
        u4_tp_br_m_2 = &u4_dp_rimmod_3b_oth_mirr2[u2_t_index];

        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u2_t_nlong; u4_t_lpcnt++){
            u4_sp_rim_3b_cpb_mai[u4_t_lpcnt] = u4_tp_br_mai[u4_t_lpcnt];
            u4_sp_rim_3b_cpb_m_1[u4_t_lpcnt] = u4_tp_br_m_1[u4_t_lpcnt];
            u4_sp_rim_3b_cpb_m_2[u4_t_lpcnt] = u4_tp_br_m_2[u4_t_lpcnt];
        }

        u1_t_major = u1_d_Rim_MajorityByDataOther(&u4_sp_rim_3b_cpb_mai[0],
                                                  &u4_sp_rim_3b_cpb_m_1[0],
                                                  &u4_sp_rim_3b_cpb_m_2[0],
                                                  u2_t_nlong);
        if(u1_t_major == (U1)RIM_MAJOR_OK){

            vd_d_Rim_CopyU1(u1_ap_data, (U1*)(&u4_sp_rim_3b_cpb_mai[0]), u2_a_NBYTE);
            u1_t_ret = (U1)RIM_RESULT_OK;
        }
        else if(u1_t_major == (U1)RIM_MAJOR_NG_A){

            vd_d_Rim_CopyU4(u4_tp_br_mai, &u4_sp_rim_3b_cpb_m_1[0], u2_t_nlong);
            u4_dp_rimmod_3b_oth_cs_main[u2_t_dataid] = u4_dp_rimmod_3b_oth_cs_mirr1[u2_t_dataid];

            vd_d_Rim_CopyU1(u1_ap_data, (U1*)(&u4_sp_rim_3b_cpb_m_1[0]), u2_a_NBYTE);
            u1_t_ret = (U1)RIM_RESULT_OK_REPAIRED;
        }
        else if(u1_t_major == (U1)RIM_MAJOR_NG_B){

            vd_d_Rim_CopyU4(u4_tp_br_m_1, &u4_sp_rim_3b_cpb_mai[0], u2_t_nlong);
            u4_dp_rimmod_3b_oth_cs_mirr1[u2_t_dataid] = u4_dp_rimmod_3b_oth_cs_main[u2_t_dataid];

            vd_d_Rim_CopyU1(u1_ap_data, (U1*)(&u4_sp_rim_3b_cpb_mai[0]), u2_a_NBYTE);
            u1_t_ret = (U1)RIM_RESULT_OK_REPAIRED;
        }
        else if(u1_t_major == (U1)RIM_MAJOR_NG_C){

            vd_d_Rim_CopyU4(u4_tp_br_m_2, &u4_sp_rim_3b_cpb_mai[0], u2_t_nlong);
            u4_dp_rimmod_3b_oth_cs_mirr2[u2_t_dataid] = u4_dp_rimmod_3b_oth_cs_main[u2_t_dataid];

            vd_d_Rim_CopyU1(u1_ap_data, (U1*)(&u4_sp_rim_3b_cpb_mai[0]), u2_a_NBYTE);
            u1_t_ret = (U1)RIM_RESULT_OK_REPAIRED;
        }
        else{
            u1_t_ret = (U1)RIM_RESULT_NG_DATA;
        }
    }

    return(u1_t_ret);
#else
    return((U1)RIM_RESULT_NG_PRM_ID);
#endif  /* #if (__RIM_MOD_3BRAM_OTHER_USE__ == TRUE) */
}

/*===================================================================================================================================*/
/*  U1 u1_d_RimMod_3BRam_WriteOther(const U2 u2_a_ID, const U2 u2_a_NBYTE, const U1 * const u1_ap_DATA)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_ID     : RimId                                                                                          */
/*                  --> u2_a_NBYTE  : Size                                                                                           */
/*                  --> *u1_ap_DATA : Write Data Pointer                                                                             */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1 u1_d_RimMod_3BRam_WriteOther(const U2 u2_a_ID, const U2 u2_a_NBYTE, const U1 * const u1_ap_DATA)
{
#if (__RIM_MOD_3BRAM_OTHER_USE__ == TRUE)
    U4                       u4_t_sum;
    U2                       u2_t_dataid;
    U2                       u2_t_index;
    U2                       u2_t_nlong;
    U2                       u2_t_end;
    U1                       u1_t_ret;

    u2_t_dataid = u2_a_ID & u2_d_RIM_MOD_3BRAM_DATA_ID_MASK;
    if(u2_t_dataid >= u2_d_RIM_MOD_3BRAM_OTR_ID_NUM){
        /* PRM:RIMID Error(DataId Error) */
        u1_t_ret = (U1)RIM_RESULT_NG_PRM_ID;
    }
    else if(u2_a_NBYTE != st_d_RIM_MOD_3BRAM_OTR_SZ_CFG[u2_t_dataid].u2_size){
        /* PRM:Size Error */
        u1_t_ret = (U1)RIM_RESULT_NG_PRM_SIZE;
    }
    else{

        u2_t_index = st_d_RIM_MOD_3BRAM_OTR_SZ_CFG[u2_t_dataid].u2_index;
        u2_t_nlong = u2_d_RIM_CHGSIZE_U1_TO_U4(u2_a_NBYTE);
        u2_t_end   = u2_t_nlong - (U2)1U;

        u4_sp_rim_3b_cpb_mai[u2_t_end] = (U4)0U;

        vd_d_Rim_CopyU1((U1*)(&u4_sp_rim_3b_cpb_mai[0]), u1_ap_DATA, u2_a_NBYTE);
        u4_t_sum = u4_d_Rim_GetCheckSumOther(&u4_sp_rim_3b_cpb_mai[0], u2_t_nlong);

        vd_d_Rim_CopyU4(&u4_dp_rimmod_3b_oth_main[u2_t_index],  &u4_sp_rim_3b_cpb_mai[0], u2_t_nlong);
        u4_dp_rimmod_3b_oth_cs_main[u2_t_dataid] = u4_t_sum;

        vd_d_Rim_CopyU4(&u4_dp_rimmod_3b_oth_mirr1[u2_t_index], &u4_sp_rim_3b_cpb_mai[0], u2_t_nlong);
        u4_dp_rimmod_3b_oth_cs_mirr1[u2_t_dataid] = u4_t_sum;

        vd_d_Rim_CopyU4(&u4_dp_rimmod_3b_oth_mirr2[u2_t_index], &u4_sp_rim_3b_cpb_mai[0], u2_t_nlong);
        u4_dp_rimmod_3b_oth_cs_mirr2[u2_t_dataid] = u4_t_sum;

        u1_t_ret = (U1)RIM_RESULT_OK;
    }

    return(u1_t_ret);
#else
    return((U1)RIM_RESULT_NG_PRM_ID);
#endif  /* #if (__RIM_MOD_3BRAM_OTHER_USE__ == TRUE) */
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
/*  static void    vd_s_RimMod_3BRam_WkupInitOtr(const U4 u4_a_DATA_ID)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_DATA_ID : DataId                                                                                        */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
#if (__RIM_MOD_3BRAM_OTHER_USE__ == TRUE)
static void    vd_s_RimMod_3BRam_WkupInitOtr(const U4 u4_a_DATA_ID)
{
    static void ( * const    fp_sp_vd_RIM_3BR_WKU_INI[])(ST_RIM_3BR_WK * st_ap_3br_wk, const U2 u2_a_NLONG) = {
        &vd_s_Rim_3BR_Wkuini_000,   /* 000 */
        &vd_s_Rim_3BR_Wkuini_001,   /* 001 */
        &vd_s_Rim_3BR_Wkuini_010,   /* 010 */
        &vd_s_Rim_3BR_Wkuini_011,   /* 011 */
        &vd_s_Rim_3BR_Wkuini_100,   /* 100 */
        &vd_s_Rim_3BR_Wkuini_101,   /* 101 */
        &vd_s_Rim_3BR_Wkuini_110    /* 110 */
    };

    ST_RIM_3BR_WK            st_t_3br_wk;

    U4                       u4_t_lpcnt;

    U2                       u2_t_nbyte;
    U2                       u2_t_nlong;
    U2                       u2_t_index;
    U2                       u2_t_id;

    U1                       u1_t_wku;

    u2_t_index = st_d_RIM_MOD_3BRAM_OTR_SZ_CFG[u4_a_DATA_ID].u2_index;
    u2_t_nbyte = st_d_RIM_MOD_3BRAM_OTR_SZ_CFG[u4_a_DATA_ID].u2_size;
    u2_t_nlong = u2_d_RIM_CHGSIZE_U1_TO_U4(u2_t_nbyte);

    st_t_3br_wk.u4p_las_mai = &u4_sp_rim_3b_cpb_mai[0];
    st_t_3br_wk.u4p_las_m_1 = &u4_sp_rim_3b_cpb_m_1[0];
    st_t_3br_wk.u4p_las_m_2 = &u4_sp_rim_3b_cpb_m_2[0];

    st_t_3br_wk.u4p_nex_mai = &u4_dp_rimmod_3b_oth_main[u2_t_index];
    st_t_3br_wk.u4p_nex_m_1 = &u4_dp_rimmod_3b_oth_mirr1[u2_t_index];
    st_t_3br_wk.u4p_nex_m_2 = &u4_dp_rimmod_3b_oth_mirr2[u2_t_index];

    st_t_3br_wk.u4p_sum_mai = &u4_dp_rimmod_3b_oth_cs_main[u4_a_DATA_ID];
    st_t_3br_wk.u4p_sum_m_1 = &u4_dp_rimmod_3b_oth_cs_mirr1[u4_a_DATA_ID];
    st_t_3br_wk.u4p_sum_m_2 = &u4_dp_rimmod_3b_oth_cs_mirr2[u4_a_DATA_ID];

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u2_t_nlong; u4_t_lpcnt++){
        u4_sp_rim_3b_cpb_mai[u4_t_lpcnt] = st_t_3br_wk.u4p_nex_mai[u4_t_lpcnt];
        u4_sp_rim_3b_cpb_m_1[u4_t_lpcnt] = st_t_3br_wk.u4p_nex_m_1[u4_t_lpcnt];
        u4_sp_rim_3b_cpb_m_2[u4_t_lpcnt] = st_t_3br_wk.u4p_nex_m_2[u4_t_lpcnt];
    }

    u1_t_wku = u1_s_RimMod_3BRam_WkupInitChk(&st_t_3br_wk, u2_t_nlong);
    if(u1_t_wku == (U1)0x00U){

        (*fp_sp_vd_RIM_3BR_WKU_INI[u1_t_wku])(&st_t_3br_wk, u2_t_nlong);

        u2_t_id = u2_s_RimMod_3B_RId((U2)RIMID_RIMSIZE_OTHER, (U2)u4_a_DATA_ID);
        vd_d_Rim_WkupInitErrorHook(u2_t_id, (U1)RIM_RESULT_NG_DATA);
    }
    else if(u1_t_wku < (U1)RIM_MOD_3BRAM_WKU_ALL){

        (*fp_sp_vd_RIM_3BR_WKU_INI[u1_t_wku])(&st_t_3br_wk, u2_t_nlong);
    }
    else{
        /* do nothing */
    }
}
/*===================================================================================================================================*/
static void    vd_s_Rim_3BR_Wkuini_000(ST_RIM_3BR_WK * st_ap_3br_wk, const U2 u2_a_NLONG)
{
    (*st_ap_3br_wk->u4p_las_mai) = (U4)RIM_MOD_3BRAM_ERR_DATA_MAIN;
    (*st_ap_3br_wk->u4p_nex_mai) = (U4)RIM_MOD_3BRAM_ERR_DATA_MAIN;
    (*st_ap_3br_wk->u4p_sum_mai) = u4_d_Rim_GetCheckSumOther(st_ap_3br_wk->u4p_las_mai, u2_a_NLONG) ^ (U4)U4_MAX;

    (*st_ap_3br_wk->u4p_las_m_1) = (U4)RIM_MOD_3BRAM_ERR_DATA_MIRR1;
    (*st_ap_3br_wk->u4p_nex_m_1) = (U4)RIM_MOD_3BRAM_ERR_DATA_MIRR1;
    (*st_ap_3br_wk->u4p_sum_m_1) = u4_d_Rim_GetCheckSumOther(st_ap_3br_wk->u4p_las_m_1, u2_a_NLONG) ^ (U4)U4_MAX;

    (*st_ap_3br_wk->u4p_las_m_2) = (U4)RIM_MOD_3BRAM_ERR_DATA_MIRR2;
    (*st_ap_3br_wk->u4p_nex_m_2) = (U4)RIM_MOD_3BRAM_ERR_DATA_MIRR2;
    (*st_ap_3br_wk->u4p_sum_m_2) = u4_d_Rim_GetCheckSumOther(st_ap_3br_wk->u4p_las_m_2, u2_a_NLONG) ^ (U4)U4_MAX;
}
/*===================================================================================================================================*/
static void    vd_s_Rim_3BR_Wkuini_001(ST_RIM_3BR_WK * st_ap_3br_wk, const U2 u2_a_NLONG)
{
    vd_d_Rim_CopyU4(st_ap_3br_wk->u4p_nex_mai, st_ap_3br_wk->u4p_las_m_2, u2_a_NLONG);
    vd_d_Rim_CopyU4(st_ap_3br_wk->u4p_nex_m_1, st_ap_3br_wk->u4p_las_m_2, u2_a_NLONG);

    (*st_ap_3br_wk->u4p_sum_mai) = (*st_ap_3br_wk->u4p_sum_m_2);
    (*st_ap_3br_wk->u4p_sum_m_1) = (*st_ap_3br_wk->u4p_sum_m_2);
}
/*===================================================================================================================================*/
static void    vd_s_Rim_3BR_Wkuini_010(ST_RIM_3BR_WK * st_ap_3br_wk, const U2 u2_a_NLONG)
{
    vd_d_Rim_CopyU4(st_ap_3br_wk->u4p_nex_mai, st_ap_3br_wk->u4p_las_m_1, u2_a_NLONG);
    vd_d_Rim_CopyU4(st_ap_3br_wk->u4p_nex_m_2, st_ap_3br_wk->u4p_las_m_1, u2_a_NLONG);

    (*st_ap_3br_wk->u4p_sum_mai) = (*st_ap_3br_wk->u4p_sum_m_1);
    (*st_ap_3br_wk->u4p_sum_m_2) = (*st_ap_3br_wk->u4p_sum_m_1);
}
/*===================================================================================================================================*/
static void    vd_s_Rim_3BR_Wkuini_011(ST_RIM_3BR_WK * st_ap_3br_wk, const U2 u2_a_NLONG)
{
    vd_d_Rim_CopyU4(st_ap_3br_wk->u4p_nex_mai, st_ap_3br_wk->u4p_las_m_1, u2_a_NLONG);
    (*st_ap_3br_wk->u4p_sum_mai) = (*st_ap_3br_wk->u4p_sum_m_1);
}
/*===================================================================================================================================*/
static void    vd_s_Rim_3BR_Wkuini_100(ST_RIM_3BR_WK * st_ap_3br_wk, const U2 u2_a_NLONG)
{
    vd_d_Rim_CopyU4(st_ap_3br_wk->u4p_nex_m_1, st_ap_3br_wk->u4p_las_mai, u2_a_NLONG);
    vd_d_Rim_CopyU4(st_ap_3br_wk->u4p_nex_m_2, st_ap_3br_wk->u4p_las_mai, u2_a_NLONG);

    (*st_ap_3br_wk->u4p_sum_m_1) = (*st_ap_3br_wk->u4p_sum_mai);
    (*st_ap_3br_wk->u4p_sum_m_2) = (*st_ap_3br_wk->u4p_sum_mai);
}
/*===================================================================================================================================*/
static void    vd_s_Rim_3BR_Wkuini_101(ST_RIM_3BR_WK * st_ap_3br_wk, const U2 u2_a_NLONG)
{
    vd_d_Rim_CopyU4(st_ap_3br_wk->u4p_nex_m_1, st_ap_3br_wk->u4p_las_mai, u2_a_NLONG);
    (*st_ap_3br_wk->u4p_sum_m_1) = (*st_ap_3br_wk->u4p_sum_mai);
}    
/*===================================================================================================================================*/
static void    vd_s_Rim_3BR_Wkuini_110(ST_RIM_3BR_WK * st_ap_3br_wk, const U2 u2_a_NLONG)
{
    vd_d_Rim_CopyU4(st_ap_3br_wk->u4p_nex_m_2, st_ap_3br_wk->u4p_las_mai, u2_a_NLONG);
    (*st_ap_3br_wk->u4p_sum_m_2) = (*st_ap_3br_wk->u4p_sum_mai);
}

#endif  /* #if (__RIM_MOD_3BRAM_OTHER_USE__ == TRUE) */

/*===================================================================================================================================*/
/*  static U1      u1_s_RimMod_3BRam_WkupInitChk(const ST_RIM_3BR_WK * st_ap_3BR_WK, const U2 u2_a_NLONG)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *st_ap_3BR_WK                                                                                                */
/*                  --> u2_a_NLONG                                                                                                   */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
#if (__RIM_MOD_3BRAM_OTHER_USE__ == TRUE)
static U1      u1_s_RimMod_3BRam_WkupInitChk(const ST_RIM_3BR_WK * st_ap_3BR_WK, const U2 u2_a_NLONG)
{
    static U1 ( * const      fp_sp_u1_RIM_3BR_WKU_CHK[])(const ST_RIM_3BR_WK * st_ap_3BR_WK, const U2 u2_a_NLONG) = {
        vdp_PTR_NA,                 /* 000 */
        vdp_PTR_NA,                 /* 001 */
        vdp_PTR_NA,                 /* 010 */
        &u1_s_Rim_3BR_Wkuchk_011,   /* 011 */
        vdp_PTR_NA,                 /* 100 */
        &u1_s_Rim_3BR_Wkuchk_101,   /* 101 */
        &u1_s_Rim_3BR_Wkuchk_110,   /* 110 */
        &u1_s_Rim_3BR_Wkuchk_111    /* 111 */
    };

    U4                       u4_t_sum;
    U1                       u1_t_wku;

    u4_t_sum = u4_d_Rim_GetCheckSumOther(st_ap_3BR_WK->u4p_las_mai, u2_a_NLONG);
    if(u4_t_sum == (*st_ap_3BR_WK->u4p_sum_mai)){
        u1_t_wku  = (U1)RIM_MOD_3BRAM_WKU_MAI;
    }
    else{
        u1_t_wku  = (U1)0x00U;
    }
    u4_t_sum = u4_d_Rim_GetCheckSumOther(st_ap_3BR_WK->u4p_las_m_1, u2_a_NLONG);
    if(u4_t_sum == (*st_ap_3BR_WK->u4p_sum_m_1)){
        u1_t_wku |= (U1)RIM_MOD_3BRAM_WKU_M_1;
    }
    u4_t_sum = u4_d_Rim_GetCheckSumOther(st_ap_3BR_WK->u4p_las_m_2, u2_a_NLONG);
    if(u4_t_sum == (*st_ap_3BR_WK->u4p_sum_m_2)){
        u1_t_wku |= (U1)RIM_MOD_3BRAM_WKU_M_2;
    }

    if(fp_sp_u1_RIM_3BR_WKU_CHK[u1_t_wku] != vdp_PTR_NA){
        u1_t_wku = (*fp_sp_u1_RIM_3BR_WKU_CHK[u1_t_wku])(st_ap_3BR_WK, u2_a_NLONG);
    }

    return(u1_t_wku);
}
/*===================================================================================================================================*/
static U1      u1_s_Rim_3BR_Wkuchk_011(const ST_RIM_3BR_WK * st_ap_3BR_WK, const U2 u2_a_NLONG)
{
    U1                       u1_t_equ;
    U1                       u1_t_wku;

    u1_t_equ = u1_d_Rim_CompareOther(st_ap_3BR_WK->u4p_las_m_1, st_ap_3BR_WK->u4p_las_m_2, u2_a_NLONG);
    if(u1_t_equ == (U1)TRUE){
        u1_t_wku = (U1)RIM_MOD_3BRAM_WKU_M_1 | (U1)RIM_MOD_3BRAM_WKU_M_2;
    }
    else{
        u1_t_wku = (U1)RIM_MOD_3BRAM_WKU_M_1;
    }

    return(u1_t_wku);
}
/*===================================================================================================================================*/
static U1      u1_s_Rim_3BR_Wkuchk_101(const ST_RIM_3BR_WK * st_ap_3BR_WK, const U2 u2_a_NLONG)
{
    U1                       u1_t_equ;
    U1                       u1_t_wku;

    u1_t_equ = u1_d_Rim_CompareOther(st_ap_3BR_WK->u4p_las_mai, st_ap_3BR_WK->u4p_las_m_2, u2_a_NLONG);
    if(u1_t_equ == (U1)TRUE){
        u1_t_wku = (U1)RIM_MOD_3BRAM_WKU_MAI | (U1)RIM_MOD_3BRAM_WKU_M_2;
    }
    else{
        u1_t_wku = (U1)RIM_MOD_3BRAM_WKU_MAI;
    }

    return(u1_t_wku);
}
/*===================================================================================================================================*/
static U1      u1_s_Rim_3BR_Wkuchk_110(const ST_RIM_3BR_WK * st_ap_3BR_WK, const U2 u2_a_NLONG)
{
    U1                       u1_t_equ;
    U1                       u1_t_wku;

    u1_t_equ = u1_d_Rim_CompareOther(st_ap_3BR_WK->u4p_las_mai, st_ap_3BR_WK->u4p_las_m_1, u2_a_NLONG);
    if(u1_t_equ == (U1)TRUE){
        u1_t_wku = (U1)RIM_MOD_3BRAM_WKU_MAI | (U1)RIM_MOD_3BRAM_WKU_M_1;
    }
    else{
        u1_t_wku = (U1)RIM_MOD_3BRAM_WKU_MAI;
    }

    return(u1_t_wku);
}
/*===================================================================================================================================*/
static U1      u1_s_Rim_3BR_Wkuchk_111(const ST_RIM_3BR_WK * st_ap_3BR_WK, const U2 u2_a_NLONG)
{
    U1                       u1_t_maj;
    U1                       u1_t_wku;

    u1_t_maj = u1_d_Rim_MajorityByDataOther(st_ap_3BR_WK->u4p_las_mai,
                                            st_ap_3BR_WK->u4p_las_m_1,
                                            st_ap_3BR_WK->u4p_las_m_2,
                                            u2_a_NLONG);
    if(u1_t_maj == (U1)RIM_MAJOR_OK){
        u1_t_wku = (U1)RIM_MOD_3BRAM_WKU_MAI | (U1)RIM_MOD_3BRAM_WKU_M_1 | (U1)RIM_MOD_3BRAM_WKU_M_2;
    }
    else if(u1_t_maj == (U1)RIM_MAJOR_NG_A){
        u1_t_wku = (U1)RIM_MOD_3BRAM_WKU_M_1 | (U1)RIM_MOD_3BRAM_WKU_M_2;
    }
    else if(u1_t_maj == (U1)RIM_MAJOR_NG_B){
        u1_t_wku = (U1)RIM_MOD_3BRAM_WKU_MAI | (U1)RIM_MOD_3BRAM_WKU_M_2;
    }
    else if(u1_t_maj == (U1)RIM_MAJOR_NG_C){
        u1_t_wku = (U1)RIM_MOD_3BRAM_WKU_MAI | (U1)RIM_MOD_3BRAM_WKU_M_1;
    }
    else{
        u1_t_wku = (U1)0x00U;
    }

    return(u1_t_wku);
}
#endif  /* #if (__RIM_MOD_3BRAM_OTHER_USE__ == TRUE) */

/*===================================================================================================================================*/
/*  static inline U2    u2_s_RimMod_3B_RId(const U2 u2_a_SIZE, const U2 u2_a_DATAID)                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
static inline U2    u2_s_RimMod_3B_RId(const U2 u2_a_SIZE, const U2 u2_a_DATAID)
{
    return((u2_a_SIZE & (U2)RIMID_RIMSIZE_MASK           ) |
           (u2_d_RIM_MOD_3BRAM_MODULE_ID                 ) |
           (u2_a_DATAID & u2_d_RIM_MOD_3BRAM_DATA_ID_MASK));
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version         Date        Author  Change Description                                                                           */
/* ---------------  ----------  ------  -------------------------------------------------------------------------------------------  */
/*  1.0.0           11/18/2014  KM      New.                                                                                         */
/*  1.1.0           03/24/2015  MH      Fixed QAC issue.                                                                             */
/*                                      Data ID mask was moved to const data.                                                        */
/*                                      Update version check                                                                         */
/*  1.1.1           07/14/2015  HK      Comment correction                                                                           */
/*  1.2.0           09/07/2015  HK      Comment correction                                                                           */
/*                                      Logic change of "vd_s_RimMod_3BRam_WkupInitOtr"                                              */
/*  1.2.1           10/07/2015  HK      Expand DataID to 9bit                                                                        */
/*  1.2.2           02/29/2016  HK      Correspond non-library                                                                       */
/*  1.2.3           12/07/2016  HK      Fixed AIP3GBSW-25 issue.                                                                     */
/*  1.2.4            9/14/2021  TN      QAC Warnings were fixed.                                                                     */
/*  1.3.0            9/16/2021  TN      QAC metrics violation was fixed.                                                             */
/*                  10/ 9/2021  TN      u2_s_RIM_MOD_3BRAM_GET_RIMID() and u2_s_RIM_MOD_3BRAM_GET_DATA_ID() were deleted.            */
/*                  11/ 1/2021  TN      Codesonar red warnings "Uninitialized Variable" were fixed.                                  */
/*                                      u4_sp_rim_3b_cpb_xxx[] were implemented.                                                     */
/*  1.3.1           11/ 8/2023  KN      Improvement : Warning MISRA-C-Rule7.2 was fixed.                                             */
/*                                                                                                                                   */
/*  * KM      = Kazuyuki Makino, Denso Create                                                                                        */
/*  * MH      = Masayuki Hattori, Denso                                                                                              */
/*  * HK      = Hayato Kanamori, Denso Create                                                                                        */
/*  * TN      = Takashi Nagai, Denso                                                                                                 */
/*  * KN      = Keigo Nomura   , Denso Create                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
