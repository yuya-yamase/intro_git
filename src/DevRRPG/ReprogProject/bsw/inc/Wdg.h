/* Wdg_h_Revision(v2.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Wdg/HEADER                                                  */
/******************************************************************************/
#ifndef WDG_H
#define WDG_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define WDG_MODULE_ID                   (0x06U)

#define WDG_API_ID_INIT                 (0x00U)
#define WDG_API_ID_SETTRIGGERCONDITION  (0x01U)
#define WDG_API_ID_DEINIT               (0x02U)
#define WDG_API_ID_TRIGGER              (0x03U)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef struct {
    U2  WdgMaxTimeout;
    U2  WdgInitialTimeout;
} Wdg_WdgSettingConfigType;

typedef struct {
    P2CONST(Wdg_WdgSettingConfigType, TYPEDEF, WDG_APPL_CONST) WdgSetting;
} Wdg_ConfigType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
FUNC(void, WDG_CODE_SLOW) Wdg_Init
(
    P2CONST(Wdg_ConfigType, AUTOMATIC, WDG_APPL_CONST) Config
);
FUNC(void, WDG_CODE_SLOW) Wdg_SetTriggerCondition
(
    VAR(U2, AUTOMATIC) Timeout
);
FUNC(void, WDG_CODE_SLOW) Wdg_Trigger (void);
FUNC(void, WDG_CODE_SLOW) Wdg_DeInit (void);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define WDG_START_SEC_CST
#include <Wdg_MemMap.h>

extern CONST(Wdg_ConfigType, WDG_CONFIG_DATA) WDG_CFG_DATA;

#define WDG_STOP_SEC_CST
#include <Wdg_MemMap.h>


#endif /* WDG_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2019/02/12 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

