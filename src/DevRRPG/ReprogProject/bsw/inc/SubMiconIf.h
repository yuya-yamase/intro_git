/* SubMiconIf_h_Revision(v3.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | SubMiconIf/HEADER                                           */
/******************************************************************************/
#ifndef SUBMICONIF_H
#define SUBMICONIF_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <ComStack_Types.h>
#include <BswM.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define SUBMICONIF_E_PENDING                ((Std_ReturnType)0x02U)

#define SUBMICONIF_INITIAL                  ((SubMiconIf_OpStatusType)0x00U)
#define SUBMICONIF_PENDING                  ((SubMiconIf_OpStatusType)0x01U)

/* UserType */
#define SUBMICONIF_USER_BSWM_SESSION        ((uint16)BSWM_USER_SUBMICONIF_SESSION)
#define SUBMICONIF_USER_BSWM_SECURITY       ((uint16)BSWM_USER_SUBMICONIF_SECURITY)
#define SUBMICONIF_USER_BSWM_ECU_RESET      ((uint16)BSWM_USER_SUBMICONIF_ECU_RESET)
#define SUBMICONIF_USER_BSWM_MAIN_ERR       ((uint16)BSWM_USER_SUBMICONIF_MAIN_ERR)
#define SUBMICONIF_USER_BSWM_USR_RESET      ((uint16)BSWM_USER_SUBMICONIF_USR_RESET)
#define SUBMICONIF_USER_BSWM_USR_SLEEP      ((uint16)BSWM_USER_SUBMICONIF_USR_SLEEP)
#define SUBMICONIF_USER_BSWM_ACC            ((uint16)BSWM_USER_SUBMICONIF_ACC)
#define SUBMICONIF_USER_BSWM_IG             ((uint16)BSWM_USER_SUBMICONIF_IG)

/* ModeType */
#define SUBMICONIF_MODE_SESSION_DEF         ((uint16)BSWM_MODE_SESSION_DEF)
#define SUBMICONIF_MODE_SESSION_EXT         ((uint16)BSWM_MODE_SESSION_EXT)
#define SUBMICONIF_MODE_SESSION_PRG         ((uint16)BSWM_MODE_SESSION_PRG)

#define SUBMICONIF_MODE_SECURITY_LOCK       ((uint16)BSWM_MODE_SECURITY_LOCK)
#define SUBMICONIF_MODE_SECURITY_UNLOCK_LV1 ((uint16)BSWM_MODE_SECURITY_UNLOCK_LV1)
#define SUBMICONIF_MODE_SECURITY_UNLOCK_LV2 ((uint16)BSWM_MODE_SECURITY_UNLOCK_LV2)
#define SUBMICONIF_MODE_SECURITY_UNLOCK_LV3 ((uint16)BSWM_MODE_SECURITY_UNLOCK_LV3)
#define SUBMICONIF_MODE_SECURITY_UNLOCK_LV4 ((uint16)BSWM_MODE_SECURITY_UNLOCK_LV4)
#define SUBMICONIF_MODE_SECURITY_UNLOCK_LV5 ((uint16)BSWM_MODE_SECURITY_UNLOCK_LV5)
#define SUBMICONIF_MODE_SECURITY_UNLOCK_LV6 ((uint16)BSWM_MODE_SECURITY_UNLOCK_LV6)
#define SUBMICONIF_MODE_SECURITY_UNLOCK_LV7 ((uint16)BSWM_MODE_SECURITY_UNLOCK_LV7)
#define SUBMICONIF_MODE_SECURITY_UNLOCK_LV8 ((uint16)BSWM_MODE_SECURITY_UNLOCK_LV8)

#define SUBMICONIF_MODE_ECU_RESET_EXECUTE   ((uint16)BSWM_MODE_ECU_RESET_EXECUTE)

#define SUBMICONIF_MODE_MAIN_ERR_OCCUR      ((uint16)BSWM_MODE_MAIN_ERR_OCCUR)

