/* 1.3.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  RIM : FUNC                                                                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RIM_FUNC_C_MAJOR                         (1U)
#define RIM_FUNC_C_MINOR                         (3U)
#define RIM_FUNC_C_PATCH                         (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include "rim_ctl.h"
#include "rim_func_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((RIM_FUNC_C_MAJOR != RIM_FUNC_H_MAJOR) || \
     (RIM_FUNC_C_MINOR != RIM_FUNC_H_MINOR) || \
     (RIM_FUNC_C_PATCH != RIM_FUNC_H_PATCH))
#error "rim_func.c and rim_func_private.h : source and header files are inconsistent!"
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
/*  U1      u1_d_Rim_MajorityU1Data(U4 *u4_ap_pdst, U1 *u1_ap_a, U1 *u1_ap_b, U1 *u1_ap_c)                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u4_ap_pdst : Result Data                                                                                    */
/*                  --> *u1_ap_a    : DATA a                                                                                         */
/*                  --> *u1_ap_b    : DATA b                                                                                         */
/*                  --> *u1_ap_c    : DATA c                                                                                         */
/*  Return:         U1 u1_t_ret     : Result(RIM_RESULT)                                                                             */
/*===================================================================================================================================*/
U1      u1_d_Rim_MajorityU1Data(U4 *u4_ap_pdst, U1 *u1_ap_a, U1 *u1_ap_b, U1 *u1_ap_c)
{
    U1  u1_t_ret;
    U1  u1_t_major;
    U1  u1_t_data_a;
    U1  u1_t_data_b;
    U1  u1_t_data_c;

    u1_t_data_a = *u1_ap_a;
    u1_t_data_b = *u1_ap_b;
    u1_t_data_c = *u1_ap_c;

    u1_t_major = u1_d_Rim_MajorityByDataU4((U4)u1_t_data_a, (U4)u1_t_data_b, (U4)u1_t_data_c);
    if(u1_t_major == (U1)RIM_MAJOR_OK){
        *u4_ap_pdst = (U4)u1_t_data_a;
        u1_t_ret = (U1)RIM_RESULT_OK;
    }
    else if(u1_t_major == (U1)RIM_MAJOR_NG_A){
        *u1_ap_a = u1_t_data_b;
        *u4_ap_pdst = (U4)u1_t_data_b;
        u1_t_ret = (U1)RIM_RESULT_OK_REPAIRED;
    }
    else if(u1_t_major == (U1)RIM_MAJOR_NG_B){
        *u1_ap_b = u1_t_data_a;
        *u4_ap_pdst = (U4)u1_t_data_a;
        u1_t_ret = (U1)RIM_RESULT_OK_REPAIRED;
    }
    else if(u1_t_major == (U1)RIM_MAJOR_NG_C){
        *u1_ap_c = u1_t_data_a;
        *u4_ap_pdst = (U4)u1_t_data_a;
        u1_t_ret = (U1)RIM_RESULT_OK_REPAIRED;
    }
    else{
        u1_t_ret = (U1)RIM_RESULT_NG_DATA;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_d_Rim_MajorityU2Data(U4 *u4_ap_pdst, U2 *u2_ap_a, U2 *u2_ap_b, U2 *u2_ap_c)                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u4_ap_pdst : Result Data                                                                                    */
/*                  --> *u2_ap_a    : DATA a                                                                                         */
/*                  --> *u2_ap_b    : DATA b                                                                                         */
/*                  --> *u2_ap_c    : DATA c                                                                                         */
/*  Return:         U1 u1_t_ret     : Result(RIM_RESULT)                                                                             */
/*===================================================================================================================================*/
U1      u1_d_Rim_MajorityU2Data(U4 *u4_ap_pdst, U2 *u2_ap_a, U2 *u2_ap_b, U2 *u2_ap_c)
{
    U1  u1_t_ret;
    U1  u1_t_major;
    U2  u2_t_data_a;
    U2  u2_t_data_b;
    U2  u2_t_data_c;

    u2_t_data_a = *u2_ap_a;
    u2_t_data_b = *u2_ap_b;
    u2_t_data_c = *u2_ap_c;

    u1_t_major = u1_d_Rim_MajorityByDataU4((U4)u2_t_data_a, (U4)u2_t_data_b, (U4)u2_t_data_c);
    if(u1_t_major == (U1)RIM_MAJOR_OK){
        *u4_ap_pdst = (U4)u2_t_data_a;
        u1_t_ret = (U1)RIM_RESULT_OK;
    }
    else if(u1_t_major == (U1)RIM_MAJOR_NG_A){
        *u2_ap_a = u2_t_data_b;
        *u4_ap_pdst = (U4)u2_t_data_b;
        u1_t_ret = (U1)RIM_RESULT_OK_REPAIRED;
    }
    else if(u1_t_major == (U1)RIM_MAJOR_NG_B){
        *u2_ap_b = u2_t_data_a;
        *u4_ap_pdst = (U4)u2_t_data_a;
        u1_t_ret = (U1)RIM_RESULT_OK_REPAIRED;
    }
    else if(u1_t_major == (U1)RIM_MAJOR_NG_C){
        *u2_ap_c = u2_t_data_a;
        *u4_ap_pdst = (U4)u2_t_data_a;
        u1_t_ret = (U1)RIM_RESULT_OK_REPAIRED;
    }
    else{
        u1_t_ret = (U1)RIM_RESULT_NG_DATA;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_d_Rim_MajorityU4Data(U4 *u4_ap_pdst, U4 *u4_ap_a, U4 *u4_ap_b, U4 *u4_ap_c)                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u4_ap_pdst : Result Data                                                                                    */
/*                  --> *u4_ap_a    : DATA a                                                                                         */
/*                  --> *u4_ap_b    : DATA b                                                                                         */
/*                  --> *u4_ap_c    : DATA c                                                                                         */
/*  Return:         U1 u1_t_ret     : Result(RIM_RESULT)                                                                             */
/*===================================================================================================================================*/
U1      u1_d_Rim_MajorityU4Data(U4 *u4_ap_pdst, U4 *u4_ap_a, U4 *u4_ap_b, U4 *u4_ap_c)
{
    U1  u1_t_ret;
    U1  u1_t_major;
    U4  u4_t_data_a;
    U4  u4_t_data_b;
    U4  u4_t_data_c;

    u4_t_data_a = *u4_ap_a;
    u4_t_data_b = *u4_ap_b;
    u4_t_data_c = *u4_ap_c;

    u1_t_major = u1_d_Rim_MajorityByDataU4(u4_t_data_a, u4_t_data_b, u4_t_data_c);
    if(u1_t_major == (U1)RIM_MAJOR_OK){
        *u4_ap_pdst = u4_t_data_a;
        u1_t_ret = (U1)RIM_RESULT_OK;
    }
    else if(u1_t_major == (U1)RIM_MAJOR_NG_A){
        *u4_ap_a = u4_t_data_b;
        *u4_ap_pdst = u4_t_data_b;
        u1_t_ret = (U1)RIM_RESULT_OK_REPAIRED;
    }
    else if(u1_t_major == (U1)RIM_MAJOR_NG_B){
        *u4_ap_b = u4_t_data_a;
        *u4_ap_pdst = u4_t_data_a;
        u1_t_ret = (U1)RIM_RESULT_OK_REPAIRED;
    }
    else if(u1_t_major == (U1)RIM_MAJOR_NG_C){
        *u4_ap_c = u4_t_data_a;
        *u4_ap_pdst = u4_t_data_a;
        u1_t_ret = (U1)RIM_RESULT_OK_REPAIRED;
    }
    else{
        u1_t_ret = (U1)RIM_RESULT_NG_DATA;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_d_Rim_MajorityByDataU4(const U4 u4_a_A, const U4 u4_a_B, const U4 u4_a_C)                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u4_ap_A : DATA a                                                                                            */
/*                  --> *u4_ap_B : DATA b                                                                                            */
/*                  --> *u4_ap_C : DATA c                                                                                            */
/*  Return:         U1 u1_t_ret  : Result(RIM_MAJOR)                                                                                 */
/*===================================================================================================================================*/
U1      u1_d_Rim_MajorityByDataU4(const U4 u4_a_A, const U4 u4_a_B, const U4 u4_a_C)
{
    U1  u1_t_ret;

    u1_t_ret = (U1)RIM_MAJOR_NG_ALL;

    if(u4_a_A == u4_a_B){
        if(u4_a_A == u4_a_C){
            /* A == B == C */
            u1_t_ret = (U1)RIM_MAJOR_OK;
        }
        else{
            u1_t_ret = (U1)RIM_MAJOR_NG_C;
        }
    }
    else if(u4_a_A == u4_a_C){
        u1_t_ret = (U1)RIM_MAJOR_NG_B;
    }
    else if(u4_a_B == u4_a_C){
            u1_t_ret = (U1)RIM_MAJOR_NG_A;
    }
    else{
        /* A != B != C */
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_d_Rim_MajorityByDataOther(const U4 *u4_ap_A, const U4 *u4_ap_B, const U4 *u4_ap_C, const U2 u2_a_NLONG)               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u4_ap_A   : DATA A                                                                                          */
/*                  --> *u4_ap_B   : DATA B                                                                                          */
/*                  --> *u4_ap_C   : DATA C                                                                                          */
/*                  --> u2_a_NLONG : Size                                                                                            */
/*  Return:         U1 u1_t_ret    : Result(RIM_MAJOR)                                                                               */
/*===================================================================================================================================*/
U1      u1_d_Rim_MajorityByDataOther(const U4 *u4_ap_A, const U4 *u4_ap_B, const U4 *u4_ap_C, const U2 u2_a_NLONG)
{
    U1  u1_t_ret;
    U1  u1_t_comp_ab;
    U1  u1_t_comp_ac;
    U1  u1_t_comp_bc;

    u1_t_ret = (U1)RIM_MAJOR_NG_ALL;

    u1_t_comp_ab = u1_d_Rim_CompareOther(u4_ap_A, u4_ap_B, u2_a_NLONG);
    u1_t_comp_ac = u1_d_Rim_CompareOther(u4_ap_A, u4_ap_C, u2_a_NLONG);
    if(u1_t_comp_ab == (U1)TRUE){
        if(u1_t_comp_ac == (U1)TRUE){
            /* A == B == C */
            u1_t_ret = (U1)RIM_MAJOR_OK;
        }
        else{
            u1_t_ret = (U1)RIM_MAJOR_NG_C;
        }
    }
    else if(u1_t_comp_ac == (U1)TRUE){
        u1_t_ret = (U1)RIM_MAJOR_NG_B;
    }
    else{
        u1_t_comp_bc = u1_d_Rim_CompareOther(u4_ap_B, u4_ap_C, u2_a_NLONG);
        if(u1_t_comp_bc == (U1)TRUE){
            u1_t_ret = (U1)RIM_MAJOR_NG_A;
        }
        else{
        /* A != B != C */
        }
    }

    return(u1_t_ret);
}


/*===================================================================================================================================*/
/*  U1 u1_d_Rim_CompareOther(const U4 *u4_ap_A, const U4 *u4_ap_B, const U2 u2_a_NLONG)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u4_ap_A   : DATA A                                                                                          */
/*                  --> *u4_ap_B   : DATA B                                                                                          */
/*                  --> u2_a_NLONG : Size                                                                                            */
/*  Return:         U1 u1_t_ret    : Result(TRUE/FALSE)                                                                              */
/*===================================================================================================================================*/
U1 u1_d_Rim_CompareOther(const U4 *u4_ap_A, const U4 *u4_ap_B, const U2 u2_a_NLONG)
{
    U4      u4_t_lpcnt;
    U1      u1_t_ret;

    u1_t_ret = (U1)TRUE;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u2_a_NLONG; u4_t_lpcnt++){

        if(u4_ap_A[u4_t_lpcnt] != u4_ap_B[u4_t_lpcnt]){
            u1_t_ret = (U1)FALSE;
            break;
        }
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U4      u4_d_Rim_GetCheckSumOther(const U4 *u4_ap_PSRC, const U2 u2_a_NLONG)                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> *u4_ap_PSRC : Data Pointer                                                                                   */
/*                  --> u2_a_NLONG  : Size                                                                                           */
/*  Return:         U4 u4_t_ret     : SUM                                                                                            */
/*===================================================================================================================================*/
U4      u4_d_Rim_GetCheckSumOther(const U4 *u4_ap_PSRC, const U2 u2_a_NLONG)
{
#if ((defined(__AIP_DEBUG_SIM__)) && (__AIP_DEBUG_SIM__==1U))
    return((U4)0U);
#else
    U4      u4_t_ret;
    U4      u4_t_lpcnt;

    u4_t_ret = (U4)0U;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u2_a_NLONG; u4_t_lpcnt++){
        u4_t_ret += u4_ap_PSRC[u4_t_lpcnt];
    }
    u4_t_ret ^= (U4)RIM_FUNC_CHECKSUM_KEY;

    return(u4_t_ret);
#endif /* #if ((defined(__AIP_DEBUG_SIM__)) && (__AIP_DEBUG_SIM__==1U)) */
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
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version         Date        Author  Change Description                                                                           */
/* ---------------  ----------  ------  -------------------------------------------------------------------------------------------  */
/*  1.0.0           11/17/2014  KM      New.                                                                                         */
/*  1.1.0           03/30/2015  MH      Update version check                                                                         */
/*  1.1.1           04/21/2015  KM      Mis-typecast was fixed.                                                                      */
/*  1.2.0           06/15/2015  MH      Updated checksum logic.                                                                      */
/*  1.2.1           07/14/2015  HK      Comment correction                                                                           */
/*                                      Revise a function return value                                                               */
/*  1.2.2           09/07/2015  HK      Comment correction                                                                           */
/*  1.2.3           09/09/2016  MH      Add compiler option for simulator.                                                           */
/*  1.2.4            7/16/2020  ST      Update u2_d_RIM_CHGSIZE_U1_TO_U4 to fix QAC warning.                                         */
/*  1.3.0            9/15/2021  TN      u4_a_NC was added because of MISAR-C Rule 18.1.                                              */
/*  1.3.1           11/ 8/2023  KN      Improvement : Warning MISRA-C-Rule7.2 was fixed.                                             */
/*                                                                                                                                   */
/*  * KM      = Kazuyuki Makino, Denso Create                                                                                        */
/*  * MH      = Masayuki Hattori, Denso                                                                                              */
/*  * HK      = Hayato Kanamori, Denso Create                                                                                        */
/*  * ST      = Shohei Takada, Denso Create                                                                                          */
/*  * TN      = Takashi Nagai, Denso                                                                                                 */
/*  * KN      = Keigo Nomura   , Denso Create                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
