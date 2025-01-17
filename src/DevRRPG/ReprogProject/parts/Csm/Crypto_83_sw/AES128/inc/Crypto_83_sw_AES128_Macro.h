/* Crypto_83_sw_AES128_Macro_h_v2-0-0                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | AES128/Macro/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef CRYPTO_83_SW_AES128_MACRO_H
#define CRYPTO_83_SW_AES128_MACRO_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "Crypto_83_sw_AES128_Type.h"
#include "Crypto_83_sw_AES128_Table.h"
#include "Crypto_83_sw_AES128_Ecb.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define     CRYPTO_83_SW_AES128_BIT7         ((uint8)0x80U)

#define     CRYPTO_83_SW_AES128_ROW_0        ((uint8)0U)
#define     CRYPTO_83_SW_AES128_ROW_1        ((uint8)1U)
#define     CRYPTO_83_SW_AES128_ROW_2        ((uint8)2U)
#define     CRYPTO_83_SW_AES128_ROW_3        ((uint8)3U)
#define     CRYPTO_83_SW_AES128_ROW_4        ((uint8)4U)
#define     CRYPTO_83_SW_AES128_ROW_5        ((uint8)5U)
#define     CRYPTO_83_SW_AES128_ROW_6        ((uint8)6U)
#define     CRYPTO_83_SW_AES128_ROW_7        ((uint8)7U)
#define     CRYPTO_83_SW_AES128_ROW_8        ((uint8)8U)
#define     CRYPTO_83_SW_AES128_ROW_9        ((uint8)9U)
#define     CRYPTO_83_SW_AES128_ROW_10       ((uint8)10U)
#define     CRYPTO_83_SW_AES128_ROW_11       ((uint8)11U)
#define     CRYPTO_83_SW_AES128_ROW_12       ((uint8)12U)
#define     CRYPTO_83_SW_AES128_ROW_13       ((uint8)13U)
#define     CRYPTO_83_SW_AES128_ROW_14       ((uint8)14U)
#define     CRYPTO_83_SW_AES128_ROW_15       ((uint8)15U)

#define     CRYPTO_83_SW_AES128_COL_0        ((uint8)0U)
#define     CRYPTO_83_SW_AES128_COL_1        ((uint8)1U)
#define     CRYPTO_83_SW_AES128_COL_2        ((uint8)2U)
#define     CRYPTO_83_SW_AES128_COL_3        ((uint8)3U)

#define     CRYPTO_83_SW_AES128_ROUND_0      ((uint8)0U)
#define     CRYPTO_83_SW_AES128_ROUND_1      ((uint8)1U)
#define     CRYPTO_83_SW_AES128_ROUND_2      ((uint8)2U)
#define     CRYPTO_83_SW_AES128_ROUND_3      ((uint8)3U)
#define     CRYPTO_83_SW_AES128_ROUND_4      ((uint8)4U)
#define     CRYPTO_83_SW_AES128_ROUND_5      ((uint8)5U)
#define     CRYPTO_83_SW_AES128_ROUND_6      ((uint8)6U)
#define     CRYPTO_83_SW_AES128_ROUND_7      ((uint8)7U)
#define     CRYPTO_83_SW_AES128_ROUND_8      ((uint8)8U)
#define     CRYPTO_83_SW_AES128_ROUND_9      ((uint8)9U)
#define     CRYPTO_83_SW_AES128_ROUND_10     ((uint8)10U)

#define     CRYPTO_83_SW_AES128_SHIFT_1BIT   (1U)
#define     CRYPTO_83_SW_AES128_SHIFT_7BIT   (7U)

#define     CRYPTO_83_SW_AES128_ONE          ((uint8)1U)
#define     CRYPTO_83_SW_AES128_PADM2        (0x80U)

/****************************************************************************/
/* Macro Name    | CRYPTO_83_SW_AES128_Align4                               */
/* Description   | Check word align                                         */
/****************************************************************************/

#define CRYPTO_83_SW_AES128_Align4(addr)  (((uint32)(addr)) & 3UL)

/****************************************************************************/
/* Macro Name    | CRYPTO_83_SW_AES128_blockClear                           */
/* Description   | Clear 1 block memory                                     */
/****************************************************************************/
#define CRYPTO_83_SW_AES128_blockClear(blk)                                  \
do {                                                                         \
    (blk)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_0] = 0U;                 \
    (blk)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_1] = 0U;                 \
    (blk)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_2] = 0U;                 \
    (blk)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_3] = 0U;                 \
} while( 0 )

/****************************************************************************/
/* Macro Name    | CRYPTO_83_SW_AES128_blockCopy_U8ToBuf                    */
/* Description   | Copy array(uint8) to square data.                        */
/****************************************************************************/
#define CRYPTO_83_SW_AES128_blockCopy_U8ToBuf(pdst, psrc)                              \
do {                                                                                   \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_0] =    \
        (psrc)[CRYPTO_83_SW_AES128_ROW_0];                                             \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_1] =    \
        (psrc)[CRYPTO_83_SW_AES128_ROW_1];                                             \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_2] =    \
        (psrc)[CRYPTO_83_SW_AES128_ROW_2];                                             \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_3] =    \
        (psrc)[CRYPTO_83_SW_AES128_ROW_3];                                             \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_0] =    \
        (psrc)[CRYPTO_83_SW_AES128_ROW_4];                                             \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_1] =    \
        (psrc)[CRYPTO_83_SW_AES128_ROW_5];                                             \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_2] =    \
        (psrc)[CRYPTO_83_SW_AES128_ROW_6];                                             \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_3] =    \
        (psrc)[CRYPTO_83_SW_AES128_ROW_7];                                             \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_0] =    \
        (psrc)[CRYPTO_83_SW_AES128_ROW_8];                                             \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_1] =    \
        (psrc)[CRYPTO_83_SW_AES128_ROW_9];                                             \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_2] =    \
        (psrc)[CRYPTO_83_SW_AES128_ROW_10];                                            \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_3] =    \
        (psrc)[CRYPTO_83_SW_AES128_ROW_11];                                            \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_0] =    \
        (psrc)[CRYPTO_83_SW_AES128_ROW_12];                                            \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_1] =    \
        (psrc)[CRYPTO_83_SW_AES128_ROW_13];                                            \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_2] =    \
        (psrc)[CRYPTO_83_SW_AES128_ROW_14];                                            \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_3] =    \
        (psrc)[CRYPTO_83_SW_AES128_ROW_15];                                            \
} while( 0 )

