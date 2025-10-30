/* Fee_Write.c v1-1-0                                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/WRITE/CODE                                            */
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

/* D.F.C. header */
#include "../inc/Fee_Dfc.h"

#include "../inc/Fee_Record_Pos_Tbl.h"

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
/* Function Name | Fee_BWriteMain                                           */
/* Description   | Data write status management (with block management)     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Result of processing                                     */
/*               | 0x00000002 : u4gSTATUS_EXIT : Data writing               */
/*               |                               and non-continuable        */
/*               | 0x00000003 : u4gSTATUS_DONE : End of data write          */
/*               | 0x00000004 : u4gSTATUS_CONT : Data write and             */
/*               |                               can continue               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_BWriteMain( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* RETURN */

    /* Branch by main state */
    switch ( ptstCPUDTFInfo->u1MainStatus )
    {
        case FEE_MSTATUSWBIDLE:                 /* If main state is idle (MAIN _ STATUS _ W _ B _ IDLE) */
            /* Set main state to block selected (MAIN _ STATUS _ W _ B _ SEL) */
            ptstCPUDTFInfo->u1MainStatus = FEE_MSTATUSWBSEL;
            /* Block counter clear */
            ptstCPUDTFInfo->u4BlockCount = 0U;
            /* Set sub-state to 'Block status data determining' */
            ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWSFIX;
            /* Not set since there are no sub-sub-states while finalizing block status data */
            /* Set return value as data write and continuable */
            u4tReturn = FEE_STATUS_CONT;
            break;

        case FEE_MSTATUSWBSEL:                  /* When main status is write block selected (MAIN _ STATUS _ W _ B _ SEL) */
            /* Write block selection state management processing */
            u4tReturn = Fee_SelectWriteBlock( ptstCPUDTFInfo );
            break;

        case FEE_MSTATUSWBWRITE:                    /* When main status is record writing (MAIN _ STATUS _ W _ B _ WRITE) */
            /* Record write status management processing */
            u4tReturn = Fee_WriteRecord( ptstCPUDTFInfo );
            break;

        case FEE_MSTATUSWBMOVE:                 /* When main status is data transfer (MAIN _ STATUS _ W _ B _ MOVE) */
            /* Data transfer state management processing */
            u4tReturn = Fee_MoveData( ptstCPUDTFInfo );
            break;

        default:                                            /* If the main state is anything else */
            /* Valid Record Position TBL Initialization */
            Fee_RecordPosTbl_ClearPosArea( ptstCPUDTFInfo->u1AreaNum );
            if ( ptstCPUDTFInfo->u1ProcessStatus == FEE_STATUSWRITE )
            {
                /* If the operating status is write (STATUS _ WRITE) */
                /* Set result to write failed (RSP _ NG _ WRITE _ DATA) */
                ptstCPUDTFInfo->u1Result = FEE_RSP_NG_WRITE_DATA;
            }
            else
            {
                /* If the operating status is other than: Reorganize */
                /* Set Result to Reorganize Failed (RSP _ NG) */
                ptstCPUDTFInfo->u1Result = FEE_RSP_NG;
            }
            /* Set return value to end data write */
            u4tReturn = FEE_STATUS_DONE;
            break;
    }

    /* Return return value and finish processing */
    return u4tReturn;
}

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/07/04                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
