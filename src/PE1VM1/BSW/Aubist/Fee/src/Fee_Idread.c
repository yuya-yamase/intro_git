/* Fee_Idread.c v2-1-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/IDREAD/CODE                                           */
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
#include "../inc/Fee_Idread_Internal.h"

/* D.F.C. header */
#include "../inc/Fee_Dfc.h"

#include "../inc/Fee_Record_Pos_Tbl.h"

#include "../inc/Fee_FlsWrp.h"

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
/* Function Name | Fee_ReadMain                                             */
/* Description   | ID designation data read status management               */
/* Preconditions | None                                                     */
/* Parameters    | stCPUDTF * ptstCPUDTFInfo                                */
/*               |                 MHA management data                      */
/* Return Value  | Processing status                                        */
/*               | 0x00000002 : u4gSTATUS_EXIT : Reading                    */
/*               | 0x00000003 : u4gSTATUS_DONE : Processing ended           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_ReadMain( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* RETURN */
    
    /* Set return value to continue processing */
    u4tReturn = FEE_STATUS_CONT;
    while ( u4tReturn == FEE_STATUS_CONT )
    {
        /* Continue processing while processing continues */
        /* Branch by main state */
        switch ( ptstCPUDTFInfo->u1MainStatus )
        {
            case FEE_MSTATUSRIDLE:                  /* If main state is idle (MAIN _ STATUS _ R _ IDLE) */
                u4tReturn = Fee_ReadMainSelectReadBlock( ptstCPUDTFInfo );
                break;

            case FEE_MSTATUSRBSRCH:                 /* If the main state is searching for free space (MAIN _ STATUS _ R _ BSRCH) */
                u4tReturn = Fee_ReadMainSrchFreeSpace( ptstCPUDTFInfo );
                break;

            case FEE_MSTATUSRPREPISRCH:             /* When the main state is preparing to read ID designation data */
                u4tReturn = Fee_ReadMainPrepSrchReadData( ptstCPUDTFInfo );
                break;

            case FEE_MSTATUSRISRCH:                 /* When main status is reading ID designation data (MAIN _ STATUS _ R _ ISRCH) */
                u4tReturn = Fee_ReadMainSrchReadData( ptstCPUDTFInfo );
                break;

            default:                                            /* If the main state is anything else */
                /* Set processing result to no applicable data (RSP _ NODATA) */
                ptstCPUDTFInfo->u1Result = FEE_RSP_NODATA;
                /* Set return value to end processing */
                u4tReturn = FEE_STATUS_DONE;
                break;
        }
    }

    /* Return return value and finish processing */
    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_ReadMainSelectReadBlock                              */
/* Description   | ID-specified data read status management (idle)          */
/* Preconditions | None                                                     */
/* Parameters    | stCPUDTF * ptstCPUDTFInfo                                */
/*               |                 MHA management data                      */
/* Return Value  | Processing status                                        */
/*               | 0x00000002 : u4gSTATUS_EXIT : Reading                    */
/*               | 0x00000003 : u4gSTATUS_DONE : Processing ended           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_ReadMainSelectReadBlock( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* RETURN */
    uint32          u4tSelResult;                               /* Result of read block selection */
    uint32          u4tRcrdDataAreaStartAbsAddr;
    uint32          u4tBlockStartAddr;
    Std_ReturnType  u1_dfPrepare;

    /* Preparing for MemAcc data flash access. */
    u1_dfPrepare = Fee_FlsWrp_ExtDfPreExecution();
    if( u1_dfPrepare == (Std_ReturnType)E_OK )
    {
        /* Read block selection processing */
        u4tSelResult = Fee_SelectReadBlock( ptstCPUDTFInfo );
        if ( u4tSelResult == FEE_STATUS_OK )
        {
            /* for successful selection */
            /* Is the last write record position valid? */
            if ( ptstCPUDTFInfo->u4WriteLastRecMngAbsAddr != FEE_ADDRESS_INVALID )
            {
                /* If last write record position is enabled */
                /* Set read search start address to last write record position */
                ptstCPUDTFInfo->u4ReadSrchAddress = ptstCPUDTFInfo->u4WriteLastRecMngAbsAddr;
    
                ptstCPUDTFInfo->u1MainStatus = FEE_MSTATUSRPREPISRCH;
            }
            else
            {
                /* If last write record position is invalid */
                /* Set read search start address to last record of block */
                u4tBlockStartAddr = FEE_BLKSTARTADDRTBL[ptstCPUDTFInfo->u1MainBlockNo];
                u4tRcrdDataAreaStartAbsAddr = u4tBlockStartAddr
                                              + (uint32)( ptstCPUDTFInfo->ptstAreaInf->u2RcrdDataAreaStartAddr );
                ptstCPUDTFInfo->u4ReadSrchAddress = u4tRcrdDataAreaStartAbsAddr - (uint32)FEE_RECORDMNGINFOLEN;
    
                /* Set main state to searching for free space (MAIN _ STATUS _ R _ BSRCH) */
                ptstCPUDTFInfo->u1MainStatus = FEE_MSTATUSRBSRCH;
            }
            /* Set return value to continue processing */
            u4tReturn = FEE_STATUS_CONT;
        }
        else if ( u4tSelResult == FEE_STATUS_NODATA )
        {
            /* If all blocks are unused */
            /* Set result to unblocked (RSP _ UNUSED) */
            ptstCPUDTFInfo->u1Result = FEE_RSP_UNUSED;
            /* Set return value to end processing */
            u4tReturn = FEE_STATUS_DONE;
        }
        else
        {
            /* Otherwise: In case of selection failure */
            /* Set processing result to no applicable data (RSP _ NODATA) */
            ptstCPUDTFInfo->u1Result = FEE_RSP_NODATA;
            /* Set return value to end processing */
            u4tReturn = FEE_STATUS_DONE;
        }
    }
    else
    {
        /* Set return value to exit */
        u4tReturn = FEE_STATUS_EXIT;
    }

    /* Return return value and finish processing */
    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_ReadMainSrchFreeSpace                                */
