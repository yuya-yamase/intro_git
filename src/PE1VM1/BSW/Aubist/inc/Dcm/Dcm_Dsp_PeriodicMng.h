/* Dcm_Dsp_PeriodicMng_h(v5-0-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_PeriodicMng/HEADER                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_PERIODICMNG_H
#define DCM_DSP_PERIODICMNG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>

#if( DCM_PERIODIC_SEND_USE == STD_ON )

#include "../../Dcm/Dsp/cfg/Dcm_Dsp_PeriodicMng_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct
{
    uint32    u4DownCounter;
    uint16    u2ConnectionID;
    uint8     u1Pdid;
    uint8     u1ReqType;
    uint8     u1Rate;
    uint8     u1Status;
    boolean   bQueueflg;
}Dcm_Dsp_Periodic_PdidInfoType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

FUNC(void, DCM_CODE) Dcm_Dsp_PeriodicMng_Init
(void);
FUNC(void, DCM_CODE) Dcm_Dsp_PeriodicMng_Main
(void);
FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_PeriodicStatusCheck
(
    P2VAR( Dcm_ActiveStateType, AUTOMATIC, DCM_APPL_DATA ) ptActive
);
FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_SetActiveResponse
(
    const Dcm_ActiveStateType u1ActiveStatus
);
FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_UpdatePDIDTbl
(
    const uint8 u1PdidNumNew,
    const uint8 u1ReqTMmode
);
FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_NotifySecCtrl
(
    const Dcm_SecLevelType u1SecLevelNew
);
FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_NotifySesCtrl
(
    const Dcm_SesCtrlType u1SesCtrlTypeNew
);
#if( DCM_PERIODIC_DDDID_USE == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_UpdPDidInfDDDidClr
(void);
FUNC( void, DCM_CODE ) Dcm_Dsp_PeriodicMng_UpdPDidInfSpecDDDidClr
(
    const uint8 u1ClrDDDid
);
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON */
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_PeriodicMng_ChkDID
(
    const uint16 u2Did,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptKindOfDid,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA ) ptDidIndex
);

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>
extern VAR( Dcm_Dsp_Periodic_PdidInfoType, DCM_VAR_NO_INIT )    Dcm_Dsp_Periodic_stPdidInfoTbl[ DCM_DSP_PERIODIC_PDIDINFO_TBL ];
extern VAR( uint8, DCM_VAR_NO_INIT )    Dcm_Dsp_Periodic_u1DidInfo_RegNum;

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
/*  v5-0-0         :2021-09-28                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
