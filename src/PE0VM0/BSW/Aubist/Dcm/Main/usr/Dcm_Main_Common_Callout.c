/* Dcm_Main_Common_Callout_c(v5-0-0)                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Main_Common_Callout/CODE                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Main_Common_Callout.h>

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
/* Function Name | Dcm_GetProgConditions                                    */
/* Description   | The Dcm_GetProgConditions callout is called upon DCM     */
/*               | initialization and allows to determine if a response     */
/*               | (50 or 51) has to be sent depending on request within    */
/*               | the bootloader. The context parameter are defined in     */
/*               | Dcm_ProgConditionsType.                                  */
/* Preconditions | None                                                     */
/* Parameters    | [OUT] ProgConditions : Conditions on which the jump to   */
/*               |                        bootloader has been requested     */
/* Return Value  | Dcm_EcuStartModeType                                     */
/*               |   DCM_COLD_START : The ECU starts normally               */
/*               |   DCM_WARM_START : The ECU starts from a bootloader jump */
/*               |   Other user defined values : -                          */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dcm_EcuStartModeType, DCM_CODE_CALLOUT ) Dcm_GetProgConditions
(
    P2VAR( Dcm_ProgConditionsType, AUTOMATIC, DCM_APPL_DATA ) ProgConditions    /* MISRA DEVIATION */
)
{
    Dcm_EcuStartModeType u1_RetVal;

    u1_RetVal = DCM_COLD_START;

    return u1_RetVal;
}

#define DCM_STOP_SEC_CODE_CALLOUT
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-07-27                                              */
/*  v5-0-0         :2021-09-28                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-2                                              */
/*  BSW plug-in        :v5-5-1                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
