/* Dcm_Dsp_SID01_Cfg_h(v5-3-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID01_Cfg/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_SID01_CFG_H
#define DCM_DSP_SID01_CFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>
#if( DCM_SUPPORT_SID01 == STD_ON )
#include <Dcm/Dcm_Dsp_Main.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_SID01_SUPPIDNUM   ( (uint8)0U )
#define DCM_SID01_SUPPIDTBL   ( DCM_SID01_SUPPIDNUM + (uint8)1U )

#define DCM_SID01_PIDNUM      ( (uint8)0U )
#define DCM_SID01_PIDTBL      ( DCM_SID01_PIDNUM + (uint8)1U )


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef P2FUNC(Std_ReturnType, DCM_CODE, DcmDspPidDataReadFncPTR)
(
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptData
);

typedef struct
{
    DcmDspPidDataReadFncPTR ptDcmDspPidDataReadFnc;
    uint16                  u2DcmDspPidDataPos;
    uint16                  u2DcmDspPidDataSize;
    uint8                   u1DcmDspPidDataType;
}Dcm_Dsp_PidDataType;

typedef struct
{
    CONSTP2CONST( AB_83_ConstV Dcm_Dsp_PidDataType, TYPEDEF, DCM_APPL_CONST ) ptPidData;
    uint8                                                                     u1DcmDspPidIdentifier;
    uint8                                                                     u1DcmDspPidSize;
}Dcm_Dsp_PidDataInfoType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

extern CONST( AB_83_ConstV Dcm_Dsp_PidDataInfoType, DCM_CONFIG_DATA ) DcmDspPidDataInfo[DCM_SID01_PIDTBL];
extern CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_P_SID01_u1SupPidNumber;
extern CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_P_SID01_u1PidNumber;

#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

#define DCM_START_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTPIDSERVICE01
#include <Dcm_MemMap.h>

extern CONST( AB_83_ConstV uint32, DCM_CONST_PBCONFIG_DIRECTLY_SUPPORTPIDSERVICE01 ) DcmDspSupportPidTableForSid01[DCM_SID01_SUPPIDTBL];

#define DCM_STOP_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTPIDSERVICE01
#include <Dcm_MemMap.h>

#endif /* DCM_SUPPORT_SID01 == STD_ON */
#endif /* DCM_DSP_SID01_CFG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-05-29                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-5-1                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
