/* Dcm_Dsp_SID2A_h(v5-0-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID2A/HEADER                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_SID2A_H
#define DCM_DSP_SID2A_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>

#if( DCM_PERIODIC_SEND_USE == STD_ON )

#include <Dcm/Dcm_Dsp_PeriodicMng.h>
#include <Dcm/Dcm_Dsp_DidMng.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#if( DCM_PERIODIC_DDDID_USE == STD_ON )
#define DCM_DSP_SID2A_DDDID_ALLCLR                 ((uint16)0x0000U)
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON */

#define DCM_DSP_SID2A_CONDITION_INVALID            ((uint8)0U)
#define DCM_DSP_SID2A_CONDITION_SLOW               DCM_DSP_PERIODIC_TM_SLOWRATE
#define DCM_DSP_SID2A_CONDITION_MEDIUM             DCM_DSP_PERIODIC_TM_MEDIUMRATE
#define DCM_DSP_SID2A_CONDITION_FAST               DCM_DSP_PERIODIC_TM_FASTRATE
#define DCM_DSP_SID2A_CONDITION_STOP               DCM_DSP_PERIODIC_TM_STOPSENDING

#define DCM_DSP_SID2A_PDIDUPDINFO_TBL              ((uint16)( (uint16)DCM_DSP_PERIODIC_MAX_SCHDULER_NUM + DCM_DSP_PERIODIC_MAX_DIDREAD_NUM ))

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct
{
    uint16    u2ConnectionID;
    uint8     u1Pdid;
    uint8     u1ReqType;
    uint8     u1Condition;
}Dcm_Dsp_SID2A_PDidUpdateInfoType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>
FUNC(void, DCM_CODE) Dcm_Dsp_SID2A_Init
(void);
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID2A
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
);
FUNC( void, DCM_CODE ) Dcm_Dsp_SID2A_IsDidAvailableCbk
(
    const uint8 u1EventId
);
FUNC( void, DCM_CODE ) Dcm_Dsp_SID2A_DidRangeDataLenCbk
(
    const uint8 u1EventId
);
FUNC( void, DCM_CODE ) Dcm_Dsp_SID2A_Confirmation
(
    const Dcm_IdContextType u1IdContext,
    const uint16 u2ConnectionId,
    const Dcm_ConfirmationStatusType u1Status
);
FUNC( void, DCM_CODE ) Dcm_Dsp_SID2A_NotifySecCtrl
(
    const Dcm_SecLevelType u1SecLevelOld,
    const Dcm_SecLevelType u1SecLevelNew
);
FUNC( void, DCM_CODE ) Dcm_Dsp_SID2A_NotifySesCtrl
(
    const Dcm_SesCtrlType u1SesCtrlTypeOld,
    const Dcm_SesCtrlType u1SesCtrlTypeNew
);
#if( DCM_PERIODIC_DDDID_USE == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsp_SID2A_PDidInfoChkByDDDidClr
(
    const uint16 u2ClrDDDidInfo
);
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>
extern VAR( Dcm_Dsp_SID2A_PDidUpdateInfoType, DCM_VAR_NO_INIT ) Dcm_Dsp_SID2A_stPDIDUpdInfoTbl[ DCM_DSP_SID2A_PDIDUPDINFO_TBL ];
extern VAR( uint16, DCM_VAR_NO_INIT ) Dcm_Dsp_SID2A_u2PDidUpdInfoNum;

#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_CONST
#include <Dcm_MemMap.h>
#endif /* DCM_PERIODIC_SEND_USE */

#endif /* DCM_DSP_SID2A_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-2-0         :2018-12-25                                              */
/*  v5-0-0         :2021-12-24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
