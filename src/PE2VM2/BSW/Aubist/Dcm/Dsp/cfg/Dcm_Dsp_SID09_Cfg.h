/* Dcm_Dsp_SID09_Cfg_h(v5-3-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID09_Cfg/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_SID09_CFG_H
#define DCM_DSP_SID09_CFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>
#if( DCM_SUPPORT_SID09 == STD_ON )

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_INFOTYPE08_NUM   ( (uint8)0x08U )
#define DCM_INFOTYPE0B_NUM   ( (uint8)0x0BU )

#define DCM_SUPINFOTYPE_NUM  ( (uint8)0U )
#define DCM_SUPINFOTYPE_TBL  ( DCM_SUPINFOTYPE_NUM + (uint8)1U )

#define DCM_INFOTYPE_NUM     ( (uint8)0U )
#define DCM_INFOTYPE_TBL     ( DCM_INFOTYPE_NUM + (uint8)1U )


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef P2FUNC( Std_ReturnType, DCM_CODE_CALLOUT, DcmDspVehInfoDataReadFncPTR )
(
    CONST( Dcm_OpStatusType, AUTOMATIC ) OpStatus,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DataValueBuffer,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DataValueBufferSize
);

typedef struct
{
    DcmDspVehInfoDataReadFncPTR ptDcmDspVehInfoDataReadFnc;
    uint8                       u1DcmDspVehInfoDataSize;
}DcmDspInfoTypeDataType;

typedef struct
{
    CONSTP2CONST( AB_83_ConstV DcmDspInfoTypeDataType, TYPEDEF, DCM_APPL_CONST ) ptDcmDspVehInfoData;
    uint8                                                                        u1DcmDspVehInfoDataNum;
    uint8                                                                        u1DcmDspVehInfoInfoType;
    uint8                                                                        u1DcmDspVehInfoInterNODI;
}DcmDspVehInfoType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

FUNC( boolean, DCM_CODE ) Dcm_Dsp_SID09_JudgeDemIUMPRUse
(
    CONST( Dcm_MsgItemType, AUTOMATIC ) u1reqInfoType
);

FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID09_GetInfoTypeValue
(
    CONST( Dcm_OpStatusType, AUTOMATIC ) u1OpStatus,
    CONST( Dcm_MsgItemType, AUTOMATIC ) u1reqInfoType,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) DataValueBuffer,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) BufferSize
);

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

extern CONST( AB_83_ConstV DcmDspVehInfoType, DCM_CONFIG_DATA ) DcmDspInfoTypeTbl[DCM_INFOTYPE_TBL];
extern CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_P_SID09_u1SupInfoTypeNumber;
extern CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_P_SID09_u1InfoTypeNumber;

#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

#define DCM_START_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTVEHINFOINFOTYPE
#include <Dcm_MemMap.h>

extern CONST( AB_83_ConstV uint32, DCM_CONST_PBCONFIG_DIRECTLY_SUPPORTVEHINFOINFOTYPE ) DcmDspSupportInfoTypeTbl[DCM_SUPINFOTYPE_TBL];

#define DCM_STOP_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTVEHINFOINFOTYPE
#include <Dcm_MemMap.h>

#endif /* DCM_SUPPORT_SID09 == STD_ON */
#endif /* DCM_DSP_SID09_CFG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-05-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-3-z0003                                        */
/*  BSW plug-in        :v5-5-1                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