#define SUBMICONIF_MODE_USR_RESET_EXECUTE   ((uint16)BSWM_MODE_USR_RESET_EXECUTE)

#define SUBMICONIF_MODE_USR_SLEEP_EXECUTE   ((uint16)BSWM_MODE_USR_SLEEP_EXECUTE)

#define SUBMICONIF_MODE_ACC_OFF             ((uint16)BSWM_MODE_ACC_OFF)
#define SUBMICONIF_MODE_ACC_ON              ((uint16)BSWM_MODE_ACC_ON)

#define SUBMICONIF_MODE_IG_OFF              ((uint16)BSWM_MODE_IG_OFF)
#define SUBMICONIF_MODE_IG_ON               ((uint16)BSWM_MODE_IG_ON)

/* Microcontroller identifier */
#define SUBMICONIF_ID_MAIN                  ((uint8)0U)
#define SUBMICONIF_ID_SUB_1                 ((uint8)1U)
#define SUBMICONIF_ID_SUB_2                 ((uint8)2U)
#define SUBMICONIF_ID_SUB_3                 ((uint8)3U)
#define SUBMICONIF_ID_SUB_4                 ((uint8)4U)
#define SUBMICONIF_ID_SUB_5                 ((uint8)5U)
#define SUBMICONIF_ID_SUB_6                 ((uint8)6U)
#define SUBMICONIF_ID_SUB_7                 ((uint8)7U)
#define SUBMICONIF_ID_SUB_8                 ((uint8)8U)
#define SUBMICONIF_ID_SUB_9                 ((uint8)9U)
#define SUBMICONIF_ID_SUB_10                ((uint8)10U)
#define SUBMICONIF_ID_SUB_11                ((uint8)11U)
#define SUBMICONIF_ID_SUB_12                ((uint8)12U)
#define SUBMICONIF_ID_SUB_13                ((uint8)13U)
#define SUBMICONIF_ID_SUB_14                ((uint8)14U)
#define SUBMICONIF_ID_SUB_15                ((uint8)15U)
#define SUBMICONIF_ID_SUB_16                ((uint8)16U)
#define SUBMICONIF_ID_SUB_17                ((uint8)17U)
#define SUBMICONIF_ID_SUB_18                ((uint8)18U)
#define SUBMICONIF_ID_SUB_19                ((uint8)19U)
#define SUBMICONIF_ID_SUB_20                ((uint8)20U)
#define SUBMICONIF_ID_SUB_21                ((uint8)21U)
#define SUBMICONIF_ID_SUB_22                ((uint8)22U)
#define SUBMICONIF_ID_SUB_23                ((uint8)23U)
#define SUBMICONIF_ID_SUB_24                ((uint8)24U)
#define SUBMICONIF_ID_SUB_25                ((uint8)25U)
#define SUBMICONIF_ID_SUB_26                ((uint8)26U)
#define SUBMICONIF_ID_SUB_27                ((uint8)27U)
#define SUBMICONIF_ID_SUB_28                ((uint8)28U)
#define SUBMICONIF_ID_SUB_29                ((uint8)29U)
#define SUBMICONIF_ID_SUB_30                ((uint8)30U)
#define SUBMICONIF_ID_SUB_31                ((uint8)31U)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef uint8   SubMiconIf_OpStatusType;

typedef struct {
    P2CONST(uint8, TYPEDEF, SUBMICONIF_APPL_CONST) ReqData;
    uint16  ReqDataSize;
} SubMiconIf_ReqInfoType;

typedef struct {
    P2VAR(uint8, TYPEDEF, SUBMICONIF_APPL_DATA) RespData;
    uint16  RespDataSize;
} SubMiconIf_RespInfoType;

