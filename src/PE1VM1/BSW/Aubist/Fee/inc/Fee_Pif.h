/* Fee_Pif.h v2-0-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/PIF/HEADER                                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef FEE_PIF_H
#define FEE_PIF_H

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

FUNC( void, FEE_CODE ) Fee_Pif_WriteEndNotification(
    uint8   JobResult
);

FUNC( void, FEE_CODE ) Fee_Pif_ReadEndNotification(
    uint8   JobResult
);

FUNC( void, FEE_CODE ) Fee_Pif_RebuildEndNotification(
    uint8   JobResult
);

FUNC( void, FEE_CODE )
Fee_Pif_CancelEndNotification( void );

FUNC( void, FEE_CODE )
Fee_Pif_AbortEndNotification( void );

FUNC( Std_ReturnType, FEE_CODE ) Fee_Pif_GetAreaNoFromBlockNumber(
    uint16 SrcBlockNumber,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DstAreaNo
);

FUNC( Std_ReturnType, FEE_CODE )
Fee_Pif_GetCfgTblIdxFromBlockNumber(
    uint16 SrcBlockNumber,
    P2VAR( uint16, AUTOMATIC, AUTOMATIC ) DstCfgTblIdx
);

#if (FEE_RECORDPOSTBL_ENABLE == STD_ON) 
FUNC( void, FEE_CODE )
Fee_Pif_GetDatasetIdxFromBlockNumber(
    uint16 SrcBlockNumber,
    P2VAR( uint16, AUTOMATIC, AUTOMATIC ) DstDatasetIdx
);
#endif /* FEE_RECORDPOSTBL_ENABLE == STD_ON */ 

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

#endif /* FEE_PIF_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/08/26                                              */
/*  2-0-0          :2022/08/24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
