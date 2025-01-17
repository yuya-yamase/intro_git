/* Crypto_83_sw_SWSHE_ifcrypto_c_v2-0-0                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | swshe/ifcrypto/CODE                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../inc/Crypto_83_sw_SWSHE.h"
#include "../inc/Crypto_83_sw_SWSHE_ifcrypto.h"
#include "../../AES128/inc/Crypto_83_sw_AES128.h"
#include "../../SecStd/inc/Crypto_83_sw_SecStd_String.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define CRYPTO_83_SW_SWSHE_KEY_CACHE_MISS            ((uint8)0U)
#define CRYPTO_83_SW_SWSHE_KEY_CACHE_HIT             ((uint8)1U)
#define CRYPTO_83_SW_SWSHE_CMAC_BLOCK_ADDR           ((uint8)15U)
#define CRYPTO_83_SW_SWSHE_CMAC_LEN_TO_BLOCK_SHIFT   ((uint8)4U)
#define CRYPTO_83_SW_SWSHE_CTX_CRYBUF_1BYTE          ((uint8)0U)
#define CRYPTO_83_SW_SWSHE_CTX_CRYBUF_2BYTE          ((uint8)1U)
#define CRYPTO_83_SW_SWSHE_CTX_CRYBUF_3BYTE          ((uint8)2U)
#define CRYPTO_83_SW_SWSHE_CTX_CRYBUF_4BYTE          ((uint8)3U)

#define CRYPTO_83_SW_SWSHE_CMAC_ONE_BLOCK            ((uint32)1U)
#define CRYPTO_83_SW_SWSHE_CMAC_MAXLENGTH            ((uint32)0xFFFFFFF1U)
#define CRYPTO_83_SW_SWSHE_CMAC_MAXBLOCK             ((uint32)0x10000000U)

#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
#define CRYPTO_83_SW_SWSHE_KEY_CACHE_EXPIRE          ((uint16)1000U)
#define CRYPTO_83_SW_SWSHE_IF_U2_ZERO                ((uint16)0U)
#endif

#define CRYPTO_83_SW_SWSHE_IF_U4_ZERO                ((uint32)0UL)

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define CRYPTO_83_sw_START_SEC_CODE
#include <Crypto_83_sw_MemMap.h>

static FUNC(uint8, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_GetCmacCache
(
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_VAR_NO_INIT) ptKey,
    P2VAR(Crypto_83_sw_AES128_CMac_CtxBufType*, AUTOMATIC, AUTOMATIC) ptCtx
);

#define CRYPTO_83_sw_STOP_SEC_CODE
#include <Crypto_83_sw_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define CRYPTO_83_sw_START_SEC_VAR_NO_INIT
#include <Crypto_83_sw_MemMap.h>

static VAR(Crypto_83_sw_AES128_RandomGen_CtxBufType, CRYPTO_83_sw_VAR_NO_INIT) Crypto_83_sw_Swshe_stCtxRnd;               /* for random buffer */

typedef struct {
    Crypto_83_sw_AES128_CMac_CtxBufType stCtxCmac;
#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
    uint16 u2Expire;
#endif
} Crypto_83_sw_Swshe_KeyCacheType;

