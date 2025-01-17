/* MemIf.h v2-0-0                                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MEMIF/HEADER                                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef MEMIF_H
#define MEMIF_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <MemIf_Types.h>
#include <Fee.h>
#include <Fee_Ext.h>
#include "../MemIf/cfg/MemIf_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define MEMIF_BROADCAST_ID  (0xFFU)

#define MEMIF_VENDOR_ID                   (0x0053U)
#define MEMIF_MODULE_ID                   (0x0016U)
#define MEMIF_AR_RELEASE_MAJOR_VERSION    (0x04U)
#define MEMIF_AR_RELEASE_MINOR_VERSION    (0x05U)
#define MEMIF_AR_RELEASE_REVISION_VERSION (0x00U)
#define MEMIF_SW_MAJOR_VERSION            (0x02U)
#define MEMIF_SW_MINOR_VERSION            (0x00U)
#define MEMIF_SW_PATCH_VERSION            (0x00U)

#define MemIf_SetMode( Mode ) ( Fee_SetMode( ( Mode ) ) )
#define MemIf_Read( DeviceIndex, BlockNumber, BlockOffset, DataBufferPtr, Length ) ( Fee_Read( ( BlockNumber ), ( BlockOffset ), ( DataBufferPtr ), ( Length ) ) )
#define MemIf_Write( DeviceIndex, BlockNumber, DataBufferPtr ) ( Fee_Write( ( BlockNumber ), ( DataBufferPtr ) ) )
#define MemIf_Cancel( DeviceIndex ) ( Fee_Cancel() )
#define MemIf_GetStatus( DeviceIndex ) ( Fee_GetStatus() )
#define MemIf_GetJobResult( DeviceIndex ) ( Fee_GetJobResult() )
#define MemIf_InvalidateBlock( DeviceIndex, BlockNumber ) ( Fee_InvalidateBlock( ( BlockNumber ) ) )
#define MemIf_EraseImmediateBlock( DeviceIndex, BlockNumber ) ( Fee_EraseImmediateBlock( ( BlockNumber ) ) )
#define MemIf_ExtGetProductionError( DeviceIndex, BlockNumber, JobKind, Level ) ( Fee_ExtGetProductionError( ( BlockNumber ), ( JobKind ), ( Level ) ) )

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* External Reference                                                       */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define MEMIF_START_SEC_CODE
#include <MemIf_MemMap.h>

FUNC( void, MEMIF_CODE )
MemIf_GetVersionInfo(
    P2VAR( Std_VersionInfoType, AUTOMATIC, MEMIF_APPL_DATA ) VersionInfoPtr
);

#define MEMIF_STOP_SEC_CODE
#include <MemIf_MemMap.h>

#endif /* MEMIF_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  2-0-0          :2021/04/27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
