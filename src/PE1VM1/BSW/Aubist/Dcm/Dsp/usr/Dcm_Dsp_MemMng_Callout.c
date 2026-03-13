/* Dcm_Dsp_MemMng_Callout_c(v5-6-0)                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_MemMng_Callout/CODE                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_MemMng_Callout.h>
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

#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID23 == STD_ON ) )
/****************************************************************************/
/* Function Name | Dcm_ReadMemory                                           */
/* Description   | Read memory by MemoryIdentifier, MemoryAddress and       */
/*               | MemorySize                                               */
/* Preconditions | None                                                     */
/* Parameters    | [IN]  OpStatus         : Status of the current operation */
/*               | [IN]  MemoryIdentifier : Identifier of the Memory Block  */
/*               | [IN]  MemoryAddress    : Starting of thc Memory Block    */
/*               | [IN]  MemorySize       : Number of bytes in the Memory   */
/*               | [OUT] MemoryData       : Data read                       */
/*               | [OUT] ErrorCode        : NRC                             */
/* Return Value  | Dcm_ReturnReadMemoryType                                 */
/*               |   DCM_READ_OK          : read was successful             */
/*               |   DCM_READ_FAILED      : read was not successful         */
/*               |   DCM_READ_PENDING     : read is not yet finished        */
/*               |   DCM_READ_FORCE_RCRRP : reading is pending              */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Dcm_ReturnReadMemoryType, DCM_CODE_CALLOUT ) Dcm_ReadMemory
(
    Dcm_OpStatusType OpStatus,
    uint8 MemoryIdentifier,
    uint32 MemoryAddress,
    uint32 MemorySize,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) MemoryData,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ErrorCode
)
{
    Dcm_ReturnReadMemoryType u1_RetVal;
    
    u1_RetVal = DCM_READ_FAILED;


    return u1_RetVal;
}



#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID23 == STD_ON */


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define DCM_STOP_SEC_CODE_CALLOUT
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-02-27                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