static VAR(Crypto_83_sw_Swshe_KeyCacheType, CRYPTO_83_sw_VAR_NO_INIT) Crypto_83_sw_Swshe_stKeyCache;

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
/* Function Name | Crypto_83_sw_SWSHE_IfcryptoInit                          */
/* Description   | Ifcrypto initialization                                  */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_IfcryptoInit
(
    void
)
{

    /* KeyCashe clear */

    (void)Crypto_83_sw_SecStd_MemSet( &Crypto_83_sw_Swshe_stKeyCache, (uint8)0x00U, (uint32)sizeof(Crypto_83_sw_Swshe_KeyCacheType) ); /* no return check required */
#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
    Crypto_83_sw_Swshe_stKeyCache.u2Expire = CRYPTO_83_SW_SWSHE_KEY_CACHE_EXPIRE;
#endif

    /* CtxRnd clear */
    (void)Crypto_83_sw_SecStd_MemSet( &Crypto_83_sw_Swshe_stCtxRnd, (uint8)0x00U, (uint32)sizeof(Crypto_83_sw_AES128_RandomGen_CtxBufType) ); /* no return check required */

    return;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_AES128_EncEcb                         */
/* Description   | ECB Encryption                                           */
/* Preconditions | -                                                        */
/* Parameters    | (in)  ptKey    : Keydata start address(16byte)           */
/*               | (in)  ptPlain  : Plain text start address(16byte)        */
/*               | (out) ptCipher : Cipher text start address(16byte)       */
/* Return Value  | Error Code                                               */
/*               |  E_OK                                                    */
/*               |  CSM_AB_E_SHE_GENERAL_ERROR                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_AES128_EncEcb
(
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_VAR_NO_INIT) ptKey,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptPlain,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptCipher
)
{
    Crypto_83_sw_AES128_Ecb_CtxBufType   st_Ctx;
    uint8                                u1_CplRet;
    Std_ReturnType                       u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_GENERAL_ERROR;

    /* AES128 ECB mode initialization */
    u1_CplRet = Crypto_83_sw_AES128_Ecb_start( (Crypto_83_sw_ConstR uint8*)ptKey, (uint8)CRYPTO_83_SW_SWSHE_KEY_SIZE, &st_Ctx );
    if( u1_CplRet == CRYPTO_83_SW_AES128_OK )
    {
        /* AES128 ECB mode encryption */
        u1_CplRet = Crypto_83_sw_AES128_Ecb_updateEnc( (Crypto_83_sw_ConstR uint8*)ptPlain, (uint8*)ptCipher, (uint8)CRYPTO_83_SW_SWSHE_BLOCK_SIZE, &st_Ctx );
        if( u1_CplRet == CRYPTO_83_SW_AES128_OK )
        {
            /* AES128 ECB mode finish */
            Crypto_83_sw_AES128_Ecb_finish( &st_Ctx );
        }
    }
    if( u1_CplRet == CRYPTO_83_SW_AES128_OK )
    {
        u1_Ret = (Std_ReturnType)E_OK;
    }

    return u1_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_AES128_DecEcb                         */
/* Description   | ECB Decryption                                           */
/* Preconditions | -                                                        */
/* Parameters    | (in)  ptKey    : Keydata start address(16byte)           */
/*               | (in)  ptCipher : Plain text start address(16byte)        */
/*               | (out) ptPlain  : Cipher text start address(16byte)       */
/* Return Value  | Error Code                                               */
/*               |  E_OK                                                    */
/*               |  CSM_AB_E_SHE_GENERAL_ERROR                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_AES128_DecEcb
(
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_VAR_NO_INIT) ptKey,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptCipher,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptPlain
)
{
    Crypto_83_sw_AES128_Ecb_CtxBufType   st_Ctx;
    uint8                                u1_CplRet;
    Std_ReturnType                       u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_GENERAL_ERROR;

    /* AES128 ECB mode initialization */
    u1_CplRet = Crypto_83_sw_AES128_Ecb_start( (Crypto_83_sw_ConstR uint8*)ptKey, (uint8)CRYPTO_83_SW_SWSHE_KEY_SIZE, &st_Ctx );
    if( u1_CplRet == CRYPTO_83_SW_AES128_OK )
    {
        /* AES128 ECB mode decryption */
        u1_CplRet = Crypto_83_sw_AES128_Ecb_updateDec( (Crypto_83_sw_ConstR uint8*)ptCipher, (uint8*)ptPlain, (uint8)CRYPTO_83_SW_SWSHE_BLOCK_SIZE, &st_Ctx );
        if( u1_CplRet == CRYPTO_83_SW_AES128_OK )
        {
            /* AES128 ECB mode finish */
            Crypto_83_sw_AES128_Ecb_finish( &st_Ctx );
        }
    }

    if( u1_CplRet == CRYPTO_83_SW_AES128_OK )
    {
        u1_Ret = (Std_ReturnType)E_OK;
    }

    return u1_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_AES128_EncCbc                         */
/* Description   | CBC Encryption                                           */
/* Preconditions | -                                                        */
/* Parameters    | (in)  ptKey    : Keydata start address(16byte)           */
/*               | (in)  ptIvdata : IV start address(16byte)                */
/*               | (in)  u4Len    : Plain text Block size                   */
/*               | (in)  ptPlain  : Plain text start address                */
/*               | (out) ptCipher : Cipher text start address               */
/* Return Value  | Error Code                                               */
/*               |  E_OK                                                    */
/*               |  CSM_AB_E_SHE_GENERAL_ERROR                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_AES128_EncCbc
(
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_VAR_NO_INIT) ptKey,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_VAR_NO_INIT) ptIvdata,
    uint32 u4Len,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptPlain,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptCipher
)
{
    Crypto_83_sw_AES128_Cbc_CtxBufType   st_Ctx;
    uint32                               u4_Cnt;
    uint8                                u1_CplRet;
    Std_ReturnType                       u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_GENERAL_ERROR;

    /* AES128 CBC mode initialization */
    u1_CplRet = Crypto_83_sw_AES128_Cbc_start( (Crypto_83_sw_ConstR uint8*)ptKey, (uint8)CRYPTO_83_SW_SWSHE_KEY_SIZE, (Crypto_83_sw_ConstR uint8*)ptIvdata, (uint8)CRYPTO_83_SW_SWSHE_BLOCK_SIZE, &st_Ctx );
    if( u1_CplRet == CRYPTO_83_SW_AES128_OK )
    {
        for( u4_Cnt = (uint32)0U; u4_Cnt < u4Len; (u4_Cnt += (uint32)CRYPTO_83_SW_SWSHE_BLOCK_SIZE) )
        {
            u1_CplRet = Crypto_83_sw_AES128_Cbc_updateEnc( (Crypto_83_sw_ConstR uint8*)&ptPlain[u4_Cnt], (uint8*)&ptCipher[u4_Cnt], (uint8)CRYPTO_83_SW_SWSHE_BLOCK_SIZE, &st_Ctx );
            if( u1_CplRet != CRYPTO_83_SW_AES128_OK )
            {
                break;
            }
        }
    }
    Crypto_83_sw_AES128_Cbc_finish( &st_Ctx );
    if( u1_CplRet == CRYPTO_83_SW_AES128_OK )
    {
        u1_Ret = (Std_ReturnType)E_OK;
    }

    return u1_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_AES128_DecCbc                         */
/* Description   | CBC Decryption                                           */
/* Preconditions | -                                                        */
/* Parameters    | (in)  ptKey    : Keydata start address(16byte)           */
/*               | (in)  ptIvdata : IV start address(16byte)                */
/*               | (in)  u4Len    : Cipher text Block size                  */
/*               | (in)  ptCipher : Cipher text start address               */
/*               | (out) ptPlain  : Plain text start address                */
/* Return Value  | Error Code                                               */
/*               |  E_OK                                                    */
/*               |  CSM_AB_E_SHE_GENERAL_ERROR                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_AES128_DecCbc
(
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_VAR_NO_INIT) ptKey,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_VAR_NO_INIT) ptIvdata,
    uint32 u4Len,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptCipher,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptPlain
)
{
    Crypto_83_sw_AES128_Cbc_CtxBufType   st_Ctx;
    uint32                               u4_Cnt;
    uint8                                u1_CplRet;
    Std_ReturnType                       u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_GENERAL_ERROR;

    /* AES128 CBC mode initialization */
    u1_CplRet = Crypto_83_sw_AES128_Cbc_start( (Crypto_83_sw_ConstR uint8*)ptKey, (uint8)CRYPTO_83_SW_SWSHE_KEY_SIZE, (Crypto_83_sw_ConstR uint8*)ptIvdata, (uint8)CRYPTO_83_SW_SWSHE_BLOCK_SIZE, &st_Ctx );
    if( u1_CplRet == CRYPTO_83_SW_AES128_OK )
    {
        for( u4_Cnt = (uint32)0U; u4_Cnt < u4Len; (u4_Cnt += (uint32)CRYPTO_83_SW_SWSHE_BLOCK_SIZE) )
        {
            u1_CplRet = Crypto_83_sw_AES128_Cbc_updateDec( (Crypto_83_sw_ConstR uint8*)&ptCipher[u4_Cnt], (uint8*)&ptPlain[u4_Cnt], (uint8)CRYPTO_83_SW_SWSHE_BLOCK_SIZE, &st_Ctx );
            if( u1_CplRet != CRYPTO_83_SW_AES128_OK )
            {
                break;
            }
        }
    }
    Crypto_83_sw_AES128_Cbc_finish( &st_Ctx );
    if( u1_CplRet == CRYPTO_83_SW_AES128_OK )
    {
        u1_Ret = (Std_ReturnType)E_OK;
    }

    return u1_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_AES128_CMac                           */
/* Description   | CMAC Generate                                            */
/* Preconditions | -                                                        */
/* Parameters    | (in)  ptKey    : Keydata start address(16byte)           */
/*               | (in)  ptInput  : Message data start address              */
/*               | (in)  u4Length : Message data length (bit)               */
/*               | (out) ptOutput : MAC start address(16byte)               */
/* Return Value  | Error Code                                               */
/*               |  E_OK                                                    */
/*               |  CSM_AB_E_SHE_GENERAL_ERROR                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_AES128_CMac
(
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_VAR_NO_INIT) ptKey,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptInput,
    uint32 u4Length,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptOutput
)
{
    P2VAR(Crypto_83_sw_AES128_CMac_CtxBufType, AUTOMATIC, CRYPTO_83_sw_VAR_NO_INIT) pt_Ctx = NULL_PTR;
    uint32                                 u4_BlkNum;
    uint32                                 u4_ProcCnt;
    uint8                                  u1_CacheHit;
    uint8                                  u1_LastBlockLength;
    uint8                                  u1_CplRet = CRYPTO_83_SW_AES128_OK;
    Std_ReturnType                         u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_GENERAL_ERROR;

    if( u4Length == (uint32)0x00U )
    {
        u4_BlkNum = CRYPTO_83_SW_SWSHE_CMAC_ONE_BLOCK;
    }
    else if( u4Length < CRYPTO_83_SW_SWSHE_CMAC_MAXLENGTH )
    {
        u4_BlkNum = ( u4Length + CRYPTO_83_SW_SWSHE_CMAC_BLOCK_ADDR ) >> CRYPTO_83_SW_SWSHE_CMAC_LEN_TO_BLOCK_SHIFT;
    }
    else
    {
        u4_BlkNum = CRYPTO_83_SW_SWSHE_CMAC_MAXBLOCK;
    }


    u1_CacheHit = Crypto_83_sw_SWSHE_GetCmacCache( ptKey, &pt_Ctx );

    if( u1_CacheHit == CRYPTO_83_SW_SWSHE_KEY_CACHE_MISS )
    {
        u1_CplRet = Crypto_83_sw_AES128_CMac_start( (Crypto_83_sw_ConstR uint8*)ptKey, (uint8)CRYPTO_83_SW_SWSHE_KEY_SIZE, pt_Ctx );
        if( u1_CplRet == CRYPTO_83_SW_AES128_OK )
        {
            /* AES128 CMAC mode SubKey generate */
            u1_CplRet = Crypto_83_sw_AES128_CMac_updSubkey( pt_Ctx );
        }
    }

    /* AES128 CMAC mode initialization */
    if( u1_CplRet == CRYPTO_83_SW_AES128_OK )
    {
        u4_ProcCnt = (uint32)0U;
        while( u4_BlkNum > CRYPTO_83_SW_SWSHE_IF_U4_ZERO )
        {
            if( u4_BlkNum > CRYPTO_83_SW_SWSHE_CMAC_ONE_BLOCK )
            {
                /* AES128 CMAC mode generate MAC */
                u1_CplRet = Crypto_83_sw_AES128_CMac_update( (Crypto_83_sw_ConstR uint8*)&ptInput[u4_ProcCnt], (uint8*)ptOutput, (uint8)CRYPTO_83_SW_SWSHE_BLOCK_SIZE, CRYPTO_83_SW_AES128_OTHER_BLOCK, pt_Ctx );
                u4_ProcCnt += (uint32)CRYPTO_83_SW_SWSHE_BLOCK_SIZE;
            }
            else
            {
                u1_LastBlockLength = (uint8)(u4Length - u4_ProcCnt);
                u1_CplRet = Crypto_83_sw_AES128_CMac_update( (Crypto_83_sw_ConstR uint8*)&ptInput[u4_ProcCnt], (uint8*)ptOutput, (uint8)u1_LastBlockLength, CRYPTO_83_SW_AES128_LAST_BLOCK, pt_Ctx );
            }
            if( u1_CplRet == CRYPTO_83_SW_AES128_NOT_OK )
            {
                break;
            }
            u4_BlkNum --;
        }
    }
    pt_Ctx->unVectorData.u4CryptBufUint32[CRYPTO_83_SW_SWSHE_CTX_CRYBUF_1BYTE] = CRYPTO_83_SW_SWSHE_IF_U4_ZERO;
    pt_Ctx->unVectorData.u4CryptBufUint32[CRYPTO_83_SW_SWSHE_CTX_CRYBUF_2BYTE] = CRYPTO_83_SW_SWSHE_IF_U4_ZERO;
    pt_Ctx->unVectorData.u4CryptBufUint32[CRYPTO_83_SW_SWSHE_CTX_CRYBUF_3BYTE] = CRYPTO_83_SW_SWSHE_IF_U4_ZERO;
    pt_Ctx->unVectorData.u4CryptBufUint32[CRYPTO_83_SW_SWSHE_CTX_CRYBUF_4BYTE] = CRYPTO_83_SW_SWSHE_IF_U4_ZERO;
    if ( u1_CplRet == CRYPTO_83_SW_AES128_OK )
    {
        u1_Ret = (Std_ReturnType)E_OK;
    }

    return u1_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_InitRandom                            */
