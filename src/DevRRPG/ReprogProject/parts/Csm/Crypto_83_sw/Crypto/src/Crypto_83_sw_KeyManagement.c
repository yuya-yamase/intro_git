/* Crypto_83_sw_KeyManagement_c_v2-0-0                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Crypto_83_sw/KeyManagement/CODE                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Crypto_83_sw.h>
#include "../inc/Crypto_83_sw_Internal.h"

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
#define CRYPTO_83_sw_START_SEC_CODE
#include <Crypto_83_sw_MemMap.h>

/****************************************************************************/
/* Function Name | Crypto_83_sw_KeyElementSet                               */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | cryptoKeyId  :                                           */
/*               | keyElementId :                                           */
/*               | keyPtr       :                                           */
/*               | keyLength    :                                           */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                             :                      */
/*               |  E_NOT_OK                         :                      */
/*               |  CRYPTO_E_BUSY                    :                      */
/*               |  CRYPTO_E_KEY_SIZE_MISMATCH       :                      */
/*               |  CRYPTO_E_KEY_WRITE_FAIL          :                      */
/*               |  CRYPTO_E_KEY_EMPTY               :                      */
/*               |  CSM_AB_E_SHE_KEY_INVALID         :                      */
/*               |  CSM_AB_E_SHE_KEY_WRITE_PROTECTED :                      */
/*               |  CSM_AB_E_SHE_KEY_UPDATE_ERROR    :                      */
/*               |  CSM_AB_E_SHE_MEMORY_FAILURE      :                      */
/*               |  CSM_AB_E_SHE_GENERAL_ERROR       :                      */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_KeyElementSet
(
    uint32 cryptoKeyId,
    uint32 keyElementId,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) keyPtr,
    uint32 keyLength
)
{
    Std_ReturnType                  ud_Ret = (Std_ReturnType)E_OK;
    Crypto_83_sw_DriverStatusType   ud_Status;

    ud_Status = Crypto_83_sw_GetStatus();

    if( ud_Status != CRYPTO_83_SW_S_CD_INIT )
    {
        ud_Ret = (Std_ReturnType)E_NOT_OK;
    }

    if( ud_Ret == (Std_ReturnType)E_OK )
    {
        if( ( keyPtr == NULL_PTR )
         || ( keyLength == (uint32)0UL ) )
        {
            ud_Ret = (Std_ReturnType)E_NOT_OK;
        }
    }

    if( ud_Ret == (Std_ReturnType)E_OK )
    {
        if( ( cryptoKeyId == CRYPTO_83_SW_KEYID_MASTER_ECU_KEY )
         || ( ( cryptoKeyId >= CRYPTO_83_SW_KEYID_KEY_1 )
           && ( cryptoKeyId <= CRYPTO_83_SW_KEYID_KEY_10) ) )
        {
            ud_Ret = Crypto_83_sw_NvMKey_KeyEleSet( cryptoKeyId, keyElementId, keyPtr, keyLength );
        }
        else if( cryptoKeyId == CRYPTO_83_SW_KEYID_RAM_KEY )
        {
            ud_Ret = Crypto_83_sw_RamKey_KeyEleSet( cryptoKeyId, keyElementId, keyPtr, keyLength );
        }
        else if( cryptoKeyId == CRYPTO_83_SW_KEYID_UID )
        {
            ud_Ret = Crypto_83_sw_UID_KeyEleSet( keyElementId, keyPtr, keyLength );
        }
        else if( cryptoKeyId == CRYPTO_83_SW_KEYID_PUBKEY )
        {
            ud_Ret = Crypto_83_sw_PubKey_KeyEleSet( keyElementId, keyPtr, keyLength );
        }
        else
        {
            ud_Ret = (Std_ReturnType)E_NOT_OK;
        }
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_KeySetValid                                 */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | cryptoKeyId :                                            */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK     :                                              */
/*               |  E_NOT_OK :                                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_KeySetValid
(
    uint32 cryptoKeyId
)
{
    Std_ReturnType                  ud_Ret = (Std_ReturnType)E_OK;
    Crypto_83_sw_DriverStatusType   ud_Status;

    ud_Status = Crypto_83_sw_GetStatus();

    if( ud_Status != CRYPTO_83_SW_S_CD_INIT )
    {
        ud_Ret = (Std_ReturnType)E_NOT_OK;
    }

    if( ud_Ret == (Std_ReturnType)E_OK )
    {
        if( (cryptoKeyId == CRYPTO_83_SW_KEYID_MASTER_ECU_KEY)
         || ( (cryptoKeyId >= CRYPTO_83_SW_KEYID_KEY_1)
           && (cryptoKeyId <= CRYPTO_83_SW_KEYID_RAM_KEY) ) )
        {
            Crypto_83_sw_SetSwsheValidStatus( cryptoKeyId, CRYPTO_83_SW_S_KEY_VALID );
        }
        else if( cryptoKeyId == CRYPTO_83_SW_KEYID_PUBKEY )
        {
            Crypto_83_sw_SetRsaValidStatus( CRYPTO_83_SW_S_KEY_VALID );
        }
        else
        {
            ud_Ret = (Std_ReturnType)E_NOT_OK;
        }
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_KeyElementGet                               */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | cryptoKeyId     :                                        */
/*               | keyElementId    :                                        */
/*               | resultPtr       :                                        */
/*               | resultLengthPtr :                                        */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                        :                           */
/*               |  E_NOT_OK                    :                           */
/*               |  CRYPTO_E_KEY_READ_FAIL      :                           */
/*               |  CSM_AB_E_SHE_MEMORY_FAILURE :                           */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_KeyElementGet
(
    uint32 cryptoKeyId,
    uint32 keyElementId,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA)  resultPtr,
    P2VAR(uint32, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) resultLengthPtr
)
{
    Std_ReturnType                  ud_Ret = (Std_ReturnType)E_OK;
    Crypto_83_sw_DriverStatusType   ud_Status;

    ud_Status = Crypto_83_sw_GetStatus();

    if( ud_Status != CRYPTO_83_SW_S_CD_INIT )
    {
        ud_Ret = (Std_ReturnType)E_NOT_OK;
    }

    if( ud_Ret == (Std_ReturnType)E_OK )
    {
        if( ( resultPtr == NULL_PTR )
         || ( resultLengthPtr == NULL_PTR )
         || ( *resultLengthPtr == (uint32)0UL ) )
        {
            ud_Ret = (Std_ReturnType)E_NOT_OK;
        }
    }

    if( ud_Ret == (Std_ReturnType)E_OK )
    {
        if( ( cryptoKeyId == CRYPTO_83_SW_KEYID_MASTER_ECU_KEY )
         || ( ( cryptoKeyId >= CRYPTO_83_SW_KEYID_KEY_1 )
           && ( cryptoKeyId <= CRYPTO_83_SW_KEYID_KEY_10) ) )
        {
            ud_Ret = Crypto_83_sw_NvMKey_KeyEleGet( cryptoKeyId, keyElementId, resultPtr, resultLengthPtr );
        }
        else if( cryptoKeyId == CRYPTO_83_SW_KEYID_RAM_KEY )
        {
            ud_Ret = Crypto_83_sw_RamKey_KeyEleGet( keyElementId, resultPtr, resultLengthPtr );
        }
        else if( cryptoKeyId == CRYPTO_83_SW_KEYID_UID )
        {
            ud_Ret = Crypto_83_sw_UID_KeyEleGet( keyElementId, resultPtr, resultLengthPtr );
        }
        else if( cryptoKeyId == CRYPTO_83_SW_KEYID_PUBKEY )
        {
            ud_Ret = Crypto_83_sw_PubKey_KeyEleGet( keyElementId );
        }
        else
        {
            ud_Ret = (Std_ReturnType)E_NOT_OK;
        }
    }

    return ud_Ret;

}

/****************************************************************************/
/* Function Name | Crypto_83_sw_RandomSeed                                  */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | cryptoKeyId :                                            */
/*               | seedPtr     :                                            */
/*               | seedLength  :                                            */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                       :                            */
/*               |  E_NOT_OK                   :                            */
/*               |  CRYPTO_E_BUSY              :                            */
/*               |  CSM_AB_E_SHE_RNG_SEED      :                            */
/*               |  CSM_AB_E_SHE_GENERAL_ERROR :                            */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_RandomSeed
(
    uint32 cryptoKeyId,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) seedPtr,
    uint32 seedLength
)
{
    Std_ReturnType                  ud_Ret = (Std_ReturnType)E_NOT_OK;
    Crypto_83_sw_DriverStatusType   ud_Status;

    ud_Status = Crypto_83_sw_GetStatus();

    if( ud_Status == CRYPTO_83_SW_S_CD_INIT )
    {
        ud_Ret = Crypto_83_sw_RndSeed_KeyEleSet( cryptoKeyId, seedPtr, seedLength );
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_KeyElementCopy                              */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | cryptoKeyId        :                                     */
/*               | keyElementId       :                                     */
/*               | targetCryptoKeyId  :                                     */
/*               | targetKeyElementId :                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_NOT_OK :                                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_KeyElementCopy
(
    uint32 cryptoKeyId,
    uint32 keyElementId,
    uint32 targetCryptoKeyId,
    uint32 targetKeyElementId
)
{
    return (Std_ReturnType)E_NOT_OK;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_KeyElementCopyPartial                       */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | cryptoKeyId            :                                 */
/*               | keyElementId           :                                 */
/*               | keyElementSourceOffset :                                 */
/*               | keyElementTargetOffset :                                 */
/*               | keyElementCooyLength   :                                 */
/*               | targetCryptoKeyId      :                                 */
/*               | targetKeyElementId     :                                 */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_NOT_OK :                                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_KeyElementCopyPartial
(
    uint32 cryptoKeyId,
    uint32 keyElementId,
    uint32 keyElementSourceOffset,
    uint32 keyElementTargetOffset,
    uint32 keyElementCopyLength,
    uint32 targetCryptoKeyId,
    uint32 targetKeyElementId
)
{
    return (Std_ReturnType)E_NOT_OK;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_KeyCopy                                     */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | cryptoKeyId       :                                      */
/*               | targetCryptoKeyId :                                      */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_NOT_OK :                                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_KeyCopy
(
    uint32 cryptoKeyId,
    uint32 targetCryptoKeyId
)
{
    return (Std_ReturnType)E_NOT_OK;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_KeyGenerate                                 */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | cryptoKeyId :                                            */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_NOT_OK :                                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_KeyGenerate
(
    uint32 cryptoKeyId
)
{
    return (Std_ReturnType)E_NOT_OK;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_KeyDerive                                   */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | cryptoKeyId       :                                      */
/*               | targetCryptoKeyId :                                      */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_NOT_OK :                                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_KeyDerive
(
    uint32 cryptoKeyId,
    uint32 targetCryptoKeyId
)
{
    return (Std_ReturnType)E_NOT_OK;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_KeyExchangeCalcPubVal                       */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | cryptoKeyId          :                                   */
/*               | publicValuePtr       :                                   */
/*               | publicValueLengthPtr :                                   */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_NOT_OK :                                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_KeyExchangeCalcPubVal
(
    uint32 cryptoKeyId,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA)  publicValuePtr,
    P2VAR(uint32, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) publicValueLengthPtr
)
{
    return (Std_ReturnType)E_NOT_OK;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_KeyExchangeCalcSecret                       */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | cryptoKeyId                 :                            */
/*               | partnerPublicValuePtr       :                            */
/*               | partnerPublicValueLengthPtr :                            */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_NOT_OK :                                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_KeyExchangeCalcSecret
(
    uint32 cryptoKeyId,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) partnerPublicValuePtr,
    uint32 partnerPublicValueLength
)
{
    return (Std_ReturnType)E_NOT_OK;
}

#define CRYPTO_83_sw_STOP_SEC_CODE
#include <Crypto_83_sw_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2023/01/13                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
