/* Dcm_Dsp_DidMng_OBD_c(v5-3-0)                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_DidMng_OBD/CODE                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include <Dcm.h>

#if( DCM_OBD_RANGE_DID_USE == STD_ON )

#include <Dcm/Dcm_Dsp_DidMng_OBD.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSP_DIDMNG_OBD_READ_DATA_NONE        ((uint8)0x00U)
#define DCM_DSP_DIDMNG_OBD_READ_DATA_OK          ((uint8)0x01U)
#define DCM_DSP_DIDMNG_OBD_READ_OVER_FLOW        ((uint8)0x02U)
#define DCM_DSP_DIDMNG_OBD_READ_DATA_PENDING     ((uint8)0x03U)
#define DCM_DSP_DIDMNG_OBD_READ_DATA_NOT_OK      ((uint8)0x04U)

#define DCM_DSP_DIDMNG_OBD_OBDDIDKIND_SUPPORT    ((uint8)0x00U)
#define DCM_DSP_DIDMNG_OBD_OBDDIDKIND_NORMAL     ((uint8)0x01U)

#define DCM_DSP_DIDMNG_OBD_NODI_SIZE             ((uint32)1U)
#define DCM_DSP_DIDMNG_OBD_SUP_DATALEN           ((uint32)4U)
#define DCM_DSP_DIDMNG_OBD_READ_OFS              ((uint32)2U)
#define DCM_DSP_DIDMNG_OBD_DID_MASK_HI           ((uint16)0xFF00U)
#define DCM_DSP_DIDMNG_OBD_DID_MASK_LO           ((uint16)0x00FFU)
#define DCM_DSP_DIDMNG_OBD_DID_PID_HI            ((uint16)0xF400U)
#define DCM_DSP_DIDMNG_OBD_DID_OBDMID_HI         ((uint16)0xF600U)
#define DCM_DSP_DIDMNG_OBD_DID_INFOTYPE_HI       ((uint16)0xF800U)
#define DCM_DSP_DIDMNG_OBD_SUPPORT_MASK          ((uint8)0x1FU)
#define DCM_DSP_DIDMNG_OBD_KIND_SUPPORT          ((uint8)0x00U)
#define DCM_DSP_DIDMNG_OBD_DTRDATA_SIZE          ((uint8)8U)
#define DCM_DSP_DIDMNG_OBD_DATA_POS_0            ((uint8)0U)
#define DCM_DSP_DIDMNG_OBD_DATA_POS_1            ((uint8)1U)
#define DCM_DSP_DIDMNG_OBD_DATA_POS_2            ((uint8)2U)
#define DCM_DSP_DIDMNG_OBD_DATA_POS_3            ((uint8)3U)
#define DCM_DSP_DIDMNG_OBD_BITSHIFT_8            ((uint8)8U)
#define DCM_DSP_DIDMNG_OBD_BITSHIFT_16           ((uint8)16U)
#define DCM_DSP_DIDMNG_OBD_BITSHIFT_24           ((uint8)24U)
#define DCM_DSP_DIDMNG_OBD_DATA_POS_UASID        ((uint8)1U)
#define DCM_DSP_DIDMNG_OBD_DATA_POS_TESTVAL_H    ((uint8)2U)
#define DCM_DSP_DIDMNG_OBD_DATA_POS_TESTVAL_L    ((uint8)3U)
#define DCM_DSP_DIDMNG_OBD_DATA_POS_LLIMVAL_H    ((uint8)4U)
#define DCM_DSP_DIDMNG_OBD_DATA_POS_LLIMVAL_L    ((uint8)5U)
#define DCM_DSP_DIDMNG_OBD_DATA_POS_ULIMVAL_H    ((uint8)6U)
#define DCM_DSP_DIDMNG_OBD_DATA_POS_ULIMVAL_L    ((uint8)7U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC( uint8, DCM_CODE ) Dcm_Dsp_DidMng_OBD_CheckIdKind
(
    const uint8 u1ObdDid
);
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_OBD_GetPidDataLen
(
    const uint8 u1Pid,
    P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA)ptDataLength
);
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_OBD_GetObdmidDataLen
(
    const uint8 u1Obdmid,
    P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA)ptDataLength
);
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_OBD_GetInfoTypeDataLen
(
    const uint8 u1InfoType,
    P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA)ptDataLength
);
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_DidMng_OBD_CallReadPidDidFnc
(
    const uint8  u1Pid,
    const uint32 u4DataBufferLength,
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA ) ptData,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptDataLength
);
#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_OFF )
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_DidMng_OBD_CallReadObdmidDidFnc
(
    const uint8  u1Obdmid,
    const uint32 u4DataBufferLength,
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA ) ptData,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptDataLength
);
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_OFF */
#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON )
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_DidMng_OBD_CallReadObdmidDidFnc
(
    const uint8  u1Obdmid,
    const Dcm_OpStatusType u1OpStatus,
    const uint32 u4DataBufferLength,
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA ) ptData,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptDataLength
);
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON */
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_DidMng_OBD_CallReadInfoTypeDidFnc
(
    const uint8 u1InfoType,
    const Dcm_OpStatusType u1OpStatus,
    const uint32 u4DataBufferLength,
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA ) ptData,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptDataLength
);
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_DidMng_OBD_MakePidSupData
(
    const uint8 u1Pid,
    const uint32 u4DataBufferLength,
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA ) ptData,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptDataLength
);
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_DidMng_OBD_MakeNormalPidData
(
    const uint8 u1PidTableIndex,
    const uint32 u4DataBufferLength,
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA ) ptData,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptDataLength
);
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_DidMng_OBD_MakeObdmidSupData
(
    const uint8 u1Obdmid,
    const uint32 u4DataBufferLength,
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA ) ptData,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptDataLength
);
#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_OFF )
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_DidMng_OBD_MakeDTRData
(
    const uint8 u1Obdmid,
    const uint8 u1NumberOfTIDs,
    const uint32 u4DataBufferLength,
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA ) ptData,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptDataLength
);
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_OFF */
#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON )
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_DidMng_OBD_MakeDTRData
(
    const uint8 u1Obdmid,
    const Dcm_OpStatusType u1OpStatus,
    const uint8 u1NumberOfTIDs,
    const uint32 u4DataBufferLength,
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA ) ptData,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptDataLength
);
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON */

static FUNC( uint8, DCM_CODE ) Dcm_Dsp_DidMng_OBD_MakeSupInfTypData
(
    CONST( Dcm_MsgItemType, AUTOMATIC ) u1reqInfoType,
    const uint32 u4DataBufferLength,
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA ) ptData,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptDataLength
);
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_DidMng_OBD_MakeNormInfTypDEM
(
    CONST( Dcm_OpStatusType, AUTOMATIC ) u1OpStatus,
    CONST( Dcm_MsgItemType, AUTOMATIC ) u1reqInfoType,
    const uint8 u1InfoTypeTblIndex,
    const uint32 u4DataBufferLength,
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA ) ptData,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptDataLength
);
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_DidMng_OBD_MakeNormInfTypDat
(
    CONST( Dcm_OpStatusType, AUTOMATIC ) u1OpStatus,
    CONST( Dcm_MsgItemType, AUTOMATIC ) u1reqInfoType,
    const uint8 u1InfoTypeTblIndex,
    const uint32 u4DataBufferLength,
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA ) ptData,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptDataLength
);

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

static VAR( Dcm_MsgLenType, DCM_VAR_NO_INIT ) Dcm_Dsp_DidMng_OBD_u4PendingDataLen;
static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Dsp_DidMng_OBD_u1PendingElement;
#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON )
static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Dsp_DidMng_OBD_NumOfExtantTid;
static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Dsp_DidMng_OBD_NumOfReadTid;
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON */

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

/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_OBD_ClrForEachReq                         */
/* Description   | Clear values for each request                            */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_DidMng_OBD_ClrForEachReq
(
    void
)
{
    Dcm_Dsp_DidMng_OBD_ClearHist();

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_OBD_ChkObdDid                             */
/* Description   | Find Did                                                 */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2Did : Reqest Data Id                              */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : OBDDID is valid                            */
/*               |        E_NOT_OK : OBDDID is invalid                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_OBD_ChkObdDid
(
    const uint16 u2Did
)
{
    uint16                     u2_DidHiByte;
    uint8                      u1_DidLoByte;
    Std_ReturnType             u1_RetVal;

    u1_RetVal    = (Std_ReturnType)E_NOT_OK;
    u2_DidHiByte = (uint16)( u2Did & DCM_DSP_DIDMNG_OBD_DID_MASK_HI );
    u1_DidLoByte = (uint8)( u2Did & DCM_DSP_DIDMNG_OBD_DID_MASK_LO );

    if( u2_DidHiByte == DCM_DSP_DIDMNG_OBD_DID_PID_HI )
    {
        /* PID */
        u1_RetVal = Dcm_Dsp_DidMng_OBD_ChkSupPid( u1_DidLoByte );
    }
    else if( u2_DidHiByte == DCM_DSP_DIDMNG_OBD_DID_OBDMID_HI )
    {
        /* OBDMID */
        u1_RetVal = Dcm_Dsp_DidMng_OBD_ChkSupObdmid( u1_DidLoByte );
    }
    else if( u2_DidHiByte == DCM_DSP_DIDMNG_OBD_DID_INFOTYPE_HI )
    {
        /* INFOTYPE */
        u1_RetVal = Dcm_Dsp_DidMng_OBD_ChkSupInfoType( u1_DidLoByte );
    }
    else
    {
        /* no process */
    }
    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_OBD_GetObdDidDataLen                      */
/* Description   | Get OBDMID Data Length                                   */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2Did : Reqest Data Id                              */
/*               | [out] ptDataLength : Data Length                         */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Process complete                           */
/*               |        E_NOT_OK : Process abnormal termination           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_OBD_GetObdDidDataLen
(
    const uint16  u2Did,
    P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA)ptDataLength
)
{
    uint16                     u2_DidHiByte;
    uint8                      u1_DidLoByte;
    Std_ReturnType             u1_RetVal;

    u1_RetVal    = (Std_ReturnType)E_NOT_OK;
    u2_DidHiByte = (uint16)( u2Did & DCM_DSP_DIDMNG_OBD_DID_MASK_HI );
    u1_DidLoByte = (uint8)( u2Did & DCM_DSP_DIDMNG_OBD_DID_MASK_LO );

    if( u2_DidHiByte == DCM_DSP_DIDMNG_OBD_DID_PID_HI )
    {
        /* PID */
        u1_RetVal = Dcm_Dsp_DidMng_OBD_GetPidDataLen( u1_DidLoByte, ptDataLength );
    }
    else if( u2_DidHiByte == DCM_DSP_DIDMNG_OBD_DID_OBDMID_HI )
    {
        /* OBDMID */
        u1_RetVal = Dcm_Dsp_DidMng_OBD_GetObdmidDataLen( u1_DidLoByte, ptDataLength );
    }
    else if( u2_DidHiByte == DCM_DSP_DIDMNG_OBD_DID_INFOTYPE_HI )
    {
        /* INFOTYPE */
        u1_RetVal = Dcm_Dsp_DidMng_OBD_GetInfoTypeDataLen( u1_DidLoByte, ptDataLength );
    }
    else
    {
        /* no process */
    }
    return u1_RetVal;
}

