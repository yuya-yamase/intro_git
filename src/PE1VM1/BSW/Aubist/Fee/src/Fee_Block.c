/* Fee_Block.c v2-1-0                                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/BLOCK/CODE                                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Fee.h>

#include "../inc/Fee_Ram.h"
#include "../inc/Fee_Common.h"

#include "../inc/Fee_Block_Internal.h"

#include <Mscd_Common.h>

#include "../inc/Fee_ExConst.h"

#include "../inc/Fee_Dfc.h"
#include "../inc/Fee_DfcMpu.h"
#include "../inc/Fee_Mpu_Dev_Const.h"
#include "../inc/Fee_Lib.h"
#include "../inc/Fee_Legacy.h"
#include "../inc/Fee_Record_Pos_Tbl.h"
#include "../inc/Fee_FlsWrp.h"

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define FEE_BSDATAPOS_USED            (0U)
#define FEE_BSDATAPOS_MOVE            (1U)
#define FEE_BSDATAPOS_USING           (2U)
#define FEE_VALIDBLKNUM               (2U)

#define FEE_VALIDBLKNUM_00            (0U)
#define FEE_VALIDBLKNUM_01            (1U)
#define FEE_VALIDBLKNUM_02            (2U)

#define FEE_USEBLKNUM_02              (2U)
#define FEE_USEBLKNUM_03              (3U)
/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define FEE_START_SEC_CONST_32
#include <Fee_MemMap.h>

/* Block status data determination transition destination determination table */
CONST(AB_83_ConstV uint8, FEE_CONST) Fee_FixBSJudgeTBL[FEE_BSJUDGESTATUSKINDNUM][FEE_BSJUDGESTATUSKINDNUM][FEE_BSJUDGESTATUSNUM] = 
{
    /* Dest Substate        Dest SubSubstate           Main Block       Sub Block       */
    {{FEE_SSTATUSINVALID,   FEE_SSSTATUSINVALID},   /* In use           In use          */
    {FEE_SSTATUSINVALID,    FEE_SSSTATUSINVALID},   /* In use           Transferring    */
    {FEE_SSTATUSWWIDLE,     FEE_SSSTATUSINVALID},   /* In use           In Use          */
    {FEE_SSTATUSWWIDLE,     FEE_SSSTATUSINVALID},   /* In use           Not used        */
    {FEE_SSTATUSWWIDLE,     FEE_SSSTATUSINVALID}},  /* Incorrect        In use          */
    
    {{FEE_SSTATUSWSMOV,     FEE_SSSTATUSWSMWERSG},  /* Transferring     In use          */
    {FEE_SSTATUSWSMOV,      FEE_SSSTATUSWSMWERSG},  /* Transferring     Transferring    */
    {FEE_SSTATUSWSMOV,      FEE_SSSTATUSWSMWUSD},   /* Transferring     Used            */
    {FEE_SSTATUSWSMOV,      FEE_SSSTATUSWSMWERSG},  /* Transferring     Not used        */
    {FEE_SSTATUSWSMOV,      FEE_SSSTATUSWSMWERSG}}, /* Transferring     Incorrect       */
    
    {{FEE_SSTATUSINVALID,   FEE_SSSTATUSINVALID},   /* Used             In use          */
    {FEE_SSTATUSINVALID,    FEE_SSSTATUSINVALID},   /* Used             Transferring    */
    {FEE_SSTATUSWSUSG,      FEE_SSSTATUSWSUWERSG},  /* Used             Used            */
    {FEE_SSTATUSWSUSG,      FEE_SSSTATUSWSUWERSG},  /* Used             Not used        */
    {FEE_SSTATUSWSUSG,      FEE_SSSTATUSWSUWERSG}}, /* Used             Incorrect       */
    
    {{FEE_SSTATUSINVALID,   FEE_SSSTATUSINVALID},   /* Not used         In use          */
    {FEE_SSTATUSINVALID,    FEE_SSSTATUSINVALID},   /* Not used         Transferring    */
    {FEE_SSTATUSWSUSG,      FEE_SSSTATUSWSUWERSG},  /* Not used         Used            */
    {FEE_SSTATUSWSUSG,      FEE_SSSTATUSWSUWERSG},  /* Not used         Not used        */
    {FEE_SSTATUSWSUSG,      FEE_SSSTATUSWSUWERSG}}, /* Not used         Incorrect       */
    
    {{FEE_SSTATUSINVALID,   FEE_SSSTATUSINVALID},   /* Incorrect        In use          */
    {FEE_SSTATUSINVALID,    FEE_SSSTATUSINVALID},   /* Incorrect        Transferring    */
    {FEE_SSTATUSWSUSG,      FEE_SSSTATUSWSUWERSG},  /* Incorrect        Used            */
    {FEE_SSTATUSWSUSG,      FEE_SSSTATUSWSUWERSG},  /* Incorrect        Not used        */
    {FEE_SSTATUSWSUSG,      FEE_SSSTATUSWSUWERSG}}  /* Incorrect        Incorrect       */
};

/* Block status determination table */
CONST(AB_83_ConstV uint8, FEE_CONST) Fee_JudgeBSTBL[FEE_BSDATARANGE][FEE_BSDATAPOSNUM][FEE_BSDATAKINDNUM] = 
{
    /* Block status         In use,     Transferring    In use  */
    {{FEE_BS_UNUSED,     /* Erase       Erase           Erase   */
      FEE_BS_ILLEGAL,    /* Erase       Erase           5A      */
      FEE_BS_ILLEGAL},   /* Erase       Erase           Other   */
    
    {FEE_BS_ILLEGAL,     /* Erase       5A              Erase   */
     FEE_BS_ILLEGAL,     /* Erasure     5A              5A      */
     FEE_BS_ILLEGAL},    /* Erase       5A              Other   */
    
    {FEE_BS_ILLEGAL,     /* Erase       Other           Erase   */
     FEE_BS_ILLEGAL,     /* Erase       Other           5A      */
     FEE_BS_ILLEGAL}},   /* Erase       Other           Other   */
    
    {{FEE_BS_USING,      /* 5A          Erase           Erase   */
      FEE_BS_USED,       /* 5A          Erase           5A      */
      FEE_BS_USED},      /* 5A          ERASE           Other   */
    
    {FEE_BS_MOVE,        /* 5A          5A              Erase   */
     FEE_BS_USED  ,      /* 5A          5A              5A      */
     FEE_BS_USED},       /* 5A          5A              Other   */
    
    {FEE_BS_USING,       /* 5A          Other           Erase   */
     FEE_BS_USED,        /* 5A          Other           5A      */
     FEE_BS_USED}},      /* 5A          Other           Other   */
    
    {{FEE_BS_ILLEGAL,    /* Other       Erase           Erase   */
      FEE_BS_ILLEGAL,    /* Other       Erase           5A      */
      FEE_BS_ILLEGAL},   /* Other       Erase           Other   */
    
    {FEE_BS_ILLEGAL,     /* Other       5A              Erase   */
     FEE_BS_ILLEGAL,     /* Other       5A              5A      */
     FEE_BS_ILLEGAL},    /* Other       5A              Other   */
    
    {FEE_BS_ILLEGAL,     /* Other       Other           Erase   */
     FEE_BS_ILLEGAL,     /* Other       Other           5A      */
     FEE_BS_ILLEGAL}}    /* Other       Other           Other   */
};

/* Duplex Block Status Data Judgment Table (Area Status) */
CONST(AB_83_ConstV uint8, FEE_CONST) Fee_JudgeBSDataTBL_A[FEE_BSDATARANGE][FEE_BSDATARANGE] = 
{
    /* Block status data     fixed type                 2nd read result         1st read result */
    {(FEE_BSDATA_ERASE | FEE_BSFIXKIND_NONFIX),       /* Erase                  Erase           */
     (FEE_BSDATA_ERASE | FEE_BSFIXKIND_NONFIX),       /* Erase                  5A              */
     (FEE_BSDATA_ERASE | FEE_BSFIXKIND_NONFIX)},      /* Erase                  Other           */
    
    {(FEE_BSDATA_ERASE | FEE_BSFIXKIND_NONFIX),       /* 5A                     Erase           */
     (FEE_BSDATA_VALID | FEE_BSFIXKIND_NONFIX),       /* 5A                     5A              */
     (FEE_BSDATA_ERASE | FEE_BSFIXKIND_NONFIX)},      /* 5A                     Other           */
    
    {(FEE_BSDATA_ERASE | FEE_BSFIXKIND_NONFIX),       /* Other                  Erase           */
     (FEE_BSDATA_ERASE | FEE_BSFIXKIND_NONFIX),       /* Other                  5A              */
     (FEE_BSDATA_ERASE | FEE_BSFIXKIND_NONFIX)}       /* Other                  Ohter           */
};

/* Duplex Block Status Data Judgment Table (Used) */
CONST(AB_83_ConstV uint8, FEE_CONST) Fee_JudgeBSDataTBL_C[FEE_BSDATARANGE][FEE_BSDATARANGE] = 
{
    /* Block status data    fixed type                  2nd read result         1st read result */
    {(FEE_BSDATA_ERASE | FEE_BSFIXKIND_NONFIX),       /* Erase                  Erase           */
     (FEE_BSDATA_VALID | FEE_BSFIXKIND_FIXALL),       /* Erase                  5A              */
     (FEE_BSDATA_VALID | FEE_BSFIXKIND_FIXALL)},      /* Erase                  Other           */
    
    {(FEE_BSDATA_VALID | FEE_BSFIXKIND_FIXALL),       /* 5A                     Erase           */
     (FEE_BSDATA_VALID | FEE_BSFIXKIND_NONFIX),       /* 5A                     5A              */
     (FEE_BSDATA_VALID | FEE_BSFIXKIND_FIXALL)},      /* 5A                     Other           */
    
    {(FEE_BSDATA_VALID | FEE_BSFIXKIND_FIXALL),       /* Other                  Erase           */
     (FEE_BSDATA_VALID | FEE_BSFIXKIND_FIXALL),       /* Other                  5A              */
     (FEE_BSDATA_VALID | FEE_BSFIXKIND_FIXALL)}       /* Other                  Other           */
};

/* Duplex Block Status Data Judgment Table (In Use/In Transfer) */
CONST(AB_83_ConstV uint8, FEE_CONST) Fee_JudgeBSDataTBL_B[FEE_BSDATARANGE][FEE_BSDATARANGE] = 
{
    /* Block status data    fixed type                  2nd read result         1st read result */
    {(FEE_BSDATA_ERASE | FEE_BSFIXKIND_NONFIX),       /* Erase                  Erase           */
     (FEE_BSDATA_VALID | FEE_BSFIXKIND_FIXALL),       /* Erase                  5A              */
     (FEE_BSDATA_OTHER | FEE_BSFIXKIND_NONFIX)},      /* Erase                  Other           */
    
    {(FEE_BSDATA_VALID | FEE_BSFIXKIND_FIXALL),       /* 5A                     Erase           */
     (FEE_BSDATA_VALID | FEE_BSFIXKIND_NONFIX),       /* 5A                     5A              */
     (FEE_BSDATA_VALID | FEE_BSFIXKIND_FIXALL)},      /* 5A                     Other           */
    
    {(FEE_BSDATA_OTHER | FEE_BSFIXKIND_NONFIX),       /* Other                  Erase           */
     (FEE_BSDATA_VALID | FEE_BSFIXKIND_FIXALL),       /* Other                  5A              */
     (FEE_BSDATA_OTHER | FEE_BSFIXKIND_NONFIX)}       /* Other                  Other           */
};

