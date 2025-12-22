/* Dcm_Dsp_SID31_Cfg_h(v5-5-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID31_Cfg/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_SID31_CFG_H
#define DCM_DSP_SID31_CFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>
#if ( DCM_SUPPORT_SID31 == STD_ON )
#include <Dcm/Dcm_Dsp_SID31.h>
#include <Dcm/Dcm_Dsp_SID10.h>
#include <Dcm/Dcm_Dsp_SID27.h>
#include <Dcm/Dcm_Main_Common.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*------------------------------*/
/*---------Multiplicity---------*/
/*------------------------------*/

/*------CommonAuthorization-----*/
#define DCM_P_COMAUTH_N                        ((uint16)0U)
#define DCM_P_COMAUTH_T                        (DCM_P_COMAUTH_N + (uint16)1U)


/*--------------RID-------------*/
#define DCM_P_RID_N                            ((uint16)0U)
#define DCM_P_RID_T                            (DCM_P_RID_N + (uint16)1U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

typedef struct
{
    P2CONST( AB_83_ConstV Dcm_Dsp_SecurityRowType, TYPEDEF, DCM_CONFIG_DATA ) ptSecurityLevelRef;                         /* DcmDspCommonAuthorizationSecurityLevelRef */
}Dcm_Dsp_SID31_SecLevRefType; 

typedef struct
{
    P2CONST( AB_83_ConstV Dcm_Dsp_SessionRowType, TYPEDEF, DCM_CONFIG_DATA ) ptSessionRef;                                /* DcmDspCommonAuthorizationSessionRef */
}Dcm_Dsp_SID31_SesRefType; 

typedef struct
{
    P2CONST( AB_83_ConstV Dcm_Dsp_SID31_SecLevRefType, TYPEDEF, DCM_CONFIG_DATA ) ptRIDNSecurityLevelRef;
    P2CONST( AB_83_ConstV Dcm_Dsp_SID31_SesRefType, TYPEDEF, DCM_CONFIG_DATA ) ptRIDNSessionRef;
}Dcm_Dsp_CommonAuthorizationType;                                                                        /* DcmDspCommonAuthorization (Container Name ) */

typedef struct
{
    uint8     u1Endianness;                                                                              /* DcmDspRoutineSignalEndianness                          */
    uint8     u1Type;                                                                                    /* DcmDspRoutineSignalType                                */
    uint32    u4Length;                                                                                  /* DcmDspRoutineParameterSize                             */
    uint16    u2Pos;                                                                                     /* DcmDspRoutineSignalPos                                 */
}Dcm_Dsp_SigType;                                                                                        /* DcmDspRequestRoutineResultsOutSignal (Container Name ) */
                                                                                                         /* DcmDspStopRoutineInSignal (Container Name )            */
                                                                                                         /* DcmDspStopRoutineOutSignal (Container Name )           */
                                                                                                         /* DcmDspStartRoutineInSignal (Container Name )           */
                                                                                                         /* DcmDspStartRoutineOutSignal (Container Name )          */

typedef struct
{
    P2CONST( AB_83_ConstV Dcm_Dsp_SigType, TYPEDEF, DCM_APPL_CONST ) ptSignal;                           /* DcmDspRequestRoutineResultsOutSignal             */
                                                                                                         /* DcmDspStopRoutineInSignal                        */
                                                                                                         /* DcmDspStopRoutineOutSignal                       */
                                                                                                         /* DcmDspStartRoutineInSignal                       */
                                                                                                         /* DcmDspStartRoutineOutSignal                      */
}Dcm_Dsp_RoutineInOutType;                                                                               /* DcmDspRequestRoutineResultsOut (Container Name ) */
                                                                                                         /* DcmDspStopRoutineIn (Container Name )            */
                                                                                                         /* DcmDspStopRoutineOut (Container Name )           */
                                                                                                         /* DcmDspStartRoutineIn (Container Name )           */
                                                                                                         /* DcmDspStartRoutineOut (Container Name )          */

typedef P2FUNC(Std_ReturnType, DCM_CODE, Dcm_Dsp_RoutineFuncType )
(
    P2VAR( Dcm_Dsp_SID31_SigDataType, AUTOMATIC, DCM_APPL_DATA ) ptSigData,
    const Dcm_OpStatusType u1OpStatus,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
);

typedef struct
{
    Dcm_Dsp_RoutineFuncType   ptReqRslt;
    Dcm_Dsp_RoutineFuncType   ptStart;
    Dcm_Dsp_RoutineFuncType   ptStop;
    uint16 u2ID;                                                                                         /* DcmDspRoutineIdentifier         */
    uint8  u1RoutineInfo;                                                                                /* DcmDspRoutineInfoByte           */
    boolean bRoutineInfoUsed;
    boolean bUsePort;                                                                                    /* DcmDspRoutineUsePort            */
    boolean bUsed;                                                                                       /* DcmDspRoutineUsed               */
    P2CONST( AB_83_ConstV Dcm_Dsp_CommonAuthorizationType, TYPEDEF, DCM_APPL_DATA ) ptCommonAuthorizationRef;/* DcmDspCommonAuthorizationRef    */
}Dcm_Dsp_RoutineType;                                                                                    /* DcmDspRoutine (Container Name ) */

typedef struct
{
    uint8 u1SecurityLevelRefNum;
    uint8 u1SessionRefNum;
}Dcm_Dsp_SID31_ComAuthNumType;

