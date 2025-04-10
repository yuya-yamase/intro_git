/* Dem_DTR_Callout_c(v5-0-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DTR_Callout/CODE                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_DTR_SUPPORT == STD_ON )
#include "Dem_DTR_Callout.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

#if ( DEM_DTR_FLOAT_SUPPORT == STD_ON )
typedef float32    Dem_DtrConvertType;
#define DEM_DTR_U16_UPPERLIMIT            ((Dem_DtrConvertType)65535.0F)
#define DEM_DTR_S16_UPPERLIMIT            ((Dem_DtrConvertType)32767.0F)
#define DEM_DTR_S16_LOWERLIMIT            ((Dem_DtrConvertType)-32768.0F)
#endif  /* ( DEM_DTR_FLOAT_SUPPORT == STD_ON )  */

#if ( DEM_DTR_FLOAT_SUPPORT == STD_OFF )
typedef sint32     Dem_DtrConvertType;
#define DEM_DTR_U16_UPPERLIMIT            ((Dem_DtrConvertType)65535)
#define DEM_DTR_S16_UPPERLIMIT            ((Dem_DtrConvertType)32767)
#define DEM_DTR_S16_LOWERLIMIT            ((Dem_DtrConvertType)-32768)
#endif  /* ( DEM_DTR_FLOAT_SUPPORT == STD_OFF ) */

#define DEM_DTR_SIGNED_LOWERLIMIT   ((Dem_u16_DTRValueStoreType)0x8000U)
#define DEM_DTR_UNSIGNED_LOWERLIMIT ((Dem_u16_DTRValueStoreType)0x0000U)
#define DEM_DTR_SIGNED_UPPERLIMIT   ((Dem_u16_DTRValueStoreType)0x7FFFU)
#define DEM_DTR_UNSIGNED_UPPERLIMIT ((Dem_u16_DTRValueStoreType)0xFFFFU)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>

static FUNC( Dem_u16_DTRValueStoreType, DEM_CODE_CALLOUT ) Dem_DTR_CalcConvertsLinear
(
    VAR( Dem_DtrConvertType, AUTOMATIC ) CompuN0DivD0,
    VAR( Dem_DtrConvertType, AUTOMATIC ) CompuN1DivD0,
    VAR( Dem_DtrConvertType, AUTOMATIC ) PhysVal,
    VAR( Dem_u08_DTRUasidType, AUTOMATIC ) DtrUasid
);

static FUNC( Dem_DtrConvertType, DEM_CODE_CALLOUT ) Dem_DTR_CnvRawDataToConvertType
(
    VAR( Dem_s32_DTRValueRawType, AUTOMATIC ) DTRRawData
);

