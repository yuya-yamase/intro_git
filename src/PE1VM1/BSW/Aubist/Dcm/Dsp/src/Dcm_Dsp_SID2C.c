/* Dcm_Dsp_SID2C_c(v5-10-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID2C/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID2C.h>
#if ( DCM_SUPPORT_SID2C == STD_ON )
#include "../../Dsp/cfg/Dcm_Dsp_SID2C_Cfg.h"
#include <Dcm/Dcm_Dsp_DidMng.h>
#include <Dcm/Dcm_Dsp_Main.h>
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include "../../Dsd/inc/Dcm_Dsd_ServiceMng.h"
#include <Dcm/Dcm_Main_Common.h>
#include <Dcm/Dcm_Main_EvtDistr.h>
#include <Dcm.h>
#include <Dcm/Dcm_Dsp_MemMng.h>
#if ( DCM_PERIODIC_DDDID_USE == STD_ON )
#include <Dcm/Dcm_Dsp_SID2A.h>
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON */


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSP_SID2C_DID_SHIFT           ((uint8)8U)
#define DCM_DSP_SID2C_SDIDNUM_SHIFT       ((uint8)2U)
#define DCM_DSP_SID2C_ALFID_MEMADDR_MASK  ((uint8)0x0FU)
#define DCM_DSP_SID2C_ALFID_SHIFT4        ((uint8)4U)
#define DCM_DSP_SID2C_MEMID_NOT_SET       ((uint8)0U)
#define DCM_DSP_SID2C_MEMID_SET           ((uint8)1U)
#define DCM_DSP_SID2C_MEMADDR_SHIFT8      ((uint8)8U)
#define DCM_DSP_SID2C_MEMSIZE_SHIFT8      ((uint8)8U)

#define DCM_DSP_SID2C_SF_SETDDDID         ((uint8)0x01U)
#define DCM_DSP_SID2C_SF_SETDDDID_MEMADDR ((uint8)0x02U)
#define DCM_DSP_SID2C_SF_CLEAR            ((uint8)0x03U)

#define DCM_DSP_SID2C_REQDATA_DIDHIGH     ((uint8)0U)
#define DCM_DSP_SID2C_REQDATA_DIDLOW      ((uint8)1U)
#define DCM_DSP_SID2C_REQDATA_SDIDHIGH    ((uint8)2U)
#define DCM_DSP_SID2C_REQDATA_SDIDLOW     ((uint8)3U)
#define DCM_DSP_SID2C_REQDATA_POS         ((uint8)4U)
#define DCM_DSP_SID2C_REQDATA_SIZE        ((uint8)5U)
#define DCM_DSP_SID2C_REQDATA_ALFID       ((uint8)2U)
#define DCM_DSP_SID2C_REQDATA_MEMADDR_POS ((uint8)3U)
#define DCM_DSP_SID2C_SF01_REQLEN_MIN     ((uint8)6U)
#define DCM_DSP_SID2C_REQLEN_DDDID        ((uint8)2U)
#define DCM_DSP_SID2C_SF01_REQLEN_SDID    ((uint8)4U)
#define DCM_DSP_SID2C_SF01_REQLEN_MASK    ((uint32)0x00000003U)
#define DCM_DSP_SID2C_SF02_REQLEN_MIN     ((uint8)5U)
#define DCM_DSP_SID2C_SF02_REQLEN_ALFID   ((uint8)1U)
#define DCM_DSP_SID2C_SF03_REQLEN_ALL     ((uint8)0U)
#define DCM_DSP_SID2C_SF03_REQLEN_DID     ((uint8)2U)

#define DCM_DSP_SID2C_RESDATA_DIDHIGH     ((uint8)0U)
#define DCM_DSP_SID2C_RESDATA_DIDLOW      ((uint8)1U)
#define DCM_DSP_SID2C_RESLEN_DID          ((uint8)2U)

#define DCM_DSP_SID2C_PROC_CHKSUPPORT     ((uint8)0U)
#define DCM_DSP_SID2C_PROC_CHKAVAILABE    ((uint8)1U)
#define DCM_DSP_SID2C_PROC_CHKPOSSIZE     ((uint8)2U)

#define DCM_DSP_SID2C_DDDID_ALLCLR        ((uint16)0x0000U)

#define DCM_DSP_SID2C_MASKPDIDHI          ((uint16)0xFF00U)
#define DCM_DSP_SID2C_PDID_HIGHBYTE       ((uint16)0xF200U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_InitialProc
(
    const uint8  u1SubFunction,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_CancelProc
(
    const uint8  u1SubFunction
);

static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_InitialProc_Sub01
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);

static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_CancelProc_Sub01
( void );

static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_SDIDProc
(
    const uint8 u1ProcId
);
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_ChkDDDID
(
    const uint16 u2Did,
    const uint8  u1SubFunction
);
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_ChkSDID
(
    const uint8 u1ProcId
);
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_ChkSDIDSupport
( void );
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_ChkSDIDAvailable
(
    const Dcm_OpStatusType u1OpStatus
);
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_ChkSDIDSesSupport
( void );
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_ChkSDIDPosSize
(
    const Dcm_OpStatusType u1OpStatus
);
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_ChkSDIDSecSupport
( void );

static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_InitialProc_Sub02
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);

static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_CancelProc_Sub02
( void );

static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_MemAddrProc
(
    const uint8  u1MemAddrByteNum,
    const uint8  u1MemSizeByteNum,
    const uint32 u4MemAddrNum
);

static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_ChkMemAddrSesSupport
(
    const uint8 u1MemIdIndex,
    const uint8 u1MemRangeIndex
);

static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_ChkMemAddrSecSupport
(
    const uint8 u1MemIdIndex,
    const uint8 u1MemRangeIndex
);

static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_ChkALFID
(
    const uint8 u1ALFID
);

static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_ChkMemAddr
(
    const uint8  u1MemAddrByteNum,
    const uint8  u1MemSizeByteNum,
    const uint32 u4MemAddrNum
);

static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_ChkMemSize
(
    const uint32 u4MemSize
);

static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_InitialProc_Sub03
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_ChkDDDID_Sub03
(
    const uint16 u2Did
);
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_ChkCondition
(
    const uint8 u1SubFunction
);
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_CancelProc_Sub03
( void );
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SID2C_PDidInfoChkByDDDidClr
(
    const uint16 u2ClrDDDid
);

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

static VAR( uint16, DCM_VAR_NO_INIT ) Dcm_Dsp_SID2C_u2SDID;
static VAR( uint16, DCM_VAR_NO_INIT ) Dcm_Dsp_SID2C_u2SDIDIndex;
static VAR( uint32, DCM_VAR_NO_INIT ) Dcm_Dsp_SID2C_u4SDIDChkCnt;

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

#if ( DCM_SUPPORT_SID2C_SUB01 == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_SID2C_Sub01                                          */
/* Description   | Request processing of SID 2C subfunction 01              */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus      : Operation state                     */
/*               | [IN] pMsgContext   : Message Context                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID2C_Sub01    /* MISRA DEVIATION */
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID2C_InitialProc( DCM_DSP_SID2C_SF_SETDDDID, pMsgContext );
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        u1_RetVal = Dcm_Dsp_SID2C_CancelProc( DCM_DSP_SID2C_SF_SETDDDID );
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID2C_SUB01 == ON */

#if ( DCM_SUPPORT_SID2C_SUB02 == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_SID2C_Sub02                                          */
/* Description   | Request processing of SID 2C subfunction 02              */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus      : Operation state                     */
/*               | [IN] pMsgContext   : Message Context                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID2C_Sub02    /* MISRA DEVIATION */
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID2C_InitialProc( DCM_DSP_SID2C_SF_SETDDDID_MEMADDR, pMsgContext );
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        u1_RetVal = Dcm_Dsp_SID2C_CancelProc( DCM_DSP_SID2C_SF_SETDDDID_MEMADDR );
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID2C_SUB02 == ON */

