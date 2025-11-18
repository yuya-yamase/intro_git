/* Fee_Area.c v1-0-0                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/AREA/CODE                                             */
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

#include "../inc/Fee_Ram.h"

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
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* Function Name | Fee_SelectUseArea                                        */
/* Description   | Select area to be used                                   */
/* Preconditions | None                                                     */
/* Parameters    | stCPUDTF * ptstCPUDTFInfo                                */
/*               |            MHA management data                           */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_SelectUseArea( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo )
{
    uint32          u4tCounter;                         /* Counter */
    uint8           u1tBlockNum;                        /* Blocks */
    uint8           u1tStartBlockNo;                    /* Starting block number */
    uint8           u1tAreaNum;                         /* Number of areas */

    /* Eject Area Number */
    u1tAreaNum = ptstCPUDTFInfo->u1AreaNum;

    /* Set area-dependent data structures */
    ptstCPUDTFInfo->ptstAreaInf = (volatile const Fee_AreaInfType *)( &Fee_AreaInfTBL[u1tAreaNum] );

    /* Blocks taken from blocks table */
    u1tBlockNum = ptstCPUDTFInfo->ptstAreaInf->u1BlockNum;
    /* Get starting block number */
    u1tStartBlockNo = ptstCPUDTFInfo->ptstAreaInf->u1AreaStartBlockNum;
    /* Loop until all blocks are finished */
    for ( u4tCounter = 0U; u4tCounter < (uint32)u1tBlockNum; u4tCounter++ )
    {
        /* Set block number in used block data structure */
        Fee_UseBlockInfo[u4tCounter].u1BlockNo = (uint8)(u1tStartBlockNo + u4tCounter);
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
