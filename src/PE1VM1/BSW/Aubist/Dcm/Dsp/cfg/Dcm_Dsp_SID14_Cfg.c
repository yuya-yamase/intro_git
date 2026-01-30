/* Dcm_Dsp_SID14_Cfg_c(v5-8-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID14_Cfg/CODE                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../Dsp/cfg/Dcm_Dsp_SID14_Cfg.h"
#if ( DCM_SUPPORT_SID14 == STD_ON )
#include <Dcm/Dcm_Dsp_SID14_Callout.h>

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
#define DCM_START_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID14_CheckSWC                                   */
/* Description   | This function starts the condition check function of the */
/*               | SWC by a direct call, and return a result.               */
/* Preconditions | None                                                     */
/* Parameters    | [IN]  u1OpStatus  : Status of operation                  */
/*               | [IN]  u4GoDTC     : Group of DTC                         */
/*               | [OUT] ptErrorCode : Negative Response Code Value         */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK            : ClearDTC Condition Check OK          */
/*               |   E_NOT_OK        : ClearDTC Condition Check NG          */
/* Notes         | Generated as DcmDspClearDTCAsyncCheck is FALSE           */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID14_CheckSWC
(
    const Dcm_OpStatusType u1OpStatus, /* MISRA DEVIATION */
    const uint32           u4GoDTC,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
)
{
    Std_ReturnType u1_RetVal;
    
    u1_RetVal = Dem_ClearDTCCheckFnc( u4GoDTC, ptErrorCode );
    
    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID14_CheckTheClearDTCRequestIsAcceptable        */
/* Description   | This function starts the Acceptable condition check      */
/*               | function of the SWC by a direct call, and return a       */
/*               | result.                                                  */
/* Preconditions | None                                                     */
/* Parameters    | [IN]  u2PduId     : Received PduId                       */
/*               | [IN]  u4GroupOfDTC : Group of DTC                        */
/*               | [IN]  bMemorySelectionUse : MemorySelection Enabled      */
/*               | [IN]  u1MemorySelectionValue : MemorySelection Value     */
/*               | [OUT] ptErrorCode : Negative Response Code Value         */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK          : The ClearDTC reuest is acceptable      */
/*               |   E_NOT_OK      : The ClearDTC reuest is not acceptable  */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID14_CheckTheClearDTCRequestIsAcceptable
(
    const uint16      u2PduId,
    const uint32      u4GroupOfDTC,
    const boolean     bMemorySelectionUse,
    const uint8       u1MemorySelectionValue,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
)
{
    Std_ReturnType u1_RetVal;
    
    u1_RetVal = Dcm_CheckTheClearDTCRequestIsAcceptable( u2PduId, u4GroupOfDTC, bMemorySelectionUse, u1MemorySelectionValue, ptErrorCode );
    
    return u1_RetVal;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID14 == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
