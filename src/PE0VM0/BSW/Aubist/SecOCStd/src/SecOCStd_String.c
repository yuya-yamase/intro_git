/* SecOCStd_String_c_v2-0-0                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | SecOCStd/String/CODE                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <SecOCStd_String.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))

#define SECOCSTD_STRING_BLOCK128  (128UL)
#define SECOCSTD_STRING_BLOCK64   (64UL)

#endif

#if (((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U)) \
  || ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U)))

#define SECOCSTD_STRING_BLOCK32   (32UL)
#define SECOCSTD_STRING_BLOCK16   (16UL)
#define SECOCSTD_STRING_BLOCK4    (4UL)

#define SECOCSTD_STRING_ALIGN     (4UL)
#define SECOCSTD_STRING_ALIGN_MSK (SECOCSTD_STRING_ALIGN - 1UL)

#define SECOCSTD_STRING_NEXTINDEX  (1UL)

#endif

#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))

#define SECOCSTD_STRING_SFT8      (8UL)
#define SECOCSTD_STRING_SFT16     (16UL)

/* memset */
#define SECOCSTD_MEMSET16(p , c)            \
do {                                        \
    *(p) = (c);                             \
     (p) = &(p)[SECOCSTD_STRING_NEXTINDEX]; \
    *(p) = (c);                             \
     (p) = &(p)[SECOCSTD_STRING_NEXTINDEX]; \
    *(p) = (c);                             \
     (p) = &(p)[SECOCSTD_STRING_NEXTINDEX]; \
    *(p) = (c);                             \
     (p) = &(p)[SECOCSTD_STRING_NEXTINDEX]; \
} while ( 0 )

#endif

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
#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>


#if (((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U)) \
  || ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U)))
