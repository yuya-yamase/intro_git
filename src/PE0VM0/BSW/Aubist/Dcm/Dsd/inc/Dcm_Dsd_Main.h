/* Dcm_Dsd_Main_h(v3-2-0)                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsd_Main/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes |                                                                  */
/****************************************************************************/
#ifndef DCM_DSD_MAIN_H
#define DCM_DSD_MAIN_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>
#include "../../Dsd/cfg/Dcm_Dsd_Main_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSD_NRC_INVALID      ((Dcm_NegativeResponseCodeType)0x00U)
#define DCM_DSD_SUPPRESS_BIT     ((uint8)0x80U)    /* suppressPosResponse judgment bit  */
#define DCM_DSD_SUPPRESS_BITMASK ((uint8)0x7FU)    /* suppressPosResponse bit mask      */
#define DCM_DSD_CONID_INVALID    ((uint16)0xFFFFU) /* suppressPosResponse bit mask      */
#define DCM_DSD_TESTER_INVALID   ((uint16)0xFFFFU) /* suppressPosResponse bit mask      */
#define DCM_DSD_RX_SID_OFFSET    ((uint8)0x00U)    /* SID offset of the request message */
#define DCM_DSD_RX_SF_OFFSET     ((uint8)0x01U)    /* SF  offset of the request message */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

FUNC( void, DCM_CODE ) Dcm_Dsd_Init
( void );

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_CONST
#include <Dcm_MemMap.h>


#endif /* DCM_DSD_MAIN_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-2-0         :2020-10-28                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
