/* Dem_IUMPR_Ratio_OFF_c(v5-3-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/IUMPR_Ratio_OFF/CODE                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_IUMPR_SUPPORT == STD_ON )
#if ( DEM_IUMPR_RATIO_SUPPORT == STD_OFF )

#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_Pm_IUMPR.h"
#include "Dem_IUMPR_local.h"

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


/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_IUMPR_Ratio_GetInfoTypeValue                         */
/* Description   | Service is used for requesting IUMPR data according to   */
/*               | InfoType 0x08 or 0x0B.                                   */
/* Preconditions | none                                                     */
/* Parameters    | [out] IumprdataPtr :                                     */
/*               |          Buffer containing the contents of               */
/*               |          InfoType 0x08 or 0x0B.                          */
/*               |          The buffer is provided by the Dcm.              */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IUMPR_Ratio_GetInfoTypeValue
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA )        IumprdataPtr
)
{
    VAR( Dem_u08_IUMPRGroupIndexType, AUTOMATIC )   groupIndex;
    VAR( Dem_u08_IUMPRGroupIndexType, AUTOMATIC )   reqIumprGroupNum;
    VAR( uint8, AUTOMATIC )                         dataPos;

    reqIumprGroupNum                    = Dem_IUMPR_NODI_GroupNum;
    for ( groupIndex = (Dem_u08_IUMPRGroupIndexType)0U; groupIndex < reqIumprGroupNum; groupIndex++ )
    {
        dataPos = groupIndex * DEM_IUMPR_RATIO_DATA_SIZE;
        IumprdataPtr[dataPos + DEM_IUMPR_POS5] = DEM_IUMPR_DATA_INITVALUE;
        IumprdataPtr[dataPos + DEM_IUMPR_POS6] = DEM_IUMPR_DATA_INITVALUE;
        IumprdataPtr[dataPos + DEM_IUMPR_POS7] = DEM_IUMPR_DATA_INITVALUE;
        IumprdataPtr[dataPos + DEM_IUMPR_POS8] = DEM_IUMPR_DATA_INITVALUE;
    }

    return ;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif  /* ( DEM_IUMPR_RATIO_SUPPORT == STD_OFF )    */
#endif  /* ( DEM_IUMPR_SUPPORT == STD_ON )      */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
