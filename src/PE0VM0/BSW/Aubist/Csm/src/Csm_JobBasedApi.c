/* Csm_JobBasedApi_c_v2-0-0                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Csm/JobBasedApi/CODE                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Csm.h>
#include "../inc/Csm_General.h"
#include "../inc/Csm_Queue.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define CSM_KEYSETMODE_NONE             ((Csm_KeySetModeType)0x00U)
#define CSM_KEYSETMODE_KEYID            ((Csm_KeySetModeType)0x01U)
#define CSM_KEYSETMODE_TARGETKEYID      ((Csm_KeySetModeType)0x02U)
#define CSM_KEYSETMODE_BOTH             ((Csm_KeySetModeType)0x03U)

#define CSM_OPERATIONMODE_MASK_SUF      ((uint8)0x07U)
#define CSM_OPERATIONMODE_MASK_NOT_SUF  ((uint8)0xF8U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef uint8   Csm_KeySetModeType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define CSM_START_SEC_CODE
#include <Csm_MemMap.h>

static FUNC(Std_ReturnType, CSM_CODE) Csm_JobBasedApi_ProcessJob
(
    uint32 u4JobId,
    Crypto_ServiceInfoType udService,
    P2VAR(Crypto_JobPrimitiveInputOutputType, AUTOMATIC, AUTOMATIC) ptInOut,
    Csm_KeySetModeType udKeySetMode
);

#define CSM_STOP_SEC_CODE
#include <Csm_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define CSM_START_SEC_CODE
#include <Csm_MemMap.h>

/****************************************************************************/
/* Function Name | Csm_Hash                                                 */
/* Description   | Uses the given data to perform the hash calculation      */
/*               | and stores the hash.                                     */
/* Preconditions | -                                                        */
/* Parameters    | jobId  : Holds the identifier of the job                 */
/*               |          using the CSM service.                          */
/*               | mode   : Indicates which operation modes to perfom.      */
/*               | dateptr : Contains the pointer to the data               */
/*               |           for which the hash shall be computed.          */
/*               | dataLength  : Contains the number of bytes to be hashed. */
/*               | resultPtr  : Contains the pointer to the data            */
/*               |              where the hash value shall be stored.       */
/*               | resultLengthPtr  : Holds a pointer to the memory         */
/*               |                    location in which the output length   */
/*               |                    in bytes is stored. On calling this   */
/*               |                    function, this parameter shall        */
/*               |                    contain the size of the buffer        */
/*               |                    provided by resultPtr.                */
/*               |                    When the request has finished,        */
/*               |                    the actual length of the returned     */
/*               |                    value shall be stored.                */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful                          */
/*               | E_NOT_OK   : Request failed                              */
/* Notes         | SWS_Csm_00980                                            */
/****************************************************************************/
FUNC(Std_ReturnType, CSM_CODE) Csm_Hash
(
    uint32 jobId,
    Crypto_OperationModeType mode,
    P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) dataPtr,
    uint32 dataLength,
    P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) resultPtr,
    P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) resultLengthPtr
)
{
    Std_ReturnType                      ud_ret;
    Crypto_JobPrimitiveInputOutputType  ud_jobInOut;
    
    ud_jobInOut.inputPtr                    = dataPtr;
    ud_jobInOut.inputLength                 = dataLength;
    ud_jobInOut.secondaryInputPtr           = NULL_PTR;
    ud_jobInOut.secondaryInputLength        = 0UL;
    ud_jobInOut.tertiaryInputPtr            = NULL_PTR;
    ud_jobInOut.tertiaryInputLength         = 0UL;
    ud_jobInOut.outputPtr                   = resultPtr;
    ud_jobInOut.outputLengthPtr             = resultLengthPtr;
    ud_jobInOut.secondaryOutputPtr          = NULL_PTR;
    ud_jobInOut.secondaryOutputLengthPtr    = NULL_PTR;
    ud_jobInOut.verifyPtr                   = NULL_PTR;
    ud_jobInOut.mode                        = mode;
    ud_jobInOut.cryIfKeyId                  = 0UL;
    ud_jobInOut.targetCryIfKeyId            = 0UL;
    
    ud_ret = Csm_JobBasedApi_ProcessJob( jobId, CRYPTO_HASH, &ud_jobInOut, CSM_KEYSETMODE_NONE );
    
    return ud_ret;
}

/****************************************************************************/
/* Function Name | Csm_MacGenerate                                          */
/* Description   | Uses the given data to perform a MAC generation and      */
/*               | stores the MAC in the memory location pointed to         */
/*               | by the MAC pointer.                                      */
/* Preconditions | -                                                        */
/* Parameters    | jobId  : Holds the identifier of the job                 */
/*               |          using the CSM service.                          */
/*               | mode   : Indicates which operation modes to perfom.      */
/*               | dataPtr   : Contains the pointer to the data             */
/*               |             for which the MAC shall be computed.         */
/*               | dataLength  : Contains the number of bytes to be hashed. */
/*               | macPtr   : Contains the pointer to the data              */
/*               |            where the MAC shall be stored.                */
/*               | macLengthPtr  : Holds a pointer to the memory location   */
/*               |                 in which the output length in bytes      */
/*               |                 is stored. On calling this function,     */
/*               |                 this parameter shall contain the size of */
/*               |                 the buffer provided by macPtr. When the  */
/*               |                 request has finished, the actual length  */
/*               |                 of the returned MAC shall be stored.     */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful                          */
/*               | E_NOT_OK   : Request failed                              */
/*               | CRYPTO_E_BUSY : request failed, service is still busy    */
/*               | CRYPTO_E_KEY_NOT_VALID  : Request failed,                */
/*               |                          the key state is invalid        */
/*               | CRYPTO_E_KEY_SIZE_MISMATCH  : Request failed, a key      */
/*               |                               element has the wrong size */
/*               | CRYPTO_E_KEY_EMPTY : Request failed because of           */
/*               |                      uninitialized source key element    */
/* Notes         | SWS_Csm_00982                                            */
/****************************************************************************/
FUNC(Std_ReturnType, CSM_CODE) Csm_MacGenerate
(
    uint32 jobId,
    Crypto_OperationModeType mode,
    P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) dataPtr,
    uint32 dataLength,
    P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) macPtr,
    P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) macLengthPtr
)
{
    Std_ReturnType                      ud_ret;
    Crypto_JobPrimitiveInputOutputType  ud_jobInOut;
    
    ud_jobInOut.inputPtr                    = dataPtr;
    ud_jobInOut.inputLength                 = dataLength;
    ud_jobInOut.secondaryInputPtr           = NULL_PTR;
    ud_jobInOut.secondaryInputLength        = 0UL;
    ud_jobInOut.tertiaryInputPtr            = NULL_PTR;
    ud_jobInOut.tertiaryInputLength         = 0UL;
    ud_jobInOut.outputPtr                   = macPtr;
    ud_jobInOut.outputLengthPtr             = macLengthPtr;
    ud_jobInOut.secondaryOutputPtr          = NULL_PTR;
    ud_jobInOut.secondaryOutputLengthPtr    = NULL_PTR;
    ud_jobInOut.verifyPtr                   = NULL_PTR;
    ud_jobInOut.mode                        = mode;
    ud_jobInOut.cryIfKeyId                  = 0UL;
    ud_jobInOut.targetCryIfKeyId            = 0UL;
    
    ud_ret = Csm_JobBasedApi_ProcessJob( jobId, CRYPTO_MACGENERATE, &ud_jobInOut, CSM_KEYSETMODE_NONE );
    
    return ud_ret;
}

