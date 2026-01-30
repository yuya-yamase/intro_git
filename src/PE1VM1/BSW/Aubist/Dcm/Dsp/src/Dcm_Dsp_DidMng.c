/* Dcm_Dsp_DidMng_c(v5-10-0)                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_DidMng/CODE                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_DidMng.h>
#include <Dcm.h>
#include <Dcm/Dcm_Dsp_MemMng.h>
#include <Dcm/Dcm_Dsl_Ctrl.h>
#if ( DCM_NVM_DDDID_USE == STD_ON )
#include <Dcm/Dcm_Dsp_StorageMng.h>
#include <Dcm_NvM.h>
#endif /* DCM_NVM_DDDID_USE == STD_ON */

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSP_DIDMNG_RCTE ((uint8)0x00U)
#define DCM_DSP_DIDMNG_RTD  ((uint8)0x01U)
#define DCM_DSP_DIDMNG_FCS  ((uint8)0x02U)
#define DCM_DSP_DIDMNG_STA  ((uint8)0x03U)

#define DCM_DSP_DIDMNG_MASK_BYTESHIFT   ((uint8)3U)

#define DCM_DSP_DIDMNG_DIDSHIFT         ((uint8)0x08U)

#define DCM_DSP_DIDMNG_SRCELM_MSG_SIZ   ((uint8)0x04U)
#define DCM_DSP_DIDMNG_SOURCEDID_POS    ((uint8)0x02U)
#define DCM_DSP_DIDMNG_ALFID_POS        ((uint8)0x02U)
#define DCM_DSP_DIDMNG_MEMADR_POS       ((uint8)0x03U)
#define DCM_DSP_DIDMNG_ALFID_ADLEN_MASK ((uint8)0x0FU)
#define DCM_DSP_DIDMNG_ALFID_SHIFT4     ((uint8)4U)
#define DCM_DSP_DIDMNG_POSITION_POS     ((uint8)0x04U)
#define DCM_DSP_DIDMNG_SIZE_POS         ((uint8)0x05U)
#define DCM_DSP_DIDMNG_MEMID_NOT_SET    ((uint8)0x00U)
#define DCM_DSP_DIDMNG_MEMID_SET        ((uint8)0x01U)
#define DCM_DSP_DIDMNG_DID_F2           ((uint8)0xF2U)

#define DCM_DSP_DIDMNG_ALFID_MEMSIZE_MIN         ((uint8)0x1U)
#define DCM_DSP_DIDMNG_ALFID_MEMSIZE_MAX         ((uint8)0x4U)
#define DCM_DSP_DIDMNG_ALFID_ADRSIZE_MIN         ((uint8)0x1U)
#define DCM_DSP_DIDMNG_ALFID_ADRSIZE_MAX         ((uint8)0x5U)
#define DCM_DSP_DIDMNG_SIZE_1BYTE                ((uint8)0x1U)
#define DCM_DSP_DIDMNG_SHIFT8                    ((uint8)8U)

#if ( DCM_NVM_DDDID_USE == STD_ON )
#define DCM_DSP_DIDMNG_SET_DDDID        ((uint8)0x00U)
#define DCM_DSP_DIDMNG_SET_NOSE         ((uint8)0x01U)
#define DCM_DSP_DIDMNG_CLEAR            ((uint8)0x02U)
#define DCM_DSP_DIDMNG_CLEAR_ALL        ((uint8)0x03U)
#endif /* DCM_NVM_DDDID_USE == STD_ON */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>
#if ( DCM_NVM_DDDID_USE == STD_ON )
static FUNC( void, DCM_CODE ) Dcm_Dsp_DidMng_Storage_Init
(
    void
);
#endif /* DCM_NVM_DDDID_USE == STD_ON */

#if ( DCM_PERIODIC_DDDID_USE == STD_ON )
static FUNC( void, DCM_CODE ) Dcm_Dsp_DidMng_Periodic_Init
(
    void
);
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON */

#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ChkSDidInfo
(
    const uint16 u2DDDidIndex,
    const uint8 u1KindOfCheck,
    const uint8 u1CheckElement
);
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */

#if ( DCM_SUPPORT_SID22 == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallSDidRead
(
    const uint16 u2DDDidIndex,
    const uint8 u1NumOfSourceDid,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptData,
    const uint32 u4DataBufferLength,
    P2VAR (uint32, AUTOMATIC, DCM_APPL_DATA) ptDataLength,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) ptLoopCntMax
);
#endif /* DCM_SUPPORT_SID22 == STD_ON */
#if ( DCM_PERIODIC_DDDID_USE == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallSDidReadForPeriodic
(
    const uint16 u2DDDidIndex,
    const Dcm_OpStatusType u1OpStatus,
    const uint32 u4DataBufferLength,
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA) ptData,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA) ptDataLength
);
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON */
#if ( DCM_SUPPORT_SID22 == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ReadElemData
(
    P2CONST(Dcm_Dsp_SourceElementType, AUTOMATIC, DCM_APPL_DATA)    ptSourceTable,
    const Dcm_OpStatusType                                          u1OpStatus,
    const uint32                                                    u4DataBufferLength,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)                          ptData,
    P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA)                         ptDataLength,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA)   ptErrorCode
);
#endif /* DCM_SUPPORT_SID22 == STD_ON */
#if ( DCM_PERIODIC_DDDID_USE == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ReadElemDataForPeriodic
(
    P2CONST( Dcm_Dsp_SourceElementType, AUTOMATIC, DCM_APPL_DATA )  ptSourceTable,
    const Dcm_OpStatusType                                          u1OpStatus,
    const uint32                                                    u4DataBufferLength,
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA )                       ptData,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA )                       ptDataLength
);
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON */
#if ( DCM_SUPPORT_SID22 == STD_ON )
#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_OFF )
#if ( DCM_PAGEDBUFFER_SID23_ENABLED == STD_OFF )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallMemRead
(
    P2CONST(Dcm_Dsp_SourceElementType, AUTOMATIC, DCM_APPL_DATA)    ptSourceTable,
    const Dcm_OpStatusType                                          u1OpStatus,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)                          ptData,
    P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA)                         ptDataLength,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA)   ptErrorCode
);
#endif /* DCM_PAGEDBUFFER_SID23_ENABLED == STD_OFF */
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_OFF */
#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON )
#if ( DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallMemRead
(
    P2CONST(Dcm_Dsp_SourceElementType, AUTOMATIC, DCM_APPL_DATA)    ptSourceTable,
    const Dcm_OpStatusType                                          u1OpStatus,
    const uint32                                                    u4DataBufferLength,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)                          ptData,
    P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA)                         ptDataLength,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA)   ptErrorCode
);
#endif /* DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON */
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON */
#endif /* DCM_SUPPORT_SID22 == STD_ON */
#if ( DCM_PERIODIC_DDDID_USE == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallMemReadForPeriodic
(
    P2CONST( Dcm_Dsp_SourceElementType, AUTOMATIC, DCM_APPL_DATA )  ptSourceTable,
    const Dcm_OpStatusType                                          u1OpStatus,
    P2CONST( uint32, AUTOMATIC, DCM_APPL_DATA )                     ptDataLength,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )                        ptData
);
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON */
#if ( DCM_SUPPORT_SID22 == STD_ON )
#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON )
#if ( DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON )
static FUNC( uint32, DCM_CODE ) Dcm_Dsp_DidMng_CalcPBReadMemLen
(
    P2CONST(Dcm_Dsp_SourceElementType, AUTOMATIC, DCM_APPL_DATA)    ptSourceTable,
    const uint32                                                    u4DataBufferLength,
    const uint32                                                    u4StoredDataLength
);
#endif /* DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON */
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON */
#endif /* DCM_SUPPORT_SID22 == STD_ON */
#if ( DCM_SUPPORT_SID22 == STD_ON )
#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON )
#if ( DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_SetRemainSourceDidData
(
    const uint32 u4DataBufferLength,
    P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) ptDataLength,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptData
);
#endif /* DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON */
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON */
#endif /* DCM_SUPPORT_SID22 == STD_ON */
#if ( DCM_SUPPORT_SID22 == STD_ON )
#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON )
#if ( DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_SetSourceDidData
(
    const uint8 u1cnt,
    P2CONST(Dcm_Dsp_SourceElementType, AUTOMATIC, DCM_APPL_DATA) ptSourceTable,
    const uint32 u4DataBufferLength,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptData,
    P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) ptDataLength
);
#endif /* DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON */
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON */
#endif /* DCM_SUPPORT_SID22 == STD_ON */

#if ( DCM_SUPPORT_SID22 == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_InternalPending
(
    const uint8 u1cnt,
    const uint8 u1NumOfSourceDid,
    const uint16 u2LoopCntMax,
    P2VAR(boolean, AUTOMATIC, DCM_APPL_DATA) ptBreakFlag
);
#endif /* DCM_SUPPORT_SID22 == STD_ON */

#if ( DCM_SUPPORT_SID2C == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_SetSourceElement
(
    const uint16 u2DDDidIndex,
    P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) ptRequestMessage,
    const uint8 u1NumOfSourceElement
);
#endif /* DCM_SUPPORT_SID2C == STD_ON */

#if ( DCM_SUPPORT_SID2C == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_SetMemAddrSourceElement
(
    const uint16 u2DDDidIndex,
    P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) ptRequestMessage,
    const uint8 u1NumOfSourceElement
);
#endif /* DCM_SUPPORT_SID2C == STD_ON */
#if ( DCM_SUPPORT_SID2C == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CalcMemAddr
(
    P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) ptRequestMessage,
    const uint8   u1SourceDidSetCnt,
    const uint8   u1MemAddrLen,
    const uint8   u1MemSizeLen,
    const boolean bCheckUseAsMemoryId,
    const uint16  u2DDDidIndex,
    const uint8   u1NumOfSourceDid
);
#endif /* DCM_SUPPORT_SID2C == STD_ON */
#if ( ( DCM_PERIODIC_SEND_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallSDidModeRule
(
    const uint16 u2DDDidIndex,
    const uint8 u1KindOfFnc,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode
);
#endif /* DCM_PERIODIC_SEND_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON*/

#if ( ( DCM_M_USE_VINDATAIDENTIFIER == STD_ON ) || ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
static FUNC( void, DCM_CODE ) Dcm_Dsp_DidMng_SearchDidRange
(
    const uint16 u2DID,
    P2VAR(uint16, AUTOMATIC,DCM_APPL_DATA) ptTopIndex,
    const uint16 u2EndIndex,
    P2VAR(boolean, AUTOMATIC,DCM_APPL_DATA) ptCheckFlag
);
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_ON || DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */

#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
static FUNC( Std_ReturnType, DCM_CODE) Dcm_Dsp_DidMng_InternalDidInfo
(
    const uint8 u1KindOfCheck,
    const uint8 u1CheckElement,
    P2CONST(AB_83_ConstV Dcm_Dsp_DidInfoType, AUTOMATIC, DCM_APPL_CONST) ptTargetInfoTbl
);
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */

#if ( ( DCM_PERIODIC_SEND_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ))
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_InternalModeRule
(
    const uint8 u1KindOfFnc,
    P2CONST(AB_83_ConstV Dcm_Dsp_DidInfoType, AUTOMATIC, DCM_APPL_CONST) ptTargetInfoTbl,
    const uint16 u2DID,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode
);
#endif /* DCM_PERIODIC_SEND_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON */

#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_GetDynamicIndex
(
    const uint16 u2DDDid,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) ptDynamicIndex
);
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON */

#if ( ( DCM_M_USE_VINDATAIDENTIFIER == STD_ON ) || ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
static FUNC( Dcm_Main_ReturnCheckType, DCM_CODE ) Dcm_Dsp_DidMng_BinarySearchDidRange
(
    const uint16 u2DID,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) ptDidIndex,
    P2VAR(uint8, AUTOMATIC,DCM_APPL_DATA) ptControlReadWriteSupport
);
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_ON || DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */

#if ( ( DCM_M_USE_VINDATAIDENTIFIER == STD_ON ) || ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
static FUNC( Dcm_Main_ReturnCheckType, DCM_CODE ) Dcm_Dsp_DidMng_BinarySearchDid
(
    const uint16 u2DID,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) ptDidIndex,
    P2VAR(uint8, AUTOMATIC,DCM_APPL_DATA) ptControlReadWriteSupport
);
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_ON || DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */
#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_InternalAddrInfo
(
    const uint8         u1KindOfCheck,
    const uint8         u1CheckElement,
    const uint8         u1MemId,
    const uint32        u4MemAddr
);
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */

#if ( DCM_SUPPORT_SID2C == STD_ON )
#if ( DCM_NVM_DDDID_USE == STD_ON )
static FUNC( void, DCM_CODE ) Dcm_Dsp_DidMng_WriteStorage
(
    const uint8  u1Kind,
    const uint16 u2DDDidIndex,
    const uint8  u1SourceDidIndex
);
#endif /* DCM_NVM_DDDID_USE == STD_ON */
#endif /* DCM_SUPPORT_SID2C == STD_ON */
#if ( DCM_SUPPORT_SID2C == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ChkDDDIDDataLen
(
    const uint32 u4TotalSize,
    const uint32 u4CurrentSize,
    const uint16 u2DDDid
);
#endif /* DCM_SUPPORT_SID2C == STD_ON */
#if ( DCM_NVM_DDDID_USE == STD_ON )
static FUNC( void, DCM_CODE ) Dcm_Dsp_DidMng_InitSourceElementId
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
#if ( DCM_SUPPORT_SID22 == STD_ON )
static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Dsp_DidMng_u1LoopCnt;
static VAR( boolean, DCM_VAR_NO_INIT ) Dcm_Dsp_DidMng_bUserNotifyFlag;
static VAR( boolean, DCM_VAR_NO_INIT ) Dcm_Dsp_DidMng_bUserRcrrpFlag;
#endif /* DCM_SUPPORT_SID22 == STD_ON */
#if ( DCM_NVM_DDDID_USE == STD_ON )
static VAR( boolean, DCM_VAR_NO_INIT ) Dcm_Dsp_DidMng_bReadStorageCompleteFlag;
#endif /* DCM_NVM_DDDID_USE == STD_ON */
#if ( DCM_SUPPORT_SID22 == STD_ON )
static VAR( uint8 , DCM_VAR_NO_INIT ) Dcm_Dsp_DidMng_u1ReadBuffer[ DCM_P_SOURCE_DID_MAX_DATA_SIZE ];    /* MISRA DEVIATION */
#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON )
#if ( DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON )
static VAR( boolean, DCM_VAR_NO_INIT ) Dcm_Dsp_DidMng_bRemainData;
static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Dsp_DidMng_u1RemainIndex;
static VAR( boolean, DCM_VAR_NO_INIT ) Dcm_Dsp_DidMng_bSetData;
static VAR( uint32, DCM_VAR_NO_INIT ) Dcm_Dsp_DidMng_u4UnsetIndex;
static VAR( Dcm_Dsp_SourceElementType, DCM_VAR_NO_INIT ) Dcm_Dsp_DidMng_stSourceTable;
static VAR( uint32, DCM_VAR_NO_INIT ) Dcm_Dsp_DidMng_u4StoredDataLen;
#endif /* DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON */
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON */
#endif /* DCM_SUPPORT_SID22 == STD_ON */
#if ( DCM_PERIODIC_DDDID_USE == STD_ON )
static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Dsp_DidMng_u1LoopCntForPeriodic;
static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Dsp_DidMng_u1NumOfSrcDidForPeriodic;
static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Dsp_DidMng_u1ReadPdidBuffer[ DCM_P_SOURCE_DID_MAX_DATA_SIZE ];    /* MISRA DEVIATION */
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON */

#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST
#include <Dcm_MemMap.h>

#define DCM_STOP_SEC_CONST
#include <Dcm_MemMap.h>
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

#if ( ( DCM_M_USE_VINDATAIDENTIFIER == STD_ON ) || ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_ChkDid                                    */
/* Description   | Find Did                                                 */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DID : Reqest Data Id                              */
/*               | [in] u1KindOfTable : Kind of the Did Table               */
/*               | [out] ptDidIndex : Index of the Did Table                */
/*               | [out] ptControlReadWriteSupport : C/R/W Support Info     */
/*               |                                                          */
/* Return Value  | Dcm_Main_ReturnCheckType                                 */
/*               |        DCM_MAIN_E_CHECK_OK : DID is valid                */
/*               |        DCM_MAIN_E_CHECK_NOT_OK : DID is invalid          */
/*               |        DCM_MAIN_E_INVALID_CONFIG : Incorrect user c-     */
/*               |        onfiguration                                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Dcm_Main_ReturnCheckType, DCM_CODE ) Dcm_Dsp_DidMng_ChkDid
(
    const uint16 u2DID,
    const uint8 u1KindOfTable,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) ptDidIndex,
    P2VAR(uint8, AUTOMATIC,DCM_APPL_DATA) ptControlReadWriteSupport
)
{
    Dcm_Main_ReturnCheckType u1_RetVal;

    *ptControlReadWriteSupport = (uint8)0x00U;

    if( u1KindOfTable == DCM_DSP_DIDMNG_DID_RANGE )
    {
        u1_RetVal = Dcm_Dsp_DidMng_BinarySearchDidRange( u2DID, ptDidIndex, ptControlReadWriteSupport );
    }
    else
    {
        u1_RetVal = Dcm_Dsp_DidMng_BinarySearchDid( u2DID, ptDidIndex, ptControlReadWriteSupport );
    }
    return u1_RetVal;
}
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_ON || DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */


#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_ChkDidInfo                                */
/* Description   | Security/Session Check of the Did                        */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DidIndex :Index of either of the following Tables */
/*               |                   DcmDspDidRangeTbl[], DcmDspDidTbl[],   */
/*               |                   DcmDspDDDidTbl[]                       */
/*               | [in] u1KindOfTable : Kind of the Did Table               */
/*               | [in] u1KindOfCheck : Kind of Check                       */
/*               | [in] u1CheckElement : SecLevel/SesLevel                  */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Check OK                                   */
/*               |        E_NOT_OK : Check not OK                           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ChkDidInfo
(
    const uint16 u2DidIndex,
    const uint8 u1KindOfTable,
    const uint8 u1KindOfCheck,
    const uint8 u1CheckElement
)
{
    P2CONST( AB_83_ConstV Dcm_Dsp_DidInfoType, AUTOMATIC, DCM_APPL_CONST ) pt_InfoRef;
    Std_ReturnType u1_RetVal;
    Std_ReturnType u1_RetDid;
    Std_ReturnType u1_RetChkDDDid;
    uint16 u2ReqDDDid;
    uint16 u2TargetIndex;
    uint16 u2_DidT;
    uint16 u2_DidrangeT;
    uint16 u2_DddidT;
    uint8 u1RWSupport;

    u1_RetVal = E_NOT_OK;
    u2_DidT = Dcm_P_u2Did_T;
    u2_DidrangeT = Dcm_P_u2Didrange_T;
    u2_DddidT = Dcm_P_u2Dddid_T;

    if( u1KindOfTable == DCM_DSP_DIDMNG_DID )
    {
        if( u2DidIndex < u2_DidT )
        {
            pt_InfoRef = DcmDspDidTbl[u2DidIndex].ptInfoRef;
            u1_RetVal = Dcm_Dsp_DidMng_InternalDidInfo( u1KindOfCheck, u1CheckElement, pt_InfoRef );
        }
    }
    else if( u1KindOfTable == DCM_DSP_DIDMNG_DID_RANGE )
    {
        if( u2DidIndex < u2_DidrangeT )
        {
            pt_InfoRef = DcmDspDidRangeTbl[u2DidIndex].ptInfoRef;
            u1_RetVal = Dcm_Dsp_DidMng_InternalDidInfo( u1KindOfCheck, u1CheckElement, pt_InfoRef );
        }
    }
    else
    {
        /* if( u1KindOfTable == DCM_DSP_DIDMNG_DID_DYNAMIC ) */
        if( u2DidIndex < u2_DddidT )
        {
            u2ReqDDDid = DcmDspDDDidTbl[ u2DidIndex ].u2DDDid;
            u1_RetDid = Dcm_Dsp_DidMng_ChkDid( u2ReqDDDid, DCM_DSP_DIDMNG_DID, &u2TargetIndex, &u1RWSupport );

            if( u1_RetDid == DCM_MAIN_E_CHECK_OK )
            {
                pt_InfoRef = DcmDspDidTbl[ u2TargetIndex ].ptInfoRef;
                u1_RetChkDDDid = Dcm_Dsp_DidMng_InternalDidInfo( u1KindOfCheck, u1CheckElement, pt_InfoRef );

                if( u1_RetChkDDDid == (Std_ReturnType)E_OK )
                {
                    u1_RetVal = Dcm_Dsp_DidMng_ChkSDidInfo( u2DidIndex, u1KindOfCheck, u1CheckElement );
                }
                /* In the case of else, E_NOT_OK has been already set by u1_RetVal. */
            }
            /* In the case of else, E_NOT_OK has been already set by u1_RetVal. */
        }
        /* In the case of else, E_NOT_OK has been already set by u1_RetVal. */
    }
    return u1_RetVal;
}
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */

#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_CallAvailableFnc                          */
/* Description   | Call the IsDidAvailableFnc                               */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2RangeIndex : Index of DcmDspDidRangeTbl[]         */
/*               | [in] u2DID : Reqest Data Id                              */
/*               | [in] u1OpStatus : Operation state                        */
/*               | [out] ptSupported : Support Infomation of the Data Id    */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Process complete                           */
/*               |        DCM_E_PENDING : Process pending                   */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallAvailableFnc
(
    const uint16 u2RangeIndex,
    const uint16 u2DID,
    const Dcm_OpStatusType u1OpStatus,
    P2VAR(Dcm_DidSupportedType, AUTOMATIC, DCM_APPL_DATA) ptSupported
)
{
    Std_ReturnType u1_RetVal;
    uint16         u2_DidrangeT;

    u1_RetVal = E_OK;
    u2_DidrangeT = Dcm_P_u2Didrange_T;
    *ptSupported = DCM_DID_NOT_SUPPORTED;

    if( u2RangeIndex < u2_DidrangeT )
    {
        if( DcmDspDidRangeTbl[u2RangeIndex].bHasGaps == (boolean)TRUE )
        {
            if( DcmDspDidRangeTbl[u2RangeIndex].ptIsDidAvailableFnc != NULL_PTR )
            {
#ifndef JGXSTACK
                u1_RetVal = DcmDspDidRangeTbl[u2RangeIndex].ptIsDidAvailableFnc( u2DID, u1OpStatus, ptSupported );
#else  /* JGXSTACK */
                /* user-defined */
#endif /* JGXSTACK */
            }
        }
        else
        {
            *ptSupported = DCM_DID_SUPPORTED;
        }
    }
    return u1_RetVal;
}
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON */

#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_CallDataLengthFnc                         */
/* Description   | Call the ReadDataLengthFnc                               */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2RangeIndex : Index of DcmDspDidRangeTbl[]         */
/*               | [in] u2DID : Reqest Data Id                              */
/*               | [in] u1OpStatus : Operation state                        */
/*               | [out] ptDataLength : Length of the R/W Data              */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Process complete                           */
/*               |        E_NOT_OK : Process abnormal termination           */
/*               |        DCM_E_PENDING : Process pending                   */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallDataLengthFnc
(
    const uint16 u2RangeIndex,
    const uint16 u2DID,
    const Dcm_OpStatusType u1OpStatus,
    P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA)ptDataLength
)
{
    Std_ReturnType u1_RetVal;
    uint16         u2_DidrangeT;

    u1_RetVal = E_NOT_OK;
    u2_DidrangeT = Dcm_P_u2Didrange_T;
    *ptDataLength = (uint32)0U;

    if( u2RangeIndex < u2_DidrangeT )
    {
#ifndef JGXSTACK
        u1_RetVal = DcmDspDidRangeTbl[u2RangeIndex].ptReadDataLengthFnc( u2DID, u1OpStatus, ptDataLength );
#else  /* JGXSTACK */
        /* user-defined */
#endif /* JGXSTACK */
    }

    return u1_RetVal;
}
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON */


#if ( ( DCM_PERIODIC_SEND_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_GetDynDidDataLen                          */
/* Description   | Get DDDid Length                                         */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DidIndex : Index of DcmDspDDDidTbl[]              */
/*               | [out] ptDataLength : Data Length                         */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Process complete                           */
/*               |        E_NOT_OK : Process abnormal termination           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_GetDynDidDataLen
(
    const uint16 u2DidIndex,
    P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA)ptDataLength
)
{
    Std_ReturnType u1_RetVal;
    Std_ReturnType u1_RetGetSourceDID;
    Std_ReturnType u1_RetGetNumOfSrcDid;
    uint8 u1NumOfSourceDid;
    uint8 u1_cnt;
    Dcm_Dsp_SourceElementType stSourceTable;

    u1_RetVal = E_OK;
    *ptDataLength = (uint32)0U;

    u1_RetGetNumOfSrcDid = Dcm_Dsp_DidMng_GetNumOfSrcDid( u2DidIndex, &u1NumOfSourceDid );
    if( u1_RetGetNumOfSrcDid == (Std_ReturnType)E_OK )
    {
        if( u1NumOfSourceDid > (uint8)0U )
        {
            for( u1_cnt = (uint8)0U; u1_cnt < u1NumOfSourceDid; u1_cnt++ )
            {
                u1_RetGetSourceDID = Dcm_Dsp_DidMng_GetSourceDID( u2DidIndex, u1_cnt, &stSourceTable );
                if( u1_RetGetSourceDID != (Std_ReturnType)E_OK )
                {
                    u1_RetVal = E_NOT_OK;
                    break;
                }
                if( stSourceTable.u1SourceElementId == DCM_DSP_DIDMNG_SOURCEELEMENTID_DID )
                {
                    *ptDataLength += stSourceTable.u1Size;  /* no wrap around */
                }
                else if( stSourceTable.u1SourceElementId == DCM_DSP_DIDMNG_SOURCEELEMENTID_MEMADDR )
                {
                    *ptDataLength += stSourceTable.u4MemSize;   /* no wrap around */
                }
                else
                {
                    /* no process */
                }
            }
        }
        else
        {
            u1_RetVal = E_NOT_OK;
        }
    }
    else
    {
        u1_RetVal = E_NOT_OK;
    }
    return u1_RetVal;
}
#endif /* DCM_PERIODIC_SEND_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON */


#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_M_USE_VINDATAIDENTIFIER == STD_ON ) )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_CallReadDidFnc                            */
/* Description   | Call the ReadDidFnc                                      */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2RangeIndex : Index of DcmDspDidRangeTbl[]         */
/*               | [in] u2DID : Reqest Data Id                              */
/*               | [out] ptData : Read Data                                 */
/*               | [in] u1OpStatus : Operation state                        */
/*               | [out] ptDataLength : Read Data Length                    */
/*               | [out] ptErrorCode : Negative Response Code               */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Process complete                           */
/*               |        E_NOT_OK : Process abnormal termination           */
/*               |        DCM_E_PENDING : Process pending                   */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallReadDidFnc
(
    const uint16 u2RangeIndex,
    const uint16 u2DID,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptData,
    const Dcm_OpStatusType u1OpStatus,
    const uint32 u4DataBufferLength,
    P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) ptDataLength,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode
)
{
    Std_ReturnType u1_RetVal;
    uint16         u2_DidrangeT;

    u1_RetVal = E_NOT_OK;
    u2_DidrangeT = Dcm_P_u2Didrange_T;
    *ptDataLength = (uint32)0U;
    *ptErrorCode = (uint8)0x00U;

    if( u2RangeIndex < u2_DidrangeT )
    {
        if( DcmDspDidRangeTbl[u2RangeIndex].ptReadDidFnc != NULL_PTR )
        {
#ifndef JGXSTACK
            u1_RetVal = DcmDspDidRangeTbl[u2RangeIndex].ptReadDidFnc( u2DID, ptData, u1OpStatus, u4DataBufferLength, ptDataLength, ptErrorCode );
#else  /* JGXSTACK */
            /* user-defined */
#endif /* JGXSTACK */
        }
    }

    return u1_RetVal;
}
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_M_USE_VINDATAIDENTIFIER == STD_ON */