/****************************************************************************/
/* Function Name | SecOCStd_MemCpy                                          */
/* Description   | memory copy                                              */
/* Preconditions |                                                          */
/* Parameters    | ptDst : output address                                   */
/*               | ptSrc : input address                                    */
/*               | u4Size : byte size                                       */
/* Return Value  | output address                                           */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC_P2VAR(void, AUTOMATIC, SECOC_CODE) SecOCStd_MemCpy
(
    P2VAR(void, AUTOMATIC, SECOC_APPL_DATA) ptDst,
    P2CONST(void, AUTOMATIC, SECOC_APPL_DATA) ptSrc,
    uint32 u4Size
)
{
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) pt_u4Dst;
    P2CONST(uint32, AUTOMATIC, SECOC_APPL_DATA) pt_u4Src;
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) pt_u1Dst;
    P2CONST(uint8, AUTOMATIC, SECOC_APPL_DATA) pt_u1Src;
    uint32  u4_remainSize;
    
    pt_u4Dst = (uint32*)ptDst;
    pt_u4Src = (const uint32*)ptSrc;
    
    u4_remainSize = u4Size;
    
    if( (((uint32)pt_u4Dst & SECOCSTD_STRING_ALIGN_MSK) == 0UL) /* MISRA DEVIATION: */
      && (((uint32)pt_u4Src & SECOCSTD_STRING_ALIGN_MSK) == 0UL) ) /* MISRA DEVIATION: */
    {
        while( u4_remainSize >= SECOCSTD_STRING_BLOCK32 )
        {
            *pt_u4Dst = *pt_u4Src;
            pt_u4Dst = &pt_u4Dst[SECOCSTD_STRING_NEXTINDEX];
            pt_u4Src = &pt_u4Src[SECOCSTD_STRING_NEXTINDEX];
            *pt_u4Dst = *pt_u4Src;
            pt_u4Dst = &pt_u4Dst[SECOCSTD_STRING_NEXTINDEX];
            pt_u4Src = &pt_u4Src[SECOCSTD_STRING_NEXTINDEX];
            *pt_u4Dst = *pt_u4Src;
            pt_u4Dst = &pt_u4Dst[SECOCSTD_STRING_NEXTINDEX];
            pt_u4Src = &pt_u4Src[SECOCSTD_STRING_NEXTINDEX];
            *pt_u4Dst = *pt_u4Src;
            pt_u4Dst = &pt_u4Dst[SECOCSTD_STRING_NEXTINDEX];
            pt_u4Src = &pt_u4Src[SECOCSTD_STRING_NEXTINDEX];
            *pt_u4Dst = *pt_u4Src;
            pt_u4Dst = &pt_u4Dst[SECOCSTD_STRING_NEXTINDEX];
            pt_u4Src = &pt_u4Src[SECOCSTD_STRING_NEXTINDEX];
            *pt_u4Dst = *pt_u4Src;
            pt_u4Dst = &pt_u4Dst[SECOCSTD_STRING_NEXTINDEX];
            pt_u4Src = &pt_u4Src[SECOCSTD_STRING_NEXTINDEX];
            *pt_u4Dst = *pt_u4Src;
            pt_u4Dst = &pt_u4Dst[SECOCSTD_STRING_NEXTINDEX];
            pt_u4Src = &pt_u4Src[SECOCSTD_STRING_NEXTINDEX];
            *pt_u4Dst = *pt_u4Src;
            pt_u4Dst = &pt_u4Dst[SECOCSTD_STRING_NEXTINDEX];
            pt_u4Src = &pt_u4Src[SECOCSTD_STRING_NEXTINDEX];
            
            u4_remainSize -= SECOCSTD_STRING_BLOCK32;
        }
        if( u4_remainSize >= SECOCSTD_STRING_BLOCK16 )
        {
            *pt_u4Dst = *pt_u4Src;
            pt_u4Dst = &pt_u4Dst[SECOCSTD_STRING_NEXTINDEX];
            pt_u4Src = &pt_u4Src[SECOCSTD_STRING_NEXTINDEX];
            *pt_u4Dst = *pt_u4Src;
            pt_u4Dst = &pt_u4Dst[SECOCSTD_STRING_NEXTINDEX];
            pt_u4Src = &pt_u4Src[SECOCSTD_STRING_NEXTINDEX];
            *pt_u4Dst = *pt_u4Src;
            pt_u4Dst = &pt_u4Dst[SECOCSTD_STRING_NEXTINDEX];
            pt_u4Src = &pt_u4Src[SECOCSTD_STRING_NEXTINDEX];
            *pt_u4Dst = *pt_u4Src;
            pt_u4Dst = &pt_u4Dst[SECOCSTD_STRING_NEXTINDEX];
            pt_u4Src = &pt_u4Src[SECOCSTD_STRING_NEXTINDEX];
            
            u4_remainSize -= SECOCSTD_STRING_BLOCK16;
        }
        while( u4_remainSize >= SECOCSTD_STRING_BLOCK4 )
        {
            *pt_u4Dst = *pt_u4Src;
            pt_u4Dst = &pt_u4Dst[SECOCSTD_STRING_NEXTINDEX];
            pt_u4Src = &pt_u4Src[SECOCSTD_STRING_NEXTINDEX];
            
            u4_remainSize -= SECOCSTD_STRING_BLOCK4;
        }
    }
    
    pt_u1Dst = (uint8*)pt_u4Dst;
    pt_u1Src = (const uint8*)pt_u4Src;
    while( u4_remainSize > 0UL )
    {
        *pt_u1Dst = *pt_u1Src;
        pt_u1Dst = &pt_u1Dst[SECOCSTD_STRING_NEXTINDEX];
        pt_u1Src = &pt_u1Src[SECOCSTD_STRING_NEXTINDEX];
        
        u4_remainSize--;
    }
    
    return ptDst;
}
#endif

