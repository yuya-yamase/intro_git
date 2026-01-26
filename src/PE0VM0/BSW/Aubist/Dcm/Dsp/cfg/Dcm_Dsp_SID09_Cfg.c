/* Dcm_Dsp_SID09_Cfg_c(v5-3-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID09_Cfg/CODE                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../Dsp/cfg/Dcm_Dsp_SID09_Cfg.h"
#if( DCM_SUPPORT_SID09 == STD_ON )

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

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

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

CONST( AB_83_ConstV DcmDspVehInfoType, DCM_CONFIG_DATA ) DcmDspInfoTypeTbl[DCM_INFOTYPE_TBL] =
{
    { NULL_PTR,                    (uint8)0x00U,         (uint8)0x00U, (uint8)(STD_ON) } /* <---Dummy Data */
};

CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_P_SID09_u1SupInfoTypeNumber = DCM_SUPINFOTYPE_NUM;
CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_P_SID09_u1InfoTypeNumber = DCM_INFOTYPE_NUM;
static CONST( AB_83_ConstV boolean, DCM_CONFIG_DATA ) Dcm_P_SID09_InfoType08_Nofunc = FALSE;
static CONST( AB_83_ConstV boolean, DCM_CONFIG_DATA ) Dcm_P_SID09_InfoType0B_Nofunc = FALSE;

#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

#define DCM_START_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTVEHINFOINFOTYPE
#include <Dcm_MemMap.h>

CONST( AB_83_ConstV uint32, DCM_CONST_PBCONFIG_DIRECTLY_SUPPORTVEHINFOINFOTYPE ) DcmDspSupportInfoTypeTbl[DCM_SUPINFOTYPE_TBL] =
{
    (uint32)0x00000000U  /* <---Dummy Data */
};

#define DCM_STOP_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTVEHINFOINFOTYPE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>
/***********************************************************************************************************/
/* Function Name | Dcm_Dsp_SID09_JudgeDemIUMPRUse                                                          */
/* Description   | Determine whether to use the function of DEM-IUMPR                                      */
/* Preconditions | None                                                                                    */
/* Parameters    | [in] u1reqInfoType :                                                                    */
/*               |        Request InfoType                                                                 */
/* Return Value  | Std_ReturnType                                                                          */
/*               |   TRUE                : DEM-API Use setting                                             */
/*               |   FALSE               : DEM-API No-Use setting                                          */
/* Notes         | None                                                                                    */
/***********************************************************************************************************/
FUNC( boolean, DCM_CODE ) Dcm_Dsp_SID09_JudgeDemIUMPRUse
(
    CONST( Dcm_MsgItemType, AUTOMATIC ) u1reqInfoType
)
{
    boolean     b_IsDemCall;

    b_IsDemCall     = FALSE;

    if( u1reqInfoType == DCM_INFOTYPE08_NUM )
    {
        b_IsDemCall = Dcm_P_SID09_InfoType08_Nofunc;
    }
    else if( u1reqInfoType ==DCM_INFOTYPE0B_NUM )
    {
        b_IsDemCall = Dcm_P_SID09_InfoType0B_Nofunc;
    }
    else
    {
        /* No process */
    }
    

    return b_IsDemCall;
}



/***********************************************************************************************************/
/* Function Name | Dcm_Dsp_SID09_GetInfoTypeValue                                                          */
/* Description   | requests to DEM a data value of InfoType08/InfoType0B                                   */
/* Preconditions | None                                                                                    */
/* Parameters    | [IN] OpStatus         : Operation state                                                 */
/* Parameters    | [IN] u1reqInfoType    : Request InfoType                                                */
/*               | [OUT] DataValueBuffer : Data value buffer                                               */
/*               | [INOUT] BufferSize    : [IN] Size of Buffer / [OUT] Size of Data                        */
/* Return Value  | Std_ReturnType                                                                          */
/*               |   E_OK                : Request was successful                                          */
/*               |   E_NOT_OK            : Request was not successful                                      */
/* Notes         | None                                                                                    */
/***********************************************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID09_GetInfoTypeValue
(
    CONST( Dcm_OpStatusType, AUTOMATIC ) u1OpStatus,            /* MISRA DEVIATION */
    CONST( Dcm_MsgItemType, AUTOMATIC ) u1reqInfoType,          /* MISRA DEVIATION */
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) DataValueBuffer,   /* MISRA DEVIATION */
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) BufferSize         /* MISRA DEVIATION */
)
{
    Std_ReturnType  u1_RetVal;

    u1_RetVal = E_NOT_OK;

    return u1_RetVal;
}



/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID09 == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-05-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-5-1                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
