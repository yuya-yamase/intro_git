/* Dcm_Dsp_SID27_Cfg_c(v5-3-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID27_Cfg/CODE                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID27.h>
#include "../../Dsp/cfg/Dcm_Dsp_SID27_Cfg.h"
#include <Dcm.h>

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

#if ( DCM_SUPPORT_SID27 == STD_ON )
#endif /* DCM_SUPPORT_SID27 == STD_ON */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/*-----------------*/
/* SubFunction ID  */
/*-----------------*/

/*----------------*/
/* SeculityNumber */
/*----------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>
#if ( DCM_SUPPORT_SID27 == STD_ON )

/*---------MultiP--------*/
CONST( AB_83_ConstV Dcm_Dsp_SecurityNumType, DCM_CONFIG_DATA ) Dcm_Dsp_SecurityNumTbl[DCM_P_SECURITY_N_TBL] =
{
    { (boolean)FALSE              }
};


/*--------param--------*/
CONST( AB_83_ConstV Dcm_Dsp_SecurityRowType, DCM_CONFIG_DATA ) Dcm_Dsp_SecurityParamTbl[DCM_P_SECURITY_N_TBL] =
{
    { (uint32)0UL,    (uint32)0UL,       (uint32)0UL,    NULL_PTR,             NULL_PTR,     NULL_PTR,                 (uint8)0U  }
};


CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsp_u1Security_N = DCM_P_SECURITY_N;

#endif /* DCM_SUPPORT_SID27 == STD_ON */
#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>
#if ( DCM_SUPPORT_SID27 == STD_ON )






/****************************************************************************/
/* Function Name | Dcm_Dsp_SID27_CallGetSeedCout                            */
/* Description   | Xxx_GetSeed Function call                                */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1SecLvIndex :SecurityParamTbl Index                 */
/*               | [IN]ptSecurityAccessDataRecord                           */
/*               |          :Additional data for calculating the seed value */
/*               | [IN]u1OpStatus   :Status of the current operation        */
/*               | [OUT]ptSeed      :provided seed                          */
/*               | [OUT]ptErrorCode :NRC to be sent if E_NOT_OK is returned */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                     :Request was successful         */
/*               | E_NOT_OK                 :Request was not successful     */
/*               | DCM_E_PENDING            :Request is not yet finished    */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID27_CallGetSeedCout
(
    const uint8 u1SecLvIndex,                                                   /* MISRA DEVIATION */
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA) ptSecurityAccessDataRecord,       /* MISRA DEVIATION */
    const Dcm_OpStatusType u1OpStatus,                                          /* MISRA DEVIATION */
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA) ptSeed,                             /* MISRA DEVIATION */
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode   /* MISRA DEVIATION */
)
{
    Std_ReturnType      u1_RetVal;

    u1_RetVal   = E_OK;
    

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID27_CallCompKeyCout                            */
/* Description   | Xxx_CompareKey Function call                             */
/* Preconditions | None                                                     */
/* Parameters    | [IN]u1SecLvIndex :SecurityParamTbl Index                 */
/*               | [IN]ptKey        :Key, which needs to be compared        */
/*               | [IN]u1OpStatus   :Status of the current operation        */
/*               | [OUT]ptErrorCode :NRC to be sent if E_NOT_OK is returned */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                     :Request was successful         */
/*               | E_NOT_OK                 :Request was not successful     */
/*               | DCM_E_PENDING            :Request is not yet finished    */
/*               | DCM_E_COMPARE_KEY_FAILED :Key did not match              */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID27_CallCompKeyCout
(
    const uint8 u1SecLvIndex,                                                       /* MISRA DEVIATION */
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA ) ptKey,                               /* MISRA DEVIATION */
    const Dcm_OpStatusType u1OpStatus,                                              /* MISRA DEVIATION */
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode     /* MISRA DEVIATION */
)
{
    Std_ReturnType      u1_RetVal;
    
    u1_RetVal   = E_OK;
    


    
    return u1_RetVal;
}




/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#endif /* DCM_SUPPORT_SID27 == STD_ON */
#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v3-2-0         :2020-08-27                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-5-1                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
