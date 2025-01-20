/* Crypto_83_sw_SecStd_String_c_v2-0-0                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | SecStd/String/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../inc/Crypto_83_sw_SecStd_String.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define CRYPTO_83_SW_SECSTD_STR_BLOCK128  (128UL)
#define CRYPTO_83_SW_SECSTD_STR_BLOCK64   (64UL)
#define CRYPTO_83_SW_SECSTD_STR_BLOCK32   (32UL)
#define CRYPTO_83_SW_SECSTD_STR_BLOCK16   (16UL)
#define CRYPTO_83_SW_SECSTD_STR_BLOCK4    (4UL)

#define CRYPTO_83_SW_SECSTD_STR_SFT8      (8UL)
#define CRYPTO_83_SW_SECSTD_STR_SFT16     (16UL)

#define CRYPTO_83_SW_SECSTD_STR_ALIGN     (4UL)
#define CRYPTO_83_SW_SECSTD_STR_ALIGN_MSK (CRYPTO_83_SW_SECSTD_STR_ALIGN - 1UL)

#define CRYPTO_83_SW_SECSTD_STR_DATA_0    (0UL)

#define CRYPTO_83_SW_SECSTD_NEXTINDEX     (1UL)

/* memset */
#define CRYPTO_83_SW_SECSTD_MEMSET16(p , c)     \
do {                                            \
    *(p) = (c);                                 \
     (p) = &(p)[CRYPTO_83_SW_SECSTD_NEXTINDEX]; \
    *(p) = (c);                                 \
     (p) = &(p)[CRYPTO_83_SW_SECSTD_NEXTINDEX]; \
    *(p) = (c);                                 \
     (p) = &(p)[CRYPTO_83_SW_SECSTD_NEXTINDEX]; \
    *(p) = (c);                                 \
     (p) = &(p)[CRYPTO_83_SW_SECSTD_NEXTINDEX]; \
} while( 0 )

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
#define CRYPTO_83_sw_START_SEC_CODE
#include <Crypto_83_sw_MemMap.h>

