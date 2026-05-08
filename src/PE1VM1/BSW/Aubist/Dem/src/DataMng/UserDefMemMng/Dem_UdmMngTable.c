/* Dem_UdmMngTable_c(v5-3-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmMngTable/CODE                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_NvM_Cfg.h"
#include "../../../inc/Dem_Rc_UdmMng_rc.h"
#include "../../../inc/Dem_Rc_UdmMngTable.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CONST_CONFIG
#include <Dem_MemMap.h>

CONST( AB_83_ConstV Dem_UdmExcFncType           ,DEM_CONFIG_DATA )  Dem_UdmExcFncTable[ DEM_USER_DEFINED_MEMORY_NUM ] =
{
    {   &SchM_Enter_Dem_Udm_RkDemUDM_Occurrence1_EventMemory, &SchM_Exit_Dem_Udm_RkDemUDM_Occurrence1_EventMemory   },
    {   &SchM_Enter_Dem_Udm_RkDemUDM_Occurrence2_EventMemory, &SchM_Exit_Dem_Udm_RkDemUDM_Occurrence2_EventMemory   },
    {   &SchM_Enter_Dem_Udm_RkDemUDM_Occurrence2_NM_EventMemory, &SchM_Exit_Dem_Udm_RkDemUDM_Occurrence2_NM_EventMemory   },
    {   &SchM_Enter_Dem_Udm_RkDemUDM_Occurrence3_NM_EventMemory, &SchM_Exit_Dem_Udm_RkDemUDM_Occurrence3_NM_EventMemory   },
    {   &SchM_Enter_Dem_Udm_RkDemUDM_Occurrence7_NM_EventMemory, &SchM_Exit_Dem_Udm_RkDemUDM_Occurrence7_NM_EventMemory   },
    {   &SchM_Enter_Dem_Udm_RkDemUDM_Maintenance1_EventMemory, &SchM_Exit_Dem_Udm_RkDemUDM_Maintenance1_EventMemory   },
    {   &SchM_Enter_Dem_Udm_RkDemUDM_SystemOperation2_EventMemory, &SchM_Exit_Dem_Udm_RkDemUDM_SystemOperation2_EventMemory   }
};

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
/* Function Name | Dem_UdmExcEnterFnc_ForStack                              */
/* Description   | Dem_UdmExcEnterFnc for measuring stack size.             */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmExcEnterFnc_ForStack
(
    void
)
{
    SchM_Enter_Dem_Udm_RkDemUDM_Occurrence1_EventMemory();
    SchM_Enter_Dem_Udm_RkDemUDM_Occurrence2_EventMemory();
    SchM_Enter_Dem_Udm_RkDemUDM_Occurrence2_NM_EventMemory();
    SchM_Enter_Dem_Udm_RkDemUDM_Occurrence3_NM_EventMemory();
    SchM_Enter_Dem_Udm_RkDemUDM_Occurrence7_NM_EventMemory();
    SchM_Enter_Dem_Udm_RkDemUDM_Maintenance1_EventMemory();
    SchM_Enter_Dem_Udm_RkDemUDM_SystemOperation2_EventMemory();

    return;
}

/****************************************************************************/
/* Function Name | Dem_UdmExcExitFnc_ForStack                               */
/* Description   | Dem_UdmExcExitFnc for measuring stack size.              */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmExcExitFnc_ForStack
(
    void
)
{
    SchM_Exit_Dem_Udm_RkDemUDM_Occurrence1_EventMemory();
    SchM_Exit_Dem_Udm_RkDemUDM_Occurrence2_EventMemory();
    SchM_Exit_Dem_Udm_RkDemUDM_Occurrence2_NM_EventMemory();
    SchM_Exit_Dem_Udm_RkDemUDM_Occurrence3_NM_EventMemory();
    SchM_Exit_Dem_Udm_RkDemUDM_Occurrence7_NM_EventMemory();
    SchM_Exit_Dem_Udm_RkDemUDM_Maintenance1_EventMemory();
    SchM_Exit_Dem_Udm_RkDemUDM_SystemOperation2_EventMemory();

    return;
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
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
