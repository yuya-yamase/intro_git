/* DiagCmn_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Diag/Cmn/HEADER                                             */
/******************************************************************************/
#ifndef DIAGCMN_H
#define DIAGCMN_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Gdn.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define DIAG_TRUE               (TRUE)
#define DIAG_FALSE              (FALSE)

#define DIAG_NOT_SUPPORT        ((uint8)0x00U)
#define DIAG_SUPPORT            ((uint8)0x01U)

#define DIAG_ADDRESSING_FUNC    ((uint8)0x00U)
#define DIAG_ADDRESSING_PHYS    ((uint8)0x01U)

#define DIAG_INITIAL            ((uint8)0x00U)
#define DIAG_CANCEL             ((uint8)0x02U)

#define DIAG_POSRSP_OK          ((uint8)0x00U)
#define DIAG_POSRSP_NG          ((uint8)0x01U)
#define DIAG_NEGRSP_OK          ((uint8)0x02U)
#define DIAG_NEGRSP_NG          ((uint8)0x03U)

#define DIAG_COM_IDLE           ((uint8)0x00U)
#define DIAG_COM_BUSY           ((uint8)0x01U)

#define DIAG_PENDRSP_NO         ((uint8)0x00U)
#define DIAG_PENDRSP_SENT       ((uint8)0x01U)

#define DIAG_SESSION_DEF        ((uint8)0x01U)
#define DIAG_SESSION_PRG        ((uint8)0x02U)
#define DIAG_SESSION_EXT        ((uint8)0x03U)
#define DIAG_SESSION_OTH        ((uint8)0xFFU)

#define DIAG_CHGSESSION_FACT_INIT       ((uint8)0x00U)
#define DIAG_CHGSESSION_FACT_S3TIMEOUT  ((uint8)0x01U)
#define DIAG_CHGSESSION_FACT_SID10      ((uint8)0x02U)
#define DIAG_CHGSESSION_FACT_OTHER      ((uint8)0xFFU)

#define DIAG_SECURITY_LOCK      ((uint8)0x00U)
#define DIAG_SECURITY_UNLOCK    ((uint8)0x01U)

#define DIAG_TFMODE_NONE        ((uint8)0x00U)
#define DIAG_TFMODE_DL          ((uint8)0x01U)
#define DIAG_TFMODE_UL          ((uint8)0x02U)

#define DIAG_SID_DSC            ((uint8)0x10U)      /* DiagnosticSessionControl */
#define DIAG_SID_ER             ((uint8)0x11U)      /* ECUReset */
#define DIAG_SID_SA             ((uint8)0x27U)      /* SecurityAccess */
#define DIAG_SID_CC             ((uint8)0x28U)      /* CommunicationControl */
#define DIAG_SID_ARS            ((uint8)0x29U)      /* Authentication */
#define DIAG_SID_TP             ((uint8)0x3EU)      /* TesterPresent */
#define DIAG_SID_SDT            ((uint8)0x84U)      /* SecuredDataTransmission */
#define DIAG_SID_CDTCS          ((uint8)0x85U)      /* ControlDTCSetting */
#define DIAG_SID_ROE            ((uint8)0x86U)      /* ResponseOnEvent */
#define DIAG_SID_LC             ((uint8)0x87U)      /* LinkControl */
#define DIAG_SID_RDBI           ((uint8)0x22U)      /* ReadDataByIdentifier */
#define DIAG_SID_RMBA           ((uint8)0x23U)      /* ReadMemoryByAddress */
#define DIAG_SID_RSDBI          ((uint8)0x24U)      /* ReadScalingDataByIdentifier */
#define DIAG_SID_RDBPI          ((uint8)0x2AU)      /* ReadDataByPeriodicIdentifier */
#define DIAG_SID_DDDI           ((uint8)0x2CU)      /* DynamicallyDefineDataIdentifier */
#define DIAG_SID_WDBI           ((uint8)0x2EU)      /* WriteDataByIdentifier */
#define DIAG_SID_WMBA           ((uint8)0x3DU)      /* WriteMemoryByAddress */
#define DIAG_SID_CDTCI          ((uint8)0x14U)      /* ClearDiagnosticInformation */
#define DIAG_SID_RDTCI          ((uint8)0x19U)      /* ReadDTCInformation */
#define DIAG_SID_IOCBI          ((uint8)0x2FU)      /* InputOutputControlByIdentifier */
#define DIAG_SID_RC             ((uint8)0x31U)      /* RoutineControl */
#define DIAG_SID_RD             ((uint8)0x34U)      /* RequestDownload */
#define DIAG_SID_RU             ((uint8)0x35U)      /* RequestUpload */
#define DIAG_SID_TD             ((uint8)0x36U)      /* TransferData */
#define DIAG_SID_RTE            ((uint8)0x37U)      /* RequestTransferExit */
#define DIAG_SID_RFT            ((uint8)0x38U)      /* RequestFileTransfer */