#if ( DCM_SUPPORT_SID2C_SUB03 == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_SID2C_Sub03                                          */
/* Description   | Request processing of SID 2C subfunction 03              */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus      : Operation state                     */
/*               | [IN] pMsgContext   : Message Context                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID2C_Sub03    /* MISRA DEVIATION */
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID2C_InitialProc( DCM_DSP_SID2C_SF_CLEAR, pMsgContext );
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        u1_RetVal = Dcm_Dsp_SID2C_CancelProc( DCM_DSP_SID2C_SF_CLEAR );
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID2C_SUB03 == ON */

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2C_Init                                       */
/* Description   | SID 2C initialization                                    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID2C_Init    /* MISRA DEVIATION */
( void )
{

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2C_DidAvailableCbk                            */
/* Description   | Callback function for event delivery registration of     */
/*               | ChkSDIDAvailable Function                                */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID2C_DidAvailableCbk    /* MISRA DEVIATION */
(
    const uint8 u1EventId                               /* MISRA DEVIATION */
)
{

    (void)Dcm_Dsp_SID2C_SDIDProc( DCM_DSP_SID2C_PROC_CHKAVAILABE ); /* no return check required */

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2C_ChkPosSizeCbk                              */
/* Description   | Callback function for event delivery registration of     */
/*               | ChkSDIDPosSize Function                                  */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID2C_ChkPosSizeCbk    /* MISRA DEVIATION */
(
    const uint8 u1EventId                             /* MISRA DEVIATION */
)
{

    (void)Dcm_Dsp_SID2C_SDIDProc( DCM_DSP_SID2C_PROC_CHKPOSSIZE ); /* no return check required */

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2C_ClearDDDID                                 */
/* Description   | Clear All DDDID                                          */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1SesCtrlTypeOld     : Session before change        */
/*               | [IN] u1SesCtrlTypeNew     : Session after change         */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID2C_ClearDDDID    /* MISRA DEVIATION */
(
    const Dcm_SesCtrlType u1SesCtrlTypeOld,
    const Dcm_SesCtrlType u1SesCtrlTypeNew
)
{
    uint8          u1_DspDDDIDClearSesChg;

    u1_DspDDDIDClearSesChg = Dcm_Dsp_Sid2C_u1DspDDDIDClearSesChg;

    if( u1_DspDDDIDClearSesChg == DCM_DSP_SID2C_CLEAR_ALL_SESCHG )
    {
        /* Clear all DDDID */
        (void)Dcm_Dsp_DidMng_ClearAllDDDID( DCM_DSP_DIDMNG_CLEAR_ALL_SESCHG ); /* no return check required */
    }
    else if( u1_DspDDDIDClearSesChg == DCM_DSP_SID2C_CLEAR_DEFAULT_SESCHG )
    {
        if( u1SesCtrlTypeNew == DCM_DEFAULT_SESSION )
        {
            /* Clear all DDDID */
            (void)Dcm_Dsp_DidMng_ClearAllDDDID( DCM_DSP_DIDMNG_CLEAR_ALL_SESCHG ); /* no return check required */
        }
    }
    else if( u1_DspDDDIDClearSesChg == DCM_DSP_SID2C_CLEAR_OUT_OF_SUPPORT_SESSION )
    {
        if( u1SesCtrlTypeOld != u1SesCtrlTypeNew )
        {
            /* Clear DDDID that not supported in u1SesCtrlTypeNew */
            Dcm_Dsp_DidMng_ClearNoSupDDDID( DCM_DSP_DIDMNG_CHECK_READ_SES, u1SesCtrlTypeNew );
        }
    }
    else
    {
        /* In case for DCM_DSP_SID2C_NOT_CLEAR_SESCHG */
        /* No process */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2C_NotifySecCtrl                              */
/* Description   | Notify of security level change.                         */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1SecLevelOld     : Security level before change    */
/*               | [IN] u1SecLevelNew     : Security level after change     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID2C_NotifySecCtrl /* MISRA DEVIATION */
(
    const Dcm_SecLevelType u1SecLevelOld,
    const Dcm_SecLevelType u1SecLevelNew
)
{
    uint8          u1_DspDDDIDClearSecChg;

    u1_DspDDDIDClearSecChg = Dcm_Dsp_Sid2C_u1DspDDDIDClearSecChg;

    if( u1_DspDDDIDClearSecChg == DCM_DSP_SID2C_CLEAR_OUT_OF_SUPPORT_SECURITY )
    {
        if( u1SecLevelOld != u1SecLevelNew )
        {
            /* Clear DDDID that not supported in u1SecLevelNew */
            Dcm_Dsp_DidMng_ClearNoSupDDDID( DCM_DSP_DIDMNG_CHECK_READ_SEC, u1SecLevelNew );
        }
    }

    return;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2C_InitialProc                                */
/* Description   | Initial process of SID 2C request                        */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1SubFunction  : Sub Function                       */
/*               | [IN] ptMsgContext   : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_InitialProc
(
    const uint8  u1SubFunction,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    Std_ReturnType u1_RetVal;
    
    if( u1SubFunction == DCM_DSP_SID2C_SF_SETDDDID )
    {
        u1_RetVal = Dcm_Dsp_SID2C_InitialProc_Sub01(ptMsgContext);
    }
    else if( u1SubFunction == DCM_DSP_SID2C_SF_SETDDDID_MEMADDR )
    {
        u1_RetVal = Dcm_Dsp_SID2C_InitialProc_Sub02(ptMsgContext);
    }
    else
    {
        u1_RetVal = Dcm_Dsp_SID2C_InitialProc_Sub03(ptMsgContext);
    }

    return u1_RetVal;

}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2C_CancelProc_Sub                             */
/* Description   | Cancel process of SID 2C request                         */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1SubFunction  : Sub Function                       */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_CancelProc
(
    const uint8  u1SubFunction
)
{
    Std_ReturnType u1_RetVal;
    
    if( u1SubFunction == DCM_DSP_SID2C_SF_SETDDDID )
    {
        u1_RetVal = Dcm_Dsp_SID2C_CancelProc_Sub01();
    }
    else if( u1SubFunction == DCM_DSP_SID2C_SF_SETDDDID_MEMADDR )
    {
        u1_RetVal = Dcm_Dsp_SID2C_CancelProc_Sub02();
    }
    else
    {
        u1_RetVal = Dcm_Dsp_SID2C_CancelProc_Sub03();
    }

    return u1_RetVal;

}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2C_InitialProc_Sub01                          */
/* Description   | Initial process of SID 2C subfunction 01 request         */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext   : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_InitialProc_Sub01
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    Std_ReturnType  u1_RetVal;
    Std_ReturnType  u1_ChkReqLen;
    Std_ReturnType  u1_RetChkDDDID;
    uint16          u2_Did;
    uint32          u4_ReqDataLen;

    u1_RetVal = E_OK;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );

    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;

    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

    u1_ChkReqLen = E_NOT_OK;
    u4_ReqDataLen = Dcm_Dsp_Main_stMsgContext.reqDataLen;
    if( u4_ReqDataLen >= DCM_DSP_SID2C_SF01_REQLEN_MIN )
    {
        if( ( ( u4_ReqDataLen - DCM_DSP_SID2C_REQLEN_DDDID ) & DCM_DSP_SID2C_SF01_REQLEN_MASK ) == (uint32)0U ) /* no wrap around */
        {
            u1_ChkReqLen = E_OK;
        }
    }

    if( u1_ChkReqLen == (Std_ReturnType)E_OK )
    {
        /* Check DDDID */
        u2_Did = (uint16)(((uint16)Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2C_REQDATA_DIDHIGH]) << DCM_DSP_SID2C_DID_SHIFT )
                        | ((uint16)Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2C_REQDATA_DIDLOW]);
        u1_RetChkDDDID = Dcm_Dsp_SID2C_ChkDDDID( u2_Did, DCM_DSP_SID2C_SF_SETDDDID );
        if( u1_RetChkDDDID == (Std_ReturnType)E_OK )
        {
            Dcm_Dsp_SID2C_u4SDIDChkCnt = (uint32)0U;

            u1_RetVal = Dcm_Dsp_SID2C_SDIDProc( DCM_DSP_SID2C_PROC_CHKSUPPORT );

        }
    }
    else
    {
        /* NRC 0x13 */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT );
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2C_CancelProc_Sub01                           */
/* Description   | Cancel process of SID 2C subfunction 01 request          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_CancelProc_Sub01
( void )
{
    boolean              b_UserNotifyFlag;
    Dcm_DidSupportedType u1_Supported;
    uint32               u4_DataLen;
    uint16               u2_SDID;
    uint16               u2_SDIDIndex;

    b_UserNotifyFlag = Dcm_Dsp_Main_GetUserNotifyFlag();
    if( b_UserNotifyFlag == (boolean)TRUE )
    {
        u2_SDID         = Dcm_Dsp_SID2C_u2SDID;
        u2_SDIDIndex    = Dcm_Dsp_SID2C_u2SDIDIndex;

        u1_Supported = DCM_DID_NOT_SUPPORTED;
        (void)Dcm_Dsp_DidMng_CallAvailableFnc( u2_SDIDIndex, u2_SDID, DCM_CANCEL, &u1_Supported ); /* no return check required */

        u4_DataLen = (uint32)0U;
        (void)Dcm_Dsp_DidMng_CallDataLengthFnc( u2_SDIDIndex, u2_SDID, DCM_CANCEL, &u4_DataLen ); /* no return check required */

        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

        (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID2C_DIDAVAILABLE,  (boolean)FALSE ); /* no return check required */
        (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID2C_CHKPOSSIZE,    (boolean)FALSE ); /* no return check required */
    }

    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return E_OK;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2C_SDIDProc                                   */
/* Description   | SDID process of SID 2C subfunction 01 request            */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1ProcId       : Process ID                         */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_SDIDProc
(
    const uint8 u1ProcId
)
{
    Std_ReturnType  u1_RetVal;
    Std_ReturnType  u1_RetChkSDID;
    Std_ReturnType  u1_RetChkCondition;
    Std_ReturnType  u1_RetSetDDDID;
    uint32          u4_SDIDNum;

    u1_RetVal = E_OK;

    u1_RetChkSDID = Dcm_Dsp_SID2C_ChkSDID( u1ProcId );
    if( u1_RetChkSDID == (Std_ReturnType)E_OK )
    {
        u1_RetChkCondition = Dcm_Dsp_SID2C_ChkCondition( DCM_DSP_SID2C_SF_SETDDDID );
        if( u1_RetChkCondition == (Std_ReturnType)E_OK )
        {
            /* Set DDDID */
            u4_SDIDNum = ( Dcm_Dsp_Main_stMsgContext.reqDataLen - DCM_DSP_SID2C_REQLEN_DDDID ) >> DCM_DSP_SID2C_SDIDNUM_SHIFT;  /* no wrap around */
            u1_RetSetDDDID = Dcm_Dsp_DidMng_SetDDDID( DCM_DSP_DIDMNG_DATA_IDENTIFIER, Dcm_Dsp_Main_stMsgContext.reqData, (uint8)u4_SDIDNum );

            if( u1_RetSetDDDID == (Std_ReturnType)E_OK )
            {
                /* Positive response */
                Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID2C_RESDATA_DIDHIGH] = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2C_REQDATA_DIDHIGH];
                Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID2C_RESDATA_DIDLOW ] = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2C_REQDATA_DIDLOW ];
                Dcm_Dsp_Main_stMsgContext.resDataLen = DCM_DSP_SID2C_RESLEN_DID;
                Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
            }
        }
    }
    else if( u1_RetChkSDID == (Std_ReturnType)DCM_E_PENDING )
    {
        u1_RetVal = DCM_E_PENDING;
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2C_ChkDDDID                                   */
/* Description   | Check DDDID of request data                              */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u2Did           : DDDID                             */
/* Parameters    | [IN] u1SubFunction   : Sub function                      */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK               : Check OK                          */
/*               |   E_NOT_OK           : Check NG                          */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_ChkDDDID
(
    const uint16 u2Did,
    const uint8  u1SubFunction
)
{
    uint32                          u4_SDIDNum;
    uint32                          u4_MemSizeLen;
    uint32                          u4_SDIDCnt;
    uint16                          u2_DidIndex;
    uint16                          u2_DynamicIndex;
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetChkLimit;
    Std_ReturnType                  u1_RetChkSes;
    Std_ReturnType                  u1_RetChkSec;
    Std_ReturnType                  u1_RetSupportedDid;
    Std_ReturnType                  u1_RetChkModeRule;
    Dcm_Main_ReturnCheckType        u1_RetChkDid;
    uint8                           u1_CRWSupport;
    uint8                           u1_NumOfSourceDid;
    Dcm_SesCtrlType                 u1_SesCtrlType;
    Dcm_SecLevelType                u1_SecLevel;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;

    u1_RetVal = E_NOT_OK;
    u1_RetChkLimit = E_OK;
    u1_ErrorCode = DCM_E_GENERALREJECT;

    /* Check DID support */
    u2_DidIndex   = (uint16)0U;
    u1_CRWSupport = (uint8)0U;
    u1_RetChkDid = Dcm_Dsp_DidMng_ChkDid( u2Did,
                                          DCM_DSP_DIDMNG_DID,
                                          &u2_DidIndex,
                                          &u1_CRWSupport );
    if( u1_RetChkDid == DCM_MAIN_E_CHECK_OK )
    {
        if( ( u1_CRWSupport & DCM_DSP_DIDMNG_READ_ONLY_DYN ) == DCM_DSP_DIDMNG_READ_ONLY_DYN )
        {
            u1_RetSupportedDid = Dcm_Dsp_DidMng_CheckSupportedDid( u2Did, DCM_DID_REQTYPE_DYNAMIC_DDDID, Dcm_Dsp_Main_stMsgContext.dcmRxPduId );
            if( u1_RetSupportedDid == (Std_ReturnType)E_OK )
            {
                if( u1SubFunction == DCM_DSP_SID2C_SF_SETDDDID )
                {
                    /* Check the number of data and data length that can be defined with DDDID */
                    u4_SDIDNum = ( Dcm_Dsp_Main_stMsgContext.reqDataLen - DCM_DSP_SID2C_REQLEN_DDDID ) >> DCM_DSP_SID2C_SDIDNUM_SHIFT;  /* no wrap around */
                    u4_MemSizeLen = (uint32)0U;
                    for( u4_SDIDCnt = (uint32)0U; u4_SDIDCnt < u4_SDIDNum; u4_SDIDCnt++ )
                    {
                        u4_MemSizeLen += Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2C_REQDATA_SIZE + (u4_SDIDCnt * DCM_DSP_SID2C_SF01_REQLEN_SDID)]; /* no wrap around */
                    }
                    u1_RetChkLimit = Dcm_Dsp_DidMng_ChkDDDIDLimit( u2_DidIndex, u4_SDIDNum, u4_MemSizeLen );
                }
                if( u1_RetChkLimit == (Std_ReturnType)E_OK  )
                {
                    /* Get active session */
                    u1_SesCtrlType = DCM_DEFAULT_SESSION;
                    ( void )Dcm_GetSesCtrlType( &u1_SesCtrlType ); /* no return check required */

                    /* Check session support  */
                    u1_RetChkSes = Dcm_Dsp_DidMng_ChkDidInfo( u2_DidIndex, DCM_DSP_DIDMNG_DID, DCM_DSP_DIDMNG_CHECK_READ_SES, u1_SesCtrlType );
                    if( u1_RetChkSes == (Std_ReturnType)E_OK )
                    {
                        /* Get active security level */
                        u1_SecLevel = DCM_SEC_LEV_LOCKED;
                        ( void )Dcm_GetSecurityLevel( &u1_SecLevel ); /* no return check required */

                        /* Check security level support */
                        u1_RetChkSec = Dcm_Dsp_DidMng_ChkDidInfo( u2_DidIndex, DCM_DSP_DIDMNG_DID, DCM_DSP_DIDMNG_CHECK_READ_SEC, u1_SecLevel );
                        if( u1_RetChkSec == (Std_ReturnType)E_OK )
                        {
                            if( u1SubFunction == DCM_DSP_SID2C_SF_SETDDDID)
                            {
                                /* Get DDDID Index */
                                u2_DynamicIndex   = (uint16)0U;
                                u1_NumOfSourceDid = (uint8)0U;
                                /* Return value have already checked in Dcm_Dsp_DidMng_ChkDDDIDLimit(). */
                                ( void )Dcm_Dsp_DidMng_ChkDynamic( u2Did, &u1_NumOfSourceDid, &u2_DynamicIndex ); /* no return check required */

                                u1_RetChkModeRule = Dcm_Dsp_DidMng_DynDidModeRuleFnc( u2_DynamicIndex, DCM_DSP_DIDMNG_CHECK_READ_MR, &u1_ErrorCode);
                                
                                if( u1_RetChkModeRule == (Std_ReturnType)E_OK )
                                {
                                    u1_RetVal = E_OK;
                                }
                                else
                                {
                                    if( u1_ErrorCode != (Dcm_NegativeResponseCodeType)0x00 )
                                    {
                                        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_ErrorCode );
                                    }
                                    else
                                    {
                                        /* NRC 0x10 */
                                        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_GENERALREJECT );
                                    }
                                }
                            }
                            else
                            {
                                u1_RetVal = E_OK;
                            }
                        }
                        else
                        {
                            /* NRC 0x33 */
                            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_SECURITYACCESSDENIED );
                        }
                    }
                    else
                    {
                        /* NRC 0x31 */
                        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
                    }
                }
                else
                {
                    /* NRC 0x31 */
                    Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
                }
            }
            else
            {
                /* NRC 0x31 */
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
            }
        }
        else
        {
            /* NRC 0x31 */
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
        }
    }
    else if( u1_RetChkDid == DCM_MAIN_E_CHECK_NOT_OK )
    {
        /* NRC 0x31 */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2C_ChkSDID                                    */
/* Description   | Check SDID of request data                               */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1ProcId       : Process ID                         */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Check OK                           */
/*               |   E_NOT_OK          : Check NG                           */
/*               |   DCM_E_PENDING     : PENDING                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_ChkSDID
(
    const uint8 u1ProcId
)
{
    boolean                         b_BreakFlag;
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetChkFunc;
    uint8                           u1_ChkProcId;
    uint32                          u4_SDIDCnt;
    uint32                          u4_SDIDNum;

    u1_RetVal = E_OK;
    b_BreakFlag = (boolean)FALSE;
    u1_ChkProcId  = u1ProcId;

    u4_SDIDNum = ( Dcm_Dsp_Main_stMsgContext.reqDataLen - DCM_DSP_SID2C_REQLEN_DDDID ) >> DCM_DSP_SID2C_SDIDNUM_SHIFT;  /* no wrap around */
    for( u4_SDIDCnt = Dcm_Dsp_SID2C_u4SDIDChkCnt; u4_SDIDCnt < u4_SDIDNum; u4_SDIDCnt++ )
    {
        Dcm_Dsp_SID2C_u2SDID = (uint16)(((uint16)Dcm_Dsp_Main_stMsgContext.reqData[( u4_SDIDCnt * DCM_DSP_SID2C_SF01_REQLEN_SDID ) + DCM_DSP_SID2C_REQDATA_SDIDHIGH]) << DCM_DSP_SID2C_DID_SHIFT )  /* no wrap around */
                                      | ((uint16)Dcm_Dsp_Main_stMsgContext.reqData[( u4_SDIDCnt * DCM_DSP_SID2C_SF01_REQLEN_SDID ) + DCM_DSP_SID2C_REQDATA_SDIDLOW]);   /* no wrap around */

        if( u1_ChkProcId == DCM_DSP_SID2C_PROC_CHKSUPPORT )
        {
            u1_RetChkFunc = Dcm_Dsp_SID2C_ChkSDIDSupport();
        }
        else if( u1_ChkProcId == DCM_DSP_SID2C_PROC_CHKAVAILABE )
        {
            u1_RetChkFunc = Dcm_Dsp_SID2C_ChkSDIDAvailable( DCM_PENDING );
        }
        else
        {
            u1_RetChkFunc = Dcm_Dsp_SID2C_ChkSDIDPosSize( DCM_PENDING );
        }

        if( u1_RetChkFunc == (Std_ReturnType)E_OK )
        {
            Dcm_Dsp_SID2C_u4SDIDChkCnt++;   /* no wrap around */
            u1_ChkProcId  = DCM_DSP_SID2C_PROC_CHKSUPPORT;
        }
        else if( u1_RetChkFunc == (Std_ReturnType)E_NOT_OK )
        {
            b_BreakFlag = (boolean)TRUE;
            u1_RetVal = E_NOT_OK;
        }
        else
        {
            b_BreakFlag = (boolean)TRUE;
            u1_RetVal = DCM_E_PENDING;
        }

        if( b_BreakFlag == (boolean)TRUE )
        {
            break;
        }
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2C_ChkSDIDSupport                             */
/* Description   | Support check SDID of request data                       */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Check OK                           */
/*               |   E_NOT_OK          : Check NG                           */
/*               |   DCM_E_PENDING     : PENDING                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_ChkSDIDSupport
( void )
{
    Std_ReturnType u1_RetVal;
    Dcm_Main_ReturnCheckType        u1_RetChkDid;
    uint8                           u1_CRWSupport;
    uint16                          u2_SDIDIndex;

    u1_RetVal = E_NOT_OK;

    /* Check SDID support */
    u1_CRWSupport = (uint8)0U;
    u2_SDIDIndex = (uint16)0U;
    u1_RetChkDid = Dcm_Dsp_DidMng_ChkDid( Dcm_Dsp_SID2C_u2SDID,
                                          DCM_DSP_DIDMNG_DID_RANGE,
                                          &u2_SDIDIndex,
                                          &u1_CRWSupport );
    Dcm_Dsp_SID2C_u2SDIDIndex = u2_SDIDIndex;
    if( u1_RetChkDid == DCM_MAIN_E_CHECK_OK )
    {
        if( ( u1_CRWSupport & DCM_DSP_DIDMNG_READ_ONLY ) == DCM_DSP_DIDMNG_READ_ONLY )
        {
            u1_RetVal = Dcm_Dsp_SID2C_ChkSDIDAvailable( DCM_INITIAL );
        }
        else
        {
            /* NRC 0x31 */
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
        }
    }
    else if( u1_RetChkDid == DCM_MAIN_E_CHECK_NOT_OK )
    {
        /* NRC 0x31 */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2C_ChkSDIDAvailable                           */
/* Description   | Available check SDID of request data                     */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1OpStatus     : Operation state                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Check OK                           */
/*               |   E_NOT_OK          : Check NG                           */
/*               |   DCM_E_PENDING     : PENDING                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_ChkSDIDAvailable
(
    const Dcm_OpStatusType u1OpStatus
)
{
    Std_ReturnType          u1_RetVal;
    Std_ReturnType          u1_RetAvailableFnc;
    Std_ReturnType          u1_RetSupportedDid;
    Dcm_DidSupportedType    u1_Supported;

    u1_RetVal = E_NOT_OK;

    u1_Supported = DCM_DID_NOT_SUPPORTED;
    u1_RetAvailableFnc = Dcm_Dsp_DidMng_CallAvailableFnc( Dcm_Dsp_SID2C_u2SDIDIndex,
                                                          Dcm_Dsp_SID2C_u2SDID,
                                                          u1OpStatus,
                                                          &u1_Supported );
    if( u1_RetAvailableFnc == (Std_ReturnType)E_OK )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

        if( u1_Supported == (Dcm_DidSupportedType)DCM_DID_SUPPORTED )
        {
            u1_RetSupportedDid = Dcm_Dsp_DidMng_CheckSupportedDid( Dcm_Dsp_SID2C_u2SDID, DCM_DID_REQTYPE_DYNAMIC_SOURCE, Dcm_Dsp_Main_stMsgContext.dcmRxPduId );
            if( u1_RetSupportedDid == (Std_ReturnType)E_OK )
            {
                u1_RetVal = Dcm_Dsp_SID2C_ChkSDIDSesSupport();
            }
            else
            {
                /* NRC 0x31 */
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
            }
        }
        else
        {
            /* NRC 0x31 */
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
        }
    }
    else if( u1_RetAvailableFnc == (Std_ReturnType)DCM_E_PENDING )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        ( void )Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID2C_DIDAVAILABLE ); /* no return check required */
        u1_RetVal = DCM_E_PENDING;
    }
    else
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2C_ChkSDIDSesSupport                          */
/* Description   | Session support check SDID of request data               */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Check OK                           */
/*               |   E_NOT_OK          : Check NG                           */
/*               |   DCM_E_PENDING     : PENDING                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_ChkSDIDSesSupport
( void )
{
    Std_ReturnType  u1_RetVal;
    Std_ReturnType  u1_RetChkSes;
    Dcm_SesCtrlType u1_SesCtrlType;

    u1_RetVal = E_NOT_OK;

    /* Get active session */
    u1_SesCtrlType = DCM_DEFAULT_SESSION;
    ( void )Dcm_GetSesCtrlType( &u1_SesCtrlType ); /* no return check required */

    /* Check session support  */
    u1_RetChkSes = Dcm_Dsp_DidMng_ChkDidInfo( Dcm_Dsp_SID2C_u2SDIDIndex, DCM_DSP_DIDMNG_DID_RANGE, DCM_DSP_DIDMNG_CHECK_READ_SES, u1_SesCtrlType );
    if( u1_RetChkSes == (Std_ReturnType)E_OK )
    {
        u1_RetVal = Dcm_Dsp_SID2C_ChkSDIDSecSupport();
    }
    else
    {
        /* NRC 0x31 */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2C_ChkSDIDPosSize                             */
/* Description   | Check Position and Memsize of request data               */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1OpStatus     : Operation state                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Check OK                           */
/*               |   E_NOT_OK          : Check NG                           */
/*               |   DCM_E_PENDING     : PENDING                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_ChkSDIDPosSize
(
    const Dcm_OpStatusType u1OpStatus
)
{
    Std_ReturnType  u1_RetVal;
    Std_ReturnType  u1_RetDataLen;
    Std_ReturnType  u1_ChkSDidSize;
    Std_ReturnType  u1_ChkPosSize;
    uint8           u1_DataPosition;
    uint8           u1_DataMemSize;
    uint32          u4_DataLen;
    uint32          u4_SDIDChkCnt;

    u1_RetVal = E_NOT_OK;

    u4_DataLen = (uint32)0U;
    u1_RetDataLen = Dcm_Dsp_DidMng_CallDataLengthFnc( Dcm_Dsp_SID2C_u2SDIDIndex,
                                                      Dcm_Dsp_SID2C_u2SDID,
                                                      u1OpStatus,
                                                      &u4_DataLen );

    if( u1_RetDataLen == (Std_ReturnType)E_OK )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

        u1_ChkSDidSize = Dcm_Dsp_DidMng_ChkSDidSize( u4_DataLen );

        if( u1_ChkSDidSize == (Std_ReturnType)E_OK )
        {
            u4_SDIDChkCnt = Dcm_Dsp_SID2C_u4SDIDChkCnt;
            u1_DataPosition = Dcm_Dsp_Main_stMsgContext.reqData[( u4_SDIDChkCnt * DCM_DSP_SID2C_SF01_REQLEN_SDID ) + DCM_DSP_SID2C_REQDATA_POS];    /* no wrap around */
            u1_DataMemSize  = Dcm_Dsp_Main_stMsgContext.reqData[( u4_SDIDChkCnt * DCM_DSP_SID2C_SF01_REQLEN_SDID ) + DCM_DSP_SID2C_REQDATA_SIZE];   /* no wrap around */

            u1_ChkPosSize = E_NOT_OK;
            if( u1_DataPosition != (uint8)0U )
            {
                if( u1_DataMemSize != (uint8)0U )
                {
                    if( ( ( (uint32)u1_DataMemSize + u1_DataPosition ) - (uint32)1U ) <= u4_DataLen )   /* no wrap around */
                    {
                        u1_ChkPosSize = E_OK;
                    }
                }
            }

            if( u1_ChkPosSize == (Std_ReturnType)E_OK )
            {
                u1_RetVal = E_OK;
            }
            else
            {
                /* NRC 0x31 */
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
            }
        }
        else
        {
            /* NRC 0x31 */
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
        }
    }
    else if( u1_RetDataLen == (Std_ReturnType)E_NOT_OK )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        /* NRC 0x31 */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
    }
    else if( u1_RetDataLen == (Std_ReturnType)DCM_E_PENDING )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        ( void )Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID2C_CHKPOSSIZE ); /* no return check required */
        u1_RetVal = DCM_E_PENDING;
    }
    else
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2C_ChkSDIDSecSupport                          */
/* Description   | Security support check SDID of request data              */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Check OK                           */
/*               |   E_NOT_OK          : Check NG                           */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_ChkSDIDSecSupport
( void )
{
    Std_ReturnType u1_RetVal;
    Std_ReturnType                  u1_RetChkSec;
    Std_ReturnType                  u1_RetChkModeRule;
    Dcm_SecLevelType                u1_SecLevel;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;

    u1_RetVal = E_NOT_OK;
    u1_ErrorCode = DCM_E_GENERALREJECT; 

    /* Get active security level */
    u1_SecLevel = DCM_SEC_LEV_LOCKED;
    ( void )Dcm_GetSecurityLevel( &u1_SecLevel ); /* no return check required */

    /* Check security level support */
    u1_RetChkSec = Dcm_Dsp_DidMng_ChkDidInfo( Dcm_Dsp_SID2C_u2SDIDIndex, DCM_DSP_DIDMNG_DID_RANGE, DCM_DSP_DIDMNG_CHECK_READ_SEC, u1_SecLevel );
    if( u1_RetChkSec == (Std_ReturnType)E_OK )
    {
        u1_RetChkModeRule = Dcm_Dsp_DidMng_CallModeRuleFnc( Dcm_Dsp_SID2C_u2SDIDIndex, DCM_DSP_DIDMNG_CHECK_READ_MR, Dcm_Dsp_SID2C_u2SDID, &u1_ErrorCode);
        if( u1_RetChkModeRule == (Std_ReturnType)E_OK )
        {
            u1_RetVal = Dcm_Dsp_SID2C_ChkSDIDPosSize( DCM_INITIAL );
        }
        else if( u1_RetChkModeRule == (Std_ReturnType)E_NOT_OK )
        {
            if( u1_ErrorCode != (Dcm_NegativeResponseCodeType)0x00 )
            {
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_ErrorCode );
            }
            /* No error code */
            else
            {
                /* NRC 0x10 */
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_GENERALREJECT );
            }
        }
        else
        {
            /* NRC 0x10 */
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_GENERALREJECT );
        }
    }
    else
    {
        /* NRC 0x33 */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_SECURITYACCESSDENIED );
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2C_InitialProc_Sub02                          */
/* Description   | Initial process of SID 2C subfunction 02 request         */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext   : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_InitialProc_Sub02
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    uint32          u4_ReqDataLen;
    uint32          u4_DataLenLeft;
    uint32          u4_MemAddrNum;
    uint32          u4_MemAddrMaxNum;
    uint16          u2_Did;
    uint8           u1_MemAddrByteNum;
    uint8           u1_MemSizeByteNum;
    Std_ReturnType  u1_RetChkDDDID;
    Std_ReturnType  u1_RetChkALFID;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );

    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;

    u4_ReqDataLen = Dcm_Dsp_Main_stMsgContext.reqDataLen;
    if( u4_ReqDataLen >= DCM_DSP_SID2C_SF02_REQLEN_MIN )
    {
        /* Check DDDID */
        u2_Did = (uint16)(((uint16)Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2C_REQDATA_DIDHIGH]) << DCM_DSP_SID2C_DID_SHIFT )
                        | ((uint16)Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2C_REQDATA_DIDLOW]);
        u1_RetChkDDDID = Dcm_Dsp_SID2C_ChkDDDID( u2_Did, DCM_DSP_SID2C_SF_SETDDDID_MEMADDR );
        if( u1_RetChkDDDID == (Std_ReturnType)E_OK )
        {

            if( Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2C_REQDATA_ALFID] != (uint8)0U )
            {
                u1_MemAddrByteNum = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2C_REQDATA_ALFID] & DCM_DSP_SID2C_ALFID_MEMADDR_MASK;
                u1_MemSizeByteNum = ((Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2C_REQDATA_ALFID]) >> DCM_DSP_SID2C_ALFID_SHIFT4);

                u4_MemAddrMaxNum = (uint32)((u4_ReqDataLen - DCM_DSP_SID2C_REQLEN_DDDID) - DCM_DSP_SID2C_SF02_REQLEN_ALFID);    /* no wrap around */
                u4_DataLenLeft = u4_MemAddrMaxNum;
                for( u4_MemAddrNum = (uint32)0U; u4_MemAddrNum < u4_MemAddrMaxNum; u4_MemAddrNum++ )
                {
                    if( u4_DataLenLeft >= ((uint32)u1_MemAddrByteNum + (uint32)u1_MemSizeByteNum))  /* no wrap around */
                    {
                        u4_DataLenLeft -= ((uint32)u1_MemAddrByteNum + (uint32)u1_MemSizeByteNum);  /* no wrap around */
                    }
                    else
                    {
                        break;
                    }
                }

                if( u4_DataLenLeft == (uint32)0U )
                {
                    /* Check Request addressAndLengthFormatIdentifier */
                    u1_RetChkALFID = Dcm_Dsp_SID2C_ChkALFID( Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2C_REQDATA_ALFID] );
                    if( u1_RetChkALFID == (Std_ReturnType)E_OK )
                    {
                        (void)Dcm_Dsp_SID2C_MemAddrProc( u1_MemAddrByteNum, u1_MemSizeByteNum, u4_MemAddrNum ); /* no return check required */
                    }
                    else
                    {
                        /* NRC 0x31 */
                        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
                    }
                }
                else
                {
                    /* NRC 0x13 */
                    Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT );
                }
            }
            else
            {
                /* NRC 0x13 */
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT );
            }
        }
    }
    else
    {
        /* NRC 0x13 */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT );
    }

    return E_OK;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2C_CancelProc_Sub02                           */
