/* Dcm_Dsp_SID27_Cfg_c(v5-3-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
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
#include <Dcm/Dcm_Dsp_SID27_Callout.h>
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
#define DCM_DSP_SID27_SUBFNC03  ((uint8)0x03U)
#define DCM_DSP_SID27_SUBFNC04  ((uint8)0x04U)

/*----------------*/
/* SeculityNumber */
/*----------------*/
#define DCM_DSP_SID27_SEC_LV2           ((uint8)2U)


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>
#if ( DCM_SUPPORT_SID27 == STD_ON )

/*---------MultiP--------*/
CONST( AB_83_ConstV Dcm_Dsp_SecurityNumType, DCM_CONFIG_DATA ) Dcm_Dsp_SecurityNumTbl[DCM_P_SECURITY_N_TBL] =
{
    { DCM_P_SECURITY02_ADR_SIZE_N },
    { (boolean)FALSE              }
};


/*--------param--------*/
CONST( AB_83_ConstV Dcm_Dsp_SecurityRowType, DCM_CONFIG_DATA ) Dcm_Dsp_SecurityParamTbl[DCM_P_SECURITY_N_TBL] =
{
    { (uint32)0UL,       (uint32)16UL,       (uint32)16UL,    &Dcm_SecLevel_GetSeed_Candi,    NULL_PTR,    &Dcm_SecLevel_CompareKey_Candi,      DCM_DSP_SID27_SEC_LV2  },
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
/* Function Name | Dcm_SID27_Sub03                                          */
/* Description   | SID27 request processing                                 */
/* Preconditions | None                                                     */
/* Parameters    | [IN]OpStatus       :Operation Status                     */
/*               | [IN]pMsgContext    :Message Context                      */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK               :Request was successful               */
/*               | DCM_E_PENDING      :Request is not yet finished          */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID27_Sub03
(
    Dcm_OpStatusType OpStatus,
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext
)
{
    Std_ReturnType u1_RetVal;
    
    u1_RetVal = Dcm_Dsp_SID27_RequestSeed( DCM_DSP_SID27_SUBFNC03, OpStatus, pMsgContext );
    
    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_SID27_Sub04                                          */
/* Description   | SID27 request processing                                 */
/* Preconditions | None                                                     */
/* Parameters    | [IN]OpStatus       :Operation Status                     */
/*               | [IN]pMsgContext    :Message Context                      */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK               :Request was successful               */
/*               | DCM_E_PENDING      :Request is not yet finished          */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID27_Sub04
(
    Dcm_OpStatusType OpStatus,
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext
)
{
    Std_ReturnType u1_RetVal;
    
    u1_RetVal = Dcm_Dsp_SID27_SendKey( DCM_DSP_SID27_SUBFNC04, OpStatus, pMsgContext );
    
    return u1_RetVal;
}





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
    const uint8 u1SecLvIndex,
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA) ptSecurityAccessDataRecord,       /* MISRA DEVIATION */
    const Dcm_OpStatusType u1OpStatus,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA) ptSeed,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode
)
{
    Std_ReturnType      u1_RetVal;

    u1_RetVal   = E_OK;
    
    if( Dcm_Dsp_SecurityParamTbl[u1SecLvIndex].ptGetSeed != NULL_PTR )
    {
#ifndef JGXSTACK
        u1_RetVal = Dcm_Dsp_SecurityParamTbl[u1SecLvIndex].ptGetSeed( u1OpStatus, ptSeed, ptErrorCode );
#else /* JGXSTACK */
        /* user-defined */
#endif /* JGXSTACK */
    }
    else
    {
        if( Dcm_Dsp_SecurityParamTbl[u1SecLvIndex].ptGetSeedADRSize != NULL_PTR )
        {
#ifndef JGXSTACK
            u1_RetVal = Dcm_Dsp_SecurityParamTbl[u1SecLvIndex].ptGetSeedADRSize( ptSecurityAccessDataRecord, u1OpStatus, ptSeed, ptErrorCode );
#else /* JGXSTACK */
            /* user-defined */
#endif /* JGXSTACK */
        }
    }

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
    const uint8 u1SecLvIndex,
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA ) ptKey,
    const Dcm_OpStatusType u1OpStatus,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
)
{
    Std_ReturnType      u1_RetVal;
    
    u1_RetVal   = E_OK;
    

    if( Dcm_Dsp_SecurityParamTbl[u1SecLvIndex].ptCompareKey != NULL_PTR )
    {
#ifndef JGXSTACK
        u1_RetVal = Dcm_Dsp_SecurityParamTbl[u1SecLvIndex].ptCompareKey( ptKey, u1OpStatus, ptErrorCode );
#else /* JGXSTACK */
        /* user-defined */
#endif /* JGXSTACK */
    }

    
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
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
