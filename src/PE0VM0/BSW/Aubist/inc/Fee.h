/* Fee.h v2-0-0                                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/HEADER                                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef FEE_H
#define FEE_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include "../Fee/cfg/Fee_Cfg.h"
#include "../Fee/cfg/Fee_Lcfg.h"
#include "../Fee/cfg/Fee_Wcfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

#define FEE_VENDOR_ID                   ( 0x0053U )
#define FEE_MODULE_ID                   ( 0x0015U )
#define FEE_AR_RELEASE_MAJOR_VERSION    ( 0x04U )
#define FEE_AR_RELEASE_MINOR_VERSION    ( 0x05U )
#define FEE_AR_RELEASE_REVISION_VERSION ( 0x00U )
#define FEE_SW_MAJOR_VERSION            ( 0x02U )
#define FEE_SW_MINOR_VERSION            ( 0x00U )
#define FEE_SW_PATCH_VERSION            ( 0x00U )

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct {
    uint32      dummy;
} Fee_ConfigType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

FUNC( void,                FEE_CODE ) Fee_Init(
    P2CONST( Fee_ConfigType, AUTOMATIC, FEE_CONFIG_DATA ) ConfigPtr
);

FUNC( Std_ReturnType,      FEE_CODE )
Fee_Read(
    uint16 BlockNumber,
    uint16 BlockOffset,
    P2VAR( uint8, AUTOMATIC, TYPEDEF ) DataBufferPtr,
    uint16 Length
);

FUNC( Std_ReturnType,      FEE_CODE )
Fee_Write(
    uint16 BlockNumber,
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) DataBufferPtr
);

FUNC( void,                FEE_CODE ) Fee_Cancel( void );

FUNC( MemIf_StatusType,    FEE_CODE ) Fee_GetStatus( void );

FUNC( MemIf_JobResultType, FEE_CODE ) Fee_GetJobResult( void );

FUNC( void,                FEE_CODE )
Fee_GetVersionInfo(
    P2VAR( Std_VersionInfoType, AUTOMATIC, FEE_APPL_DATA ) VersionInfoPtr
);

FUNC( void,                FEE_CODE)
Fee_MainFunction( void );

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

#endif    /* FEE_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  1-1-0          :2019/07/04                                              */
/*  2-0-0          :2022/08/24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
