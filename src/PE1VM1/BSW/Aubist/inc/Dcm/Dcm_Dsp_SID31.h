/* Dcm_Dsp_SID31_h(v5-5-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID31/HEADER                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_SID31_H
#define DCM_DSP_SID31_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>
#if ( DCM_SUPPORT_SID31 == STD_ON )

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSP_SID31_SIGMAX    ((uint16)4U)    /* Signal maximum number */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct
{
    uint32  u4SigData[DCM_DSP_SID31_SIGMAX];    /* Signal data */
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptVarInData;                       /* Input VALIABLE_LENGTH data address */
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptVarOutData;                      /* Output VALIABLE_LENGTH data address */
    uint32  u4VarDataLen;                       /* VALIABLE_LENGTH data length */
#if ( DCM_PAGEDBUFFER_SID31_ENABLED == STD_ON )
    uint32  u4PageDataLen;                      /* VALIABLE_LENGTH page data length */
#endif /* DCM_PAGEDBUFFER_SID31_ENABLED == STD_ON */
    uint8   u1SigInDataNum;                     /* Input signal data number */
    uint8   u1SigOutDataNum;                    /* Output signal data number */
}Dcm_Dsp_SID31_SigDataType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID31
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
);
FUNC( void, DCM_CODE ) Dcm_Dsp_SID31_Cbk
(
    const uint8 u1EventId
);
#if ( DCM_PAGEDBUFFER_SID31_ENABLED == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsp_SID31_UpdatePageCbk
(
    const uint8 u1EventId
);
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_UpdatePage
(
    Dcm_MsgType     ptResData,
    Dcm_MsgLenType  u4ResMaxDataLen
);
FUNC( void, DCM_CODE ) Dcm_Dsp_SID31_CancelPage
(void);
#endif /* DCM_PAGEDBUFFER_SID31_ENABLED == STD_ON */

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

#endif /* DCM_SUPPORT_SID31 == STD_ON */
#endif /* DCM_DSP_SID31_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
