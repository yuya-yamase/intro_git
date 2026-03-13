/* Dem_Dcm_IUMPR_c(v5-5-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/If_IUMPR_OBD/CODE                                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem_Dcm.h>

#if ( DEM_IUMPR_SUPPORT == STD_ON )

#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Pm_Control_IUMPR.h"

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
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_ENGINETYPE_COMPRESSION_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_DcmGetInfoTypeValue08                                */
/* Description   | Service is used for requesting IUMPR data according to   */
/*               | InfoType 0x08.                                           */
/* Preconditions | none                                                     */
/* Parameters    | [in] OpStatus :                                          */
/*               |          Only DCM_INITIAL will appear, because this API  */
/*               |          behaves synchronous.                            */
/*               | [out] Iumprdata08 :                                      */
/*               |          Buffer containing the contents of InfoType 0x08.*/
/*               |          The buffer is provided by the Dcm.              */
/*               | [inout] Iumprdata08BufferSize :                          */
/*               |          Buffer containing the number of data elements   */
/*               |          (as defined in ISO-15031-5) and contents of     */
/*               |          InfoType 0x08.                                  */
/*               |          The buffer is provided by the Dcm.              */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK     : Operation was successful.              */
/*               |        E_NOT_OK : Operation failed.                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmGetInfoTypeValue08
(
    VAR( Dcm_OpStatusType, AUTOMATIC )          OpStatus,
    P2VAR( uint8 , AUTOMATIC, DEM_APPL_DATA )   Iumprdata08,
    P2VAR( uint8 , AUTOMATIC, DEM_APPL_DATA )   Iumprdata08BufferSize
)
{
    VAR( Std_ReturnType, AUTOMATIC )                retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )    retInfoTypeValue;
    VAR( uint8, AUTOMATIC )                         wkIumprdata08BufferSize;

    retVal = E_NOT_OK;

    if( OpStatus == DCM_INITIAL )
    {
        if( Iumprdata08 != NULL_PTR )
        {
            if( Iumprdata08BufferSize != NULL_PTR )
            {
                wkIumprdata08BufferSize = *Iumprdata08BufferSize;
                retInfoTypeValue    = Dem_Control_GetInfoTypeValue( Iumprdata08, &wkIumprdata08BufferSize );
                if( retInfoTypeValue == DEM_IRT_OK )
                {
                    *Iumprdata08BufferSize  = wkIumprdata08BufferSize;
                    retVal                  = E_OK;
                }
            }
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DcmGetInfoTypeValue0B                                */
/* Description   | Service is used for requesting IUMPR data according to   */
/*               | InfoType 0x0B.                                           */
/* Preconditions | none                                                     */
/* Parameters    | [in] OpStatus :                                          */
/*               |          Only DCM_INITIAL will appear, because this API  */
/*               |          behaves synchronous.                            */
/*               | [out] Iumprdata0B :                                      */
/*               |          Buffer containing the contents of InfoType 0x0B.*/
/*               |          The buffer is provided by the Dcm.              */
/*               | [inout] Iumprdata0BBufferSize :                          */
/*               |          Buffer containing the number of data elements   */
/*               |          (as defined in ISO-15031-5) and contents of     */
/*               |          InfoType 0x0B.                                  */
/*               |          The buffer is provided by the Dcm.              */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK     : Operation was successful.              */
/*               |        E_NOT_OK : Operation failed.                      */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmGetInfoTypeValue0B
(
    VAR( Dcm_OpStatusType, AUTOMATIC )          OpStatus,               /* MISRA DEVIATION */
    P2VAR( uint8 , AUTOMATIC, DEM_APPL_DATA )   Iumprdata0B,            /* MISRA DEVIATION */
    P2VAR( uint8 , AUTOMATIC, DEM_APPL_DATA )   Iumprdata0BBufferSize   /* MISRA DEVIATION */
)
{
    return E_NOT_OK;
}

