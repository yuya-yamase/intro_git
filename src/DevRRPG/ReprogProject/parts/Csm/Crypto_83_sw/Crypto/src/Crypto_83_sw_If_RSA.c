/* Crypto_83_sw_If_RSA_c_v2-0-0                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Crypto_83_sw/If_RSA/CODE                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Crypto_83_sw.h>
#include "../../RSA/inc/Crypto_83_sw_RSA.h"
#include "../../SHA256/inc/Crypto_83_sw_SHA256.h"
#include "../inc/Crypto_83_sw_Internal.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Public Key Parameter */
#define CRYPTO_83_SW_IF_N_PTR_POS_0                 ((uint32)0UL)
#define CRYPTO_83_SW_IF_N_PTR_POS_1                 ((uint32)1UL)
#define CRYPTO_83_SW_IF_N_PTR_POS_2                 ((uint32)2UL)
#define CRYPTO_83_SW_IF_N_PTR_POS_3                 ((uint32)3UL)
#define CRYPTO_83_SW_IF_N_LEN_POS_0                 ((uint32)4UL)
#define CRYPTO_83_SW_IF_N_LEN_POS_1                 ((uint32)5UL)
#define CRYPTO_83_SW_IF_N_LEN_POS_2                 ((uint32)6UL)
#define CRYPTO_83_SW_IF_N_LEN_POS_3                 ((uint32)7UL)
#define CRYPTO_83_SW_IF_E_DATA_POS_0                ((uint32)8UL)
#define CRYPTO_83_SW_IF_E_DATA_POS_1                ((uint32)9UL)
#define CRYPTO_83_SW_IF_E_DATA_POS_2                ((uint32)10UL)
#define CRYPTO_83_SW_IF_E_DATA_POS_3                ((uint32)11UL)
#define CRYPTO_83_SW_IF_PUBKEY_EXP_POS              ((uint8)0U)
#define CRYPTO_83_SW_IF_PUBKEY_MOD_POS              ((uint8)1U)
#define CRYPTO_83_SW_IF_PUBKEY_NUM                  ((uint8)2U)
#define CRYPTO_83_SW_IF_SWAP_PTR_POS_1              ((uint32)1UL)
#define CRYPTO_83_SW_IF_SWAP_PTR_POS_2              ((uint32)2UL)
#define CRYPTO_83_SW_IF_SWAP_PTR_POS_3              ((uint32)3UL)

/* Size Parameter */
#define CRYPTO_83_SW_IF_SIG_MESSAGE_SIZE_MAX        ((uint32)536870911UL)
#define CRYPTO_83_SW_IF_SIG_DATA_SIZE_MAX           ((uint32)384UL)
#define CRYPTO_83_SW_IF_EDATA_SIZE                  ((uint32)1UL)
#define CRYPTO_83_SW_IF_EDATA_1BYTE_SIZE            ((uint32)4UL)
#define CRYPTO_83_SW_IF_HASH_MESSAGE_SIZE_MAX       ((uint32)536870911UL)
#define CRYPTO_83_SW_IF_HASH_SIZE_MAX               ((uint32)32UL)

/* Enable Parameter */
#define CRYPTO_83_SW_IF_UPDATE_DISABLE              ((uint8)0U)
#define CRYPTO_83_SW_IF_UPDATE_ENABLE               ((uint8)1U)

/* Mask Parameter */
#define CRYPTO_83_SW_IF_2BIT_MASK                   ((uint32)0x03UL)

/* Shift Parameter */
#define CRYPTO_83_SW_IF_2BIT_SHIFT                  ((uint32)2UL)
#define CRYPTO_83_SW_IF_4BYTE_ADDRESS_CALC          ((uint32)4UL)

/* Array Parameter */
#define CRYPTO_83_SW_IF_POS_0                       ((uint8)0U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define CRYPTO_83_sw_START_SEC_CODE
#include <Crypto_83_sw_MemMap.h>

static FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_CheckRsaValidStatus
(
    uint32  u4CryptoKeyId
);

#define CRYPTO_83_sw_STOP_SEC_CODE
#include <Crypto_83_sw_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define CRYPTO_83_sw_START_SEC_VAR_NO_INIT
#include <Crypto_83_sw_MemMap.h>