/****************************************************************************/
/* Function Name | Csm_MacVerify                                            */
/* Description   | Verifies the given MAC by comparing                      */
/*               | if the MAC is generated with the given data.             */
/* Preconditions | -                                                        */
/* Parameters    | jobId  : Holds the identifier of the job                 */
/*               |          using the CSM service.                          */
/*               | mode   : Indicates which operation modes to perfom.      */
/*               | dataPtr   : Holds a pointer to the data for              */
/*               |             which the MAC shall be verified.             */
/*               | dataLength  : Contains the number of data bytes          */
/*               |               for which the MAC shall be verified.       */
/*               | macPtr  : Holds a pointer to the MAC to be verified.     */
/*               | macLength  : Contains the MAC length                     */
/*               |              in BITS to be verified.                     */
/*               | verifyPtr  : Holds a pointer to the memory location,     */
/*               |              which will hold                             */
/*               |              the result of the MAC verification.         */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful                          */
/*               | E_NOT_OK   : Request failed                              */
/*               | CRYPTO_E_BUSY : request failed, service is still busy    */
/*               | CRYPTO_E_KEY_NOT_VALID  : Request failed,                */
/*               |                          the key state is invalid        */
/*               | CRYPTO_E_KEY_SIZE_MISMATCH  : Request failed, a key      */
/*               |                               element has the wrong size */
/*               | CRYPTO_E_KEY_EMPTY : Request failed because of           */
/*               |                      uninitialized source key element    */
/* Notes         | SWS_Csm_01050                                            */
/****************************************************************************/
FUNC(Std_ReturnType, CSM_CODE) Csm_MacVerify
(
    uint32 jobId,
    Crypto_OperationModeType mode,
    P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) dataPtr,
    uint32 dataLength,
    P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) macPtr,
    const uint32 macLength,
    P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_DATA) verifyPtr
)
{
    Std_ReturnType                      ud_ret;
    Crypto_JobPrimitiveInputOutputType  ud_jobInOut;
    
    ud_jobInOut.inputPtr                    = dataPtr;
    ud_jobInOut.inputLength                 = dataLength;
    ud_jobInOut.secondaryInputPtr           = macPtr;
    ud_jobInOut.secondaryInputLength        = macLength;
    ud_jobInOut.tertiaryInputPtr            = NULL_PTR;
    ud_jobInOut.tertiaryInputLength         = 0UL;
    ud_jobInOut.outputPtr                   = NULL_PTR;
    ud_jobInOut.outputLengthPtr             = NULL_PTR;
    ud_jobInOut.secondaryOutputPtr          = NULL_PTR;
    ud_jobInOut.secondaryOutputLengthPtr    = NULL_PTR;
    ud_jobInOut.verifyPtr                   = verifyPtr;
    ud_jobInOut.mode                        = mode;
    ud_jobInOut.cryIfKeyId                  = 0UL;
    ud_jobInOut.targetCryIfKeyId            = 0UL;
    
    ud_ret = Csm_JobBasedApi_ProcessJob( jobId, CRYPTO_MACVERIFY, &ud_jobInOut, CSM_KEYSETMODE_NONE );
    
    return ud_ret;
}

/****************************************************************************/
/* Function Name | Csm_Encrypt                                              */
/* Description   | Encrypts the given data and store the ciphertext         */
/*               | in the memory location pointed by the result pointer.    */
/* Preconditions | -                                                        */
/* Parameters    | jobId  : Holds the identifier of the job                 */
/*               |          using the CSM service.                          */
/*               | mode   : Indicates which operation modes to perfom.      */
/*               | dataPtr  : Contains the pointer to the data              */
/*               |            to be encrypted.                              */
/*               | dataLength  : Contains the number of bytes to encrypt.   */
/*               | resultPtr  : Contains the pointer to the data            */
/*               |              where the encrypted data shall be stored.   */
/*               | resultLengthPtr  : Holds a pointer to                    */
/*               |                    the memory location in which          */
/*               |                    the output length information         */
/*               |                    is stored in bytes. On calling        */
/*               |                    this function, this parameter shall   */
/*               |                    contain the size of the buffer        */
/*               |                    provided by resultPtr.                */
/*               |                    When the request has finished,        */
/*               |                    the actual length of                  */
/*               |                    the returned value shall be stored.   */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful                          */
/*               | E_NOT_OK   : Request failed                              */
/*               | CRYPTO_E_BUSY : request failed, service is still busy    */
/*               | CRYPTO_E_KEY_NOT_VALID  : Request failed,                */
/*               |                          the key state is invalid        */
/*               | CRYPTO_E_KEY_SIZE_MISMATCH  : Request failed, a key      */
/*               |                               element has the wrong size */
/*               | CRYPTO_E_KEY_EMPTY : Request failed because of           */
/*               |                      uninitialized source key element    */
/* Notes         | SWS_Csm_00984                                            */
/****************************************************************************/
FUNC(Std_ReturnType, CSM_CODE) Csm_Encrypt
(
    uint32 jobId,
    Crypto_OperationModeType mode,
    P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) dataPtr,
    uint32 dataLength,
    P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) resultPtr,
    P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) resultLengthPtr
)
{
    Std_ReturnType                      ud_ret;
    Crypto_JobPrimitiveInputOutputType  ud_jobInOut;
    
    ud_jobInOut.inputPtr                    = dataPtr;
    ud_jobInOut.inputLength                 = dataLength;
    ud_jobInOut.secondaryInputPtr           = NULL_PTR;
    ud_jobInOut.secondaryInputLength        = 0UL;
    ud_jobInOut.tertiaryInputPtr            = NULL_PTR;
    ud_jobInOut.tertiaryInputLength         = 0UL;
    ud_jobInOut.outputPtr                   = resultPtr;
    ud_jobInOut.outputLengthPtr             = resultLengthPtr;
    ud_jobInOut.secondaryOutputPtr          = NULL_PTR;
    ud_jobInOut.secondaryOutputLengthPtr    = NULL_PTR;
    ud_jobInOut.verifyPtr                   = NULL_PTR;
    ud_jobInOut.mode                        = mode;
    ud_jobInOut.cryIfKeyId                  = 0UL;
    ud_jobInOut.targetCryIfKeyId            = 0UL;
    
    ud_ret = Csm_JobBasedApi_ProcessJob( jobId, CRYPTO_ENCRYPT, &ud_jobInOut, CSM_KEYSETMODE_NONE );
    
    return ud_ret;
}

