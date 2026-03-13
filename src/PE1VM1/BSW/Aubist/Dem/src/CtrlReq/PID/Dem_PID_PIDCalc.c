/* Dem_PID_PIDCalc_c(v5-10-0)                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/PID_PIDCalc/CODE                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_NvM_Cfg.h"
#include "../../../cfg/Dem_Data_Cfg.h"
#include "../../../inc/Dem_Pm_PID.h"
#include "../../../inc/Dem_Pm_PID_PIDCalc.h"
#include "../../../inc/Dem_Rc_PIDMng.h"
#include "../../../inc/Dem_Pm_DataCtl_OBD.h"
#include "../../../usr/Dem_UserDTC_OBD_Callout.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_CmnLib_DataElement.h"
#include "Dem_PID_local.h"

#if ( DEM_PID_CALC_DEMINTERNALPID_SUPPORT == STD_ON )
#include "../../../cfg/Dem_MasterOBD_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_PID_DATAPOS0 ((uint8)0U)
#define DEM_PID_DATAPOS1 ((uint8)1U)

#define DEM_PID_CALCULATION_DATASIZE_DISTANCE  ((uint8)2U)
#define DEM_PID_CALCULATION_DATASIZE_TIMESES   ((uint8)2U)
#define DEM_PID_FRACTION_DATA_INITVALUE        ((Dem_u16_PIDCalcValueType)0x0000U)
#define DEM_PID_DATA_UPPER_LIMIT               ((Dem_u16_PIDCalcValueType)0xFFFFU)
#define DEM_PID_DATA_UPDATE_COUNT_INITIAL      ((Dem_u16_PIDCalcValueType)0x0000U)
#define DEM_PID_DATA_BITSHIFT_8                ((uint8)0x08U)
#define DEM_PID_DISTANCE_1KMVALUE              ((Dem_u32_PIDCalcValueType)1000U)
#define DEM_PID_TIMESES_1MINVALUE              ((Dem_u32_PIDCalcValueType)60U)
#define DEM_PID_DATA_MASK                      ((Dem_u16_PIDCalcValueType)0x00FFU)


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct {
    Dem_u16_PIDCalcValueType     FractionDistancePID21;
    Dem_u16_PIDCalcValueType     FractionDistancePID31;
    Dem_u16_PIDCalcValueType     FractionSESTimePID4D;
    Dem_u16_PIDCalcValueType     FractionSESTimePID4E;
    boolean    CalculationStatusByMILForPID21;
    boolean    CalculationStatusByMILForPID4D;
} Dem_PIDCalculationType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PID_GetDataForCalcDistance
(
    P2VAR( Dem_u16_PIDCalcValueType, AUTOMATIC, AUTOMATIC ) DistanceDataPtr
);
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PID_GetDataForCalcTimeSES
(
    P2VAR( Dem_u16_PIDCalcValueType, AUTOMATIC, AUTOMATIC ) TimeSESDataPtr
);
static FUNC( void, DEM_CODE ) Dem_PID_CalclateDataOfPID21
(
    VAR( Dem_u32_PIDCalcValueType, AUTOMATIC ) DistanceData
);
static FUNC( void, DEM_CODE ) Dem_PID_CalclateDataOfPID31
(
    VAR( Dem_u32_PIDCalcValueType, AUTOMATIC ) DistanceData
);
static FUNC( void, DEM_CODE ) Dem_PID_CalclateDataOfPID4D
(
    VAR( Dem_u16_PIDCalcValueType, AUTOMATIC ) TimeSESData
);
static FUNC( void, DEM_CODE ) Dem_PID_CalclateDataOfPID4E
(
    VAR( Dem_u16_PIDCalcValueType, AUTOMATIC ) TimeSESData
);
static FUNC( void, DEM_CODE ) Dem_PID_CalclateDistanceData
(
    VAR( Dem_u32_PIDCalcValueType, AUTOMATIC ) DistanceData,
    P2VAR( Dem_u16_PIDCalcValueType, AUTOMATIC, AUTOMATIC ) FractionDistancePtr,
    P2VAR( Dem_u16_PIDCalcValueType, AUTOMATIC, AUTOMATIC ) UpdateCountPtr
);
static FUNC( void, DEM_CODE ) Dem_PID_CalclateTimeSESData
(
    VAR( Dem_u16_PIDCalcValueType, AUTOMATIC ) TimeSESData,
    P2VAR( Dem_u16_PIDCalcValueType, AUTOMATIC, AUTOMATIC ) FractionTimeSESPtr,
    P2VAR( Dem_u16_PIDCalcValueType, AUTOMATIC, AUTOMATIC ) UpdateCountPtr
);
static FUNC( void, DEM_CODE ) Dem_PID_GetActiveStatus_MIL
(
    P2VAR( boolean, AUTOMATIC, AUTOMATIC )  IsActiveMILPtr
);
static FUNC( void, DEM_CODE ) Dem_PID_GetActiveStatus_MILAndConfirmedDTC_AtClearPID
(
    P2VAR( boolean, AUTOMATIC, AUTOMATIC )  IsActiveMILPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC )  IsActiveCDTCPtr
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( Dem_PIDCalculationType, DEM_VAR_NO_INIT ) Dem_PID_CalculationInfo;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_PID_Init                                             */
/* Description   | Initializes the value of PIDs                            */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PID_Init
( void )
{
    Dem_PID_CalculationInfo.FractionDistancePID21 = DEM_PID_FRACTION_DATA_INITVALUE;
    Dem_PID_CalculationInfo.FractionDistancePID31 = DEM_PID_FRACTION_DATA_INITVALUE;
    Dem_PID_CalculationInfo.FractionSESTimePID4D  = DEM_PID_FRACTION_DATA_INITVALUE;
    Dem_PID_CalculationInfo.FractionSESTimePID4E  = DEM_PID_FRACTION_DATA_INITVALUE;
    Dem_PID_CalculationInfo.CalculationStatusByMILForPID21 = ( boolean )TRUE;
    Dem_PID_CalculationInfo.CalculationStatusByMILForPID4D = ( boolean )TRUE;

    return;
}

