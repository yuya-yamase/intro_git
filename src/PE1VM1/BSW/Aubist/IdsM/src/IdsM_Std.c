/* IdsM_Std_c_v2-0-2                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | IdsM/Std/CODE                                              */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <IdsM.h>
#include "../inc/IdsM_Cfg_Fixed.h"
#include "../inc/IdsM_Std.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#if ((IDSM_CFG_USE_DEM == STD_ON) || ( IDSM_CFG_USE_CTXDATA == STD_ON ))
#define IDSM_BLOCK32   ((uint16)32U)
#define IDSM_BLOCK16   ((uint16)16U)
#define IDSM_BLOCK4    ((uint16)4U)

#define IDSM_ALIGN_MSK (3UL)

#define IDSM_MEM_POS0   (0U)
#define IDSM_MEM_POS1   (1U)
#define IDSM_MEM_POS2   (2U)
#define IDSM_MEM_POS3   (3U)
#define IDSM_MEM_POS4   (4U)
#define IDSM_MEM_POS5   (5U)
#define IDSM_MEM_POS6   (6U)
#define IDSM_MEM_POS7   (7U)
#define IDSM_MEM_POS8   (8U)
#define IDSM_MEM_POS9   (9U)
#define IDSM_MEM_POS10 (10U)
#define IDSM_MEM_POS11 (11U)
#define IDSM_MEM_POS12 (12U)
#define IDSM_MEM_POS13 (13U)
#define IDSM_MEM_POS14 (14U)
#define IDSM_MEM_POS15 (15U)
#define IDSM_MEM_POS16 (16U)
#define IDSM_MEM_POS17 (17U)
#define IDSM_MEM_POS18 (18U)
#define IDSM_MEM_POS19 (19U)
#define IDSM_MEM_POS20 (20U)
#define IDSM_MEM_POS21 (21U)
#define IDSM_MEM_POS22 (22U)
#define IDSM_MEM_POS23 (23U)
#define IDSM_MEM_POS24 (24U)
#define IDSM_MEM_POS25 (25U)
#define IDSM_MEM_POS26 (26U)
#define IDSM_MEM_POS27 (27U)
#define IDSM_MEM_POS28 (28U)
#define IDSM_MEM_POS29 (29U)
#define IDSM_MEM_POS30 (30U)
#define IDSM_MEM_POS31 (31U)
#define IDSM_MEM_POS32 (32U)

#endif  /* ((IDSM_CFG_USE_DEM == STD_ON) || ( IDSM_CFG_USE_CTXDATA == STD_ON )) */

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

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define IDSM_START_SEC_CODE
#include <IdsM_MemMap.h>

