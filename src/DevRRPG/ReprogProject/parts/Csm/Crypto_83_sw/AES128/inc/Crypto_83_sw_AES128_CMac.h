/* Crypto_83_sw_AES128_CMac_h_v2-0-0                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | AES128/CMac/HEADER                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef CRYPTO_83_SW_AES128_CMAC_H
#define CRYPTO_83_SW_AES128_CMAC_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "Crypto_83_sw_AES128_Ecb.h"


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define     CRYPTO_83_SW_AES128_OTHER_BLOCK          ((uint8)0x00U)
#define     CRYPTO_83_SW_AES128_LAST_BLOCK           ((uint8)0x01U)
#define     CRYPTO_83_SW_AES128_SUBKEY_UNCOMPLETE    ((uint8)0x00U)
#define     CRYPTO_83_SW_AES128_SUBKEY_COMPLETE      ((uint8)0x01U)
#define     CRYPTO_83_SW_AES128_SUBKEY_RB            ((uint8)0x87U)

#define     CRYPTO_83_SW_AES128_CMAC_LEN_MIN         ((uint8)0x01U)
#define     CRYPTO_83_SW_AES128_CMAC_LEN_MAX         ((uint8)0x10U)
#define     CRYPTO_83_SW_AES128_CMAC_RESERVED_NUM    ((uint8)0x03U)


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct
{
    Crypto_83_sw_AES128_Ecb_CtxBufType   stEcbCtxBuf;
    Crypto_83_sw_AES128_CryptBufType     unVectorData;
    Crypto_83_sw_AES128_CryptBufType     unSubKey1;
    Crypto_83_sw_AES128_CryptBufType     unSubKey2;
    uint8                                u1SubKeyState;
    uint8                                u1Reserved[CRYPTO_83_SW_AES128_CMAC_RESERVED_NUM];
} Crypto_83_sw_AES128_CMac_CtxBufType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
uint8 Crypto_83_sw_AES128_CMac_start(
    Crypto_83_sw_ConstR uint8 *ptKeyStartAddr,
    uint8 u1KeyLength,
    Crypto_83_sw_AES128_CMac_CtxBufType *ptContextBuffer
);

uint8 Crypto_83_sw_AES128_CMac_updSubkey(
    Crypto_83_sw_AES128_CMac_CtxBufType *ptContextBuffer
);

uint8 Crypto_83_sw_AES128_CMac_update(
    Crypto_83_sw_ConstR uint8 *ptInputDataStartAddr,
    uint8 *ptOutputDataStartAddr,
    uint8 u1InputDataLength,
    uint32 u4LastBlock,
    Crypto_83_sw_AES128_CMac_CtxBufType *ptContextBuffer
);


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif  /* CRYPTO_83_SW_AES128_CMAC_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2022/11/11                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
