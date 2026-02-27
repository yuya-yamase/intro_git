/* Dcm_Dsp_DidMng_h(v5-10-0)                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_DidMng/HEADER                                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_DIDMNG_H
#define DCM_DSP_DIDMNG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../Dcm/Dsp/cfg/Dcm_Dsp_DidMng_Cfg.h"
#include <Dcm/Dcm_Dsp_DidMng_OBD.h>
#include <Dcm/Dcm_Main_Common.h>
#include <Dcm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSP_DIDMNG_CHECK_CTRL_SES    ((uint8)0x01U)
#define DCM_DSP_DIDMNG_CHECK_CTRL_SEC    ((uint8)0x02U)
#define DCM_DSP_DIDMNG_CHECK_READ_MR     ((uint8)0x10U)
#define DCM_DSP_DIDMNG_CHECK_READ_SES    ((uint8)0x11U)
#define DCM_DSP_DIDMNG_CHECK_READ_SEC    ((uint8)0x12U)
#define DCM_DSP_DIDMNG_CHECK_WRITE_SES   ((uint8)0x21U)
#define DCM_DSP_DIDMNG_CHECK_WRITE_SEC   ((uint8)0x22U)

#define DCM_DSP_DIDMNG_CONTROL_ONLY      ((uint8)0x01U)
#define DCM_DSP_DIDMNG_READ_ONLY         ((uint8)0x02U)
#define DCM_DSP_DIDMNG_CR_BOTH           ((uint8)0x03U)
#define DCM_DSP_DIDMNG_WRITE_ONLY        ((uint8)0x04U)
#define DCM_DSP_DIDMNG_CW_BOTH           ((uint8)0x05U)
#define DCM_DSP_DIDMNG_RW_BOTH           ((uint8)0x06U)
#define DCM_DSP_DIDMNG_CRW_ALL           ((uint8)0x07U)
#define DCM_DSP_DIDMNG_DYNAMIC           ((uint8)0x08U)
#define DCM_DSP_DIDMNG_CONTROL_ONLY_DYN  ((uint8)0x09U)
#define DCM_DSP_DIDMNG_READ_ONLY_DYN     ((uint8)0x0AU)
#define DCM_DSP_DIDMNG_CR_BOTH_DYN       ((uint8)0x0BU)
#define DCM_DSP_DIDMNG_WRITE_ONLY_DYN    ((uint8)0x0CU)
#define DCM_DSP_DIDMNG_CW_BOTH_DYN       ((uint8)0x0DU)
#define DCM_DSP_DIDMNG_RW_BOTH_DYN       ((uint8)0x0EU)
#define DCM_DSP_DIDMNG_CRW_ALL_DYN       ((uint8)0x0FU)

#define DCM_DSP_DIDMNG_DID               ((uint8)0x00U)
#define DCM_DSP_DIDMNG_DID_RANGE         ((uint8)0x01U)
#define DCM_DSP_DIDMNG_DID_DYNAMIC       ((uint8)0x02U)
#define DCM_DSP_DIDMNG_DID_OBDDID        ((uint8)0x03U)

#define DCM_DSP_DIDMNG_MEM_ID_VALID      ((uint8)0x00U)
#define DCM_DSP_DIDMNG_MEM_ID_INVALID    ((uint8)0x01U)

#define DCM_DSP_DIDMNG_MEM_READ          ((uint8)0x00U)
#define DCM_DSP_DIDMNG_MEM_WRITE         ((uint8)0x01U)

#define DCM_DSP_DIDMNG_DATA_IDENTIFIER   ((uint8)0x01U)
#define DCM_DSP_DIDMNG_MEM_ADDRESS       ((uint8)0x02U)


#define DCM_DSP_DIDMNG_SOURCEELEMENTID_INVALID  ((uint8)0x0U)
#define DCM_DSP_DIDMNG_SOURCEELEMENTID_DID      ((uint8)0x1U)
#define DCM_DSP_DIDMNG_SOURCEELEMENTID_MEMADDR  ((uint8)0x2U)

#define DCM_DSP_DIDMNG_CLEAR_ALL_2CSF03         ((uint8)0x00U)
#define DCM_DSP_DIDMNG_CLEAR_ALL_SESCHG         ((uint8)0x01U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

#if ( ( DCM_M_USE_VINDATAIDENTIFIER == STD_ON ) || ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
FUNC( Dcm_Main_ReturnCheckType, DCM_CODE ) Dcm_Dsp_DidMng_ChkDid
(
    const uint16 u2DID,
    const uint8 u1KindOfTable,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) ptDidIndex,
    P2VAR(uint8, AUTOMATIC,DCM_APPL_DATA) ptControlReadWriteSupport
);
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_ON || DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */
#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ChkDidInfo
(
    const uint16 u2DidIndex,
    const uint8 u1KindOfTable,
    const uint8 u1KindOfCheck,
    const uint8 u1CheckElement
);
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */
#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallAvailableFnc
(
    const uint16 u2RangeIndex,
    const uint16 u2DID,
    const Dcm_OpStatusType u1OpStatus,
    P2VAR(Dcm_DidSupportedType, AUTOMATIC, DCM_APPL_DATA) ptSupported
);
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON */
#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallDataLengthFnc
(
    const uint16 u2RangeIndex,
    const uint16 u2DID,
    const Dcm_OpStatusType u1OpStatus,
    P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA)ptDataLength
);
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON */
#if ( ( DCM_PERIODIC_SEND_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_GetDynDidDataLen
(
    const uint16 u2DidIndex,
    P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA)ptDataLength
);
#endif /* DCM_PERIODIC_SEND_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON */
#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_M_USE_VINDATAIDENTIFIER == STD_ON ) )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallReadDidFnc
(
    const uint16 u2RangeIndex,
    const uint16 u2DID,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptData,
    const Dcm_OpStatusType u1OpStatus,
    const uint32 u4DataBufferLength,
    P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) ptDataLength,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode
);
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_M_USE_VINDATAIDENTIFIER == STD_ON */
#if ( DCM_SUPPORT_SID22 == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallReadDynDidFnc
(
    const uint16 u2DidIndex,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptData,
    const Dcm_OpStatusType u1OpStatus,
    const uint32 u4DataBufferLength,
    P2VAR (uint32, AUTOMATIC, DCM_APPL_DATA) ptDataLength,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) ptLoopCntMax
);
#endif /* DCM_SUPPORT_SID22 == STD_ON */
#if ( DCM_PERIODIC_DDDID_USE == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallReadDynDidFncForPeriodic
(
    const uint16 u2DidIndex,
    const Dcm_OpStatusType u1OpStatus,
    const uint32 u4DataBufferLength,
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA ) ptData,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptDataLength
);
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON */
#if ( DCM_SUPPORT_SID2E == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallWriteDidFnc
(
    const uint16 u2RangeIndex,
    const uint16 u2DID,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptData,
    const Dcm_OpStatusType u1OpStatus,
    const uint16 u2DataLength,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
);
#endif /* DCM_SUPPORT_SID2E == STD_ON */
#if ( DCM_SUPPORT_SID2F == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ChkIOCP
(
    const uint16 u2DidIndex,
    const uint8 u1IOCP
);
#endif /* DCM_SUPPORT_SID2F == STD_ON */
#if ( DCM_SUPPORT_SID2F == STD_ON )
#if ( DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_GetCtrlParamLen
(
    const uint16 u2DidIndex,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) ptControlStateLen,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptNumOfData
);
#endif /* DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON */
#if ( DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_GetCtrlParamLenExternal
(
    const uint16 u2DidIndex,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) ptControlStateLen,
    P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) ptControlMaskLen
);
#endif /* DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON */
#endif /* DCM_SUPPORT_SID2F == STD_ON */
#if ( DCM_SUPPORT_SID2F == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ChkCtrlParam
(
    const uint16 u2DidIndex,
    P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) ptControlStateInfo,
    P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) ptControlMaskInfo
);
#endif /* DCM_SUPPORT_SID2F == STD_ON */
#if ( DCM_SUPPORT_SID2F == STD_ON )
#if ( DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallIOCP00Fnc
(
    const uint16 u2DidIndex,
    const uint8 u1SignalIndex,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode
);
#endif /* DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON */
#if ( DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallIOCP00Fnc
(
    const uint16 u2DidIndex,
    const uint8 u1SignalIndex,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptControlMaskInfo,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode
);
#endif /* DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON */
#endif /* DCM_SUPPORT_SID2F == STD_ON */
#if ( DCM_SUPPORT_SID2F == STD_ON )
#if ( DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallIOCP01Fnc
(
    const uint16 u2DidIndex,
    const uint8 u1SignalIndex,
    const Dcm_OpStatusType u1OpStatus,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode
);
#endif /* DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON */
#if ( DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallIOCP01Fnc
(
    const uint16 u2DidIndex,
    const uint8 u1SignalIndex,
    const Dcm_OpStatusType u1OpStatus,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptControlMaskInfo,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode
);
#endif /* DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON */
#endif /* DCM_SUPPORT_SID2F == STD_ON */
#if ( DCM_SUPPORT_SID2F == STD_ON )
#if ( DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallIOCP02Fnc
(
    const uint16 u2DidIndex,
    const uint8 u1SignalIndex,
    const Dcm_OpStatusType u1OpStatus,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode
);
#endif /* DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON */
#if ( DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallIOCP02Fnc
(
    const uint16 u2DidIndex,
    const uint8 u1SignalIndex,
    const Dcm_OpStatusType u1OpStatus,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptControlMaskInfo,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode
);
#endif /* DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON */
#endif /* DCM_SUPPORT_SID2F == STD_ON */
#if ( DCM_SUPPORT_SID2F == STD_ON )
#if ( DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallIOCP03Fnc
(
    const uint16 u2DidIndex,
    const uint8 u1SignalIndex,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptControlStateInfo,
    const Dcm_OpStatusType u1OpStatus,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode
);
#endif /* DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON */
#if ( DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallIOCP03Fnc
(
    const uint16 u2DidIndex,
    const uint8 u1SignalIndex,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptControlStateInfo,
    const Dcm_OpStatusType u1OpStatus,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptControlMaskInfo,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode
);
#endif /* DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON */
#endif /* DCM_SUPPORT_SID2F == STD_ON */
#if ( DCM_SUPPORT_SID2F == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallReadFnc
(
    const uint16 u2DidIndex,
    const uint8 u1SignalIndex,
    const Dcm_OpStatusType u1OpStatus,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptData,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode
);
#endif /* DCM_SUPPORT_SID2F == STD_ON */
#if ( ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID23 == STD_ON ) || ( DCM_SUPPORT_SID3D == STD_ON ) )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ChkALFID
(
    const uint8 u1ALFId
);
#endif /* DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID23 == STD_ON || DCM_SUPPORT_SID3D == STD_ON */
#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID23 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) || ( DCM_SUPPORT_SID3D == STD_ON ) )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ChkMemAddress
(
    const uint8 u1ReadWrite,
    const uint32 u4MemAddress,
    const uint8 u1MemIdFlag,
    const uint8 u1MemId,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptMemoryIdIndex,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptMemoryRangeIndex
);
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID23 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON || DCM_SUPPORT_SID3D == STD_ON */
#if ( ( DCM_SUPPORT_SID23 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID3D == STD_ON ) )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ChkMemSize
(
    const uint8 u1ReadWrite,
    const uint8 u1MemoryIdIndex,
    const uint8 u1MemoryRangeIndex,
    const uint32 u4MemAddress,
    const uint32 u4MemSize
);
#endif /* DCM_SUPPORT_SID23 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID3D == STD_ON */
#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID23 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) || ( DCM_SUPPORT_SID3D == STD_ON ) )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ChkMemSes
(
    const uint8 u1ReadWrite,
    const uint8 u1MemoryIdIndex,
    const uint8 u1MemoryRangeIndex,
    const uint8 u1CurrentSessionLevel
);
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID23 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON || DCM_SUPPORT_SID3D == STD_ON */
#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID23 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) || ( DCM_SUPPORT_SID3D == STD_ON ) )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ChkMemSec
(
    const uint8 u1ReadWrite,
    const uint8 u1MemoryIdIndex,
    const uint8 u1MemoryRangeIndex,
    const uint8 u1CurrentSecurityLevel
);
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID23 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON || DCM_SUPPORT_SID3D == STD_ON */
#if ( DCM_SUPPORT_SID2C == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ChkDDDIDLimit
(
    const uint16 u2DidIndex,
    const uint32 u4NumOfSourceElement,
    const uint32 u4TotalSize
);
#endif /* DCM_SUPPORT_SID2C == STD_ON */
#if ( DCM_SUPPORT_SID2C == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ChkDDDIDLimitMemAddr
(
    const uint16 u2DidIndex,
    const uint32 u4NumOfSourceElement,
    const uint32 u4MemSizeTotal
);
#endif /* DCM_SUPPORT_SID2C == ON */
#if ( DCM_SUPPORT_SID2C == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_SetDDDID
(
    const uint8 u1KindOfSourceElement,
    P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) ptRequestMessage,
    const uint8 u1NumOfSourceElement
);
#endif /* DCM_SUPPORT_SID2C == ON */
#if ( DCM_SUPPORT_SID2C == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ClearDDDID
(
    const uint16 u2DDDid
);
#endif /* DCM_SUPPORT_SID2C == ON */
#if ( DCM_SUPPORT_SID2C == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ClearAllDDDID
(
    const uint8 u1KindOfClear
);
#endif /* DCM_SUPPORT_SID2C == ON */
#if ( DCM_SUPPORT_SID2C == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsp_DidMng_ClearNoSupDDDID
(
    const uint8 u1KindOfCheck,
    const uint8 u1CheckElement
);
#endif /* DCM_SUPPORT_SID2C == ON */
#if ( ( DCM_PERIODIC_SEND_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ChkDynamic
(
    const uint16 u2DDDid,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptNumOfSourceDid,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) ptDynamicIndex
);
#endif /* DCM_PERIODIC_SEND_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON */
#if ( ( DCM_PERIODIC_SEND_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ))
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallModeRuleFnc
(
    const uint16 u2DidIndex,
    const uint8 u1KindOfFnc,
    const uint16 u2DID,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode
);
#endif /* DCM_PERIODIC_SEND_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON */
#if ( ( DCM_PERIODIC_SEND_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ))
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_DynDidModeRuleFnc
(
    const uint16 u2DidIndex,
    const uint8 u1KindOfFnc,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode
);
#endif /* DCM_PERIODIC_SEND_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON */

