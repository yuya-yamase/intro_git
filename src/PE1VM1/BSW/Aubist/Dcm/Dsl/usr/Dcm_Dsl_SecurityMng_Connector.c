/* Dcm_Dsl_SecurityMng_Connector_c(v5-0-0)                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsl_SecurityMng_Connector/CODE                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>
#include "../../Dsl/usr/Dcm_Dsl_SecurityMng_Connector.h"

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
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* Function Name | Dcm_Dsl_Cnct_Switch_SecurityAccess                       */
/* Description   | SchM_Switch_Dcm_SecurityAccessModeSwitchInterface call   */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1Mode         : Next mode                          */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK         : Processing normal                       */
/*               |   E_NOT_OK     : Queue overflow                          */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsl_Cnct_Switch_SecurityAccess
(
    const uint8 u1Mode
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = (Std_ReturnType)E_OK;

    /* u1_Ret = SchM_Switch_Dcm_SecurityAccessModeSwitchInterface(u1Mode); */
    /* if( u1_Ret != (Std_ReturnType)SCHM_E_OK )                           */
    /* {                                                                   */
    /*     u1_RetVal = (Std_ReturnType)E_NOT_OK;                           */
    /* }                                                                   */

    return u1_RetVal;

}

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