typedef struct {
    P2VAR(uint8, TYPEDEF, SUBMICONIF_APPL_DATA) UserData;
    uint16  UserDataSize;
} SubMiconIf_UserDataInfoType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
#if (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON)
 /* SubMicon(Main) */
 FUNC(void, SUBMICONIF_CODE_SLOW) SubMiconIf_Init (void);
 FUNC(void, SUBMICONIF_CODE_SLOW) SubMiconIf_DeInit (void);
 FUNC(void, SUBMICONIF_CODE_SLOW) SubMiconIf_MainFunction (void);
 FUNC(void, SUBMICONIF_CODE_SLOW) SubMiconIf_Time (void);
 FUNC(Std_ReturnType, SUBMICONIF_CODE_SLOW) SubMiconIf_UserDataTransmit
 (
     VAR(uint8, AUTOMATIC) MiconId,
     P2CONST(SubMiconIf_UserDataInfoType, AUTOMATIC, SUBMICONIF_APPL_CONST) UserDataInfo
 );
 FUNC(Std_ReturnType, SUBMICONIF_CODE_SLOW) SubMiconIf_Main_RequestService
 (
     VAR(uint8, AUTOMATIC) MiconId,
     P2CONST(SubMiconIf_ReqInfoType, AUTOMATIC, SUBMICONIF_APPL_CONST) ReqInfo,
     P2VAR(SubMiconIf_RespInfoType, AUTOMATIC, SUBMICONIF_APPL_DATA) RespInfo,
     VAR(SubMiconIf_OpStatusType, AUTOMATIC) OpStatus
 );
 FUNC(void, SUBMICONIF_CODE_SLOW) SubMiconIf_Main_NotifyEvent
 (
     VAR(uint16, AUTOMATIC) User,
     VAR(uint16, AUTOMATIC) Mode
 );
 #define SubMiconIf_Sub_Transmit(Id, TxInfoPtr)     (E_NOT_OK)

#elif (REPROG_CFG_SUBMICON_USE_SUB == STD_ON)
 /* SubMicon(Sub) */
 FUNC(void, SUBMICONIF_CODE_SLOW) SubMiconIf_Init (void);
 FUNC(void, SUBMICONIF_CODE_SLOW) SubMiconIf_DeInit (void);
 FUNC(void, SUBMICONIF_CODE_SLOW) SubMiconIf_MainFunction (void);
 FUNC(void, SUBMICONIF_CODE_SLOW) SubMiconIf_Time (void);
 FUNC(Std_ReturnType, SUBMICONIF_CODE_SLOW) SubMiconIf_UserDataTransmit
 (
     VAR(uint8, AUTOMATIC) MiconId,
     P2CONST(SubMiconIf_UserDataInfoType, AUTOMATIC, SUBMICONIF_APPL_CONST) UserDataInfo
 );
 #define SubMiconIf_Main_RequestService(MiconId, ReqInfo, RespInfo, OpStatus)    (E_NOT_OK)
 #define SubMiconIf_Main_NotifyEvent(User, Mode)    do{ }while( 0 )
 FUNC(Std_ReturnType, SUBMICONIF_CODE_SLOW) SubMiconIf_Sub_Transmit
 (
     VAR(PduIdType, AUTOMATIC) Id,
     P2CONST(PduInfoType, AUTOMATIC, SUBMICONIF_APPL_CONST) TxInfoPtr
 );

#else
 /* Not SubMicon */
 #define SubMiconIf_Init()                          do{ }while( 0 )
 #define SubMiconIf_DeInit()                        do{ }while( 0 )
 #define SubMiconIf_MainFunction()                  do{ }while( 0 )
 #define SubMiconIf_Time()                          do{ }while( 0 )
 #define SubMiconIf_UserDataTransmit(MiconIf, UserDataInfo)    (E_NOT_OK)
 #define SubMiconIf_Main_RequestService(MiconId, ReqInfo, RespInfo, OpStatus)    (E_NOT_OK)
 #define SubMiconIf_Main_NotifyEvent(User, Mode)    do{ }while( 0 )
 #define SubMiconIf_Sub_Transmit(Id, TxInfoPtr)     (E_NOT_OK)

#endif


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/


#endif /* SUBMICONIF_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2019/12/03 :Update                                rel.AUBASS */
/*  v3.00       :2021/09/14 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

