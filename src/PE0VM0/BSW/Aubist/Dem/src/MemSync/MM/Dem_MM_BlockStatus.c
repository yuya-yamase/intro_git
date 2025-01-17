/* Dem_MM_BlockStatus_c(v5-5-0)                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/MM_BlockStatus/CODE                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/


/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_Mm_MM.h"
#include "Dem_MM_local.h"
#include "../../../cfg/Dem_MM_Cfg.h"

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* DemNvBlockStatusType */
typedef struct
{
    Dem_u08_MMBlockStatusType                  BlockStatus;

} Dem_NvBlockStatusType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/* Nonvolatile block management information */
static VAR( Dem_NvBlockStatusType, DEM_VAR_NO_INIT ) Dem_MM_NvBlockStsList[DEM_NVM_USE_NVBLOCK_NUM];


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


/****************************************************************************/
/* Function Name | Dem_MM_InitNvBlockStatusOfList                           */
/* Description   | Initialize setting of nonvolatile block list             */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/*               |         :                                                */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MM_InitNvBlockStatusOfList
( void )
{
    VAR( Dem_u16_NvBlockIndexType, AUTOMATIC ) blockCnt;
    VAR( Dem_u16_NvBlockIndexType, AUTOMATIC ) nvmUseNvblockNum;

    nvmUseNvblockNum                      = Dem_NvMUseNvblockNum;

    /* Block state list initialization processing */
    for( blockCnt = 0U; blockCnt < nvmUseNvblockNum; blockCnt++ )                       /* [GUD:for]blockCnt */
    {
        /* Block status initialization(For cyclic processing) */
        Dem_MM_NvBlockStsList[blockCnt].BlockStatus     = DEM_MM_BLK_STS_INITIAL_VALUE; /* [GUD]blockCnt */
    }
    return ;
}


/****************************************************************************/
/* Function Name | Dem_MM_SetNvBlockStatusOfList                            */
/* Description   | Status setting of nonvolatile block list                 */
/* Preconditions | ListIndex < Dem_NvMUseNvblockNum                         */
/* Parameters    | [in] ListIndex :                                         */
/*               |        Index of Nv block list                            */
/*               | [in] Status :                                            */
/*               |        Status of Nv block                                */
/* Return Value  | void                                                     */
/*               |         :                                                */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MM_SetNvBlockStatusOfList
(
    VAR( Dem_u16_NvBlockIndexType, AUTOMATIC ) ListIndex,   /* [PRMCHK:CALLER] */
    VAR( Dem_u08_MMBlockStatusType, AUTOMATIC ) Status
)
{
    Dem_MM_NvBlockStsList[ListIndex].BlockStatus = Status;  /* [GUDCHK:CALLER]ListIndex */

    return ;
}


/****************************************************************************/
/* Function Name | Dem_MM_GetNvBlockStatusOfList                            */
/* Description   | Acquire status of specified nonvolatile block Id         */
/* Preconditions | ListIndex < Dem_NvMUseNvblockNum                         */
/* Parameters    | [in] ListIndex :                                         */
/*               |        Index of Nv block list                            */
/* Return Value  | Dem_u08_MMBlockStatusType                                */
/*               |        Status of Nv block                                */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_MMBlockStatusType, DEM_CODE ) Dem_MM_GetNvBlockStatusOfList
(
    VAR( Dem_u16_NvBlockIndexType, AUTOMATIC ) ListIndex    /* [PRMCHK:CALLER] */
)
{
    return Dem_MM_NvBlockStsList[ListIndex].BlockStatus;    /* [GUDCHK:CALLER]ListIndex */
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