/****************************************************************************/
/* Macro Name    | CRYPTO_83_SW_AES128_blockCopy_BufToU8                    */
/* Description   | Copy square data to array(uint8).                        */
/****************************************************************************/
#define CRYPTO_83_SW_AES128_blockCopy_BufToU8(pdst, psrc)                              \
do {                                                                                   \
    (pdst)[CRYPTO_83_SW_AES128_ROW_0] =                                                \
        (psrc)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_0]; \
    (pdst)[CRYPTO_83_SW_AES128_ROW_1] =                                                \
        (psrc)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_1]; \
    (pdst)[CRYPTO_83_SW_AES128_ROW_2] =                                                \
        (psrc)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_2]; \
    (pdst)[CRYPTO_83_SW_AES128_ROW_3] =                                                \
        (psrc)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_3]; \
    (pdst)[CRYPTO_83_SW_AES128_ROW_4] =                                                \
        (psrc)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_0]; \
    (pdst)[CRYPTO_83_SW_AES128_ROW_5] =                                                \
        (psrc)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_1]; \
    (pdst)[CRYPTO_83_SW_AES128_ROW_6] =                                                \
        (psrc)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_2]; \
    (pdst)[CRYPTO_83_SW_AES128_ROW_7] =                                                \
        (psrc)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_3]; \
    (pdst)[CRYPTO_83_SW_AES128_ROW_8] =                                                \
        (psrc)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_0]; \
    (pdst)[CRYPTO_83_SW_AES128_ROW_9] =                                                \
        (psrc)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_1]; \
    (pdst)[CRYPTO_83_SW_AES128_ROW_10] =                                               \
        (psrc)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_2]; \
    (pdst)[CRYPTO_83_SW_AES128_ROW_11] =                                               \
        (psrc)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_3]; \
    (pdst)[CRYPTO_83_SW_AES128_ROW_12] =                                               \
        (psrc)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_0]; \
    (pdst)[CRYPTO_83_SW_AES128_ROW_13] =                                               \
        (psrc)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_1]; \
    (pdst)[CRYPTO_83_SW_AES128_ROW_14] =                                               \
        (psrc)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_2]; \
    (pdst)[CRYPTO_83_SW_AES128_ROW_15] =                                               \
        (psrc)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_3]; \
} while( 0 )

/****************************************************************************/
/* Macro Name    | CRYPTO_83_SW_AES128_blockCopy32                          */
/* Description   | Copy aligned square data.                                */
/****************************************************************************/
#define CRYPTO_83_SW_AES128_blockCopy32(pdst, psrc)                                                            \
do {                                                                                                           \
    (pdst)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_0] = (psrc)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_0]; \
    (pdst)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_1] = (psrc)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_1]; \
    (pdst)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_2] = (psrc)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_2]; \
    (pdst)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_3] = (psrc)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_3]; \
} while( 0 )

/****************************************************************************/
/* Macro Name    | CRYPTO_83_SW_AES128_Buf_XorBufBuf                        */
/* Description   | Xor  block data.                                         */
/****************************************************************************/
#define CRYPTO_83_SW_AES128_Buf_XorBufBuf(pdst, ps1, ps2)                                     \
do {                                                                                          \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_0] =           \
                (ps1)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_0]  \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_0]; \
                                                                                              \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_1] =           \
                (ps1)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_1]  \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_1]; \
                                                                                              \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_2] =           \
                (ps1)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_2]  \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_2]; \
                                                                                              \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_3] =           \
                (ps1)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_3]  \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_3]; \
                                                                                              \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_0] =           \
                (ps1)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_0]  \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_0]; \
                                                                                              \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_1] =           \
                (ps1)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_1]  \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_1]; \
                                                                                              \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_2] =           \
                (ps1)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_2]  \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_2]; \
                                                                                              \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_3] =           \
                (ps1)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_3]  \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_3]; \
                                                                                              \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_0] =           \
                (ps1)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_0]  \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_0]; \
                                                                                              \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_1] =           \
                (ps1)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_1]  \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_1]; \
                                                                                              \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_2] =           \
                (ps1)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_2]  \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_2]; \
                                                                                              \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_3] =           \
                (ps1)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_3]  \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_3]; \
                                                                                              \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_0] =           \
                (ps1)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_0]  \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_0]; \
                                                                                              \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_1] =           \
                (ps1)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_1]  \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_1]; \
                                                                                              \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_2] =           \
                (ps1)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_2]  \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_2]; \
                                                                                              \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_3] =           \
                (ps1)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_3]  \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_3]; \
} while( 0 )

/****************************************************************************/
/* Macro Name    | CRYPTO_83_SW_AES128_U8_XorBufBuf                         */
/* Description   | Xor block data and set it array(uint8).                  */
/****************************************************************************/
#define CRYPTO_83_SW_AES128_U8_XorBufBuf(pdst, ps1, ps2)                                      \
do {                                                                                          \
    (pdst)[CRYPTO_83_SW_AES128_ROW_0] =                                                       \
                (ps1)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_0]  \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_0]; \
                                                                                              \
    (pdst)[CRYPTO_83_SW_AES128_ROW_1] =                                                       \
                (ps1)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_1]  \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_1]; \
                                                                                              \
    (pdst)[CRYPTO_83_SW_AES128_ROW_2] =                                                       \
                (ps1)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_2]  \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_2]; \
                                                                                              \
    (pdst)[CRYPTO_83_SW_AES128_ROW_3] =                                                       \
                (ps1)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_3]  \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_3]; \
                                                                                              \
    (pdst)[CRYPTO_83_SW_AES128_ROW_4] =                                                       \
                (ps1)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_0]  \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_0]; \
                                                                                              \
    (pdst)[CRYPTO_83_SW_AES128_ROW_5] =                                                       \
                (ps1)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_1]  \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_1]; \
                                                                                              \
    (pdst)[CRYPTO_83_SW_AES128_ROW_6] =                                                       \
                (ps1)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_2]  \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_2]; \
                                                                                              \
    (pdst)[CRYPTO_83_SW_AES128_ROW_7] =                                                       \
                (ps1)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_3]  \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_3]; \
                                                                                              \
    (pdst)[CRYPTO_83_SW_AES128_ROW_8] =                                                       \
                (ps1)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_0]  \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_0]; \
                                                                                              \
    (pdst)[CRYPTO_83_SW_AES128_ROW_9] =                                                       \
                (ps1)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_1]  \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_1]; \
                                                                                              \
    (pdst)[CRYPTO_83_SW_AES128_ROW_10] =                                                      \
                (ps1)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_2]  \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_2]; \
                                                                                              \
    (pdst)[CRYPTO_83_SW_AES128_ROW_11] =                                                      \
                (ps1)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_3]  \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_3]; \
                                                                                              \
    (pdst)[CRYPTO_83_SW_AES128_ROW_12] =                                                      \
                (ps1)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_0]  \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_0]; \
                                                                                              \
    (pdst)[CRYPTO_83_SW_AES128_ROW_13] =                                                      \
                (ps1)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_1]  \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_1]; \
                                                                                              \
    (pdst)[CRYPTO_83_SW_AES128_ROW_14] =                                                      \
                (ps1)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_2]  \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_2]; \
                                                                                              \
    (pdst)[CRYPTO_83_SW_AES128_ROW_15] =                                                      \
                (ps1)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_3]  \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_3]; \
} while( 0 )

