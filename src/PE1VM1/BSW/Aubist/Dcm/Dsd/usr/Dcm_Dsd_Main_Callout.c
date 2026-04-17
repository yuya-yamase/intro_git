/* Dcm_Dsd_Main_Callout_c(v5-6-0)                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsd_Main_Callout/CODE                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../Dsd/inc/Dcm_Dsd_Main.h"
#include <Dcm/Dcm_Dsd_Main_Callout.h>
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
#define DCM_START_SEC_CODE_CALLOUT
#include <Dcm_MemMap.h>

#define DCM_STOP_SEC_CODE_CALLOUT
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
#define DCM_START_SEC_CODE_CALLOUT
#include <Dcm_MemMap.h>


/****************************************************************************/
/* Function Name | Dcm_Indication                                           */
/* Description   | When checking the SID or sub-function, check whether to  */
/*               | run the diagnostic service.                              */
/* Preconditions | none                                                     */
/* Parameters    | [in] SID : Service ID                                    */
/*               | [in] RequestData : Request data excluding SID            */
/*               | [in] DataSize : Request data length excluding SID        */
/*               | [in] ReqType : Request address type                      */
/*               | [in] ConnectionId : Active Connection Id                 */
/*               | [out] ErrorCode : Request notification error code        */
/*               | [in] ProtocolType : Active Protocol                      */
/*               | [in] TesterSourceAddress : TesterAddress                 */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Request successful                         */
/*               |        E_NOT_OK : Request failed                         */
/*               |        E_REQUEST_NOT_ACCEPTED : Request rejected         */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE_CALLOUT) Dcm_Indication
(
    uint8 SID,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) RequestData,
    uint32 DataSize,
    uint8 ReqType,
    uint16 ConnectionId,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode,
    Dcm_ProtocolType ProtocolType,
    uint16 TesterSourceAddress
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;
    if((ReqType & (uint8)0xF0U) == (uint8)0U){      /* SID check */
        vd_g_oXDoCANAubIfStoreReqData(RequestData, DataSize);
    }

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
/*  v5-0-0         :2021-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-6-0         :2024-02-27                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
