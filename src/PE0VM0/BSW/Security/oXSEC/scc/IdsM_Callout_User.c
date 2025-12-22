/****************************************************************************/
/* Protected                                                                */
/* Copyright Denso CO., LTD.                                                */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <IdsM.h>
#include "IdsM_User.h"

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

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/* IdsR Tx Callout Function */
Std_ReturnType IdsM_IdsRTxCallout
(
    const uint8* ptData, 
    uint16 u2DataSize
)
{
    return (Std_ReturnType)E_OK;
}

/* QSEv Error Callout Function */
void IdsM_QSEvErrCallout
(
    const uint8* ptEventFrame,
    const IdsM_TimestampType* ptTimestamp,
    const volatile uint8* ptContextData,
    uint16 u2ContextDataSize,
    IdsM_Ab_ErrorStatusType udQSEvError
)
{
    return;
}

/* Parameter Error Callout Function */
void IdsM_ParamErrCallout
(
    IdsM_SecurityEventIdType udSecurityEventId,
    IdsM_Ab_ErrorStatusType udParamError
)
{
    return;
}

/* Ram Error Callout Function */
void IdsM_RamErrCallout
(
    IdsM_Ab_ErrorStatusType udError
)
{
    return;
}

/*--------------------------------------------------------------------------*/
/* Revision History                                                         */
/*   Revision    :Date       :Description                                   */
/*   v1_00       :2025/11/14 :New                                            */
/*--------------------------------------------------------------------------*/
/* Notes                                                                    */
/**** End of File************************************************************/
