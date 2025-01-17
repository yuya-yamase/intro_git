/* Rte_MemM_h_Revision(v4.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Rte/MemM/HEADER                                             */
/******************************************************************************/
#ifndef RTE_MEMM_H
#define RTE_MEMM_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <MemM.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define RTE_MEMM_UNINIT             ((Rte_MemM_StatusType)MEMM_UNINIT)
#define RTE_MEMM_IDLE               ((Rte_MemM_StatusType)MEMM_IDLE)
#define RTE_MEMM_BUSY               ((Rte_MemM_StatusType)MEMM_BUSY)
#define RTE_MEMM_UPDATEIDLE         ((Rte_MemM_StatusType)MEMM_UPDATEIDLE)
#define RTE_MEMM_UPDATEBUSY         ((Rte_MemM_StatusType)MEMM_UPDATEBUSY)
#define RTE_MEMM_UPDATECOMPLETE     ((Rte_MemM_StatusType)MEMM_UPDATECOMPLETE)

#define RTE_MEMM_JOB_OK             ((Rte_MemM_JobResultType)MEMM_JOB_OK)
#define RTE_MEMM_JOB_FAILED         ((Rte_MemM_JobResultType)MEMM_JOB_FAILED)
#define RTE_MEMM_JOB_PENDING        ((Rte_MemM_JobResultType)MEMM_JOB_PENDING)

#define RTE_MEMM_DEVICE_TYPE_CODEFLS    (MEMM_DEVICE_TYPE_CODEFLS)
#define RTE_MEMM_DEVICE_TYPE_EXTCODEFLS (MEMM_DEVICE_TYPE_EXTCODEFLS)
#define RTE_MEMM_DEVICE_TYPE_CODERAM    (MEMM_DEVICE_TYPE_CODERAM)

#define Rte_MemM_Erase              (MemM_Erase)
#define Rte_MemM_Read               (MemM_Read)
#define Rte_MemM_GetStatus          (MemM_GetStatus)
#define Rte_MemM_GetJobResult       (MemM_GetJobResult)
#define Rte_MemM_ReprogComplete     (MemM_ReprogComplete)
#define Rte_MemM_GetBlockInfo       (MemM_GetBlockInfo)
#define Rte_MemM_WriteStart         (MemM_WriteStart)
#define Rte_MemM_WriteUpdate        (MemM_WriteUpdate)
#define Rte_MemM_WriteFinish        (MemM_WriteFinish)
#define Rte_MemM_CnvPhysicalAddr    (MemM_CnvPhysicalAddr)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef MemM_StatusType       Rte_MemM_StatusType;
typedef MemM_JobResultType    Rte_MemM_JobResultType;
typedef MemM_BlockInfoType    Rte_MemM_BlockInfoType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/


#endif /* RTE_MEMM_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2019/12/03 :Update                                rel.AUBASS */
/*  v3.00       :2021/03/09 :Update                                rel.AUBASS */
/*  v4.00       :2021/09/14 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

