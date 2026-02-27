/* Dcm_Dsp_SID86_Callout_c(v5-0-0)                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID86_Callout/CODE                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID86_Callout.h>
#include <Dcm.h>

#include "oxdocan_aubif.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

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
#define DCM_START_SEC_CONST
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_CONST
#include <Dcm_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE_CALLOUT
#include <Dcm_MemMap.h>

/****************************************************************************/
/* Function Name | Dcm_SetComparisonOfValues                                */
/* Description   | When there is a demand of onComparisonOfValues,          */
/*               | this function is started.                                */
/* Preconditions | None                                                     */
/* Parameters    | [IN]  u1RoeEventId  : RoeEventID                         */
/*               | [IN]  ptRecord      : Pointer to reception information   */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Accept onComparisonOfValues in     */
/*               |                       notice information                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE_CALLOUT ) Dcm_SetComparisonOfValues
(
    const uint8 u1RoeEventId,
    P2CONST( Dcm_ComparisonValueType, AUTOMATIC, DCM_APPL_DATA ) ptRecord
)
{
    Std_ReturnType u1_RetVal;
    
    u1_RetVal       = E_OK;
    
    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_CheckRoeCondition                                    */
/* Description   | Check Setup and Start Reuests.                           */
/* Preconditions | None                                                     */
/* Parameters    | [IN]  u1SubFunction  : SubFunction                       */
/*               | [IN]  u1EventWindowTime  : EventWindowTime               */
/*               | [IN]  ptEventTypeRecord  : Pointer to EventTypeRecord    */
/*               | [IN]  u1EventTypeRecordLength: Length of EventTypeRecord */
/*               | [OUT] ptErrorCode      : Pointer to NRC                  */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Accept this Request                */
/*               |   E_NOT_OK          : Not accept this Request            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE_CALLOUT ) Dcm_CheckRoeCondition
(
    const uint8 u1SubFunction,
    const uint8 u1EventWindowTime,
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA ) ptEventTypeRecord,
    const uint8 u1EventTypeRecordLength,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
)
{
    Std_ReturnType u1_RetVal;
    uint8           u1_t_res;

    if(u1SubFunction == (U1)0x03U){
        /* Check DID of EventTypeRecord */
        u1_t_res = u1_g_oXDoCANAubIfRoeChkDidSup(ptEventTypeRecord);
        if(u1_t_res != E_OK){
            *ptErrorCode = DCM_E_REQUESTOUTOFRANGE;
    u1_RetVal       = E_NOT_OK;
        }
        else{
            /* Check serviceToRespondToRecord */
            u1_RetVal = u1_g_oXDoCANAubIfRoeChkServToRes(ptErrorCode);
        }
    }
    else{
        u1_RetVal = E_OK;
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_IndicateRoeStatusChange                              */
/* Description   | Notify of a Status Change in the ROE Event State.        */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Accept this Request                */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE_CALLOUT ) Dcm_IndicateRoeStatusChange
(
    void
)
{
    Std_ReturnType u1_RetVal;
    
    u1_RetVal       = E_OK;
    
    return u1_RetVal;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define DCM_STOP_SEC_CODE_CALLOUT
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
