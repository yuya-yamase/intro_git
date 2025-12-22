/* Dcm_Dsp_SID02_Cfg_c(v5-0-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID02_Cfg/CODE                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../Dsp/cfg/Dcm_Dsp_SID02_Cfg.h"
#if( DCM_SUPPORT_SID02 == STD_ON )
#include <Dcm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>


CONST( AB_83_ConstV Dcm_Dsp_PidFfdInfoType, DCM_CONFIG_DATA ) DcmDspPidFfdInfo[DCM_SID02_PIDTBL] = 
{
    { NULL_PTR,                 (uint8)0x00U, (uint8)0x00U }  /* <---Dummy Data */
};

CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_P_SID02_u1PidNumber = DCM_SID02_PIDNUM;
CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_P_SID02_u1SupPidNum = DCM_SID02_SUPPIDNUM;
CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_P_SID02_u1SupPidNum_NoFfd = DCM_SID02_SUPPIDNUM_NOFFD;

#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

#define DCM_START_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTPIDSERVICE02
#include <Dcm_MemMap.h>

CONST( AB_83_ConstV uint32, DCM_CONST_PBCONFIG_DIRECTLY_SUPPORTPIDSERVICE02 ) DcmDspSupportPidTableForSid02[DCM_SID02_SUPPIDTBL] =
{
    (uint32)0x00000000U  /* <---Dummy Data */
};

#define DCM_STOP_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTPIDSERVICE02
#include <Dcm_MemMap.h>

#define DCM_START_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTPIDSERVICE02NOFFD
#include <Dcm_MemMap.h>

CONST( AB_83_ConstV uint32, DCM_CONST_PBCONFIG_DIRECTLY_SUPPORTPIDSERVICE02NOFFD ) DcmDspSupportPidTableForSid02NoFfd[DCM_SID02_SUPPIDTBL_NOFFD] =
{
    (uint32)0x40000000U, /* 0x01-0x08, 0x09-0x10, 0x11-0x18, 0x19-0x20 */
    (uint32)0x00000000U  /* <---Dummy Data */
};

#define DCM_STOP_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTPIDSERVICE02NOFFD
#include <Dcm_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID02 == STD_ON */

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
