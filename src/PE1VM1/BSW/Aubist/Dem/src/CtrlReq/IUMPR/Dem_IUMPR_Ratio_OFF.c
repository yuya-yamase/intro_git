/* Dem_IUMPR_Ratio_OFF_c(v5-10-0)                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
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
/*               | [in] NODIGroupNum :                                      */
/*               |          Number Of Data Items GroupNum                   */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | no object changed.                                       */
/*   v5-10-0     | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IUMPR_Ratio_GetInfoTypeValue
(
#ifndef DEM_SIT_RANGE_CHECK
#else   /* DEM_SIT_RANGE_CHECK */
    VAR( uint8, AUTOMATIC ) BuffSize,
#endif  /* DEM_SIT_RANGE_CHECK */
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA )        IumprdataPtr,
    VAR( Dem_u08_IUMPRGroupIndexType, AUTOMATIC )   NODIGroupNum
)
{
    VAR( Dem_u08_IUMPRGroupIndexType, AUTOMATIC )   groupIndex;
    VAR( Dem_u08_IUMPRGroupIndexType, AUTOMATIC )   reqIumprGroupNum;
    VAR( uint8, AUTOMATIC )                         dataPos;

    reqIumprGroupNum                    = NODIGroupNum;
    for ( groupIndex = (Dem_u08_IUMPRGroupIndexType)0U; groupIndex < reqIumprGroupNum; groupIndex++ )
    {
        dataPos = groupIndex * DEM_IUMPR_RATIO_DATA_SIZE;
        IumprdataPtr[dataPos + DEM_IUMPR_POS5] = DEM_IUMPR_DATA_INITVALUE;/* [ARYCHK] BuffSize / 1 / dataPos+DEM_IUMPR_POS5 */
        IumprdataPtr[dataPos + DEM_IUMPR_POS6] = DEM_IUMPR_DATA_INITVALUE;/* [ARYCHK] BuffSize / 1 / dataPos+DEM_IUMPR_POS6 */
        IumprdataPtr[dataPos + DEM_IUMPR_POS7] = DEM_IUMPR_DATA_INITVALUE;/* [ARYCHK] BuffSize / 1 / dataPos+DEM_IUMPR_POS7 */
        IumprdataPtr[dataPos + DEM_IUMPR_POS8] = DEM_IUMPR_DATA_INITVALUE;/* [ARYCHK] BuffSize / 1 / dataPos+DEM_IUMPR_POS8 */
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
/*  v5-7-0         :2024-05-29                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
