/* Rte_SecOC_Type_h_v2-1-0                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | Rte/SecOC/Type/HEADER                                      */
/*--------------------------------------------------------------------------*/
/* Notes                                                                    */
/****************************************************************************/

#ifndef RTE_SECOC_TYPE_H
#define RTE_SECOC_TYPE_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <ComStack_Types.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Enumeration to indicate verification results */
typedef uint16 SecOC_VerificationResultType;
#define SECOC_VERIFICATIONSUCCESS                ((SecOC_VerificationResultType)0x00)   /* Verification successful */
#define SECOC_VERIFICATIONFAILURE                ((SecOC_VerificationResultType)0x01)   /* Verification not successful */
#define SECOC_FRESHNESSFAILURE                   ((SecOC_VerificationResultType)0x02)   /* Verification not successful because of wrong freshness value */
#define SECOC_AUTHENTICATIONBUILDFAILURE         ((SecOC_VerificationResultType)0x03)   /* Verification not successful because of wrong build authentication codes */
#define SECOC_NO_VERIFICATION                    ((SecOC_VerificationResultType)0x04)   /* Verification has been skipped and the data has been provided to upper layer "as is". */
#define SECOC_VERIFICATIONFAILURE_OVERWRITTEN    ((SecOC_VerificationResultType)0x05)   /* Verification failed, but the I-PDU was passed on to the upper layer due to the override status for this PDU. */
#define SECOC_AB_VERIFICATIONFAILURE_VERIFYSTART ((SecOC_VerificationResultType)0x40)   /* Verification failed, but the I-PDU was passed on to the upper layer due to VerifyStart. */

/* Defines possibilities to override the verification status. */
typedef uint16 SecOC_OverrideStatusType;
#define SECOC_OVERRIDE_DROP_UNTIL_NOTICE      ((SecOC_OverrideStatusType)0x00)   /* Until further notice, authenticator verification is not performed */
#define SECOC_OVERRIDE_DROP_UNTIL_LIMIT       ((SecOC_OverrideStatusType)0x01)   /* Until NumberOfMessagesToOverride is reached, authenticator verification is not performed */
#define SECOC_OVERRIDE_CANCEL                 ((SecOC_OverrideStatusType)0x02)   /* Cancel Override of VerifyStatus. */
#define SECOC_OVERRIDE_PASS_UNTIL_NOTICE      ((SecOC_OverrideStatusType)0x40)   /* Until further notice, authenticator verification is performed, I-PDU is sent to upper layer independent of verification result */
#define SECOC_OVERRIDE_SKIP_UNTIL_LIMIT       ((SecOC_OverrideStatusType)0x41)   /* Until NumberOfMessagesToOverride is reached, authenticator verification is not performed, I-PDU is sent to upper layer */
#define SECOC_OVERRIDE_PASS_UNTIL_LIMIT       ((SecOC_OverrideStatusType)0x42)   /* Until NumberOfMessagesToOverride is reached, authenticator verification is performed, I-PDU is sent to upper layer independent of verification result */
#define SECOC_OVERRIDE_SKIP_UNTIL_NOTICE      ((SecOC_OverrideStatusType)0x43)   /* Until further notice, authenticator verification is not performed, I-PDU is sent to upper layer */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* Data structure to bundle the status of a verification attempt for a specific Freshness Values */
typedef struct {
    uint16                              freshnessValueID;   /* Identifier of the Freshness Value which resulted in the Verification Status */
    SecOC_VerificationResultType        verificationStatus; /* Result of verification attempt */
    uint32                              Ab_SecOCDataId;     /* Data ID of SecOCDataId */
} SecOC_VerificationStatusType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/



#endif /* RTE_SECOC_TYPE_H */

/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-1-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

