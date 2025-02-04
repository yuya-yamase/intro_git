/* EcuM_BootMode_c_Revision(v3.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | EcuM/BootMode/CODE                                          */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <EcuM.h>
#include "EcuM_Local.h"


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
#define ECUM_START_SEC2_VAR
#include <EcuM_MemMap.h>

static VAR(uint8, ECUM_VAR_CLEARED) EcuM_StartupMode;

#define ECUM_STOP_SEC2_VAR
#include <EcuM_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define ECUM_START_SEC2_CST
#include <EcuM_MemMap.h>

#define ECUM_STOP_SEC2_CST
#include <EcuM_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define ECUM_START_SEC2_CODE
#include <EcuM_MemMap.h>

/******************************************************************************/
/* Function Name | EcuM_SetBootMode                                           */
/* Description   | Notified of the boot mode                                  */
/* Preconditions |                                                            */
/* Parameters    | [IN] Mode : boot mode                                      */
/*               |       ECUM_START_AP_ENTRY                                  */
/*               |       ECUM_START_BOOT_ENTRY                                */
/*               |       ECUM_START_BOOT_POSRES_ENTRY                         */
/*               |       ECUM_START_STAYINBOOT_ENTRY                          */
/* Return Value  | None                                                       */
/* Notes         | - This function is called only once at the time of Startup.*/
/*               | - When Mode is not valid value,                            */
/*               |   it sets ECUM_START_BOOT_ENTRY.                           */
/*               | - ECUM_START_BOOT_POSRES_ENTRY can be used when            */
/*               |   REPROG_CFG_POSRES_AFTER_RESET is STD_ON.                 */
/*               | - ECUM_START_STAYINBOOT_ENTRY can be used when             */
/*               |   REPROG_CFG_STAYINBOOT_ENABLE is STD_ON.                  */
/******************************************************************************/
FUNC(void, ECUM_CODE_SLOW) EcuM_SetBootMode
(
    VAR(uint8, AUTOMATIC) Mode
)
{
    VAR(EcuM_ErrorType, AUTOMATIC) Error;

    if( ( Mode == ECUM_START_AP_ENTRY ) || ( Mode == ECUM_START_BOOT_ENTRY )
#if (REPROG_CFG_POSRES_AFTER_RESET == STD_ON)
        || ( Mode == ECUM_START_BOOT_POSRES_ENTRY )
#endif
#if (REPROG_CFG_STAYINBOOT_ENABLE == STD_ON)
        || ( Mode == ECUM_START_STAYINBOOT_ENTRY )
#endif
      )
    {
        EcuM_StartupMode = Mode;
    }
    else
    {
        EcuM_StartupMode = ECUM_START_BOOT_ENTRY;

        Error.ModuleId = ECUM_MODULE_ECUM;
        Error.ApiId = ECUM_API_ID_SETBOOTMODE;
        Error.ErrorId = ECUM_E_INVALID_PAR;

        EcuM_ReportError(&Error);
    }

    return;
}

/******************************************************************************/
/* Function Name | EcuM_GetBootMode                                           */
/* Description   | Acquire the boot mode                                      */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | boot mode                                                  */
/*               |  ECUM_START_AP_ENTRY                                       */
/*               |  ECUM_START_BOOT_ENTRY                                     */
/*               |  ECUM_START_BOOT_POSRES_ENTRY                              */
/*               |  ECUM_START_STAYINBOOT_ENTRY                               */
/* Notes         | - ECUM_START_BOOT_POSRES_ENTRY can be used when            */
/*               |   REPROG_CFG_POSRES_AFTER_RESET is STD_ON.                 */
/*               | - ECUM_START_STAYINBOOT_ENTRY can be used when             */
/*               |   REPROG_CFG_STAYINBOOT_ENABLE is STD_ON.                  */
/******************************************************************************/
FUNC(uint8, ECUM_CODE_SLOW) EcuM_GetBootMode (void)
{
    return EcuM_StartupMode;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define ECUM_STOP_SEC2_CODE
#include <EcuM_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2018/06/19 :Update                                rel.AUBASS */
/*  v3.00       :2021/09/14 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