#if ( DCM_SUPPORT_SID22 == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_CallReadDynDidFnc                         */
/* Description   | Call the ReadDidFnc                                      */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DidIndex : Index of DcmDspDDDidTbl[]              */
/*               | [in] ptData : Start pointer of read data                 */
/*               | [in] u1OpStatus : Operation state                        */
/*               | [out] ptDataLength : Read Data Length                    */
/*               | [out] ptErrorCode : Negative Response Code               */
/*               | [in/out] ptLoopCntMax : Maximum number of read operation */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Process complete                           */
/*               |        E_NOT_OK : Process abnormal termination           */
/*               |        DCM_E_PENDING : Process pending                   */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON )
#if ( DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallReadDynDidFnc
(
    const uint16 u2DidIndex,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptData,
    const Dcm_OpStatusType u1OpStatus,
    const uint32 u4DataBufferLength,
    P2VAR (uint32, AUTOMATIC, DCM_APPL_DATA) ptDataLength,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) ptLoopCntMax
)
{
    Std_ReturnType u1_RetVal;
    Std_ReturnType u1_RetReadFnc;
    Std_ReturnType u1_RetDidRange;
    Std_ReturnType u1_RetGetSourceDID;
    Std_ReturnType u1_RetGetNumOfSrcDid;
    Dcm_NegativeResponseCodeType u1LocalErrorCode;
    uint8 u1NumOfSourceDid;
    uint8 u1RWSupport;
    Dcm_Dsp_SourceElementType stSourceTable;
    uint16 u2TargetIndex;
    uint32 u4_DataBufferLength;
    uint32 u4_DataLength;

    u1_RetVal = E_NOT_OK;
    *ptErrorCode = (uint8)0U;
    u1LocalErrorCode = (uint8)0U;
    *ptDataLength       = (uint32)0U;
    u4_DataBufferLength = (uint32)0U;
    u4_DataLength       = (uint32)0U;

    if( u1OpStatus != DCM_CANCEL )
    {
        u1_RetGetNumOfSrcDid = Dcm_Dsp_DidMng_GetNumOfSrcDid( u2DidIndex, &u1NumOfSourceDid );
        if( u1_RetGetNumOfSrcDid == (Std_ReturnType)E_OK )
        {
            if( u1NumOfSourceDid > (uint8)0U )
            {
                if( u1OpStatus == DCM_INITIAL )
                {
                    /* Temporary RAM Data Clear at DDDID First Read */
                    Dcm_Dsp_DidMng_u1LoopCnt                    = (uint8)0U;
                    Dcm_Dsp_DidMng_bUserNotifyFlag              = (boolean)FALSE;
                    Dcm_Dsp_DidMng_bUserRcrrpFlag               = (boolean)FALSE;
                    Dcm_Dsp_DidMng_bRemainData                  = (boolean)FALSE;
                    Dcm_Dsp_DidMng_u1RemainIndex                = 0U;
                    Dcm_Dsp_DidMng_bSetData                     = (boolean)FALSE;
                    Dcm_Dsp_DidMng_u4StoredDataLen              = 0U;
                    Dcm_Dsp_DidMng_u4UnsetIndex                 = 0U;
                    Dcm_Dsp_DidMng_stSourceTable.u4MemAddr      = 0U;
                    Dcm_Dsp_DidMng_stSourceTable.u4MemSize      = 0U;
                    Dcm_Dsp_DidMng_stSourceTable.u2SourceDid    = 0U;
                    Dcm_Dsp_DidMng_stSourceTable.u1Position     = 0U;
                    Dcm_Dsp_DidMng_stSourceTable.u1Size         = 0U;
                    Dcm_Dsp_DidMng_stSourceTable.u1MemId        = 0U;
                    Dcm_Dsp_DidMng_stSourceTable.u1SourceElementId = DCM_DSP_DIDMNG_SOURCEELEMENTID_INVALID;
                }
                u1_RetVal = Dcm_Dsp_DidMng_CallSDidRead( u2DidIndex, u1NumOfSourceDid, ptData, u4DataBufferLength, ptDataLength, ptErrorCode, ptLoopCntMax );

                if( u1_RetVal == (Std_ReturnType)DCM_E_PENDING )
                {
                    /* no process */
                }
                else if( u1_RetVal == (Std_ReturnType)DCM_E_FORCE_RCRRP )
                {
                    /* no process */
                }
                else
                {
                    Dcm_Dsp_DidMng_u1LoopCnt = (uint8)0U;
                }
            }
            else
            {
                Dcm_Dsp_DidMng_u1LoopCnt = (uint8)0U;
                u1_RetVal = E_NOT_OK;
            }
        }
        else
        {
            Dcm_Dsp_DidMng_u1LoopCnt = (uint8)0U;
        }
    }
    else
    {
        if( Dcm_Dsp_DidMng_bUserNotifyFlag == (boolean)TRUE )
        {
            u1_RetGetSourceDID = Dcm_Dsp_DidMng_GetSourceDID( u2DidIndex, Dcm_Dsp_DidMng_u1LoopCnt, &stSourceTable );
            if( u1_RetGetSourceDID == (Std_ReturnType)E_OK )
            {
                if( stSourceTable.u1SourceElementId == DCM_DSP_DIDMNG_SOURCEELEMENTID_DID )
                {
                    u1_RetDidRange = Dcm_Dsp_DidMng_ChkDid( stSourceTable.u2SourceDid, DCM_DSP_DIDMNG_DID_RANGE, &u2TargetIndex, &u1RWSupport );

                    if( u1_RetDidRange == DCM_MAIN_E_CHECK_OK )
                    {
                        if( DcmDspDidRangeTbl[ u2TargetIndex ].ptReadDidFnc != NULL_PTR )
                        {
#ifndef JGXSTACK
                            u1_RetReadFnc = DcmDspDidRangeTbl[ u2TargetIndex ].ptReadDidFnc( stSourceTable.u2SourceDid, ptData, u1OpStatus, u4_DataBufferLength, &u4_DataLength, &u1LocalErrorCode );
#else  /* JGXSTACK */
                            u1_RetReadFnc = E_OK;
                            /* user-defined */
#endif /* JGXSTACK */
                            u1_RetVal = u1_RetReadFnc;
                        }
                    }
                }
                else if( stSourceTable.u1SourceElementId == DCM_DSP_DIDMNG_SOURCEELEMENTID_MEMADDR )
                {
                    (void)Dcm_Dsp_DidMng_CallMemRead( &stSourceTable, DCM_CANCEL, u4_DataBufferLength, ptData, ptDataLength, &u1LocalErrorCode );
                }
                else
                {
                    /* no process */
                }
            }
            Dcm_Dsp_DidMng_bUserNotifyFlag = (boolean)FALSE;
        }

        /* Temporary RAM Data Clear at DDDID Read Process End */
        Dcm_Dsp_DidMng_u1LoopCnt                    = (uint8)0U;
        Dcm_Dsp_DidMng_bUserRcrrpFlag               = (boolean)FALSE;
        Dcm_Dsp_DidMng_bRemainData                  = (boolean)FALSE;
        Dcm_Dsp_DidMng_u1RemainIndex                = 0U;
        Dcm_Dsp_DidMng_bSetData                     = (boolean)FALSE;
        Dcm_Dsp_DidMng_u4UnsetIndex                 = 0U;
        Dcm_Dsp_DidMng_u4StoredDataLen              = 0U;
        Dcm_Dsp_DidMng_stSourceTable.u4MemAddr      = 0U;
        Dcm_Dsp_DidMng_stSourceTable.u4MemSize      = 0U;
        Dcm_Dsp_DidMng_stSourceTable.u2SourceDid    = 0U;
        Dcm_Dsp_DidMng_stSourceTable.u1Position     = 0U;
        Dcm_Dsp_DidMng_stSourceTable.u1Size         = 0U;
        Dcm_Dsp_DidMng_stSourceTable.u1MemId        = 0U;
        Dcm_Dsp_DidMng_stSourceTable.u1SourceElementId = DCM_DSP_DIDMNG_SOURCEELEMENTID_INVALID;
    }

    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON */
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON */
#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_OFF )
#if ( DCM_PAGEDBUFFER_SID23_ENABLED == STD_OFF )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallReadDynDidFnc
(
    const uint16 u2DidIndex,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptData,
    const Dcm_OpStatusType u1OpStatus,
    const uint32 u4DataBufferLength,
    P2VAR (uint32, AUTOMATIC, DCM_APPL_DATA) ptDataLength,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) ptLoopCntMax
)
{
    Std_ReturnType u1_RetVal;
    Std_ReturnType u1_RetReadFnc;
    Std_ReturnType u1_RetDidRange;
    Std_ReturnType u1_RetGetSourceDID;
    Std_ReturnType u1_RetGetNumOfSrcDid;
    Dcm_NegativeResponseCodeType u1LocalErrorCode;
    uint8 u1NumOfSourceDid;
    uint8 u1RWSupport;
    Dcm_Dsp_SourceElementType stSourceTable;
    uint16 u2TargetIndex;
    uint32 u4_DataBufferLength;
    uint32 u4_DataLength;

    u1_RetVal = E_NOT_OK;
    *ptErrorCode = (uint8)0U;
    u1LocalErrorCode = (uint8)0U;
    *ptDataLength       = (uint32)0U;
    u4_DataBufferLength = (uint32)0U;
    u4_DataLength       = (uint32)0U;

    if( u1OpStatus != DCM_CANCEL )
    {
        u1_RetGetNumOfSrcDid = Dcm_Dsp_DidMng_GetNumOfSrcDid( u2DidIndex, &u1NumOfSourceDid );
        if( u1_RetGetNumOfSrcDid == (Std_ReturnType)E_OK )
        {
            if( u1NumOfSourceDid > (uint8)0U )
            {
                u1_RetVal = Dcm_Dsp_DidMng_CallSDidRead( u2DidIndex, u1NumOfSourceDid, ptData, u4DataBufferLength, ptDataLength, ptErrorCode, ptLoopCntMax );

                if( u1_RetVal == (Std_ReturnType)DCM_E_PENDING )
                {
                    /* no process */
                }
                else if( u1_RetVal == (Std_ReturnType)DCM_E_FORCE_RCRRP )
                {
                    /* no process */
                }
                else
                {
                    Dcm_Dsp_DidMng_u1LoopCnt = (uint8)0U;
                }
            }
            else
            {
                Dcm_Dsp_DidMng_u1LoopCnt = (uint8)0U;
                u1_RetVal = E_NOT_OK;
            }
        }
        else
        {
            Dcm_Dsp_DidMng_u1LoopCnt = (uint8)0U;
        }
    }
    else
    {
        u1_RetVal = E_OK;
        if( Dcm_Dsp_DidMng_bUserNotifyFlag == (boolean)TRUE )
        {
            u1_RetGetSourceDID = Dcm_Dsp_DidMng_GetSourceDID( u2DidIndex, Dcm_Dsp_DidMng_u1LoopCnt, &stSourceTable );
            if( u1_RetGetSourceDID == (Std_ReturnType)E_OK )
            {
                if( stSourceTable.u1SourceElementId == DCM_DSP_DIDMNG_SOURCEELEMENTID_DID )
                {
                    u1_RetDidRange = Dcm_Dsp_DidMng_ChkDid( stSourceTable.u2SourceDid, DCM_DSP_DIDMNG_DID_RANGE, &u2TargetIndex, &u1RWSupport );

                    if( u1_RetDidRange == DCM_MAIN_E_CHECK_OK )
                    {
                        if( DcmDspDidRangeTbl[ u2TargetIndex ].ptReadDidFnc != NULL_PTR )
                        {
#ifndef JGXSTACK
                            u1_RetReadFnc = DcmDspDidRangeTbl[ u2TargetIndex ].ptReadDidFnc( stSourceTable.u2SourceDid, ptData, u1OpStatus, u4_DataBufferLength, &u4_DataLength, &u1LocalErrorCode );
#else  /* JGXSTACK */
                            u1_RetReadFnc = E_OK;
                        /* user-defined */
#endif /* JGXSTACK */
                            u1_RetVal = u1_RetReadFnc;
                        }
                    }
                }
                else if( stSourceTable.u1SourceElementId == DCM_DSP_DIDMNG_SOURCEELEMENTID_MEMADDR )
                {
                    (void)Dcm_Dsp_DidMng_CallMemRead( &stSourceTable, DCM_CANCEL, ptData, ptDataLength, &u1LocalErrorCode );
                }
                else
                {
                    /* no process */
                }
            }
            Dcm_Dsp_DidMng_bUserNotifyFlag = (boolean)FALSE;
        }
        Dcm_Dsp_DidMng_u1LoopCnt = (uint8)0U;
        Dcm_Dsp_DidMng_bUserRcrrpFlag = (boolean)FALSE;
    }

    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID23_ENABLED == STD_OFF */
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_OFF */
#endif /* DCM_SUPPORT_SID22 == STD_ON */


#if ( DCM_PERIODIC_DDDID_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_CallReadDynDidFncForPeriodic              */
/* Description   | Call the ReadDidFnc                                      */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DidIndex : Index of DcmDspDDDidTbl[]              */
/*               | [in] u1OpStatus : Operation state                        */
/*               | [in] u4DataBufferLength : Buffer Length                  */
/*               | [out] ptData : Start pointer of read data                */
/*               | [out] ptDataLength : Read Data Length                    */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Process complete                           */
/*               |        E_NOT_OK : Process abnormal termination           */
/*               |        DCM_E_PENDING : Process pending                   */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallReadDynDidFncForPeriodic
(
    const uint16 u2DidIndex,
    const Dcm_OpStatusType u1OpStatus,
    const uint32 u4DataBufferLength,
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA ) ptData,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptDataLength
)
{
    Dcm_Dsp_SourceElementType    stSourceTable;
    uint32                       u4_DataBufferLength;
    uint32                       u4_DataLength;
    uint16                       u2TargetIndex;
    uint8                        u1NumOfSourceDid;
    uint8                        u1RWSupport;
    Std_ReturnType               u1_RetVal;
    Std_ReturnType               u1_RetDidRange;
    Std_ReturnType               u1_RetGetSourceDID;
    Std_ReturnType               u1_RetGetNumOfSrcDid;
    Dcm_NegativeResponseCodeType u1LocalErrorCode;

    u1_RetVal           = E_NOT_OK;
    u1LocalErrorCode    = (uint8)0U;
    *ptDataLength       = (uint32)0U;
    u4_DataBufferLength = (uint32)0U;
    u4_DataLength       = (uint32)0U;

    if( u1OpStatus == DCM_PERIODIC_INITIAL )
    {
        u1_RetGetNumOfSrcDid = Dcm_Dsp_DidMng_GetNumOfSrcDid( u2DidIndex, &u1NumOfSourceDid );
        if( u1_RetGetNumOfSrcDid == (Std_ReturnType)E_OK )
        {
            if( u1NumOfSourceDid > (uint8)0U )
            {
                Dcm_Dsp_DidMng_u1LoopCntForPeriodic = (uint8)0U;
                Dcm_Dsp_DidMng_u1NumOfSrcDidForPeriodic = u1NumOfSourceDid;
                u1_RetVal = Dcm_Dsp_DidMng_CallSDidReadForPeriodic( u2DidIndex, u1OpStatus, u4DataBufferLength, ptData, ptDataLength );

                if( u1_RetVal == (Std_ReturnType)E_OK )
                {
                    /* no process */
                }
                else if( u1_RetVal == (Std_ReturnType)DCM_E_PENDING )
                {
                    /* no process */
                }
                else
                {
                    u1_RetVal = E_NOT_OK;
                }
            }
            else
            {
                /* no process */
            }
        }
        else
        {
            /* no process */
        }
    }
    else if( u1OpStatus == DCM_PERIODIC_PENDING )
    {
        u1_RetVal = Dcm_Dsp_DidMng_CallSDidReadForPeriodic( u2DidIndex, u1OpStatus, u4DataBufferLength, ptData, ptDataLength );
        if( u1_RetVal == (Std_ReturnType)E_OK )
        {
            /* no process */
        }
        else if( u1_RetVal == (Std_ReturnType)DCM_E_PENDING )
        {
            /* no process */
        }
        else
        {
            u1_RetVal = E_NOT_OK;
        }
    }
    else
    {
        u1_RetVal = E_OK;
        u1_RetGetSourceDID = Dcm_Dsp_DidMng_GetSourceDID( u2DidIndex, Dcm_Dsp_DidMng_u1LoopCntForPeriodic, &stSourceTable );
        if( u1_RetGetSourceDID == (Std_ReturnType)E_OK )
        {
            if( stSourceTable.u1SourceElementId == DCM_DSP_DIDMNG_SOURCEELEMENTID_DID )
            {
                u1_RetDidRange = Dcm_Dsp_DidMng_ChkDid( stSourceTable.u2SourceDid, DCM_DSP_DIDMNG_DID_RANGE, &u2TargetIndex, &u1RWSupport );

                if( u1_RetDidRange == DCM_MAIN_E_CHECK_OK )
                {
                    if( DcmDspDidRangeTbl[ u2TargetIndex ].ptReadDidFnc != NULL_PTR )
                    {
#ifndef JGXSTACK
                        (void)DcmDspDidRangeTbl[ u2TargetIndex ].ptReadDidFnc( stSourceTable.u2SourceDid, ptData, u1OpStatus, u4_DataBufferLength, &u4_DataLength, &u1LocalErrorCode );
#else  /* JGXSTACK */
                        /* user-defined */
#endif /* JGXSTACK */
                    }
                }
            }
            else if( stSourceTable.u1SourceElementId == DCM_DSP_DIDMNG_SOURCEELEMENTID_MEMADDR )
            {
                (void)Dcm_Dsp_DidMng_CallMemReadForPeriodic( &stSourceTable, u1OpStatus, ptDataLength, ptData );
            }
            else
            {
                /* no process */
            }
        }
    }

    if( u1_RetVal != (Std_ReturnType)DCM_E_PENDING )
    {
        Dcm_Dsp_DidMng_u1LoopCntForPeriodic = (uint8)0U;
        Dcm_Dsp_DidMng_u1NumOfSrcDidForPeriodic = (uint8)0U;
    }

    return u1_RetVal;
}
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON */


#if ( DCM_SUPPORT_SID2E == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_CallWriteDidFnc                           */
/* Description   | Call the WriteDidFnc                                     */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2RangeIndex : Index of DcmDspDidRangeTbl[]         */
/*               | [in] u2DID : Reqest Data Id                              */
/*               | [in] ptData : Write Data                                 */
/*               | [in] u1OpStatus : Operation state                        */
/*               | [in] ptDataLength : Write Data Length                    */
/*               | [out] ptErrorCode : Negative Response Code               */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Process complete                           */
/*               |        E_NOT_OK : Process abnormal termination           */
/*               |        DCM_E_PENDING : Process pending                   */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallWriteDidFnc
(
    const uint16 u2RangeIndex,
    const uint16 u2DID,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptData,
    const Dcm_OpStatusType u1OpStatus,
    const uint16 u2DataLength,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
)
{
    Std_ReturnType u1_RetVal;
    uint16         u2_DidrangeT;

    u1_RetVal = E_NOT_OK;
    u2_DidrangeT = Dcm_P_u2Didrange_T;
    *ptErrorCode = (uint8)0x00U;

    if( u2RangeIndex < u2_DidrangeT )
    {
        if( DcmDspDidRangeTbl[u2RangeIndex].ptWriteDidFnc != NULL_PTR )
        {
#ifndef JGXSTACK
            u1_RetVal = DcmDspDidRangeTbl[u2RangeIndex].ptWriteDidFnc( u2DID, ptData, u1OpStatus, u2DataLength, ptErrorCode );
#else  /* JGXSTACK */
            /* user-defined */
#endif /* JGXSTACK */
        }
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID2E == STD_ON */


#if ( DCM_SUPPORT_SID2F == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_ChkIOCP                                   */
/* Description   | Check the IOCP Support                                   */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DidIndex : Index of DcmDspDidTbl[]                */
/*               | [in] u1IOCP : Request IOCP                               */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Support                                    */
/*               |        E_NOT_OK : Not Support                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ChkIOCP
(
    const uint16 u2DidIndex,
    const uint8 u1IOCP
)
{
    Std_ReturnType u1_RetVal;
    uint16         u2_DidT;

    u1_RetVal = E_NOT_OK;
    u2_DidT = Dcm_P_u2Did_T;

    if( u2DidIndex < u2_DidT )
    {
        if( DcmDspDidTbl[u2DidIndex].ptInfoRef != NULL_PTR )
        {
            switch( u1IOCP )
            {
                case DCM_DSP_DIDMNG_RCTE:
                    if( ( DcmDspDidTbl[u2DidIndex].ptInfoRef->ptControl->bResetToDefault == (boolean)TRUE ) ||
                        ( DcmDspDidTbl[u2DidIndex].ptInfoRef->ptControl->bFreezeCurrentState == (boolean)TRUE ) ||
                        ( DcmDspDidTbl[u2DidIndex].ptInfoRef->ptControl->bShortTermAdjustment == (boolean)TRUE ) )
                    {
                        u1_RetVal = E_OK;
                    }
                    break;
                case DCM_DSP_DIDMNG_RTD:
                    if( DcmDspDidTbl[u2DidIndex].ptInfoRef->ptControl->bResetToDefault == (boolean)TRUE )
                    {
                        u1_RetVal = E_OK;
                    }
                    break;
                case DCM_DSP_DIDMNG_FCS:
                    if( DcmDspDidTbl[u2DidIndex].ptInfoRef->ptControl->bFreezeCurrentState == (boolean)TRUE )
                    {
                        u1_RetVal = E_OK;
                    }
                    break;
                case DCM_DSP_DIDMNG_STA:
                    if( DcmDspDidTbl[u2DidIndex].ptInfoRef->ptControl->bShortTermAdjustment == (boolean)TRUE )
                    {
                        u1_RetVal = E_OK;
                    }
                    break;
                default:
                    /* no process */
                    break;
            }
        }
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID2F == STD_ON */

#if ( DCM_SUPPORT_SID2F == STD_ON )
#if ( DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_GetCtrlParamLen                           */
/* Description   | Get ControlState length & Num of Data on the DID         */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DidIndex : Index of DcmDspDidTbl[]                */
/*               | [out] ptControlStateLen : controlState length            */
/*               | [out] ptNumOfData : Num of Data on Did                   */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Get OK                                     */
/*               |        E_NOT_OK : Get NG                                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_GetCtrlParamLen
(
    const uint16 u2DidIndex,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) ptControlStateLen,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptNumOfData
)
{
    Std_ReturnType u1_RetVal;
    uint8 u1_cnt;
    uint16         u2_DidT;

    u1_RetVal = E_NOT_OK;
    u2_DidT = Dcm_P_u2Did_T;
    *ptControlStateLen = (uint16)0U;
    *ptNumOfData = (uint8)0U;

    if( u2DidIndex < u2_DidT )
    {
        *ptNumOfData = DcmDspDidTbl[u2DidIndex].u1SignalNum;

        for( u1_cnt = (uint8)0U; u1_cnt < DcmDspDidTbl[u2DidIndex].u1SignalNum; u1_cnt++ )
        {
            if( DcmDspDidTbl[u2DidIndex].ptSignal[u1_cnt].ptDataRef != NULL_PTR )
            {
                *ptControlStateLen += ( (DcmDspDidTbl[u2DidIndex].ptSignal[u1_cnt].ptDataRef->u2Size) >> DCM_DSP_DIDMNG_MASK_BYTESHIFT );   /* no wrap around */
                u1_RetVal = E_OK;
            }
            else
            {
                u1_RetVal = E_NOT_OK;
                break;
            }
        }
    }

    return u1_RetVal;
}
#endif /* DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON */
#endif /* DCM_SUPPORT_SID2F == STD_ON */

#if ( DCM_SUPPORT_SID2F == STD_ON )
#if ( DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_GetCtrlParamLenExternal                   */
/* Description   | Get ControlState length & ControlMask Length             */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DidIndex : Index of DcmDspDidTbl[]                */
/*               | [out] ptControlStateLen : controlState length            */
/*               | [out] ptControlMaskLen  : ControlMask Length             */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Get OK                                     */
/*               |        E_NOT_OK : Get NG                                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_GetCtrlParamLenExternal
(
    const uint16 u2DidIndex,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) ptControlStateLen,
    P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) ptControlMaskLen
)
{
    Std_ReturnType u1_RetVal;
    uint16         u2_DidT;

    u1_RetVal = E_NOT_OK;
    u2_DidT = Dcm_P_u2Did_T;
    *ptControlStateLen = (uint16)0U;
    *ptControlMaskLen  = (uint16)0U;

    if( u2DidIndex < u2_DidT )
    {
        *ptControlStateLen = DcmDspDidTbl[u2DidIndex].u2DidSize;
        if( DcmDspDidTbl[u2DidIndex].ptInfoRef != NULL_PTR )
        {
            *ptControlMaskLen = DcmDspDidTbl[u2DidIndex].ptInfoRef->ptControl->u4ControlMaskSize;
            u1_RetVal = E_OK;
        }
        else
        {
            u1_RetVal = E_NOT_OK;
        }
    }

    return u1_RetVal;
}
#endif /* DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON */
#endif /* DCM_SUPPORT_SID2F == STD_ON */


#if ( DCM_SUPPORT_SID2F == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_ChkCtrlParam                              */
/* Description   | Check the controlState value & controlMask value         */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DidIndex : Index of DcmDspDidTbl[]                */
/*               | [in] ptControlStateInfo : Request ControlState           */
/*               | [in] ptControlMaskInfo : Request ControlMask             */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Check OK                                   */
/*               |        E_NOT_OK : Check NG                               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ChkCtrlParam
(
    const uint16 u2DidIndex,
    P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) ptControlStateInfo,
    P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) ptControlMaskInfo
)
{
    Std_ReturnType u1_RetVal;
    uint16         u2_DidT;

    u1_RetVal = E_NOT_OK;
    u2_DidT = Dcm_P_u2Did_T;

    if( (ptControlStateInfo != NULL_PTR) || (ptControlMaskInfo != NULL_PTR) )
    {
        if( u2DidIndex < u2_DidT )
        {
            if( DcmDspDidTbl[u2DidIndex].pCheckControlParamFnc != NULL_PTR )
            {
#ifndef JGXSTACK
                u1_RetVal = DcmDspDidTbl[u2DidIndex].pCheckControlParamFnc( ptControlStateInfo, ptControlMaskInfo );
#else  /* JGXSTACK */
                /* user-defined */
#endif /* JGXSTACK */
            }
        }
    }
    else
    {
        u1_RetVal = E_OK;
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID2F == STD_ON */


#if ( DCM_SUPPORT_SID2F == STD_ON )
#if ( DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_CallIOCP00Fnc                             */
/* Description   | Call the ReturnControlToEcuFnc                           */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DidIndex : Index of DcmDspDidTbl[]                */
/*               | [in] u1SignalIndex : Index of Signal on the Did          */
/*               | [out] ptErrorCode : Negative Response Code               */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Process complete                           */
/*               |        E_NOT_OK : Process abnormal termination           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallIOCP00Fnc
(
    const uint16 u2DidIndex,
    const uint8 u1SignalIndex,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode
)
{
    Std_ReturnType u1_RetVal;
    Std_ReturnType u1_FuncRet;
    Dcm_NegativeResponseCodeType u1_FuncErrorCode;
    uint16         u2_FuncIndex;
    uint16         u2_DataRCTECUFncT;
    uint16         u2_DidT;

    u1_RetVal = E_NOT_OK;
    u1_FuncRet = E_NOT_OK;
    *ptErrorCode = (uint8)0x00U;
    u1_FuncErrorCode = (uint8)0x00U;
    u2_DidT = Dcm_P_u2Did_T;
    u2_DataRCTECUFncT = Dcm_P_u2Data_RCTECU_Fnc_T;

    if( u2DidIndex < u2_DidT )
    {
        if( u1SignalIndex < DcmDspDidTbl[u2DidIndex].u1SignalNum )
        {
            u2_FuncIndex = DcmDspDidTbl[u2DidIndex].ptSignal[u1SignalIndex].ptDataRef->u2ReturnControlToEcuFnc;

            switch( DcmDspDidTbl[u2DidIndex].ptSignal[u1SignalIndex].ptDataRef->u1UsePort )
            {
                case DCM_DSP_USE_SYNCH_FNC:
                case DCM_DSP_USE_ASYNCH_FNC:
                case DCM_DSP_USE_ASYNCH_FNC_ERR:
                case DCM_DSP_USE_SYNCH_CS:
                case DCM_DSP_USE_ASYNCH_CS:
                case DCM_DSP_USE_ASYNCH_CS_ERR:
                    if( u2_FuncIndex < u2_DataRCTECUFncT )
                    {
                        if( DcmDspDataReturnControlToECUFuncTbl[u2_FuncIndex] != NULL_PTR )
                        {
#ifndef JGXSTACK
                            u1_FuncRet = DcmDspDataReturnControlToECUFuncTbl[u2_FuncIndex]( &u1_FuncErrorCode );
#else  /* JGXSTACK */
                            /* user-defined */
#endif /* JGXSTACK */
                        }
                    }
                    if( (u1_FuncRet == (Std_ReturnType)E_OK) || (u1_FuncRet == (Std_ReturnType)E_NOT_OK) )
                    {
                        u1_RetVal = u1_FuncRet;
                        *ptErrorCode = u1_FuncErrorCode;
                    }
                    break;
                default :
                    /* no process */
                    break;
            }
        }
    }
    return u1_RetVal;
}
#endif /* DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON */

#if ( DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_CallIOCP00Fnc                             */
/* Description   | Call the ReturnControlToEcuFnc                           */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DidIndex : Index of DcmDspDidTbl[]                */
/*               | [in] u1SignalIndex : Index of Signal on the Did          */
/*               | [in] ptControlMaskInfo : Request controMask              */
/*               | [out] ptErrorCode : Negative Response Code               */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Process complete                           */
/*               |        E_NOT_OK : Process abnormal termination           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallIOCP00Fnc
(
    const uint16 u2DidIndex,
    const uint8 u1SignalIndex,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptControlMaskInfo,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode
)
{
    Std_ReturnType u1_RetVal;
    Std_ReturnType u1_FuncRet;
    uint16         u2_DidT;
    uint16         u2_FuncIndex;
    uint16         u2_DataRCTECUFncT;
    uint16         u2_DataExternalRCTECUFncT;

    u1_RetVal        = E_NOT_OK;
    u1_FuncRet       = E_NOT_OK;
    u2_DidT          = Dcm_P_u2Did_T;
    u2_DataRCTECUFncT         = Dcm_P_u2Data_RCTECU_Fnc_T;
    u2_DataExternalRCTECUFncT = Dcm_P_u2Data_External_RCTECU_Fnc_T;

    if( u2DidIndex < u2_DidT )
    {
        if( u1SignalIndex < DcmDspDidTbl[u2DidIndex].u1SignalNum )
        {
            u2_FuncIndex = DcmDspDidTbl[u2DidIndex].ptSignal[u1SignalIndex].ptDataRef->u2ReturnControlToEcuFnc;

            switch( DcmDspDidTbl[u2DidIndex].ptSignal[u1SignalIndex].ptDataRef->u1UsePort )
            {
                case DCM_DSP_USE_SYNCH_FNC:
                case DCM_DSP_USE_ASYNCH_FNC:
                case DCM_DSP_USE_ASYNCH_FNC_ERR:
                case DCM_DSP_USE_SYNCH_CS:
                case DCM_DSP_USE_ASYNCH_CS:
                case DCM_DSP_USE_ASYNCH_CS_ERR:
                    if( ptControlMaskInfo == NULL_PTR )
                    {
                        if( u2_FuncIndex < u2_DataRCTECUFncT )
                        {
                            if( DcmDspDataReturnControlToECUFuncTbl[u2_FuncIndex] != NULL_PTR )
                            {
#ifndef JGXSTACK
                                u1_FuncRet = DcmDspDataReturnControlToECUFuncTbl[u2_FuncIndex]( ptErrorCode );
#else  /* JGXSTACK */
                                /* user-defined */
#endif /* JGXSTACK */
                            }
                        
                        }
                    }
                    else
                    {
                        if( u2_FuncIndex < u2_DataExternalRCTECUFncT )
                        {
                            if( DcmDspDataExternalReturnControlToECUFuncTbl[u2_FuncIndex] != NULL_PTR )
                            {
#ifndef JGXSTACK
                                u1_FuncRet = DcmDspDataExternalReturnControlToECUFuncTbl[u2_FuncIndex]( ptControlMaskInfo, ptErrorCode );
#else  /* JGXSTACK */
                                /* user-defined */
#endif /* JGXSTACK */
                            }
                        }
                    }
                    u1_RetVal = u1_FuncRet;
                    break;
                default :
                    /* no process */
                    break;
            }
        }
    }
    return u1_RetVal;
}
#endif /* DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON */
#endif /* DCM_SUPPORT_SID2F == STD_ON */


#if ( DCM_SUPPORT_SID2F == STD_ON )
#if ( DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_CallIOCP01Fnc                             */
/* Description   | Call the ResetToDefaultFnc                               */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DidIndex : Index of DcmDspDidTbl[]                */
/*               | [in] u1SignalIndex : Index of Signal on the Did          */
/*               | [in] u1OpStatus : Operation state                        */
/*               | [out] ptErrorCode : Negative Response Code               */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Process complete                           */
/*               |        E_NOT_OK : Process abnormal termination           */
/*               |        DCM_E_PENDING : Process pending                   */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallIOCP01Fnc
(
    const uint16 u2DidIndex,
    const uint8 u1SignalIndex,
    const Dcm_OpStatusType u1OpStatus,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode
)
{
    Std_ReturnType u1_RetVal;
    Std_ReturnType u1_FuncRet;
    uint16 u2_FuncIndex;
    uint16 u2_DataSyncRTDFncT;
    uint16 u2_DataAsyncRTDFncT;
    uint16 u2_DidT;
    Dcm_NegativeResponseCodeType u1_FuncErrorCode;

    u1_RetVal = E_NOT_OK;
    *ptErrorCode = (uint8)0x00U;
    u2_DataSyncRTDFncT  = Dcm_P_u2Data_Sync_RTD_Fnc_T;
    u2_DataAsyncRTDFncT = Dcm_P_u2Data_Async_RTD_Fnc_T;
    u2_DidT = Dcm_P_u2Did_T;
    u1_FuncErrorCode = (uint8)0x00U;

    if( u2DidIndex < u2_DidT )
    {
        if( u1SignalIndex < DcmDspDidTbl[u2DidIndex].u1SignalNum )
        {
            u2_FuncIndex = DcmDspDidTbl[u2DidIndex].ptSignal[u1SignalIndex].ptDataRef->u2ResetToDefaultFnc;

            switch( DcmDspDidTbl[u2DidIndex].ptSignal[u1SignalIndex].ptDataRef->u1UsePort )
            {
                case DCM_DSP_USE_SYNCH_FNC:
                case DCM_DSP_USE_SYNCH_CS:
                    if( u2_FuncIndex < u2_DataSyncRTDFncT )
                    {
                        if( DcmDspDataSyncResetToDefaultFuncTbl[u2_FuncIndex] != NULL_PTR )
                        {
#ifndef JGXSTACK
                            u1_FuncRet = DcmDspDataSyncResetToDefaultFuncTbl[u2_FuncIndex]( &u1_FuncErrorCode );
#else  /* JGXSTACK */
                            u1_FuncRet = E_OK;
                            /* user-defined */
#endif /* JGXSTACK */
                            if( (u1_FuncRet == (Std_ReturnType)E_OK) || (u1_FuncRet == (Std_ReturnType)E_NOT_OK) )
                            {
                                u1_RetVal = u1_FuncRet;
                                *ptErrorCode = u1_FuncErrorCode;
                            }
                        }
                    }
                    break;
                case DCM_DSP_USE_ASYNCH_FNC:
                case DCM_DSP_USE_ASYNCH_FNC_ERR:
                case DCM_DSP_USE_ASYNCH_CS:
                case DCM_DSP_USE_ASYNCH_CS_ERR:
                    if( u2_FuncIndex < u2_DataAsyncRTDFncT )
                    {
                        if( DcmDspDataAsyncResetToDefaultFuncTbl[u2_FuncIndex] != NULL_PTR )
                        {
#ifndef JGXSTACK
                            u1_FuncRet = DcmDspDataAsyncResetToDefaultFuncTbl[u2_FuncIndex]( u1OpStatus, &u1_FuncErrorCode );
#else  /* JGXSTACK */
                            u1_FuncRet = E_OK;
                            /* user-defined */
#endif /* JGXSTACK */
                            if( (u1_FuncRet == (Std_ReturnType)E_OK) || (u1_FuncRet == (Std_ReturnType)E_NOT_OK) || (u1_FuncRet == (Std_ReturnType)DCM_E_PENDING) )
                            {
                                u1_RetVal = u1_FuncRet;
                                *ptErrorCode = u1_FuncErrorCode;
                            }
                        }
                    }
                    break;
                default :
                    /* no process */
                    break;
            }
        }
    }

    return u1_RetVal;
}
#endif /* DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON */

#if ( DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_CallIOCP01Fnc                             */
/* Description   | Call the ResetToDefaultFnc                               */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DidIndex : Index of DcmDspDidTbl[]                */
/*               | [in] u1SignalIndex : Index of Signal on the Did          */
/*               | [in] u1OpStatus : Operation state                        */
/*               | [in] ptControlMaskInfo : Request controMask              */
/*               | [out] ptErrorCode : Negative Response Code               */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Process complete                           */
/*               |        E_NOT_OK : Process abnormal termination           */
/*               |        DCM_E_PENDING : Process pending                   */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallIOCP01Fnc
(
    const uint16 u2DidIndex,
    const uint8 u1SignalIndex,
    const Dcm_OpStatusType u1OpStatus,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptControlMaskInfo,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode
)
{
    Std_ReturnType u1_RetVal;
    Std_ReturnType u1_FuncRet;
    uint16 u2_FuncIndex;
    uint16 u2_DataSyncRTDFncT;
    uint16 u2_DataAsyncRTDFncT;
    uint16 u2_DataSyncExternalRTDFncT;
    uint16 u2_DataAsyncExternalRTDFncT;
    uint16 u2_DidT;

    u1_RetVal = E_NOT_OK;
    u1_FuncRet = E_NOT_OK;
    u2_DataSyncRTDFncT  = Dcm_P_u2Data_Sync_RTD_Fnc_T;
    u2_DataAsyncRTDFncT = Dcm_P_u2Data_Async_RTD_Fnc_T;
    u2_DataSyncExternalRTDFncT  = Dcm_P_u2Data_Sync_External_RTD_Fnc_T;
    u2_DataAsyncExternalRTDFncT = Dcm_P_u2Data_Async_External_RTD_Fnc_T;
    u2_DidT = Dcm_P_u2Did_T;

    if( u2DidIndex < u2_DidT )
    {
        if( u1SignalIndex < DcmDspDidTbl[u2DidIndex].u1SignalNum )
        {
            u2_FuncIndex = DcmDspDidTbl[u2DidIndex].ptSignal[u1SignalIndex].ptDataRef->u2ResetToDefaultFnc;

            switch( DcmDspDidTbl[u2DidIndex].ptSignal[u1SignalIndex].ptDataRef->u1UsePort )
            {
                case DCM_DSP_USE_SYNCH_FNC:
                case DCM_DSP_USE_SYNCH_CS:
                    if( ptControlMaskInfo == NULL_PTR )
                    {
                        if( u2_FuncIndex < u2_DataSyncRTDFncT )
                        {
                            if( DcmDspDataSyncResetToDefaultFuncTbl[u2_FuncIndex] != NULL_PTR )
                            {
#ifndef JGXSTACK
                                u1_FuncRet = DcmDspDataSyncResetToDefaultFuncTbl[u2_FuncIndex]( ptErrorCode );
#else  /* JGXSTACK */
                                /* user-defined */
#endif /* JGXSTACK */
                            }
                        }
                    }
                    else
                    {
                        if( u2_FuncIndex < u2_DataSyncExternalRTDFncT )
                        {
                            if( DcmDspDataSyncExternalResetToDefaultFuncTbl[u2_FuncIndex] != NULL_PTR )
                            {
#ifndef JGXSTACK
                                u1_FuncRet = DcmDspDataSyncExternalResetToDefaultFuncTbl[u2_FuncIndex]( ptControlMaskInfo, ptErrorCode );
#else  /* JGXSTACK */
                                /* user-defined */
#endif /* JGXSTACK */
                            }
                        }
                    }
                    u1_RetVal = u1_FuncRet;
                    break;
                case DCM_DSP_USE_ASYNCH_FNC:
                case DCM_DSP_USE_ASYNCH_FNC_ERR:
                case DCM_DSP_USE_ASYNCH_CS:
                case DCM_DSP_USE_ASYNCH_CS_ERR:
                    if( ptControlMaskInfo == NULL_PTR )
                    {
                        if( u2_FuncIndex < u2_DataAsyncRTDFncT )
                        {
                            if( DcmDspDataAsyncResetToDefaultFuncTbl[u2_FuncIndex] != NULL_PTR )
                            {
#ifndef JGXSTACK
                                u1_FuncRet = DcmDspDataAsyncResetToDefaultFuncTbl[u2_FuncIndex]( u1OpStatus, ptErrorCode );
#else  /* JGXSTACK */
                                /* user-defined */
#endif /* JGXSTACK */
                            }
                        }
                    }
                    else
                    {
                        if( u2_FuncIndex < u2_DataAsyncExternalRTDFncT )
                        {
                            if( DcmDspDataAsyncExternalResetToDefaultFuncTbl[u2_FuncIndex] != NULL_PTR )
                            {
#ifndef JGXSTACK
                                u1_FuncRet = DcmDspDataAsyncExternalResetToDefaultFuncTbl[u2_FuncIndex]( u1OpStatus, ptControlMaskInfo, ptErrorCode );
#else  /* JGXSTACK */
                                /* user-defined */
#endif /* JGXSTACK */
                            }
                        }
                    }
                    u1_RetVal = u1_FuncRet;
                    break;
                default :
                    /* no process */
                    break;
            }
        }
    }

    return u1_RetVal;
}
#endif /* DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON */
#endif /* DCM_SUPPORT_SID2F == STD_ON */