#endif  /* ( DEM_ENGINETYPE_COMPRESSION_SUPPORT == STD_OFF ) */

#if ( DEM_ENGINETYPE_COMPRESSION_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DcmGetInfoTypeValue08                                */
/* Description   | Service is used for requesting IUMPR data according to   */
/*               | InfoType 0x08.                                           */
/* Preconditions | none                                                     */
/* Parameters    | [in] OpStatus :                                          */
/*               |          Only DCM_INITIAL will appear, because this API  */
/*               |          behaves synchronous.                            */
/*               | [out] Iumprdata08 :                                      */
/*               |          Buffer containing the contents of InfoType 0x08.*/
/*               |          The buffer is provided by the Dcm.              */
/*               | [inout] Iumprdata08BufferSize :                          */
/*               |          Buffer containing the number of data elements   */
/*               |          (as defined in ISO-15031-5) and contents of     */
/*               |          InfoType 0x08.                                  */
/*               |          The buffer is provided by the Dcm.              */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK     : Operation was successful.              */
/*               |        E_NOT_OK : Operation failed.                      */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmGetInfoTypeValue08
(
    VAR( Dcm_OpStatusType, AUTOMATIC )          OpStatus,               /* MISRA DEVIATION */
    P2VAR( uint8 , AUTOMATIC, DEM_APPL_DATA )   Iumprdata08,            /* MISRA DEVIATION */
    P2VAR( uint8 , AUTOMATIC, DEM_APPL_DATA )   Iumprdata08BufferSize   /* MISRA DEVIATION */
)
{
    return E_NOT_OK;
}

/****************************************************************************/
/* Function Name | Dem_DcmGetInfoTypeValue0B                                */
/* Description   | Service is used for requesting IUMPR data according to   */
/*               | InfoType 0x0B.                                           */
/* Preconditions | none                                                     */
/* Parameters    | [in] OpStatus :                                          */
/*               |          Only DCM_INITIAL will appear, because this API  */
/*               |          behaves synchronous.                            */
/*               | [out] Iumprdata0B :                                      */
/*               |          Buffer containing the contents of InfoType 0x0B.*/
/*               |          The buffer is provided by the Dcm.              */
/*               | [inout] Iumprdata0BBufferSize :                          */
/*               |          Buffer containing the number of data elements   */
/*               |          (as defined in ISO-15031-5) and contents of     */
/*               |          InfoType 0x0B.                                  */
/*               |          The buffer is provided by the Dcm.              */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK     : Operation was successful.              */
/*               |        E_NOT_OK : Operation failed.                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmGetInfoTypeValue0B
(
    VAR( Dcm_OpStatusType, AUTOMATIC )          OpStatus,
    P2VAR( uint8 , AUTOMATIC, DEM_APPL_DATA )   Iumprdata0B,
    P2VAR( uint8 , AUTOMATIC, DEM_APPL_DATA )   Iumprdata0BBufferSize
)
{
    VAR( Std_ReturnType, AUTOMATIC )                retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )    retInfoTypeValue;
    VAR( uint8, AUTOMATIC )                         wkIumprdata0BBufferSize;

    retVal = E_NOT_OK;

    if( OpStatus == DCM_INITIAL )
    {
        if( Iumprdata0B != NULL_PTR )
        {
            if( Iumprdata0BBufferSize != NULL_PTR )
            {
                wkIumprdata0BBufferSize = *Iumprdata0BBufferSize;
                retInfoTypeValue    = Dem_Control_GetInfoTypeValue( Iumprdata0B, &wkIumprdata0BBufferSize );
                if( retInfoTypeValue == DEM_IRT_OK )
                {
                    *Iumprdata0BBufferSize  = wkIumprdata0BBufferSize;
                    retVal                  = E_OK;
                }
            }
        }
    }

    return retVal;
}
#endif  /* ( DEM_ENGINETYPE_COMPRESSION_SUPPORT == STD_ON ) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_IUMPR_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
