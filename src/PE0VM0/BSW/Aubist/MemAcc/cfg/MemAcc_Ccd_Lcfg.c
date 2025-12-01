/* MemAcc_Ccd_Lcfg.c v2-0-0                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MEMACC/CCD/LCFG/CODE                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <MemAcc.h>
#include "MemAcc_Cfg_Internal.h"

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define MEMACC_START_SEC_VAR_NO_INIT_32
#include <MemAcc_MemMap.h>
VAR ( MemAcc_JobCtlExternalInfoType, MEMACC_VAR_NO_INIT )   MemAcc_JobCtlExtInfoTbl[MEMACC_ADDRESS_AREA_MAX];
#define MEMACC_STOP_SEC_VAR_NO_INIT_32
#include <MemAcc_MemMap.h>

#define MEMACC_START_SEC_CONST_CONFIG_32
#include <MemAcc_MemMap.h>
CONST(AB_83_ConstV uint16, MEMACC_CONFIG_DATA) MemAcc_JobCtlExtInfoTblSize = (uint16)(sizeof(MemAcc_JobCtlExtInfoTbl) / sizeof(MemAcc_JobCtlExtInfoTbl[0]));
#define MEMACC_STOP_SEC_CONST_CONFIG_32
#include <MemAcc_MemMap.h>


#define MEMACC_START_SEC_VAR_NO_INIT_32
#include <MemAcc_MemMap.h>
VAR ( MemAcc_JobCtlExternalInfoType, MEMACC_VAR_NO_INIT )   MemAcc_JobCtlExtInfoTblSub[MEMACC_ADDRESS_AREA_MAX];
#define MEMACC_STOP_SEC_VAR_NO_INIT_32
#include <MemAcc_MemMap.h>

#define MEMACC_START_SEC_CONST_CONFIG_32
#include <MemAcc_MemMap.h>
CONST(AB_83_ConstV uint16, MEMACC_CONFIG_DATA) MemAcc_JobCtlExtInfoTblSubSize = (uint16)(sizeof(MemAcc_JobCtlExtInfoTblSub) / sizeof(MemAcc_JobCtlExtInfoTblSub[0]));
#define MEMACC_STOP_SEC_CONST_CONFIG_32
#include <MemAcc_MemMap.h>


#define MEMACC_START_SEC_VAR_NO_INIT_32
#include <MemAcc_MemMap.h>
VAR ( MemAcc_JobRequestManageType, MEMACC_VAR_NO_INIT )   MemAcc_JobRequestTbl[MEMACC_ADDRESS_AREA_MAX];
#define MEMACC_STOP_SEC_VAR_NO_INIT_32
#include <MemAcc_MemMap.h>

#define MEMACC_START_SEC_CONST_CONFIG_32
#include <MemAcc_MemMap.h>
CONST(AB_83_ConstV uint16, MEMACC_CONFIG_DATA) MemAcc_JobRequestTblSize = (uint16)(sizeof(MemAcc_JobRequestTbl) / sizeof(MemAcc_JobRequestTbl[0]));
#define MEMACC_STOP_SEC_CONST_CONFIG_32
#include <MemAcc_MemMap.h>


#define MEMACC_START_SEC_VAR_NO_INIT_32
#include <MemAcc_MemMap.h>
VAR ( MemAcc_JobRequestManageType, MEMACC_VAR_NO_INIT )   MemAcc_JobRequestTblSub[MEMACC_ADDRESS_AREA_MAX];
#define MEMACC_STOP_SEC_VAR_NO_INIT_32
#include <MemAcc_MemMap.h>

#define MEMACC_START_SEC_CONST_CONFIG_32
#include <MemAcc_MemMap.h>
CONST(AB_83_ConstV uint16, MEMACC_CONFIG_DATA) MemAcc_JobRequestTblSubSize = (uint16)(sizeof(MemAcc_JobRequestTblSub) / sizeof(MemAcc_JobRequestTblSub[0]));
#define MEMACC_STOP_SEC_CONST_CONFIG_32
#include <MemAcc_MemMap.h>


#define MEMACC_START_SEC_VAR_NO_INIT_32
#include <MemAcc_MemMap.h>
VAR( MemAcc_SemCtlLockInfoType, MEMACC_VAR_NO_INIT ) MemAcc_Sem_CtlTBL[MEMACC_ADDRESS_AREA_MAX];
#define MEMACC_STOP_SEC_VAR_NO_INIT_32
#include <MemAcc_MemMap.h>

#define MEMACC_START_SEC_CONST_CONFIG_32
#include <MemAcc_MemMap.h>
CONST(AB_83_ConstV uint16, MEMACC_CONFIG_DATA) MemAcc_Sem_CtlTBLSize = (uint16)(sizeof(MemAcc_Sem_CtlTBL) / sizeof(MemAcc_Sem_CtlTBL[0]));
#define MEMACC_STOP_SEC_CONST_CONFIG_32
#include <MemAcc_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#define MEMACC_START_SEC_CONST_CONFIG_32
#include <MemAcc_MemMap.h>

CONST(AB_83_ConstV uint16, MEMACC_CONFIG_DATA) MemAcc_AddressArea_Max = (uint16)MEMACC_ADDRESS_AREA_MAX;
CONST(AB_83_ConstV uint16, MEMACC_CONFIG_DATA) MemAcc_MemBank_Max     = (uint16)MEMACC_MEM_BANK_MAX;

#define MEMACC_STOP_SEC_CONST_CONFIG_32
#include <MemAcc_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  2-0-0          :2025/02/28                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
