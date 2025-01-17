/* Dem_IUMPR_FiM_Connector_c(v5-0-0)                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/IUMPR_FiM_Connector/CODE                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_IUMPR_SUPPORT == STD_ON )

#include "Dem_IUMPR_FiM_Connector.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
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

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CONST
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_CONST
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_FiM_GetFunctionPermission                            */
/* Description   | This service reports the permission state to             */
/*               | the functionality.                                       */
/* Preconditions | none                                                     */
/* Parameters    | [in]  FID :                                              */
/*               | [out] PermissionPtr :                                    */
/*               |         TRUE : FID has permission to run                 */
/*               |         FALSE: FID has no permission to run,             */
/*               |                i.e. shall not be executed                */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Operation was successful                   */
/*               |        E_NOT_OK : Operation failed                       */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_FiM_GetFunctionPermission
(
    VAR( Dem_FiM_FunctionIdType, AUTOMATIC )    FID,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC )      PermissionPtr
)
{
    VAR( Std_ReturnType, AUTOMATIC )    retVal;

    retVal = FiM_GetFunctionPermission( (FiM_FunctionIdType)FID, PermissionPtr );

    return retVal;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
#endif  /* ( DEM_IUMPR_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
