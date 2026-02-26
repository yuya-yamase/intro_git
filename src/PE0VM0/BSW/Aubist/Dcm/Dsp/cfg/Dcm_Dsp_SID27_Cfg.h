/* Dcm_Dsp_SID27_Cfg_h(v5-3-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID27_Cfg/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_SID27_CFG_H
#define DCM_DSP_SID27_CFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*---------------------*/
/* Config Multiplicity */
/*---------------------*/
#define DCM_P_SECURITY_N    ((uint8)0U)



#define DCM_P_SECURITY_N_TBL (DCM_P_SECURITY_N + (uint8)1U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

typedef    struct
{
    boolean    bSecADRSizeFlag;
}Dcm_Dsp_SecurityNumType;


typedef P2FUNC(Std_ReturnType, DCM_CODE_CALLOUT, Dcm_Dsp_GetSeedFuncType )
(
    const Dcm_OpStatusType OpStatus,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA) Seed,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode
);


typedef P2FUNC(Std_ReturnType, DCM_CODE_CALLOUT, Dcm_Dsp_GetSeedADRSizeFuncType )
(
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA ) SecurityAccessDataRecord,
    const Dcm_OpStatusType OpStatus,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA) Seed,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode
);


typedef P2FUNC(Std_ReturnType, DCM_CODE_CALLOUT, Dcm_Dsp_CompareKeyFuncType )
(
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA ) Key,
    const Dcm_OpStatusType OpStatus,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ErrorCode
);


typedef struct
{
    uint32                                  u4ADRSize;                      /* DcmDspSecurityADRSize               */
    uint32                                  u4KeySize;                      /* DcmDspSecurityKeySize               */
    uint32                                  u4SeedSize;                     /* DcmDspSecuritySeedSize              */
    Dcm_Dsp_GetSeedFuncType                 ptGetSeed;
    Dcm_Dsp_GetSeedADRSizeFuncType          ptGetSeedADRSize;
    Dcm_Dsp_CompareKeyFuncType              ptCompareKey;
    uint8                                   u1Level;                        /* DcmDspSecurityLevel                 */
}Dcm_Dsp_SecurityRowType;                                                   /* DcmDspSecurityRow                   */


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>
#if ( DCM_SUPPORT_SID27 == STD_ON )

FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID27_CallGetSeedCout
(
    const uint8 u1SecLvIndex,
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA) ptSecurityAccessDataRecord,
    const Dcm_OpStatusType u1OpStatus,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA) ptSeed,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode
);
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID27_CallCompKeyCout
(
    const uint8 u1SecLvIndex,
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA ) ptKey,
    const Dcm_OpStatusType u1OpStatus,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
);

#endif /* DCM_SUPPORT_SID27 == STD_ON */
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

#if ( DCM_SUPPORT_SID27 == STD_ON )
extern CONST( AB_83_ConstV Dcm_Dsp_SecurityNumType, DCM_CONFIG_DATA ) Dcm_Dsp_SecurityNumTbl[DCM_P_SECURITY_N_TBL];
extern CONST( AB_83_ConstV Dcm_Dsp_SecurityRowType, DCM_CONFIG_DATA ) Dcm_Dsp_SecurityParamTbl[DCM_P_SECURITY_N_TBL];
extern CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsp_u1Security_N;
#endif /* DCM_SUPPORT_SID27 == STD_ON */

#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

#endif /* DCM_DSP_SID27_CFG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v3-2-0         :2020-08-27                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-5-1                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
