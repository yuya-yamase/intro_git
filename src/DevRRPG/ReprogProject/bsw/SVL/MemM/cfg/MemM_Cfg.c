/* MemM_Cfg_c_Revision(v3.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | MemM/Cfg/CODE                                               */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <MemM.h>
#include "MemM_Local.h"
#include "MemM_Cfg.h"
#include "MemM_Ucfg.h"


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
#define MEMM_START_SEC_VAR
#include <MemM_MemMap.h>

#define MEMM_STOP_SEC_VAR
#include <MemM_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define MEMM_START_SEC_CST
#include <MemM_MemMap.h>

static CONST(MemM_TimerConfigType, MEMM_CONFIG_DATA) MemM_Cfg_TimerData = {
    /* TimeoutValue in erasing phase */
    {
        MEMM_UCFG_ERASETIME_CODEFLS,
        MEMM_UCFG_ERASETIME_EXTCODEFLS
    },
    /* TimeoutValue in writing phase */
    {
        MEMM_UCFG_WRITETIME_CODEFLS,
        MEMM_UCFG_WRITETIME_EXTCODEFLS,
        MEMM_UCFG_WRITETIME_CODERAM
    },
    /* TimeoutValue in reading phase */
    {
        MEMM_UCFG_READTIME_CODEFLS,
        MEMM_UCFG_READTIME_EXTCODEFLS,
        MEMM_UCFG_READTIME_CODERAM
    },
    /* TimeoutValue in Reprog complete phase */
    {
        MEMM_UCFG_RPGCMPLTTIME
    }
};

static CONST(MemM_GrntConfigType, MEMM_CONFIG_DATA) MemM_Cfg_GrntData[MEMM_GRNT_MODE_NUM] = {
    /* No_1 : MEMM_GRNT_MODE_KEYWORDSTAMP */
    {
        {
            MEMM_CFG_GRNT_INVALIDVALUE,
            MEMM_ERASE_GRNTACT_ERASE,
            MEMM_GRNT_AREA_1ST
        },
        {
            {
                { MEMM_INVALID_GRNT_VALUE, MEMM_WRITE_GRNT_AREA_NOT_SKIP },
                { MEMM_INVALID_GRNT_VALUE, MEMM_WRITE_GRNT_AREA_NOT_SKIP }
            }
        },
        {
            MEMM_CFG_GRNT_VALIDVALUE
        }
    },
    /* No_2 : MEMM_GRNT_MODE_FLASHSTATUS1 */
    {
        {
            MEMM_CFG_GRNT_INVALIDVALUE,
            MEMM_ERASE_GRNTACT_WRITE,
            MEMM_GRNT_AREA_2ND
        },
        {
            {
                { MEMM_CFG_GRNT_EXPECTEDVALUE_1ST, MEMM_WRITE_GRNT_AREA_SKIP },
                { MEMM_CFG_GRNT_EXPECTEDVALUE_2ND, MEMM_WRITE_GRNT_AREA_SKIP }
            }
        },
        {
            MEMM_CFG_GRNT_VALIDVALUE
        }
    },
    /* No_3 : MEMM_GRNT_MODE_FLASHSTATUS2 */
    {
        {
            MEMM_CFG_GRNT_INVALIDVALUE,
            MEMM_ERASE_GRNTACT_WRITE,
            MEMM_GRNT_AREA_2ND
        },
        {
            {
                { MEMM_CFG_GRNT_EXPECTEDVALUE_1ST, MEMM_WRITE_GRNT_AREA_SKIP },
                { MEMM_INVALID_GRNT_VALUE,         MEMM_WRITE_GRNT_AREA_NOT_SKIP }
            }
        },
        {
            MEMM_CFG_GRNT_VALIDVALUE
        }
    },
    /* No_4 : MEMM_GRNT_MODE_FLASHSTATUS3 */
    {
        {
            MEMM_CFG_GRNT_INVALIDVALUE,
            MEMM_ERASE_GRNTACT_WRITE,
            MEMM_GRNT_AREA_1ST
        },
        {
            {
                { MEMM_CFG_GRNT_EXPECTEDVALUE_1ST, MEMM_WRITE_GRNT_AREA_SKIP },
                { MEMM_INVALID_GRNT_VALUE,         MEMM_WRITE_GRNT_AREA_NOT_SKIP }
            }
        },
        {
            MEMM_CFG_GRNT_VALIDVALUE
        }
    },
    /* No_5 : MEMM_GRNT_MODE_FLASHSTATUS4 */
    {
        {
            MEMM_CFG_GRNT_INVALIDVALUE,
            MEMM_ERASE_GRNTACT_NONE,
            MEMM_GRNT_AREA_NONE
        },
        {
            {
                { MEMM_CFG_GRNT_EXPECTEDVALUE_1ST, MEMM_WRITE_GRNT_AREA_SKIP },
                { MEMM_INVALID_GRNT_VALUE,         MEMM_WRITE_GRNT_AREA_NOT_SKIP }
            }
        },
        {
            MEMM_CFG_GRNT_VALIDVALUE
        }
    }
};

CONST(MemM_ConfigType, MEMM_CONFIG_DATA) MemM_Cfg_Data = {
    &MemM_Ucfg_MemoryAreaData[0],
    &MemM_Cfg_TimerData,
    &MemM_Cfg_GrntData[0],
    MEMM_CFG_GRNT_AREA_SIZE,
    MEMM_UCFG_KEYWORD_BLOCK_SIZE,
    MEMM_UCFG_GRNT_MODE,
    MEMM_UCFG_MEMORY_AREA_NUM
};

#define MEMM_STOP_SEC_CST
#include <MemM_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define MEMM_START_SEC_CODE
#include <MemM_MemMap.h>


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/
#define MEMM_STOP_SEC_CODE
#include <MemM_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2018/10/23 :Update                                rel.AUBASS */
/*  v3.00       :2019/12/03 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

