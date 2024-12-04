/* Can_GeneralTypes_h_v2-0-0                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN_GENERALTYPES/HEADER                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     BSW_CAN_GENERALTYPES_AR_H
#define     BSW_CAN_GENERALTYPES_AR_H

#include <Can.h>
#include <canif/bsw_canif_public.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define CANTRCV_TRCVMODE_NORMAL             (BSW_CANTRCV_TRCVMODE_NORMAL)
#define CANTRCV_TRCVMODE_SLEEP              (BSW_CANTRCV_TRCVMODE_SLEEP)
#define CANTRCV_TRCVMODE_STANDBY            (BSW_CANTRCV_TRCVMODE_STANDBY)

#define CANTRCV_WUMODE_ENABLE               (BSW_CANTRCV_WUMODE_ENABLE)
#define CANTRCV_WUMODE_DISABLE              (BSW_CANTRCV_WUMODE_DISABLE)
#define CANTRCV_WUMODE_CLEAR                (BSW_CANTRCV_WUMODE_CLEAR)

#define CANTRCV_WU_ERROR                    (BSW_CANTRCV_WU_ERROR)
#define CANTRCV_WU_NOT_SUPPORTED            (BSW_CANTRCV_WU_NOT_SUPPORTED)
#define CANTRCV_WU_BY_BUS                   (BSW_CANTRCV_WU_BY_BUS)
#define CANTRCV_WU_INTERNALLY               (BSW_CANTRCV_WU_INTERNALLY)
#define CANTRCV_WU_RESET                    (BSW_CANTRCV_WU_RESET)
#define CANTRCV_WU_POWER_ON                 (BSW_CANTRCV_WU_POWER_ON)
#define CANTRCV_WU_BY_PIN                   (BSW_CANTRCV_WU_BY_PIN)
#define CANTRCV_WU_BY_SYSERR                (BSW_CANTRCV_WU_BY_SYSERR)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
#define CanTrcv_TrcvModeType            Bsw_CanTrcv_TrcvModeType
#define CanTrcv_TrcvWakeupModeType      Bsw_CanTrcv_TrcvWakeupModeType
#define CanTrcv_TrcvWakeupReasonType    Bsw_CanTrcv_TrcvWakeupReasonType

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif  /* BSW_CAN_GENERALTYPES_AR_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/02/22                                             */
/*  v2-0-0          :2021/05/19                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
