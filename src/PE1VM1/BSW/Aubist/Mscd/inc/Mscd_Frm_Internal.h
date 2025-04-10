/* Mscd_Frm_Internal.h v1-0-0                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MSCD/FRM/INTERNAL/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef MSCD_FRM_INTERNAL_H
#define MSCD_FRM_INTERNAL_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

#if( MSCD_FRM_USE == STD_ON )

#define MSCD_FRM_REQUEST_EVT_SUSPEND       (0x00U)
#define MSCD_FRM_RESPONSE_EVT_SUSPEND      (0x01U)
#define MSCD_FRM_REQUEST_EVT_NONE          (0xFFU)

#define MSCD_FRM_EXCLUSIVE_LOCK            (0x00U)
#define MSCD_FRM_EXCLUSIVE_UNLOCK          (0x01U)

#define MSCD_FRM_RESULTHOOK_DISABLED       (0x00U)
#define MSCD_FRM_RESULTHOOK_ENABLED        (0x01U)

#define MSCD_FRM_RESULT_OK                 (FEE_EXT_SRA_RESULT_OK)
#define MSCD_FRM_RESULT_NG_USED_HSM        (FEE_EXT_SRA_RESULT_NG_USED_HSM)
#define MSCD_FRM_RESULT_NG_HW_BUSY         (FEE_EXT_SRA_RESULT_NG_HW_BUSY)
#define MSCD_FRM_RESULT_NG_SUSPEND         (FEE_EXT_SRA_RESULT_NG_SUSPEND)
#define MSCD_FRM_RESULT_NG_INTERNAL        (FEE_EXT_SRA_RESULT_INTERNAL)
#define MSCD_FRM_RESULT_NG_REQ_CANCELED    (FEE_EXT_SRA_RESULT_REQ_CANCELED)
#define MSCD_FRM_RESULT_NONE               (0xFFU)

#define MSCD_FRM_RSP_OK                    (FEE_EXT_SRA_RSP_OK)
#define MSCD_FRM_RSP_OK_SUSPENDED          (FEE_EXT_SRA_RSP_OK_SUSPENDED)
#define MSCD_FRM_RSP_NG_USED_HSM           (FEE_EXT_SRA_RSP_NG_USED_HSM)
#define MSCD_FRM_RSP_NG_SUSPEND            (FEE_EXT_SRA_RSP_NG_SUSPEND)
#define MSCD_FRM_RSP_NG_INTERNAL           (FEE_EXT_SRA_RSP_NG_INTERNAL)

#endif

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define MSCD_START_SEC_CODE
#include <Mscd_MemMap.h>

#if( MSCD_FRM_USE == STD_ON )

FUNC( void, MSCD_CODE ) Mscd_Frm_ActSuspendFlashAccess( void );
FUNC( void, MSCD_CODE ) Mscd_Frm_SubSuspendResultHook( uint8 u1Result );
FUNC( void, MSCD_CODE ) Mscd_Frm_ActSuspendResultHook( void );
FUNC( void, MSCD_CODE ) Mscd_Frm_ActErrorSuspendResultHook( void );
FUNC( void, MSCD_CODE ) Mscd_Frm_ActResumeFlashAccess( void );
FUNC( void, MSCD_CODE ) Mscd_Frm_ActCancelSuspendFlashAccess( void );
FUNC( void, MSCD_CODE ) Mscd_Frm_PreExclusiveLock( void );
FUNC( void, MSCD_CODE ) Mscd_Frm_PostExclusiveUnLock( void );
FUNC( void, MSCD_CODE ) Mscd_Frm_PreSuspendFlashAccess( void );
FUNC( void, MSCD_CODE ) Mscd_Frm_PostSuspendFlashAccess( void );
FUNC( void, MSCD_CODE ) Mscd_Frm_UpdateSuspendStatus( uint8 u1SuspendStatus );
FUNC( Std_ReturnType, MSCD_CODE ) Mscd_Frm_CheckSuspendStatus( void );

#endif

#define MSCD_STOP_SEC_CODE
#include <Mscd_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


#endif /* MSCD_FRM_INTERNAL_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