#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
/****************************************************************************/
/* Function Name | SecOCStd_MemSet                                          */
/* Description   | memory set                                               */
/* Preconditions |                                                          */
/* Parameters    | ptDst : output address                                   */
/*               | u1Src : input value                                      */
/*               | u4Size : byte size                                       */
/* Return Value  | output address                                           */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC_P2VAR(void, AUTOMATIC, SECOC_CODE) SecOCStd_MemSet
(
    P2VAR(void, AUTOMATIC, SECOC_APPL_DATA) ptDst,
    uint8 u1Src,
    uint32 u4Size
)
{
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) pt_u4Dst;
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) pt_u1Dst;
    P2VAR(void, AUTOMATIC, SECOC_APPL_DATA) pt_Dst;
    uint32  u4_copy;
    uint32  u4_cnt;
    uint32  u4_remainSize;
    
    /* copy data */
    u4_copy = (uint32)u1Src;
    u4_copy |= u4_copy << SECOCSTD_STRING_SFT8;
    u4_copy |= u4_copy << SECOCSTD_STRING_SFT16;
    
    pt_u4Dst = (uint32 *)ptDst;
    
    /* start address 4 byte align check */
    u4_cnt = (uint32)pt_u4Dst & SECOCSTD_STRING_ALIGN_MSK; /* MISRA DEVIATION: */
    
    u4_remainSize = u4Size;
    
    if( (u4_cnt != 0UL)
      && (u4_remainSize >= SECOCSTD_STRING_ALIGN) )
    {
        u4_cnt = SECOCSTD_STRING_ALIGN - u4_cnt;
        
        pt_u1Dst = (uint8*)ptDst;
        
        u4_remainSize -= u4_cnt;
        while( u4_cnt > 0UL )
        {
            *pt_u1Dst = u1Src;
            pt_u1Dst = &pt_u1Dst[SECOCSTD_STRING_NEXTINDEX];
            u4_cnt--;
        }
        
        pt_Dst = (void*)pt_u1Dst;
        pt_u4Dst = (uint32*)pt_Dst;
    }
    
    while( u4_remainSize >= SECOCSTD_STRING_BLOCK128 )
    {
        SECOCSTD_MEMSET16( pt_u4Dst, u4_copy );
        SECOCSTD_MEMSET16( pt_u4Dst, u4_copy );
        SECOCSTD_MEMSET16( pt_u4Dst, u4_copy );
        SECOCSTD_MEMSET16( pt_u4Dst, u4_copy );
        SECOCSTD_MEMSET16( pt_u4Dst, u4_copy );
        SECOCSTD_MEMSET16( pt_u4Dst, u4_copy );
        SECOCSTD_MEMSET16( pt_u4Dst, u4_copy );
        SECOCSTD_MEMSET16( pt_u4Dst, u4_copy );
        
        u4_remainSize -= SECOCSTD_STRING_BLOCK128;
    }
    if( u4_remainSize >= SECOCSTD_STRING_BLOCK64 )
    {
        SECOCSTD_MEMSET16( pt_u4Dst, u4_copy );
        SECOCSTD_MEMSET16( pt_u4Dst, u4_copy );
        SECOCSTD_MEMSET16( pt_u4Dst, u4_copy );
        SECOCSTD_MEMSET16( pt_u4Dst, u4_copy );
        
        u4_remainSize -= SECOCSTD_STRING_BLOCK64;
    }
    if( u4_remainSize >= SECOCSTD_STRING_BLOCK32 )
    {
        SECOCSTD_MEMSET16( pt_u4Dst, u4_copy );
        SECOCSTD_MEMSET16( pt_u4Dst, u4_copy );
        
        u4_remainSize -= SECOCSTD_STRING_BLOCK32;
    }
    if( u4_remainSize >= SECOCSTD_STRING_BLOCK16 )
    {
        SECOCSTD_MEMSET16( pt_u4Dst, u4_copy );
        
        u4_remainSize -= SECOCSTD_STRING_BLOCK16;
    }
    while( u4_remainSize >= SECOCSTD_STRING_BLOCK4 )
    {
        *pt_u4Dst = u4_copy;
        pt_u4Dst = &pt_u4Dst[SECOCSTD_STRING_NEXTINDEX];
        
        u4_remainSize -= SECOCSTD_STRING_BLOCK4;
    }
    
    pt_u1Dst = (uint8*)pt_u4Dst;
    while( u4_remainSize > 0UL )
    {
        *pt_u1Dst = u1Src;
        pt_u1Dst = &pt_u1Dst[SECOCSTD_STRING_NEXTINDEX];
        
        u4_remainSize--;
    }
    
    return ptDst;
}
#endif

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0     :2023/02/28                                                  */
/****************************************************************************/

/**** End of File ***********************************************************/
