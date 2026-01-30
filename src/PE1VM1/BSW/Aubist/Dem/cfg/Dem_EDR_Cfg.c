/* Dem_EDR_Cfg_c(v5-5-0)                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DEM/EDR_Cfg/CODE                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Dem/Dem_InternalDataElement.h>
#include "Dem_EDR_Cfg.h"

/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DEM_START_SEC_CONST_CONFIG
#include <Dem_MemMap.h>

CONST( AB_83_ConstV Dem_ExDataClassType                 ,DEM_CONFIG_DATA ) Dem_ExDataClassTable[ DEM_EX_DATA_CLASS_NUM ] =
{
    /*  DemEDRClassRef  */
    {  {   DEM_EDRCLASSINDEX_INVALID  }  }
};

CONST( AB_83_ConstV Dem_EDRClassType                    ,DEM_CONFIG_DATA ) Dem_EDRClassTable[ DEM_EDR_CLASS_NUM ] =
{
    /*  DemDataElementClassRef DemDataElementKind DemEDRNumber  */
    {   DEM_DATAELEMENTCLASSINDEX_INVALID, DEM_DATA_ELEMENT_KIND_INVALID, DEM_EDR_NUMBER_INVALID  }
};

CONST( AB_83_ConstV Dem_InternalDataElementClassType    ,DEM_CONFIG_DATA ) Dem_InternalDataElementClassTable[ DEM_INTERNAL_DATAELEMENT_NUM ] =
{
    /*  DemInternalDataElementReadFnc  */
    {   NULL_PTR  }
};

CONST( AB_83_ConstV Dem_EDRNumberSupportBitmapType      ,DEM_CONFIG_DATA ) Dem_EDRNumberSupportBitmapTable[ DEM_EDR_SUPPORT_RECNUM_NUM ] =
{
    /*  ExtendDataRecordNumber Reserve SupportDTCNumber SupportDTCBitmapTable  */
    {   0xFFU, 0x00U, 0x0000U, {  0x00000000U  }  }
};


CONST( AB_83_ConstV Dem_u16_ExDataClassIndexType        ,DEM_CONFIG_DATA ) Dem_ExDataClassNum        = DEM_EX_DATA_CLASS_NUM;
CONST( AB_83_ConstV Dem_u08_EDRClassRefIndexType        ,DEM_CONFIG_DATA ) Dem_EDRClassRefNum        = DEM_EDR_CLASS_REF_NUM;
CONST( AB_83_ConstV Dem_u08_EDRClassIndexType           ,DEM_CONFIG_DATA ) Dem_EDRClassNum           = DEM_EDR_CLASS_NUM;

CONST( AB_83_ConstV Dem_u08_EDRNumberSupBmpIndexType    ,DEM_CONFIG_DATA ) Dem_EDRSupportRecNumNum          = DEM_EDR_SUPPORT_RECNUM_NUM;
CONST( AB_83_ConstV Dem_u08_EDRSupDTCBmpIndexType       ,DEM_CONFIG_DATA ) Dem_EDRSupportDTCNumber          = DEM_EDR_SUPPORT_DTC_NUMBER;

CONST( AB_83_ConstV Dem_u08_EDRNumberSupBmpIndexType    ,DEM_CONFIG_DATA ) Dem_EDRSupportObdRecordNumberPos = DEM_EDR_SUPPORT_OBDRECORDNUMBER_POS;

CONST( AB_83_ConstV Dem_u08_EDRNumberSupBmpIndexType    ,DEM_CONFIG_DATA ) Dem_EDRSupportEndOfBehaviorAt0xFERecordNumberPos = DEM_EDR_SUPPORT_ENDOFBHVRATFE_RECORDNUMBER_POS;

#define DEM_STOP_SEC_CONST_CONFIG
#include <Dem_MemMap.h>


#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

#ifndef JGXSTACK
#else /* JGXSTACK */
/****************************************************************************/
/* Function Name | Dem_InternalDataElementReadFnc_ForStack                  */
/* Description   | DemInternalDataElementReadFnc for measuring stack size.  */
/* Preconditions | none                                                     */
/* Parameters    | [in]     EventCtrlIndex                                  */
/*               | [in]     DTCValue                                        */
/*               | [in]     GetExtendDataMode                               */
/*               | [out]    BufferPtr                                       */
/*               | [in/out] BufSizePtr                                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |       DEM_IRT_OK : success                               */
/*               |       DEM_IRT_NG : failed                                */
/*               |       DEM_IRT_WRONG_BUFFERSIZE : buffer size overflow    */
/* Notes         | At the caller, the value of BufferPtr and BufSizePtr are-*/
/*               |    guaranteed.                                           */
/*               | Caller:Dem_EDR_GetData                                   */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_InternalDataElementReadFnc_ForStack
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_u08_GetExtendDataModeType, AUTOMATIC ) GetExtendDataMode,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) BufferPtr,
    P2VAR( Dem_u16_EDRRecordSizeType, AUTOMATIC, AUTOMATIC ) BufSizePtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_OK;


    return retVal;
}
#endif /* JGXSTACK */

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
