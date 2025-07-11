/* Dcm_Dsl_Main_Callout_c(v5-3-0)                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsl_Main_Callout/CODE                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsl_Main_Callout.h>

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
/* Function Name | Dcm_IndicateSesCtrlChange                                */
/* Description   | Notify SW-C change of the session                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1SesCtrlTypeOld : old session control type value   */
/*               | [in] u1SesCtrlTypeNew : new session control type value   */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : this value is always returned.             */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE_CALLOUT) Dcm_IndicateSesCtrlChange
(
    const Dcm_SesCtrlType u1SesCtrlTypeOld,
    const Dcm_SesCtrlType u1SesCtrlTypeNew
)
{
    return E_OK;
}

/****************************************************************************/
/* Function Name | Dcm_IndicateSecLevelChange                               */
/* Description   | Notify SW-C change of the security                       */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1SecLevelOld : old session control type value      */
/*               | [in] u1SecLevelNew : new session control type value      */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : this value is always returned.             */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE_CALLOUT) Dcm_IndicateSecLevelChange
(
    const Dcm_SecLevelType u1SecLevelOld,
    const Dcm_SecLevelType u1SecLevelNew
)
{
    return E_OK;
}

/****************************************************************************/
/* Function Name | Dcm_ChangeClient                                         */
/* Description   | Confirm whether changing of the Rx channel is possible   */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduIdOld : old PduID                              */
/*               | [in] u2PduIdNew : new PduID                              */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Allow changing active clients              */
/*               |    E_NOT_OK : Transmit NRC 0x22                          */
/*               |    E_REQUEST_NOT_ACCEPTED : No response                  */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE_CALLOUT) Dcm_ChangeClient
(
    const uint16 u2PduIdOld,
    const uint16 u2PduIdNew
)
{
    Std_ReturnType u1_RetVal;
    u1_RetVal = E_NOT_OK;
    
    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_AcceptanceOfReception                                */
/* Description   | This function asks the user if it is okay to start       */
/*               | receiving.                                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2RxPduId : RxPduID                                 */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Allow the start of reception               */
/*               |    E_NOT_OK : Reject the start of reception              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE_CALLOUT) Dcm_AcceptanceOfReception
(
    const uint16 u2RxPduId
)
{
    Std_ReturnType u1_RetVal;
    u1_RetVal = E_OK;

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_BusyResponse                                         */
/* Description   | This function asks the user whether or not to send a     */
/*               | busy response when the reception is discarded.           */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2RxPduId : RxPduID                                 */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Allow response                             */
/*               |    E_NOT_OK : Reject the response                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE_CALLOUT) Dcm_BusyResponse
(
    const uint16 u2RxPduId
)
{
    Std_ReturnType u1_RetVal;
    u1_RetVal = E_NOT_OK;

    return u1_RetVal;
}


#define DCM_STOP_SEC_CODE_CALLOUT
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-2-0         :2020-08-27                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-3-z0003                                        */
/*  BSW plug-in        :v5-5-1                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
