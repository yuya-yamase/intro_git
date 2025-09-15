/* Dcm_Dsp_SID28_Cfg_c(v5-0-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID28_Cfg/CODE                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID28.h>
#if ( DCM_SUPPORT_SID28 == STD_ON )
#include "../../Dsp/cfg/Dcm_Dsp_SID28_Cfg.h"
#include <Dcm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSP_SID28_SUB00     ((uint8)0x00U)
#define DCM_DSP_SID28_SUB03     ((uint8)0x03U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

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
#define DCM_START_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>
/* DcmDspComControlAllChannel */
static CONST ( AB_83_ConstV Dcm_Dsp_ComControlAllChType, DCM_CONFIG_DATA ) Dcm_P_SID28_stComCtrlAllCh_Tbl[ DCM_P_COMCTRL_ALLCH_N ] =
{
    /* Used */          /* ChannelRef */
    { (boolean)TRUE,    (uint8)0x00U   }
};



/* DcmDspComControl */
CONST ( AB_83_ConstV Dcm_Dsp_ComControlType, DCM_CONFIG_DATA ) Dcm_P_SID28_stComCtrl_Tbl =
{
    (boolean)TRUE,                     /* ChkSession         */
    (boolean)TRUE,                     /* NormalComMsgUsed   */
    (boolean)FALSE,                     /* NwMngComMsgUsed    */
    (boolean)FALSE,                     /* ReceiveChannelUsed */
    DCM_P_COMCTRL_ALLCH_N,              /* AllChannelNum      */
    DCM_P_COMCTRL_SPCH_N,               /* SpecificChannelNum */
    DCM_P_COMCTRL_SUBN_N,               /* SubNodeNum         */
    Dcm_P_SID28_stComCtrlAllCh_Tbl,     /* AllChannel         */
    NULL_PTR,      /* SpecificChannel    */
    NULL_PTR       /* SubNode            */
};

CONST ( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_Dsp_SID28_u1ComCtrlTiming = DCM_P_COMCTRL_CNF;

#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* Function Name | Dcm_SID28_Sub00                                          */
/* Description   | Request processing of SID 28 Subfunction                 */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus       : Operation state                    */
/*               | [IN] pMsgContext    : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Request was successful             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID28_Sub00
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType u1_RetVal;
    
    u1_RetVal = Dcm_Dsp_SID28( OpStatus, pMsgContext, DCM_DSP_SID28_SUB00 );
    
    return u1_RetVal;
}
/****************************************************************************/
/* Function Name | Dcm_SID28_Sub03                                          */
/* Description   | Request processing of SID 28 Subfunction                 */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus       : Operation state                    */
/*               | [IN] pMsgContext    : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Request was successful             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID28_Sub03
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType u1_RetVal;
    
    u1_RetVal = Dcm_Dsp_SID28( OpStatus, pMsgContext, DCM_DSP_SID28_SUB03 );
    
    return u1_RetVal;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID28 == STD_ON */

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
