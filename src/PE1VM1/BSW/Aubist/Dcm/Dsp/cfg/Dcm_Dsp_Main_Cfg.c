/* Dcm_Dsp_Main_Cfg_c(v5-6-0)                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_Main_Cfg/CODE                                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_Main.h>
#include <Dcm/Dcm_Dsp_DidMng.h>
#include <Dcm/Dcm_Dsp_SID10.h>
#include <Dcm/Dcm_Dsp_SID28.h>
#include <Dcm_Security.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

CONST ( AB_83_ConstV Dcm_Dsp_Main_Init_FuncType, DCM_CONFIG_DATA ) Dcm_Dsp_Main_InitFunc_Tbl[ DCM_DSP_MAIN_INIT_FUNC_TBL ] = 
{
    &Dcm_Dsp_DidMng_Init,
    &Dcm_Dsp_SID10_Init,
    &Dcm_Dsp_SID28_Init,
    NULL_PTR
};

CONST ( AB_83_ConstV Dcm_Dsp_Main_NtfiWroRqType, DCM_CONFIG_DATA ) Dcm_Dsp_Main_NtfiWroRq_Tbl[ DCM_DSP_MAIN_NOTIFIWRONGREQ_TBL ] = 
{
    { (uint8)0x00 , NULL_PTR                             }
};

CONST ( AB_83_ConstV Dcm_P_Main_SlpPermission_FuncType, DCM_CONFIG_DATA ) Dcm_P_Main_SlpPermissionFunc_Tbl[ DCM_P_MAIN_SLPPERMISSION_FNC_TBL ] = 
{
    NULL_PTR
};

CONST ( AB_83_ConstV Dcm_Dsp_Main_PreWriteAll_FuncType, DCM_CONFIG_DATA ) Dcm_Dsp_Main_PreWriteAllFunc_Tbl[ DCM_DSP_MAIN_PREWRITEALL_FUNC_TBL ] = 
{
    NULL_PTR
};

CONST ( AB_83_ConstV Dcm_Dsp_Main_Refresh_FuncType, DCM_CONFIG_DATA ) Dcm_Dsp_Main_RefreshFunc_Tbl[ DCM_DSP_MAIN_REFRESH_FUNC_TBL ] = 
{
    NULL_PTR
};

CONST ( AB_83_ConstV Dcm_Dsp_Main_GetActiveResp_FuncType, DCM_CONFIG_DATA ) Dcm_Dsp_Main_GetActiveRespFunc_Tbl[ DCM_DSP_MAIN_ACTIVERESP_FUNC_NUM ] = 
{
    NULL_PTR
};

CONST ( AB_83_ConstV Dcm_Dsp_Main_SetActiveResp_FuncType, DCM_CONFIG_DATA ) Dcm_Dsp_Main_SetActiveRespFunc_Tbl[ DCM_DSP_MAIN_ACTIVERESP_FUNC_NUM ] = 
{
    NULL_PTR
};

CONST ( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsp_Main_u1Refresh_Func_Num = DCM_DSP_MAIN_REFRESH_FUNC_NUM;
CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsp_Main_u1Init_Func_Num = DCM_DSP_MAIN_INIT_FUNC_NUM;
#if ( DCM_SUPPORT_SID31 == STD_ON )
CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsp_u1Data_Default_Endianness = (uint8)DCM_DSP_DATA_DEFAULT_ENDIANNESS;
#endif /* DCM_SUPPORT_SID31 == STD_ON */
CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsp_Main_u1Notifiwrongreq_Num = DCM_DSP_MAIN_NOTIFIWRONGREQ_NUM;
CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsp_Main_u1Slppermission_Fnc_Num = DCM_P_MAIN_SLPPERMISSION_FNC_NUM;
CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsp_Main_u1ActiveResp_Func_Num = DCM_DSP_MAIN_ACTIVERESP_FUNC_NUM;
CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsp_Main_u1PreWriteAll_Fnc_Num = DCM_DSP_MAIN_PREWRITEALL_FUNC_NUM;

#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v3-2-0         :2020-08-27                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-6-0         :2024-02-27                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
