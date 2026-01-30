/* Dem_If_PID_Readiness_c(v5-5-0)                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/If_PID_Readiness/CODE                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_Pm_Control_OBD.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_PID_READINESS_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_ReadDataOfPID01                                      */
/* Description   | Service to set the value of PID01 in the Dem by a sof-   */
/*               | tware component.                                         */
/*               | API is needed in OBD-relevant ECUs only.                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] PID01value :                                        */
/*               |        Buffer containing the contents of PID01 comput-   */
/*               |        ed by the Dem. The buffer is provided by the app- */
/*               |        ication with the size of 4 bytes.                 */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Always E_OK is returned, as E_NOT_OK will  */
/*               |        never appear.                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_ReadDataOfPID01
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID01value
)
{
    if( PID01value != NULL_PTR )
    {
        Dem_Control_ReadDataOfPID01( DEM_READINESS_CALLBY_SWC, PID01value );
    }
    else
    {
        /* No Process */
    }

    return E_OK;
}

/****************************************************************************/
/* Function Name | Dem_ReadDataOfPIDF501                                    */
/* Description   | Service to set the value of PIDF501 in the Dem by a sof- */
/*               | tware component.                                         */
/*               | API is needed in OBD-relevant ECUs only.                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] PIDF501value :                                      */
/*               |        Buffer containing the contents of PIDF501 comput- */
/*               |        ed by the Dem. The buffer is provided by the app- */
/*               |        ication with the size of 6 bytes.                 */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Always E_OK is returned, as E_NOT_OK will  */
/*               |        never appear.                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_ReadDataOfPIDF501
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PIDF501value
)
{
    if( PIDF501value != NULL_PTR )
    {
        Dem_Control_ReadDataOfPIDF501( DEM_READINESS_CALLBY_SWC, PIDF501value );
    }
    else
    {
        /* No Process */
    }

    return E_OK;
}

/****************************************************************************/
/* Function Name | Dem_ReadDataOfPID41                                      */
/* Description   | Service to report the value of PID41 computed by the     */
/*               | Dem. API is needed in OBD - relevant ECUs only.          */
/* Preconditions | none                                                     */
/* Parameters    | [out] PID41value :                                       */
/*               |        Buffer containing the contents of PID41 computed  */
/*               |        by the Dem. The buffer is provided by the app-    */
/*               |        ication with the size of 4 bytes.                 */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Always E_OK is returned, as E_NOT_OK will  */
/*               |        never appear.                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_ReadDataOfPID41
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID41value
)
{
    if( PID41value != NULL_PTR )
    {
        Dem_Control_ReadDataOfPID41( DEM_READINESS_CALLBY_SWC, PID41value );
    }
    else
    {
        /* No Process */
    }

    return E_OK;
}

/****************************************************************************/
/* Function Name | Dem_SetEventDisabled                                     */
/* Description   | Service for reporting the event as disabled to the Dem.  */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId    : Event identifier.                      */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK     : Operation was successful.              */
/*               |        E_NOT_OK : Operation failed.                      */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_SetEventDisabled
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalRetVal;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;

    retVal = E_NOT_OK;
    internalRetVal = Dem_Control_SetEvtDisable( EventId );

    /* Convert return value */
    if( internalRetVal == DEM_IRT_OK)
    {
        retVal = E_OK;
    }
    else
    {
        /* No Process */
    }

    return retVal;
}
#endif  /* ( DEM_PID_READINESS_SUPPORT == STD_ON )  */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