#define FEE_STOP_SEC_CONST_32
#include <Fee_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* Function Name | Fee_SelectWriteBlock                                     */
/* Description   | Write block selection state management                   */
/* Preconditions | None                                                     */
/* Parameters    | stCPUDTF *ptstCPUDTFInfo                                 */
/*               |                   MHA management data                    */
/* Return Value  | Result of processing                                     */
/*               | 0x00000002 : u4gSTATUS _ EXIT: Write block selected,     */
/*               |              not continuable                             */
/*               | 0x00000003 : u4gSTATUS _ DONE: End write block selection */
/*               | 0x00000004 : u4gSTATUS _ CONT: Write block selected,     */
/*               |                               can continue               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_SelectWriteBlock( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* RETURN */
    
    /* Branch by substate */
    switch ( ptstCPUDTFInfo->u1SubStatus )
    {
        case FEE_SSTATUSWSFIX:  /* For "Block status data is being finalized" */
            /* Block status data finalization state management processing */
            u4tReturn = Fee_FixBlockStatus( ptstCPUDTFInfo );
            break;
        case FEE_SSTATUSWSUSG:  /* For "In use block creation" */
            /* In-use block creation status management processing */
            u4tReturn = Fee_MakeUseBlock( ptstCPUDTFInfo );
            break;
        case FEE_SSTATUSWSMOV:  /* "Transferring block in progress" */
            /* In-transit block creation status management processing */
            u4tReturn = Fee_MakeMoveBlock( ptstCPUDTFInfo );
            break;
        case FEE_SSTATUSWSWEMOV:    /* In the case of "Reorg end setting" */
            /* State management processing while restructuring termination is set */
            u4tReturn = Fee_SetMoveEnd( ptstCPUDTFInfo );
            break;
        case FEE_SSTATUSWSALLU: /* For "Area Disabled/Used Setting" */
            /* Area Disabled/Used Setting Status Management */
            u4tReturn = Fee_SetInvalidArea( ptstCPUDTFInfo );
            break;
        case FEE_SSTATUSWSFAIL: /* In case of "Used/Failure setting" */
            /* Used/fault setting status management processing */
            u4tReturn = Fee_SetFailBlock( ptstCPUDTFInfo );
            break;
        default:                            /* Otherwise */
            /* Valid Record Position TBL Initialization */
            Fee_RecordPosTbl_ClearPosArea( ptstCPUDTFInfo->u1AreaNum );
            /* Set Result to Reorganize Failed */
            ptstCPUDTFInfo->u1Result = FEE_RSP_NG;
            /* Set return value to "End write block selection" */
            u4tReturn = FEE_STATUS_DONE;
            break;
    }
    
    /* RETURN RETURN */
    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_FixBlockStatus                                       */
/* Description   | Block status data pending status management              */
/* Preconditions | None                                                     */
/* Parameters    | stCPUDTF *ptstCPUDTFInfo                                 */
/*               |                      MHA management data                 */
/* Return Value  | Result of processing                                     */
/*               |  0x00000002: u4gSTATUS _ EXIT: Finalizing and            */
/*               |                                not continuing            */
/*               |  0x00000003: u4gSTATUS _ DONE: Finalize                  */
/*               |  0x00000004: u4gSTATUS _ CONT: Finalize and can continue */
/* Notes         |  None                                                    */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_FixBlockStatus( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* RETURN */
    uint32          u4tResult;                                  /* Selected results */
    uint8           FixBSJudgeTBLMainBlockIndex;
    uint8           FixBSJudgeTBLSubBlockIndex;
    Std_ReturnType  u1_dfPrepare;
    
    /* Initialize selection with "Selection failed" */
    u4tResult = FEE_STATUS_NG;

    /* If block status is not remembered */
    if ( (ptstCPUDTFInfo->u1MainBlockStatus == FEE_BS_INVALID)
        || (ptstCPUDTFInfo->u1SubBlockStatus == FEE_BS_INVALID) )
    {
        /* Preparing for MemAcc data flash access. */
        u1_dfPrepare = Fee_FlsWrp_ExtDfPreExecution();
        if( u1_dfPrepare == (Std_ReturnType)E_OK )
        {
            /* All block status determination processing */
            u4tReturn = Fee_JudgeAllBS( ptstCPUDTFInfo );
            /* In case of "Judgment ends" */
            if ( u4tReturn == FEE_STATUS_DONE )
            {
                /* In-use block selection processing */
                u4tResult = Fee_SelectUseBlock( ptstCPUDTFInfo );
                /* For "Successful Selection" */
                if ( u4tResult == FEE_STATUS_OK )
                {
                    /* Do the same as if the block status had been memorized */
                    /* Select next sub-state and sub-sub-state from block status combinations */
                }
                /* For "Unblocked" */
                else if ( u4tResult == FEE_STATUS_NODATA )
                {
                    /* Set substate to "In Use Blocking" */
                    ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWSUSG;
                    /* Set subsubstate to 'Blocking in use - Waiting for setting in use' */
                    ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSUWUSG;
                }
                /* For "selection failed" */
                else
                {
                    /* Set sub status to "Area Disabled/Used Setting" */
                    ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWSALLU;
                    /* Set sub sub status to "Area Disabled/Used Setting - Idle" */
                    ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSAIDLE;
                }
                /* Set return value to EXIT */
                u4tReturn = FEE_STATUS_EXIT;
            }
            /* In case of "Judging/Uncontinuable" */
            else
            {
                /* No process to return the return value */
            }
        }
        else
        {
            /* Set return value to EXIT */
            u4tReturn = FEE_STATUS_EXIT;
        }
    }
    /* If block status is remembered */
    else
    {
        /* Set return value to "Firming/Continuable" */
        u4tReturn = FEE_STATUS_CONT;
        /* Set Selection Success for Selection Results */
        u4tResult = FEE_STATUS_OK;
    }
    
    /* If the selection is "Selection success" */
    if ( u4tResult == FEE_STATUS_OK )
    {
        FixBSJudgeTBLMainBlockIndex = ptstCPUDTFInfo->u1MainBlockStatus - (uint8)FEE_FIX_BS_JUDGE_TBL_OFFSET;
        FixBSJudgeTBLSubBlockIndex  = ptstCPUDTFInfo->u1SubBlockStatus - (uint8)FEE_FIX_BS_JUDGE_TBL_OFFSET;
        /* Block status range check */
        if ( ( FixBSJudgeTBLMainBlockIndex < (uint8)FEE_BSJUDGESTATUSKINDNUM ) && ( FixBSJudgeTBLSubBlockIndex < (uint8)FEE_BSJUDGESTATUSKINDNUM ) )
        {
            /* Select next sub-state, sub-sub-state from block status combination */
            ptstCPUDTFInfo->u1SubStatus = Fee_FixBSJudgeTBL[FixBSJudgeTBLMainBlockIndex][FixBSJudgeTBLSubBlockIndex][FEE_FIX_BSTBLINDEX_SSTATUS];
            ptstCPUDTFInfo->u1SubSubStatus = Fee_FixBSJudgeTBL[FixBSJudgeTBLMainBlockIndex][FixBSJudgeTBLSubBlockIndex][FEE_FIX_BSTBLINDEX_SSSTATUS];

            /* Substate writing record - idle */
            if ( ptstCPUDTFInfo->u1SubStatus == FEE_SSTATUSWWIDLE )
            {
                /* When the operating status is "Reorganizing data" */
                if ( ptstCPUDTFInfo->u1ProcessStatus == FEE_STATUSMOVE )
                {
                    /* Overwrite next substate, subsubstate */
                    /* Set sub-state to 'Transferring block creation' */
                    ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWSMOV;
                    /* Set subsubstate to "Transferring block creation - Transferring pending setup" */
                    ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSMWMOVE;
                }
                /* When the operating status is Writing */
                else
                {
                    /* Set main state to "record writing" */
                    ptstCPUDTFInfo->u1MainStatus = FEE_MSTATUSWBWRITE;
                }
            }
            /* Incorrect substate */
            else if ( ptstCPUDTFInfo->u1SubStatus == FEE_SSTATUSINVALID )
            {
                /* Set Result to Reorganize Failed */
                ptstCPUDTFInfo->u1Result = FEE_RSP_NG;
                /* Set return value to DONE */
                u4tReturn = FEE_STATUS_DONE;
            }
            /* Otherwise */
            else
            {
                /* No process */
            }
        }
        /* Otherwise */
        else
        {
            /* No process */
        }
    }
    /* Otherwise */
    else
    {
        /* No process */
    }
    
    /* RETURN RETURN */
    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_MakeUseBlock                                         */
/* Description   | In-use block creation status management                  */
/* Preconditions | None                                                     */
/* Parameters    | stCPUDTF *ptstCPUDTFInfo                                 */
/*               |                       MHA management data                */
/* Return Value  | Result of processing                                     */
/*               | 0x00000002: u4gSTATUS _ EXIT: Creating block in use,     */
/*               |                               not allowed to continue    */
/*               | 0x00000003: u4gSTATUS _ DONE: End block creation in use  */
/*               | 0x00000004: u4gSTATUS _ CONT: Creating block in use,     */
/*               |                               can continue               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_MakeUseBlock( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* RETURN */
    
    /* Set return value to "In use, creating block, not continuable" */
    u4tReturn = FEE_STATUS_EXIT;
    /* Branch by subsubstate */
    switch ( ptstCPUDTFInfo->u1SubSubStatus )
    {
        case FEE_SSSTATUSWSUWERSG:  /* For "Waiting to be erased" */
            /* Start erasing main block */
            Fee_StartErase( ptstCPUDTFInfo->u1MainBlockNo );
            /* Set subsubstate to "cleaning" */
            ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSUERSG;
            break;
        case FEE_SSSTATUSWSUWUSG:   /* For "Waiting for use" */
            /* Set main block status to "In Use" */
            Fee_WriteBlockStatus( ptstCPUDTFInfo->u1MainBlockNo,
                                            (uint32)FEE_BS_USING,
                                            FEE_BSWRITE_ALL );
            /* Set subsubstate to "In Use" */
            ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSUUSG;
            break;
        case FEE_SSSTATUSWSUERSG:   /* For "Erasing" */
            u4tReturn = Fee_MakeUseBlock_DoErasing( ptstCPUDTFInfo );
            break;
        case FEE_SSSTATUSWSUUSG:        /* For "In use" */
            u4tReturn = Fee_MakeUseBlock_DoWritingUsing( ptstCPUDTFInfo );
            break;
        default:                                /* Otherwise */
            /* Valid Record Position TBL Initialization */
            Fee_RecordPosTbl_ClearPosArea( ptstCPUDTFInfo->u1AreaNum );
            /* When the processing result is other than "Write successful/No target block" */
            if ( ptstCPUDTFInfo->u1Result != FEE_RSP_NG_INITIALIZE )
            {
                /* Set Result to Reorganize Failed */
                ptstCPUDTFInfo->u1Result = FEE_RSP_NG;
            }
            /* When the processing result is "Write successful, no target block" */
            else
            {
                /* Set processing result to "write failed, no target block" */
                ptstCPUDTFInfo->u1Result = FEE_RSP_NG_NODATA;
            }
            /* Set return value to "End in use block creation" */
            u4tReturn = FEE_STATUS_DONE;
            break;
    }
    
    /* RETURN RETURN */
    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_MakeUseBlock_DoErasing                               */
/* Description   | In-use block creation status management (erasing)        */
/* Preconditions | None                                                     */
/* Parameters    | stCPUDTF *ptstCPUDTFInfo                                 */
/*               |                          MHA management data             */
/* Return Value  | Result of processing                                     */
/*               | 0x00000002: u4gSTATUS _ EXIT: Creating block in use,     */
/*               |                               not allowed to continue    */
/*               | 0x00000003: u4gSTATUS _ DONE: End block creation in use  */
/*               | 0x00000004: u4gSTATUS _ CONT: Creating block in use,     */
/*               |                               can continue               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_MakeUseBlock_DoErasing( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* RETURN */
    uint32          u4tResult;                                  /* Results */

    u4tReturn = FEE_STATUS_EXIT;

    /* Get data Flash control result */
    u4tResult = Fee_GetMngDfcResult( NULL_PTR );
    /* If no error */
    if ( u4tResult == FEE_STATUS_OK )
    {
        /* Set main block status to "In Use" */
        Fee_WriteBlockStatus( ptstCPUDTFInfo->u1MainBlockNo,
                                        (uint32)FEE_BS_USING,
                                        FEE_BSWRITE_ALL );
        /* Set subsubstate to "In Use" */
        ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSUUSG;
    }
    /* with error */
    else
    {
        /* Set sub sub status first, this is the order since it will save 16 bytes */
        /* Set sub sub status to "Used/Fault Setting - Main Block Fault Setting Waiting" */
        ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSFWMF;
        /* When the processing result is other than "Write successful/No target block" */
        if ( ptstCPUDTFInfo->u1Result != FEE_RSP_NG_INITIALIZE )
        {
            /* Set Result to Reorganize Failed */
            ptstCPUDTFInfo->u1Result = FEE_RSP_NG;
        }
        /* When the processing result is "Write successful, no target block" */
        else
        {
            /* Set processing result to "write failed, no target block" */
            ptstCPUDTFInfo->u1Result = FEE_RSP_NG_NODATA;
        }
        /* Set sub status to "Used/Fault Setting" */
        ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWSFAIL;
    }
    
    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_MakeUseBlock_DoWritingUsing                          */
/* Description   | In-use block creation status management (In use setting) */
/* Preconditions | None                                                     */
/* Parameters    | stCPUDTF *ptstCPUDTFInfo                                 */
/*               |          MHA management data                             */
/* Return Value  | Result of processing                                     */
/*               | 0x00000002: u4gSTATUS _ EXIT: Creating block in use,     */
/*               |                               not allowed to continue    */
/*               | 0x00000003: u4gSTATUS _ DONE: End block creation in use  */
/*               | 0x00000004: u4gSTATUS _ CONT: Creating block in use,     */
/*               |                               can continue               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_MakeUseBlock_DoWritingUsing( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* RETURN */
    uint32          u4tResult;                                  /* Results */

    u4tReturn = FEE_STATUS_EXIT;

    /* Get data Flash control result */
    u4tResult = Fee_GetMngDfcResult( NULL_PTR );
    /* If no error */
    if ( u4tResult == FEE_STATUS_OK )
    {
        /* Set main block status in use */
        ptstCPUDTFInfo->u1MainBlockStatus = FEE_BS_USING;
        /* When the operating status is Writing */
        if ( ptstCPUDTFInfo->u1ProcessStatus == FEE_STATUSWRITE )
        {
            /* Set main state to "record writing" */
            ptstCPUDTFInfo->u1MainStatus = FEE_MSTATUSWBWRITE;
            /* Set substate to "Record Writing - Idle" */
            ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWWIDLE;
        }
        /* Otherwise */
        else
        {
            /* When the processing result is other than "Write successful/No target block" */
            if ( ptstCPUDTFInfo->u1Result != FEE_RSP_NG_INITIALIZE )
            {
                /* Set Result to Reorganize Successful */
                ptstCPUDTFInfo->u1Result = FEE_RSP_OK;
            }
            /* Set return value to "End in use block creation" */
            u4tReturn = FEE_STATUS_DONE;
        }
    }
    /* with error */
    else
    {
        /* Set sub sub status first, this is the order since it will save 16 bytes */
        /* Set sub sub status to "Used/Fault Setting - Main Block Used Setting Waiting" */
        ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSFWMUSD;
        /* When the processing result is other than "Write successful/No target block" */
        if ( ptstCPUDTFInfo->u1Result != FEE_RSP_NG_INITIALIZE )
        {
            /* Set Result to Reorganize Failed */
            ptstCPUDTFInfo->u1Result = FEE_RSP_NG;
        }
        /* When the processing result is "Write successful, no target block" */
        else
        {
            /* Set processing result to "write failed, no target block" */
            ptstCPUDTFInfo->u1Result = FEE_RSP_NG_NODATA;
        }
        /* Set sub status to "Used/Fault Setting" */
        ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWSFAIL;
    }
    
    return u4tReturn;
}