/* Description   | Cancel process of SID 2C subfunction 02 request          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_CancelProc_Sub02
( void )
{
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return E_OK;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2C_MemAddrProc                                */
/* Description   | MemoryAddress process of SID 2C subfunction 02 request   */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1MemAddrByteNum  : Number of Memory Address Bytes  */
/*               | [IN] u1MemSizeByteNum  : Number of Memory Size Bytes     */
/*               | [IN] u4MemAddrNum      : Number of Memory Address        */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_MemAddrProc
(
    const uint8  u1MemAddrByteNum,
    const uint8  u1MemSizeByteNum,
    const uint32 u4MemAddrNum
)
{
    Std_ReturnType  u1_RetChkMemAddr;
    Std_ReturnType  u1_RetChkCondition;
    Std_ReturnType  u1_RetSetDDDID;


    u1_RetChkMemAddr = Dcm_Dsp_SID2C_ChkMemAddr( u1MemAddrByteNum, u1MemSizeByteNum, u4MemAddrNum );
    if( u1_RetChkMemAddr == (Std_ReturnType)E_OK )
    {
        u1_RetChkCondition = Dcm_Dsp_SID2C_ChkCondition( DCM_DSP_SID2C_SF_SETDDDID_MEMADDR );
        if( u1_RetChkCondition == (Std_ReturnType)E_OK )
        {
            /* Set DDDID */
            u1_RetSetDDDID = Dcm_Dsp_DidMng_SetDDDID( DCM_DSP_DIDMNG_MEM_ADDRESS, Dcm_Dsp_Main_stMsgContext.reqData, (uint8)u4MemAddrNum );

            if( u1_RetSetDDDID == (Std_ReturnType)E_OK )
            {
                /* Positive response */
                Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID2C_RESDATA_DIDHIGH] = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2C_REQDATA_DIDHIGH];
                Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID2C_RESDATA_DIDLOW ] = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2C_REQDATA_DIDLOW ];
                Dcm_Dsp_Main_stMsgContext.resDataLen = DCM_DSP_SID2C_RESLEN_DID;
                Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
            }
        }
    }
    else
    {
        /* No process */
    }

    return E_OK;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2C_ChkMemAddrSesSupport                       */
