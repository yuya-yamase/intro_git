/* Mscd_FreeSpace_Internal.c v1-0-0                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MSCD/FREESPACE/INTERNAL/CODE                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Mscd.h>
#include <Fee_Ext.h>

#include <Mscd_Common.h>

#include "../inc/Mscd_FreeSpace_Internal.h"

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define MSCD_START_SEC_CODE
#include <Mscd_MemMap.h>

#if ( MSCD_FREESPACE_USE == STD_ON )
/****************************************************************************/
/* Function Name | Mscd_FreeSpace_TransformFreeSpaceInfo                    */
/* Description   | Function to transform free space information.            */
/* Preconditions | None                                                     */
/* Parameters    | MscdFreeSpaceInfoPtr                                     */
/*               | FeeFreeSpaceInfoPtr                                      */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, MSCD_CODE)
Mscd_FreeSpace_TransformFreeSpaceInfo(
    P2VAR(Mscd_FreeSpaceInfoType, AUTOMATIC, MSCD_APPL_DATA) MscdFreeSpaceInfoPtr,
    P2CONST(Fee_ExtFreeSpaceInfoType, AUTOMATIC, TYPEDEF) FeeFreeSpaceInfoPtr
){
    Fee_ExtFreeSpaceResultType FeeFreeSpaceResult;
    Mscd_FreeSpaceResultType   MscdFreeSpaceResult;

    FeeFreeSpaceResult  = FeeFreeSpaceInfoPtr->Result;

    MscdFreeSpaceResult = MSCD_FREESPACE_RESULT_OK;
    if ( (FeeFreeSpaceResult & (Fee_ExtFreeSpaceResultType)FEE_EXT_FRSP_RESULT_MNG_OVER_LIMIT ) == (Fee_ExtFreeSpaceResultType)FEE_EXT_FRSP_RESULT_MNG_OVER_LIMIT )
    {
        MscdFreeSpaceResult |= (Mscd_FreeSpaceResultType)MSCD_FREESPACE_RESULT_MNG_OVER_LIMIT;
    }
    if ( (FeeFreeSpaceResult & (Fee_ExtFreeSpaceResultType)FEE_EXT_FRSP_RESULT_DATA_OVER_LIMIT ) == (Fee_ExtFreeSpaceResultType)FEE_EXT_FRSP_RESULT_DATA_OVER_LIMIT )
    {
        MscdFreeSpaceResult |= (Mscd_FreeSpaceResultType)MSCD_FREESPACE_RESULT_DATA_OVER_LIMIT;
    }
    if ( (FeeFreeSpaceResult & (Fee_ExtFreeSpaceResultType)FEE_EXT_FRSP_RESULT_PENDING_RBLD ) == (Fee_ExtFreeSpaceResultType)FEE_EXT_FRSP_RESULT_PENDING_RBLD )
    {
        MscdFreeSpaceResult |= (Mscd_FreeSpaceResultType)MSCD_FREESPACE_RESULT_PENDING_REBUILD;
    }
    if ( (FeeFreeSpaceResult & (Fee_ExtFreeSpaceResultType)FEE_EXT_FRSP_RESULT_BLANK ) == (Fee_ExtFreeSpaceResultType)FEE_EXT_FRSP_RESULT_BLANK )
    {
        MscdFreeSpaceResult |= (Mscd_FreeSpaceResultType)MSCD_FREESPACE_RESULT_BLANK;
    }
    if ( (FeeFreeSpaceResult & (Fee_ExtFreeSpaceResultType)FEE_EXT_FRSP_RESULT_AREAINFO_INCONSISTENT ) == (Fee_ExtFreeSpaceResultType)FEE_EXT_FRSP_RESULT_AREAINFO_INCONSISTENT )
    {
        MscdFreeSpaceResult |= (Mscd_FreeSpaceResultType)MSCD_FREESPACE_RESULT_AREAINFO_INCONSISTENT;
    }

    MscdFreeSpaceInfoPtr->Result       = MscdFreeSpaceResult;
    MscdFreeSpaceInfoPtr->RcrdNum      = FeeFreeSpaceInfoPtr->RcrdNum;
    MscdFreeSpaceInfoPtr->DataAreaByte = FeeFreeSpaceInfoPtr->DataAreaByte;

    return;
}
#endif /*( MSCD_FREESPACE_USE == STD_ON )*/

#define MSCD_STOP_SEC_CODE
#include <Mscd_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/10/09                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