/****************************************************************************/
/* Function Name | Fee_MakeMoveBlock                                        */
/* Description   | State management during transfer block creation          */
/* Preconditions | None                                                     */
/* Parameters    | stCPUDTF *ptstCPUDTFInfo                                 */
/*               |          MHA management data                             */
/* Return Value  | Result of processing                                     */
/*               | 0x00000002: u4gSTATUS _ EXIT: Creating block in transit, */
/*               |                               not allowed to continue    */
/*               | 0x00000003: u4gSTATUS _ DONE: End block creation         */
/*               |                               in transit                 */
/*               | 0x00000004: u4gSTATUS _ CONT: Creating block in transit, */
/*               |                               can continue               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_MakeMoveBlock( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* RETURN */
    uint32          u4tResult;                                  /* Results */
    
    /* Set return value to "Blocking in transit/Uncontinuable" */
    u4tReturn = FEE_STATUS_EXIT;
    /* Branch by subsubstate */
    switch ( ptstCPUDTFInfo->u1SubSubStatus )
    {
        case FEE_SSSTATUSWSMWMOVE:      /* For "Waiting for transfer settings" */
            /* Set main block status to "Transferring" */
            Fee_WriteBlockStatus( ptstCPUDTFInfo->u1MainBlockNo,
                                            (uint32)FEE_BS_MOVE,
                                            FEE_BSWRITE_ALL );
            /* Set subsubstate to "Setting transfer" */
            ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSMMOVE;
            break;
        case FEE_SSSTATUSWSMWUSD:       /* For "Waiting for used settings" */
            /* Set subblock status to "Used" */
            Fee_WriteBlockStatus( ptstCPUDTFInfo->u1SubBlockNo,
                                            (uint32)FEE_BS_USED,
                                            FEE_BSWRITE_ALL );
            /* Set sub sub status to 'Used Setting' */
            ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSMUSD;
            break;
        case FEE_SSSTATUSWSMWERSG:      /* For "Waiting to be erased" */
            /* Start erasing subblocks */
            Fee_StartErase( ptstCPUDTFInfo->u1SubBlockNo );
            /* Set subsubstate to "cleaning" */
            ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSMERSG;
            break;
        case FEE_SSSTATUSWSMMOVE:       /* For "forwarding setting" */
            /* Set main block status during transfer */
            ptstCPUDTFInfo->u1MainBlockStatus = FEE_BS_MOVE;
            /* Start erasing subblocks */
            Fee_StartErase( ptstCPUDTFInfo->u1SubBlockNo );
            /* Set subsubstate to "cleaning" */
            ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSMERSG;
            break;
        case FEE_SSSTATUSWSMUSD:            /* For "Used Setting" */
            /* Start erasing subblocks */
            Fee_StartErase( ptstCPUDTFInfo->u1SubBlockNo );
            /* Set subsubstate to "cleaning" */
            ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSMERSG;
            break;
        case FEE_SSSTATUSWSMERSG:       /* For "Erasing" */
            /* Get data Flash control result */
            u4tResult = Fee_GetMngDfcResult( NULL_PTR );
            /* If no error */
            if ( u4tResult == FEE_STATUS_OK )
            {
                /* Set subblock status to unused */
                ptstCPUDTFInfo->u1SubBlockStatus = FEE_BS_UNUSED;
                /* Set main state to "data transfer" */
                ptstCPUDTFInfo->u1MainStatus = FEE_MSTATUSWBMOVE;
                /* Set sub state to "Transferring data - Idle" */
                ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWMIDLE;
            }
            /* with error */
            else
            {
                /* Set Result to Reorganize Failed */
                ptstCPUDTFInfo->u1Result = FEE_RSP_NG;
                /* Set sub status to "Used/Fault Setting" */
                ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWSFAIL;
                /* Set sub sub status to "Used/Fault Setting - Wait for sub block fault setting" */
                ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSFWSF;
            }
            break;
        default:                                    /* Otherwise */
            /* Valid Record Position TBL Initialization */
            Fee_RecordPosTbl_ClearPosArea( ptstCPUDTFInfo->u1AreaNum );
            /* Set Result to Reorganize Failed */
            ptstCPUDTFInfo->u1Result = FEE_RSP_NG;
            /* Set return value to "end creating block in transit" */
            u4tReturn = FEE_STATUS_DONE;
            break;
    }
    
    /* RETURN RETURN */
    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_SetMoveEnd                                           */
