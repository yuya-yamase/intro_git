/* Dcm_Dsp_SID2F_Callout_c(v5-0-0)                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID2F_Callout/CODE                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID2F_Callout.h>
#if ( DCM_SUPPORT_SID2F == STD_ON )
#include <Dcm.h>

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
/* Function Name | Dcm_IOCReturnControlToECUBySec                           */
/* Description   | ReturnControlToECU processing by security level change.  */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1SecLevelOld     : Security level before change    */
/*               | [IN] u1SecLevelNew     : Security level after change     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE_CALLOUT ) Dcm_IOCReturnControlToECUBySec
(
    const Dcm_SecLevelType u1SecLevelOld,
    const Dcm_SecLevelType u1SecLevelNew
)
{

    return;
}

/****************************************************************************/
/* Function Name | Dcm_IOCReturnControlToECUBySes                           */
/* Description   | ReturnControlToECU processing by session change.         */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1SesCtrlTypeOld     : Session before change        */
/*               | [IN] u1SesCtrlTypeNew     : Session after change         */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE_CALLOUT ) Dcm_IOCReturnControlToECUBySes
(
    const Dcm_SesCtrlType u1SesCtrlTypeOld,
    const Dcm_SesCtrlType u1SesCtrlTypeNew
)
{

    return;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define DCM_STOP_SEC_CODE_CALLOUT
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID2F == STD_ON */

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
