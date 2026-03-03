/* 3.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Seatbelt reminder warning                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef SBLTWRN_H
#define SBLTWRN_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SBLTWRN_H_MAJOR                         (3)
#define SBLTWRN_H_MINOR                         (1)
#define SBLTWRN_H_PATCH                         (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SBLTWRN_NUM_COL                         (3U)
#define SBLTWRN_NUM_ROW                         (4U)
#define SBLTWRN_NUM_ALLSEAT                     (SBLTWRN_NUM_COL * SBLTWRN_NUM_ROW)

#define SBLTWRN_DRV_SEAT                        (0U)
#define SBLTWRN_FRC_SEAT                        (1U)
#define SBLTWRN_PSG_SEAT                        (2U)
#define SBLTWRN_R2L_SEAT                        (3U)
#define SBLTWRN_R2C_SEAT                        (4U)
#define SBLTWRN_R2R_SEAT                        (5U)
#define SBLTWRN_R3L_SEAT                        (6U)
#define SBLTWRN_R3C_SEAT                        (7U)
#define SBLTWRN_R3R_SEAT                        (8U)
#define SBLTWRN_R4L_SEAT                        (9U)
#define SBLTWRN_R4C_SEAT                        (10U)
#define SBLTWRN_R4R_SEAT                        (11U)

#define SBLTWRN_STS_ERR                         (0xFFU)

#define SBLTWRN_NUM_CHMSTS                      (10U)
#define SBLTWRN_CHMSTS_OFF                      (0U)
#define SBLTWRN_CHMSTS_LGLPR                    (1U)
#define SBLTWRN_CHMSTS_LEGAL                    (2U)
#define SBLTWRN_CHMSTS_LGLWT                    (3U)
#define SBLTWRN_CHMSTS_LGLCMP                   (4U)
#define SBLTWRN_CHMSTS_UNBKNT                   (5U)
#define SBLTWRN_CHMSTS_GP                       (6U)
#define SBLTWRN_CHMSTS_LV1                      (7U)
#define SBLTWRN_CHMSTS_LV2                      (8U)
#define SBLTWRN_CHMSTS_L2CMP                    (9U)

#define SBLTWRN_NUM_CHMSTS_FM                   (10U)
#define SBLTWRN_CHMSTS_OFF_FM                   (0U)
#define SBLTWRN_CHMSTS_INIPR_FM                 (1U)
#define SBLTWRN_CHMSTS_INITIAL_FM               (2U)
#define SBLTWRN_CHMSTS_INICMP_FM                (3U)
#define SBLTWRN_CHMSTS_UNBKNT_FM                (4U)
#define SBLTWRN_CHMSTS_UNBKCMP_FM               (5U)
#define SBLTWRN_CHMSTS_LV1_FM                   (6U)
#define SBLTWRN_CHMSTS_LV2_FM                   (7U)
#define SBLTWRN_CHMSTS_L2INT_FM                 (8U)
#define SBLTWRN_CHMSTS_L2CMP_FM                 (9U)

#define SBLTWRN_CHMSTS_KEEP                     (255U)

#define SBLTWRN_NUM_TTSTS                       (19U)
#define SBLTWRN_TTSTS_OFF                       (0U)
#define SBLTWRN_TTSTS_LGLPR                     (1U)
#define SBLTWRN_TTSTS_LEGAL                     (2U)
#define SBLTWRN_TTSTS_LGLWT                     (3U)
#define SBLTWRN_TTSTS_LGLCMP                    (4U)
#define SBLTWRN_TTSTS_FR_LV1                    (5U)
#define SBLTWRN_TTSTS_FR_LV2                    (6U)
#define SBLTWRN_TTSTS_FR_L2CMP                  (7U)
#define SBLTWRN_TTSTS_FR_PARK                   (8U)
#define SBLTWRN_TTSTS_FR_LWSP                   (9U)
#define SBLTWRN_TTSTS_IGON                      (10U)
#define SBLTWRN_TTSTS_DOOR                      (11U)
#define SBLTWRN_TTSTS_RR_PARK                   (12U)
#define SBLTWRN_TTSTS_RR_LV1                    (13U)
#define SBLTWRN_TTSTS_RR_LV2                    (14U)
#define SBLTWRN_TTSTS_RR_L2CMP_ON               (15U)
#define SBLTWRN_TTSTS_RR_L2CMP_OFF              (16U)
#define SBLTWRN_TTSTS_RR_LWSP                   (17U)
#define SBLTWRN_TTSTS_SYNC                      (18U)

#define SBLTWRN_NUM_TTSTS_FM                    (11U)
#define SBLTWRN_TTSTS_OFF_FM                    (0U)
#define SBLTWRN_TTSTS_INIPR_FM                  (1U)
#define SBLTWRN_TTSTS_INITIAL_FM                (2U)
#define SBLTWRN_TTSTS_INICMP_FM                 (3U)
#define SBLTWRN_TTSTS_IGON_FM                   (4U)
#define SBLTWRN_TTSTS_DOOR_FM                   (5U)
#define SBLTWRN_TTSTS_UNBKNT_FM                 (6U)
#define SBLTWRN_TTSTS_LV1_FM                    (7U)
#define SBLTWRN_TTSTS_LV2_FM                    (8U)
#define SBLTWRN_TTSTS_L2INT_FM                  (9U)
#define SBLTWRN_TTSTS_L2CMP_FM                  (10U)

#define SBLTWRN_TTSTS_KEEP                      (255U)

#define SBLTWRN_DRV_SEAT_BIT_IDX0               (0x80U)
#define SBLTWRN_FRC_SEAT_BIT_IDX0               (0x40U)
#define SBLTWRN_PSG_SEAT_BIT_IDX0               (0x20U)
#define SBLTWRN_R2R_SEAT_BIT_IDX0               (0x10U)
#define SBLTWRN_R2C_SEAT_BIT_IDX0               (0x08U)
#define SBLTWRN_R2L_SEAT_BIT_IDX0               (0x04U)
#define SBLTWRN_R3R_SEAT_BIT_IDX0               (0x02U)
#define SBLTWRN_R3C_SEAT_BIT_IDX0               (0x01U)
#define SBLTWRN_R3L_SEAT_BIT_IDX1               (0x80U)

#define SBLTWRN_BKLSTS_BCKL                     (0x00U)
#define SBLTWRN_BKLSTS_UNBCKLFLG                (0x01U)
#define SBLTWRN_BKLSTS_UNBCKL                   (0x02U)
#define SBLTWRN_BKLSTS_UNBCKLEDG                (0x04U)
#define SBLTWRN_BKLSTS_COMFAIL                  (0x08U)
#define SBLTWRN_BKLSTS_FIXUNBKL                 (0x10U)
#define SBLTWRN_BKLSTS_BCKLEDG                  (0x20U)
#define SBLTWRN_BKLSTS_FAILRSTEDG               (0x40U)         /* Turned from COMFAIL to NORMAL edge*/

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
void            vd_g_SbltwrnInit(void);
void            vd_g_SbltwrnMainTask(void);
U1              u1_g_SbltwrnChmStsBySeat(const U1 u1_a_SEATID);
U4              u4_g_SbltwrnTtSts(void);
U1              u1_g_SbltwrnTtStsBySeat(const U1 u1_a_SEATID);
U1              u1_g_SbltwrnDiagEvCapt(const U1 u1_a_ODO_UPDT, U4 * u4_ap_ss);
U1              u1_g_SbltwrnChmStsBySeat_FM(const U1 u1_a_SEATID);
U4              u4_g_SbltwrnTtSts_FM(void);
U1              u1_g_SbltwrnTtStsBySeat_FM(const U1 u1_a_SEATID);
U1              u1_g_SbltSeatBklStsBySeat(const U1 u1_a_SEATID);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#endif /* SBLTWRN_H */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  sbltwrn.c                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
