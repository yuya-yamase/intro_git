/* Csm_DirectApi_c_v2-0-0                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Csm/DirectApi/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Csm.h>
#include <CryIf.h>
#include "../inc/Csm_General.h"

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

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define CSM_START_SEC_CODE
#include <Csm_MemMap.h>

/****************************************************************************/
/* Function Name | Csm_KeyElementSet                                        */
/* Description   | Sets the given key element bytes to the key              */
/*               | identified by keyId.                                     */
/* Preconditions | -                                                        */
/* Parameters    | keyId  : Holds the identifier of the key                 */
/*               |          for which a new material shall be set.          */
/*               | keyElementId   : Holds the identifier of the key element */
/*               |                  to be written.                          */
/*               | keyPtr  : Holds the pointer to the key element bytes     */
/*               |           to be processed.                               */
/*               | keyLength  : Contains the number of key element bytes.   */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful                          */
/*               | E_NOT_OK   : Request failed                              */
/*               | CRYPTO_E_BUSY  : Request failed,                         */
/*               |                  Crypto Driver Object is busy            */
/*               | CRYPTO_E_KEY_WRITE_FAIL  : Request failed because        */
/*               |                            write access was denied       */
/*               | CRYPTO_E_KEY_NOT_AVAILABLE  : Request failed because     */
/*               |                               the key is not available   */
/*               | CRYPTO_E_KEY_SIZE_MISMATCH : Request failed, key element */
/*               |                              size does not match         */
/*               |                              size of provided data       */
/* Notes         | SWS_Csm_00957                                            */
/****************************************************************************/
FUNC(Std_ReturnType, CSM_CODE) Csm_KeyElementSet
(
    uint32 keyId,
    uint32 keyElementId,
    P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) keyPtr,
    uint32 keyLength
)
{
    P2CONST(AB_83_ConstV uint32, AUTOMATIC, CSM_CONFIG_DATA)    pt_keyConfig;
    Std_ReturnType  ud_ret = E_NOT_OK;
    uint32          u4_keyId;
    
    if( Csm_General_udStatus == CSM_S_INIT )
    {
        if( keyId < Csm_Cfg_stKey.u4ConfigNum )
        {
            pt_keyConfig = Csm_Cfg_stKey.ptConfig;
            
            u4_keyId = pt_keyConfig[keyId];
            
            ud_ret = CryIf_KeyElementSet( u4_keyId,
                                          keyElementId,
                                          keyPtr,
                                          keyLength );
        }
    }
    
    return ud_ret;
}

/****************************************************************************/
/* Function Name | Csm_KeySetValid                                          */
/* Description   | Sets the key state of the key                            */
/*               | identified by keyId to valid.                            */
/* Preconditions | -                                                        */
/* Parameters    | keyId  : Holds the identifier of the key                 */
/*               |          from which a key element shall be extracted.    */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful                          */
/*               | E_NOT_OK   : Request failed                              */
/*               | CRYPTO_E_BUSY  : Request failed,                         */
/*               |                  Crypto Driver Object is busy            */
/* Notes         | SWS_Csm_00958                                            */
/****************************************************************************/
FUNC(Std_ReturnType, CSM_CODE) Csm_KeySetValid
(
    uint32 keyId
)
{
    P2CONST(AB_83_ConstV uint32, AUTOMATIC, CSM_CONFIG_DATA)    pt_keyConfig;
    Std_ReturnType  ud_ret = E_NOT_OK;
    uint32          u4_keyId;
    
    if( Csm_General_udStatus == CSM_S_INIT )
    {
        if( keyId < Csm_Cfg_stKey.u4ConfigNum )
        {
            pt_keyConfig = Csm_Cfg_stKey.ptConfig;
            
            u4_keyId = pt_keyConfig[keyId];
            
            ud_ret = CryIf_KeySetValid( u4_keyId );
        }
    }
    
    return ud_ret;
}

