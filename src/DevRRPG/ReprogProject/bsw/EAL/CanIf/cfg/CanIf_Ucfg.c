/* CanIf_Ucfg_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | CanIf/Ucfg/CODE                                             */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <CanIf.h>
#include "CanIf_Ucfg.h"
#include "CanIf_Local.h"


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
#define CANIF_START_SEC_VAR
#include <CanIf_MemMap.h>

#define CANIF_STOP_SEC_VAR
#include <CanIf_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define CANIF_START_SEC_CST
#include <CanIf_MemMap.h>

CONST(CanIf_ControllerSettingConfigType, CANIF_CONFIG_DATA) CanIf_Ucfg_ControllerSetting_Data[CANIF_UCFG_CONTROLLERNUM] = {
    {CANIF_UCFG_CANCONTROLLERID_0}
};

CONST(CanIf_RxPduSettingConfigType, CANIF_CONFIG_DATA) CanIf_Ucfg_RxPduSetting_Data[CANIF_UCFG_RXPDUNUM] = {
    {
        CANIF_UCFG_RXINDICATIONFUNC_0,
        CANIF_UCFG_RXPDUCANID_0,
        CANIF_RXPDUID_0,
        CANIF_UCFG_HRHINDX_0,
        CANIF_UCFG_RXPDUCANIDTYPE_0
    },
    {
        CANIF_UCFG_RXINDICATIONFUNC_1,
        CANIF_UCFG_RXPDUCANID_1,
        CANIF_RXPDUID_1,
        CANIF_UCFG_HRHINDX_1,
        CANIF_UCFG_RXPDUCANIDTYPE_1
    },
    {                                       /* ^^^ */
        CANIF_UCFG_RXINDICATIONFUNC_2,      /* ^^^ */
        CANIF_UCFG_RXPDUCANID_2,            /* ^^^ */
        CANIF_RXPDUID_2,                    /* ^^^ */
        CANIF_UCFG_HRHINDX_2,               /* ^^^ */
        CANIF_UCFG_RXPDUCANIDTYPE_2         /* ^^^ */
    },                                      /* ^^^ */
    {
        CANIF_UCFG_RXINDICATIONFUNC_3,      /* ^^^ */
        CANIF_UCFG_RXPDUCANID_3,            /* ^^^ */
        CANIF_RXPDUID_3,                    /* ^^^ */
        CANIF_UCFG_HRHINDX_3,               /* ^^^ */
        CANIF_UCFG_RXPDUCANIDTYPE_3         /* ^^^ */
    }                                       /* ^^^ */
};

CONST(CanIf_TxPduSettingConfigType, CANIF_CONFIG_DATA) CanIf_Ucfg_TxPduSetting_Data[CANIF_UCFG_TXPDUNUM] = {
    {
        CANIF_UCFG_TXCONFIRMATIONFUNC_0,
        CANIF_UCFG_TXPDUCANID_0,
        CANIF_TXPDUID_0,
        CANIF_UCFG_HTHINDX_0,
        CANIF_UCFG_TXPDUCANIDTYPE_0
    },                                      /* ^^^ */
    {                                       /* ^^^ */
        CANIF_UCFG_TXCONFIRMATIONFUNC_1,    /* ^^^ */
        CANIF_UCFG_TXPDUCANID_1,            /* ^^^ */
        CANIF_TXPDUID_1,                    /* ^^^ */
        CANIF_UCFG_HTHINDX_1,               /* ^^^ */
        CANIF_UCFG_TXPDUCANIDTYPE_1         /* ^^^ */
    }
};

#define CANIF_STOP_SEC_CST
#include <CanIf_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define CANIF_START_SEC_CODE
#include <CanIf_MemMap.h>


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/


#define CANIF_STOP_SEC_CODE
#include <CanIf_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/**** End of File *************************************************************/