/****************************************************************************/
/* Macro Name    | CRYPTO_83_SW_AES128_Buf_XorU8Buf                         */
/* Description   | Xor array(uint8) with block data and set it block data.  */
/****************************************************************************/
#define CRYPTO_83_SW_AES128_Buf_XorU8Buf(pdst, ps1, ps2)                                      \
do {                                                                                          \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_0] =           \
                (ps1)[CRYPTO_83_SW_AES128_ROW_0]                                              \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_0]; \
                                                                                              \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_1] =           \
                (ps1)[CRYPTO_83_SW_AES128_ROW_1]                                              \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_1]; \
                                                                                              \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_2] =           \
                (ps1)[CRYPTO_83_SW_AES128_ROW_2]                                              \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_2]; \
                                                                                              \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_3] =           \
                (ps1)[CRYPTO_83_SW_AES128_ROW_3]                                              \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_3]; \
                                                                                              \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_0] =           \
                (ps1)[CRYPTO_83_SW_AES128_ROW_4]                                              \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_0]; \
                                                                                              \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_1] =           \
                (ps1)[CRYPTO_83_SW_AES128_ROW_5]                                              \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_1]; \
                                                                                              \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_2] =           \
                (ps1)[CRYPTO_83_SW_AES128_ROW_6]                                              \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_2]; \
                                                                                              \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_3] =           \
                (ps1)[CRYPTO_83_SW_AES128_ROW_7]                                              \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_3]; \
                                                                                              \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_0] =           \
                (ps1)[CRYPTO_83_SW_AES128_ROW_8]                                              \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_0]; \
                                                                                              \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_1] =           \
                (ps1)[CRYPTO_83_SW_AES128_ROW_9]                                              \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_1]; \
                                                                                              \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_2] =           \
                (ps1)[CRYPTO_83_SW_AES128_ROW_10]                                             \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_2]; \
                                                                                              \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_3] =           \
                (ps1)[CRYPTO_83_SW_AES128_ROW_11]                                             \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_3]; \
                                                                                              \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_0] =           \
                (ps1)[CRYPTO_83_SW_AES128_ROW_12]                                             \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_0]; \
                                                                                              \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_1] =           \
                (ps1)[CRYPTO_83_SW_AES128_ROW_13]                                             \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_1]; \
                                                                                              \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_2] =           \
                (ps1)[CRYPTO_83_SW_AES128_ROW_14]                                             \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_2]; \
                                                                                              \
    (pdst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_3] =           \
                (ps1)[CRYPTO_83_SW_AES128_ROW_15]                                             \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_3]; \
} while( 0 )

/****************************************************************************/
/* Macro Name    | CRYPTO_83_SW_AES128_U8_XorU8Buf                          */
/* Description   | Xor array(uint8) with block data and set it array.       */
/****************************************************************************/
#define CRYPTO_83_SW_AES128_U8_XorU8Buf(pdst, ps1, ps2)                                       \
do {                                                                                          \
    (pdst)[CRYPTO_83_SW_AES128_ROW_0] =                                                       \
                (ps1)[CRYPTO_83_SW_AES128_ROW_0]                                              \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_0]; \
                                                                                              \
    (pdst)[CRYPTO_83_SW_AES128_ROW_1] =                                                       \
                (ps1)[CRYPTO_83_SW_AES128_ROW_1]                                              \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_1]; \
                                                                                              \
    (pdst)[CRYPTO_83_SW_AES128_ROW_2] =                                                       \
                (ps1)[CRYPTO_83_SW_AES128_ROW_2]                                              \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_2]; \
                                                                                              \
    (pdst)[CRYPTO_83_SW_AES128_ROW_3] =                                                       \
                (ps1)[CRYPTO_83_SW_AES128_ROW_3]                                              \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_3]; \
                                                                                              \
    (pdst)[CRYPTO_83_SW_AES128_ROW_4] =                                                       \
                (ps1)[CRYPTO_83_SW_AES128_ROW_4]                                              \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_0]; \
                                                                                              \
    (pdst)[CRYPTO_83_SW_AES128_ROW_5] =                                                       \
                (ps1)[CRYPTO_83_SW_AES128_ROW_5]                                              \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_1]; \
                                                                                              \
    (pdst)[CRYPTO_83_SW_AES128_ROW_6] =                                                       \
                (ps1)[CRYPTO_83_SW_AES128_ROW_6]                                              \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_2]; \
                                                                                              \
    (pdst)[CRYPTO_83_SW_AES128_ROW_7] =                                                       \
                (ps1)[CRYPTO_83_SW_AES128_ROW_7]                                              \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_3]; \
                                                                                              \
    (pdst)[CRYPTO_83_SW_AES128_ROW_8] =                                                       \
                (ps1)[CRYPTO_83_SW_AES128_ROW_8]                                              \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_0]; \
                                                                                              \
    (pdst)[CRYPTO_83_SW_AES128_ROW_9] =                                                       \
                (ps1)[CRYPTO_83_SW_AES128_ROW_9]                                              \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_1]; \
                                                                                              \
    (pdst)[CRYPTO_83_SW_AES128_ROW_10] =                                                      \
                (ps1)[CRYPTO_83_SW_AES128_ROW_10]                                             \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_2]; \
                                                                                              \
    (pdst)[CRYPTO_83_SW_AES128_ROW_11] =                                                      \
                (ps1)[CRYPTO_83_SW_AES128_ROW_11]                                             \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_3]; \
                                                                                              \
    (pdst)[CRYPTO_83_SW_AES128_ROW_12] =                                                      \
                (ps1)[CRYPTO_83_SW_AES128_ROW_12]                                             \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_0]; \
                                                                                              \
    (pdst)[CRYPTO_83_SW_AES128_ROW_13] =                                                      \
                (ps1)[CRYPTO_83_SW_AES128_ROW_13]                                             \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_1]; \
                                                                                              \
    (pdst)[CRYPTO_83_SW_AES128_ROW_14] =                                                      \
                (ps1)[CRYPTO_83_SW_AES128_ROW_14]                                             \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_2]; \
                                                                                              \
    (pdst)[CRYPTO_83_SW_AES128_ROW_15] =                                                      \
                (ps1)[CRYPTO_83_SW_AES128_ROW_15]                                             \
               ^(ps2)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_3]; \
} while( 0 )

/****************************************************************************/
/* Macro Name    | CRYPTO_83_SW_AES128_blockXor32                           */
/* Description   | Xor aligned block data.                                  */
/****************************************************************************/
#define CRYPTO_83_SW_AES128_blockXor32(pdst, ps1, ps2)                                                            \
do {                                                                                                              \
    (pdst)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_0] =                                                         \
         (ps1)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_0] ^ (ps2)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_0]; \
    (pdst)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_1] =                                                         \
         (ps1)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_1] ^ (ps2)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_1]; \
    (pdst)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_2] =                                                         \
         (ps1)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_2] ^ (ps2)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_2]; \
    (pdst)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_3] =                                                         \
         (ps1)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_3] ^ (ps2)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_3]; \
} while( 0 )

