/* Dem_ConfigInfo_UserDefMem_OFF_c(v5-5-0)                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/ConfigInfo_UserDefMem_OFF/CODE                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/


/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_OFF )


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
/* Functions                                                                */
/****************************************************************************/

/****************************************************************************/
/* External Functions(PreInit section)                                      */
/****************************************************************************/
#define DEM_START_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>



#define DEM_STOP_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_CfgInfoUdm_CheckClearParameter                       */
/* Description   | check DTC,Format,Origin                                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCGroup :                                          */
/*               |        DTC                                               */
/*               | [in] DTCFormat :                                         */
/*               |        DTCFormat                                         */
/*               | [in] DTCOrigin :                                         */
/*               |        DTCOrigin                                         */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : parameter is OK                      */
/*               |        DEM_IRT_WRONG_DTC : DTC value not existing(in th- */
/*               |        is format)                                        */
/*               |        DEM_IRT_WRONG_DTCORIGIN : Wrong DTC origin        */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfoUdm_CheckClearParameter
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,    /* MISRA DEVIATION */
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,      /* MISRA DEVIATION */
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin       /* MISRA DEVIATION */
)
{
    /*  no UserDefinedMemory.       */
    return DEM_IRT_WRONG_DTCORIGIN;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_OFF )      */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
