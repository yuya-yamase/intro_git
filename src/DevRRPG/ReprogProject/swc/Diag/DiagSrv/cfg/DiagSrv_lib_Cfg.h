/* DiagSrv_lib_Cfg_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/lib/Cfg/HEADER                                      */
/******************************************************************************/
#ifndef DIAGSRV_LIB_CFG_H
#define DIAGSRV_LIB_CFG_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include "DiagSrv_Local.h"
#include "DiagSrv_lib_Core_Cfg.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_CFG_FINGERPRINT_SIZE                    ((uint16)24U)
#define DIAGSRV_CFG_SIGNATURE_SIZE                      ((uint16)384U)

#define DIAGSRV_CFG_RPRGDATA_SIZE                       ((uint16)512U)

#define DIAGSRV_CFG_RPRGDATA_FINGERPRINT_HEADER_SIZE    ((uint16)2U)    /* Length = 2byte */
#define DIAGSRV_CFG_RPRGDATA_SIGNATURE_HEADER_SIZE      ((uint16)2U)    /* Length = 2byte */

#define DIAGSRV_CFG_RPRGDATA_FINGERPRINTSIZE_POS        ((uint16)0U)
#define DIAGSRV_CFG_RPRGDATA_FINGERPRINT_POS            (DIAGSRV_CFG_RPRGDATA_FINGERPRINTSIZE_POS + DIAGSRV_CFG_RPRGDATA_FINGERPRINT_HEADER_SIZE)
#define DIAGSRV_CFG_RPRGDATA_SIGNATURESIZE_POS          (DIAGSRV_CFG_RPRGDATA_FINGERPRINT_POS + DIAGSRV_CFG_FINGERPRINT_SIZE)
#define DIAGSRV_CFG_RPRGDATA_SIGNATURE_POS              (DIAGSRV_CFG_RPRGDATA_SIGNATURESIZE_POS + DIAGSRV_CFG_RPRGDATA_SIGNATURE_HEADER_SIZE)

#define DIAGSRV_GET_RPRGDATA_FINGERPRINTSIZE_ADDR(addr) ((addr) + DIAGSRV_CFG_RPRGDATA_FINGERPRINTSIZE_POS)
#define DIAGSRV_GET_RPRGDATA_FINGERPRINTDATA_ADDR(addr) ((addr) + DIAGSRV_CFG_RPRGDATA_FINGERPRINT_POS)
#define DIAGSRV_GET_RPRGDATA_SIGNATURESIZE_ADDR(addr)   ((addr) + DIAGSRV_CFG_RPRGDATA_SIGNATURESIZE_POS)
#define DIAGSRV_GET_RPRGDATA_SIGNATUREDATA_ADDR(addr)   ((addr) + DIAGSRV_CFG_RPRGDATA_SIGNATURE_POS)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef struct {
    uint8 RewriteAreaNum;
    uint32 RprgDataAddr;
    uint16 RprgDataSize;
} DiagSrv_RprgDataAreaInfoConfigType;

typedef struct {
    P2CONST(DiagSrv_RprgDataAreaInfoConfigType, TYPEDEF, DIAGSRV_APPL_CONST) InfoPtr;
    uint8 RewriteInfoNum;
} DiagSrv_RprgDataAreaConfigType;

typedef struct {
    uint32 VersionAddr;
    uint32 TemporaryVersionAddr;
    uint8 VersionSize;
} DiagSrv_VersionInfoConfigType;


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_CST
#include <DiagSrv_MemMap.h>

extern CONST(DiagSrv_RprgDataAreaConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_RprgDataAreaConfig;
extern CONST(DiagSrv_VersionInfoConfigType, DIAGSRV_CONFIG_DATA) DiagSrv_VersionInfoConfig;
extern CONST(DiagSrv_RewriteAreaStatusType, DIAGSRV_CONFIG_DATA) DiagSrv_RewriteAreaStatus;

#define DIAGSRV_STOP_SEC_CST
#include <DiagSrv_MemMap.h>

#define DIAGSRV_START_SEC_CST_ENCRYPTION_FLAG
#include <DiagSrv_MemMap.h>

extern CONST(uint8, DIAGSRV_CONFIG_DATA) DiagSrv_EncryptionFlagConfig;

#define DIAGSRV_STOP_SEC_CST_ENCRYPTION_FLAG
#include <DiagSrv_MemMap.h>


#endif /* DIAGSRV_LIB_CFG_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/07/05 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

