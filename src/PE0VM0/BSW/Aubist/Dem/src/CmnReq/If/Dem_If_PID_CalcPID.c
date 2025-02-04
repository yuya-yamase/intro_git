/* Dem_If_PID_CalcPID_c(v5-5-0)                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/If_PID_CalcPID/CODE                                   */
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

#if ( DEM_PID_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_ReadDataOfPID21                                      */
/* Description   | Service to report the value of PID21 computed by the     */
/*               | Dem.API is needed in OBD-relevant ECUs only.             */
/* Preconditions | none                                                     */
/* Parameters    | [out] PID21value :                                       */
/*               |        Buffer containing the contents of PID21 computed  */
/*               |        by the Dem. The buffer is provided by the app-    */
/*               |        ication with the size of 2 bytes.                 */
/* Return Value  | Std_ReturnType :                                         */
/*               |        E_OK : Always E_OK is returned, as E_NOT_OK will  */
/*               |        never appear.                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_ReadDataOfPID21
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID21value
)
{
    if( PID21value != NULL_PTR )
    {
        Dem_Control_ReadDataOfPID21( PID21value );
    }
    else
    {
        /* No Process */
    }

    return E_OK;
}

/****************************************************************************/
/* Function Name | Dem_ReadDataOfPID31                                      */
/* Description   | Service to report the value of PID31 computed by the     */
/*               | Dem. API is needed in OBD-relevant ECUs only.            */
/* Preconditions | none                                                     */
/* Parameters    | [out] PID31value :                                       */
/*               |        Buffer containing the contents of PID31 computed  */
/*               |        by the Dem. The buffer is provided by the app-    */
/*               |        ication with the size of 2 bytes.                 */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Always E_OK is returned, as E_NOT_OK will  */
/*               |        never appear.                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_ReadDataOfPID31
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID31value
)
{
    if( PID31value != NULL_PTR )
    {
        Dem_Control_ReadDataOfPID31( PID31value );
    }
    else
    {
        /* No Process */
    }

    return E_OK;
}


/****************************************************************************/
/* Function Name | Dem_ReadDataOfPID4D                                      */
/* Description   | Service to report the value of PID4D computed by the     */
/*               | Dem. API is needed in OBD-relevant ECUs only.            */
/* Preconditions | none                                                     */
/* Parameters    | [out] PID4Dvalue :                                       */
/*               |        Buffer containing the contents of PID4D computed  */
/*               |        by the Dem. The buffer is provided by the app-    */
/*               |        ication with the size of 2 bytes.                 */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Always E_OK is returned, as E_NOT_OK will  */
/*               |        never appear.                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_ReadDataOfPID4D
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID4Dvalue
)
{
    if( PID4Dvalue != NULL_PTR )
    {
        Dem_Control_ReadDataOfPID4D( PID4Dvalue );
    }
    else
    {
        /* No Process */
    }

    return E_OK;
}

/****************************************************************************/
/* Function Name | Dem_ReadDataOfPID4E                                      */
/* Description   | Service to report the value of PID4E computed by the     */
/*               | Dem. API is needed in OBD-relevant ECUs only.            */
/* Preconditions | none                                                     */
/* Parameters    | [out] PID4Evalue :                                       */
/*               |        Buffer containing the contents of PID4E computed  */
/*               |        by the Dem. The buffer is provided by the app-    */
/*               |        ication with the size of 2 bytes.                 */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Always E_OK is returned, as E_NOT_OK will  */
/*               |        never appear.                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_ReadDataOfPID4E
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID4Evalue
)
{
    if( PID4Evalue != NULL_PTR )
    {
        Dem_Control_ReadDataOfPID4E( PID4Evalue );
    }
    else
    {
        /* No Process */
    }

    return E_OK;
}