/* Description   | State management during reorganization                   */
/*               | termination setting                                      */
/* Preconditions | None                                                     */
/* Parameters    | stCPUDTF *ptstCPUDTFInfo                                 */
/*               |                  MHA management data                     */
/* Return Value  | Result of processing                                     */
/*               | 0x00000002: u4gSTATUS _ EXIT: Reorg end set,             */
/*               |                               not allowed to continue    */
/*               | 0x00000003: u4gSTATUS _ DONE: End of reorganization      */
/*               |                               settings                   */
/*               | 0x00000004: u4gSTATUS _ CONT: Reorg end set,             */
/*               |                               can continue               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_SetMoveEnd( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;          /* RETURN */
    uint32          u4tResult;          /* Results */
    uint8           u1tWorkBlockNo;     /* For temporary work */
    Fee_UseBlockType    sttUseBlock;        /* Block data structure in use */
    Std_ReturnType      u1_dfPrepare;

    /* Branch by subsubstate */
    switch ( ptstCPUDTFInfo->u1SubSubStatus )
    {
        case FEE_SSSTATUSWSEIDLE:       /* For "Idol" */
            /* Set subblock status to In Use */
            Fee_WriteBlockStatus( ptstCPUDTFInfo->u1SubBlockNo,
                                            (uint32)FEE_BS_USING,
                                            FEE_BSWRITE_ALL );
            /* Set subsubstate to "In Use" */
            ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSEUSG;
            /* Set return value to "Reorg end set/Uncontinuable" */
            u4tReturn = FEE_STATUS_EXIT;
            break;
        case FEE_SSSTATUSWSEUSG:            /* For "In use" */
            /* Set EXIT in return */
            u4tReturn = FEE_STATUS_EXIT;
            /* Get data Flash control result */
            u4tResult = Fee_GetMngDfcResult( NULL_PTR );
            /* If no error */
            if ( u4tResult == FEE_STATUS_OK )
            {
                /* Set main block status to "Used" */
                Fee_WriteBlockStatus( ptstCPUDTFInfo->u1MainBlockNo,
                                                (uint32)FEE_BS_USED,
                                                FEE_BSWRITE_ALL );
                /* Set sub sub status to 'Used Setting' */
                ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSEUSD;
            }
            /* with error */
            else
            {
                /* Valid Record Position TBL Initialization */
                Fee_RecordPosTbl_ClearPosArea( ptstCPUDTFInfo->u1AreaNum );
                /* Set Result to Reorganize Failed */
                ptstCPUDTFInfo->u1Result = FEE_RSP_NG;
                /* Set sub status to "Used/Fault Setting" */
                ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWSFAIL;
                /* Set subsubstate to "Used/Fault Setting - Subblock Used Setting Waiting" */
                ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSFWSUSD;
            }
            break;
        case FEE_SSSTATUSWSEUSD:            /* For "Used Setting" */
            u4tReturn = FEE_STATUS_CONT;
            /* if number of blocks = 2 */
            if ( ptstCPUDTFInfo->ptstAreaInf->u1BlockNum == (uint8)FEE_USEBLKNUM_02 )
            {
                /* Swap main and subblocks */
                u1tWorkBlockNo = ptstCPUDTFInfo->u1MainBlockNo;
                ptstCPUDTFInfo->u1MainBlockNo = ptstCPUDTFInfo->u1SubBlockNo;
                ptstCPUDTFInfo->u1SubBlockNo = u1tWorkBlockNo;
                /* Set main block status in use */
                ptstCPUDTFInfo->u1MainBlockStatus = FEE_BS_USING;
                /* Set Subblock Status as Used */
                ptstCPUDTFInfo->u1SubBlockStatus = FEE_BS_USED;
            }
            /* 3 or more blocks */
            else
            {
                /* Preparing for MemAcc data flash access. */
                u1_dfPrepare = Fee_FlsWrp_ExtDfPreExecution();
                if( u1_dfPrepare == (Std_ReturnType)E_OK )
                {
                    /* Set subblock number to original subblock number */
                    u1tWorkBlockNo = ptstCPUDTFInfo->u1SubBlockNo;
                    /* Set subblock as main block */
                    ptstCPUDTFInfo->u1MainBlockNo = ptstCPUDTFInfo->u1SubBlockNo;
                    /* Set main block status in use */
                    ptstCPUDTFInfo->u1MainBlockStatus = FEE_BS_USING;
                    /* If the original subblock is the last block of the area */
                    if ( u1tWorkBlockNo >= (ptstCPUDTFInfo->ptstAreaInf->u1AreaLastBlockNum) )
                    {
                        /* Set top block of area as subblock */
                        ptstCPUDTFInfo->u1SubBlockNo = ptstCPUDTFInfo->ptstAreaInf->u1AreaStartBlockNum;
                    }
                    /* Otherwise */
                    else
                    {
                        /* Set next block after original subblock as subblock */
                        ptstCPUDTFInfo->u1SubBlockNo = u1tWorkBlockNo + (uint8)FEE_NEXT_BLOCKNUM_OFFSET;
                    }
                    /* Determine block status of subblocks */
                    /* Set subblock in used block data structure */
                    sttUseBlock.u1BlockNo = ptstCPUDTFInfo->u1SubBlockNo;
                    sttUseBlock.u1BlockStatus = FEE_BS_INVALID;
                    /* Block status determination */
                    /* Note: The return value of Fee_JudgeBSForRead is not checked. */
                    /*       It indicates whether FEE needs to fix BS. */
                    /*       In reading jobs, FEE do not fix BS. */
                    (void)Fee_JudgeBSForRead( &sttUseBlock );
                    /* Set Subblock */
                    ptstCPUDTFInfo->u1SubBlockNo = sttUseBlock.u1BlockNo;
                    ptstCPUDTFInfo->u1SubBlockStatus = sttUseBlock.u1BlockStatus;
                }
                else
                {
                    /* Set EXIT in return */
                    u4tReturn = FEE_STATUS_EXIT;
                }
            }
            
            if( u4tReturn != FEE_STATUS_EXIT )
            {
                /* When the operating status is Writing */
                if ( ptstCPUDTFInfo->u1ProcessStatus == FEE_STATUSWRITE )
                {
                    /* Set main state to "record writing" */
                    ptstCPUDTFInfo->u1MainStatus = FEE_MSTATUSWBWRITE;
                    /* Set substate to "Record Writing - Idle" */
                    ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWWIDLE;
                    /* Set EXIT in return */
                    u4tReturn = FEE_STATUS_EXIT;
                }
                /* Otherwise */
                else
                {
                    /* If there is a write-to address when data is written or transferred */
                    if(( ptstCPUDTFInfo->u4WriteLastRecMngAbsAddr != FEE_ADDRESS_INVALID )
                    && ( ptstCPUDTFInfo->u4WriteLastRecDatAbsAddr != FEE_ADDRESS_INVALID ))
                    {
                        /* Set last write record position update permission flag to "allow" */
                        ptstCPUDTFInfo->u1LastWritePosFlag = FEE_FLAG_ON;
                    }
                    /* Otherwise */
                    else
                    {
                        /* No process */
                    }
                    /* Set Result to Reorganize Successful */
                    ptstCPUDTFInfo->u1Result = FEE_RSP_OK;
                    /* Set return value to "Finish reorganization" */
                    u4tReturn = FEE_STATUS_DONE;
                }
            }
            break;
        default:                                    /* Otherwise */
            /* Valid Record Position TBL Initialization */
            Fee_RecordPosTbl_ClearPosArea( ptstCPUDTFInfo->u1AreaNum );
            /* Set Result to Reorganize Failed */
            ptstCPUDTFInfo->u1Result = FEE_RSP_NG;
            /* Set return value to "Finish reorganization" */
            u4tReturn = FEE_STATUS_DONE;
            break;
    }
    
    /* RETURN RETURN */
    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_SetInvalidArea                                       */
/* Description   | Area Disabled/Used Setting State Management              */
/* Preconditions | None                                                     */
/* Parameters    | stCPUDTF *ptstCPUDTFInfo                                 */
/*               |              MHA management data                         */
/* Return Value  | Result of processing                                     */
/*               | 0x00000002: u4gSTATUS _ EXIT: Area Disabled/Used Setting */
/*               |                               /Uncontinuable             */
/*               | 0x00000003: u4gSTATUS _ DONE: Area disabled              */
/*               |                               /Used settings ended       */
/*               | 0x00000004: u4gSTATUS _ CONT: Area Disabled/Used Setting */
/*               |                               /Continued                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_SetInvalidArea( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* RETURN */
    uint32          u4tResult;                                  /* Results */
    uint8           u1tBlockNum;                                /* Block number */
    uint32          u4tBSFixKind;                               /* Firm processing type */
    uint8           u1tWritePlace = FEE_BSWRITE_NOTWRITE;
    Std_ReturnType  u1_dfPrepare;
    
    /* Branch by subsubstate */
    switch ( ptstCPUDTFInfo->u1SubSubStatus )
    {
        case FEE_SSSTATUSWSAIDLE:       /* For "Idol" */
            /* Preparing for MemAcc data flash access. */
            u1_dfPrepare = Fee_FlsWrp_ExtDfPreExecution();
            if( u1_dfPrepare == (Std_ReturnType)E_OK )
            {
                /* Block counter initialisation */
                ptstCPUDTFInfo->u4BlockCount = 0x00000000UL;
                /* Set sub sub status to "Setting" */
                ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSASET;
                /* Block status data judgment (area status) */
                u4tResult = Fee_JudgeBSData( ptstCPUDTFInfo->ptstAreaInf->u1AreaStartBlockNum,
                                                        (uint32)FEE_BS_AREA,
                                                        &u4tBSFixKind,
                                                        &u1tWritePlace );
                /* Area in area status is blank */
                if ( u4tResult == (uint32)FEE_BSDATA_ERASE )
                {
                    /* Area Status Settings */
                    Fee_WriteBlockStatus( ptstCPUDTFInfo->ptstAreaInf->u1AreaStartBlockNum,
                                                    (uint32)FEE_BS_AREA,
                                                    u1tWritePlace );
                    /* Set return value to "Area disabled/Used set/Uncontinuable" */
                    u4tReturn = FEE_STATUS_EXIT;
                }
                /* Otherwise */
                else
                {
                    /* Set return value to "Area disabled/Used set/Continued" */
                    u4tReturn = FEE_STATUS_CONT;
                }
            }
            else
            {
                /* Set return value to "Area disabled/Used set/Uncontinuable" */
                u4tReturn = FEE_STATUS_EXIT;
            }
            break;
        case FEE_SSSTATUSWSASET:            /* For "Setting" */
            /* If all blocks end */
            if ( (ptstCPUDTFInfo->u4BlockCount) >= (ptstCPUDTFInfo->ptstAreaInf->u1BlockNum) )
            {
                /* Set processing result to "write successful, no target block" */
                ptstCPUDTFInfo->u1Result = FEE_RSP_NG_INITIALIZE;
                /* Set area head block as main block */
                ptstCPUDTFInfo->u1MainBlockNo = ptstCPUDTFInfo->ptstAreaInf->u1AreaStartBlockNum;
                /* Set top block of area + 1 as subblock */
                ptstCPUDTFInfo->u1SubBlockNo = ptstCPUDTFInfo->ptstAreaInf->u1AreaStartBlockNum + (uint8)FEE_NEXT_BLOCKNUM_OFFSET;
                /* Set main block status to used */
                ptstCPUDTFInfo->u1MainBlockStatus = FEE_BS_USED;
                /* Set Subblock Status as Used */
                ptstCPUDTFInfo->u1SubBlockStatus = FEE_BS_USED;
                /* Set substate to "In Use Blocking" */
                ptstCPUDTFInfo->u1SubStatus = FEE_SSTATUSWSUSG;
                /* Set subsubstate to 'Blocking in use - waiting to be erased' */
                ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSUWERSG;
                /* Set EXIT in return */
                u4tReturn = FEE_STATUS_EXIT;
            }
            /* Otherwise */
            else
            {
                /* Preparing for MemAcc data flash access. */
                u1_dfPrepare = Fee_FlsWrp_ExtDfPreExecution();
                if( u1_dfPrepare == (Std_ReturnType)E_OK )
                {
                    /* Used settings in order from first block */
                    /* Calculate block number of target block */
                    u1tBlockNum = Fee_UseBlockInfo[ptstCPUDTFInfo->u4BlockCount].u1BlockNo;
                    /* Block counter increment */
                    ptstCPUDTFInfo->u4BlockCount++;
                    /* Block status data judgment (used) */
                    u4tResult = Fee_JudgeBSData( u1tBlockNum,
                                                            (uint32)FEE_BS_USED,
                                                            &u4tBSFixKind,
                                                            &u1tWritePlace );
                    /* If the block status area is blank */
                    if ( u4tResult == (uint32)FEE_BSDATA_ERASE )
                    {
                        /* Set Affected Block Status to Used */
                        Fee_WriteBlockStatus( u1tBlockNum,
                                                        (uint32)FEE_BS_USED,
                                                        u1tWritePlace );
                        /* Set return value to "Area disabled/Used set/Uncontinuable" */
                        u4tReturn = FEE_STATUS_EXIT;
                    }
                    /* Otherwise */
                    else
                    {
                        /* Set return value to "Area disabled/Used set/Continued" */
                        u4tReturn = FEE_STATUS_CONT;
                    }
                }
                else
                {
                    /* Set return value to "Area disabled/Used set/Uncontinuable" */
                    u4tReturn = FEE_STATUS_EXIT;
                }
            }
            break;
        default:                                    /* Otherwise */
            /* Set processing result to "write failed, no target block" */
            ptstCPUDTFInfo->u1Result = FEE_RSP_NG_NODATA;
            /* Set return value to "Area Disabled/Used Settings Ended" */
            u4tReturn = FEE_STATUS_DONE;
            break;
    }
    
    /* RETURN RETURN */
    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_SetFailBlock                                         */