FUNC( void, DCM_CODE ) Dcm_Dsp_DidMng_Init
(
    void
);


#if ( DCM_SUPPORT_SID2C == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ChkSDidSize
(
    const uint32 u4DidDataLength
);
#endif /* DCM_SUPPORT_SID2C == ON */

#if ( DCM_SUPPORT_SID2F == STD_ON )
#if ( DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_GetTopSigType
(
    const uint16 u2DidIndex,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptDataType
);
#endif /* DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON */
#endif /* DCM_SUPPORT_SID2F == STD_ON */
#if ( DCM_SUPPORT_SID2F == STD_ON )
#if ( DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_GetSigNum
(
    const uint16 u2DidIndex,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptSignalNum
);
#endif /* DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON */
#endif /* DCM_SUPPORT_SID2F == STD_ON */
#if ( DCM_SUPPORT_SID2F == STD_ON )
#if ( DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_GetAnySigPos
(
    const uint16 u2DidIndex,
    const uint8 u1SignalIndex,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) ptDataPos
);
#endif /* DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON */
#endif /* DCM_SUPPORT_SID2F == STD_ON */

#if ( DCM_SUPPORT_SID2C == STD_ON )
#if ( DCM_NVM_DDDID_USE == STD_ON )
FUNC( boolean, DCM_CODE ) Dcm_Dsp_DidMng_GetReadStorageCompleteFlag
(
    void
);
#endif /* DCM_NVM_DDDID_USE == STD_ON */
#endif /* DCM_SUPPORT_SID2C == STD_ON */

#if ( DCM_NVM_DDDID_USE == STD_ON )
FUNC( void, DCM_CODE) Dcm_Dsp_DidMng_SetDataStorage2Mirror
(
    const uint16 u2BlockIdx
);
#endif /* DCM_NVM_DDDID_USE == STD_ON */

#if ( DCM_NVM_DDDID_USE == STD_ON )
FUNC( void, DCM_CODE) Dcm_Dsp_DidMng_SetDataMirror2Storage
(
    const uint16 u2BlockIdx
);

#endif /* DCM_NVM_DDDID_USE == STD_ON */
#if ( DCM_NVM_DDDID_USE == STD_ON )
FUNC( void, DCM_CODE) Dcm_Dsp_DidMng_ReadConfirmation
(
    const uint16 u2BlockIdx,
    const uint8  u1Result
);
#endif /* DCM_NVM_DDDID_USE == STD_ON */
#if ( DCM_NVM_DDDID_USE == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsp_DidMng_Refresh
(
    void
);
#endif /* DCM_NVM_DDDID_USE == STD_ON */

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


#endif /* DSP_DIDMNG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-6-0         :2024-02-27                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