#if ((IDSM_CFG_USE_DEM == STD_ON) || ( IDSM_CFG_USE_CTXDATA == STD_ON ))
/****************************************************************************/
/* Function Name | IdsM_Std_MemCpy                                          */
/* Description   | memory copy                                              */
/* Preconditions |                                                          */
/* Parameters    | ptDst : output address                                   */
/*               | ptSrc : input address                                    */
/*               | u2Size : byte size                                       */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_Std_MemCpy
(
    P2VAR(volatile void, AUTOMATIC, AUTOMATIC) ptDst,
    P2CONST(volatile void, AUTOMATIC, AUTOMATIC) ptSrc,
    uint16 u2Size
)
{
    P2VAR(volatile uint32, AUTOMATIC, AUTOMATIC)   pt_u4Dst;
    P2CONST(volatile uint32, AUTOMATIC, AUTOMATIC) pt_u4Src;
    P2VAR(volatile uint8, AUTOMATIC, AUTOMATIC)    pt_u1Dst;
    P2CONST(volatile uint8, AUTOMATIC, AUTOMATIC)  pt_u1Src;
    uint16  u2_remainSize;
    uint16  u2_Index;

    pt_u4Dst = (volatile uint32*)ptDst;
    pt_u4Src = (const volatile uint32*)ptSrc;

    u2_remainSize = u2Size;

    if(  (((uint32)pt_u4Dst & IDSM_ALIGN_MSK) == 0UL)
      && (((uint32)pt_u4Src & IDSM_ALIGN_MSK) == 0UL) )
    {
        while( u2_remainSize >= IDSM_BLOCK32 )
        {
            pt_u4Dst[IDSM_MEM_POS0] = pt_u4Src[IDSM_MEM_POS0];
            pt_u4Dst[IDSM_MEM_POS1] = pt_u4Src[IDSM_MEM_POS1];
            pt_u4Dst[IDSM_MEM_POS2] = pt_u4Src[IDSM_MEM_POS2];
            pt_u4Dst[IDSM_MEM_POS3] = pt_u4Src[IDSM_MEM_POS3];
            pt_u4Dst[IDSM_MEM_POS4] = pt_u4Src[IDSM_MEM_POS4];
            pt_u4Dst[IDSM_MEM_POS5] = pt_u4Src[IDSM_MEM_POS5];
            pt_u4Dst[IDSM_MEM_POS6] = pt_u4Src[IDSM_MEM_POS6];
            pt_u4Dst[IDSM_MEM_POS7] = pt_u4Src[IDSM_MEM_POS7];

            pt_u4Dst = &pt_u4Dst[IDSM_MEM_POS8];
            pt_u4Src = &pt_u4Src[IDSM_MEM_POS8];
            u2_remainSize -= IDSM_BLOCK32;
        }
        if( u2_remainSize >= IDSM_BLOCK16 )
        {
            pt_u4Dst[IDSM_MEM_POS0] = pt_u4Src[IDSM_MEM_POS0];
            pt_u4Dst[IDSM_MEM_POS1] = pt_u4Src[IDSM_MEM_POS1];
            pt_u4Dst[IDSM_MEM_POS2] = pt_u4Src[IDSM_MEM_POS2];
            pt_u4Dst[IDSM_MEM_POS3] = pt_u4Src[IDSM_MEM_POS3];

            pt_u4Dst = &pt_u4Dst[IDSM_MEM_POS4];
            pt_u4Src = &pt_u4Src[IDSM_MEM_POS4];
            u2_remainSize -= IDSM_BLOCK16;
        }
        while( u2_remainSize >= IDSM_BLOCK4 )
        {
            pt_u4Dst[IDSM_MEM_POS0] = pt_u4Src[IDSM_MEM_POS0];

            pt_u4Dst = &pt_u4Dst[IDSM_MEM_POS1];
            pt_u4Src = &pt_u4Src[IDSM_MEM_POS1];
            u2_remainSize -= IDSM_BLOCK4;
        }

        pt_u1Dst = (volatile uint8*)pt_u4Dst;
        pt_u1Src = (const volatile uint8*)pt_u4Src;
    }
    else {
        pt_u1Dst = (volatile uint8*)ptDst;
        pt_u1Src = (const volatile uint8*)ptSrc;

        while( u2_remainSize >= IDSM_BLOCK32 )
        {
            pt_u1Dst[IDSM_MEM_POS0]  = pt_u1Src[IDSM_MEM_POS0];
            pt_u1Dst[IDSM_MEM_POS1]  = pt_u1Src[IDSM_MEM_POS1];
            pt_u1Dst[IDSM_MEM_POS2]  = pt_u1Src[IDSM_MEM_POS2];
            pt_u1Dst[IDSM_MEM_POS3]  = pt_u1Src[IDSM_MEM_POS3];
            pt_u1Dst[IDSM_MEM_POS4]  = pt_u1Src[IDSM_MEM_POS4];
            pt_u1Dst[IDSM_MEM_POS5]  = pt_u1Src[IDSM_MEM_POS5];
            pt_u1Dst[IDSM_MEM_POS6]  = pt_u1Src[IDSM_MEM_POS6];
            pt_u1Dst[IDSM_MEM_POS7]  = pt_u1Src[IDSM_MEM_POS7];
            pt_u1Dst[IDSM_MEM_POS8]  = pt_u1Src[IDSM_MEM_POS8];
            pt_u1Dst[IDSM_MEM_POS9]  = pt_u1Src[IDSM_MEM_POS9];
            pt_u1Dst[IDSM_MEM_POS10] = pt_u1Src[IDSM_MEM_POS10];
            pt_u1Dst[IDSM_MEM_POS11] = pt_u1Src[IDSM_MEM_POS11];
            pt_u1Dst[IDSM_MEM_POS12] = pt_u1Src[IDSM_MEM_POS12];
            pt_u1Dst[IDSM_MEM_POS13] = pt_u1Src[IDSM_MEM_POS13];
            pt_u1Dst[IDSM_MEM_POS14] = pt_u1Src[IDSM_MEM_POS14];
            pt_u1Dst[IDSM_MEM_POS15] = pt_u1Src[IDSM_MEM_POS15];
            pt_u1Dst[IDSM_MEM_POS16] = pt_u1Src[IDSM_MEM_POS16];
            pt_u1Dst[IDSM_MEM_POS17] = pt_u1Src[IDSM_MEM_POS17];
            pt_u1Dst[IDSM_MEM_POS18] = pt_u1Src[IDSM_MEM_POS18];
            pt_u1Dst[IDSM_MEM_POS19] = pt_u1Src[IDSM_MEM_POS19];
            pt_u1Dst[IDSM_MEM_POS20] = pt_u1Src[IDSM_MEM_POS20];
            pt_u1Dst[IDSM_MEM_POS21] = pt_u1Src[IDSM_MEM_POS21];
            pt_u1Dst[IDSM_MEM_POS22] = pt_u1Src[IDSM_MEM_POS22];
            pt_u1Dst[IDSM_MEM_POS23] = pt_u1Src[IDSM_MEM_POS23];
            pt_u1Dst[IDSM_MEM_POS24] = pt_u1Src[IDSM_MEM_POS24];
            pt_u1Dst[IDSM_MEM_POS25] = pt_u1Src[IDSM_MEM_POS25];
            pt_u1Dst[IDSM_MEM_POS26] = pt_u1Src[IDSM_MEM_POS26];
            pt_u1Dst[IDSM_MEM_POS27] = pt_u1Src[IDSM_MEM_POS27];
            pt_u1Dst[IDSM_MEM_POS28] = pt_u1Src[IDSM_MEM_POS28];
            pt_u1Dst[IDSM_MEM_POS29] = pt_u1Src[IDSM_MEM_POS29];
            pt_u1Dst[IDSM_MEM_POS30] = pt_u1Src[IDSM_MEM_POS30];
            pt_u1Dst[IDSM_MEM_POS31] = pt_u1Src[IDSM_MEM_POS31];

            pt_u1Dst = &pt_u1Dst[IDSM_MEM_POS32];
            pt_u1Src = &pt_u1Src[IDSM_MEM_POS32];

            u2_remainSize -= IDSM_BLOCK32;
        }
        if( u2_remainSize >= IDSM_BLOCK16 )
        {
            pt_u1Dst[IDSM_MEM_POS0]  = pt_u1Src[IDSM_MEM_POS0];
            pt_u1Dst[IDSM_MEM_POS1]  = pt_u1Src[IDSM_MEM_POS1];
            pt_u1Dst[IDSM_MEM_POS2]  = pt_u1Src[IDSM_MEM_POS2];
            pt_u1Dst[IDSM_MEM_POS3]  = pt_u1Src[IDSM_MEM_POS3];
            pt_u1Dst[IDSM_MEM_POS4]  = pt_u1Src[IDSM_MEM_POS4];
            pt_u1Dst[IDSM_MEM_POS5]  = pt_u1Src[IDSM_MEM_POS5];
            pt_u1Dst[IDSM_MEM_POS6]  = pt_u1Src[IDSM_MEM_POS6];
            pt_u1Dst[IDSM_MEM_POS7]  = pt_u1Src[IDSM_MEM_POS7];
            pt_u1Dst[IDSM_MEM_POS8]  = pt_u1Src[IDSM_MEM_POS8];
            pt_u1Dst[IDSM_MEM_POS9]  = pt_u1Src[IDSM_MEM_POS9];
            pt_u1Dst[IDSM_MEM_POS10] = pt_u1Src[IDSM_MEM_POS10];
            pt_u1Dst[IDSM_MEM_POS11] = pt_u1Src[IDSM_MEM_POS11];
            pt_u1Dst[IDSM_MEM_POS12] = pt_u1Src[IDSM_MEM_POS12];
            pt_u1Dst[IDSM_MEM_POS13] = pt_u1Src[IDSM_MEM_POS13];
            pt_u1Dst[IDSM_MEM_POS14] = pt_u1Src[IDSM_MEM_POS14];
            pt_u1Dst[IDSM_MEM_POS15] = pt_u1Src[IDSM_MEM_POS15];

            pt_u1Dst = &pt_u1Dst[IDSM_MEM_POS16];
            pt_u1Src = &pt_u1Src[IDSM_MEM_POS16];
            u2_remainSize -= IDSM_BLOCK16;
        }
        while( u2_remainSize >= IDSM_BLOCK4 )
        {
            pt_u1Dst[IDSM_MEM_POS0] = pt_u1Src[IDSM_MEM_POS0];
            pt_u1Dst[IDSM_MEM_POS1] = pt_u1Src[IDSM_MEM_POS1];
            pt_u1Dst[IDSM_MEM_POS2] = pt_u1Src[IDSM_MEM_POS2];
            pt_u1Dst[IDSM_MEM_POS3] = pt_u1Src[IDSM_MEM_POS3];

            pt_u1Dst = &pt_u1Dst[IDSM_MEM_POS4];
            pt_u1Src = &pt_u1Src[IDSM_MEM_POS4];
            u2_remainSize -= IDSM_BLOCK4;
        }
    }

    for ( u2_Index = 0U; u2_Index < u2_remainSize; u2_Index++ )
    {
        pt_u1Dst[u2_Index] = pt_u1Src[u2_Index];
    }

    return;
}
#endif  /* ((IDSM_CFG_USE_DEM == STD_ON) || ( IDSM_CFG_USE_CTXDATA == STD_ON )) */

