/* Dcm_Dsp_SID29_h(v5-0-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID29/HEADER                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_SID29_H
#define DCM_DSP_SID29_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>

#if ( DCM_AUTHENTICATION_USE == STD_ON )

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

FUNC( void, DCM_CODE ) Dcm_Dsp_SID29_Init
( void );

#if ( DCM_SUPPORT_SID29_SUB00 == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID29_Sub00
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
);
#endif /* DCM_SUPPORT_SID29_SUB00 == STD_ON */

#if ( DCM_SUPPORT_SID29_SUB01 == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID29_Sub01
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
);
#endif /* DCM_SUPPORT_SID29_SUB01 == STD_ON */

#if ( DCM_SUPPORT_SID29_SUB02 == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID29_Sub02
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
);
#endif /* DCM_SUPPORT_SID29_SUB02 == STD_ON */

#if ( DCM_SUPPORT_SID29_SUB03 == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID29_Sub03
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
);
#endif /* DCM_SUPPORT_SID29_SUB03 == STD_ON */

#if ( DCM_SUPPORT_SID29_SUB08 == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID29_Sub08
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
);
#endif /* DCM_SUPPORT_SID29_SUB08 == STD_ON */

FUNC( void, DCM_CODE ) Dcm_Dsp_SID29_VrfyCertUnidirCbk
(
    const uint8 u1EventId
);

FUNC( void, DCM_CODE ) Dcm_Dsp_SID29_VrfyCertBidirCbk
(
    const uint8 u1EventId
);

FUNC( void, DCM_CODE ) Dcm_Dsp_SID29_VrfyPownCbk
(
    const uint8 u1EventId
);

FUNC( void, DCM_CODE ) Dcm_Dsp_SID29_NotifyAuthStateUpdate
(
    const uint8 u1AuthState,
    const uint16 u2ConnectionId
);

FUNC( void, DCM_CODE ) Dcm_Dsp_SID29_Confirmation
(
    const Dcm_IdContextType u1IdContext,
    const uint16 u2ConnectionId,
    const Dcm_ConfirmationStatusType u1Status
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
#endif /* DCM_AUTHENTICATION_USE */

#endif /* DCM_DSP_SID29_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
