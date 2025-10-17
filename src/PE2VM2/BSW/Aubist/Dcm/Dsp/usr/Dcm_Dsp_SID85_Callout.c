/* Dcm_Dsp_SID85_Callout_c(v5-0-0)                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID85_Callout/CODE                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID85_Callout.h>
#if ( DCM_SUPPORT_SID85 == STD_ON )

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
/* Function Name | Dcm_CheckControlDTCSetting                               */
/* Description   | Take next step by this function.                         */
/*               | Confirm whether it is the situation that handling of     */
/*               | ControlDTCSetting appointed with the first argument      */
/*               | is possible. When possible, return E_OK,                 */
/*               | and return E_NOT_OK if impossible.                       */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1Mode         : Request mode                       */
/*               | [IN] u4DTCGroupe    : Group of DTC                       */
/*               | [IN] u1DTCKind      : Requested DTC Kind                 */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : ControlDTCSetting is possible      */
/*               |   E_NOT_OK          : ControlDTCSetting is impossible    */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE_CALLOUT ) Dcm_CheckControlDTCSetting
(
    const uint8             u1Mode,
    const uint32            u4DTCGroup,
    const Dem_DTCKindType   u1DTCKind
)
{
    Std_ReturnType u1_RetVal;
    
    u1_RetVal = E_NOT_OK;

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_ControlDTCSettingProcess                             */
/* Description   | Control the DTCSetting value by this function.           */
/*               | When the DTCSetting control is success, return E_OK,     */
/*               | and return E_NOT_OK if it is fail, and return            */
/*               | DCM_E_PENDING if it continue control.                    */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1Mode         : Request mode                       */
/*               | [IN] OpStatus       : Request OpStatus                   */
/*               | [IN] ptOptionRecord : Requested Option Record            */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Control success                    */
/*               |   DCM_E_PENDING     : Control continue                   */
/*               |   E_NOT_OK          : Control fail                       */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE_CALLOUT ) Dcm_ControlDTCSettingProcess
(
    const uint8          u1Mode,
    Dcm_OpStatusType                            OpStatus,
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA ) ptOptionRecord
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = (Std_ReturnType)E_NOT_OK;

    return u1_RetVal;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define DCM_STOP_SEC_CODE_CALLOUT
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID85 == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v3-2-0         :2020-08-27                                              */
/*  v5-0-0         :2022-03-29                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-5-1                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
