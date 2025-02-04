/* DiagSrv_0x31_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/0x31/HEADER                                         */
/******************************************************************************/
#ifndef DIAGSRV_0X31_H
#define DIAGSRV_0X31_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <DiagCmn.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/* RID Code */
#define DIAGSRV_0X31_RID_ERASE                  ((uint16)0xFF00U)
#define DIAGSRV_0X31_RID_CHECK_SBL              ((uint16)0xDD00U)
#define DIAGSRV_0X31_RID_CHECK_APL              ((uint16)0xDD01U)
#define DIAGSRV_0X31_RID_VALIDATE               ((uint16)0xDD02U)

#define DIAGSRV_0X31_CHECKTYPE_SIG              ((uint8)0x01U)
#define DIAGSRV_0X31_CHECKTYPE_CRC              ((uint8)0x02U)

/* User Status */
#define DIAGSRV_0X31_USR_IDLE                   ((uint8)0x00U)
#define DIAGSRV_0X31_USR_BUSY                   ((uint8)0x01U)

/* User Job Result */
#define DIAGSRV_0X31_USR_JOB_OK                 ((uint8)0x00U)
#define DIAGSRV_0X31_USR_JOB_FAILED             ((uint8)0x01U)

/* User CheckValidate Result */
#define DIAGSRV_0X31_USR_VALID_OK               ((uint8)0U)
#define DIAGSRV_0X31_USR_VALID_NG               ((uint8)1U)
#define DIAGSRV_0X31_USR_ALREADY_VALID          ((uint8)2U)

/* Request Message Parameter Position */
/* common */
#define DIAGSRV_0X31_SID_POS                    ((uint8)0U)
#define DIAGSRV_0X31_SUBFUNC_POS                ((uint8)1U)
#define DIAGSRV_0X31_RID_H_POS                  ((uint8)2U)
#define DIAGSRV_0X31_RID_L_POS                  ((uint8)3U)
/* erase */
#define DIAGSRV_0X31_ERASE_ALFID_POS            ((uint8)4U)
#define DIAGSRV_0X31_ERASE_ADDR_POS             ((uint8)5U)
#define DIAGSRV_0X31_ERASE_SIZE_POS             ((uint8)9U)
/* check */
#define DIAGSRV_0X31_CHK_ID_POS                 ((uint8)4U)
#define DIAGSRV_0X31_CHK_DATALEN_POS            ((uint8)5U)
#define DIAGSRV_0X31_CHK_DATA_POS               ((uint8)7U)

/* Request Message Length */
#define DIAGSRV_0X31_CHK_MSG_MIN_LEN            ((uint16)7U)

/* Response Message Length */
#define DIAGSRV_0X31_RESPLEN_ERASE              ((uint16)5U)
#define DIAGSRV_0X31_RESPLEN_CHECK              ((uint16)7U)
#define DIAGSRV_0X31_RESPLEN_VALID              ((uint16)6U)

/* Response Message Parameter Position */
#define DIAGSRV_0X31_ROUTINEINFO_POS            ((uint8)4U)
#define DIAGSRV_0X31_CHECKSTATUS_POS            ((uint8)5U)
#define DIAGSRV_0X31_FAILEDCAUSE_POS            ((uint8)6U)
#define DIAGSRV_0X31_APLSTATUS_POS              ((uint8)5U)

/* routineInfo Parameter */
#define DIAGSRV_0X31_ROUTINEINFO_VALUE          ((uint8)0x02U)

/* checkStatus Parameter */
#define DIAGSRV_0X31_CHECKSTATUS_FAILED         ((uint8)0x01U)
#define DIAGSRV_0X31_CHECKSTATUS_SUCCESS        ((uint8)0x02U)

/* failedCause Parameter */
#define DIAGSRV_0X31_FAILEDCAUSE_NOFAILED       ((uint8)0x00U)
#define DIAGSRV_0X31_FAILEDCAUSE_GENERAL        ((uint8)0x01U)
#define DIAGSRV_0X31_FAILEDCAUSE_VERIFY_ERROR   ((uint8)0x02U)

/* applicationStatus Parameter */
#define DIAGSRV_0X31_APLSTATUS_NOT_PRESENT      ((uint8)0x01U)
#define DIAGSRV_0X31_APLSTATUS_PRESENT          ((uint8)0x02U)

#define DIAGSRV_0X31_VERSIONINFO_MAX_SIZE       ((uint8)255U)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef struct {
    uint8 CheckStatus;
    uint8 FailedCause;
} DiagSrv_0x31_CheckMemoryStatusType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
/* DiagSrv_0x31.c */
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Init (void);
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Time (void);
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Processing
(
    P2VAR(Diag_MsgContextType, AUTOMATIC, DIAGSRV_APPL_DATA) Msg
);
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Confirmation
(
    VAR(uint8, AUTOMATIC) Status
);
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_MsgCheckCondition (void);
FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_0x31_CheckVersionData
(
    CONST(uint8, AUTOMATIC) Version[],
    VAR(uint8, AUTOMATIC) VersionSize
);
/* DiagSrv_0x31_Erase.c */
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Erase_Init (void);
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Erase_Time (void);
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Erase_Processing (void);
/* DiagSrv_0x31_Check.c */
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_Init (void);
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_Time (void);
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_Processing (void);
/* DiagSrv_0x31_Validate.c */
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Valid_Init (void);
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Valid_Time (void);
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Valid_Processing (void);
/* DiagSrv_0x31_Usr.c */
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Usr_Init (void);
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Usr_Time (void);
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Usr_GetStatus (void);
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Usr_GetJobResult (void);
FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_0x31_Usr_ReqPreErase
(
    VAR(uint8, AUTOMATIC) RewriteAreaNum
);
FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_0x31_Usr_ReqPostCheckData
(
    VAR(uint8, AUTOMATIC) RewriteAreaNum,
    VAR(uint8, AUTOMATIC) CheckTypeIdentifier
);
FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_0x31_Usr_ReqCheckValidateApl
(
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) CheckResult
);
FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_0x31_Usr_ReqGetAplVersion
(
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) AplVer,
    VAR(uint8, AUTOMATIC) AplVerSize
);
FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_0x31_Usr_CompareAplVersion
(
    P2CONST(uint8, AUTOMATIC, DIAGSRV_APPL_CONST) OldAplVer,
    P2CONST(uint8, AUTOMATIC, DIAGSRV_APPL_CONST) NewAplVer,
    VAR(uint8, AUTOMATIC) AplVerSize
);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_VAR
#include <DiagSrv_MemMap.h>

extern P2VAR(Diag_MsgContextType, DIAGSRV_VAR_CLEARED, DIAGSRV_APPL_DATA) DiagSrv_0x31_Msg;
extern VAR(DiagSrv_0x31_CheckMemoryStatusType, DIAGSRV_VAR_CLEARED) DiagSrv_0x31_CheckMemoryStatus;
extern VAR(uint16, DIAGSRV_VAR_CLEARED) DiagSrv_0x31_Rid;
extern VAR(uint8, DIAGSRV_VAR_CLEARED) DiagSrv_0x31_ApplicationStatusValue;

#define DIAGSRV_STOP_SEC_VAR
#include <DiagSrv_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_CST
#include <DiagSrv_MemMap.h>


#define DIAGSRV_STOP_SEC_CST
#include <DiagSrv_MemMap.h>

#endif /* DIAGSRV_0X31_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2023/01/17 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