/* Description   | Used and fault setting status management                 */
/* Preconditions | None                                                     */
/* Parameters    | stCPUDTF *ptstCPUDTFInfo                                 */
/*               |              MHA management data                         */
/* Return Value  | Result of processing                                     */
/*               | 0x00000002: u4gSTATUS _ EXIT: Area Disabled/Used Setting */
/*               |                               /Uncontinuable             */
/*               | 0x00000003: u4gSTATUS _ DONE: Area disabled              */
/*               |                               /Used settings ended       */
/*               | 0x00000004: u4gSTATUS _ CONT: Area Disabled/Used Setting */
/*               |                               /Continued                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_SetFailBlock( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* RETURN */

    /* Branch by subsubstate */
    switch ( ptstCPUDTFInfo->u1SubSubStatus )
    {
        case FEE_SSSTATUSWSFWMUSD:          /* For "Main block used waiting for setup" */
            /* Set main block status to "Used" */
            Fee_WriteBlockStatus( ptstCPUDTFInfo->u1MainBlockNo,
                                            (uint32)FEE_BS_USED,
                                            FEE_BSWRITE_ALL );
            /* Set sub sub status to "Setting" */
            ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSFSET;
            /* Set return value to "Used/Failure setting/Uncontinuable" */
            u4tReturn = FEE_STATUS_EXIT;
            break;
        case FEE_SSSTATUSWSFWSUSD:          /* For "Wait for Subblock Used" */
            /* Set subblock status to "Used" */
            Fee_WriteBlockStatus( ptstCPUDTFInfo->u1SubBlockNo,
                                            (uint32)FEE_BS_USED,
                                            FEE_BSWRITE_ALL );
            /* Set sub sub status to "Setting" */
            ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSFSET;
            /* Set return value to "Used/Failure setting/Uncontinuable" */
            u4tReturn = FEE_STATUS_EXIT;
            break;
        case FEE_SSSTATUSWSFWMF:            /* For "Main block failure setting waiting" */
            /* Set main block status to "Used" */
            Fee_WriteBlockStatus( ptstCPUDTFInfo->u1MainBlockNo,
                                            (uint32)FEE_BS_USED,
                                            FEE_BSWRITE_ALL );
            /* Set sub sub status to "Setting" */
            ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSFSET;
            /* Set return value to "Used/Failure setting/Uncontinuable" */
            u4tReturn = FEE_STATUS_EXIT;
            break;
        case FEE_SSSTATUSWSFWSF:            /* In the case of "Wait for subblock failure setting" */
            /* Set subblock status to "Used" */
            Fee_WriteBlockStatus( ptstCPUDTFInfo->u1SubBlockNo,
                                            (uint32)FEE_BS_USED,
                                            FEE_BSWRITE_ALL );
            /* Set sub sub status to "Setting" */
            ptstCPUDTFInfo->u1SubSubStatus = FEE_SSSTATUSWSFSET;
            /* Set return value to "Used/Failure setting/Uncontinuable" */
            u4tReturn = FEE_STATUS_EXIT;
            break;
        default:                                    /* Otherwise */
            /* Set return value to "End used/failure setting" */
            u4tReturn = FEE_STATUS_DONE;
            break;
    }
    /* RETURN RETURN */
    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_JudgeAllBS                                           */
/* Description   | Full block status judgment                               */
/* Preconditions | None                                                     */
/* Parameters    | stCPUDTF *ptstCPUDTFInfo                                 */
/*               |              MHA management data                         */
/* Return Value  | Result of judgment                                       */
/*               | 0x00000002: u4gSTATUS _ EXIT: Judging in progress,       */
/*               |                               not possible to continue   */
/*               | 0x00000003: u4gSTATUS _ DONE: End of judgment            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_JudgeAllBS( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* RETURN */
    uint32          u4tResult;                                  /* Results */
    uint8           u1tWriteReqFlag;                            /* Write-request flag */
    uint32          u4tBSFixKind;                               /* Firm processing type */
    uint8           u1tWritePlace = FEE_BSWRITE_NOTWRITE;
    uint8           BlockNum;
    boolean         DummyNeedsToFixBS = FALSE;
    
    /* Write request flag cleared */
    u1tWriteReqFlag = FEE_FLAG_OFF;
    /* Buffer Initialization for Continuous Writing */
    Fee_ClearCWriteBuf();
    BlockNum = ptstCPUDTFInfo->ptstAreaInf->u1BlockNum;
    
    /* If block counter = 0 (area status) */
    if ( ptstCPUDTFInfo->u4BlockCount == (uint32)FEE_TOP_BLOCK_IN_AREA )
    {
        /* Block status data judgment (area status) */
        /* Return value is not checked. */
        /* This process is to set BlockStatus and does not use return value that is judgment of BlockStatus. */
        (void)Fee_JudgeBSData( ptstCPUDTFInfo->ptstAreaInf->u1AreaStartBlockNum,
                                (uint32)FEE_BS_AREA,
                                &u4tBSFixKind,
                                &u1tWritePlace );
        /* If firm processing is required */
        if ( u4tBSFixKind != (uint32)FEE_BSFIXKIND_NONFIX )
        {
            /* Block Status Settings (Area Status) */
            Fee_SetBlockStatus( ptstCPUDTFInfo->ptstAreaInf->u1AreaStartBlockNum,
                                            (uint32)FEE_BS_AREA,
                                            u1tWritePlace );
            /* Set write request flag */
            u1tWriteReqFlag = FEE_FLAG_ON;
            /* If confirmation of the area status is necessary, it is the time of an area error, so */
            /* Keep the block counter moving forward because there is no need to determine the block status next */
            ptstCPUDTFInfo->u4BlockCount = BlockNum;
            /* However, the in-use block data structure (Fee _ UseBlockInfo) */
            /* Call full block status judgment for reading since the judgment result needs to be entered */
            /* Full block status determination process for reading */
            Fee_JudgeAllBSRead( ptstCPUDTFInfo, &DummyNeedsToFixBS );
        }
        /* Otherwise */
        else
        {
            /* No process */
        }
    }
    /* Otherwise */
    else
    {
        /* No process */
    }
    
    /* Block status determination until all blocks end or write request flag is set */
    while ( ((ptstCPUDTFInfo->u4BlockCount) < BlockNum )
            && (u1tWriteReqFlag == FEE_FLAG_OFF) )
    {
        /* Block status determination */
        u4tResult = Fee_JudgeBS( &(Fee_UseBlockInfo[ptstCPUDTFInfo->u4BlockCount]) );
        /* In the case of "Judgment ended/Confirmation processed" */
        if ( u4tResult == FEE_STATUS_EXIT )
        {
            /* Set write request flag */
            u1tWriteReqFlag = FEE_FLAG_ON;
        }
        /* In the case of "Finished judgment/No firm processing" */
        else
        {
            /* No process */
        }
        /* Block counter increment */
        ptstCPUDTFInfo->u4BlockCount++;
    }
    
    /* If the write request flag is set */
    if ( u1tWriteReqFlag == FEE_FLAG_ON )
    {
        /* Continuous write start */
        Fee_StartCWrite();
        /* Set return value to "Judging/Uncontinuable" */
        u4tReturn = FEE_STATUS_EXIT;
    }
    /* Otherwise */
    else
    {
        /* Set return value to "End judgment" */
        u4tReturn = FEE_STATUS_DONE;
    }
    
    /* RETURN RETURN */
    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_JudgeAllBSRead                                       */
/* Description   | Full block status judgment for reading                   */
/* Preconditions | None                                                     */
/* Parameters    | stCPUDTF *ptstCPUDTFInfo                                 */
/*               |                      MHA management data                 */
/*               |      NeedsToFix , An output argument.                    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_JudgeAllBSRead(
    P2CONST( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) ptstCPUDTFInfo,
    P2VAR  ( boolean,        AUTOMATIC, TYPEDEF         ) NeedsToFix
){
    uint32          u4tCounter;                                 /* Counter */
    uint32          ResultNeedsToFix;
    uint8           BlockNum;
    boolean         TmpNeedsToFix;

    /* Counter clear */
    u4tCounter = 0U;
    BlockNum = ptstCPUDTFInfo->ptstAreaInf->u1BlockNum;
    TmpNeedsToFix = FALSE;
    /* Block status judgment until all blocks are finished */
    do {
        /* Block status determination */
        ResultNeedsToFix = Fee_JudgeBSForRead( &(Fee_UseBlockInfo[u4tCounter]) );
        if( ResultNeedsToFix == FEE_STATUS_EXIT )
        {
            TmpNeedsToFix = TRUE;
        }
        /* Block counter increment */
        u4tCounter++;
    } while ( u4tCounter < (uint32)BlockNum );

    (*NeedsToFix) = TmpNeedsToFix;

    return;
}

/****************************************************************************/
/* Function Name | Fee_JudgeBS                                              */
/* Description   | BLOCK STATUS JUDGMENT                                    */
/* Preconditions | None                                                     */
/* Parameters    | FEE _ stUSEBLOCK * ptstUseBlock                          */
/*               |                   : In-use block structure               */
/* Return Value  | Result of judgment                                       */
/*               | 0x00000002: u4gSTATUS _ EXIT: Judgment ended/confirmed   */
/*               | 0x00000003: u4gSTATUS _ DONE: Judgment end               */
/*               |                               /no finalization           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_JudgeBS( P2VAR(Fee_UseBlockType, AUTOMATIC, TYPEDEF) ptstUseBlock )
{
    uint32          u4tReturn;                                  /* RETURN */
    uint32          u4tBSFixKind;                               /* Firm processing type */
    uint32          u4tBSData[FEE_BSDATAKINDNUM];       /* Block status data judgment result */
    uint8           u1tWritePlace;
    uint32          u4tCounter;                                 /* Counter */
    uint8           u1tWriteReqFlag;                            /* Write-request flag */
    
    /* Block status data judgment result initialization */
    for ( u4tCounter = 0U; u4tCounter < (uint32)FEE_BSDATAKINDNUM; u4tCounter++ )
    {
        u4tBSData[u4tCounter] = (uint32)FEE_BSDATA_OTHER;
    }
    
    /* Write request flag cleared */
    u1tWriteReqFlag = FEE_FLAG_OFF;
    /* Counter clear */
    u4tCounter = 0U;
    
    /* Determine block status data in the order of Used, Transferring, and In Use */
    while ( u4tCounter < (uint32)FEE_BSDATAKINDNUM )
    {
        u1tWritePlace = FEE_BSWRITE_NOTWRITE;
        /* Block status data judgment */
        u4tBSData[u4tCounter] = Fee_JudgeBSData( ptstUseBlock->u1BlockNo,
                                                            (uint32)((uint32)FEE_BS_USED - u4tCounter),
                                                            &u4tBSFixKind,
                                                            &u1tWritePlace );
        /* If firm processing is required */
        if ( u4tBSFixKind != (uint32)FEE_BSFIXKIND_NONFIX )
        {
            /* Block status setting (overwrites 0 x 55 AA 55 AA) */
            Fee_SetBlockStatus( ptstUseBlock->u1BlockNo,
                                            (uint32)((uint32)FEE_BS_USED - u4tCounter),
                                             u1tWritePlace );
            /* Set write request flag */
            u1tWriteReqFlag = FEE_FLAG_ON;
        }
        /* Otherwise */
        else
        {
            /* No process */
        }
        
        /* Counter increment */
        u4tCounter++;
    }
    
    /* Determine block status from block status data judgment result */
    ptstUseBlock->u1BlockStatus = Fee_JudgeBSTBL[u4tBSData[FEE_BSDATAPOS_USING]][u4tBSData[FEE_BSDATAPOS_MOVE]][u4tBSData[FEE_BSDATAPOS_USED]];
    
    /* If the write request flag is set */
    if ( u1tWriteReqFlag == FEE_FLAG_ON )
    {
        /* Set return value to "Finished judgment/Finalized" */
        u4tReturn = FEE_STATUS_EXIT;
    }
    /* Otherwise */
    else
    {
        /* Set return value to "End judgment/No firm processing" */
        u4tReturn = FEE_STATUS_DONE;
    }
    
    /* RETURN RETURN */
    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_JudgeBSForRead                                       */
