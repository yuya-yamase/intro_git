/* AbPartition_h_v2-0-0                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/ABPARTITION/HEADER                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef ABPARTITION_H
#define ABPARTITION_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include "../AbPartition/cfg/AbPartition_Cfg.h"


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define ABPT_KIND_MNG_CENTRAL    ((AbPT_PartitionKind)0x00U)
#define ABPT_KIND_MNG            ((AbPT_PartitionKind)0x01U)
#define ABPT_KIND_UNMNG          ((AbPT_PartitionKind)0x02U)


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef uint8 AbPT_PartitionKind;

typedef struct {
    VAR(AbPT_PartitionKind, TYPEDEF) u1PartitionKind;
} AbPT_PartitionInfo;

typedef struct {
    P2CONST(AB_83_ConstV AbPT_PartitionInfo, TYPEDEF, TYPEDEF) ptstPartitionInfo;
    VAR(uint32, TYPEDEF) u4OsapId;
    VAR(uint16, TYPEDEF) u2CoreId;
    VAR(boolean, TYPEDEF) bIsTrusted;
} AbPT_OsApplicationInfo;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define ABPT_START_SEC_CONST_CONFIG
#include <AbPartition_MemMap.h>

extern CONST(AB_83_ConstV AbPT_OsApplicationInfo, ABPT_CONST_CONFIG) AbPT_stOsApplicationInfoList[ABPT_OS_APPLICATION_NUM];
extern CONST(AB_83_ConstV uint32, ABPT_CONST_CONFIG) AbPT_u4PartitionNum;
extern CONST(AB_83_ConstV uint8, ABPT_CONST_CONFIG) AbPT_u1OsApplicationNum;
extern CONST(AB_83_ConstV uint8, ABPT_CONST_CONFIG) AbPT_u1CoreNum;

#define ABPT_STOP_SEC_CONST_CONFIG
#include <AbPartition_MemMap.h>

#endif /* ABPARTITION_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2021/12/1                                               */
/****************************************************************************/

/**** End of File ***********************************************************/
