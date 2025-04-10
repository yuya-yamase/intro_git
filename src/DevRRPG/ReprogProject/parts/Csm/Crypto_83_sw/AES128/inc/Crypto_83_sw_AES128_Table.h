/* Crypto_83_sw_AES128_Table_h_v2-0-0                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | AES128/Table/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef CRYPTO_83_SW_AES128_TABLE_H
#define CRYPTO_83_SW_AES128_TABLE_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "Crypto_83_sw_AES128_Type.h"


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define     CRYPTO_83_SW_AES128_SIZE_SBMC_TABLE (256)
#define     CRYPTO_83_SW_AES128_SIZE_RCON_TABLE  (17)
#define     CRYPTO_83_SW_AES128_BIT32_BYTE_NUM    (4)


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

typedef union
{
    uint8   u8[CRYPTO_83_SW_AES128_BIT32_BYTE_NUM];
    uint32  u32;
} Crypto_83_sw_AES128_Bit32;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
extern CONST(AB_83_ConstV Crypto_83_sw_AES128_Bit32, CRYPTO_83_sw_CONST) Crypto_83_sw_AES128_unLutMc02_01_01_03[CRYPTO_83_SW_AES128_SIZE_SBMC_TABLE];
extern CONST(AB_83_ConstV Crypto_83_sw_AES128_Bit32, CRYPTO_83_sw_CONST) Crypto_83_sw_AES128_unLutMc03_02_01_01[CRYPTO_83_SW_AES128_SIZE_SBMC_TABLE];
extern CONST(AB_83_ConstV Crypto_83_sw_AES128_Bit32, CRYPTO_83_sw_CONST) Crypto_83_sw_AES128_unLutMc01_03_02_01[CRYPTO_83_SW_AES128_SIZE_SBMC_TABLE];
extern CONST(AB_83_ConstV Crypto_83_sw_AES128_Bit32, CRYPTO_83_sw_CONST) Crypto_83_sw_AES128_unLutMc01_01_03_02[CRYPTO_83_SW_AES128_SIZE_SBMC_TABLE];
extern CONST(AB_83_ConstV Crypto_83_sw_AES128_Bit32, CRYPTO_83_sw_CONST) Crypto_83_sw_AES128_unLut0E090D0B[CRYPTO_83_SW_AES128_SIZE_SBMC_TABLE];
extern CONST(AB_83_ConstV Crypto_83_sw_AES128_Bit32, CRYPTO_83_sw_CONST) Crypto_83_sw_AES128_unLut0B0E090D[CRYPTO_83_SW_AES128_SIZE_SBMC_TABLE];
extern CONST(AB_83_ConstV Crypto_83_sw_AES128_Bit32, CRYPTO_83_sw_CONST) Crypto_83_sw_AES128_unLut0D0B0E09[CRYPTO_83_SW_AES128_SIZE_SBMC_TABLE];
extern CONST(AB_83_ConstV Crypto_83_sw_AES128_Bit32, CRYPTO_83_sw_CONST) Crypto_83_sw_AES128_unLut090D0B0E[CRYPTO_83_SW_AES128_SIZE_SBMC_TABLE];
extern CONST(AB_83_ConstV uint8, CRYPTO_83_sw_CONST) Crypto_83_sw_AES128_u1InvSbox[CRYPTO_83_SW_AES128_SIZE_SBMC_TABLE];
extern CONST(AB_83_ConstV uint8, CRYPTO_83_sw_CONST) Crypto_83_sw_AES128_u1Rcon[CRYPTO_83_SW_AES128_SIZE_RCON_TABLE];


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif  /* CRYPTO_83_SW_AES128_TABLE_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2023/01/13                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