/****************************************************************************/
/* Function Name | Csm_Decrypt                                              */
/* Description   | Decrypts the given encrypted data and store              */
/*               | the decrypted plaintext in the memory location           */
/*               | pointed by the result pointer.                           */
/* Preconditions | -                                                        */
/* Parameters    | jobId  : Holds the identifier of the job                 */
/*               |          using the CSM service.                          */
/*               | mode   : Indicates which operation modes to perfom.      */
/*               | dataPtr  : Contains the pointer to the data              */
/*               |            to be decrypted.                              */
/*               | dataLength  : Contains the number of bytes to decrypt.   */
/*               | resultPtr  : Contains the pointer to the data            */
/*               |              where the decrypted data shall be stored.   */
/*               | resultLengthPtr  : Holds a pointer to                    */
/*               |                    the memory location in which          */
/*               |                    the output length information         */
/*               |                    is stored in bytes. On calling        */
/*               |                    this function, this parameter shall   */
/*               |                    contain the size of the buffer        */
/*               |                    provided by resultPtr.                */
/*               |                    When the request has finished,        */
/*               |                    the actual length of                  */
/*               |                    the returned value shall be stored.   */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful                          */
/*               | E_NOT_OK   : Request failed                              */
/*               | CRYPTO_E_BUSY : request failed, service is still busy    */
/*               | CRYPTO_E_KEY_NOT_VALID  : Request failed,                */
/*               |                          the key state is invalid        */
/*               | CRYPTO_E_KEY_SIZE_MISMATCH  : Request failed, a key      */
/*               |                               element has the wrong size */
/*               | CRYPTO_E_KEY_EMPTY : Request failed because of           */
/*               |                      uninitialized source key element    */
/* Notes         | SWS_Csm_00989                                            */
/****************************************************************************/
FUNC(Std_ReturnType, CSM_CODE) Csm_Decrypt
(
    uint32 jobId,
    Crypto_OperationModeType mode,
    P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) dataPtr,
    uint32 dataLength,
    P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) resultPtr,
    P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) resultLengthPtr
)
{
    Std_ReturnType                      ud_ret;
    Crypto_JobPrimitiveInputOutputType  ud_jobInOut;
    
    ud_jobInOut.inputPtr                    = dataPtr;
    ud_jobInOut.inputLength                 = dataLength;
    ud_jobInOut.secondaryInputPtr           = NULL_PTR;
    ud_jobInOut.secondaryInputLength        = 0UL;
    ud_jobInOut.tertiaryInputPtr            = NULL_PTR;
    ud_jobInOut.tertiaryInputLength         = 0UL;
    ud_jobInOut.outputPtr                   = resultPtr;
    ud_jobInOut.outputLengthPtr             = resultLengthPtr;
    ud_jobInOut.secondaryOutputPtr          = NULL_PTR;
    ud_jobInOut.secondaryOutputLengthPtr    = NULL_PTR;
    ud_jobInOut.verifyPtr                   = NULL_PTR;
    ud_jobInOut.mode                        = mode;
    ud_jobInOut.cryIfKeyId                  = 0UL;
    ud_jobInOut.targetCryIfKeyId            = 0UL;
    
    ud_ret = Csm_JobBasedApi_ProcessJob( jobId, CRYPTO_DECRYPT, &ud_jobInOut, CSM_KEYSETMODE_NONE );
    
    return ud_ret;
}

/****************************************************************************/
/* Function Name | Csm_AEADEncrypt                                          */
/* Description   | Uses the given input data to perform a AEAD encryption   */
/*               | and stores the ciphertext and the MAC                    */
/*               | in the memory locations pointed                          */
/*               | by the ciphertext pointer and Tag pointer.               */
/* Preconditions | -                                                        */
/* Parameters    | jobId  : Holds the identifier of the job                 */
/*               |          using the CSM service.                          */
/*               | mode   : Indicates which operation modes to perfom.      */
/*               | plaintextPtr  : Contains the pointer                     */
/*               |                 to the data to be encrypted.             */
/*               | plaintextLength  : Contains the number of bytes          */
/*               |                    to encrypt.                           */
/*               | associatedDataPtr  : Contains the pointer                */
/*               |                      to the associated data.             */
/*               | associatedDataLength  : Contains the number of bytes     */
/*               |                         of the associated data.          */
/*               | ciphertextPtr  : Contains the pointer to the data  where */
/*               |                  the encrypted data shall be stored.     */
/*               | ciphertextLengthPtr  : Holds a pointer                   */
/*               |                        to the memory location in which   */
/*               |                        the output length in bytes of     */
/*               |                        the ciphertext is stored.         */
/*               |                        On calling this function, this    */
/*               |                        parameter shall contain the       */
/*               |                        size of the buffer in bytes       */
/*               |                        provided by resultPtr.            */
/*               |                        When the request has finished,    */
/*               |                        the actual length of the          */
/*               |                        returned value shall be stored.   */
/*               | tagPtr  : Contains the pointer to the data               */
/*               |           where the Tag shall be stored.                 */
/*               | tagLengthPtr  : Holds a pointer to the memory location   */
/*               |                 in which the output length in bytes of   */
/*               |                 the Tag is stored. On calling            */
/*               |                 this function, this parameter shall      */
/*               |                 contain the size of the buffer in bytes  */
/*               |                 provided by resultPtr. When the request  */
/*               |                 has finished, the actual length of       */
/*               |                 the returned value shall be stored.      */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful                          */
/*               | E_NOT_OK   : Request failed                              */
/*               | CRYPTO_E_BUSY : request failed, service is still busy    */
/*               | CRYPTO_E_KEY_NOT_VALID  : Request failed,                */
/*               |                          the key state is invalid        */
/*               | CRYPTO_E_KEY_SIZE_MISMATCH  : Request failed, a key      */
/*               |                               element has the wrong size */
/*               | CRYPTO_E_KEY_EMPTY : Request failed because of           */
/*               |                      uninitialized source key element    */
/* Notes         | SWS_Csm_01023                                            */
/****************************************************************************/
FUNC(Std_ReturnType, CSM_CODE) Csm_AEADEncrypt
(
    uint32 jobId,
    Crypto_OperationModeType mode,
    P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) plaintextPtr,
    uint32 plaintextLength,
    P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) associatedDataPtr,
    uint32 associatedDataLength,
    P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) ciphertextPtr,
    P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) ciphertextLengthPtr,
    P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) tagPtr,
    P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) tagLengthPtr
)
{
    Std_ReturnType                      ud_ret;
    Crypto_JobPrimitiveInputOutputType  ud_jobInOut;
    
    ud_jobInOut.inputPtr                    = plaintextPtr;
    ud_jobInOut.inputLength                 = plaintextLength;
    ud_jobInOut.secondaryInputPtr           = associatedDataPtr;
    ud_jobInOut.secondaryInputLength        = associatedDataLength;
    ud_jobInOut.tertiaryInputPtr            = NULL_PTR;
    ud_jobInOut.tertiaryInputLength         = 0UL;
    ud_jobInOut.outputPtr                   = ciphertextPtr;
    ud_jobInOut.outputLengthPtr             = ciphertextLengthPtr;
    ud_jobInOut.secondaryOutputPtr          = tagPtr;
    ud_jobInOut.secondaryOutputLengthPtr    = tagLengthPtr;
    ud_jobInOut.verifyPtr                   = NULL_PTR;
    ud_jobInOut.mode                        = mode;
    ud_jobInOut.cryIfKeyId                  = 0UL;
    ud_jobInOut.targetCryIfKeyId            = 0UL;
    
    ud_ret = Csm_JobBasedApi_ProcessJob( jobId, CRYPTO_AEADENCRYPT, &ud_jobInOut, CSM_KEYSETMODE_NONE );
    
    return ud_ret;
}

