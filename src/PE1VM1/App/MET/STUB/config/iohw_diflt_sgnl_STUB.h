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
#define IOHW_DISGNL_IGN__3P8V                    (U2_MAX)   /* Warning Chime/Buzzer     */
#define IOHW_DISGNL_IGN__7V                      (U2_MAX)   /* Vehicle Operational Mode */
#define IOHW_DISGNL_IGN_10P5V                    (U2_MAX)   /* Diag Trouble Code Record */
#define IOHW_DISGNL_RHEO_UP                      (U2_MAX)   /* RHEOSTAT_UP              */
#define IOHW_DISGNL_RHEO_DN                      (U2_MAX)   /* RHEOSTAT_DOWN            */
#define IOHW_DISGNL_HAZARD                       (U2_MAX)   /* HAZARD                   */
#define IOHW_DISGNL_PMIC_INT_6                   (U2_MAX)   /* PMIC_INT                 */
#define IOHW_DISGNL_ODO                          (U2_MAX)   /* ODO_SW                   */
#define IOHW_DISGNL_B_MONI_3P6V                  (U2_MAX)   /* SWB_MONI_3P6V            */
#define IOHW_DISGNL_B_MONI_7P2V_6                (U2_MAX)   /* SWB_MONI_7P2V            */
#define IOHW_DISGNL_B_MONI_6P7V_6                (U2_MAX)  /* SWB_MONI_6P7V            */
#define IOHW_DISGNL_IGN__7P2V_6                  (U2_MAX)  /* IG_MONI_7P2V             */
#define IOHW_DISGNL_IGN__6P7V_6                  (U2_MAX)  /* IG_MONI_6P7V             */
#define IOHW_DISGNL_PMIC_INT_20                  (U2_MAX)  /* PMIC_INT                 */
#define IOHW_DISGNL_PMIC_VIN_6                   (U2_MAX)  /* PMIC_VIN_MONI            */
#define IOHW_DISGNL_PMIC_VIN_20                  (U2_MAX)  /* PMIC_VIN_MONI            */
#define IOHW_DISGNL_LID_IN                       (U2_MAX)  /* LID_IN                   */
#define IOHW_DISGNL_TURN_L_IN                    (U2_MAX)  /* TURN_L_IN                */
#define IOHW_DISGNL_TURN_R_IN                    (U2_MAX)  /* TURN_R_IN                */
#define IOHW_DISGNL_HUD_MAIN_SW_IN               (U2_MAX)  /* HUD_MAIN_SW_IN           */
#define IOHW_DISGNL_RHEOSTAT_DOWN_SW             (U2_MAX)  /* RHEOSTAT_DOWN_SW         */
#define IOHW_DISGNL_TAIL_CANCEL_IN               (U2_MAX)  /* TAIL_CANCEL_IN           */
#define IOHW_DISGNL_RCAR_COM_EN                  (U2_MAX)  /* RCAR_COM_EN              */

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

#define IOHW_DIFLT_DIGR_UB_MIS                   (U2_MAX)  /* user button : odo/trip select, dimming up/down */
#define IOHW_DIFLT_DIGR_UB_STE                   (U2_MAX)

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