#if ( DCM_SUPPORT_SID2F == STD_ON )
#if ( DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_CallIOCP02Fnc                             */
/* Description   | Call the FreezeCurrentStateFnc                           */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DidIndex : Index of DcmDspDidTbl[]                */
/*               | [in] u1SignalIndex : Index of Signal on the Did          */
/*               | [in] u1OpStatus : Operation state                        */
/*               | [out] ptErrorCode : Negative Response Code               */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Process complete                           */
/*               |        E_NOT_OK : Process abnormal termination           */
/*               |        DCM_E_PENDING : Process pending                   */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallIOCP02Fnc
(
    const uint16 u2DidIndex,
    const uint8 u1SignalIndex,
    const Dcm_OpStatusType u1OpStatus,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode
)
{
    Std_ReturnType u1_RetVal;
    Std_ReturnType u1_FuncRet;
    uint16 u2_FuncIndex;
    uint16 u2_DataSyncFcsFncT;
    uint16 u2_DataAsyncFcsFncT;
    uint16 u2_DidT;
    Dcm_NegativeResponseCodeType u1_FuncErrorCode;

    u1_RetVal = E_NOT_OK;
    *ptErrorCode = (uint8)0x00U;
    u2_DataSyncFcsFncT  = Dcm_P_u2Data_Sync_Fcs_Fnc_T;
    u2_DataAsyncFcsFncT = Dcm_P_u2Data_Async_Fcs_Fnc_T;
    u2_DidT = Dcm_P_u2Did_T;
    u1_FuncErrorCode = (uint8)0x00U;

    if( u2DidIndex < u2_DidT )
    {
        if( u1SignalIndex < DcmDspDidTbl[u2DidIndex].u1SignalNum )
        {
            u2_FuncIndex = DcmDspDidTbl[u2DidIndex].ptSignal[u1SignalIndex].ptDataRef->u2FreezeCurrentStateFnc;

            switch( DcmDspDidTbl[u2DidIndex].ptSignal[u1SignalIndex].ptDataRef->u1UsePort )
            {
                case DCM_DSP_USE_SYNCH_FNC:
                case DCM_DSP_USE_SYNCH_CS:
                    if( u2_FuncIndex < u2_DataSyncFcsFncT )
                    {
                        if( DcmDspDataSyncFreezeCurrentStateFuncTbl[u2_FuncIndex] != NULL_PTR )
                        {
#ifndef JGXSTACK
                            u1_FuncRet = DcmDspDataSyncFreezeCurrentStateFuncTbl[u2_FuncIndex]( &u1_FuncErrorCode );
#else  /* JGXSTACK */
                            u1_FuncRet = E_OK;
                            /* user-defined */
#endif /* JGXSTACK */
                            if( (u1_FuncRet == (Std_ReturnType)E_OK) || (u1_FuncRet == (Std_ReturnType)E_NOT_OK) )
                            {
                                u1_RetVal = u1_FuncRet;
                                *ptErrorCode = u1_FuncErrorCode;
                            }
                        }
                    }
                    break;
                case DCM_DSP_USE_ASYNCH_FNC:
                case DCM_DSP_USE_ASYNCH_FNC_ERR:
                case DCM_DSP_USE_ASYNCH_CS:
                case DCM_DSP_USE_ASYNCH_CS_ERR:
                    if( u2_FuncIndex < u2_DataAsyncFcsFncT )
                    {
                        if( DcmDspDataAsyncFreezeCurrentStateFuncTbl[u2_FuncIndex] != NULL_PTR )
                        {
#ifndef JGXSTACK
                            u1_FuncRet = DcmDspDataAsyncFreezeCurrentStateFuncTbl[u2_FuncIndex]( u1OpStatus, &u1_FuncErrorCode );
#else  /* JGXSTACK */
                            u1_FuncRet = E_OK;
                            /* user-defined */
#endif /* JGXSTACK */
                            if( (u1_FuncRet == (Std_ReturnType)E_OK) || (u1_FuncRet == (Std_ReturnType)E_NOT_OK) || (u1_FuncRet == (Std_ReturnType)DCM_E_PENDING) )
                            {
                                u1_RetVal = u1_FuncRet;
                                *ptErrorCode = u1_FuncErrorCode;
                            }
                        }
                    }
                    break;
                default :
                    /* no process */
                    break;
            }
        }
    }
    return u1_RetVal;
}
#endif /* DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON */

#if ( DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_CallIOCP02Fnc                             */
/* Description   | Call the FreezeCurrentStateFnc                           */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DidIndex : Index of DcmDspDidTbl[]                */
/*               | [in] u1SignalIndex : Index of Signal on the Did          */
/*               | [in] u1OpStatus : Operation state                        */
/*               | [in] ptControlMaskInfo : Request controMask              */
/*               | [out] ptErrorCode : Negative Response Code               */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Process complete                           */
/*               |        E_NOT_OK : Process abnormal termination           */
/*               |        DCM_E_PENDING : Process pending                   */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallIOCP02Fnc
(
    const uint16 u2DidIndex,
    const uint8 u1SignalIndex,
    const Dcm_OpStatusType u1OpStatus,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptControlMaskInfo,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode
)
{
    Std_ReturnType u1_RetVal;
    Std_ReturnType u1_FuncRet;
    uint16 u2_FuncIndex;
    uint16 u2_DataSyncFcsFncT;
    uint16 u2_DataAsyncFcsFncT;
    uint16 u2_DataSyncExternalFcsFncT;
    uint16 u2_DataAsyncExternalFcsFncT;
    uint16 u2_DidT;

    u1_RetVal = E_NOT_OK;
    u1_FuncRet = E_NOT_OK;
    u2_DataSyncFcsFncT  = Dcm_P_u2Data_Sync_Fcs_Fnc_T;
    u2_DataAsyncFcsFncT = Dcm_P_u2Data_Async_Fcs_Fnc_T;
    u2_DataSyncExternalFcsFncT  = Dcm_P_u2Data_Sync_External_Fcs_Fnc_T ;
    u2_DataAsyncExternalFcsFncT = Dcm_P_u2Data_Async_External_Fcs_Fnc_T;
    u2_DidT = Dcm_P_u2Did_T;

    if( u2DidIndex < u2_DidT )
    {
        if( u1SignalIndex < DcmDspDidTbl[u2DidIndex].u1SignalNum )
        {
            u2_FuncIndex = DcmDspDidTbl[u2DidIndex].ptSignal[u1SignalIndex].ptDataRef->u2FreezeCurrentStateFnc;

            switch( DcmDspDidTbl[u2DidIndex].ptSignal[u1SignalIndex].ptDataRef->u1UsePort )
            {
                case DCM_DSP_USE_SYNCH_FNC:
                case DCM_DSP_USE_SYNCH_CS:
                    if( ptControlMaskInfo == NULL_PTR )
                    {
                        if( u2_FuncIndex < u2_DataSyncFcsFncT )
                        {
                            if( DcmDspDataSyncFreezeCurrentStateFuncTbl[u2_FuncIndex] != NULL_PTR )
                            {
#ifndef JGXSTACK
                                u1_FuncRet = DcmDspDataSyncFreezeCurrentStateFuncTbl[u2_FuncIndex]( ptErrorCode );
#else  /* JGXSTACK */
                                /* user-defined */
#endif /* JGXSTACK */
                            }
                        }
                    }
                    else
                    {
                        if( u2_FuncIndex < u2_DataSyncExternalFcsFncT )
                        {
                            if( DcmDspDataSyncExternalFreezeCurrentStateFuncTbl[u2_FuncIndex] != NULL_PTR )
                            {
#ifndef JGXSTACK
                                u1_FuncRet = DcmDspDataSyncExternalFreezeCurrentStateFuncTbl[u2_FuncIndex]( ptControlMaskInfo, ptErrorCode );
#else  /* JGXSTACK */
                                /* user-defined */
#endif /* JGXSTACK */
                            }
                        }
                    }
                    u1_RetVal = u1_FuncRet;
                    break;
                case DCM_DSP_USE_ASYNCH_FNC:
                case DCM_DSP_USE_ASYNCH_FNC_ERR:
                case DCM_DSP_USE_ASYNCH_CS:
                case DCM_DSP_USE_ASYNCH_CS_ERR:
                    if( ptControlMaskInfo == NULL_PTR )
                    {
                        if( u2_FuncIndex < u2_DataAsyncFcsFncT )
                        {
                            if( DcmDspDataAsyncFreezeCurrentStateFuncTbl[u2_FuncIndex] != NULL_PTR )
                            {
#ifndef JGXSTACK
                                u1_FuncRet = DcmDspDataAsyncFreezeCurrentStateFuncTbl[u2_FuncIndex]( u1OpStatus, ptErrorCode );
#else  /* JGXSTACK */
                                /* user-defined */
#endif /* JGXSTACK */
                            }
                        }
                    }
                    else
                    {
                        if( u2_FuncIndex < u2_DataAsyncExternalFcsFncT )
                        {
                            if( DcmDspDataAsyncExternalFreezeCurrentStateFuncTbl[u2_FuncIndex] != NULL_PTR )
                            {
#ifndef JGXSTACK
                                u1_FuncRet = DcmDspDataAsyncExternalFreezeCurrentStateFuncTbl[u2_FuncIndex]( u1OpStatus,  ptControlMaskInfo, ptErrorCode );
#else  /* JGXSTACK */
                                /* user-defined */
#endif /* JGXSTACK */
                            }
                        }
                    }
                    u1_RetVal = u1_FuncRet;
                    break;
                default :
                    /* no process */
                    break;
            }
        }
    }
    return u1_RetVal;
}
#endif /* DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON */
#endif /* DCM_SUPPORT_SID2F == STD_ON */


#if ( DCM_SUPPORT_SID2F == STD_ON )
#if ( DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_CallIOCP03Fnc                             */
/* Description   | Call the ShortTermAdjustmentFnc                          */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DidIndex : Index of DcmDspDidTbl[]                */
/*               | [in] u1SignalIndex : Index of Signal on the Did          */
/*               | [in] ptControlStateInfo : Request controlState           */
/*               | [in] u1OpStatus : Operation state                        */
/*               | [out] ptErrorCode : Negative Response Code               */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Process complete                           */
/*               |        E_NOT_OK : Process abnormal termination           */
/*               |        DCM_E_PENDING : Process pending                   */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallIOCP03Fnc
(
    const uint16 u2DidIndex,
    const uint8 u1SignalIndex,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptControlStateInfo,
    const Dcm_OpStatusType u1OpStatus,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode
)
{
    Std_ReturnType u1_RetVal;
    Std_ReturnType u1_FuncRet;
    uint16 u2_FuncIndex;
    uint16 u2_DataPos;
    uint16 u2_DataSyncSTAFncT;
    uint16 u2_DataAsyncSTAFncT;
    uint16 u2_DidT;
    Dcm_NegativeResponseCodeType u1_FuncErrorCode;

    u1_RetVal = E_NOT_OK;
    *ptErrorCode = (uint8)0x00U;
    u2_DataSyncSTAFncT  = Dcm_P_u2Data_Sync_STA_Fnc_T;
    u2_DataAsyncSTAFncT = Dcm_P_u2Data_Async_STA_Fnc_T;
    u2_DidT = Dcm_P_u2Did_T;
    u1_FuncErrorCode = (uint8)0x00U;

    if( u2DidIndex < u2_DidT )
    {
        if( u1SignalIndex < DcmDspDidTbl[u2DidIndex].u1SignalNum )
        {
            if( DcmDspDidTbl[u2DidIndex].ptSignal[u1SignalIndex].ptDataRef->u1Type == DCM_DSP_BOOLEAN )
            {
                u2_DataPos = (uint16)0U;
            }
            else
            {
                u2_DataPos = ( DcmDspDidTbl[u2DidIndex].ptSignal[u1SignalIndex].u2DataPos >> DCM_DSP_DIDMNG_MASK_BYTESHIFT );
            }

            u2_FuncIndex = DcmDspDidTbl[u2DidIndex].ptSignal[u1SignalIndex].ptDataRef->u2ShortTermAdjustmentFnc;

            switch( DcmDspDidTbl[u2DidIndex].ptSignal[u1SignalIndex].ptDataRef->u1UsePort )
            {
                case DCM_DSP_USE_SYNCH_FNC:
                case DCM_DSP_USE_SYNCH_CS:
                    if( u2_FuncIndex < u2_DataSyncSTAFncT )
                    {
                        if( DcmDspDataSyncShortTermAdjustmentFuncTbl[u2_FuncIndex] != NULL_PTR )
                        {
#ifndef JGXSTACK
                            u1_FuncRet = DcmDspDataSyncShortTermAdjustmentFuncTbl[u2_FuncIndex]( &ptControlStateInfo[u2_DataPos], &u1_FuncErrorCode );
#else  /* JGXSTACK */
                            u1_FuncRet = E_OK;
                            /* user-defined */
#endif /* JGXSTACK */
                            if( (u1_FuncRet == (Std_ReturnType)E_OK) || (u1_FuncRet == (Std_ReturnType)E_NOT_OK) )
                            {
                                u1_RetVal = u1_FuncRet;
                                *ptErrorCode = u1_FuncErrorCode;
                            }
                        }
                    }
                    break;
                case DCM_DSP_USE_ASYNCH_FNC:
                case DCM_DSP_USE_ASYNCH_FNC_ERR:
                case DCM_DSP_USE_ASYNCH_CS:
                case DCM_DSP_USE_ASYNCH_CS_ERR:
                    if( u2_FuncIndex < u2_DataAsyncSTAFncT )
                    {
                        if( DcmDspDataAsyncShortTermAdjustmentFuncTbl[u2_FuncIndex] != NULL_PTR )
                        {
#ifndef JGXSTACK
                            u1_FuncRet = DcmDspDataAsyncShortTermAdjustmentFuncTbl[u2_FuncIndex]( &ptControlStateInfo[u2_DataPos], u1OpStatus, &u1_FuncErrorCode );
#else  /* JGXSTACK */
                            u1_FuncRet = E_OK;
                            /* user-defined */
#endif /* JGXSTACK */
                            if( (u1_FuncRet == (Std_ReturnType)E_OK) || (u1_FuncRet == (Std_ReturnType)E_NOT_OK) || (u1_FuncRet == (Std_ReturnType)DCM_E_PENDING) )
                            {
                                u1_RetVal = u1_FuncRet;
                                *ptErrorCode = u1_FuncErrorCode;
                            }
                        }
                    }
                    break;
                default :
                    /* no process */
                    break;
            }
        }
    }
    return u1_RetVal;
}
#endif /* DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON */
#if ( DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_CallIOCP03Fnc                             */
/* Description   | Call the ShortTermAdjustmentFnc                          */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DidIndex : Index of DcmDspDidTbl[]                */
/*               | [in] u1SignalIndex : Index of Signal on the Did          */
/*               | [in] ptControlStateInfo : Request controlState           */
/*               | [in] u1OpStatus : Operation state                        */
/*               | [in] ptControlMaskInfo : Request controMask              */
/*               | [out] ptErrorCode : Negative Response Code               */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Process complete                           */
/*               |        E_NOT_OK : Process abnormal termination           */
/*               |        DCM_E_PENDING : Process pending                   */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallIOCP03Fnc
(
    const uint16 u2DidIndex,
    const uint8 u1SignalIndex,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptControlStateInfo,
    const Dcm_OpStatusType u1OpStatus,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptControlMaskInfo,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode
)
{
    Std_ReturnType u1_RetVal;
    Std_ReturnType u1_FuncRet;
    uint16 u2_FuncIndex;
    uint16 u2_DataSyncSTAFncT;
    uint16 u2_DataAsyncSTAFncT;
    uint16 u2_DataSyncExternalSTAFncT;
    uint16 u2_DataAsyncExternalSTAFncT;
    uint16 u2_DidT;

    u1_RetVal = E_NOT_OK;
    u1_FuncRet = E_NOT_OK;
    u2_DataSyncSTAFncT  = Dcm_P_u2Data_Sync_STA_Fnc_T;
    u2_DataAsyncSTAFncT = Dcm_P_u2Data_Async_STA_Fnc_T;
    u2_DataSyncExternalSTAFncT  = Dcm_P_u2Data_Sync_External_STA_Fnc_T;
    u2_DataAsyncExternalSTAFncT = Dcm_P_u2Data_Async_External_STA_Fnc_T;
    u2_DidT = Dcm_P_u2Did_T;

    if( u2DidIndex < u2_DidT )
    {
        if( u1SignalIndex < DcmDspDidTbl[u2DidIndex].u1SignalNum )
        {
            u2_FuncIndex = DcmDspDidTbl[u2DidIndex].ptSignal[u1SignalIndex].ptDataRef->u2ShortTermAdjustmentFnc;

            switch( DcmDspDidTbl[u2DidIndex].ptSignal[u1SignalIndex].ptDataRef->u1UsePort )
            {
                case DCM_DSP_USE_SYNCH_FNC:
                case DCM_DSP_USE_SYNCH_CS:
                    if( ptControlMaskInfo == NULL_PTR )
                    {
                        if( u2_FuncIndex < u2_DataSyncSTAFncT )
                        {
                            if( DcmDspDataSyncShortTermAdjustmentFuncTbl[u2_FuncIndex] != NULL_PTR )
                            {
#ifndef JGXSTACK
                                u1_FuncRet = DcmDspDataSyncShortTermAdjustmentFuncTbl[u2_FuncIndex]( ptControlStateInfo, ptErrorCode );
#else  /* JGXSTACK */
                                /* user-defined */
#endif /* JGXSTACK */
                            }
                        }
                    }
                    else
                    {
                        if( u2_FuncIndex < u2_DataSyncExternalSTAFncT )
                        {
                            if( DcmDspDataSyncExternalShortTermAdjustmentFuncTbl[u2_FuncIndex] != NULL_PTR )
                            {
#ifndef JGXSTACK
                                u1_FuncRet = DcmDspDataSyncExternalShortTermAdjustmentFuncTbl[u2_FuncIndex]( ptControlStateInfo, ptControlMaskInfo, ptErrorCode );
#else  /* JGXSTACK */
                                /* user-defined */
#endif /* JGXSTACK */
                            }
                        }
                    }
                    u1_RetVal = u1_FuncRet;
                    break;
                case DCM_DSP_USE_ASYNCH_FNC:
                case DCM_DSP_USE_ASYNCH_FNC_ERR:
                case DCM_DSP_USE_ASYNCH_CS:
                case DCM_DSP_USE_ASYNCH_CS_ERR:
                    if( ptControlMaskInfo == NULL_PTR )
                    {
                        if( u2_FuncIndex < u2_DataAsyncSTAFncT )
                        {
                            if( DcmDspDataAsyncShortTermAdjustmentFuncTbl[u2_FuncIndex] != NULL_PTR )
                            {
#ifndef JGXSTACK
                                u1_FuncRet = DcmDspDataAsyncShortTermAdjustmentFuncTbl[u2_FuncIndex]( ptControlStateInfo, u1OpStatus, ptErrorCode );
#else  /* JGXSTACK */
                                /* user-defined */
#endif /* JGXSTACK */
                            }
                        }
                    }
                    else
                    {
                        if( u2_FuncIndex < u2_DataAsyncExternalSTAFncT )
                        {
                            if( DcmDspDataAsyncExternalShortTermAdjustmentFuncTbl[u2_FuncIndex] != NULL_PTR )
                            {
#ifndef JGXSTACK
                                u1_FuncRet = DcmDspDataAsyncExternalShortTermAdjustmentFuncTbl[u2_FuncIndex]( ptControlStateInfo, u1OpStatus, ptControlMaskInfo, ptErrorCode );
#else  /* JGXSTACK */
                                /* user-defined */
#endif /* JGXSTACK */
                            }
                        }
                    }
                    u1_RetVal = u1_FuncRet;
                    break;
                default :
                    /* no process */
                    break;
            }
        }
    }
    return u1_RetVal;
}
#endif /* DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON */
#endif /* DCM_SUPPORT_SID2F == STD_ON */

#if ( DCM_SUPPORT_SID2F == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_CallReadFnc                               */
/* Description   | Call the ReadFnc                                         */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DidIndex : Index of DcmDspDidTbl[]                */
/*               | [in] u1SignalIndex : Index of Signal on the Did          */
/*               | [in] u1OpStatus : Operation state                        */
/*               | [out] ptData : Read Data                                 */
/*               | [out] ptErrorCode : Negative Response Code               */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Process complete                           */
/*               |        E_NOT_OK : Process abnormal termination           */
/*               |        DCM_E_PENDING : Process pending                   */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallReadFnc
(
    const uint16 u2DidIndex,
    const uint8 u1SignalIndex,
    const Dcm_OpStatusType u1OpStatus,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptData,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode
)
{
    Std_ReturnType u1_RetVal;
    Std_ReturnType u1_FuncRet;
    uint16 u2_FuncIndex;
    uint16 u2_DataPos;
    uint16 u2_DataSyncReadFncT;
    uint16 u2_DataAsyncReadFncT;
    uint16 u2_DataAsyncErrReadFNCT;
    uint16 u2_DidT;
    Dcm_NegativeResponseCodeType u1_FuncErrorCode;

    u1_RetVal = E_NOT_OK;
    *ptErrorCode = (uint8)0x00U;
    u2_DataSyncReadFncT     = Dcm_P_u2Data_Sync_Read_Fnc_T;
    u2_DataAsyncReadFncT    = Dcm_P_u2Data_Async_Read_Fnc_T;
    u2_DataAsyncErrReadFNCT = Dcm_P_u2Data_Async_Err_Read_FNC_T;
    u2_DidT = Dcm_P_u2Did_T;
    u1_FuncErrorCode = (uint8)0x00U;

    if( u2DidIndex < u2_DidT )
    {
        if( u1SignalIndex < DcmDspDidTbl[u2DidIndex].u1SignalNum )
        {
            if( DcmDspDidTbl[u2DidIndex].ptSignal[u1SignalIndex].ptDataRef->u1Type == DCM_DSP_BOOLEAN )
            {
                u2_DataPos = (uint16)0U;
            }
            else
            {
                u2_DataPos = ( DcmDspDidTbl[u2DidIndex].ptSignal[u1SignalIndex].u2DataPos >> DCM_DSP_DIDMNG_MASK_BYTESHIFT );
            }

            u2_FuncIndex = DcmDspDidTbl[u2DidIndex].ptSignal[u1SignalIndex].ptDataRef->u2ReadFnc;

            switch( DcmDspDidTbl[u2DidIndex].ptSignal[u1SignalIndex].ptDataRef->u1UsePort )
            {
                case DCM_DSP_USE_SYNCH_FNC:
                case DCM_DSP_USE_SYNCH_CS:
                    if( u2_FuncIndex < u2_DataSyncReadFncT )
                    {
#ifndef JGXSTACK
                        u1_FuncRet = DcmDspDataSyncReadFuncTbl[u2_FuncIndex]( &ptData[u2_DataPos] );
#else  /* JGXSTACK */
                        u1_FuncRet = E_OK;
                        /* user-defined */
#endif /* JGXSTACK */

                        if( u1_FuncRet == (Std_ReturnType)E_OK )
                        {
                            u1_RetVal = u1_FuncRet;
                        }
                    }
                    break;
                case DCM_DSP_USE_ASYNCH_FNC:
                case DCM_DSP_USE_ASYNCH_CS:
                    if( u2_FuncIndex < u2_DataAsyncReadFncT )
                    {
#ifndef JGXSTACK
                        u1_FuncRet = DcmDspDataAsyncReadFuncTbl[u2_FuncIndex]( u1OpStatus, &ptData[u2_DataPos] );
#else  /* JGXSTACK */
                        u1_FuncRet = E_OK;
                        /* user-defined */
#endif /* JGXSTACK */

                        if( (u1_FuncRet == (Std_ReturnType)E_OK) || (u1_FuncRet == (Std_ReturnType)DCM_E_PENDING) )
                        {
                            u1_RetVal = u1_FuncRet;
                        }
                    }
                    break;
                case DCM_DSP_USE_ASYNCH_FNC_ERR:
                case DCM_DSP_USE_ASYNCH_CS_ERR:
                    if( u2_FuncIndex < u2_DataAsyncErrReadFNCT )
                    {
#ifndef JGXSTACK
                        u1_FuncRet = DcmDspDataAsyncErrReadFuncTbl[u2_FuncIndex]( u1OpStatus, &ptData[u2_DataPos], &u1_FuncErrorCode );
#else  /* JGXSTACK */
                        u1_FuncRet = E_OK;
                        /* user-defined */
#endif /* JGXSTACK */

                        if( (u1_FuncRet == (Std_ReturnType)E_OK) || (u1_FuncRet == (Std_ReturnType)E_NOT_OK) || (u1_FuncRet == (Std_ReturnType)DCM_E_PENDING) )
                        {
                            u1_RetVal = u1_FuncRet;
                            *ptErrorCode = u1_FuncErrorCode;
                        }
                    }
                    break;
                default :
                    /* no process */
                    break;
            }
        }
    }
    return u1_RetVal;
}
#endif /* DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON */
#if ( DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallReadFnc
(
    const uint16 u2DidIndex,
    const uint8 u1SignalIndex,
    const Dcm_OpStatusType u1OpStatus,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptData,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode
)
{
    Std_ReturnType u1_RetVal;
    Std_ReturnType u1_FuncRet;
    uint16 u2_FuncIndex;
    uint16 u2_DataSyncReadFncT;
    uint16 u2_DataAsyncReadFncT;
    uint16 u2_DataAsyncErrReadFNCT;
    uint16 u2_DidT;

    u1_RetVal = E_NOT_OK;
    u1_FuncRet = E_NOT_OK;
    u2_DataSyncReadFncT     = Dcm_P_u2Data_Sync_Read_Fnc_T;
    u2_DataAsyncReadFncT    = Dcm_P_u2Data_Async_Read_Fnc_T;
    u2_DataAsyncErrReadFNCT = Dcm_P_u2Data_Async_Err_Read_FNC_T;
    u2_DidT = Dcm_P_u2Did_T;

    if( u2DidIndex < u2_DidT )
    {
        if( u1SignalIndex < DcmDspDidTbl[u2DidIndex].u1SignalNum )
        {
            u2_FuncIndex = DcmDspDidTbl[u2DidIndex].ptSignal[u1SignalIndex].ptDataRef->u2ReadFnc;

            switch( DcmDspDidTbl[u2DidIndex].ptSignal[u1SignalIndex].ptDataRef->u1UsePort )
            {
                case DCM_DSP_USE_SYNCH_FNC:
                case DCM_DSP_USE_SYNCH_CS:
                    if( u2_FuncIndex < u2_DataSyncReadFncT )
                    {
#ifndef JGXSTACK
                        u1_FuncRet = DcmDspDataSyncReadFuncTbl[u2_FuncIndex]( &ptData[0] );
#else  /* JGXSTACK */
                        /* user-defined */
#endif /* JGXSTACK */
                    }
                    u1_RetVal = u1_FuncRet;
                    break;
                case DCM_DSP_USE_ASYNCH_FNC:
                case DCM_DSP_USE_ASYNCH_CS:
                    if( u2_FuncIndex < u2_DataAsyncReadFncT )
                    {
#ifndef JGXSTACK
                        u1_FuncRet = DcmDspDataAsyncReadFuncTbl[u2_FuncIndex]( u1OpStatus, &ptData[0] );
#else  /* JGXSTACK */
                        /* user-defined */
#endif /* JGXSTACK */
                    }
                    u1_RetVal = u1_FuncRet;
                    break;
                case DCM_DSP_USE_ASYNCH_FNC_ERR:
                case DCM_DSP_USE_ASYNCH_CS_ERR:
                    if( u2_FuncIndex < u2_DataAsyncErrReadFNCT )
                    {
#ifndef JGXSTACK
                        u1_FuncRet = DcmDspDataAsyncErrReadFuncTbl[u2_FuncIndex]( u1OpStatus, &ptData[0], ptErrorCode );
#else  /* JGXSTACK */
                        /* user-defined */
#endif /* JGXSTACK */
                    }
                    u1_RetVal = u1_FuncRet;
                    break;
                default :
                    /* no process */
                    break;
            }
        }
    }
    return u1_RetVal;
}
#endif /* DCM_SID2F_CONTROLMASK_EXTERNAL_USE == STD_ON */
#endif /* DCM_SUPPORT_SID2F == STD_ON */