#if(IDSM_CFG_DEM_BUFF_PADDING == STD_ON)
/****************************************************************************/
/* Function Name | IdsM_Std_MemSet                                          */
/* Description   | memory set                                               */
/* Preconditions |                                                          */
/* Parameters    | ptDst : output address                                   */
/*               | u1Src : input value                                      */
/*               | u2Size : byte size                                       */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_Std_MemSet
(
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) ptDst,
    uint8 u1Src,
    uint16 u2Size
)
{
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) pt_u1Dst;
    uint16  u2_remainSize;
    uint16  u2_Index;

    u2_remainSize = u2Size;
    pt_u1Dst = ptDst;

    while( u2_remainSize >= IDSM_BLOCK32 )
    {
        pt_u1Dst[IDSM_MEM_POS0]  = u1Src;
        pt_u1Dst[IDSM_MEM_POS1]  = u1Src;
        pt_u1Dst[IDSM_MEM_POS2]  = u1Src;
        pt_u1Dst[IDSM_MEM_POS3]  = u1Src;
        pt_u1Dst[IDSM_MEM_POS4]  = u1Src;
        pt_u1Dst[IDSM_MEM_POS5]  = u1Src;
        pt_u1Dst[IDSM_MEM_POS6]  = u1Src;
        pt_u1Dst[IDSM_MEM_POS7]  = u1Src;
        pt_u1Dst[IDSM_MEM_POS8]  = u1Src;
        pt_u1Dst[IDSM_MEM_POS9]  = u1Src;
        pt_u1Dst[IDSM_MEM_POS10] = u1Src;
        pt_u1Dst[IDSM_MEM_POS11] = u1Src;
        pt_u1Dst[IDSM_MEM_POS12] = u1Src;
        pt_u1Dst[IDSM_MEM_POS13] = u1Src;
        pt_u1Dst[IDSM_MEM_POS14] = u1Src;
        pt_u1Dst[IDSM_MEM_POS15] = u1Src;
        pt_u1Dst[IDSM_MEM_POS16] = u1Src;
        pt_u1Dst[IDSM_MEM_POS17] = u1Src;
        pt_u1Dst[IDSM_MEM_POS18] = u1Src;
        pt_u1Dst[IDSM_MEM_POS19] = u1Src;
        pt_u1Dst[IDSM_MEM_POS20] = u1Src;
        pt_u1Dst[IDSM_MEM_POS21] = u1Src;
        pt_u1Dst[IDSM_MEM_POS22] = u1Src;
        pt_u1Dst[IDSM_MEM_POS23] = u1Src;
        pt_u1Dst[IDSM_MEM_POS24] = u1Src;
        pt_u1Dst[IDSM_MEM_POS25] = u1Src;
        pt_u1Dst[IDSM_MEM_POS26] = u1Src;
        pt_u1Dst[IDSM_MEM_POS27] = u1Src;
        pt_u1Dst[IDSM_MEM_POS28] = u1Src;
        pt_u1Dst[IDSM_MEM_POS29] = u1Src;
        pt_u1Dst[IDSM_MEM_POS30] = u1Src;
        pt_u1Dst[IDSM_MEM_POS31] = u1Src;

        pt_u1Dst = &pt_u1Dst[IDSM_MEM_POS32];
        u2_remainSize -= IDSM_BLOCK32;
    }
    if( u2_remainSize >= IDSM_BLOCK16 )
    {
        pt_u1Dst[IDSM_MEM_POS0]  = u1Src;
        pt_u1Dst[IDSM_MEM_POS1]  = u1Src;
        pt_u1Dst[IDSM_MEM_POS2]  = u1Src;
        pt_u1Dst[IDSM_MEM_POS3]  = u1Src;
        pt_u1Dst[IDSM_MEM_POS4]  = u1Src;
        pt_u1Dst[IDSM_MEM_POS5]  = u1Src;
        pt_u1Dst[IDSM_MEM_POS6]  = u1Src;
        pt_u1Dst[IDSM_MEM_POS7]  = u1Src;
        pt_u1Dst[IDSM_MEM_POS8]  = u1Src;
        pt_u1Dst[IDSM_MEM_POS9]  = u1Src;
        pt_u1Dst[IDSM_MEM_POS10] = u1Src;
        pt_u1Dst[IDSM_MEM_POS11] = u1Src;
        pt_u1Dst[IDSM_MEM_POS12] = u1Src;
        pt_u1Dst[IDSM_MEM_POS13] = u1Src;
        pt_u1Dst[IDSM_MEM_POS14] = u1Src;
        pt_u1Dst[IDSM_MEM_POS15] = u1Src;

        pt_u1Dst = &pt_u1Dst[IDSM_MEM_POS16];
        u2_remainSize -= IDSM_BLOCK16;
    }
    while( u2_remainSize >= IDSM_BLOCK4 )
    {
        pt_u1Dst[IDSM_MEM_POS0] = u1Src;
        pt_u1Dst[IDSM_MEM_POS1] = u1Src;
        pt_u1Dst[IDSM_MEM_POS2] = u1Src;
        pt_u1Dst[IDSM_MEM_POS3] = u1Src;

        pt_u1Dst = &pt_u1Dst[IDSM_MEM_POS4];
        u2_remainSize -= IDSM_BLOCK4;
    }

    for ( u2_Index = 0U; u2_Index < u2_remainSize; u2_Index++ )
    {
        pt_u1Dst[u2_Index] = u1Src;
    }

    return;
}
#endif  /* ( IDSM_CFG_DEM_BUFF_PADDING == STD_ON ) */

