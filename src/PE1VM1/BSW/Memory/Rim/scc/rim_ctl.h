/* 1.3.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  RIM : CTL                                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef RIM_CTL_H
#define RIM_CTL_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RIM_CTL_H_MAJOR                          (1U)
#define RIM_CTL_H_MINOR                          (3U)
#define RIM_CTL_H_PATCH                          (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "rim_ctl_cfg.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Result */
#define RIM_RESULT_OK                            (0x00U)      /* OK                           */
#define RIM_RESULT_OK_REPAIRED                   (0x01U)      /* OK             (Data Repaired)            */
#define RIM_RESULT_NG                            (0x10U)      /* NG                           */
#define RIM_RESULT_NG_HARD                       (0x11U)      /* HARD Error                   */
#define RIM_RESULT_NG_DATA                       (0x12U)      /* DATA Error             (Can not Repaire)  */
#define RIM_RESULT_NG_PRM_ID                     (0x21U)      /* PRM:ID Error                 */
#define RIM_RESULT_NG_PRM_SIZE                   (0x22U)      /* PRM:Size Error               */
#define RIM_RESULT_NG_PRM_DATA_P                 (0x23U)      /* PRM:Data Pointer Error       */

#define RIM_RESULT_KIND_MASK                     (0xF0U)
#define RIM_RESULT_KIND_OK                       (0x00U)
#define RIM_RESULT_KIND_NG                       (0x10U)
#define RIM_RESULT_KIND_NG_PRM                   (0x20U)

/* RimId */
#define RIMID_RIMSIZE_SHIFT                      (14U)
#define RIMID_MODULE_ID_SHIFT                    (8U)
#define RIMID_DATA_ID_SHIFT                      (0U)

#define RIMID_RIMSIZE_MASK                       (0xC000U)
#define RIMID_MODULE_ID_MASK                     (0x0F00U)
#define RIMID_DATA_ID_MASK                       (0x00FFU)

#define RIM_MODULE_ID_NUM                        (16U)
#define RIM_DATA_ID_NUM                          (256U)

/* RimId:SIZE */
#define RIMID_RIMSIZE_1BYTE                      (0x0000U)
#define RIMID_RIMSIZE_2BYTE                      (0x4000U)
#define RIMID_RIMSIZE_4BYTE                      (0x8000U)
#define RIMID_RIMSIZE_OTHER                      (0xC000U)

/* RimId:ModuleId */
#define RIM_MOD_ID_0                             (0x0000U)    /*  RIM Module ID 0     */
#define RIM_MOD_ID_1                             (0x0100U)    /*  RIM Module ID 1     */
#define RIM_MOD_ID_2                             (0x0200U)    /*  RIM Module ID 2     */
#define RIM_MOD_ID_3                             (0x0300U)    /*  RIM Module ID 3     */
#define RIM_MOD_ID_4                             (0x0400U)    /*  RIM Module ID 4     */
#define RIM_MOD_ID_5                             (0x0500U)    /*  RIM Module ID 5     */
#define RIM_MOD_ID_6                             (0x0600U)    /*  RIM Module ID 6     */
#define RIM_MOD_ID_7                             (0x0700U)    /*  RIM Module ID 7     */
#define RIM_MOD_ID_8                             (0x0800U)    /*  RIM Module ID 8     */
#define RIM_MOD_ID_9                             (0x0900U)    /*  RIM Module ID 9     */
#define RIM_MOD_ID_10                            (0x0A00U)    /*  RIM Module ID 10    */
#define RIM_MOD_ID_11                            (0x0B00U)    /*  RIM Module ID 11    */
#define RIM_MOD_ID_12                            (0x0C00U)    /*  RIM Module ID 12    */
#define RIM_MOD_ID_13                            (0x0D00U)    /*  RIM Module ID 13    */
#define RIM_MOD_ID_14                            (0x0E00U)    /*  RIM Module ID 14    */
#define RIM_MOD_ID_15                            (0x0F00U)    /*  RIM Module ID 15    */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u2_g_RIM_GET_RIMSIZE(u2_a_ID)            ((u2_a_ID) & (U2)RIMID_RIMSIZE_MASK)
#define u1_g_RIM_GET_MODULE_ID(u2_a_ID)          ((U1)(((u2_a_ID) & (U2)RIMID_MODULE_ID_MASK) >> RIMID_MODULE_ID_SHIFT))
#define u1_g_RIM_GET_DATA_ID(u2_a_ID)            ((U1)((u2_a_ID) & (U2)RIMID_DATA_ID_MASK))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Externs                                                                                                        */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_Rim_BonInit(void);
void    vd_g_Rim_WkupInit(void);
void    vd_g_Rim_PostInit(void);
void    vd_g_Rim_DeInit(void);
void    vd_g_Rim_Task(void);

U1      u1_g_Rim_WkupRAMCheck(void);
U1      u1_g_Rim_TmrWkupRAMCheck(void);

void    vd_g_Rim_WriteU1(const U2 u2_a_ID, const U1 u1_a_DATA);
void    vd_g_Rim_WriteU2(const U2 u2_a_ID, const U2 u2_a_DATA);
void    vd_g_Rim_WriteU4(const U2 u2_a_ID, const U4 u4_a_DATA);
void    vd_g_Rim_WriteOther(const U2 u2_a_ID, const U2 u2_a_SIZE, const U1 * const u1_ap_DATA);

U1      u1_g_Rim_ReadU1withStatus(const U2 u2_a_ID, U1 *u1_ap_data);
U1      u1_g_Rim_ReadU2withStatus(const U2 u2_a_ID, U2 *u2_ap_data);
U1      u1_g_Rim_ReadU4withStatus(const U2 u2_a_ID, U4 *u4_ap_data);
U1      u1_g_Rim_ReadOtherwithStatus(const U2 u2_a_ID, const U2 u2_a_SIZE, U1 *u1_ap_data);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif /* RIM_CTL_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see rim_ctl.c                                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/
