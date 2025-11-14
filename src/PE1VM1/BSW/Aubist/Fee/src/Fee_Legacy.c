/* Fee_Legacy.c v2-0-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/LEGACY/CODE                                           */
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


#include "../inc/Fee_Ram.h"


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/*      CONFIGURE SETTING (user can not edit)    */

/* Offset of area status data 1 */
#define FEE_AREASTATUSPOS1      ((uint8)0x00U)
/* Offset of area status data 2 */
#define FEE_AREASTATUSPOS2      ((uint8)(FEE_AREASTATUSPOS1 + (FEE_READ_UNIT_SIZE * 7U)))
/* Offset of block status data "Used 1" */
#define FEE_BLS_USEDPOS1            ((uint8)(FEE_READ_UNIT_SIZE * 1U))
/* Offset of block status data "Used 2" */
#define FEE_BLS_USEDPOS2            ((uint8)(FEE_BLS_USEDPOS1 + (FEE_READ_UNIT_SIZE * 5U)))
/* Offset of block status data "Transferring 1" */
#define FEE_BLS_MOVEPOS1            ((uint8)(FEE_READ_UNIT_SIZE * 2U))
/* Offset of block status data "Transferring 2" */
#define FEE_BLS_MOVEPOS2            ((uint8)(FEE_BLS_MOVEPOS1 + (FEE_READ_UNIT_SIZE * 3U)))
/* Offset of block status data "In use 1" */
#define FEE_BLS_USEPOS1         ((uint8)(FEE_READ_UNIT_SIZE * 3U))
/* Offset of block status data "In use 2" */
#define FEE_BLS_USEPOS2         ((uint8)(FEE_BLS_USEPOS1 + (FEE_READ_UNIT_SIZE * 1U)))

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define FEE_START_SEC_CONST_32
#include <Fee_MemMap.h>

/* Write Hardware latency threshold */
CONST(AB_83_ConstV uint32, FEE_CONST) Fee_HwLmtWriteTime = FEE_TIMEOUT_PERIODIC_FLS_WRITE;
/* Area block status data address */
/* Order definitions to match order of block status type */
CONST(AB_83_ConstV uint8, FEE_CONST) Fee_ASBSDataTBL[FEE_ASBSDATASETNUM][FEE_ASBSDATAKINDNUM] = 
{
    {FEE_AREASTATUSPOS1,        /* Area Status Data 1 */
    FEE_BLS_USEPOS1,            /* Block status data [in use 1] */
    FEE_BLS_MOVEPOS1,           /* Block status data [Transferring 1] */
    FEE_BLS_USEDPOS1},          /* Block status data [used 1] */

    {FEE_AREASTATUSPOS2,        /* Area Status Data 2 */
    FEE_BLS_USEPOS2,            /* Block status data [in use 2] */
    FEE_BLS_MOVEPOS2,           /* Block status data [Transferring 2] */
    FEE_BLS_USEDPOS2}           /* Block status data [used2 ] */
};

#define FEE_STOP_SEC_CONST_32
#include <Fee_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  2-0-0          :2021/03/18                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