typedef struct
{
    uint8 u1UsePortNum;
    uint8 u1ComAuthNum;
    uint8 u1ReqRsltNum;
    uint8 u1ReqRsltInNum;
    uint8 u1ReqRsltInSigNum;
    uint8 u1ReqRsltOutNum;
    uint8 u1ReqRsltOutSigNum;
    uint8 u1StaNum;
    uint8 u1StaInNum;
    uint8 u1StaInSigNum;
    uint8 u1StaOutNum;
    uint8 u1StaOutSigNum;
    uint8 u1StoNum;
    uint8 u1StoInNum;
    uint8 u1StoInSigNum;
    uint8 u1StoOutNum;
    uint8 u1StoOutSigNum;
}Dcm_Dsp_SID31_RIDNumType;

typedef struct
{
    uint8 u1SigEndNum;
    uint8 u1SigLenNum;
}Dcm_Dsp_SID31_SigNumType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>
FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_ReqResultsCout
(
    const uint16 u2RoutineIndex,
    P2VAR( Dcm_Dsp_SID31_SigDataType, AUTOMATIC, DCM_APPL_DATA ) ptSigData,
    const Dcm_OpStatusType u1OpStatus,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
);
FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_StartCout
(
    const uint16 u2RoutineIndex,
    P2VAR( Dcm_Dsp_SID31_SigDataType, AUTOMATIC, DCM_APPL_DATA ) ptSigData,
    const Dcm_OpStatusType u1OpStatus,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
);
FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_StopCout
(
    const uint16 u2RoutineIndex,
    P2VAR( Dcm_Dsp_SID31_SigDataType, AUTOMATIC, DCM_APPL_DATA ) ptSigData,
    const Dcm_OpStatusType u1OpStatus,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
);
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_CheckSupportedRid
(
    uint16 u2RoutineId,
    uint16 u2PduId 
);

FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_CheckSupportedSubFuncForRid
(
    uint16 u2RoutineId,
    uint8  u1SubFunction,
    uint16 u2PduId 
);

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

extern CONST ( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_SID31_ComAuth_INDEX_Tbl[ DCM_P_RID_T ];
extern CONST ( AB_83_ConstV Dcm_Dsp_SID31_ComAuthNumType, DCM_CONFIG_DATA ) Dcm_P_SID31_ComAuthN_Tbl[ DCM_P_COMAUTH_T ];
extern CONST ( AB_83_ConstV Dcm_Dsp_RoutineType, DCM_CONFIG_DATA ) Dcm_P_SID31_Routine_Tbl[ DCM_P_RID_T ];
extern CONST ( AB_83_ConstV Dcm_Dsp_SID31_RIDNumType, DCM_CONFIG_DATA ) Dcm_P_SID31_RIDN_Tbl[ DCM_P_RID_T ];
extern CONST ( AB_83_ConstV Dcm_Dsp_RoutineInOutType, DCM_CONFIG_DATA ) Dcm_P_SID31_ReqRsltIn_Tbl[ DCM_P_RID_T ];
extern CONST ( AB_83_ConstV Dcm_Dsp_RoutineInOutType, DCM_CONFIG_DATA ) Dcm_P_SID31_ReqRsltOut_Tbl[ DCM_P_RID_T ];
extern CONSTP2CONST ( AB_83_ConstV Dcm_Dsp_SID31_SigNumType, AUTOMATIC, DCM_APPL_CONST ) Dcm_P_SID31_RID_ReqRsltInNTbl[ DCM_P_RID_T ];
extern CONSTP2CONST ( AB_83_ConstV Dcm_Dsp_SID31_SigNumType, AUTOMATIC, DCM_APPL_CONST ) Dcm_P_SID31_RID_ReqRsltOutNTbl[ DCM_P_RID_T ];
extern CONST ( AB_83_ConstV Dcm_Dsp_RoutineInOutType, DCM_CONFIG_DATA ) Dcm_P_SID31_StaIn_Tbl[ DCM_P_RID_T ];
extern CONST ( AB_83_ConstV Dcm_Dsp_RoutineInOutType, DCM_CONFIG_DATA ) Dcm_P_SID31_StaOut_Tbl[ DCM_P_RID_T ];
extern CONSTP2CONST ( AB_83_ConstV Dcm_Dsp_SID31_SigNumType, AUTOMATIC, DCM_APPL_CONST ) Dcm_P_SID31_RID_StaInNTbl[ DCM_P_RID_T ];
extern CONSTP2CONST ( AB_83_ConstV Dcm_Dsp_SID31_SigNumType, AUTOMATIC, DCM_APPL_CONST ) Dcm_P_SID31_RID_StaOutNTbl[ DCM_P_RID_T ];
extern CONST ( AB_83_ConstV Dcm_Dsp_RoutineInOutType, DCM_CONFIG_DATA ) Dcm_P_SID31_StoIn_Tbl[ DCM_P_RID_T ];
extern CONST ( AB_83_ConstV Dcm_Dsp_RoutineInOutType, DCM_CONFIG_DATA ) Dcm_P_SID31_StoOut_Tbl[DCM_P_RID_T];
extern CONSTP2CONST ( AB_83_ConstV Dcm_Dsp_SID31_SigNumType, AUTOMATIC, DCM_APPL_CONST ) Dcm_P_SID31_RID_StoInNTbl[ DCM_P_RID_T ];
extern CONSTP2CONST ( AB_83_ConstV Dcm_Dsp_SID31_SigNumType, AUTOMATIC, DCM_APPL_CONST ) Dcm_P_SID31_RID_StoOutNTbl[ DCM_P_RID_T ];
extern CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_SID31_u2RIDNumber;
extern CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_SID31_u2Comauth_N;

#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

#endif /* DCM_SUPPORT_SID31 == STD_ON */
#endif /* DCM_DSP_SID31_CFG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v3-2-0         :2020-08-27                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