/* Description   | Session support check Memory Address of request data     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Check OK                           */
/*               |   E_NOT_OK          : Check NG                           */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_ChkMemAddrSesSupport
(
    const uint8 u1MemIdIndex,
    const uint8 u1MemRangeIndex
)
{
    Std_ReturnType        u1_RetVal;
    Dcm_SesCtrlType       u1_SesCtrlType;

    /* Get active session */
    u1_SesCtrlType = DCM_DEFAULT_SESSION;
    (void)Dcm_GetSesCtrlType( &u1_SesCtrlType ); /* no return check required */
    /* Check session support */
    u1_RetVal = Dcm_Dsp_DidMng_ChkMemSes( DCM_DSP_DIDMNG_MEM_READ,
                                                u1MemIdIndex,
                                                u1MemRangeIndex,
                                                u1_SesCtrlType );

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2C_ChkMemAddrSecSupport                       */
/* Description   | Security support check Memory Address of request data    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Check OK                           */
/*               |   E_NOT_OK          : Check NG                           */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_ChkMemAddrSecSupport
(
    const uint8 u1MemIdIndex,
    const uint8 u1MemRangeIndex
)
{
    Std_ReturnType        u1_RetVal;
    Dcm_SecLevelType      u1_SecLevel;

    /* Get active security level */
    (void)Dcm_GetSecurityLevel( &u1_SecLevel ); /* no return check required */
    /* Check Security lock is canceled */
    u1_RetVal = Dcm_Dsp_DidMng_ChkMemSec( DCM_DSP_DIDMNG_MEM_READ,
                                                u1MemIdIndex,
                                                u1MemRangeIndex,
                                                u1_SecLevel );

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2C_ChkALFID                                   */
/* Description   | Check addressAndLengthFormatIdentifier of request data   */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1ALFID  : addressAndLengthFormatIdentifier         */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK               : Check OK                          */
/*               |   E_NOT_OK           : Check NG                          */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_ChkALFID
(
    const uint8 u1ALFID
)
{
    Std_ReturnType    u1_RetVal;


    u1_RetVal = Dcm_Dsp_DidMng_ChkALFID( u1ALFID );

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2C_ChkMemAddr                                 */
/* Description   | Check Memory Address of request data                     */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1MemAddrByteNum  : Number of Memory Address Bytes  */
/*               | [IN] u1MemSizeByteNum  : Number of Memory Size Bytes     */
/*               | [IN] u4MemAddrNum      : Number of Memory Address        */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK               : Check OK                          */
/*               |   E_NOT_OK           : Check NG                          */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_ChkMemAddr
(
    const uint8  u1MemAddrByteNum,
    const uint8  u1MemSizeByteNum,
    const uint32 u4MemAddrNum
)
{
    uint32                          u4_MemAddrCnt;
    uint32                          u4_MemAddrPos;
    uint32                          u4_MemAddr;
    uint32                          u4_MemSize;
    uint32                          u4_MemSizeTotal;
    uint16                          u2_Did;
    uint16                          u2_DidIndex;
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetChkMemAddr;
    Std_ReturnType                  u1_RetChkMemAddrSes;
    Std_ReturnType                  u1_RetChkMemAddrSec;
    Std_ReturnType                  u1_RetChkMemRange;
    Std_ReturnType                  u1_RetChkLimitAddr;
    Std_ReturnType                  u1_RetChkMemSize;
    Std_ReturnType                  u1_ChkSDidSize;
    uint8                           u1_MemId;
    uint8                           u1_MemIdFlag;
    uint8                           u1_MemAddrConvertCnt;
    uint8                           u1_MemIdIndex;
    uint8                           u1_MemRangeIndex;
    uint8                           u1_CRWSupport;
    uint8                           u1_MemSizeCnt;
    boolean                         b_BreakFlag;
    boolean                         b_CheckMemAddrUseAsMemoryId;

    b_BreakFlag     = (boolean)FALSE;
    u1_RetVal       = E_OK;
    u2_DidIndex     = (uint16)0U;
    u1_CRWSupport   = (uint8)0U;
    u4_MemSizeTotal = (uint32)0U;
    b_CheckMemAddrUseAsMemoryId = Dcm_Dsp_MemMng_GetUseAsMemoryId();

    u2_Did = (uint16)(((uint16)Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2C_REQDATA_DIDHIGH]) << DCM_DSP_SID2C_DID_SHIFT )
                    | ((uint16)Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2C_REQDATA_DIDLOW]);
    (void)Dcm_Dsp_DidMng_ChkDid( u2_Did,                /* no return check required */
                                 DCM_DSP_DIDMNG_DID,
                                 &u2_DidIndex,
                                 &u1_CRWSupport );

    for( u4_MemAddrCnt = (uint32)0U; u4_MemAddrCnt < u4MemAddrNum; u4_MemAddrCnt++ )
    {
        u4_MemAddrPos = (uint32)((u4_MemAddrCnt * ((uint32)u1MemAddrByteNum + (uint32)u1MemSizeByteNum)) + (uint32)DCM_DSP_SID2C_REQDATA_MEMADDR_POS);  /* no wrap around */
        u4_MemSize = (uint32)0U;
        for( u1_MemSizeCnt = (uint8)0U; u1_MemSizeCnt < u1MemSizeByteNum; u1_MemSizeCnt++ )
        {
            u4_MemSize <<= DCM_DSP_SID2C_MEMSIZE_SHIFT8;
            u4_MemSize += Dcm_Dsp_Main_stMsgContext.reqData[u4_MemAddrPos + u1MemAddrByteNum + u1_MemSizeCnt];  /* no wrap around */
        }
        
        u1_RetChkMemRange = E_NOT_OK;
        if( u4_MemSize > (uint32)0U )
        {
            /* Check DcmDspMemAddrUseAsMemId */
            if( b_CheckMemAddrUseAsMemoryId == (boolean)TRUE )
            {
                u1_MemId = Dcm_Dsp_Main_stMsgContext.reqData[u4_MemAddrPos];
                u1_MemIdFlag = DCM_DSP_DIDMNG_MEM_ID_VALID;
                u1_MemAddrConvertCnt = DCM_DSP_SID2C_MEMID_SET;
            }
            else
            {
                u1_MemId = (uint8)0U;
                u1_MemIdFlag = DCM_DSP_DIDMNG_MEM_ID_INVALID;
                u1_MemAddrConvertCnt = DCM_DSP_SID2C_MEMID_NOT_SET;
            }

            u4_MemAddr = (uint32)0U;
            /* Convert MemoryAddress into uint32 */
            for( ; u1_MemAddrConvertCnt < u1MemAddrByteNum; u1_MemAddrConvertCnt++ )
            {
                u4_MemAddr <<= DCM_DSP_SID2C_MEMADDR_SHIFT8;
                u4_MemAddr += Dcm_Dsp_Main_stMsgContext.reqData[u4_MemAddrPos + u1_MemAddrConvertCnt];  /* no wrap around */
            }
            /* Check MemoryAddress */
            u1_RetChkMemAddr = Dcm_Dsp_DidMng_ChkMemAddress( DCM_DSP_DIDMNG_MEM_READ,
                                                             u4_MemAddr,
                                                             u1_MemIdFlag,
                                                             u1_MemId,
                                                             &u1_MemIdIndex,
                                                             &u1_MemRangeIndex );
            if( u1_RetChkMemAddr == (Std_ReturnType)E_OK )
            {
                u1_RetChkMemRange = Dcm_Dsp_DidMng_ChkMemSize( DCM_DSP_DIDMNG_MEM_READ,
                                                               u1_MemIdIndex,
                                                               u1_MemRangeIndex,
                                                               u4_MemAddr,
                                                               u4_MemSize );
            }
        }

        if( u1_RetChkMemRange == (Std_ReturnType)E_OK )
        {
            u4_MemSizeTotal += u4_MemSize;  /* no wrap around */

            u1_RetChkLimitAddr = Dcm_Dsp_DidMng_ChkDDDIDLimitMemAddr( u2_DidIndex, u4MemAddrNum, u4_MemSizeTotal );
            if( u1_RetChkLimitAddr != (Std_ReturnType)E_OK )
            {
                /* NRC 0x31 */
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
                b_BreakFlag = (boolean)TRUE;
            }
        }
        else
        {
            /* NRC 0x31 */
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
            b_BreakFlag = (boolean)TRUE;
        }

        if( b_BreakFlag == (boolean)FALSE )
        {
            u1_RetChkMemAddrSes = Dcm_Dsp_SID2C_ChkMemAddrSesSupport( u1_MemIdIndex, u1_MemRangeIndex );
            if( u1_RetChkMemAddrSes == (Std_ReturnType)E_OK )
            {
                u1_RetChkMemAddrSec = Dcm_Dsp_SID2C_ChkMemAddrSecSupport( u1_MemIdIndex, u1_MemRangeIndex );
                if( u1_RetChkMemAddrSec == (Std_ReturnType)E_OK )
                {
                    /* Check MemorySize */
                    u1_RetChkMemSize = Dcm_Dsp_SID2C_ChkMemSize( u4_MemSize );
                    if( u1_RetChkMemSize == (Std_ReturnType)E_OK )
                    {
                        /* Check Source Did Data Length */
                        u1_ChkSDidSize = Dcm_Dsp_DidMng_ChkSDidSize( u4_MemSize );
                        if( u1_ChkSDidSize == (Std_ReturnType)E_OK )
                        {
                            /* No process */
                        }
                        else
                        {
                            /* NRC 0x31 */
                            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
                            b_BreakFlag = (boolean)TRUE;
                        }
                    }
                    else
                    {
                        /* NRC 0x31 */
                        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
                        b_BreakFlag = (boolean)TRUE;
                    }
                }
                else
                {
                    /* NRC 0x33 */
                    Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_SECURITYACCESSDENIED );
                    b_BreakFlag = (boolean)TRUE;
                }
            }
            else
            {
                /* NRC 0x31 */
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
                b_BreakFlag = (boolean)TRUE;
            }
        }

        if( b_BreakFlag == (boolean)TRUE )
        {
            u1_RetVal = E_NOT_OK;
            break;
        }
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2C_ChkMemSize                                 */
/* Description   | Check MemorySize of request data                         */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u4MemSize  : Memory Size                            */
/*               | [IN] u1MemSizeByteNum  : Number of Memory Size Bytes     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK               : Check OK                          */
/*               |   E_NOT_OK           : Check NG                          */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_ChkMemSize
(
    const uint32 u4MemSize
)
{
    uint32            u4_MaxMemorySize;
    Std_ReturnType    u1_RetVal;

    u1_RetVal       = E_NOT_OK;


    u4_MaxMemorySize = Dcm_Dsp_MemMng_GetMaxReadMemorySize();
    if( u4MemSize <= u4_MaxMemorySize )
    {
        u1_RetVal = E_OK;
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2C_InitialProc_Sub03                          */
/* Description   | Initial process of SID 2C subfunction 03 request         */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext   : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_InitialProc_Sub03
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    Std_ReturnType                  u1_RetChkDDDID;
    Std_ReturnType                  u1_RetChkCondition;
    Std_ReturnType                  u1_RetClearAllDDDID;
    Std_ReturnType                  u1_RetClearDDDID;
    uint16                          u2_Did;
    uint32                          u4_ReqDataLen;
    boolean                         b_ReqSub03Flg;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );

    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;

    b_ReqSub03Flg = (boolean)FALSE;

    u4_ReqDataLen = Dcm_Dsp_Main_stMsgContext.reqDataLen;
    if( u4_ReqDataLen == DCM_DSP_SID2C_SF03_REQLEN_ALL )
    {
        u1_RetChkCondition = Dcm_Dsp_SID2C_ChkCondition( DCM_DSP_SID2C_SF_CLEAR );
        if( u1_RetChkCondition == (Std_ReturnType)E_OK )
        {
            /* Clear all DDDID setting */
            u1_RetClearAllDDDID = Dcm_Dsp_DidMng_ClearAllDDDID( DCM_DSP_DIDMNG_CLEAR_ALL_2CSF03 );

            if( u1_RetClearAllDDDID == (Std_ReturnType)E_OK )
            {
                /* Positive response */
                Dcm_Dsp_Main_stMsgContext.resDataLen = (uint32)0U;
                Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );

                /* flag for updating of PDID information table */
                b_ReqSub03Flg = (boolean)TRUE;
                /* INPUT for all clear */
                u2_Did = DCM_DSP_SID2C_DDDID_ALLCLR;
            }
        }
    }
    else if( u4_ReqDataLen == DCM_DSP_SID2C_SF03_REQLEN_DID )
    {

        u2_Did = (uint16)(((uint16)Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2C_REQDATA_DIDHIGH]) << DCM_DSP_SID2C_DID_SHIFT )
                        | ((uint16)Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2C_REQDATA_DIDLOW]);

        /* Check DDDID */
        u1_RetChkDDDID = Dcm_Dsp_SID2C_ChkDDDID_Sub03( u2_Did );
        if( u1_RetChkDDDID == (Std_ReturnType)E_OK )
        {
            u1_RetChkCondition = Dcm_Dsp_SID2C_ChkCondition( DCM_DSP_SID2C_SF_CLEAR );
            if( u1_RetChkCondition == (Std_ReturnType)E_OK )
            {
                /* Clear DDDID setting */
                u1_RetClearDDDID = Dcm_Dsp_DidMng_ClearDDDID( u2_Did );

                if( u1_RetClearDDDID == (Std_ReturnType)E_OK )
                {
                    /* Positive response */
                    Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID2C_RESDATA_DIDHIGH] = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2C_REQDATA_DIDHIGH];
                    Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID2C_RESDATA_DIDLOW ] = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID2C_REQDATA_DIDLOW ];
                    Dcm_Dsp_Main_stMsgContext.resDataLen = DCM_DSP_SID2C_RESLEN_DID;
                    Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );

                    /* flag for updating of PDID information table */
                    if( ( u2_Did & DCM_DSP_SID2C_MASKPDIDHI ) == DCM_DSP_SID2C_PDID_HIGHBYTE )
                    {
                        b_ReqSub03Flg = (boolean)TRUE;
                    }
                }
            }
        }
    }
    else
    {
        /* NRC 0x13 */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT );
    } 

    /* Update PDID infomation table */
    if( b_ReqSub03Flg == (boolean)TRUE )
    {
        Dcm_Dsp_SID2C_PDidInfoChkByDDDidClr( u2_Did );
    }

    return E_OK;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2C_ChkDDDID_Sub03                             */
