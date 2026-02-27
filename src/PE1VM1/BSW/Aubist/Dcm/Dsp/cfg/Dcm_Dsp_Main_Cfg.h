/* Dcm_Dsp_Main_Cfg_h(v5-6-0)                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_Main_Cfg/HEADER                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_MAIN_CFG_H
#define DCM_DSP_MAIN_CFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSP_MAIN_INIT_FUNC_NUM           ( (uint8)6U )

#define DCM_DSP_MAIN_INIT_FUNC_TBL           ( (DCM_DSP_MAIN_INIT_FUNC_NUM + (uint8)1U) )
#define DCM_DSP_DATA_DEFAULT_ENDIANNESS      ( DCM_DSP_LITTLE_ENDIAN )

#define DCM_DSP_MAIN_NOTIFIWRONGREQ_NUM      ( (uint8)1U )
#define DCM_DSP_MAIN_NOTIFIWRONGREQ_TBL      ( (DCM_DSP_MAIN_NOTIFIWRONGREQ_NUM + (uint8)1U) )

#define DCM_P_MAIN_SLPPERMISSION_FNC_NUM     ( (uint8)1U )
#define DCM_P_MAIN_SLPPERMISSION_FNC_TBL     ( (DCM_P_MAIN_SLPPERMISSION_FNC_NUM + (uint8)1U) )

#define DCM_DSP_MAIN_PREWRITEALL_FUNC_NUM    ( (uint8)1U )
#define DCM_DSP_MAIN_PREWRITEALL_FUNC_TBL    ( (DCM_DSP_MAIN_PREWRITEALL_FUNC_NUM + (uint8)1U) )

#define DCM_DSP_MAIN_REFRESH_FUNC_NUM        ( (uint8)3U )
#define DCM_DSP_MAIN_REFRESH_FUNC_TBL        ( (DCM_DSP_MAIN_REFRESH_FUNC_NUM + (uint8)1U) )

#define DCM_DSP_MAIN_ACTIVERESP_FUNC_NUM     ( (uint8)1U )

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef P2FUNC( void, DCM_CODE, Dcm_Dsp_Main_Init_FuncType )( void );
typedef CONSTP2FUNC( void, DCM_CODE, Dcm_Dsp_Main_NtfiWroRq_FuncType )( const Dcm_NegativeResponseCodeType u1ErrorCode );
typedef P2FUNC( boolean, DCM_CODE, Dcm_P_Main_SlpPermission_FuncType )( void );
typedef P2FUNC( void, DCM_CODE, Dcm_Dsp_Main_PreWriteAll_FuncType )( void );
typedef P2FUNC( void, DCM_CODE, Dcm_Dsp_Main_Refresh_FuncType )( void );
typedef P2FUNC( void, DCM_CODE, Dcm_Dsp_Main_GetActiveResp_FuncType )
(
    P2VAR( Dcm_ActiveStateType, AUTOMATIC, DCM_APPL_DATA ) ptActive
);
typedef P2FUNC( void, DCM_CODE, Dcm_Dsp_Main_SetActiveResp_FuncType )
(
    const Dcm_ActiveStateType u1ActiveStatus
);

typedef struct
{
    uint8 u1SID;
    Dcm_Dsp_Main_NtfiWroRq_FuncType ptFunc;
}Dcm_Dsp_Main_NtfiWroRqType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

extern CONST ( AB_83_ConstV Dcm_Dsp_Main_Init_FuncType, DCM_CONFIG_DATA ) Dcm_Dsp_Main_InitFunc_Tbl[ DCM_DSP_MAIN_INIT_FUNC_TBL ];
extern CONST ( AB_83_ConstV Dcm_Dsp_Main_NtfiWroRqType, DCM_CONFIG_DATA ) Dcm_Dsp_Main_NtfiWroRq_Tbl[ DCM_DSP_MAIN_NOTIFIWRONGREQ_TBL ];
extern CONST ( AB_83_ConstV Dcm_P_Main_SlpPermission_FuncType, DCM_CONFIG_DATA ) Dcm_P_Main_SlpPermissionFunc_Tbl[ DCM_P_MAIN_SLPPERMISSION_FNC_TBL ];
extern CONST ( AB_83_ConstV Dcm_Dsp_Main_PreWriteAll_FuncType, DCM_CONFIG_DATA ) Dcm_Dsp_Main_PreWriteAllFunc_Tbl[ DCM_DSP_MAIN_PREWRITEALL_FUNC_TBL ];
extern CONST ( AB_83_ConstV Dcm_Dsp_Main_Refresh_FuncType, DCM_CONFIG_DATA ) Dcm_Dsp_Main_RefreshFunc_Tbl[ DCM_DSP_MAIN_REFRESH_FUNC_TBL ];
extern CONST ( AB_83_ConstV Dcm_Dsp_Main_GetActiveResp_FuncType, DCM_CONFIG_DATA ) Dcm_Dsp_Main_GetActiveRespFunc_Tbl[ DCM_DSP_MAIN_ACTIVERESP_FUNC_NUM ];
extern CONST ( AB_83_ConstV Dcm_Dsp_Main_SetActiveResp_FuncType, DCM_CONFIG_DATA ) Dcm_Dsp_Main_SetActiveRespFunc_Tbl[ DCM_DSP_MAIN_ACTIVERESP_FUNC_NUM ];
extern CONST ( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsp_Main_u1Refresh_Func_Num;
extern CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsp_Main_u1Init_Func_Num;
#if ( DCM_SUPPORT_SID31 == STD_ON )
extern CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsp_u1Data_Default_Endianness;
#endif /* DCM_SUPPORT_SID31 == STD_ON */
extern CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsp_Main_u1Notifiwrongreq_Num;
extern CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsp_Main_u1Slppermission_Fnc_Num;
extern CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsp_Main_u1ActiveResp_Func_Num;
extern CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsp_Main_u1PreWriteAll_Fnc_Num;

#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

#endif /* DCM_DSP_MAIN_CFG_H */

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
