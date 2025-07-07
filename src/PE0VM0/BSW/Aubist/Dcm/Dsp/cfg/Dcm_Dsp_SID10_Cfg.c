/* Dcm_Dsp_SID10_Cfg_c(v5-5-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID10_Cfg/CODE                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID10.h>
#include "../../Dsp/cfg/Dcm_Dsp_SID10_Cfg.h"

#include <Dcm.h>
/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSP_SID10_SUB01     ((uint8)0x01U)
#define DCM_DSP_SID10_SUB02     ((uint8)0x02U)
#define DCM_DSP_SID10_SUB03     ((uint8)0x03U)

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
#if ( DCM_SUPPORT_SID10 == STD_ON )
/* DcmDspSession */
CONST ( AB_83_ConstV Dcm_Dsp_SessionRowType, DCM_CONFIG_DATA ) Dcm_P_SID10_stSessionRow_Tbl[ DCM_P_SESSIONROW_T ] =
{
    /* ForBoot */   /* Level */    /* P2ServerMax */ /* P2StarServerMax */ /* P2StarServerMin *//* P2StarServerLsb */
    { DCM_NO_BOOT,  (uint8)0x01U,  (uint16)50U,      (uint16)5000U,        (uint16)4500U,       (uint16)500U          },
    { DCM_SYS_BOOT_RESPAPP,  (uint8)0x02U,  (uint16)50U,      (uint16)5000U,        (uint16)4500U,       (uint16)500U          },
    { DCM_NO_BOOT,  (uint8)0x03U,  (uint16)50U,      (uint16)5000U,        (uint16)4500U,       (uint16)500U          },
    { (uint8)0U,    (uint8)0U,     (uint16)0U,       (uint16)0U,           (uint16)0U,          (uint16)0U            } /* no parameter */
};

CONST ( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_P_SID10_u1SessionSetTiming = DCM_DSP_SID10_SETSES_CNF;
CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_P_u1SessionRow_N = DCM_P_SESSIONROW_N ;
CONST( AB_83_ConstV boolean, DCM_CONFIG_DATA ) Dcm_P_SID10_bNoSetSPREC = (boolean)FALSE;
#endif /* DCM_SUPPORT_SID10 == STD_ON */

#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>
#if ( DCM_SUPPORT_SID10 == STD_ON )

/****************************************************************************/
/* Function Name | Dcm_SID10_Sub01                                          */
/* Description   | Request processing of SID 10 Subfunction                 */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus       : Operation state                    */
/*               | [IN] pMsgContext    : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Request was successful             */
/*               |   DCM_E_PENDING     : Request is not yet finished        */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID10_Sub01
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType u1_RetVal;
    
    u1_RetVal = Dcm_Dsp_SID10( OpStatus, pMsgContext, DCM_DSP_SID10_SUB01 );
    
    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_SID10_Sub02                                          */
/* Description   | Request processing of SID 10 Subfunction                 */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus       : Operation state                    */
/*               | [IN] pMsgContext    : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Request was successful             */
/*               |   DCM_E_PENDING     : Request is not yet finished        */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID10_Sub02
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType u1_RetVal;
    
    u1_RetVal = Dcm_Dsp_SID10( OpStatus, pMsgContext, DCM_DSP_SID10_SUB02 );
    
    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_SID10_Sub03                                          */
/* Description   | Request processing of SID 10 Subfunction                 */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus       : Operation state                    */
/*               | [IN] pMsgContext    : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Request was successful             */
/*               |   DCM_E_PENDING     : Request is not yet finished        */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID10_Sub03
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType u1_RetVal;
    
    u1_RetVal = Dcm_Dsp_SID10( OpStatus, pMsgContext, DCM_DSP_SID10_SUB03 );
    
    return u1_RetVal;
}

#endif /* DCM_SUPPORT_SID10 == STD_ON */
#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-2-0         :2020-08-27                                              */
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
