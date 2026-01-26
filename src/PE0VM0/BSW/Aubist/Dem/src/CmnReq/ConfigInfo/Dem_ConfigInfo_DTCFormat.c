/* Dem_ConfigInfo_c(v5-5-0)                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/ConfigInfo/CODE                                       */
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

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfo_CheckDTCGroup
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup
);
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfo_CheckDTCSettingGroup
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup
);
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfo_CheckDTCSettingKind
(
    VAR( Dem_DTCKindType, AUTOMATIC ) DTCKind
);

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfo_CheckDTCKind
(
    VAR( Dem_DTCKindType, AUTOMATIC ) DTCKind
);

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
/* Function Name | Dem_CfgInfo_CheckClearParameter                          */
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
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfo_CheckClearParameter
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retValGroup;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retValFormat;

    retVal  =   DEM_IRT_WRONG_DTC;

    /* Checks the specified DTCOrigin type. */
    if( DTCOrigin == DEM_DTC_ORIGIN_PRIMARY_MEMORY )
    {
        /*  check DTC group.        */
        retValGroup =   Dem_CfgInfo_CheckDTCGroup( DTCGroup );              /*  DEM_IRT_OK / DEM_IRT_WRONG_DTC  */

        if ( retValGroup == DEM_IRT_OK )
        {
            retValFormat    =   Dem_CfgInfoPm_CheckDTCFormat( DTCFormat );  /*  DEM_IRT_OK / DEM_IRT_WRONG_DTC  */
            if ( retValFormat == DEM_IRT_OK )
            {
                retVal = DEM_IRT_OK;
            }
        }
    }
    else
    {
        /*  check UserDefinedMemory.        */
        retVal  =   Dem_CfgInfoUdm_CheckClearParameter( DTCGroup, DTCFormat, DTCOrigin );       /*  DEM_IRT_OK / DEM_IRT_WRONG_DTCORIGIN / DEM_IRT_WRONG_DTC  */
    }
    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_CfgInfo_CheckDTCSettingParameter                     */
/* Description   | Checks the parameter of control DTC setting.             */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCGroup :                                          */
/*               |        Defineds DTC group for the check.                 */
/*               | [in] DTCKind :                                           */
/*               |        Defineds DTC kind for the check.                  */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : A parameter of the DTC setting cont- */
/*               |        rol is right                                      */
/*               |        DEM_IRT_WRONG_DTCGROUP :  DTC setting control no- */
/*               |        t successful because group of DTC was wrong       */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfo_CheckDTCSettingParameter
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_DTCKindType, AUTOMATIC ) DTCKind
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultChkGrp;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultChkKind;

    retVal = DEM_IRT_WRONG_DTCGROUP;

    /* Checks DTC Group. */
    resultChkGrp = Dem_CfgInfo_CheckDTCSettingGroup( DTCGroup );

    if( resultChkGrp == DEM_IRT_OK )
    {
        /* Checks DTC Kind. */
        resultChkKind = Dem_CfgInfo_CheckDTCSettingKind( DTCKind );

        if( resultChkKind == DEM_IRT_OK )
        {
            retVal = DEM_IRT_OK;
        }
        else
        {
            /* Wrong DTCGroup. */
            /* No Process */
        }
    }
    else
    {
        /* Wrong DTCGroup. */
        /* No Process */
    }

    return retVal;
}



/****************************************************************************/
/* Function Name | Dem_CfgInfo_CheckDTCReadDTCParameter                     */
/* Description   | Checks the consistency of the specified DTCFormat type.  */
/* Preconditions |                                                          */
/* Parameters    | [in] DTCFormat :                                         */
/*               |        The specified DTCFormat type to check consistenc- */
/*               |        y.                                                */
/*               |  [in] DTCOrigin :                                        */
/*               |        The specified DTCOrigin type to check consistenc- */
/*               |        y.                                                */
/*               |  [OUT] UdmInfoTableIndexPtr :                            */
/*               |        The Index of Dem_UserDefinedMemoryTable           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : The consistency checking of DTCForm- */
/*               |        at type is successful.                            */
/*               |        DEM_IRT_NG : The consistency checking of DTCForm- */
/*               |        at type is failed.                                */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfo_CheckDTCReadDTCParameter
(
    VAR( Dem_DTCKindType, AUTOMATIC ) DTCKind,
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultChkKind;

    retVal  =   DEM_IRT_NG;

    resultChkKind = Dem_CfgInfo_CheckDTCKind( DTCKind );
    if( resultChkKind == DEM_IRT_OK )
    {
        if( DTCOrigin == DEM_DTC_ORIGIN_PRIMARY_MEMORY )
        {
            retVal  =   Dem_CfgInfoPm_CheckDTCFormat( DTCFormat );
        }
        else if ( DTCOrigin == DEM_DTC_ORIGIN_PERMANENT_MEMORY )
        {
#if ( DEM_OBD_SUPPORT == STD_ON )   /*  [FuncSw]    */
            retVal  =   Dem_CfgInfoPermanentM_CheckDTCOriginAndFormat( DTCFormat );
#endif  /* ( DEM_OBD_SUPPORT == STD_ON )            */
        }
        else
        {
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) /*  [FuncSw]    */
            /*  check UserDefinedMemory.        */
            retVal  =   Dem_CfgInfoUdm_CheckDTCOriginAndFormat( DTCFormat, DTCOrigin );
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )          */
        }
    }
    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_CfgInfo_CheckDTCGroup                                */