/* Description   | Check DDDID of request data                              */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u2Did           : DDDID                             */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK               : Check OK                          */
/*               |   E_NOT_OK           : Check NG                          */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_ChkDDDID_Sub03
(
    const uint16 u2Did
)
{
    Std_ReturnType                  u1_RetVal;
    Std_ReturnType                  u1_RetChkSes;
    Std_ReturnType                  u1_RetChkSec;
    Std_ReturnType                  u1_RetSupportedDid;
    Dcm_Main_ReturnCheckType        u1_RetChkDid;
    uint8                           u1_CRWSupport;
    Dcm_SesCtrlType                 u1_SesCtrlType;
    Dcm_SecLevelType                u1_SecLevel;
    uint16                          u2_DidIndex;

    u1_RetVal = E_NOT_OK;

    /* Check DID support */
    u2_DidIndex   = (uint16)0U;
    u1_CRWSupport = (uint8)0U;
    u1_RetChkDid = Dcm_Dsp_DidMng_ChkDid( u2Did,
                                          DCM_DSP_DIDMNG_DID,
                                          &u2_DidIndex,
                                          &u1_CRWSupport );
    if( u1_RetChkDid == DCM_MAIN_E_CHECK_OK )
    {
        if( ( u1_CRWSupport & DCM_DSP_DIDMNG_READ_ONLY_DYN ) == DCM_DSP_DIDMNG_READ_ONLY_DYN )
        {
            u1_RetSupportedDid = Dcm_Dsp_DidMng_CheckSupportedDid( u2Did, DCM_DID_REQTYPE_DYNAMIC_DDDID, Dcm_Dsp_Main_stMsgContext.dcmRxPduId );
            if( u1_RetSupportedDid == (Std_ReturnType)E_OK )
            {

                /* Get active session */
                u1_SesCtrlType = DCM_DEFAULT_SESSION;
                ( void )Dcm_GetSesCtrlType( &u1_SesCtrlType ); /* no return check required */

                /* Check session support  */
                u1_RetChkSes = Dcm_Dsp_DidMng_ChkDidInfo( u2_DidIndex, DCM_DSP_DIDMNG_DID, DCM_DSP_DIDMNG_CHECK_READ_SES, u1_SesCtrlType );
                if( u1_RetChkSes == (Std_ReturnType)E_OK )
                {
                    /* Get active security level */
                    u1_SecLevel = DCM_SEC_LEV_LOCKED;
                    ( void )Dcm_GetSecurityLevel( &u1_SecLevel ); /* no return check required */

                    /* Check security level support */
                    u1_RetChkSec = Dcm_Dsp_DidMng_ChkDidInfo( u2_DidIndex, DCM_DSP_DIDMNG_DID, DCM_DSP_DIDMNG_CHECK_READ_SEC, u1_SecLevel );
                    if( u1_RetChkSec == (Std_ReturnType)E_OK )
                    {
                        u1_RetVal = E_OK;
                    }
                    else
                    {
                        /* NRC 0x33 */
                        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_SECURITYACCESSDENIED );
                    }
                }
                else
                {
                    /* NRC 0x31 */
                    Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
                }
            }
            else
            {
                /* NRC 0x31 */
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
            }
        }
        else
        {
            /* NRC 0x31 */
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
        }
    }
    else if( u1_RetChkDid == DCM_MAIN_E_CHECK_NOT_OK )
    {
        /* NRC 0x31 */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2C_ChkCondition                               */
/* Description   | Check processing of DynamicallyDefineDataIdentifie       */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1SubFunction  : Sub function                       */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Check OK                           */
/*               |   E_NOT_OK          : Check NG                           */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_NVM_DDDID_USE == STD_ON )
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_ChkCondition
(
    const uint8 u1SubFunction
)
{
    Std_ReturnType u1_RetVal;
    Std_ReturnType u1_RetChkCondition;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;
    boolean b_ReadStorageCompleteFlag;

    u1_RetVal = E_NOT_OK;
    u1_ErrorCode = (Dcm_NegativeResponseCodeType)0x00U;

    b_ReadStorageCompleteFlag = Dcm_Dsp_DidMng_GetReadStorageCompleteFlag();
    if( b_ReadStorageCompleteFlag == (boolean)TRUE )
    {
        u1_RetChkCondition = Dcm_Dsp_SID2C_CallChkDynDefDid( u1SubFunction, &u1_ErrorCode );

        if( u1_RetChkCondition == (Std_ReturnType)E_OK )
        {
            u1_RetVal = E_OK;
        }
        else if( u1_RetChkCondition == (Std_ReturnType)E_NOT_OK )
        {
            /* Negative response */
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_ErrorCode );
        }
        else
        {
            /* No process */
        }
    }
    else
    {
        /* Negative response (0x22) */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_CONDITIONSNOTCORRECT );
    }

    return u1_RetVal;
}
#endif /* DCM_NVM_DDDID_USE == STD_ON */
#if ( DCM_NVM_DDDID_USE == STD_OFF )
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_ChkCondition
(
    const uint8 u1SubFunction
)
{
    Std_ReturnType u1_RetVal;
    Std_ReturnType u1_RetChkCondition;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;

    u1_RetVal = E_NOT_OK;
    u1_ErrorCode = (Dcm_NegativeResponseCodeType)0x00U;

    u1_RetChkCondition = Dcm_Dsp_SID2C_CallChkDynDefDid( u1SubFunction, &u1_ErrorCode );

    if( u1_RetChkCondition == (Std_ReturnType)E_OK )
    {
        u1_RetVal = E_OK;
    }
    else if( u1_RetChkCondition == (Std_ReturnType)E_NOT_OK )
    {
        /* Negative response */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_ErrorCode );
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}
#endif /* DCM_NVM_DDDID_USE == STD_OFF */

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2C_CancelProc_Sub03                           */
/* Description   | Cancel process of SID 2C subfunction 03 request          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID2C_CancelProc_Sub03
( void )
{
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return E_OK;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID2C_PDidInfoChkByDDDidClr                      */
/* Description   | Process if DDDID table cleared                           */
/* Preconditions | None                                                     */
/* Parameters    | [in] u2ClrDDDid : Cleared DDDID                          */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_PERIODIC_DDDID_USE == STD_ON )
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SID2C_PDidInfoChkByDDDidClr
(
    const uint16 u2ClrDDDid
)
{
    if( u2ClrDDDid == DCM_DSP_SID2C_DDDID_ALLCLR )
    {
        Dcm_Dsp_SID2A_PDidInfoChkByDDDidClr( DCM_DSP_SID2A_DDDID_ALLCLR );
    }
    else
    {
        Dcm_Dsp_SID2A_PDidInfoChkByDDDidClr( u2ClrDDDid );
    }

    return;
}
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON */
#if ( DCM_PERIODIC_DDDID_USE == STD_OFF )
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SID2C_PDidInfoChkByDDDidClr
(
    const uint16 u2ClrDDDid                                /* MISRA DEVIATION */
)
{
    /* No process */

    return;
}
#endif /* DCM_PERIODIC_DDDID_USE == STD_OFF */


#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID2C == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-6-0         :2024-02-27                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