/****************************************************************************/
/* Function Name | IdsM_Std_EventBuffCopy                                   */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ptDst : output address                                   */
/*               | ptSrc : input address                                    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_Std_EventBuffCopy
(
    P2VAR(volatile IdsMEventBuffType, AUTOMATIC, AUTOMATIC) ptDst,
    P2CONST(volatile IdsMEventBuffType, AUTOMATIC, AUTOMATIC) ptSrc
)
{
#if ( IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE )
        ptDst->udTimestamp = ptSrc->udTimestamp;
#endif /* ( IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE ) */
        ptDst->udSEvId = ptSrc->udSEvId;
        ptDst->u2Count = ptSrc->u2Count;
#if ( IDSM_CFG_USE_CTXDATA == STD_ON )
        ptDst->u2Dummy = 0U;
        ptDst->u2CtxDataSize = ptSrc->u2CtxDataSize;
        ptDst->u2TableIndex = ptSrc->u2TableIndex;
        ptDst->u2RecordIndex = ptSrc->u2RecordIndex;
#endif /* ( IDSM_CFG_USE_CTXDATA == STD_ON ) */

    return ;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define IDSM_STOP_SEC_CODE
#include <IdsM_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version    :Date                                                        */
/*  v2-0-0     :2023/01/20                                                  */
/*  v2-0-1     :2023/02/24                                                  */
/*  v2-0-2     :2023/04/10                                                  */
/****************************************************************************/

/**** End of File ***********************************************************/
