#include "Std_Types.h"
//#include "Crypto_GeneralTypes.h"

#include "Crypto_83_sw.h"
//#include "Hsm_82_CycurHsm.h"
//#include "Crypto_83_sw_DnExt_BulkMac.h"

# define CRYPTO_83_sw_START_SEC_CODE
# include "Crypto_83_sw_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_ProcessJob(
    VAR(uint32, AUTOMATIC) objectId,
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_VAR) job /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    return E_OK;
}

FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_CancelJob(
    VAR(uint32, AUTOMATIC) objectId,
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_VAR) job) /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
{
    return E_OK;
}

FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_KeyElementSet(
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    VAR(uint32, AUTOMATIC) keyElementId,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_SW_CONST) keyPtr,
    VAR(uint32, AUTOMATIC) keyLength
)
{
    return E_OK;
}

FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_KeySetValid(VAR(uint32, AUTOMATIC) cryptoKeyId)
{
    return E_OK;
}

FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_KeyElementGet(
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    VAR(uint32, AUTOMATIC) keyElementId,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_VAR) resultPtr, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_83_sw_VAR) resultLengthPtr /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    return E_OK;
}

FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_KeyElementCopy(
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    VAR(uint32, AUTOMATIC) keyElementId,
    VAR(uint32, AUTOMATIC) targetCryptoKeyId,
    VAR(uint32, AUTOMATIC) targetKeyElementId
)
{
    return E_OK;
}

FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_KeyElementCopyPartial(
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    VAR(uint32, AUTOMATIC) keyElementId,
    VAR(uint32, AUTOMATIC) keyElementSourceOffset,
    VAR(uint32, AUTOMATIC) keyElementTargetOffset,
    VAR(uint32, AUTOMATIC) keyElementCopyLength,
    VAR(uint32, AUTOMATIC) targetCryptoKeyId,
    VAR(uint32, AUTOMATIC) targetKeyElementId
)
{
    return E_OK;
}

FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_KeyCopy(
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    VAR(uint32, AUTOMATIC) targetCryptoKeyId
)
{
    return E_OK;
}

FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_RandomSeed(
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_CONST) seedPtr,
    VAR(uint32, AUTOMATIC) seedLength
)
{
    return E_OK;
}

FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_KeyGenerate(
    VAR(uint32, AUTOMATIC) cryptoKeyId
)
{
    return E_OK;
}

FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_KeyDerive(
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    VAR(uint32, AUTOMATIC) targetCryptoKeyId
)
{
    return E_OK;
}

FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_KeyExchangeCalcPubVal(
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_VAR) publicValuePtr, /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
    P2VAR(uint32, AUTOMATIC, CRYPTO_83_sw_VAR) publicValueLengthPtr /* PRQA S 3432  #This rule violation is suppressed because it is not occurring due to the Crypto Driver implementation */
)
{
    return E_OK;
}

FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_KeyExchangeCalcSecret(
    VAR(uint32, AUTOMATIC) cryptoKeyId,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_CONST) partnerPublicValuePtr,
    VAR(uint32, AUTOMATIC) partnerPublicValueLength
)
{
    return E_OK;
}

FUNC(void, CRYPTO_83_sw_CODE) Crypto_83_sw_Init
(
    P2CONST(Crypto_83_sw_ConfigType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) configPtr
)
{

}

void Crypto_83_sw_Ab_MainFunctionOut()
{

}

void Crypto_83_sw_Ab_MainFunctionIn()
{
    
}

#define CRYPTO_83_sw_STOP_SEC_CODE
#include "Crypto_83_sw_MemMap.h"