/****************************************************************************/
/* Function Name | Dem_PID_Clear                                            */
/* Description   | Clear the value of PIDs                                  */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PID_Clear
( void )
{
    Dem_PID_ClearAllEventDisable();

    Dem_PIDMngC_ClearDataOfPID21();
    Dem_PIDMngC_ClearDataOfPID30();
    Dem_PIDMngC_ClearDataOfPID31();
    Dem_PIDMngC_ClearDataOfPID4D();
    Dem_PIDMngC_ClearDataOfPID4E();

    Dem_PID_CalculationInfo.FractionDistancePID31 = DEM_PID_FRACTION_DATA_INITVALUE;
    Dem_PID_CalculationInfo.FractionSESTimePID4E  = DEM_PID_FRACTION_DATA_INITVALUE;

    return;
}

/****************************************************************************/
/* Function Name | Dem_PID_UpdateDistanceInfo                               */
/* Description   | UpDate the Value of PID21/31                             */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PID_UpdateDistanceInfo
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_PIDCalcValueType, AUTOMATIC ) distanceData;

    retVal = Dem_PID_GetDataForCalcDistance( &distanceData );

    if( retVal == DEM_IRT_OK )
    {
        Dem_PID_CalclateDataOfPID21( (Dem_u32_PIDCalcValueType)distanceData );
        Dem_PID_CalclateDataOfPID31( (Dem_u32_PIDCalcValueType)distanceData );
    }
    else
    {
        /* No process */
    }
    return;
}

/****************************************************************************/
/* Function Name | Dem_PID_UpdateTimeSESInfo                                */
/* Description   | UpDate the Value of PID4D/4E                             */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PID_UpdateTimeSESInfo
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_PIDCalcValueType, AUTOMATIC ) TimeSESData;

    retVal = Dem_PID_GetDataForCalcTimeSES( &TimeSESData );

    if( retVal == DEM_IRT_OK )
    {
        Dem_PID_CalclateDataOfPID4D( TimeSESData );
        Dem_PID_CalclateDataOfPID4E( TimeSESData );
    }
    else
    {
        /* No process */
    }
    return;
}

