/* SecOC_Com_c_v2-0-0                                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | SecOC/Com/CODE                                             */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <SecOCStd_String.h>
#include <SecOCStd_Util.h>
#include "../inc/SecOC_Com.h"
#if (SECOC_AB_EXTENDED_ENABLE == STD_ON)
#include "../inc/SecOC_Extd_Internal.h"
#endif

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define SECOC_COM_DATAID_INDEX0 (0U)
#define SECOC_COM_DATAID_INDEX1 (1U)
#define SECOC_COM_DATAID_INDEX2 (2U)
#define SECOC_COM_DATAID_INDEX3 (3U)

#define SECOC_COM_BYTE_1        ((uint16)1U)
#define SECOC_COM_BYTE_2        ((uint16)2U)
#define SECOC_COM_BYTE_3        ((uint16)3U)
#define SECOC_COM_BYTE_4        ((uint16)4U)

#define SECOC_COM_BITSHIFT_8    (8UL)
#define SECOC_COM_BITSHIFT_16   (16UL)
#define SECOC_COM_BITSHIFT_24   (24UL)

#if (SECOC_COM_PADDING_ENABLE == STD_ON)
#define SECOC_COM_BLOCK_SIZE    (16UL)
#define SECOC_COM_BLOCK_MASK    (0x0000000FUL)

#define SECOC_COM_PADDING_MSB   ((uint8)0x80U)
#endif

#define SECOC_COM_UINT32_MAX_VALUE   ((uint32)0xFFFFFFFFU)


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
/* Function Name | SecOC_Com_BuildAuthData                                  */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ptInfo :                                                 */
/*               | ptData :                                                 */
/*               | ptSize :                                                 */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_Com_BuildAuthData
(
    P2CONST(SecOC_Com_BuildAuthDataType, AUTOMATIC, SECOC_APPL_DATA) ptInfo,
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) ptData,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) ptSize
)
{
    uint32  u4_index = 0UL;
    uint32  u4_totalSize;
    uint16  u2_dataIdSize;
    uint32  u4_idFvSize;
#if (SECOC_COM_PADDING_ENABLE == STD_ON)
    uint16  u2_pdSize = 0U;
    uint16  u2_blockSurplus;
#endif
    
    /* Parameters check */
    if( (ptInfo != NULL_PTR)
        && (ptData != NULL_PTR)
        && (ptSize != NULL_PTR) )
    {
        
        u2_dataIdSize = (uint16)(((uint32)ptInfo->u2DataIdLength + SECOC_COM_BIT2BYTE_ROUND_ADD) >> SECOC_COM_BIT2BYTE_SHIFT);
        u4_idFvSize = (uint32)u2_dataIdSize + (uint32)ptInfo->u2FreshnessValueSize;
        if( (SECOC_COM_UINT32_MAX_VALUE - ptInfo->u4ProtDataSize) >= u4_idFvSize )
        {
            u4_totalSize = u4_idFvSize + ptInfo->u4ProtDataSize;
#if (SECOC_COM_PADDING_ENABLE == STD_ON)
            u2_blockSurplus = (uint16)(u4_totalSize & SECOC_COM_BLOCK_MASK);
            
            if( u2_blockSurplus != (uint16)0U )
            {
                u2_pdSize = (uint16)SECOC_COM_BLOCK_SIZE - u2_blockSurplus;
                u4_totalSize += (uint32)u2_pdSize;
            }
#endif
            
            if( *ptSize >= u4_totalSize )
            {
                /* Message ID */
                if( u2_dataIdSize == SECOC_COM_BYTE_2 )
                {
                    ptData[SECOC_COM_DATAID_INDEX0] = (uint8)(ptInfo->u4DataId >> SECOC_COM_BITSHIFT_8);
                    ptData[SECOC_COM_DATAID_INDEX1] = (uint8)ptInfo->u4DataId;
                    u4_index = (uint32)SECOC_COM_BYTE_2;
                }
                else if( u2_dataIdSize >= SECOC_COM_BYTE_4 )
                {
                    ptData[SECOC_COM_DATAID_INDEX0] = (uint8)(ptInfo->u4DataId >> SECOC_COM_BITSHIFT_24);
                    ptData[SECOC_COM_DATAID_INDEX1] = (uint8)(ptInfo->u4DataId >> SECOC_COM_BITSHIFT_16);
                    ptData[SECOC_COM_DATAID_INDEX2] = (uint8)(ptInfo->u4DataId >> SECOC_COM_BITSHIFT_8);
                    ptData[SECOC_COM_DATAID_INDEX3] = (uint8)ptInfo->u4DataId;
                    u4_index = (uint32)SECOC_COM_BYTE_4;
                }
                else if( u2_dataIdSize == SECOC_COM_BYTE_3 )
                {
                    ptData[SECOC_COM_DATAID_INDEX0] = (uint8)(ptInfo->u4DataId >> SECOC_COM_BITSHIFT_16);
                    ptData[SECOC_COM_DATAID_INDEX1] = (uint8)(ptInfo->u4DataId >> SECOC_COM_BITSHIFT_8);
                    ptData[SECOC_COM_DATAID_INDEX2] = (uint8)ptInfo->u4DataId;
                    u4_index = (uint32)SECOC_COM_BYTE_3;
                }
                else if( u2_dataIdSize == SECOC_COM_BYTE_1 )
                {
                    ptData[SECOC_COM_DATAID_INDEX0] = (uint8)ptInfo->u4DataId;
                    u4_index = (uint32)SECOC_COM_BYTE_1;
                }
                else
                {
                    /* No Processing */
                }
                
                /* Protection data */
#if (SECOC_AB_EXTD_MEMUTIL == STD_ON)
                SecOC_Extd_MemCpy( &ptData[u4_index], ptInfo->ptProtData, ptInfo->u4ProtDataSize );
#else
                (void)SecOCStd_MemCpy( &ptData[u4_index], ptInfo->ptProtData, ptInfo->u4ProtDataSize ); /* no return check required */
#endif
                u4_index += ptInfo->u4ProtDataSize;
                
                /* Freshness Value */
#if (SECOC_AB_EXTD_MEMUTIL == STD_ON)
                SecOC_Extd_MemCpy( &ptData[u4_index], ptInfo->ptFreshnessValue, (uint32)ptInfo->u2FreshnessValueSize );
#else
                (void)SecOCStd_MemCpy( &ptData[u4_index], ptInfo->ptFreshnessValue, (uint32)ptInfo->u2FreshnessValueSize ); /* no return check required */
#endif
                
#if (SECOC_COM_PADDING_ENABLE == STD_ON)
                u4_index += (uint32)ptInfo->u2FreshnessValueSize;
                
                /* Padding */
                if( u2_pdSize > (uint16)0U )
                {
                    if( u2_pdSize > SECOC_COM_BYTE_1 )
                    {
                        (void)SecOCStd_MemClr( &ptData[u4_index], (uint32)u2_pdSize ); /* no return check required */
                    }
                    ptData[u4_index] = SECOC_COM_PADDING_MSB;
                }
#endif
                
                /* Size */
                *ptSize = u4_totalSize;
            }
        }
    }
    
    return ;
}
#endif

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version    :Date                                                        */
/*  v2-0-0     :2023/02/28                                                  */
/****************************************************************************/

/**** End of File ***********************************************************/
