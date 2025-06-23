/* Dcm_Dsp_SID2C_h(v5-3-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID2C/HEADER                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_SID2C_H
#define DCM_DSP_SID2C_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>
#if ( DCM_SUPPORT_SID2C == STD_ON )

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
#if ( DCM_SUPPORT_SID2C_SUB01 == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID2C_Sub01
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
);
#endif /* DCM_SUPPORT_SID2C_SUB01 == STD_ON */
#if ( DCM_SUPPORT_SID2C_SUB02 == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID2C_Sub02
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
);
#endif /* DCM_SUPPORT_SID2C_SUB02 == STD_ON */
#if ( DCM_SUPPORT_SID2C_SUB03 == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID2C_Sub03
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
);
#endif /* DCM_SUPPORT_SID2C_SUB03 == STD_ON */
FUNC( void, DCM_CODE ) Dcm_Dsp_SID2C_Init
( void );
FUNC( void, DCM_CODE ) Dcm_Dsp_SID2C_DidAvailableCbk
(
    const uint8 u1EventId
);
FUNC( void, DCM_CODE ) Dcm_Dsp_SID2C_ChkPosSizeCbk
(
    const uint8 u1EventId
);
FUNC( void, DCM_CODE ) Dcm_Dsp_SID2C_ClearDDDID
(
    const Dcm_SesCtrlType u1SesCtrlTypeOld,
    const Dcm_SesCtrlType u1SesCtrlTypeNew
);
FUNC( void, DCM_CODE ) Dcm_Dsp_SID2C_NotifySecCtrl
(
    const Dcm_SecLevelType u1SecLevelOld,
    const Dcm_SecLevelType u1SecLevelNew
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
#define DCM_START_SEC_CONST
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_CONST
#include <Dcm_MemMap.h>

#endif /* DCM_SUPPORT_SID2C == STD_ON */
#endif /* DCM_DSP_SID2C_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