#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_OFF )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_OBD_CallReadObdDidFnc                     */
/* Description   | Read OBDDID Data                                         */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2Did      : DID                                    */
/*               | [in] u1OpStatus : Operation state                        */
/*               | [in] u4DataBufferLength : Buffer Length                  */
/*               | [out] ptData : Start pointer of read data                */
/*               | [out] ptDataLength : Read Data Length                    */
/*               | [out] ptErrorCode : Negative Response Code               */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Process complete                           */
/*               |        E_NOT_OK : Process abnormal termination           */
/*               |        DCM_E_PENDING : Process pending                   */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_OBD_CallReadObdDidFnc
(
    const uint16 u2Did,
    const Dcm_OpStatusType u1OpStatus,
    const uint32 u4DataBufferLength,
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA ) ptData,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptDataLength,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode
)
{
    uint16                     u2_DidHiByte;
    uint8                      u1_DidLoByte;
    uint8                      u1_RetReadData;
    Std_ReturnType             u1_RetVal;

    u1_RetVal      = (Std_ReturnType)E_NOT_OK;
    u2_DidHiByte   = (uint16)( u2Did & DCM_DSP_DIDMNG_OBD_DID_MASK_HI );
    u1_DidLoByte   = (uint8)( u2Did & DCM_DSP_DIDMNG_OBD_DID_MASK_LO );

    if( u2_DidHiByte == DCM_DSP_DIDMNG_OBD_DID_PID_HI )
    {
        /* PID */
        u1_RetReadData = Dcm_Dsp_DidMng_OBD_CallReadPidDidFnc( u1_DidLoByte, u4DataBufferLength, ptData, ptDataLength );
    }
    else if( u2_DidHiByte == DCM_DSP_DIDMNG_OBD_DID_OBDMID_HI )
    {
        /* OBDMID */
        u1_RetReadData = Dcm_Dsp_DidMng_OBD_CallReadObdmidDidFnc( u1_DidLoByte, u4DataBufferLength, ptData, ptDataLength );
    }
    else if( u2_DidHiByte == DCM_DSP_DIDMNG_OBD_DID_INFOTYPE_HI )
    {
        /* INFOTYPE */
        u1_RetReadData = Dcm_Dsp_DidMng_OBD_CallReadInfoTypeDidFnc( u1_DidLoByte, u1OpStatus, u4DataBufferLength, ptData, ptDataLength );
    }
    else
    {
        u1_RetReadData = DCM_DSP_DIDMNG_OBD_READ_DATA_NOT_OK;
    }

    if( u1_RetReadData == DCM_DSP_DIDMNG_OBD_READ_DATA_OK )
    {
        u1_RetVal = (Std_ReturnType)E_OK;
    }
    else if( u1_RetReadData == DCM_DSP_DIDMNG_OBD_READ_DATA_NONE )
    {
        *ptDataLength = (uint32)0U;
        u1_RetVal = (Std_ReturnType)E_OK;
    }
    else if( u1_RetReadData == DCM_DSP_DIDMNG_OBD_READ_DATA_PENDING )
    {
        u1_RetVal = (Std_ReturnType)DCM_E_PENDING;
    }
    else if( u1_RetReadData == DCM_DSP_DIDMNG_OBD_READ_OVER_FLOW )
    {
        *ptErrorCode = DCM_E_RESPONSETOOLONG;
    }
    else
    {
        *ptErrorCode = DCM_E_GENERALREJECT;
    }

    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_OFF */
#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_OBD_CallReadObdDidFnc                     */
/* Description   | Read OBDDID Data                                         */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2Did      : DID                                    */
/*               | [in] u1OpStatus : Operation state                        */
/*               | [in] u4DataBufferLength : Buffer Length                  */
/*               | [out] ptData : Start pointer of read data                */
/*               | [out] ptDataLength : Read Data Length                    */
/*               | [out] ptErrorCode : Negative Response Code               */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Process complete                           */
/*               |        E_NOT_OK : Process abnormal termination           */
/*               |        DCM_E_PENDING : Process pending                   */
/*               |        DCM_E_UPDATE_PAGE : Update Page                   */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_OBD_CallReadObdDidFnc
(
    const uint16 u2Did,
    const Dcm_OpStatusType u1OpStatus,
    const uint32 u4DataBufferLength,
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA ) ptData,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptDataLength,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode
)
{
    uint16                     u2_DidHiByte;
    uint8                      u1_DidLoByte;
    uint8                      u1_RetReadData;
    Std_ReturnType             u1_RetVal;

    u1_RetVal      = (Std_ReturnType)E_NOT_OK;
    u2_DidHiByte   = (uint16)( u2Did & DCM_DSP_DIDMNG_OBD_DID_MASK_HI );
    u1_DidLoByte   = (uint8)( u2Did & DCM_DSP_DIDMNG_OBD_DID_MASK_LO );

    if( u2_DidHiByte == DCM_DSP_DIDMNG_OBD_DID_PID_HI )
    {
        /* PID */
        u1_RetReadData = Dcm_Dsp_DidMng_OBD_CallReadPidDidFnc( u1_DidLoByte, u4DataBufferLength, ptData, ptDataLength );
    }
    else if( u2_DidHiByte == DCM_DSP_DIDMNG_OBD_DID_OBDMID_HI )
    {
        /* OBDMID */
        u1_RetReadData = Dcm_Dsp_DidMng_OBD_CallReadObdmidDidFnc( u1_DidLoByte, u1OpStatus, u4DataBufferLength, ptData, ptDataLength );
    }
    else if( u2_DidHiByte == DCM_DSP_DIDMNG_OBD_DID_INFOTYPE_HI )
    {
        /* INFOTYPE */
        u1_RetReadData = Dcm_Dsp_DidMng_OBD_CallReadInfoTypeDidFnc( u1_DidLoByte, u1OpStatus, u4DataBufferLength, ptData, ptDataLength );
    }
    else
    {
        u1_RetReadData = DCM_DSP_DIDMNG_OBD_READ_DATA_NOT_OK;
    }

    if( u1_RetReadData == DCM_DSP_DIDMNG_OBD_READ_DATA_OK )
    {
        u1_RetVal = (Std_ReturnType)E_OK;
    }
    else if( u1_RetReadData == DCM_DSP_DIDMNG_OBD_READ_DATA_NONE )
    {
        *ptDataLength = (uint32)0U;
        u1_RetVal = (Std_ReturnType)E_OK;
    }
    else if( u1_RetReadData == DCM_DSP_DIDMNG_OBD_READ_DATA_PENDING )
    {
        u1_RetVal = (Std_ReturnType)DCM_E_PENDING;
    }
    else if( u1_RetReadData == DCM_DSP_DIDMNG_OBD_READ_OVER_FLOW )
    {
        u1_RetVal = (Std_ReturnType)DCM_E_UPDATE_PAGE;
    }
    else
    {
        *ptErrorCode = DCM_E_GENERALREJECT;
    }

    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON */

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_OBD_CheckIdKind                           */
/* Description   | Check Obdmid Kind SupportObdmid or NormalObdmid          */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1ObdDid             : Lower 1byte of Did           */
/* Return Value  | uint8                                                    */
/*               |   DCM_DSP_DIDMNG_OBD_OBDDIDKIND_SUPPORT: Support ObdDid  */
/*               |   DCM_DSP_DIDMNG_OBD_OBDDIDKIND_NORMAL : Normal ObdDid   */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_DidMng_OBD_CheckIdKind
(
    const uint8 u1ObdDid
)
{
    uint8 u1_ObdDidKind;

    u1_ObdDidKind = DCM_DSP_DIDMNG_OBD_OBDDIDKIND_NORMAL;

    if( (uint8)( u1ObdDid & DCM_DSP_DIDMNG_OBD_SUPPORT_MASK ) == DCM_DSP_DIDMNG_OBD_KIND_SUPPORT )
    {
        u1_ObdDidKind = DCM_DSP_DIDMNG_OBD_OBDDIDKIND_SUPPORT;
    }

    return u1_ObdDidKind;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_OBD_GetPidDataLen                         */
/* Description   | Get PID Data Length                                      */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1Pid : Reqest PID                                  */
/*               | [out] ptDataLength : Data Length                         */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Process complete                           */
/*               |        E_NOT_OK : Process abnormal termination           */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_OBD_GetPidDataLen
(
    const uint8 u1Pid,
    P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA)ptDataLength
)
{
    uint8          u1_PidKind;
    uint8          u1_PidTableIndex;
    Std_ReturnType u1_RetGetIndex;
    Std_ReturnType u1_RetVal;

    u1_RetVal       = (Std_ReturnType)E_NOT_OK;
    *ptDataLength   = (uint32)0U;
    u1_PidKind      = Dcm_Dsp_DidMng_OBD_CheckIdKind( u1Pid );

    if( u1_PidKind == DCM_DSP_DIDMNG_OBD_OBDDIDKIND_SUPPORT )
    {
        *ptDataLength = DCM_DSP_DIDMNG_OBD_SUP_DATALEN;
        u1_RetVal = (Std_ReturnType)E_OK;
    }
    else
    {
        u1_RetGetIndex = Dcm_Dsp_DidMng_OBD_GetPidDataInfoIdx( u1Pid, &u1_PidTableIndex );
        if( u1_RetGetIndex == (Std_ReturnType)E_OK )
        {
            *ptDataLength = Dcm_Dsp_DidMng_OBD_GetPidDataSize( u1_PidTableIndex );
            u1_RetVal = (Std_ReturnType)E_OK;
        }
    }
    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_OBD_GetObdmidDataLen                      */
/* Description   | Get OBDMID Data Length                                   */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1Obdmid : Reqest Obdmid                            */
/*               | [out] ptDataLength : Data Length                         */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Process complete                           */
/*               |        E_NOT_OK : Process abnormal termination           */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_OBD_GetObdmidDataLen
(
    const uint8 u1Obdmid,
    P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA)ptDataLength
)
{
    uint8          u1_ObdmidKind;
    uint8          u1_TidNum;
    Std_ReturnType u1_RetGetTidNum;
    Std_ReturnType u1_RetVal;

    u1_RetVal     = (Std_ReturnType)E_NOT_OK;
    *ptDataLength = (uint32)0U;
    u1_ObdmidKind = Dcm_Dsp_DidMng_OBD_CheckIdKind( u1Obdmid );

    if( u1_ObdmidKind == DCM_DSP_DIDMNG_OBD_OBDDIDKIND_SUPPORT )
    {
        *ptDataLength = DCM_DSP_DIDMNG_OBD_SUP_DATALEN;
        u1_RetVal = (Std_ReturnType)E_OK;
    }
    else
    {
        u1_RetGetTidNum = Dcm_Dsp_DidMng_OBD_GetNumTIDsOfOBDMID( u1Obdmid, &u1_TidNum );
        if( u1_RetGetTidNum == (Std_ReturnType)E_OK )
        {
            if( u1_TidNum > (uint8)0U )
            {
                *ptDataLength = (uint32)( (uint32)u1_TidNum * (uint32)DCM_DSP_DIDMNG_OBD_DTRDATA_SIZE ); /* no wrap around */
                u1_RetVal = (Std_ReturnType)E_OK;
            }
        }
    }
    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_OBD_GetInfoTypeDataLen                    */
/* Description   | Get INFOTYPE Data Length                                 */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1InfoType : Reqest InfoType                        */
/*               | [out] ptDataLength : Data Length                         */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Process complete                           */
/*               |        E_NOT_OK : Process abnormal termination           */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_OBD_GetInfoTypeDataLen
(
    const uint8 u1InfoType,
    P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA)ptDataLength
)
{
    uint32         u4_DataLen;
    uint8          u1_InfoTypeKind;
    uint8          u1_InfoTypeTableIndex;
    uint8          u1_NumOfVehInfoData;
    uint8          u1_InfoTypeSize;
    uint8          u1_VehInfoInterNODI;
    uint8          u1_Cnt;
    Std_ReturnType u1_RetGetIndex;
    Std_ReturnType u1_RetVal;

    u1_RetVal       = (Std_ReturnType)E_NOT_OK;
    *ptDataLength   = (uint32)0U;
    u4_DataLen      = *ptDataLength;
    u1_InfoTypeKind = Dcm_Dsp_DidMng_OBD_CheckIdKind( u1InfoType );

    if( u1_InfoTypeKind == DCM_DSP_DIDMNG_OBD_OBDDIDKIND_SUPPORT )
    {
        *ptDataLength = DCM_DSP_DIDMNG_OBD_SUP_DATALEN;
        u1_RetVal = (Std_ReturnType)E_OK;
    }
    else
    {
        u1_RetGetIndex = Dcm_Dsp_DidMng_OBD_GetInfTypTableIdx( u1InfoType, &u1_InfoTypeTableIndex );
        if( u1_RetGetIndex == (Std_ReturnType)E_OK )
        {
            u1_NumOfVehInfoData = Dcm_Dsp_DidMng_OBD_GetNumOfInfoType( u1_InfoTypeTableIndex );
            for( u1_Cnt = (uint8)0U; u1_Cnt < u1_NumOfVehInfoData; u1_Cnt++ )
            {
                u1_InfoTypeSize = Dcm_Dsp_DidMng_OBD_GetInfoTypeDataSize( u1_InfoTypeTableIndex, u1_Cnt );
                u4_DataLen += (uint32)u1_InfoTypeSize; /* no wrap around */
            }
            if( u4_DataLen > (uint32)0U )
            {
                u1_VehInfoInterNODI = Dcm_Dsp_DidMng_OBD_GetInfoTypeInterNODI( u1_InfoTypeTableIndex );
                if( u1_VehInfoInterNODI == (uint8)STD_OFF )
                {
                    u4_DataLen -= DCM_DSP_DIDMNG_OBD_NODI_SIZE;
                }
                *ptDataLength = u4_DataLen;
                u1_RetVal = (Std_ReturnType)E_OK;
            }
        }
    }
    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_OBD_CallReadPidDidFnc                     */
/* Description   | Read PID Data                                            */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1Pid : Reqest PID                                  */
/*               | [in] u4DataBufferLength : Buffer Length                  */
/*               | [out] ptData : Start pointer of read data                */
/*               | [out] ptDataLength : Read Data Length                    */
/*               |                                                          */
/* Return Value  | uint8                                                    */
/*               |   DCM_DSP_DIDMNG_OBD_READ_DATA_NONE    : Read Data None  */
/*               |   DCM_DSP_DIDMNG_OBD_READ_DATA_OK      : Read Data OK    */
/*               |   DCM_DSP_DIDMNG_OBD_READ_OVER_FLOW    : Over Flow       */
/*               |   DCM_DSP_DIDMNG_OBD_READ_DATA_NOT_OK  : Read Data NG    */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_DidMng_OBD_CallReadPidDidFnc
(
    const uint8  u1Pid,
    const uint32 u4DataBufferLength,
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA ) ptData,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptDataLength
)
{
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )    pt_ReadData;
    uint32         u4_DataBufferLen;
    uint8          u1_PidKind;
    uint8          u1_PidTableIndex;
    uint8          u1_RetVal;
    Std_ReturnType u1_RetGetIndex;

    u1_RetVal        = DCM_DSP_DIDMNG_OBD_READ_DATA_NOT_OK;
    *ptDataLength    = (uint32)0U;
    u1_PidKind       = Dcm_Dsp_DidMng_OBD_CheckIdKind( u1Pid );
    pt_ReadData      = &ptData[DCM_DSP_DIDMNG_OBD_READ_OFS];
    u4_DataBufferLen = u4DataBufferLength - DCM_DSP_DIDMNG_OBD_READ_OFS; /* no wrap around */

    if( u1_PidKind == DCM_DSP_DIDMNG_OBD_OBDDIDKIND_SUPPORT )
    {
        /* Set Support PID Data */
        u1_RetVal = Dcm_Dsp_DidMng_OBD_MakePidSupData( u1Pid, u4_DataBufferLen, pt_ReadData, ptDataLength );
    }
    else
    {
        /* Set Normal PID Data */
        u1_RetGetIndex = Dcm_Dsp_DidMng_OBD_GetPidDataInfoIdx( u1Pid, &u1_PidTableIndex );
        if( u1_RetGetIndex == (Std_ReturnType)E_OK )
        {
            u1_RetVal = Dcm_Dsp_DidMng_OBD_MakeNormalPidData( u1_PidTableIndex, u4_DataBufferLen, pt_ReadData, ptDataLength );
        }
    }
    if( u1_RetVal == DCM_DSP_DIDMNG_OBD_READ_DATA_OK )
    {
        *ptDataLength += DCM_DSP_DIDMNG_OBD_READ_OFS; /* no wrap around */
    }
    return u1_RetVal;
}

