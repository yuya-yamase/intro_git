/* SecOCStd_Util_c_v2-0-0                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | SecOCStd/Util/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <SecOCStd_Util.h>

#if (((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U)) \
  || ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U)))
/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define SECOCSTD_UTIL_BLOCK128    (128UL)
#define SECOCSTD_UTIL_BLOCK64     (64UL)
#define SECOCSTD_UTIL_BLOCK32     (32UL)
#define SECOCSTD_UTIL_BLOCK16     (16UL)
#define SECOCSTD_UTIL_BLOCK4      (4UL)

#define SECOCSTD_UTIL_BYTE_BIT    (8UL)
#define SECOCSTD_UTIL_BYTE_SFT    (3UL)
#define SECOCSTD_UTIL_BYTE_MSK    (0x07UL)

#define SECOCSTD_UTIL_ALIGN       (4UL)
#define SECOCSTD_UTIL_ALIGN_MSK   (SECOCSTD_UTIL_ALIGN - 1UL)

#define SECOCSTD_UTIL_BIT1_MSK    (1UL)

#define SECOCSTD_UTIL_NEXTINDEX   (1UL)

/* memclr */
#define SECOCSTD_MEMCLR16( p )            \
do {                                      \
    *(p) = 0UL;                           \
     (p) = &(p)[SECOCSTD_UTIL_NEXTINDEX]; \
    *(p) = 0UL;                           \
     (p) = &(p)[SECOCSTD_UTIL_NEXTINDEX]; \
    *(p) = 0UL;                           \
     (p) = &(p)[SECOCSTD_UTIL_NEXTINDEX]; \
    *(p) = 0UL;                           \
     (p) = &(p)[SECOCSTD_UTIL_NEXTINDEX]; \
} while ( 0 )

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

/****************************************************************************/
/* Function Name | SecOCStd_MemClr                                          */
/* Description   | memory 0 clear                                           */
/* Preconditions |                                                          */
/* Parameters    | ptDst  : output                                          */
/*               | u4Size : byte size                                       */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOCStd_MemClr
(
    P2VAR(void, AUTOMATIC, SECOC_APPL_DATA) ptDst,
    uint32 u4Size
)
{
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) pt_u4Dst;
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) pt_u1Dst;
    P2VAR(void, AUTOMATIC, SECOC_APPL_DATA) pt_Dst;
    uint32  u4_cnt;
    uint32  u4_remainSize;
    
    pt_u4Dst = (uint32*)ptDst;
    
    /* start address 4 byte align check */
    u4_cnt = (uint32)pt_u4Dst & SECOCSTD_UTIL_ALIGN_MSK; /* MISRA DEVIATION: */
    
    u4_remainSize = u4Size;
    
    if( (u4_cnt != 0UL)
      && (u4_remainSize >= SECOCSTD_UTIL_ALIGN) )
    {
        u4_cnt = SECOCSTD_UTIL_ALIGN - u4_cnt;
        
        pt_u1Dst = (uint8*)ptDst;
        
        u4_remainSize -= u4_cnt;
        while( u4_cnt > 0UL )
        {
            *pt_u1Dst = (uint8)0U;
            pt_u1Dst = &pt_u1Dst[SECOCSTD_UTIL_NEXTINDEX];
            u4_cnt--;
        }
        
        pt_Dst = (void*)pt_u1Dst;
        pt_u4Dst = (uint32*)pt_Dst;
    }
    
    while( u4_remainSize >= SECOCSTD_UTIL_BLOCK128 )
    {
        SECOCSTD_MEMCLR16( pt_u4Dst );
        SECOCSTD_MEMCLR16( pt_u4Dst );
        SECOCSTD_MEMCLR16( pt_u4Dst );
        SECOCSTD_MEMCLR16( pt_u4Dst );
        SECOCSTD_MEMCLR16( pt_u4Dst );
        SECOCSTD_MEMCLR16( pt_u4Dst );
        SECOCSTD_MEMCLR16( pt_u4Dst );
        SECOCSTD_MEMCLR16( pt_u4Dst );
        
        u4_remainSize -= SECOCSTD_UTIL_BLOCK128;
    }
    if( u4_remainSize >= SECOCSTD_UTIL_BLOCK64 )
    {
        SECOCSTD_MEMCLR16( pt_u4Dst );
        SECOCSTD_MEMCLR16( pt_u4Dst );
        SECOCSTD_MEMCLR16( pt_u4Dst );
        SECOCSTD_MEMCLR16( pt_u4Dst );
        
        u4_remainSize -= SECOCSTD_UTIL_BLOCK64;
    }
    if( u4_remainSize >= SECOCSTD_UTIL_BLOCK32 )
    {
        SECOCSTD_MEMCLR16( pt_u4Dst );
        SECOCSTD_MEMCLR16( pt_u4Dst );
        
        u4_remainSize -= SECOCSTD_UTIL_BLOCK32;
    }
    if( u4_remainSize >= SECOCSTD_UTIL_BLOCK16 )
    {
        SECOCSTD_MEMCLR16( pt_u4Dst );
        
        u4_remainSize -= SECOCSTD_UTIL_BLOCK16;
    }
    while( u4_remainSize >= SECOCSTD_UTIL_BLOCK4 )
    {
        *pt_u4Dst = 0UL;
        pt_u4Dst = &pt_u4Dst[SECOCSTD_UTIL_NEXTINDEX];
        
        u4_remainSize -= SECOCSTD_UTIL_BLOCK4;
    }
    
    pt_u1Dst = (uint8*)pt_u4Dst;
    while( u4_remainSize > 0UL )
    {
        *pt_u1Dst = (uint8)0U;
        pt_u1Dst = &pt_u1Dst[SECOCSTD_UTIL_NEXTINDEX];
        
        u4_remainSize--;
    }
    
    return ;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

#endif

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0     :2023/02/28                                                  */
/****************************************************************************/

/**** End of File ***********************************************************/
