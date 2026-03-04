/* MemAcc_Lcfg.h v2-0-0                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MEMACC/LCFG/HEADER                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     MEMACC_LCFG_H
#define     MEMACC_LCFG_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define MEMACC_START_SEC_VAR_NO_INIT_32
#include <MemAcc_MemMap.h>
extern VAR ( MemAcc_JobCtlExternalInfoType, MEMACC_VAR_NO_INIT )   MemAcc_JobCtlExtInfoTbl[];
#define MEMACC_STOP_SEC_VAR_NO_INIT_32
#include <MemAcc_MemMap.h>

#define MEMACC_START_SEC_CONST_CONFIG_32
#include <MemAcc_MemMap.h>
extern CONST(AB_83_ConstV uint16, MEMACC_CONFIG_DATA) MemAcc_JobCtlExtInfoTblSize;
#define MEMACC_STOP_SEC_CONST_CONFIG_32
#include <MemAcc_MemMap.h>


#define MEMACC_START_SEC_VAR_NO_INIT_32
#include <MemAcc_MemMap.h>
extern VAR ( MemAcc_JobCtlExternalInfoType, MEMACC_VAR_NO_INIT )   MemAcc_JobCtlExtInfoTblSub[];
#define MEMACC_STOP_SEC_VAR_NO_INIT_32
#include <MemAcc_MemMap.h>

#define MEMACC_START_SEC_CONST_CONFIG_32
#include <MemAcc_MemMap.h>
extern CONST(AB_83_ConstV uint16, MEMACC_CONFIG_DATA) MemAcc_JobCtlExtInfoTblSubSize;
#define MEMACC_STOP_SEC_CONST_CONFIG_32
#include <MemAcc_MemMap.h>


#define MEMACC_START_SEC_VAR_NO_INIT_32
#include <MemAcc_MemMap.h>
extern VAR ( MemAcc_JobRequestManageType, MEMACC_VAR_NO_INIT )   MemAcc_JobRequestTbl[];
#define MEMACC_STOP_SEC_VAR_NO_INIT_32
#include <MemAcc_MemMap.h>

#define MEMACC_START_SEC_CONST_CONFIG_32
#include <MemAcc_MemMap.h>
extern CONST(AB_83_ConstV uint16, MEMACC_CONFIG_DATA) MemAcc_JobRequestTblSize;
#define MEMACC_STOP_SEC_CONST_CONFIG_32
#include <MemAcc_MemMap.h>


#define MEMACC_START_SEC_VAR_NO_INIT_32
#include <MemAcc_MemMap.h>
extern VAR ( MemAcc_JobRequestManageType, MEMACC_VAR_NO_INIT )   MemAcc_JobRequestTblSub[];
#define MEMACC_STOP_SEC_VAR_NO_INIT_32
#include <MemAcc_MemMap.h>

#define MEMACC_START_SEC_CONST_CONFIG_32
#include <MemAcc_MemMap.h>
extern CONST(AB_83_ConstV uint16, MEMACC_CONFIG_DATA) MemAcc_JobRequestTblSubSize;
#define MEMACC_STOP_SEC_CONST_CONFIG_32
#include <MemAcc_MemMap.h>


#define MEMACC_START_SEC_VAR_NO_INIT_32
#include <MemAcc_MemMap.h>
extern VAR( MemAcc_SemCtlLockInfoType, MEMACC_VAR_NO_INIT ) MemAcc_Sem_CtlTBL[];
#define MEMACC_STOP_SEC_VAR_NO_INIT_32
#include <MemAcc_MemMap.h>

#define MEMACC_START_SEC_CONST_CONFIG_32
#include <MemAcc_MemMap.h>
extern CONST(AB_83_ConstV uint16, MEMACC_CONFIG_DATA) MemAcc_Sem_CtlTBLSize;
#define MEMACC_STOP_SEC_CONST_CONFIG_32
#include <MemAcc_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define MEMACC_START_SEC_CONST_CONFIG_32
#include <MemAcc_MemMap.h>

extern CONST (AB_83_ConstV uint16, MEMACC_CONFIG_DATA) MemAcc_AddressArea_Max;
extern CONST (AB_83_ConstV uint16, MEMACC_CONFIG_DATA) MemAcc_MemBank_Max;

extern CONST ( AB_83_ConstV MemAcc_AddressAreaConfiguration, MEMACC_CONFIG_DATA ) MemAcc_AddrAreaCfg[];

#define MEMACC_STOP_SEC_CONST_CONFIG_32
#include <MemAcc_MemMap.h>

#endif  /* MEMACC_LCFG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  2-0-0          :2025/02/28                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
