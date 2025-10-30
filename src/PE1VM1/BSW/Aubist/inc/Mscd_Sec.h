/* Mscd_Sec.h v2-0-0                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MSCD/SEC/HEADER                                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef MSCD_SEC_H
#define MSCD_SEC_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Mscd_Types.h>
#include "../Mscd/cfg/Mscd_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/* Flash Resource Manager */
#define MSCD_FRM_USE                 (STD_OFF)

#define MSCD_FRM_SUSPEND_OK                    (0x00U)
#define MSCD_FRM_SUSPEND_WAIT                  (0x01U)
#define MSCD_FRM_SUSPEND_HARD_ERROR            (0x02U)
#define MSCD_FRM_SUSPEND_DENIED                (0x03U)

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define MSCD_START_SEC_CODE
#include <Mscd_MemMap.h>

FUNC(void, MSCD_CODE) Mscd_Frm_SuspendFlashAccess( void );

FUNC(void, MSCD_CODE) Mscd_Frm_ResumeFlashAccess( uint8 u1Result );

FUNC(void, MSCD_CODE) Mscd_Frm_CancelSuspendFlashAccess( void );

#define MSCD_STOP_SEC_CODE
#include <Mscd_MemMap.h>

#endif /* MSCD_SEC_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  1-1-0          :2019/01/31                                              */
/*  2-0-0          :2021/04/14                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
