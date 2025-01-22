/* bsw_bswm_cs_status_bswmlin_c_v3-0-0                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/BSWM/CS/STATUS/BSWMLIN/CODE                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <cs/bsw_cs_common.h>

#include <bswm_cs/bsw_bswm_cs.h>
#include <comm/bsw_comm.h>
#include "../../ComM/inc/bsw_comm_config.h"
#include "../inc/bsw_bswm_cs_config.h"
#if ( BSW_BSWM_CS_FUNC_BSWMLIN == BSW_USE )
#include "../../BswM_Lin/inc/bsw_bswm_lin_MemMap.h"
#include <bswm_lin/bsw_bswm_lin.h>
#include "../inc/bsw_bswm_cs_status_bswmlin.h"

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

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_BswMLinInit                               */
/* Description   | Initialize LIN                                           */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_cs_st_BswMLinInit( void )
{
    BswM_Lin_Init();
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_BswMLinInitDrv                            */
/* Description   | LIN Initialize driver                                    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_cs_st_BswMLinInitDrv( void )
{
    BswM_Lin_InitDriver();
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_BswMLinPreDeInit                          */
/* Description   | LIN Prepare for shutdown                                 */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_cs_st_BswMLinPreDeInit( void )
{
    BswM_Lin_PrepareDeInit();
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_BswMLinDeInit                             */
/* Description   | LIN Shutdown                                             */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_cs_st_BswMLinDeInit( void )
{
    BswM_Lin_DeInit();
}

#if ( BSW_BSWM_CS_ECU_SLEEP == BSW_USE )
/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_BswMLinWakeup                             */
/* Description   | LIN Wake-up initialization                               */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_cs_st_BswMLinWakeup( void )
{
    BswM_Lin_Wakeup();
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_BswMLinSleep                              */
/* Description   | LIN Sleep                                                */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_cs_st_BswMLinSleep( void )
{
    BswM_Lin_Sleep();
}
#endif /* ( BSW_BSWM_CS_ECU_SLEEP == BSW_USE ) */

/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_BswMLinReset                              */
/* Description   | LIN Reset                                                */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_cs_st_BswMLinReset( void )
{
    BswM_Lin_Reset();
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_BswMLinMainHI                             */
/* Description   | LIN High-priority periodic processing - Input            */
/* Preconditions | When processing high-priority periodic process           */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_cs_st_BswMLinMainHI( void )
{
    BswM_Lin_MainFunctionHighIn();
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_BswMLinMainHO                             */
/* Description   | LIN High-priority periodic processing - Output           */
/* Preconditions | When processing high-priority periodic process           */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_cs_st_BswMLinMainHO( void )
{
    BswM_Lin_MainFunctionHighOut();
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_BswMLinMainMI                             */
/* Description   | LIN Medium-priority periodic processing - Input          */
/* Preconditions | When processing medium-priority periodic process         */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_cs_st_BswMLinMainMI( void )
{
    BswM_Lin_MainFunctionMidIn();
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_BswMLinMainMC                             */
/* Description   | LIN Medium-Priority Control                              */
/* Preconditions | When processing medium-priority periodic process         */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_cs_st_BswMLinMainMC( void )
{
    BswM_Lin_MainFunctionMidCtrl();
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_BswMLinMainMO                             */
/* Description   | LIN Medium-priority periodic processing - Output         */
/* Preconditions | When processing medium-priority periodic process         */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_cs_st_BswMLinMainMO( void )
{
    BswM_Lin_MainFunctionMidOut();
}

/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_BswMLinUpdIPDUSt                          */
/* Description   | Request LIN I-PDU group update                           */
/* Preconditions | When processing medium-priority periodic process         */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_cs_st_BswMLinUpdIPDUSt( void )
{
    BswM_Lin_UpdateIPDUStatus();
}

#if ( BSW_BSWM_CS_ECU_FAIL == BSW_NOUSE )
/****************************************************************************/
/* Function Name | bsw_bswm_cs_st_BswMLinCheckRam                           */
/* Description   | Check RAM corruption for LIN-related components          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
void
bsw_bswm_cs_st_BswMLinCheckRam( void )
{
    BswM_Lin_CheckRam();
}
#endif /* ( BSW_BSWM_CS_ECU_FAIL == BSW_NOUSE ) */

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#endif /* ( BSW_BSWM_CS_FUNC_BSWMLIN == BSW_NOUSE ) */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2018/12/12                                             */
/*  v2-0-0          :2021/12/02                                             */
/*  v3-0-0          :2024/09/05                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
