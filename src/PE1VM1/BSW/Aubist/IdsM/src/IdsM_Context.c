/* IdsM_Context_c_v2-0-2                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | IdsM/Context/CODE                                          */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <IdsM.h>
#include <SchM_IdsM.h>
#include "../inc/IdsM_Cfg_Fixed.h"
#include "../inc/IdsM_Context.h"
#include "../inc/IdsM_General.h"
#include "../inc/IdsM_Std.h"

#if ( IDSM_CFG_USE_CTXDATA == STD_ON )
/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define IDSM_CTXS_NOUSE     ((IdsM_CtxDataBuffStatusType)0x00U)
#define IDSM_CTXS_USE       ((IdsM_CtxDataBuffStatusType)0xE1U)

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

/****************************************************************************/
/* Function Name | IdsM_Context_Init                                        */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_Context_Init
(
    void
)
{
    uint16 u2_tableloop;
    uint16 u2_recordloop;
    P2CONST(AB_83_ConstV IdsMCtxDataBuffType, AUTOMATIC, IDSM_CONFIG_DATA) pt_ctx_BoxAccs;

    pt_ctx_BoxAccs = IdsM_Cfg_CtxDataBoxAcss.ptCBox->ptCData;

    for( u2_tableloop = 0U; u2_tableloop < IdsM_Cfg_CtxDataBoxAcss.u2CBNum; u2_tableloop++ )
    {
        for( u2_recordloop = 0U; u2_recordloop < pt_ctx_BoxAccs[u2_tableloop].u2CtxDataBuffNum; u2_recordloop++ )
        {
            pt_ctx_BoxAccs[u2_tableloop].ptCtxDataStatus[u2_recordloop] = IDSM_CTXS_NOUSE;
        }
    }

    return ;
}

/****************************************************************************/
/* Function Name | IdsM_Context_SetBuff                                     */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ptData                                                   */
/*               | u2DataSize                                               */
/*               | ptCtxDataIndex1                                          */
/*               | ptCtxDataIndex2                                          */
/* Return Value  | Std_ReturnType                                           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, IDSM_CODE) IdsM_Context_SetBuff
(
    P2CONST(uint8, AUTOMATIC, AUTOMATIC) ptData,
    VAR(uint16, AUTOMATIC) u2DataSize,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) ptCtxDataIndex1,
    P2VAR(uint16, AUTOMATIC, AUTOMATIC) ptCtxDataIndex2
)
{
    Std_ReturnType ud_StdRet = (Std_ReturnType)E_NOT_OK;
    Std_ReturnType ud_search_result = (Std_ReturnType)E_NOT_OK;
    uint16 u2_tableloop;
    uint16 u2_recordloop = 0U;
    uint16 u2_BuffSize;
    uint32 u4_sizeindex;
    P2CONST(AB_83_ConstV IdsMCtxDataBuffType, AUTOMATIC, IDSM_CONFIG_DATA) pt_ctx_BoxAccs;
    P2VAR(volatile uint8, AUTOMATIC, IDSM_VAR_NO_INIT) pt_CtxData;

    pt_ctx_BoxAccs = IdsM_Cfg_CtxDataBoxAcss.ptCBox->ptCData;

    SchM_Enter_IdsM_General();

    for( u2_tableloop = 0U; u2_tableloop < IdsM_Cfg_CtxDataBoxAcss.u2CBNum; u2_tableloop++ )
    {
        if( u2DataSize <= pt_ctx_BoxAccs[u2_tableloop].u2CtxDataBuffSize )
        {
            for( u2_recordloop = 0U; u2_recordloop < pt_ctx_BoxAccs[u2_tableloop].u2CtxDataBuffNum; u2_recordloop++ )
            {
                if( pt_ctx_BoxAccs[u2_tableloop].ptCtxDataStatus[u2_recordloop] == IDSM_CTXS_NOUSE )
                {
                    pt_ctx_BoxAccs[u2_tableloop].ptCtxDataStatus[u2_recordloop] = IDSM_CTXS_USE;
                    ud_search_result = (Std_ReturnType)E_OK;
                    break;
                }
            }

            if( ud_search_result == (Std_ReturnType)E_OK )
            {
                break;
            }
        }
    }

    SchM_Exit_IdsM_General();

    if( ud_search_result == (Std_ReturnType)E_OK )
    {
        u2_BuffSize = pt_ctx_BoxAccs[u2_tableloop].u2CtxDataBuffSize;
        u4_sizeindex = ( (uint32)u2_BuffSize ) * ( (uint32)u2_recordloop );

        pt_CtxData = pt_ctx_BoxAccs[u2_tableloop].ptCtxData;
        IdsM_Std_MemCpy( &pt_CtxData[u4_sizeindex], &ptData[0], u2DataSize );

        *ptCtxDataIndex1 = u2_tableloop;
        *ptCtxDataIndex2 = u2_recordloop;
        ud_StdRet = (Std_ReturnType)E_OK;
    }

    return ud_StdRet;
}

/****************************************************************************/
/* Function Name | IdsM_Context_ClearBuff                                   */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2CtxDataIndex1                                          */
/*               | u2CtxDataIndex2                                          */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_Context_ClearBuff
(
    VAR(uint16, AUTOMATIC) u2CtxDataIndex1,
    VAR(uint16, AUTOMATIC) u2CtxDataIndex2
)
{
    P2CONST(AB_83_ConstV IdsMCtxDataBuffType, AUTOMATIC, IDSM_CONFIG_DATA) pt_ctx_BoxAccs;

    pt_ctx_BoxAccs = IdsM_Cfg_CtxDataBoxAcss.ptCBox->ptCData;
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
    if( ( u2CtxDataIndex1 < IdsM_Cfg_CtxDataBoxAcss.u2CBNum ) &&
        ( u2CtxDataIndex2 < pt_ctx_BoxAccs[u2CtxDataIndex1].u2CtxDataBuffNum ) )
    {
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */
        pt_ctx_BoxAccs[u2CtxDataIndex1].ptCtxDataStatus[u2CtxDataIndex2] = IDSM_CTXS_NOUSE;
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
    }
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */

    return ;
}

