/* 1.2.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  RIM : MODULE_3CRAM                                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RIM_MOD_3CRAM_C_MAJOR                    (1U)
#define RIM_MOD_3CRAM_C_MINOR                    (2U)
#define RIM_MOD_3CRAM_C_PATCH                    (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include "rim_ctl.h"
#include "rim_func_private.h"

#include "rim_mod_3cram_private.h"
#include "rim_mod_3cram_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((RIM_MOD_3CRAM_C_MAJOR != RIM_MOD_3CRAM_H_MAJOR) || \
     (RIM_MOD_3CRAM_C_MINOR != RIM_MOD_3CRAM_H_MINOR) || \
     (RIM_MOD_3CRAM_C_PATCH != RIM_MOD_3CRAM_H_PATCH))
#error "rim_mod_3cram.c and rim_mod_3cram_private.h : source and header files are inconsistent!"
#endif

#if ((RIM_MOD_3CRAM_C_MAJOR != RIM_MOD_3CRAM_CFG_PRIVATE_H_MAJOR) || \
     (RIM_MOD_3CRAM_C_MINOR != RIM_MOD_3CRAM_CFG_PRIVATE_H_MINOR) || \
     (RIM_MOD_3CRAM_C_PATCH != RIM_MOD_3CRAM_CFG_PRIVATE_H_PATCH))
#error "rim_mod_3cram.c and rim_mod_3cram_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U1 u1_d_RimMod_3CRam_ReadU4(const U2 u2_a_ID, U4 *u4_ap_data)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_ID     : RimId                                                                                          */
/*                  --> *u4_ap_data : Read Data Pointer                                                                              */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1 u1_d_RimMod_3CRam_ReadU4(const U2 u2_a_ID, U4 *u4_ap_data)
{
    U1  u1_t_ret;
    U2  u2_t_rimsize;
    U2  u2_t_dataid;

    u1_t_ret = (U1)RIM_RESULT_NG_PRM_ID;

    u2_t_rimsize = u2_g_RIM_GET_RIMSIZE(u2_a_ID);
    u2_t_dataid  = u2_a_ID & u2_d_RIM_MOD_3CRAM_DATA_ID_MASK;

    if(u2_t_rimsize == (U2)RIMID_RIMSIZE_1BYTE){
#if (__RIM_MOD_3CRAM_U1_USE__ == TRUE)
        if(u2_t_dataid < u2_d_RIM_MOD_3CRAM_U1_ID_NUM){
            u1_t_ret = u1_d_Rim_MajorityU1Data(u4_ap_data,
                                               &u1_dp_rimmod_3cram_u1buf_main[u2_t_dataid],
                                               &u1_dp_rimmod_3cram_u1buf_mirr1[u2_t_dataid],
                                               &u1_dp_rimmod_3cram_u1buf_mirr2[u2_t_dataid]);
        }
        else{
            /* PRM:RIMID Error(DataId Error) */
        }
#endif  /* #if (__RIM_MOD_3CRAM_U1_USE__ == TRUE) */
    }
    else if(u2_t_rimsize == (U2)RIMID_RIMSIZE_2BYTE){
#if (__RIM_MOD_3CRAM_U2_USE__ == TRUE)
        if(u2_t_dataid < u2_d_RIM_MOD_3CRAM_U2_ID_NUM){
            u1_t_ret = u1_d_Rim_MajorityU2Data(u4_ap_data,
                                               &u2_dp_rimmod_3cram_u2buf_main[u2_t_dataid],
                                               &u2_dp_rimmod_3cram_u2buf_mirr1[u2_t_dataid],
                                               &u2_dp_rimmod_3cram_u2buf_mirr2[u2_t_dataid]);
        }
        else{
            /* PRM:RIMID Error(DataId Error) */
        }
#endif  /* #if (__RIM_MOD_3CRAM_U2_USE__ == TRUE) */
    }
    else if(u2_t_rimsize == (U2)RIMID_RIMSIZE_4BYTE){
#if (__RIM_MOD_3CRAM_U4_USE__ == TRUE)
        if(u2_t_dataid < u2_d_RIM_MOD_3CRAM_U4_ID_NUM){
            u1_t_ret = u1_d_Rim_MajorityU4Data(u4_ap_data,
                                               &u4_dp_rimmod_3cram_u4buf_main[u2_t_dataid],
                                               &u4_dp_rimmod_3cram_u4buf_mirr1[u2_t_dataid],
                                               &u4_dp_rimmod_3cram_u4buf_mirr2[u2_t_dataid]);
        }
        else{
            /* PRM:RIMID Error(DataId Error) */
        }
#endif  /* #if (__RIM_MOD_3CRAM_U4_USE__ == TRUE) */
    }
    else{
        /* PRM:RIMID Error(SIZE Error) */
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1 u1_d_RimMod_3CRam_WriteU4(const U2 u2_a_ID, const U4 u4_a_DATA)                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_ID   : RimId                                                                                            */
/*                  --> u4_a_DATA : Write Data                                                                                       */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1 u1_d_RimMod_3CRam_WriteU4(const U2 u2_a_ID, const U4 u4_a_DATA)
{
    U1  u1_t_ret;
    U2  u2_t_rimsize;
    U2  u2_t_dataid;

    u1_t_ret = (U1)RIM_RESULT_NG_PRM_ID;

    u2_t_rimsize = u2_g_RIM_GET_RIMSIZE(u2_a_ID);
    u2_t_dataid  = u2_a_ID & u2_d_RIM_MOD_3CRAM_DATA_ID_MASK;

    if(u2_t_rimsize == (U2)RIMID_RIMSIZE_1BYTE){
#if (__RIM_MOD_3CRAM_U1_USE__ == TRUE)
        if(u2_t_dataid < u2_d_RIM_MOD_3CRAM_U1_ID_NUM){
            u1_dp_rimmod_3cram_u1buf_main[u2_t_dataid]  = (U1)u4_a_DATA;
            u1_dp_rimmod_3cram_u1buf_mirr1[u2_t_dataid] = (U1)u4_a_DATA;
            u1_dp_rimmod_3cram_u1buf_mirr2[u2_t_dataid] = (U1)u4_a_DATA;

            u1_t_ret = (U1)RIM_RESULT_OK;
        }
        else{
            /* PRM:RIMID Error(DataId Error) */
        }
#endif  /* #if (__RIM_MOD_3CRAM_U1_USE__ == TRUE) */
    }
    else if(u2_t_rimsize == (U2)RIMID_RIMSIZE_2BYTE){
#if (__RIM_MOD_3CRAM_U2_USE__ == TRUE)
        if(u2_t_dataid < u2_d_RIM_MOD_3CRAM_U2_ID_NUM){
            u2_dp_rimmod_3cram_u2buf_main[u2_t_dataid]  = (U2)u4_a_DATA;
            u2_dp_rimmod_3cram_u2buf_mirr1[u2_t_dataid] = (U2)u4_a_DATA;
            u2_dp_rimmod_3cram_u2buf_mirr2[u2_t_dataid] = (U2)u4_a_DATA;

            u1_t_ret = (U1)RIM_RESULT_OK;
        }
        else{
            /* PRM:RIMID Error(DataId Error) */
        }
#endif  /* #if (__RIM_MOD_3CRAM_U2_USE__ == TRUE) */
    }
    else if(u2_t_rimsize == (U2)RIMID_RIMSIZE_4BYTE){
#if (__RIM_MOD_3CRAM_U4_USE__ == TRUE)
        if(u2_t_dataid < u2_d_RIM_MOD_3CRAM_U4_ID_NUM){
            u4_dp_rimmod_3cram_u4buf_main[u2_t_dataid]  = u4_a_DATA;
            u4_dp_rimmod_3cram_u4buf_mirr1[u2_t_dataid] = u4_a_DATA;
            u4_dp_rimmod_3cram_u4buf_mirr2[u2_t_dataid] = u4_a_DATA;

            u1_t_ret = (U1)RIM_RESULT_OK;
        }
        else{
            /* PRM:RIMID Error(DataId Error) */
        }
#endif  /* #if (__RIM_MOD_3CRAM_U4_USE__ == TRUE) */
    }
    else{
        /* PRM:RIMID Error(SIZE Error) */
    }

    return(u1_t_ret);
}


/*===================================================================================================================================*/
/*  U1 u1_d_RimMod_3CRam_ReadOther(const U2 u2_a_ID, const U2 u2_a_NBYTE, U1 *u1_ap_data)                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_ID     : RimId                                                                                          */
/*                  --> u2_a_NBYTE  : Size                                                                                           */
/*                  --> *u1_ap_data : Read Data Pointer                                                                              */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1 u1_d_RimMod_3CRam_ReadOther(const U2 u2_a_ID, const U2 u2_a_NBYTE, U1 *u1_ap_data)
{
#if (__RIM_MOD_3CRAM_OTHER_USE__ == TRUE)
    U4 * u4_tp_mai;
    U4 * u4_tp_m_1;
    U4 * u4_tp_m_2;

    U2   u2_t_dataid;
    U2   u2_t_index;
    U2   u2_t_nlong;

    U1   u1_t_major;
    U1   u1_t_ret;

    u2_t_dataid = u2_a_ID & u2_d_RIM_MOD_3CRAM_DATA_ID_MASK;
    if(u2_t_dataid >= u2_d_RIM_MOD_3CRAM_OTR_ID_NUM){
        /* PRM:RIMID Error(DataId Error) */
        u1_t_ret = (U1)RIM_RESULT_NG_PRM_ID;
    }
    else if(u2_a_NBYTE != st_d_RIM_MOD_3CRAM_OTR_SZ_CFG[u2_t_dataid].u2_size){
        /* PRM:Size Error */
        u1_t_ret = (U1)RIM_RESULT_NG_PRM_SIZE;
    }
    else{

        u2_t_index = st_d_RIM_MOD_3CRAM_OTR_SZ_CFG[u2_t_dataid].u2_index;
        u2_t_nlong = u2_d_RIM_CHGSIZE_U1_TO_U4(u2_a_NBYTE);

        u4_tp_mai  = &u4_dp_rimmod_3cram_otrbuf_main[u2_t_index];
        u4_tp_m_1  = &u4_dp_rimmod_3cram_otrbuf_mirr1[u2_t_index];
        u4_tp_m_2  = &u4_dp_rimmod_3cram_otrbuf_mirr2[u2_t_index];

        u1_t_major = u1_d_Rim_MajorityByDataOther(u4_tp_mai, u4_tp_m_1, u4_tp_m_2, u2_t_nlong);
        if(u1_t_major == (U1)RIM_MAJOR_OK){

            vd_d_Rim_CopyU1(u1_ap_data, (U1 *)u4_tp_mai, u2_a_NBYTE);
            u1_t_ret = (U1)RIM_RESULT_OK;
        }
        else if(u1_t_major == (U1)RIM_MAJOR_NG_A){

            vd_d_Rim_CopyU4(u4_tp_mai, u4_tp_m_1, u2_t_nlong);

            vd_d_Rim_CopyU1(u1_ap_data, (U1 *)u4_tp_m_1, u2_a_NBYTE);
            u1_t_ret = (U1)RIM_RESULT_OK_REPAIRED;
        }
        else if(u1_t_major == (U1)RIM_MAJOR_NG_B){

            vd_d_Rim_CopyU4(u4_tp_m_1, u4_tp_mai, u2_t_nlong);

            vd_d_Rim_CopyU1(u1_ap_data, (U1 *)u4_tp_mai, u2_a_NBYTE);
            u1_t_ret = (U1)RIM_RESULT_OK_REPAIRED;
        }
        else if(u1_t_major == (U1)RIM_MAJOR_NG_C){

            vd_d_Rim_CopyU4(u4_tp_m_2, u4_tp_mai, u2_t_nlong);

            vd_d_Rim_CopyU1(u1_ap_data, (U1 *)u4_tp_mai, u2_a_NBYTE);
            u1_t_ret = (U1)RIM_RESULT_OK_REPAIRED;
        }
        else{
            u1_t_ret = (U1)RIM_RESULT_NG_DATA;
        }
    }

    return(u1_t_ret);
#else
    return((U1)RIM_RESULT_NG_PRM_ID);
#endif  /* #if (__RIM_MOD_3CRAM_OTHER_USE__ == TRUE) */
}

/*===================================================================================================================================*/
/*  U1 u1_d_RimMod_3CRam_WriteOther(const U2 u2_a_ID, const U2 u2_a_NBYTE, const U1 * const u1_ap_DATA)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_ID     : RimId                                                                                          */
/*                  --> u2_a_NBYTE  : Size                                                                                           */
/*                  --> *u1_ap_DATA : Write Data Pointer                                                                             */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1 u1_d_RimMod_3CRam_WriteOther(const U2 u2_a_ID, const U2 u2_a_NBYTE, const U1 * const u1_ap_DATA)
{
#if (__RIM_MOD_3CRAM_OTHER_USE__ == TRUE)
    U4 * u4_tp_mai;

    U2   u2_t_dataid;
    U2   u2_t_index;
    U2   u2_t_nlong;
    U2   u2_t_end;

    U1   u1_t_ret;

    u2_t_dataid = u2_a_ID & u2_d_RIM_MOD_3CRAM_DATA_ID_MASK;
    if(u2_t_dataid >= u2_d_RIM_MOD_3CRAM_OTR_ID_NUM){
        /* PRM:RIMID Error(DataId Error) */
        u1_t_ret = (U1)RIM_RESULT_NG_PRM_ID;
    }
    else if(u2_a_NBYTE != st_d_RIM_MOD_3CRAM_OTR_SZ_CFG[u2_t_dataid].u2_size){
        /* PRM:Size Error */
        u1_t_ret = (U1)RIM_RESULT_NG_PRM_SIZE;
    }
    else{

        u2_t_index = st_d_RIM_MOD_3CRAM_OTR_SZ_CFG[u2_t_dataid].u2_index;
        u2_t_nlong = u2_d_RIM_CHGSIZE_U1_TO_U4(u2_a_NBYTE);
        u2_t_end   = u2_t_nlong - (U2)1U;
        u4_tp_mai  = &u4_dp_rimmod_3cram_otrbuf_main[u2_t_index];

        u4_tp_mai[u2_t_end] = (U4)0U;
        vd_d_Rim_CopyU1((U1 *)u4_tp_mai, u1_ap_DATA, u2_a_NBYTE);

        vd_d_Rim_CopyU4(&u4_dp_rimmod_3cram_otrbuf_mirr1[u2_t_index], u4_tp_mai, u2_t_nlong);
        vd_d_Rim_CopyU4(&u4_dp_rimmod_3cram_otrbuf_mirr2[u2_t_index], u4_tp_mai, u2_t_nlong);

        u1_t_ret = (U1)RIM_RESULT_OK;
    }

    return(u1_t_ret);
#else
    return((U1)RIM_RESULT_NG_PRM_ID);
#endif  /* #if (__RIM_MOD_3CRAM_OTHER_USE__ == TRUE) */
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
/*                                      Clear unused area in stack variable.                                                         */
/*                                      Update version check                                                                         */
/*  1.1.1           07/14/2015  HK      Comment correction                                                                           */
/*  1.1.2           09/07/2015  HK      Comment correction                                                                           */
/*  1.1.3           10/07/2015  HK      Expand DataID to 9bit                                                                        */
/*  1.1.4           02/29/2016  HK      Correspond non-library                                                                       */
/*  1.1.5           12/07/2016  HK      Fixed AIP3GBSW-25 issue.                                                                     */
/*  1.1.6            8/22/2017  HK      Fixed QAC warning.                                                                           */
/*  1.1.7           10/ 9/2021  TN      u2_s_RIM_MOD_3CRAM_GET_RIMID() and u2_s_RIM_MOD_3CRAM_GET_DATA_ID() were deleted.            */
/*  1.2.0           11/ 1/2021  TN      Codesonar red warnings "Uninitialized Variable" were fixed.                                  */
/*  1.2.1           11/ 8/2023  KN      Improvement : Warning MISRA-C-Rule7.2 was fixed.                                             */
/*                                                                                                                                   */
/*  * KM      = Kazuyuki Makino, Denso Create                                                                                        */
/*  * MH      = Masayuki Hattori, Denso                                                                                              */
/*  * HK      = Hayato Kanamori, Denso Create                                                                                        */
/*  * TN      = Takashi Nagai, DENSO                                                                                                 */
/*  * KN      = Keigo Nomura   , Denso Create                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
