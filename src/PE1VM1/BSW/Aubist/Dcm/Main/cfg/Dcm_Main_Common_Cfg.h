/* Dcm_Main_Common_Cfg_h(v5-3-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Main_Common_Cfg/HEADER                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_MAIN_COMMON_CFG_H
#define DCM_MAIN_COMMON_CFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_M_DEV_ERROR_DETECT                      (STD_OFF)
#define DCM_M_SATELLITE_USED                        (STD_OFF)
#define DCM_M_USE_VINDATAIDENTIFIER                 (STD_OFF)
#define DCM_M_RESPONSE_AFTER_REBOOT                 (STD_OFF)
#define DCM_OBD_SUPPORT                             (STD_OFF)

#define Dcm_Main_NotifyAct() Dcm_NotifyAct()

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct
{
    boolean bDDDIDStorageNum;                                   /* DDDIDStorage multiplicity */
    boolean bDDDIDStorage;                                      /* DDDID definition is stored non-volatile or not */
    boolean bDevErrorDetect;                                    /* The DET mechanism enable or disable */
    boolean bRespondAllRequest;                                 /* If set to FALSE the DCM will not respond to diagnostic request that contains a service ID(0x40-0x7F or 0xC0-0xFF */
    uint32  u4TaskTime;                                         /* The time for the periodic cyclic task */
    boolean bVersionInfoApi;                                    /* The output Version info of the functionality enable or disable */
    boolean bVinRefNum;                                         /* VinRef multiplicity */
    uint16  u2VinRef;                                           /* The Did containing the VIN Information */
}Dcm_GeneralType;

typedef struct
{
    uint8 u1SatelliteEcucPartition;
}DcmSatelliteType;

typedef struct
{
    uint8 u1MasterEcucPartition;
    P2CONST( AB_83_ConstV DcmSatelliteType, AUTOMATIC, DCM_APPL_CONST ) ptSatellite;
}DcmMasterType;

typedef struct
{
    P2CONST( AB_83_ConstV DcmMasterType, AUTOMATIC, DCM_APPL_CONST ) ptMaster;
}DcmPartitionType;

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
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

extern CONST( AB_83_ConstV Dcm_GeneralType, DCM_CONFIG_DATA ) Dcm_M_General;
extern CONSTP2CONST( AB_83_ConstV DcmPartitionType, AUTOMATIC, DCM_APPL_CONST ) Dcm_M_ptPartition;

#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

#endif /* DCM_MAIN_COMMON_CFG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-07-27                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