/****************************************************************************/
/* Function Name | Crypto_83_sw_SecStd_MemCmp                               */
/* Description   | memory compere                                           */
/* Preconditions |                                                          */
/* Parameters    | ptCmp1 : input1                                          */
/*               | ptCmp2 : input2                                          */
/*               | u4Size : byte size                                       */
/* Return Value  | sint32                                                   */
/*               |  same       : 0                                          */
/*               |  difference : ptCmp1 - ptCmp2                            */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(sint32, CRYPTO_83_sw_CODE) Crypto_83_sw_SecStd_MemCmp
(
    P2CONST(void, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptCmp1,
    P2CONST(void, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptCmp2,
    uint32 u4Size
)
{
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) pt_u1Cmp1;
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) pt_u1Cmp2;
    sint32  u4_ret = 0;
    uint32  u4_remainSize;
    
    pt_u1Cmp1 = (const uint8*)ptCmp1;
    pt_u1Cmp2 = (const uint8*)ptCmp2;
    
    u4_remainSize = u4Size;
    
    while( u4_remainSize > CRYPTO_83_SW_SECSTD_STR_DATA_0 )
    {
        if( *pt_u1Cmp1 != *pt_u1Cmp2 )
        {
            u4_ret = (sint32)*pt_u1Cmp1 - (sint32)*pt_u1Cmp2;
            break;
        }
        pt_u1Cmp1 = &pt_u1Cmp1[CRYPTO_83_SW_SECSTD_NEXTINDEX];
        pt_u1Cmp2 = &pt_u1Cmp2[CRYPTO_83_SW_SECSTD_NEXTINDEX];
        
        u4_remainSize--;
    }
    
    return u4_ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SecStd_MemCpy                               */
/* Description   | memory copy                                              */
/* Preconditions |                                                          */
/* Parameters    | ptDst : output address                                   */
/*               | ptSrc : input address                                    */
/*               | u4Size : byte size                                       */
/* Return Value  | output address                                           */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC_P2VAR(void, AUTOMATIC, CRYPTO_83_sw_CODE) Crypto_83_sw_SecStd_MemCpy
(
    P2VAR(void, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptDst,
    P2CONST(void, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptSrc,
    uint32 u4Size
)
{
    P2VAR(uint32, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) pt_u4Dst;
    P2CONST(uint32, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) pt_u4Src;
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) pt_u1Dst;
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) pt_u1Src;
    uint32  u4_remainSize;
    
    pt_u4Dst = (uint32*)ptDst;
    pt_u4Src = (const uint32*)ptSrc;
    
    u4_remainSize = u4Size;
    
    if( (((uint32)pt_u4Dst & CRYPTO_83_SW_SECSTD_STR_ALIGN_MSK) == 0UL)     /* MISRA DEVIATION */
      && (((uint32)pt_u4Src & CRYPTO_83_SW_SECSTD_STR_ALIGN_MSK) == 0UL) )  /* MISRA DEVIATION */
    {
        while( u4_remainSize >= CRYPTO_83_SW_SECSTD_STR_BLOCK32 )
        {
            *pt_u4Dst = *pt_u4Src;
            pt_u4Dst = &pt_u4Dst[CRYPTO_83_SW_SECSTD_NEXTINDEX];
            pt_u4Src = &pt_u4Src[CRYPTO_83_SW_SECSTD_NEXTINDEX];
            *pt_u4Dst = *pt_u4Src;
            pt_u4Dst = &pt_u4Dst[CRYPTO_83_SW_SECSTD_NEXTINDEX];
            pt_u4Src = &pt_u4Src[CRYPTO_83_SW_SECSTD_NEXTINDEX];
            *pt_u4Dst = *pt_u4Src;
            pt_u4Dst = &pt_u4Dst[CRYPTO_83_SW_SECSTD_NEXTINDEX];
            pt_u4Src = &pt_u4Src[CRYPTO_83_SW_SECSTD_NEXTINDEX];
            *pt_u4Dst = *pt_u4Src;
            pt_u4Dst = &pt_u4Dst[CRYPTO_83_SW_SECSTD_NEXTINDEX];
            pt_u4Src = &pt_u4Src[CRYPTO_83_SW_SECSTD_NEXTINDEX];
            *pt_u4Dst = *pt_u4Src;
            pt_u4Dst = &pt_u4Dst[CRYPTO_83_SW_SECSTD_NEXTINDEX];
            pt_u4Src = &pt_u4Src[CRYPTO_83_SW_SECSTD_NEXTINDEX];
            *pt_u4Dst = *pt_u4Src;
            pt_u4Dst = &pt_u4Dst[CRYPTO_83_SW_SECSTD_NEXTINDEX];
            pt_u4Src = &pt_u4Src[CRYPTO_83_SW_SECSTD_NEXTINDEX];
            *pt_u4Dst = *pt_u4Src;
            pt_u4Dst = &pt_u4Dst[CRYPTO_83_SW_SECSTD_NEXTINDEX];
            pt_u4Src = &pt_u4Src[CRYPTO_83_SW_SECSTD_NEXTINDEX];
            *pt_u4Dst = *pt_u4Src;
            pt_u4Dst = &pt_u4Dst[CRYPTO_83_SW_SECSTD_NEXTINDEX];
            pt_u4Src = &pt_u4Src[CRYPTO_83_SW_SECSTD_NEXTINDEX];
            u4_remainSize -= CRYPTO_83_SW_SECSTD_STR_BLOCK32;
        }
        if( u4_remainSize >= CRYPTO_83_SW_SECSTD_STR_BLOCK16 )
        {
            *pt_u4Dst = *pt_u4Src;
            pt_u4Dst = &pt_u4Dst[CRYPTO_83_SW_SECSTD_NEXTINDEX];
            pt_u4Src = &pt_u4Src[CRYPTO_83_SW_SECSTD_NEXTINDEX];
            *pt_u4Dst = *pt_u4Src;
            pt_u4Dst = &pt_u4Dst[CRYPTO_83_SW_SECSTD_NEXTINDEX];
            pt_u4Src = &pt_u4Src[CRYPTO_83_SW_SECSTD_NEXTINDEX];
            *pt_u4Dst = *pt_u4Src;
            pt_u4Dst = &pt_u4Dst[CRYPTO_83_SW_SECSTD_NEXTINDEX];
            pt_u4Src = &pt_u4Src[CRYPTO_83_SW_SECSTD_NEXTINDEX];
            *pt_u4Dst = *pt_u4Src;
            pt_u4Dst = &pt_u4Dst[CRYPTO_83_SW_SECSTD_NEXTINDEX];
            pt_u4Src = &pt_u4Src[CRYPTO_83_SW_SECSTD_NEXTINDEX];
            
            u4_remainSize -= CRYPTO_83_SW_SECSTD_STR_BLOCK16;
        }
        while( u4_remainSize >= CRYPTO_83_SW_SECSTD_STR_BLOCK4 )
        {
            *pt_u4Dst = *pt_u4Src;
            pt_u4Dst = &pt_u4Dst[CRYPTO_83_SW_SECSTD_NEXTINDEX];
            pt_u4Src = &pt_u4Src[CRYPTO_83_SW_SECSTD_NEXTINDEX];
            
            u4_remainSize -= CRYPTO_83_SW_SECSTD_STR_BLOCK4;
        }
    }
    
    pt_u1Dst = (uint8*)pt_u4Dst;
    pt_u1Src = (const uint8*)pt_u4Src;
    while( u4_remainSize > CRYPTO_83_SW_SECSTD_STR_DATA_0 )
    {
        *pt_u1Dst = *pt_u1Src;
        pt_u1Dst = &pt_u1Dst[CRYPTO_83_SW_SECSTD_NEXTINDEX];
        pt_u1Src = &pt_u1Src[CRYPTO_83_SW_SECSTD_NEXTINDEX];
        
        u4_remainSize--;
    }
    
    return ptDst;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SecStd_MemSet                               */
/* Description   | memory set                                               */
/* Preconditions |                                                          */
/* Parameters    | ptDst : output address                                   */
/*               | u1Src : input value                                      */
/*               | u4Size : byte size                                       */
/* Return Value  | output address                                           */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC_P2VAR(void, AUTOMATIC, CRYPTO_83_sw_CODE) Crypto_83_sw_SecStd_MemSet
(
    P2VAR(void, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptDst,
    uint8 u1Src,
    uint32 u4Size
)
{
    P2VAR(uint32, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) pt_u4Dst;
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) pt_u1Dst;
    P2VAR(void, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) pt_Dst;
    uint32  u4_copy;
    uint32  u4_cnt;
    uint32  u4_remainSize;
    
    /* copy data */
    u4_copy = (uint32)u1Src;
    u4_copy |= u4_copy << CRYPTO_83_SW_SECSTD_STR_SFT8;
    u4_copy |= u4_copy << CRYPTO_83_SW_SECSTD_STR_SFT16;
    
    pt_u4Dst = (uint32 *)ptDst;
    
    /* start address 4 byte align check */
    u4_cnt = (uint32)pt_u4Dst & CRYPTO_83_SW_SECSTD_STR_ALIGN_MSK;  /* MISRA DEVIATION */
    
    u4_remainSize = u4Size;
    
    if( (u4_cnt != 0UL)
      && (u4_remainSize >= CRYPTO_83_SW_SECSTD_STR_ALIGN) )
    {
        u4_cnt = CRYPTO_83_SW_SECSTD_STR_ALIGN - u4_cnt;
        
        pt_u1Dst = (uint8*)ptDst;
        
        u4_remainSize -= u4_cnt;
        while( u4_cnt > CRYPTO_83_SW_SECSTD_STR_DATA_0 )
        {
            *pt_u1Dst = u1Src;
            pt_u1Dst = &pt_u1Dst[CRYPTO_83_SW_SECSTD_NEXTINDEX];
            u4_cnt--;
        }
        
        pt_Dst = (void*)pt_u1Dst;
        pt_u4Dst = (uint32*)pt_Dst;
    }
    
    while( u4_remainSize >= CRYPTO_83_SW_SECSTD_STR_BLOCK128 )
    {
        CRYPTO_83_SW_SECSTD_MEMSET16( pt_u4Dst, u4_copy );
        CRYPTO_83_SW_SECSTD_MEMSET16( pt_u4Dst, u4_copy );
        CRYPTO_83_SW_SECSTD_MEMSET16( pt_u4Dst, u4_copy );
        CRYPTO_83_SW_SECSTD_MEMSET16( pt_u4Dst, u4_copy );
        CRYPTO_83_SW_SECSTD_MEMSET16( pt_u4Dst, u4_copy );
        CRYPTO_83_SW_SECSTD_MEMSET16( pt_u4Dst, u4_copy );
        CRYPTO_83_SW_SECSTD_MEMSET16( pt_u4Dst, u4_copy );
        CRYPTO_83_SW_SECSTD_MEMSET16( pt_u4Dst, u4_copy );
        
        u4_remainSize -= CRYPTO_83_SW_SECSTD_STR_BLOCK128;
    }
    if( u4_remainSize >= CRYPTO_83_SW_SECSTD_STR_BLOCK64 )
    {
        CRYPTO_83_SW_SECSTD_MEMSET16( pt_u4Dst, u4_copy );
        CRYPTO_83_SW_SECSTD_MEMSET16( pt_u4Dst, u4_copy );
        CRYPTO_83_SW_SECSTD_MEMSET16( pt_u4Dst, u4_copy );
        CRYPTO_83_SW_SECSTD_MEMSET16( pt_u4Dst, u4_copy );
        
        u4_remainSize -= CRYPTO_83_SW_SECSTD_STR_BLOCK64;
    }
    if( u4_remainSize >= CRYPTO_83_SW_SECSTD_STR_BLOCK32 )
    {
        CRYPTO_83_SW_SECSTD_MEMSET16( pt_u4Dst, u4_copy );
        CRYPTO_83_SW_SECSTD_MEMSET16( pt_u4Dst, u4_copy );
        
        u4_remainSize -= CRYPTO_83_SW_SECSTD_STR_BLOCK32;
    }
    if( u4_remainSize >= CRYPTO_83_SW_SECSTD_STR_BLOCK16 )
    {
        CRYPTO_83_SW_SECSTD_MEMSET16( pt_u4Dst, u4_copy );
        
        u4_remainSize -= CRYPTO_83_SW_SECSTD_STR_BLOCK16;
    }
    while( u4_remainSize >= CRYPTO_83_SW_SECSTD_STR_BLOCK4 )
    {
        *pt_u4Dst = u4_copy;
        pt_u4Dst = &pt_u4Dst[CRYPTO_83_SW_SECSTD_NEXTINDEX];
        
        u4_remainSize -= CRYPTO_83_SW_SECSTD_STR_BLOCK4;
    }
    
    pt_u1Dst = (uint8*)pt_u4Dst;
    while( u4_remainSize > CRYPTO_83_SW_SECSTD_STR_DATA_0 )
    {
        *pt_u1Dst = u1Src;
        pt_u1Dst = &pt_u1Dst[CRYPTO_83_SW_SECSTD_NEXTINDEX];
        
        u4_remainSize--;
    }
    
    return ptDst;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


#define CRYPTO_83_sw_STOP_SEC_CODE
#include <Crypto_83_sw_MemMap.h>


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2023/01/16                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
