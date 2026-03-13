/* Dem_Dcm_OBD_c(v5-5-0)                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Dcm_OBD/CODE                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem_Dcm.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnIf_Control.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_Pm_Control_OBD.h"

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

#if ( DEM_PID_SUPPORT == STD_ON )

/****************************************************************************/
/* Function Name | Dem_DcmReadDataOfPID01                                   */
/* Description   | Service to report the value of PID01 computed by the     */
/*               | Dem. API is needed in OBD - relevant ECUs only.          */
/* Preconditions | none                                                     */
/* Parameters    | [out] PID01value :                                       */
/*               |        Buffer containing the contents of PID01 computed  */
/*               |        by the Dem. The buffer is provided by the Dcm     */
/*               |        with the appropriate size, i.e. during            */
/*               |        configuration, the Dcm identifies the required    */
/*               |        size from the largest PID in order to configure a */
/*               |        PIDBuffer.                                        */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Always E_OK is returned, as E_NOT_OK will  */
/*               |        never appear.                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmReadDataOfPID01
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID01value
)
{
    if( PID01value != NULL_PTR )
    {
        Dem_Control_ReadDataOfPID01( DEM_READINESS_CALLBY_DCM, PID01value );
    }
    else
    {
        /* No Process */
    }

    return E_OK;
}

/****************************************************************************/
/* Function Name | Dem_DcmReadDataOfPID1C                                   */
/* Description   | Service to report the value of PID1C computed by the     */
/*               | Dem. API is needed in OBD - relevant ECUs only.          */
/* Preconditions | none                                                     */
/* Parameters    | [out] PID1Cvalue :                                       */
/*               |        Buffer containing the contents of PID1C computed  */
/*               |        by the Dem. The value of PID1C is configuration   */
/*               |        within DemOBDCompliancy. The buffer is provided   */
/*               |        by the Dcm with the appropriate size, i.e.during  */
/*               |        configuration, the Dcm identifies the required    */
/*               |        size from the largest PID in order to configure a */
/*               |        PIDBuffer.                                        */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Always E_OK is returned, as E_NOT_OK will  */
/*               |        never appear.                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmReadDataOfPID1C
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID1Cvalue
)
{
    VAR( uint8, AUTOMATIC ) value;

    if( PID1Cvalue != NULL_PTR )
    {
        Dem_Control_ReadDataOfPID1C( &value );
        *PID1Cvalue = value;
    }
    else
    {
        /* No Process */
    }

    return E_OK;
}


/****************************************************************************/
/* Function Name | Dem_DcmReadDataOfPID21                                   */
/* Description   | Service to report the value of PID21 computed by the     */
/*               | Dem.API is needed in OBD-relevant ECUs only.             */
/* Preconditions | none                                                     */
/* Parameters    | [out] PID21value :                                       */
/*               |        Buffer containing the contents of PID21           */
/*               |        computed by the Dem. The buffer is provided by    */
/*               |        the Dcm with the appropriate size, i.e. during    */
/*               |        configuration, the Dcm identifies the required    */
/*               |        size from the largest PID in order to configure   */
/*               |        a PIDBuffer.                                      */
/* Return Value  | Std_ReturnType :                                         */
/*               |        E_OK : Always E_OK is returned, as E_NOT_OK will  */
/*               |        never appear.                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmReadDataOfPID21
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID21value
)
{
    if( PID21value != NULL_PTR )
    {
        Dem_Control_ReadDataOfPID21( PID21value );
    }
    else
    {
        /* No Process */
    }

    return E_OK;
}

/****************************************************************************/
/* Function Name | Dem_DcmReadDataOfPID30                                   */
/* Description   | Service to report the value of PID30 computed by the     */
/*               | Dem. API is needed in OBD - relevant ECUs only.          */
/* Preconditions | none                                                     */
/* Parameters    | [out] PID30value :                                       */
/*               |        Buffer containing the contents of PID30 computed  */
/*               |        by the Dem. The buffer is provided by the Dcm     */
/*               |        with the appropriate size, i.e. during            */
/*               |        configuration, the Dcm identifies the required    */
/*               |        size from the largest PID in order to configure a */
/*               |        PIDBuffer.                                        */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Always E_OK is returned, as E_NOT_OK will  */
/*               |        never appear.                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmReadDataOfPID30
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID30value
)
{
    VAR( uint8, AUTOMATIC ) value;

    if( PID30value != NULL_PTR )
    {
        Dem_Control_ReadDataOfPID30( &value );
        *PID30value = value;
    }
    else
    {
        /* No Process */
    }

    return E_OK;
}

