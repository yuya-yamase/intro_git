/* Dcm_Dsp_SID28_Cfg_h(v5-0-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID28_Cfg/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_SID28_CFG_H
#define DCM_DSP_SID28_CFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID28_Callout.h>
#include <Dcm.h>
#if ( DCM_SUPPORT_SID28 == STD_ON )

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_P_COMCTRL_ALLCH_N               ((uint8)1U)
#define DCM_P_COMCTRL_SPCH_N                ((uint8)0U)
#define DCM_P_COMCTRL_SUBN_N                ((uint16)0U)

#define DCM_P_COMCTRL_IND                   ((uint8)0U)
#define DCM_P_COMCTRL_CNF                   ((uint8)1U)

#define Dcm_Dsp_SID28_CheckComCtrl( u1SubFunction, u1Com, u2NodeId, ptErrorCode ) Dcm_ComCtrl_CheckComCtrl( (u1SubFunction), (u1Com), (u2NodeId), (ptErrorCode) ) /* MISRA DEVIATION */
#define Dcm_Dsp_SID28_CompComCtrl( u1ComMChId, u1ComMode ) Dcm_CompCommunicationControl( (u1ComMChId), (u1ComMode) ) /* MISRA DEVIATION */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* DcmDspComControlAllChannel */
typedef struct
{
    boolean bUsed;                              /* DcmDspComControlAllChannelUsed           */
    uint8   u1ComMChannel;                      /* DcmDspAllComMChannelRef                  */
}Dcm_Dsp_ComControlAllChType;


/* DcmDspComControlSpecificChannel */
typedef struct
{
    boolean bUsed;                              /* DcmDspComControlSpecificChannelUsed      */
    uint8   u1SubnetNumber;                     /* DcmDspSubnetNumber                       */
    uint8   u1ComMChannel;                      /* DcmDspSpecificComMChannelRef             */
}Dcm_Dsp_ComControlSpChType;


/* DcmDspComControlSubNode */
typedef struct
{
    boolean bUsed;                              /* DcmDspComControlSubNodeUsed              */
    uint8   u1ComMChannel;                      /* DcmDspComControlSubNodeComMChannelRef    */
    uint16  u2SubNodeId;                        /* DcmDspComControlSubNodeId                */
}Dcm_Dsp_ComControlSubNodeType;


/* DcmDspComControl */
typedef struct
{
    boolean bChkSession;                        /* DcmDspComControlChkSession               */
    boolean bNormalComMsgUsed;                  /* DcmDspComControlNormalComMsgUsed         */
    boolean bNwMngComMsgUsed;                   /* DcmDspComControlNwMngComMsgUsed          */
    boolean bRxChUsed;                          /* DcmDspComControlReceiveChannelUsed       */
    uint8   u1AllChNum;                         /* DcmDspComControlAllChannelNum            */
    uint8   u1SpChNum;                          /* DcmDspComControlSpecificChannelNum       */
    uint16  u2SubNodeNum;                       /* DcmDspComControlSubNodeNum               */
    P2CONST( AB_83_ConstV Dcm_Dsp_ComControlAllChType, TYPEDEF, DCM_APPL_CONST ) ptAllCh;
                                                /* DcmDspComControlAllChannel               */
    P2CONST( AB_83_ConstV Dcm_Dsp_ComControlSpChType, TYPEDEF, DCM_APPL_CONST ) ptSpCh;
                                                /* DcmDspComControlSpecificChannel          */
    P2CONST( AB_83_ConstV Dcm_Dsp_ComControlSubNodeType, TYPEDEF, DCM_APPL_CONST ) ptSubNode;
                                                /* DcmDspComControlSubNode                  */
}Dcm_Dsp_ComControlType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID28_Sub00
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
);

FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID28_Sub03
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
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
extern CONST ( AB_83_ConstV Dcm_Dsp_ComControlType, DCM_CONFIG_DATA ) Dcm_P_SID28_stComCtrl_Tbl;
extern CONST ( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsp_SID28_u1ComCtrlTiming;

#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

#endif /* DCM_SUPPORT_SID28 == STD_ON */
#endif /* DCM_DSP_SID28_CFG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v5-0-0         :2022-03-29                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-5-1                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