#if ( ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID23 == STD_ON ) || ( DCM_SUPPORT_SID3D == STD_ON ) )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_ChkALFID                                  */
/* Description   | ALFID support check                                      */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1ALFId : Request ALFID                             */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : ALFID support                              */
/*               |        E_NOT_OK : ALFID not supported                    */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ChkALFID
(
    const uint8 u1ALFId
)
{
    P2CONST( AB_83_ConstV uint8, AUTOMATIC, DCM_APPL_CONST ) pt_SptALFId;
    Std_ReturnType u1_RetVal;
    uint8 u1_cnt;

    u1_RetVal = E_NOT_OK;

    if( DcmDspMemory.ptMemoryIdInfo != NULL_PTR )
    {
        if( DcmDspMemory.ptALFId != NULL_PTR )
        {
            pt_SptALFId = DcmDspMemory.ptALFId->ptSupportedALFId;
            for( u1_cnt = (uint8)0U; u1_cnt < DcmDspMemory.ptALFId->u1SupportedALFIdNum; u1_cnt++ )
            {
                if( u1ALFId == pt_SptALFId[u1_cnt] )
                {
                    u1_RetVal = E_OK;
                    break;
                }
            }
        }
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID23 == STD_ON || DCM_SUPPORT_SID3D == STD_ON */


#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID23 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) || ( DCM_SUPPORT_SID3D == STD_ON ) )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_ChkMemAddress                             */
/* Description   | Memory Address support check                             */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1ReadWrite : Reading/Writing type                  */
/*               | [in] u4MemAddress : Request memory address               */
/*               | [in] u1MemIdFlag : Memory Flag                           */
/*               | [in] u1MemId : Memory Id                                 */
/*               | [out] ptMemoryIdIndex : Index of Memory Id Table         */
/*               | [out] ptMemoryRangeIndex : Index of Memory Range Table   */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Memory Address support                     */
/*               |        E_NOT_OK : Memory Address not supported           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ChkMemAddress
(
    const uint8 u1ReadWrite,
    const uint32 u4MemAddress,
    const uint8 u1MemIdFlag,
    const uint8 u1MemId,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptMemoryIdIndex,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptMemoryRangeIndex
)
{
    Std_ReturnType u1_RetVal;
    boolean b_CheckFlag;
    uint8 u1_MemoryIdIndex;
    uint8 u1_MemoryRangeIndex;

    u1_RetVal = E_NOT_OK;
    b_CheckFlag = (boolean)FALSE;
    u1_MemoryIdIndex = (uint8)0U;

    if( DcmDspMemory.ptMemoryIdInfo != NULL_PTR )
    {
        if( u1MemIdFlag == DCM_DSP_DIDMNG_MEM_ID_VALID )
        {
            for( u1_MemoryIdIndex = (uint8)0U; u1_MemoryIdIndex < DcmDspMemory.u1MemoryIdInfoNum; u1_MemoryIdIndex++ )
            {
                if( DcmDspMemory.ptMemoryIdInfo[u1_MemoryIdIndex].bMemoryIdValueFlag == (boolean)TRUE )
                {
                    if( u1MemId == DcmDspMemory.ptMemoryIdInfo[u1_MemoryIdIndex].u1MemoryIdValue )
                    {
                        *ptMemoryIdIndex = u1_MemoryIdIndex;
                        b_CheckFlag = (boolean)TRUE;
                        break;
                    }
                }
            }
        }
        else
        {
            *ptMemoryIdIndex = (uint8)0U;
            b_CheckFlag = (boolean)TRUE;
        }

        if( b_CheckFlag == (boolean)TRUE )
        {
            if( u1ReadWrite == DCM_DSP_DIDMNG_MEM_READ )
            {
                if( DcmDspMemory.ptMemoryIdInfo[u1_MemoryIdIndex].u1ReadMemoryRangeInfoNum != (uint8)0U )   /* If not Zero, then ptReadMemoryRangeInfo is not NULL_PTR */
                {
                    for( u1_MemoryRangeIndex = (uint8)0U; u1_MemoryRangeIndex < DcmDspMemory.ptMemoryIdInfo[u1_MemoryIdIndex].u1ReadMemoryRangeInfoNum; u1_MemoryRangeIndex++ )
                    {
                        if( DcmDspMemory.ptMemoryIdInfo[u1_MemoryIdIndex].ptReadMemoryRangeInfo[u1_MemoryRangeIndex].u4MemoryRangeLow <= u4MemAddress )
                        {
                            if( u4MemAddress <= DcmDspMemory.ptMemoryIdInfo[u1_MemoryIdIndex].ptReadMemoryRangeInfo[u1_MemoryRangeIndex].u4MemoryRangeHigh )
                            {
                                *ptMemoryRangeIndex = u1_MemoryRangeIndex;
                                u1_RetVal = E_OK;
                                break;
                            }
                        }
                    }
                }
            }
            else
            {
                if( DcmDspMemory.ptMemoryIdInfo[u1_MemoryIdIndex].u1WriteMemoryRangeInfoNum != (uint8)0U )   /* If not Zero, then ptWriteMemoryRangeInfo is not NULL_PTR */
                {
                    for( u1_MemoryRangeIndex = (uint8)0U; u1_MemoryRangeIndex < DcmDspMemory.ptMemoryIdInfo[u1_MemoryIdIndex].u1WriteMemoryRangeInfoNum; u1_MemoryRangeIndex++ )
                    {
                        if( DcmDspMemory.ptMemoryIdInfo[u1_MemoryIdIndex].ptWriteMemoryRangeInfo[u1_MemoryRangeIndex].u4MemoryRangeLow <= u4MemAddress )
                        {
                            if( u4MemAddress <= DcmDspMemory.ptMemoryIdInfo[u1_MemoryIdIndex].ptWriteMemoryRangeInfo[u1_MemoryRangeIndex].u4MemoryRangeHigh )
                            {
                                *ptMemoryRangeIndex = u1_MemoryRangeIndex;
                                u1_RetVal = E_OK;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    return u1_RetVal;
}
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID23 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON || DCM_SUPPORT_SID3D == STD_ON */


#if ( ( DCM_SUPPORT_SID23 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID3D == STD_ON ) )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_ChkMemSize                                */
/* Description   | Memory Size support check                                */
/* Preconditions | Before calling this function, ensure that the memory to  */
/*               | be checked exists using Dcm_Dsp_DidMng_ChkMemAddress()   */
/* Parameters    | [in] u1ReadWrite : Reading/Writing type                  */
/*               | [in] u1MemoryIdIndex : Index of Memory Id Table          */
/*               | [in] u1MemoryRangeIndex : Index of Memory Range Table    */
/*               | [in] u4MemAddress : Request memory address               */
/*               | [in] u4MemSize : Request memory size                     */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Space support                              */
/*               |        E_NOT_OK : No area support                        */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ChkMemSize
(
    const uint8 u1ReadWrite,
    const uint8 u1MemoryIdIndex,
    const uint8 u1MemoryRangeIndex,
    const uint32 u4MemAddress,
    const uint32 u4MemSize
)
{
    Std_ReturnType u1_RetVal;
    uint32 u4_MemoryRangeHigh;

    u1_RetVal = E_NOT_OK;

    if( u1ReadWrite == DCM_DSP_DIDMNG_MEM_READ )
    {
        u4_MemoryRangeHigh = DcmDspMemory.ptMemoryIdInfo[u1MemoryIdIndex].ptReadMemoryRangeInfo[u1MemoryRangeIndex].u4MemoryRangeHigh;
    }
    else
    {
        u4_MemoryRangeHigh = DcmDspMemory.ptMemoryIdInfo[u1MemoryIdIndex].ptWriteMemoryRangeInfo[u1MemoryRangeIndex].u4MemoryRangeHigh;
    }

    if( (u4MemSize - (uint32)1U) <= (u4_MemoryRangeHigh - u4MemAddress) )   /* no wrap around */
    {
        u1_RetVal = E_OK;
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID23 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID3D == STD_ON */


#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID23 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) || ( DCM_SUPPORT_SID3D == STD_ON ) )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_ChkMemSes                                 */
/* Description   | Session check of designated area                         */
/* Preconditions | Before calling this function, ensure that the memory to  */
/*               | be checked exists using Dcm_Dsp_DidMng_ChkMemAddress()   */
/* Parameters    | [in] u1ReadWrite : Reading/Writing type                  */
/*               | [in] u1MemoryIdIndex : Index of Memory Id Table          */
/*               | [in] u1MemoryRangeIndex : Index of Memory Range Table    */
/*               | [in] u1CurrentSessionLevel : Current session level       */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Accessible                                 */
/*               |        E_NOT_OK : Inaccessible                           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ChkMemSes
(
    const uint8 u1ReadWrite,
    const uint8 u1MemoryIdIndex,
    const uint8 u1MemoryRangeIndex,
    const uint8 u1CurrentSessionLevel
)
{
    Std_ReturnType u1_RetVal;
    uint8 u1_cnt;

    u1_RetVal = E_NOT_OK;

    if( u1ReadWrite == DCM_DSP_DIDMNG_MEM_READ )
    {
        if( DcmDspMemory.ptMemoryIdInfo[u1MemoryIdIndex].ptReadMemoryRangeInfo[u1MemoryRangeIndex].u1MemoryRangeSessionLevelNum == (uint8)0U )
        {
            u1_RetVal = E_OK;
        }
        else
        {
            for( u1_cnt = (uint8)0U; u1_cnt < DcmDspMemory.ptMemoryIdInfo[u1MemoryIdIndex].ptReadMemoryRangeInfo[u1MemoryRangeIndex].u1MemoryRangeSessionLevelNum; u1_cnt++ )
            {
                if( u1CurrentSessionLevel == DcmDspMemory.ptMemoryIdInfo[u1MemoryIdIndex].ptReadMemoryRangeInfo[u1MemoryRangeIndex].ptMemoryRangeSessionLevelRef[u1_cnt] )
                {
                    u1_RetVal = E_OK;
                    break;
                }
            }
        }
    }
    else
    {
        if( DcmDspMemory.ptMemoryIdInfo[u1MemoryIdIndex].ptWriteMemoryRangeInfo[u1MemoryRangeIndex].u1MemoryRangeSessionLevelNum == (uint8)0U )
        {
            u1_RetVal = E_OK;
        }
        else
        {
            for( u1_cnt = (uint8)0U; u1_cnt < DcmDspMemory.ptMemoryIdInfo[u1MemoryIdIndex].ptWriteMemoryRangeInfo[u1MemoryRangeIndex].u1MemoryRangeSessionLevelNum; u1_cnt++ )
            {
                if( u1CurrentSessionLevel == DcmDspMemory.ptMemoryIdInfo[u1MemoryIdIndex].ptWriteMemoryRangeInfo[u1MemoryRangeIndex].ptMemoryRangeSessionLevelRef[u1_cnt] )
                {
                    u1_RetVal = E_OK;
                    break;
                }
            }
        }
    }

    return u1_RetVal;
}
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID23 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON || DCM_SUPPORT_SID3D == STD_ON */


#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID23 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) || ( DCM_SUPPORT_SID3D == STD_ON ) )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_ChkMemSec                                 */
/* Description   | Security check of designated area                        */
/* Preconditions | Before calling this function, ensure that the memory to  */
/*               | be checked exists using Dcm_Dsp_DidMng_ChkMemAddress()   */
/* Parameters    | [in] u1ReadWrite : Reading/Writing type                  */
/*               | [in] u1MemoryIdIndex : Index of Memory Id Table          */
/*               | [in] u1MemoryRangeIndex : Index of Memory Range Table    */
/*               | [in] u1CurrentSecurityLevel : Current security level     */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Accessible                                 */
/*               |        E_NOT_OK : Inaccessible                           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ChkMemSec
(
    const uint8 u1ReadWrite,
    const uint8 u1MemoryIdIndex,
    const uint8 u1MemoryRangeIndex,
    const uint8 u1CurrentSecurityLevel
)
{
    Std_ReturnType u1_RetVal;
    uint8 u1_cnt;

    u1_RetVal = E_NOT_OK;

    if( u1ReadWrite == DCM_DSP_DIDMNG_MEM_READ )
    {
        if( DcmDspMemory.ptMemoryIdInfo[u1MemoryIdIndex].ptReadMemoryRangeInfo[u1MemoryRangeIndex].u1MemoryRangeSecurityLevelNum == (uint8)0U )
        {
            u1_RetVal = E_OK;
        }
        else
        {
            for( u1_cnt = (uint8)0U; u1_cnt < DcmDspMemory.ptMemoryIdInfo[u1MemoryIdIndex].ptReadMemoryRangeInfo[u1MemoryRangeIndex].u1MemoryRangeSecurityLevelNum; u1_cnt++ )
            {
                if( u1CurrentSecurityLevel == DcmDspMemory.ptMemoryIdInfo[u1MemoryIdIndex].ptReadMemoryRangeInfo[u1MemoryRangeIndex].ptMemoryRangeSecurityLevelRef[u1_cnt] )
                {
                    u1_RetVal = E_OK;
                    break;
                }
            }
        }
    }
    else
    {
        if( DcmDspMemory.ptMemoryIdInfo[u1MemoryIdIndex].ptWriteMemoryRangeInfo[u1MemoryRangeIndex].u1MemoryRangeSecurityLevelNum == (uint8)0U )
        {
            u1_RetVal = E_OK;
        }
        else
        {
            for( u1_cnt = (uint8)0U; u1_cnt < DcmDspMemory.ptMemoryIdInfo[u1MemoryIdIndex].ptWriteMemoryRangeInfo[u1MemoryRangeIndex].u1MemoryRangeSecurityLevelNum; u1_cnt++ )
            {
                if( u1CurrentSecurityLevel == DcmDspMemory.ptMemoryIdInfo[u1MemoryIdIndex].ptWriteMemoryRangeInfo[u1MemoryRangeIndex].ptMemoryRangeSecurityLevelRef[u1_cnt] )
                {
                    u1_RetVal = E_OK;
                    break;
                }
            }
        }
    }

    return u1_RetVal;
}
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID23 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON || DCM_SUPPORT_SID3D == STD_ON */


#if ( DCM_SUPPORT_SID2C == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_ChkDDDIDLimit                             */
/* Description   | Check limit of number of elements                        */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DidIndex : Index of DcmDspDidTbl[]                */
/*               | [in] u4NumOfSourceElement : Number of elements           */
/*               | [in] u4TotalSize : Total memory size                     */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Check OK                                   */
/*               |        E_NOT_OK : Check NG                               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ChkDDDIDLimit    /* MISRA DEVIATION */
(
    const uint16 u2DidIndex,
    const uint32 u4NumOfSourceElement,
    const uint32 u4TotalSize
)
{
    uint32 u4_CurrentSize;
    uint16 u2DDDidIndex;
    uint16 u2_DidT;
    uint16 u2_DataId;
    Std_ReturnType u1_RetVal;
    Std_ReturnType u1_FuncRet;
    uint8 u1_NumOfSourceElement;
    uint8 u1_cnt;
    Dcm_Dsp_SourceElementType stSourceElement;
    boolean b_CheckFlag;

    u1_RetVal = E_OK;
    u2_DidT = Dcm_P_u2Did_T;

    if( u2DidIndex < u2_DidT )
    {
        u2_DataId = DcmDspDidTbl[u2DidIndex].u2Identifier;
        u1_FuncRet = Dcm_Dsp_DidMng_GetDynamicIndex(u2_DataId, &u2DDDidIndex);
        if( u1_FuncRet == (Std_ReturnType)E_OK )
        {
            u1_FuncRet = Dcm_Dsp_DidMng_GetNumOfSrcDid(u2DDDidIndex, &u1_NumOfSourceElement);
            if( u1_FuncRet == (Std_ReturnType)E_OK )
            {
                if( (u4NumOfSourceElement + u1_NumOfSourceElement) <= DcmDspDidTbl[u2DidIndex].ptInfoRef->u1DDDIDMaxElements )  /* no wrap around */
                {
                    u4_CurrentSize = (uint32)0U;
                    b_CheckFlag = (boolean)TRUE;

                    for( u1_cnt = (uint8)0U; u1_cnt < u1_NumOfSourceElement; u1_cnt++ )
                    {
                        u1_FuncRet = Dcm_Dsp_DidMng_GetSourceDID(u2DDDidIndex, u1_cnt, &stSourceElement);
                        if( u1_FuncRet == (Std_ReturnType)E_OK )
                        {
                            if( stSourceElement.u1SourceElementId == DCM_DSP_DIDMNG_SOURCEELEMENTID_DID )
                            {
                                u4_CurrentSize += stSourceElement.u1Size;   /* no wrap around */
                            }
                            else if( stSourceElement.u1SourceElementId == DCM_DSP_DIDMNG_SOURCEELEMENTID_MEMADDR )
                            {
                                u4_CurrentSize += stSourceElement.u4MemSize;    /* no wrap around */
                            }
                            else
                            {
                                b_CheckFlag = (boolean)FALSE;
                            }
                        }
                        else
                        {
                            b_CheckFlag = (boolean)FALSE;
                        }

                        if( b_CheckFlag == (boolean)FALSE )
                        {
                            break;
                        }
                    }

                    if( b_CheckFlag == (boolean)TRUE )
                    {
                        u1_FuncRet = Dcm_Dsp_DidMng_ChkDDDIDDataLen( u4TotalSize, u4_CurrentSize, u2_DataId );
                        if( u1_FuncRet != (Std_ReturnType)E_OK )
                        {
                            u1_RetVal = E_NOT_OK;
                        }
                    }
                    else
                    {
                        u1_RetVal = E_NOT_OK;
                    }
                }
                else
                {
                    u1_RetVal = E_NOT_OK;
                }
            }
            else
            {
                u1_RetVal = E_NOT_OK;
            }
        }
        else
        {
            u1_RetVal = E_NOT_OK;
        }
    }
    else
    {
        u1_RetVal = E_NOT_OK;
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID2C == STD_ON */


#if ( DCM_SUPPORT_SID2C == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_ChkDDDIDLimitMemAddr                      */
/* Description   | Check limit of number of elements                        */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DidIndex : Index of DcmDspDidTbl[]                */
/*               | [in] u4NumOfSourceElement : Number of elements           */
/*               | [in] u4MemSizeTotal : Total memorySize                   */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Check OK                                   */
/*               |        E_NOT_OK : Check NG                               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ChkDDDIDLimitMemAddr    /* MISRA DEVIATION */
(
    const uint16 u2DidIndex,
    const uint32 u4NumOfSourceElement,
    const uint32 u4MemSizeTotal
)
{
    uint32         u4_CurrentSize;
    uint16         u2DDDidIndex;
    uint16         u2_DataId;
    boolean        b_CheckFlag;
    uint8          u1_NumOfSourceElement;
    uint8          u1_cnt;
    Std_ReturnType u1_RetVal;
    Std_ReturnType u1_FuncRet;
    Dcm_Dsp_SourceElementType stSourceElement;

    u1_RetVal = E_OK;

    if( u2DidIndex < DCM_P_DID_T )
    {
        u2_DataId = DcmDspDidTbl[u2DidIndex].u2Identifier;
        u1_FuncRet = Dcm_Dsp_DidMng_GetDynamicIndex(u2_DataId, &u2DDDidIndex);
        if( u1_FuncRet == (Std_ReturnType)E_OK )
        {
            u1_FuncRet = Dcm_Dsp_DidMng_GetNumOfSrcDid(u2DDDidIndex, &u1_NumOfSourceElement);
            if( u1_FuncRet == (Std_ReturnType)E_OK )
            {
                if( (u4NumOfSourceElement + u1_NumOfSourceElement) <= DcmDspDidTbl[u2DidIndex].ptInfoRef->u1DDDIDMaxElements )  /* no wrap around */
                {
                    u4_CurrentSize = (uint32)0U;
                    b_CheckFlag = (boolean)TRUE;

                    for( u1_cnt = (uint8)0U; u1_cnt < u1_NumOfSourceElement; u1_cnt++ )
                    {
                        u1_FuncRet = Dcm_Dsp_DidMng_GetSourceDID(u2DDDidIndex, u1_cnt, &stSourceElement);
                        if( u1_FuncRet == (Std_ReturnType)E_OK )
                        {
                            if( stSourceElement.u1SourceElementId == DCM_DSP_DIDMNG_SOURCEELEMENTID_DID )
                            {
                                u4_CurrentSize += stSourceElement.u1Size;   /* no wrap around */
                            }
                            else if( stSourceElement.u1SourceElementId == DCM_DSP_DIDMNG_SOURCEELEMENTID_MEMADDR )
                            {
                                u4_CurrentSize += stSourceElement.u4MemSize;    /* no wrap around */
                            }
                            else
                            {
                                b_CheckFlag = (boolean)FALSE;
                            }
                        }
                        else
                        {
                            b_CheckFlag = (boolean)FALSE;
                        }

                        if( b_CheckFlag == (boolean)FALSE )
                        {
                            break;
                        }
                    }

                    if( b_CheckFlag == (boolean)TRUE )
                    {
                        u1_FuncRet = Dcm_Dsp_DidMng_ChkDDDIDDataLen( u4MemSizeTotal, u4_CurrentSize, u2_DataId );
                        if( u1_FuncRet != (Std_ReturnType)E_OK )
                        {
                            u1_RetVal = E_NOT_OK;
                        }
                    }
                    else
                    {
                        u1_RetVal = E_NOT_OK;
                    }
                }
                else
                {
                    u1_RetVal = E_NOT_OK;
                }
            }
            else
            {
                u1_RetVal = E_NOT_OK;
            }
        }
        else
        {
            u1_RetVal = E_NOT_OK;
        }
    }
    else
    {
        u1_RetVal = E_NOT_OK;
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID2C == ON */


#if ( DCM_SUPPORT_SID2C == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_SetDDDID                                  */
/* Description   | Set DDDID to RAM                                         */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1KindOfSourceElement : Kind of element             */
/*               | [in] ptRequestMessage : Request message                  */
/*               | [in] u1NumOfSourceElement : Number of elements           */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Set OK                                     */
/*               |        E_NOT_OK : Set NG                                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_SetDDDID  /* MISRA DEVIATION */
(
    const uint8 u1KindOfSourceElement,
    P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) ptRequestMessage,
    const uint8 u1NumOfSourceElement
)
{
    uint16 u2_DddidT;
    uint16 u2_DDDid;
    uint16 u2DDDidIndex;
    Std_ReturnType u1_FuncRet;
    Std_ReturnType u1_RetVal;

    u2_DddidT = Dcm_P_u2Dddid_T;

    if( u1NumOfSourceElement != (uint8)0U )
    {
        if( ptRequestMessage != NULL_PTR )
        {
            u2_DDDid = (uint16)(((uint16)ptRequestMessage[0]) << DCM_DSP_DIDMNG_DIDSHIFT) | ((uint16)ptRequestMessage[1]);

            u1_FuncRet = Dcm_Dsp_DidMng_GetDynamicIndex(u2_DDDid, &u2DDDidIndex);
            if( u1_FuncRet == (Std_ReturnType)E_OK )
            {
                if( u2DDDidIndex < u2_DddidT )
                {
                    if( DcmDspDDDidTbl[u2DDDidIndex].ptSourceElementRef != NULL_PTR )
                    {
                        if( u1KindOfSourceElement ==  DCM_DSP_DIDMNG_DATA_IDENTIFIER )
                        {
                            u1_RetVal = Dcm_Dsp_DidMng_SetSourceElement( u2DDDidIndex, ptRequestMessage, u1NumOfSourceElement );
                        } else if( u1KindOfSourceElement ==  DCM_DSP_DIDMNG_MEM_ADDRESS )  {
                            u1_RetVal = Dcm_Dsp_DidMng_SetMemAddrSourceElement( u2DDDidIndex, ptRequestMessage, u1NumOfSourceElement );
                        } else {
                            u1_RetVal = E_NOT_OK;
                        }
                    }
                    else
                    {
                        u1_RetVal = E_NOT_OK;
                    }
                }
                else
                {
                    u1_RetVal = E_NOT_OK;
                }
            }
            else
            {
                u1_RetVal = E_NOT_OK;
            }
        }
        else
        {
            u1_RetVal = E_NOT_OK;
        }
    }
    else
    {
        u1_RetVal = E_NOT_OK;
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID2C == ON */


#if ( DCM_SUPPORT_SID2C == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_ClearDDDID                                */
/* Description   | Clear DDDID                                              */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DDDid : Request Data Id                           */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Clear OK                                   */
/*               |        E_NOT_OK : Clear NG                               */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_NVM_DDDID_USE == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ClearDDDID   /* MISRA DEVIATION */
(
    const uint16 u2DDDid
)
{
    Std_ReturnType u1_FuncRet;
    uint16 u2DDDidIndex;
    Std_ReturnType u1_RetVal;
    uint8  u1_SourceDidIndex;

    u1_RetVal = E_NOT_OK;
    u1_SourceDidIndex = (uint8)0x00U;

    u1_FuncRet = Dcm_Dsp_DidMng_GetDynamicIndex(u2DDDid, &u2DDDidIndex);
    if( u1_FuncRet == (Std_ReturnType)E_OK )
    {
        u1_RetVal = Dcm_Dsp_DidMng_ClrNumOfSrcElm(u2DDDidIndex);
        if( u1_RetVal ==  (Std_ReturnType)E_OK )
        {
            (void)Dcm_Dsp_DidMng_WriteStorage(DCM_DSP_DIDMNG_CLEAR, u2DDDidIndex, u1_SourceDidIndex);
        }
    }

    return u1_RetVal;
}
#endif /* DCM_NVM_DDDID_USE == STD_ON */
#if ( DCM_NVM_DDDID_USE == STD_OFF )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ClearDDDID   /* MISRA DEVIATION */
(
    const uint16 u2DDDid
)
{
    Std_ReturnType u1_FuncRet;
    uint16 u2DDDidIndex;
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_NOT_OK;

    u1_FuncRet = Dcm_Dsp_DidMng_GetDynamicIndex(u2DDDid, &u2DDDidIndex);
    if( u1_FuncRet == (Std_ReturnType)E_OK )
    {
        u1_RetVal = Dcm_Dsp_DidMng_ClrNumOfSrcElm(u2DDDidIndex);
    }

    return u1_RetVal;
}
#endif /* DCM_NVM_DDDID_USE == STD_OFF */
#endif /* DCM_SUPPORT_SID2C == ON */


#if ( DCM_SUPPORT_SID2C == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_ClearAllDDDID                             */
/* Description   | Clear All DDDID                                          */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1KindOfClear : Kind of Clear DDDid                 */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Clear OK                                   */
/*               |        E_NOT_OK : Clear NG                               */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_NVM_DDDID_USE == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ClearAllDDDID   /* MISRA DEVIATION */
(
    const uint8 u1KindOfClear
)
{
    uint16 u2_DDDidIndex;
    uint8  u1_SourceDidIndex;
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;
    u2_DDDidIndex = (uint16)0x0000U;
    u1_SourceDidIndex = (uint8)0x00U;

    if( u1KindOfClear == DCM_DSP_DIDMNG_CLEAR_ALL_2CSF03 )
    {
        u1_RetVal = Dcm_Dsp_DidMng_ClrAllNumOfSrcElm();
        if( u1_RetVal == (Std_ReturnType)E_OK )
        {
            (void)Dcm_Dsp_DidMng_WriteStorage( DCM_DSP_DIDMNG_CLEAR_ALL, u2_DDDidIndex, u1_SourceDidIndex );
        }
    }

    return u1_RetVal;
}
#endif /* DCM_NVM_DDDID_USE == STD_ON */
#if ( DCM_NVM_DDDID_USE == STD_OFF )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ClearAllDDDID   /* MISRA DEVIATION */
(
    const uint8 u1KindOfClear   /* MISRA DEVIATION */
)
{
    Std_ReturnType u1_RetVal;

    /* Clear all DDDID */
    u1_RetVal = Dcm_Dsp_DidMng_ClrAllNumOfSrcElm();

    return u1_RetVal;
}
#endif /* DCM_NVM_DDDID_USE == STD_OFF */
#endif /* DCM_SUPPORT_SID2C == ON */

#if ( DCM_SUPPORT_SID2C == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_ClearNoSupDDDID                           */
/* Description   | Clear DDDID that not supported in New Ses/Sec            */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1KindOfCheck : Kind of Check                       */
/*               | [in] u1CheckElement : SecLevel/SesLevel                  */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_DidMng_ClearNoSupDDDID   /* MISRA DEVIATION */
(
    const uint8 u1KindOfCheck,
    const uint8 u1CheckElement
)
{
    Dcm_Dsp_SourceElementType st_SourceTable;
    P2CONST(AB_83_ConstV Dcm_Dsp_DidInfoType, AUTOMATIC, DCM_APPL_CONST) pt_InfoTbl;
    uint16                    u2_DDDid;
    uint16                    u2_DDDidNumber;
    uint16                    u2_DDDidIndex;
    uint16                    u2_DidIndex;
    uint16                    u2_RangeDidIndex;
    uint8                     u1_RWSupport;
    uint8                     u1_NumOfSourceDid;
    uint8                     u1_SourceDidIndex;
    Std_ReturnType            u1_RetDDDidInfo;
    Std_ReturnType            u1_RetGetSourceDID;
    Std_ReturnType            u1_RetDidRange;
    Std_ReturnType            u1_RetSourceDidInfo;
    Std_ReturnType            u1_RetAddrInfo;
    Dcm_Main_ReturnCheckType  u1_RetSearchDid;
    boolean                   b_ClearDDDid;
    boolean                   b_SupportedSourceElm;
    boolean                   b_ChkSrcElm;
    boolean                   b_Chk_Per_Source_Did;

    u2_DDDidNumber       = Dcm_P_DIDMNG_u2DDDidNumber;
    b_Chk_Per_Source_Did = Dcm_P_DIDMNG_bChk_Per_Source_Did;

    for( u2_DDDidIndex = (uint16)0U; u2_DDDidIndex < u2_DDDidNumber; u2_DDDidIndex++ )
    {
        u1_NumOfSourceDid = DcmDspDDDidNumOfSourceElement[u2_DDDidIndex];
        if( u1_NumOfSourceDid > (uint8)0U )
        {
            b_ClearDDDid = (boolean)FALSE;
            u2_DDDid = DcmDspDDDidTbl[u2_DDDidIndex].u2DDDid;
            u2_DidIndex = (uint16)0U;
            u1_RWSupport = (uint8)0x00U;
            /* Get Index of DcmDspDidTbl[] */
            u1_RetSearchDid = Dcm_Dsp_DidMng_BinarySearchDid( u2_DDDid, &u2_DidIndex, &u1_RWSupport );
            if( u1_RetSearchDid == DCM_MAIN_E_CHECK_OK )
            {
                pt_InfoTbl = DcmDspDidTbl[u2_DidIndex].ptInfoRef;
                /* Security/Session Check of DDDID */
                u1_RetDDDidInfo = Dcm_Dsp_DidMng_InternalDidInfo( u1KindOfCheck, u1CheckElement, pt_InfoTbl );
                if( u1_RetDDDidInfo == (Std_ReturnType)E_OK )
                {
                    for( u1_SourceDidIndex = (uint8)0U; u1_SourceDidIndex < u1_NumOfSourceDid; u1_SourceDidIndex++ )
                    {
                        b_SupportedSourceElm = (boolean)FALSE;
                        b_ChkSrcElm = (boolean)FALSE;
                        u1_RetGetSourceDID = Dcm_Dsp_DidMng_GetSourceDID( u2_DDDidIndex, u1_SourceDidIndex, &st_SourceTable );
                        if( u1_RetGetSourceDID == (Std_ReturnType)E_OK )
                        {
                            if( st_SourceTable.u1SourceElementId == DCM_DSP_DIDMNG_SOURCEELEMENTID_DID )
                            {
                                if( b_Chk_Per_Source_Did == (boolean)TRUE )
                                {
                                    b_ChkSrcElm = (boolean)TRUE;
                                }
                            }
                            else if( st_SourceTable.u1SourceElementId == DCM_DSP_DIDMNG_SOURCEELEMENTID_MEMADDR )
                            {
                                b_ChkSrcElm = (boolean)TRUE;
                            }
                            else
                            {
                                /* No process */
                            }
                        }

                        if( b_ChkSrcElm == (boolean)TRUE )
                        {
                            if( st_SourceTable.u1SourceElementId == DCM_DSP_DIDMNG_SOURCEELEMENTID_DID )
                            {
                                u2_RangeDidIndex = (uint16)0U;
                                u1_RWSupport = (uint8)0x00U;
                                /* Get Index of DcmDspDidRangeTbl[] */
                                u1_RetDidRange = Dcm_Dsp_DidMng_BinarySearchDidRange( st_SourceTable.u2SourceDid, &u2_RangeDidIndex, &u1_RWSupport );
                                if( u1_RetDidRange == DCM_MAIN_E_CHECK_OK )
                                {
                                    pt_InfoTbl = DcmDspDidRangeTbl[u2_RangeDidIndex].ptInfoRef;
                                    /* Security/Session Check of SourceDID */
                                    u1_RetSourceDidInfo = Dcm_Dsp_DidMng_InternalDidInfo( u1KindOfCheck, u1CheckElement, pt_InfoTbl );
                                    if( u1_RetSourceDidInfo == (Std_ReturnType)E_OK )
                                    {
                                        b_SupportedSourceElm = (boolean)TRUE;
                                    }
                                }
                            }
                            else
                            {
                                /* Security/Session Check of SourceMemory */
                                u1_RetAddrInfo = Dcm_Dsp_DidMng_InternalAddrInfo( u1KindOfCheck, u1CheckElement, st_SourceTable.u1MemId, st_SourceTable.u4MemAddr );
                                if( u1_RetAddrInfo == (Std_ReturnType)E_OK )
                                {
                                    b_SupportedSourceElm = (boolean)TRUE;
                                }
                            }
                        }

                        if( b_SupportedSourceElm != (boolean)TRUE )
                        {
                            b_ClearDDDid = (boolean)TRUE;
                            break;
                        }
                    }
                }
                else
                {
                    b_ClearDDDid = (boolean)TRUE;
                }
            }
            else
            {
                b_ClearDDDid = (boolean)TRUE;
            }

            if( b_ClearDDDid == (boolean)TRUE )
            {
                /* Clear DDDID */
                (void)Dcm_Dsp_DidMng_ClrNumOfSrcElm( u2_DDDidIndex );
#if ( DCM_NVM_DDDID_USE == STD_ON )
                (void)Dcm_Dsp_DidMng_WriteStorage( DCM_DSP_DIDMNG_CLEAR, u2_DDDidIndex, (uint8)0U );
#endif /* DCM_NVM_DDDID_USE == STD_ON */
            }
        }
    }

    return ;
}
#endif /* DCM_SUPPORT_SID2C == ON */

#if ( ( DCM_PERIODIC_SEND_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_ChkDynamic                                */
/* Description   | Check DDDid                                              */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DDDid : Request Data Id                           */
/*               | [out] ptNumOfSourceDid : Number of elements              */
/*               | [out] ptDynamicIndex : Index of the DDDid                */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Request DID Normal                         */
/*               |        E_NOT_OK : Request DID error                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ChkDynamic
(
    const uint16 u2DDDid,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptNumOfSourceDid,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) ptDynamicIndex
)
{
    Std_ReturnType u1_RetVal;
    Std_ReturnType u1_FuncRet;

    u1_RetVal = E_NOT_OK;
    *ptNumOfSourceDid = (uint8)0U;

    u1_FuncRet = Dcm_Dsp_DidMng_GetDynamicIndex(u2DDDid, ptDynamicIndex);
    if( u1_FuncRet == (Std_ReturnType)E_OK )
    {
        u1_RetVal = Dcm_Dsp_DidMng_GetNumOfSrcDid(*ptDynamicIndex, ptNumOfSourceDid);
    }

    return u1_RetVal;
}
#endif /* DCM_PERIODIC_SEND_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON */


#if ( ( DCM_PERIODIC_SEND_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_CallModeRuleFnc                           */
/* Description   | Check ModeRule                                           */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DidIndex :Index of either of the following Tables */
/*               |                   DcmDspDidRangeTbl[], DcmDspDidTbl[]    */
/*               | [in] u1KindOfFnc : Kind of Func                          */
/*               | [in] u2DID       : Request Did                           */
/*               | [out] ptErrorCode : Negative Response Code               */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Process complete                           */
/*               |        E_NOT_OK : Process abnormal termination           */
/* Notes         | This function should be called only in                   */
/*               | that u1KindOfFnc is DCM_DSP_DIDMNG_CHECK_READ_MR         */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallModeRuleFnc
(
    const uint16 u2DidIndex,
    const uint8 u1KindOfFnc,
    const uint16 u2DID,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode
)
{
    Std_ReturnType u1_RetVal;
    uint16         u2_DidrangeT;
    P2CONST(AB_83_ConstV Dcm_Dsp_DidInfoType, AUTOMATIC, DCM_APPL_CONST) ptTargetInfoTbl;

    u1_RetVal = E_NOT_OK;
    u2_DidrangeT = Dcm_P_u2Didrange_T;
    *ptErrorCode = (uint8)0x00U;

    if( u1KindOfFnc == DCM_DSP_DIDMNG_CHECK_READ_MR )
    {
        if( u2DidIndex < u2_DidrangeT )
        {
            ptTargetInfoTbl = DcmDspDidRangeTbl[ u2DidIndex ].ptInfoRef;

            u1_RetVal = Dcm_Dsp_DidMng_InternalModeRule( u1KindOfFnc, ptTargetInfoTbl, u2DID, ptErrorCode );
        }
    }
    return u1_RetVal;
}
#endif /* DCM_PERIODIC_SEND_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON*/


#if ( ( DCM_PERIODIC_SEND_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_DynDidModeRuleFnc                         */
/* Description   | Check ModeRule by DDDID and SourceElement                */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DidIndex : Index of DcmDspDDDidTbl[]              */
/*               | [in] u1KindOfFnc : Kind of Func                          */
/*               | [out] ptErrorCode : Negative Response Code               */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Process complete                           */
/*               |        E_NOT_OK : Process abnormal termination           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_DynDidModeRuleFnc
(
    const uint16 u2DidIndex,
    const uint8 u1KindOfFnc,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode
)
{
    Std_ReturnType u1_RetVal;
    Std_ReturnType u1_RetDid;
    Std_ReturnType u1_RetModeRule;
    uint8 u1RWSupport;
    uint16 u2_DddidT;
    uint16 u2ReqDDDid;
    uint16 u2TargetIndex;
    P2CONST(AB_83_ConstV Dcm_Dsp_DidInfoType, AUTOMATIC, DCM_APPL_CONST) ptTargetInfoTbl;
    Dcm_NegativeResponseCodeType u1LocalErrorCode;

    u1_RetVal = E_NOT_OK;
    u2_DddidT = Dcm_P_u2Dddid_T;
    *ptErrorCode = (uint8)0x00U;

    if( u2DidIndex < u2_DddidT )
    {
        u2ReqDDDid = DcmDspDDDidTbl[ u2DidIndex ].u2DDDid;

        u1_RetDid = Dcm_Dsp_DidMng_ChkDid( u2ReqDDDid, DCM_DSP_DIDMNG_DID, &u2TargetIndex, &u1RWSupport );

        if( u1_RetDid == DCM_MAIN_E_CHECK_OK )
        {
            ptTargetInfoTbl = DcmDspDidTbl[ u2TargetIndex ].ptInfoRef;

            u1_RetModeRule = Dcm_Dsp_DidMng_InternalModeRule( u1KindOfFnc, ptTargetInfoTbl, u2ReqDDDid, &u1LocalErrorCode );

            if( u1_RetModeRule == (Std_ReturnType)E_OK )
            {
                u1_RetVal = Dcm_Dsp_DidMng_CallSDidModeRule( u2DidIndex, u1KindOfFnc, ptErrorCode );
            }
            else if( u1_RetModeRule == (Std_ReturnType)E_NOT_OK )
            {
                u1_RetVal = u1_RetModeRule;
                *ptErrorCode = u1LocalErrorCode;
            }
            else
            {
                u1_RetVal = u1_RetModeRule;
            }
        }
        /* In the case of else, E_NOT_OK has been already set by u1_RetVal. */
    }
    /* In the case of else, E_NOT_OK has been already set by u1_RetVal. */

    return u1_RetVal;
}
#endif /* DCM_PERIODIC_SEND_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON */



/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_Init                                      */
/* Description   | DidMng initialization                                    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON )
#if ( DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON )

FUNC( void, DCM_CODE ) Dcm_Dsp_DidMng_Init
(
    void
)
{
#if ( DCM_SUPPORT_SID22 == STD_ON )
    Dcm_Dsp_DidMng_u1LoopCnt = (uint8)0U;
    Dcm_Dsp_DidMng_bUserNotifyFlag = (boolean)FALSE;
    Dcm_Dsp_DidMng_bUserRcrrpFlag  = (boolean)FALSE;
    Dcm_Dsp_DidMng_bRemainData                  = (boolean)FALSE;
    Dcm_Dsp_DidMng_u1RemainIndex                = (uint8)0U;
    Dcm_Dsp_DidMng_bSetData                     = (boolean)FALSE;
    Dcm_Dsp_DidMng_u4UnsetIndex                 = (uint32)0U;
    Dcm_Dsp_DidMng_u4StoredDataLen              = (uint32)0U;
    Dcm_Dsp_DidMng_stSourceTable.u4MemAddr      = (uint32)0U;
    Dcm_Dsp_DidMng_stSourceTable.u4MemSize      = (uint32)0U;
    Dcm_Dsp_DidMng_stSourceTable.u2SourceDid    = (uint16)0U;
    Dcm_Dsp_DidMng_stSourceTable.u1Position     = (uint8)0U;
    Dcm_Dsp_DidMng_stSourceTable.u1Size         = (uint8)0U;
    Dcm_Dsp_DidMng_stSourceTable.u1MemId        = (uint8)0U;
    Dcm_Dsp_DidMng_stSourceTable.u1SourceElementId = DCM_DSP_DIDMNG_SOURCEELEMENTID_INVALID;
#endif /* DCM_SUPPORT_SID22 == STD_ON */
#if ( DCM_NVM_DDDID_USE == STD_ON )
    Dcm_Dsp_DidMng_Storage_Init();
#endif /* DCM_NVM_DDDID_USE == STD_ON */
#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID23 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
    (void)Dcm_Dsp_DidMng_ClrAllNumOfSrcElm(); /* no return check required */
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID23 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */
#if ( DCM_NVM_DDDID_USE == STD_ON )
    Dcm_Dsp_DidMng_InitSourceElementId();
#endif /* DCM_NVM_DDDID_USE == STD_ON */
#if ( DCM_PERIODIC_DDDID_USE == STD_ON )
    Dcm_Dsp_DidMng_Periodic_Init();
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON */
    return ;
}
#endif /* DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON */
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON */
#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_OFF )
#if ( DCM_PAGEDBUFFER_SID23_ENABLED == STD_OFF )

FUNC( void, DCM_CODE ) Dcm_Dsp_DidMng_Init
(
    void
)
{
#if ( DCM_SUPPORT_SID22 == STD_ON )
    Dcm_Dsp_DidMng_u1LoopCnt = (uint8)0U;
    Dcm_Dsp_DidMng_bUserNotifyFlag = (boolean)FALSE;
    Dcm_Dsp_DidMng_bUserRcrrpFlag  = (boolean)FALSE;
#endif /* DCM_SUPPORT_SID22 == STD_ON */
#if ( DCM_NVM_DDDID_USE == STD_ON )
    Dcm_Dsp_DidMng_Storage_Init();
#endif /* DCM_NVM_DDDID_USE == STD_ON */
#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID23 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
    (void)Dcm_Dsp_DidMng_ClrAllNumOfSrcElm(); /* no return check required */
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID23 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */
#if ( DCM_NVM_DDDID_USE == STD_ON )
    Dcm_Dsp_DidMng_InitSourceElementId();
#endif /* DCM_NVM_DDDID_USE == STD_ON */
#if ( DCM_PERIODIC_DDDID_USE == STD_ON )
    Dcm_Dsp_DidMng_Periodic_Init();
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON */
    return ;
}
#endif /* DCM_PAGEDBUFFER_SID23_ENABLED == STD_OFF */
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_OFF */




#if ( DCM_SUPPORT_SID2C == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_ChkSDidSize                               */
/* Description   | Check the Source Did data length                         */
/* Preconditions | None                                                     */
/* Parameters    | [in] u4DidDataLength : Source Did Data Length            */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Check OK                                   */
/*               |        E_NOT_OK : Check NG                               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ChkSDidSize   /* MISRA DEVIATION */
(
    const uint32 u4DidDataLength
)
{
    uint32         u4_SourceDidMaxDataSize;
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_NOT_OK;
    u4_SourceDidMaxDataSize = (uint32)Dcm_P_u2Source_Did_Max_Data_Size;

    if( u4DidDataLength <= u4_SourceDidMaxDataSize )
    {
        u1_RetVal = E_OK;
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID2C == ON */

#if ( DCM_SUPPORT_SID2F == STD_ON )
#if ( DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_GetTopSigType                             */
/* Description   | Get Signal Type for the request DID config               */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DidIndex : Index of DcmDspDidTbl[]                */
/*               | [out] ptDataType : Data type                             */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Process complete                           */
/*               |        E_NOT_OK : Process abnormal termination           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_GetTopSigType
(
    const uint16 u2DidIndex,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptDataType
)
{
    Std_ReturnType u1_RetVal;
    uint16         u2_DidT;

    u1_RetVal = E_NOT_OK;
    u2_DidT = Dcm_P_u2Did_T;

    if( u2DidIndex < u2_DidT )
    {
        if( DcmDspDidTbl[ u2DidIndex ].ptSignal != NULL_PTR )
        {
            if( DcmDspDidTbl[ u2DidIndex ].ptSignal[ 0 ].ptDataRef != NULL_PTR )
            {
                *ptDataType = DcmDspDidTbl[ u2DidIndex ].ptSignal[ 0 ].ptDataRef->u1Type;
                u1_RetVal = E_OK;
            }
        }
    }

    return u1_RetVal;
}
#endif /* DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON */
#endif /* DCM_SUPPORT_SID2F == STD_ON */

#if ( DCM_SUPPORT_SID2F == STD_ON )
#if ( DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_GetSigNum                                 */
/* Description   | Get total number of signal for the request DID config    */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DidIndex : Index of DcmDspDidTbl[]                */
/*               | [out] ptSignalNum : Total number of signal               */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Process complete                           */
/*               |        E_NOT_OK : Process abnormal termination           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_GetSigNum
(
    const uint16 u2DidIndex,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptSignalNum
)
{
    Std_ReturnType u1_RetVal;
    uint16         u2_DidT;

    u1_RetVal = E_NOT_OK;
    u2_DidT = Dcm_P_u2Did_T;

    if( u2DidIndex < u2_DidT )
    {
        *ptSignalNum = DcmDspDidTbl[ u2DidIndex ].u1SignalNum;
        u1_RetVal = E_OK;
    }

    return u1_RetVal;
}
#endif /* DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON */
#endif /* DCM_SUPPORT_SID2F == STD_ON */

#if ( DCM_SUPPORT_SID2F == STD_ON )
#if ( DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_GetAnySigPos                              */
/* Description   | Get signal position for the request DID config           */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DidIndex : Index of DcmDspDidTbl[]                */
/*               | [in] u1SignalIndex : Index of the Signal                 */
/*               | [out] ptDataPos : Data position                          */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Process complete                           */
/*               |        E_NOT_OK : Process abnormal termination           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_GetAnySigPos
(
    const uint16 u2DidIndex,
    const uint8 u1SignalIndex,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) ptDataPos
)
{
    Std_ReturnType u1_RetVal;
    uint16         u2_DidT;

    u1_RetVal = E_NOT_OK;
    u2_DidT = Dcm_P_u2Did_T;

    if( u2DidIndex < u2_DidT )
    {
        if( u1SignalIndex < DcmDspDidTbl[ u2DidIndex ].u1SignalNum )
        {
            if( DcmDspDidTbl[ u2DidIndex ].ptSignal != NULL_PTR )
            {
                *ptDataPos = DcmDspDidTbl[ u2DidIndex ].ptSignal[ u1SignalIndex ].u2DataPos;
                u1_RetVal = E_OK;
            }
        }
    }

    return u1_RetVal;
}
#endif /* DCM_SID2F_CONTROLMASK_AUBIST_USE == STD_ON */
#endif /* DCM_SUPPORT_SID2F == STD_ON */

#if ( DCM_SUPPORT_SID2C == STD_ON )
#if ( DCM_NVM_DDDID_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_GetReadStorageCompleteFlag                */
/* Description   | Get the ReadStorageCompleteFlag                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | boolean                                                  */
/*               | TRUE                                                     */
/*               | FALSE                                                    */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( boolean, DCM_CODE ) Dcm_Dsp_DidMng_GetReadStorageCompleteFlag
(
    void
)
{
    return ( Dcm_Dsp_DidMng_bReadStorageCompleteFlag );
}
#endif /* DCM_NVM_DDDID_USE == STD_ON */
#endif /* DCM_SUPPORT_SID2C == STD_ON */

#if ( DCM_NVM_DDDID_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_SetDataStorage2Mirror                     */
/* Description   | Storage to Mirror                                        */
/* Preconditions | None                                                     */
/* Parameters    |  [in] u2BlockIdx : Block Index                           */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE) Dcm_Dsp_DidMng_SetDataStorage2Mirror
(
    const uint16 u2BlockIdx
)
{
    P2VAR(Dcm_Dsp_StorageBlockType, AUTOMATIC, DCM_APPL_DATA) pt_DataNOSE_Src;
    P2VAR(AB_83_ConstV Dcm_Dsp_SourceElementType, AUTOMATIC, DCM_APPL_DATA) pt_DataSRCINFO_Src;
    Dcm_Dsp_SourceElementType st_DataSRCINFO_Dest;
    uint16 u2_DDDid_BlockIdx;
    uint16 u2_CvtTblIdx;
    uint16 u2_DDDidTblIdx;
    uint16 u2_StorageDDDidNum;
    uint16 u2_BIdxStaNose;
    uint16 u2_BIdxEndNose;
    uint16 u2_BIdxStaSrcInf;
    uint16 u2_BIdxEndSrcInf;
    uint16 u2_NOSEBlockSize;
    uint16 u2_Cnt;
    uint8  u1_DDDidElementIdx;

    u2_StorageDDDidNum = Dcm_P_u2StorageDDDIDNum;
    u2_BIdxStaNose = Dcm_Dsp_StorageMng_u2BIdx_StaNose;
    u2_BIdxEndNose = Dcm_Dsp_StorageMng_u2BIdx_EndNose;
    u2_BIdxStaSrcInf = Dcm_Dsp_StorageMng_u2BIdx_StaSrcInf;
    u2_BIdxEndSrcInf = Dcm_Dsp_StorageMng_u2BIdx_EndSrcInf;
    u2_NOSEBlockSize = Dcm_P_u2Source_NOSE_Block_Size;

    if( u2_StorageDDDidNum > (uint16)0x0000U )
    {
        if( ( u2_BIdxStaNose <= u2BlockIdx ) && ( u2BlockIdx <= u2_BIdxEndNose ) )
        {
            /* Convert For DDDID Scope */
            u2_DDDid_BlockIdx = u2BlockIdx - u2_BIdxStaNose;

            /* Get Dest */
            pt_DataNOSE_Src = &DcmDspStorageDDDidNumOfSourceElement[u2_DDDid_BlockIdx]; 

            /* Get Src and Set SrctoDest */
            for( u2_Cnt = (uint16)0U; u2_Cnt < u2_NOSEBlockSize; u2_Cnt++ )
            {
                u2_CvtTblIdx  = (( u2_DDDid_BlockIdx * u2_NOSEBlockSize ) + u2_Cnt);
                if( u2_CvtTblIdx < u2_StorageDDDidNum )
                {
                    u2_DDDidTblIdx  = DcmDspCvtStorageIdx2MirrorIdxNOSE[u2_CvtTblIdx];
                    (void)Dcm_Dsp_DidMng_SetNumOfSrcDid(u2_DDDidTblIdx, pt_DataNOSE_Src->u1Data[u2_Cnt]);
                }
            }
        }
        else if( ( u2_BIdxStaSrcInf <= u2BlockIdx ) && ( u2BlockIdx <= u2_BIdxEndSrcInf ) )
        {
            /* Convert For DDDID Scope */
            u2_DDDid_BlockIdx = u2BlockIdx - u2_BIdxStaSrcInf;

            /* Get Src */
            pt_DataSRCINFO_Src   = DcmDspStorageDDDidTbl[u2_DDDid_BlockIdx];

            /* Set SrctoDest*/
            st_DataSRCINFO_Dest.u4MemAddr          = pt_DataSRCINFO_Src->u4MemAddr;
            st_DataSRCINFO_Dest.u4MemSize          = pt_DataSRCINFO_Src->u4MemSize;
            st_DataSRCINFO_Dest.u2SourceDid        = pt_DataSRCINFO_Src->u2SourceDid;
            st_DataSRCINFO_Dest.u1Position         = pt_DataSRCINFO_Src->u1Position;
            st_DataSRCINFO_Dest.u1Size             = pt_DataSRCINFO_Src->u1Size;
            st_DataSRCINFO_Dest.u1MemId            = pt_DataSRCINFO_Src->u1MemId;
            st_DataSRCINFO_Dest.u1SourceElementId  = pt_DataSRCINFO_Src->u1SourceElementId;

            /* Set Dest */
            u2_DDDidTblIdx      = DcmDspCvtStorageIdx2MirrorIdxDIDDATA[u2_DDDid_BlockIdx];
            u1_DDDidElementIdx  = DcmDspCvtStorageIdx2MirrorIdxSRCDIDELEMENT[u2_DDDid_BlockIdx];
            (void)Dcm_Dsp_DidMng_SetSourceDID(u2_DDDidTblIdx, u1_DDDidElementIdx, &st_DataSRCINFO_Dest);
        }
        else
        {
            /* no proc */
        }
    }

    return ;
}
#endif /* DCM_NVM_DDDID_USE == STD_ON */

#if ( DCM_NVM_DDDID_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_SetDataMirror2Storage                     */
/* Description   | Mirror to Storage                                        */
/* Preconditions | None                                                     */
/* Parameters    |  [in] u2BlockIdx : Block Index                           */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE) Dcm_Dsp_DidMng_SetDataMirror2Storage
(
    const uint16 u2BlockIdx
)
{
    P2VAR(Dcm_Dsp_StorageBlockType, AUTOMATIC, DCM_APPL_DATA) pt_DataNOSE_Dest;
    P2VAR(AB_83_ConstV Dcm_Dsp_SourceElementType, AUTOMATIC, DCM_APPL_DATA) pt_DataSRCINFO_Dest;
    Dcm_Dsp_SourceElementType st_DataSRCINFO_Src;
    uint16 u2_DDDid_BlockIdx;
    uint16 u2_CvtTblIdx;
    uint16 u2_DDDidTblIdx;
    uint16 u2_StorageDDDidNum;
    uint16 u2_BIdxStaNose;
    uint16 u2_BIdxEndNose;
    uint16 u2_BIdxStaSrcInf;
    uint16 u2_BIdxEndSrcInf;
    uint16 u2_NOSEBlockSize;
    uint16 u2_Cnt;
    uint8  u1_DDDidElementIdx;
    uint8  u1_NumOfSourceDid;

    u1_NumOfSourceDid = (uint8)0x00U;
    u2_StorageDDDidNum = Dcm_P_u2StorageDDDIDNum;
    u2_BIdxStaNose = Dcm_Dsp_StorageMng_u2BIdx_StaNose;
    u2_BIdxEndNose = Dcm_Dsp_StorageMng_u2BIdx_EndNose;
    u2_BIdxStaSrcInf = Dcm_Dsp_StorageMng_u2BIdx_StaSrcInf;
    u2_BIdxEndSrcInf = Dcm_Dsp_StorageMng_u2BIdx_EndSrcInf;
    u2_NOSEBlockSize = Dcm_P_u2Source_NOSE_Block_Size;

    if( ( u2_BIdxStaNose <= u2BlockIdx ) && ( u2BlockIdx <= u2_BIdxEndNose ) )
    {
        /* Convert For DDDID Scope */
        u2_DDDid_BlockIdx = u2BlockIdx - u2_BIdxStaNose;

        /* Get Dest */
        pt_DataNOSE_Dest = &DcmDspStorageDDDidNumOfSourceElement[u2_DDDid_BlockIdx];

        /* Get Src  and Set SrctoDest */
        for( u2_Cnt = (uint16)0U; u2_Cnt < u2_NOSEBlockSize; u2_Cnt++ )
        {
            u2_CvtTblIdx  = ((u2_DDDid_BlockIdx * u2_NOSEBlockSize) + u2_Cnt);
            if( u2_CvtTblIdx < u2_StorageDDDidNum )
            {
                u2_DDDidTblIdx  = DcmDspCvtStorageIdx2MirrorIdxNOSE[u2_CvtTblIdx];
                (void)Dcm_Dsp_DidMng_GetNumOfSrcDid(u2_DDDidTblIdx, &u1_NumOfSourceDid);
                pt_DataNOSE_Dest->u1Data[u2_Cnt] = u1_NumOfSourceDid;
            }
            else
            {
                pt_DataNOSE_Dest->u1Data[u2_Cnt] = (uint8)0x00U;
            }
        }
    }
    else if( ( u2_BIdxStaSrcInf <= u2BlockIdx ) && ( u2BlockIdx <= u2_BIdxEndSrcInf ) )
    {
        /* Convert For DDDID Scope */
        u2_DDDid_BlockIdx = u2BlockIdx - u2_BIdxStaSrcInf;

        /* Get Dest */
        pt_DataSRCINFO_Dest   = DcmDspStorageDDDidTbl[u2_DDDid_BlockIdx];

        /* Get Src */
        u2_DDDidTblIdx       = DcmDspCvtStorageIdx2MirrorIdxDIDDATA[u2_DDDid_BlockIdx];
        u1_DDDidElementIdx  = DcmDspCvtStorageIdx2MirrorIdxSRCDIDELEMENT[u2_DDDid_BlockIdx];
        (void)Dcm_Dsp_DidMng_GetSourceDID(u2_DDDidTblIdx, u1_DDDidElementIdx, &st_DataSRCINFO_Src);

        /* Set SrctoDest*/
        pt_DataSRCINFO_Dest->u4MemAddr          = st_DataSRCINFO_Src.u4MemAddr;
        pt_DataSRCINFO_Dest->u4MemSize          = st_DataSRCINFO_Src.u4MemSize;
        pt_DataSRCINFO_Dest->u2SourceDid        = st_DataSRCINFO_Src.u2SourceDid;
        pt_DataSRCINFO_Dest->u1Position         = st_DataSRCINFO_Src.u1Position;
        pt_DataSRCINFO_Dest->u1Size             = st_DataSRCINFO_Src.u1Size;
        pt_DataSRCINFO_Dest->u1MemId            = st_DataSRCINFO_Src.u1MemId;
        pt_DataSRCINFO_Dest->u1SourceElementId  = st_DataSRCINFO_Src.u1SourceElementId;
    }
    else
    {
        /* no proc */
    }

    return ;
}
#endif /* DCM_NVM_DDDID_USE == STD_ON */

#if ( DCM_NVM_DDDID_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_ReadConfirmation                          */
/* Description   | Read Storage Confirmation                                */
/* Preconditions | None                                                     */
/* Parameters    |  [in] u2BlockIdx : Block Index                           */
/*               |  [in] u1Result : Read Storage Result                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE) Dcm_Dsp_DidMng_ReadConfirmation
(
    const uint16 u2BlockIdx,      /* MISRA DEVIATION */
    const uint8  u1Result
)
{
    if( u1Result == (uint8)E_NOT_OK )
    {
        (void)Dcm_Dsp_DidMng_ClrAllNumOfSrcElm();
    }

    Dcm_Dsp_DidMng_bReadStorageCompleteFlag = (boolean)TRUE;

    return;
}
#endif /* DCM_NVM_DDDID_USE == STD_ON */

#if ( DCM_NVM_DDDID_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_Refresh                                   */
/* Description   | DidMng Refresh processing                                */
/* Preconditions | None                                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_DidMng_Refresh            /* MISRA DEVIATION */
(
    void
)
{
    boolean   b_ReadStorageCompleteFlag;
    P2VAR(volatile boolean, AUTOMATIC, DCM_APPL_DATA) pt_ReadStorageCompleteFlag;

    pt_ReadStorageCompleteFlag  = &Dcm_Dsp_DidMng_bReadStorageCompleteFlag;
    b_ReadStorageCompleteFlag   = *pt_ReadStorageCompleteFlag;
    *pt_ReadStorageCompleteFlag = b_ReadStorageCompleteFlag ;

    return;
}
#endif /* DCM_NVM_DDDID_USE == STD_ON */

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


#if ( DCM_NVM_DDDID_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_Storage_Init                              */
/* Description   | DidMng initialization(About NvM)                         */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_DidMng_Storage_Init
(
    void
)
{
    /* Set to False to wait for NvM to reflect */
    Dcm_Dsp_DidMng_bReadStorageCompleteFlag = (boolean)FALSE;

    return ;
}
#endif /* DCM_NVM_DDDID_USE == STD_ON */

#if ( DCM_PERIODIC_DDDID_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_Periodic_Init                             */
/* Description   | DidMng initialization(for Periodic)                      */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_DidMng_Periodic_Init
(
    void
)
{
    Dcm_Dsp_DidMng_u1LoopCntForPeriodic = (uint8)0U;
    Dcm_Dsp_DidMng_u1NumOfSrcDidForPeriodic = (uint8)0U;

    return ;
}
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON */

#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_ChkSDidInfo                               */
/* Description   | Security/Session Check of the Source Did                 */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DDDidIndex : Index of DcmDspDDDidTbl[]            */
/*               | [in] u1KindOfCheck : Kind of Check                       */
/*               | [in] u1CheckElement : SecLevel/SesLevel                  */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Check OK                                   */
/*               |        E_NOT_OK : Check not OK                           */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ChkSDidInfo
(
    const uint16 u2DDDidIndex,
    const uint8 u1KindOfCheck,
    const uint8 u1CheckElement
)
{
    P2CONST(AB_83_ConstV Dcm_Dsp_DidInfoType, AUTOMATIC, DCM_APPL_CONST) pt_InfoTbl;
    Std_ReturnType u1_RetVal;
    Std_ReturnType u1_RetGetNumOfSrcDid;
    Std_ReturnType u1_RetGetSourceDID;
    Std_ReturnType u1_RetDidRange;
    Std_ReturnType u1_RetChkSourceDid;
    Std_ReturnType u1_RetAddrInfo;
    uint8 u1_cnt;
    uint8 u1NumOfSourceDid;
    uint16 u2TargetIndex;
    uint8 u1RWSupport;
    boolean b_BreakFlag;
    Dcm_Dsp_SourceElementType stSourceTable;
    boolean b_Chk_Per_Source_Did;
    boolean b_ChkSrcElm;

    u1_RetVal = E_OK;
    b_BreakFlag = (boolean)FALSE;
    b_Chk_Per_Source_Did = Dcm_P_DIDMNG_bChk_Per_Source_Did;

    u1_RetGetNumOfSrcDid = Dcm_Dsp_DidMng_GetNumOfSrcDid( u2DDDidIndex, &u1NumOfSourceDid );
    if( u1_RetGetNumOfSrcDid == (Std_ReturnType)E_OK )
    {
        if( u1NumOfSourceDid > (uint8)0x00U )
        {
            for( u1_cnt = (uint8)0U; u1_cnt < u1NumOfSourceDid; u1_cnt++ )
            {
                b_ChkSrcElm = (boolean)FALSE;
                u1_RetGetSourceDID = Dcm_Dsp_DidMng_GetSourceDID( u2DDDidIndex, u1_cnt, &stSourceTable );
                if( u1_RetGetSourceDID == (Std_ReturnType)E_OK )
                {
                    if( stSourceTable.u1SourceElementId == DCM_DSP_DIDMNG_SOURCEELEMENTID_DID )
                    {
                        if( b_Chk_Per_Source_Did == (boolean)TRUE )
                        {
                            b_ChkSrcElm = (boolean)TRUE;
                        }
                    }
                    else if( stSourceTable.u1SourceElementId == DCM_DSP_DIDMNG_SOURCEELEMENTID_MEMADDR )
                    {
                        b_ChkSrcElm = (boolean)TRUE;
                    }
                    else
                    {
                        u1_RetVal = E_NOT_OK;
                        b_BreakFlag = (boolean)TRUE;
                    }
                }
                else
                {
                    u1_RetVal = E_NOT_OK;
                    b_BreakFlag = (boolean)TRUE;
                }

                if( b_ChkSrcElm == (boolean)TRUE )
                {
                    if( stSourceTable.u1SourceElementId == DCM_DSP_DIDMNG_SOURCEELEMENTID_DID )
                    {
                        u1_RetDidRange = Dcm_Dsp_DidMng_ChkDid( stSourceTable.u2SourceDid, DCM_DSP_DIDMNG_DID_RANGE, &u2TargetIndex, &u1RWSupport );
                        if( u1_RetDidRange == DCM_MAIN_E_CHECK_OK )
                        {
                            pt_InfoTbl = DcmDspDidRangeTbl[u2TargetIndex].ptInfoRef;
                            u1_RetChkSourceDid = Dcm_Dsp_DidMng_InternalDidInfo( u1KindOfCheck, u1CheckElement, pt_InfoTbl );
                            if( u1_RetChkSourceDid != (Std_ReturnType)E_OK )
                            {
                                u1_RetVal = E_NOT_OK;
                                b_BreakFlag = (boolean)TRUE;
                            }
                        }
                        else
                        {
                            u1_RetVal = E_NOT_OK;
                            b_BreakFlag = (boolean)TRUE;
                        }
                    }
                    else
                    {
                        /*  if( stSourceTable.u1SourceElementId == DCM_DSP_DIDMNG_SOURCEELEMENTID_MEMADDR ) */
                        u1_RetAddrInfo = Dcm_Dsp_DidMng_InternalAddrInfo( u1KindOfCheck, u1CheckElement, stSourceTable.u1MemId, stSourceTable.u4MemAddr );
                        if( u1_RetAddrInfo != (Std_ReturnType)E_OK )
                        {
                            u1_RetVal = E_NOT_OK;
                            b_BreakFlag = (boolean)TRUE;
                        }
                    }
                }

                if( b_BreakFlag == (boolean)TRUE )
                {
                    break;
                }
            }
        }
        else
        {
            u1_RetVal = E_NOT_OK;
        }
    }
    else
    {
        u1_RetVal = E_NOT_OK;
    }

    return u1_RetVal;
}
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */

#if ( DCM_SUPPORT_SID22 == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_CallSDidRead                              */
/* Description   | Call Read Function of the Source Did                     */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DDDidIndex : Index of DcmDspDDDidTbl[]              */
/*               | [in] u1NumOfSourceDid : Num Of Soure Did                 */
/*               | [out] ptData : Res Data Buffer                           */
/*               | [out] ptDataLength : Res Data Length                     */
/*               | [in]  u4DataBufferLength : Send Buffer Length            */
/*               | [out] ptErrorCode : Negative Response Code               */
/*               | [in/out] ptLoopCntMax : Max Loop Num of a Cycle          */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Check OK                                   */
/*               |        E_NOT_OK : Check not OK                           */
/*               |        DCM_E_PENDING : Process pending                   */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON )
#if ( DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallSDidRead
(
    const uint16 u2DDDidIndex,
    const uint8 u1NumOfSourceDid,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptData,
    const uint32 u4DataBufferLength,
    P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) ptDataLength,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) ptLoopCntMax
)
{
    Std_ReturnType u1_RetVal;
    Std_ReturnType u1_RetGetSourceDID;
    Std_ReturnType u1_RetReadFnc;
    Std_ReturnType u1_RetSetSourceFnc;
    Std_ReturnType u1_RetSetRemainFnc;
    uint8 u1_cnt;
    boolean b_BreakFlag;
    Dcm_Dsp_SourceElementType stSourceTable;
    Dcm_OpStatusType u1OpStatusTmp;
    Dcm_NegativeResponseCodeType u1LocalErrorCode;
    boolean b_SkipFlag;

    u1_RetVal = E_NOT_OK;
    *ptErrorCode = (uint8)0U;
    b_BreakFlag = (boolean)FALSE;
    b_SkipFlag  = (boolean)FALSE;

    if( Dcm_Dsp_DidMng_bRemainData == (boolean)TRUE )
    {
        u1_RetSetRemainFnc = Dcm_Dsp_DidMng_SetRemainSourceDidData( u4DataBufferLength, ptDataLength, ptData );
        if( u1_RetSetRemainFnc == (Std_ReturnType)E_OK )
        {
            u1_RetVal = E_OK;
        }
        else
        {
            u1_RetVal   = u1_RetSetRemainFnc;
            b_SkipFlag  = (boolean)TRUE;
        }
    }

    if( b_SkipFlag != (boolean)TRUE )
    {
        if( Dcm_Dsp_DidMng_bUserNotifyFlag == (boolean)TRUE )
        {
            if( Dcm_Dsp_DidMng_bUserRcrrpFlag == (boolean)TRUE )
            {
                u1OpStatusTmp = DCM_FORCE_RCRRP_OK;
            }
            else
            {
                u1OpStatusTmp = DCM_PENDING;
                if( Dcm_Dsp_DidMng_bSetData == (boolean)TRUE )
                {
                    Dcm_Dsp_DidMng_bSetData = (boolean)FALSE;
                    u1OpStatusTmp           = DCM_UPDATE_PAGE_OK;
                }
            }
        }
        else
        {
            u1OpStatusTmp = DCM_INITIAL;
            Dcm_Dsp_DidMng_bRemainData                     = (boolean)FALSE;
            Dcm_Dsp_DidMng_u1RemainIndex                   = 0U;
            Dcm_Dsp_DidMng_bSetData                        = (boolean)FALSE;
            Dcm_Dsp_DidMng_u4UnsetIndex                    = 0U;
            Dcm_Dsp_DidMng_u4StoredDataLen                 = 0U;
            Dcm_Dsp_DidMng_stSourceTable.u4MemAddr         = 0U;
            Dcm_Dsp_DidMng_stSourceTable.u4MemSize         = 0U;
            Dcm_Dsp_DidMng_stSourceTable.u2SourceDid       = 0U;
            Dcm_Dsp_DidMng_stSourceTable.u1Position        = 0U;
            Dcm_Dsp_DidMng_stSourceTable.u1Size            = 0U;
            Dcm_Dsp_DidMng_stSourceTable.u1MemId           = 0U;
            Dcm_Dsp_DidMng_stSourceTable.u1SourceElementId = DCM_DSP_DIDMNG_SOURCEELEMENTID_INVALID;
        }
        /* Initialize RAM-Data Before Each Source DID Reading */
        Dcm_Dsp_DidMng_bUserNotifyFlag  = (boolean)FALSE;
        Dcm_Dsp_DidMng_bUserRcrrpFlag   = (boolean)FALSE;

        for( u1_cnt = Dcm_Dsp_DidMng_u1LoopCnt; u1_cnt < u1NumOfSourceDid; u1_cnt++ )
        {
            u1_RetGetSourceDID  = Dcm_Dsp_DidMng_GetSourceDID( u2DDDidIndex, u1_cnt, &stSourceTable );
            if( u1_RetGetSourceDID == (Std_ReturnType)E_OK )
            {

                u1LocalErrorCode    = (uint8)0U;
                u1_RetReadFnc       = Dcm_Dsp_DidMng_ReadElemData( &stSourceTable, u1OpStatusTmp, u4DataBufferLength, ptData, ptDataLength, &u1LocalErrorCode );

                if( u1_RetReadFnc == (Std_ReturnType)E_OK )
                {
                    u1OpStatusTmp = DCM_INITIAL;
                    (*ptLoopCntMax) = (uint16)((*ptLoopCntMax) - (uint16)1U);
                    u1_RetSetSourceFnc = Dcm_Dsp_DidMng_SetSourceDidData( u1_cnt, &stSourceTable, u4DataBufferLength, ptData, ptDataLength );
                    if ( u1_RetSetSourceFnc == (Std_ReturnType)E_OK )
                    {
                        u1_RetVal   = Dcm_Dsp_DidMng_InternalPending( u1_cnt, u1NumOfSourceDid, *ptLoopCntMax, &b_BreakFlag );
                        /* If u1_RetVal equal DCM_E_PENDING, Dcm_Dsp_DidMng_u1LoopCnt is set by Dcm_Dsp_DidMng_InternalPending() */
                    }
                    else if( u1_RetSetSourceFnc == (Std_ReturnType)DCM_E_PENDING )
                    {
                        /* Dcm_Dsp_DidMng_bRemainData is set by Dcm_Dsp_DidMng_SetSourceDidData() */
                        u1_RetVal   = DCM_E_PENDING;
                        b_BreakFlag = (boolean)TRUE;
                    }
                    else
                    {
                        u1_RetVal   = E_NOT_OK;
                        b_BreakFlag = (boolean)TRUE;
                    }
                }
                else if( u1_RetReadFnc == (Std_ReturnType)DCM_E_PENDING )
                {
                    Dcm_Dsp_DidMng_bUserNotifyFlag = (boolean)TRUE;
                    u1_RetVal = u1_RetReadFnc;
                    Dcm_Dsp_DidMng_u1LoopCnt = u1_cnt;
                    b_BreakFlag = (boolean)TRUE;
                }
                else if( u1_RetReadFnc == (Std_ReturnType)DCM_E_UPDATE_PAGE )
                {
                    Dcm_Dsp_DidMng_bSetData     = (boolean)TRUE;
                    Dcm_Dsp_DidMng_bUserNotifyFlag = (boolean)TRUE;
                    u1_RetVal = DCM_E_PENDING;
                    Dcm_Dsp_DidMng_u1LoopCnt = u1_cnt;
                    b_BreakFlag = (boolean)TRUE;
                }
                else if( u1_RetReadFnc == (Std_ReturnType)DCM_E_FORCE_RCRRP )
                {
                    Dcm_Dsp_DidMng_bUserNotifyFlag  = (boolean)TRUE;
                    Dcm_Dsp_DidMng_bUserRcrrpFlag   = (boolean)TRUE;
                    u1_RetVal   = u1_RetReadFnc;
                    Dcm_Dsp_DidMng_u1LoopCnt = u1_cnt;
                    b_BreakFlag = (boolean)TRUE;
                }
                else
                {
                    /*  if( u1_RetReadFnc == (Std_ReturnType)E_NOT_OK ) */
                    *ptErrorCode = u1LocalErrorCode;
                    u1_RetVal = u1_RetReadFnc;
                    b_BreakFlag = (boolean)TRUE;
                }
            }
            else
            {
                u1_RetVal = E_NOT_OK;
                b_BreakFlag = (boolean)TRUE;
            }

            if( b_BreakFlag == (boolean)TRUE )
            {
                break;
            }
        }
    }
    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON */
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON */
#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_OFF )
#if ( DCM_PAGEDBUFFER_SID23_ENABLED == STD_OFF )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallSDidRead
(
    const uint16 u2DDDidIndex,
    const uint8 u1NumOfSourceDid,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptData,
    const uint32 u4DataBufferLength,
    P2VAR (uint32, AUTOMATIC, DCM_APPL_DATA) ptDataLength,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) ptLoopCntMax
)
{
    Std_ReturnType u1_RetVal;
    Std_ReturnType u1_RetGetSourceDID;
    Std_ReturnType u1_RetReadFnc;
    uint8 u1_cnt;
    boolean b_BreakFlag;
    Dcm_Dsp_SourceElementType stSourceTable;
    Dcm_OpStatusType u1OpStatusTmp;
    Dcm_NegativeResponseCodeType u1LocalErrorCode;

    u1_RetVal = E_NOT_OK;
    *ptErrorCode = (uint8)0U;
    b_BreakFlag = (boolean)FALSE;

    if( Dcm_Dsp_DidMng_bUserNotifyFlag == (boolean)TRUE )
    {
        if( Dcm_Dsp_DidMng_bUserRcrrpFlag == (boolean)TRUE )
        {
            u1OpStatusTmp = DCM_FORCE_RCRRP_OK;
        }
        else
        {
            u1OpStatusTmp = DCM_PENDING;
        }
    }
    else
    {
        u1OpStatusTmp = DCM_INITIAL;
    }

    Dcm_Dsp_DidMng_bUserNotifyFlag  = (boolean)FALSE;
    Dcm_Dsp_DidMng_bUserRcrrpFlag   = (boolean)FALSE;

    for( u1_cnt = Dcm_Dsp_DidMng_u1LoopCnt; u1_cnt < u1NumOfSourceDid; u1_cnt++ )
    {
        u1_RetGetSourceDID = Dcm_Dsp_DidMng_GetSourceDID( u2DDDidIndex, u1_cnt, &stSourceTable );
        if( u1_RetGetSourceDID == (Std_ReturnType)E_OK )
        {

            u1LocalErrorCode = (uint8)0U;
            u1_RetReadFnc = Dcm_Dsp_DidMng_ReadElemData( &stSourceTable, u1OpStatusTmp, u4DataBufferLength, ptData, ptDataLength, &u1LocalErrorCode );

            if( u1_RetReadFnc == (Std_ReturnType)E_OK )
            {
                u1OpStatusTmp   = DCM_INITIAL;
                (*ptLoopCntMax) = (uint16)((*ptLoopCntMax) - (uint16)1U);

                u1_RetVal = Dcm_Dsp_DidMng_InternalPending( u1_cnt, u1NumOfSourceDid, *ptLoopCntMax, &b_BreakFlag );
            }
            else if( u1_RetReadFnc == (Std_ReturnType)DCM_E_PENDING )
            {
                Dcm_Dsp_DidMng_bUserNotifyFlag = (boolean)TRUE;
                u1_RetVal       = DCM_E_PENDING;
                Dcm_Dsp_DidMng_u1LoopCnt = u1_cnt;
                b_BreakFlag     = (boolean)TRUE;
            }
            else if( u1_RetReadFnc == (Std_ReturnType)DCM_E_FORCE_RCRRP )
            {
                Dcm_Dsp_DidMng_bUserNotifyFlag  = (boolean)TRUE;
                Dcm_Dsp_DidMng_bUserRcrrpFlag   = (boolean)TRUE;
                u1_RetVal       = DCM_E_FORCE_RCRRP;
                Dcm_Dsp_DidMng_u1LoopCnt = u1_cnt;
                b_BreakFlag     = (boolean)TRUE;
            }
            else
            {
                /* if( u1_RetReadFnc == (Std_ReturnType)E_NOT_OK ) */
                *ptErrorCode    = u1LocalErrorCode;
                u1_RetVal       = E_NOT_OK;
                b_BreakFlag     = (boolean)TRUE;
            }

        }
        else
        {
            u1_RetVal   = E_NOT_OK;
            b_BreakFlag = (boolean)TRUE;
        }
        if( b_BreakFlag == (boolean)TRUE )
        {
            break;
        }
    }

    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID23_ENABLED == STD_OFF */
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_OFF */
#endif /* DCM_SUPPORT_SID22 == STD_ON */


#if ( DCM_PERIODIC_DDDID_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_CallSDidReadForPeriodic                   */
/* Description   | Call Read Function of the Source Did                     */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DDDidIndex : Index of DcmDspDDDidTbl[]            */
/*               | [in] u1OpStatus : Operation state                        */
/*               | [in]  u4DataBufferLength : Send Buffer Length            */
/*               | [out] ptData : Res Data Buffer                           */
/*               | [out] ptDataLength : Res Data Length                     */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Check OK                                   */
/*               |        E_NOT_OK : Check not OK                           */
/*               |        DCM_E_PENDING : Process pending                   */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallSDidReadForPeriodic
(
    const uint16 u2DDDidIndex,
    const Dcm_OpStatusType u1OpStatus,
    const uint32 u4DataBufferLength,
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA) ptData,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA) ptDataLength
)
{
    Dcm_Dsp_SourceElementType    stSourceTable;
    uint8                        u1_NumOfSourceDid;
    uint8                        u1_cnt;
    Std_ReturnType               u1_RetVal;
    Std_ReturnType               u1_RetGetSourceDID;
    Std_ReturnType               u1_RetReadFnc;
    Dcm_OpStatusType             u1OpStatusTmp;
    boolean                      b_BreakFlag;

    u1_RetVal     = E_NOT_OK;
    b_BreakFlag   = (boolean)FALSE;
    u1_NumOfSourceDid = Dcm_Dsp_DidMng_u1NumOfSrcDidForPeriodic;
    u1OpStatusTmp = u1OpStatus;

    for( u1_cnt = Dcm_Dsp_DidMng_u1LoopCntForPeriodic; u1_cnt < u1_NumOfSourceDid; u1_cnt++ )
    {
        u1_RetGetSourceDID = Dcm_Dsp_DidMng_GetSourceDID( u2DDDidIndex, u1_cnt, &stSourceTable );
        if( u1_RetGetSourceDID == (Std_ReturnType)E_OK )
        {

            u1_RetReadFnc = Dcm_Dsp_DidMng_ReadElemDataForPeriodic( &stSourceTable, u1OpStatusTmp, u4DataBufferLength, ptData, ptDataLength );

            if( u1_RetReadFnc == (Std_ReturnType)E_OK )
            {
                u1_RetVal       = E_OK;
                u1OpStatusTmp   = DCM_PERIODIC_INITIAL;
            }
            else if( u1_RetReadFnc == (Std_ReturnType)DCM_E_PENDING )
            {
                u1_RetVal       = DCM_E_PENDING;
                Dcm_Dsp_DidMng_u1LoopCntForPeriodic = u1_cnt;
                b_BreakFlag     = (boolean)TRUE;
            }
            else
            {
                u1_RetVal       = E_NOT_OK;
                b_BreakFlag     = (boolean)TRUE;
            }

        }
        else
        {
            u1_RetVal   = E_NOT_OK;
            b_BreakFlag = (boolean)TRUE;
        }
        if( b_BreakFlag == (boolean)TRUE )
        {
            break;
        }
    }

    return u1_RetVal;
}
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON */


#if ( DCM_SUPPORT_SID22 == STD_ON )
#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON )
#if ( DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_ReadElemData                              */
/* Description   | Read Source Element Data                                 */
/* Preconditions | None                                                     */
/* Parameters    | [in] ptSourceTable : SourceElement structure Table       */
/*               | [in] u1OpStatus : Operation state                        */
/*               | [out] ptDataLength : Read Data Length                    */
/*               | [out] ptErrorCode : Negative Response Code               */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Process complete                           */
/*               |        E_NOT_OK : Process abnormal termination           */
/*               |        DCM_E_PENDING : Process pending                   */
/*               |        DCM_E_FORCE_RCRRP : Force Process pending         */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ReadElemData
(
    P2CONST(Dcm_Dsp_SourceElementType, AUTOMATIC, DCM_APPL_DATA)    ptSourceTable,
    const Dcm_OpStatusType                                          u1OpStatus,
    const uint32                                                    u4DataBufferLength,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)                          ptData,
    P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA)                         ptDataLength,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA)   ptErrorCode
)
{
    Std_ReturnType  u1_RetVal;
    Std_ReturnType  u1_RetDidRange;
    Std_ReturnType  u1_RetReadFnc;
    uint8           u1_RWSupport;
    uint16          u2_TargetIndex;
    uint32          u4_SDidBuffLen;
    uint32          u4_ReadLen;
    Dcm_NegativeResponseCodeType u1_LocalErrorCode;


    *ptErrorCode    = (Dcm_NegativeResponseCodeType)0U;
    u1_RetVal       = (Std_ReturnType)E_NOT_OK;
    u4_ReadLen      = (uint32)0U;
    u1_LocalErrorCode = (Dcm_NegativeResponseCodeType)0U;

    if( ptSourceTable->u1SourceElementId == DCM_DSP_DIDMNG_SOURCEELEMENTID_DID )
    {
        u1_RetDidRange = Dcm_Dsp_DidMng_ChkDid( ptSourceTable->u2SourceDid, DCM_DSP_DIDMNG_DID_RANGE, &u2_TargetIndex, &u1_RWSupport );
        if( u1_RetDidRange == DCM_MAIN_E_CHECK_OK )
        {
            if( DcmDspDidRangeTbl[ u2_TargetIndex ].ptReadDidFnc != NULL_PTR )
            {
                u4_SDidBuffLen  = (uint32)Dcm_P_u2Source_Did_Max_Data_Size;
                if( u1OpStatus == DCM_UPDATE_PAGE_OK )
                {
                    u4_SDidBuffLen -= Dcm_Dsp_DidMng_u4UnsetIndex;  /* no wrap around */
                }
#ifndef JGXSTACK
                u1_RetReadFnc = DcmDspDidRangeTbl[ u2_TargetIndex ].ptReadDidFnc( ptSourceTable->u2SourceDid, &Dcm_Dsp_DidMng_u1ReadBuffer[Dcm_Dsp_DidMng_u4UnsetIndex], u1OpStatus, u4_SDidBuffLen, &u4_ReadLen, &u1_LocalErrorCode );
#else  /* JGXSTACK */
                u1_RetReadFnc = E_OK;
                /* user-defined */
#endif /* JGXSTACK */
                if( u1_RetReadFnc == (Std_ReturnType)E_OK )
                {
                    Dcm_Dsp_DidMng_u4UnsetIndex = (uint32)0U;
                    if( u4_SDidBuffLen >= u4_ReadLen )
                    {
                        u1_RetVal   = E_OK;
                    }
                }
                else if( u1_RetReadFnc == (Std_ReturnType)E_NOT_OK )
                {
                    *ptErrorCode    = u1_LocalErrorCode;
                    /* u1_RetVal equal E_NOT_OK; */
                }
                else if( u1_RetReadFnc == (Std_ReturnType)DCM_E_PENDING )
                {
                    u1_RetVal       = DCM_E_PENDING;
                }
                else if( u1_RetReadFnc == (Std_ReturnType)DCM_E_UPDATE_PAGE )
                {
                    if( u4_SDidBuffLen >= u4_ReadLen )
                    {
                        Dcm_Dsp_DidMng_u4UnsetIndex += u4_ReadLen;  /* no wrap around */
                        u1_RetVal   = DCM_E_UPDATE_PAGE;
                    }
                    else
                    {
                        /* u1_RetVal equal E_NOT_OK; */
                        /* No process */
                    }
                }
                else
                {
                    /* u1_RetVal equal E_NOT_OK; */
                    /* No process */
                }
            }
        }
    }
    else if( ptSourceTable->u1SourceElementId == DCM_DSP_DIDMNG_SOURCEELEMENTID_MEMADDR )
    {
        u1_RetReadFnc = Dcm_Dsp_DidMng_CallMemRead( ptSourceTable, u1OpStatus, u4DataBufferLength, ptData, ptDataLength, &u1_LocalErrorCode );
        if( u1_RetReadFnc == (Std_ReturnType)E_NOT_OK )
        {
            *ptErrorCode    = u1_LocalErrorCode;
        }
        u1_RetVal = u1_RetReadFnc;
    }
    else
    {
        /* u1_RetVal equal E_NOT_OK; */
        /* No process */
    }

    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON */
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON */
#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_OFF )
#if ( DCM_PAGEDBUFFER_SID23_ENABLED == STD_OFF )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_ReadElemData                              */
/* Description   | Read Source Element Data                                 */
/* Preconditions | None                                                     */
/* Parameters    | [in] ptSourceTable : SourceElement structure Table       */
/*               | [in] u1OpStatus : Operation state                        */
/*               | [in] u4DataBufferLength : Read Data Length               */
/*               | [out] ptErrorCode : Negative Response Code               */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Process complete                           */
/*               |        E_NOT_OK : Process abnormal termination           */
/*               |        DCM_E_PENDING : Process pending                   */
/*               |        DCM_E_FORCE_RCRRP : Force Process pending         */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ReadElemData
(
    P2CONST(Dcm_Dsp_SourceElementType, AUTOMATIC, DCM_APPL_DATA)    ptSourceTable,
    const Dcm_OpStatusType                                          u1OpStatus,
    const uint32                                                    u4DataBufferLength,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)                          ptData,
    P2VAR (uint32, AUTOMATIC, DCM_APPL_DATA)                        ptDataLength,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA)   ptErrorCode
)
{
    Std_ReturnType  u1_RetVal;
    Std_ReturnType  u1_RetDidRange;
    Std_ReturnType  u1_RetReadFnc;
    uint8           u1_RWSupport;
    uint16          u2_TargetIndex;
    uint32          u4_SDidBuffLen;
    uint32          u4_ReadLen;
    uint8           u1_cnt2;
    Dcm_NegativeResponseCodeType u1_LocalErrorCode;

    *ptErrorCode    = (Dcm_NegativeResponseCodeType)0U;
    u1_RetVal       = (Std_ReturnType)E_NOT_OK;
    u4_SDidBuffLen  = (uint32)Dcm_P_u2Source_Did_Max_Data_Size;
    u4_ReadLen      = (uint32)0U;
    u1_LocalErrorCode = (Dcm_NegativeResponseCodeType)0U;
    
    if( ptSourceTable->u1SourceElementId == DCM_DSP_DIDMNG_SOURCEELEMENTID_DID )
    {
        u1_RetDidRange = Dcm_Dsp_DidMng_ChkDid( ptSourceTable->u2SourceDid, DCM_DSP_DIDMNG_DID_RANGE, &u2_TargetIndex, &u1_RWSupport );

        if( u1_RetDidRange == DCM_MAIN_E_CHECK_OK )
        {
            if( DcmDspDidRangeTbl[ u2_TargetIndex ].ptReadDidFnc != NULL_PTR )
            {
#ifndef JGXSTACK
                u1_RetReadFnc = DcmDspDidRangeTbl[ u2_TargetIndex ].ptReadDidFnc( ptSourceTable->u2SourceDid, &Dcm_Dsp_DidMng_u1ReadBuffer[0], u1OpStatus, u4_SDidBuffLen, &u4_ReadLen, &u1_LocalErrorCode );
#else  /* JGXSTACK */
                u1_RetReadFnc = E_OK;
                /* user-defined */
#endif /* JGXSTACK */
                if( u1_RetReadFnc == (Std_ReturnType)E_OK )
                {
                    if( u4_SDidBuffLen >= u4_ReadLen )
                    {
                        if( ( ptSourceTable->u1Position > (uint8)0U ) &&
                            ( (uint32)((uint32)ptSourceTable->u1Position + (uint32)ptSourceTable->u1Size) <= (uint32)( u4_SDidBuffLen + (uint32)1U ) ) )   /* MISRA DEVIATION */    /* no wrap around */
                        {
                            for( u1_cnt2 = (uint8)0U; u1_cnt2 < ptSourceTable->u1Size; u1_cnt2++ )    /* MISRA DEVIATION */
                            {
                                ptData[u1_cnt2 + *ptDataLength] = Dcm_Dsp_DidMng_u1ReadBuffer[(u1_cnt2 + ptSourceTable->u1Position) - (uint8)1U];    /* MISRA DEVIATION */  /* no wrap around */
                            }
                            *ptDataLength   += ptSourceTable->u1Size;   /* no wrap around */
                            u1_RetVal       = E_OK;
                        }
                    }
                }
                else if( u1_RetReadFnc == (Std_ReturnType)E_NOT_OK )
                {
                    *ptErrorCode    = u1_LocalErrorCode;
                    u1_RetVal       = E_NOT_OK;
                }
                else if( u1_RetReadFnc == (Std_ReturnType)DCM_E_PENDING )
                {
                    u1_RetVal       = DCM_E_PENDING;
                }
                else
                {
                    /* u1_RetVal equal E_NOT_OK; */
                    /* No process */
                }
            }
        }
    }
    else if( ptSourceTable->u1SourceElementId == DCM_DSP_DIDMNG_SOURCEELEMENTID_MEMADDR )
    {
        if( (u4DataBufferLength - *ptDataLength) >= ptSourceTable->u4MemSize )  /* no wrap around */
        {
            u1_RetReadFnc   = Dcm_Dsp_DidMng_CallMemRead( ptSourceTable, u1OpStatus, ptData, ptDataLength, &u1_LocalErrorCode );
            if( u1_RetReadFnc == (Std_ReturnType)E_OK )
            {
                *ptDataLength   += ptSourceTable->u4MemSize;    /* no wrap around */
            }
            else if( u1_RetReadFnc == (Std_ReturnType)E_NOT_OK )
            {
                *ptErrorCode    = u1_LocalErrorCode;
            }
            else
            {
                /* No process */
            }
            u1_RetVal           = u1_RetReadFnc;
        }
    }
    else
    {
        /* u1_RetVal equal E_NOT_OK; */
        /* No process */
    }

    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID23_ENABLED == STD_OFF */
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_OFF */
#endif /* DCM_SUPPORT_SID22 == STD_ON */

#if ( DCM_PERIODIC_DDDID_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_ReadElemDataForPeriodic                   */
/* Description   | Read Source Element Data                                 */
/* Preconditions | None                                                     */
/* Parameters    | [in] ptSourceTable : SourceElement structure Table       */
/*               | [in] u1OpStatus : Operation state                        */
/*               | [in] u4DataBufferLength : Read Data Length               */
/*               | [out] ptData : Res Data Buffer                           */
/*               | [out] ptDataLength : Read Data Length                    */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Process complete                           */
/*               |        E_NOT_OK : Process abnormal termination           */
/*               |        DCM_E_PENDING : Process pending                   */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ReadElemDataForPeriodic
(
    P2CONST( Dcm_Dsp_SourceElementType, AUTOMATIC, DCM_APPL_DATA )  ptSourceTable,
    const Dcm_OpStatusType                                          u1OpStatus,
    const uint32                                                    u4DataBufferLength,
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA )                       ptData,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA )                       ptDataLength
)
{
    Std_ReturnType  u1_RetVal;
    Std_ReturnType  u1_RetDidRange;
    Std_ReturnType  u1_RetReadFnc;
    uint8           u1_RWSupport;
    uint16          u2_TargetIndex;
    uint32          u4_SDidBuffLen;
    uint32          u4_ReadLen;
    uint8           u1_cnt2;
    Dcm_NegativeResponseCodeType u1_LocalErrorCode;

    u1_RetVal       = (Std_ReturnType)E_NOT_OK;
    u4_SDidBuffLen  = (uint32)Dcm_P_u2Source_Did_Max_Data_Size;
    u4_ReadLen      = (uint32)0U;
    u1_LocalErrorCode = (Dcm_NegativeResponseCodeType)0U;
    
    if( ptSourceTable->u1SourceElementId == DCM_DSP_DIDMNG_SOURCEELEMENTID_DID )
    {
        u1_RetDidRange = Dcm_Dsp_DidMng_ChkDid( ptSourceTable->u2SourceDid, DCM_DSP_DIDMNG_DID_RANGE, &u2_TargetIndex, &u1_RWSupport );

        if( u1_RetDidRange == DCM_MAIN_E_CHECK_OK )
        {
            if( DcmDspDidRangeTbl[ u2_TargetIndex ].ptReadDidFnc != NULL_PTR )
            {
#ifndef JGXSTACK
                u1_RetReadFnc = DcmDspDidRangeTbl[ u2_TargetIndex ].ptReadDidFnc( ptSourceTable->u2SourceDid, &Dcm_Dsp_DidMng_u1ReadPdidBuffer[0], u1OpStatus, u4_SDidBuffLen, &u4_ReadLen, &u1_LocalErrorCode );
#else  /* JGXSTACK */
                u1_RetReadFnc = E_OK;
                /* user-defined */
#endif /* JGXSTACK */
                if( u1_RetReadFnc == (Std_ReturnType)E_OK )
                {
                    if( u4_SDidBuffLen >= u4_ReadLen )
                    {
                        if( ( ptSourceTable->u1Position > (uint8)0U ) &&
                            ( (uint32)((uint32)ptSourceTable->u1Position + (uint32)ptSourceTable->u1Size) <= (uint32)( u4_SDidBuffLen + (uint32)1U ) ) )   /* MISRA DEVIATION */    /* no wrap around */
                        {
                            for( u1_cnt2 = (uint8)0U; u1_cnt2 < ptSourceTable->u1Size; u1_cnt2++ )    /* MISRA DEVIATION */
                            {
                                ptData[u1_cnt2 + *ptDataLength] = Dcm_Dsp_DidMng_u1ReadPdidBuffer[(u1_cnt2 + ptSourceTable->u1Position) - (uint8)1U];    /* MISRA DEVIATION */  /* no wrap around */
                            }
                            *ptDataLength   += ptSourceTable->u1Size;   /* no wrap around */
                            u1_RetVal       = E_OK;
                        }
                    }
                }
                else if( u1_RetReadFnc == (Std_ReturnType)DCM_E_PENDING )
                {
                    u1_RetVal       = DCM_E_PENDING;
                }
                else
                {
                    /* u1_RetVal equal E_NOT_OK; */
                    /* No process */
                }
            }
        }
    }
    else if( ptSourceTable->u1SourceElementId == DCM_DSP_DIDMNG_SOURCEELEMENTID_MEMADDR )
    {
        if( (u4DataBufferLength - *ptDataLength) >= ptSourceTable->u4MemSize )  /* no wrap around */
        {
            u1_RetReadFnc = Dcm_Dsp_DidMng_CallMemReadForPeriodic( ptSourceTable, u1OpStatus, ptDataLength, ptData );
            if( u1_RetReadFnc == (Std_ReturnType)E_OK )
            {
                *ptDataLength   += ptSourceTable->u4MemSize;    /* no wrap around */
            }
            u1_RetVal           = u1_RetReadFnc;
        }
    }
    else
    {
        /* u1_RetVal equal E_NOT_OK; */
        /* No process */
    }

    return u1_RetVal;
}
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON */

#if ( DCM_SUPPORT_SID22 == STD_ON )
#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON )
#if ( DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_CallMemRead                               */
/* Description   | Read Data by Addressing                                  */
/* Preconditions | None                                                     */
/* Parameters    | [in] ptSourceTable : SourceElement structure Table       */
/*               | [in] u1OpStatus : Operation state                        */
/*               | [out] ptData : Data Buffer                               */
/*               | [out] ptDataLength : Data Buffer Length                  */
/*               | [out] ptErrorCode : Negative Response Code               */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Process complete                           */
/*               |        E_NOT_OK : Process abnormal termination           */
/*               |        DCM_E_PENDING : Process pending                   */
/*               |        DCM_E_FORCE_RCRRP : Force Process pending         */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallMemRead
(
    P2CONST(Dcm_Dsp_SourceElementType, AUTOMATIC, DCM_APPL_DATA)    ptSourceTable,
    const Dcm_OpStatusType                                          u1OpStatus,
    const uint32                                                    u4DataBufferLength,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)                          ptData,
    P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA)                         ptDataLength,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA)   ptErrorCode
)
{
    Dcm_ReturnReadMemoryType        u1_RetReadMemory;
    Std_ReturnType                  u1_RetVal;
    uint32                          u4_UnusedBufLen;
    uint32                          u4_ReadMemSize;
    uint32                          u4_wkStoredLen;
    boolean                         b_ExecReadMemory;
    Dcm_OpStatusType                                                u1_tmpOpStatus;
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)                          pt_wkWriteBuff;
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA)   pt_wkErrorCode;
    Dcm_NegativeResponseCodeType                                    u1_LocalErrorCode;

    u1_RetVal           = (Std_ReturnType)E_NOT_OK;
    *ptErrorCode        = (Dcm_NegativeResponseCodeType)0x00U;
    u1_LocalErrorCode   = (Dcm_NegativeResponseCodeType)0x00U;
    b_ExecReadMemory    = (boolean)TRUE;
    u1_tmpOpStatus      = u1OpStatus;
    u4_ReadMemSize      = (uint32)0U;
    pt_wkWriteBuff      = NULL_PTR;
    pt_wkErrorCode      = NULL_PTR;
    u4_UnusedBufLen     = u4DataBufferLength - *ptDataLength;   /* no wrap around */
    if( u1OpStatus == DCM_INITIAL )
    {
        Dcm_Dsp_DidMng_bSetData = (boolean)FALSE;
        Dcm_Dsp_DidMng_u4StoredDataLen = (uint32)0U;
    }
    u4_wkStoredLen      = Dcm_Dsp_DidMng_u4StoredDataLen;

    if( u1OpStatus == DCM_INITIAL )
    {
        u4_ReadMemSize          = Dcm_Dsp_DidMng_CalcPBReadMemLen( ptSourceTable, u4_UnusedBufLen, u4_wkStoredLen );
        if( u4_ReadMemSize != (uint32)0U )
        {
            pt_wkWriteBuff      = &ptData[*ptDataLength];
            pt_wkErrorCode      = &u1_LocalErrorCode;
        }
        else
        {
            b_ExecReadMemory    = (boolean)FALSE;
        }
    }
    else if( u1OpStatus == DCM_PENDING )
    {
        u4_ReadMemSize          = Dcm_Dsp_DidMng_CalcPBReadMemLen( ptSourceTable, u4_UnusedBufLen, u4_wkStoredLen );
        if( u4_ReadMemSize != (uint32)0U )
        {
            pt_wkWriteBuff      = &ptData[*ptDataLength];
            pt_wkErrorCode      = &u1_LocalErrorCode;
        }
        else
        {
            b_ExecReadMemory    = (boolean)FALSE;
        }
    }
    else if( u1OpStatus == DCM_UPDATE_PAGE_OK )
    {
        u4_ReadMemSize  = Dcm_Dsp_DidMng_CalcPBReadMemLen( ptSourceTable, u4_UnusedBufLen, u4_wkStoredLen );
        if( u4_ReadMemSize != (uint32)0U )
        {
            u1_tmpOpStatus      = DCM_INITIAL;
            pt_wkWriteBuff      = &ptData[*ptDataLength];
            pt_wkErrorCode      = &u1_LocalErrorCode;
        }
        else
        {
            b_ExecReadMemory    = (boolean)FALSE;
        }
    }
    else if( u1OpStatus == DCM_FORCE_RCRRP_OK )
    {
        u4_ReadMemSize          = Dcm_Dsp_DidMng_CalcPBReadMemLen( ptSourceTable, u4_UnusedBufLen, u4_wkStoredLen );
        if( u4_ReadMemSize != (uint32)0U )
        {
            pt_wkWriteBuff      = &ptData[*ptDataLength];
            pt_wkErrorCode      = &u1_LocalErrorCode;
        }
        else
        {
            b_ExecReadMemory    = (boolean)FALSE;
        }
    }
    else if( u1OpStatus == DCM_CANCEL )
    {
        /* No process */
    }
    else
    {
        b_ExecReadMemory        = (boolean)FALSE;
    }

    if( b_ExecReadMemory == (boolean)TRUE )
    {
        u1_RetReadMemory = Dcm_Dsp_MemMng_ReadMemory(   u1_tmpOpStatus,
                                                        ptSourceTable->u1MemId,
                                                        ptSourceTable->u4MemAddr,
                                                        u4_ReadMemSize,
                                                        ptSourceTable->u4MemSize,
                                                        u4_wkStoredLen,
                                                        pt_wkWriteBuff,
                                                        pt_wkErrorCode
                                                    );
        if( u1_RetReadMemory == DCM_READ_OK )
        {
            Dcm_Dsp_DidMng_u4StoredDataLen  = u4_wkStoredLen + u4_ReadMemSize;  /* no wrap around */
            *ptDataLength                   += u4_ReadMemSize;  /* no wrap around */
            u4_wkStoredLen                  = Dcm_Dsp_DidMng_u4StoredDataLen;
            if( u4_wkStoredLen >= ptSourceTable->u4MemSize )
            {
                u1_RetVal           = E_OK;
            }
            else
            {
                u1_RetVal           = DCM_E_UPDATE_PAGE;
            }
        }
        else if( u1_RetReadMemory == DCM_READ_FAILED )
        {
            /* u1_RetVal equal E_NOT_OK; */
            /* if OpStatus is DCM_CANCEL , u1_LocalErrorCode is 0. */
            /* if OpStatus is not DCM_CANCEL , u1_LocalErrorCode is set by CalloutFunction. */
            *ptErrorCode        = u1_LocalErrorCode;
        }
        else if( u1_RetReadMemory == DCM_READ_PENDING )
        {
            u1_RetVal           = DCM_E_PENDING;
        }
        else if( u1_RetReadMemory == DCM_READ_FORCE_RCRRP )
        {
            u1_RetVal           = DCM_E_FORCE_RCRRP;
        }
        else
        {
            /* u1_RetVal equal E_NOT_OK; */
            /* No process */
        }
    }
    else
    {
        /* u1_RetVal equal E_NOT_OK; */
        /* No process */
    }

    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON */
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON */
#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_OFF )
#if ( DCM_PAGEDBUFFER_SID23_ENABLED == STD_OFF )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_CallMemRead                               */
/* Description   | Read Data by Addressing                                  */
/* Preconditions | None                                                     */
/* Parameters    | [in] ptSourceTable : SourceElement structure Table       */
/*               | [in] u1OpStatus : Operation state                        */
/*               | [out] ptData : Data Buffer                               */
/*               | [out] ptDataLength : Data Buffer Length                  */
/*               | [out] ptErrorCode : Negative Response Code               */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Process complete                           */
/*               |        E_NOT_OK : Process abnormal termination           */
/*               |        DCM_E_PENDING : Process pending                   */
/*               |        DCM_E_FORCE_RCRRP : Force Process pending         */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallMemRead
(
    P2CONST(Dcm_Dsp_SourceElementType, AUTOMATIC, DCM_APPL_DATA)    ptSourceTable,
    const Dcm_OpStatusType                                          u1OpStatus,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)                          ptData,
    P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA)                         ptDataLength,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA)   ptErrorCode
)
{
    Dcm_ReturnReadMemoryType        u1_RetReadMemory;
    Std_ReturnType                  u1_RetVal;
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)                          pt_wkWriteBuff;
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA)   pt_wkErrorCode;
    Dcm_NegativeResponseCodeType                                    u1_LocalErrorCode;

    u1_RetVal           = E_NOT_OK;
    *ptErrorCode        = (Dcm_NegativeResponseCodeType)0x00U;
    u1_LocalErrorCode   = (Dcm_NegativeResponseCodeType)0x00U;

    if( u1OpStatus == DCM_CANCEL )
    {
        pt_wkWriteBuff  = NULL_PTR;
        pt_wkErrorCode  = NULL_PTR;
    }
    else
    {
        pt_wkWriteBuff  = &ptData[*ptDataLength];
        pt_wkErrorCode  = &u1_LocalErrorCode;
    }

    u1_RetReadMemory = Dcm_Dsp_MemMng_ReadMemory(   u1OpStatus,
                                                    ptSourceTable->u1MemId,
                                                    ptSourceTable->u4MemAddr,
                                                    ptSourceTable->u4MemSize,
                                                    pt_wkWriteBuff,
                                                    pt_wkErrorCode
                                                );
    if( u1_RetReadMemory == DCM_READ_OK )
    {
        u1_RetVal           = E_OK;
    }
    else if( u1_RetReadMemory == DCM_READ_FAILED )
    {
        u1_RetVal           = E_NOT_OK;
        *ptErrorCode        = u1_LocalErrorCode;
    }
    else if( u1_RetReadMemory == DCM_READ_PENDING )
    {
        u1_RetVal           = DCM_E_PENDING;
    }
    else if( u1_RetReadMemory == DCM_READ_FORCE_RCRRP )
    {
        u1_RetVal           = DCM_E_FORCE_RCRRP;
    }
    else
    {
        /* u1_RetVal equal E_NOT_OK; */
        /* No process */
    }

    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID23_ENABLED == STD_OFF */
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_OFF */
#endif /* DCM_SUPPORT_SID22 == STD_ON */

