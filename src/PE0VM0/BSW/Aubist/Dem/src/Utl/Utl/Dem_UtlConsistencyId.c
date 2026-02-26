/* Dem_UtlConsistencyId_c(v5-3-0)                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UtlConsistencyId/CODE                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../../../inc/Dem_Utl.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

#define DEM_UTLCID_CONSISTENCY_MAX  ((Dem_u08_ConsistencyIdType)0xFEU)

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


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


/****************************************************************************/
/* Function Name | Dem_UtlCid_CalcConsistencyId                             */
/* Description   | calculate consisntency ID                                */
/* Preconditions |                                                          */
/* Parameters    | ConsistencyId: Consistency ID before calculation         */
/* Return Value  | Dem_u08_ConsistencyIdType                                */
/*               |   Consistency ID After calculation                       */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_ConsistencyIdType, DEM_CODE ) Dem_UtlCid_CalcConsistencyId
(
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId
)
{
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) calcConsistencyId;

    if( ConsistencyId > (Dem_u08_ConsistencyIdType)0U )
    {
        calcConsistencyId = ConsistencyId - (Dem_u08_ConsistencyIdType)1U;
    }
    else
    {
        calcConsistencyId = DEM_UTLCID_CONSISTENCY_MAX;
    }

    return calcConsistencyId;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