/****************************************************************************/
/* Macro Name    | CRYPTO_83_SW_AES128_blockShiftLeft                       */
/* Description   | Shift 128 bit to left 1 bit.                             */
/****************************************************************************/
#define CRYPTO_83_SW_AES128_blockShiftLeft(dstbase, srcbase)                                         \
do {                                                                                                 \
    ((uint8*)(dstbase))[CRYPTO_83_SW_AES128_ROW_0]  =                                                \
        (uint8)(((uint8*)(srcbase))[CRYPTO_83_SW_AES128_ROW_0] << CRYPTO_83_SW_AES128_SHIFT_1BIT) |  \
        (uint8)(((uint8*)(srcbase))[CRYPTO_83_SW_AES128_ROW_1] >> CRYPTO_83_SW_AES128_SHIFT_7BIT);   \
                                                                                                     \
    ((uint8*)(dstbase))[CRYPTO_83_SW_AES128_ROW_1]  =                                                \
        (uint8)(((uint8*)(srcbase))[CRYPTO_83_SW_AES128_ROW_1] << CRYPTO_83_SW_AES128_SHIFT_1BIT) |  \
        (uint8)(((uint8*)(srcbase))[CRYPTO_83_SW_AES128_ROW_2] >> CRYPTO_83_SW_AES128_SHIFT_7BIT);   \
                                                                                                     \
    ((uint8*)(dstbase))[CRYPTO_83_SW_AES128_ROW_2]  =                                                \
        (uint8)(((uint8*)(srcbase))[CRYPTO_83_SW_AES128_ROW_2] << CRYPTO_83_SW_AES128_SHIFT_1BIT) |  \
        (uint8)(((uint8*)(srcbase))[CRYPTO_83_SW_AES128_ROW_3] >> CRYPTO_83_SW_AES128_SHIFT_7BIT);   \
                                                                                                     \
    ((uint8*)(dstbase))[CRYPTO_83_SW_AES128_ROW_3]  =                                                \
        (uint8)(((uint8*)(srcbase))[CRYPTO_83_SW_AES128_ROW_3] << CRYPTO_83_SW_AES128_SHIFT_1BIT) |  \
        (uint8)(((uint8*)(srcbase))[CRYPTO_83_SW_AES128_ROW_4] >> CRYPTO_83_SW_AES128_SHIFT_7BIT);   \
                                                                                                     \
    ((uint8*)(dstbase))[CRYPTO_83_SW_AES128_ROW_4]  =                                                \
        (uint8)(((uint8*)(srcbase))[CRYPTO_83_SW_AES128_ROW_4] << CRYPTO_83_SW_AES128_SHIFT_1BIT) |  \
        (uint8)(((uint8*)(srcbase))[CRYPTO_83_SW_AES128_ROW_5] >> CRYPTO_83_SW_AES128_SHIFT_7BIT);   \
                                                                                                     \
    ((uint8*)(dstbase))[CRYPTO_83_SW_AES128_ROW_5]  =                                                \
        (uint8)(((uint8*)(srcbase))[CRYPTO_83_SW_AES128_ROW_5] << CRYPTO_83_SW_AES128_SHIFT_1BIT) |  \
        (uint8)(((uint8*)(srcbase))[CRYPTO_83_SW_AES128_ROW_6] >> CRYPTO_83_SW_AES128_SHIFT_7BIT);   \
                                                                                                     \
    ((uint8*)(dstbase))[CRYPTO_83_SW_AES128_ROW_6]  =                                                \
        (uint8)(((uint8*)(srcbase))[CRYPTO_83_SW_AES128_ROW_6] << CRYPTO_83_SW_AES128_SHIFT_1BIT) |  \
        (uint8)(((uint8*)(srcbase))[CRYPTO_83_SW_AES128_ROW_7] >> CRYPTO_83_SW_AES128_SHIFT_7BIT);   \
                                                                                                     \
    ((uint8*)(dstbase))[CRYPTO_83_SW_AES128_ROW_7]  =                                                \
        (uint8)(((uint8*)(srcbase))[CRYPTO_83_SW_AES128_ROW_7] << CRYPTO_83_SW_AES128_SHIFT_1BIT) |  \
        (uint8)(((uint8*)(srcbase))[CRYPTO_83_SW_AES128_ROW_8] >> CRYPTO_83_SW_AES128_SHIFT_7BIT);   \
                                                                                                     \
    ((uint8*)(dstbase))[CRYPTO_83_SW_AES128_ROW_8]  =                                                \
        (uint8)(((uint8*)(srcbase))[CRYPTO_83_SW_AES128_ROW_8] << CRYPTO_83_SW_AES128_SHIFT_1BIT) |  \
        (uint8)(((uint8*)(srcbase))[CRYPTO_83_SW_AES128_ROW_9] >> CRYPTO_83_SW_AES128_SHIFT_7BIT);   \
                                                                                                     \
    ((uint8*)(dstbase))[CRYPTO_83_SW_AES128_ROW_9]  =                                                \
        (uint8)(((uint8*)(srcbase))[CRYPTO_83_SW_AES128_ROW_9]  << CRYPTO_83_SW_AES128_SHIFT_1BIT) | \
        (uint8)(((uint8*)(srcbase))[CRYPTO_83_SW_AES128_ROW_10] >> CRYPTO_83_SW_AES128_SHIFT_7BIT);  \
                                                                                                     \
    ((uint8*)(dstbase))[CRYPTO_83_SW_AES128_ROW_10] =                                                \
        (uint8)(((uint8*)(srcbase))[CRYPTO_83_SW_AES128_ROW_10] << CRYPTO_83_SW_AES128_SHIFT_1BIT) | \
        (uint8)(((uint8*)(srcbase))[CRYPTO_83_SW_AES128_ROW_11] >> CRYPTO_83_SW_AES128_SHIFT_7BIT);  \
                                                                                                     \
    ((uint8*)(dstbase))[CRYPTO_83_SW_AES128_ROW_11] =                                                \
        (uint8)(((uint8*)(srcbase))[CRYPTO_83_SW_AES128_ROW_11] << CRYPTO_83_SW_AES128_SHIFT_1BIT) | \
        (uint8)(((uint8*)(srcbase))[CRYPTO_83_SW_AES128_ROW_12] >> CRYPTO_83_SW_AES128_SHIFT_7BIT);  \
                                                                                                     \
    ((uint8*)(dstbase))[CRYPTO_83_SW_AES128_ROW_12] =                                                \
        (uint8)(((uint8*)(srcbase))[CRYPTO_83_SW_AES128_ROW_12] << CRYPTO_83_SW_AES128_SHIFT_1BIT) | \
        (uint8)(((uint8*)(srcbase))[CRYPTO_83_SW_AES128_ROW_13] >> CRYPTO_83_SW_AES128_SHIFT_7BIT);  \
                                                                                                     \
    ((uint8*)(dstbase))[CRYPTO_83_SW_AES128_ROW_13] =                                                \
        (uint8)(((uint8*)(srcbase))[CRYPTO_83_SW_AES128_ROW_13] << CRYPTO_83_SW_AES128_SHIFT_1BIT) | \
        (uint8)(((uint8*)(srcbase))[CRYPTO_83_SW_AES128_ROW_14] >> CRYPTO_83_SW_AES128_SHIFT_7BIT);  \
                                                                                                     \
    ((uint8*)(dstbase))[CRYPTO_83_SW_AES128_ROW_14] =                                                \
        (uint8)(((uint8*)(srcbase))[CRYPTO_83_SW_AES128_ROW_14] << CRYPTO_83_SW_AES128_SHIFT_1BIT) | \
        (uint8)(((uint8*)(srcbase))[CRYPTO_83_SW_AES128_ROW_15] >> CRYPTO_83_SW_AES128_SHIFT_7BIT);  \
                                                                                                     \
    ((uint8*)(dstbase))[CRYPTO_83_SW_AES128_ROW_15] =                                                \
        (uint8)(((uint8*)(srcbase))[CRYPTO_83_SW_AES128_ROW_15] << CRYPTO_83_SW_AES128_SHIFT_1BIT);  \
} while( 0 )

