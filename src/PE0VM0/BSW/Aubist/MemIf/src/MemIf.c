/* MemIf.c v1-0-0                                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MEMIF/CODE                                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <MemIf.h>
#include "../inc/MemIf_Internal.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Global Variable                                                          */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define MEMIF_START_SEC_CONST_32
#include <MemIf_MemMap.h>

/* MemIf module version information */
CONST( Std_VersionInfoType, MEMIF_CONST ) MemIf_VersionInfo = {
    MEMIF_VENDOR_ID,          /* vendorID          */
    MEMIF_MODULE_ID,          /* moduleID          */
    MEMIF_SW_MAJOR_VERSION,   /* sw_major_version  */
    MEMIF_SW_MINOR_VERSION,   /* sw_minor_version  */
    MEMIF_SW_PATCH_VERSION    /* sw_patch_version  */
};

#define MEMIF_STOP_SEC_CONST_32
#include <MemIf_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

#define MEMIF_START_SEC_CODE
#include <MemIf_MemMap.h>
/****************************************************************************/
/* Function Name | MemIf_GetVersionInfo                                     */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | VersionInfoPtr : The pointer which stores away the       */
/*               |                  version information of this module.     */
/* Return Value  | None                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, MEMIF_CODE )
MemIf_GetVersionInfo(
    P2VAR( Std_VersionInfoType, AUTOMATIC, MEMIF_APPL_DATA ) VersionInfoPtr
){

    if( NULL_PTR != VersionInfoPtr )
    {
        *( VersionInfoPtr ) = MemIf_VersionInfo;
    }

    return;
}

#define MEMIF_STOP_SEC_CODE
#include <MemIf_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
