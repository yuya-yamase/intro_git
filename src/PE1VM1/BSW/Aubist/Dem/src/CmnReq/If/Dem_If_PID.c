/* Dem_If_PID_c(v5-5-0)                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/If_PID/CODE                                           */
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
/* Function Name | Dem_ReadDataOfPID1C                                      */
/* Description   | Service to report the value of PID1C computed by the     */
/*               | Dem. API is needed in OBD - relevant ECUs only.          */
/* Preconditions | none                                                     */
/* Parameters    | [out] PID1Cvalue :                                       */
/*               |        Buffer containing the contents of PID1C computed  */
/*               |        by the Dem. The buffer is provided by the app-    */
/*               |        ication with the size of 1 bytes.                 */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Always E_OK is returned, as E_NOT_OK will  */
/*               |        never appear.                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_ReadDataOfPID1C
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID1Cvalue
)
{
    VAR( uint8, AUTOMATIC ) value;

    if( PID1Cvalue != NULL_PTR )
    {
        Dem_Control_ReadDataOfPID1C( &value );
        *PID1Cvalue = value;
    }
    else
    {
        /* No Process */
    }

    return E_OK;
}

/****************************************************************************/
/* Function Name | Dem_ReadDataOfPID30                                      */
/* Description   | Service to report the value of PID30 computed by the     */
/*               | Dem. API is needed in OBD - relevant ECUs only.          */
/* Preconditions | none                                                     */
/* Parameters    | [out] PID30value :                                       */
/*               |        Buffer containing the contents of PID30 computed  */
/*               |        by the Dem. The buffer is provided by the app-    */
/*               |        ication with the size of 1 bytes.                 */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Always E_OK is returned, as E_NOT_OK will  */
/*               |        never appear.                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_ReadDataOfPID30
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID30value
)
{
    VAR( uint8, AUTOMATIC ) value;

    if( PID30value != NULL_PTR )
    {
        Dem_Control_ReadDataOfPID30( &value );
        *PID30value = value;
    }
    else
    {
        /* No Process */
    }

    return E_OK;
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