/****************************************************************************/
/* Macro Name    | CRYPTO_83_SW_AES128_addRoundKey                          */
/* Description   | Add round key (xor)                                      */
/****************************************************************************/

#define CRYPTO_83_SW_AES128_addRoundKey(ctx, r)                                               \
    CRYPTO_83_SW_AES128_blockXor32(&(ctx)->unState, &(ctx)->unState, &(ctx)->unRoundKey[(r)])

/****************************************************************************/
/* Macro Name    | CRYPTO_83_SW_AES128_keyExpandRound                       */
/* Description   | 1 round key schedule.                                    */
/****************************************************************************/
#define CRYPTO_83_SW_AES128_keyExpandRound(rk, r)                                                                                                 \
do {                                                                                                                                              \
    /* Round[r].NK[0] */                                                                                                                          \
    (rk)[(r)].u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_3] =                                                             \
        CRYPTO_83_SW_AES128_subBytes((rk)[(r) - CRYPTO_83_SW_AES128_ONE].u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_0]);  \
    (rk)[(r)].u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_2] =                                                             \
        CRYPTO_83_SW_AES128_subBytes((rk)[(r) - CRYPTO_83_SW_AES128_ONE].u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_3]);  \
    (rk)[(r)].u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_1] =                                                             \
        CRYPTO_83_SW_AES128_subBytes((rk)[(r) - CRYPTO_83_SW_AES128_ONE].u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_2]);  \
    (rk)[(r)].u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_0] =                                                             \
        CRYPTO_83_SW_AES128_subBytes((rk)[(r) - CRYPTO_83_SW_AES128_ONE].u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_1]) ^ \
        Crypto_83_sw_AES128_u1Rcon[(r)];                                                                                                          \
    (rk)[(r)].u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_0] ^=                                                                                      \
        (rk)[(r) - CRYPTO_83_SW_AES128_ONE].u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_0];                                                          \
                                                                                                                                                  \
    /* Round[r].NK[1] */                                                                                                                          \
    (rk)[(r)].u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_1]  =                                                                                      \
        (rk)[(r) - CRYPTO_83_SW_AES128_ONE].u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_1] ^                                                         \
        (rk)[(r)].u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_0];                                                                                    \
                                                                                                                                                  \
    /* Round[r].NK[2] */                                                                                                                          \
    (rk)[(r)].u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_2]  =                                                                                      \
        (rk)[(r) - CRYPTO_83_SW_AES128_ONE].u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_2] ^                                                         \
        (rk)[(r)].u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_1];                                                                                    \
                                                                                                                                                  \
    /* Round[r].NK[3] */                                                                                                                          \
    (rk)[(r)].u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_3]  =                                                                                      \
        (rk)[(r) - CRYPTO_83_SW_AES128_ONE].u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_3] ^                                                         \
        (rk)[(r)].u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_2];                                                                                    \
} while( 0 )

/****************************************************************************/
/* Macro Name    | CRYPTO_83_SW_AES128_subBytes                             */
/* Description   | Subbytes.                                                */
/****************************************************************************/

#define CRYPTO_83_SW_AES128_subBytes(v) (uint8)(Crypto_83_sw_AES128_unLutMc01_03_02_01[(v)].u8[CRYPTO_83_SW_AES128_ROW_0])

/****************************************************************************/
/* Macro Name    | CRYPTO_83_SW_AES128_invSubBytes                          */
/* Description   | Inversed subbytes.                                       */
/****************************************************************************/

#define CRYPTO_83_SW_AES128_invSubBytes(v)   Crypto_83_sw_AES128_u1InvSbox[(v)]

/****************************************************************************/
/* Macro Name    | CRYPTO_83_SW_AES128_keyExpand                            */
/* Description   | 10 round key shedule                                     */
/****************************************************************************/
#define CRYPTO_83_SW_AES128_keyExpand(key, ctx)                                          \
do {                                                                                     \
    CRYPTO_83_SW_AES128_blockCopy_U8ToBuf(                                               \
        (ctx)->unRoundKey,                                                               \
        (key)                                                                            \
    );                                                                                   \
    CRYPTO_83_SW_AES128_keyExpandRound((ctx)->unRoundKey, CRYPTO_83_SW_AES128_ROUND_1);  \
    CRYPTO_83_SW_AES128_keyExpandRound((ctx)->unRoundKey, CRYPTO_83_SW_AES128_ROUND_2);  \
    CRYPTO_83_SW_AES128_keyExpandRound((ctx)->unRoundKey, CRYPTO_83_SW_AES128_ROUND_3);  \
    CRYPTO_83_SW_AES128_keyExpandRound((ctx)->unRoundKey, CRYPTO_83_SW_AES128_ROUND_4);  \
    CRYPTO_83_SW_AES128_keyExpandRound((ctx)->unRoundKey, CRYPTO_83_SW_AES128_ROUND_5);  \
    CRYPTO_83_SW_AES128_keyExpandRound((ctx)->unRoundKey, CRYPTO_83_SW_AES128_ROUND_6);  \
    CRYPTO_83_SW_AES128_keyExpandRound((ctx)->unRoundKey, CRYPTO_83_SW_AES128_ROUND_7);  \
    CRYPTO_83_SW_AES128_keyExpandRound((ctx)->unRoundKey, CRYPTO_83_SW_AES128_ROUND_8);  \
    CRYPTO_83_SW_AES128_keyExpandRound((ctx)->unRoundKey, CRYPTO_83_SW_AES128_ROUND_9);  \
    CRYPTO_83_SW_AES128_keyExpandRound((ctx)->unRoundKey, CRYPTO_83_SW_AES128_ROUND_10); \
} while( 0 )