/****************************************************************************/
/* Function Name | Csm_KeyElementGet                                        */
/* Description   | Retrieves the key element bytes from a specific          */
/*               | key element of the key identified by the keyId and       */
/*               | stores the key element in the memory location            */
/*               | pointed by the key pointer.                              */
/* Preconditions | -                                                        */
/* Parameters    | keyId  : Holds the identifier of the key                 */
/*               |          for which a new material shall be extracted.    */
/*               | keyElementId   : Holds the identifier of the key element */
/*               |                  to be extracted.                        */
/*               | keyPtr  : Holds the pointer to the memory location       */
/*               |           where the key shall be copied to.              */
/*               | keyLengthPtr  : Holds a pointer to the memory location   */
/*               |                 in which the output buffer length        */
/*               |                 in bytes is stored. On calling this      */
/*               |                 function, this parameter shall contain   */
/*               |                 the buffer length in bytes of the keyPtr.*/
/*               |                 When the request has finished,           */
/*               |                 the actual size of the written           */
/*               |                 input bytes shall be stored.             */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful                          */
/*               | E_NOT_OK   : Request failed                              */
/*               | CRYPTO_E_BUSY  : Request failed,                         */
/*               |                  Crypto Driver Object is busy            */
/*               | CRYPTO_E_KEY_NOT_AVAILABLE  : Request failed,            */
/*               |                               the requested key element  */
/*               |                               is not available           */
/*               | CRYPTO_E_KEY_READ_FAIL  : Request failed because         */
/*               |                           write access was denied        */
/*               | CRYPTO_E_KEY_EMPTY : Request failed because of           */
/*               |                      uninitialized source key element    */
/* Notes         | SWS_Csm_00959                                            */
/****************************************************************************/
FUNC(Std_ReturnType, CSM_CODE) Csm_KeyElementGet
(
    uint32 keyId,
    uint32 keyElementId,
    P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) keyPtr,
    P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) keyLengthPtr
)
{
    P2CONST(AB_83_ConstV uint32, AUTOMATIC, CSM_CONFIG_DATA)    pt_keyConfig;
    Std_ReturnType  ud_ret = E_NOT_OK;
    uint32          u4_keyId;
    
    if( Csm_General_udStatus == CSM_S_INIT )
    {
        if( keyId < Csm_Cfg_stKey.u4ConfigNum )
        {
            pt_keyConfig = Csm_Cfg_stKey.ptConfig;
            
            u4_keyId = pt_keyConfig[keyId];
            
            ud_ret = CryIf_KeyElementGet( u4_keyId,
                                          keyElementId,
                                          keyPtr,
                                          keyLengthPtr );
        }
    }
    
    return ud_ret;
}

/****************************************************************************/
/* Function Name | Csm_KeyElementCopy                                       */
/* Description   | This function shall copy a key elements from one key     */
/*               | to a target key.                                         */
/* Preconditions | -                                                        */
/* Parameters    | keyId  : Holds the identifier of the key                 */
/*               |          whose key element shall be the source element.  */
/*               | keyElementId  : Holds the identifier of the key element  */
/*               |                 which shall be the source                */
/*               |                 for the copy operation.                  */
/*               | targetKeyId  : Holds the identifier of the key           */
/*               |                whose key element shall be                */
/*               |                the destination element.                  */
/*               | targetKeyElementId  : Holds the identifier of            */
/*               |                       the key element which shall be     */
/*               |                       the destination                    */
/*               |                       for the copy operation.            */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful                          */
/*               | E_NOT_OK   : Request failed                              */
/*               | CRYPTO_E_BUSY  : Request failed,                         */
/*               |                  Crypto Driver Object is busy            */
/*               | CRYPTO_E_KEY_NOT_AVAILABLE  : Request failed,            */
/*               |                               the requested key element  */
/*               |                               is not available           */
/*               | CRYPTO_E_KEY_READ_FAIL: Request failed, not allowed      */
/*               |                         to extract key element           */
/*               | CRYPTO_E_KEY_WRITE_FAIL  : Request failed, not allowed   */
/*               |                            to write key element          */
/*               | CRYPTO_E_KEY_SIZE_MISMATCH : Request failed, key element */
/*               |                              sizes are not compatible    */
/*               | CRYPTO_E_KEY_EMPTY : Request failed because of           */
/*               |                      uninitialized source key element    */
/* Notes         | SWS_Csm_00969                                            */
/****************************************************************************/
FUNC(Std_ReturnType, CSM_CODE) Csm_KeyElementCopy
(
    const uint32 keyId,
    const uint32 keyElementId,
    const uint32 targetKeyId,
    const uint32 targetKeyElementId
)
{
    P2CONST(AB_83_ConstV uint32, AUTOMATIC, CSM_CONFIG_DATA)    pt_keyConfig;
    Std_ReturnType  ud_ret = E_NOT_OK;
    uint32          u4_keyId;
    uint32          u4_targetKeyId;
    
    if( Csm_General_udStatus == CSM_S_INIT )
    {
        if( (keyId < Csm_Cfg_stKey.u4ConfigNum)
         && (targetKeyId < Csm_Cfg_stKey.u4ConfigNum) )
        {
            pt_keyConfig = Csm_Cfg_stKey.ptConfig;
            
            u4_keyId = pt_keyConfig[keyId];
            u4_targetKeyId = pt_keyConfig[targetKeyId];
            
            ud_ret = CryIf_KeyElementCopy( u4_keyId,
                                           keyElementId,
                                           u4_targetKeyId,
                                           targetKeyElementId );
        }
    }
    
    return ud_ret;
}