#define DIAG_NRC_PR             ((uint8)0x00U)      /* positiveResponse */
#define DIAG_NRC_GR             ((uint8)0x10U)      /* generalReject */
#define DIAG_NRC_SNS            ((uint8)0x11U)      /* serviceNotSupported */
#define DIAG_NRC_SFNS           ((uint8)0x12U)      /* sub-functionNotSupported */
#define DIAG_NRC_IMLOIF         ((uint8)0x13U)      /* incorrectMessageLengthOrInvalidFormat */
#define DIAG_NRC_RTL            ((uint8)0x14U)      /* responseTooLong */
#define DIAG_NRC_BRR            ((uint8)0x21U)      /* busyRepeatRequest */
#define DIAG_NRC_CNC            ((uint8)0x22U)      /* conditionsNotCorrect */
#define DIAG_NRC_RSE            ((uint8)0x24U)      /* requestSequenceError */
#define DIAG_NRC_NRFSC          ((uint8)0x25U)      /* noResponseFromSubnetComponent */
#define DIAG_NRC_FPEORA         ((uint8)0x26U)      /* FailurePreventsExecutionOfRequestedAction */
#define DIAG_NRC_ROOR           ((uint8)0x31U)      /* requestOutOfRange */
#define DIAG_NRC_SAD            ((uint8)0x33U)      /* securityAccessDenied */
#define DIAG_NRC_AR             ((uint8)0x34U)      /* authenticationRequired */
#define DIAG_NRC_IK             ((uint8)0x35U)      /* invalidKey */
#define DIAG_NRC_ENOA           ((uint8)0x36U)      /* exceedNumberOfAttempts */
#define DIAG_NRC_RTDNE          ((uint8)0x37U)      /* requiredTimeDelayNotExpired */
#define DIAG_NRC_SDTR           ((uint8)0x38U)      /* secureDataTransmissionRequired */
#define DIAG_NRC_SDTNA          ((uint8)0x39U)      /* secureDataTransmissionNotAllowed */
#define DIAG_NRC_SDTF           ((uint8)0x3AU)      /* secureDataVerificationFailed */
#define DIAG_NRC_CVFITP         ((uint8)0x50U)      /* Certificate verification failed - Invalid Time Period */
#define DIAG_NRC_CVFISIG        ((uint8)0x51U)      /* Certificate verification failed - Invalid Signature */
#define DIAG_NRC_CVFICOT        ((uint8)0x52U)      /* Certificate verification failed - Invalid Chain of Trust */
#define DIAG_NRC_CVFIT          ((uint8)0x53U)      /* Certificate verification failed - Invalid Type */
#define DIAG_NRC_CVFIF          ((uint8)0x54U)      /* Certificate verification failed - Invalid Format */
#define DIAG_NRC_CVFIC          ((uint8)0x55U)      /* Certificate verification failed - Invalid Content */
#define DIAG_NRC_CVFIS          ((uint8)0x56U)      /* Certificate verification failed - Invalid Scope */
#define DIAG_NRC_CVFICR         ((uint8)0x57U)      /* Certificate verification failed - Invalid Certificate(revoked) */
#define DIAG_NRC_OVF            ((uint8)0x58U)      /* Ownership verification failed */
#define DIAG_NRC_CCF            ((uint8)0x59U)      /* Challenge calculation failed */
#define DIAG_NRC_SARF           ((uint8)0x5AU)      /* Setting Access Rights failed */
#define DIAG_NRC_SKCDF          ((uint8)0x5BU)      /* Session key creation/derivation failed */
#define DIAG_NRC_CDUF           ((uint8)0x5CU)      /* Configuration data usage failed */
#define DIAG_NRC_DAF            ((uint8)0x5DU)      /* DeAuthentication failed */
#define DIAG_NRC_UDNA           ((uint8)0x70U)      /* uploadDownloadNotAccepted */
#define DIAG_NRC_TDS            ((uint8)0x71U)      /* transferDataSuspended */
#define DIAG_NRC_GPF            ((uint8)0x72U)      /* generalProgrammingFailure */
#define DIAG_NRC_WBSC           ((uint8)0x73U)      /* wrongBlockSequenceCounter */
#define DIAG_NRC_RCRRP          ((uint8)0x78U)      /* requestCorrectlyReceived-ResponsePending */
#define DIAG_NRC_SFNSIAS        ((uint8)0x7EU)      /* sub-functionNotSupportedInActiveSession */
#define DIAG_NRC_SNSIAS         ((uint8)0x7FU)      /* serviceNotSupportedInActiveSession */
#define DIAG_NRC_RPMTH          ((uint8)0x81U)      /* rpmTooHigh */
#define DIAG_NRC_RPMTL          ((uint8)0x82U)      /* rpmTooLow */
#define DIAG_NRC_EIR            ((uint8)0x83U)      /* engineIsRunning */
#define DIAG_NRC_EINR           ((uint8)0x84U)      /* engineIsNotRunning */
#define DIAG_NRC_ERTTL          ((uint8)0x85U)      /* engineRunTimeTooLow */
#define DIAG_NRC_TEMPTH         ((uint8)0x86U)      /* temperatureTooHigh */
#define DIAG_NRC_TEMPTL         ((uint8)0x87U)      /* temperatureTooLow */
#define DIAG_NRC_VSTH           ((uint8)0x88U)      /* vehicleSpeedTooHigh */
#define DIAG_NRC_VSTL           ((uint8)0x89U)      /* vehicleSpeedTooLow */
#define DIAG_NRC_TPTH           ((uint8)0x8AU)      /* throttle/PedalTooHigh */
#define DIAG_NRC_TPTL           ((uint8)0x8BU)      /* throttle/PedalTooLow */
#define DIAG_NRC_TRNIN          ((uint8)0x8CU)      /* transmissionRangeNotInNeutral */
#define DIAG_NRC_TRNIG          ((uint8)0x8DU)      /* transmissionRangeNotInGear */
#define DIAG_NRC_BSNC           ((uint8)0x8FU)      /* brakeSwitch(es)NotClosed */
#define DIAG_NRC_SLNIP          ((uint8)0x90U)      /* shifterLeverNotInPark */
#define DIAG_NRC_TCCL           ((uint8)0x91U)      /* torqueConverterClutchLocked */
#define DIAG_NRC_VTH            ((uint8)0x92U)      /* voltageTooHigh */
#define DIAG_NRC_VTL            ((uint8)0x93U)      /* voltageTooLow */
#define DIAG_NRC_RTNA           ((uint8)0x94U)      /* ResourceTemporarilyNotAvailable */

