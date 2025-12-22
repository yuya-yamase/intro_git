/* Dcm_Dsp_Main_h(v5-3-0)                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_Main/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_MAIN_H
#define DCM_DSP_MAIN_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>
#include "../../Dcm/Dsp/cfg/Dcm_Dsp_Main_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSP_BIG_ENDIAN               ( (uint8)0x00U )
#define DCM_DSP_LITTLE_ENDIAN            ( (uint8)0x01U )
#define DCM_DSP_OPAQUE                   ( (uint8)0x02U )

/* Do not change the definition order. -----from here----- */
#define DCM_DSP_BOOLEAN                  ( (uint8)0x00U )
#define DCM_DSP_SINT16                   ( (uint8)0x01U )
#define DCM_DSP_SINT32                   ( (uint8)0x02U )
#define DCM_DSP_SINT8                    ( (uint8)0x03U )
#define DCM_DSP_UINT16                   ( (uint8)0x04U )
#define DCM_DSP_UINT32                   ( (uint8)0x05U )
#define DCM_DSP_UINT8                    ( (uint8)0x06U )
#define DCM_DSP_VARIABLE_LENGTH          ( (uint8)0x07U )
#define DCM_DSP_DYNAMIC_LENGTH           ( (uint8)0x08U )
#define DCM_DSP_SINT16_N                 ( (uint8)0x09U )
#define DCM_DSP_SINT32_N                 ( (uint8)0x0AU )
#define DCM_DSP_SINT8_N                  ( (uint8)0x0BU )
#define DCM_DSP_UINT16_N                 ( (uint8)0x0CU )
#define DCM_DSP_UINT32_N                 ( (uint8)0x0DU )
#define DCM_DSP_UINT8_DYN                ( (uint8)0x0EU )
#define DCM_DSP_UINT8_N                  ( (uint8)0x0FU )
/* Do not change the definition order. -----So far----- */

#define DCM_DSP_USE_BLOCK_ID       ( (uint8)0x00U )
#define DCM_DSP_USE_ASYNCH_CS      ( (uint8)0x01U )
#define DCM_DSP_USE_ASYNCH_CS_ERR  ( (uint8)0x02U )
#define DCM_DSP_USE_ASYNCH_FNC     ( (uint8)0x03U )
#define DCM_DSP_USE_ASYNCH_FNC_ERR ( (uint8)0x04U )
#define DCM_DSP_USE_SR             ( (uint8)0x05U )
#define DCM_DSP_USE_SYNCH_CS       ( (uint8)0x06U )
#define DCM_DSP_USE_SYNCH_FNC      ( (uint8)0x07U )
#define DCM_DSP_USE_ECU_SIGNAL     ( (uint8)0x08U )

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

FUNC( void, DCM_CODE ) Dcm_Dsp_Init
( void );
#if ( DCM_PERIODIC_SEND_USE == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsp_Main
( void );
#endif  /* DCM_PERIODIC_SEND_USE == STD_ON */
#if ( DCM_USE_PROVIDE_SERVICE == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsp_Main_SetUserNotifyFlag
(
    const boolean bFlag
);
#endif /* DCM_USE_PROVIDE_SERVICE == STD_ON */
#if ( DCM_USE_PROVIDE_SERVICE == STD_ON )
FUNC( boolean, DCM_CODE ) Dcm_Dsp_Main_GetUserNotifyFlag
( void );
#endif /* DCM_USE_PROVIDE_SERVICE == STD_ON */
FUNC( void, DCM_CODE ) Dcm_Dsp_NotifiedWrongReq
(
    const uint8 u1SID ,
    const Dcm_NegativeResponseCodeType u1ErrorCode
);
FUNC( boolean, DCM_CODE ) Dcm_Dsp_GetSleepPermission
( void );
FUNC( void, DCM_CODE ) Dcm_Dsp_Main_SetIdleFlag
(
    const boolean bFlag
);
FUNC( void, DCM_CODE ) Dcm_Dsp_IdleRefresh
( void );
#if ( DCM_PAGEDBUFFER_ENABLED == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsp_ServiceInit
( void );
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */
FUNC( void, DCM_CODE ) Dcm_Dsp_Main_PreWriteAll
( void );

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>
#if ( DCM_USE_PROVIDE_SERVICE == STD_ON )
extern  VAR( Dcm_MsgContextType, DCM_VAR_NO_INIT ) Dcm_Dsp_Main_stMsgContext;
#endif /* DCM_USE_PROVIDE_SERVICE == STD_ON */
#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST
#include <Dcm_MemMap.h>

#define DCM_STOP_SEC_CONST
#include <Dcm_MemMap.h>

#endif /* DCM_DSP_MAIN_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
