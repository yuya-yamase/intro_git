/* Crypto_83_sw_AES128_Cbc_h_v2-0-0                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | AES128/Cbc/HEADER                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef CRYPTO_83_SW_AES128_CBC_H
#define CRYPTO_83_SW_AES128_CBC_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "Crypto_83_sw_AES128_Ecb.h"


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define     CRYPTO_83_SW_AES128_IV_LENGTH        ((uint8)0x10U)


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct
{
    Crypto_83_sw_AES128_Ecb_CtxBufType   stEcbCtxBuf;
    Crypto_83_sw_AES128_CryptBufType     unVectorData;
    Crypto_83_sw_AES128_CryptBufType     unInputDataBuf;
} Crypto_83_sw_AES128_Cbc_CtxBufType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
uint8 Crypto_83_sw_AES128_Cbc_start(
    Crypto_83_sw_ConstR uint8 *ptKeyStartAddr,
    uint8 u1KeyLength,
    Crypto_83_sw_ConstR uint8 *ptVectorStartAddr,
    uint8 u1VectorLength,
    Crypto_83_sw_AES128_Cbc_CtxBufType *ptContextBuffer
);

uint8 Crypto_83_sw_AES128_Cbc_updateEnc(
    Crypto_83_sw_ConstR uint8 *ptInputDataStartAddr,
    uint8 *ptOutputDataStartAddr,
    uint8 u1InputDataLength,
    Crypto_83_sw_AES128_Cbc_CtxBufType *ptContextBuffer
);

uint8 Crypto_83_sw_AES128_Cbc_updateDec(
    Crypto_83_sw_ConstR uint8 *ptInputDataStartAddr,
    uint8 *ptOutputDataStartAddr,
    uint8 u1InputDataLength,
    Crypto_83_sw_AES128_Cbc_CtxBufType *ptContextBuffer
);

void Crypto_83_sw_AES128_Cbc_finish(
    Crypto_83_sw_AES128_Cbc_CtxBufType *ptContextBuffer
);


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif  /* CRYPTO_83_SW_AES128_CBC_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2022/09/26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
