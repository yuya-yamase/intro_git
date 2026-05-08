/* Dcm_Dsp_SID28_Callout_c(v5-0-0)                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID28_Callout/CODE                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID28_Callout.h>
#if ( DCM_SUPPORT_SID28 == STD_ON )
#include <Dcm.h>

#include "oxdocan_aubif.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

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

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE_CALLOUT
#include <Dcm_MemMap.h>

/****************************************************************************/
/* Function Name | Dcm_ComCtrl_CheckComCtrl                                 */
/* Description   | Check processing of communication control                */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1SubFunction : SubFunction                         */
/*               | [IN] u1Com         : CommunicationType                   */
/*               | [IN] u2NodeId      : NodeIdentificationNumber            */
/*               | [OUT]ptErrorCode   : NRC                                 */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK             : Check OK                            */
/*               |   E_NOT_OK         : Check NG                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE_CALLOUT ) Dcm_ComCtrl_CheckComCtrl
(
    const uint8 u1SubFunction,
    const uint8 u1Com,
    const uint16 u2NodeId,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
)
{
    Std_ReturnType u1_RetVal;
    uint8          u1_t_nrc;

    u1_t_nrc = u1_g_oXDoCANAubIfComCtrlOk();
    if(u1_t_nrc == (U1)0U){
        u1_RetVal      = (Std_ReturnType)E_OK;
    }
    else{
        (*ptErrorCode) = u1_t_nrc;
        u1_RetVal      = (Std_ReturnType)E_NOT_OK;
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_CompCommunicationControl                             */
/* Description   | Confirm completion of communication control              */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1ComMChId    : ComM channel ID                     */
/*               | [IN] u1ComMode     : Communication mode                  */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK             : Complete                            */
/*               |   DCM_E_PENDING    : Not complete                        */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE_CALLOUT ) Dcm_CompCommunicationControl
(
    const uint8 u1ComMChId,
    const Dcm_CommunicationModeType u1ComMode
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    return u1_RetVal;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define DCM_STOP_SEC_CODE_CALLOUT
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID28 == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v5-0-0         :2022-03-29                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
