/* Dcm_Dsp_MsgMaker_Cfg_h(v5-5-0)                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_MsgMaker_Cfg/HEADER                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_MSGMAKER_CFG_H
#define DCM_DSP_MSGMAKER_CFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_P_MSGMAKER_CONF_NUM                 ((uint8)2U)
#define DCM_P_MSGMAKER_CONF_TBL                 (DCM_P_MSGMAKER_CONF_NUM + (uint8)1U)


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef CONSTP2FUNC( void, DCM_CODE, Dcm_P_MsgMaker_ConfFuncType ) ( const Dcm_IdContextType u1IdContext, const uint16 u2ConnectionId, const Dcm_ConfirmationStatusType u1Status );

typedef struct
{
    Dcm_P_MsgMaker_ConfFuncType ptFnc;
    uint8                       u1Sid;
}Dcm_P_MsgMaker_ConfType; 


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
extern CONST ( AB_83_ConstV Dcm_P_MsgMaker_ConfType, DCM_CONFIG_DATA ) Dcm_P_MsgMaker_stConfTbl[ DCM_P_MSGMAKER_CONF_TBL ];
extern CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_P_Msgmaker_u1Conf_Num;

#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

#endif /* DCM_DSP_MSGMAKER_CFG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-2                                              */
/*  BSW plug-in        :v5-5-1                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
