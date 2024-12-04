/* 1.3.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  RIM : MODULE_1B2CRAM                                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RIM_MOD_1B2CRAM_C_MAJOR                  (1U)
#define RIM_MOD_1B2CRAM_C_MINOR                  (3U)
#define RIM_MOD_1B2CRAM_C_PATCH                  (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "rim_ctl_cfg_private.h"
#include "rim_func_private.h"

#include "rim_mod_1b2cram_private.h"
#include "rim_mod_1b2cram_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((RIM_MOD_1B2CRAM_C_MAJOR != RIM_MOD_1B2CRAM_H_MAJOR) || \
     (RIM_MOD_1B2CRAM_C_MINOR != RIM_MOD_1B2CRAM_H_MINOR) || \
     (RIM_MOD_1B2CRAM_C_PATCH != RIM_MOD_1B2CRAM_H_PATCH))
#error "rim_mod_1b2cram.c and rim_mod_1b2cram_private.h : source and header files are inconsistent!"
#endif

#if ((RIM_MOD_1B2CRAM_C_MAJOR != RIM_MOD_1B2CRAM_CFG_PRIVATE_H_MAJOR) || \
     (RIM_MOD_1B2CRAM_C_MINOR != RIM_MOD_1B2CRAM_CFG_PRIVATE_H_MINOR) || \
     (RIM_MOD_1B2CRAM_C_PATCH != RIM_MOD_1B2CRAM_CFG_PRIVATE_H_PATCH))
#error "rim_mod_1b2cram.c and rim_mod_1b2cram_cfg_private.h : source and header files are inconsistent!"
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
static inline U2    u2_s_RimMod_1B2C_RId(const U2 u2_a_SIZE, const U2 u2_a_DATAID);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void vd_d_RimMod_1B2CRam_WkupInit(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_d_RimMod_1B2CRam_WkupInit(void)
{
#if (__RIM_MOD_1B2CRAM_U1_USE__ == TRUE)
    vd_d_Rim_CopyU1(&u1_dp_rimmod_1b2c_byte_mirr1[0], &u1_dp_rimmod_1b2c_byte_main[0],  u2_d_RIM_MOD_1B2CRAM_U1_ID_NUM);
    vd_d_Rim_CopyU1(&u1_dp_rimmod_1b2c_byte_mirr2[0], &u1_dp_rimmod_1b2c_byte_mirr1[0], u2_d_RIM_MOD_1B2CRAM_U1_ID_NUM);
#endif  /* #if (__RIM_MOD_1B2CRAM_U1_USE__ == TRUE) */

#if (__RIM_MOD_1B2CRAM_U2_USE__ == TRUE)
    vd_d_Rim_CopyU2(&u2_dp_rimmod_1b2c_half_mirr1[0], &u2_dp_rimmod_1b2c_half_main[0],  u2_d_RIM_MOD_1B2CRAM_U2_ID_NUM);
    vd_d_Rim_CopyU2(&u2_dp_rimmod_1b2c_half_mirr2[0], &u2_dp_rimmod_1b2c_half_mirr1[0], u2_d_RIM_MOD_1B2CRAM_U2_ID_NUM);
#endif  /* #if (__RIM_MOD_1B2CRAM_U2_USE__ == TRUE) */

#if (__RIM_MOD_1B2CRAM_U4_USE__ == TRUE)
    vd_d_Rim_CopyU4(&u4_dp_rimmod_1b2c_word_mirr1[0], &u4_dp_rimmod_1b2c_word_main[0],  u2_d_RIM_MOD_1B2CRAM_U4_ID_NUM);
    vd_d_Rim_CopyU4(&u4_dp_rimmod_1b2c_word_mirr2[0], &u4_dp_rimmod_1b2c_word_mirr1[0], u2_d_RIM_MOD_1B2CRAM_U4_ID_NUM);
#endif  /* #if (__RIM_MOD_1B2CRAM_U4_USE__ == TRUE) */
}

