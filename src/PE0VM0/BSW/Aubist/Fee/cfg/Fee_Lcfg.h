/* Fee_Lcfg.h v1-1-0                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/LCFG/HEADER                                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef FEE_LCFG_H
#define FEE_LCFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "Fee_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#define FEE_START_SEC_CONST_CONFIG_32
#include <Fee_MemMap.h>

extern CONST( AB_83_ConstV uint8,  FEE_CONFIG_DATA ) FeeBlockConfigurations[];
extern CONST( AB_83_ConstV uint16, FEE_CONFIG_DATA)  FeeBlockConfigurationsSize;

#if ( FEE_RECORDPOSTBL_ENABLE == STD_ON )
extern CONST( AB_83_ConstV uint16, FEE_CONFIG_DATA ) FeeRecPosTblIdx[];
extern CONST( AB_83_ConstV uint16, FEE_CONFIG_DATA ) FeeRecPosTblIdxSize;
#endif /* FEE_RECORDPOSTBL_ENABLE == STD_ON */

#define FEE_STOP_SEC_CONST_CONFIG_32
#include <Fee_MemMap.h>

#endif /* FEE_LCFG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/06/04                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