/****************************************************************************/
/* Function Name | Dem_PID_GetDataForCalcDistance                           */
/* Description   | Get of distance information.                             */
/* Preconditions | none                                                     */
/* Parameters    | [out] DistanceDataPtr :                                  */
/*               |        The Buffer that stores distance information get   */
/*               |        from SW-C.                                        */
/* Return Value  | Dem_u08_InternalReturnType :                             */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PID_GetDataForCalcDistance
(
    P2VAR( Dem_u16_PIDCalcValueType, AUTOMATIC, AUTOMATIC ) DistanceDataPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( uint8, AUTOMATIC ) getDistanceData[DEM_PID_CALCULATION_DATASIZE_DISTANCE];
    VAR( Std_ReturnType, AUTOMATIC ) resultOfCallback;
    VAR( Dem_u16_DataElementClassIndexType, AUTOMATIC ) dataElementClassIndex;
    VAR( Dem_u16_DataElementClassIndexType, AUTOMATIC ) elementClassTableNum;
    P2CONST( AB_83_ConstV Dem_DataElementClassType, AUTOMATIC, DEM_CONFIG_DATA ) dataElementClassPtr;

    retVal = DEM_IRT_NG;
    dataElementClassIndex = Dem_CalculationDistanceTable.DemDataElementClassIndex;
    elementClassTableNum  = Dem_DataElementNum;

    if( dataElementClassIndex < elementClassTableNum )                                  /* [GUD:if]dataElementClassIndex */
    {
        dataElementClassPtr = &Dem_DataElementClassTable[dataElementClassIndex];        /* [GUD]dataElementClassIndex */

        resultOfCallback = Dem_DataElement_ReadData( dataElementClassPtr, getDistanceData, DEM_MONITORDATA_PID );

        if( resultOfCallback == (Std_ReturnType)E_OK )
        {
            *DistanceDataPtr = (Dem_u16_PIDCalcValueType)(( ((Dem_u16_PIDCalcValueType)getDistanceData[DEM_PID_DATAPOS0]) << DEM_PID_DATA_BITSHIFT_8  ) | ( ((Dem_u16_PIDCalcValueType)getDistanceData[DEM_PID_DATAPOS1]) )  );/* [ARYCHK] DEM_PID_CALCULATION_DATASIZE_DISTANCE / 1 / DEM_PID_DATAPOS0 *//* [ARYCHK] DEM_PID_CALCULATION_DATASIZE_DISTANCE / 1 / DEM_PID_DATAPOS1 */
            retVal = DEM_IRT_OK;
        }
        else
        {
            /* No process */
        }
    }
    else
    {
        /* No process */
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_PID_GetDataForCalcTimeSES                            */
/* Description   | Get of TimeSES information.                              */
/* Preconditions | none                                                     */
/* Parameters    | [out] TimeSESDataPtr  :                                  */
/*               |        The Buffer that stores TimeSES information get    */
/*               |        from SW-C.                                        */
/* Return Value  | Dem_u08_InternalReturnType :                             */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PID_GetDataForCalcTimeSES
(
    P2VAR( Dem_u16_PIDCalcValueType, AUTOMATIC, AUTOMATIC ) TimeSESDataPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( uint8, AUTOMATIC ) getTimeSESData[DEM_PID_CALCULATION_DATASIZE_TIMESES];
    VAR( Std_ReturnType, AUTOMATIC ) resultOfCallback;
    VAR( Dem_u16_DataElementClassIndexType, AUTOMATIC ) dataElementClassIndex;
    VAR( Dem_u16_DataElementClassIndexType, AUTOMATIC ) elementClassTableNum;
    P2CONST( AB_83_ConstV Dem_DataElementClassType, AUTOMATIC, DEM_CONFIG_DATA ) dataElementClassPtr;

    retVal = DEM_IRT_NG;
    dataElementClassIndex = Dem_CalculationTimeSESTable.DemDataElementClassIndex;
    elementClassTableNum  = Dem_DataElementNum;

    if( dataElementClassIndex < elementClassTableNum )                              /* [GUD:if]dataElementClassIndex */
    {
        dataElementClassPtr = &Dem_DataElementClassTable[dataElementClassIndex];    /* [GUD]dataElementClassIndex */

        resultOfCallback = Dem_DataElement_ReadData(dataElementClassPtr, getTimeSESData , DEM_MONITORDATA_PID);

        if( resultOfCallback == (Std_ReturnType)E_OK )
        {
            *TimeSESDataPtr = (Dem_u16_PIDCalcValueType)((Dem_u16_PIDCalcValueType)( ((Dem_u16_PIDCalcValueType)getTimeSESData[DEM_PID_DATAPOS0]) << DEM_PID_DATA_BITSHIFT_8  ) | ((Dem_u16_PIDCalcValueType)getTimeSESData[DEM_PID_DATAPOS1])   );/* [ARYCHK] DEM_PID_CALCULATION_DATASIZE_TIMESES / 1 / DEM_PID_DATAPOS0 *//* [ARYCHK] DEM_PID_CALCULATION_DATASIZE_TIMESES / 1 / DEM_PID_DATAPOS1 */
            retVal = DEM_IRT_OK;
        }
        else
        {
            /* No process */
        }
    }
    else
    {
        /* No process */
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_PID_CalclateDataOfPID21                              */
/* Description   | Service to calculate the value of PID21                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] DistanceData :                                      */
/*               |        distance information                              */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_PID_CalclateDataOfPID21
(
    VAR( Dem_u32_PIDCalcValueType, AUTOMATIC ) DistanceData
)
{
    VAR( Dem_u16_PIDCalcValueType, AUTOMATIC )  convertPIDValue;
    VAR( Dem_u16_PIDCalcValueType, AUTOMATIC )  updateCount;
    VAR( uint8, AUTOMATIC )   pidValue[DEM_PID21_SIZE];
    VAR( boolean, AUTOMATIC )  isActiveMIL;

    updateCount = DEM_PID_DATA_UPDATE_COUNT_INITIAL;

    /*  get active status.          */
    isActiveMIL =   (boolean)FALSE;
    Dem_PID_GetActiveStatus_MIL( &isActiveMIL );

    if( isActiveMIL == (boolean)TRUE )
    {
        if( Dem_PID_CalculationInfo.CalculationStatusByMILForPID21 == ( boolean )FALSE )
        {
            Dem_PID_CalculationInfo.FractionDistancePID21 = DEM_PID_FRACTION_DATA_INITVALUE;

            Dem_PIDMngC_ClearDataOfPID21();

            Dem_PID_CalculationInfo.CalculationStatusByMILForPID21 = ( boolean )TRUE;
        }
        else
        {
           Dem_PID_CalclateDistanceData( DistanceData, &Dem_PID_CalculationInfo.FractionDistancePID21, &updateCount);

           if( updateCount != DEM_PID_DATA_UPDATE_COUNT_INITIAL )
           {
               Dem_PIDMngC_ReadDataOfPID21( pidValue );
               convertPIDValue = (Dem_u16_PIDCalcValueType)pidValue[DEM_PID_DATAPOS0] << DEM_PID_DATA_BITSHIFT_8;/* [ARYCHK] DEM_PID21_SIZE / 1 / DEM_PID_DATAPOS0 */
               convertPIDValue |= (Dem_u16_PIDCalcValueType)pidValue[DEM_PID_DATAPOS1];/* [ARYCHK] DEM_PID21_SIZE / 1 / DEM_PID_DATAPOS1 */
               if( convertPIDValue != DEM_PID_DATA_UPPER_LIMIT)
               {
                   if( (Dem_u32_PIDCalcValueType)((Dem_u32_PIDCalcValueType)convertPIDValue + (Dem_u32_PIDCalcValueType)updateCount) > (Dem_u32_PIDCalcValueType)DEM_PID_DATA_UPPER_LIMIT )        /*  no wrap around      */
                   {
                       convertPIDValue = DEM_PID_DATA_UPPER_LIMIT;
                   }
                   else
                   {
                       convertPIDValue = convertPIDValue + updateCount;
                   }
                   pidValue[DEM_PID_DATAPOS0] = (uint8)( convertPIDValue >> DEM_PID_DATA_BITSHIFT_8 );/* [ARYCHK] DEM_PID21_SIZE / 1 / DEM_PID_DATAPOS0 */
                   pidValue[DEM_PID_DATAPOS1] = (uint8)( convertPIDValue & DEM_PID_DATA_MASK );/* [ARYCHK] DEM_PID21_SIZE / 1 / DEM_PID_DATAPOS1 */
                   Dem_PIDMngC_SetDataOfPID21( pidValue );
               }
               else
               {
                    /* No process */
               }
           }
           else
           {
               /* No process */
           }
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_PID_CalclateDataOfPID31                              */
/* Description   | Service to calculate the value of PID31                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] DistanceData :                                      */
/*               |        distance information                              */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_PID_CalclateDataOfPID31
(
    VAR( Dem_u32_PIDCalcValueType, AUTOMATIC ) DistanceData
)
{
    VAR( Dem_u16_PIDCalcValueType, AUTOMATIC ) convertPIDValue;
    VAR( Dem_u16_PIDCalcValueType, AUTOMATIC ) updateCount;
    VAR( uint8, AUTOMATIC )  pidValue[DEM_PID31_SIZE];

    updateCount = DEM_PID_DATA_UPDATE_COUNT_INITIAL;
    Dem_PID_CalclateDistanceData( DistanceData, &Dem_PID_CalculationInfo.FractionDistancePID31, &updateCount);

    if( updateCount != DEM_PID_DATA_UPDATE_COUNT_INITIAL )
    {
        Dem_PIDMngC_ReadDataOfPID31( pidValue );
        convertPIDValue = (Dem_u16_PIDCalcValueType)pidValue[DEM_PID_DATAPOS0] << DEM_PID_DATA_BITSHIFT_8;/* [ARYCHK] DEM_PID31_SIZE / 1 / DEM_PID_DATAPOS0 */
        convertPIDValue |= (Dem_u16_PIDCalcValueType)pidValue[DEM_PID_DATAPOS1];/* [ARYCHK] DEM_PID31_SIZE / 1 / DEM_PID_DATAPOS1 */
        if( convertPIDValue != DEM_PID_DATA_UPPER_LIMIT)
        {
            if( (Dem_u32_PIDCalcValueType)((Dem_u32_PIDCalcValueType)convertPIDValue + (Dem_u32_PIDCalcValueType)updateCount) > (Dem_u32_PIDCalcValueType)DEM_PID_DATA_UPPER_LIMIT )        /*  no wrap around      */
            {
                convertPIDValue = DEM_PID_DATA_UPPER_LIMIT;
            }
            else
            {
                convertPIDValue = convertPIDValue + updateCount;
            }
            pidValue[DEM_PID_DATAPOS0] = (uint8)( convertPIDValue >> DEM_PID_DATA_BITSHIFT_8 );/* [ARYCHK] DEM_PID31_SIZE / 1 / DEM_PID_DATAPOS0 */
            pidValue[DEM_PID_DATAPOS1] = (uint8)( convertPIDValue & DEM_PID_DATA_MASK );/* [ARYCHK] DEM_PID31_SIZE / 1 / DEM_PID_DATAPOS1 */
            Dem_PIDMngC_SetDataOfPID31( pidValue );
        }
        else
        {
             /* No process */
        }
    }
    else
    {
        /* No process */
    }
    return;
}

/****************************************************************************/
/* Function Name | Dem_PID_CalclateDataOfPID4D                              */
/* Description   | Service to calculate the value of PID4D                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] TimeSESData :                                       */
/*               |        TimeSES information                               */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_PID_CalclateDataOfPID4D
(
    VAR( Dem_u16_PIDCalcValueType, AUTOMATIC ) TimeSESData
)
{
    VAR( Dem_u16_PIDCalcValueType, AUTOMATIC )  convertPIDValue;
    VAR( Dem_u16_PIDCalcValueType, AUTOMATIC )  updateCount;
    VAR( uint8, AUTOMATIC )   pidValue[DEM_PID4D_SIZE];
    VAR( boolean, AUTOMATIC )  isActiveMIL;

    updateCount = DEM_PID_DATA_UPDATE_COUNT_INITIAL;

    /*  get active status.          */
    isActiveMIL =   (boolean)FALSE;
    Dem_PID_GetActiveStatus_MIL( &isActiveMIL );
    if( isActiveMIL == (boolean)TRUE )
    {
        if( Dem_PID_CalculationInfo.CalculationStatusByMILForPID4D == ( boolean )FALSE )
        {
            Dem_PID_CalculationInfo.FractionSESTimePID4D = DEM_PID_FRACTION_DATA_INITVALUE;

            Dem_PIDMngC_ClearDataOfPID4D();

            Dem_PID_CalculationInfo.CalculationStatusByMILForPID4D = ( boolean )TRUE;
        }
        else
        {
            Dem_PID_CalclateTimeSESData( TimeSESData, &Dem_PID_CalculationInfo.FractionSESTimePID4D, &updateCount);

            if( updateCount != DEM_PID_DATA_UPDATE_COUNT_INITIAL )
            {
                Dem_PIDMngC_ReadDataOfPID4D( pidValue );
                convertPIDValue = (Dem_u16_PIDCalcValueType)pidValue[DEM_PID_DATAPOS0] << DEM_PID_DATA_BITSHIFT_8;/* [ARYCHK] DEM_PID4D_SIZE / 1 / DEM_PID_DATAPOS0 */
                convertPIDValue |= (Dem_u16_PIDCalcValueType)pidValue[DEM_PID_DATAPOS1];/* [ARYCHK] DEM_PID4D_SIZE / 1 / DEM_PID_DATAPOS1 */
                if( convertPIDValue != DEM_PID_DATA_UPPER_LIMIT )
                {
                    if( (Dem_u32_PIDCalcValueType)((Dem_u32_PIDCalcValueType)convertPIDValue + (Dem_u32_PIDCalcValueType)updateCount) > (Dem_u32_PIDCalcValueType)DEM_PID_DATA_UPPER_LIMIT )        /*  no wrap around      */
                    {
                        convertPIDValue = DEM_PID_DATA_UPPER_LIMIT;
                    }
                    else
                    {
                        convertPIDValue = convertPIDValue + updateCount;
                    }
                    pidValue[DEM_PID_DATAPOS0] = (uint8)( convertPIDValue >> DEM_PID_DATA_BITSHIFT_8 );/* [ARYCHK] DEM_PID4D_SIZE / 1 / DEM_PID_DATAPOS0 */
                    pidValue[DEM_PID_DATAPOS1] = (uint8)( convertPIDValue & DEM_PID_DATA_MASK );/* [ARYCHK] DEM_PID4D_SIZE / 1 / DEM_PID_DATAPOS1 */
                    Dem_PIDMngC_SetDataOfPID4D( pidValue );
                }
                else
                {
                     /* No process */
                }
            }
            else
            {
                /* No process */
            }
        }

    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_PID_CalclateDataOfPID4E                              */
/* Description   | Service to calculate the value of PID4E                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] TimeSESData :                                       */
/*               |        TimeSES information                               */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_PID_CalclateDataOfPID4E
(
    VAR( Dem_u16_PIDCalcValueType, AUTOMATIC ) TimeSESData
)
{
    VAR( Dem_u16_PIDCalcValueType, AUTOMATIC ) convertPIDValue;
    VAR( Dem_u16_PIDCalcValueType, AUTOMATIC ) updateCount;
    VAR( uint8, AUTOMATIC )  pidValue[DEM_PID4E_SIZE];

    updateCount = DEM_PID_DATA_UPDATE_COUNT_INITIAL;
    Dem_PID_CalclateTimeSESData( TimeSESData, &Dem_PID_CalculationInfo.FractionSESTimePID4E, &updateCount);

    if( updateCount != DEM_PID_DATA_UPDATE_COUNT_INITIAL )
    {
        Dem_PIDMngC_ReadDataOfPID4E( pidValue );
        convertPIDValue = (Dem_u16_PIDCalcValueType)pidValue[DEM_PID_DATAPOS0] << DEM_PID_DATA_BITSHIFT_8;/* [ARYCHK] DEM_PID4E_SIZE / 1 / DEM_PID_DATAPOS0 */
        convertPIDValue |= (Dem_u16_PIDCalcValueType)pidValue[DEM_PID_DATAPOS1];/* [ARYCHK] DEM_PID4E_SIZE / 1 / DEM_PID_DATAPOS1 */
        if( convertPIDValue != DEM_PID_DATA_UPPER_LIMIT )
        {
            if( (Dem_u32_PIDCalcValueType)((Dem_u32_PIDCalcValueType)convertPIDValue + (Dem_u32_PIDCalcValueType)updateCount) > (Dem_u32_PIDCalcValueType)DEM_PID_DATA_UPPER_LIMIT )        /*  no wrap around      */
            {
                convertPIDValue = DEM_PID_DATA_UPPER_LIMIT;
            }
            else
            {
                convertPIDValue = convertPIDValue + updateCount;
            }
            pidValue[DEM_PID_DATAPOS0] = (uint8)( convertPIDValue >> DEM_PID_DATA_BITSHIFT_8 );/* [ARYCHK] DEM_PID4E_SIZE / 1 / DEM_PID_DATAPOS0 */
            pidValue[DEM_PID_DATAPOS1] = (uint8)( convertPIDValue & DEM_PID_DATA_MASK );/* [ARYCHK] DEM_PID4E_SIZE / 1 / DEM_PID_DATAPOS1 */
            Dem_PIDMngC_SetDataOfPID4E( pidValue );
        }
        else
        {
             /* No process */
        }
    }
    else
    {
        /* No process */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_PID_CalclateDistanceData                             */
/* Description   | PID data update value calculation                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] DistanceData :                                      */
/*               |        Distance Information                              */
/*               | [in/out] PreviousValuePtr :                              */
/*               |        Distance Information Previous Value               */
/*               | [in/out] FractionDistancePtr :                           */
/*               |        Distance Information Fraction Value               */
/*               | [out] UpdateCountptr :                                   */
/*               |        PID Data Update Count                             */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_PID_CalclateDistanceData
(
    VAR( Dem_u32_PIDCalcValueType, AUTOMATIC ) DistanceData,
    P2VAR( Dem_u16_PIDCalcValueType, AUTOMATIC, AUTOMATIC ) FractionDistancePtr,
    P2VAR( Dem_u16_PIDCalcValueType, AUTOMATIC, AUTOMATIC ) UpdateCountPtr
)
{
    VAR( Dem_u16_PIDCalcValueType, AUTOMATIC ) fractionDistance;
    VAR( Dem_u32_PIDCalcValueType, AUTOMATIC ) fractionTotalValue;
    VAR( Dem_u16_PIDCalcValueType, AUTOMATIC ) updateCount;

    updateCount = DEM_PID_DATA_UPDATE_COUNT_INITIAL;
    fractionDistance = *FractionDistancePtr;
    fractionTotalValue = (Dem_u32_PIDCalcValueType)( DistanceData + (Dem_u32_PIDCalcValueType)fractionDistance );     /*  no wrap around      */

    while( fractionTotalValue >= DEM_PID_DISTANCE_1KMVALUE )
    {
        fractionTotalValue -= DEM_PID_DISTANCE_1KMVALUE;
        updateCount = updateCount + (Dem_u16_PIDCalcValueType)1U;
    }

    *FractionDistancePtr = (Dem_u16_PIDCalcValueType)fractionTotalValue;
    *UpdateCountPtr = updateCount;

    return ;
}
/****************************************************************************/
/* Function Name | Dem_PID_CalclateTimeSESData                              */
/* Description   | PID data update value calculation                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] TimeSESData :                                       */
/*               |        TimeSES Information                               */
/*               | [in/out] FractionTimeSESPtr :                            */
/*               |        TimeSES Information Fraction Value                */
/*               | [out] UpdateCount :                                      */
/*               |        PID Data Update Count                             */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_PID_CalclateTimeSESData
(
    VAR( Dem_u16_PIDCalcValueType, AUTOMATIC ) TimeSESData,
    P2VAR( Dem_u16_PIDCalcValueType, AUTOMATIC, AUTOMATIC ) FractionTimeSESPtr,
    P2VAR( Dem_u16_PIDCalcValueType, AUTOMATIC, AUTOMATIC ) UpdateCountPtr
)
{
    VAR( Dem_u32_PIDCalcValueType, AUTOMATIC ) calcTotalTimeSES;
    VAR( Dem_u16_PIDCalcValueType, AUTOMATIC ) fractionTimeSES;
    VAR( Dem_u16_PIDCalcValueType, AUTOMATIC ) updateCount;

    updateCount = DEM_PID_DATA_UPDATE_COUNT_INITIAL;
    fractionTimeSES = *FractionTimeSESPtr;
    calcTotalTimeSES = (Dem_u32_PIDCalcValueType)( (Dem_u32_PIDCalcValueType)TimeSESData + (Dem_u32_PIDCalcValueType)fractionTimeSES );     /*  no wrap around      */

    while( calcTotalTimeSES >= DEM_PID_TIMESES_1MINVALUE )
    {
        calcTotalTimeSES -= DEM_PID_TIMESES_1MINVALUE;
        updateCount = updateCount + (Dem_u16_PIDCalcValueType)1U;
    }
    *FractionTimeSESPtr = (Dem_u16_PIDCalcValueType)calcTotalTimeSES;
    *UpdateCountPtr = updateCount;

    return ;
}

/****************************************************************************/
/* Function Name | Dem_PID_ConfirmedDTCClear                                */
/* Description   | Judgment of existence of ConfirmedDTC. If there is no    */
/*               | ConfirmedDTC, clear the PID.                             */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PID_ConfirmedDTCClear
( void )
{
    VAR( boolean, AUTOMATIC )  isActiveMIL;
    VAR( boolean, AUTOMATIC )  isActiveCDTC;

    isActiveMIL         =   (boolean)FALSE;
    Dem_PID_GetActiveStatus_MILAndConfirmedDTC_AtClearPID( &isActiveMIL, &isActiveCDTC );

    /*  Confirmed DTC           */
    if( isActiveCDTC == (boolean)FALSE )
    {
        Dem_PIDMngC_ClearDataOfPID21();
        Dem_PIDMngC_ClearDataOfPID4D();
    }

    /*   MIL Status             */
    if( isActiveMIL == (boolean)FALSE )
    {
        Dem_PID_CalculationInfo.CalculationStatusByMILForPID21 = ( boolean )FALSE;
        Dem_PID_CalculationInfo.CalculationStatusByMILForPID4D = ( boolean )FALSE;
    }

    return;
}

#if ( DEM_PID21AND4D_CALCCONDITION_CDTC_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_PID_GetActiveStatus_MIL                              */
/* Description   | get MIL status is active or not.                         */
/* Preconditions | none                                                     */
/* Parameters    | [out] IsActiveMILPtr                                     */
/*               |          TRUE    :   MIL is active.                      */
/*               |          FALSE   :   MIL is not active.                  */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_PID_GetActiveStatus_MIL
(
    P2VAR( boolean, AUTOMATIC, AUTOMATIC )  IsActiveMILPtr
)
{
    VAR( boolean, AUTOMATIC )  isActiveMIL;

    Dem_Data_GetOBDDTCActiveStatus_CDTCAndMIL_forCalcPID( NULL_PTR, &isActiveMIL );

    *IsActiveMILPtr =   isActiveMIL;

    return ;
}

/****************************************************************************/
/* Function Name | Dem_PID_GetActiveStatus_MILAndConfirmedDTC_AtClearPID    */
/* Description   | get MIL status is active or not.                         */
/* Preconditions | none                                                     */
/* Parameters    | [out] IsActiveMILPtr                                     */
/*               |          TRUE    :   MIL is active.                      */
/*               |          FALSE   :   MIL is not active.                  */
/*               | [out] IsActiveCDTCPtr                                    */
/*               |          TRUE    :   ConfirmedDTC is active.             */
/*               |          FALSE   :   ConfirmedDTC is not active.         */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_PID_GetActiveStatus_MILAndConfirmedDTC_AtClearPID
(
    P2VAR( boolean, AUTOMATIC, AUTOMATIC )  IsActiveMILPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC )  IsActiveCDTCPtr
)
{
    VAR( boolean, AUTOMATIC )  isActiveMIL;
    VAR( boolean, AUTOMATIC )  isActiveCDTC;
    VAR( Dem_u08_UserDTCNumType, AUTOMATIC )   numberOfUserOBDDTC;

    numberOfUserOBDDTC = (Dem_u08_UserDTCNumType)0U;

    /*  get OBD event's active status : CDTC and MIL.       */
    Dem_Data_GetOBDDTCActiveStatus_CDTCAndMIL_forCalcPID( &isActiveCDTC, &isActiveMIL );

    Dem_GetNumberOfUserDTC(DEM_DTC_KIND_EMISSION_REL_DTCS, &numberOfUserOBDDTC );
    if ( numberOfUserOBDDTC > (Dem_u08_UserDTCNumType)0U )
    {
        isActiveCDTC    =   (boolean)TRUE;
    }

    *IsActiveMILPtr  =   isActiveMIL;
    *IsActiveCDTCPtr =   isActiveCDTC;

    return ;
}
#endif  /* ( DEM_PID21AND4D_CALCCONDITION_CDTC_SUPPORT == STD_OFF )     */

#if ( DEM_PID21AND4D_CALCCONDITION_CDTC_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_PID_GetActiveStatus_MIL                              */
/* Description   | get ConfirmedDTC status(insted of MIL) is active or not. */
/* Preconditions | none                                                     */
/* Parameters    | [out] IsActiveMILPtr                                     */
/*               |          TRUE    :   ConfirmedDTC is active.             */
/*               |          FALSE   :   ConfirmedDTC is not active.         */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_PID_GetActiveStatus_MIL
(
    P2VAR( boolean, AUTOMATIC, AUTOMATIC )  IsActiveMILPtr
)
{
    VAR( boolean, AUTOMATIC )  isActiveCDTC;
    VAR( Dem_u08_UserDTCNumType, AUTOMATIC )   numberOfUserOBDDTC;

    Dem_Data_GetOBDDTCActiveStatus_CDTCAndMIL_forCalcPID( &isActiveCDTC, NULL_PTR );

    numberOfUserOBDDTC = (Dem_u08_UserDTCNumType)0U;
    Dem_GetNumberOfUserDTC(DEM_DTC_KIND_EMISSION_REL_DTCS, &numberOfUserOBDDTC );
    if ( numberOfUserOBDDTC > (Dem_u08_UserDTCNumType)0U )
    {
        isActiveCDTC    =   (boolean)TRUE;
    }
    *IsActiveMILPtr =   isActiveCDTC;

    return ;
}

/****************************************************************************/
/* Function Name | Dem_PID_GetActiveStatus_MILAndConfirmedDTC_AtClearPID    */
/* Description   | get ConfirmedDTC status(insted of MIL) is active or not.*/
/* Preconditions | none                                                     */
/* Parameters    | [out] IsActiveMILPtr                                     */
/*               |          TRUE    :   ConfirmedDTC is active.             */
/*               |          FALSE   :   ConfirmedDTC is not active.         */
/*               | [out] IsActiveCDTCPtr                                    */
/*               |          TRUE    :   ConfirmedDTC is active.             */
/*               |          FALSE   :   ConfirmedDTC is not active.         */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.based on Dem_PID_GetActiveStatus_MILAndConfirmedDTC_AtClearPID. */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_PID_GetActiveStatus_MILAndConfirmedDTC_AtClearPID
(
    P2VAR( boolean, AUTOMATIC, AUTOMATIC )  IsActiveMILPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC )  IsActiveCDTCPtr
)
{
    VAR( boolean, AUTOMATIC )  isActiveCDTC;
    VAR( Dem_u08_UserDTCNumType, AUTOMATIC )   numberOfUserOBDDTC;

    Dem_Data_GetOBDDTCActiveStatus_CDTCAndMIL_forCalcPID( &isActiveCDTC, NULL_PTR );

    numberOfUserOBDDTC = (Dem_u08_UserDTCNumType)0U;
    Dem_GetNumberOfUserDTC(DEM_DTC_KIND_EMISSION_REL_DTCS, &numberOfUserOBDDTC );
    if ( numberOfUserOBDDTC > (Dem_u08_UserDTCNumType)0U )
    {
        isActiveCDTC    =   (boolean)TRUE;
    }

    *IsActiveMILPtr  =   isActiveCDTC;
    *IsActiveCDTCPtr =   isActiveCDTC;

    return ;
}
#endif  /* ( DEM_PID21AND4D_CALCCONDITION_CDTC_SUPPORT == STD_ON )      */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_PID_CALC_DEMINTERNALPID_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
