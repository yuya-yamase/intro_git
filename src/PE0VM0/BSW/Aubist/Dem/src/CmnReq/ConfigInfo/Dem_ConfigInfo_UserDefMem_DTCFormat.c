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
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )

#include "../../../cfg/Dem_UserDefMem_Cfg.h"


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
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfoUdm_CheckClearParameter
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_UserDefinedMemoryType, AUTOMATIC ) memType;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;

    retVal  =   DEM_IRT_WRONG_DTC;

    memType =   Dem_CfgInfoUdm_GetUserDefinedMemoryTypeByDTCOrigin( DTCOrigin, &udmInfoTableIndex ); /* [GUD:RET:Not DEM_MEMORYTYPE_INVALID]udmInfoTableIndex */

    /* Checks the specified DTCOrigin type. */
    if ( memType != DEM_MEMORYTYPE_INVALID )
    {
        /*  check DTC group.        */
        if ( DTCGroup == DEM_DTC_GROUP_ALL_DTCS )
        {
            if ( DTCFormat == DEM_DTC_FORMAT_UDS )
            {
                retVal = DEM_IRT_OK;
            }
        }
    }
    else
    {
        /*  no UserDefinedMemory.       */
        retVal  =   DEM_IRT_WRONG_DTCORIGIN;
    }
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_CfgInfoUdm_CnvDTCOriginToInternalInfoTableIndex      */
/* Description   | Checks the consistency of the specified DTCOrigin type.  */
/* Preconditions |                                                          */
/* Parameters    | [in] DTCOrigin :                                         */
/*               |        The specified DTCOrigin type to check consistenc- */
/*               |        y.                                                */
/*               | [out] UdmInfoTableIndexPtr :                             */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:DEM_IRT_OK] UdmInfoTableIndexPtr                */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | rename from Dem_CfgInfoUdm_CnvDTCOriginToMemoryDestination(v5-3-0).  */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfoUdm_CnvDTCOriginToInternalInfoTableIndex
(
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    P2VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC, AUTOMATIC ) UdmInfoTableIndexPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_UserDefinedMemoryType, AUTOMATIC ) memType;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;

    retVal  =   DEM_IRT_NG;

    memType  =   Dem_CfgInfoUdm_GetUserDefinedMemoryTypeByDTCOrigin( DTCOrigin, &udmInfoTableIndex );  /* [GUD:RET:Not DEM_MEMORYTYPE_INVALID] udmInfoTableIndex */
    if ( memType == DEM_MEMORYTYPE_INVALID )
    {
        /* No process */
    }
    else if ( memType == DEM_MEMORYTYPE_EXTERNAL )
    {
        /* No process */
    }
    else
    {
        *UdmInfoTableIndexPtr = udmInfoTableIndex;
        retVal = DEM_IRT_OK;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_CfgInfoUdm_CheckDTCOriginAndFormat                   */
/* Description   | Checks the consistency of the specified DTCFormat type.  */
/* Preconditions |                                                          */
/* Parameters    | [in] DTCFormat :                                         */
/*               |        The specified DTCFormat type to check consistenc- */
/*               |        y.                                                */
/*               | [in] DTCOrigin :                                         */
/*               |        The specified DTCOrigin type to check consistenc- */
/*               |        y.                                                */
/*               |                                                          */
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
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfoUdm_CheckDTCOriginAndFormat
(
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_UserDefinedMemoryType, AUTOMATIC ) memType;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;

    retVal  =   DEM_IRT_NG;

    /* Checks the specified DTCOrigin type. */
    memType = Dem_CfgInfoUdm_GetUserDefinedMemoryTypeByDTCOrigin( DTCOrigin, &udmInfoTableIndex ); /* [GUD:RET:Not DEM_MEMORYTYPE_INVALID] udmInfoTableIndex */

    /* Checks the specified DTCOrigin type. */
    if ( memType != DEM_MEMORYTYPE_INVALID )
    {
        if ( DTCFormat == DEM_DTC_FORMAT_UDS )
        {
            retVal = DEM_IRT_OK;
        }
    }
    return retVal;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )      */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
