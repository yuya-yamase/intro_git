/****************************************************************************/
/*  Copyright DENSO Corporation. All rights reserved.						*/
/****************************************************************************/
/****************************************************************************/
/* [File Name]		Ecu_Task.h 												*/
/* [Module]			Ecu_Task												*/
/* [Function]		Ecu_Task												*/
/* [Notes]			None													*/
/****************************************************************************/

#ifndef ECU_TASK_H
#define ECU_TASK_H

/*--------------------------------------------------------------------------*/
/*		Headers															*/
/*--------------------------------------------------------------------------*/
#include <SS.h>

/*--------------------------------------------------------------------------*/
/*		Symbols															*/
/*--------------------------------------------------------------------------*/
#if (SS_INTG_RTE != STD_ON)
#define ECU_TASK_u4HIGHTASK_ACTIVATECYCLE   (1UL)  /* 1ms （1ms × 1カウント） */
#define ECU_TASK_u4MEDIUMTASK_ACTIVATECYCLE (5UL)  /* 5ms  (1ms × 5カウント） */
#define ECU_TASK_u4LOWTASK_ACTIVATECYCLE    (1UL)  /* 1ms  (1ms × 1カウント） */

#define ECU_TASK_u4ALARMOFFSET (1UL)

#endif /* (SS_INTG_RTE != STD_ON) */

/*--------------------------------------------------------------------------*/
/*		Prototypes															*/
/*--------------------------------------------------------------------------*/
#if (SS_INTG_RTE == STD_ON) // RTEから呼び出すため、公開する。
void Ecu_HighTask(void);
/* void Ecu_MediumHighTask(void); */
void Ecu_MediumTask(void);
#if 0u /* for future extention */
void Ecu_MediumLowTask(void);
#endif
void Ecu_LowTask(void);
#endif

#endif /* ECU_TASK_H */
