/* Dcm_Dsl_CommHandling_Connector_c(v5-0-0)                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsl_CommHandling_Connector/CODE                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../Dsl/usr/Dcm_Dsl_CommHandling_Connector.h"
#include <BswM_CS.h>

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
/* Function Name | Dcm_Dsl_Cnct_ActiveDiagnostic                            */
/* Description   | This function is a connector for -                       */
/*               | ComM_DCM_ActiveDiagnostic function.                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1Channel : NetworkId(ComMChannelId)                */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_Cnct_ActiveDiagnostic
(
    uint8 u1Channel
)
{
    ComM_DCM_ActiveDiagnostic(u1Channel);

    return ;
}


/****************************************************************************/
/* Function Name | Dcm_Dsl_Cnct_InactiveDiagnostic                          */
/* Description   | This function is a connector for -                       */
/*               | ComM_DCM_InactiveDiagnostic function.                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1Channel : NetworkId(ComMChannelId)                */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_Cnct_InactiveDiagnostic
(
    uint8 u1Channel
)
{
    ComM_DCM_InactiveDiagnostic(u1Channel);

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Cnct_IsComTxEnable                               */
/* Description   | This function determines whether CS is ready for         */
/*               | transmission.                                            */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1Channel : NetworkId(ComMChannelId)                */
/*               |                                                          */
/* Return Value  | boolean                                                  */
/*               |        True  : Enable Communication                      */
/*               |        False : Disable Communication                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_Dsl_Cnct_IsComTxEnable
(
    const uint8 u1Channel
)
{
    boolean b_TxEnable;
    uint8   u1_Result;

    b_TxEnable = (boolean)TRUE;

    u1_Result = BswM_CS_GetTRXStatus(u1Channel);
    if( u1_Result != BSWM_CS_TRXST_TRX_ENABLE )
    {
        b_TxEnable = (boolean)FALSE;
    }

    return b_TxEnable;
}

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2022-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
