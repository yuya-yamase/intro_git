/* Dcm_Dsp_SIDBA_h(v5-3-0)                                               */

/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SIDBA/HEADER                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_SIDBA_H
#define DCM_DSP_SIDBA_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>
#if( DCM_SUPPORT_SIDBA == STD_ON )
#include <Dcm/Dcm_Main_Common.h>


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

FUNC( Std_ReturnType, DCM_CODE ) Dcm_SIDBA_Sub02
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
);
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SIDBA_Sub03
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
);
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SIDBA_Sub04
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
);
FUNC(void, DCM_CODE) Dcm_Dsp_SIDBA_Cbk
(
    const uint8 u1EventId
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


#endif /* DCM_SUPPORT_SIDBA == STD_ON */
#endif /* DCM_DSP_SIDBA_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

