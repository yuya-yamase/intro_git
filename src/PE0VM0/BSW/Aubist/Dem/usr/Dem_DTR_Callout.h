/* Dem_DTR_Callout_h(v5-0-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DTR_Callout/HEADER                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_DTR_CALLOUT_H
#define DEM_DTR_CALLOUT_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_DTR_SUPPORT == STD_ON )
/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
typedef uint8        Dem_u08_DTRConvertInfoType;               /*  for DTR result of check TestResult type      */
#define DEM_DTR_TESTRESULT_NORMAL        ((Dem_u08_DTRConvertInfoType)0x00U)
#define DEM_DTR_TESTRESULT_INVALID_LOWER ((Dem_u08_DTRConvertInfoType)0x01U)
#define DEM_DTR_TESTRESULT_INVALID_UPPER ((Dem_u08_DTRConvertInfoType)0x02U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct {

    Dem_s32_DTRValueRawType         TestResult;
    Dem_s32_DTRValueRawType         LowerLimit;
    Dem_s32_DTRValueRawType         UpperLimit;
    Dem_s32_DTRValueRawType         CompuN0DivD0;
    Dem_s32_DTRValueRawType         CompuN1DivD0;
    Dem_u08_DTRUasidType            DtrUasid;
    Dem_DTRControlType              Ctrlval;

} Dem_DTRConvertInputType;

typedef struct {

    Dem_u16_DTRValueStoreType       TestResult;
    Dem_u16_DTRValueStoreType       LowerLimit;
    Dem_u16_DTRValueStoreType       UpperLimit;
    Dem_u08_DTRConvertInfoType      ConvertInfo;

} Dem_DTRConvertOutputType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>

FUNC( void, DEM_CODE_CALLOUT ) Dem_DTR_ConvertLinear
(
    P2CONST( Dem_DTRConvertInputType, AUTOMATIC, AUTOMATIC ) DTRConvertInputPtr,
    P2VAR( Dem_DTRConvertOutputType, AUTOMATIC, AUTOMATIC ) DTRConvertOutputPtr
);

#define DEM_STOP_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>


#endif  /* ( DEM_DTR_SUPPORT == STD_ON )    */

#endif /* DEM_DTR_CALLOUT_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