#if ( DCM_PERIODIC_DDDID_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_CallMemReadForPeriodic                    */
/* Description   | Read Data by Addressing                                  */
/* Preconditions | None                                                     */
/* Parameters    | [in] ptSourceTable : SourceElement structure Table       */
/*               | [in] u1OpStatus : Operation state                        */
/*               | [in] ptDataLength : Data Buffer Length                   */
/*               | [out] ptData : Data Buffer                               */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Process complete                           */
/*               |        E_NOT_OK : Process abnormal termination           */
/*               |        DCM_E_PENDING : Process pending                   */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallMemReadForPeriodic
(
    P2CONST( Dcm_Dsp_SourceElementType, AUTOMATIC, DCM_APPL_DATA )  ptSourceTable,
    const Dcm_OpStatusType                                          u1OpStatus,
    P2CONST( uint32, AUTOMATIC, DCM_APPL_DATA )                     ptDataLength,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )                        ptData
)
{
    uint32                          u4_wkStoredLen;
    Dcm_ReturnReadMemoryType        u1_RetReadMemory;
    Std_ReturnType                  u1_RetVal;
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)                          pt_wkWriteBuff;
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA)   pt_wkErrorCode;
    Dcm_NegativeResponseCodeType                                    u1_LocalErrorCode;

    u1_RetVal           = E_NOT_OK;
    u1_LocalErrorCode   = (Dcm_NegativeResponseCodeType)0x00U;
    u4_wkStoredLen      = (uint32)0U;

    if( u1OpStatus == DCM_PERIODIC_CANCEL )
    {
        pt_wkWriteBuff  = NULL_PTR;
        pt_wkErrorCode  = NULL_PTR;
    }
    else
    {
        pt_wkWriteBuff  = &ptData[*ptDataLength];
        pt_wkErrorCode  = &u1_LocalErrorCode;
    }

    u1_RetReadMemory = Dcm_Dsp_MemMng_ReadMemoryForPeriodic( u1OpStatus,
                                                             ptSourceTable->u1MemId,
                                                             ptSourceTable->u4MemAddr,
                                                             ptSourceTable->u4MemSize,
                                                             ptSourceTable->u4MemSize,
                                                             u4_wkStoredLen,
                                                             pt_wkWriteBuff,
                                                             pt_wkErrorCode
                                                           );
    if( u1OpStatus == DCM_PERIODIC_CANCEL )
    {
        u1_RetVal = E_OK;
    }
    else
    {
        if( u1_RetReadMemory == DCM_READ_OK )
        {
            u1_RetVal           = E_OK;
        }
        else if( u1_RetReadMemory == DCM_READ_PENDING )
        {
            u1_RetVal           = DCM_E_PENDING;
        }
        else
        {
            /* u1_RetVal equal E_NOT_OK; */
            /* No process */
        }
    }

    return u1_RetVal;
}
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON */


#if ( DCM_SUPPORT_SID22 == STD_ON )
#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON )
#if ( DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_CalcPBReadMemLen                          */
/* Description   | Read Data by Addressing                                  */
/* Preconditions | None                                                     */
/* Parameters    | [in] ptSourceTable : SourceElement structure Table       */
/*               | [in] u1OpStatus : Operation state                        */
/*               | [in] u1OpStatus : Operation state                        */
/*               |                                                          */
/* Return Value  | uint32  ReadMemLen                                       */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( uint32, DCM_CODE ) Dcm_Dsp_DidMng_CalcPBReadMemLen
(
    P2CONST(Dcm_Dsp_SourceElementType, AUTOMATIC, DCM_APPL_DATA)    ptSourceTable,
    const uint32                                                    u4DataBufferLength,
    const uint32                                                    u4StoredDataLength
)
{
    uint32          u4_ReadMemLen;

    u4_ReadMemLen   = (uint32)0U;

    if( ptSourceTable->u4MemSize > u4StoredDataLength )
    {
        if( u4DataBufferLength >= ( ptSourceTable->u4MemSize - u4StoredDataLength ) )   /* no wrap around */
        {
            u4_ReadMemLen  = ptSourceTable->u4MemSize - u4StoredDataLength; /* no wrap around */
        }
        else
        {
            u4_ReadMemLen  = u4DataBufferLength;
        }
    }
    else
    {
        /* No process */
    }

    return u4_ReadMemLen;
}
#endif /* DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON */
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON */
#endif /* DCM_SUPPORT_SID22 == STD_ON */


#if ( DCM_SUPPORT_SID22 == STD_ON )
#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON )
#if ( DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_SetRemainSourceDidData                    */
/* Description   | Set Remain Source DID Data to Send Buffer                */
/* Preconditions | None                                                     */
/* Parameters    | [in] u4DataBufferLength : Send Buffer Length             */
/*               | [out] ptDataLength : Res Data Length                     */
/*               | [out] ptData : Res Data Buffer                           */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Set OK                                     */
/*               |        E_NOT_OK : Set NG                                 */
/*               |        DCM_E_PENDING : Process pending                   */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_SetRemainSourceDidData
(
    const uint32 u4DataBufferLength,
    P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) ptDataLength,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptData
)
{
    Std_ReturnType  u1_RetVal;
    uint8           u1_RemainDataSize;
    uint8           u1_cnt2;

    u1_RetVal = E_OK;

    if( Dcm_Dsp_DidMng_stSourceTable.u1SourceElementId == DCM_DSP_DIDMNG_SOURCEELEMENTID_DID )
    {
        if( Dcm_Dsp_DidMng_stSourceTable.u1Size >= Dcm_Dsp_DidMng_u1RemainIndex )
        {
            u1_RemainDataSize = Dcm_Dsp_DidMng_stSourceTable.u1Size - Dcm_Dsp_DidMng_u1RemainIndex;
            for( u1_cnt2 = 0U; u1_cnt2 < u1_RemainDataSize; u1_cnt2++ )    /* MISRA DEVIATION */
            {
                /* Set Remain Data within Notified buffer size */
                /* It means "u1_cnt2 + *ptDataLength < u4DataBufferLength" */
                if( (u1_cnt2 + *ptDataLength) < u4DataBufferLength )    /* no wrap around */
                {
                    /* Write Data Location is "u1_cnt2 + *ptDataLength" */
                    /* Read Data Location is "(Dcm_Dsp_DidMng_u1RemainIndex + u1_cnt2 + Dcm_Dsp_DidMng_stSourceTable.u1Position) - 1U" */
                    ptData[u1_cnt2 + *ptDataLength] = Dcm_Dsp_DidMng_u1ReadBuffer[(Dcm_Dsp_DidMng_u1RemainIndex + u1_cnt2 + Dcm_Dsp_DidMng_stSourceTable.u1Position) - (uint8)1U];    /* MISRA DEVIATION */ /* no wrap around */
                }
                else
                {
                    Dcm_Dsp_DidMng_u1RemainIndex += u1_cnt2;    /* no wrap around */
                    /* Dcm_Dsp_DidMng_bRemainData, Dcm_Dsp_DidMng_u1RemainIndex, Dcm_Dsp_DidMng_stSourceTable are already set. */
                    u1_RetVal  = DCM_E_PENDING;
                    break;
                }
            }
            *ptDataLength += u1_cnt2;   /* no wrap around */
        }
        else
        {
            u1_RetVal = E_NOT_OK;
        }
    }
    else if( Dcm_Dsp_DidMng_stSourceTable.u1SourceElementId == DCM_DSP_DIDMNG_SOURCEELEMENTID_MEMADDR )
    {
        /* Dcm_Dsp_DidMng_bRemainData is used only for DCM_DSP_DIDMNG_SOURCEELEMENTID_DID */
        u1_RetVal = E_NOT_OK;
    }
    else
    {
        u1_RetVal = E_NOT_OK;
    }
        
    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON */
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON */
#endif /* DCM_SUPPORT_SID22 == STD_ON */


#if ( DCM_SUPPORT_SID22 == STD_ON )
#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON )
#if ( DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_SetSourceDidData                          */
/* Description   | Set Source DID Data to Send Buffer                       */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1cnt : Counter of the Internal Cycle               */
/*               | [in] ptSourceTable : SourceElement structure Table       */
/*               | [in] u4DataBufferLength : Send Buffer Length             */
/*               | [out] ptData : Res Data Buffer                           */
/*               | [out] ptDataLength : Res Data Length                     */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Set OK                                     */
/*               |        E_NOT_OK : Set NG                                 */
/*               |        DCM_E_PENDING : Process pending                   */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_SetSourceDidData
(
    const uint8 u1cnt,
    P2CONST(Dcm_Dsp_SourceElementType, AUTOMATIC, DCM_APPL_DATA) ptSourceTable,
    const uint32 u4DataBufferLength,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptData,
    P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) ptDataLength
)
{
    uint16          u2_SourceDidMaxDataSize;
    uint8           u1_cnt2;
    Std_ReturnType  u1_RetVal;

    u1_RetVal = E_OK;
    u2_SourceDidMaxDataSize = Dcm_P_u2Source_Did_Max_Data_Size;

    if( ptSourceTable->u1SourceElementId == DCM_DSP_DIDMNG_SOURCEELEMENTID_DID )
    {
        if( ( ptSourceTable->u1Position > (uint8)0U ) &&
            ( (uint32)((uint32)ptSourceTable->u1Position + (uint32)ptSourceTable->u1Size) <= (uint32)( (uint32)u2_SourceDidMaxDataSize + (uint32)1U ) ) )   /* no wrap around */
        {
            for( u1_cnt2 = (uint8)0U; u1_cnt2 < ptSourceTable->u1Size; u1_cnt2++ )    /* MISRA DEVIATION */
            {
                if( (u1_cnt2 + *ptDataLength) < u4DataBufferLength )    /* no wrap around */
                {
                    ptData[u1_cnt2 + *ptDataLength] = Dcm_Dsp_DidMng_u1ReadBuffer[(u1_cnt2 + ptSourceTable->u1Position) - (uint8)1U];    /* MISRA DEVIATION */  /* no wrap around */
                }
                else
                {
                    Dcm_Dsp_DidMng_bRemainData      = (boolean)TRUE;
                    Dcm_Dsp_DidMng_u1RemainIndex    = u1_cnt2;
                    Dcm_Dsp_DidMng_stSourceTable    = *ptSourceTable;
                    Dcm_Dsp_DidMng_u1LoopCnt        = u1cnt + (uint8)1U;
                    u1_RetVal                       = DCM_E_PENDING;
                    break;
                }
            }
            *ptDataLength += u1_cnt2;   /* no wrap around */
        }
        else
        {
            u1_RetVal = E_NOT_OK;
        }
    }
    else if( ptSourceTable->u1SourceElementId == DCM_DSP_DIDMNG_SOURCEELEMENTID_MEMADDR )
    {
        /* No process */
    }
    else
    {
        u1_RetVal = E_NOT_OK;
    }

    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON */
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON */
#endif /* DCM_SUPPORT_SID22 == STD_ON */


#if ( DCM_SUPPORT_SID22 == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_InternalPending                           */
/* Description   | Check the Internal Pending                               */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1cnt : Counter of the Internal Cycle               */
/*               | [in] u1NumOfSourceDid : Num Of Soure Did                 */
/*               | [in] u2LoopCntMax : Max Loop Num of a Cycle              */
/*               | [in/out] ptBreakFlag : Break Flag                        */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Check OK                                   */
/*               |        DCM_E_PENDING : Process pending                   */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_InternalPending
(
    const uint8 u1cnt,
    const uint8 u1NumOfSourceDid,
    const uint16 u2LoopCntMax,
    P2VAR(boolean, AUTOMATIC, DCM_APPL_DATA) ptBreakFlag
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    if( u1cnt < (u1NumOfSourceDid - (uint8)1U) )
    {
        if( u2LoopCntMax == (uint8)0U )
        {
            Dcm_Dsp_DidMng_u1LoopCnt = u1cnt + (uint8)1U;
            u1_RetVal = DCM_E_PENDING;
            *ptBreakFlag = (boolean)TRUE;
        }
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID22 == STD_ON */

#if ( DCM_SUPPORT_SID2C == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_SetSourceElement                          */
/* Description   | Set the Source Element for a DDDID                       */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DDDidIndex : Index of DcmDspDDDidTbl[]            */
/*               | [in] ptRequestMessage : Request message                  */
/*               | [in] u1NumOfSourceElement : Number of elements           */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Set OK                                     */
/*               |        E_NOT_OK : Set NG                                 */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_NVM_DDDID_USE == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_SetSourceElement
(
    const uint16 u2DDDidIndex,
    P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) ptRequestMessage,
    const uint8 u1NumOfSourceElement
)
{
    Std_ReturnType u1_RetVal;
    Std_ReturnType u1_FuncRet;
    uint8 u1_NumOfSourceDid;
    uint8 u1_SourceDidSetCnt;
    uint16 u2_DidHighByte;
    uint16 u2_DidLowByte;
    Dcm_Dsp_SourceElementType st_SourceElement;
    boolean b_CheckFlag;

    b_CheckFlag = (boolean)TRUE;

    u1_FuncRet = Dcm_Dsp_DidMng_GetNumOfSrcDid(u2DDDidIndex, &u1_NumOfSourceDid);
    if( u1_FuncRet == (Std_ReturnType)E_OK )
    {
        for( u1_SourceDidSetCnt = (uint8)0U; u1_SourceDidSetCnt < u1NumOfSourceElement; u1_SourceDidSetCnt++ )
        {
            u2_DidHighByte = DCM_DSP_DIDMNG_SOURCEDID_POS + ((uint16)u1_SourceDidSetCnt * DCM_DSP_DIDMNG_SRCELM_MSG_SIZ);
            u2_DidLowByte = DCM_DSP_DIDMNG_SOURCEDID_POS + (uint16)1U + ((uint16)u1_SourceDidSetCnt * DCM_DSP_DIDMNG_SRCELM_MSG_SIZ);

            st_SourceElement.u2SourceDid = (uint16)(((uint16)ptRequestMessage[u2_DidHighByte]) << DCM_DSP_DIDMNG_DIDSHIFT)
                                                    | ((uint16)ptRequestMessage[u2_DidLowByte]);

            st_SourceElement.u1Position = ptRequestMessage[DCM_DSP_DIDMNG_POSITION_POS + (u1_SourceDidSetCnt * DCM_DSP_DIDMNG_SRCELM_MSG_SIZ)];

            st_SourceElement.u1Size = ptRequestMessage[DCM_DSP_DIDMNG_SIZE_POS + (u1_SourceDidSetCnt * DCM_DSP_DIDMNG_SRCELM_MSG_SIZ)];

            st_SourceElement.u1SourceElementId = DCM_DSP_DIDMNG_SOURCEELEMENTID_DID;

            st_SourceElement.u4MemAddr = (uint32)0U;

            st_SourceElement.u4MemSize = (uint32)0U;

            st_SourceElement.u1MemId = (uint8)0U;

            u1_FuncRet = Dcm_Dsp_DidMng_SetSourceDID(u2DDDidIndex, (u1_NumOfSourceDid + u1_SourceDidSetCnt), &st_SourceElement);
            if( u1_FuncRet != (Std_ReturnType)E_OK )
            {
                b_CheckFlag = (boolean)FALSE;
                break;
            }
            else
            {
                (void)Dcm_Dsp_DidMng_WriteStorage(DCM_DSP_DIDMNG_SET_DDDID, u2DDDidIndex, (u1_NumOfSourceDid + u1_SourceDidSetCnt));
            }
        }

        if( b_CheckFlag == (boolean)TRUE )
        {
            u1_RetVal = Dcm_Dsp_DidMng_SetNumOfSrcDid(u2DDDidIndex, (u1_NumOfSourceDid + u1NumOfSourceElement));
            if( u1_RetVal == (Std_ReturnType)E_OK )
            {
                (void)Dcm_Dsp_DidMng_WriteStorage(DCM_DSP_DIDMNG_SET_NOSE, u2DDDidIndex, (u1_NumOfSourceDid + u1NumOfSourceElement));
            }
        }
        else
        {
            u1_RetVal = E_NOT_OK;
        }
    }
    else
    {
        u1_RetVal = E_NOT_OK;
    }

    return u1_RetVal;
}
#endif /* DCM_NVM_DDDID_USE == STD_ON */
#if ( DCM_NVM_DDDID_USE == STD_OFF )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_SetSourceElement
(
    const uint16 u2DDDidIndex,
    P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) ptRequestMessage,
    const uint8 u1NumOfSourceElement
)
{
    Std_ReturnType u1_RetVal;
    Std_ReturnType u1_FuncRet;
    uint8 u1_NumOfSourceDid;
    uint8 u1_SourceDidSetCnt;
    uint16 u2_DidHighByte;
    uint16 u2_DidLowByte;
    Dcm_Dsp_SourceElementType st_SourceElement;
    boolean b_CheckFlag;

    b_CheckFlag = (boolean)TRUE;

    u1_FuncRet = Dcm_Dsp_DidMng_GetNumOfSrcDid(u2DDDidIndex, &u1_NumOfSourceDid);
    if( u1_FuncRet == (Std_ReturnType)E_OK )
    {
        for( u1_SourceDidSetCnt = (uint8)0U; u1_SourceDidSetCnt < u1NumOfSourceElement; u1_SourceDidSetCnt++ )
        {
            u2_DidHighByte = DCM_DSP_DIDMNG_SOURCEDID_POS + ((uint16)u1_SourceDidSetCnt * DCM_DSP_DIDMNG_SRCELM_MSG_SIZ);
            u2_DidLowByte = DCM_DSP_DIDMNG_SOURCEDID_POS + (uint16)1U + ((uint16)u1_SourceDidSetCnt * DCM_DSP_DIDMNG_SRCELM_MSG_SIZ);

            st_SourceElement.u2SourceDid = (uint16)(((uint16)ptRequestMessage[u2_DidHighByte]) << DCM_DSP_DIDMNG_DIDSHIFT)
                                                    | ((uint16)ptRequestMessage[u2_DidLowByte]);

            st_SourceElement.u1Position = ptRequestMessage[DCM_DSP_DIDMNG_POSITION_POS + (u1_SourceDidSetCnt * DCM_DSP_DIDMNG_SRCELM_MSG_SIZ)];

            st_SourceElement.u1Size = ptRequestMessage[DCM_DSP_DIDMNG_SIZE_POS + (u1_SourceDidSetCnt * DCM_DSP_DIDMNG_SRCELM_MSG_SIZ)];

            st_SourceElement.u1SourceElementId = DCM_DSP_DIDMNG_SOURCEELEMENTID_DID;

            st_SourceElement.u4MemAddr = (uint32)0U;

            st_SourceElement.u4MemSize = (uint32)0U;

            st_SourceElement.u1MemId = (uint8)0U;

            u1_FuncRet = Dcm_Dsp_DidMng_SetSourceDID(u2DDDidIndex, (u1_NumOfSourceDid + u1_SourceDidSetCnt), &st_SourceElement);
            if( u1_FuncRet != (Std_ReturnType)E_OK )
            {
                b_CheckFlag = (boolean)FALSE;
                break;
            }
        }

        if( b_CheckFlag == (boolean)TRUE )
        {
            u1_RetVal = Dcm_Dsp_DidMng_SetNumOfSrcDid(u2DDDidIndex, (u1_NumOfSourceDid + u1NumOfSourceElement));
        }
        else
        {
            u1_RetVal = E_NOT_OK;
        }
    }
    else
    {
        u1_RetVal = E_NOT_OK;
    }

    return u1_RetVal;
}
#endif /* DCM_NVM_DDDID_USE == STD_OFF */
#endif /* DCM_SUPPORT_SID2C == STD_ON */

#if ( DCM_SUPPORT_SID2C == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_SetMemAddrSourceElement                   */
/* Description   | Set the Source Element for a Memory Address              */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DDDidIndex : Index of DcmDspDDDidTbl[]            */
/*               | [in] ptRequestMessage : Request message                  */
/*               | [in] u1NumOfSourceElement : Number of elements           */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Set OK                                     */
/*               |        E_NOT_OK : Set NG                                 */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_NVM_DDDID_USE == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_SetMemAddrSourceElement
(
    const uint16 u2DDDidIndex,
    P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) ptRequestMessage,
    const uint8 u1NumOfSourceElement
)
{
    boolean b_CheckUseAsMemoryId;
    boolean b_CheckFlag;
    Std_ReturnType u1_RetVal;
    Std_ReturnType u1_FuncRet;
    uint8  u1_NumOfSourceDid;
    uint8  u1_SourceDidSetCnt;
    uint8  u1_MemAddrLen;
    uint8  u1_MemSizeLen;

    b_CheckFlag = (boolean)TRUE;
    u1_FuncRet = Dcm_Dsp_DidMng_GetNumOfSrcDid(u2DDDidIndex, &u1_NumOfSourceDid);
    if( u1_FuncRet == (Std_ReturnType)E_OK )
    {
        u1_MemAddrLen = ptRequestMessage[DCM_DSP_DIDMNG_ALFID_POS] & DCM_DSP_DIDMNG_ALFID_ADLEN_MASK;
        u1_MemSizeLen = ptRequestMessage[DCM_DSP_DIDMNG_ALFID_POS] >> DCM_DSP_DIDMNG_ALFID_SHIFT4;
        b_CheckUseAsMemoryId = Dcm_Dsp_MemMng_GetUseAsMemoryId();
        for( u1_SourceDidSetCnt = (uint8)0U; u1_SourceDidSetCnt < u1NumOfSourceElement; u1_SourceDidSetCnt++ )
        {
            u1_FuncRet = Dcm_Dsp_DidMng_CalcMemAddr( ptRequestMessage,
                                                     u1_SourceDidSetCnt,
                                                     u1_MemAddrLen,
                                                     u1_MemSizeLen,
                                                     b_CheckUseAsMemoryId,
                                                     u2DDDidIndex,
                                                     u1_NumOfSourceDid );

            if( u1_FuncRet == (boolean)TRUE )
            {
                b_CheckFlag = (boolean)FALSE;
                break;
            }
            else
            {
                (void)Dcm_Dsp_DidMng_WriteStorage(DCM_DSP_DIDMNG_SET_DDDID, u2DDDidIndex, (u1_NumOfSourceDid + u1_SourceDidSetCnt));
            }
        }

        if( b_CheckFlag == (boolean)TRUE )
        {
            u1_RetVal = Dcm_Dsp_DidMng_SetNumOfSrcDid(u2DDDidIndex, (u1_NumOfSourceDid + u1NumOfSourceElement));
            if( u1_RetVal == (Std_ReturnType)E_OK )
            {
                (void)Dcm_Dsp_DidMng_WriteStorage(DCM_DSP_DIDMNG_SET_NOSE, u2DDDidIndex, (u1_NumOfSourceDid + u1NumOfSourceElement));
            }
        }
        else
        {
            u1_RetVal = E_NOT_OK;
        }
    }
    else
    {
        u1_RetVal = E_NOT_OK;
    }

    return u1_RetVal;
}
#endif /* DCM_NVM_DDDID_USE == STD_ON */
#if ( DCM_NVM_DDDID_USE == STD_OFF )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_SetMemAddrSourceElement
(
    const uint16 u2DDDidIndex,
    P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) ptRequestMessage,
    const uint8 u1NumOfSourceElement
)
{
    boolean b_CheckUseAsMemoryId;
    boolean b_CheckFlag;
    Std_ReturnType u1_RetVal;
    Std_ReturnType u1_FuncRet;
    uint8  u1_NumOfSourceDid;
    uint8  u1_SourceDidSetCnt;
    uint8  u1_MemAddrLen;
    uint8  u1_MemSizeLen;

    b_CheckFlag = (boolean)TRUE;
    u1_FuncRet = Dcm_Dsp_DidMng_GetNumOfSrcDid(u2DDDidIndex, &u1_NumOfSourceDid);
    if( u1_FuncRet == (Std_ReturnType)E_OK )
    {
        u1_MemAddrLen = ptRequestMessage[DCM_DSP_DIDMNG_ALFID_POS] & DCM_DSP_DIDMNG_ALFID_ADLEN_MASK;
        u1_MemSizeLen = ptRequestMessage[DCM_DSP_DIDMNG_ALFID_POS] >> DCM_DSP_DIDMNG_ALFID_SHIFT4;
        b_CheckUseAsMemoryId = Dcm_Dsp_MemMng_GetUseAsMemoryId();
        for( u1_SourceDidSetCnt = (uint8)0U; u1_SourceDidSetCnt < u1NumOfSourceElement; u1_SourceDidSetCnt++ )
        {
            u1_FuncRet = Dcm_Dsp_DidMng_CalcMemAddr( ptRequestMessage,
                                                     u1_SourceDidSetCnt,
                                                     u1_MemAddrLen,
                                                     u1_MemSizeLen,
                                                     b_CheckUseAsMemoryId,
                                                     u2DDDidIndex,
                                                     u1_NumOfSourceDid );

            if( u1_FuncRet == (boolean)TRUE )
            {
                b_CheckFlag = (boolean)FALSE;
                break;
            }
        }

        if( b_CheckFlag == (boolean)TRUE )
        {
            u1_RetVal = Dcm_Dsp_DidMng_SetNumOfSrcDid(u2DDDidIndex, (u1_NumOfSourceDid + u1NumOfSourceElement));
        }
        else
        {
            u1_RetVal = E_NOT_OK;
        }
    }
    else
    {
        u1_RetVal = E_NOT_OK;
    }

    return u1_RetVal;
}
#endif /* DCM_NVM_DDDID_USE == STD_OFF */
#endif /* DCM_SUPPORT_SID2C == STD_ON */