/****************************************************************************/
/* Function Name | Csm_KeyCopy                                              */
/* Description   | This function shall copy all key elements                */
/*               | from the source key to a target key.                     */
/* Preconditions | -                                                        */
/* Parameters    | keyId  : Holds the identifier of the key                 */
/*               |          whose key element shall be the source element.  */
/*               | targetKeyId  : Holds the identifier of the key           */
/*               |                whose key element shall be                */
/*               |                the destination element.                  */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful                          */
/*               | E_NOT_OK   : Request failed                              */
/*               | CRYPTO_E_BUSY  : Request failed,                         */
/*               |                  Crypto Driver Object is busy            */
/*               | CRYPTO_E_KEY_NOT_AVAILABLE  : Request failed,            */
/*               |                               the requested key element  */
/*               |                               is not available           */
/*               | CRYPTO_E_KEY_READ_FAIL: Request failed, not allowed      */
/*               |                         to extract key element           */
/*               | CRYPTO_E_KEY_WRITE_FAIL  : Request failed, not allowed   */
/*               |                            to write key element          */
/*               | CRYPTO_E_KEY_SIZE_MISMATCH : Request failed, key element */
/*               |                              sizes are not compatible    */
/*               | CRYPTO_E_KEY_EMPTY : Request failed because of           */
/*               |                      uninitialized source key element    */
/* Notes         | SWS_Csm_01034                                            */
/****************************************************************************/
FUNC(Std_ReturnType, CSM_CODE) Csm_KeyCopy
(
    const uint32 keyId,
    const uint32 targetKeyId
)
{
    P2CONST(AB_83_ConstV uint32, AUTOMATIC, CSM_CONFIG_DATA)    pt_keyConfig;
    Std_ReturnType  ud_ret = E_NOT_OK;
    uint32          u4_keyId;
    uint32          u4_targetKeyId;
    
    if( Csm_General_udStatus == CSM_S_INIT )
    {
        if( (keyId < Csm_Cfg_stKey.u4ConfigNum)
         && (targetKeyId < Csm_Cfg_stKey.u4ConfigNum) )
        {
            pt_keyConfig = Csm_Cfg_stKey.ptConfig;
            
            u4_keyId = pt_keyConfig[keyId];
            u4_targetKeyId = pt_keyConfig[targetKeyId];
            
            ud_ret = CryIf_KeyCopy( u4_keyId,
                                    u4_targetKeyId );
        }
    }
    
    return ud_ret;
}

