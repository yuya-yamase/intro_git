/****************************************************************************/
/* Protected                                                                */
/* Copyright Denso CO., LTD.                                                */
/****************************************************************************/

#ifndef IDSM_CALLOUT_USER_H
#define IDSM_CALLOUT_USER_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <IdsM.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/* IdsR Tx Callout Function */
Std_ReturnType IdsM_IdsRTxCallout
(
    const uint8* ptData, 
    uint16 u2DataSize
);

/* QSEv Error Callout Function */
void IdsM_QSEvErrCallout
(
    const uint8* ptEventFrame,
    const IdsM_TimestampType* ptTimestamp,
    const volatile uint8* ptContextData,
    uint16 u2ContextDataSize,
    IdsM_Ab_ErrorStatusType udQSEvError
);

/* Parameter Error Callout Function */
void IdsM_ParamErrCallout
(
    IdsM_SecurityEventIdType udSecurityEventId,
    IdsM_Ab_ErrorStatusType udParamError
);

/* Ram Error Callout Function */
void IdsM_RamErrCallout
(
    IdsM_Ab_ErrorStatusType udError
);

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* IDSM_CALLOUT_USER_H */

/*--------------------------------------------------------------------------*/
/* Revision History                                                         */
/*   Revision    :Date       :Description                                   */
/*   v1_00       :2025/11/14 :New                                            */
/*--------------------------------------------------------------------------*/
/* Notes                                                                    */
/**** End of File************************************************************/
