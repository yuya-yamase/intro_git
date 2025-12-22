/* Dcm_Dsp_SID28_Connector_c(v3-2-0)                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID28_Connector/CODE                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../Dsp/usr/Dcm_Dsp_SID28_Connector.h"
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
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>


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

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID28_Cnct_BswMComMode                           */
/* Description   | BswM_Dcm_CommunicationMode_CurrentState call             */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1ComMChId    : ComM channel ID                     */
/*               | [IN] u1ComMode     : Next communication mode             */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID28_Cnct_BswMComMode
(
    const uint8 u1ComMChId,
    const Dcm_CommunicationModeType u1ComMode
)
{
    vd_g_oXDoCANAubIfComTREOvrrd( u1ComMChId, u1ComMode );

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID28_Cnct_Switch_CCrl                           */
/* Description   | SchM_Switch_DcmCommunicationControl_                     */
/*               |     <symbolic name of ComMChannelId> call                */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1ComMChId    : ComM channel ID                     */
/*               | [IN] u1ComMode     : Next communication mode             */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   SCHM_E_LIMIT      : Queue overflow                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID28_Cnct_Switch_CCrl
(
    const uint8 u1ComMChId,
    const Dcm_CommunicationModeType u1ComMode
)
{
    return (Std_ReturnType)E_OK;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID28_Cnct_Mode_CCrl                             */
/* Description   | SchM_Mode_DcmCommunicationControl_                       */
/*               |     <symbolic name of ComMChannelId> call                */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1ComMChId  : ComM channel ID                       */
/* Return Value  | uint8            : Active communication mode             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint8, DCM_CODE ) Dcm_Dsp_SID28_Cnct_Mode_CCrl
(
    const uint8 u1ComMChId
)
{
    return((uint8)DCM_DISABLE_RX_TX_NORM_NM);
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
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2022-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