/*===================================================================================================================================*/
/*  void vd_d_RimMod_1B2CRam_DeInit(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_d_RimMod_1B2CRam_DeInit(void)
{
#if ((__RIM_MOD_1B2CRAM_U1_USE__ == TRUE) || \
     (__RIM_MOD_1B2CRAM_U2_USE__ == TRUE) || \
     (__RIM_MOD_1B2CRAM_U4_USE__ == TRUE))
    U2  u2_t_cnt;
    U1  u1_t_ret;
    U4  u4_t_temp;
    U1  u1_t_kind;
    U2  u2_t_id;
#endif

#if (__RIM_MOD_1B2CRAM_U1_USE__ == TRUE)
    for(u2_t_cnt = (U2)0U; u2_t_cnt < u2_d_RIM_MOD_1B2CRAM_U1_ID_NUM; u2_t_cnt++){
        u1_t_ret = u1_d_Rim_MajorityU1Data(&u4_t_temp,
                                           &u1_dp_rimmod_1b2c_byte_main[u2_t_cnt],
                                           &u1_dp_rimmod_1b2c_byte_mirr1[u2_t_cnt],
                                           &u1_dp_rimmod_1b2c_byte_mirr2[u2_t_cnt]);
        u1_t_kind = u1_t_ret & (U1)RIM_RESULT_KIND_MASK;
        if(u1_t_kind != (U1)RIM_RESULT_KIND_OK){
            /* Majority Error */
            u2_t_id = u2_s_RimMod_1B2C_RId((U2)RIMID_RIMSIZE_1BYTE, u2_t_cnt);
            vd_d_Rim_DeInitErrorHook(u2_t_id, u1_t_ret);
        }
    }
#endif  /* #if (__RIM_MOD_1B2CRAM_U1_USE__ == TRUE) */

#if (__RIM_MOD_1B2CRAM_U2_USE__ == TRUE)
    for(u2_t_cnt = (U2)0U; u2_t_cnt < u2_d_RIM_MOD_1B2CRAM_U2_ID_NUM; u2_t_cnt++){
        u1_t_ret = u1_d_Rim_MajorityU2Data(&u4_t_temp,
                                           &u2_dp_rimmod_1b2c_half_main[u2_t_cnt],
                                           &u2_dp_rimmod_1b2c_half_mirr1[u2_t_cnt],
                                           &u2_dp_rimmod_1b2c_half_mirr2[u2_t_cnt]);
        u1_t_kind = u1_t_ret & (U1)RIM_RESULT_KIND_MASK;
        if(u1_t_kind != (U1)RIM_RESULT_KIND_OK){
            /* Majority Error */
            u2_t_id = u2_s_RimMod_1B2C_RId((U2)RIMID_RIMSIZE_2BYTE, u2_t_cnt);
            vd_d_Rim_DeInitErrorHook(u2_t_id, u1_t_ret);
        }
    }
#endif  /* #if (__RIM_MOD_1B2CRAM_U2_USE__ == TRUE) */

#if (__RIM_MOD_1B2CRAM_U4_USE__ == TRUE)
    for(u2_t_cnt = (U2)0U; u2_t_cnt < u2_d_RIM_MOD_1B2CRAM_U4_ID_NUM; u2_t_cnt++){
        u1_t_ret = u1_d_Rim_MajorityU4Data(&u4_t_temp,
                                           &u4_dp_rimmod_1b2c_word_main[u2_t_cnt],
                                           &u4_dp_rimmod_1b2c_word_mirr1[u2_t_cnt],
                                           &u4_dp_rimmod_1b2c_word_mirr2[u2_t_cnt]);
        u1_t_kind = u1_t_ret & (U1)RIM_RESULT_KIND_MASK;
        if(u1_t_kind != (U1)RIM_RESULT_KIND_OK){
            /* Majority Error */
            u2_t_id = u2_s_RimMod_1B2C_RId((U2)RIMID_RIMSIZE_4BYTE, u2_t_cnt);
            vd_d_Rim_DeInitErrorHook(u2_t_id, u1_t_ret);
        }
    }
#endif  /* #if (__RIM_MOD_1B2CRAM_U4_USE__ == TRUE) */
}