/****************************************************************************/
/* Macro Name    | CRYPTO_83_SW_AES128_shiftRow0                            */
/* Description   | Subbytes and ShiftRow0                                   */
/****************************************************************************/
/* ROW-0 */
#define CRYPTO_83_SW_AES128_shiftRow0(base, r0, r1, r2, r3)                            \
do {                                                                                   \
    (r0) = CRYPTO_83_SW_AES128_subBytes(((uint8*)(base))[CRYPTO_83_SW_AES128_ROW_0]);  \
    (r1) = CRYPTO_83_SW_AES128_subBytes(((uint8*)(base))[CRYPTO_83_SW_AES128_ROW_5]);  \
    (r2) = CRYPTO_83_SW_AES128_subBytes(((uint8*)(base))[CRYPTO_83_SW_AES128_ROW_10]); \
    (r3) = CRYPTO_83_SW_AES128_subBytes(((uint8*)(base))[CRYPTO_83_SW_AES128_ROW_15]); \
} while( 0 )

/****************************************************************************/
/* Macro Name    | CRYPTO_83_SW_AES128_shiftRow1                            */
/* Description   | Subbytes and ShiftRow1                                   */
/****************************************************************************/
/* ROW-1 */
#define CRYPTO_83_SW_AES128_shiftRow1(base, r0, r1, r2, r3)                            \
do {                                                                                   \
    (r0) = CRYPTO_83_SW_AES128_subBytes(((uint8*)(base))[CRYPTO_83_SW_AES128_ROW_4]);  \
    (r1) = CRYPTO_83_SW_AES128_subBytes(((uint8*)(base))[CRYPTO_83_SW_AES128_ROW_9]);  \
    (r2) = CRYPTO_83_SW_AES128_subBytes(((uint8*)(base))[CRYPTO_83_SW_AES128_ROW_14]); \
    (r3) = CRYPTO_83_SW_AES128_subBytes(((uint8*)(base))[CRYPTO_83_SW_AES128_ROW_3]);  \
} while( 0 )

/****************************************************************************/
/* Macro Name    | CRYPTO_83_SW_AES128_shiftRow2                            */
/* Description   | Subbytes and ShiftRow2                                   */
/****************************************************************************/
/* ROW-2 */
#define CRYPTO_83_SW_AES128_shiftRow2(base, r0, r1, r2, r3)                            \
do {                                                                                   \
    (r0) = CRYPTO_83_SW_AES128_subBytes(((uint8*)(base))[CRYPTO_83_SW_AES128_ROW_8]);  \
    (r1) = CRYPTO_83_SW_AES128_subBytes(((uint8*)(base))[CRYPTO_83_SW_AES128_ROW_13]); \
    (r2) = CRYPTO_83_SW_AES128_subBytes(((uint8*)(base))[CRYPTO_83_SW_AES128_ROW_2]);  \
    (r3) = CRYPTO_83_SW_AES128_subBytes(((uint8*)(base))[CRYPTO_83_SW_AES128_ROW_7]);  \
} while( 0 )

/****************************************************************************/
/* Macro Name    | CRYPTO_83_SW_AES128_shiftRow3                            */
/* Description   | Subbytes and ShiftRow3                                   */
/****************************************************************************/
/* ROW-3 */
#define CRYPTO_83_SW_AES128_shiftRow3(base, r0, r1, r2, r3)                            \
do {                                                                                   \
    (r0) = CRYPTO_83_SW_AES128_subBytes(((uint8*)(base))[CRYPTO_83_SW_AES128_ROW_12]); \
    (r1) = CRYPTO_83_SW_AES128_subBytes(((uint8*)(base))[CRYPTO_83_SW_AES128_ROW_1]);  \
    (r2) = CRYPTO_83_SW_AES128_subBytes(((uint8*)(base))[CRYPTO_83_SW_AES128_ROW_6]);  \
    (r3) = CRYPTO_83_SW_AES128_subBytes(((uint8*)(base))[CRYPTO_83_SW_AES128_ROW_11]); \
} while( 0 )

/****************************************************************************/
/* Macro Name    | CRYPTO_83_SW_AES128_roundEnc                             */
/* Description   | 1 round process for encryption.                          */
/****************************************************************************/
#define CRYPTO_83_SW_AES128_roundEnc(ds, ss, rk)                                                                                  \
do {                                                                                                                              \
    (ds)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_0] =                                                                           \
        Crypto_83_sw_AES128_unLutMc02_01_01_03[(ss)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_0]].u32 ^ \
        Crypto_83_sw_AES128_unLutMc03_02_01_01[(ss)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_1]].u32 ^ \
        Crypto_83_sw_AES128_unLutMc01_03_02_01[(ss)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_2]].u32 ^ \
        Crypto_83_sw_AES128_unLutMc01_01_03_02[(ss)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_3]].u32 ^ \
        (rk)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_0];                                                                        \
    (ds)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_1] =                                                                           \
        Crypto_83_sw_AES128_unLutMc02_01_01_03[(ss)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_0]].u32 ^ \
        Crypto_83_sw_AES128_unLutMc03_02_01_01[(ss)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_1]].u32 ^ \
        Crypto_83_sw_AES128_unLutMc01_03_02_01[(ss)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_2]].u32 ^ \
        Crypto_83_sw_AES128_unLutMc01_01_03_02[(ss)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_3]].u32 ^ \
        (rk)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_1];                                                                        \
    (ds)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_2] =                                                                           \
        Crypto_83_sw_AES128_unLutMc02_01_01_03[(ss)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_0]].u32 ^ \
        Crypto_83_sw_AES128_unLutMc03_02_01_01[(ss)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_1]].u32 ^ \
        Crypto_83_sw_AES128_unLutMc01_03_02_01[(ss)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_2]].u32 ^ \
        Crypto_83_sw_AES128_unLutMc01_01_03_02[(ss)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_3]].u32 ^ \
        (rk)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_2];                                                                        \
    (ds)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_3] =                                                                           \
        Crypto_83_sw_AES128_unLutMc02_01_01_03[(ss)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_0]].u32 ^ \
        Crypto_83_sw_AES128_unLutMc03_02_01_01[(ss)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_1]].u32 ^ \
        Crypto_83_sw_AES128_unLutMc01_03_02_01[(ss)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_2]].u32 ^ \
        Crypto_83_sw_AES128_unLutMc01_01_03_02[(ss)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_3]].u32 ^ \
        (rk)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_3];                                                                        \
} while( 0 )