static VAR(Crypto_83_sw_KeyValidStatusType, CRYPTO_83_sw_VAR_NO_INIT)       Crypto_83_sw_If_udPubKeyValidStatus;
static VAR(Crypto_83_sw_RSA_AsymPublicKeyType, CRYPTO_83_sw_VAR_NO_INIT)    Crypto_83_sw_If_stModKey;
static VAR(Crypto_83_sw_RSA_AsymPublicKeyType, CRYPTO_83_sw_VAR_NO_INIT)    Crypto_83_sw_If_stExpKey;
static VAR(Crypto_83_sw_RSA_PKCS1V15_CtxBufType, CRYPTO_83_sw_VAR_NO_INIT)  Crypto_83_sw_If_stRsaPkcs1v15ContextBuffer;
static VAR(Crypto_83_sw_RSA_PSS_CtxBufType, CRYPTO_83_sw_VAR_NO_INIT)       Crypto_83_sw_If_stRsaPssContextBuffer;
static VAR(Crypto_83_sw_SHA256_Hash_CtxBufType, CRYPTO_83_sw_VAR_NO_INIT)   Crypto_83_sw_If_stHashContextBuffer;

#define CRYPTO_83_sw_STOP_SEC_VAR_NO_INIT
#include <Crypto_83_sw_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define CRYPTO_83_sw_START_SEC_CODE
#include <Crypto_83_sw_MemMap.h>

/****************************************************************************/
/* Function Name | Crypto_83_sw_If_RsaInit                                  */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, CRYPTO_83_sw_CODE) Crypto_83_sw_If_RsaInit
(
    void
)
{
    (void)Crypto_83_sw_SecStd_MemSet( (void*)&Crypto_83_sw_If_stModKey.u4Data[0],
                                      (uint8)0U,
                                      CRYPTO_83_SW_PUBKEY_NDATA_SIZE );    /* no return check required */
    Crypto_83_sw_If_stModKey.u4Length = (uint32)0UL;

    (void)Crypto_83_sw_SecStd_MemSet( (void*)&Crypto_83_sw_If_stExpKey.u4Data[0],
                                      (uint8)0U,
                                      CRYPTO_83_SW_IF_EDATA_1BYTE_SIZE );    /* no return check required */
    Crypto_83_sw_If_stExpKey.u4Length = (uint32)0UL;

    Crypto_83_sw_If_udPubKeyValidStatus = CRYPTO_83_SW_S_KEY_INVALID;

    return;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_Hash                                        */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | ptJob :                                                  */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK     :                                              */
/*               |  E_NOT_OK :                                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_Hash
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
)
{
    Std_ReturnType      ud_Ret = (Std_ReturnType)E_OK;
    uint8  ud_ShaRet;
    uint8  ud_Hash[CRYPTO_83_SW_IF_HASH_SIZE_MAX];

    if( (ptJob->jobPrimitiveInputOutput.inputPtr == NULL_PTR)
     || (ptJob->jobPrimitiveInputOutput.outputPtr == NULL_PTR)
     || (ptJob->jobPrimitiveInputOutput.outputLengthPtr == NULL_PTR)
     || (ptJob->jobPrimitiveInputOutput.inputLength == (uint32)0UL)
     || (*(ptJob->jobPrimitiveInputOutput.outputLengthPtr) == (uint32)0UL)
     || (ptJob->jobPrimitiveInputOutput.inputLength > CRYPTO_83_SW_IF_HASH_MESSAGE_SIZE_MAX) )
    {
        ud_Ret = (Std_ReturnType)E_NOT_OK;
    }

    if( ud_Ret == (Std_ReturnType)E_OK )
    {
        Crypto_83_sw_SHA256_HashStart( &Crypto_83_sw_If_stHashContextBuffer );
        
        ud_ShaRet = Crypto_83_sw_SHA256_HashUpdate( (Crypto_83_sw_ConstR uint8 *)(ptJob->jobPrimitiveInputOutput.inputPtr),
                                                    (uint32)(ptJob->jobPrimitiveInputOutput.inputLength),
                                                    &Crypto_83_sw_If_stHashContextBuffer );
        
        if( ud_ShaRet == CRYPTO_83_SW_SHA256_OK )
        {
            Crypto_83_sw_SHA256_HashFinish( &ud_Hash[0],
                                            &Crypto_83_sw_If_stHashContextBuffer );
        }
        else
        {
            ud_Ret = (Std_ReturnType)E_NOT_OK;
        }
        
        if( ud_Ret == (Std_ReturnType)E_OK )
        {
            if( *(ptJob->jobPrimitiveInputOutput.outputLengthPtr) > CRYPTO_83_SW_IF_HASH_SIZE_MAX )
            {
                *(ptJob->jobPrimitiveInputOutput.outputLengthPtr) = CRYPTO_83_SW_IF_HASH_SIZE_MAX;
            }

            (void)Crypto_83_sw_SecStd_MemCpy( (void*)(ptJob->jobPrimitiveInputOutput.outputPtr),
                                              (void*)&ud_Hash[0],
                                              *(ptJob->jobPrimitiveInputOutput.outputLengthPtr) );   /* no return check required */
        }
    }
    
    return ud_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_RSA_PKCS1_SigVerStart                       */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | ptJob :                                                  */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                   :                                */
