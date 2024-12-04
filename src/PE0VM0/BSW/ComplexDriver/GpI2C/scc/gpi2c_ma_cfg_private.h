/* 1.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  General Purpose I2C Communication / Master                                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef GP_I2C_MA_CFG_H
#define GP_I2C_MA_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GP_I2C_MA_CFG_H_MAJOR                    (1)
#define GP_I2C_MA_CFG_H_MINOR                    (1)
#define GP_I2C_MA_CFG_H_PATCH                    (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "gpi2c_ma.h"

/* #include "port_drv.h" */
#include "i2c_drv.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GP_I2C_MA_SEQ_STA                        (0U)                           /* Seq. STArt     / start condition                  */
#define GP_I2C_MA_SEQ_WRI                        (1U)                           /* Seq. WRIte     / write operation                  */
#define GP_I2C_MA_SEQ_WEN                        (2U)                           /* Seq. Write ENd / write operation                  */
#define GP_I2C_MA_SEQ_REA                        (3U)                           /* Seq. REAd      / read  operation                  */
#define GP_I2C_MA_SEQ_RLA                        (4U)                           /* Seq. REAd LAst / read  operation                  */
#define GP_I2C_MA_SEQ_FIN                        (5U)                           /* Seq. FINish    / stop  condition                  */
#define GP_I2C_MA_SEQ_REQ                        (6U)                           /* Seq. REQuest   / wait for request                 */

#define GP_I2C_MA_SEQ_INA                        (0xffffU)                      /* inactive                                          */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Event and State */
#define GP_I2C_MA_EAS_SEQ_ABT                    (0x00000002U)
#define GP_I2C_MA_EAS_REQ_NEX                    (0x00000001U)
#define GP_I2C_MA_EAS_RWC_MAX                    (0x00000001U)                  /* read/write count max                              */
#define GP_I2C_MA_EAS_OPE_REA                    (0x00000001U)
#define GP_I2C_MA_EAS_REA_RUN                    (0x00000001U)                  /* read operation is in run                          */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GP_I2C_MA_RWC_DMA_WRI                    (0U)                           /* >= 2U                                             */
#define GP_I2C_MA_RWC_DMA_REA                    (0U)                           /* >= 4U                                             */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u2_GP_I2C_MA_FRT(us0p1)                  ((U2)(((U4)(us0p1) + (U4)127U) >> 7U))
                                                                                /* see gpi2c_ma_if.h about free-run timer resolution */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    ST_GP_I2C_MA_REQ * const     stp_QUE;                    /* PDU TRx Req. FIFO/Queue      */

    U2                           u2_nque;                    /* size of stp_QUE              */
    U2                           u2_fr_tout;                 /* frame timout                 */

    U2                           u2_scl_act;
    U2                           u2_sda_act;
    U2                           u2_scl_ina;
    U2                           u2_sda_ina;

    U1                           u1_i2c_ch;
    U1                           u1_dma_ch;
}ST_GP_I2C_MA_CH;

typedef struct{
    volatile U2                  u2_req;
    volatile U2                  u2_run;
    U2                           u2_ack;

    U2                           u2_frt;
    U2                           u2_rwc;                     /* read/write byte count        */
    volatile U2                  u2_seq;
}ST_GP_I2C_MA_CTRL;

typedef struct{
    void ( * const               fp_vd_ACK)(const ST_GP_I2C_MA_REQ * st_ap_ACK);
    const ST_GP_I2C_MA_CH *      stp_CH;
    ST_GP_I2C_MA_CTRL * const    stp_CTRL;
    U2                           u2_rwc_max;                 /* read/write byte count limit  */
}ST_GP_I2C_MA_SLA;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern ST_GP_I2C_MA_CTRL          st_gp_gpi2c_ma_ctrl[];
extern U2                         u2_gp_gpi2c_ma_rwc_by_sla[];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_GpI2cMaCfgInit(void);
U1      u1_g_GpI2cMaCfgSlaActvtd(const U1 u1_a_CH);               /* Return : TRUE = Activated   */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const ST_GP_I2C_MA_CH      st_gp_GP_I2C_MA_CH[];
extern const U1                   u1_g_GP_I2C_MA_NUM_CH;

#if ((GP_I2C_MA_RWC_DMA_WRI >= 2U) || (GP_I2C_MA_RWC_DMA_REA >=4U))
extern const U1                   u1_g_GP_I2C_MA_DMA_NUM_CH;
#endif /* #if ((GP_I2C_MA_RWC_DMA_WRI >= 2U) || (GP_I2C_MA_RWC_DMA_REA >=4U)) */

extern const ST_GP_I2C_MA_SLA     st_gp_GP_I2C_MA_SLA[];
extern const U1                   u1_g_GP_I2C_MA_NUM_SLA;

#endif      /* GP_I2C_MA_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  gpi2c_ma.c                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