/****************************************************************************/
/* Macro Name    | CRYPTO_83_SW_AES128_InvSbInvSr                           */
/* Description   | Inversed ByteSub - Inversed ShiftRow                     */
/****************************************************************************/
#define CRYPTO_83_SW_AES128_InvSbInvSr(dstState, srcState)                                                                  \
do {                                                                                                                        \
    (dstState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_0] =                                     \
        CRYPTO_83_SW_AES128_invSubBytes((srcState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_0]); \
    (dstState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_1] =                                     \
        CRYPTO_83_SW_AES128_invSubBytes((srcState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_1]); \
    (dstState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_2] =                                     \
        CRYPTO_83_SW_AES128_invSubBytes((srcState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_2]); \
    (dstState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_3] =                                     \
        CRYPTO_83_SW_AES128_invSubBytes((srcState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_3]); \
    (dstState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_0] =                                     \
        CRYPTO_83_SW_AES128_invSubBytes((srcState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_0]); \
    (dstState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_1] =                                     \
        CRYPTO_83_SW_AES128_invSubBytes((srcState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_1]); \
    (dstState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_2] =                                     \
        CRYPTO_83_SW_AES128_invSubBytes((srcState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_2]); \
    (dstState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_3] =                                     \
        CRYPTO_83_SW_AES128_invSubBytes((srcState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_3]); \
    (dstState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_0] =                                     \
        CRYPTO_83_SW_AES128_invSubBytes((srcState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_0]); \
    (dstState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_1] =                                     \
        CRYPTO_83_SW_AES128_invSubBytes((srcState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_1]); \
    (dstState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_2] =                                     \
        CRYPTO_83_SW_AES128_invSubBytes((srcState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_2]); \
    (dstState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_3] =                                     \
        CRYPTO_83_SW_AES128_invSubBytes((srcState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_3]); \
    (dstState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_0] =                                     \
        CRYPTO_83_SW_AES128_invSubBytes((srcState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_0]); \
    (dstState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_1] =                                     \
        CRYPTO_83_SW_AES128_invSubBytes((srcState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_1]); \
    (dstState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_2] =                                     \
        CRYPTO_83_SW_AES128_invSubBytes((srcState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_2]); \
    (dstState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_3] =                                     \
        CRYPTO_83_SW_AES128_invSubBytes((srcState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_3]); \
} while( 0 )

/****************************************************************************/
/* Macro Name    | CRYPTO_83_SW_AES128_InvMixColumn                         */
/* Description   | Process inversed mix columns.                            */
/****************************************************************************/
#define CRYPTO_83_SW_AES128_InvMixColumn(dstState, srcState)                                                                   \
do {                                                                                                                           \
    (dstState)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_0] =                                                                  \
    Crypto_83_sw_AES128_unLut0E090D0B[(srcState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_0]].u32 ^ \
    Crypto_83_sw_AES128_unLut0B0E090D[(srcState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_1]].u32 ^ \
    Crypto_83_sw_AES128_unLut0D0B0E09[(srcState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_2]].u32 ^ \
    Crypto_83_sw_AES128_unLut090D0B0E[(srcState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_3]].u32;  \
    (dstState)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_1] =                                                                  \
    Crypto_83_sw_AES128_unLut0E090D0B[(srcState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_0]].u32 ^ \
    Crypto_83_sw_AES128_unLut0B0E090D[(srcState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_1]].u32 ^ \
    Crypto_83_sw_AES128_unLut0D0B0E09[(srcState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_2]].u32 ^ \
    Crypto_83_sw_AES128_unLut090D0B0E[(srcState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_3]].u32;  \
    (dstState)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_2] =                                                                  \
    Crypto_83_sw_AES128_unLut0E090D0B[(srcState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_0]].u32 ^ \
    Crypto_83_sw_AES128_unLut0B0E090D[(srcState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_1]].u32 ^ \
    Crypto_83_sw_AES128_unLut0D0B0E09[(srcState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_2]].u32 ^ \
    Crypto_83_sw_AES128_unLut090D0B0E[(srcState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_3]].u32;  \
    (dstState)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_3] =                                                                  \
    Crypto_83_sw_AES128_unLut0E090D0B[(srcState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_0]].u32 ^ \
    Crypto_83_sw_AES128_unLut0B0E090D[(srcState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_1]].u32 ^ \
    Crypto_83_sw_AES128_unLut0D0B0E09[(srcState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_2]].u32 ^ \
    Crypto_83_sw_AES128_unLut090D0B0E[(srcState)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_3]].u32;  \
} while( 0 )

/****************************************************************************/
/* Macro Name    | CRYPTO_83_SW_AES128_roundDec                             */
/* Description   | 1 round process for decryption.                          */
/* Parameter(s)  | ctx  : Pointer to the context buffer                     */
/*               | tmp  : Pointer to the work buffer(type=context buffer)   */
/*               | round: Number of round                                   */
/****************************************************************************/
#define CRYPTO_83_SW_AES128_roundDec(ctx, tmp, round)                        \
do {                                                                         \
    CRYPTO_83_SW_AES128_InvSbInvSr((tmp), &(ctx)->unState);                  \
    CRYPTO_83_SW_AES128_blockXor32((tmp), (tmp), &(ctx)->unRoundKey[round]); \
    CRYPTO_83_SW_AES128_InvMixColumn(&(ctx)->unState, (tmp));                \
} while( 0 )

/****************************************************************************/
/* Macro Name    | CRYPTO_83_SW_AES128_Ecb_encLastFunc                      */
/* Description   | Final round process for encryption.                      */
/****************************************************************************/
#define CRYPTO_83_SW_AES128_Ecb_encLastFunc(dst, src, r)                                                    \
do {                                                                                                        \
    CRYPTO_83_SW_AES128_shiftRow0((src),                                                                    \
        (dst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_0],                       \
        (dst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_1],                       \
        (dst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_2],                       \
        (dst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_3]);                      \
    CRYPTO_83_SW_AES128_shiftRow1((src),                                                                    \
        (dst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_0],                       \
        (dst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_1],                       \
        (dst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_2],                       \
        (dst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_1][CRYPTO_83_SW_AES128_COL_3]);                      \
    CRYPTO_83_SW_AES128_shiftRow2((src),                                                                    \
        (dst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_0],                       \
        (dst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_1],                       \
        (dst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_2],                       \
        (dst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_2][CRYPTO_83_SW_AES128_COL_3]);                      \
    CRYPTO_83_SW_AES128_shiftRow3((src),                                                                    \
        (dst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_0],                       \
        (dst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_1],                       \
        (dst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_2],                       \
        (dst)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_3]);                      \
                                                                                                            \
    /* AddRoundKey & Store result */                                                                        \
    (dst)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_0] ^= (r)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_0]; \
    (dst)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_1] ^= (r)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_1]; \
    (dst)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_2] ^= (r)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_2]; \
    (dst)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_3] ^= (r)->u4CryptBufUint32[CRYPTO_83_SW_AES128_ROW_3]; \
} while( 0 )