/*===================================================================================================================================*/
/*  U1 u1_d_RimMod_1B2CRam_ReadU4(const U2 u2_a_ID, U4 *u4_ap_data)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_ID     : RimId                                                                                          */
/*                  --> *u4_ap_data : Read Data Pointer                                                                              */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1 u1_d_RimMod_1B2CRam_ReadU4(const U2 u2_a_ID, U4 *u4_ap_data)
{
    U1  u1_t_ret;
    U2  u2_t_rimsize;
    U2  u2_t_dataid;

    u1_t_ret     = (U1)RIM_RESULT_NG_PRM_ID;

    u2_t_rimsize = u2_g_RIM_GET_RIMSIZE(u2_a_ID);
    u2_t_dataid  = u2_a_ID & u2_d_RIM_MOD_1B2CRAM_DATA_ID_MASK;

    if(u2_t_rimsize == (U2)RIMID_RIMSIZE_1BYTE){
#if (__RIM_MOD_1B2CRAM_U1_USE__ == TRUE)
        if(u2_t_dataid < u2_d_RIM_MOD_1B2CRAM_U1_ID_NUM){
            u1_t_ret = u1_d_Rim_MajorityU1Data(u4_ap_data,
                                               &u1_dp_rimmod_1b2c_byte_main[u2_t_dataid],
                                               &u1_dp_rimmod_1b2c_byte_mirr1[u2_t_dataid],
                                               &u1_dp_rimmod_1b2c_byte_mirr2[u2_t_dataid]);
        }
        else{
            /* PRM:RIMID Error(DataId Error) */
        }
#endif  /* #if (__RIM_MOD_1B2CRAM_U1_USE__ == TRUE) */
    }
    else if(u2_t_rimsize == (U2)RIMID_RIMSIZE_2BYTE){
#if (__RIM_MOD_1B2CRAM_U2_USE__ == TRUE)
        if(u2_t_dataid < u2_d_RIM_MOD_1B2CRAM_U2_ID_NUM){
            u1_t_ret = u1_d_Rim_MajorityU2Data(u4_ap_data,
                                               &u2_dp_rimmod_1b2c_half_main[u2_t_dataid],
                                               &u2_dp_rimmod_1b2c_half_mirr1[u2_t_dataid],
                                               &u2_dp_rimmod_1b2c_half_mirr2[u2_t_dataid]);
        }
        else{
            /* PRM:RIMID Error(DataId Error) */
        }
#endif  /* #if (__RIM_MOD_1B2CRAM_U2_USE__ == TRUE) */
    }
    else if(u2_t_rimsize == (U2)RIMID_RIMSIZE_4BYTE){
#if (__RIM_MOD_1B2CRAM_U4_USE__ == TRUE)
        if(u2_t_dataid < u2_d_RIM_MOD_1B2CRAM_U4_ID_NUM){
            u1_t_ret = u1_d_Rim_MajorityU4Data(u4_ap_data,
                                               &u4_dp_rimmod_1b2c_word_main[u2_t_dataid],
                                               &u4_dp_rimmod_1b2c_word_mirr1[u2_t_dataid],
                                               &u4_dp_rimmod_1b2c_word_mirr2[u2_t_dataid]);
        }
        else{
            /* PRM:RIMID Error(DataId Error) */
        }
#endif  /* #if (__RIM_MOD_1B2CRAM_U4_USE__ == TRUE) */
    }
    else{
        /* PRM:RIMID Error(SIZE Error) */
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1 u1_d_RimMod_1B2CRam_WriteU4(const U2 u2_a_ID, const U4 u4_a_DATA)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_ID   : RimId                                                                                            */
/*                  --> u4_a_DATA : Write Data                                                                                       */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1 u1_d_RimMod_1B2CRam_WriteU4(const U2 u2_a_ID, const U4 u4_a_DATA)
{
    U1  u1_t_ret;
    U2  u2_t_rimsize;
    U2  u2_t_dataid;

    u1_t_ret     = (U1)RIM_RESULT_NG_PRM_ID;

    u2_t_rimsize = u2_g_RIM_GET_RIMSIZE(u2_a_ID);
    u2_t_dataid  = u2_a_ID & u2_d_RIM_MOD_1B2CRAM_DATA_ID_MASK;

    if(u2_t_rimsize == (U2)RIMID_RIMSIZE_1BYTE){
#if (__RIM_MOD_1B2CRAM_U1_USE__ == TRUE)
        if(u2_t_dataid < u2_d_RIM_MOD_1B2CRAM_U1_ID_NUM){
            u1_dp_rimmod_1b2c_byte_main[u2_t_dataid]  = (U1)u4_a_DATA;
            u1_dp_rimmod_1b2c_byte_mirr1[u2_t_dataid] = (U1)u4_a_DATA;
            u1_dp_rimmod_1b2c_byte_mirr2[u2_t_dataid] = (U1)u4_a_DATA;

            u1_t_ret = (U1)RIM_RESULT_OK;
        }
        else{
            /* PRM:RIMID Error(DataId Error) */
        }
#endif  /* #if (__RIM_MOD_1B2CRAM_U1_USE__ == TRUE) */
    }
    else if(u2_t_rimsize == (U2)RIMID_RIMSIZE_2BYTE){
#if (__RIM_MOD_1B2CRAM_U2_USE__ == TRUE)
        if(u2_t_dataid < u2_d_RIM_MOD_1B2CRAM_U2_ID_NUM){
            u2_dp_rimmod_1b2c_half_main[u2_t_dataid]  = (U2)u4_a_DATA;
            u2_dp_rimmod_1b2c_half_mirr1[u2_t_dataid] = (U2)u4_a_DATA;
            u2_dp_rimmod_1b2c_half_mirr2[u2_t_dataid] = (U2)u4_a_DATA;

            u1_t_ret = (U1)RIM_RESULT_OK;
        }
        else{
            /* PRM:RIMID Error(DataId Error) */
        }
#endif  /* #if (__RIM_MOD_1B2CRAM_U2_USE__ == TRUE) */
    }
    else if(u2_t_rimsize == (U2)RIMID_RIMSIZE_4BYTE){
#if (__RIM_MOD_1B2CRAM_U4_USE__ == TRUE)
        if(u2_t_dataid < u2_d_RIM_MOD_1B2CRAM_U4_ID_NUM){
            u4_dp_rimmod_1b2c_word_main[u2_t_dataid]  = u4_a_DATA;
            u4_dp_rimmod_1b2c_word_mirr1[u2_t_dataid] = u4_a_DATA;
            u4_dp_rimmod_1b2c_word_mirr2[u2_t_dataid] = u4_a_DATA;

            u1_t_ret = (U1)RIM_RESULT_OK;
        }
        else{
            /* PRM:RIMID Error(DataId Error) */
        }
#endif  /* #if (__RIM_MOD_1B2CRAM_U4_USE__ == TRUE) */
    }
    else{
        /* PRM:RIMID Error(SIZE Error) */
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static inline U2    u2_s_RimMod_1B2C_RId(const U2 u2_a_SIZE, const U2 u2_a_DATAID)                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
static inline U2    u2_s_RimMod_1B2C_RId(const U2 u2_a_SIZE, const U2 u2_a_DATAID)
{
    return((u2_a_SIZE & (U2)RIMID_RIMSIZE_MASK             ) |
           (u2_d_RIM_MOD_1B2CRAM_MODULE_ID                 ) |
           (u2_a_DATAID & u2_d_RIM_MOD_1B2CRAM_DATA_ID_MASK));
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
/*  1.2.0           09/07/2015  HK      Logic change of "vd_d_RimMod_1B2CRam_DeInit"                                                 */
/*  1.2.1           10/07/2015  HK      Expand DataID to 9bit                                                                        */
/*  1.2.2           02/29/2016  HK      Correspond non-library                                                                       */
/*  1.2.3           12/07/2016  HK      Fixed AIP3GBSW-25 issue.                                                                     */
/*  1.2.4            9/30/2021  TN      QAC warning MISRA-C Rule-5.1 was fixed.                                                      */
/*  1.3.0           10/ 5/2021  TN      QAC warning MISRA-C Rule-2.2 was fixed.                                                      */
/*  1.3.1           11/ 8/2023  KN      Improvement : Warning MISRA-C-Rule7.2 was fixed.                                             */
/*                                                                                                                                   */
/*  * KM      = Kazuyuki Makino, Denso Create                                                                                        */
/*  * MH      = Masayuki Hattori, Denso                                                                                              */
/*  * HK      = Hayato Kanamori, Denso Create                                                                                        */
/*  * TN      = Takashi Nagai, DENSO                                                                                                 */
/*  * KN      = Keigo Nomura   , Denso Create                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
