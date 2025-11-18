/* Fee_Hook.c v1-0-0                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/HOOK/CODE                                             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Fee.h>

#include "../inc/Fee_Mpu_Dev_Const.h"

/* MHA (Data Flash) I/F header */
#include "../inc/Fee_Legacy.h"

/* MHA header */
#include "../inc/Fee_Lib.h"

/* MHA library header */
#include "../inc/Fee_Common.h"
#include "../inc/Fee_Hook_Internal.h"

/* D.F.C. header */
#include "../inc/Fee_Dfc.h"

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* Function Name | Fee_RspHook                                              */
/* Description   | Response Hook calling common processing                  */
/* Preconditions | None                                                     */
/* Parameters    | stCPUDTF * ptstCPUDTFInfo                                */
/*               |             MHA management data                          */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_RspHook( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo)
{
    uint8   u1tProcessStatus;   /* Operational status */
    uint8   u1tResult;          /* Process successful */
    uint16  u2tDATA_ID;         /* DATA-ID */
    uint8   u1tAreaNum;         /* Area number */

    /* Eject operating status */
    u1tProcessStatus = ptstCPUDTFInfo->u1ProcessStatus;
    /* Retrieve processing results */
    u1tResult = ptstCPUDTFInfo->u1Result;
    /* DATA-ID Eject */
    u2tDATA_ID = ptstCPUDTFInfo->u2DATA_ID;
    /* Eject Area Number */
    u1tAreaNum = ptstCPUDTFInfo->u1AreaNum;

    /* Last write record position */
    if ( ptstCPUDTFInfo->u1LastWritePosFlag == FEE_FLAG_ON )
    {
        /* Last write record position update allowed flag is updatable */
        /* Final write record position preservation */
        /* Return value is not checked. */
        (void)Fee_SetLastWritePos( ptstCPUDTFInfo );
    }

    /* Initialize MHA management data */
    Fee_InitCpuDtfData( ptstCPUDTFInfo );

    /* Response Hook call by activity state */
    Fee_CallRspHook( u1tProcessStatus, u1tResult, u2tDATA_ID, u1tAreaNum );
    
    return;
}

/****************************************************************************/
/* Function Name | Fee_CallRspHook                                          */
/* Description   | Responsive Hook call                                     */
/* Preconditions | None                                                     */
/* Parameters    | uint8  u1tProcessStatus       : Operating status         */
/*               | uint8  u1tResult              : ProcessSuccess           */
/*               | uint16 u2tDATA_ID             : DATA-ID                  */
/*               | uint8  u1tAreaNum             : area number              */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_CallRspHook(
    uint8   u1tProcessStatus,
    uint8   u1tResult,
    uint16  u2tDATA_ID,
    uint8   u1tAreaNum
){
    switch( u1tProcessStatus )
    {
        case FEE_STATUSWRITE:   /* WRITING (STATUS _ WRITE) */
            /* Data write response Hook */
            Fee_Write_Rsp_Hook( u1tResult, u2tDATA_ID, u1tAreaNum );
            break;

        case FEE_STATUSIDREAD:  /* Reading ID designation data (STATUS _ IDREAD) */
            /* Data read response Hook (ID specified) */
            Fee_Read_Rsp_Hook( u1tResult, u2tDATA_ID, u1tAreaNum );
            break;

        case FEE_STATUSMOVE:    /* Data Restructuring (STATUS _ MOVE) */
            /* Data Restructuring Response Hook */
            Fee_Rebuild_Rsp_Hook( u1tResult, u1tAreaNum );
            break;

        default:                /* Is operating in any other state (impossible) */
            /* No process */
            break;
    }

    return;
}

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