/* Description   | ID-specified data read status management                 */
/*               | (searching for free space)                               */
/* Preconditions | None                                                     */
/* Parameters    | stCPUDTF * ptstCPUDTFInfo                                */
/*               |                 MHA management data                      */
/* Return Value  | Processing status                                        */
/*               | 0x00000002 : u4gSTATUS_EXIT : Reading                    */
/*               | 0x00000003 : u4gSTATUS_DONE : Processing ended           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_ReadMainSrchFreeSpace( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* RETURN */
    uint32          u4tSrchFSResult;                            /* Free space search results */

    /* Free space search */
    u4tSrchFSResult = Fee_SrchFreeSpace( ptstCPUDTFInfo );
    /* Branch by return */
    switch ( u4tSrchFSResult )
    {
        case FEE_STATUS_OK:             /* If the return value is in use (STATUS _ OK) */
            /* Set tail-record retention data update permission flag to allowed (FLAG _ ON) */
            ptstCPUDTFInfo->u1LastWritePosFlag = FEE_FLAG_ON;
            /* Set search result address to write destination address when data is written and transferred */
            ptstCPUDTFInfo->u4WriteLastRecMngAbsAddr = ptstCPUDTFInfo->u4ReadSrchAddress;
            ptstCPUDTFInfo->u4WriteLastRecDatAbsAddr = FEE_ADDRESS_INVALID;

            ptstCPUDTFInfo->u1MainStatus = FEE_MSTATUSRPREPISRCH;
            /* Set return value to continue processing */
            u4tReturn = FEE_STATUS_CONT;
            break;

        case FEE_STATUS_NG:             /* If the return value is unused (STATUS _ NG) */
            /* Set tail-record retention data update permission flag to allowed (FLAG _ ON) */
            ptstCPUDTFInfo->u1LastWritePosFlag = FEE_FLAG_ON;
            /* Set search result address to write destination address when data is written and transferred */
            ptstCPUDTFInfo->u4WriteLastRecMngAbsAddr = ptstCPUDTFInfo->u4ReadSrchAddress;
            ptstCPUDTFInfo->u4WriteLastRecDatAbsAddr = FEE_ADDRESS_INVALID;
            /* Set processing result to no applicable data (RSP _ NODATA) */
            ptstCPUDTFInfo->u1Result = FEE_RSP_NODATA;
            /* Set return value to end processing */
            u4tReturn = FEE_STATUS_DONE;
            break;

        case FEE_STATUS_BUSY:           /* If the return value is ongoing (STATUS _ BUSY) */
            /* Set return value to reading (STATUS _ EXIT) */
            u4tReturn = FEE_STATUS_EXIT;
            break;

        default:                                    /* Other */
            /* Set processing result to no applicable data (RSP _ NODATA) */
            ptstCPUDTFInfo->u1Result = FEE_RSP_NODATA;
            /* Set return value to end processing */
            u4tReturn = FEE_STATUS_DONE;
            break;
    }

    /* Return return value and finish processing */
    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_ReadMainPrepSrchReadData                             */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_ReadMainPrepSrchReadData( P2VAR(Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT) ptstCPUDTFInfo )
{
    Fee_Record_StateScRdStart();
    /* Set main status to reading ID designation data (MAIN_STATUS_R_ISRCH) */
    ptstCPUDTFInfo->u1MainStatus = FEE_MSTATUSRISRCH;

    return FEE_STATUS_CONT;
}

/****************************************************************************/
/* Function Name | Fee_ReadMainSrchReadData                                 */
/* Description   | ID-specified data reading status management              */
/*               | (ID-specified data reading)                              */
/* Preconditions | None                                                     */
/* Parameters    | stCPUDTF * ptstCPUDTFInfo                                */
/*               |                 MHA management data                      */
/* Return Value  | Processing status                                        */
/*               | 0x00000002 : u4gSTATUS_EXIT : Reading                    */
/*               | 0x00000003 : u4gSTATUS_DONE : Processing ended           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_ReadMainSrchReadData( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* RETURN */
    uint32          u4tReadActStatus;
    uint32          u4tReadExecResult;

    u4tReadActStatus = Fee_Record_StateScRdExec( ptstCPUDTFInfo, &u4tReadExecResult );
    switch ( u4tReadActStatus )
    {
        case FEE_STATUS_EXIT:
            u4tReturn = FEE_STATUS_EXIT;
            break;

        case FEE_STATUS_DONE:
            switch ( u4tReadExecResult )
            {
                case FEE_STATUS_OK:
                    ptstCPUDTFInfo->u1Result = FEE_RSP_OK;
                    break;
                case FEE_STATUS_INVALID:
                case FEE_STATUS_NG:
                default:
                    ptstCPUDTFInfo->u1Result = FEE_RSP_NODATA;
                    break;
            }
            u4tReturn = FEE_STATUS_DONE;
            break;

        case FEE_STATUS_NG:
        default:
            ptstCPUDTFInfo->u1Result = FEE_RSP_NODATA;
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
/*  1-1-0          :2019/08/19                                              */
/*  2-0-0          :2021/07/29                                              */
/*  2-1-0          :2024/09/04                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

