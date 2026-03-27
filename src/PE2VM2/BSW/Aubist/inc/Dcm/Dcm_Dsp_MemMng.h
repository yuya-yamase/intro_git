/* Dcm_Dsp_MemMng_h(v5-6-0)                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_MemMng/HEADER                                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_MEMMNG_H
#define DCM_DSP_MEMMNG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Main_Common.h>
#include "../../Dcm/Dsp/cfg/Dcm_Dsp_MemMng_Cfg.h"
#include <Dcm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

#if( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID23 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) || ( DCM_SUPPORT_SID3D == STD_ON ) )
FUNC( boolean, DCM_CODE ) Dcm_Dsp_MemMng_GetUseAsMemoryId
(
    void
);
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID23 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON || DCM_SUPPORT_SID3D == STD_ON */
#if( ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID23 == STD_ON ) )
FUNC( uint32, DCM_CODE ) Dcm_Dsp_MemMng_GetMaxReadMemorySize
(
    void
);
#endif /* DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID23 == STD_ON */
#if( DCM_SUPPORT_SID3D == STD_ON )
FUNC( uint32, DCM_CODE ) Dcm_Dsp_MemMng_GetMaxWriteMemorySize
(
    void
);
#endif /* DCM_SUPPORT_SID3D == STD_ON */

#if( DCM_SUPPORT_SID22 == STD_ON )
#if( DCM_PAGEDBUFFER_SID22_ENABLED == STD_OFF )
#if( DCM_PAGEDBUFFER_SID23_ENABLED == STD_OFF )
FUNC( Dcm_ReturnReadMemoryType, DCM_CODE ) Dcm_Dsp_MemMng_ReadMemory
(
    Dcm_OpStatusType                                                u1OpStatus,
    uint8                                                           u1MemoryIdentifier,
    uint32                                                          u4MemoryAddress,
    uint32                                                          u4MemorySize,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )                        ptMemoryData,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
);
#endif /* DCM_PAGEDBUFFER_SID23_ENABLED == STD_OFF */
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_OFF */
#if( DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON )
#if( DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON )
FUNC( Dcm_ReturnReadMemoryType, DCM_CODE ) Dcm_Dsp_MemMng_ReadMemory
(
    Dcm_OpStatusType                                                u1OpStatus,
    uint8                                                           u1MemoryIdentifier,
    uint32                                                          u4MemoryAddress,
    uint32                                                          u4MemorySize,
    uint32                                                          u4MaxMemorySize,
    uint32                                                          u4StoredMemorySize,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )                        ptMemoryData,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
);
#endif /* DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON */
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON */
#endif /* DCM_SUPPORT_SID22 == STD_ON */

#if( DCM_PERIODIC_DDDID_USE == STD_ON )
FUNC( Dcm_ReturnReadMemoryType, DCM_CODE ) Dcm_Dsp_MemMng_ReadMemoryForPeriodic
(
    Dcm_OpStatusType                                                u1OpStatus,
    uint8                                                           u1MemoryIdentifier,
    uint32                                                          u4MemoryAddress,
    uint32                                                          u4MemorySize,
    uint32                                                          u4MaxMemorySize,
    uint32                                                          u4StoredMemorySize,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )                        ptMemoryData,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
);
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON */

#if( DCM_SUPPORT_SID3D == STD_ON )
FUNC( Dcm_ReturnWriteMemoryType, DCM_CODE ) Dcm_Dsp_MemMng_WriteMemory
(
    Dcm_OpStatusType                                                u1OpStatus,
    uint8                                                           u1MemoryIdentifier,
    uint32                                                          u4MemoryAddress,
    uint32                                                          u4MemorySize,
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA )                      ptMemoryData,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
);
#endif /* DCM_SUPPORT_SID3D == STD_ON */

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


#endif /* DSP_MEMMNG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-6-0         :2024-02-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

