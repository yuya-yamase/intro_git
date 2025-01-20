/* WrapCrypto_Local_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | WrapCrypto/Local/HEADER                                     */
/******************************************************************************/
#ifndef WRAPCRYPTO_LOCAL_H
#define WRAPCRYPTO_LOCAL_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/*===== Sample ===============================================================*/
#define WRAPCRYPTO_USE_CRYPTO_SW_83_ENCRYPT     (STD_ON)
#define WRAPCRYPTO_USE_CRYPTO_SW_83_DECRYPT     (STD_ON)
#define WRAPCRYPTO_USE_CRYPTO_SW_83_SIGVERIFY   (STD_ON)

#if ((WRAPCRYPTO_USE_CRYPTO_SW_83_ENCRYPT == STD_ON) || \
    (WRAPCRYPTO_USE_CRYPTO_SW_83_DECRYPT == STD_ON) ||  \
    (WRAPCRYPTO_USE_CRYPTO_SW_83_SIGVERIFY == STD_ON))
  #define WRAPCRYPTO_USE_CRYPTO_SW_83           (STD_ON)
#else
  #define WRAPCRYPTO_USE_CRYPTO_SW_83           (STD_OFF)
#endif

#define WRAPCRYPTO_JOB_OK                       ((uint8)0x00U)
#define WRAPCRYPTO_JOB_FAILED                   ((uint8)0x01U)
#define WRAPCRYPTO_JOB_PENDING                  ((uint8)0x02U)
#define WRAPCRYPTO_JOB_VERIFYERR                ((uint8)0x03U)

#define WRAPCRYPTO_STAT_IDLE                    ((uint8)0x00U)
#define WRAPCRYPTO_STAT_ENCRYPT                 ((uint8)0x11U)
#define WRAPCRYPTO_STAT_PRE_DECRYPT             ((uint8)0x21U)
#define WRAPCRYPTO_STAT_DECRYPT                 ((uint8)0x22U)
#define WRAPCRYPTO_STAT_FIN_DECRYPT             ((uint8)0x23U)
#define WRAPCRYPTO_STAT_PRE_SIGVERIFY           ((uint8)0x31U)
#define WRAPCRYPTO_STAT_SIGVERIFY               ((uint8)0x32U)
#define WRAPCRYPTO_STAT_FIN_SIGVERIFY           ((uint8)0x33U)
#define WRAPCRYPTO_STAT_RESULT                  ((uint8)0xFFU)
/*===== Sample ===============================================================*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
/*===== Sample ===============================================================*/
typedef struct {
    uint8 Result;
    uint8 Status;
} WrapCrypto_JobInfoType;
/*===== Sample ===============================================================*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
/*===== Sample ===============================================================*/
FUNC(void, WRAPCRYPTO_CODE_FAST) WrapCrypto_UpdateJobInfo
(
    P2CONST(WrapCrypto_JobInfoType, AUTOMATIC, WRAPCRYPTO_APPL_CONST) JobInfo
);
FUNC(void, WRAPCRYPTO_CODE_FAST) WrapCrypto_GetJobInfo
(
    P2VAR(WrapCrypto_JobInfoType, AUTOMATIC, WRAPCRYPTO_APPL_DATA) JobInfo
);
/*===== Sample ===============================================================*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define WRAPCRYPTO_START_SEC_VAR
#include <WrapCrypto_MemMap.h>

#define WRAPCRYPTO_STOP_SEC_VAR
#include <WrapCrypto_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define WRAPCRYPTO_START_SEC_CST
#include <WrapCrypto_MemMap.h>

#define WRAPCRYPTO_STOP_SEC_CST
#include <WrapCrypto_MemMap.h>


#endif /* WRAPCRYPTO_LOCAL_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/10/04 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