/****************************************************************************/
/* Function Name | Dem_DcmReadDataOfPID31                                   */
/* Description   | Service to report the value of PID31 computed by the     */
/*               | Dem. API is needed in OBD-relevant ECUs only.            */
/* Preconditions | none                                                     */
/* Parameters    | [out] PID31value :                                       */
/*               |        Buffer containing the contents of PID31 computed  */
/*               |        ed by the Dem. The buffer is provided by the Dcm  */
/*               |        with the appropriate size, i.e. during configura- */
/*               |        tion, the Dcm identifies the required size from   */
/*               |        the largest PID in order to configure a PIDBuffer.*/
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Always E_OK is returned, as E_NOT_OK will  */
/*               |        never appear.                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmReadDataOfPID31
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID31value
)
{
    if( PID31value != NULL_PTR )
    {
        Dem_Control_ReadDataOfPID31( PID31value );
    }
    else
    {
        /* No Process */
    }

    return E_OK;
}

/****************************************************************************/
/* Function Name | Dem_DcmReadDataOfPID41                                   */
/* Description   | Service to report the value of PID41 computed by the     */
/*               | Dem. API is needed in OBD - relevant ECUs only.          */
/* Preconditions | none                                                     */
/* Parameters    | [out] PID41value :                                       */
/*               |        Buffer containing the contents of PID41 computed  */
/*               |        by the Dem. The buffer is provided by the Dcm     */
/*               |        with the appropriate size, i.e. during            */
/*               |        configuration, the Dcm identifies the required    */
/*               |        size from the largest PID in order to configure a */
/*               |        PIDBuffer.                                        */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Always E_OK is returned, as E_NOT_OK will  */
/*               |        never appear.                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmReadDataOfPID41
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID41value
)
{
    if( PID41value != NULL_PTR )
    {
        Dem_Control_ReadDataOfPID41( DEM_READINESS_CALLBY_DCM, PID41value );
    }
    else
    {
        /* No Process */
    }

    return E_OK;
}

/****************************************************************************/
/* Function Name | Dem_DcmReadDataOfPID4D                                   */
/* Description   | Service to report the value of PID4D computed by the     */
/*               | Dem. API is needed in OBD-relevant ECUs only.            */
/* Preconditions | none                                                     */
/* Parameters    | [out] PID4Dvalue :                                       */
/*               |        Buffer containing the contents of PID4D computed  */
/*               |        by the Dem. The buffer is provided by the Dcm     */
/*               |        with the appropriate size, i.e. during configura- */
/*               |        tion, the Dcm identifies the required size from   */
/*               |        the largest PID in order to configure a PIDBuffer.*/
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Always E_OK is returned, as E_NOT_OK will  */
/*               |        never appear.                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmReadDataOfPID4D
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID4Dvalue
)
{
    if( PID4Dvalue != NULL_PTR )
    {
        Dem_Control_ReadDataOfPID4D( PID4Dvalue );
    }
    else
    {
        /* No Process */
    }

    return E_OK;
}

/****************************************************************************/
/* Function Name | Dem_DcmReadDataOfPID4E                                   */
/* Description   | Service to report the value of PID4E computed by the     */
/*               | Dem. API is needed in OBD-relevant ECUs only.            */
/* Preconditions | none                                                     */
/* Parameters    | [out] PID4Evalue :                                       */
/*               |        Buffer containing the contents of PID4E computed  */
/*               |        by the Dem. The buffer is provided by the Dcm     */
/*               |        with the appropriate size, i.e. during configura- */
/*               |        tion, the Dcm identifies the required size from   */
/*               |        the largest PID in order to configure a PIDBuffer.*/
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Always E_OK is returned, as E_NOT_OK will  */
/*               |        never appear.                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmReadDataOfPID4E
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID4Evalue
)
{
    if( PID4Evalue != NULL_PTR )
    {
        Dem_Control_ReadDataOfPID4E( PID4Evalue );
    }
    else
    {
        /* No Process */
    }

    return E_OK;
}


/****************************************************************************/
/* Function Name | Dem_DcmReadDataOfPIDF501                                 */
/* Description   | Service to report the value of PIDF501 computed by the   */
/*               | Dem. API is needed in OBD - relevant ECUs only.          */
/* Preconditions | none                                                     */
/* Parameters    | [out] PIDF501value :                                     */
/*               |        Buffer containing the contents of PIDF501 comput- */
/*               |        ed by the Dem. The buffer is provided by the Dcm  */
/*               |        with the appropriate size, i.e. during            */
/*               |        configuration, the Dcm identifies the required    */
/*               |        size from the largest PID in order to configure a */
/*               |        PIDBuffer.                                        */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Always E_OK is returned, as E_NOT_OK will  */
/*               |        never appear.                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Std_ReturnType, DEM_CODE ) Dem_DcmReadDataOfPIDF501
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PIDF501value
)
{
    if( PIDF501value != NULL_PTR )
    {
        Dem_Control_ReadDataOfPIDF501( DEM_READINESS_CALLBY_DCM, PIDF501value );
    }
    else
    {
        /* No Process */
    }

    return E_OK;
}
#endif  /* ( DEM_PID_SUPPORT == STD_ON )    */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2019-03-27                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
