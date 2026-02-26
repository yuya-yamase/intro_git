/* Dcm_Dsp_SID08_Cfg_h(v5-0-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID08_Cfg/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_SID08_CFG_H
#define DCM_DSP_SID08_CFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>
#if( DCM_SUPPORT_SID08 == STD_ON )
#include <Dcm/Dcm_Dsp_Main.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_SID08_SUPTIDNUM   ( (uint8)0U )
#define DCM_SID08_SUPTIDTBL   ( DCM_SID08_SUPTIDNUM + (uint8)1U )

#define DCM_SID08_TIDNUM      ( (uint8)0U )
#define DCM_SID08_TIDTBL      ( DCM_SID08_TIDNUM + (uint8)1U )

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef P2FUNC(Std_ReturnType, DCM_CODE, DcmDspTidReqControlFncPTR)
(
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) OutBuffer,
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA ) InBuffer
);

typedef struct
{
    DcmDspTidReqControlFncPTR ptDcmDspTidReqControlFnc;
    uint8                     u1DcmDspRequestControlInBufferSize;
    uint8                     u1DcmDspRequestControlOutBufferSize;
    uint8                     u1DcmDspTidIdentifier;
}Dcm_Dsp_TidInfoType;

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

extern CONST( AB_83_ConstV Dcm_Dsp_TidInfoType, DCM_CONFIG_DATA ) DcmDspTidInfo[DCM_SID08_TIDTBL];
extern CONST( AB_83_ConstV uint32, DCM_CONFIG_DATA ) DcmDspSupportTidTableForSid08[DCM_SID08_SUPTIDTBL];
extern CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_P_SID08_u1SupTidNumber;
extern CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_P_SID08_u1TidNumber;

#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

#endif /* DCM_SUPPORT_SID08 == STD_ON */
#endif /* DCM_DSP_SID08_CFG_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-5-1                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