/****************************************************************************/
/* Function Name | Csm_AEADDecrypt                                          */
/* Description   | Uses the given data to perform an AEAD encryption        */
/*               | and stores the ciphertext and the MAC in the             */
/*               | memory locations pointed by the ciphertext pointer       */
/*               | and Tag pointer.                                         */
/* Parameters    | jobId  : Holds the identifier of the job                 */
/*               |          using the CSM service.                          */
/*               | mode   : Indicates which operation modes to perfom.      */
/*               | ciphertextPtr  : Contains the pointer to the data        */
/*               |                  to be decrypted.                        */
/*               | ciphertextLength  : Contains the number of bytes         */
/*               |                     to decrypt.                          */
/*               | associatedDataPtr  : Contains the pointer                */
/*               |                      to the associated data.             */
/*               | associatedDataLength  : Contains the length in bytes of  */
/*               |                         the associated data.             */
/*               | tagPtr  : Contains the pointer to the Tag to be verified.*/
/*               | tagLength  : Contains the length in bytes of             */
/*               |              the Tag to be verified.                     */
/*               | plaintextPtr  : Contains the pointer to the data         */
/*               |                 where the decrypted data                 */
/*               |                 shall be stored.                         */
/*               | plaintextLengthPtr  : Holds a pointer to                 */
/*               |                       the memory location in which       */
/*               |                       the output length in bytes of      */
/*               |                       the paintext is stored.            */
/*               |                       On calling this function,          */
/*               |                       this parameter shall contain       */
/*               |                       the size of the buffer provided by */
/*               |                       plaintextPtr. When the request     */
/*               |                       has finished, the actual length of */
/*               |                       the returned value shall be stored.*/
/*               | verifyPtr  : Contains the pointer to the result of       */
/*               |              the verification.                           */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful                          */
/*               | E_NOT_OK   : Request failed                              */
/*               | CRYPTO_E_BUSY : request failed, service is still busy    */
/*               | CRYPTO_E_KEY_NOT_VALID  : Request failed,                */
/*               |                          the key state is invalid        */
/*               | CRYPTO_E_KEY_SIZE_MISMATCH  : Request failed, a key      */
/*               |                               element has the wrong size */
/*               | CRYPTO_E_KEY_EMPTY : Request failed because of           */
/*               |                      uninitialized source key element    */
/* Notes         | SWS_Csm_01026                                            */
/****************************************************************************/
FUNC(Std_ReturnType, CSM_CODE) Csm_AEADDecrypt
(
    uint32 jobId,
    Crypto_OperationModeType mode,
    P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) ciphertextPtr,
    uint32 ciphertextLength,
    P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) associatedDataPtr,
    uint32 associatedDataLength,
    P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) tagPtr,
    uint32 tagLength,
    P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) plaintextPtr,
    P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) plaintextLengthPtr,
    P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_DATA) verifyPtr
)
{
    Std_ReturnType                      ud_ret;
    Crypto_JobPrimitiveInputOutputType  ud_jobInOut;
    
    ud_jobInOut.inputPtr                    = ciphertextPtr;
    ud_jobInOut.inputLength                 = ciphertextLength;
    ud_jobInOut.secondaryInputPtr           = associatedDataPtr;
    ud_jobInOut.secondaryInputLength        = associatedDataLength;
    ud_jobInOut.tertiaryInputPtr            = tagPtr;
    ud_jobInOut.tertiaryInputLength         = tagLength;
    ud_jobInOut.outputPtr                   = plaintextPtr;
    ud_jobInOut.outputLengthPtr             = plaintextLengthPtr;
    ud_jobInOut.secondaryOutputPtr          = NULL_PTR;
    ud_jobInOut.secondaryOutputLengthPtr    = NULL_PTR;
    ud_jobInOut.verifyPtr                   = verifyPtr;
    ud_jobInOut.mode                        = mode;
    ud_jobInOut.cryIfKeyId                  = 0UL;
    ud_jobInOut.targetCryIfKeyId            = 0UL;
    
    ud_ret = Csm_JobBasedApi_ProcessJob( jobId, CRYPTO_AEADDECRYPT, &ud_jobInOut, CSM_KEYSETMODE_NONE );
    
    return ud_ret;
}

