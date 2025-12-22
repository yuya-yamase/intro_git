/* Dcm_Dsl_Main_c(v5-0-0)                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsl_Main/CODE                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../Dsl/inc/Dcm_Dsl_Main.h"

#include <Dcm/Dcm_Dsl_Ctrl.h>
#include "../../Dsl/inc/Dcm_Dsl_AuthMng.h"
#include "../../Dsl/inc/Dcm_Dsl_CommHandling.h"
#include "../../Dsl/inc/Dcm_Dsl_RxMsg.h"
#include "../../Dsl/inc/Dcm_Dsl_RxAbt.h"
#include "../../Dsl/inc/Dcm_Dsl_SessionMng.h"
#include "../../Dsl/inc/Dcm_Dsl_SecurityMng.h"
#include "../../Dsl/inc/Dcm_Dsl_TxMsg.h"
#include "../../Dsl/inc/Dcm_Dsl_TxIf.h"
#include "../../Dsl/inc/Dcm_Dsl_TxAbt.h"

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
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>


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
/* Function Name | Dcm_Dsl_Init                                             */
/* Description   | This function calls the initialization function          */
/*               | of the DSL unit.                                         */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_Init
(void)
{
#if( DCM_PAGEDBUFFER_ENABLED == STD_ON )
    Dcm_Dsl_TxMsg_Init();
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON  */
    Dcm_Dsl_TxIf_Init();
    Dcm_Dsl_RxMsg_Init();
    Dcm_Dsl_CmHdl_Init();
    Dcm_Dsl_SessionMng_Init();
    Dcm_Dsl_SecurityMng_Init();
#if( DCM_AUTHENTICATION_USE == STD_ON )
    Dcm_Dsl_AuthMng_Init();
#endif /* DCM_AUTHENTICATION_USE == STD_ON */
    Dcm_Dsl_TxAbt_Init();
    Dcm_Dsl_RxAbt_Init();
    Dcm_Dsl_Ctrl_Init();

    return ;
}

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2022-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