#define DEM_STOP_SEC_CODE_CALLOUT
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
#define DEM_START_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_DTR_ConvertLinear                                    */
/* Description   | Converts linear.                                         */
/* Preconditions | none                                                     */
/* Parameters    | [in]  DTRConvertInputPtr  : DTR input data.              */
/*               | [out] DTRConvertOutputPtr : DTR output data.             */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE_CALLOUT ) Dem_DTR_ConvertLinear
(
    P2CONST( Dem_DTRConvertInputType, AUTOMATIC, AUTOMATIC ) DTRConvertInputPtr,
    P2VAR( Dem_DTRConvertOutputType, AUTOMATIC, AUTOMATIC ) DTRConvertOutputPtr
)
{
    VAR( Dem_DtrConvertType, AUTOMATIC ) cnvTestResult;
    VAR( Dem_DtrConvertType, AUTOMATIC ) cnvLowerLimit;
    VAR( Dem_DtrConvertType, AUTOMATIC ) cnvUpperLimit;
    VAR( Dem_DtrConvertType, AUTOMATIC ) cnvCompuN0DivD0;
    VAR( Dem_DtrConvertType, AUTOMATIC ) cnvCompuN1DivD0;
    VAR( Dem_u16_DTRValueStoreType, AUTOMATIC ) outTestResult;
    VAR( Dem_u16_DTRValueStoreType, AUTOMATIC ) outLowerLimit;
    VAR( Dem_u16_DTRValueStoreType, AUTOMATIC ) outUpperLimit;
    VAR( Dem_u08_DTRConvertInfoType, AUTOMATIC ) outConvertInfo;
    VAR( Dem_u08_DTRUasidType, AUTOMATIC ) uasid;
    VAR( Dem_DTRControlType, AUTOMATIC ) ctrlval;


    /*------------------------------------------------------------------------------*/
    /*  Convert data : Dem_s32_DTRValueRawType to  Dem_DtrConvertType.              */
    /*------------------------------------------------------------------------------*/
    cnvTestResult   =   Dem_DTR_CnvRawDataToConvertType( DTRConvertInputPtr->TestResult );
    cnvLowerLimit   =   Dem_DTR_CnvRawDataToConvertType( DTRConvertInputPtr->LowerLimit );
    cnvUpperLimit   =   Dem_DTR_CnvRawDataToConvertType( DTRConvertInputPtr->UpperLimit );
    cnvCompuN0DivD0 =   Dem_DTR_CnvRawDataToConvertType( DTRConvertInputPtr->CompuN0DivD0 );
    cnvCompuN1DivD0 =   Dem_DTR_CnvRawDataToConvertType( DTRConvertInputPtr->CompuN1DivD0 );

    /*------------------------------------------------------------------------------*/
    /*  Set input value.                                                            */
    /*------------------------------------------------------------------------------*/
    uasid           =   DTRConvertInputPtr->DtrUasid;
    ctrlval         =   DTRConvertInputPtr->Ctrlval;

    /*------------------------------------------------------------------------------*/
    /*  Initialize output value.                                                    */
    /*------------------------------------------------------------------------------*/
    outConvertInfo  =   DEM_DTR_TESTRESULT_NORMAL;

    if ( ctrlval == DEM_DTR_CTL_NO_MIN )
    {
        /*--------------------------------------------------------------------------*/
        /*  CtrlVal pattern : There is No Minimum limit.                            */
        /*--------------------------------------------------------------------------*/

        /*  Get result of comparison : TestResult and UpperLimit.                               */
        if ( cnvTestResult > cnvUpperLimit )
        {
            /*  Get convert information : TestResult has exceeded the upper limit.              */
            outConvertInfo = DEM_DTR_TESTRESULT_INVALID_UPPER;
        }

        /*  Converts linear :   Dem_DtrConvertType to Dem_u16_DTRValueStoreType.                */
        outTestResult = Dem_DTR_CalcConvertsLinear( cnvCompuN0DivD0, cnvCompuN1DivD0, cnvTestResult, uasid );
        outUpperLimit = Dem_DTR_CalcConvertsLinear( cnvCompuN0DivD0, cnvCompuN1DivD0, cnvUpperLimit, uasid );

        /*  Get the LowerLimit value when There is No Minimum limit.                            */
        if ( uasid >= DEM_DTR_UASID_SIGNED )
        {
            /*  Get signed limit value.                 */
            outLowerLimit = DEM_DTR_SIGNED_LOWERLIMIT;
        }
        else
        {
            /*  Get unsigned limit value.               */
            outLowerLimit = DEM_DTR_UNSIGNED_LOWERLIMIT;
        }
    }
    else if ( ctrlval == DEM_DTR_CTL_NO_MAX )
    {
        /*--------------------------------------------------------------------------*/
        /*  CtrlVal pattern : There is No Maximum limit.                            */
        /*--------------------------------------------------------------------------*/

        /*  Get result of comparison : TestResult and LowerLimit.                               */
        if ( cnvTestResult < cnvLowerLimit )
        {
            /*  Get convert information : TestResult has exceeded the lower limit.              */
            outConvertInfo = DEM_DTR_TESTRESULT_INVALID_LOWER;
        }

        /*  Converts linear :   Dem_DtrConvertType to Dem_u16_DTRValueStoreType.                */
        outTestResult = Dem_DTR_CalcConvertsLinear( cnvCompuN0DivD0, cnvCompuN1DivD0, cnvTestResult, uasid );
        outLowerLimit = Dem_DTR_CalcConvertsLinear( cnvCompuN0DivD0, cnvCompuN1DivD0, cnvLowerLimit, uasid );

        /*  Get the UpperLimit value when There is No Maximum limit.                            */
        if ( uasid >= DEM_DTR_UASID_SIGNED )
        {
            /*  Get signed limit value.                 */
            outUpperLimit = DEM_DTR_SIGNED_UPPERLIMIT;
        }
        else
        {
            /*  Get unsigned limit value.               */
            outUpperLimit = DEM_DTR_UNSIGNED_UPPERLIMIT;
        }
    }
    else
    {
        /*--------------------------------------------------------------------------*/
        /*  CtrlVal pattern : It has Minimum and Maximum limit.                     */
        /*--------------------------------------------------------------------------*/
        /*  ctrlval == DEM_DTR_CTL_NORMAL                                           */

        /*  Get result of comparison : TestResult and LowerLimit, TestResult and UpperLimit.    */
        if ( cnvTestResult < cnvLowerLimit )
        {
            /*  Get convert information : TestResult has exceeded the lower limit.              */
            outConvertInfo = DEM_DTR_TESTRESULT_INVALID_LOWER;
        }
        else if ( cnvTestResult > cnvUpperLimit )
        {
            /*  Get convert information : TestResult has exceeded the upper limit.              */
            outConvertInfo = DEM_DTR_TESTRESULT_INVALID_UPPER;
        }
        else
        {
            /*  No Process.     */
        }

        /*  Converts linear :   Dem_DtrConvertType to Dem_u16_DTRValueStoreType.                */
        outTestResult = Dem_DTR_CalcConvertsLinear( cnvCompuN0DivD0, cnvCompuN1DivD0, cnvTestResult, uasid );
        outLowerLimit = Dem_DTR_CalcConvertsLinear( cnvCompuN0DivD0, cnvCompuN1DivD0, cnvLowerLimit, uasid );
        outUpperLimit = Dem_DTR_CalcConvertsLinear( cnvCompuN0DivD0, cnvCompuN1DivD0, cnvUpperLimit, uasid );
    }

    /*------------------------------------------------------------------------------*/
    /*  Set value of Converts linear to output parameter.                           */
    /*------------------------------------------------------------------------------*/
    DTRConvertOutputPtr->TestResult     =   outTestResult;
    DTRConvertOutputPtr->LowerLimit     =   outLowerLimit;
    DTRConvertOutputPtr->UpperLimit     =   outUpperLimit;
    DTRConvertOutputPtr->ConvertInfo    =   outConvertInfo;

    return;
}