/****************************************************************************/
/* Function Name | Csm_KeyElementCopyPartial                                */
/* Description   | Copies a key element to another key element              */
/*               | in the same crypto driver. The keyElementSourceOffset    */
/*               | and keyElementCopyLength allows to copy just a part of   */
/*               | the source key element into the destination.             */
/*               | The offset into the target key is also                   */
/*               | specified with this function.                            */
/* Preconditions | -                                                        */
/* Parameters    | keyId  : Holds the identifier of the key                 */
/*               |          whose key element shall be the source element   */
/*               |          for copy operation.                             */
/*               | keyElementId  : Holds the identifier of the key element  */
/*               |                 which shall be the source                */
/*               |                 for the copy operation.                  */
/*               | keyElementSourceOffset  : This is the offset of          */
/*               |                           the source key element         */
/*               |                           indicating the start           */
/*               |                           index of the copy operation.   */
/*               | keyElementTargetOffset  : This is the offset of          */
/*               |                           the destination key element    */
/*               |                           indicating the start index of  */
/*               |                           the copy operation.            */
/*               | keyElementCopyLength  : Specifies the number of bytes    */
/*               |                         that shall be copied.            */
/*               | targetKeyId  : Holds the identifier of the key           */
/*               |                whose key element                         */
/*               |                shall be the destination element.         */
/*               | targetKeyElementId  : Holds the identifier of            */
/*               |                       the key element which shall be the */
/*               |                       destination for the copy operation.*/
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful                          */
/*               | E_NOT_OK   : Request failed                              */
/*               | CRYPTO_E_BUSY  : Request failed,                         */
/*               |                  Crypto Driver Object is busy            */
/*               | CRYPTO_E_KEY_NOT_AVAILABLE  : Request failed,            */
/*               |                               the requested key element  */
/*               |                               is not available           */
/*               | CRYPTO_E_KEY_READ_FAIL: Request failed, not allowed      */
/*               |                         to extract key element           */
/*               | CRYPTO_E_KEY_WRITE_FAIL  : Request failed, not allowed   */
/*               |                            to write key element          */
/*               | CRYPTO_E_KEY_SIZE_MISMATCH : Request failed, key element */
/*               |                              sizes are not compatible    */
/*               | CRYPTO_E_KEY_EMPTY : Request failed because of           */
/*               |                      uninitialized source key element    */
/* Notes         | SWS_Csm_91025                                            */
/****************************************************************************/
FUNC(Std_ReturnType, CSM_CODE) Csm_KeyElementCopyPartial
(
    uint32 keyId,
    uint32 keyElementId,
    uint32 keyElementSourceOffset,
    uint32 keyElementTargetOffset,
    uint32 keyElementCopyLength,
    uint32 targetKeyId,
    uint32 targetKeyElementId
)
{
    P2CONST(AB_83_ConstV uint32, AUTOMATIC, CSM_CONFIG_DATA)    pt_keyConfig;
    Std_ReturnType  ud_ret = E_NOT_OK;
    uint32          u4_keyId;
    uint32          u4_targetKeyId;
    
    if( Csm_General_udStatus == CSM_S_INIT )
    {
        if( (keyId < Csm_Cfg_stKey.u4ConfigNum)
         && (targetKeyId < Csm_Cfg_stKey.u4ConfigNum) )
        {
            pt_keyConfig = Csm_Cfg_stKey.ptConfig;
            
            u4_keyId = pt_keyConfig[keyId];
            u4_targetKeyId = pt_keyConfig[targetKeyId];
            
            ud_ret = CryIf_KeyElementCopyPartial( u4_keyId,
                                                  keyElementId,
                                                  keyElementSourceOffset,
                                                  keyElementTargetOffset,
                                                  keyElementCopyLength,
                                                  u4_targetKeyId,
                                                  targetKeyElementId );
        }
    }
    
    return ud_ret;
}

/****************************************************************************/
/* Function Name | Csm_RandomSeed                                           */
/* Description   | Feeds the key element CRYPTO_KE_RANDOM_SEED              */
/*               | with a random seed.                                      */
/* Preconditions | -                                                        */
/* Parameters    | keyId  : Holds the identifier of the key                 */
/*               |          for which a new seed shall be generated.        */
/*               | seedPtr   : Holds a pointer to the memory location       */
/*               |             which contains the data to feed the seed.    */
/*               | seedLength  : Contains the length of the seed in bytes.  */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful                          */
/*               | E_NOT_OK   : Request failed                              */
/*               | CRYPTO_E_BUSY : Request failed,                          */
/*               |                 Crypto Driver Object is busy             */
/*               | CRYPTO_E_KEY_NOT_VALID  : Request failed,                */
/*               |                          the key state is invalid        */
/* Notes         | SWS_Csm_01051                                            */
/****************************************************************************/
FUNC(Std_ReturnType, CSM_CODE) Csm_RandomSeed
(
    uint32 keyId,
    P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) seedPtr,
    uint32 seedLength
)
{
    P2CONST(AB_83_ConstV uint32, AUTOMATIC, CSM_CONFIG_DATA)    pt_keyConfig;
    Std_ReturnType  ud_ret = E_NOT_OK;
    uint32          u4_keyId;
    
    if( Csm_General_udStatus == CSM_S_INIT )
    {
        if( keyId < Csm_Cfg_stKey.u4ConfigNum )
        {
            pt_keyConfig = Csm_Cfg_stKey.ptConfig;
            
            u4_keyId = pt_keyConfig[keyId];
            
            ud_ret = CryIf_RandomSeed( u4_keyId,
                                       seedPtr,
                                       seedLength );
        }
    }
    
    return ud_ret;
}

