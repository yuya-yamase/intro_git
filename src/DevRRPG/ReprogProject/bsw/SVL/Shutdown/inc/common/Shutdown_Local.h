/* Shutdown_Local_h_Revision(v3.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Shutdown/Local/HEADER                                       */
/******************************************************************************/
#ifndef SHUTDOWN_LOCAL_H
#define SHUTDOWN_LOCAL_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#if( REPROG_CFG_STAYINBOOT_ENABLE == STD_ON )
#include <SchM.h>
#endif


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#if( REPROG_CFG_STAYINBOOT_ENABLE == STD_ON )
#define SHUTDOWN_STATE_BOOT_ENTRY           (SCHM_STATE_BOOT_ENTRY)
#define SHUTDOWN_STATE_AP_ENTRY             (SCHM_STATE_AP_ENTRY)
#define SHUTDOWN_STATE_STAYINBOOT_WAIT      (SCHM_STATE_STAYINBOOT_WAIT)
#define SHUTDOWN_STATE_STAYINBOOT_TMO       (SCHM_STATE_STAYINBOOT_TMO)
#define SHUTDOWN_STATE_STAYINBOOT_PRGRCV    (SCHM_STATE_STAYINBOOT_PRGRCV)
#endif


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
/* Shutdown.c */
FUNC(void, SHUTDOWN_CODE_FAST) Shutdown_ClearRamUnused (void);
FUNC(void, SHUTDOWN_CODE_FAST) Shutdown_ClearRam2nd (void);
FUNC(void, SHUTDOWN_CODE_FAST) Shutdown_ClearRam1st (void);
FUNC(void, SHUTDOWN_CODE_FAST) Shutdown_WdgTrigger (void);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/


#endif /* SHUTDOWN_LOCAL_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2018/06/19 :Update                                rel.AUBASS */
/*  v3.00       :2021/09/14 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

