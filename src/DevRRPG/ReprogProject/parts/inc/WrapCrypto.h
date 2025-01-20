/* WrapCrypto_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | WrapCrypto/HEADER                                           */
/******************************************************************************/
#ifndef WRAPCRYPTO_H
#define WRAPCRYPTO_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Csm.h>

/*===== Sample ===============================================================*/
#include <Crypto_83_sw.h>
/*===== Sample ===============================================================*/


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define WRAPCRYPTO_E_PENDING        ((Std_ReturnType)0x02U)
#define WRAPCRYPTO_E_VERIFY         ((Std_ReturnType)0x03U)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
/* WrapCrypto.c */
FUNC(void, WRAPCRYPTO_CODE_SLOW) WrapCrypto_Init (void);
FUNC(void, WRAPCRYPTO_CODE_SLOW) WrapCrypto_MainFunction (void);
FUNC(Std_ReturnType, WRAPCRYPTO_CODE_SLOW) WrapCrypto_Set_UID
(
    VAR(uint32, AUTOMATIC) KeyId,
    P2CONST(uint8, AUTOMATIC, WRAPCRYPTO_APPL_CONST) Uid,
    VAR(uint32, AUTOMATIC) UidSize
);
FUNC(Std_ReturnType, WRAPCRYPTO_CODE_SLOW) WrapCrypto_Set_ToolAuthKey
(
    VAR(uint32, AUTOMATIC) KeyId,
    P2CONST(uint8, AUTOMATIC, WRAPCRYPTO_APPL_CONST) ToolAuthKey,
    VAR(uint32, AUTOMATIC) ToolAuthKeySize
);
FUNC(Std_ReturnType, WRAPCRYPTO_CODE_SLOW) WrapCrypto_Set_SystemKey
(
    VAR(uint32, AUTOMATIC) KeyId,
    P2CONST(uint8, AUTOMATIC, WRAPCRYPTO_APPL_CONST) SystemKey,
    VAR(uint32, AUTOMATIC) SystemKeySize
);
FUNC(Std_ReturnType, WRAPCRYPTO_CODE_SLOW) WrapCrypto_Set_SigVerifyKey
(
    VAR(uint32, AUTOMATIC) KeyId,
    P2CONST(uint8, AUTOMATIC, WRAPCRYPTO_APPL_CONST) SigVerifyKey,
    VAR(uint32, AUTOMATIC) SigVerifyKeySize
);
FUNC(Std_ReturnType, WRAPCRYPTO_CODE_SLOW) WrapCrypto_Set_Nonce
(
    VAR(uint32, AUTOMATIC) KeyId,
    P2CONST(uint8, AUTOMATIC, WRAPCRYPTO_APPL_CONST) Nonce,
    VAR(uint32, AUTOMATIC) NonceSize
);
FUNC(void, WRAPCRYPTO_CODE_SLOW) WrapCrypto_SchM_Enter (void);
FUNC(void, WRAPCRYPTO_CODE_SLOW) WrapCrypto_SchM_Exit (void);
FUNC(void, WRAPCRYPTO_CODE_SLOW) WrapCrypto_ErrorCallout
(
    VAR(Csm_Ab_ErrorStatusType, AUTOMATIC) udErrorStatus
);
FUNC(void, WRAPCRYPTO_CODE_SLOW) WrapCrypto_TimeoutCallout
(
    VAR(uint32, AUTOMATIC) u4ChannelId
);
/*===== Sample ===============================================================*/
FUNC(void, WRAPCRYPTO_CODE_SLOW) WrapCrypto_83_sw_ErrorCallout
(
    VAR(Crypto_83_sw_Ab_ErrorStatusType, AUTOMATIC) udErrorStatus
);
FUNC(void, WRAPCRYPTO_CODE_SLOW) WrapCrypto_83_sw_IntervalCallout (void);
/*===== Sample ===============================================================*/
/* WrapCrypto_Decrypt.c */
FUNC(Std_ReturnType, WRAPCRYPTO_CODE_SLOW) WrapCrypto_Pre_Decrypt
(
    VAR(uint32, AUTOMATIC) JobId
);
FUNC(Std_ReturnType, WRAPCRYPTO_CODE_SLOW) WrapCrypto_Decrypt
(
    VAR(boolean, AUTOMATIC) FirstData,
    VAR(uint32, AUTOMATIC) JobId,
    P2CONST(uint8, AUTOMATIC, WRAPCRYPTO_APPL_CONST) Ciphertext,
    VAR(uint32, AUTOMATIC) CiphertextSize,
    P2VAR(uint8, AUTOMATIC, WRAPCRYPTO_APPL_DATA) Plaintext,
    P2VAR(uint32, AUTOMATIC, WRAPCRYPTO_APPL_DATA) PlaintextSize
);
FUNC(Std_ReturnType, WRAPCRYPTO_CODE_SLOW) WrapCrypto_Fin_Decrypt
(
    VAR(uint32, AUTOMATIC) JobId
);
FUNC(void, WRAPCRYPTO_CODE_SLOW) WrapCrypto_DecryptCallout
(
    VAR(uint32, AUTOMATIC) jobId,
    VAR(Crypto_ResultType, AUTOMATIC) result
);
/* WrapCrypto_Encrypt.c */
FUNC(Std_ReturnType, WRAPCRYPTO_CODE_SLOW) WrapCrypto_Pre_Encrypt
(
    VAR(uint32, AUTOMATIC) JobId
);
FUNC(Std_ReturnType, WRAPCRYPTO_CODE_SLOW) WrapCrypto_Encrypt
(
    VAR(boolean, AUTOMATIC) FirstData,
    VAR(uint32, AUTOMATIC) JobId,
    P2CONST(uint8, AUTOMATIC, WRAPCRYPTO_APPL_CONST) Plaintext,
    VAR(uint32, AUTOMATIC) PlaintextSize,
    P2VAR(uint8, AUTOMATIC, WRAPCRYPTO_APPL_DATA) Ciphertext,
    P2VAR(uint32, AUTOMATIC, WRAPCRYPTO_APPL_DATA) CiphertextSize
);
FUNC(Std_ReturnType, WRAPCRYPTO_CODE_SLOW) WrapCrypto_Fin_Encrypt
(
    VAR(uint32, AUTOMATIC) JobId
);
FUNC(void, WRAPCRYPTO_CODE_SLOW) WrapCrypto_EncryptCallout
(
    VAR(uint32, AUTOMATIC) jobId,
    VAR(Crypto_ResultType, AUTOMATIC) result
);
/* WrapCrypto_SigVerify.c */
FUNC(Std_ReturnType, WRAPCRYPTO_CODE_SLOW) WrapCrypto_Pre_SigVerify
(
    VAR(uint32, AUTOMATIC) JobId
);
FUNC(Std_ReturnType, WRAPCRYPTO_CODE_SLOW) WrapCrypto_SigVerify
(
    VAR(boolean, AUTOMATIC) FirstData,
    VAR(uint32, AUTOMATIC) JobId,
    P2CONST(uint8, AUTOMATIC, WRAPCRYPTO_APPL_CONST) Data,
    VAR(uint32, AUTOMATIC) DataSize
);
FUNC(Std_ReturnType, WRAPCRYPTO_CODE_SLOW) WrapCrypto_Fin_SigVerify
(
    VAR(uint32, AUTOMATIC) JobId,
    P2CONST(uint8, AUTOMATIC, WRAPCRYPTO_APPL_CONST) Signature,
    VAR(uint32, AUTOMATIC) SignatureSize
);
FUNC(void, WRAPCRYPTO_CODE_SLOW) WrapCrypto_SigVerifyCallout
(
    VAR(uint32, AUTOMATIC) jobId,
    VAR(Crypto_ResultType, AUTOMATIC) result
);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define WRAPCRYPTO_START_SEC_VAR
#include <WrapCrypto_MemMap.h>

#define WRAPCRYPTO_STOP_SEC_VAR
#include <WrapCrypto_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define WRAPCRYPTO_START_SEC_CST
#include <WrapCrypto_MemMap.h>

#define WRAPCRYPTO_STOP_SEC_CST
#include <WrapCrypto_MemMap.h>


#endif /* WRAPCRYPTO_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/10/04 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

