/* DiagSrv_Local_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/Local/HEADER                                        */
/******************************************************************************/
#ifndef DIAGSRV_LOCAL_H
#define DIAGSRV_LOCAL_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Rte.h>

#include "DiagSrv_lib_Core.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_REWRITESTAT_IDLE                ((uint8)0U)
#define DIAGSRV_REWRITESTAT_FINGER_RECV         ((uint8)2U)
#define DIAGSRV_REWRITESTAT_READY               ((uint8)3U)
#define DIAGSRV_REWRITESTAT_SBL_DL_START        ((uint8)4U)
#define DIAGSRV_REWRITESTAT_SBL_DL_UPDATE       ((uint8)5U)
#define DIAGSRV_REWRITESTAT_SBL_DL_END          ((uint8)6U)
#define DIAGSRV_REWRITESTAT_SBL_DL_COMPLETE     ((uint8)7U)
#define DIAGSRV_REWRITESTAT_SBL_DL_CHECK        ((uint8)8U)
#define DIAGSRV_REWRITESTAT_ERASE               ((uint8)9U)
#define DIAGSRV_REWRITESTAT_DATA_DL_START       ((uint8)10U)
#define DIAGSRV_REWRITESTAT_DATA_DL_UPDATE      ((uint8)11U)
#define DIAGSRV_REWRITESTAT_DATA_DL_END         ((uint8)12U)
#define DIAGSRV_REWRITESTAT_DATA_DL_COMPLETE    ((uint8)13U)
#define DIAGSRV_REWRITESTAT_DATA_CHECK          ((uint8)14U)
#define DIAGSRV_REWRITESTAT_VALIDATE            ((uint8)15U)

#define DIAGSRV_NONCE_BUFF_SIZE                 (16U)

#define DIAGSRV_LBSTAT_BEFORE_REWRITING         ((uint8)0U)
#define DIAGSRV_LBSTAT_IN_REWRITING             ((uint8)1U)
#define DIAGSRV_LBSTAT_REWRITING_OK             ((uint8)2U)
#define DIAGSRV_LBSTAT_REWRITING_NG             ((uint8)3U)

#define DIAGSRV_EXT_BOOT_MODE_BOOT              ((uint8)0U)
#define DIAGSRV_EXT_BOOT_MODE_APL               ((uint8)1U)
#define DIAGSRV_EXT_BOOT_MODE_UNMATCH           ((uint8)2U)
#define DIAGSRV_EXT_BOOT_MODE_STAYINBOOT        ((uint8)3U)

#define DIAGSRV_DEVICE_TYPE_CODEFLS             (RTE_MEMM_DEVICE_TYPE_CODEFLS)
#define DIAGSRV_DEVICE_TYPE_EXTCODEFLS          (RTE_MEMM_DEVICE_TYPE_EXTCODEFLS)
#define DIAGSRV_DEVICE_TYPE_CODERAM             (RTE_MEMM_DEVICE_TYPE_CODERAM)

#define DIAGSRV_ENCRYPTIONFLAG_ON               ((uint8)0x00U)
#define DIAGSRV_ENCRYPTIONFLAG_OFF              ((uint8)0xFFU)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef struct {
    uint8 ExtendedBootMode;
} DiagSrv_RewriteAreaBootInfoType;

typedef struct {
    uint8 RewriteAreaNum;
    uint8 Status;
} DiagSrv_RewriteAreaStatusInfoType;

typedef struct {
    P2VAR(DiagSrv_RewriteAreaBootInfoType, TYPEDEF, DIAGSRV_APPL_DATA) BootInfoPtr;
    P2VAR(DiagSrv_RewriteAreaStatusInfoType, TYPEDEF, DIAGSRV_APPL_DATA) StatusInfoPtr;
    uint8 StatusInfoNum;
} DiagSrv_RewriteAreaStatusType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_lib_Init
(
    VAR(uint8, AUTOMATIC) BootModeEx
);
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_GetRewriteStatus (void);
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_SetRewriteStatus
(
    VAR(uint8, AUTOMATIC) Status
);
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_GetCipherTextMode (void);
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_SetCipherTextMode
(
    VAR(uint8, AUTOMATIC) Flag
);
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_GetCompressionMode (void);
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_SetCompressionMode
(
    VAR(uint8, AUTOMATIC) Flag
);
FUNC_P2VAR(uint8, DIAGSRV_APPL_DATA, DIAGSRV_CODE_FAST) DiagSrv_GetNonceTempArea (void);
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_SetNonceTempArea
(
    P2CONST(uint8, AUTOMATIC, DIAGSRV_APPL_CONST) Nonce
);
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_ClearNonceTempArea (void);
FUNC_P2VAR(uint8, DIAGSRV_APPL_DATA, DIAGSRV_CODE_FAST) DiagSrv_GetFingerprintTempArea (void);
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_SetFingerprintTempArea
(
    P2CONST(uint8, AUTOMATIC, DIAGSRV_APPL_CONST) Fingerprint
);
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_ClearFingerprintTempArea (void);
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_GetRprgDataAreaInfo
(
    VAR(uint8, AUTOMATIC) RewriteAreaNum,
    P2VAR(uint32, AUTOMATIC, DIAGSRV_APPL_DATA) DataAddr,
    P2VAR(uint32, AUTOMATIC, DIAGSRV_APPL_DATA) DataSize
);
FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_GetEraseAreaInfo
(
    VAR(uint8, AUTOMATIC) RewriteAreaNum,
    P2VAR(uint32, AUTOMATIC, DIAGSRV_APPL_DATA) EraseAddr,
    P2VAR(uint32, AUTOMATIC, DIAGSRV_APPL_DATA) EraseSize
);
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_GetVersionAreaInfo
(
    P2VAR(uint32, AUTOMATIC, DIAGSRV_APPL_DATA) VerAddr,
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) VerSize
);
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_GetTempVersionAreaInfo
(
    P2VAR(uint32, AUTOMATIC, DIAGSRV_APPL_DATA) TempVerAddr,
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) TempVerSize
);
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_SetRewriteAreaStatus
(
    VAR(uint8, AUTOMATIC) RewriteAreaNum,
    VAR(uint8, AUTOMATIC) Status
);
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_GetRewriteAreaStatus
(
    VAR(uint8, AUTOMATIC) RewriteAreaNum
);
FUNC_P2CONST(DiagSrv_RewriteAreaStatusType, DIAGSRV_APPL_CONST, DIAGSRV_CODE_FAST) DiagSrv_GetRewriteAreaStatusInfo (void);
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_SetWriteDeviceType
(
    VAR(uint8, AUTOMATIC) DeviceType
);
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_GetWriteDeviceType (void);
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_GetEncryptionFlag (void);
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_EnableChangePrgSession (void);
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_DisableChangePrgSession (void);
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_CheckChangePrgSession (void);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_VAR
#include <DiagSrv_MemMap.h>

#define DIAGSRV_STOP_SEC_VAR
#include <DiagSrv_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_CST
#include <DiagSrv_MemMap.h>

#define DIAGSRV_STOP_SEC_CST
#include <DiagSrv_MemMap.h>


#endif /* DIAGSRV_LOCAL_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/07/05 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

