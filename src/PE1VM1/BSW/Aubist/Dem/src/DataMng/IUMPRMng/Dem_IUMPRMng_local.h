/* Dem_IUMPRMng_local_h(v5-3-0)                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/IUMPRMng_local/HEADER                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_IUMPRMNG_LOCAL_H
#define DEM_IUMPRMNG_LOCAL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

#if ( DEM_IUMPR_SUPPORT == STD_ON )

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_IUMPR_GENDEN_IGCC_REC_INDEX         ((Dem_u16_IUMPRIndexType)0x00U) /*  General record          */

#if ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )
#define DEM_IUMPR_RATIO_REC_START_INDEX         ((Dem_u16_IUMPRIndexType)0x01U) /*  start of Ratio record   */
#endif  /* ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )    */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct
{
    uint16    CommonCounter1;
    uint16    CommonCounter2;
    uint8     CommonCondition1;
    uint8     CommonCondition2;
    uint8     CommonCondition3;
    uint8     CommonCondition4;

} Dem_IUMPRCommonRecordInternalType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )

FUNC( void, DEM_CODE ) Dem_IUMPRMng_Ratio_ClearCondition
( void );

#endif  /* ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )    */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_IUMPR_SUPPORT == STD_ON )    */

#endif /* DEM_IUMPRMNG_LOCAL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