#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_OFF )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_OBD_CallReadObdmidDidFnc                  */
/* Description   | Read OBDMID Data                                         */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1Obdmid : Reqest Obdmid                            */
/*               | [in] u4DataBufferLength : Buffer Length                  */
/*               | [out] ptData : Start pointer of read data                */
/*               | [out] ptDataLength : Read Data Length                    */
/*               |                                                          */
/* Return Value  | uint8                                                    */
/*               |   DCM_DSP_DIDMNG_OBD_READ_DATA_NONE    : Read Data None  */
/*               |   DCM_DSP_DIDMNG_OBD_READ_DATA_OK      : Read Data OK    */
/*               |   DCM_DSP_DIDMNG_OBD_READ_OVER_FLOW    : Over Flow       */
/*               |   DCM_DSP_DIDMNG_OBD_READ_DATA_NOT_OK  : Read Data NG    */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_DidMng_OBD_CallReadObdmidDidFnc
(
    const uint8  u1Obdmid,
    const uint32 u4DataBufferLength,
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA ) ptData,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptDataLength
)
{
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )    pt_ReadData;
    uint32         u4_DataBufferLen;
    uint8          u1_ObdmidKind;
    uint8          u1_TidNum;
    uint8          u1_RetVal;
    Std_ReturnType u1_RetGetTidNum;

    u1_RetVal        = DCM_DSP_DIDMNG_OBD_READ_DATA_NOT_OK;
    *ptDataLength    = (uint32)0U;
    u1_ObdmidKind    = Dcm_Dsp_DidMng_OBD_CheckIdKind( u1Obdmid );
    pt_ReadData      = &ptData[DCM_DSP_DIDMNG_OBD_READ_OFS];
    u4_DataBufferLen = u4DataBufferLength - DCM_DSP_DIDMNG_OBD_READ_OFS; /* no wrap around */

    if( u1_ObdmidKind == DCM_DSP_DIDMNG_OBD_OBDDIDKIND_SUPPORT )
    {
        /* Set Support Obdmid Data */
        u1_RetVal = Dcm_Dsp_DidMng_OBD_MakeObdmidSupData( u1Obdmid, u4_DataBufferLen, pt_ReadData, ptDataLength );
    }
    else
    {
        /* Set Normal Obdmid Data */
        u1_RetGetTidNum = Dcm_Dsp_DidMng_OBD_GetNumTIDsOfOBDMID( u1Obdmid, &u1_TidNum );
        if( u1_RetGetTidNum == (Std_ReturnType)E_OK )
        {
            if( u1_TidNum > (uint8)0U )
            {
                u1_RetVal = Dcm_Dsp_DidMng_OBD_MakeDTRData( u1Obdmid, u1_TidNum, u4_DataBufferLen, pt_ReadData, ptDataLength );
            }
            else
            {
                u1_RetVal = DCM_DSP_DIDMNG_OBD_READ_DATA_NONE;
            }
        }
    }
    if( u1_RetVal == DCM_DSP_DIDMNG_OBD_READ_DATA_OK )
    {
        *ptDataLength += DCM_DSP_DIDMNG_OBD_READ_OFS; /* no wrap around */
    }
    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_OFF */