/****************************************************************************/
/* Function Name | Csm_SignatureGenerate                                    */
/* Description   | Uses the given data to perform the signature calculation */
/*               | and stores the signature in the memory location          */
/*               | pointed by the result pointer.                           */
/* Preconditions | -                                                        */
/* Parameters    | jobId  : Holds the identifier of the job                 */
/*               |          using the CSM service.                          */
/*               | mode   : Indicates which operation modes to perfom.      */
/*               | dataPtr   : Contains the pointer to the data             */
/*               |             to be signed.                                */
/*               | dataLength  : Contains the number of bytes to sign.      */
/*               | resultPtr   : Contains the pointer to the data           */
/*               |               where the signature shall be stored.       */
/*               | resultLengthPtr  : Holds a pointer                       */
/*               |                    to the memory location in which       */
/*               |                    the output length in bytes of         */
/*               |                    the signature is stored. On calling   */
/*               |                    this function, this parameter shall   */
/*               |                    contain the size of the buffer        */
/*               |                    provided by resultPtr.                */
/*               |                    When the request has finished,        */
/*               |                    the actual length of the              */
/*               |                    returned value shall be stored.       */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful                          */
/*               | E_NOT_OK   : Request failed                              */
/*               | CRYPTO_E_BUSY : request failed, service is still busy    */
/*               | CRYPTO_E_KEY_NOT_VALID  : Request failed,                */
/*               |                          the key state is invalid        */
/*               | CRYPTO_E_KEY_SIZE_MISMATCH  : Request failed, a key      */
/*               |                               element has the wrong size */
/*               | CRYPTO_E_KEY_EMPTY : Request failed because of           */
/*               |                      uninitialized source key element    */
/* Notes         | SWS_Csm_00992                                            */
/****************************************************************************/
FUNC(Std_ReturnType, CSM_CODE) Csm_SignatureGenerate
(
    uint32 jobId,
    Crypto_OperationModeType mode,
    P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) dataPtr,
    uint32 dataLength,
    P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) resultPtr,
    P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) resultLengthPtr
)
{
    Std_ReturnType                      ud_ret;
    Crypto_JobPrimitiveInputOutputType  ud_jobInOut;
    
    ud_jobInOut.inputPtr                    = dataPtr;
    ud_jobInOut.inputLength                 = dataLength;
    ud_jobInOut.secondaryInputPtr           = NULL_PTR;
    ud_jobInOut.secondaryInputLength        = 0UL;
    ud_jobInOut.tertiaryInputPtr            = NULL_PTR;
    ud_jobInOut.tertiaryInputLength         = 0UL;
    ud_jobInOut.outputPtr                   = resultPtr;
    ud_jobInOut.outputLengthPtr             = resultLengthPtr;
    ud_jobInOut.secondaryOutputPtr          = NULL_PTR;
    ud_jobInOut.secondaryOutputLengthPtr    = NULL_PTR;
    ud_jobInOut.verifyPtr                   = NULL_PTR;
    ud_jobInOut.mode                        = mode;
    ud_jobInOut.cryIfKeyId                  = 0UL;
    ud_jobInOut.targetCryIfKeyId            = 0UL;
    
    ud_ret = Csm_JobBasedApi_ProcessJob( jobId, CRYPTO_SIGNATUREGENERATE, &ud_jobInOut, CSM_KEYSETMODE_NONE );
    
    return ud_ret;
}

/****************************************************************************/
/* Function Name | Csm_SignatureVerify                                      */
/* Description   | Verifies the given MAC by comparing                      */
/*               | if the signature is generated with the given data.       */
/* Preconditions | -                                                        */
/* Parameters    | jobId  : Holds the identifier of the job                 */
/*               |          using the CSM service.                          */
/*               | mode   : The Crypto_JobInfoType job with                 */
/*               |          the corresponding jobId                         */
/*               |          shall be modified in the following way:         */
/*               | dataPtr  : Contains the pointer to the data              */
/*               |            to be verified.                               */
/*               | dataLength  : Contains the number of data bytes.         */
/*               | signaturePtr  : Holds a pointer to the signature         */
/*               |                 to be verified.                          */
/*               | signatureLength  : Contains the signature length         */
/*               |              in bytes.                                   */
/*               | verifyPtr  : Holds a pointer to the memory location,     */
/*               |              which will hold                             */
/*               |              the result of the signature verification.   */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful                          */
/*               | E_NOT_OK   : Request failed                              */
/*               | CRYPTO_E_BUSY : request failed, service is still busy    */
/*               | CRYPTO_E_KEY_NOT_VALID  : Request failed,                */
/*               |                          the key state is invalid        */
/*               | CRYPTO_E_KEY_SIZE_MISMATCH  : Request failed, a key      */
/*               |                               element has the wrong size */
/*               | CRYPTO_E_KEY_EMPTY : Request failed because of           */
/*               |                      uninitialized source key element    */
/* Notes         | SWS_Csm_00996                                            */
/****************************************************************************/
FUNC(Std_ReturnType, CSM_CODE) Csm_SignatureVerify
(
    uint32 jobId,
    Crypto_OperationModeType mode,
    P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) dataPtr,
    uint32 dataLength,
    P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) signaturePtr,
    uint32 signatureLength,
    P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_DATA) verifyPtr
)
{
    Std_ReturnType                      ud_ret;
    Crypto_JobPrimitiveInputOutputType  ud_jobInOut;
    
    ud_jobInOut.inputPtr                    = dataPtr;
    ud_jobInOut.inputLength                 = dataLength;
    ud_jobInOut.secondaryInputPtr           = signaturePtr;
    ud_jobInOut.secondaryInputLength        = signatureLength;
    ud_jobInOut.tertiaryInputPtr            = NULL_PTR;
    ud_jobInOut.tertiaryInputLength         = 0UL;
    ud_jobInOut.outputPtr                   = NULL_PTR;
    ud_jobInOut.outputLengthPtr             = NULL_PTR;
    ud_jobInOut.secondaryOutputPtr          = NULL_PTR;
    ud_jobInOut.secondaryOutputLengthPtr    = NULL_PTR;
    ud_jobInOut.verifyPtr                   = verifyPtr;
    ud_jobInOut.mode                        = mode;
    ud_jobInOut.cryIfKeyId                  = 0UL;
    ud_jobInOut.targetCryIfKeyId            = 0UL;
    
    ud_ret = Csm_JobBasedApi_ProcessJob( jobId, CRYPTO_SIGNATUREVERIFY, &ud_jobInOut, CSM_KEYSETMODE_NONE );
    
    return ud_ret;
}

/****************************************************************************/
/* Function Name | Csm_RandomGenerate                                       */
/* Description   | Generate a random number and stores it                   */
/*               | in the memory location pointed by the result pointer.    */
/* Preconditions | -                                                        */
/* Parameters    | jobId  : Holds the identifier of the job                 */
/*               |          using the CSM service.                          */
/*               | resultPtr   : Holds a pointer to the memory location     */
/*               |               which will hold the result of              */
/*               |               the random number generation.              */
/*               | resultLengthPtr  : Holds a pointer to                    */
/*               |                    the  memory location in which         */
/*               |                    the result length in bytes is stored. */
/*               |                    On calling this function,             */
/*               |                    this parameter shall contain          */
/*               |                    the number of random bytes,           */
/*               |                    which shall be stored to the buffer   */
/*               |                    provided by resultPtr.                */
/*               |                    When the request has finished,        */
/*               |                    the actual length of                  */
/*               |                    the returned value shall be stored.   */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful                          */
/*               | E_NOT_OK   : Request failed                              */
/*               | CRYPTO_E_BUSY : request failed, service is still busy    */
/*               | CRYPTO_E_ENTROPY_EXHAUSTED  : Request failed, entropy of */
/*               |                               random number generator    */
/*               |                               is exhausted               */
/* Notes         | SWS_Csm_01543                                            */
/****************************************************************************/
FUNC(Std_ReturnType, CSM_CODE) Csm_RandomGenerate
(
    uint32 jobId,
    P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) resultPtr,
    P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) resultLengthPtr
)
{
    Std_ReturnType                      ud_ret;
    Crypto_JobPrimitiveInputOutputType  ud_jobInOut;
    
    ud_jobInOut.inputPtr                    = NULL_PTR;
    ud_jobInOut.inputLength                 = 0UL;
    ud_jobInOut.secondaryInputPtr           = NULL_PTR;
    ud_jobInOut.secondaryInputLength        = 0UL;
    ud_jobInOut.tertiaryInputPtr            = NULL_PTR;
    ud_jobInOut.tertiaryInputLength         = 0UL;
    ud_jobInOut.outputPtr                   = resultPtr;
    ud_jobInOut.outputLengthPtr             = resultLengthPtr;
    ud_jobInOut.secondaryOutputPtr          = NULL_PTR;
    ud_jobInOut.secondaryOutputLengthPtr    = NULL_PTR;
    ud_jobInOut.verifyPtr                   = NULL_PTR;
    ud_jobInOut.mode                        = CRYPTO_OPERATIONMODE_SINGLECALL;
    ud_jobInOut.cryIfKeyId                  = 0UL;
    ud_jobInOut.targetCryIfKeyId            = 0UL;
    
    ud_ret = Csm_JobBasedApi_ProcessJob( jobId, CRYPTO_RANDOMGENERATE, &ud_jobInOut, CSM_KEYSETMODE_NONE );
    
    return ud_ret;
}