/****************************************************************************/
/* Function Name | Csm_KeyGenerate                                          */
/* Description   | Generates new key material and store it                  */
/*               | in the key identified by keyId.                          */
/* Preconditions | -                                                        */
/* Parameters    | keyId  : Holds the identifier of the key                 */
/*               |          for which a new material shall be generated.    */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful                          */
/*               | E_NOT_OK   : Request failed                              */
/*               | CRYPTO_E_BUSY : Request failed,                          */
/*               |                 Crypto Driver Object is busy             */
/*               | CRYPTO_E_KEY_NOT_VALID  : Request failed,                */
/*               |                          the key state is invalid        */
/*               | CRYPTO_E_KEY_EMPTY  : Request failed because of          */
/*               |                       uninitialized source key element   */
/* Notes         | SWS_Csm_00955                                            */
/****************************************************************************/
FUNC(Std_ReturnType, CSM_CODE) Csm_KeyGenerate
(
    uint32 keyId
)
{
    P2CONST(AB_83_ConstV uint32, AUTOMATIC, CSM_CONFIG_DATA)    pt_keyConfig;
    Std_ReturnType  ud_ret = E_NOT_OK;
    uint32          u4_keyId;
    
    if( Csm_General_udStatus == CSM_S_INIT )
    {
        if( keyId < Csm_Cfg_stKey.u4ConfigNum )
        {
            pt_keyConfig = Csm_Cfg_stKey.ptConfig;
            
            u4_keyId = pt_keyConfig[keyId];
            
            ud_ret = CryIf_KeyGenerate( u4_keyId );
        }
    }
    
    return ud_ret;
}

/****************************************************************************/
/* Function Name | Csm_KeyDerive                                            */
/* Description   | Derives a new key by using the key elements              */
/*               | in the given key identified by the keyId.                */
/*               | The given key contains the key elements for              */
/*               | the password and salt. The derived key is stored         */
/*               | in the key element with the id 1 of the key identified   */
/*               | by targetCryptoKeyId.                                    */
/* Preconditions | -                                                        */
/* Parameters    | keyId  : Holds the identifier of the key                 */
/*               |          which is used for key derivation.               */
/*               | targetKeyId  : Holds the identifier of the key           */
/*               |                which is used to store the derived key.   */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful                          */
/*               | E_NOT_OK   : Request failed                              */
/*               | CRYPTO_E_BUSY : Request failed,                          */
/*               |                 Crypto Driver Object is busy             */
/*               | CRYPTO_E_KEY_READ_FAIL  : Request failed, not allowed    */
/*               |                           to extract key element         */
/*               | CRYPTO_E_KEY_WRITE_FAIL  : Request failed, not allowed   */
/*               |                            to write key element          */
/*               | CRYPTO_E_KEY_NOT_VALID  : Request failed,                */
/*               |                          the key state is invalid        */
/*               | CRYPTO_E_KEY_SIZE_MISMATCH  : Request failed,            */
/*               |                               key element sizes          */
/*               |                               are not compatible         */
/*               | CRYPTO_E_KEY_EMPTY  : Request failed because of          */
/*               |                       uninitialized source key element   */
/* Notes         | SWS_Csm_00956                                            */
/****************************************************************************/
FUNC(Std_ReturnType, CSM_CODE) Csm_KeyDerive
(
    uint32 keyId,
    uint32 targetKeyId
)
{
    P2CONST(AB_83_ConstV uint32, AUTOMATIC, CSM_CONFIG_DATA)    pt_keyConfig;
    Std_ReturnType  ud_ret = E_NOT_OK;
    uint32          u4_keyId;
    uint32          u4_targetKeyId;
    
    if( Csm_General_udStatus == CSM_S_INIT )
    {
        if( (keyId < Csm_Cfg_stKey.u4ConfigNum)
         && (targetKeyId < Csm_Cfg_stKey.u4ConfigNum) )
        {
            pt_keyConfig = Csm_Cfg_stKey.ptConfig;
            
            u4_keyId = pt_keyConfig[keyId];
            u4_targetKeyId = pt_keyConfig[targetKeyId];
            
            ud_ret = CryIf_KeyDerive( u4_keyId,
                                      u4_targetKeyId );
        }
    }
    
    return ud_ret;
}

