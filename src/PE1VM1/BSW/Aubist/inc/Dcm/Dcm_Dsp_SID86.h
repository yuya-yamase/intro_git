/* Dcm_Dsp_SID86_h(v5-3-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID86/HEADER                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_SID86_H
#define DCM_DSP_SID86_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>
#if ( DCM_SID86_ROE_USE == STD_ON )
#include "../../Dcm/Dsp/cfg/Dcm_Dsp_SID86_Cfg.h"

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
FUNC(void, DCM_CODE) Dcm_Dsp_SID86_Init
(void);
#if ( DCM_SUPPORT_SID86_SUB00 == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID86_Sub00
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
);
#endif /* DCM_SUPPORT_SID86_SUB00 == STD_ON */
#if ( DCM_SUPPORT_SID86_SUB01 == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID86_Sub01
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
);
#endif /* DCM_SUPPORT_SID86_SUB01 == STD_ON */
#if ( DCM_SUPPORT_SID86_SUB03 == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID86_Sub03
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
);
#endif /* DCM_SUPPORT_SID86_SUB03 == STD_ON */
#if ( DCM_SUPPORT_SID86_SUB05 == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID86_Sub05
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
);
#endif /* DCM_SUPPORT_SID86_SUB05 == STD_ON */
#if ( DCM_SUPPORT_SID86_SUB06 == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID86_Sub06
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
);
#endif /* DCM_SUPPORT_SID86_SUB06 == STD_ON */
#if ( DCM_SUPPORT_SID86_SUB07 == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID86_Sub07
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
);
#endif /* DCM_SUPPORT_SID86_SUB07 == STD_ON */
#if ( DCM_SUPPORT_SID86_SUB40 == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID86_Sub40
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
);
#endif /* DCM_SUPPORT_SID86_SUB40 == STD_ON */
#if ( DCM_SUPPORT_SID86_SUB41 == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID86_Sub41
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
);
#endif /* DCM_SUPPORT_SID86_SUB41 == STD_ON */
#if ( DCM_SUPPORT_SID86_SUB43 == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID86_Sub43
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
);
#endif /* DCM_SUPPORT_SID86_SUB43 == STD_ON */
#if ( DCM_SUPPORT_SID86_SUB45 == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID86_Sub45
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
);
#endif /* DCM_SUPPORT_SID86_SUB45 == STD_ON */
#if ( DCM_SUPPORT_SID86_SUB46 == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID86_Sub46
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
);
#endif /* DCM_SUPPORT_SID86_SUB46 == STD_ON */
#if ( DCM_SUPPORT_SID86_SUB47 == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID86_Sub47
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
);
#endif /* DCM_SUPPORT_SID86_SUB47 == STD_ON */
/* For Session Chagne */
FUNC(void, DCM_CODE) Dcm_Dsp_SID86_NotifySesCtrl
(
    const Dcm_SesCtrlType u1SesCtrlTypeOld,
    const Dcm_SesCtrlType u1SesCtrlTypeNew
);
/* Event of ServiceToRenpondTo send */
FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_TrigServToRespTo_Cbk
(
    const   uint8   u1EventId
);
/* Event of QueueOver Message send */
FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_RespQueueOver_Cbk
(
    const   uint8   u1EventId
);
/* For Intermediate Message Interval */
FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_InterMessageTime_Cbk
(
    const   uint8   u1TimerId
);
/* For GetActiveResponse */
FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_ROEStatusCheck
(
    P2VAR( Dcm_ActiveStateType, AUTOMATIC, DCM_APPL_DATA )  ptActive
);
/* For SetActiveResponse */
FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_SetActiveResponse
(
    const Dcm_ActiveStateType u1ServiceActiveStatus
);

#if ( DCM_DSP_SID86_NVM_USE == STD_ON )
/* for NvM */
FUNC( void, DCM_CODE) Dcm_Dsp_SID86_SetDataStorage2Mirror
(
    const uint16 u2BlockIdx
);
FUNC( void, DCM_CODE) Dcm_Dsp_SID86_SetDataMirror2Storage
(
    const uint16 u2BlockIdx
);
FUNC( void, DCM_CODE) Dcm_Dsp_SID86_ReadConfirmation
(
    const uint16 u2BlockIdx,
    const uint8  u1Result
);
FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_AllReadCompleteCbk
(
    const uint8 u1EventId
);
FUNC( void, DCM_CODE ) Dcm_Dsp_SID86_Refresh
(
    void
);
#endif  /* DCM_DSP_SID86_NVM_USE == STD_ON */

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
#define DCM_START_SEC_CONST
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_CONST
#include <Dcm_MemMap.h>



#endif /* DCM_SID86_ROE_USE */

#endif /* DCM_DSP_SID86_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