/****************************************************************************/
/* Function Name | Csm_JobKeySetValid                                       */
/* Description   | Stores the key if necessary and sets the key state       */
/*               | of the key identified by keyId to valid.                 */
/* Preconditions | -                                                        */
/* Parameters    | jobId  : Holds the identifier of the job                 */
/*               |          using the CSM service.                          */
/*               | keyId   : Holds the identifier of the key for which      */
/*               |           a new material shall be validated.             */
/*               | dataLength  : Contains the number of bytes to encrypt.   */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful                          */
/*               | E_NOT_OK   : Request failed                              */
/*               | CRYPTO_E_BUSY : Request failed,                          */
/*               |                 Crypro Driver Object is busy             */
/* Notes         | SWS_Csm_91027                                            */
/****************************************************************************/
FUNC(Std_ReturnType, CSM_CODE) Csm_JobKeySetValid
(
    uint32 jobId,
    uint32 keyId
)
{
    Std_ReturnType                      ud_ret;
    Crypto_JobPrimitiveInputOutputType  ud_jobInOut;
    
    ud_jobInOut.inputPtr                    = NULL_PTR;
    ud_jobInOut.inputLength                 = 0UL;
    ud_jobInOut.secondaryInputPtr           = NULL_PTR;
    ud_jobInOut.secondaryInputLength        = 0UL;
    ud_jobInOut.tertiaryInputPtr            = NULL_PTR;
    ud_jobInOut.tertiaryInputLength         = 0UL;
    ud_jobInOut.outputPtr                   = NULL_PTR;
    ud_jobInOut.outputLengthPtr             = NULL_PTR;
    ud_jobInOut.secondaryOutputPtr          = NULL_PTR;
    ud_jobInOut.secondaryOutputLengthPtr    = NULL_PTR;
    ud_jobInOut.verifyPtr                   = NULL_PTR;
    ud_jobInOut.mode                        = CRYPTO_OPERATIONMODE_SINGLECALL;
    ud_jobInOut.cryIfKeyId                  = keyId;
    ud_jobInOut.targetCryIfKeyId            = 0UL;
    
    ud_ret = Csm_JobBasedApi_ProcessJob( jobId, CRYPTO_KEYSETVALID, &ud_jobInOut, CSM_KEYSETMODE_KEYID );
    
    return ud_ret;
}

/****************************************************************************/
/* Function Name | Csm_JobRandomSeed                                        */
/* Description   | This function shall dispatch the random seed function    */
/*               | to the configured crypto driver object.                  */
/* Preconditions | -                                                        */
/* Parameters    | jobId  : Holds the identifier of the job                 */
/*               |          using the CSM service.                          */
/*               | keyId   : Holds the identifier of the key                */
/*               |           for which a new seed shall be generated.       */
/*               | seedPtr  : Holds a pointer to the memory location        */
/*               |            which contains the data to feed the seed.     */
/*               | seedLength  : Contains the length of the seed in bytes.  */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful                          */
/*               | E_NOT_OK   : Request failed                              */
/*               | CRYPTO_E_BUSY : Request failed, service is still busy    */
/*               | CRYPTO_E_KEY_NOT_VALID : Request failed,                 */
/*               |                          the key state is invalid        */
/* Notes         | SWS_Csm_91028                                            */
/****************************************************************************/
FUNC(Std_ReturnType, CSM_CODE) Csm_JobRandomSeed
(
    uint32 jobId,
    uint32 keyId,
    P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) seedPtr,
    uint32 seedLength
)
{
    Std_ReturnType                      ud_ret;
    Crypto_JobPrimitiveInputOutputType  ud_jobInOut;
    
    ud_jobInOut.inputPtr                    = seedPtr;
    ud_jobInOut.inputLength                 = seedLength;
    ud_jobInOut.secondaryInputPtr           = NULL_PTR;
    ud_jobInOut.secondaryInputLength        = 0UL;
    ud_jobInOut.tertiaryInputPtr            = NULL_PTR;
    ud_jobInOut.tertiaryInputLength         = 0UL;
    ud_jobInOut.outputPtr                   = NULL_PTR;
    ud_jobInOut.outputLengthPtr             = NULL_PTR;
    ud_jobInOut.secondaryOutputPtr          = NULL_PTR;
    ud_jobInOut.secondaryOutputLengthPtr    = NULL_PTR;
    ud_jobInOut.verifyPtr                   = NULL_PTR;
    ud_jobInOut.mode                        = CRYPTO_OPERATIONMODE_SINGLECALL;
    ud_jobInOut.cryIfKeyId                  = keyId;
    ud_jobInOut.targetCryIfKeyId            = 0UL;
    
    ud_ret = Csm_JobBasedApi_ProcessJob( jobId, CRYPTO_RANDOMSEED, &ud_jobInOut, CSM_KEYSETMODE_KEYID );
    
    return ud_ret;
}

