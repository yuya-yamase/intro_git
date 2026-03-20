/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  CAN L-PDU FIFO/Queue                                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CAN_LPFQ_CFG_C_MAJOR                     (1)
#define CAN_LPFQ_CFG_C_MINOR                     (0)
#define CAN_LPFQ_CFG_C_PATCH                     (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "can_lpfq_cfg_private.h"
#include "Os.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((CAN_LPFQ_CFG_C_MAJOR != CAN_LPFQ_CFG_H_MAJOR) || \
     (CAN_LPFQ_CFG_C_MINOR != CAN_LPFQ_CFG_H_MINOR) || \
     (CAN_LPFQ_CFG_C_PATCH != CAN_LPFQ_CFG_H_PATCH))
#error "can_lpfq_cfg.c and can_lpfq_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CAN_LPFQ_QUE_NWORD_0            (270U)    /*  0 = PHY_TX_G2M1_P0 : # of message = 27 / data length max = 32 */
#define CAN_LPFQ_QUE_NWORD_1            (972U)    /*  1 = PHY_TX_G2M1_P1 : # of message = 54 / data length max = 64 */
#define CAN_LPFQ_QUE_NWORD_2            (420U)    /*  2 = PHY_TX_G2M1_P2 : # of message = 42 / data length max = 32 */
#define CAN_LPFQ_QUE_NWORD_3            (420U)    /*  3 = PHY_TX_G2M1_P3 : # of message = 42 / data length max = 32 */
#define CAN_LPFQ_QUE_NWORD_4            (240U)    /*  4 = PHY_TX_G2M1_P4 : # of message = 24 / data length max = 32 */
#define CAN_LPFQ_QUE_NWORD_5            (270U)    /*  5 = PHY_TX_G2M1_P5 : # of message = 27 / data length max = 32 */
#define CAN_LPFQ_QUE_NWORD_6            (240U)    /*  6 = PHY_TX_G2M1_P6 : # of message = 24 / data length max = 32 */
#define CAN_LPFQ_QUE_NWORD_7            (360U)    /*  7 = PHY_TX_G2M1_P7 : # of message = 36 / data length max = 32 */
#define CAN_LPFQ_QUE_NWORD_8            (420U)    /*  8 = PHY_TX_G5M__P0 : # of message = 42 / data length max = 32 */
#define CAN_LPFQ_QUE_NWORD_9            (450U)    /*  9 = PHY_TX_G5M__P1 : # of message = 45 / data length max = 32 */
#define CAN_LPFQ_QUE_NWORD_10           (756U)    /* 10 = PHY_TX_G5M__P2 : # of message = 42 / data length max = 64 */
#define CAN_LPFQ_QUE_NWORD_11           (180U)    /* 11 = PHY_TX_G5M__P3 : # of message = 18 / data length max = 32 */
#define CAN_LPFQ_QUE_NWORD_12           (12U)     /* 12 = PHY_TX_LOCA_P0 : # of message =  3 / data length max =  8 */
#define CAN_LPFQ_QUE_NWORD_13           (12U)	  /* 13 = PHY_TX_G2M2_P0 : # of message =  3 / data length max =  8 */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
ST_CAN_LPFQ_RWCT          st_gp_can_lpfq_rwct[CAN_LPFQ_NUM_CH];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4                 u4_sp_can_lpfq_que_0[CAN_LPFQ_QUE_NWORD_0];
static U4                 u4_sp_can_lpfq_que_1[CAN_LPFQ_QUE_NWORD_1];
static U4                 u4_sp_can_lpfq_que_2[CAN_LPFQ_QUE_NWORD_2];
static U4                 u4_sp_can_lpfq_que_3[CAN_LPFQ_QUE_NWORD_3];
static U4                 u4_sp_can_lpfq_que_4[CAN_LPFQ_QUE_NWORD_4];
static U4                 u4_sp_can_lpfq_que_5[CAN_LPFQ_QUE_NWORD_5];
static U4                 u4_sp_can_lpfq_que_6[CAN_LPFQ_QUE_NWORD_6];
static U4                 u4_sp_can_lpfq_que_7[CAN_LPFQ_QUE_NWORD_7];
static U4                 u4_sp_can_lpfq_que_8[CAN_LPFQ_QUE_NWORD_8];
static U4                 u4_sp_can_lpfq_que_9[CAN_LPFQ_QUE_NWORD_9];
static U4                 u4_sp_can_lpfq_que_10[CAN_LPFQ_QUE_NWORD_10];
static U4                 u4_sp_can_lpfq_que_11[CAN_LPFQ_QUE_NWORD_11];
static U4                 u4_sp_can_lpfq_que_12[CAN_LPFQ_QUE_NWORD_12];
static U4                 u4_sp_can_lpfq_que_13[CAN_LPFQ_QUE_NWORD_13];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_CAN_LPFQ_CH      st_gp_CAN_LPFQ_CH[CAN_LPFQ_NUM_CH] = {
    /* u4p_QUE,                     u2_nque                   u2_ovwr                                                    */
    {&u4_sp_can_lpfq_que_0[0U],  (U2)CAN_LPFQ_QUE_NWORD_0,  (U2)CAN_LPFQ_OVWR_EN},  /* CAN_LPFQ_CH_PHY_TX_G2M1_P0  (0U)  */
    {&u4_sp_can_lpfq_que_1[0U],  (U2)CAN_LPFQ_QUE_NWORD_1,  (U2)CAN_LPFQ_OVWR_EN},  /* CAN_LPFQ_CH_PHY_TX_G2M1_P1  (1U)  */
    {&u4_sp_can_lpfq_que_2[0U],  (U2)CAN_LPFQ_QUE_NWORD_2,  (U2)CAN_LPFQ_OVWR_EN},  /* CAN_LPFQ_CH_PHY_TX_G2M1_P2  (2U)  */
    {&u4_sp_can_lpfq_que_3[0U],  (U2)CAN_LPFQ_QUE_NWORD_3,  (U2)CAN_LPFQ_OVWR_EN},  /* CAN_LPFQ_CH_PHY_TX_G2M1_P3  (3U)  */
    {&u4_sp_can_lpfq_que_4[0U],  (U2)CAN_LPFQ_QUE_NWORD_4,  (U2)CAN_LPFQ_OVWR_EN},  /* CAN_LPFQ_CH_PHY_TX_G2M1_P4  (4U)  */
    {&u4_sp_can_lpfq_que_5[0U],  (U2)CAN_LPFQ_QUE_NWORD_5,  (U2)CAN_LPFQ_OVWR_EN},  /* CAN_LPFQ_CH_PHY_TX_G2M1_P5  (5U)  */
    {&u4_sp_can_lpfq_que_6[0U],  (U2)CAN_LPFQ_QUE_NWORD_6,  (U2)CAN_LPFQ_OVWR_EN},  /* CAN_LPFQ_CH_PHY_TX_G2M1_P6  (6U)  */
    {&u4_sp_can_lpfq_que_7[0U],  (U2)CAN_LPFQ_QUE_NWORD_7,  (U2)CAN_LPFQ_OVWR_EN},  /* CAN_LPFQ_CH_PHY_TX_G2M1_P7  (7U)  */

    {&u4_sp_can_lpfq_que_8[0U],  (U2)CAN_LPFQ_QUE_NWORD_8,  (U2)CAN_LPFQ_OVWR_EN},  /* CAN_LPFQ_CH_PHY_TX_G5M__P8  (8U)  */
    {&u4_sp_can_lpfq_que_9[0U],  (U2)CAN_LPFQ_QUE_NWORD_9,  (U2)CAN_LPFQ_OVWR_EN},  /* CAN_LPFQ_CH_PHY_TX_G5M__P9  (9U)  */
    {&u4_sp_can_lpfq_que_10[0U], (U2)CAN_LPFQ_QUE_NWORD_10, (U2)CAN_LPFQ_OVWR_EN},  /* CAN_LPFQ_CH_PHY_TX_G5M__P10 (10U) */
    {&u4_sp_can_lpfq_que_11[0U], (U2)CAN_LPFQ_QUE_NWORD_11, (U2)CAN_LPFQ_OVWR_EN},  /* CAN_LPFQ_CH_PHY_TX_G5M__P11 (11U) */

    {&u4_sp_can_lpfq_que_12[0U], (U2)CAN_LPFQ_QUE_NWORD_12, (U2)CAN_LPFQ_OVWR_EN},   /* CAN_LPFQ_CH_PHY_TX_LOCA_P12 (12U) */

    {&u4_sp_can_lpfq_que_13[0U], (U2)CAN_LPFQ_QUE_NWORD_13, (U2)CAN_LPFQ_OVWR_EN}   /* CAN_LPFQ_CH_PHY_TX_G2M2_P0  (13U) */
};
const U2                  u2_g_CAN_LPFQ_NUM_CH = (U2)CAN_LPFQ_NUM_CH;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U4      u4_g_CANLpFq_IRQ_DI(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4      u4_g_CANLpFq_IRQ_DI(void)
{
    SuspendAllInterrupts();
    return((U4)0U);
}
/*===================================================================================================================================*/
/*  void    vd_g_CANLpFq_IRQ_EI(const U4 u4_a_GLI)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_CANLpFq_IRQ_EI(const U4 u4_a_GLI)
{
    ResumeAllInterrupts();
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     3/18/2025  TN       New.                                                                                               */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
