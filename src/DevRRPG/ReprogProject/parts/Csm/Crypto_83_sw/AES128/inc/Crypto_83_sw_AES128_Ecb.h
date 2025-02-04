/* Crypto_83_sw_AES128_Ecb_h_v2-0-0                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | AES128/Ecb/HEADER                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef CRYPTO_83_SW_AES128_ECB_H
#define CRYPTO_83_SW_AES128_ECB_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define     CRYPTO_83_SW_AES128_OK                   ((uint8)0x00U)
#define     CRYPTO_83_SW_AES128_NOT_OK               ((uint8)0xFFU)



#define     CRYPTO_83_SW_AES128_BUF_SIZE             (4U)
#define     CRYPTO_83_SW_AES128_BYTE_NUM             (4U)

#define     CRYPTO_83_SW_AES128_ROUND_NUM            ((uint8)10U)
#define     CRYPTO_83_SW_AES128_ROUND_KEY_NUM        (CRYPTO_83_SW_AES128_ROUND_NUM + (uint8)(1U))

#define     CRYPTO_83_SW_AES128_UNINIT               ((uint8)0x00U)
#define     CRYPTO_83_SW_AES128_CALC_ENABLE          ((uint8)0x01U)


#define     CRYPTO_83_SW_AES128_KEY_LENGTH           ((uint8)0x10U)
#define     CRYPTO_83_SW_AES128_INPUTDATA_LENGTH     ((uint8)0x10U)


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

typedef union
{
    uint32  u4CryptBufUint32[CRYPTO_83_SW_AES128_BUF_SIZE];
    uint8   u1CryptBufUint8[CRYPTO_83_SW_AES128_BUF_SIZE][CRYPTO_83_SW_AES128_BYTE_NUM];
} Crypto_83_sw_AES128_CryptBufType;


typedef struct
{
    Crypto_83_sw_AES128_CryptBufType   unRoundKey[CRYPTO_83_SW_AES128_ROUND_KEY_NUM];
    Crypto_83_sw_AES128_CryptBufType   unState;
    uint8                              u1CalcState;
    uint8                              u1RoundNum;
    uint16                             u2Reserved;
} Crypto_83_sw_AES128_Ecb_CtxBufType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
uint8 Crypto_83_sw_AES128_Ecb_start
(
    Crypto_83_sw_ConstR uint8 *ptKeyStartAddr,
    uint8 u1KeyLength,
    Crypto_83_sw_AES128_Ecb_CtxBufType *ptContextBuffer
);

uint8 Crypto_83_sw_AES128_Ecb_updateEnc(
    Crypto_83_sw_ConstR uint8 *ptInputDataStartAddr,
    uint8 *ptOutputDataStartAddr,
    uint8 u1InputDataLength,
    Crypto_83_sw_AES128_Ecb_CtxBufType *ptContextBuffer
);

uint8 Crypto_83_sw_AES128_Ecb_updateDec(
    Crypto_83_sw_ConstR uint8 *ptInputDataStartAddr,
    uint8 *ptOutputDataStartAddr,
    uint8 u1InputDataLength,
    Crypto_83_sw_AES128_Ecb_CtxBufType *ptContextBuffer
);

void Crypto_83_sw_AES128_Ecb_finish(
    Crypto_83_sw_AES128_Ecb_CtxBufType *ptContextBuffer
);

void Crypto_83_sw_AES128_Ecb_blockEnc(
    Crypto_83_sw_AES128_Ecb_CtxBufType *ptContextBuffer
);


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif  /* CRYPTO_83_SW_AES128_ECB_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2023/01/13                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
