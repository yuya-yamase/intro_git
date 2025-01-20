/* WdgM_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | WdgM/HEADER                                                 */
/******************************************************************************/
#ifndef WDGM_H
#define WDGM_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define WDGM_ENTITYID_BASE      (0x0000U)
#define WDGM_ENTITYID_TIMEHIGH  (0x0001U)
#define WDGM_ENTITYID_TIMELOW   (0x0002U)

#define WDGM_CHKPNTID_0         ((WdgM_CheckpointIdType)0x0000U)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef struct {
    uint16  TimeoutVal;
} WdgM_ConfigType;

typedef uint16 WdgM_SupervisedEntityIdType;
typedef uint16 WdgM_CheckpointIdType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
FUNC(void, WDGM_CODE_SLOW) WdgM_Init
(
    P2CONST(WdgM_ConfigType, AUTOMATIC, WDGM_APPL_CONST) ConfigPtr
);
FUNC(void, WDGM_CODE_SLOW) WdgM_DeInit (void);
FUNC(Std_ReturnType, WDGM_CODE_SLOW) WdgM_CheckpointReached
(
    VAR(WdgM_SupervisedEntityIdType, AUTOMATIC) SeId,
    VAR(WdgM_CheckpointIdType, AUTOMATIC) CheckpointId
);
FUNC(void, WDGM_CODE_SLOW) WdgM_Trigger (void);
FUNC(void, WDGM_CODE_SLOW) WdgM_SetTriggerCondition (void);
FUNC(void, WDGM_CODE_SLOW) WdgM_MainFunction (void);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define WDGM_START_SEC_CST
#include <WdgM_MemMap.h>

extern CONST(WdgM_ConfigType, WDGM_CONFIG_DATA) WdgM_Cfg_Data;

#define WDGM_STOP_SEC_CST
#include <WdgM_MemMap.h>


#endif /* WDGM_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

