/* nmstack_types_h_v2-0-0                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NMSTACK/TYPES/HEADER                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_NMSTACK_TYPES_AR_H
#define BSW_NMSTACK_TYPES_AR_H

#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include <ComStack_Types.h>
#include <nm/bsw_nm_public.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/* NM State */
#define NM_STATE_UNINIT             (BSW_NM_STATE_UNINIT)
#define NM_STATE_BUS_SLEEP          (BSW_NM_STATE_BUS_SLEEP)
#define NM_STATE_PREPARE_BUS_SLEEP  (BSW_NM_STATE_PREPARE_BUS_SLEEP)
#define NM_STATE_READY_SLEEP        (BSW_NM_STATE_READY_SLEEP)
#define NM_STATE_NORMAL_OPERATION   (BSW_NM_STATE_NORMAL_OPERATION)
#define NM_STATE_REPEAT_MESSAGE     (BSW_NM_STATE_REPEAT_MESSAGE)
#define NM_STATE_SYNCHRONIZE        (BSW_NM_STATE_SYNCHRONIZE)
#define NM_STATE_OFFLINE            (BSW_NM_STATE_OFFLINE)
#define NM_STATE_INVALID            (BSW_NM_STATE_INVALID)

/* NM Mode */
#define NM_MODE_BUS_SLEEP           (BSW_NM_MODE_BUS_SLEEP)
#define NM_MODE_PREPARE_BUS_SLEEP   (BSW_NM_MODE_PREPARE_BUS_SLEEP)
#define NM_MODE_SYNCHRONIZE         (BSW_NM_MODE_SYNCHRONIZE)
#define NM_MODE_NETWORK             (BSW_NM_MODE_NETWORK)
#define NM_MODE_INVALID             (BSW_NM_MODE_INVALID)

/* BusNm Type */
#define NM_BUSNM_CANNM              (BSW_NM_BUSNM_CANNM)
#define NM_BUSNM_LINNM              (BSW_NM_BUSNM_LINNM)
#define NM_BUSNM_UDPNM              (BSW_NM_BUSNM_UDPNM)
#define NM_BUSNM_GENERICNM1         (BSW_NM_BUSNM_GENERICNM1)
#define NM_BUSNM_GENERICNM2         (BSW_NM_BUSNM_GENERICNM2)
#define NM_BUSNM_UNDEF              (BSW_NM_BUSNM_UNDEF)

/* Direction */
#define NM_DIRECTION_TX             (BSW_NM_DIRECTION_TX)
#define NM_DIRECTION_RX             (BSW_NM_DIRECTION_RX)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
#define Nm_StateType            Bsw_Nm_StateType
#define Nm_ModeType             Bsw_Nm_ModeType
#define Nm_BusNmType            Bsw_Nm_BusNmType
#define Nm_DirectionType        Bsw_Nm_DirectionType

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif  /* BSW_NMSTACK_TYPES_AR_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/02/22                                             */
/*  v2-0-0          :2021/09/09                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