/*               |  E_NOT_OK               :                                */
/*               |  CRYPTO_E_KEY_NOT_VALID :                                */
/*               |  CRYPTO_E_KEY_EMPTY     :                                */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_RSA_PKCS1_SigVerStart
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
)
{
    P2CONST(Crypto_83_sw_RSA_AsymPublicKeyType, AUTOMATIC, CRYPTO_83_sw_VAR_NO_INIT) pt_PubKey[CRYPTO_83_SW_IF_PUBKEY_NUM];
    Std_ReturnType              ud_Ret;
    Crypto_83_sw_RSA_ReturnType ud_RsaRet;

    ud_Ret = Crypto_83_sw_CheckRsaValidStatus( ptJob->cryptoKeyId );

    if( ud_Ret == (Std_ReturnType)E_OK )
    {
        if( Crypto_83_sw_If_stModKey.u4Length == (uint32)0UL )
        {
            ud_Ret = (Std_ReturnType)CRYPTO_E_KEY_EMPTY;
        }
        else
        {
            pt_PubKey[CRYPTO_83_SW_IF_PUBKEY_EXP_POS] = &Crypto_83_sw_If_stExpKey;
            pt_PubKey[CRYPTO_83_SW_IF_PUBKEY_MOD_POS] = &Crypto_83_sw_If_stModKey;

            ud_RsaRet = Crypto_83_sw_RSA_PKCS1V15_VerStart( &Crypto_83_sw_If_stRsaPkcs1v15ContextBuffer,
                                                            pt_PubKey );

            if( ud_RsaRet == CRYPTO_83_SW_RSA_E_OK )
            {
                ud_Ret = (Std_ReturnType)E_OK;
            }
            else
            {
                ud_Ret = (Std_ReturnType)E_NOT_OK;
            }
        }
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_RSA_PKCS1_SigVerUpdate                      */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | ptJob :                                                  */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                   :                                */
/*               |  E_NOT_OK               :                                */
/*               |  CRYPTO_E_KEY_NOT_VALID :                                */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_RSA_PKCS1_SigVerUpdate
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
)
{
    Std_ReturnType              ud_Ret;
    Crypto_83_sw_RSA_ReturnType ud_RsaRet;

    ud_Ret = Crypto_83_sw_CheckRsaValidStatus( ptJob->cryptoKeyId );

    if( ud_Ret == (Std_ReturnType)E_OK )
    {
        if( ( ptJob->jobPrimitiveInputOutput.inputPtr == NULL_PTR )
           || ( ptJob->jobPrimitiveInputOutput.inputLength == (uint32)0UL )
           || ( ptJob->jobPrimitiveInputOutput.inputLength > CRYPTO_83_SW_IF_SIG_MESSAGE_SIZE_MAX ) )
        {
            ud_Ret = (Std_ReturnType)E_NOT_OK;
        }

        if( ud_Ret == (Std_ReturnType)E_OK )
        {
            ud_RsaRet = Crypto_83_sw_RSA_PKCS1V15_VerUpdate( &Crypto_83_sw_If_stRsaPkcs1v15ContextBuffer,
                                                             (Crypto_83_sw_ConstR uint8*)(ptJob->jobPrimitiveInputOutput.inputPtr),
                                                             (uint32)(ptJob->jobPrimitiveInputOutput.inputLength) );

            if( ud_RsaRet == CRYPTO_83_SW_RSA_E_OK )
            {
                ud_Ret = (Std_ReturnType)E_OK;
            }
            else
            {
                ud_Ret = (Std_ReturnType)E_NOT_OK;
            }
        }
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_RSA_PKCS1_SigVerFinish                      */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | ptJob :                                                  */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                   :                                */
/*               |  E_NOT_OK               :                                */
/*               |  CRYPTO_E_KEY_NOT_VALID :                                */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_RSA_PKCS1_SigVerFinish
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
)
{
    Std_ReturnType                      ud_Ret;
    Crypto_83_sw_RSA_ReturnType         ud_RsaRet;
    Crypto_83_sw_RSA_VerifyResultType   ud_RsaVerifyPtr;
    uint8                               u1_EnableStramUpdate;

    ud_Ret = Crypto_83_sw_CheckRsaValidStatus( ptJob->cryptoKeyId );

    if( ud_Ret == (Std_ReturnType)E_OK )
    {
        if( ( ptJob->jobPrimitiveInputOutput.secondaryInputPtr == NULL_PTR )
           || ( ptJob->jobPrimitiveInputOutput.verifyPtr == NULL_PTR )
           || ( ptJob->jobPrimitiveInputOutput.secondaryInputLength == (uint32)0UL )
           || ( ptJob->jobPrimitiveInputOutput.secondaryInputLength > CRYPTO_83_SW_IF_SIG_DATA_SIZE_MAX ) )
        {
            ud_Ret = (Std_ReturnType)E_NOT_OK;
        }
        else
        {
            u1_EnableStramUpdate = CRYPTO_83_SW_IF_UPDATE_DISABLE;

            if( ( ptJob->jobPrimitiveInputOutput.mode & CRYPTO_OPERATIONMODE_UPDATE ) != CRYPTO_OPERATIONMODE_UPDATE )
            {
                if( ( ptJob->jobPrimitiveInputOutput.inputPtr != NULL_PTR )
                 && ( ptJob->jobPrimitiveInputOutput.inputLength != (uint32)0UL )
                 && ( ptJob->jobPrimitiveInputOutput.inputLength <= CRYPTO_83_SW_IF_SIG_MESSAGE_SIZE_MAX ) )
                {
                    u1_EnableStramUpdate = CRYPTO_83_SW_IF_UPDATE_ENABLE;
                }
            }
        }

        if( ud_Ret == (Std_ReturnType)E_OK )
        {
            if( u1_EnableStramUpdate == CRYPTO_83_SW_IF_UPDATE_ENABLE )
            {
                ud_RsaRet = Crypto_83_sw_RSA_PKCS1V15_VerUpdate( &Crypto_83_sw_If_stRsaPkcs1v15ContextBuffer,
                                                                 (Crypto_83_sw_ConstR uint8*)(ptJob->jobPrimitiveInputOutput.inputPtr),
                                                                 (uint32)(ptJob->jobPrimitiveInputOutput.inputLength) );

                if( ud_RsaRet == CRYPTO_83_SW_RSA_E_OK )
                {
                    ud_Ret = (Std_ReturnType)E_OK;
                }
                else
                {
                    ud_Ret = (Std_ReturnType)E_NOT_OK;
                }
            }

            if( ud_Ret == (Std_ReturnType)E_OK )
            {
                Crypto_83_sw_If_stRsaPkcs1v15ContextBuffer.stRsaCtxBuf.ptExponent = &Crypto_83_sw_If_stExpKey;
                Crypto_83_sw_If_stRsaPkcs1v15ContextBuffer.stRsaCtxBuf.ptModulus = &Crypto_83_sw_If_stModKey;
                ud_RsaRet = Crypto_83_sw_RSA_PKCS1V15_VerFinish( &Crypto_83_sw_If_stRsaPkcs1v15ContextBuffer,
                                                                 (Crypto_83_sw_ConstR uint8*)(ptJob->jobPrimitiveInputOutput.secondaryInputPtr),
                                                                 (uint32)(ptJob->jobPrimitiveInputOutput.secondaryInputLength),
                                                                 &ud_RsaVerifyPtr );

                if( ud_RsaRet == CRYPTO_83_SW_RSA_E_OK )
                {
                    ud_Ret = (Std_ReturnType)E_OK;

                    if( ud_RsaVerifyPtr == CRYPTO_83_SW_RSA_E_VER_OK )
                    {
                        *(ptJob->jobPrimitiveInputOutput.verifyPtr) = CRYPTO_E_VER_OK;
                    }
                    else
                    {
                        *(ptJob->jobPrimitiveInputOutput.verifyPtr) = CRYPTO_E_VER_NOT_OK;
                    }
                }
                else
                {
                    ud_Ret = (Std_ReturnType)E_NOT_OK;
                }
            }
        }
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_RSA_PSS_SigVerStart                         */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | ptJob :                                                  */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                   :                                */
/*               |  E_NOT_OK               :                                */
/*               |  CRYPTO_E_KEY_NOT_VALID :                                */
/*               |  CRYPTO_E_KEY_EMPTY     :                                */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_RSA_PSS_SigVerStart
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
)
{
    P2CONST(Crypto_83_sw_RSA_AsymPublicKeyType, AUTOMATIC, CRYPTO_83_sw_VAR_NO_INIT) pt_PubKey[CRYPTO_83_SW_IF_PUBKEY_NUM];
    Std_ReturnType              ud_Ret;
    Crypto_83_sw_RSA_ReturnType ud_RsaRet;

    ud_Ret = Crypto_83_sw_CheckRsaValidStatus( ptJob->cryptoKeyId );

    if( ud_Ret == (Std_ReturnType)E_OK )
    {
        if( Crypto_83_sw_If_stModKey.u4Length == (uint32)0UL )
        {
            ud_Ret = (Std_ReturnType)CRYPTO_E_KEY_EMPTY;
        }
        else
        {
            pt_PubKey[CRYPTO_83_SW_IF_PUBKEY_EXP_POS] = &Crypto_83_sw_If_stExpKey;
            pt_PubKey[CRYPTO_83_SW_IF_PUBKEY_MOD_POS] = &Crypto_83_sw_If_stModKey;

            ud_RsaRet = Crypto_83_sw_RSA_PSS_VerStart( &Crypto_83_sw_If_stRsaPssContextBuffer,
                                                       pt_PubKey );

            if( ud_RsaRet == CRYPTO_83_SW_RSA_E_OK )
            {
                ud_Ret = (Std_ReturnType)E_OK;
            }
            else
            {
                ud_Ret = (Std_ReturnType)E_NOT_OK;
            }
        }
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_RSA_PSS_SigVerUpdate                        */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | ptJob :                                                  */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                   :                                */
/*               |  E_NOT_OK               :                                */
/*               |  CRYPTO_E_KEY_NOT_VALID :                                */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_RSA_PSS_SigVerUpdate
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
)
{
    Std_ReturnType              ud_Ret;
    Crypto_83_sw_RSA_ReturnType ud_RsaRet;

    ud_Ret = Crypto_83_sw_CheckRsaValidStatus( ptJob->cryptoKeyId );

    if( ud_Ret == (Std_ReturnType)E_OK )
    {
        if( ( ptJob->jobPrimitiveInputOutput.inputPtr == NULL_PTR )
           || ( ptJob->jobPrimitiveInputOutput.inputLength == (uint32)0UL )
           || ( ptJob->jobPrimitiveInputOutput.inputLength > CRYPTO_83_SW_IF_SIG_MESSAGE_SIZE_MAX ) )
        {
            ud_Ret = (Std_ReturnType)E_NOT_OK;
        }

        if( ud_Ret == (Std_ReturnType)E_OK )
        {
            ud_RsaRet = Crypto_83_sw_RSA_PSS_VerUpdate( &Crypto_83_sw_If_stRsaPssContextBuffer,
                                                        (Crypto_83_sw_ConstR uint8*)(ptJob->jobPrimitiveInputOutput.inputPtr),
                                                        (uint32)(ptJob->jobPrimitiveInputOutput.inputLength) );

            if( ud_RsaRet == CRYPTO_83_SW_RSA_E_OK )
            {
                ud_Ret = (Std_ReturnType)E_OK;
            }
            else
            {
                ud_Ret = (Std_ReturnType)E_NOT_OK;
            }
        }
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_RSA_PSS_SigVerFinish                        */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | ptJob :                                                  */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                   :                                */
/*               |  E_NOT_OK               :                                */
/*               |  CRYPTO_E_KEY_NOT_VALID :                                */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_RSA_PSS_SigVerFinish
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
)
{
    Std_ReturnType                      ud_Ret;
    Crypto_83_sw_RSA_ReturnType         ud_RsaRet;
    Crypto_83_sw_RSA_VerifyResultType   ud_RsaVerifyPtr;
    uint8                               u1_EnableStramUpdate;

    ud_Ret = Crypto_83_sw_CheckRsaValidStatus( ptJob->cryptoKeyId );

    if( ud_Ret == (Std_ReturnType)E_OK )
    {
        if( ( ptJob->jobPrimitiveInputOutput.secondaryInputPtr == NULL_PTR )
           || ( ptJob->jobPrimitiveInputOutput.verifyPtr == NULL_PTR )
           || ( ptJob->jobPrimitiveInputOutput.secondaryInputLength == (uint32)0UL )
           || ( ptJob->jobPrimitiveInputOutput.secondaryInputLength > CRYPTO_83_SW_IF_SIG_DATA_SIZE_MAX ) )
        {
            ud_Ret = (Std_ReturnType)E_NOT_OK;
        }
        else
        {
            u1_EnableStramUpdate = CRYPTO_83_SW_IF_UPDATE_DISABLE;

            if( ( ptJob->jobPrimitiveInputOutput.mode & CRYPTO_OPERATIONMODE_UPDATE ) != CRYPTO_OPERATIONMODE_UPDATE )
            {
                if( ( ptJob->jobPrimitiveInputOutput.inputPtr != NULL_PTR )
                 && ( ptJob->jobPrimitiveInputOutput.inputLength != (uint32)0UL )
                 && ( ptJob->jobPrimitiveInputOutput.inputLength <= CRYPTO_83_SW_IF_SIG_MESSAGE_SIZE_MAX ) )
                {
                    u1_EnableStramUpdate = CRYPTO_83_SW_IF_UPDATE_ENABLE;
                }
            }
        }

        if( ud_Ret == (Std_ReturnType)E_OK )
        {
            if( u1_EnableStramUpdate == CRYPTO_83_SW_IF_UPDATE_ENABLE )
            {
                ud_RsaRet = Crypto_83_sw_RSA_PSS_VerUpdate( &Crypto_83_sw_If_stRsaPssContextBuffer,
                                                            (Crypto_83_sw_ConstR uint8*)(ptJob->jobPrimitiveInputOutput.inputPtr),
                                                            (uint32)(ptJob->jobPrimitiveInputOutput.inputLength) );

                if( ud_RsaRet == CRYPTO_83_SW_RSA_E_OK )
                {
                    ud_Ret = (Std_ReturnType)E_OK;
                }
                else
                {
                    ud_Ret = (Std_ReturnType)E_NOT_OK;
                }
            }

            if( ud_Ret == (Std_ReturnType)E_OK )
            {
                Crypto_83_sw_If_stRsaPssContextBuffer.stRsaCtxBuf.ptExponent = &Crypto_83_sw_If_stExpKey;
                Crypto_83_sw_If_stRsaPssContextBuffer.stRsaCtxBuf.ptModulus = &Crypto_83_sw_If_stModKey;
                ud_RsaRet = Crypto_83_sw_RSA_PSS_VerFinish( &Crypto_83_sw_If_stRsaPssContextBuffer,
                                                            (Crypto_83_sw_ConstR uint8*)(ptJob->jobPrimitiveInputOutput.secondaryInputPtr),
                                                            (uint32)(ptJob->jobPrimitiveInputOutput.secondaryInputLength),
                                                            &ud_RsaVerifyPtr );

                if( ud_RsaRet == CRYPTO_83_SW_RSA_E_OK )
                {
                    ud_Ret = (Std_ReturnType)E_OK;

                    if( ud_RsaVerifyPtr == CRYPTO_83_SW_RSA_E_VER_OK )
                    {
                        *(ptJob->jobPrimitiveInputOutput.verifyPtr) = CRYPTO_E_VER_OK;
                    }
                    else
                    {
                        *(ptJob->jobPrimitiveInputOutput.verifyPtr) = CRYPTO_E_VER_NOT_OK;
                    }
                }
                else
                {
                    ud_Ret = (Std_ReturnType)E_NOT_OK;
                }
            }
        }
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_PubKey_KeyEleSet                            */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | u4KeyElementId :                                         */
/*               | ptKey          :                                         */
/*               | u4KeyLength    :                                         */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                       :                            */
/*               |  E_NOT_OK                   :                            */
/*               |  CRYPTO_E_KEY_SIZE_MISMATCH :                            */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_PubKey_KeyEleSet
(
    uint32 u4KeyElementId,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptKey,
    uint32 u4KeyLength
)
{
    Std_ReturnType  ud_Ret = (Std_ReturnType)E_OK;
    uint32          u4_NKeyLength;
    uint32          u4_EKey;
    uint32          u4_NKey4byteLength;
    uint32          u4_NKey4byteIndex;
    uint32          u4_NKey1byteIndex;
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) pt_NKey;

    if( u4KeyElementId == CRYPTO_83_SW_AB_KE_KEY )
    {
        if( u4KeyLength != CRYPTO_83_SW_PUBKEY_DATA_SIZE )
        {
            ud_Ret = (Std_ReturnType)CRYPTO_E_KEY_SIZE_MISMATCH;
        }

        if( ud_Ret == (Std_ReturnType)E_OK )
        {
            pt_NKey = (const uint8*)(((uint32)ptKey[CRYPTO_83_SW_IF_N_PTR_POS_0] << CRYPTO_83_SW_24BIT_SHIFT)   /* MISRA DEVIATION */
                                   | ((uint32)ptKey[CRYPTO_83_SW_IF_N_PTR_POS_1] << CRYPTO_83_SW_16BIT_SHIFT)
                                   | ((uint32)ptKey[CRYPTO_83_SW_IF_N_PTR_POS_2] << CRYPTO_83_SW_8BIT_SHIFT)
                                   | ((uint32)ptKey[CRYPTO_83_SW_IF_N_PTR_POS_3]));
            u4_NKeyLength = ((uint32)ptKey[CRYPTO_83_SW_IF_N_LEN_POS_0] << CRYPTO_83_SW_24BIT_SHIFT)
                          | ((uint32)ptKey[CRYPTO_83_SW_IF_N_LEN_POS_1] << CRYPTO_83_SW_16BIT_SHIFT)
                          | ((uint32)ptKey[CRYPTO_83_SW_IF_N_LEN_POS_2] << CRYPTO_83_SW_8BIT_SHIFT)
                          | ((uint32)ptKey[CRYPTO_83_SW_IF_N_LEN_POS_3]);
            u4_EKey = ((uint32)ptKey[CRYPTO_83_SW_IF_E_DATA_POS_0] << CRYPTO_83_SW_24BIT_SHIFT)
                    | ((uint32)ptKey[CRYPTO_83_SW_IF_E_DATA_POS_1] << CRYPTO_83_SW_16BIT_SHIFT)
                    | ((uint32)ptKey[CRYPTO_83_SW_IF_E_DATA_POS_2] << CRYPTO_83_SW_8BIT_SHIFT)
                    | ((uint32)ptKey[CRYPTO_83_SW_IF_E_DATA_POS_3]);
            
            if( pt_NKey == NULL_PTR )
            {
                ud_Ret = (Std_ReturnType)E_NOT_OK;
            }
            else
            {
                if( ( u4_NKeyLength == (uint32)0UL )
                 || ( u4_NKeyLength > CRYPTO_83_SW_PUBKEY_NDATA_SIZE )
                 || ( ( u4_NKeyLength & CRYPTO_83_SW_IF_2BIT_MASK ) != (uint32)0UL ) )
                {
                    ud_Ret = (Std_ReturnType)CRYPTO_E_KEY_SIZE_MISMATCH;
                }
            }
            
            if( ud_Ret == (Std_ReturnType)E_OK )
            {
                u4_NKey1byteIndex = u4_NKeyLength;
                u4_NKey4byteLength = u4_NKeyLength >> CRYPTO_83_SW_IF_2BIT_SHIFT;
                
                Crypto_83_sw_If_stModKey.u4Length = u4_NKey4byteLength;
                for( u4_NKey4byteIndex = (uint32)0UL; u4_NKey4byteIndex < u4_NKey4byteLength; u4_NKey4byteIndex++ )
                {
                    u4_NKey1byteIndex -= CRYPTO_83_SW_IF_4BYTE_ADDRESS_CALC;

                    Crypto_83_sw_If_stModKey.u4Data[u4_NKey4byteIndex] = ((uint32)pt_NKey[u4_NKey1byteIndex] << CRYPTO_83_SW_24BIT_SHIFT)
                                                                     | ((uint32)pt_NKey[u4_NKey1byteIndex + CRYPTO_83_SW_IF_SWAP_PTR_POS_1] << CRYPTO_83_SW_16BIT_SHIFT)
                                                                     | ((uint32)pt_NKey[u4_NKey1byteIndex + CRYPTO_83_SW_IF_SWAP_PTR_POS_2] << CRYPTO_83_SW_8BIT_SHIFT)
                                                                     | ((uint32)pt_NKey[u4_NKey1byteIndex + CRYPTO_83_SW_IF_SWAP_PTR_POS_3]);
                }

                Crypto_83_sw_If_stExpKey.u4Length = CRYPTO_83_SW_IF_EDATA_SIZE;
                Crypto_83_sw_If_stExpKey.u4Data[CRYPTO_83_SW_IF_POS_0] = u4_EKey;

                Crypto_83_sw_If_udPubKeyValidStatus = CRYPTO_83_SW_S_KEY_INVALID;
            }
        }
    }
    else
    {
        ud_Ret = (Std_ReturnType)E_NOT_OK;
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_PubKey_KeyEleGet                            */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | u4KeyElementId :                                         */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_NOT_OK               :                                */
/*               |  CRYPTO_E_KEY_READ_FAIL :                                */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_PubKey_KeyEleGet
(
    uint32 u4KeyElementId
)
{
    Std_ReturnType  ud_Ret = (Std_ReturnType)E_NOT_OK;

    if( u4KeyElementId == CRYPTO_83_SW_AB_KE_KEY )
    {
        ud_Ret = (Std_ReturnType)CRYPTO_E_KEY_READ_FAIL;
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SetRsaValidStatus                           */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | udSetValidStatus :                                       */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, CRYPTO_83_sw_CODE) Crypto_83_sw_SetRsaValidStatus
(
    Crypto_83_sw_KeyValidStatusType udSetValidStatus
)
{
    Crypto_83_sw_If_udPubKeyValidStatus = udSetValidStatus;

    return;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Crypto_83_sw_CheckRsaValidStatus                         */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | u4CryptoKeyId :                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                                                    */
/*               |  E_NOT_OK                                                */
/*               |  CRYPTO_E_KEY_NOT_VALID                                  */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_CheckRsaValidStatus
(
    uint32  u4CryptoKeyId
)
{
    Std_ReturnType  ud_Ret = (Std_ReturnType)E_NOT_OK;

    if( u4CryptoKeyId == CRYPTO_83_SW_KEYID_PUBKEY )
    {
        if( Crypto_83_sw_If_udPubKeyValidStatus == CRYPTO_83_SW_S_KEY_VALID )
        {
            ud_Ret = (Std_ReturnType)E_OK;
        }
        else
        {
            ud_Ret = (Std_ReturnType)CRYPTO_E_KEY_NOT_VALID;
        }
    }

    return ud_Ret;
}

#define CRYPTO_83_sw_STOP_SEC_CODE
#include <Crypto_83_sw_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2023/01/13                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
