/* IdsM_Cfg_h_v2-1-0                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | IdsM/Cfg/HEADER                                            */
/*--------------------------------------------------------------------------*/
/* Notes                                                                    */
/****************************************************************************/

#ifndef IDSM_CFG_H
#define IDSM_CFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include <Std_Types.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define IDSM_TS_OPT_NONE       (0U)
#define IDSM_TS_OPT_AUTOSAR    (1U)
#define IDSM_TS_OPT_CUSTOM     (2U)

#define IDSM_CFG_USE_IDSR       (STD_ON)
#define IDSM_CFG_USE_DEM       (STD_OFF)
#define IDSM_CFG_USE_TIMESTAMP        (IDSM_TS_OPT_NONE)
#define IDSM_CFG_USE_CTXDATA        (STD_ON)
#define IDSM_CFG_USE_INTSEV_EVEBUFFUL        (STD_OFF)
#define IDSM_CFG_USE_INTSEV_CTXBUFFUL        (STD_OFF)
#define IDSM_CFG_USE_INTSEV_TRAFFICLMIT        (STD_OFF)
#define IDSM_CFG_USE_FILTERCHAIN        (STD_OFF)
#define IDSM_CFG_USE_FIL_BLKSTATE        (STD_OFF)
#define IDSM_CFG_USE_FIL_AGGREGATION        (STD_OFF)
#define IDSM_CFG_USE_FIL_THRESHOLD        (STD_OFF)
#define IDSM_CFG_USE_FIL_NTH        (STD_OFF)
#define IDSM_CFG_USE_FIL_RATELMT        (STD_ON)
#define IDSM_CFG_USE_FIL_TRAFFICLMT        (STD_OFF)
#define IDSM_CFG_RAM_ERROR_CHECK        (STD_ON)
#define IDSM_CFG_DEM_BUFF_PADDING        (STD_OFF)


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif /* IDSM_CFG_H */

/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-1-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

