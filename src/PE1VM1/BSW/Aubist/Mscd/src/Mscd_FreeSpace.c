/* Mscd_FreeSpace.c v1-0-0                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MSCD/FREESPACE/CODE                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Mscd.h>
#include <Fee_Ext.h>

#include <Mscd_Common.h>

#include "../inc/Mscd_FreeSpace.h"
#include "../inc/Mscd_FreeSpace_Internal.h"

#include "../inc/Mscd_Suspend.h"

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define MSCD_START_SEC_CODE
#include <Mscd_MemMap.h>
/****************************************************************************/
/* Function Name | Mscd_FreeSpace_Init                                      */
/* Description   | Service to initialize this unit.                         */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, MSCD_CODE)
Mscd_FreeSpace_Init( void )
{
    return;
}

#if ( MSCD_FREESPACE_USE == STD_ON )
/****************************************************************************/
/* Function Name | Mscd_GetFreeSpace                                        */
/* Description   | Service to get free space sizes on data flash.           */
/* Preconditions | None                                                     */
/* Parameters    | AreaNo                                                   */
/*               | LimitSearchMngArea                                       */
/*               | LimitDataAreaByte                                        */
/*               | FreeSpaceInfoPtr                                         */
/* Return Value  | MSCD_E_FREESPACE_OK                                      */
/*               | MSCD_E_FREESPACE_PARAM_ERROR                             */
/*               | MSCD_E_FREESPACE_BUSY                                    */
/*               | MSCD_E_FREESPACE_AREA_FAULT                              */
/*               | MSCD_E_FREESPACE_INTERNAL_ERROR                          */
/*               | MSCD_E_FREESPACE_MS_SUSPEND                              */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Mscd_FreeSpaceReturnType, MSCD_CODE)
Mscd_GetFreeSpace(
    uint8 AreaNo,
    uint16 LimitSearchMngArea,
    uint32 LimitDataAreaByte,
    P2VAR(Mscd_FreeSpaceInfoType, AUTOMATIC, MSCD_APPL_DATA) FreeSpaceInfoPtr
){
    uint8                      UserSuspendState;
    Fee_ExtFreeSpaceReturnType FeeFreeSpaceReturn;
    Fee_ExtFreeSpaceInfoType   FeeFreeSpaceInfo;
    Mscd_FreeSpaceReturnType   MscdFreeSpaceReturn;

    if ( FreeSpaceInfoPtr != NULL_PTR )
    {
        UserSuspendState = Mscd_Suspend_GetUserSuspendState();
        if ( UserSuspendState == MSCD_SUSPEND_MS_RUN )
        {
            FeeFreeSpaceInfo.Result       = FEE_EXT_FRSP_RESULT_OK;
            FeeFreeSpaceInfo.RcrdNum      = 0U;
            FeeFreeSpaceInfo.DataAreaByte = 0UL;
            FeeFreeSpaceReturn = Fee_ExtGetFreeSpace( AreaNo, LimitSearchMngArea, LimitDataAreaByte, &FeeFreeSpaceInfo );
            if ( FeeFreeSpaceReturn == (Fee_ExtFreeSpaceReturnType)FEE_EXT_E_FRSP_OK )
            {
                MscdFreeSpaceReturn = MSCD_E_FREESPACE_OK;
                Mscd_FreeSpace_TransformFreeSpaceInfo( FreeSpaceInfoPtr, &FeeFreeSpaceInfo );
            }
            else if ( FeeFreeSpaceReturn == (Fee_ExtFreeSpaceReturnType)FEE_EXT_E_FRSP_PARAM_ERROR )
            {
                MscdFreeSpaceReturn = MSCD_E_FREESPACE_PARAM_ERROR;
            }
            else if ( FeeFreeSpaceReturn == (Fee_ExtFreeSpaceReturnType)FEE_EXT_E_FRSP_BUSY )
            {
                MscdFreeSpaceReturn = MSCD_E_FREESPACE_BUSY;
            }
            else if ( FeeFreeSpaceReturn == (Fee_ExtFreeSpaceReturnType)FEE_EXT_E_FRSP_AREA_FAULT )
            {
                MscdFreeSpaceReturn = MSCD_E_FREESPACE_AREA_FAULT;
            }
            else if ( FeeFreeSpaceReturn == (Fee_ExtFreeSpaceReturnType)FEE_EXT_E_FRSP_INTERNAL_ERROR )
            {
                MscdFreeSpaceReturn = MSCD_E_FREESPACE_INTERNAL_ERROR;
            }
            else /* Unlikely case. */
            {
                MscdFreeSpaceReturn = MSCD_E_FREESPACE_INTERNAL_ERROR;
            }
        }
        else
        {
            MscdFreeSpaceReturn = MSCD_E_FREESPACE_MS_SUSPEND;
        }
    }
    else
    {
        MscdFreeSpaceReturn = MSCD_E_FREESPACE_PARAM_ERROR;
    }

    return MscdFreeSpaceReturn;
}
#endif /*( MSCD_FREESPACE_USE == STD_ON )*/

#define MSCD_STOP_SEC_CODE
#include <Mscd_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/10/15                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