/* Description   | Reading block status judgment                            */
/* Preconditions | None                                                     */
/* Parameters    | FEE _ stUSEBLOCK * ptstUseBlock                          */
/*               |                      : In-use block structure            */
/* Return Value  | Definite processing required                             */
/*               |           FEE_STATUS_EXIT                                */
/*               |           FEE_STATUS_DONE                                */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_JudgeBSForRead(
    P2VAR( Fee_UseBlockType, AUTOMATIC, FEE_VAR_NO_INIT ) ptstUseBlock
){
    uint32          u4tBSFixKind;                               /* Firm processing type */
    uint32          u4tBSData[FEE_BSDATAKINDNUM];       /* Block status data judgment result */
    uint32          u4tCounter;                                 /* Counter */
    uint32          Rtn;
    uint8           u1tDummyWritePlace;

    /* Block status data judgment result initialization */
    for ( u4tCounter = 0U; u4tCounter < (uint32)FEE_BSDATAKINDNUM; u4tCounter++ )
    {
        u4tBSData[u4tCounter] = (uint32)FEE_BSDATA_OTHER;
    }
    
    /* Counter clear */
    u4tCounter = 0U;
    
    /* Determine block status data in the order of Used, Transferring, and In Use */
    Rtn = FEE_STATUS_DONE;
    while ( u4tCounter < (uint32)FEE_BSDATAKINDNUM )
    {
        /* Block status data judgment */
        u4tBSData[u4tCounter] = Fee_JudgeBSData( ptstUseBlock->u1BlockNo,
                                                            (uint32)((uint32)FEE_BS_USED - u4tCounter),
                                                            &u4tBSFixKind,
                                                            &u1tDummyWritePlace );
        if( u4tBSFixKind != (uint32)FEE_BSFIXKIND_NONFIX )
        {
            Rtn = FEE_STATUS_EXIT;
        }
        /* Counter increment */
        u4tCounter++;
    }
    
    /* Determine block status from block status data judgment result */
    ptstUseBlock->u1BlockStatus = Fee_JudgeBSTBL[u4tBSData[FEE_BSDATAPOS_USING]][u4tBSData[FEE_BSDATAPOS_MOVE]][u4tBSData[FEE_BSDATAPOS_USED]];

    return Rtn;
}

