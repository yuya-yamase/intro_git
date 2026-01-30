/* Dcm_Dsp_SID02_Cfg_h(v5-0-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID02_Cfg/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_SID02_CFG_H
#define DCM_DSP_SID02_CFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>
#if( DCM_SUPPORT_SID02 == STD_ON )

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_SID02_SUPPIDNUM       ( (uint8)0U )
#define DCM_SID02_SUPPIDTBL       ( DCM_SID02_SUPPIDNUM + (uint8)1U )

#define DCM_SID02_SUPPIDNUM_NOFFD ( (uint8)1U )
#define DCM_SID02_SUPPIDTBL_NOFFD ( DCM_SID02_SUPPIDNUM_NOFFD + (uint8)1U )

#define DCM_SID02_PIDNUM          ( (uint8)0U )
#define DCM_SID02_PIDTBL          ( DCM_SID02_PIDNUM + (uint8)1U )


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct
{
    uint16 u2DcmDspPidDataPos;
    uint16 u2DcmDspPidDataSize;
}Dcm_Dsp_PidFfdDataType;

typedef struct
{
    CONSTP2CONST( AB_83_ConstV Dcm_Dsp_PidFfdDataType, TYPEDEF, DCM_APPL_CONST ) ptPidData;
    uint8                                                                        u1DcmDspPidIdentifier;
    uint8                                                                        u1DcmDspPidSize;
}Dcm_Dsp_PidFfdInfoType;

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

extern CONST(AB_83_ConstV Dcm_Dsp_PidFfdInfoType, DCM_CONFIG_DATA) DcmDspPidFfdInfo[DCM_SID02_PIDTBL];
extern CONST(AB_83_ConstV uint8, DCM_CONFIG_DATA) Dcm_P_SID02_u1PidNumber;
extern CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_P_SID02_u1SupPidNum;
extern CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_P_SID02_u1SupPidNum_NoFfd;

#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

#define DCM_START_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTPIDSERVICE02
#include <Dcm_MemMap.h>

extern CONST(AB_83_ConstV uint32, DCM_CONST_PBCONFIG_DIRECTLY_SUPPORTPIDSERVICE02 ) DcmDspSupportPidTableForSid02[DCM_SID02_SUPPIDTBL];

#define DCM_STOP_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTPIDSERVICE02
#include <Dcm_MemMap.h>

#define DCM_START_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTPIDSERVICE02NOFFD
#include <Dcm_MemMap.h>

extern CONST(AB_83_ConstV uint32, DCM_CONST_PBCONFIG_DIRECTLY_SUPPORTPIDSERVICE02NOFFD ) DcmDspSupportPidTableForSid02NoFfd[DCM_SID02_SUPPIDTBL_NOFFD];

#define DCM_STOP_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTPIDSERVICE02NOFFD
#include <Dcm_MemMap.h>

#endif /* DCM_SUPPORT_SID02 == STD_ON */
#endif /* DCM_DSP_SID02_CFG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
