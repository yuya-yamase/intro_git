/* Dcm_Dsp_DataTfrMng_h(v5-3-0)                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_DataTfrMng/HEADER                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_DATATFRMNG_H
#define DCM_DSP_DATATFRMNG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>

#if ( DCM_ULDL_SERVICE_USE == STD_ON )

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct
{
    uint32  u4MemoryAddress;
    uint32  u4MemorySize;
    uint8   u1Dfid;
    uint8   u1MemoryId;
    uint8   u1Bsc;
}Dcm_Dsp_DataTfrMng_TfrInfoType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

FUNC( void, DCM_CODE ) Dcm_Dsp_DataTfrMng_Init
( void );

FUNC( void, DCM_CODE ) Dcm_Dsp_DataTfrMng_InitTfrStatus
( void );

FUNC( uint8, DCM_CODE ) Dcm_Dsp_DataTfrMng_GetTfrStatus
( void );

FUNC( void, DCM_CODE ) Dcm_Dsp_DataTfrMng_InitTfrInfo
( void );

FUNC( void, DCM_CODE ) Dcm_Dsp_DataTfrMng_GetTfrInfo
(
    P2VAR( Dcm_Dsp_DataTfrMng_TfrInfoType, AUTOMATIC, DCM_APPL_DATA ) ptTfrInfo
);

FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DataTfrMng_ChkAlfid
(
    const uint8 u1Alfid
);

FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DataTfrMng_ProcReqDL
(
    Dcm_OpStatusType u1OpStatus,
    uint8 u1DataFormatIdentifier,
    uint8 u1MemoryIdentifier,
    uint32 u4MemoryAddress,
    uint32 u4MemorySize,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptBlockLength,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
);

#if ( DCM_UL_PROCESS_USE == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DataTfrMng_ProcReqUL
(
    Dcm_OpStatusType u1OpStatus,
    uint8 u1DataFormatIdentifier,
    uint8 u1MemoryIdentifier,
    uint32 u4MemoryAddress,
    uint32 u4MemorySize,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptBlockLength,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
);
#endif  /* DCM_UL_PROCESS_USE == STD_ON */

FUNC( Dcm_ReturnWriteMemoryType, DCM_CODE ) Dcm_Dsp_DataTfrMng_ProcTfrDataWrite
(
    Dcm_OpStatusType u1OpStatus,
    uint8 u1Bsc,
    uint32 u4MemorySize,
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA ) ptMemoryData,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
);

#if ( DCM_UL_PROCESS_USE == STD_ON )
FUNC( Dcm_ReturnReadMemoryType, DCM_CODE ) Dcm_Dsp_DataTfrMng_ProcTfrDataRead
(
    Dcm_OpStatusType u1OpStatus,
    uint8 u1Bsc,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptMemorySize,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptMemoryData,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
);
#endif  /* DCM_UL_PROCESS_USE == STD_ON */

FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DataTfrMng_ProcReqTfrExit
(
    Dcm_OpStatusType u1OpStatus,
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA ) ptTransferRequestParameterRecord,
    uint32 u4TransferRequestParameterRecordSize,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptTransferResponseParameterRecord,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptTransferResponseParameterRecordSize,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
);

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

#endif /* DCM_ULDL_SERVICE_USE == STD_ON */

#endif /* DCM_DSP_DATATFRMNG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
