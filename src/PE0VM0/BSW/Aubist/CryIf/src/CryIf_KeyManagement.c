/* CryIf_KeyManagement_c_v2-0-0                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CryIf/KeyManagement/CODE                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <CryIf.h>
#include <Csm_Cfg_Fixed.h>

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

#define CRYIF_START_SEC_SHARED_VAR_NO_INIT
#include <CryIf_MemMap.h>

static VAR(uint32, CRYIF_SHARED_VAR_NO_INIT) CryIf_KeyMng_u4ResultLength;

#define CRYIF_STOP_SEC_SHARED_VAR_NO_INIT
#include <CryIf_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define CRYIF_START_SEC_CODE
#include <CryIf_MemMap.h>

/****************************************************************************/
/* Function Name | CryIf_KeyElementSet                                      */
/* Description   | Call the key element setting function of Crypto.         */
/* Preconditions | -                                                        */
/* Parameters    | cryIfKeyId   : Holds the identifier of the key           */
/*               |                whose key element shall be set.           */
/*               | keyElementId : Holds the identifier of the key element   */
/*               |                which shall be set.                       */
/*               | keyPtr       : Holds the pointer to the key data         */
/*               |                which shall be set as key element.        */
/*               | keyLength    : Contains the  length of the key element   */
/*               |                in bytes.                                 */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful                          */
/*               | E_NOT_OK   : Request failed                              */
/*               | CRYPTO_E_BUSY  : Crypto Driver Object is busy            */
/*               | CRYPTO_E_KEY_WRITE_FAIL  : Write access was denied       */
/*               | CRYPTO_E_KEY_NOT_AVAILABLE  : The key is not available   */
/*               | CRYPTO_E_KEY_SIZE_MISMATCH : Key element size does not   */
/*               |                              match size of provided data */
/* Notes         | SWS_CryIf_91004                                          */
/****************************************************************************/
FUNC(Std_ReturnType, CRYIF_CODE) CryIf_KeyElementSet
(
    uint32 cryIfKeyId,
    uint32 keyElementId,
    P2CONST(uint8, AUTOMATIC, CRYIF_APPL_DATA) keyPtr,
    uint32 keyLength
)
{
    Std_ReturnType ud_Ret = E_NOT_OK;
    uint16 u2_CryptoIndex;
    uint32 u4_CryptoKeyId;

    if( cryIfKeyId < CryIf_Cfg_stKey.u4ConfigNum )
    {
        u2_CryptoIndex = (uint16)CryIf_Cfg_stKey.ptConfig[cryIfKeyId].u4CryptoIndex;

        if( CryIf_Cfg_stFunc.ptConfig[u2_CryptoIndex].ptKeyElementSet != NULL_PTR )
        {
            u4_CryptoKeyId = CryIf_Cfg_stKey.ptConfig[cryIfKeyId].u4CryptoKeyId;

            ud_Ret = CryIf_Cfg_stFunc.ptConfig[u2_CryptoIndex].ptKeyElementSet( u4_CryptoKeyId,
                                                                                keyElementId,
                                                                                keyPtr,
                                                                                keyLength );
        }
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | CryIf_KeySetValid                                        */
/* Description   | Call the Key activation function of Crypto.              */
/* Preconditions | -                                                        */
/* Parameters    | cryIfKeyId  : Holds the identifier of the key            */
/*               |               whose key elements shall be set to valid.  */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful                          */
/*               | E_NOT_OK   : Request failed                              */
/*               | CRYPTO_E_BUSY : Crypto Driver Object is busy             */
/* Notes         | SWS_CryIf_91005                                          */
/****************************************************************************/
FUNC(Std_ReturnType, CRYIF_CODE) CryIf_KeySetValid
(
    uint32 cryIfKeyId
)
{
    Std_ReturnType ud_Ret = E_NOT_OK;
    uint16 u2_CryptoIndex;
    uint32 u4_CryptoKeyId;

    if( cryIfKeyId < CryIf_Cfg_stKey.u4ConfigNum )
    {
        u2_CryptoIndex = (uint16)CryIf_Cfg_stKey.ptConfig[cryIfKeyId].u4CryptoIndex;

        if( CryIf_Cfg_stFunc.ptConfig[u2_CryptoIndex].ptKeySetValid != NULL_PTR )
        {
            u4_CryptoKeyId = CryIf_Cfg_stKey.ptConfig[cryIfKeyId].u4CryptoKeyId;

            ud_Ret = CryIf_Cfg_stFunc.ptConfig[u2_CryptoIndex].ptKeySetValid( u4_CryptoKeyId );
        }
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | CryIf_KeyElementGet                                      */
/* Description   | Call the Get key element function of Crypto.             */
/* Preconditions | -                                                        */
/* Parameters    | cryIfKeyId      : Holds the identifier of the key        */
/*               |                   whose key element shall be returned.   */
/*               | keyElementId    : Holds the identifier of the key        */
/*               |                   element which shall be returned.       */
/*               | resultPtr       : Holds the pointer of the buffer        */
/*               |                   for the returned key element           */
/*               | resultLengthPtr : Holds a pointer to a memory location   */
/*               |                   in which the length information is     */
/*               |                   stored.                                */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful                          */
/*               | E_NOT_OK   : Request failed                              */
/*               | CRYPTO_E_BUSY : Crypto Driver Object is busy             */
/*               | CRYPTO_E_KEY_NOT_AVAILABLE : The requested key element   */
/*               |                              is not available            */
/*               | CRYPTO_E_KEY_READ_FAIL  : Read access was denied         */
/*               | CRYPTO_E_KEY_EMPTY : Uninitialized source key element    */
/* Notes         | SWS_CryIf_91006                                          */
/****************************************************************************/
FUNC(Std_ReturnType, CRYIF_CODE) CryIf_KeyElementGet
(
    uint32 cryIfKeyId,
    uint32 keyElementId,
    P2VAR(uint8, AUTOMATIC, CRYIF_APPL_DATA) resultPtr,
    P2VAR(uint32, AUTOMATIC, CRYIF_APPL_DATA) resultLengthPtr
)
{
    Std_ReturnType ud_Ret = E_NOT_OK;
    uint16 u2_CryptoIndex;
    uint32 u4_CryptoKeyId;

    if( cryIfKeyId < CryIf_Cfg_stKey.u4ConfigNum )
    {
        u2_CryptoIndex = (uint16)CryIf_Cfg_stKey.ptConfig[cryIfKeyId].u4CryptoIndex;

        if( CryIf_Cfg_stFunc.ptConfig[u2_CryptoIndex].ptKeyElementGet != NULL_PTR )
        {
            u4_CryptoKeyId = CryIf_Cfg_stKey.ptConfig[cryIfKeyId].u4CryptoKeyId;

            ud_Ret = CryIf_Cfg_stFunc.ptConfig[u2_CryptoIndex].ptKeyElementGet( u4_CryptoKeyId,
                                                                                keyElementId,
                                                                                resultPtr,
                                                                                resultLengthPtr );
        }
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | CryIf_KeyElementCopy                                     */
/* Description   | Call the Key element copy function of Crypto.            */
/* Preconditions | -                                                        */
/* Parameters    | cryIfKeyId : Holds the identifier of the key  whose      */
/*               |              key element shall be the source element.    */
/*               | keyElementId  : Holds the identifier of the key element  */
/*               |                 which shall be the source                */
/*               |                 for the copy operation.                  */
/*               | targetCryIfKeyId  : Holds the identifier of the key      */
/*               |                     whose key element shall be           */
/*               |                     the destination element.             */
/*               | targetKeyElementId : Holds the identifier of  the key    */
/*               |                      element which shall be  the         */
/*               |                      destination for the copy operation. */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful                          */
/*               | E_NOT_OK   : Request failed                              */
/*               | CRYPTO_E_BUSY : Crypto Driver Object is busy             */
/*               | CRYPTO_E_KEY_NOT_AVAILABLE : The requested key element   */
/*               |                               is not available           */
/*               | CRYPTO_E_KEY_READ_FAIL : Not allowed                     */
/*               |                          to extract key element          */
/*               | CRYPTO_E_KEY_WRITE_FAIL : Not allowed                    */
/*               |                           to write key element           */
/*               | CRYPTO_E_KEY_SIZE_MISMATCH : Key element                 */
/*               |                              sizes are not compatible    */
/*               | CRYPTO_E_KEY_EMPTY : Uninitialized source key element    */
/* Notes         | SWS_CryIf_91015                                          */
/****************************************************************************/
FUNC(Std_ReturnType, CRYIF_CODE) CryIf_KeyElementCopy
(
    uint32 cryIfKeyId,
    uint32 keyElementId,
    uint32 targetCryIfKeyId,
    uint32 targetKeyElementId
)
{
    Std_ReturnType ud_Ret = E_NOT_OK;
    P2VAR(uint8, AUTOMATIC, CRYIF_APPL_DATA) pt_Result;
    uint32 u4_configNum;
    uint16 u2_CryptoIndex;
    uint16 u2_TargetCryptoIndex;
    uint32 u4_CryptoKeyId;
    uint32 u4_TargetCryptoKeyId;

    if( ( cryIfKeyId < CryIf_Cfg_stKey.u4ConfigNum ) && ( targetCryIfKeyId < CryIf_Cfg_stKey.u4ConfigNum ) )
    {
        u2_CryptoIndex = (uint16)CryIf_Cfg_stKey.ptConfig[cryIfKeyId].u4CryptoIndex;
        u2_TargetCryptoIndex = (uint16)CryIf_Cfg_stKey.ptConfig[targetCryIfKeyId].u4CryptoIndex;

        if( u2_CryptoIndex == u2_TargetCryptoIndex )
        {
            if( CryIf_Cfg_stFunc.ptConfig[u2_CryptoIndex].ptKeyElementCopy != NULL_PTR )
            {
                u4_CryptoKeyId = CryIf_Cfg_stKey.ptConfig[cryIfKeyId].u4CryptoKeyId;
                u4_TargetCryptoKeyId = CryIf_Cfg_stKey.ptConfig[targetCryIfKeyId].u4CryptoKeyId;

                ud_Ret = CryIf_Cfg_stFunc.ptConfig[u2_CryptoIndex].ptKeyElementCopy( u4_CryptoKeyId,
                                                                                     keyElementId,
                                                                                     u4_TargetCryptoKeyId,
                                                                                     targetKeyElementId );
            }
        }
        else
        {
            if( CryIf_Cfg_stFunc.ptConfig[u2_CryptoIndex].ptKeyElementGet != NULL_PTR )
            {
                if( CryIf_Cfg_stFunc.ptConfig[u2_TargetCryptoIndex].ptKeyElementSet != NULL_PTR )
                {
                    pt_Result = CryIf_Cfg_stElem.ptConfig;
                    CryIf_KeyMng_u4ResultLength = CryIf_Cfg_stElem.u4ConfigNum;

                    for( u4_configNum = 0UL; u4_configNum < CryIf_KeyMng_u4ResultLength; u4_configNum++ )
                    {
                        pt_Result[u4_configNum] = 0U;
                    }

                    u4_CryptoKeyId = CryIf_Cfg_stKey.ptConfig[cryIfKeyId].u4CryptoKeyId;

                    ud_Ret = CryIf_Cfg_stFunc.ptConfig[u2_CryptoIndex].ptKeyElementGet( u4_CryptoKeyId,
                                                                                        keyElementId,
                                                                                        pt_Result,
                                                                                        &CryIf_KeyMng_u4ResultLength );

                    if( ud_Ret == (Std_ReturnType)E_OK )
                    {
                        u4_TargetCryptoKeyId = CryIf_Cfg_stKey.ptConfig[targetCryIfKeyId].u4CryptoKeyId;

                        ud_Ret = CryIf_Cfg_stFunc.ptConfig[u2_TargetCryptoIndex].ptKeyElementSet( u4_TargetCryptoKeyId,
                                                                                                  targetKeyElementId,
                                                                                                  pt_Result,
                                                                                                  CryIf_KeyMng_u4ResultLength );
                    }

                    if( CryIf_Cfg_stElem.u4ConfigNum < CryIf_KeyMng_u4ResultLength )
                    {
                        CryIf_KeyMng_u4ResultLength = CryIf_Cfg_stElem.u4ConfigNum;
                    }
                    
                    for( u4_configNum = 0UL; u4_configNum < CryIf_KeyMng_u4ResultLength; u4_configNum++ )
                    {
                        pt_Result[u4_configNum] = 0U;
                    }
                }
            }
        }
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | CryIf_KeyElementCopyPartial                              */
/* Description   | Call the Partial copy of key element function of Crypto. */
/* Preconditions | -                                                        */
/* Parameters    | cryIfKeyId : Holds the identifier of the key whose       */
/*               |              key element shall be the source element     */
/*               | keyElementId : Holds the identifier of the key element   */
/*               |                which shall be the source                 */
/*               |                for the copy operation.                   */
/*               | keyElementSourceOffset  : This is the offset of          */
/*               |                           the source key element         */
/*               |                           indicating the start           */
/*               |                           index of the copy operation.   */
/*               | keyElementTargetOffset  : This is the offset of          */
/*               |                           the  target key element        */
/*               |                           indicating the start index of  */
/*               |                           the copy operation.            */
/*               | keyElementCopyLength  : Specifies the number of bytes    */
/*               |                         that shall be copied.            */
/*               | targetCryIfKeyId  : Holds the identifier of the key      */
/*               |                     whose key element                    */
/*               |                     shall be the destination element.    */
/*               | targetKeyElementId  : Holds the identifier of            */
/*               |                       the key element which shall be the */
/*               |                       destination for the copy operation.*/
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful                          */
/*               | E_NOT_OK   : Request failed                              */
/*               | CRYPTO_E_BUSY  : Crypto Driver Object is busy            */
/*               | CRYPTO_E_KEY_NOT_AVAILABLE : The requested key element   */
/*               |                              is not available            */
/*               | CRYPTO_E_KEY_READ_FAIL : Not allowed                     */
/*               |                          to extract key element          */
/*               | CRYPTO_E_KEY_WRITE_FAIL : Not allowed                    */
/*               |                           to write key element           */
/*               | CRYPTO_E_KEY_SIZE_MISMATCH : Key element sizes           */
/*               |                              are not compatible          */
/*               | CRYPTO_E_KEY_EMPTY : Uninitialized source key element    */
/* Notes         | SWS_CryIf_91018                                          */
/****************************************************************************/
FUNC(Std_ReturnType, CRYIF_CODE) CryIf_KeyElementCopyPartial
(
    uint32 cryIfKeyId,
    uint32 keyElementId,
    uint32 keyElementSourceOffset,
    uint32 keyElementTargetOffset,
    uint32 keyElementCopyLength,
    uint32 targetCryIfKeyId,
    uint32 targetKeyElementId
)
{
    Std_ReturnType ud_Ret = E_NOT_OK;
    uint16 u2_CryptoIndex;
    uint16 u2_TargetCryptoIndex;
    uint32 u4_CryptoKeyId;
    uint32 u4_TargetCryptoKeyId;

    if( ( cryIfKeyId < CryIf_Cfg_stKey.u4ConfigNum ) && ( targetCryIfKeyId < CryIf_Cfg_stKey.u4ConfigNum ) )
    {
        u2_CryptoIndex = (uint16)CryIf_Cfg_stKey.ptConfig[cryIfKeyId].u4CryptoIndex;
        u2_TargetCryptoIndex = (uint16)CryIf_Cfg_stKey.ptConfig[targetCryIfKeyId].u4CryptoIndex;

        if( u2_CryptoIndex == u2_TargetCryptoIndex )
        {
            if( CryIf_Cfg_stFunc.ptConfig[u2_CryptoIndex].ptKeyElemCopyPart != NULL_PTR )
            {
                u4_CryptoKeyId = CryIf_Cfg_stKey.ptConfig[cryIfKeyId].u4CryptoKeyId;
                u4_TargetCryptoKeyId = CryIf_Cfg_stKey.ptConfig[targetCryIfKeyId].u4CryptoKeyId;

                ud_Ret = CryIf_Cfg_stFunc.ptConfig[u2_CryptoIndex].ptKeyElemCopyPart( u4_CryptoKeyId,
                                                                                      keyElementId,
                                                                                      keyElementSourceOffset,
                                                                                      keyElementTargetOffset,
                                                                                      keyElementCopyLength,
                                                                                      u4_TargetCryptoKeyId,
                                                                                      targetKeyElementId );
            }
        }
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | CryIf_KeyCopy                                            */
/* Description   | Call the key copy function of Crypto.                    */
/* Preconditions | -                                                        */
/* Parameters    | cryIfKeyId : Holds the identifier of the key whose       */
/*               |              key element shall be the source element.    */
/*               | targetCryIfKeyId : Holds the identifier of the key       */
/*               |                    whose key element shall be            */
/*               |                    the destination element.              */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful                          */
/*               | E_NOT_OK   : Request failed                              */
/*               | CRYPTO_E_BUSY : Crypto Driver Object is busy             */
/*               | CRYPTO_E_KEY_NOT_AVAILABLE : The requested key element   */
/*               |                              is not available            */
/*               | CRYPTO_E_KEY_READ_FAIL : Not allowed                     */
/*               |                          to extract key element          */
/*               | CRYPTO_E_KEY_WRITE_FAIL : Not allowed                    */
/*               |                           to write key element           */
/*               | CRYPTO_E_KEY_SIZE_MISMATCH : Key element sizes           */
/*               |                              are not compatible          */
/*               | CRYPTO_E_KEY_EMPTY : Uninitialized source key element    */
/* Notes         | SWS_CryIf_91016                                          */
/****************************************************************************/
FUNC(Std_ReturnType, CRYIF_CODE) CryIf_KeyCopy
(
    uint32 cryIfKeyId,
    uint32 targetCryIfKeyId
)
{
    Std_ReturnType ud_Ret = E_NOT_OK;
    uint16 u2_CryptoIndex;
    uint16 u2_TargetCryptoIndex;
    uint32 u4_CryptoKeyId;
    uint32 u4_TargetCryptoKeyId;

    if( ( cryIfKeyId < CryIf_Cfg_stKey.u4ConfigNum ) && ( targetCryIfKeyId < CryIf_Cfg_stKey.u4ConfigNum ) )
    {
        u2_CryptoIndex = (uint16)CryIf_Cfg_stKey.ptConfig[cryIfKeyId].u4CryptoIndex;
        u2_TargetCryptoIndex = (uint16)CryIf_Cfg_stKey.ptConfig[targetCryIfKeyId].u4CryptoIndex;

        if( u2_CryptoIndex == u2_TargetCryptoIndex )
        {
            if( CryIf_Cfg_stFunc.ptConfig[u2_CryptoIndex].ptKeyCopy != NULL_PTR )
            {
                u4_CryptoKeyId = CryIf_Cfg_stKey.ptConfig[cryIfKeyId].u4CryptoKeyId;
                u4_TargetCryptoKeyId = CryIf_Cfg_stKey.ptConfig[targetCryIfKeyId].u4CryptoKeyId;

                ud_Ret = CryIf_Cfg_stFunc.ptConfig[u2_CryptoIndex].ptKeyCopy( u4_CryptoKeyId,
                                                                              u4_TargetCryptoKeyId );
            }
        }
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | CryIf_RandomSeed                                         */
/* Description   | Call the Random seed function of Crypto.                 */
/* Preconditions | -                                                        */
/* Parameters    | cryIfKeyId : Holds the identifier of the key             */
/*               |              for which a new seed shall be generated.    */
/*               | seedPtr    : Holds a pointer to the memory location      */
/*               |              which contains the data to feed the seed.   */
/*               | seedLength : Contains the length of the seed in bytes.   */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful                          */
/*               | E_NOT_OK   : Request failed                              */
/*               | CRYPTO_E_BUSY : Crypto Driver Object is busy             */
/*               | CRYPTO_E_KEY_NOT_VALID : The key state is invalid        */
/* Notes         | SWS_CryIf_91007                                          */
/****************************************************************************/
FUNC(Std_ReturnType, CRYIF_CODE) CryIf_RandomSeed
(
    uint32 cryIfKeyId,
    P2CONST(uint8, AUTOMATIC, CRYIF_APPL_DATA) seedPtr,
    uint32 seedLength
)
{
    Std_ReturnType ud_Ret = E_NOT_OK;
    uint16 u2_CryptoIndex;
    uint32 u4_CryptoKeyId;

    if( cryIfKeyId < CryIf_Cfg_stKey.u4ConfigNum )
    {
        u2_CryptoIndex = (uint16)CryIf_Cfg_stKey.ptConfig[cryIfKeyId].u4CryptoIndex;

        if( CryIf_Cfg_stFunc.ptConfig[u2_CryptoIndex].ptRandomSeed != NULL_PTR )
        {
            u4_CryptoKeyId = CryIf_Cfg_stKey.ptConfig[cryIfKeyId].u4CryptoKeyId;

            ud_Ret = CryIf_Cfg_stFunc.ptConfig[u2_CryptoIndex].ptRandomSeed( u4_CryptoKeyId,
                                                                             seedPtr,
                                                                             seedLength );
        }
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | CryIf_KeyGenerate                                        */
/* Description   | Call the Key generation function of Crypto.              */
/* Preconditions | -                                                        */
/* Parameters    | cryIfKeyId : Holds the identifier of the key which is    */
/*               |              to be updated with the generated value.     */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful                          */
/*               | E_NOT_OK   : Request failed                              */
/*               | CRYPTO_E_BUSY : Crypto Driver Object is busy             */
/*               | CRYPTO_E_KEY_EMPTY  : Uninitialized source key element   */
/* Notes         | SWS_CryIf_91008                                          */
/****************************************************************************/
FUNC(Std_ReturnType, CRYIF_CODE) CryIf_KeyGenerate
(
    uint32 cryIfKeyId
)
{
    Std_ReturnType ud_Ret = E_NOT_OK;
    uint16 u2_CryptoIndex;
    uint32 u4_CryptoKeyId;

    if( cryIfKeyId < CryIf_Cfg_stKey.u4ConfigNum )
    {
        u2_CryptoIndex = (uint16)CryIf_Cfg_stKey.ptConfig[cryIfKeyId].u4CryptoIndex;

        if( CryIf_Cfg_stFunc.ptConfig[u2_CryptoIndex].ptKeyGenerate != NULL_PTR )
        {
            u4_CryptoKeyId = CryIf_Cfg_stKey.ptConfig[cryIfKeyId].u4CryptoKeyId;

            ud_Ret = CryIf_Cfg_stFunc.ptConfig[u2_CryptoIndex].ptKeyGenerate( u4_CryptoKeyId );
        }
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | CryIf_KeyDerive                                          */
/* Description   | Call the Key derivation function of Crypto.              */
/* Preconditions | -                                                        */
/* Parameters    | cryIfKeyId  : Holds the identifier of the key            */
/*               |               which is used for key derivation.          */
/*               | targetCryIfKeyId : Holds the identifier of the key which */
/*               |                    is used to store the derived key.     */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful                          */
/*               | E_NOT_OK   : Request failed                              */
/*               | CRYPTO_E_BUSY : Crypto Driver Object is busy             */
/*               | CRYPTO_E_KEY_EMPTY  : Uninitialized source key element   */
/* Notes         | SWS_CryIf_91009                                          */
/****************************************************************************/
FUNC(Std_ReturnType, CRYIF_CODE) CryIf_KeyDerive
(
    uint32 cryIfKeyId,
    uint32 targetCryIfKeyId
)
{
    Std_ReturnType ud_Ret = E_NOT_OK;
    uint16 u2_CryptoIndex;
    uint16 u2_TargetCryptoIndex;
    uint32 u4_CryptoKeyId;
    uint32 u4_TargetCryptoKeyId;

    if( ( cryIfKeyId < CryIf_Cfg_stKey.u4ConfigNum ) && ( targetCryIfKeyId < CryIf_Cfg_stKey.u4ConfigNum ) )
    {
        u2_CryptoIndex = (uint16)CryIf_Cfg_stKey.ptConfig[cryIfKeyId].u4CryptoIndex;
        u2_TargetCryptoIndex = (uint16)CryIf_Cfg_stKey.ptConfig[targetCryIfKeyId].u4CryptoIndex;

        if( u2_CryptoIndex == u2_TargetCryptoIndex )
        {
            if( CryIf_Cfg_stFunc.ptConfig[u2_CryptoIndex].ptKeyDerive != NULL_PTR )
            {
                u4_CryptoKeyId = CryIf_Cfg_stKey.ptConfig[cryIfKeyId].u4CryptoKeyId;
                u4_TargetCryptoKeyId = CryIf_Cfg_stKey.ptConfig[targetCryIfKeyId].u4CryptoKeyId;

                ud_Ret = CryIf_Cfg_stFunc.ptConfig[u2_CryptoIndex].ptKeyDerive( u4_CryptoKeyId,
                                                                                u4_TargetCryptoKeyId );
            }
        }
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | CryIf_KeyExchangeCalcPubVal                              */
/* Description   | Call the Key exchange public key calculation function    */
/*               | of Crypto.                                               */
/* Preconditions | -                                                        */
/* Parameters    | cryIfKeyId : Holds the identifier of the key which shall */
/*               |              be used for the key exchange protocol.      */
/*               | publicValuePtr : Contains the pointer to the data        */
/*               |                  where the public value shall be stored. */
/*               | publicValueLengthPtr : Holds a pointer to the memory     */
/*               |                        location in which the public      */
/*               |                        value length information is       */
/*               |                        stored. On calling this function, */
/*               |                        this parameter shall contain the  */
/*               |                        size of the buffer provided by    */
/*               |                        publicValuePtr. When the request  */
/*               |                        has finished, the actual length   */
/*               |                        of the returned value shall be    */
/*               |                        stored.                           */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful                          */
/*               | E_NOT_OK   : Request failed                              */
/*               | CRYPTO_E_BUSY : Crypto Driver Object is busy             */
/*               | CRYPTO_E_KEY_EMPTY  : Uninitialized source key element   */
/* Notes         | SWS_CryIf_91010                                          */
/****************************************************************************/
FUNC(Std_ReturnType, CRYIF_CODE) CryIf_KeyExchangeCalcPubVal
(
    uint32 cryIfKeyId,
    P2VAR(uint8, AUTOMATIC, CRYIF_APPL_DATA) publicValuePtr,
    P2VAR(uint32, AUTOMATIC, CRYIF_APPL_DATA) publicValueLengthPtr
)
{
    Std_ReturnType ud_Ret = E_NOT_OK;
    uint16 u2_CryptoIndex;
    uint32 u4_CryptoKeyId;

    if( cryIfKeyId < CryIf_Cfg_stKey.u4ConfigNum )
    {
        u2_CryptoIndex = (uint16)CryIf_Cfg_stKey.ptConfig[cryIfKeyId].u4CryptoIndex;

        if( CryIf_Cfg_stFunc.ptConfig[u2_CryptoIndex].ptKeyExCalcPubVal != NULL_PTR )
        {
            u4_CryptoKeyId = CryIf_Cfg_stKey.ptConfig[cryIfKeyId].u4CryptoKeyId;

            ud_Ret = CryIf_Cfg_stFunc.ptConfig[u2_CryptoIndex].ptKeyExCalcPubVal( u4_CryptoKeyId,
                                                                                  publicValuePtr,
                                                                                  publicValueLengthPtr );
        }
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | CryIf_KeyExchangeCalcSecret                              */
/* Description   | Call the Key exchange shared key calculation function    */
/* Preconditions | -                                                        */
/* Parameters    | cryIfKeyId : Holds the identifier of the key which shall */
/*               |              be used for the key exchange protocol.      */
/*               | partnerPublicValuePtr : Holds the pointer to the         */
/*               |                         memory location which contains   */
/*               |                         the partner public value.        */
/*               | partnerPublicValueLength : Contains the length of the    */
/*               |                            partner public value in       */
/*               |                            bytes.                        */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK       : Request successful                          */
/*               | E_NOT_OK   : Request failed                              */
/*               | CRYPTO_E_BUSY : Crypto Driver Object is busy             */
/*               | CRYPTO_E_KEY_EMPTY : Uninitialized source key element    */
/* Notes         | SWS_CryIf_91011                                          */
/****************************************************************************/
FUNC(Std_ReturnType, CRYIF_CODE) CryIf_KeyExchangeCalcSecret
(
    uint32 cryIfKeyId,
    P2CONST(uint8, AUTOMATIC, CRYIF_APPL_DATA) partnerPublicValuePtr,
    uint32 partnerPublicValueLength
)
{
    Std_ReturnType ud_Ret = E_NOT_OK;
    uint16 u2_CryptoIndex;
    uint32 u4_CryptoKeyId;

    if( cryIfKeyId < CryIf_Cfg_stKey.u4ConfigNum )
    {
        u2_CryptoIndex = (uint16)CryIf_Cfg_stKey.ptConfig[cryIfKeyId].u4CryptoIndex;

        if( CryIf_Cfg_stFunc.ptConfig[u2_CryptoIndex].ptKeyExCalcSecret != NULL_PTR )
        {
            u4_CryptoKeyId = CryIf_Cfg_stKey.ptConfig[cryIfKeyId].u4CryptoKeyId;

            ud_Ret = CryIf_Cfg_stFunc.ptConfig[u2_CryptoIndex].ptKeyExCalcSecret( u4_CryptoKeyId,
                                                                                  partnerPublicValuePtr,
                                                                                  partnerPublicValueLength );
        }
    }

    return ud_Ret;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define CRYIF_STOP_SEC_CODE
#include <CryIf_MemMap.h>

/****************************************************************************/
/*  History                                                                 */
/*  Version        :Date                                                    */
/*  v2-0-0         :2022/09/26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
