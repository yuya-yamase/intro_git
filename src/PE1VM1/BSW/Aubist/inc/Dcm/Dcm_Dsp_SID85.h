/* Dcm_Dsp_SID85_h(v5-0-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID85/HEADER                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_SID85_H
#define DCM_DSP_SID85_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>
#if ( DCM_SUPPORT_SID85 == STD_ON )


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSP_SID85_SF_ENABLE         ((uint8)0x01U)
#define DCM_DSP_SID85_SF_DISABLE        ((uint8)0x02U)


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>
#if ( DCM_SUPPORT_SID85_SUB01 == STD_ON )
FUNC(Std_ReturnType, DCM_CODE) Dcm_SID85_Sub01
(
    Dcm_OpStatusType                                            OpStatus,
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA)       pMsgContext
);
#endif /* DCM_SUPPORT_SID85_SUB01 == STD_ON */
#if ( DCM_SUPPORT_SID85_SUB02 == STD_ON )
FUNC(Std_ReturnType, DCM_CODE) Dcm_SID85_Sub02
(
    Dcm_OpStatusType                                            OpStatus,
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA)       pMsgContext
);
#endif /* DCM_SUPPORT_SID85_SUB02 == STD_ON */
FUNC(void, DCM_CODE) Dcm_Dsp_SID85_Init
(
    void
);
FUNC(void, DCM_CODE) Dcm_Dsp_SID85_NotifySesCtrl
(
    const Dcm_SesCtrlType u1SesCtrlTypeOld,
    const Dcm_SesCtrlType u1SesCtrlTypeNew
);
FUNC( void, DCM_CODE ) Dcm_Dsp_SID85_Confirmation
(
    const Dcm_IdContextType u1IdContext,
    const uint16 u2ConnectionId,
    const Dcm_ConfirmationStatusType u1Status
);

#if ( DCM_SUPPORT_SID85_SUB01 == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsp_SID85_Sub01_Cbk
(
    const uint8 u1EventId
);
#endif /* DCM_SUPPORT_SID85_SUB01 == STD_ON */

#if ( DCM_SUPPORT_SID85_SUB02 == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsp_SID85_Sub02_Cbk
(
    const uint8 u1EventId
);
#endif /* DCM_SUPPORT_SID85_SUB02 == STD_ON */

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


#endif /* DCM_SUPPORT_SID85 == STD_ON */
#endif /* DCM_DSP_SID85_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-2-0         :2019-01-29                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2022-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