/****************************************************************************/
/* Function Name | Csm_JobKeyGenerate                                       */
/* Description   | Generates new key material and stores it                 */
/*               | in the key identified by keyId.                          */
/* Preconditions | -                                                        */
/* Parameters    | jobId  : Holds the identifier of the job                 */
/*               |          using the CSM service.                          */
/*               | keyId   : Holds the identifier of the key                */
/*               |           for which a new material shall be generated.   */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful                          */
/*               | E_NOT_OK   : Request failed                              */
/*               | CRYPTO_E_BUSY : Request failed, service is still busy    */
/*               | CRYPTO_E_KEY_NOT_VALID : Request failed,                 */
/*               |                          the key state is invalid        */
/*               | CRYPTO_E_KEY_EMPTY : Request failed because of           */
/*               |                      uninitialized source key element    */
/* Notes         | SWS_Csm_91029                                            */
/****************************************************************************/
FUNC(Std_ReturnType, CSM_CODE) Csm_JobKeyGenerate
(
    uint32 jobId,
    uint32 keyId
)
{
    Std_ReturnType                      ud_ret;
    Crypto_JobPrimitiveInputOutputType  ud_jobInOut;
    
    ud_jobInOut.inputPtr                    = NULL_PTR;
    ud_jobInOut.inputLength                 = 0UL;
    ud_jobInOut.secondaryInputPtr           = NULL_PTR;
    ud_jobInOut.secondaryInputLength        = 0UL;
    ud_jobInOut.tertiaryInputPtr            = NULL_PTR;
    ud_jobInOut.tertiaryInputLength         = 0UL;
    ud_jobInOut.outputPtr                   = NULL_PTR;
    ud_jobInOut.outputLengthPtr             = NULL_PTR;
    ud_jobInOut.secondaryOutputPtr          = NULL_PTR;
    ud_jobInOut.secondaryOutputLengthPtr    = NULL_PTR;
    ud_jobInOut.verifyPtr                   = NULL_PTR;
    ud_jobInOut.mode                        = CRYPTO_OPERATIONMODE_SINGLECALL;
    ud_jobInOut.cryIfKeyId                  = keyId;
    ud_jobInOut.targetCryIfKeyId            = 0UL;
    
    ud_ret = Csm_JobBasedApi_ProcessJob( jobId, CRYPTO_KEYGENERATE, &ud_jobInOut, CSM_KEYSETMODE_KEYID );
    
    return ud_ret;
}

/****************************************************************************/
/* Function Name | Csm_JobKeyDerive                                         */
/* Description   | Derives a new key by using the key elements              */
/*               | in the given key identified by the keyId. The given key  */
/*               | contains the key elements for the password and salt.     */
/*               | The derived key is stored in the key element with        */
/*               | the id 1 of the key identified by targetCryptoKeyId.     */
/* Preconditions | -                                                        */
/* Parameters    | jobId  : Holds the identifier of the job                 */
/*               |          using the CSM service.                          */
/*               | keyId   : Holds the identifier of the key                */
/*               |           which is used for key derivation.              */
/*               | targetKeyId  : Holds the identifier of the key           */
/*               |                which is used to store the derived key.   */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful                          */
/*               | E_NOT_OK   : Request failed                              */
/*               | CRYPTO_E_BUSY : Request failed, service is still busy    */
/*               | CRYPTO_E_KEY_READ_FAIL : Request failed, not allowed     */
/*               |                          to extract key element          */
/*               | CRYPTO_E_KEY_WRITE_FAIL : Request failed, not allowed    */
/*               |                          to write key element            */
/*               | CRYPTO_E_KEY_NOT_VALID : Request failed,                 */
/*               |                          the key state is invalid        */
/*               | CRYPTO_E_KEY_SIZE_MISMATCH : Request failed,             */
/*               |                              key element sizes           */
/*               |                              are not compatible          */
/*               | CRYPTO_E_KEY_EMPTY : Request failed because of           */
/*               |                      uninitialized source key element    */
/* Notes         | SWS_Csm_91030                                            */
/****************************************************************************/
FUNC(Std_ReturnType, CSM_CODE) Csm_JobKeyDerive
(
    uint32 jobId,
    uint32 keyId,
    uint32 targetKeyId
)
{
    Std_ReturnType                      ud_ret;
    Crypto_JobPrimitiveInputOutputType  ud_jobInOut;
    
    ud_jobInOut.inputPtr                    = NULL_PTR;
    ud_jobInOut.inputLength                 = 0UL;
    ud_jobInOut.secondaryInputPtr           = NULL_PTR;
    ud_jobInOut.secondaryInputLength        = 0UL;
    ud_jobInOut.tertiaryInputPtr            = NULL_PTR;
    ud_jobInOut.tertiaryInputLength         = 0UL;
    ud_jobInOut.outputPtr                   = NULL_PTR;
    ud_jobInOut.outputLengthPtr             = NULL_PTR;
    ud_jobInOut.secondaryOutputPtr          = NULL_PTR;
    ud_jobInOut.secondaryOutputLengthPtr    = NULL_PTR;
    ud_jobInOut.verifyPtr                   = NULL_PTR;
    ud_jobInOut.mode                        = CRYPTO_OPERATIONMODE_SINGLECALL;
    ud_jobInOut.cryIfKeyId                  = keyId;
    ud_jobInOut.targetCryIfKeyId            = targetKeyId;
    
    ud_ret = Csm_JobBasedApi_ProcessJob( jobId, CRYPTO_KEYDERIVE, &ud_jobInOut, CSM_KEYSETMODE_BOTH );
    
    return ud_ret;
}

/****************************************************************************/
/* Function Name | Csm_JobKeyExchangeCalcPubVal                             */
/* Description   | Calculates the public value of the current user for      */
/*               | the key exchange and stores the public key in the        */
/*               | memory location pointed by the public value pointer.     */
/* Preconditions | -                                                        */
/* Parameters    | jobId  : Holds the identifier of the job                 */
/*               |          using the CSM service.                          */
/*               | keyId   : Holds the identifier of the key which          */
/*               |           shall be used for the key exchange protocol.   */
/*               | publicValuePtr  : Contains the pointer to the data       */
/*               |                   where the public value shall be stored.*/
/*               | publicValueLengthPtr  : Holds the identifier of the key  */
/*               |                         which shall be used for the key  */
/*               |                         exchange protocol.               */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful                          */
/*               | E_NOT_OK   : Request failed                              */
/*               | CRYPTO_E_BUSY : Request failed, service is still busy    */
/*               | CRYPTO_E_KEY_NOT_VALID : Request failed,                 */
/*               |                          the key state is invalid        */
/*               | CRYPTO_E_KEY_EMPTY : Request failed because of           */
/*               |                      uninitialized source key element    */
/* Notes         | SWS_Csm_91031                                            */
/****************************************************************************/
FUNC(Std_ReturnType, CSM_CODE) Csm_JobKeyExchangeCalcPubVal
(
    uint32 jobId,
    uint32 keyId,
    P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) publicValuePtr,
    P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) publicValueLengthPtr
)
{
    Std_ReturnType                      ud_ret;
    Crypto_JobPrimitiveInputOutputType  ud_jobInOut;
    
    ud_jobInOut.inputPtr                    = NULL_PTR;
    ud_jobInOut.inputLength                 = 0UL;
    ud_jobInOut.secondaryInputPtr           = NULL_PTR;
    ud_jobInOut.secondaryInputLength        = 0UL;
    ud_jobInOut.tertiaryInputPtr            = NULL_PTR;
    ud_jobInOut.tertiaryInputLength         = 0UL;
    ud_jobInOut.outputPtr                   = publicValuePtr;
    ud_jobInOut.outputLengthPtr             = publicValueLengthPtr;
    ud_jobInOut.secondaryOutputPtr          = NULL_PTR;
    ud_jobInOut.secondaryOutputLengthPtr    = NULL_PTR;
    ud_jobInOut.verifyPtr                   = NULL_PTR;
    ud_jobInOut.mode                        = CRYPTO_OPERATIONMODE_SINGLECALL;
    ud_jobInOut.cryIfKeyId                  = keyId;
    ud_jobInOut.targetCryIfKeyId            = 0UL;
    
    ud_ret = Csm_JobBasedApi_ProcessJob( jobId, CRYPTO_KEYEXCHANGECALCPUBVAL, &ud_jobInOut, CSM_KEYSETMODE_KEYID );
    
    return ud_ret;
}

