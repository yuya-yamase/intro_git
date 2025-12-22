/* Dcm_Dsl_AuthMng_Connector_c(v5-0-0)                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsl_AuthMng_Connector/CODE                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>
#include "../../Dsl/usr/Dcm_Dsl_AuthMng_Connector.h"

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

#if( DCM_AUTHENTICATION_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_Cnct_Switch_AuthState                            */
/* Description   | Rte_Switch_DcmAuthenticationState_{Connection} call      */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1Mode         : Next mode                          */
/*               | [in] u2ConnectionId : ConnectionId                       */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK         : Processing normal                       */
/*               |   E_NOT_OK     : Queue overflow                          */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsl_Cnct_Switch_AuthState
(
    const uint8 u1Mode,
    const uint16 u2ConnectionId
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = (Std_ReturnType)E_OK;

    /* u1_Ret = SchM_Switch_DcmAuthenticationState_ConnectionName(u1Mode); */
    /* if( u1_Ret != (Std_ReturnType)RTE_E_OK )                            */
    /* {                                                                   */
    /*     u1_RetVal = (Std_ReturnType)E_NOT_OK;                           */
    /* }                                                                   */

    return u1_RetVal;

}
#endif /* DCM_AUTHENTICATION_USE == STD_ON */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