/* Description   | Random number generator initialization                   */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | Error Code                                               */
/*               |  E_OK                                                    */
/*               |  CSM_AB_E_SHE_GENERAL_ERROR                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_InitRandom
(
    void
)
{
    uint8                        u1_ZeroSeed[CRYPTO_83_SW_SWSHE_SEED_SIZE];
    uint8                        u1_Count;
    uint8                        u1_CplRet;
    Std_ReturnType               u1_Ret = (Std_ReturnType)E_OK;

    for( u1_Count = (uint8)0x00U; u1_Count < (uint8)CRYPTO_83_SW_SWSHE_SEED_SIZE; u1_Count++ )
    {
        u1_ZeroSeed[u1_Count] = (uint8)0x00U;
    }

    u1_CplRet = Crypto_83_sw_AES128_RandomGen_start( (Crypto_83_sw_ConstR uint8*)&u1_ZeroSeed[0], (uint8)CRYPTO_83_SW_SWSHE_SEED_SIZE, &Crypto_83_sw_Swshe_stCtxRnd );
    if( u1_CplRet != CRYPTO_83_SW_AES128_OK )
    {
        u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_GENERAL_ERROR;
    }

    return u1_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_ReseedRandom                          */
/* Description   | Random number seed setting                               */
/* Preconditions | -                                                        */
/* Parameters    | (in/out) ptSeed : Seed start address(16byte)             */
/* Return Value  | Error Code                                               */
/*               |  E_OK                                                    */
/*               |  CSM_AB_E_SHE_GENERAL_ERROR                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_ReseedRandom
(
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptSeed
)
{
    uint8                        u1_CplRet;
    Std_ReturnType               u1_Ret = (Std_ReturnType)E_OK;

    u1_CplRet = Crypto_83_sw_AES128_RandomGen_restart( (Crypto_83_sw_ConstR uint8*)ptSeed, (uint8)CRYPTO_83_SW_SWSHE_SEED_SIZE, &Crypto_83_sw_Swshe_stCtxRnd );
    if( u1_CplRet != CRYPTO_83_SW_AES128_OK )
    {
        u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_GENERAL_ERROR;
    }

    return u1_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_GenerateRandom                        */
