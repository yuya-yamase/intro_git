/* Dcm_Dsp_SID10_Cfg_h(v5-5-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID10_Cfg/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_SID10_CFG_H
#define DCM_DSP_SID10_CFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID10_Callout.h>
#include <Dcm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_P_SESSIONROW_N                  ((uint8)2U)
#define DCM_P_SESSIONROW_T                  ((uint8)(DCM_P_SESSIONROW_N + (uint8)1U))

#define DCM_DSP_SID10_SETSES_IND            ((uint8)0U)
#define DCM_DSP_SID10_SETSES_CNF            ((uint8)1U)

#define Dcm_Dsp_SID10_CheckSesCtrl( u1SubFunction, u1OpStatus, ptErrorCode ) Dcm_CheckSessionControl( (u1SubFunction), (u1OpStatus), (ptErrorCode) ) /* MISRA DEVIATION */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct
{
    uint8     u1ForBoot;                      /* DcmDspSessionForBoot               */
    uint8     u1Level;                        /* DcmDspSessionLevel                 */
    uint16    u2P2ServerMax;                  /* DcmDspSessionP2ServerMax           */
    uint16    u2P2StarServerMax;              /* DcmDspSessionP2StarServerMax       */
    uint16    u2P2StarServerTimeoutMin;       /* DcmDspSessionP2StarServerMin       */
    uint16    u2P2StarServerLsb;              /* DcmDspSessionP2StarServerLsb       */
}Dcm_Dsp_SessionRowType;                      /* DcmDspSessionRow (Container Name ) */

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>
#if ( DCM_SUPPORT_SID10 == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID10_Sub01
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
);
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID10_Sub03
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
);

#endif /* DCM_SUPPORT_SID10 == STD_ON */
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
#if ( DCM_SUPPORT_SID10 == STD_ON )
extern CONST ( AB_83_ConstV Dcm_Dsp_SessionRowType, DCM_CONFIG_DATA ) Dcm_P_SID10_stSessionRow_Tbl[ DCM_P_SESSIONROW_T ];
extern CONST ( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_P_SID10_u1SessionSetTiming;
extern CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_P_u1SessionRow_N;
extern CONST( AB_83_ConstV boolean, DCM_CONFIG_DATA ) Dcm_P_SID10_bNoSetSPREC;
#endif /* DCM_SUPPORT_SID10 == STD_ON */

#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

#endif /* DCM_DSP_SID10_CFG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-3-z0003                                        */
/*  BSW plug-in        :v5-5-1                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