#if ( DCM_SUPPORT_SID2C == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_CalcMemAddr                               */
/* Description   | Calculate memory address                                 */
/* Preconditions | None                                                     */
/* Parameters    | [in] ptRequestMessage : Request message                  */
/*               | [in] u1SourceDidSetCnt : Number of SourceDid sets        */
/*               | [in] u1MemAddrLen : Memory Address Length                */
/*               | [in] u1MemSizeLen : Memory Size Length                   */
/*               | [in] bCheckUseAsMemoryId : Check use as MemoryId         */
/*               | [in] u2DDDidIndex : Index of DcmDspDDDidTbl[]            */
/*               | [in] u1NumOfSourceDid : Num Of Soure Did                 */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : calculate OK                               */
/*               |        E_NOT_OK : calculate NG                           */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CalcMemAddr
(
    P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) ptRequestMessage,
    const uint8   u1SourceDidSetCnt,
    const uint8   u1MemAddrLen,
    const uint8   u1MemSizeLen,
    const boolean bCheckUseAsMemoryId,
    const uint16  u2DDDidIndex,
    const uint8   u1NumOfSourceDid
)
{
    uint16  u2_MemAddrPos;
    boolean b_CheckMemAddrFlag;
    boolean b_CalcNGFlag;
    boolean b_CheckMemSizeFlag;
    Std_ReturnType u1_RetVal;
    Std_ReturnType u1_FuncRet;
    uint8   u1_MemAddrConvertCnt;
    uint8   u1_MemSizeConvertCnt;
    uint8   u1_SourceDidIndex;
    Dcm_Dsp_SourceElementType st_SourceElement;

    b_CheckMemAddrFlag = (boolean)TRUE;
    b_CalcNGFlag       = (boolean)FALSE;
    b_CheckMemSizeFlag = (boolean)TRUE;
    u2_MemAddrPos = (uint16)(((uint16)u1SourceDidSetCnt * (uint16)((uint16)u1MemAddrLen + (uint16)u1MemSizeLen)) + (uint16)DCM_DSP_DIDMNG_MEMADR_POS);

    if( bCheckUseAsMemoryId == (boolean)TRUE )
    {
        st_SourceElement.u1MemId = ptRequestMessage[u2_MemAddrPos];
        u1_MemAddrConvertCnt = DCM_DSP_DIDMNG_MEMID_SET;
    }
    else
    {
        st_SourceElement.u1MemId = (uint8)0U;
        u1_MemAddrConvertCnt = DCM_DSP_DIDMNG_MEMID_NOT_SET;
    }

    st_SourceElement.u4MemAddr = (uint32)0U;
    /* Convert MemoryAddress into uint32 */
    for( ; u1_MemAddrConvertCnt < u1MemAddrLen; u1_MemAddrConvertCnt++ )
    {
         st_SourceElement.u4MemAddr <<= DCM_DSP_DIDMNG_SHIFT8;
         st_SourceElement.u4MemAddr += ptRequestMessage[u2_MemAddrPos + u1_MemAddrConvertCnt];  /* no wrap around */
    }

    if( u1MemAddrLen < DCM_DSP_DIDMNG_ALFID_ADRSIZE_MIN )
    {
        b_CheckMemAddrFlag = FALSE;
        b_CalcNGFlag = (boolean)TRUE;
    }
    else if( u1MemAddrLen > DCM_DSP_DIDMNG_ALFID_ADRSIZE_MAX )
    {
        b_CheckMemAddrFlag = FALSE;
        b_CalcNGFlag = (boolean)TRUE;
    }
    else
    {
        /* No process */
    }

    if( b_CheckMemAddrFlag == (boolean)TRUE )
    {
        st_SourceElement.u4MemSize = (uint32)0U;
        /* Convert MemorySize into uint32 */
        for( u1_MemSizeConvertCnt = (uint8)0U; u1_MemSizeConvertCnt < u1MemSizeLen; u1_MemSizeConvertCnt++ )
        {
            st_SourceElement.u4MemSize <<= DCM_DSP_DIDMNG_SHIFT8;
            st_SourceElement.u4MemSize += ptRequestMessage[((u2_MemAddrPos + u1MemAddrLen) + u1_MemSizeConvertCnt)];    /* no wrap around */
        }

        if( u1MemSizeLen < DCM_DSP_DIDMNG_ALFID_MEMSIZE_MIN )
        {
            b_CheckMemSizeFlag = (boolean)FALSE;
            b_CalcNGFlag = (boolean)TRUE;
        }
        else if( u1MemSizeLen > DCM_DSP_DIDMNG_ALFID_MEMSIZE_MAX )
        {
            b_CheckMemSizeFlag = (boolean)FALSE;
            b_CalcNGFlag = (boolean)TRUE;
        }
        else
        {
            /* No process */
        }

        if( b_CheckMemSizeFlag == (boolean)TRUE )
        {
            st_SourceElement.u1SourceElementId = DCM_DSP_DIDMNG_SOURCEELEMENTID_MEMADDR;
            st_SourceElement.u2SourceDid = (uint16)0U;
            st_SourceElement.u1Position = (uint8)0U;
            st_SourceElement.u1Size = (uint8)0U;
            u1_SourceDidIndex = u1NumOfSourceDid + u1SourceDidSetCnt;
            u1_FuncRet = Dcm_Dsp_DidMng_SetSourceDID(u2DDDidIndex, u1_SourceDidIndex, &st_SourceElement);
            if( u1_FuncRet != (Std_ReturnType)E_OK )
            {
                b_CalcNGFlag = (boolean)TRUE;
            }
        }
    }

    if( b_CalcNGFlag == (boolean)TRUE )
    {
        u1_RetVal = E_NOT_OK;
    }
    else
    {
        u1_RetVal = E_OK;
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID2C == STD_ON */

#if ( ( DCM_PERIODIC_SEND_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ))
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_CallSDidModeRule                          */
/* Description   | Call the ModeRule Function of the Source Did             */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DDDidIndex : Index of DcmDspDDDidTbl[]            */
/*               | [in] u1KindOfFnc : Kind of Func                          */
/*               | [out] ptErrorCode : Negative Response Code               */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Process complete                           */
/*               |        E_NOT_OK : Process abnormal termination           */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CallSDidModeRule
(
    const uint16 u2DDDidIndex,
    const uint8 u1KindOfFnc,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode
)
{
    Std_ReturnType u1_RetVal;
    Std_ReturnType u1_RetGetNumOfSrcDid;
    Std_ReturnType u1_RetGetSourceDID;
    Std_ReturnType u1_RetDidRange;
    Std_ReturnType u1_RetModeRule;
    Std_ReturnType u1_RetChkCond;
    uint8 u1NumOfSourceDid;
    uint8 u1_cnt;
    uint8 u1RWSupport;
    uint16 u2TargetIndex;
    boolean b_BreakFlag;
    Dcm_NegativeResponseCodeType u1LocalErrorCode;
    Dcm_Dsp_SourceElementType stSourceTable;
    P2CONST(AB_83_ConstV Dcm_Dsp_DidInfoType, AUTOMATIC, DCM_APPL_CONST) ptTargetInfoTbl;
    boolean b_Chk_Per_Source_Did;
    boolean b_CheckSrcElm;
    boolean b_ValidSrcElm;

    b_BreakFlag = (boolean)FALSE;
    *ptErrorCode = (uint8)0x00U;
    u1LocalErrorCode = (uint8)0x00U;
    b_Chk_Per_Source_Did = Dcm_P_DIDMNG_bChk_Per_Source_Did;
    u1_RetVal = E_OK;
    b_ValidSrcElm = (boolean)FALSE;

    u1_RetGetNumOfSrcDid = Dcm_Dsp_DidMng_GetNumOfSrcDid( u2DDDidIndex, &u1NumOfSourceDid );
    if( u1_RetGetNumOfSrcDid == (Std_ReturnType)E_OK )
    {
        if( u1NumOfSourceDid > (uint8)0U )
        {
            b_ValidSrcElm = (boolean)TRUE;
        }
    }
    if( b_ValidSrcElm == (boolean)TRUE )
    {
        for( u1_cnt = (uint8)0U; u1_cnt < u1NumOfSourceDid; u1_cnt++ )
        {
            b_CheckSrcElm = (boolean)FALSE;
            u1_RetGetSourceDID = Dcm_Dsp_DidMng_GetSourceDID( u2DDDidIndex, u1_cnt, &stSourceTable );
            if( u1_RetGetSourceDID == (Std_ReturnType)E_OK )
            {
                if( stSourceTable.u1SourceElementId == DCM_DSP_DIDMNG_SOURCEELEMENTID_DID )
                {
                    if( b_Chk_Per_Source_Did == (boolean)TRUE )
                    {
                        b_CheckSrcElm = (boolean)TRUE;
                    }
                }
                else if( stSourceTable.u1SourceElementId == DCM_DSP_DIDMNG_SOURCEELEMENTID_MEMADDR )
                {
                    b_CheckSrcElm = (boolean)TRUE;
                }
                else
                {
                    u1_RetVal = E_NOT_OK;
                    b_BreakFlag     = (boolean)TRUE;
                }
            }
            if( b_CheckSrcElm == (boolean)TRUE )
            {
                if( stSourceTable.u1SourceElementId == DCM_DSP_DIDMNG_SOURCEELEMENTID_DID )
                {
                    u1_RetDidRange = Dcm_Dsp_DidMng_ChkDid( stSourceTable.u2SourceDid, DCM_DSP_DIDMNG_DID_RANGE, &u2TargetIndex, &u1RWSupport );

                    if( u1_RetDidRange == DCM_MAIN_E_CHECK_OK )
                    {
                        ptTargetInfoTbl = DcmDspDidRangeTbl[ u2TargetIndex ].ptInfoRef;

                        u1_RetModeRule = Dcm_Dsp_DidMng_InternalModeRule( u1KindOfFnc, ptTargetInfoTbl, stSourceTable.u2SourceDid, &u1LocalErrorCode );

                        if( u1_RetModeRule == (Std_ReturnType)E_OK )
                        {
                            u1_RetVal = u1_RetModeRule;
                        }
                        else if( u1_RetModeRule == (Std_ReturnType)E_NOT_OK )
                        {
                            u1_RetVal = u1_RetModeRule;
                            *ptErrorCode = u1LocalErrorCode;
                            b_BreakFlag = (boolean)TRUE;
                        }
                        else
                        {
                            u1_RetVal = u1_RetModeRule;
                            b_BreakFlag = (boolean)TRUE;
                        }
                    }
                    else
                    {
                        u1_RetVal = E_NOT_OK;
                        b_BreakFlag = (boolean)TRUE;
                    }
                }
                else
                {
                    /* if( stSourceTable.u1SourceElementId == DCM_DSP_DIDMNG_SOURCEELEMENTID_MEMADDR ) */
                    u1_RetChkCond = Dcm_Dsp_MemMng_CheckCondition( stSourceTable.u1MemId, stSourceTable.u4MemAddr, stSourceTable.u4MemSize, &u1LocalErrorCode );
                    if( u1_RetChkCond == (Std_ReturnType)E_OK )
                    {
                        u1_RetVal       = u1_RetChkCond;
                    }
                    else if( u1_RetChkCond == (Std_ReturnType)E_NOT_OK )
                    {
                        u1_RetVal       = u1_RetChkCond;
                        *ptErrorCode    = u1LocalErrorCode;
                        b_BreakFlag     = (boolean)TRUE;
                    }
                    else
                    {
                        u1_RetVal       = u1_RetChkCond;
                        b_BreakFlag     = (boolean)TRUE;
                    }
                }
            }
            
            if( b_BreakFlag == (boolean)TRUE )
            {
                break;
            }
        }
    }

    return u1_RetVal;
}
#endif /* DCM_PERIODIC_SEND_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON */

#if ( ( DCM_M_USE_VINDATAIDENTIFIER == STD_ON ) || ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_SearchDidRange                            */
/* Description   | Search Did from DidRange Table                           */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DID : Did Value                                   */
/*               | [in/out] ptTopIndex : Top Index of the Binary search     */
/*               | [in] u2EndIndex : End Index of the Binary search         */
/*               | [out] ptCheckFlag : Check result                         */
/*               |                                                          */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_DidMng_SearchDidRange
(
    const uint16 u2DID,
    P2VAR(uint16, AUTOMATIC,DCM_APPL_DATA) ptTopIndex,
    const uint16 u2EndIndex,
    P2VAR(boolean, AUTOMATIC,DCM_APPL_DATA) ptCheckFlag
)
{
    boolean b_BreakFlag;
    uint16 u2_MidIndex;
    uint16 u2_EndIndexTmp;

    b_BreakFlag = (boolean)FALSE;
    u2_EndIndexTmp = u2EndIndex;

    while( *ptTopIndex < u2_EndIndexTmp )
    {
        u2_MidIndex = (u2_EndIndexTmp + *ptTopIndex) >> (uint16)1U;
        if( DcmDspDidRangeTbl[u2_MidIndex].u2IdentifierUpperLimit < u2DID )
        {
            *ptTopIndex = u2_MidIndex + (uint16)1U;
        }
        else
        {
            u2_EndIndexTmp = u2_MidIndex;
        }

        if( DcmDspDidRangeTbl[*ptTopIndex].u2IdentifierLowerLimit <= u2DID )
        {
            if( DcmDspDidRangeTbl[*ptTopIndex].u2IdentifierUpperLimit >= u2DID )
            {
                *ptCheckFlag = (boolean)TRUE;
                b_BreakFlag = (boolean)TRUE;
            }
        }

        if( b_BreakFlag == (boolean)TRUE )
        {
            break;
        }
    }

    return;
}
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_ON || DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */

#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_InternalDidInfo                           */
/* Description   | Security/Session Check of the Did                        */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1KindOfCheck : Kind of Check                       */
/*               | [in] u1CheckElement : SecLevel/SesLevel                  */
/*               | [in] ptTargetInfoTbl : Check Target Table                */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Check OK                                   */
/*               |        E_NOT_OK : Check not OK                           */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_InternalDidInfo
(
    const uint8 u1KindOfCheck,
    const uint8 u1CheckElement,
    P2CONST(AB_83_ConstV Dcm_Dsp_DidInfoType, AUTOMATIC, DCM_APPL_CONST) ptTargetInfoTbl
)
{
    Std_ReturnType u1_RetVal;
    boolean b_CheckFlag;
    uint8 u1_cnt;
    uint8 u1LoopCntMax;
    P2CONST(AB_83_ConstV uint8, AUTOMATIC, DCM_APPL_CONST) ptLevelTbl;

    u1_RetVal = E_NOT_OK;
    b_CheckFlag = (boolean)FALSE;
    u1LoopCntMax = (uint8)0x00U;
    ptLevelTbl = NULL_PTR;

    if( ptTargetInfoTbl != NULL_PTR )
    {
        if( ( u1KindOfCheck == DCM_DSP_DIDMNG_CHECK_CTRL_SES ) ||
            ( u1KindOfCheck == DCM_DSP_DIDMNG_CHECK_CTRL_SEC ) )
        {
            if( ptTargetInfoTbl->ptControl != NULL_PTR )
            {
                if( u1KindOfCheck == DCM_DSP_DIDMNG_CHECK_CTRL_SES )
                {
                    u1LoopCntMax = ptTargetInfoTbl->ptControl->u1SessionNum;
                    ptLevelTbl = ptTargetInfoTbl->ptControl->ptSessionRef;
                }
                else
                {
                    u1LoopCntMax = ptTargetInfoTbl->ptControl->u1SecurityLevelNum;
                    ptLevelTbl = ptTargetInfoTbl->ptControl->ptSecurityLevelRef;
                }
                b_CheckFlag = (boolean)TRUE;
            }
        }
        else if( ( u1KindOfCheck == DCM_DSP_DIDMNG_CHECK_READ_SES ) ||
                 ( u1KindOfCheck == DCM_DSP_DIDMNG_CHECK_READ_SEC ) )
        {
            if( ptTargetInfoTbl->ptRead != NULL_PTR )
            {
                if( u1KindOfCheck == DCM_DSP_DIDMNG_CHECK_READ_SES )
                {
                    u1LoopCntMax = ptTargetInfoTbl->ptRead->u1SessionNum;
                    ptLevelTbl = ptTargetInfoTbl->ptRead->ptSessionRef;
                }
                else
                {
                    u1LoopCntMax = ptTargetInfoTbl->ptRead->u1SecurityLevelNum;
                    ptLevelTbl = ptTargetInfoTbl->ptRead->ptSecurityLevelRef;
                }
                b_CheckFlag = (boolean)TRUE;
            }
        }
        else if( ( u1KindOfCheck == DCM_DSP_DIDMNG_CHECK_WRITE_SES ) ||
                 ( u1KindOfCheck == DCM_DSP_DIDMNG_CHECK_WRITE_SEC ) )
        {
            if( ptTargetInfoTbl->ptWrite != NULL_PTR )
            {
                if( u1KindOfCheck == DCM_DSP_DIDMNG_CHECK_WRITE_SES )
                {
                    u1LoopCntMax = ptTargetInfoTbl->ptWrite->u1SessionNum;
                    ptLevelTbl = ptTargetInfoTbl->ptWrite->ptSessionRef;
                }
                else
                {
                    u1LoopCntMax = ptTargetInfoTbl->ptWrite->u1SecurityLevelNum;
                    ptLevelTbl = ptTargetInfoTbl->ptWrite->ptSecurityLevelRef;
                }
                b_CheckFlag = (boolean)TRUE;
            }
        }
        else
        {
            /* no process */
        }

        if( b_CheckFlag == (boolean)TRUE )
        {
            if( u1LoopCntMax > (uint8)0U )
            {
                if( ptLevelTbl != NULL_PTR )
                {
                    for( u1_cnt = (uint8)0U; u1_cnt < u1LoopCntMax; u1_cnt++ )
                    {
                        if( ptLevelTbl[ u1_cnt ] == u1CheckElement )
                        {
                            u1_RetVal = E_OK;
                            break;
                        }
                    }
                }
            }
            else
            {
                u1_RetVal = E_OK;
            }
        }
    }

    return u1_RetVal;
}
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */

#if ( ( DCM_PERIODIC_SEND_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ))
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_InternalModeRule                          */
/* Description   | Call the ModeRuleFnc                                     */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1KindOfFnc : Kind of Func                          */
/*               | [in] ptTargetInfoTbl : Target Table                      */
/*               | [in] u2DID           : Request Did                       */
/*               | [out] ptErrorCode : Negative Response Code               */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Process complete                           */
/*               |        E_NOT_OK : Process abnormal termination           */
/* Notes         | This function should be called only in                   */
/*               | that u1KindOfFnc is DCM_DSP_DIDMNG_CHECK_READ_MR         */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_InternalModeRule
(
    const uint8 u1KindOfFnc,
    P2CONST(AB_83_ConstV Dcm_Dsp_DidInfoType, AUTOMATIC, DCM_APPL_CONST) ptTargetInfoTbl,
    const uint16 u2DID,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_NOT_OK;
    *ptErrorCode = (uint8)0x00U;

    if( ptTargetInfoTbl != NULL_PTR )
    {
        if( u1KindOfFnc == DCM_DSP_DIDMNG_CHECK_READ_MR )
        {
            if( ptTargetInfoTbl->ptRead != NULL_PTR )
            {
                if( ptTargetInfoTbl->ptRead->ptModeRuleFnc != NULL_PTR )
                {
#ifndef JGXSTACK
                    u1_RetVal = ptTargetInfoTbl->ptRead->ptModeRuleFnc( u2DID, ptErrorCode );
#else  /* JGXSTACK */
                    /* user-defined */
#endif /* JGXSTACK */
                }
                else
                {
                    u1_RetVal = E_OK;
                }
            }
        }
    }
    return u1_RetVal;
}
#endif /* DCM_PERIODIC_SEND_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON */


#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_GetDynamicIndex                           */
/* Description   | Returns the number of SourceDIDs associated with DDDID   */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DDDid : Request Data Id                           */
/*               | [out] ptDynamicIndex : Index of DDDid Table              */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Request DID Normal                         */
/*               |        E_NOT_OK : Abnormal termination                   */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_GetDynamicIndex
(
    const uint16 u2DDDid,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) ptDynamicIndex
)
{
    Std_ReturnType u1_RetVal;
    uint16 u2_TopIndex;
    uint16 u2_MidIndex;
    uint16 u2_EndIndex;
    boolean b_CheckFlag;
    boolean b_BreakFlag;
    uint16 u2_DDDidNumber;

    u1_RetVal = E_NOT_OK;
    u2_DDDidNumber = Dcm_P_DIDMNG_u2DDDidNumber;

    if( u2_DDDidNumber != (uint16)0U )
    {
        b_CheckFlag = (boolean)FALSE;
        u2_TopIndex = (uint16)0U;
        u2_EndIndex = (uint16)(u2_DDDidNumber - (uint16)1U);

        if( DcmDspDDDidTbl[u2_TopIndex].u2DDDid > u2DDDid )
        {
            /* no process */
        }
        else if( DcmDspDDDidTbl[u2_TopIndex].u2DDDid == u2DDDid )
        {
            b_CheckFlag = (boolean)TRUE;
        }
        else if( DcmDspDDDidTbl[u2_EndIndex].u2DDDid < u2DDDid )
        {
            /* no process */
        }
        else
        {
            b_BreakFlag = (boolean)FALSE;
            while( u2_TopIndex < u2_EndIndex )
            {
                u2_MidIndex = (u2_EndIndex + u2_TopIndex) >> (uint16)1U;
                if( DcmDspDDDidTbl[u2_MidIndex].u2DDDid < u2DDDid )
                {
                    u2_TopIndex = u2_MidIndex + (uint16)1U;
                }
                else
                {
                    u2_EndIndex = u2_MidIndex;
                }

                if( DcmDspDDDidTbl[u2_TopIndex].u2DDDid == u2DDDid )
                {
                    b_CheckFlag = (boolean)TRUE;
                    b_BreakFlag = (boolean)TRUE;
                }

                if( b_BreakFlag == (boolean)TRUE )
                {
                    break;
                }
            }
        }

        if( b_CheckFlag == (boolean)TRUE )
        {
            *ptDynamicIndex = u2_TopIndex;
            u1_RetVal = E_OK;
        }
    }
    return u1_RetVal;
}
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON */

#if ( ( DCM_M_USE_VINDATAIDENTIFIER == STD_ON ) || ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_BinarySearchDidRange                      */
/* Description   | Find Did Range                                           */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DID : Request Data Id                             */
/*               | [out] ptDidIndex : Index of DcmDspDidRangeTbl[]          */
/*               | [out] ptControlReadWriteSupport : C/R/W Support Info     */
/*               |                                                          */
/* Return Value  | Dcm_Main_ReturnCheckType                                 */
/*               |        DCM_MAIN_E_CHECK_OK : DID is valid                */
/*               |        DCM_MAIN_E_CHECK_NOT_OK : DID is invalid          */
/*               |        DCM_MAIN_E_INVALID_CONFIG : Incorrect user c-     */
/*               |        onfiguration                                      */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Dcm_Main_ReturnCheckType, DCM_CODE ) Dcm_Dsp_DidMng_BinarySearchDidRange
(
    const uint16 u2DID,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) ptDidIndex,
    P2VAR(uint8, AUTOMATIC,DCM_APPL_DATA) ptControlReadWriteSupport
)
{
    Dcm_Main_ReturnCheckType u1_RetVal;
    boolean b_CheckFlag;
    uint16 u2_TopIndex;
    uint16 u2_EndIndex;
    uint16 u2_DidRangeNumber;
    uint16 u2_DidrangeT;

    u1_RetVal = DCM_MAIN_E_CHECK_NOT_OK;
    b_CheckFlag = (boolean)FALSE;
    u2_DidRangeNumber = Dcm_P_DIDMNG_u2DidRangeNumber;
    u2_DidrangeT = Dcm_P_u2Didrange_T;

    if( u2_DidRangeNumber != (uint16)0U )
    {
        u2_TopIndex = (uint16)0U;
        u2_EndIndex = (uint16)(u2_DidRangeNumber - (uint16)1U);

        if( DcmDspDidRangeTbl[u2_TopIndex].u2IdentifierLowerLimit > u2DID )
        {
            /* no process */
        }
        else if( DcmDspDidRangeTbl[u2_TopIndex].u2IdentifierUpperLimit >= u2DID )
        {
            b_CheckFlag = (boolean)TRUE;
        }
        else if( DcmDspDidRangeTbl[u2_EndIndex].u2IdentifierUpperLimit < u2DID )
        {
            /* no process */
        }
        else
        {
            Dcm_Dsp_DidMng_SearchDidRange( u2DID, &u2_TopIndex, u2_EndIndex, &b_CheckFlag );
        }

        if( b_CheckFlag == (boolean)TRUE )
        {
            if( u2_TopIndex < u2_DidrangeT )
            {
                *ptDidIndex = u2_TopIndex;
                if( DcmDspDidRangeTbl[u2_TopIndex].bHasGaps == (boolean)TRUE )
                {
                    if( DcmDspDidRangeTbl[u2_TopIndex].ptIsDidAvailableFnc != NULL_PTR )
                    {
                        /* no process */
                    }
                    else
                    {
                        u1_RetVal = DCM_MAIN_E_INVALID_CONFIG;
                        b_CheckFlag = (boolean)FALSE;
                    }
                }

                if( b_CheckFlag == (boolean)TRUE )
                {
                    if( DcmDspDidRangeTbl[u2_TopIndex].ptInfoRef->ptRead != NULL_PTR )
                    {
                        *ptControlReadWriteSupport = DCM_DSP_DIDMNG_READ_ONLY;
                    }
                    if( DcmDspDidRangeTbl[u2_TopIndex].ptInfoRef->ptWrite != NULL_PTR )
                    {
                        *ptControlReadWriteSupport |= DCM_DSP_DIDMNG_WRITE_ONLY;
                    }
                    u1_RetVal = DCM_MAIN_E_CHECK_OK;
                }
                else
                {
                    /* no process */
                }
            }
        }
    }

    return u1_RetVal;
}
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_ON || DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */

#if ( ( DCM_M_USE_VINDATAIDENTIFIER == STD_ON ) || ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_BinarySearchDid                           */
/* Description   | Find Did                                                 */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2DID : Request Data Id                             */
/*               | [out] ptDidIndex : Index of DcmDspDidRangeTbl[]          */
/*               | [out] ptControlReadWriteSupport : C/R/W Support Info     */
/*               |                                                          */
/* Return Value  | Dcm_Main_ReturnCheckType                                 */
/*               |        DCM_MAIN_E_CHECK_OK : DID is valid                */
/*               |        DCM_MAIN_E_CHECK_NOT_OK : DID is invalid          */
/*               |        DCM_MAIN_E_INVALID_CONFIG : Incorrect user c-     */
/*               |        onfiguration                                      */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Dcm_Main_ReturnCheckType, DCM_CODE ) Dcm_Dsp_DidMng_BinarySearchDid
(
    const uint16 u2DID,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) ptDidIndex,
    P2VAR(uint8, AUTOMATIC,DCM_APPL_DATA) ptControlReadWriteSupport
)
{
    Dcm_Main_ReturnCheckType u1_RetVal;
    boolean b_CheckFlag;
    boolean b_BreakFlag;
    uint16 u2_TopIndex;
    uint16 u2_MidIndex;
    uint16 u2_EndIndex;
    uint16 u2_DidNumber;

    u1_RetVal = DCM_MAIN_E_CHECK_NOT_OK;
    b_CheckFlag = (boolean)FALSE;
    b_BreakFlag = (boolean)FALSE;
    u2_DidNumber = Dcm_P_DIDMNG_u2DidNumber;

    if( u2_DidNumber != (uint16)0U )
    {
        u2_TopIndex = (uint16)0U;
        u2_EndIndex = (uint16)(u2_DidNumber - (uint16)1U);

        if( DcmDspDidTbl[u2_TopIndex].u2Identifier > u2DID )
        {
            /* no process */
        }
        else if( DcmDspDidTbl[u2_TopIndex].u2Identifier == u2DID )
        {
            b_CheckFlag = (boolean)TRUE;
        }
        else if( DcmDspDidTbl[u2_EndIndex].u2Identifier < u2DID )
        {
            /* no process */
        }
        else
        {
            while( u2_TopIndex < u2_EndIndex )
            {
                u2_MidIndex = (u2_EndIndex + u2_TopIndex) >> (uint16)1U;
                if( DcmDspDidTbl[u2_MidIndex].u2Identifier < u2DID )
                {
                    u2_TopIndex = u2_MidIndex + (uint16)1U;
                }
                else
                {
                    u2_EndIndex = u2_MidIndex;
                }

                if( DcmDspDidTbl[u2_TopIndex].u2Identifier == u2DID )
                {
                    b_CheckFlag = (boolean)TRUE;
                    b_BreakFlag = (boolean)TRUE;
                }

                if( b_BreakFlag == (boolean)TRUE )
                {
                    break;
                }
            }
        }

        if( b_CheckFlag == (boolean)TRUE )
        {
            if( DcmDspDidTbl[u2_TopIndex].bUsed == (boolean)TRUE )
            {
                *ptDidIndex = u2_TopIndex;
                if( DcmDspDidTbl[u2_TopIndex].ptInfoRef->ptControl != NULL_PTR )
                {
                    *ptControlReadWriteSupport = DCM_DSP_DIDMNG_CONTROL_ONLY;
                }
                if( DcmDspDidTbl[u2_TopIndex].ptInfoRef->ptRead != NULL_PTR )
                {
                    *ptControlReadWriteSupport |= DCM_DSP_DIDMNG_READ_ONLY;
                }
                if( DcmDspDidTbl[u2_TopIndex].ptInfoRef->ptWrite != NULL_PTR )
                {
                    *ptControlReadWriteSupport |= DCM_DSP_DIDMNG_WRITE_ONLY;
                }
                if( DcmDspDidTbl[u2_TopIndex].ptInfoRef->bDynamicallyDefined == (boolean)TRUE )
                {
                    *ptControlReadWriteSupport |= DCM_DSP_DIDMNG_DYNAMIC;
                }
                u1_RetVal = DCM_MAIN_E_CHECK_OK;
            }
        }
    }

    return u1_RetVal;
}
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_ON || DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */


#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_InternalAddrInfo                          */
/* Description   | Call the ModeRuleFnc                                     */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1KindOfCheck  : Kind of Check                      */
/*               | [in] u1CheckElement : SecLevel/SesLevel                  */
/*               | [in] u1MemId        : Memory Id                          */
/*               | [in] u4MemAddr      : Memory Address                     */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Process complete                           */
/*               |        E_NOT_OK : Process abnormal termination           */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_InternalAddrInfo
(
    const uint8         u1KindOfCheck,
    const uint8         u1CheckElement,
    const uint8         u1MemId,
    const uint32        u4MemAddr
)
{
    Std_ReturnType              u1_RetChkMemAddr;
    Std_ReturnType              u1_RetChkMemSes;
    Std_ReturnType              u1_RetChkMemSec;
    Std_ReturnType              u1_RetVal;
    uint8                       u1_MemIdFlag;
    uint8                       u1_MemIdIndex;
    uint8                       u1_MemRangeIndex;
    boolean                     b_CheckMemAddrUseAsMemoryId;

    u1_RetVal                   = E_NOT_OK;
    u1_MemIdIndex               = (uint8)0U;
    u1_MemRangeIndex            = (uint8)0U;

    if( ( u1KindOfCheck == DCM_DSP_DIDMNG_CHECK_READ_SES ) ||
        ( u1KindOfCheck == DCM_DSP_DIDMNG_CHECK_READ_SEC ) )
    {
        b_CheckMemAddrUseAsMemoryId = Dcm_Dsp_MemMng_GetUseAsMemoryId();
        if( b_CheckMemAddrUseAsMemoryId == (boolean)TRUE )
        {
            u1_MemIdFlag = DCM_DSP_DIDMNG_MEM_ID_VALID;
        }
        else
        {
            u1_MemIdFlag = DCM_DSP_DIDMNG_MEM_ID_INVALID;
        }
        u1_RetChkMemAddr = Dcm_Dsp_DidMng_ChkMemAddress( DCM_DSP_DIDMNG_MEM_READ,
                                                         u4MemAddr,
                                                         u1_MemIdFlag,
                                                         u1MemId,
                                                         &u1_MemIdIndex,
                                                         &u1_MemRangeIndex );
        if( u1_RetChkMemAddr == (Std_ReturnType)E_OK )
        {
            if( u1KindOfCheck == DCM_DSP_DIDMNG_CHECK_READ_SES )
            {
                /* Check session support */
                u1_RetChkMemSes = Dcm_Dsp_DidMng_ChkMemSes( DCM_DSP_DIDMNG_MEM_READ,
                                                            u1_MemIdIndex,
                                                            u1_MemRangeIndex,
                                                            u1CheckElement );
                if( u1_RetChkMemSes == (Std_ReturnType)E_OK )
                {
                    u1_RetVal = E_OK;
                }
            }
            else
            {
                /* Check Security lock is canceled */
                u1_RetChkMemSec = Dcm_Dsp_DidMng_ChkMemSec( DCM_DSP_DIDMNG_MEM_READ,
                                                            u1_MemIdIndex,
                                                            u1_MemRangeIndex,
                                                            u1CheckElement );
                if( u1_RetChkMemSec == (Std_ReturnType)E_OK )
                {
                    u1_RetVal = E_OK;
                }
            }
        }
    }
    
    return u1_RetVal;
}
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */

#if ( DCM_SUPPORT_SID2C == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_WriteStorage                              */
/* Description   | Write Storage                                            */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1Kind : Kind of Write Storage                      */
/*               | [in] u2DDDidIndex : Index of                             */
/*               |                      DcmDspCvt2MirrorIdx2StorageIdx[]    */
/*               |                      (same as Index of DcmDspDDDidTbl[]) */
/*               | [in] u1SourceDidIndex : Index of SourceElement Table     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_NVM_DDDID_USE == STD_ON )
static FUNC( void, DCM_CODE ) Dcm_Dsp_DidMng_WriteStorage
(
    const uint8  u1Kind,
    const uint16 u2DDDidIndex,
    const uint8  u1SourceDidIndex
)
{
    uint16 u2_BlockIdx;
    uint16 u2_StorageDDDidNum;
    uint16 u2_BIdxStaNose;
    uint16 u2_BIdxEndNose;
    uint16 u2_BIdxStaSrcInf;

    u2_StorageDDDidNum = Dcm_P_u2StorageDDDIDNum;
    u2_BIdxStaNose = Dcm_Dsp_StorageMng_u2BIdx_StaNose;
    u2_BIdxEndNose = Dcm_Dsp_StorageMng_u2BIdx_EndNose;
    u2_BIdxStaSrcInf = Dcm_Dsp_StorageMng_u2BIdx_StaSrcInf;

    if( u2_StorageDDDidNum > (uint16)0x0000U )
    {
        if( u1Kind == DCM_DSP_DIDMNG_SET_DDDID )
        {
            u2_BlockIdx = DcmDspCvt2MirrorIdx2StorageIdx[u2DDDidIndex].u2DddidBlidx + u2_BIdxStaSrcInf + u1SourceDidIndex;
            (void)Dcm_Dsp_StorageMng_EnQueue(u2_BlockIdx);
        }
        else if( u1Kind == DCM_DSP_DIDMNG_SET_NOSE )
        {
            u2_BlockIdx = DcmDspCvt2MirrorIdx2StorageIdx[u2DDDidIndex].u2NoseBlidx + u2_BIdxStaNose;
            (void)Dcm_Dsp_StorageMng_EnQueue(u2_BlockIdx);
        }
        else if( u1Kind == DCM_DSP_DIDMNG_CLEAR )
        {
            u2_BlockIdx = DcmDspCvt2MirrorIdx2StorageIdx[u2DDDidIndex].u2NoseBlidx + u2_BIdxStaNose;
            (void)Dcm_Dsp_StorageMng_EnQueue(u2_BlockIdx);
        }
        else
        {
            /* DCM_DSP_DIDMNG_CLEAR_ALL */
            for( u2_BlockIdx = u2_BIdxStaNose; u2_BlockIdx <= u2_BIdxEndNose; u2_BlockIdx++ )
            {
                (void)Dcm_Dsp_StorageMng_EnQueue(u2_BlockIdx);
            }
        }
    }

    return ;
}
#endif /* DCM_NVM_DDDID_USE == STD_ON */
#endif /*  DCM_SUPPORT_SID2C == STD_ON  */

#if ( DCM_SUPPORT_SID2C == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_ChkDDDIDDataLen                           */
/* Description   | Check the limit of DDDID Data length                     */
/* Preconditions | None                                                     */
/* Parameters    | [in] u4TotalSize  : Total DDDID Data Size                */
/*               | [in] u4CurrentSize: Current DDDID Data Size              */
/*               | [in] u2DDDid      : DDDID                                */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK       : Check OK                             */
/*               |        E_NOT_OK   : Check NG                             */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_PERIODIC_DDDID_USE == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ChkDDDIDDataLen
(
    const uint32 u4TotalSize,
    const uint32 u4CurrentSize,
    const uint16 u2DDDid
)
{
    Dcm_MsgLenType              u4_Sid2cResMaxDataLength;
    uint16                      u2_ConnectionId;
    Std_ReturnType              u1_RetVal;

    u1_RetVal                = E_NOT_OK;

    /* Get ResMaxDataLength */
    if( ( u2DDDid >> DCM_DSP_DIDMNG_DIDSHIFT ) == DCM_DSP_DIDMNG_DID_F2 )
    {
        u2_ConnectionId          = (uint16)0U;

        /* Get Connection Id */
        (void)Dcm_GetActiveProtocol( NULL_PTR, &u2_ConnectionId, NULL_PTR ); /* no return check required */
        /* Get MaxDataLen for Periodic Sending */
        u4_Sid2cResMaxDataLength = Dcm_Dsl_GetSizeOfPeriodicBuffer( u2_ConnectionId );
        if( u4_Sid2cResMaxDataLength > (uint32)0U )
        {
            u4_Sid2cResMaxDataLength -= (uint32)1U;
        }
    }
    else
    {
        u4_Sid2cResMaxDataLength = (Dcm_MsgLenType)Dcm_P_u2Sid2c_Res_Max_Data_Length;
    }

    /* Check limit */
    if( (Dcm_MsgLenType)(u4TotalSize + u4CurrentSize) <= u4_Sid2cResMaxDataLength ) /* no wrap around */
    {
        u1_RetVal = E_OK;
    }

    return u1_RetVal;
}
#endif /*  DCM_PERIODIC_DDDID_USE == STD_ON  */
#if ( DCM_PERIODIC_DDDID_USE == STD_OFF )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ChkDDDIDDataLen
(
    const uint32 u4TotalSize,
    const uint32 u4CurrentSize,
    const uint16 u2DDDid            /* MISRA DEVIATION */
)
{
    Dcm_MsgLenType              u4_Sid2cResMaxDataLength;
    Std_ReturnType              u1_RetVal;

    u1_RetVal                = E_NOT_OK;

    /* Get ResMaxDataLength */
    u4_Sid2cResMaxDataLength = (Dcm_MsgLenType)Dcm_P_u2Sid2c_Res_Max_Data_Length;

    /* Check limit */
    if( (Dcm_MsgLenType)(u4TotalSize + u4CurrentSize) <= u4_Sid2cResMaxDataLength ) /* no wrap around */
    {
        u1_RetVal = E_OK;
    }

    return u1_RetVal;
}
#endif /*  DCM_PERIODIC_DDDID_USE == STD_OFF  */
#endif /*  DCM_SUPPORT_SID2C == STD_ON  */

#if ( DCM_NVM_DDDID_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_InitSourceElementId                       */
/* Description   | SourceElement initialization                             */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_DidMng_InitSourceElementId
(
    void
)
{
    Dcm_Dsp_DidMng_ClrSourceElementId();

    return ;
}
#endif /* DCM_NVM_DDDID_USE == STD_ON */
#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-07-27                                              */
/*  v3-0-0         :2019-09-26                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-4-0         :2023-06-28                                              */
/*  v5-6-0         :2024-02-27                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

