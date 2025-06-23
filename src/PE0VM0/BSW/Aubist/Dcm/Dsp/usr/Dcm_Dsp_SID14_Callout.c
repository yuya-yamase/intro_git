/* Dcm_Dsp_SID14_Callout_c(v5-3-0)                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID14_Callout/CODE                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID14_Callout.h>
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
/* Function Name | A user defines the function name.                        */
/* Description   | This function judges the practice right or wrong of      */
/*               | the ClearDTC.                                            */
/*               | When possible, return E_OK,                              */
/*               | and return E_NOT_OK if impossible.                       */
/*               | Set a NRC in ptErrorCode at the time of E_NOT_OK return. */
/* Preconditions | None                                                     */
/* Parameters    | [IN]  u4GoDTC       : Group of DTC                       */
/*               | [OUT] ptErrorCode   : NRC                                */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : ClearDTC is possible               */
/*               |   E_NOT_OK          : ClearDTC is impossible             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE_CALLOUT ) Dem_ClearDTCCheckFnc
(
    const uint32 u4GoDTC,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
)
{

    Std_ReturnType u1_RetVal;

#if(OXDC_SID14_NR_22_USE == OXDC_USE)
    u1_RetVal = u1_g_oXDoCANClearDTCChk();
    if(u1_RetVal == (Std_ReturnType)E_NOT_OK){
        (*ptErrorCode) = DCM_E_CONDITIONSNOTCORRECT;
    }
    else{
        vd_g_oXDoCANAubIfDtcEvmAct((uint8)OXDC_DTC_EVM_S14);
    }
#else
    vd_g_oXDoCANAubIfDtcEvmAct((uint8)OXDC_DTC_EVM_S14);
    u1_RetVal       = E_OK;
#endif

    return u1_RetVal;
	
}

/****************************************************************************/
/* Function Name | Dcm_CheckTheClearDTCRequestIsAcceptable                  */
/* Description   | This function judges the acceptance of the ClearDTC.     */
/*               | When possible, return E_OK,                              */
/*               | and return E_NOT_OK if impossible.                       */
/*               | Set a ptErrorCode to NRC at the time of E_NOT_OK return. */
/* Preconditions | None                                                     */
/* Parameters    | [IN]  u2PduId     : Received PduId                       */
/*               | [IN]  u4GroupOfDTC : Group of DTC                        */
/*               | [IN]  bMemorySelectionUse : MemorySelection Enabled      */
/*               | [IN]  u1MemorySelectionValue : MemorySelection Value     */
/*               | [OUT] ptErrorCode : Negative Response Code Value         */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK          : The ClearDTC reuest is acceptable      */
/*               |   E_NOT_OK      : The ClearDTC reuest is not acceptable  */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE_CALLOUT ) Dcm_CheckTheClearDTCRequestIsAcceptable
(
    const uint16      u2PduId,
    const uint32      u4GroupOfDTC,
    const boolean     bMemorySelectionUse,
    const uint8       u1MemorySelectionValue,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
)
{
    Std_ReturnType u1_RetVal;
    
    u1_RetVal       = E_OK;
    
    return u1_RetVal;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define DCM_STOP_SEC_CODE_CALLOUT
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-3-z0003                                        */
/*  BSW plug-in        :v5-5-1                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