/* Description   | Checks the range of the specified DTC value.             */
/* Preconditions |                                                          */
/* Parameters    | [in] DTCGroup :                                          */
/*               |        The specified DTC value to check the range.       */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : The range check of DTC value is suc- */
/*               |        uccessful.                                        */
/*               |        DEM_IRT_NG : The range check of DTC value is fai- */
/*               |        led.                                              */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfo_CheckDTCGroup
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_GroupOfDTCIndexType, AUTOMATIC ) groupOfDtcCnt;
    VAR( Dem_u08_GroupOfDTCIndexType, AUTOMATIC ) demGroupDTCNum;

    /* Initializes the return value to NG. */
    retVal = DEM_IRT_NG;

    demGroupDTCNum = Dem_GroupDTCNum;

    /* Now, checks only all DTCs. */

    for( groupOfDtcCnt = (Dem_u08_GroupOfDTCIndexType)0U; groupOfDtcCnt < demGroupDTCNum; groupOfDtcCnt++ )     /* [GUD:for]groupOfDtcCnt */
    {
        /* Checks whether the specified DTC value in DTC table. */
        if( DTCGroup == Dem_GroupOfDTCTable[groupOfDtcCnt].DemGroupDTCs )                                       /* [GUD]groupOfDtcCnt */
        {
            /* The specified DTC value is not all DTCs. */

            /* Sets the return value to OK. */
            retVal = DEM_IRT_OK;
            break;
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_CfgInfo_CheckDTCSettingGroup                         */
/* Description   | Checks whether DTC Group is supported.                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCGroup :                                          */
/*               |        Defineds DTC group for the check                  */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : The DTC group is supported.          */
/*               |        DEM_IRT_NG : The DTC group is not supported.      */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfo_CheckDTCSettingGroup
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    /* Initializes the return value to OK. */
    retVal = DEM_IRT_OK;

    /* Now, checks only all DTCs. */

    /* Checks whether the specified DTC group is all DTCs. */
    if( DTCGroup != DEM_DTC_GROUP_ALL_DTCS )
    {
        /* The specified DTC group is not all DTCs. */

        /* Sets the return value to NG. */
        retVal = DEM_IRT_NG;
    }
    else
    {
        /* no processing. */
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_CfgInfo_CheckDTCKind                                 */
/* Description   | Checks the consistency of the specified DTCKind type.    */
/* Preconditions |                                                          */
/* Parameters    | [in] DTCKind :                                           */
/*               |        The specified DTCKind type to check consistency.  */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : The consistency checking of DTCKind  */
/*               |         type is successful.                              */
/*               |        DEM_IRT_NG : The consistency checking of DTCKind  */
/*               |         type is failed.                                  */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfo_CheckDTCSettingKind
(
    VAR( Dem_DTCKindType, AUTOMATIC ) DTCKind
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    /* Initializes the return value to NG. */
    retVal = DEM_IRT_NG;

    /* Checks whether the DTCKind is all DTCs. */
    if( DTCKind == (Dem_DTCKindType)DEM_DTC_KIND_ALL_DTCS )
    {
        /* Sets the return value to OK. */
        retVal = DEM_IRT_OK;
    }

    return retVal;
}

#if ( DEM_OBD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_CfgInfo_CheckDTCKind                                 */
/* Description   | Checks the consistency of the specified DTCKind type.    */
/* Preconditions |                                                          */
/* Parameters    | [in] DTCKind :                                           */
/*               |        The specified DTCKind type to check consistency.  */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : The consistency checking of DTCKind  */
/*               |         type is successful.                              */
/*               |        DEM_IRT_NG : The consistency checking of DTCKind  */
/*               |         type is failed.                                  */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfo_CheckDTCKind
(
    VAR( Dem_DTCKindType, AUTOMATIC ) DTCKind
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    /* Initializes the return value to NG. */
    retVal = DEM_IRT_NG;

    /* Checks whether the DTCKind is all DTCs. */
    if( DTCKind == (Dem_DTCKindType)DEM_DTC_KIND_ALL_DTCS )
    {
        /* Sets the return value to OK. */
        retVal = DEM_IRT_OK;
    }
    else if( DTCKind == (Dem_DTCKindType)DEM_DTC_KIND_EMISSION_REL_DTCS )
    {
        /* Sets the return value to OK. */
        retVal = DEM_IRT_OK;
    }
    else
    {
        /* no processing. */
    }

    return retVal;
}
#endif  /* ( DEM_OBD_SUPPORT == STD_ON )    */


#if ( DEM_OBD_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_CfgInfo_CheckDTCKind                                 */
/* Description   | Checks the consistency of the specified DTCKind type.    */
/* Preconditions |                                                          */
/* Parameters    | [in] DTCKind :                                           */
/*               |        The specified DTCKind type to check consistency.  */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : The consistency checking of DTCKind  */
/*               |         type is successful.                              */
/*               |        DEM_IRT_NG : The consistency checking of DTCKind  */
/*               |         type is failed.                                  */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfo_CheckDTCKind
(
    VAR( Dem_DTCKindType, AUTOMATIC ) DTCKind
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    /* Initializes the return value to NG. */
    retVal = DEM_IRT_NG;

    /* Checks whether the DTCKind is all DTCs. */
    if( DTCKind == (Dem_DTCKindType)DEM_DTC_KIND_ALL_DTCS )
    {
        /* Sets the return value to OK. */
        retVal = DEM_IRT_OK;
    }

    return retVal;
}
#endif  /* ( DEM_OBD_SUPPORT == STD_OFF )    */





#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
