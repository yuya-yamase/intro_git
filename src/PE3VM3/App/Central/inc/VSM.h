/****************************************************************************/
/*                                                                          */
/*  FILE NAME   :   VSM.h                                                   */
/*  FUNCTION    :   CPU SleepWakeup                                         */
/*                  Data Select Layer                                       */
/*                                                                          */
/*  DEPARTMENT  :   DNJP                                                    */
/*  AUTHOR      :                                                           */
/*                                                                          */
/****************************************************************************/
#ifndef VSM_H
#define VSM_H

#include "Std_Types.h"
#include "aip_common.h"
#include "VSM_cfg.h"

/****************************************************************/
/* define                                                       */
/****************************************************************/
#define VSM_SLEEPNG           (0U)
#define VSM_SLEEPOK           (1U)

/*************************************************************/
/*      functions                                            */
/*************************************************************/
void vd_g_VSM_Init(void);
void App_VSM_Main(void);
void vd_g_VSM_SAILWrapper_Init(void);
void vd_g_VSM_SAILWrapper(void);

void PutCnSleepNG_SAIL(const U1 SleepNG);

#endif

