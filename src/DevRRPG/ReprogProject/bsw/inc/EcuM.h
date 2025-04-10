/* EcuM_h_Revision(v4.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | EcuM/HEADER                                                 */
/******************************************************************************/
#ifndef ECUM_H
#define ECUM_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/* Module ID */
/* MCAL */
#define ECUM_MODULE_CODEFLS         (0x0000U)
#define ECUM_MODULE_CAN             (0x0001U)
#define ECUM_MODULE_GPT             (0x0002U)
#define ECUM_MODULE_MCU             (0x0003U)
#define ECUM_MODULE_PORT            (0x0004U)
#define ECUM_MODULE_DIO             (0x0005U)
#define ECUM_MODULE_WDG             (0x0006U)
#define ECUM_MODULE_INT             (0x0007U)
#define ECUM_MODULE_ECC             (0x0008U)
#define ECUM_MODULE_INTHNDLR        (0x0009U)
#define ECUM_MODULE_VECT            (0x000AU)
/* EAL */
#define ECUM_MODULE_WDGIF           (0x1000U)
#define ECUM_MODULE_CANIF           (0x1001U)
#define ECUM_MODULE_CANTRCV         (0x1002U)
#define ECUM_MODULE_CODEFLSIF       (0x1003U)
#define ECUM_MODULE_EXTCODEFLSIF    (0x1004U)
#define ECUM_MODULE_CODERAMIF       (0x1005U)
#define ECUM_MODULE_USRSOFTIF       (0x1006U)
#define ECUM_MODULE_SLEEPIF         (0x1007U)
#define ECUM_MODULE_SUBMICONIF      (0x1008U)
/* SVL */
#define ECUM_MODULE_STARTUP         (0x2000U)
#define ECUM_MODULE_SYS             (0x2001U)
#define ECUM_MODULE_ECUM            (0x2002U)
#define ECUM_MODULE_BSWM            (0x2003U)
#define ECUM_MODULE_SCHM            (0x2004U)
#define ECUM_MODULE_TM              (0x2005U)
#define ECUM_MODULE_WDGM            (0x2006U)
#define ECUM_MODULE_DCM             (0x2008U)
#define ECUM_MODULE_COMM            (0x2009U)
#define ECUM_MODULE_CANSM           (0x200AU)
#define ECUM_MODULE_PDUR            (0x200BU)
#define ECUM_MODULE_CANTP           (0x200CU)
#define ECUM_MODULE_MEMM            (0x200DU)
#define ECUM_MODULE_MEMERRM         (0x200EU)
#define ECUM_MODULE_SHUTDOWN        (0x200FU)
#define ECUM_MODULE_GDNTMRSRV       (0x2010U)
#define ECUM_MODULE_GDNCANIF        (0x2011U)
/* PARTS */
#define ECUM_MODULE_WRAPCRYPTO      (0x3000U)
/* RTE */
#define ECUM_MODULE_RTE             (0x4000U)
/* AP */
#define ECUM_MODULE_RPGMFR          (0x8000U)
#define ECUM_MODULE_RPGSPP          (0x8001U)
#define ECUM_MODULE_SEC             (0x8002U)
#define ECUM_MODULE_DECRYPT         (0x8005U)
#define ECUM_MODULE_PRGCHK          (0x8006U)
#define ECUM_MODULE_FSCDTCT         (0x8007U)
#define ECUM_MODULE_RPGEVTHK        (0x8009U)
#define ECUM_MODULE_VEHINF          (0x800AU)
#define ECUM_MODULE_CMPDECMP        (0x800BU)
#define ECUM_MODULE_RPGLIB          (0x800CU)
#define ECUM_MODULE_DIAGLIB         (0x800DU)
#define ECUM_MODULE_DIAGSRV         (0xC000U)

/* EcuM status type */
#define ECUM_STATE_STARTUP          ((EcuM_StateType)0x10U)
#define ECUM_STATE_RUN              ((EcuM_StateType)0x30U)
#define ECUM_STATE_SHUTDOWN         ((EcuM_StateType)0x40U)

/* Reset type */
#define ECUM_RESET_MCU              ((EcuM_ResetType)0x00U)
#define ECUM_RESET_WDG              ((EcuM_ResetType)0x01U)

/* Entry type */
#define ECUM_START_BOOT_ENTRY       ((uint8)0x00U)
#define ECUM_START_AP_ENTRY         ((uint8)0x01U)
#if (REPROG_CFG_POSRES_AFTER_RESET == STD_ON)
#define ECUM_START_BOOT_POSRES_ENTRY    ((uint8)0x02U)
#endif
#if (REPROG_CFG_STAYINBOOT_ENABLE == STD_ON)
#define ECUM_START_STAYINBOOT_ENTRY ((uint8)0x03U)
#endif


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef uint8   EcuM_StateType;
typedef uint8   EcuM_ResetType;

typedef struct {
    uint16 ModuleId;
    uint8  ApiId;
    uint8  ErrorId;
} EcuM_ErrorType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
/* EcuM.c */
FUNC(void, ECUM_CODE_SLOW) EcuM_Init (void);
FUNC(void, ECUM_CODE_SLOW) EcuM_SetState
(
    VAR(EcuM_StateType, AUTOMATIC) State
);
FUNC(Std_ReturnType, ECUM_CODE_SLOW) EcuM_GoDown
(
    VAR(uint16, AUTOMATIC) Caller
);
FUNC(Std_ReturnType, ECUM_CODE_SLOW) EcuM_GoHalt (void);

/* EcuM_BootMode.c */
FUNC(void, ECUM_CODE_SLOW) EcuM_SetBootMode
(
    VAR(uint8, AUTOMATIC) Mode
);
FUNC(uint8, ECUM_CODE_SLOW) EcuM_GetBootMode (void);

/* EcuM_Error.c */
FUNC(void, ECUM_CODE_SLOW) EcuM_ClearReportError (void);
FUNC(Std_ReturnType, ECUM_CODE_SLOW) EcuM_CheckError (void);
FUNC(void, ECUM_CODE_SLOW) EcuM_ReportError
(
    P2CONST(EcuM_ErrorType, AUTOMATIC, ECUM_APPL_CONST) ErrorInfo
);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/


#endif /* ECUM_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2018/06/19 :Update                                rel.AUBASS */
/*  v3.00       :2019/12/03 :Update                                rel.AUBASS */
/*  v4.00       :2021/09/14 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

