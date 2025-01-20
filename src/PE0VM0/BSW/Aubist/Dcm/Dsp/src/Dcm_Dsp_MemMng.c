/* Dcm_Dsp_MemMng_c(v5-3-0)                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_MemMng/CODE                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_MemMng.h>
#include <Dcm/Dcm_Dsp_MemMng_Callout.h>
#include "../../Dsp/cfg/Dcm_Dsp_MemMng_Cfg.h"

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

#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID23 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
/****************************************************************************/
/* Function Name | Dcm_Dsp_MemMng_GetUseAsMemoryId                          */
/* Description   | Get the UserNotifyFlag                                   */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | boolean                                                  */
/*               | TRUE                                                     */
/*               | FALSE                                                    */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( boolean, DCM_CODE ) Dcm_Dsp_MemMng_GetUseAsMemoryId
( void )
{
    return ( Dcm_Dsp_MemMng_bMemAddrUseAsMemoryId );
}
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID23 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */

#if ( ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID23 == STD_ON ) )
/****************************************************************************/
/* Function Name | Dcm_Dsp_MemMng_GetMaxMemorySize                          */
/* Description   | Get the UserNotifyFlag                                   */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | uint32                                                   */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( uint32, DCM_CODE ) Dcm_Dsp_MemMng_GetMaxMemorySize
( void )
{
    return ( Dcm_Dsp_MemMng_u4MaxMemorySize );
}
#endif /* DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID23 == STD_ON */