#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_OBD_CallReadObdmidDidFnc                  */
/* Description   | Read OBDMID Data                                         */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1Obdmid : Reqest Obdmid                            */
/*               | [in] u1OpStatus : Operation state                        */
/*               | [in] u4DataBufferLength : Buffer Length                  */
/*               | [out] ptData : Start pointer of read data                */
/*               | [out] ptDataLength : Read Data Length                    */
/*               |                                                          */
/* Return Value  | uint8                                                    */
/*               |   DCM_DSP_DIDMNG_OBD_READ_DATA_NONE    : Read Data None  */
/*               |   DCM_DSP_DIDMNG_OBD_READ_DATA_OK      : Read Data OK    */
/*               |   DCM_DSP_DIDMNG_OBD_READ_OVER_FLOW    : Over Flow       */
/*               |   DCM_DSP_DIDMNG_OBD_READ_DATA_NOT_OK  : Read Data NG    */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_DidMng_OBD_CallReadObdmidDidFnc
(
    const uint8  u1Obdmid,
    const Dcm_OpStatusType u1OpStatus,
    const uint32 u4DataBufferLength,
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA ) ptData,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptDataLength
)
{
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )    pt_ReadData;
    uint32         u4_DataBufferLen;
    uint8          u1_ObdmidKind;
    uint8          u1_TidNum;
    uint8          u1_RetVal;
    Std_ReturnType u1_RetGetTidNum;

    u1_RetVal        = DCM_DSP_DIDMNG_OBD_READ_DATA_NOT_OK;
    *ptDataLength    = (uint32)0U;
    u1_ObdmidKind    = Dcm_Dsp_DidMng_OBD_CheckIdKind( u1Obdmid );

    if( u1_ObdmidKind == DCM_DSP_DIDMNG_OBD_OBDDIDKIND_SUPPORT )
    {
        pt_ReadData      = &ptData[DCM_DSP_DIDMNG_OBD_READ_OFS];
        u4_DataBufferLen = u4DataBufferLength - DCM_DSP_DIDMNG_OBD_READ_OFS; /* no wrap around */
        /* Set Support Obdmid Data */
        u1_RetVal = Dcm_Dsp_DidMng_OBD_MakeObdmidSupData( u1Obdmid, u4_DataBufferLen, pt_ReadData, ptDataLength );
    }
    else
    {
        if( u1OpStatus == DCM_INITIAL )
        {
            pt_ReadData      = &ptData[DCM_DSP_DIDMNG_OBD_READ_OFS];
            u4_DataBufferLen = u4DataBufferLength - DCM_DSP_DIDMNG_OBD_READ_OFS; /* no wrap around */
            /* Dcm_Dsp_DidMng_OBD_NumOfExtantTid Initialyze      */
            Dcm_Dsp_DidMng_OBD_NumOfExtantTid = (uint8)0U;
            /* Set Normal Obdmid Data */
            u1_RetGetTidNum = Dcm_Dsp_DidMng_OBD_GetNumTIDsOfOBDMID( u1Obdmid, &u1_TidNum );
            if( u1_RetGetTidNum == (Std_ReturnType)E_OK )
            {
                if( u1_TidNum > (uint8)0U )
                {
                    Dcm_Dsp_DidMng_OBD_NumOfExtantTid = u1_TidNum;
                    u1_RetVal = Dcm_Dsp_DidMng_OBD_MakeDTRData( u1Obdmid, u1OpStatus, u1_TidNum, u4_DataBufferLen, pt_ReadData, ptDataLength );
                }
                else
                {
                    u1_RetVal = DCM_DSP_DIDMNG_OBD_READ_DATA_NONE;
                }
            }
        }
        else if( u1OpStatus == DCM_UPDATE_PAGE_OK )
        {
            pt_ReadData      = ptData;
            u4_DataBufferLen = u4DataBufferLength;
            u1_TidNum = Dcm_Dsp_DidMng_OBD_NumOfExtantTid;
            u1_RetVal = Dcm_Dsp_DidMng_OBD_MakeDTRData( u1Obdmid, u1OpStatus, u1_TidNum, u4_DataBufferLen, pt_ReadData, ptDataLength );
        }
        else
        {
            /* No process */
        }
    }

    if( u1OpStatus == DCM_INITIAL )
    {
        if( ( u1_RetVal == DCM_DSP_DIDMNG_OBD_READ_DATA_OK ) || ( u1_RetVal == DCM_DSP_DIDMNG_OBD_READ_OVER_FLOW ) )
        {
            if( *ptDataLength != (uint32)0U )
            {
                *ptDataLength += DCM_DSP_DIDMNG_OBD_READ_OFS; /* no wrap around */
            }
        }
    }
    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_OBD_CallReadInfoTypeDidFnc                */