/****************************************************************************/
/* Function Name | IdsM_Context_GetCtxData                                  */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2CtxDataIndex1                                          */
/*               | u2CtxDataIndex2                                          */
/*               | u2CtxDataSize                                            */
/*               | ptCtxData                                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_Context_GetCtxData
(
    VAR(uint16, AUTOMATIC) u2CtxDataIndex1,
    VAR(uint16, AUTOMATIC) u2CtxDataIndex2,
    VAR(uint16, AUTOMATIC) u2CtxDataSize,
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) ptCtxData
)
{
    P2CONST(AB_83_ConstV IdsMCtxDataBuffType, AUTOMATIC, IDSM_CONFIG_DATA) pt_ctx_BoxAccs;
    uint16 u2_buffsize;
    uint32 u4_sizeindex;
    P2CONST(volatile uint8, AUTOMATIC, IDSM_VAR_NO_INIT) pt_CtxData;

    pt_ctx_BoxAccs = IdsM_Cfg_CtxDataBoxAcss.ptCBox->ptCData;
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
    if( ( u2CtxDataIndex1 <  IdsM_Cfg_CtxDataBoxAcss.u2CBNum ) &&
        ( u2CtxDataIndex2 <  pt_ctx_BoxAccs[u2CtxDataIndex1].u2CtxDataBuffNum ) &&
        ( u2CtxDataSize   <= pt_ctx_BoxAccs[u2CtxDataIndex1].u2CtxDataBuffSize ) )
    {
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */

        u2_buffsize = IdsM_Cfg_CtxDataBoxAcss.ptCBox->ptCData[u2CtxDataIndex1].u2CtxDataBuffSize;
        u4_sizeindex = ( (uint32)u2CtxDataIndex2 ) * ( (uint32)u2_buffsize );

        pt_CtxData = pt_ctx_BoxAccs[u2CtxDataIndex1].ptCtxData;
        IdsM_Std_MemCpy( &ptCtxData[0], &pt_CtxData[u4_sizeindex], u2CtxDataSize );

#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
    }
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */

    return ;
}

/****************************************************************************/
/* Function Name | IdsM_Context_GetBuffAdr                                  */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2CtxDataIndex1                                          */
/*               | u2CtxDataIndex2                                          */
/* Return Value  | const uint8*                                             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC_P2CONST(volatile uint8, IDSM_VAR_NO_INIT, IDSM_CODE) IdsM_Context_GetBuffAdr
(
    VAR(uint16, AUTOMATIC) u2CtxDataIndex1,
    VAR(uint16, AUTOMATIC) u2CtxDataIndex2
)
{
    P2CONST(AB_83_ConstV IdsMCtxDataBuffType, AUTOMATIC, IDSM_CONFIG_DATA) pt_ctx_BoxAccs;
    uint16 u2_buffsize;
    uint32 u4_sizeindex;
    P2CONST(volatile uint8, AUTOMATIC, IDSM_VAR_NO_INIT) pt_CtxDataBuff;

    pt_ctx_BoxAccs = IdsM_Cfg_CtxDataBoxAcss.ptCBox->ptCData;
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
    if( ( u2CtxDataIndex1 <  IdsM_Cfg_CtxDataBoxAcss.u2CBNum ) &&
        ( u2CtxDataIndex2 <  pt_ctx_BoxAccs[u2CtxDataIndex1].u2CtxDataBuffNum ) )
    {
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */
        u2_buffsize = IdsM_Cfg_CtxDataBoxAcss.ptCBox->ptCData[u2CtxDataIndex1].u2CtxDataBuffSize;
        u4_sizeindex = ( (uint32)u2CtxDataIndex2 ) * ( (uint32)u2_buffsize );
        pt_CtxDataBuff = &pt_ctx_BoxAccs[u2CtxDataIndex1].ptCtxData[u4_sizeindex];
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
    }
    else
    {
        pt_CtxDataBuff = NULL_PTR;
    }
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */

    return pt_CtxDataBuff;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define IDSM_STOP_SEC_CODE
#include <IdsM_MemMap.h>

#endif /* ( IDSM_CFG_USE_CTXDATA == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version    :Date                                                        */
/*  v2-0-0     :2022/11/30                                                  */
/*  v2-0-1     :2023/01/23                                                  */
/*  v2-0-2     :2023/02/24                                                  */
/****************************************************************************/

/**** End of File ***********************************************************/