/****************************************************************************/
/* Function Name | Csm_JobKeyExchangeCalcSecret                             */
/* Description   | Calculates the shared secret key for the key             */
/*               | exchange with the key material of the key identified by  */
/*               | the keyId and the partner public key. The shared         */
/*               | secret key is stored as a key element in the same key.   */
/* Preconditions | -                                                        */
/* Parameters    | jobId  : Holds the identifier of the job                 */
/*               |          using the CSM service.                          */
/*               | keyId   : Holds the identifier of the key which          */
/*               |           shall be used for the key exchange protocol.   */
/*               | partnerPublicValuePtr  : Holds the pointer to the        */
/*               |                          memory location which contains  */
/*               |                           the partner public value.      */
/*               | partnerPublicValueLength  : Contains the length of the   */
/*               |                             partner public value         */
/*               |                             in bytes.                    */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful                          */
/*               | E_NOT_OK   : Request failed                              */
/*               | CRYPTO_E_BUSY : Request failed, service is still busy    */
/*               | CRYPTO_E_KEY_NOT_VALID : Request failed,                 */
/*               |                          the key state is invalid        */
/*               | CRYPTO_E_KEY_EMPTY : Request failed because of           */
/*               |                      uninitialized source key element    */
/* Notes         | SWS_Csm_91032                                            */
/****************************************************************************/
FUNC(Std_ReturnType, CSM_CODE) Csm_JobKeyExchangeCalcSecret
(
    uint32 jobId,
    uint32 keyId,
    P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) partnerPublicValuePtr,
    uint32 partnerPublicValueLength
)
{
    Std_ReturnType                      ud_ret;
    Crypto_JobPrimitiveInputOutputType  ud_jobInOut;
    
    ud_jobInOut.inputPtr                    = partnerPublicValuePtr;
    ud_jobInOut.inputLength                 = partnerPublicValueLength;
    ud_jobInOut.secondaryInputPtr           = NULL_PTR;
    ud_jobInOut.secondaryInputLength        = 0UL;
    ud_jobInOut.tertiaryInputPtr            = NULL_PTR;
    ud_jobInOut.tertiaryInputLength         = 0UL;
    ud_jobInOut.outputPtr                   = NULL_PTR;
    ud_jobInOut.outputLengthPtr             = NULL_PTR;
    ud_jobInOut.secondaryOutputPtr          = NULL_PTR;
    ud_jobInOut.secondaryOutputLengthPtr    = NULL_PTR;
    ud_jobInOut.verifyPtr                   = NULL_PTR;
    ud_jobInOut.mode                        = CRYPTO_OPERATIONMODE_SINGLECALL;
    ud_jobInOut.cryIfKeyId                  = keyId;
    ud_jobInOut.targetCryIfKeyId            = 0UL;
    
    ud_ret = Csm_JobBasedApi_ProcessJob( jobId, CRYPTO_KEYEXCHANGECALCSECRET, &ud_jobInOut, CSM_KEYSETMODE_KEYID );
    
    return ud_ret;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Csm_JobBasedApi_ProcessJob                               */
/* Description   |                                                          */
/* Preconditions | -                                                        */
/* Parameters    | jobId        :                                           */
/*               | udService    :                                           */
/*               | ptInOut      :                                           */
/*               | udKeySetMode :                                           */
/* Return Value  | Std_ReturnType                                           */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC(Std_ReturnType, CSM_CODE) Csm_JobBasedApi_ProcessJob
(
    uint32 u4JobId,
    Crypto_ServiceInfoType udService,
    P2VAR(Crypto_JobPrimitiveInputOutputType, AUTOMATIC, AUTOMATIC) ptInOut,
    Csm_KeySetModeType udKeySetMode
)
{
    P2CONST(Csm_Cfg_JobConfigType, AUTOMATIC, CSM_CONFIG_DATA)  pt_config;
    P2CONST(AB_83_ConstV uint32, AUTOMATIC, CSM_CONFIG_DATA)    pt_keyConfig;
    Std_ReturnType  ud_ret = E_NOT_OK;
    
    if( Csm_General_udStatus == CSM_S_INIT )
    {
        if( (u4JobId < Csm_Cfg_stJob.u4ConfigNum)
         && (ptInOut->cryIfKeyId < Csm_Cfg_stKey.u4ConfigNum)
         && (ptInOut->targetCryIfKeyId < Csm_Cfg_stKey.u4ConfigNum) )
        {
            pt_config = &Csm_Cfg_stJob.ptConfig[u4JobId];
            pt_keyConfig = Csm_Cfg_stKey.ptConfig;
            
            if( (pt_config->stJobPrimitiveInfo.primitiveInfo->service == udService)
             && (ptInOut->mode != (CRYPTO_OPERATIONMODE_START | CRYPTO_OPERATIONMODE_FINISH))
             && ((ptInOut->mode & CSM_OPERATIONMODE_MASK_SUF) != (Crypto_OperationModeType)0U)
             && ((ptInOut->mode & CSM_OPERATIONMODE_MASK_NOT_SUF) == (Crypto_OperationModeType)0U) )
            {
                if( (udKeySetMode & CSM_KEYSETMODE_KEYID) == CSM_KEYSETMODE_KEYID )
                {
                    ptInOut->cryIfKeyId = pt_keyConfig[ptInOut->cryIfKeyId];
                }
                
                if( (udKeySetMode & CSM_KEYSETMODE_TARGETKEYID) == CSM_KEYSETMODE_TARGETKEYID )
                {
                    ptInOut->targetCryIfKeyId = pt_keyConfig[ptInOut->targetCryIfKeyId];
                }
                
                ud_ret = Csm_Queue_ProcessJob( (uint16)u4JobId, ptInOut );
            }
        }
    }
    
    return ud_ret;
}

#define CSM_STOP_SEC_CODE
#include <Csm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2022/09/26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
