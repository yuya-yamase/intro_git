/* Dcm_Dsl_SecurityMng_c(v5-0-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsl_SecurityMng/CODE                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../Dsl/inc/Dcm_Dsl_Main.h"
#include "../../Dsl/inc/Dcm_Dsl_SecurityMng.h"
#include "../../Dsl/usr/Dcm_Dsl_SecurityMng_Connector.h"

#include <Dcm.h>
#include <SchM_Dcm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSL_SEC_LV_MAX                 ((uint8)64U)   /* Max of the security level */

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
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

static VAR(Dcm_SecLevelType, DCM_VAR_NO_INIT) Dcm_Dsl_u1SecLevel;

#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_CONST
#include <Dcm_MemMap.h>
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>


/****************************************************************************/
/* Function Name | Dcm_Dsl_SecurityMng_Init                                 */
/* Description   | This function calls the initialization function          */
/*               | of the DSL unit.                                         */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_SecurityMng_Init
(void)
{

    /* lock */
    SchM_Enter_Dcm_Dsl_SecLevel();

    Dcm_Dsl_u1SecLevel = DCM_SEC_LEV_LOCKED;

    /* unlock */
    SchM_Exit_Dcm_Dsl_SecLevel();

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_SecurityMng_GetSecurityLevel                     */
/* Description   | This function provides the active security level value.  */
/* Preconditions | -                                                        */
/* Parameters    | [out] ptSecLevel :                                       */
/*               |        Active Security Level value Conversion formula t- */
/*               |        o calculate SecurityLevel out of tester requeste- */
/*               |        d SecurityAccessType parameter: SecurityLevel = - */
/*               |        (SecurityAccessType + 1) / 2 Content of Security- */
/*               |        AccessType is according to "securityAccessType" - */
/*               |        parameter of SecurityAccess request               */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK: : this value is always returned.            */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_SecurityMng_GetSecurityLevel
(
    P2VAR(Dcm_SecLevelType, AUTOMATIC, DCM_APPL_DATA) ptSecLevel
)
{
    /* lock */
    SchM_Enter_Dcm_Dsl_SecLevel();

    *ptSecLevel = Dcm_Dsl_u1SecLevel;

    /* unlock */
    SchM_Exit_Dcm_Dsl_SecLevel();

    return E_OK;
}


/****************************************************************************/
/* Function Name | Dcm_Dsl_SecurityMng_SetSecurityLevel                     */
/* Description   | This function sets a new security level value in the     */
/*               | DCM Component.                                           */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1SecurityLevel : new security level value          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_SecurityMng_SetSecurityLevel
(
    const Dcm_SecLevelType u1SecurityLevel
)
{
    uint8            u1_Count;
    uint8            u1_IndSecLvChgNumMax;
    Dcm_SecLevelType u1_SecLevelOld;

    u1_IndSecLvChgNumMax = Dcm_Dsl_u1IndSecLvChgNum;

    if( u1SecurityLevel < DCM_DSL_SEC_LV_MAX )
    {
        /* lock */
        SchM_Enter_Dcm_Dsl_SecLevel();

        u1_SecLevelOld      = Dcm_Dsl_u1SecLevel;
        Dcm_Dsl_u1SecLevel  = u1SecurityLevel;

        /* unlock */
        SchM_Exit_Dcm_Dsl_SecLevel();

        for( u1_Count = (uint8)0U; u1_Count < u1_IndSecLvChgNumMax; u1_Count++ )
        {
#ifndef JGXSTACK

            Dcm_Dsl_IndSecLevelChgTable[u1_Count](u1_SecLevelOld, u1SecurityLevel);

#else   /* JGXSTACK */

            Dcm_Stack_IndSecLevelChgFunc(u1_SecLevelOld, u1SecurityLevel);

#endif  /* JGXSTACK */
        }

        /* Return value ignoring */
        (void)Dcm_Dsl_IndicateSecLevelChange(u1_SecLevelOld, u1SecurityLevel);
        (void)Dcm_Dsl_Cnct_Switch_SecurityAccess(u1SecurityLevel);
    }

    return ;
}

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-05-29                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2022-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