#if ( DCM_SUPPORT_SID22 == STD_ON )
#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_OFF )
#if ( DCM_PAGEDBUFFER_SID23_ENABLED == STD_OFF )
/****************************************************************************/
/* Function Name | Dcm_Dsp_MemMng_ReadMemory                                */
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
FUNC( Dcm_ReturnReadMemoryType, DCM_CODE ) Dcm_Dsp_MemMng_ReadMemory
(
    Dcm_OpStatusType                                                u1OpStatus,
    uint8                                                           u1MemoryIdentifier,
    uint32                                                          u4MemoryAddress,
    uint32                                                          u4MemorySize,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )                        ptMemoryData,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
)
{
    Dcm_ReturnReadMemoryType u1_RetVal;
    
    u1_RetVal = Dcm_ReadMemory( u1OpStatus,
                                u1MemoryIdentifier,
                                u4MemoryAddress,
                                u4MemorySize,
                                ptMemoryData,
                                ptErrorCode );

    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID23_ENABLED == STD_OFF */
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_OFF */
#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON )
#if ( DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_MemMng_ReadMemory                                */
/* Description   | Read memory by MemoryIdentifier, MemoryAddress and       */
/*               | MemorySize                                               */
/* Preconditions | None                                                     */
/* Parameters    | [IN]  OpStatus         : Status of the current operation */
/*               | [IN]  MemoryIdentifier : Identifier of the Memory Block  */
/*               | [IN]  MemoryAddress    : Starting of thc Memory Block    */
/*               | [IN]  MemorySize       : Number of bytes in the Memory   */
/*               | [IN]  MaxMemorySize    : Max Memory Size                 */
/*               | [IN]  StoredMemorySize : Stored Memory Size              */
/*               | [OUT] MemoryData       : Data read                       */
/*               | [OUT] ErrorCode        : NRC                             */
/* Return Value  | Dcm_ReturnReadMemoryType                                 */
/*               |   DCM_READ_OK          : read was successful             */
/*               |   DCM_READ_FAILED      : read was not successful         */
/*               |   DCM_READ_PENDING     : read is not yet finished        */
/*               |   DCM_READ_FORCE_RCRRP : reading is pending              */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Dcm_ReturnReadMemoryType, DCM_CODE ) Dcm_Dsp_MemMng_ReadMemory
(
    Dcm_OpStatusType                                                u1OpStatus,
    uint8                                                           u1MemoryIdentifier,
    uint32                                                          u4MemoryAddress,
    uint32                                                          u4MemorySize,
    uint32                                                          u4MaxMemorySize,
    uint32                                                          u4StoredMemorySize,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )                        ptMemoryData,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
)
{
    Dcm_ReturnReadMemoryType u1_RetVal;
    
    u1_RetVal = Dcm_ReadMemory( u1OpStatus,
                                u1MemoryIdentifier,
                                u4MemoryAddress,
                                u4MemorySize,
                                u4MaxMemorySize,
                                u4StoredMemorySize,
                                ptMemoryData,
                                ptErrorCode );

    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON */
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON */
#endif /* DCM_SUPPORT_SID22 == STD_ON */


/****************************************************************************/
/* Function Name | Dcm_Dsp_MemMng_ReadMemoryForPeriodic                     */
/* Description   | Call Read memory Function                                */
/* Preconditions | None                                                     */
/* Parameters    | [IN]  OpStatus         : Status of the current operation */
/*               | [IN]  MemoryIdentifier : Identifier of the Memory Block  */
/*               | [IN]  MemoryAddress    : Starting of thc Memory Block    */
/*               | [IN]  MemorySize       : Number of bytes in the Memory   */
/*               | [IN]  MaxMemorySize    : Max Memory Size                 */
/*               | [IN]  StoredMemorySize : Stored Memory Size              */
/*               | [OUT] MemoryData       : Data read                       */
/*               | [OUT] ErrorCode        : NRC                             */
/* Return Value  | Dcm_ReturnReadMemoryType                                 */
/*               |   DCM_READ_OK          : read was successful             */
/*               |   DCM_READ_FAILED      : read was not successful         */
/*               |   DCM_READ_PENDING     : read is not yet finished        */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_PERIODIC_DDDID_USE == STD_ON )
#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON )
#if ( DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON )
FUNC( Dcm_ReturnReadMemoryType, DCM_CODE ) Dcm_Dsp_MemMng_ReadMemoryForPeriodic
(
    Dcm_OpStatusType                                                u1OpStatus,
    uint8                                                           u1MemoryIdentifier,
    uint32                                                          u4MemoryAddress,
    uint32                                                          u4MemorySize,
    uint32                                                          u4MaxMemorySize,
    uint32                                                          u4StoredMemorySize,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )                        ptMemoryData,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
)
{
    Dcm_ReturnReadMemoryType u1_RetVal;
    
    u1_RetVal = Dcm_ReadMemory( u1OpStatus,
                                u1MemoryIdentifier,
                                u4MemoryAddress,
                                u4MemorySize,
                                u4MaxMemorySize,
                                u4StoredMemorySize,
                                ptMemoryData,
                                ptErrorCode
                              );

    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON */
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_ON */
#if ( DCM_PAGEDBUFFER_SID22_ENABLED == STD_OFF )
#if ( DCM_PAGEDBUFFER_SID23_ENABLED == STD_OFF )
FUNC( Dcm_ReturnReadMemoryType, DCM_CODE ) Dcm_Dsp_MemMng_ReadMemoryForPeriodic
(
    Dcm_OpStatusType                                                u1OpStatus,
    uint8                                                           u1MemoryIdentifier,
    uint32                                                          u4MemoryAddress,
    uint32                                                          u4MemorySize,
    uint32                                                          u4MaxMemorySize,       /* MISRA DEVIATION */
    uint32                                                          u4StoredMemorySize,    /* MISRA DEVIATION */
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA )                        ptMemoryData,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
)
{
    Dcm_ReturnReadMemoryType u1_RetVal;
    
    u1_RetVal = Dcm_ReadMemory( u1OpStatus,
                                u1MemoryIdentifier,
                                u4MemoryAddress,
                                u4MemorySize,
                                ptMemoryData,
                                ptErrorCode
                              );

    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID23_ENABLED == STD_OFF */
#endif /* DCM_PAGEDBUFFER_SID22_ENABLED == STD_OFF */
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON */

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
