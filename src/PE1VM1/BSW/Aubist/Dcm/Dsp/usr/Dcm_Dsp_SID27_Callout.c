/* Dcm_Dsp_SID27_Callout_c(v5-3-0)                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID27_Callout/CODE                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID27_Callout.h>
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
/* Function Name | Dcm_SecLevel_GetSeed_Candi                               */
/* Description   | Seed generation processing of security level 02          */
/* Preconditions | None                                                     */
/* Parameters    | [IN]OpStatus     :Status of the current operation        */
/*               | [OUT]Seed        :provided seed                          */
/*               | [OUT]ErrorCode   :NRC to be sent if E_NOT_OK is returned */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                     :Request was successful         */
/*               | E_NOT_OK                 :Request was not successful     */
/*               | DCM_E_PENDING            :Request is not yet finished    */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE_CALLOUT) Dcm_SecLevel_GetSeed_Candi
(
    const Dcm_OpStatusType OpStatus,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA) Seed,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode
)
{
    Std_ReturnType        u1_t_ret;
    uint8                 u1_t_err;

    if( (OpStatus == DCM_INITIAL) ||
        (OpStatus == DCM_PENDING) || 
        (OpStatus == DCM_CANCEL)
    ){
        u1_t_ret = u1_g_oXDoCANAubIfSaSeed( (uint8)OXDC_SECURITY_ID01, 
                                            OpStatus, 
                                            Seed,
                                            &u1_t_err);
        if(u1_t_ret == (Std_ReturnType)E_NOT_OK){
            (*ErrorCode) = u1_t_err;
        }
    }
    else{
        /* ------------------------------------------------------------- */
        /* Attention :                                                   */
        /* ------------------------------------------------------------- */
        /* If OpStatus != DCM_INITIAL / DCM_PENDING / DCM_CANCEL         */
        /* the return of Dcm_SecLevel_GetSeed is discarded.              */
        /* ------------------------------------------------------------- */
        u1_t_ret = (Std_ReturnType)E_OK;
    }

    return(u1_t_ret);
}





/****************************************************************************/
/* Function Name | Dcm_SecLevel_CompareKey_Candi                            */
/* Description   | Key verification of security level 02                    */
/* Preconditions | None                                                     */
/* Parameters    | [IN]Key          :Key, which needs to be compared        */
/*               | [IN]OpStatus     :Status of the current operation        */
/*               | [OUT]ErrorCode   :NRC to be sent if E_NOT_OK is returned */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                     :Request was successful         */
/*               | E_NOT_OK                 :Request was not successful     */
/*               | DCM_E_PENDING            :Request is not yet finished    */
/*               | DCM_E_COMPARE_KEY_FAILED :Key did not match              */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE_CALLOUT) Dcm_SecLevel_CompareKey_Candi
(
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA ) Key,
    const Dcm_OpStatusType OpStatus,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ErrorCode
)
{
    Std_ReturnType        u1_t_ret;
    uint8                 u1_t_err;

    if(OpStatus == DCM_INITIAL){
        u1_t_ret = u1_g_oXDoCANAubIfSaKeyOk((uint8)OXDC_SECURITY_ID01, Key, &u1_t_err);
        if(u1_t_ret == (Std_ReturnType)E_NOT_OK){
            (*ErrorCode) = u1_t_err;
        }
    }
    else{
        /* ------------------------------------------------------------- */
        /* Attention :                                                   */
        /* ------------------------------------------------------------- */
        /* If OpStatus != DCM_INITIAL,                                   */
        /* the return of Dcm_SecLevel_CompareKey is discarded.           */
        /* ------------------------------------------------------------- */
        u1_t_ret = (Std_ReturnType)E_OK;
    }

    return (u1_t_ret);
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define DCM_STOP_SEC_CODE_CALLOUT
#include <Dcm_MemMap.h>

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
