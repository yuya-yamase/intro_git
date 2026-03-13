/* Dcm_Dsp_SID10_Callout_c(v5-0-0)                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID10_Callout/CODE                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID10_Callout.h>
#if ( DCM_SUPPORT_SID10 == STD_ON )

#include <Dcm.h>

#include "oxdocan_aubif.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_PROGRAMMING_SESSION    ((uint8)0x02U)

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
/* Function Name | Dcm_SetProgConditions                                    */
/* Description   | The Dcm_SetProgConditions callout allows the integrator  */
/*               | to store relevant information prior to jumping to        */
/*               | bootloader.                                              */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus       : Operation state                    */
/*               | [IN] ProgConditions : Conditions on which the jump to    */
/*               |                       bootloader has been requested      */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Conditions have correctly been set */
/*               |   E_NOT_OK          : Conditions cannot be set           */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | If this function is called for session where application */
/*               | (DCM) sends final response, only E_OK must be returned.  */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE_CALLOUT ) Dcm_SetProgConditions
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_ProgConditionsType, AUTOMATIC, DCM_APPL_DATA ) ProgConditions
)
{
    return((Std_ReturnType)E_OK);
}

/****************************************************************************/
/* Function Name | Dcm_CheckSessionControl                                  */
/* Description   | Check processing of SessionControl                       */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1SubFunction     : Sub function                    */
/*               | [IN] OpStatus          : Operation state                 */
/*               | [OUT] ptErrorCode      : NRC                             */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK             : Check OK                            */
/*               |   E_NOT_OK         : Check NG                            */
/*               |   DCM_E_PENDING    : Pending                             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE_CALLOUT ) Dcm_CheckSessionControl
(
    const uint8 u1SubFunction,
    Dcm_OpStatusType OpStatus,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
)
{
    Std_ReturnType               u1_RetVal;
    Dcm_NegativeResponseCodeType u1_t_errcode;

    if(u1SubFunction == DCM_PROGRAMMING_SESSION){
        if(OpStatus == DCM_INITIAL){
            u1_t_errcode = DCM_E_CONDITIONSNOTCORRECT;
            u1_RetVal = u1_g_oXDoCANAubIfRpgToAct(&u1_t_errcode);
            if(u1_RetVal == (Std_ReturnType)E_NOT_OK){
                (*ptErrorCode) = u1_t_errcode;
            }
            else{
                u1_RetVal = (Std_ReturnType)DCM_E_PENDING;
            }
        }
        else{
            u1_RetVal = u1_g_oXDoCANAubIfRpgToRun(OpStatus);
            if(u1_RetVal == (Std_ReturnType)E_NOT_OK){
                (*ptErrorCode) = DCM_E_CONDITIONSNOTCORRECT;
            }
        }
    }
    else{
        u1_RetVal = (Std_ReturnType)E_OK;
    }

    return(u1_RetVal);
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define DCM_STOP_SEC_CODE_CALLOUT
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID10 == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v5-0-0         :2022-03-29                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
