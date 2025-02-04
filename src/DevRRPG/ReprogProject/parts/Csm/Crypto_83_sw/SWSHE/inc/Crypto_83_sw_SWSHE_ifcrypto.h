/* Crypto_83_sw_SWSHE_ifcrypto_h_v2-0-0                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | SWSHE/ifcrypto/HEADER                                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef CRYPTO_83_SW_SWSHE_IFCRYPTO_H
#define CRYPTO_83_SW_SWSHE_IFCRYPTO_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "Crypto_83_sw_SWSHE.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define CRYPTO_83_SW_SWSHE_MEMCMP_OK  ((uint32)0x00)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define CRYPTO_83_sw_START_SEC_CODE
#include <Crypto_83_sw_MemMap.h>

extern FUNC(void, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_IfcryptoInit
(
    void
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_AES128_EncEcb
(
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_VAR_NO_INIT) ptKey,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptPlain,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptCipher
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_AES128_DecEcb
(
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_VAR_NO_INIT) ptKey,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptCipher,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptPlain
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_AES128_EncCbc
(
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_VAR_NO_INIT) ptKey,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_VAR_NO_INIT) ptIvdata,
    uint32 u4Len,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptPlain,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptCipher
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_AES128_DecCbc
(
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_VAR_NO_INIT) ptKey,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_VAR_NO_INIT) ptIvdata,
    uint32 u4Len,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptCipher,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptPlain
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_AES128_CMac
(
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_VAR_NO_INIT) ptKey,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptInput,
    uint32 u4Length,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptOutput
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_InitRandom
(
    void
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_ReseedRandom
(
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptSeed
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_GenerateRandom
(
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptRnd
);

#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SWSHE_IfCryptoGetErrorStatus
(
    void
);
#endif

#define CRYPTO_83_sw_STOP_SEC_CODE
#include <Crypto_83_sw_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* CRYPTO_83_SW_SWSHE_IFCRYPTO_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2022/09/26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