/****************************************************************************/
/* Function Name | Dem_DTR_CalcConvertsLinear                               */
/* Description   | Calculation Converts linear.                             */
/* Preconditions | none                                                     */
/* Parameters    | [in]  CompuN0DivD0: CompuNumerator0 / CompuDenominator0  */
/*               | [in]  CompuN1DivD0: CompuNumerator1 / CompuDenominator0  */
/*               | [in]  PhysVal     : phys                                 */
/*               | [in]  DtrUasid    : Unit and Scaling Id                  */
/* Return Value  | Dem_u16_DTRValueStoreType                                */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( Dem_u16_DTRValueStoreType, DEM_CODE_CALLOUT ) Dem_DTR_CalcConvertsLinear
(
    VAR( Dem_DtrConvertType, AUTOMATIC ) CompuN0DivD0,
    VAR( Dem_DtrConvertType, AUTOMATIC ) CompuN1DivD0,
    VAR( Dem_DtrConvertType, AUTOMATIC ) PhysVal,
    VAR( Dem_u08_DTRUasidType, AUTOMATIC ) DtrUasid
)
{
    VAR( Dem_DtrConvertType, AUTOMATIC ) compuFPhysVal;
    VAR( Dem_u16_DTRValueStoreType, AUTOMATIC ) convertLinearVal;

    /*------------------------------------------------------------------------------*/
    /*  Compute value.                                                              */
    /*      F(phys) = (N0 + N1*phys)/D0                                             */
    /*------------------------------------------------------------------------------*/
    compuFPhysVal = CompuN0DivD0 + ( CompuN1DivD0 * PhysVal );

    if ( DtrUasid >= DEM_DTR_UASID_SIGNED )
    {
        /*--------------------------------------------------------------------------*/
        /*  It's signed value.                                                      */
        /*--------------------------------------------------------------------------*/
        /*  Get result of comparison : compuFPhysVal and LowerLimit(signed 16bit), compuFPhysVal and UpperLimit(signed 16bit).    */
        if( compuFPhysVal > DEM_DTR_S16_UPPERLIMIT )
        {
            /*  conver linear value is Signed Upper limit value.        */
            convertLinearVal = DEM_DTR_SIGNED_UPPERLIMIT;
        }
        else if( compuFPhysVal < DEM_DTR_S16_LOWERLIMIT )
        {
            /*  convert linear value is Signed Lower limit value.       */
            convertLinearVal = DEM_DTR_SIGNED_LOWERLIMIT;
        }
        else
        {
            /*  convert linear value is conpute value.                  */
            convertLinearVal = (Dem_u16_DTRValueStoreType)((Dem_s16_DTRValueStoreType)compuFPhysVal);
        }
    }
    else
    {
        /*--------------------------------------------------------------------------*/
        /*  It's unsigned value.                                                    */
        /*--------------------------------------------------------------------------*/
        /*  Get result of comparison : compuFPhysVal and UpperLimit(unsigned 16bit).     */
        if( compuFPhysVal > DEM_DTR_U16_UPPERLIMIT )
        {
            /*  convert linear value is Unsigned Upper limit value.     */
            convertLinearVal = DEM_DTR_UNSIGNED_UPPERLIMIT;
        }
        else
        {
            /*  convert linear value is conpute value.                  */
            convertLinearVal = (Dem_u16_DTRValueStoreType)compuFPhysVal;
        }
    }
    return convertLinearVal;
}


