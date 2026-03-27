/* Dcm_Dsp_SID31_ChkSuptRid_Callout_c(v5-0-0)                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID31_ChkSuptRid_Callout/CODE                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID31_ChkSuptRid_Callout.h>
#if ( DCM_SUPPORT_SID31 == STD_ON )

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

/**********************************************************************************************************/
/* Function Name | Dcm_CheckSupportedRid                                                                  */
/* Description   | Requests if a specific RID is available.                                               */
/* Preconditions | None                                                                                   */
/* Parameters    | [IN] u2RoutineId : RID value                                                           */
/*               | [IN] u2PduId     : Received PduID                                                      */
/* Return Value  | Std_ReturnType                                                                         */
/*               |   E_OK              : RID Supported                                                    */
/*               |   E_NOT_OK          : RID Not Supported                                                */
/* Notes         | None                                                                                   */
/**********************************************************************************************************/
FUNC( Std_ReturnType, DCM_CODE_CALLOUT ) Dcm_CheckSupportedRid
(
    uint16 u2RoutineId,
    uint16 u2PduId
)
{
    Std_ReturnType u1_RetVal;
    
    u1_RetVal = E_NOT_OK;
    
    return u1_RetVal;
}

/**********************************************************************************************************/
/* Function Name | Dcm_CheckSupportedSubFuncForRid                                                        */
/* Description   | Requests if a specific RID Subfunction is available.                                   */
/* Preconditions | None                                                                                   */
/* Parameters    | [IN] u2RoutineId   : RID value                                                         */
/*               | [IN] u1SubFunction : RID Subfunction value                                             */
/*               | [IN] u2PduId       : Received PduID                                                    */
/* Return Value  | Std_ReturnType                                                                         */
/*               |   E_OK              : RID Subfunction Supported                                        */
/*               |   E_NOT_OK          : RID Subfunction Not Supported                                    */
/* Notes         | None                                                                                   */
/**********************************************************************************************************/
FUNC( Std_ReturnType, DCM_CODE_CALLOUT ) Dcm_CheckSupportedSubFuncForRid
(
    uint16 u2RoutineId,
    uint8  u1SubFunction,
    uint16 u2PduId
)
{
    Std_ReturnType u1_RetVal;
    
    u1_RetVal = E_NOT_OK;
    
    return u1_RetVal;
}

#define DCM_STOP_SEC_CODE_CALLOUT
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID31 == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-1-0         :2018-08-20                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v5-0-0         :2022-03-29                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