/****************************************************************************/
/* Function Name | Fee_JudgeBSData                                          */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u1BlockNo                                                */
/*               | u4BSDataKind                                             */
/*               | ptu4FixKind                                              */
/*               | ptu1WritePlace                                           */
/* Return Value  | FEE_BSDATA_ERASE                                         */
/*               | FEE_BSDATA_VALID                                         */
/*               | FEE_BSDATA_OTHER                                         */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_JudgeBSData(
    uint8 u1BlockNo,
    uint32 u4BSDataKind,
    P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4FixKind,
    P2VAR(uint8, AUTOMATIC, TYPEDEF) ptu1WritePlace
){
    uint32          u4tReturn;                                  /* RETURN */
    uint32          u4tBSData1;                                 /* Block status data read result (1st) */
    uint32          u4tBSData2;                                 /* Block status data read result (2nd) */
    uint8           u1tTmpWritePlace = (uint8)FEE_BSWRITE_NOTWRITE;
    
    /* Read Block Status Data (1st) */
    u4tBSData1 = Fee_ReadBSData( u1BlockNo, u4BSDataKind, FEE_DUPLIDATA_1ST );
    /* Read Block Status Data (2nd) */
    u4tBSData2 = Fee_ReadBSData( u1BlockNo, u4BSDataKind, FEE_DUPLIDATA_2ND );

    if( u4tBSData1 == (uint32)FEE_BSDATA_ERASE )
    {
        u1tTmpWritePlace = (uint8)FEE_BSWRITE_MAIN;
    }
    if( u4tBSData2 == (uint32)FEE_BSDATA_ERASE )
    {
        u1tTmpWritePlace |= (uint8)FEE_BSWRITE_SUB;
    }
    *ptu1WritePlace = u1tTmpWritePlace;

    /* Determine block status data from block status data read result */
    /* When block status data type is "Area status" */
    if ( u4BSDataKind == FEE_BS_AREA )
    {
        u4tReturn = ((uint32)Fee_JudgeBSDataTBL_A[u4tBSData2][u4tBSData1] & (uint32)FEE_LOWER4BIT);
        *ptu4FixKind = ((uint32)Fee_JudgeBSDataTBL_A[u4tBSData2][u4tBSData1] & (uint32)FEE_UPPER4BIT);
    }
    /* If block status data type is "Used" */
    else if ( u4BSDataKind == FEE_BS_USED )
    {
        u4tReturn = ((uint32)Fee_JudgeBSDataTBL_C[u4tBSData2][u4tBSData1] & (uint32)FEE_LOWER4BIT);
        *ptu4FixKind = ((uint32)Fee_JudgeBSDataTBL_C[u4tBSData2][u4tBSData1] & (uint32)FEE_UPPER4BIT);
    }
    /* Otherwise */
    else
    {
        u4tReturn = ((uint32)Fee_JudgeBSDataTBL_B[u4tBSData2][u4tBSData1] & (uint32)FEE_LOWER4BIT);
        *ptu4FixKind = ((uint32)Fee_JudgeBSDataTBL_B[u4tBSData2][u4tBSData1] & (uint32)FEE_UPPER4BIT);
    }
    
    /* RETURN RETURN */
    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_ReadBSData                                           */
/* Description   | Read block status data                                   */
/* Preconditions | None                                                     */
/* Parameters    | uint8u1BlockNo                : Block #                  */
/*               |   : uint 32 u4 BSDataKind        : block status data type*/
/*               |   : uint 32 u4 DuplicateDataKind : Duplex data type      */
/* Return Value  | Block status data judgment result                        */
/*               |   : 0x00000000 : FEE_BSDATA_ERASE  : Erase status        */
/*               |   : 0x00000001 : FEE_BSDATA_VALID  : 0x55AA55AA          */
/*               |   : 0x00000002 : FEE_BSDATA_OTHER  : Other than above    */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_ReadBSData( uint8 u1BlockNo, uint32 u4BSDataKind, uint32 u4DuplicateDataKind )
{
    uint32          u4tReturn;                                  /* RETURN */
    uint32          u4tReadAddress;                             /* read-address */
    uint8           u1tCompareResult;
    uint32          u4tBlockStartAddr;

    /* Calculate read address */
    u4tBlockStartAddr = FEE_BLKSTARTADDRTBL[u1BlockNo];
    u4tReadAddress    = u4tBlockStartAddr + Fee_ASBSDataTBL[u4DuplicateDataKind][u4BSDataKind];

    /* Compare data flash. */
    u1tCompareResult = Fee_DfcMpu_SyncCompare_EccFixSize( u4tReadAddress, &Fee_FixBSData[0] );

    /* Judge the result of comparision. */
    switch ( u1tCompareResult )
    {
        case FEE_DFCMPU_RESULT_BLANK:
            /* Set return value as ERASE. */
            u4tReturn = (uint32)FEE_BSDATA_ERASE;
            break;
        case FEE_DFCMPU_RESULT_OK:
            /* Set return value as VALID (0x55AA55AA). */
            u4tReturn = (uint32)FEE_BSDATA_VALID;
            break;
        default:
            /* Set return value as OTHER. */
            u4tReturn = (uint32)FEE_BSDATA_OTHER;
            break;
    }

    /* RETURN RETURN */
    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_SelectUseBlock                                       */
/* Description   | In-use block selection                                   */
/* Preconditions | None                                                     */
/* Parameters    | uint8 u1MainBlockStatus : MainBlockStatus                */
/*               | uint8 u1SubBlockStatus  : subblock status                */
/*               | uint8 u1BlockNum        : Number of blocks in area       */
/*               | boolean *u1Swap         : main sub needs to be replaced  */
/* Return Value  | Selection Results                                        */
/*               | 0x00000000    : u4gSTATUS_OK : Successful Selection      */
/*               | 0x00000001    : u4gSTATUS_NG : Selection failed          */
/* Notes         | Block data structures in use must be in advance          */
/*               | (For reading) Judged by all-block status judgment        */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_SelectUseBlock( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* RETURN */
    uint32          u4tResult;                                  /* Results */
    uint32          u4tBSFixKind;                               /* Firm processing type */
    uint32          u4tCounter;                                 /* Counter */
    uint32          u4tUnUsedCount;                             /* Number of unused blocks */
    uint32          u4tValidCount;                              /* effective blocks */
    uint32          u4tValidBlockNum[FEE_VALIDBLKNUM];  /* Valid block storage array number */
    uint32          u4tMainValidBlockNum;                       /* Mainblock candidate storage array number */
    uint32          u4tSubValidBlockNum;                        /* Subblock candidate storage array number */
    uint8           u1tDummyWritePlace;
    
    /* Initialize valid block storage array */
    for ( u4tCounter = 0U; u4tCounter < (uint32)FEE_VALIDBLKNUM; u4tCounter++ )
    {
        u4tValidBlockNum[u4tCounter] = 0U;
    }
    u4tMainValidBlockNum = 0U;
    u4tSubValidBlockNum = 0U;
    
    /* Block status data judgment (area status) */
    u4tResult = Fee_JudgeBSData( ptstCPUDTFInfo->ptstAreaInf->u1AreaStartBlockNum,
                                            (uint32)FEE_BS_AREA,
                                            &u4tBSFixKind,
                                            &u1tDummyWritePlace );
    /* If area status is normal */
    if ( u4tResult == (uint32)FEE_BSDATA_ERASE )
    {
        
        /* Valid block count */
        Fee_CountValidBlock( ptstCPUDTFInfo, &u4tValidBlockNum[0], &u4tValidCount, &u4tUnUsedCount );
        
        /* Branch by number of effective blocks */
        switch ( u4tValidCount )
        {
            case FEE_VALIDBLKNUM_00:                    /* for zero */
                u4tReturn = Fee_FixUseBlockInCaseOfZero( ptstCPUDTFInfo, u4tUnUsedCount, &u4tMainValidBlockNum, &u4tSubValidBlockNum );
                break;
            case FEE_VALIDBLKNUM_01:                    /* for one */
                u4tReturn = Fee_FixUseBlockInCaseOfOne( ptstCPUDTFInfo, &u4tValidBlockNum[0], &u4tMainValidBlockNum, &u4tSubValidBlockNum );
                break;
            case FEE_VALIDBLKNUM_02:                    /* For 2 */
                u4tReturn = Fee_FixUseBlockInCaseOfTwoAndMore( ptstCPUDTFInfo, &u4tValidBlockNum[0], &u4tMainValidBlockNum, &u4tSubValidBlockNum );
                break;
            default:                /* Otherwise */
                /* Set return value to "failed selection" */
                u4tReturn = FEE_STATUS_NG;
                break;
        }
    }
    /* Otherwise */
    else
    {
        /* Set return value to "failed selection" */
        u4tReturn = FEE_STATUS_NG;
    }
    
    /* if the return value is not "selection failed" */
    if ( u4tReturn != FEE_STATUS_NG )
    {
        /* Set main block of MHA management data */
        ptstCPUDTFInfo->u1MainBlockNo = Fee_UseBlockInfo[u4tMainValidBlockNum].u1BlockNo;
        ptstCPUDTFInfo->u1MainBlockStatus = Fee_UseBlockInfo[u4tMainValidBlockNum].u1BlockStatus;
        /* Set subblock of MHA management data */
        ptstCPUDTFInfo->u1SubBlockNo = Fee_UseBlockInfo[u4tSubValidBlockNum].u1BlockNo;
        ptstCPUDTFInfo->u1SubBlockStatus = Fee_UseBlockInfo[u4tSubValidBlockNum].u1BlockStatus;
    }
    /* No action if return value is "selection failed" */

    /* Return return value and finish processing */
    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_CountValidBlock                                      */
/* Description   | Effective block count                                    */
/* Preconditions | None                                                     */
/* Parameters    | stCPUDTF *ptstCPUDTFInfo                                 */
/*               |                      MHA management data                 */
/*               | uint32 *ptu4ValidBlock : valid block storage array number*/
/*               | uint 32 *ptu4ValidNum  : valid blocks                    */
/*               | uint 32 *ptu4UnUsedNum : Number of unused blocks         */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_CountValidBlock( P2CONST(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo, P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4ValidBlock,
                                 P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4ValidNum, P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4UnUsedNum )
{
    uint32          u4tCounter;                                 /* Counter */
    uint32          u4tUnUsedCount;                             /* Number of unused blocks */
    uint32          u4tValidCount;                              /* effective blocks */
    uint8           BlockNum;

    /* Clear unused blocks */
    u4tUnUsedCount = 0U;
    /* Clear effective blocks */
    u4tValidCount = 0U;
    BlockNum = ptstCPUDTFInfo->ptstAreaInf->u1BlockNum;
    /* Count the number of unused blocks and the number of valid blocks from the used block data (loop for number of blocks) */
    for ( u4tCounter = 0U; u4tCounter < (uint32)BlockNum; u4tCounter++ )
    {
        /* If the block status is Unused */
        if ( Fee_UseBlockInfo[u4tCounter].u1BlockStatus == FEE_BS_UNUSED )
        {
            /* Unused block count increment */
            u4tUnUsedCount++;
        }
        /* If the block status is In Use or Transferring */
        else if ( (Fee_UseBlockInfo[u4tCounter].u1BlockStatus == FEE_BS_USING)
                || (Fee_UseBlockInfo[u4tCounter].u1BlockStatus == FEE_BS_MOVE) )
        {
            /* Memorize up to two sequence numbers containing valid blocks found */
            if ( u4tValidCount < (uint32)FEE_VALIDBLKNUM )
            {
                /* Set valid block storage array number */
                ptu4ValidBlock[u4tValidCount] = u4tCounter;
            }
            /* Valid block count increment */
            u4tValidCount++;
        }
        /* Otherwise */
        else
        {
            /* No process */
        }
    }
    
    *ptu4UnUsedNum = u4tUnUsedCount;
    *ptu4ValidNum = u4tValidCount;
    
    return;
}

/****************************************************************************/
/* Function Name | Fee_FixUseBlockInCaseOfZero                              */
/* Description   | In-use block selection (0 effective blocks)              */
/* Preconditions | None                                                     */
/* Parameters    | stCPUDTF *ptstCPUDTFInfo                                 */
/*               |                      MHA management data                 */
/*               | uint32 u4UnUsedCount  : Number of unused blocks          */
/*               | uint32 *ptu4MainValidBlockNum                            */
/*               |          mainblock candidate storage sequence number     */
/*               | uint32 *ptu4SubValidBlockNum                             */
/*               |          Subblock candidate storage sequence number      */
/* Return Value  | Selection Results                                        */
/*               | 0x00000000    : u4gSTATUS_OK     : Successful Selection  */
/*               | 0x00000007    : u4gSTATUS_NODATA : Block not used        */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_FixUseBlockInCaseOfZero( P2CONST(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo, uint32 u4UnUsedCount,
                                        P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4MainValidBlockNum, P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4SubValidBlockNum )
{
    uint32          u4tReturn;                                  /* RETURN */
    
    /* Set area head block as main block */
    *ptu4MainValidBlockNum = (uint32)FEE_TOP_BLOCK_IN_AREA;
    /* Subblock after main block */
    *ptu4SubValidBlockNum = (uint32)FEE_SECOND_BLOCK_IN_AREA;
    /* If all blocks are unused */
    if ( u4UnUsedCount >= (uint32)(ptstCPUDTFInfo->ptstAreaInf->u1BlockNum) )
    {
        /* Set return value to "Unblocked" */
        u4tReturn = FEE_STATUS_NODATA;
    }
    /* Otherwise */
    else
    {
        /* Set return value to "Selection success" */
        u4tReturn = FEE_STATUS_OK;
    }
    
    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_FixUseBlockInCaseOfOne                               */
/* Description   | In-use block selection (1 effective block)               */
/* Preconditions | None                                                     */
/* Parameters    | stCPUDTF *ptstCPUDTFInfo                                 */
/*               |                      MHA management data                 */
/*               | uint32 *ptu4ValidBlockNum                                */
/*               |              valid block storage array number            */
/*               | uint32 *ptu4MainValidBlockNum                            */
/*               |              mainblock candidate storage sequence number */
/*               | uint32 *ptu4SubValidBlockNum                             */
/*               |              Subblock candidate storage sequence number  */
/* Return Value  | Selection Results                                        */
/*               | 0x00000000: u4gSTATUS_OK : Successful Selection          */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_FixUseBlockInCaseOfOne( P2CONST(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo, P2CONST(uint32, AUTOMATIC, TYPEDEF) ptu4ValidBlockNum,
                                        P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4MainValidBlockNum, P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4SubValidBlockNum )
{
    uint32          u4tReturn;                                  /* RETURN */
    
    /* Make the effective block the main block */
    *ptu4MainValidBlockNum = ptu4ValidBlockNum[FEE_ARRAY_INDEX_00];
    /* Set next block of main block as subblock */
    *ptu4SubValidBlockNum = (*ptu4MainValidBlockNum) + (uint32)FEE_NEXT_BLOCKNUM_OFFSET;
    /* If the subblock exceeds the final block */
    if ( (*ptu4SubValidBlockNum) >= (uint32)(ptstCPUDTFInfo->ptstAreaInf->u1BlockNum) )
    {
        /* Set area head block as subblock */
        (*ptu4SubValidBlockNum) = (uint32)FEE_TOP_BLOCK_IN_AREA;
    }
    /* Set return value to "Selection success" */
    u4tReturn = FEE_STATUS_OK;
    
    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_FixUseBlockInCaseOfTwoAndMore                        */
/* Description   | In-use block selection (2 or more effective blocks)      */
/* Preconditions | None                                                     */
/* Parameters    | stCPUDTF *ptstCPUDTFInfo                                 */
/*               |                      MHA management data                 */
/*               | uint32 *ptu4ValidBlockNum                                */
/*               |            valid block storage array number              */
/*               | uint32 *ptu4MainValidBlockNum                            */
/*               |            mainblock candidate storage sequence number   */
/*               | uint32 *ptu4SubValidBlockNum                             */
/*               |            Subblock candidate storage sequence number    */
/* Return Value  | Selection Results                                        */
/*               | 0x00000000 : u4gSTATUS_OK : Successful Selection         */
/*               | 0x00000001 : u4gSTATUS_NG : Selection failed             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_FixUseBlockInCaseOfTwoAndMore( P2CONST(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo, P2CONST(uint32, AUTOMATIC, TYPEDEF) ptu4ValidBlockNum,
                                        P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4MainValidBlockNum, P2VAR(uint32, AUTOMATIC, TYPEDEF) ptu4SubValidBlockNum )
{
    uint32          u4tReturn;                                  /* RETURN */
    uint32          u4tMainValidBlockNum;                       /* Mainblock candidate storage array number */
    uint32          u4tSubValidBlockNum;                        /* Subblock candidate storage array number */
    uint32          u4tWorkValidBlockNum;                       /* Candidate storage sequence number work */
    boolean     u1tSwap;

    /* Set return value to "Selection success" */
    u4tReturn = FEE_STATUS_OK;

    u4tMainValidBlockNum = 0U;
    u4tSubValidBlockNum = 0U;

    /* If the first and last blocks are valid blocks */
    if ( (ptu4ValidBlockNum[FEE_ARRAY_INDEX_00] == (uint32)FEE_TOP_BLOCK_IN_AREA) 
        && (ptu4ValidBlockNum[FEE_ARRAY_INDEX_01] == ((uint32)ptstCPUDTFInfo->ptstAreaInf->u1BlockNum - (uint32)FEE_LAST_BLOCKNUM_OFFSET)) )
    {
        u4tMainValidBlockNum = ptu4ValidBlockNum[FEE_ARRAY_INDEX_01];
        u4tSubValidBlockNum = ptu4ValidBlockNum[FEE_ARRAY_INDEX_00];
    }
    /* if valid blocks are contiguous */
    else if ( ptu4ValidBlockNum[FEE_ARRAY_INDEX_01] == (ptu4ValidBlockNum[FEE_ARRAY_INDEX_00] + (uint32)FEE_NEXT_BLOCKNUM_OFFSET) )
    {
        u4tMainValidBlockNum = ptu4ValidBlockNum[FEE_ARRAY_INDEX_00];
        u4tSubValidBlockNum = ptu4ValidBlockNum[FEE_ARRAY_INDEX_01];
    }
    else
    {
        /* Set return value to "failed selection" */
        u4tReturn = FEE_STATUS_NG;
    }
    /* If the return value is "Selection success" */
    if ( u4tReturn == FEE_STATUS_OK )
    {
        
        u4tReturn = Fee_JudgeBlockStatusCombination( Fee_UseBlockInfo[u4tMainValidBlockNum].u1BlockStatus,
                                                    Fee_UseBlockInfo[u4tSubValidBlockNum].u1BlockStatus,
                                                    ptstCPUDTFInfo->ptstAreaInf->u1BlockNum,
                                                    &u1tSwap );
        if ( u1tSwap == ( boolean )TRUE )
        {
            /* Swap main and sub */
            u4tWorkValidBlockNum = u4tMainValidBlockNum;
            u4tMainValidBlockNum = u4tSubValidBlockNum;
            u4tSubValidBlockNum = u4tWorkValidBlockNum;
        }
    }
    
    /* Set fixed main block number, subblock number and exit */
    *ptu4MainValidBlockNum = u4tMainValidBlockNum;
    *ptu4SubValidBlockNum = u4tSubValidBlockNum;
    
    return u4tReturn;
    
}

/****************************************************************************/
/* Function Name | Fee_JudgeBlockStatusCombination                          */
/* Description   | Block status combination judgment                        */
/* Preconditions | None                                                     */
/* Parameters    | stCPUDTF *ptstCPUDTFInfo                                 */
/*               |                      MHA management data                 */
/*               | uint32 *ptu4ValidBlockNum                                */
/*               |              valid block storage array number            */
/*               | uint32 *ptu4MainValidBlockNum                            */
/*               |              mainblock candidate storage sequence number */
/*               | uint32 *ptu4SubValidBlockNum                             */
/*               |              Subblock candidate storage sequence number  */
/* Return Value  | Selection Results                                        */
/*               | 0x00000000 : u4gSTATUS_OK : Successful Selection         */
/*               | 0x00000001 : u4gSTATUS_NG : Selection failed             */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_JudgeBlockStatusCombination(uint8 u1MainBlockStatus, uint8 u1SubBlockStatus, uint8 u1BlockNum, P2VAR(boolean, AUTOMATIC, TYPEDEF) u1Swap)
{
    uint32          u4tReturn;                                  /* RETURN */
    
    u4tReturn = FEE_STATUS_NG;
    *u1Swap   = FALSE;
    
    /* If Main is "Transferring" */
    if (u1MainBlockStatus == FEE_BS_MOVE)
    {
        /* When the main is "Transferring" and the sub is "In Use" */
        if (u1SubBlockStatus == FEE_BS_USING)
        {
            /* SELECTION SUCCESSFUL */
            u4tReturn = FEE_STATUS_OK;
        }
        /* Main is Transferring, Sub is Transferring, and has 3 or more blocks */
        else if (( u1SubBlockStatus == FEE_BS_MOVE ) && ( u1BlockNum >= (uint8)FEE_USEBLKNUM_03 ))
        {
            /* SELECTION SUCCESSFUL */
            u4tReturn = FEE_STATUS_OK;
        }
        else
        {
            /* No process in case of selection failure */
        }
    }
    /* When the main is in use */
    else if (u1MainBlockStatus == FEE_BS_USING){
        
        /* If the main is in use, the sub is in transfer, and the number of blocks is 2 */
        if (( u1SubBlockStatus == FEE_BS_MOVE )&&(u1BlockNum == (uint8)FEE_USEBLKNUM_02))
        {
            /* SELECTION SUCCESSFUL */
            u4tReturn = FEE_STATUS_OK;
            /* Swap main and sub */
            *u1Swap = TRUE;
        }
    }
    else
    {
        /* No process in case of selection failure */
    }
    
    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_WriteBlockStatus                                     */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u1BlockNo                                                */
/*               | u4BSDataKind                                             */
/*               | u1WritePlace                                             */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_WriteBlockStatus(
    uint8 u1BlockNo,
    uint32 u4BSDataKind,
    uint8 u1WritePlace
){
    /* Buffer Initialization for Continuous Writing */
    Fee_ClearCWriteBuf();

    Fee_SetBlockStatus( u1BlockNo, u4BSDataKind, u1WritePlace );
    /* Continuous write start processing */
    Fee_StartCWrite();

    return;
}

/****************************************************************************/
/* Function Name | Fee_SetBlockStatus                                       */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u1BlockNo                                                */
/*               | u4BSDataKind                                             */
/*               | u1WritePlace                                             */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_SetBlockStatus(
    uint8 u1BlockNo,
    uint32 u4BSDataKind,
    uint8 u1WritePlace
){
    P2CONST(uint8, AUTOMATIC, TYPEDEF) ptu1WriteData;                       /* WRITE DATA POINTER */
    uint32          u4tAddress1;                                /* Address (1st) */
    uint32          u4tAddress2;                                /* ADDRESS (SECOND) */
    uint16          u2tCWriteFlag;                              /* Flags for continuous writing */
    uint32          u4tBlockStartAddress;                       /* Block head address */

    /* Write Data Initialization (0 x 55 AA 55 AA 55 AA 55 AA) */
    ptu1WriteData = &Fee_FixBSData[0];
    u2tCWriteFlag = FEE_CWFLG_VOLMINCHK;
    /* Block head address */
    u4tBlockStartAddress = FEE_BLKSTARTADDRTBL[u1BlockNo];

    if ( u4BSDataKind <= FEE_BS_USED )
    {
        /* ADDRESS CALCULATION OF BLOCK STATUS */
        u4tAddress1 = u4tBlockStartAddress + Fee_ASBSDataTBL[FEE_DUPLIDATA_1ST][u4BSDataKind];
        u4tAddress2 = u4tBlockStartAddress + Fee_ASBSDataTBL[FEE_DUPLIDATA_2ND][u4BSDataKind];
        
        /* If block status type is "In use" */
        if ( u4BSDataKind == FEE_BS_USING )
        {
            u2tCWriteFlag = FEE_CWFLG_VOLMINCHK | FEE_CWFLG_VRFYERRCHK;
        }
        /* Otherwise */
        else
        {
            /* No process */
        }
        
        if( (u1WritePlace & (uint8)FEE_BSWRITE_MAIN) == (uint8)FEE_BSWRITE_MAIN )
        {
            Fee_AddCWriteBuf( u4tAddress1, ptu1WriteData, FEE_DATA_FLASH_ECC_FIX_SIZE, FEE_CWOFFSET_ZERO, u2tCWriteFlag );
        }
        if( (u1WritePlace & (uint8)FEE_BSWRITE_SUB) == (uint8)FEE_BSWRITE_SUB )
        {
            Fee_AddCWriteBuf( u4tAddress2, ptu1WriteData, FEE_DATA_FLASH_ECC_FIX_SIZE, FEE_CWOFFSET_ZERO, u2tCWriteFlag );
        }
    }
    /* Otherwise */
    else
    {
        /* No process */
    }

    return;
}

/****************************************************************************/
/* Function Name | Fee_SelectReadBlock                                      */
/* Description   | Block selection for reading/checking free space          */
/* Preconditions | None                                                     */
/* Parameters    | stCPUDTF * ptstCPUDTFInfo                                */
/*               |          : MHA (Data Flash) administrative data          */
/* Return Value  | Selection Results                                        */
/*               | 0x00000000 : u4gSTATUS_OK     : Successful Selection     */
/*               | 0x00000001 : u4gSTATUS_NG     : Selection failed         */
/*               |                                 (no data)                */
/*               | 0x00000007 : u4gSTATUS_NODATA : Selection failed         */
/*               |                                 (no block used)          */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) Fee_SelectReadBlock( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tReturn;                                  /* RETURN */
    uint32          u4tResult;                                  /* Selected results */
    boolean         DummyNeedsToFixBS = FALSE;
    
    /* Set return value to "Selection failed (no data)" */
    u4tReturn = FEE_STATUS_NG;
    
    /* If block status is not remembered */
    if ( (ptstCPUDTFInfo->u1MainBlockStatus == FEE_BS_INVALID)
        || (ptstCPUDTFInfo->u1SubBlockStatus == FEE_BS_INVALID) )
    {
        /* Full block status determination process for reading */
        Fee_JudgeAllBSRead( ptstCPUDTFInfo, &DummyNeedsToFixBS );
        /* In-use block selection processing */
        u4tResult = Fee_SelectUseBlock( ptstCPUDTFInfo );
    }
    /* If block status is remembered */
    else
    {
        /* Set Selection Success for Selection Results */
        u4tResult = FEE_STATUS_OK;
    }
    
    /* If the selection is "Selection success" */
    if ( u4tResult == FEE_STATUS_OK )
    {
        /* If the status of the main block is In Use or Transferring */
        if ( (ptstCPUDTFInfo->u1MainBlockStatus == FEE_BS_USING)
            || (ptstCPUDTFInfo->u1MainBlockStatus == FEE_BS_MOVE) )
        {
            /* Set return value to "Selection success" */
            u4tReturn = FEE_STATUS_OK;
        }
        /* Otherwise */
        else
        {
            /* Set return value to "Selection failed (no data)" */
            u4tReturn = FEE_STATUS_NG;
        }
    }
    /* For "Unblocked" */
    else if ( u4tResult == FEE_STATUS_NODATA )
    {
        /* set return value to "selection failed (block not used)" */
        u4tReturn = FEE_STATUS_NODATA;
    }
    /* For "selection failed" */
    else
    {
        /* No process */
    }
    
    /* RETURN RETURN */
    return u4tReturn;
}

/****************************************************************************/
/* Function Name | Fee_ClrUseBlockInfo                                      */
/* Description   | Initializing block data in use                           */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_ClrUseBlockInfo( void )
{
    uint32          u4tCounter;                                 /* For temporary work */
    uint32          u4CounterMax;
    
    u4CounterMax = Fee_UseBlockInfoSize;
    
    for ( u4tCounter = 0U; u4tCounter < u4CounterMax; u4tCounter++ )
    {
        Fee_UseBlockInfo[u4tCounter].u1BlockNo = FEE_BLOCKNUM_INVALID;
        Fee_UseBlockInfo[u4tCounter].u1BlockStatus = FEE_BS_INVALID;
    }

    return;
}

/****************************************************************************/
/* Function Name | Fee_Block_CheckUseBlockInfo                              */
/* Description   | Function to check Fee_UseBlockInfo.                      */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Check result.                                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, FEE_CODE )
Fee_Block_CheckUseBlockInfo( void )
{
#if ( FEE_USE_REDUNDANCY_RAM == STD_ON )
    Std_ReturnType  Rtn = E_OK;
    uint32          Counter;
    uint32          CounterMax;

    CounterMax = Fee_UseBlockInfoSize;

    for( Counter = 0U; Counter < CounterMax; Counter++ )
    {
        if((( Fee_UseBlockInfo[Counter].u1BlockNo     ^ Fee_UseBlockInfoSub[Counter].u1BlockNo     ) != (uint8)FEE_MIRROR_CHECK_UINT8 )
        || (( Fee_UseBlockInfo[Counter].u1BlockStatus ^ Fee_UseBlockInfoSub[Counter].u1BlockStatus ) != (uint8)FEE_MIRROR_CHECK_UINT8 ))
        {
            Rtn = E_NOT_OK;
            break;
        }
    }

    return Rtn;
#else /* FEE_USE_REDUNDANCY_RAM == STD_OFF */
    return E_OK;
#endif /* FEE_USE_REDUNDANCY_RAM */
}

/****************************************************************************/
/* Function Name | Fee_Block_SetUseBlockInfoSub                             */
/* Description   | Function to set value to sub Fee_UseBlockInfo from main. */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, FEE_CODE )
Fee_Block_SetUseBlockInfoSub( void )
{
#if ( FEE_USE_REDUNDANCY_RAM == STD_ON )
    uint32  Counter;
    uint32  CounterMax;

    CounterMax = Fee_UseBlockInfoSubSize;

    for ( Counter = 0U; Counter < CounterMax; Counter++ )
    {
        Fee_UseBlockInfoSub[Counter].u1BlockNo     = (uint8)(~Fee_UseBlockInfo[Counter].u1BlockNo);
        Fee_UseBlockInfoSub[Counter].u1BlockStatus = (uint8)(~Fee_UseBlockInfo[Counter].u1BlockStatus);
    }
#endif /* FEE_USE_REDUNDANCY_RAM == STD_ON */

    return;
}

#if ( MSCD_FREESPACE_USE == STD_ON )
/****************************************************************************/
/* Function Name | Fee_Block_GetSectorInfo                                  */
/* Description   | Function to get a main sector number.                    */
/* Preconditions | Set Fee_UseBlockInfo.                                    */
/* Parameters    | None                                                     */
/* Return Value  | FEE_STATUS_OK                                            */
/*               | FEE_STATUS_NODATA                                        */
/*               | FEE_STATUS_NG                                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint32, FEE_CODE )
Fee_Block_GetSectorInfo(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo,
    P2VAR( boolean,        AUTOMATIC, TYPEDEF         ) NeedsToFix
){
    uint32 Rtn;

    Fee_JudgeAllBSRead( CPUDTFInfo, NeedsToFix );
    Rtn = Fee_SelectUseBlock( CPUDTFInfo );

    return Rtn;
}
#endif /*( MSCD_FREESPACE_USE == STD_ON )*/

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/10/09                                              */
/*  2-0-0          :2022/08/24                                              */
/*  2-1-0          :2024/09/04                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
