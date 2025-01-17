/* Crypto_83_sw_If_SWSHE_c_v2-0-0                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Crypto_83_sw/If_SWSHE/CODE                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Crypto_83_sw.h>
#include "../inc/Crypto_83_sw_Internal.h"
#include "../../SWSHE/inc/Crypto_83_sw_SWSHE.h"
#include "../../SWSHE/inc/Crypto_83_sw_SWSHE_cache.h"
#include "../../SWSHE/inc/Crypto_83_sw_SWSHE_ifcache.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/* SHE Key Position */
#define CRYPTO_83_SW_IF_KID_POS                     ((uint8)0U)
#define CRYPTO_83_SW_IF_FID_WP_POS                  ((uint8)1U)
#define CRYPTO_83_SW_IF_FID_BP_POS                  ((uint8)2U)
#define CRYPTO_83_SW_IF_FID_DP_POS                  ((uint8)3U)
#define CRYPTO_83_SW_IF_FID_KU_POS                  ((uint8)4U)
#define CRYPTO_83_SW_IF_FID_WC_POS                  ((uint8)5U)
#define CRYPTO_83_SW_IF_FID_PL_POS                  ((uint8)6U)
#define CRYPTO_83_SW_IF_FID_RSV_POS                 ((uint8)7U)
#define CRYPTO_83_SW_IF_CID_1BYTE_POS               ((uint8)8U)
#define CRYPTO_83_SW_IF_CID_2BYTE_POS               ((uint8)9U)
#define CRYPTO_83_SW_IF_CID_3BYTE_POS               ((uint8)10U)
#define CRYPTO_83_SW_IF_CID_4BYTE_POS               ((uint8)11U)
#define CRYPTO_83_SW_IF_RSV_1BYTE_POS               ((uint8)12U)
#define CRYPTO_83_SW_IF_RSV_2BYTE_POS               ((uint8)13U)
#define CRYPTO_83_SW_IF_RSV_3BYTE_POS               ((uint8)14U)
#define CRYPTO_83_SW_IF_RSV_4BYTE_POS               ((uint8)15U)
#define CRYPTO_83_SW_IF_KEYINFO_DATA_POS            ((uint8)16U)

/* Data Parameter */
#define CRYPTO_83_SW_IF_START_ADDRESS_CALC          ((uint32)16UL)
#define CRYPTO_83_SW_IF_CBC_LAST_BLOCK_ADDRESS      ((uint32)16UL)
#define CRYPTO_83_SW_IF_MAC_VERLEN_CONV             ((uint32)0x0000007FUL)
#define CRYPTO_83_SW_IF_FRACTION_RNDUP              ((uint32)7UL)
#define CRYPTO_83_SW_IF_RND_ZERO                    ((uint8)0x00U)
#define CRYPTO_83_SW_IF_RND_FF                      ((uint8)0xFFU)

/* Size Parameter */
#define CRYPTO_83_SW_IF_MAC_SIZE                    ((uint32)16UL)
#define CRYPTO_83_SW_IF_MAC_MESSAGE_SIZE_MAX        ((uint32)536870896UL)
#define CRYPTO_83_SW_IF_MAC_VERIFY_SIZE_MAX         ((uint32)128UL)
#define CRYPTO_83_SW_IF_RND_SIZE_MAX                ((uint8)16U)
#define CRYPTO_83_SW_IF_KEY_SIZE                    ((uint32)16UL)

/* Mask Parameter */
#define CRYPTO_83_SW_IF_4BIT_MASK                   ((uint32)0x0FUL)
#define CRYPTO_83_SW_IF_8BIT_MASK                   ((uint8)0xFFU)

/* Shift Parameter */
#define CRYPTO_83_SW_IF_4BIT_SHIFT                  ((uint32)4UL)

/* InitialVector Status */
#define CRYPTO_83_SW_S_IV_EMPTY                     ((Crypto_83_sw_IvStoredStatusType)0xF0U)
#define CRYPTO_83_SW_S_IV_STORED                    ((Crypto_83_sw_IvStoredStatusType)0xE1U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef uint8   Crypto_83_sw_IvStoredStatusType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define CRYPTO_83_sw_START_SEC_CODE
#include <Crypto_83_sw_MemMap.h>

static FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_CheckSwsheValidStatus
(
    uint32 u4CryptoKeyId
);

#define CRYPTO_83_sw_STOP_SEC_CODE
#include <Crypto_83_sw_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define CRYPTO_83_sw_START_SEC_VAR_NO_INIT
#include <Crypto_83_sw_MemMap.h>