/****************************************************************************/
/* Macro Name    | CRYPTO_83_SW_AES128_Ecb_decLastFunc                      */
/* Description   | Final round process for decryption.                      */
/****************************************************************************/
#define CRYPTO_83_SW_AES128_Ecb_decLastFunc(ctx, work)                                                      \
do {                                                                                                        \
    CRYPTO_83_SW_AES128_InvSbInvSr((work), &(ctx)->unState);                                                \
    CRYPTO_83_SW_AES128_blockXor32(&(ctx)->unState, (work), &(ctx)->unRoundKey[CRYPTO_83_SW_AES128_ROW_0]); \
} while( 0 )

/****************************************************************************/
/* Macro Name    | CRYPTO_83_SW_AES128_EcbEnc                               */
/* Description   | 10 Round process for encryption.                         */
/****************************************************************************/
#define CRYPTO_83_SW_AES128_EcbEnc(ctx, tmp)                                                                     \
do {                                                                                                             \
    CRYPTO_83_SW_AES128_addRoundKey(ctx, CRYPTO_83_SW_AES128_ROUND_0);                                           \
    CRYPTO_83_SW_AES128_roundEnc((tmp), &(ctx)->unState, &(ctx)->unRoundKey[CRYPTO_83_SW_AES128_ROW_1]);         \
    CRYPTO_83_SW_AES128_roundEnc(&(ctx)->unState, (tmp), &(ctx)->unRoundKey[CRYPTO_83_SW_AES128_ROW_2]);         \
    CRYPTO_83_SW_AES128_roundEnc((tmp), &(ctx)->unState, &(ctx)->unRoundKey[CRYPTO_83_SW_AES128_ROW_3]);         \
    CRYPTO_83_SW_AES128_roundEnc(&(ctx)->unState, (tmp), &(ctx)->unRoundKey[CRYPTO_83_SW_AES128_ROW_4]);         \
    CRYPTO_83_SW_AES128_roundEnc((tmp), &(ctx)->unState, &(ctx)->unRoundKey[CRYPTO_83_SW_AES128_ROW_5]);         \
    CRYPTO_83_SW_AES128_roundEnc(&(ctx)->unState, (tmp), &(ctx)->unRoundKey[CRYPTO_83_SW_AES128_ROW_6]);         \
    CRYPTO_83_SW_AES128_roundEnc((tmp), &(ctx)->unState, &(ctx)->unRoundKey[CRYPTO_83_SW_AES128_ROW_7]);         \
    CRYPTO_83_SW_AES128_roundEnc(&(ctx)->unState, (tmp), &(ctx)->unRoundKey[CRYPTO_83_SW_AES128_ROW_8]);         \
    CRYPTO_83_SW_AES128_roundEnc((tmp), &(ctx)->unState, &(ctx)->unRoundKey[CRYPTO_83_SW_AES128_ROW_9]);         \
    CRYPTO_83_SW_AES128_Ecb_encLastFunc(&(ctx)->unState, (tmp), &(ctx)->unRoundKey[CRYPTO_83_SW_AES128_ROW_10]); \
} while( 0 )


/****************************************************************************/
/* Macro Name    | CRYPTO_83_SW_AES128_EcbDec                               */
/* Description   | 10 Round process for decryption.                         */
/****************************************************************************/
#define CRYPTO_83_SW_AES128_EcbDec(ctx, tmp)                                 \
do {                                                                         \
    CRYPTO_83_SW_AES128_addRoundKey((ctx), CRYPTO_83_SW_AES128_ROUND_10);    \
    CRYPTO_83_SW_AES128_roundDec((ctx), (tmp), CRYPTO_83_SW_AES128_ROUND_9); \
    CRYPTO_83_SW_AES128_roundDec((ctx), (tmp), CRYPTO_83_SW_AES128_ROUND_8); \
    CRYPTO_83_SW_AES128_roundDec((ctx), (tmp), CRYPTO_83_SW_AES128_ROUND_7); \
    CRYPTO_83_SW_AES128_roundDec((ctx), (tmp), CRYPTO_83_SW_AES128_ROUND_6); \
    CRYPTO_83_SW_AES128_roundDec((ctx), (tmp), CRYPTO_83_SW_AES128_ROUND_5); \
    CRYPTO_83_SW_AES128_roundDec((ctx), (tmp), CRYPTO_83_SW_AES128_ROUND_4); \
    CRYPTO_83_SW_AES128_roundDec((ctx), (tmp), CRYPTO_83_SW_AES128_ROUND_3); \
    CRYPTO_83_SW_AES128_roundDec((ctx), (tmp), CRYPTO_83_SW_AES128_ROUND_2); \
    CRYPTO_83_SW_AES128_roundDec((ctx), (tmp), CRYPTO_83_SW_AES128_ROUND_1); \
    CRYPTO_83_SW_AES128_Ecb_decLastFunc((ctx), (tmp));                       \
} while( 0 )

/****************************************************************************/
/* Macro Name    | CRYPTO_83_SW_AES128_updateSubkey                         */
/* Description   | Generate subkey.                                         */
/*               | Caller declare "u4_flagSubKey" in advance.               */
/****************************************************************************/
#define CRYPTO_83_SW_AES128_updateSubkey(subKey, baseKey)                                                                                        \
do {                                                                                                                                             \
    u4_flagSubKey = (uint32)(baseKey)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_0][CRYPTO_83_SW_AES128_COL_0] & (uint32)CRYPTO_83_SW_AES128_BIT7; \
    CRYPTO_83_SW_AES128_blockShiftLeft((subKey), (baseKey));                                                                                     \
    if (u4_flagSubKey != 0UL) {                                                                                                                  \
        (subKey)->u1CryptBufUint8[CRYPTO_83_SW_AES128_ROW_3][CRYPTO_83_SW_AES128_COL_3] ^= CRYPTO_83_SW_AES128_SUBKEY_RB;                        \
    }                                                                                                                                            \
} while( 0 )

/****************************************************************************/
/* Macro Name    | CRYPTO_83_SW_AES128_Iso9797_PadM2                        */
/* Description   | Padding by ISO9797 method-2, src data to dst.            */
/****************************************************************************/
#define CRYPTO_83_SW_AES128_Iso9797_PadM2(dst, src, len)                     \
do {                                                                         \
    CRYPTO_83_SW_AES128_blockClear(dst);                                     \
    pt_Dst = (uint8*)(dst);                                                  \
    pt_Src = (const uint8*)(src);                                            \
    for (u4_count = 0U; u4_count < (len); u4_count++) {                      \
        pt_Dst[u4_count] = pt_Src[u4_count];                                 \
    }                                                                        \
    pt_Dst[u4_count] = CRYPTO_83_SW_AES128_PADM2;                            \
} while( 0 )

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

void Crypto_83_sw_AES128_EcbCtxBufErase
(
    Crypto_83_sw_AES128_Ecb_CtxBufType *ptEcbCtxBuf
);

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif  /* CRYPTO_83_SW_AES128_MACRO_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2023/01/16                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
