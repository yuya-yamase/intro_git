/* Fee_Dfc_Ram.h  v1-1-0                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/DFC/RAM/HEADER                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef FEE_DFC_RAM_H
#define FEE_DFC_RAM_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "Fee_Common.h"
#include "Fee_Dfc.h"
#include "Fee_ExConst.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define FEE_START_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>

extern  VAR(uint32, FEE_VAR_NO_INIT) Fee_DrvWrap_State;               /* Status returned to upper tier */
extern  VAR(uint32, FEE_VAR_NO_INIT) Fee_DrvWrap_WrittenAdr;          /* Top address of last write record to return to upper layer */
extern  VAR(uint32, FEE_VAR_NO_INIT) Fee_Dfc_BlankCheckEndAdr;
extern  VAR(uint32, FEE_VAR_NO_INIT) Fee_Dfc_MaxBlankCheckNum;
extern  VAR(uint32, FEE_VAR_NO_INIT) Fee_DrvWrap_BlankCheck_State;    /* Blank check status */

#if ( FEE_USE_REDUNDANCY_RAM == STD_ON )
/* Redundancy Data */
extern  VAR(uint32, FEE_VAR_NO_INIT) Fee_DrvWrap_StateSub;
extern  VAR(uint32, FEE_VAR_NO_INIT) Fee_DrvWrap_WrittenAdrSub;
extern  VAR(uint32, FEE_VAR_NO_INIT) Fee_Dfc_BlankCheckEndAdrSub;
extern  VAR(uint32, FEE_VAR_NO_INIT) Fee_Dfc_MaxBlankCheckNumSub;
extern  VAR(uint32, FEE_VAR_NO_INIT) Fee_DrvWrap_BlankCheck_StateSub;
#endif /* FEE_USE_REDUNDANCY_RAM == STD_ON */

#define FEE_STOP_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif  /* FEE_DFC_RAM_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/08/19                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