/* Description   | Random number generation                                 */
/* Preconditions | -                                                        */
/* Parameters    | (out) ptRnd : Random number start address(16byte)        */
/* Return Value  | Error Code                                               */
/*               |  E_OK                                                    */
/*               |  CSM_AB_E_SHE_GENERAL_ERROR                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_GenerateRandom
(
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptRnd
)
{
    uint8                        u1_CplRet;
    Std_ReturnType               u1_Ret = (Std_ReturnType)E_OK;

    u1_CplRet = Crypto_83_sw_AES128_RandomGen_update( (uint8*)ptRnd, &Crypto_83_sw_Swshe_stCtxRnd );
    if( u1_CplRet != CRYPTO_83_SW_AES128_OK )
    {
        u1_Ret = (Std_ReturnType)CSM_AB_E_SHE_GENERAL_ERROR;
    }

    return u1_Ret;
}

#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_IfCryptoGetErrorStatus                */
/* Description   | Check ram                                                */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | Error Code                                               */
/*               |  E_OK                                                    */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_IfCryptoGetErrorStatus
(
    void
)
{
    Crypto_83_sw_Swshe_stKeyCache.u2Expire++;
    if ( Crypto_83_sw_Swshe_stKeyCache.u2Expire > CRYPTO_83_SW_SWSHE_KEY_CACHE_EXPIRE )
    {
        Crypto_83_sw_Swshe_stKeyCache.u2Expire = CRYPTO_83_SW_SWSHE_KEY_CACHE_EXPIRE;
    }

    return (Std_ReturnType)E_OK;
}
#endif

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Crypto_83_sw_SWSHE_GetCmacCache                          */
/* Description   | CMAC key cache search                                    */
/* Preconditions | -                                                        */
/* Parameters    | ptKey :                                                  */
/*               | ptCtx :                                                  */
/* Return Value  | Error Code                                               */
/*               |  E_OK                                                    */
/*               |  CSM_AB_E_SHE_GENERAL_ERROR                              */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(uint8, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_GetCmacCache
(
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_VAR_NO_INIT) ptKey,
    P2VAR(Crypto_83_sw_AES128_CMac_CtxBufType*, AUTOMATIC, AUTOMATIC) ptCtx
)
{
    sint32  s4_CmpRet;
    uint8   u1_CacheHit = CRYPTO_83_SW_SWSHE_KEY_CACHE_MISS;

    /* 0 an initial slot */
    *ptCtx = &Crypto_83_sw_Swshe_stKeyCache.stCtxCmac;

    /* Only in the case of CMAC use, Compare the key */
#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
    if( ( Crypto_83_sw_Swshe_stKeyCache.u2Expire < CRYPTO_83_SW_SWSHE_KEY_CACHE_EXPIRE ) && 
    ( Crypto_83_sw_Swshe_stKeyCache.stCtxCmac.u1SubKeyState == CRYPTO_83_SW_AES128_SUBKEY_COMPLETE ) )
#else
    if( Crypto_83_sw_Swshe_stKeyCache.stCtxCmac.u1SubKeyState == CRYPTO_83_SW_AES128_SUBKEY_COMPLETE )
#endif
    {
        s4_CmpRet = Crypto_83_sw_SecStd_MemCmp( &ptKey[0], &Crypto_83_sw_Swshe_stKeyCache.stCtxCmac.stEcbCtxBuf.unRoundKey[0U], (uint32)CRYPTO_83_SW_SWSHE_KEY_SIZE );
        if( s4_CmpRet == (sint32)CRYPTO_83_SW_SWSHE_MEMCMP_OK )
        {
            /* Cache hit */
            u1_CacheHit = CRYPTO_83_SW_SWSHE_KEY_CACHE_HIT;
        }

    }

#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
    if ( u1_CacheHit == CRYPTO_83_SW_SWSHE_KEY_CACHE_MISS )
    {
        Crypto_83_sw_Swshe_stKeyCache.u2Expire = CRYPTO_83_SW_SWSHE_IF_U2_ZERO;
    }
#endif
    return u1_CacheHit;
}

#define CRYPTO_83_sw_STOP_SEC_CODE
#include <Crypto_83_sw_MemMap.h>


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2023/01/17                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
