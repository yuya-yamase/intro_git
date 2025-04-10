/* Crypto_83_sw_RSA_PSS_h_v2-0-0                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CRYPTO_83_SW/RSA/PSS/HEADER                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef CRYPTO_83_SW_RSA_PSS_H
#define CRYPTO_83_SW_RSA_PSS_H

#include "Crypto_83_sw_RSA_SigVer.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

typedef Crypto_83_sw_RSA_SignatureVerifyCtxBufType Crypto_83_sw_RSA_PSS_CtxBufType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

extern Crypto_83_sw_RSA_ReturnType Crypto_83_sw_RSA_PSS_VerStart
(
    Crypto_83_sw_RSA_PSS_CtxBufType *ptContextBuffer,
    Crypto_83_sw_ConstR Crypto_83_sw_RSA_AsymPublicKeyType* Crypto_83_sw_ConstR ptPublicKey[]
);

extern Crypto_83_sw_RSA_ReturnType Crypto_83_sw_RSA_PSS_VerUpdate
(
    Crypto_83_sw_RSA_PSS_CtxBufType *ptContextBuffer,
    Crypto_83_sw_ConstR uint8 *ptData,
    uint32 u4DataLength
);

extern Crypto_83_sw_RSA_ReturnType Crypto_83_sw_RSA_PSS_VerFinish
(
    Crypto_83_sw_RSA_PSS_CtxBufType *ptContextBuffer,
    Crypto_83_sw_ConstR uint8 *ptSignature,
    uint32 u4SignatureLength,
    Crypto_83_sw_RSA_VerifyResultType *ptResult
);

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif  /* CRYPTO_83_SW_RSA_PSS_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2022/12/16                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