/****************************************************************************/
/* Function Name | Csm_KeyExchangeCalcPubVal                                */
/* Description   | Calculates the public value of the current user          */
/*               | for the key exchange and stores the public key           */
/*               | in the memory location pointed                           */
/*               | by the public value pointer.                             */
/* Preconditions | -                                                        */
/* Parameters    | keyId  : Holds the identifier of the key which shall be  */
/*               |          used for the key exchange protocol.             */
/*               | publicValuePtr  : Contains the pointer to the data       */
/*               |                   where the public value shall be stored.*/
/*               | publicValueLengthPtr  : Holds a pointer to the           */
/*               |                         memory location in which         */
/*               |                         the public value                 */
/*               |                         length information is stored.    */
/*               |                         On calling this function,        */
/*               |                         this parameter shall contain     */
/*               |                         the size of the buffer provided  */
/*               |                         by publicValuePtr. When the      */
/*               |                         request has finished,            */
/*               |                         the actual length of             */
/*               |                         the returned value               */
/*               |                         shall be stored.                 */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful                          */
/*               | E_NOT_OK   : Request failed                              */
/*               | CRYPTO_E_BUSY : Request failed,                          */
/*               |                 Crypto Driver Object is busy             */
/*               | CRYPTO_E_KEY_NOT_VALID  : Request failed,                */
/*               |                          the key state is invalid        */
/*               | CRYPTO_E_KEY_EMPTY  : Request failed because of          */
/*               |                       uninitialized source key element   */
/* Notes         | SWS_Csm_00966                                            */
/****************************************************************************/
FUNC(Std_ReturnType, CSM_CODE) Csm_KeyExchangeCalcPubVal
(
    uint32 keyId,
    P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) publicValuePtr,
    P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) publicValueLengthPtr
)
{
    P2CONST(AB_83_ConstV uint32, AUTOMATIC, CSM_CONFIG_DATA)    pt_keyConfig;
    Std_ReturnType  ud_ret = E_NOT_OK;
    uint32          u4_keyId;
    
    if( Csm_General_udStatus == CSM_S_INIT )
    {
        if( keyId < Csm_Cfg_stKey.u4ConfigNum )
        {
            pt_keyConfig = Csm_Cfg_stKey.ptConfig;
            
            u4_keyId = pt_keyConfig[keyId];
            
            ud_ret = CryIf_KeyExchangeCalcPubVal( u4_keyId,
                                                  publicValuePtr,
                                                  publicValueLengthPtr );
        }
    }
    
    return ud_ret;
}

/****************************************************************************/
/* Function Name | Csm_KeyExchangeCalcSecret                                */
/* Description   | Calculates the shared secret key for the key exchange    */
/*               | with the key material of the key identified by           */
/*               | the keyId and the partner public key. The shared         */
/*               | secret key is stored as a key element in the same key.   */
/* Preconditions | -                                                        */
/* Parameters    | keyId  : Holds the identifier of the key which shall be  */
/*               |          used for the key exchange protocol.             */
/*               | partnerPublicValuePtr  : Holds the pointer to the        */
/*               |                          memory location which contains  */
/*               |                          the partner public value.       */
/*               | partnerPublicValueLength  : Contains the length of       */
/*               |                             the partner public value     */
/*               |                             in bytes.                    */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful                          */
/*               | E_NOT_OK   : Request failed                              */
/*               | CRYPTO_E_BUSY : Request failed,                          */
/*               |                 Crypto Driver Object is busy             */
/*               | CRYPTO_E_KEY_NOT_VALID  : Request failed,                */
/*               |                          the key state is invalid        */
/*               | CRYPTO_E_KEY_EMPTY  : Request failed because of          */
/*               |                       uninitialized source key element   */
/* Notes         | SWS_Csm_00967                                            */
/****************************************************************************/
FUNC(Std_ReturnType, CSM_CODE) Csm_KeyExchangeCalcSecret
(
    uint32 keyId,
    P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) partnerPublicValuePtr,
    uint32 partnerPublicValueLength
)
{
    P2CONST(AB_83_ConstV uint32, AUTOMATIC, CSM_CONFIG_DATA)    pt_keyConfig;
    Std_ReturnType  ud_ret = E_NOT_OK;
    uint32          u4_keyId;
    
    if( Csm_General_udStatus == CSM_S_INIT )
    {
        if( keyId < Csm_Cfg_stKey.u4ConfigNum )
        {
            pt_keyConfig = Csm_Cfg_stKey.ptConfig;
            
            u4_keyId = pt_keyConfig[keyId];
            
            ud_ret = CryIf_KeyExchangeCalcSecret( u4_keyId,
                                                  partnerPublicValuePtr,
                                                  partnerPublicValueLength );
        }
    }
    
    return ud_ret;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define CSM_STOP_SEC_CODE
#include <Csm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2022/09/26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