static VAR(Crypto_83_sw_KeyValidStatusType, CRYPTO_83_sw_VAR_NO_INIT)   Crypto_83_sw_If_udSheKeyValidStatus[CRYPTO_83_SW_SHEKEY_NUM];
static VAR(Crypto_83_sw_IvStoredStatusType, CRYPTO_83_sw_VAR_NO_INIT)   Crypto_83_sw_If_udEncIvStoredStatus;
static VAR(Crypto_83_sw_IvStoredStatusType, CRYPTO_83_sw_VAR_NO_INIT)   Crypto_83_sw_If_udDecIvStoredStatus;
static VAR(uint8, CRYPTO_83_sw_VAR_NO_INIT)                             Crypto_83_sw_If_u1KeyElementEncIvData[CRYPTO_83_SW_INITVECTOR_SIZE];
static VAR(uint8, CRYPTO_83_sw_VAR_NO_INIT)                             Crypto_83_sw_If_u1KeyElementDecIvData[CRYPTO_83_SW_INITVECTOR_SIZE];
static VAR(uint8, CRYPTO_83_sw_VAR_NO_INIT)                             Crypto_83_sw_If_u1KeyElementProofData[CRYPTO_83_SW_M4M5_SIZE];

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
/* Function Name | Crypto_83_sw_If_SwsheInit                                */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, CRYPTO_83_sw_CODE) Crypto_83_sw_If_SwsheInit
(
    void
)
{
    uint32  u4_SheKeyIdNum;
    uint32  u4_CacheNum;
    uint8   u1_Cache[CRYPTO_83_SW_KEYCACHE_SIZE];

    Crypto_83_sw_SWSHE_Init();

    (void)Crypto_83_sw_SWSHE_CmdInitRng(); /* no return check required */

    (void)Crypto_83_sw_SecStd_MemSet( (void*)&u1_Cache[0],
                                      (uint8)0U,
                                      CRYPTO_83_SW_KEYCACHE_SIZE );  /* no return check required */

    for( u4_CacheNum = (uint32)0UL; u4_CacheNum < CRYPTO_83_SW_KEYID_RAM_KEY; u4_CacheNum++ )
    {
        (void)Crypto_83_sw_SWSHE_CacheUpdateKeyInfo((uint8)u4_CacheNum, (const uint8*)&u1_Cache[0]); /* no return check required */
    }

    (void)Crypto_83_sw_SecStd_MemSet( (void*)&Crypto_83_sw_If_u1KeyElementProofData[0],
                                      (uint8)0U,
                                      CRYPTO_83_SW_M4M5_SIZE );  /* no return check required */

    (void)Crypto_83_sw_SecStd_MemSet( (void*)&Crypto_83_sw_If_u1KeyElementEncIvData[0],
                                      (uint8)0U,
                                      CRYPTO_83_SW_INITVECTOR_SIZE ); /* no return check required */

    (void)Crypto_83_sw_SecStd_MemSet( (void*)&Crypto_83_sw_If_u1KeyElementDecIvData[0],
                                      (uint8)0U,
                                      CRYPTO_83_SW_INITVECTOR_SIZE ); /* no return check required */

    Crypto_83_sw_If_udEncIvStoredStatus = CRYPTO_83_SW_S_IV_EMPTY;
    Crypto_83_sw_If_udDecIvStoredStatus = CRYPTO_83_SW_S_IV_EMPTY;

    for( u4_SheKeyIdNum = (uint32)0UL; u4_SheKeyIdNum < CRYPTO_83_SW_SHEKEY_NUM; u4_SheKeyIdNum++ )
    {
        Crypto_83_sw_If_udSheKeyValidStatus[u4_SheKeyIdNum] = CRYPTO_83_SW_S_KEY_INVALID;
    }

    return;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_MacGen                                      */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | ptJob :                                                  */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                        :                           */
/*               |  E_NOT_OK                    :                           */
/*               |  CRYPTO_E_BUSY               :                           */
/*               |  CRYPTO_E_KEY_NOT_VALID      :                           */
/*               |  CRYPTO_E_KEY_EMPTY          :                           */
/*               |  CSM_AB_E_SHE_KEY_INVALID    :                           */
/*               |  CSM_AB_E_SHE_MEMORY_FAILURE :                           */
/*               |  CSM_AB_E_SHE_GENERAL_ERROR  :                           */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_MacGen
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
)
{
    Std_ReturnType  ud_Ret;
    uint32          u4_InputLength;
    uint8           u1_Mac[CRYPTO_83_SW_IF_MAC_SIZE];

    ud_Ret = Crypto_83_sw_CheckSwsheValidStatus( ptJob->cryptoKeyId );

    if( ud_Ret == (Std_ReturnType)E_OK )
    {
        if( (ptJob->jobPrimitiveInputOutput.inputPtr == NULL_PTR)
         || (ptJob->jobPrimitiveInputOutput.outputPtr == NULL_PTR)
         || (ptJob->jobPrimitiveInputOutput.outputLengthPtr == NULL_PTR)
         || (ptJob->jobPrimitiveInputOutput.inputLength == (uint32)0UL)
         || (*(ptJob->jobPrimitiveInputOutput.outputLengthPtr) == (uint32)0UL)
         || (ptJob->jobPrimitiveInputOutput.inputLength > CRYPTO_83_SW_IF_MAC_MESSAGE_SIZE_MAX) )
        {
            ud_Ret = (Std_ReturnType)E_NOT_OK;
        }

        if( ud_Ret == (Std_ReturnType)E_OK )
        {
            u4_InputLength = ptJob->jobPrimitiveInputOutput.inputLength << CRYPTO_83_SW_BYTE_TO_BIT_CONV;

            ud_Ret = Crypto_83_sw_SWSHE_CmdGenerateMac( (uint8)ptJob->cryptoKeyId,
                                                        u4_InputLength,
                                                        ptJob->jobPrimitiveInputOutput.inputPtr,
                                                        &u1_Mac[0] );

            if( ud_Ret == (Std_ReturnType)E_OK )
            {
                if( *(ptJob->jobPrimitiveInputOutput.outputLengthPtr) > CRYPTO_83_SW_IF_MAC_SIZE )
                {
                    *(ptJob->jobPrimitiveInputOutput.outputLengthPtr) = CRYPTO_83_SW_IF_MAC_SIZE;
                }
                
                (void)Crypto_83_sw_SecStd_MemCpy( (void*)(ptJob->jobPrimitiveInputOutput.outputPtr),
                                                  (void*)&u1_Mac[0],
                                                  *(ptJob->jobPrimitiveInputOutput.outputLengthPtr) );   /* no return check required */
            }
        }
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_MacVer                                      */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | ptJob :                                                  */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                        :                           */
/*               |  E_NOT_OK                    :                           */
/*               |  CRYPTO_E_BUSY               :                           */
/*               |  CRYPTO_E_KEY_NOT_VALID      :                           */
/*               |  CRYPTO_E_KEY_EMPTY          :                           */
/*               |  CSM_AB_E_SHE_KEY_INVALID    :                           */
/*               |  CSM_AB_E_SHE_MEMORY_FAILURE :                           */
/*               |  CSM_AB_E_SHE_GENERAL_ERROR  :                           */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_MacVer
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
)
{
    Std_ReturnType  ud_Ret;
    uint32          u4_InputLength;
    uint32          u4_SecondaryInputLengthByte;
    uint8           u1_SecondaryInputLengthBit;
    uint8           u1_VerifyResult = CRYPTO_83_SW_SWSHE_CMAC_VER_NG;
    uint8           u1_Mac[CRYPTO_83_SW_IF_MAC_SIZE];

    ud_Ret = Crypto_83_sw_CheckSwsheValidStatus( ptJob->cryptoKeyId );

    if( ud_Ret == (Std_ReturnType)E_OK )
    {
        if( (ptJob->jobPrimitiveInputOutput.inputPtr == NULL_PTR)
         || (ptJob->jobPrimitiveInputOutput.secondaryInputPtr == NULL_PTR)
         || (ptJob->jobPrimitiveInputOutput.inputLength == (uint32)0UL)
         || (ptJob->jobPrimitiveInputOutput.inputLength > CRYPTO_83_SW_IF_MAC_MESSAGE_SIZE_MAX)
         || (ptJob->jobPrimitiveInputOutput.secondaryInputLength == (uint32)0UL)
         || (ptJob->jobPrimitiveInputOutput.secondaryInputLength > CRYPTO_83_SW_IF_MAC_VERIFY_SIZE_MAX)
         || (ptJob->jobPrimitiveInputOutput.verifyPtr == NULL_PTR) )
        {
            ud_Ret = (Std_ReturnType)E_NOT_OK;
        }

        if( ud_Ret == (Std_ReturnType)E_OK )
        {
            u4_InputLength = ptJob->jobPrimitiveInputOutput.inputLength << CRYPTO_83_SW_BYTE_TO_BIT_CONV;

            u1_SecondaryInputLengthBit = (uint8)(CRYPTO_83_SW_IF_MAC_VERLEN_CONV & ptJob->jobPrimitiveInputOutput.secondaryInputLength);
            u4_SecondaryInputLengthByte = ptJob->jobPrimitiveInputOutput.secondaryInputLength + CRYPTO_83_SW_IF_FRACTION_RNDUP;
            u4_SecondaryInputLengthByte = u4_SecondaryInputLengthByte >> CRYPTO_83_SW_BIT_TO_BYTE_CONV;

            (void)Crypto_83_sw_SecStd_MemCpy( (void*)&u1_Mac[0],
                                              (const void*)(ptJob->jobPrimitiveInputOutput.secondaryInputPtr),
                                              u4_SecondaryInputLengthByte );   /* no return check required */

            ud_Ret = Crypto_83_sw_SWSHE_CmdVerifyMac( (uint8)ptJob->cryptoKeyId,
                                                      u4_InputLength,
                                                      ptJob->jobPrimitiveInputOutput.inputPtr,
                                                      u1_SecondaryInputLengthBit,
                                                      &u1_Mac[0],
                                                      &u1_VerifyResult );

            if( ud_Ret == (Std_ReturnType)E_OK )
            {
                if( u1_VerifyResult == (uint8)CRYPTO_83_SW_SWSHE_CMAC_VER_OK )
                {
                    *(ptJob->jobPrimitiveInputOutput.verifyPtr) = CRYPTO_E_VER_OK;
                }
                else
                {
                    *(ptJob->jobPrimitiveInputOutput.verifyPtr) = CRYPTO_E_VER_NOT_OK;
                }
            }
        }
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_EcbDecStart                                 */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | ptJob :                                                  */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                   :                                */
/*               |  E_NOT_OK               :                                */
/*               |  CRYPTO_E_KEY_NOT_VALID :                                */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_EcbDecStart
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
)
{
    Std_ReturnType  ud_Ret;

    ud_Ret = Crypto_83_sw_CheckSwsheValidStatus( ptJob->cryptoKeyId );

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_EcbDecUpdate                                */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | ptJob :                                                  */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                        :                           */
/*               |  E_NOT_OK                    :                           */
/*               |  CRYPTO_E_BUSY               :                           */
/*               |  CRYPTO_E_KEY_NOT_VALID      :                           */
/*               |  CRYPTO_E_KEY_EMPTY          :                           */
/*               |  CSM_AB_E_SHE_KEY_INVALID    :                           */
/*               |  CSM_AB_E_SHE_MEMORY_FAILURE :                           */
/*               |  CSM_AB_E_SHE_GENERAL_ERROR  :                           */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_EcbDecUpdate
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
)
{
    Std_ReturnType  ud_Ret;
    uint32          u4_LoopMax;
    uint32          u4_Loop;
    uint32          u4_Index;

    ud_Ret = Crypto_83_sw_CheckSwsheValidStatus( ptJob->cryptoKeyId );

    if( ud_Ret == (Std_ReturnType)E_OK )
    {
        if( (ptJob->jobPrimitiveInputOutput.inputPtr == NULL_PTR)
         || (ptJob->jobPrimitiveInputOutput.outputPtr == NULL_PTR)
         || (ptJob->jobPrimitiveInputOutput.outputLengthPtr == NULL_PTR)
         || (ptJob->jobPrimitiveInputOutput.inputLength == (uint32)0UL)
         || (*(ptJob->jobPrimitiveInputOutput.outputLengthPtr) == (uint32)0UL)
         || (ptJob->jobPrimitiveInputOutput.inputLength > *(ptJob->jobPrimitiveInputOutput.outputLengthPtr))
         || ((ptJob->jobPrimitiveInputOutput.inputLength & CRYPTO_83_SW_IF_4BIT_MASK) != (uint32)0UL) )
        {
            ud_Ret = (Std_ReturnType)E_NOT_OK;
        }
        
        if( ud_Ret == (Std_ReturnType)E_OK )
        {
            u4_LoopMax = ptJob->jobPrimitiveInputOutput.inputLength >> CRYPTO_83_SW_IF_4BIT_SHIFT;
            u4_Index = (uint32)0UL;

            for( u4_Loop = (uint32)0UL; u4_Loop < u4_LoopMax; u4_Loop++ )
            {
                ud_Ret = Crypto_83_sw_SWSHE_CmdDecEcb( (uint8)ptJob->cryptoKeyId,
                                                       &(ptJob->jobPrimitiveInputOutput.inputPtr[u4_Index]),
                                                       &(ptJob->jobPrimitiveInputOutput.outputPtr[u4_Index]) );

                if( ud_Ret != (Std_ReturnType)E_OK )
                {
                    break;
                }

                u4_Index += CRYPTO_83_SW_IF_START_ADDRESS_CALC;
            }

            if( ud_Ret == (Std_ReturnType)E_OK )
            {
                *(ptJob->jobPrimitiveInputOutput.outputLengthPtr) = ptJob->jobPrimitiveInputOutput.inputLength;
            }
        }
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_EcbDecFinish                                */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | ptJob :                                                  */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                        :                           */
/*               |  E_NOT_OK                    :                           */
/*               |  CRYPTO_E_BUSY               :                           */
/*               |  CRYPTO_E_KEY_NOT_VALID      :                           */
/*               |  CRYPTO_E_KEY_EMPTY          :                           */
/*               |  CSM_AB_E_SHE_KEY_INVALID    :                           */
/*               |  CSM_AB_E_SHE_MEMORY_FAILURE :                           */
/*               |  CSM_AB_E_SHE_GENERAL_ERROR  :                           */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_EcbDecFinish
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
)
{
    Std_ReturnType ud_Ret;

    ud_Ret = Crypto_83_sw_CheckSwsheValidStatus( ptJob->cryptoKeyId );

    if( ud_Ret == (Std_ReturnType)E_OK )
    {
        if( (ptJob->jobPrimitiveInputOutput.inputPtr != NULL_PTR)
         || (ptJob->jobPrimitiveInputOutput.inputLength != (uint32)0UL)
         || (ptJob->jobPrimitiveInputOutput.outputPtr != NULL_PTR)
         || (ptJob->jobPrimitiveInputOutput.outputLengthPtr != NULL_PTR) )
        {
            if( ( ptJob->jobPrimitiveInputOutput.mode & CRYPTO_OPERATIONMODE_UPDATE ) != CRYPTO_OPERATIONMODE_UPDATE )
            {
                ud_Ret = Crypto_83_sw_EcbDecUpdate( ptJob );
            }
        }
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_EcbEnc                                      */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | ptJob :                                                  */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                        :                           */
/*               |  E_NOT_OK                    :                           */
/*               |  CRYPTO_E_BUSY               :                           */
/*               |  CRYPTO_E_KEY_NOT_VALID      :                           */
/*               |  CRYPTO_E_KEY_EMPTY          :                           */
/*               |  CSM_AB_E_SHE_KEY_INVALID    :                           */
/*               |  CSM_AB_E_SHE_MEMORY_FAILURE :                           */
/*               |  CSM_AB_E_SHE_GENERAL_ERROR  :                           */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_EcbEnc
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
)
{
    Std_ReturnType  ud_Ret;
    uint32          u4_LoopMax;
    uint32          u4_Loop;
    uint32          u4_Index;

    ud_Ret = Crypto_83_sw_CheckSwsheValidStatus( ptJob->cryptoKeyId );

    if( ud_Ret == (Std_ReturnType)E_OK )
    {
        if( (ptJob->jobPrimitiveInputOutput.inputPtr == NULL_PTR)
         || (ptJob->jobPrimitiveInputOutput.outputPtr == NULL_PTR)
         || (ptJob->jobPrimitiveInputOutput.outputLengthPtr == NULL_PTR)
         || (ptJob->jobPrimitiveInputOutput.inputLength == (uint32)0UL)
         || (*(ptJob->jobPrimitiveInputOutput.outputLengthPtr) == (uint32)0UL)
         || (ptJob->jobPrimitiveInputOutput.inputLength > *(ptJob->jobPrimitiveInputOutput.outputLengthPtr))
         || ((ptJob->jobPrimitiveInputOutput.inputLength & CRYPTO_83_SW_IF_4BIT_MASK) != (uint32)0UL) )
        {
            ud_Ret = (Std_ReturnType)E_NOT_OK;
        }

        if( ud_Ret == (Std_ReturnType)E_OK )
        {
            u4_LoopMax = ptJob->jobPrimitiveInputOutput.inputLength >> CRYPTO_83_SW_IF_4BIT_SHIFT;
            u4_Index = (uint32)0UL;

            for( u4_Loop = 0UL; u4_Loop < u4_LoopMax; u4_Loop++ )
            {
                ud_Ret = Crypto_83_sw_SWSHE_CmdEncEcb( (uint8)ptJob->cryptoKeyId,
                                                       &(ptJob->jobPrimitiveInputOutput.inputPtr[u4_Index]),
                                                       &(ptJob->jobPrimitiveInputOutput.outputPtr[u4_Index]) );

                if( ud_Ret != (Std_ReturnType)E_OK )
                {
                    break;
                }

                u4_Index += CRYPTO_83_SW_IF_START_ADDRESS_CALC;
            }

            if( ud_Ret == (Std_ReturnType)E_OK )
            {
                *(ptJob->jobPrimitiveInputOutput.outputLengthPtr) = ptJob->jobPrimitiveInputOutput.inputLength;
            }
        }
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_CbcDecStart                                 */
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
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_CbcDecStart
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
)
{
    Std_ReturnType  ud_Ret;

    ud_Ret = Crypto_83_sw_CheckSwsheValidStatus( ptJob->cryptoKeyId );

    if( ud_Ret == (Std_ReturnType)E_OK )
    {
        if( Crypto_83_sw_If_udDecIvStoredStatus != CRYPTO_83_SW_S_IV_STORED )
        {
            ud_Ret = (Std_ReturnType)CRYPTO_E_KEY_EMPTY;
        }
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_CbcDecUpdate                                */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | ptJob :                                                  */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                        :                           */
/*               |  E_NOT_OK                    :                           */
/*               |  CRYPTO_E_BUSY               :                           */
/*               |  CRYPTO_E_KEY_NOT_VALID      :                           */
/*               |  CRYPTO_E_KEY_EMPTY          :                           */
/*               |  CSM_AB_E_SHE_KEY_INVALID    :                           */
/*               |  CSM_AB_E_SHE_MEMORY_FAILURE :                           */
/*               |  CSM_AB_E_SHE_GENERAL_ERROR  :                           */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_CbcDecUpdate
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
)
{
    Std_ReturnType  ud_Ret;
    uint32          u4_InputBlock;
    uint32          u4_LastBlock;

    ud_Ret = Crypto_83_sw_CheckSwsheValidStatus( ptJob->cryptoKeyId );

    if( ud_Ret == (Std_ReturnType)E_OK )
    {
        if( ( ptJob->jobPrimitiveInputOutput.inputPtr == NULL_PTR )
         || ( ptJob->jobPrimitiveInputOutput.outputPtr == NULL_PTR )
         || ( ptJob->jobPrimitiveInputOutput.outputLengthPtr == NULL_PTR )
         || ( ptJob->jobPrimitiveInputOutput.inputLength == (uint32)0UL )
         || ( *ptJob->jobPrimitiveInputOutput.outputLengthPtr == (uint32)0UL )
         || ( ptJob->jobPrimitiveInputOutput.inputLength > *ptJob->jobPrimitiveInputOutput.outputLengthPtr )
         || (( ptJob->jobPrimitiveInputOutput.inputLength & CRYPTO_83_SW_IF_4BIT_MASK ) != (uint32)0UL ) )
        {
            ud_Ret = (Std_ReturnType)E_NOT_OK;
        }

        if( ud_Ret == (Std_ReturnType)E_OK )
        {
            u4_InputBlock = (uint32)( ptJob->jobPrimitiveInputOutput.inputLength >> CRYPTO_83_SW_IF_4BIT_SHIFT );

            ud_Ret = Crypto_83_sw_SWSHE_CmdDecCbc( (uint8)ptJob->cryptoKeyId,
                                                   (Crypto_83_sw_ConstR uint8*)&Crypto_83_sw_If_u1KeyElementDecIvData[0],
                                                   u4_InputBlock,
                                                   (Crypto_83_sw_ConstR uint8*)(ptJob->jobPrimitiveInputOutput.inputPtr),
                                                   ptJob->jobPrimitiveInputOutput.outputPtr );

            if( ud_Ret == (Std_ReturnType)E_OK )
            {
                *(ptJob->jobPrimitiveInputOutput.outputLengthPtr) = ptJob->jobPrimitiveInputOutput.inputLength;

                u4_LastBlock = ptJob->jobPrimitiveInputOutput.inputLength - CRYPTO_83_SW_IF_CBC_LAST_BLOCK_ADDRESS;

                (void)Crypto_83_sw_SecStd_MemCpy( (void*)&Crypto_83_sw_If_u1KeyElementDecIvData[0],
                                                  (const void*)&(ptJob->jobPrimitiveInputOutput.inputPtr[u4_LastBlock]),
                                                  CRYPTO_83_SW_INITVECTOR_SIZE ); /* no return check required */
            }
        }
    }

    if( ud_Ret != (Std_ReturnType)E_OK )
    {
        (void)Crypto_83_sw_SecStd_MemSet( (void*)&Crypto_83_sw_If_u1KeyElementDecIvData[0],
                                          (uint8)0U,
                                          CRYPTO_83_SW_INITVECTOR_SIZE ); /* no return check required */
        Crypto_83_sw_If_udDecIvStoredStatus = CRYPTO_83_SW_S_IV_EMPTY;
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_CbcDecFinish                                */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | ptJob :                                                  */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                        :                           */
/*               |  E_NOT_OK                    :                           */
/*               |  CRYPTO_E_BUSY               :                           */
/*               |  CRYPTO_E_KEY_NOT_VALID      :                           */
/*               |  CRYPTO_E_KEY_EMPTY          :                           */
/*               |  CSM_AB_E_SHE_KEY_INVALID    :                           */
/*               |  CSM_AB_E_SHE_MEMORY_FAILURE :                           */
/*               |  CSM_AB_E_SHE_GENERAL_ERROR  :                           */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_CbcDecFinish
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
)
{
    Std_ReturnType  ud_Ret;

    ud_Ret = Crypto_83_sw_CheckSwsheValidStatus( ptJob->cryptoKeyId );

    if( ud_Ret == (Std_ReturnType)E_OK )
    {
        if( ( ptJob->jobPrimitiveInputOutput.inputPtr != NULL_PTR )
         || ( ptJob->jobPrimitiveInputOutput.outputPtr != NULL_PTR )
         || ( ptJob->jobPrimitiveInputOutput.outputLengthPtr != NULL_PTR )
         || ( ptJob->jobPrimitiveInputOutput.inputLength != (uint32)0UL ) )
        {
            if( ( ptJob->jobPrimitiveInputOutput.mode & CRYPTO_OPERATIONMODE_UPDATE ) != CRYPTO_OPERATIONMODE_UPDATE )
            {
                ud_Ret = Crypto_83_sw_CbcDecUpdate( ptJob );
            }
        }
    }

    (void)Crypto_83_sw_SecStd_MemSet( (void*)&Crypto_83_sw_If_u1KeyElementDecIvData[0],
                                      (uint8)0U,
                                      CRYPTO_83_SW_INITVECTOR_SIZE ); /* no return check required */
    Crypto_83_sw_If_udDecIvStoredStatus = CRYPTO_83_SW_S_IV_EMPTY;

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_CbcEnc                                      */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | ptJob :                                                  */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                        :                           */
/*               |  E_NOT_OK                    :                           */
/*               |  CRYPTO_E_BUSY               :                           */
/*               |  CRYPTO_E_KEY_NOT_VALID      :                           */
/*               |  CRYPTO_E_KEY_EMPTY          :                           */
/*               |  CSM_AB_E_SHE_KEY_INVALID    :                           */
/*               |  CSM_AB_E_SHE_MEMORY_FAILURE :                           */
/*               |  CSM_AB_E_SHE_GENERAL_ERROR  :                           */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_CbcEnc
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
)
{
    Std_ReturnType  ud_Ret;
    uint32          u4_InputBlock;

    ud_Ret = Crypto_83_sw_CheckSwsheValidStatus( ptJob->cryptoKeyId );

    if( ud_Ret == (Std_ReturnType)E_OK )
    {
        if( Crypto_83_sw_If_udEncIvStoredStatus != CRYPTO_83_SW_S_IV_STORED )
        {
            ud_Ret = (Std_ReturnType)CRYPTO_E_KEY_EMPTY;
        }
    }

    if( ud_Ret == (Std_ReturnType)E_OK )
    {
        if( ( ptJob->jobPrimitiveInputOutput.inputPtr == NULL_PTR )
         || ( ptJob->jobPrimitiveInputOutput.outputPtr == NULL_PTR )
         || ( ptJob->jobPrimitiveInputOutput.outputLengthPtr == NULL_PTR )
         || ( ptJob->jobPrimitiveInputOutput.inputLength == (uint32)0UL )
         || ( *ptJob->jobPrimitiveInputOutput.outputLengthPtr == (uint32)0UL )
         || ( ptJob->jobPrimitiveInputOutput.inputLength > *ptJob->jobPrimitiveInputOutput.outputLengthPtr )
         || (( ptJob->jobPrimitiveInputOutput.inputLength & CRYPTO_83_SW_IF_4BIT_MASK ) != (uint32)0UL ) )
        {
            ud_Ret = (Std_ReturnType)E_NOT_OK;
        }

        if( ud_Ret == (Std_ReturnType)E_OK )
        {
            u4_InputBlock = (uint32)( ptJob->jobPrimitiveInputOutput.inputLength >> CRYPTO_83_SW_IF_4BIT_SHIFT );

            ud_Ret = Crypto_83_sw_SWSHE_CmdEncCbc( (uint8)ptJob->cryptoKeyId,
                                                   (Crypto_83_sw_ConstR uint8*)&Crypto_83_sw_If_u1KeyElementEncIvData[0],
                                                   u4_InputBlock,
                                                   (Crypto_83_sw_ConstR uint8*)(ptJob->jobPrimitiveInputOutput.inputPtr),
                                                   ptJob->jobPrimitiveInputOutput.outputPtr );

            if( ud_Ret == (Std_ReturnType)E_OK )
            {
                *(ptJob->jobPrimitiveInputOutput.outputLengthPtr) = ptJob->jobPrimitiveInputOutput.inputLength;
            }
        }
    }

    (void)Crypto_83_sw_SecStd_MemSet( (void*)&Crypto_83_sw_If_u1KeyElementEncIvData[0],
                                      (uint8)0U,
                                      CRYPTO_83_SW_INITVECTOR_SIZE );    /* no return check required */
    Crypto_83_sw_If_udEncIvStoredStatus = CRYPTO_83_SW_S_IV_EMPTY;

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_RndGen                                      */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | ptJob :                                                  */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                        :                           */
/*               |  E_NOT_OK                    :                           */
/*               |  CRYPTO_E_BUSY               :                           */
/*               |  CRYPTO_E_ENTROPY_EXHAUSTED  :                           */
/*               |  CSM_AB_E_SHE_RNG_SEED       :                           */
/*               |  CSM_AB_E_SHE_GENERAL_ERROR  :                           */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_RndGen
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
)
{
    Std_ReturnType  ud_Ret = (Std_ReturnType)E_OK;
    uint8           u1_Rnd[CRYPTO_83_SW_IF_RND_SIZE_MAX];
    uint8           u1_Loop;
    uint8           u1_ZeroCount;
    uint8           u1_FFCount;

    if( (ptJob->jobPrimitiveInputOutput.outputPtr == NULL_PTR)
     || (ptJob->jobPrimitiveInputOutput.outputLengthPtr == NULL_PTR)
     || (*(ptJob->jobPrimitiveInputOutput.outputLengthPtr) < (uint32)CRYPTO_83_SW_IF_RND_SIZE_MAX) )
    {
        ud_Ret = (Std_ReturnType)E_NOT_OK;
    }

    if( ud_Ret == (Std_ReturnType)E_OK )
    {
        ud_Ret = Crypto_83_sw_SWSHE_CmdRnd( &u1_Rnd[0] );

        if( ud_Ret == (Std_ReturnType)E_OK )
        {
            u1_ZeroCount = (uint8)0U;
            u1_FFCount = (uint8)0U;

            for( u1_Loop = (uint8)0U; u1_Loop < CRYPTO_83_SW_IF_RND_SIZE_MAX; u1_Loop++ )
            {
                if( u1_Rnd[u1_Loop] == CRYPTO_83_SW_IF_RND_ZERO )
                {
                    u1_ZeroCount++;
                }
                else if( u1_Rnd[u1_Loop] == CRYPTO_83_SW_IF_RND_FF )
                {
                    u1_FFCount++;
                }
                else
                {
                    break;
                }
            }

            if( (u1_ZeroCount == CRYPTO_83_SW_IF_RND_SIZE_MAX)
             || (u1_FFCount == CRYPTO_83_SW_IF_RND_SIZE_MAX) )
            {
                ud_Ret = (Std_ReturnType)CRYPTO_E_ENTROPY_EXHAUSTED;
            }
            else
            {
                *(ptJob->jobPrimitiveInputOutput.outputLengthPtr) = (uint32)CRYPTO_83_SW_IF_RND_SIZE_MAX;

                (void)Crypto_83_sw_SecStd_MemCpy( (void*)(ptJob->jobPrimitiveInputOutput.outputPtr),
                                                  (void*)&u1_Rnd[0],
                                                  (uint32)CRYPTO_83_SW_IF_RND_SIZE_MAX ); /* no return check required */
            }
        }
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_JobRndSeed                                  */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | ptJob :                                                  */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                        :                           */
/*               |  E_NOT_OK                    :                           */
/*               |  CRYPTO_E_BUSY               :                           */
/*               |  CSM_AB_E_SHE_RNG_SEED       :                           */
/*               |  CSM_AB_E_SHE_GENERAL_ERROR  :                           */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_JobRndSeed
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
)
{
    Std_ReturnType  ud_Ret;

    ud_Ret = Crypto_83_sw_RndSeed_KeyEleSet ( ptJob->cryptoKeyId,
                                              ptJob->jobPrimitiveInputOutput.inputPtr,
                                              ptJob->jobPrimitiveInputOutput.inputLength );

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SetSwsheValidStatus                         */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | u4CryptoKeyId    :                                       */
/*               | udSetValidStatus :                                       */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, CRYPTO_83_sw_CODE) Crypto_83_sw_SetSwsheValidStatus
(
    uint32 u4CryptoKeyId,
    Crypto_83_sw_KeyValidStatusType udSetValidStatus
)
{
    Crypto_83_sw_If_udSheKeyValidStatus[u4CryptoKeyId] = udSetValidStatus;

    return;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_NvMKey_KeyEleSet                            */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | u4CryptoKeyId  :                                         */
/*               | u4KeyElementId :                                         */
/*               | ptKey          :                                         */
/*               | u4KeyLength    :                                         */
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
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_NvMKey_KeyEleSet
(
    uint32 u4CryptoKeyId,
    uint32 u4KeyElementId,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptKey,
    uint32 u4KeyLength
)
{
    Std_ReturnType  ud_Ret = (Std_ReturnType)E_OK;
    uint8           u1_M4M5KeyCacheData[CRYPTO_83_SW_M4M5_SIZE + CRYPTO_83_SW_KEYCACHE_SIZE];

    if( u4KeyElementId == CRYPTO_83_SW_AB_KE_KEY )
    {
        if( u4KeyLength != CRYPTO_83_SW_M1M2M3_SIZE )
        {
            ud_Ret = (Std_ReturnType)CRYPTO_E_KEY_SIZE_MISMATCH;
        }

        if( ud_Ret == (Std_ReturnType)E_OK )
        {
            ud_Ret = Crypto_83_sw_SWSHE_CmdLoadKey( (Crypto_83_sw_ConstR uint8*)&ptKey[0],
                                                    (Crypto_83_sw_ConstR uint8*)&ptKey[CRYPTO_83_SW_M1_SIZE],
                                                    (Crypto_83_sw_ConstR uint8*)&ptKey[CRYPTO_83_SW_M1M2_SIZE],
                                                    &u1_M4M5KeyCacheData[0],
                                                    &u1_M4M5KeyCacheData[CRYPTO_83_SW_M4_SIZE] );
        }

        if( ud_Ret == (Std_ReturnType)E_OK )
        {
            if( (uint8)u4CryptoKeyId == u1_M4M5KeyCacheData[CRYPTO_83_SW_M4M5_SIZE] )
            {
                ud_Ret = Crypto_83_sw_SWSHE_CacheUpdateKeyInfo( (uint8)u4CryptoKeyId,
                                                                (Crypto_83_sw_ConstR uint8*)&u1_M4M5KeyCacheData[CRYPTO_83_SW_M4M5_SIZE] );

                if( ud_Ret == (Std_ReturnType)E_OK )
                {
                    (void)Crypto_83_sw_SecStd_MemCpy( (void*)&Crypto_83_sw_If_u1KeyElementProofData[0],
                                                      (const void*)&u1_M4M5KeyCacheData[0],
                                                      CRYPTO_83_SW_M4M5_SIZE ); /* no return check required */
                    Crypto_83_sw_SetSwsheValidStatus( u4CryptoKeyId, CRYPTO_83_SW_S_KEY_INVALID );
                }
            }
            else
            {
                ud_Ret = (Std_ReturnType)E_NOT_OK;
            }
        }
    }
    else if( u4KeyElementId == CRYPTO_83_SW_AB_KE_SHE_PROOF )
    {
        ud_Ret = (Std_ReturnType)CRYPTO_E_KEY_WRITE_FAIL;
    }
    else if( (u4KeyElementId == CRYPTO_83_SW_AB_KE_ENC_CIPHER_IV)
          || (u4KeyElementId == CRYPTO_83_SW_AB_KE_DEC_CIPHER_IV) )
    {
        if( u4KeyLength != CRYPTO_83_SW_INITVECTOR_SIZE )
        {
            ud_Ret = (Std_ReturnType)CRYPTO_E_KEY_SIZE_MISMATCH;
        }

        if( ud_Ret == (Std_ReturnType)E_OK )
        {
            if( u4KeyElementId == CRYPTO_83_SW_AB_KE_ENC_CIPHER_IV )
            {
                (void)Crypto_83_sw_SecStd_MemCpy( (void*)&Crypto_83_sw_If_u1KeyElementEncIvData[0],
                                                  (const void*)ptKey,
                                                  u4KeyLength ); /* no return check required */
                Crypto_83_sw_If_udEncIvStoredStatus = CRYPTO_83_SW_S_IV_STORED;
            }
            else
            {
                (void)Crypto_83_sw_SecStd_MemCpy( (void*)&Crypto_83_sw_If_u1KeyElementDecIvData[0],
                                                  (const void*)ptKey,
                                                  u4KeyLength ); /* no return check required */
                Crypto_83_sw_If_udDecIvStoredStatus = CRYPTO_83_SW_S_IV_STORED;
            }

            Crypto_83_sw_SetSwsheValidStatus( u4CryptoKeyId, CRYPTO_83_SW_S_KEY_INVALID );
        }
    }
    else if( u4KeyElementId == CRYPTO_83_SW_AB_KE_KEYCACHE )
    {
        if( u4KeyLength != CRYPTO_83_SW_KEYCACHE_SIZE )
        {
            ud_Ret = (Std_ReturnType)CRYPTO_E_KEY_SIZE_MISMATCH;
        }

        if( ud_Ret == (Std_ReturnType)E_OK )
        {
            if( (uint8)u4CryptoKeyId == ptKey[0] )
            {
                ud_Ret = Crypto_83_sw_SWSHE_CacheUpdateKeyInfo( (uint8)u4CryptoKeyId, (Crypto_83_sw_ConstR uint8*)ptKey );

                if( ud_Ret == (Std_ReturnType)E_OK )
                {
                    Crypto_83_sw_SetSwsheValidStatus( u4CryptoKeyId, CRYPTO_83_SW_S_KEY_INVALID );
                }
            }
            else
            {
                ud_Ret = (Std_ReturnType)E_NOT_OK;
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
/* Function Name | Crypto_83_sw_RamKey_KeyEleSet                            */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | u4CryptoKeyId  :                                         */
/*               | u4KeyElementId :                                         */
/*               | ptKey          :                                         */
/*               | u4KeyLength    :                                         */
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
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_RamKey_KeyEleSet
(
    uint32 u4CryptoKeyId,
    uint32 u4KeyElementId,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptKey,
    uint32 u4KeyLength
)
{
    Std_ReturnType  ud_Ret = (Std_ReturnType)E_OK;
    uint8           u1_M4M5Data[CRYPTO_83_SW_M4M5_SIZE + CRYPTO_83_SW_KEYCACHE_SIZE];

    if( u4KeyElementId == CRYPTO_83_SW_AB_KE_KEY )
    {
        if( u4KeyLength != CRYPTO_83_SW_M1M2M3_SIZE )
        {
            ud_Ret = (Std_ReturnType)CRYPTO_E_KEY_SIZE_MISMATCH;
        }

        if( ud_Ret == (Std_ReturnType)E_OK )
        {
            ud_Ret = Crypto_83_sw_SWSHE_CmdLoadKey( (Crypto_83_sw_ConstR uint8*)&ptKey[0],
                                                    (Crypto_83_sw_ConstR uint8*)&ptKey[CRYPTO_83_SW_M1_SIZE],
                                                    (Crypto_83_sw_ConstR uint8*)&ptKey[CRYPTO_83_SW_M1M2_SIZE],
                                                    &u1_M4M5Data[0],
                                                    &u1_M4M5Data[CRYPTO_83_SW_M4_SIZE] );

            if( ud_Ret == (Std_ReturnType)E_OK )
            {
                (void)Crypto_83_sw_SecStd_MemCpy( (void*)&Crypto_83_sw_If_u1KeyElementProofData[0],
                                                  (const void*)&u1_M4M5Data[0],
                                                  CRYPTO_83_SW_M4M5_SIZE ); /* no return check required */
                Crypto_83_sw_SetSwsheValidStatus( u4CryptoKeyId, CRYPTO_83_SW_S_KEY_INVALID );
            }
        }
    }
    else if( u4KeyElementId == CRYPTO_83_SW_AB_KE_SHE_PROOF )
    {
        ud_Ret = (Std_ReturnType)CRYPTO_E_KEY_WRITE_FAIL;
    }
    else if( (u4KeyElementId == CRYPTO_83_SW_AB_KE_ENC_CIPHER_IV)
          || (u4KeyElementId == CRYPTO_83_SW_AB_KE_DEC_CIPHER_IV) )
    {
        if( u4KeyLength != CRYPTO_83_SW_INITVECTOR_SIZE )
        {
            ud_Ret = (Std_ReturnType)CRYPTO_E_KEY_SIZE_MISMATCH;
        }

        if( ud_Ret == (Std_ReturnType)E_OK )
        {
            if( u4KeyElementId == CRYPTO_83_SW_AB_KE_ENC_CIPHER_IV )
            {
                (void)Crypto_83_sw_SecStd_MemCpy( (void*)&Crypto_83_sw_If_u1KeyElementEncIvData[0],
                                                  (const void*)ptKey,
                                                  u4KeyLength ); /* no return check required */
                Crypto_83_sw_If_udEncIvStoredStatus = CRYPTO_83_SW_S_IV_STORED;
            }
            else
            {
                (void)Crypto_83_sw_SecStd_MemCpy( (void*)&Crypto_83_sw_If_u1KeyElementDecIvData[0],
                                                  (const void*)ptKey,
                                                  u4KeyLength ); /* no return check required */
                Crypto_83_sw_If_udDecIvStoredStatus = CRYPTO_83_SW_S_IV_STORED;
            }

            Crypto_83_sw_SetSwsheValidStatus( u4CryptoKeyId, CRYPTO_83_SW_S_KEY_INVALID );
        }
    }
    else if( u4KeyElementId == CRYPTO_83_SW_AB_KE_PLAINKEY )
    {
        if( u4KeyLength != CRYPTO_83_SW_PLAINKEY_SIZE )
        {
            ud_Ret = (Std_ReturnType)CRYPTO_E_KEY_SIZE_MISMATCH;
        }

        if( ud_Ret == (Std_ReturnType)E_OK )
        {
            ud_Ret = Crypto_83_sw_SWSHE_CmdLoadPlainKey( (Crypto_83_sw_ConstR uint8*)ptKey );

            if( ud_Ret == (Std_ReturnType)E_OK )
            {
                Crypto_83_sw_SetSwsheValidStatus( u4CryptoKeyId, CRYPTO_83_SW_S_KEY_INVALID );
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
/* Function Name | Crypto_83_sw_UID_KeyEleSet                               */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | u4KeyElementId :                                         */
/*               | ptKey          :                                         */
/*               | u4KeyLength    :                                         */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                       :                            */
/*               |  E_NOT_OK                   :                            */
/*               |  CRYPTO_E_KEY_SIZE_MISMATCH :                            */
/*               |  CSM_AB_E_SHE_GENERAL_ERROR :                            */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_UID_KeyEleSet
(
    uint32 u4KeyElementId,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptKey,
    uint32 u4KeyLength
)
{
    Std_ReturnType  ud_Ret = (Std_ReturnType)E_OK;

    if( u4KeyElementId == CRYPTO_83_SW_AB_KE_UID )
    {
        if( u4KeyLength != CRYPTO_83_SW_UID_SIZE )
        {
            ud_Ret = (Std_ReturnType)CRYPTO_E_KEY_SIZE_MISMATCH;
        }

        if( ud_Ret == (Std_ReturnType)E_OK )
        {
            ud_Ret = Crypto_83_sw_SWSHE_CacheUpdateUid( (Crypto_83_sw_ConstR uint8*)ptKey );
        }
    }
    else
    {
        ud_Ret = (Std_ReturnType)E_NOT_OK;
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_RndSeed_KeyEleSet                           */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | u4CryptoKeyId :                                          */
/*               | ptSeed        :                                          */
/*               | u4SeedLength  :                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                       :                            */
/*               |  E_NOT_OK                   :                            */
/*               |  CRYPTO_E_BUSY              :                            */
/*               |  CSM_AB_E_SHE_RNG_SEED      :                            */
/*               |  CSM_AB_E_SHE_GENERAL_ERROR :                            */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_RndSeed_KeyEleSet
(
    uint32 u4CryptoKeyId,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptSeed,
    uint32 u4SeedLength
)
{
    Std_ReturnType  ud_Ret = (Std_ReturnType)E_OK;

    if( (ptSeed == NULL_PTR)
     || (u4SeedLength != CRYPTO_83_SW_SEED_SIZE) )
    {
        ud_Ret = (Std_ReturnType)E_NOT_OK;
    }

    if( ud_Ret == (Std_ReturnType)E_OK )
    {
        if( u4CryptoKeyId == CRYPTO_83_SW_KEYID_RNG_SEED )
        {
            ud_Ret = Crypto_83_sw_SWSHE_CmdExtendSeed( (Crypto_83_sw_ConstR uint8*)ptSeed );
        }
        else
        {
            ud_Ret = (Std_ReturnType)E_NOT_OK;
        }
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_NvMKey_KeyEleGet                            */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | u4CryptoKeyId  :                                         */
/*               | u4KeyElementId :                                         */
/*               | ptResult       :                                         */
/*               | ptResultLength :                                         */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                        :                           */
/*               |  E_NOT_OK                    :                           */
/*               |  CRYPTO_E_KEY_READ_FAIL      :                           */
/*               |  CSM_AB_E_SHE_MEMORY_FAILURE :                           */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_NvMKey_KeyEleGet
(
    uint32 u4CryptoKeyId,
    uint32 u4KeyElementId,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA)  ptResult,
    P2VAR(uint32, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptResultLength
)
{
    Std_ReturnType                  ud_Ret = (Std_ReturnType)E_OK;
    Crypto_83_sw_Swshe_KeyInfoType  st_CacheLoadKey;

    if( u4KeyElementId == CRYPTO_83_SW_AB_KE_SHE_PROOF )
    {
        if( *ptResultLength < CRYPTO_83_SW_M4M5_SIZE )
        {
            ud_Ret = (Std_ReturnType)E_NOT_OK;
        }

        if( ud_Ret == (Std_ReturnType)E_OK )
        {
            (void)Crypto_83_sw_SecStd_MemCpy( (void*)ptResult,
                                              (void*)&Crypto_83_sw_If_u1KeyElementProofData[0],
                                              CRYPTO_83_SW_M4M5_SIZE ); /* no return check required */
            *ptResultLength = CRYPTO_83_SW_M4M5_SIZE;
        }
    }
    else if( u4KeyElementId == CRYPTO_83_SW_AB_KE_KEYCACHE )
    {
        if( *ptResultLength < CRYPTO_83_SW_KEYCACHE_SIZE )
        {
            ud_Ret = (Std_ReturnType)E_NOT_OK;
        }

        if( ud_Ret == (Std_ReturnType)E_OK )
        {
            ud_Ret = Crypto_83_sw_SWSHE_CacheLoadKey( (uint8)u4CryptoKeyId, &st_CacheLoadKey );

            if( ud_Ret == (Std_ReturnType)E_OK )
            {
                ptResult[CRYPTO_83_SW_IF_KID_POS]       = st_CacheLoadKey.u1Id;
                ptResult[CRYPTO_83_SW_IF_FID_WP_POS]    = st_CacheLoadKey.u1Flag_wp;
                ptResult[CRYPTO_83_SW_IF_FID_BP_POS]    = st_CacheLoadKey.u1Flag_bp;
                ptResult[CRYPTO_83_SW_IF_FID_DP_POS]    = st_CacheLoadKey.u1Flag_dp;
                ptResult[CRYPTO_83_SW_IF_FID_KU_POS]    = st_CacheLoadKey.u1Flag_ku;
                ptResult[CRYPTO_83_SW_IF_FID_WC_POS]    = st_CacheLoadKey.u1Flag_wc;
                ptResult[CRYPTO_83_SW_IF_FID_PL_POS]    = st_CacheLoadKey.u1Flag_plain;
                ptResult[CRYPTO_83_SW_IF_FID_RSV_POS]   = st_CacheLoadKey.u1Flag_rsv1;

                ptResult[CRYPTO_83_SW_IF_CID_1BYTE_POS] = (uint8)((st_CacheLoadKey.u4Counter >> CRYPTO_83_SW_24BIT_SHIFT));
                ptResult[CRYPTO_83_SW_IF_CID_2BYTE_POS] = (uint8)((st_CacheLoadKey.u4Counter >> CRYPTO_83_SW_16BIT_SHIFT) & CRYPTO_83_SW_IF_8BIT_MASK);
                ptResult[CRYPTO_83_SW_IF_CID_3BYTE_POS] = (uint8)((st_CacheLoadKey.u4Counter >> CRYPTO_83_SW_8BIT_SHIFT ) & CRYPTO_83_SW_IF_8BIT_MASK);
                ptResult[CRYPTO_83_SW_IF_CID_4BYTE_POS] = (uint8)(st_CacheLoadKey.u4Counter & CRYPTO_83_SW_IF_8BIT_MASK);

                ptResult[CRYPTO_83_SW_IF_RSV_1BYTE_POS] = (uint8)0U;
                ptResult[CRYPTO_83_SW_IF_RSV_2BYTE_POS] = (uint8)0U;
                ptResult[CRYPTO_83_SW_IF_RSV_3BYTE_POS] = (uint8)0U;
                ptResult[CRYPTO_83_SW_IF_RSV_4BYTE_POS] = (uint8)0U;

                (void)Crypto_83_sw_SecStd_MemCpy( (void*)&ptResult[CRYPTO_83_SW_IF_KEYINFO_DATA_POS],
                                                  (void*)&st_CacheLoadKey.u1Data,
                                                  CRYPTO_83_SW_IF_KEY_SIZE ); /* no return check required */

                *ptResultLength = CRYPTO_83_SW_KEYCACHE_SIZE;
            }
        }
    }
    else if( ( u4KeyElementId == CRYPTO_83_SW_AB_KE_KEY )
          || ( u4KeyElementId == CRYPTO_83_SW_AB_KE_ENC_CIPHER_IV )
          || ( u4KeyElementId == CRYPTO_83_SW_AB_KE_DEC_CIPHER_IV ) )
    {
        ud_Ret = (Std_ReturnType)CRYPTO_E_KEY_READ_FAIL;
    }
    else
    {
        ud_Ret = (Std_ReturnType)E_NOT_OK;
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_RamKey_KeyEleGet                            */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | u4KeyElementId :                                         */
/*               | ptResult       :                                         */
/*               | ptResultLength :                                         */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                       :                            */
/*               |  E_NOT_OK                   :                            */
/*               |  CRYPTO_E_KEY_READ_FAIL     :                            */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_RamKey_KeyEleGet
(
    uint32 u4KeyElementId,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA)  ptResult,
    P2VAR(uint32, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptResultLength
)
{
    Std_ReturnType  ud_Ret = (Std_ReturnType)E_OK;

    if( u4KeyElementId == CRYPTO_83_SW_AB_KE_SHE_PROOF )
    {
        if( *ptResultLength < CRYPTO_83_SW_M4M5_SIZE )
        {
            ud_Ret = (Std_ReturnType)E_NOT_OK;
        }

        if( ud_Ret == (Std_ReturnType)E_OK )
        {
            (void)Crypto_83_sw_SecStd_MemCpy( (void*)ptResult,
                                              (void*)&Crypto_83_sw_If_u1KeyElementProofData[0],
                                              CRYPTO_83_SW_M4M5_SIZE ); /* no return check required */
            *ptResultLength = CRYPTO_83_SW_M4M5_SIZE;
        }
    }
    else if( (u4KeyElementId == CRYPTO_83_SW_AB_KE_KEY)
          || (u4KeyElementId == CRYPTO_83_SW_AB_KE_ENC_CIPHER_IV)
          || (u4KeyElementId == CRYPTO_83_SW_AB_KE_DEC_CIPHER_IV)
          || (u4KeyElementId == CRYPTO_83_SW_AB_KE_PLAINKEY) )
    {
        ud_Ret = (Std_ReturnType)CRYPTO_E_KEY_READ_FAIL;
    }
    else
    {
        ud_Ret = (Std_ReturnType)E_NOT_OK;
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_UID_KeyEleGet                               */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | u4KeyElementId :                                         */
/*               | ptResult       :                                         */
/*               | ptResultLength :                                         */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                        :                           */
/*               |  E_NOT_OK                    :                           */
/*               |  CSM_AB_E_SHE_MEMORY_FAILURE :                           */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_UID_KeyEleGet
(
    uint32 u4KeyElementId,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA)  ptResult,
    P2VAR(uint32, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptResultLength
)
{
    Std_ReturnType  ud_Ret = (Std_ReturnType)E_OK;

    if( u4KeyElementId == CRYPTO_83_SW_AB_KE_UID )
    {
        if( *ptResultLength < CRYPTO_83_SW_UID_SIZE )
        {
            ud_Ret = (Std_ReturnType)E_NOT_OK;
        }

        if( ud_Ret == (Std_ReturnType)E_OK )
        {
            ud_Ret = Crypto_83_sw_SWSHE_CacheLoadUid( ptResult );

            if( ud_Ret == (Std_ReturnType)E_OK )
            {
                *ptResultLength = CRYPTO_83_SW_UID_SIZE;
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
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Crypto_83_sw_CheckSwsheValidStatus                       */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | u4CryptoKeyId :                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                   :                                */
/*               |  E_NOT_OK               :                                */
/*               |  CRYPTO_E_KEY_NOT_VALID :                                */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_CheckSwsheValidStatus
(
    uint32 u4CryptoKeyId
)
{
    Std_ReturnType ud_Ret = (Std_ReturnType)E_NOT_OK;

    if( (u4CryptoKeyId > (uint32)0UL)
     && (u4CryptoKeyId < CRYPTO_83_SW_SHEKEY_NUM) )
    {
        if( ( u4CryptoKeyId != CRYPTO_83_SW_KEYID_BOOT_MAC_KEY )
         && ( u4CryptoKeyId != CRYPTO_83_SW_KEYID_BOOT_MAC ) )
        {
            if( Crypto_83_sw_If_udSheKeyValidStatus[u4CryptoKeyId] == CRYPTO_83_SW_S_KEY_VALID )
            {
                ud_Ret = (Std_ReturnType)E_OK;
            }
            else
            {
                ud_Ret = (Std_ReturnType)CRYPTO_E_KEY_NOT_VALID;
            }
        }
    }

    return ud_Ret;
}

#define CRYPTO_83_sw_STOP_SEC_CODE
#include <Crypto_83_sw_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2022/09/26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