/****************************************************************************/
/* Function Name | Dem_SetDataOfPID21                                       */
/* Description   | Service to set the value of PID21 in the Dem by a softw- */
/*               | are component.                                           */
/*               | API is needed in OBD-relevant ECUs only.                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] PID21value :                                        */
/*               |        Buffer containing the contents of PID21. The      */
/*               |        buffer is provided by the SWC with the appropria- */
/*               |        te size.                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : setting successful.                        */
/*               |        E_NOT_OK : setting not successful.                */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_SetDataOfPID21
(
    P2CONST( uint8, AUTOMATIC, DEM_APPL_DATA ) PID21value
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalRetVal;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;

    retVal = E_NOT_OK;

    if( PID21value != NULL_PTR )
    {
        internalRetVal = Dem_Control_SetDataOfPID21( PID21value );

        /* Convert return value */
        if( internalRetVal == DEM_IRT_OK)
        {
            retVal = E_OK;
        }
        else
        {
            /* No Process */
        }
    }
    else
    {
        /* No Process */
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_SetDataOfPID31                                       */
/* Description   | Service to set the value of PID31 in the Dem by a softw- */
/*               | are component.                                           */
/*               | API is needed in OBD-relevant ECUs only.                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] PID31value :                                        */
/*               |        Buffer containing the contents of PID31. The      */
/*               |        buffer is provided by the SWC with the appropria- */
/*               |        te size.                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : setting successful.                        */
/*               |        E_NOT_OK : setting not successful.                */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_SetDataOfPID31
(
    P2CONST( uint8, AUTOMATIC, DEM_APPL_DATA ) PID31value
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalRetVal;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;

    retVal = E_NOT_OK;

    if( PID31value != NULL_PTR )
    {
        internalRetVal = Dem_Control_SetDataOfPID31( PID31value );

        /* Convert return value */
        if( internalRetVal == DEM_IRT_OK)
        {
            retVal = E_OK;
        }
        else
        {
            /* No Process */
        }
    }
    else
    {
        /* No Process */
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_SetDataOfPID4D                                       */
/* Description   | Service to set the value of PID4D in the Dem by a softw- */
/*               | are component.                                           */
/*               | API is needed in OBD-relevant ECUs only.                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] PID4Dvalue :                                        */
/*               |        Buffer containing the contents of PID4D. The      */
/*               |        buffer is provided by the SWC with the appropria- */
/*               |        te size.                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : setting successful.                        */
/*               |        E_NOT_OK : setting not successful.                */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_SetDataOfPID4D
(
    P2CONST( uint8, AUTOMATIC, DEM_APPL_DATA ) PID4Dvalue
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalRetVal;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;

    retVal = E_NOT_OK;

    if( PID4Dvalue != NULL_PTR )
    {
        internalRetVal = Dem_Control_SetDataOfPID4D( PID4Dvalue );

        /* Convert return value */
        if( internalRetVal == DEM_IRT_OK)
        {
            retVal = E_OK;
        }
        else
        {
            /* No Process */
        }
    }
    else
    {
        /* No Process */
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_SetDataOfPID4E                                       */
/* Description   | Service to set the value of PID4E in the Dem by a softw- */
/*               | are component.                                           */
/*               | API is needed in OBD-relevant ECUs only.                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] PID4Dvalue :                                        */
/*               |        Buffer containing the contents of PID4E. The      */
/*               |        buffer is provided by the SWC with the appropria- */
/*               |        te size.                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : setting successful.                        */
/*               |        E_NOT_OK : setting not successful.                */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_SetDataOfPID4E
(
    P2CONST( uint8, AUTOMATIC, DEM_APPL_DATA ) PID4Evalue
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) internalRetVal;
    VAR( Std_ReturnType, AUTOMATIC ) retVal;

    retVal = E_NOT_OK;

    if( PID4Evalue != NULL_PTR )
    {
        internalRetVal = Dem_Control_SetDataOfPID4E( PID4Evalue );

        /* Convert return value */
        if( internalRetVal == DEM_IRT_OK)
        {
            retVal = E_OK;
        }
        else
        {
            /* No Process */
        }
    }
    else
    {
        /* No Process */
    }

    return retVal;
}
#endif  /* ( DEM_PID_SUPPORT == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
