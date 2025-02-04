/* 1.4.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  IO Hardware Abstraction Digital Input Filter                                                                                     */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  WARNING :                                                                                                                        */
/*  iohw_dio_sgnl.h is included in iohw_diflt.h.                                                                                     */
/*  DO NOT include this file in any file even though this configuration header is public.                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define IOHW_DISGNL_IGN__3P8V                    (0U)   /* Warning Chime/Buzzer     */
#define IOHW_DISGNL_IGN__7V                      (1U)   /* Vehicle Operational Mode */
#define IOHW_DISGNL_IGN_10P5V                    (2U)   /* Diag Trouble Code Record */
#define IOHW_DISGNL_RHEO_UP                      (3U)   /* RHEOSTAT_UP              */
#define IOHW_DISGNL_RHEO_DN                      (4U)   /* RHEOSTAT_DOWN            */
#define IOHW_DISGNL_HAZARD                       (5U)   /* HAZARD                   */
#define IOHW_DISGNL_PMIC_INT_6                   (6U)   /* PMIC_INT                 */
#define IOHW_DISGNL_ODO                          (7U)   /* ODO_SW                   */
#define IOHW_DISGNL_B_MONI_3P6V                  (8U)   /* SWB_MONI_3P6V            */
#define IOHW_DISGNL_B_MONI_7P2V_6                (9U)   /* SWB_MONI_7P2V            */
#define IOHW_DISGNL_B_MONI_6P7V_6                (10U)  /* SWB_MONI_6P7V            */
#define IOHW_DISGNL_IGN__7P2V_6                  (11U)  /* IG_MONI_7P2V             */
#define IOHW_DISGNL_IGN__6P7V_6                  (12U)  /* IG_MONI_6P7V             */
#define IOHW_DISGNL_PMIC_INT_20                  (13U)  /* PMIC_INT                 */
#define IOHW_DISGNL_PMIC_VIN_6                   (14U)  /* PMIC_VIN_MONI            */
#define IOHW_DISGNL_PMIC_VIN_20                  (15U)  /* PMIC_VIN_MONI            */
#define IOHW_DISGNL_LID_IN                       (16U)  /* LID_IN                   */
#define IOHW_DISGNL_TURN_L_IN                    (17U)  /* TURN_L_IN                */
#define IOHW_DISGNL_TURN_R_IN                    (18U)  /* TURN_R_IN                */
#define IOHW_DISGNL_HUD_MAIN_SW_IN               (19U)  /* HUD_MAIN_SW_IN           */
#define IOHW_DISGNL_RHEOSTAT_DOWN_SW             (20U)  /* RHEOSTAT_DOWN_SW         */
#define IOHW_DISGNL_TAIL_CANCEL_IN               (21U)  /* TAIL_CANCEL_IN           */
#define IOHW_DISGNL_RCAR_COM_EN                  (22U)  /* RCAR_COM_EN              */

/* No Function Common Macro */
#define IOHW_DISGNL_EXHEAT                       (U2_MAX)  /* EXHAUST_HEAT_IN          */
#define IOHW_DISGNL_EXHEAT_OPT                   (U2_MAX)  /* EXHAUST_HEAT_EXIST       */
#define IOHW_DISGNL_STOP_LAMP                    (U2_MAX)  /* STOP_LAMP_IN             */
#define IOHW_DISGNL_OIL_P                        (U2_MAX)  /* OILP_IN                  */
#define IOHW_DISGNL_OILLVL                       (U2_MAX)  /* OIL_LEVEL_IN             */
#define IOHW_DISGNL_RR_BELT_C                    (U2_MAX)  /* RR_BELT_C_IN             */
#define IOHW_DISGNL_RR_BELT_L                    (U2_MAX)  /* RR_BELT_L_IN             */
#define IOHW_DISGNL_RR_BELT_R                    (U2_MAX)  /* RR_BELT_R_IN             */
#define BRAKE_LEVEL_IN                           (U2_MAX)  /* BRAKE_LEVEL_IN           */
#define IOHW_DISGNL_DBKL                         (U2_MAX)  /* DISGNL_DBKL              */
#define IOHW_DISGNL_IPD_FAIL                     (U2_MAX)  /* IPD_FAIL                 */
#define IOHW_DISGNL_OILLVL                       (U2_MAX)  /* OIL_LEVEL_IN             */
#define IOHW_DISGNL_STSW_BK                      (U2_MAX)  /* ST_SW_BACK               */
#define IOHW_DISGNL_STSW_EN                      (U2_MAX)  /* ST_SW_ENTER              */
#define IOHW_DISGNL_STSW_UP                      (U2_MAX)  /* ST_SW_UP                 */
#define IOHW_DISGNL_STSW_DN                      (U2_MAX)  /* ST_SW_DOWN               */
#define IOHW_DISGNL_STSW_LF                      (U2_MAX)  /* ST_SW_LEFT               */
#define IOHW_DISGNL_STSW_RT                      (U2_MAX)  /* ST_SW_RIGHT              */
#define IOHW_DISGNL_WLVL_IN                      (U2_MAX)  /* WASHER_LV_IN             */

/*-----------------------------------------------------------------------------------------------------------------------------------*/

#define IOHW_DIFLT_DIGR_UB_MIS                   (0U)  /* user button : odo/trip select, dimming up/down */
#define IOHW_DIFLT_DIGR_UB_STE                   (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see iohw_diflt_cfg.c                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/
