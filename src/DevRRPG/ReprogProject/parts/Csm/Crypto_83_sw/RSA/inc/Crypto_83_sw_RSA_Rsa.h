/* Crypto_83_sw_RSA_Rsa_h_v2-0-0                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CRYPTO_83_SW/RSA/RSA/HEADER                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef CRYPTO_83_SW_RSA_RSA_H
#define CRYPTO_83_SW_RSA_RSA_H

#include "Crypto_83_sw_RSA_Type.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

#define CRYPTO_83_SW_RSA_E_OK                    ((Crypto_83_sw_RSA_ReturnType)0U)
#define CRYPTO_83_SW_RSA_E_NOT_OK                ((Crypto_83_sw_RSA_ReturnType)1U)

#define CRYPTO_83_SW_RSA_3BIT_SHIFT              ((uint8)3U)
#define CRYPTO_83_SW_RSA_2BIT_SHIFT              ((uint8)2U)

#define CRYPTO_83_SW_RSA_MPI_MAX_DATANUM         ((uint32)(((CRYPTO_83_SW_RSA_KEY_BIT >> 3U) << 1U) >> 2U) + (uint32)1U)
#define CRYPTO_83_SW_RSA_KEY_MAX_SIZE            (uint32)(((CRYPTO_83_SW_RSA_KEY_BIT >> 3U) >> 2U))

#define CRYPTO_83_SW_RSA_KEY_BIT                 ((uint32)3072UL)

#define CRYPTO_83_SW_RSA_A_BIGGER_THAN_B         ((sint32)1L)
#define CRYPTO_83_SW_RSA_A_EQUAL_B               ((sint32)0L)
#define CRYPTO_83_SW_RSA_B_BIGGER_THAN_A         ((sint32)-1L)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

typedef struct {
    uint32   u4Length;
    uint32   u4Data[CRYPTO_83_SW_RSA_KEY_MAX_SIZE];
} Crypto_83_sw_RSA_KeyType;


typedef struct {
    uint32   u4Num;
    uint32   u4Data[CRYPTO_83_SW_RSA_MPI_MAX_DATANUM];
} Crypto_83_sw_RSA_MpiType;


typedef struct {
    Crypto_83_sw_ConstR Crypto_83_sw_RSA_KeyType   *ptModulus;
    Crypto_83_sw_ConstR Crypto_83_sw_RSA_KeyType   *ptExponent;
    Crypto_83_sw_RSA_MpiType         stR2modn;
    uint32                           u4N2;
    uint32                           u4NBitLength;
} Crypto_83_sw_RSA_CtxBufType;

typedef uint8                         Crypto_83_sw_RSA_ReturnType;
typedef Crypto_83_sw_RSA_CtxBufType   Crypto_83_sw_RSA_AsymEncryptCtxBufType;
typedef Crypto_83_sw_RSA_KeyType      Crypto_83_sw_RSA_AsymPublicKeyType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

Crypto_83_sw_RSA_ReturnType Crypto_83_sw_RSA_RSAVP1_Start
(
    Crypto_83_sw_RSA_AsymEncryptCtxBufType *ptContextBuffer,
    Crypto_83_sw_ConstR Crypto_83_sw_RSA_AsymPublicKeyType* Crypto_83_sw_ConstR ptKeyPtr[]
);


Crypto_83_sw_RSA_ReturnType Crypto_83_sw_RSA_RSAVP1_Update
(
    Crypto_83_sw_ConstR Crypto_83_sw_RSA_AsymEncryptCtxBufType *ptContextBuffer,
    Crypto_83_sw_ConstR uint8 *ptPlainTextPtr,
    uint32 u4PlainTextLength,
    uint8 *ptCipherTextPtr,
    uint32 *ptCipherTextLengthPtr
);


void Crypto_83_sw_RSA_RSAVP1_Finish
(
    Crypto_83_sw_RSA_AsymEncryptCtxBufType *ptContextBuffer
);

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif  /* CRYPTO_83_SW_RSA_RSA_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2023/01/16                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