#define DIAG_SUBFUNCMSG_MIN_SIZE    ((uint16)2U)
#define DIAG_DIDMSG_MIN_SIZE        ((uint16)3U)
#define DIAG_RIDMSG_MIN_SIZE        ((uint16)4U)

#define DIAG_GET_SID(msg)           ((msg)->ReqData[0])
#define DIAG_GET_SUBFUNCTION(msg)   (((msg)->ReqData[1]) & (uint8)~0x80U)
#define DIAG_CHECK_SPRMIB(msg)      (((((msg)->ReqData[1]) & (uint8)0x80U) == (uint8)0x80U) ? DIAG_TRUE : DIAG_FALSE)
#define DIAG_MAKE_POSRSP_SID(msg)   (((msg)->ReqData[0]) + (uint8)0x40U)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef Gdn_Dcm_MsgContextType Diag_MsgContextType;
/* Diag_MsgContextType is the same as.                */
/* typedef struct {                                   */
/*     P2VAR(uint8, TYPEDEF, DIAG_APPL_DATA) ReqData; */
/*     uint16 ReqDataLen;                             */
/*     P2VAR(uint8, TYPEDEF, DIAG_APPL_DATA) ResData; */
/*     uint16 ResDataLen;                             */
/*     uint8 ReqType;                                 */
/*     boolean SuppressResponse;                      */
/*     uint16 ResMaxDataLen;                          */
/* } Diag_MsgContextType;                             */

typedef struct {
    uint8 SupportDef;
    uint8 SupportPrg;
    uint8 SupportExt;
} Diag_SessionSupportType;

typedef struct {
    uint8 SupportLock;
} Diag_SecuritySupportType;

typedef Diag_SessionSupportType     Diag_SubfuncSessionSupportType;
typedef Diag_SecuritySupportType    Diag_SubfuncSecuritySupportType;

typedef struct {
    uint8 Subfunc;
    uint16 Length; /* Length excluding SID and Subfunction. */
    Diag_SubfuncSessionSupportType Session;
    Diag_SubfuncSecuritySupportType Security;
} Diag_SubfuncInfoConfigType;

typedef struct {
    P2CONST(Diag_SubfuncInfoConfigType, TYPEDEF, DIAG_APPL_CONST) InfoPtr;
    uint8 SubfuncNum;
} Diag_SubfuncConfigType;

typedef Diag_SessionSupportType     Diag_DidSessionSupportType;
typedef Diag_SecuritySupportType    Diag_DidSecuritySupportType;

typedef struct {
    uint16 Did;
    uint16 Length; /* Length excluding SID and DID. */
    Diag_DidSessionSupportType Session;
    Diag_DidSecuritySupportType Security;
} Diag_DidInfoConfigType;

typedef struct {
    P2CONST(Diag_DidInfoConfigType, TYPEDEF, DIAG_APPL_CONST) InfoPtr;
    uint8 DidNum;
} Diag_DidConfigType;

typedef Diag_SessionSupportType     Diag_RidSessionSupportType;
typedef Diag_SecuritySupportType    Diag_RidSecuritySupportType;

typedef struct {
    uint16 Rid;
    uint16 Length; /* Length excluding SID, Subfunction, and RID. */
    uint8 Subfunc;
    Diag_RidSessionSupportType Session;
    Diag_RidSecuritySupportType Security;
} Diag_RidInfoConfigType;

typedef struct {
    P2CONST(Diag_RidInfoConfigType, TYPEDEF, DIAG_APPL_CONST) InfoPtr;
    uint8 RidNum;
} Diag_RidConfigType;


#endif /* DIAGCMN_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2021/09/14 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

