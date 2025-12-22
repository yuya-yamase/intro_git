/* Dcm_Dsp_SID06_Cfg_c(v5-0-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID06_Cfg/CODE                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../Dsp/cfg/Dcm_Dsp_SID06_Cfg.h"
#if( DCM_SUPPORT_SID06 == STD_ON )

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/*****************************************************************************/
/* Function Name | Dcm_Dsp_SID06_GetAvailableOBDMIDs                         */
/* Description   | Gets value of OBDMID.                                     */
/* Preconditions | none                                                      */
/* Parameters    | [in]  u1Obdmid      : OBDMID.                             */
/*               | [out] ptObdmidvalue : value of OBDMID.                    */
/* Return Value  | Std_ReturnType                                            */
/*               |        E_OK     : Report of DTR result successful.        */
/*               |        E_NOT_OK : Report of DTR result failed.            */
/* Notes         | None                                                      */
/*****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID06_GetAvailableOBDMIDs
(
    uint8 u1Obdmid,  /* MISRA DEVIATION */
    P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) ptObdmidvalue  /* MISRA DEVIATION */
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_NOT_OK;

    return u1_RetVal;
}

/*****************************************************************************/
/* Function Name | Dem_DcmGetNumTIDsOfOBDMID                                 */
/* Description   | Gets number of TID.                                       */
/* Preconditions | none                                                      */
/* Parameters    | [in]  u1Obdmid       : Monitor ID of DTR.                 */
/*               | [out] ptNumberOfTIDs : number of TID.                     */
/* Return Value  | Std_ReturnType                                            */
/*               |        E_OK     : Report of DTR result successful.        */
/*               |        E_NOT_OK : Report of DTR result failed.            */
/* Notes         | -                                                         */
/*****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID06_GetNumTIDsOfOBDMID
(
    uint8 u1Obdmid,  /* MISRA DEVIATION */
    P2VAR(uint8 , AUTOMATIC, DCM_APPL_DATA) ptNumberOfTIDs  /* MISRA DEVIATION */
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_NOT_OK;

    return u1_RetVal;
}

/*****************************************************************************/
/* Function Name | Dcm_Dsp_SID06_GetDTRData                                  */
/* Description   | Gets a DTR result.                                        */
/* Preconditions | none                                                      */
/* Parameters    | [in]  u1Obdmid      : Monitor ID of DTR.                  */
/*               | [in]  u1TIDindex    : Test ID Index of DTR.               */
/*               | [out] ptTIDvalue    : Test ID of DTR.                     */
/*               | [out] ptUaSID       : UnitAndScalingID of DTR.            */
/*               | [out] ptTestvalue   : Test result of DTR.                 */
/*               | [out] ptLowlimvalue : Lower limit of DTR.                 */
/*               | [out] ptUpplimvalue : Upper limit of DTR.                 */
/* Return Value  | Std_ReturnType                                            */
/*               |        E_OK     : Report of DTR result successful.        */
/*               |        E_NOT_OK : Report of DTR result failed.            */
/* Notes         | -                                                         */
/*****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID06_GetDTRData
(
    uint8 u1Obdmid,    /* MISRA DEVIATION */
    uint8 u1TIDindex,  /* MISRA DEVIATION */
    P2VAR(uint8 , AUTOMATIC, DCM_APPL_DATA) ptTIDvalue,     /* MISRA DEVIATION */
    P2VAR(uint8 , AUTOMATIC, DCM_APPL_DATA) ptUaSID,        /* MISRA DEVIATION */
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) ptTestvalue,    /* MISRA DEVIATION */
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) ptLowlimvalue,  /* MISRA DEVIATION */
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) ptUpplimvalue   /* MISRA DEVIATION */
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_NOT_OK;

    return u1_RetVal;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID06 == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