/* Description   | Read InfoType Data                                       */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1InfoType : Reqest InfoType                        */
/*               | [in] u1OpStatus : Operation state                        */
/*               | [in] u4DataBufferLength : Buffer Length                  */
/*               | [out] ptData : Start pointer of read data                */
/*               | [out] ptDataLength : Read Data Length                    */
/*               |                                                          */
/* Return Value  | uint8                                                    */
/*               |   DCM_DSP_DIDMNG_OBD_READ_DATA_NONE    : Read Data None  */
/*               |   DCM_DSP_DIDMNG_OBD_READ_DATA_OK      : Read Data OK    */
/*               |   DCM_DSP_DIDMNG_OBD_READ_OVER_FLOW    : Over Flow       */
/*               |   DCM_DSP_DIDMNG_OBD_READ_DATA_PENDING : Pending         */
/*               |   DCM_DSP_DIDMNG_OBD_READ_DATA_NOT_OK  : Read Data NG    */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_DidMng_OBD_CallReadInfoTypeDidFnc
(
    const uint8 u1InfoType,
    const Dcm_OpStatusType u1OpStatus,
    const uint32 u4DataBufferLength,
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA ) ptData,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptDataLength
)
{
    uint8            u1_InfoTypeKind;
    uint8            u1_InfoTypeTableIndex;
    uint8            u1_WritableSize;
    uint8            u1_RetVal;
    Std_ReturnType   u1_RetGetIndex;
    Dcm_OpStatusType u1_opStatus;
    boolean          b_IsDemCall;

    u1_RetVal       = DCM_DSP_DIDMNG_OBD_READ_DATA_NOT_OK;
    *ptDataLength   = (uint32)0U;
    u1_InfoTypeKind = Dcm_Dsp_DidMng_OBD_CheckIdKind( u1InfoType );

    if( u1_InfoTypeKind == DCM_DSP_DIDMNG_OBD_OBDDIDKIND_SUPPORT )
    {
        u1_RetVal = Dcm_Dsp_DidMng_OBD_MakeSupInfTypData( u1InfoType, u4DataBufferLength, ptData, ptDataLength );
    }
    else
    {
        u1_InfoTypeTableIndex = (uint8)0U;
        u1_RetGetIndex = Dcm_Dsp_DidMng_OBD_GetInfTypTableIdx( u1InfoType, &u1_InfoTypeTableIndex );
        if( u1_RetGetIndex == (Std_ReturnType)E_OK )
        {
            u1_opStatus   = u1OpStatus;
            if( u1_opStatus != DCM_CANCEL )
            {
                if( u1OpStatus == DCM_INITIAL )
                {
                    Dcm_Dsp_DidMng_OBD_u1PendingElement = (uint8)0U;
                    Dcm_Dsp_DidMng_OBD_u4PendingDataLen = (Dcm_MsgLenType)0U;
                }
                b_IsDemCall = Dcm_Dsp_DidMng_OBD_JudgeDemIUMPRUse( u1InfoType );
                if( b_IsDemCall ==  (boolean)TRUE )
                {
                    u1_RetVal = Dcm_Dsp_DidMng_OBD_MakeNormInfTypDEM( u1OpStatus, u1InfoType, u1_InfoTypeTableIndex, u4DataBufferLength, ptData, ptDataLength );
                }
                else
                {
                    u1_RetVal = Dcm_Dsp_DidMng_OBD_MakeNormInfTypDat( u1OpStatus, u1InfoType, u1_InfoTypeTableIndex, u4DataBufferLength, ptData,  ptDataLength );
                }
            }
            else
            {
                u1_WritableSize = (uint8)0U;
                (void)Dcm_Dsp_DidMng_OBD_CallVehInfoDataReadFnc( u1_InfoTypeTableIndex, Dcm_Dsp_DidMng_OBD_u1PendingElement, u1OpStatus, ptData ,&u1_WritableSize );    /* no return check required */
                Dcm_Dsp_DidMng_OBD_u1PendingElement = (uint8)0U;
                Dcm_Dsp_DidMng_OBD_u4PendingDataLen = (Dcm_MsgLenType)0U;
                u1_RetVal = DCM_DSP_DIDMNG_OBD_READ_DATA_OK;
            }
        }
    }
    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_OBD_MakePidSupData                        */
/* Description   | Make PID Support Data                                    */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1Pid              : Pid                            */
/*               | [in] u4DataBufferLength : Buffer Length                  */
/*               | [out] ptData            : Start pointer of read data     */
/*               | [out] ptDataLength      : Read Data Length               */
/* Return Value  | uint8                                                    */
/*               |   DCM_DSP_DIDMNG_OBD_READ_DATA_NONE    : Read Data None  */
/*               |   DCM_DSP_DIDMNG_OBD_READ_DATA_OK      : Read Data OK    */
/*               |   DCM_DSP_DIDMNG_OBD_READ_OVER_FLOW    : Over Flow       */
/*               |   DCM_DSP_DIDMNG_OBD_READ_DATA_NOT_OK  : Read Data NG    */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_DidMng_OBD_MakePidSupData
(
    const uint8 u1Pid,
    const uint32 u4DataBufferLength,
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA ) ptData,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptDataLength
)
{
    uint32         u4_PidSupportInfo;
    Std_ReturnType u1_RetGetSupPid;
    uint8          u1_RetVal;

    u1_RetVal         = DCM_DSP_DIDMNG_OBD_READ_DATA_NOT_OK;
    u4_PidSupportInfo = (uint32)0U;

    /* Buffer Over Flow Check */
    if( DCM_DSP_DIDMNG_OBD_SUP_DATALEN <= u4DataBufferLength )
    {
        u1_RetGetSupPid = Dcm_Dsp_DidMng_OBD_GetSupPidData( u1Pid, &u4_PidSupportInfo );
        if( u1_RetGetSupPid == (Std_ReturnType)E_OK )
        {
            if( u4_PidSupportInfo != ((uint32)0U) )
            {
                ptData[DCM_DSP_DIDMNG_OBD_DATA_POS_0] = (Dcm_MsgItemType)( u4_PidSupportInfo >> DCM_DSP_DIDMNG_OBD_BITSHIFT_24 );
                ptData[DCM_DSP_DIDMNG_OBD_DATA_POS_1] = (Dcm_MsgItemType)( u4_PidSupportInfo >> DCM_DSP_DIDMNG_OBD_BITSHIFT_16 );
                ptData[DCM_DSP_DIDMNG_OBD_DATA_POS_2] = (Dcm_MsgItemType)( u4_PidSupportInfo >> DCM_DSP_DIDMNG_OBD_BITSHIFT_8 );
                ptData[DCM_DSP_DIDMNG_OBD_DATA_POS_3] = (Dcm_MsgItemType)u4_PidSupportInfo;
                *ptDataLength = DCM_DSP_DIDMNG_OBD_SUP_DATALEN;
                u1_RetVal = DCM_DSP_DIDMNG_OBD_READ_DATA_OK;
            }
            else
            {
                u1_RetVal = DCM_DSP_DIDMNG_OBD_READ_DATA_NONE;
            }
        }
    }
    else
    {
        u1_RetVal = DCM_DSP_DIDMNG_OBD_READ_OVER_FLOW;
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_OBD_MakeNormalPidData                     */
/* Description   | Make DTR Data                                            */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1PidTableIndex    : PID Info Table Index           */
/*               | [in] u1NumberOfTIDs     : number of TID.                 */
/*               | [in] u4DataBufferLength : Buffer Length                  */
/*               | [out] ptData            : Start pointer of read data     */
/*               | [out] ptDataLength      : Read Data Length               */
/* Return Value  | uint8                                                    */
/*               |   DCM_DSP_DIDMNG_OBD_READ_DATA_OK      : Read Data OK    */
/*               |   DCM_DSP_DIDMNG_OBD_READ_OVER_FLOW    : Over Flow       */
/*               |   DCM_DSP_DIDMNG_OBD_READ_DATA_NOT_OK  : Read Data NG    */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_DidMng_OBD_MakeNormalPidData
(
    const uint8 u1PidTableIndex,
    const uint32 u4DataBufferLength,
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA ) ptData,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptDataLength
)
{
    Dcm_MsgLenType u4_ResDataLen;
    Dcm_MsgLenType u4_BufIndex;
    Std_ReturnType u1_RetPidDataRead;
    Std_ReturnType u1_RetVal;

    u1_RetVal = DCM_DSP_DIDMNG_OBD_READ_DATA_NOT_OK;

    u4_ResDataLen = Dcm_Dsp_DidMng_OBD_GetPidDataSize( u1PidTableIndex );
    if( u4_ResDataLen <= u4DataBufferLength )
    {
        /* Initialize Reaponse Data */
        for( u4_BufIndex = (Dcm_MsgLenType)0U; u4_BufIndex < u4_ResDataLen; u4_BufIndex++ )
        {
            ptData[u4_BufIndex] = (Dcm_MsgItemType)0x00U;
        }

        u1_RetPidDataRead = Dcm_Dsp_DidMng_OBD_CallPidDataReadFnc( u1PidTableIndex, ptData );
        if( u1_RetPidDataRead == (Std_ReturnType)E_OK )
        {
            *ptDataLength = u4_ResDataLen;
            u1_RetVal = DCM_DSP_DIDMNG_OBD_READ_DATA_OK;
        }
    }
    else
    {
        u1_RetVal = DCM_DSP_DIDMNG_OBD_READ_OVER_FLOW;
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_OBD_MakeObdmidSupData                     */
/* Description   | Make Obdmid Support Data                                 */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1Obdmid           : Obdmid                         */
/*               | [in] u4DataBufferLength : Buffer Length                  */
/*               | [out] ptData            : Start pointer of read data     */
/*               | [out] ptDataLength      : Read Data Length               */
/* Return Value  | uint8                                                    */
/*               |   DCM_DSP_DIDMNG_OBD_READ_DATA_NONE    : Read Data None  */
/*               |   DCM_DSP_DIDMNG_OBD_READ_DATA_OK      : Read Data OK    */
/*               |   DCM_DSP_DIDMNG_OBD_READ_OVER_FLOW    : Over Flow       */
/*               |   DCM_DSP_DIDMNG_OBD_READ_DATA_NOT_OK  : Read Data NG    */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_DidMng_OBD_MakeObdmidSupData
(
    const uint8 u1Obdmid,
    const uint32 u4DataBufferLength,
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA ) ptData,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptDataLength
)
{
    uint32         u4_ObdmidSupportInfo;
    Std_ReturnType u1_RetGetAvail;
    uint8          u1_RetVal;

    u1_RetVal            = DCM_DSP_DIDMNG_OBD_READ_DATA_NOT_OK;
    u4_ObdmidSupportInfo = (uint32)0U;

    /* Buffer Over Flow Check */
    if( DCM_DSP_DIDMNG_OBD_SUP_DATALEN <= u4DataBufferLength )
    {
        u1_RetGetAvail = Dcm_Dsp_DidMng_OBD_GetAvailableOBDMIDs( u1Obdmid, &u4_ObdmidSupportInfo );
        if( u1_RetGetAvail == (Std_ReturnType)E_OK )
        {
            if( u4_ObdmidSupportInfo != ((uint32)0U) )
            {
                ptData[DCM_DSP_DIDMNG_OBD_DATA_POS_0] = (Dcm_MsgItemType)( u4_ObdmidSupportInfo >> DCM_DSP_DIDMNG_OBD_BITSHIFT_24 );
                ptData[DCM_DSP_DIDMNG_OBD_DATA_POS_1] = (Dcm_MsgItemType)( u4_ObdmidSupportInfo >> DCM_DSP_DIDMNG_OBD_BITSHIFT_16 );
                ptData[DCM_DSP_DIDMNG_OBD_DATA_POS_2] = (Dcm_MsgItemType)( u4_ObdmidSupportInfo >> DCM_DSP_DIDMNG_OBD_BITSHIFT_8 );
                ptData[DCM_DSP_DIDMNG_OBD_DATA_POS_3] = (Dcm_MsgItemType)u4_ObdmidSupportInfo;
                *ptDataLength = DCM_DSP_DIDMNG_OBD_SUP_DATALEN;
                u1_RetVal = DCM_DSP_DIDMNG_OBD_READ_DATA_OK;
            }
            else
            {
                u1_RetVal = DCM_DSP_DIDMNG_OBD_READ_DATA_NONE;
            }
        }
    }
    else
    {
        u1_RetVal = DCM_DSP_DIDMNG_OBD_READ_OVER_FLOW;
    }

    return u1_RetVal;
}

#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_OFF )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_OBD_MakeDTRData                           */
/* Description   | Make DTR Data                                            */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1Obdmid           : Obdmid                         */
/*               | [in] u1NumberOfTIDs     : number of TID.                 */
/*               | [in] u4DataBufferLength : Buffer Length                  */
/*               | [out] ptData            : Start pointer of read data     */
/*               | [out] ptDataLength      : Read Data Length               */
/* Return Value  | uint8                                                    */
/*               |   DCM_DSP_DIDMNG_OBD_READ_DATA_OK      : Read Data OK    */
/*               |   DCM_DSP_DIDMNG_OBD_READ_OVER_FLOW    : Over Flow       */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_DidMng_OBD_MakeDTRData
(
    const uint8 u1Obdmid,
    const uint8 u1NumberOfTIDs,
    const uint32 u4DataBufferLength,
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA ) ptData,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptDataLength
)
{
    Dcm_MsgLenType     u4_ResDataLen;
    uint16             u2_Testvalue;
    uint16             u2_Lowlimvalue;
    uint16             u2_Upplimvalue;
    uint8              u1_TIDvalue;
    uint8              u1_UaSID;
    uint8              u1_Cnt;
    uint8              u1_RetVal;
    Std_ReturnType     u1_RetGetDTRData;

    u4_ResDataLen = (Dcm_MsgLenType)0U;

    if( (uint32)( (uint32)u1NumberOfTIDs * (uint32)DCM_DSP_DIDMNG_OBD_DTRDATA_SIZE ) <= u4DataBufferLength ) /* no wrap around */
    {
        for( u1_Cnt = (uint8)0U; u1_Cnt < u1NumberOfTIDs; u1_Cnt++ )
        {
            u1_TIDvalue = (uint8)0;
            u1_UaSID = (uint8)0;
            u2_Testvalue = (uint16)0;
            u2_Lowlimvalue = (uint16)0;
            u2_Upplimvalue = (uint16)0;

            u1_RetGetDTRData = Dcm_Dsp_DidMng_OBD_GetDTRData( u1Obdmid, u1_Cnt, &u1_TIDvalue, &u1_UaSID, &u2_Testvalue, &u2_Lowlimvalue, &u2_Upplimvalue );
            if( u1_RetGetDTRData == (Std_ReturnType)E_OK )
            {
                ptData[u4_ResDataLen]                                         = u1_TIDvalue;
                ptData[u4_ResDataLen + DCM_DSP_DIDMNG_OBD_DATA_POS_UASID]     = u1_UaSID; /* no wrap around */
                ptData[u4_ResDataLen + DCM_DSP_DIDMNG_OBD_DATA_POS_TESTVAL_H] = (Dcm_MsgItemType)( u2_Testvalue >> DCM_DSP_DIDMNG_OBD_BITSHIFT_8 ); /* no wrap around */
                ptData[u4_ResDataLen + DCM_DSP_DIDMNG_OBD_DATA_POS_TESTVAL_L] = (Dcm_MsgItemType)u2_Testvalue; /* no wrap around */
                ptData[u4_ResDataLen + DCM_DSP_DIDMNG_OBD_DATA_POS_LLIMVAL_H] = (Dcm_MsgItemType)( u2_Lowlimvalue >> DCM_DSP_DIDMNG_OBD_BITSHIFT_8 ); /* no wrap around */
                ptData[u4_ResDataLen + DCM_DSP_DIDMNG_OBD_DATA_POS_LLIMVAL_L] = (Dcm_MsgItemType)u2_Lowlimvalue; /* no wrap around */
                ptData[u4_ResDataLen + DCM_DSP_DIDMNG_OBD_DATA_POS_ULIMVAL_H] = (Dcm_MsgItemType)( u2_Upplimvalue >> DCM_DSP_DIDMNG_OBD_BITSHIFT_8 ); /* no wrap around */
                ptData[u4_ResDataLen + DCM_DSP_DIDMNG_OBD_DATA_POS_ULIMVAL_L] = (Dcm_MsgItemType)u2_Upplimvalue; /* no wrap around */
            }
            else
            {
                ptData[u4_ResDataLen]                                         = (uint8)0;
                ptData[u4_ResDataLen + DCM_DSP_DIDMNG_OBD_DATA_POS_UASID]     = (uint8)0; /* no wrap around */
                ptData[u4_ResDataLen + DCM_DSP_DIDMNG_OBD_DATA_POS_TESTVAL_H] = (uint8)0; /* no wrap around */
                ptData[u4_ResDataLen + DCM_DSP_DIDMNG_OBD_DATA_POS_TESTVAL_L] = (uint8)0; /* no wrap around */
                ptData[u4_ResDataLen + DCM_DSP_DIDMNG_OBD_DATA_POS_LLIMVAL_H] = (uint8)0; /* no wrap around */
                ptData[u4_ResDataLen + DCM_DSP_DIDMNG_OBD_DATA_POS_LLIMVAL_L] = (uint8)0; /* no wrap around */
                ptData[u4_ResDataLen + DCM_DSP_DIDMNG_OBD_DATA_POS_ULIMVAL_H] = (uint8)0; /* no wrap around */
                ptData[u4_ResDataLen + DCM_DSP_DIDMNG_OBD_DATA_POS_ULIMVAL_L] = (uint8)0; /* no wrap around */
            }
            u4_ResDataLen += DCM_DSP_DIDMNG_OBD_DTRDATA_SIZE; /* no wrap around */
        }
        *ptDataLength = u4_ResDataLen;
        u1_RetVal = DCM_DSP_DIDMNG_OBD_READ_DATA_OK;
    }
    else
    {
        u1_RetVal = DCM_DSP_DIDMNG_OBD_READ_OVER_FLOW;
    }

    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_OFF */
#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_OBD_MakeDTRData                           */
/* Description   | Make DTR Data                                            */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1Obdmid           : Obdmid                         */
/*               | [in] u1OpStatus : Operation state                        */
/*               | [in] u1NumberOfTIDs     : number of TID.                 */
/*               | [in] u4DataBufferLength : Buffer Length                  */
/*               | [out] ptData            : Start pointer of read data     */
/*               | [out] ptDataLength      : Read Data Length               */
/* Return Value  | uint8                                                    */
/*               |   DCM_DSP_DIDMNG_OBD_READ_DATA_OK      : Read Data OK    */
/*               |   DCM_DSP_DIDMNG_OBD_READ_DATA_NOT_OK  : Read Data NG    */
/*               |   DCM_DSP_DIDMNG_OBD_READ_OVER_FLOW    : Over Flow       */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_DidMng_OBD_MakeDTRData
(
    const uint8 u1Obdmid,
    const Dcm_OpStatusType u1OpStatus,
    const uint8 u1NumberOfTIDs,
    const uint32 u4DataBufferLength,
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA ) ptData,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptDataLength
)
{
    Dcm_MsgLenType     u4_ResDataLen;
    uint16             u2_Testvalue;
    uint16             u2_Lowlimvalue;
    uint16             u2_Upplimvalue;
    uint8              u1_TIDvalue;
    uint8              u1_UaSID;
    uint8              u1_Cnt;
    uint8              u1_RetVal;
    Std_ReturnType     u1_RetGetDTRData;

    u4_ResDataLen = (Dcm_MsgLenType)0U;
    u1_RetVal = DCM_DSP_DIDMNG_OBD_READ_DATA_NOT_OK;

    if( u4DataBufferLength >= (uint32)DCM_DSP_DIDMNG_OBD_DTRDATA_SIZE )
    {
        if( u1OpStatus == DCM_INITIAL )
        {
            /* Dcm_Dsp_DidMng_OBD_NumOfReadTid Initialyze    */
            Dcm_Dsp_DidMng_OBD_NumOfReadTid = (uint8)0U;
        }
        for( u1_Cnt = Dcm_Dsp_DidMng_OBD_NumOfReadTid; u1_Cnt < u1NumberOfTIDs; u1_Cnt++ )
        {
            if( u4_ResDataLen > ( u4DataBufferLength  - (uint32)DCM_DSP_DIDMNG_OBD_DTRDATA_SIZE ) )
            {
                break;
            }
            u1_TIDvalue = (uint8)0;
            u1_UaSID = (uint8)0;
            u2_Testvalue = (uint16)0;
            u2_Lowlimvalue = (uint16)0;
            u2_Upplimvalue = (uint16)0;

            u1_RetGetDTRData = Dcm_Dsp_DidMng_OBD_GetDTRData( u1Obdmid, u1_Cnt, &u1_TIDvalue, &u1_UaSID, &u2_Testvalue, &u2_Lowlimvalue, &u2_Upplimvalue );
            if( u1_RetGetDTRData == (Std_ReturnType)E_OK )
            {
                ptData[u4_ResDataLen]                                         = u1_TIDvalue;
                ptData[u4_ResDataLen + DCM_DSP_DIDMNG_OBD_DATA_POS_UASID]     = u1_UaSID; /* no wrap around */
                ptData[u4_ResDataLen + DCM_DSP_DIDMNG_OBD_DATA_POS_TESTVAL_H] = (Dcm_MsgItemType)( u2_Testvalue >> DCM_DSP_DIDMNG_OBD_BITSHIFT_8 ); /* no wrap around */
                ptData[u4_ResDataLen + DCM_DSP_DIDMNG_OBD_DATA_POS_TESTVAL_L] = (Dcm_MsgItemType)u2_Testvalue; /* no wrap around */
                ptData[u4_ResDataLen + DCM_DSP_DIDMNG_OBD_DATA_POS_LLIMVAL_H] = (Dcm_MsgItemType)( u2_Lowlimvalue >> DCM_DSP_DIDMNG_OBD_BITSHIFT_8 ); /* no wrap around */
                ptData[u4_ResDataLen + DCM_DSP_DIDMNG_OBD_DATA_POS_LLIMVAL_L] = (Dcm_MsgItemType)u2_Lowlimvalue; /* no wrap around */
                ptData[u4_ResDataLen + DCM_DSP_DIDMNG_OBD_DATA_POS_ULIMVAL_H] = (Dcm_MsgItemType)( u2_Upplimvalue >> DCM_DSP_DIDMNG_OBD_BITSHIFT_8 ); /* no wrap around */
                ptData[u4_ResDataLen + DCM_DSP_DIDMNG_OBD_DATA_POS_ULIMVAL_L] = (Dcm_MsgItemType)u2_Upplimvalue; /* no wrap around */
            }
            else
            {
                ptData[u4_ResDataLen]                                         = (uint8)0;
                ptData[u4_ResDataLen + DCM_DSP_DIDMNG_OBD_DATA_POS_UASID]     = (uint8)0; /* no wrap around */
                ptData[u4_ResDataLen + DCM_DSP_DIDMNG_OBD_DATA_POS_TESTVAL_H] = (uint8)0; /* no wrap around */
                ptData[u4_ResDataLen + DCM_DSP_DIDMNG_OBD_DATA_POS_TESTVAL_L] = (uint8)0; /* no wrap around */
                ptData[u4_ResDataLen + DCM_DSP_DIDMNG_OBD_DATA_POS_LLIMVAL_H] = (uint8)0; /* no wrap around */
                ptData[u4_ResDataLen + DCM_DSP_DIDMNG_OBD_DATA_POS_LLIMVAL_L] = (uint8)0; /* no wrap around */
                ptData[u4_ResDataLen + DCM_DSP_DIDMNG_OBD_DATA_POS_ULIMVAL_H] = (uint8)0; /* no wrap around */
                ptData[u4_ResDataLen + DCM_DSP_DIDMNG_OBD_DATA_POS_ULIMVAL_L] = (uint8)0; /* no wrap around */
            }
            u4_ResDataLen += DCM_DSP_DIDMNG_OBD_DTRDATA_SIZE; /* no wrap around */
            Dcm_Dsp_DidMng_OBD_NumOfReadTid = (uint8)(Dcm_Dsp_DidMng_OBD_NumOfReadTid + (uint8)1U);
        }
        *ptDataLength = u4_ResDataLen;
        if( u1_Cnt >= u1NumberOfTIDs )
        {
            u1_RetVal = DCM_DSP_DIDMNG_OBD_READ_DATA_OK;
        }
        else
        {
            u1_RetVal = DCM_DSP_DIDMNG_OBD_READ_OVER_FLOW;
        }
    }
    else
    {
        if( u1OpStatus == DCM_INITIAL )
        {
            u1_RetVal = DCM_DSP_DIDMNG_OBD_READ_OVER_FLOW;
        }
    }
    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_OBD_MakeSupInfTypData                     */
/* Description   | Make Support InfoType Data                               */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1reqInfoType      : Request InfoType               */
/*               | [in] u4DataBufferLength : Buffer Length                  */
/*               | [out] ptData            : Start pointer of read data     */
/*               | [out] ptDataLength      : Read Data Length               */
/* Return Value  | uint8                                                    */
/*               |   DCM_DSP_DIDMNG_OBD_READ_DATA_NONE    : Read Data None  */
/*               |   DCM_DSP_DIDMNG_OBD_READ_DATA_OK      : Read Data OK    */
/*               |   DCM_DSP_DIDMNG_OBD_READ_OVER_FLOW    : Over Flow       */
/*               |   DCM_DSP_DIDMNG_OBD_READ_DATA_NOT_OK  : Read Data NG    */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_DidMng_OBD_MakeSupInfTypData
(
    CONST( Dcm_MsgItemType, AUTOMATIC ) u1reqInfoType,
    const uint32 u4DataBufferLength,
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA ) ptData,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptDataLength
)
{
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )    pt_ReadData;
    uint32         u4_InfoTypeSupportData;
    Std_ReturnType u1_RetInfoTypeRead;
    uint8          u1_RetVal;

    u1_RetVal        = DCM_DSP_DIDMNG_OBD_READ_DATA_NOT_OK;
    pt_ReadData      = &ptData[DCM_DSP_DIDMNG_OBD_READ_OFS];

    /* Buffer Over Flow Check */
    if( ( DCM_DSP_DIDMNG_OBD_READ_OFS + DCM_DSP_DIDMNG_OBD_SUP_DATALEN ) <= u4DataBufferLength )
    {
        u1_RetInfoTypeRead = Dcm_Dsp_DidMng_OBD_GetInfTypSupData( u1reqInfoType, &u4_InfoTypeSupportData );
        if( u1_RetInfoTypeRead == (Std_ReturnType)E_OK )
        {
            if( u4_InfoTypeSupportData != ((uint32)0U) )
            {
                pt_ReadData[DCM_DSP_DIDMNG_OBD_DATA_POS_0] = (uint8)( u4_InfoTypeSupportData >> DCM_DSP_DIDMNG_OBD_BITSHIFT_24 );
                pt_ReadData[DCM_DSP_DIDMNG_OBD_DATA_POS_1] = (uint8)( u4_InfoTypeSupportData >> DCM_DSP_DIDMNG_OBD_BITSHIFT_16 );
                pt_ReadData[DCM_DSP_DIDMNG_OBD_DATA_POS_2] = (uint8)( u4_InfoTypeSupportData >> DCM_DSP_DIDMNG_OBD_BITSHIFT_8 );
                pt_ReadData[DCM_DSP_DIDMNG_OBD_DATA_POS_3] = (uint8)u4_InfoTypeSupportData;
                *ptDataLength = DCM_DSP_DIDMNG_OBD_SUP_DATALEN + DCM_DSP_DIDMNG_OBD_READ_OFS;
                u1_RetVal = DCM_DSP_DIDMNG_OBD_READ_DATA_OK;
            }
            else
            {
                *ptDataLength = DCM_DSP_DIDMNG_OBD_READ_OFS;
                u1_RetVal = DCM_DSP_DIDMNG_OBD_READ_DATA_NONE;
            }
        }
    }
    else
    {
        u1_RetVal = DCM_DSP_DIDMNG_OBD_READ_OVER_FLOW;
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_OBD_MakeNormInfTypDEM                     */
/* Description   | Make InfoType Data Obtained From DEM                     */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1OpStatus        : Operation state                 */
/*               | [in] u1reqInfoType     : Request InfoType                */
/*               | [in] u1InfoTypeTblIndex: InfoType Table Index            */
/*               | [in] u4DataBufferLength: Buffer Length                   */
/*               | [out] ptData           : Start pointer of read data      */
/*               | [out] ptDataLength     : Read Data Length                */
/* Return Value  | uint8                                                    */
/*               |   DCM_DSP_DIDMNG_OBD_READ_DATA_OK      : Read Data OK    */
/*               |   DCM_DSP_DIDMNG_OBD_READ_OVER_FLOW    : Over Flow       */
/*               |   DCM_DSP_DIDMNG_OBD_READ_DATA_NOT_OK  : Read Data NG    */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_DidMng_OBD_MakeNormInfTypDEM
(
    CONST( Dcm_OpStatusType, AUTOMATIC ) u1OpStatus,
    CONST( Dcm_MsgItemType, AUTOMATIC ) u1reqInfoType,
    const uint8 u1InfoTypeTblIndex,
    const uint32 u4DataBufferLength,
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA ) ptData,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptDataLength
)
{
    Dcm_MsgLenType                              u4_ResDataLen;
    Dcm_MsgLenType                              u4_InfoTypeSizeForChk;
    Dcm_MsgLenType                              u4_BufIndex;
    uint8                                       u1_InfoTypeSize;
    uint8                                       u1_WritableSize;
    uint8                                       u1_RetVal;
    Std_ReturnType                              u1_RetInfoTypeRead;

    u1_RetVal       = DCM_DSP_DIDMNG_OBD_READ_DATA_NOT_OK;
    u4_ResDataLen   = DCM_DSP_DIDMNG_OBD_READ_OFS - DCM_DSP_DIDMNG_OBD_NODI_SIZE;

    u1_InfoTypeSize = Dcm_Dsp_DidMng_OBD_GetInfoTypeDataSize( u1InfoTypeTblIndex, Dcm_Dsp_DidMng_OBD_u1PendingElement );
    u4_InfoTypeSizeForChk = u4_ResDataLen + (Dcm_MsgLenType)u1_InfoTypeSize; /* no wrap around */
    /* Buffer Over Flow Check */
    if( u4_InfoTypeSizeForChk <= u4DataBufferLength )
    {
        /* Initialize Reaponse Data */
        for( u4_BufIndex = u4_ResDataLen; u4_BufIndex < u4_InfoTypeSizeForChk; u4_BufIndex++ )
        {
            ptData[u4_BufIndex] = (Dcm_MsgItemType)0x00U;
        }

        /* Call DEM-API connector */
        u1_WritableSize = u1_InfoTypeSize;
        u1_RetInfoTypeRead = Dcm_Dsp_DidMng_OBD_GetInfoTypeValue( u1OpStatus, u1reqInfoType, &ptData[u4_ResDataLen], &u1_WritableSize );
        if( u1_RetInfoTypeRead == (Std_ReturnType)E_OK )
        {
            if( u1_WritableSize <= u1_InfoTypeSize )
            {
                u4_ResDataLen += (Dcm_MsgLenType)u1_WritableSize; /* no wrap around */
                *ptDataLength = u4_ResDataLen;
                u1_RetVal = DCM_DSP_DIDMNG_OBD_READ_DATA_OK;
            }
        }
        ptData[DCM_DSP_DIDMNG_OBD_READ_OFS - DCM_DSP_DIDMNG_OBD_NODI_SIZE] = u1reqInfoType;
    }
    else
    {
        u1_RetVal = DCM_DSP_DIDMNG_OBD_READ_OVER_FLOW;
    }

    return u1_RetVal;
}

#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_OFF )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_OBD_MakeNormInfTypDat                     */
/* Description   | Make Normal InfoType Data                                */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1OpStatus        : Operation state                 */
/*               | [in] u1reqInfoType     : Request InfoType                */
/*               | [in] u1InfoTypeTblIndex: InfoType Table Index            */
/*               | [in] u4DataBufferLength: Buffer Length                   */
/*               | [out] ptData           : Start pointer of read data      */
/*               | [out] ptDataLength     : Read Data Length                */
/* Return Value  | uint8                                                    */
/*               |   DCM_DSP_DIDMNG_OBD_READ_DATA_NONE    : Read Data None  */
/*               |   DCM_DSP_DIDMNG_OBD_READ_DATA_OK      : Read Data OK    */
/*               |   DCM_DSP_DIDMNG_OBD_READ_OVER_FLOW    : Over Flow       */
/*               |   DCM_DSP_DIDMNG_OBD_READ_DATA_PENDING : Pending         */
/*               |   DCM_DSP_DIDMNG_OBD_READ_DATA_NOT_OK  : Read Data NG    */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_DidMng_OBD_MakeNormInfTypDat
(
    CONST( Dcm_OpStatusType, AUTOMATIC ) u1OpStatus,
    CONST( Dcm_MsgItemType, AUTOMATIC ) u1reqInfoType,
    const uint8 u1InfoTypeTblIndex,
    const uint32 u4DataBufferLength,
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA ) ptData,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptDataLength
)
{
    Dcm_MsgLenType                              u4_ResDataLen;
    Dcm_MsgLenType                              u4_InfoTypeSizeForChk;
    Dcm_MsgLenType                              u4_BufIndex;
    uint32                                      u4_ResDataOfs;
    uint8                                       u1_ElementNum;
    uint8                                       u1_InfoTypeSize;
    uint8                                       u1_WritableSize;
    uint8                                       u1_NumOfVehInfoData;
    uint8                                       u1_VehInfoInterNODI;
    uint8                                       u1_Cnt;
    uint8                                       u1_RetVal;
    Std_ReturnType                              u1_RetInfoTypeRead;
    Dcm_OpStatusType                            u1_opStatus;

    u1_RetVal           = DCM_DSP_DIDMNG_OBD_READ_DATA_NOT_OK;
    u1_opStatus         = u1OpStatus;
    u1_NumOfVehInfoData = Dcm_Dsp_DidMng_OBD_GetNumOfInfoType( u1InfoTypeTblIndex );

    if( u1OpStatus == DCM_PENDING )
    {
        u1_ElementNum = Dcm_Dsp_DidMng_OBD_u1PendingElement;
        u4_ResDataLen = Dcm_Dsp_DidMng_OBD_u4PendingDataLen;
        u4_ResDataOfs = u4_ResDataLen;
    }
    else
    {
        u1_ElementNum = (uint8)0U;
    }
    if( u1_ElementNum == (uint8)0U )
    {
        u1_VehInfoInterNODI = Dcm_Dsp_DidMng_OBD_GetInfoTypeInterNODI( u1InfoTypeTblIndex );
        if( u1_VehInfoInterNODI == (uint8)STD_OFF )
        {
            u4_ResDataOfs = DCM_DSP_DIDMNG_OBD_READ_OFS - DCM_DSP_DIDMNG_OBD_NODI_SIZE;
            u4_ResDataLen = (Dcm_MsgLenType)( DCM_DSP_DIDMNG_OBD_READ_OFS - DCM_DSP_DIDMNG_OBD_NODI_SIZE );
        }
        else
        {
            u4_ResDataOfs = DCM_DSP_DIDMNG_OBD_READ_OFS;
            u4_ResDataLen = (Dcm_MsgLenType)DCM_DSP_DIDMNG_OBD_READ_OFS;
        }
    }

    /* Get Normal InfoType Data */
    for( u1_Cnt = u1_ElementNum; u1_Cnt < u1_NumOfVehInfoData; u1_Cnt++ )
    {
        u1_InfoTypeSize = Dcm_Dsp_DidMng_OBD_GetInfoTypeDataSize( u1InfoTypeTblIndex, u1_Cnt );
        u4_InfoTypeSizeForChk = u4_ResDataOfs + (Dcm_MsgLenType)u1_InfoTypeSize; /* no wrap around */
        /* Buffer Over Flow Check */
        if( u4_InfoTypeSizeForChk <= u4DataBufferLength )
        {
            /* Initialize Reaponse Data */
            for( u4_BufIndex = u4_ResDataOfs; u4_BufIndex < u4_InfoTypeSizeForChk; u4_BufIndex++ )
            {
                ptData[u4_BufIndex] = (Dcm_MsgItemType)0x00U;
            }

            u1_WritableSize = u1_InfoTypeSize;
            u1_RetInfoTypeRead = Dcm_Dsp_DidMng_OBD_CallVehInfoDataReadFnc( u1InfoTypeTblIndex, u1_Cnt, u1_opStatus, &ptData[u4_ResDataOfs], &u1_WritableSize );
            if( u1_RetInfoTypeRead == (Std_ReturnType)E_OK )
            {
                if( u1_WritableSize <= u1_InfoTypeSize )
                {
                    u4_ResDataLen += (Dcm_MsgLenType)u1_WritableSize; /* no wrap around */
                    u4_ResDataOfs += (Dcm_MsgLenType)u1_WritableSize; /* no wrap around */
                    u1_opStatus = DCM_INITIAL;
                    u1_RetVal = DCM_DSP_DIDMNG_OBD_READ_DATA_OK;
                }
                else
                {
                    u1_RetVal = DCM_DSP_DIDMNG_OBD_READ_OVER_FLOW;
                }
            }
            else if( u1_RetInfoTypeRead == (Std_ReturnType)DCM_E_PENDING )
            {
                u1_RetVal = DCM_DSP_DIDMNG_OBD_READ_DATA_PENDING;
            }
            else
            {
                u1_RetVal = DCM_DSP_DIDMNG_OBD_READ_DATA_NOT_OK;
            }
        }
        else
        {
            u1_RetVal = DCM_DSP_DIDMNG_OBD_READ_OVER_FLOW;
        }

        if( u1_RetVal != DCM_DSP_DIDMNG_OBD_READ_DATA_OK )
        {
           break;
        }
    }
    if( u1_RetVal == DCM_DSP_DIDMNG_OBD_READ_DATA_OK )
    {
        if( u1_ElementNum == (uint8)0U )
        {
            ptData[DCM_DSP_DIDMNG_OBD_READ_OFS - DCM_DSP_DIDMNG_OBD_NODI_SIZE] = u1reqInfoType;
        }
        *ptDataLength = u4_ResDataLen;
        Dcm_Dsp_DidMng_OBD_u1PendingElement = (uint8)0U;
        Dcm_Dsp_DidMng_OBD_u4PendingDataLen = (Dcm_MsgLenType)0U;
    }
    else if( u1_RetVal == DCM_DSP_DIDMNG_OBD_READ_DATA_PENDING )
    {
        if( u1_ElementNum == (uint8)0U )
        {
            ptData[DCM_DSP_DIDMNG_OBD_READ_OFS - DCM_DSP_DIDMNG_OBD_NODI_SIZE] = u1reqInfoType;
        }
        Dcm_Dsp_DidMng_OBD_u1PendingElement = u1_Cnt;
        Dcm_Dsp_DidMng_OBD_u4PendingDataLen = u4_ResDataLen;
    }
    else
    {
        Dcm_Dsp_DidMng_OBD_u1PendingElement = (uint8)0U;
        Dcm_Dsp_DidMng_OBD_u4PendingDataLen = (Dcm_MsgLenType)0U;
    }

    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_OFF */
#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_DidMng_OBD_MakeNormInfTypDat                     */
/* Description   | Make Normal InfoType Data                                */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1OpStatus        : Operation state                 */
/*               | [in] u1reqInfoType     : Request InfoType                */
/*               | [in] u1InfoTypeTblIndex: InfoType Table Index            */
/*               | [in] u4DataBufferLength: Buffer Length                   */
/*               | [out] ptData           : Start pointer of read data      */
/*               | [out] ptDataLength     : Read Data Length                */
/* Return Value  | uint8                                                    */
/*               |   DCM_DSP_DIDMNG_OBD_READ_DATA_NONE    : Read Data None  */
/*               |   DCM_DSP_DIDMNG_OBD_READ_DATA_OK      : Read Data OK    */
/*               |   DCM_DSP_DIDMNG_OBD_READ_OVER_FLOW    : Over Flow       */
/*               |   DCM_DSP_DIDMNG_OBD_READ_DATA_PENDING : Pending         */
/*               |   DCM_DSP_DIDMNG_OBD_READ_DATA_NOT_OK  : Read Data NG    */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_DidMng_OBD_MakeNormInfTypDat
(
    CONST( Dcm_OpStatusType, AUTOMATIC ) u1OpStatus,
    CONST( Dcm_MsgItemType, AUTOMATIC ) u1reqInfoType,
    const uint8 u1InfoTypeTblIndex,
    const uint32 u4DataBufferLength,
    P2VAR( uint8,  AUTOMATIC, DCM_APPL_DATA ) ptData,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) ptDataLength
)
{
    Dcm_MsgLenType                              u4_ResDataLen;
    Dcm_MsgLenType                              u4_InfoTypeSizeForChk;
    Dcm_MsgLenType                              u4_BufIndex;
    uint32                                      u4_FullDataLen;
    uint32                                      u4_ResDataOfs;
    uint8                                       u1_ElementNum;
    uint8                                       u1_InfoTypeSize;
    uint8                                       u1_WritableSize;
    uint8                                       u1_NumOfVehInfoData;
    uint8                                       u1_VehInfoInterNODI;
    uint8                                       u1_Cnt;
    uint8                                       u1_RetVal;
    Std_ReturnType                              u1_RetInfoTypeRead;
    Dcm_OpStatusType                            u1_opStatus;
    boolean                                     b_IsOverFlow;

    u1_RetVal           = DCM_DSP_DIDMNG_OBD_READ_DATA_NOT_OK;
    u1_opStatus         = u1OpStatus;
    b_IsOverFlow        = (boolean)FALSE;

    if( u1OpStatus == DCM_PENDING )
    {
        u1_ElementNum = Dcm_Dsp_DidMng_OBD_u1PendingElement;
        u4_ResDataLen = Dcm_Dsp_DidMng_OBD_u4PendingDataLen;
        u4_ResDataOfs = u4_ResDataLen;
    }
    else
    {
        u1_ElementNum = (uint8)0U;

        /* Get full data length */
        /* Since that u1reqInfoType is in Dcm_P_DidMng_InfoTypeTbl[] is already checked, No need to check the return value */
        (void)Dcm_Dsp_DidMng_OBD_GetInfoTypeDataLen( u1reqInfoType, &u4_FullDataLen );

        /* Buffer Over Flow Check */
        if( u4_FullDataLen > ( u4DataBufferLength - DCM_DSP_DIDMNG_OBD_READ_OFS ) ) /* no wrap around */
        {
            u1_RetVal = DCM_DSP_DIDMNG_OBD_READ_OVER_FLOW;
            b_IsOverFlow = (boolean)TRUE;
        }
    }

    if( b_IsOverFlow == (boolean)FALSE )
    {
        if( u1_ElementNum == (uint8)0U )
        {
            u1_VehInfoInterNODI = Dcm_Dsp_DidMng_OBD_GetInfoTypeInterNODI( u1InfoTypeTblIndex );
            if( u1_VehInfoInterNODI == (uint8)STD_OFF )
            {
                u4_ResDataOfs = DCM_DSP_DIDMNG_OBD_READ_OFS - DCM_DSP_DIDMNG_OBD_NODI_SIZE;
                u4_ResDataLen = (Dcm_MsgLenType)( DCM_DSP_DIDMNG_OBD_READ_OFS - DCM_DSP_DIDMNG_OBD_NODI_SIZE );
            }
            else
            {
                u4_ResDataOfs = DCM_DSP_DIDMNG_OBD_READ_OFS;
                u4_ResDataLen = (Dcm_MsgLenType)DCM_DSP_DIDMNG_OBD_READ_OFS;
            }
        }

        u1_NumOfVehInfoData = Dcm_Dsp_DidMng_OBD_GetNumOfInfoType( u1InfoTypeTblIndex );
        /* Get Normal InfoType Data */
        for( u1_Cnt = u1_ElementNum; u1_Cnt < u1_NumOfVehInfoData; u1_Cnt++ )
        {
            u1_InfoTypeSize = Dcm_Dsp_DidMng_OBD_GetInfoTypeDataSize( u1InfoTypeTblIndex, u1_Cnt );
            u4_InfoTypeSizeForChk = u4_ResDataOfs + (Dcm_MsgLenType)u1_InfoTypeSize; /* no wrap around */
            /* Initialize Reaponse Data */
            for( u4_BufIndex = u4_ResDataOfs; u4_BufIndex < u4_InfoTypeSizeForChk; u4_BufIndex++ )
            {
                ptData[u4_BufIndex] = (Dcm_MsgItemType)0x00U;
            }

            u1_WritableSize = u1_InfoTypeSize;
            u1_RetInfoTypeRead = Dcm_Dsp_DidMng_OBD_CallVehInfoDataReadFnc( u1InfoTypeTblIndex, u1_Cnt, u1_opStatus, &ptData[u4_ResDataOfs], &u1_WritableSize );
            if( u1_RetInfoTypeRead == (Std_ReturnType)E_OK )
            {
                if( u1_WritableSize <= u1_InfoTypeSize )
                {
                    u4_ResDataLen += (Dcm_MsgLenType)u1_WritableSize; /* no wrap around */
                    u4_ResDataOfs += (Dcm_MsgLenType)u1_WritableSize; /* no wrap around */
                    u1_opStatus = DCM_INITIAL;
                    u1_RetVal = DCM_DSP_DIDMNG_OBD_READ_DATA_OK;
                }
                else
                {
                    u1_RetVal = DCM_DSP_DIDMNG_OBD_READ_DATA_NOT_OK;
                }
            }
            else if( u1_RetInfoTypeRead == (Std_ReturnType)DCM_E_PENDING )
            {
                u1_RetVal = DCM_DSP_DIDMNG_OBD_READ_DATA_PENDING;
            }
            else
            {
                u1_RetVal = DCM_DSP_DIDMNG_OBD_READ_DATA_NOT_OK;
            }

            if( u1_RetVal != DCM_DSP_DIDMNG_OBD_READ_DATA_OK )
            {
                break;
            }
        }
    }
    if( u1_RetVal == DCM_DSP_DIDMNG_OBD_READ_DATA_OK )
    {
        if( u1_ElementNum == (uint8)0U )
        {
            ptData[DCM_DSP_DIDMNG_OBD_READ_OFS - DCM_DSP_DIDMNG_OBD_NODI_SIZE] = u1reqInfoType;
        }
        *ptDataLength = u4_ResDataLen;
        Dcm_Dsp_DidMng_OBD_u1PendingElement = (uint8)0U;
        Dcm_Dsp_DidMng_OBD_u4PendingDataLen = (Dcm_MsgLenType)0U;
    }
    else if( u1_RetVal == DCM_DSP_DIDMNG_OBD_READ_DATA_PENDING )
    {
        if( u1_ElementNum == (uint8)0U )
        {
            ptData[DCM_DSP_DIDMNG_OBD_READ_OFS - DCM_DSP_DIDMNG_OBD_NODI_SIZE] = u1reqInfoType;
        }
        Dcm_Dsp_DidMng_OBD_u1PendingElement = u1_Cnt;
        Dcm_Dsp_DidMng_OBD_u4PendingDataLen = u4_ResDataLen;
    }
    else
    {
        Dcm_Dsp_DidMng_OBD_u1PendingElement = (uint8)0U;
        Dcm_Dsp_DidMng_OBD_u4PendingDataLen = (Dcm_MsgLenType)0U;
    }

    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON */


#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

#endif /* DCM_OBD_RANGE_DID_USE == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-2-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

