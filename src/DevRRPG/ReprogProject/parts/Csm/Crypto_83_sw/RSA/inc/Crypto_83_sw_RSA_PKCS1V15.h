/* Crypto_83_sw_RSA_PKCS1V15_h_v2-0-0                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CRYPTO_83_SW/RSA/PKCS1V15/HEADER                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef CRYPTO_83_SW_RSA_PKCS1V15_H
#define CRYPTO_83_SW_RSA_PKCS1V15_H

#include "Crypto_83_sw_RSA_SigVer.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

typedef Crypto_83_sw_RSA_SignatureVerifyCtxBufType Crypto_83_sw_RSA_PKCS1V15_CtxBufType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

Crypto_83_sw_RSA_ReturnType Crypto_83_sw_RSA_PKCS1V15_VerStart
(
    Crypto_83_sw_RSA_SignatureVerifyCtxBufType *ptContextBuffer,
    Crypto_83_sw_ConstR Crypto_83_sw_RSA_AsymPublicKeyType* Crypto_83_sw_ConstR ptKeyPtr[]
);

Crypto_83_sw_RSA_ReturnType Crypto_83_sw_RSA_PKCS1V15_VerUpdate
(
    Crypto_83_sw_RSA_SignatureVerifyCtxBufType* ptContextBuffer,
    Crypto_83_sw_ConstR uint8 *ptDataPtr,
    uint32 u4DataLength
);

Crypto_83_sw_RSA_ReturnType Crypto_83_sw_RSA_PKCS1V15_VerFinish
(
    Crypto_83_sw_RSA_SignatureVerifyCtxBufType *ptContextBuffer,
    Crypto_83_sw_ConstR uint8 *ptSignaturePtr,
    uint32 u4SignatureLength,
    Crypto_83_sw_RSA_VerifyResultType *ptResultPtr
);

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif  /* CRYPTO_83_SW_RSA_PKCS1V15_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2022/12/16                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