/****************************************************************************/
/* Function Name | Dem_DTR_CnvRawDataToConvertType                          */
/* Description   | convert Dem_s32_DTRValueRawType to Dem_DtrConvertType.   */
/* Preconditions | none                                                     */
/* Parameters    | [in] RawData     : DTR Raw data.                         */
/* Return Value  | Dem_DtrConvertType                                       */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( Dem_DtrConvertType, DEM_CODE_CALLOUT ) Dem_DTR_CnvRawDataToConvertType
(
    VAR( Dem_s32_DTRValueRawType, AUTOMATIC ) DTRRawData
)
{
    P2VAR( void, AUTOMATIC, AUTOMATIC ) tmpCnvDataPtr;
    VAR( Dem_DtrConvertType, AUTOMATIC ) cnvData;
    VAR( Dem_s32_DTRValueRawType, AUTOMATIC ) rawData;

    rawData         =   DTRRawData;                                 /*  get Raw data.                               */
    tmpCnvDataPtr   =   (void *)&rawData;                           /*  get address of auto valiable in Raw data    */
    cnvData         =   (*((Dem_DtrConvertType *)tmpCnvDataPtr));   /*  cast to *(Dem_DtrConvertType *) data.       */

    return cnvData;
}

#define DEM_STOP_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>

#endif  /* ( DEM_DTR_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
