/* E2E_Local_Common_h_v2-1-0                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name      | E2E/E2E_Local_Common/HEADER                           */
/*--------------------------------------------------------------------------*/
/* Notes            |                                                       */
/****************************************************************************/

#ifndef E2E_LOCAL_COMMON_H
#define E2E_LOCAL_COMMON_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define E2E_USE_SHIFT_DIV_8             (3U)
#define E2E_U4_BIT_SHIFT_1              ((uint32)1UL)
#define E2E_U2_BIT_SHIFT_3              ((uint16)3U)
#define E2E_U1_BIT_SHIFT_4              ((uint8)4U)
#define E2E_BIT_SHIFT_8                 (8U)
#define E2E_U4_BIT_SHIFT_16             ((uint32)16UL)
#define E2E_U4_BIT_SHIFT_24             ((uint32)24UL)
#define E2E_U1_MASK_HIGH_NIBBLE         ((uint8)0xF0U)
#define E2E_U1_MASK_LOW_NIBBLE          ((uint8)0x0FU)
#define E2E_MASK_BYTE                   (0xFFU)
#define E2E_REMAINDER_ZERO              (0U)
#define E2E_U2_DATALEN_ZERO             ((uint16)0U)
#define E2E_U2_OFFSET_INVALID           ((uint16)0U)
#define E2E_U1_SYNC_COUNTER_NUM_ZERO    ((uint8)0U)
#define E2E_DELTA_COUNTER_NUM_ZERO      (0U)
#define E2E_DELTA_COUNTER_NUM_ONE       (1U)
#define E2E_U2_ARRAY_INDEX_ONE          ((uint16)1U)
#define E2E_U2_ARRAY_INDEX_TWO          ((uint16)2U)
#define E2E_U2_ARRAY_INDEX_THREE        ((uint16)3U)
#define E2E_DATAID_ZERO_VALUE           (0U)
#define E2E_OFFSET_INIT_VALUE           (0U)
#define E2E_U1_MASK_MULTIPLE2           ((uint8)0x1U)
#define E2E_U2_MASK_MULTIPLE4           ((uint16)0x3U)
#define E2E_U2_MASK_MULTIPLE8           ((uint16)0x7U)
#define E2E_DELTA_COUNTER_WRAP_AROUND   (1U)

/* for profile07 */
#define E2E_U4_BIT_SHIFT_3              ((uint32)3UL)
#define E2E_U4_ARRAY_INDEX_ONE          ((uint32)1UL)
#define E2E_U4_ARRAY_INDEX_TWO          ((uint32)2UL)
#define E2E_U4_ARRAY_INDEX_THREE        ((uint32)3UL)
#define E2E_U4_ARRAY_INDEX_FOUR         ((uint32)4UL)
#define E2E_U4_ARRAY_INDEX_FIVE         ((uint32)5UL)
#define E2E_U4_ARRAY_INDEX_SIX          ((uint32)6UL)
#define E2E_U4_ARRAY_INDEX_SEVEN        ((uint32)7UL)

#define E2E_U8_BIT_SHIFT_16             ((uint64)16ULL)
#define E2E_U8_BIT_SHIFT_24             ((uint64)24ULL)
#define E2E_U8_BIT_SHIFT_32             ((uint64)32ULL)
#define E2E_U8_BIT_SHIFT_40             ((uint64)40ULL)
#define E2E_U8_BIT_SHIFT_48             ((uint64)48ULL)
#define E2E_U8_BIT_SHIFT_56             ((uint64)56ULL)

#define E2E_U4_DATALEN_ZERO             ((uint32)0UL)
#define E2E_U4_OFFSET_INVALID           ((uint32)0UL)
#define E2E_U4_MASK_MULTIPLE8           ((uint32)0x7UL)
/* for profile07 */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* E2E_LOCAL_COMMON_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-1-0         :2022/06/03                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
