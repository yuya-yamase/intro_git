/* Crypto_83_sw_Internal_h_v2-0-0                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Crypto_83_sw/Internal/HEADER                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef CRYPTO_83_SW_INTERNAL_H
#define CRYPTO_83_SW_INTERNAL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <Crypto_GeneralTypes.h>
#include "../../SecStd/inc/Crypto_83_sw_SecStd_String.h"
#include "./Crypto_83_sw_Cfg_Fixed.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* CryptoDriver Status */
#define CRYPTO_83_SW_S_CD_INIT                  ((Crypto_83_sw_DriverStatusType)0xE1U)
#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
#define CRYPTO_83_SW_S_CD_UNINIT                ((Crypto_83_sw_DriverStatusType)0x00U)
#define CRYPTO_83_SW_S_CD_FAULT                 ((Crypto_83_sw_DriverStatusType)0xD2U)
#endif

/* KeyElement Status */
#define CRYPTO_83_SW_S_KEY_INVALID              ((Crypto_83_sw_KeyValidStatusType)0xF0U)
#define CRYPTO_83_SW_S_KEY_VALID                ((Crypto_83_sw_KeyValidStatusType)0xE1U)

/* CryptoKeyId Parameter */
#define CRYPTO_83_SW_KEYID_MASTER_ECU_KEY       ((uint32)0x01UL)
#define CRYPTO_83_SW_KEYID_BOOT_MAC_KEY         ((uint32)0x02UL)
#define CRYPTO_83_SW_KEYID_BOOT_MAC             ((uint32)0x03UL)
#define CRYPTO_83_SW_KEYID_KEY_1                ((uint32)0x04UL)
#define CRYPTO_83_SW_KEYID_KEY_10               ((uint32)0x0DUL)
#define CRYPTO_83_SW_KEYID_RAM_KEY              ((uint32)0x0EUL)
#define CRYPTO_83_SW_KEYID_UID                  ((uint32)0x0FUL)
#define CRYPTO_83_SW_KEYID_RNG_SEED             ((uint32)0x10UL)
#define CRYPTO_83_SW_KEYID_PUBKEY               ((uint32)0x11UL)

/* Data Size Parameter */
#define CRYPTO_83_SW_INITVECTOR_SIZE            ((uint32)16UL)
#define CRYPTO_83_SW_M1_SIZE                    ((uint32)16UL)
#define CRYPTO_83_SW_M4_SIZE                    ((uint32)32UL)
#define CRYPTO_83_SW_M1M2M3_SIZE                ((uint32)64UL)
#define CRYPTO_83_SW_M1M2_SIZE                  ((uint32)48UL)
#define CRYPTO_83_SW_M4M5_SIZE                  ((uint32)48UL)
#define CRYPTO_83_SW_SHEKEY_NUM                 ((uint32)15UL)
#define CRYPTO_83_SW_UID_SIZE                   ((uint32)15UL)
#define CRYPTO_83_SW_PLAINKEY_SIZE              ((uint32)16UL)
#define CRYPTO_83_SW_KEYCACHE_SIZE              ((uint32)32UL)
#define CRYPTO_83_SW_PUBKEY_DATA_SIZE           ((uint32)12UL)
#define CRYPTO_83_SW_PUBKEY_NDATA_SIZE          ((uint32)384UL)
#define CRYPTO_83_SW_SEED_SIZE                  ((uint32)16UL)

/* Convert form byte to bit */
#define CRYPTO_83_SW_BYTE_TO_BIT_CONV           ((uint8)3U)

/* Convert from bit to byte */
#define CRYPTO_83_SW_BIT_TO_BYTE_CONV           ((uint8)3U)

/* Count Parametar */
#define CRYPTO_83_SW_OBJECT_NUM                 ((uint8)9U)

/* Shift Parameter */
#define CRYPTO_83_SW_24BIT_SHIFT                ((uint32)24UL)
#define CRYPTO_83_SW_16BIT_SHIFT                ((uint32)16UL)
#define CRYPTO_83_SW_8BIT_SHIFT                 ((uint32)8UL)

#ifndef Crypto_83_sw_ConstR
#define Crypto_83_sw_ConstR const
#endif

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef uint8   Crypto_83_sw_DriverStatusType;
typedef uint8   Crypto_83_sw_KeyValidStatusType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define CRYPTO_83_sw_START_SEC_CODE
#include <Crypto_83_sw_MemMap.h>

/* Crypto_83_sw */
extern FUNC(Crypto_83_sw_DriverStatusType, CRYPTO_83_sw_CODE) Crypto_83_sw_GetStatus
(
    void
);

extern FUNC(void, CRYPTO_83_sw_CODE) Crypto_83_sw_IntervalCallout
(
    void
);

/* Crypto_83_sw_If_SWSHE */
extern FUNC(void, CRYPTO_83_sw_CODE) Crypto_83_sw_If_SwsheInit
(
    void
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_MacGen
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_MacVer
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_EcbDecStart
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_EcbDecUpdate
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_EcbDecFinish
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_EcbEnc
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_CbcDecStart
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_CbcDecUpdate
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_CbcDecFinish
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_CbcEnc
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_RndGen
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_JobRndSeed
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
);

extern FUNC(void, CRYPTO_83_sw_CODE) Crypto_83_sw_SetSwsheValidStatus
(
    uint32 u4CryptoKeyId,
    Crypto_83_sw_KeyValidStatusType udSetValidStatus
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_NvMKey_KeyEleSet
(
    uint32 u4CryptoKeyId,
    uint32 u4KeyElementId,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptKey,
    uint32 u4KeyLength
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_RamKey_KeyEleSet
(
    uint32 u4CryptoKeyId,
    uint32 u4KeyElementId,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptKey,
    uint32 u4KeyLength
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_UID_KeyEleSet
(
    uint32 u4KeyElementId,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptKey,
    uint32 u4KeyLength
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_RndSeed_KeyEleSet
(
    uint32 u4CryptoKeyId,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptSeed,
    uint32 u4SeedLength
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_NvMKey_KeyEleGet
(
    uint32 u4CryptoKeyId,
    uint32 u4KeyElementId,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptResult,
    P2VAR(uint32, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptResultLength
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_RamKey_KeyEleGet
(
    uint32 u4KeyElementId,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptResult,
    P2VAR(uint32, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptResultLength
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_UID_KeyEleGet
(
    uint32 u4KeyElementId,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptResult,
    P2VAR(uint32, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptResultLength
);

/* Crypto_83_sw_If_RSA */
extern FUNC(void, CRYPTO_83_sw_CODE) Crypto_83_sw_If_RsaInit
(
    void
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_Hash
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_RSA_PKCS1_SigVerStart
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_RSA_PKCS1_SigVerUpdate
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_RSA_PKCS1_SigVerFinish
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_RSA_PSS_SigVerStart
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_RSA_PSS_SigVerUpdate
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_RSA_PSS_SigVerFinish
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_PubKey_KeyEleSet
(
    uint32 u4KeyElementId,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptKey,
    uint32 u4KeyLength
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_PubKey_KeyEleGet
(
    uint32 u4KeyElementId
);

extern FUNC(void, CRYPTO_83_sw_CODE) Crypto_83_sw_SetRsaValidStatus
(
    Crypto_83_sw_KeyValidStatusType udSetValidStatus
);

/* Crypto_83_sw_JobKey */
extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_JobKeySetValid
(
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
);

#define CRYPTO_83_sw_STOP_SEC_CODE
#include <Crypto_83_sw_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif  /* CRYPTO_83_SW_INTERNAL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2022/12/16                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
