/* 1.4.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Renesas RH850/U2A : I2C Interface                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef I2C_DRV_CFG_H
#define I2C_DRV_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define I2C_DRV_CFG_H_MAJOR                      (1)
#define I2C_DRV_CFG_H_MINOR                      (4)
#define I2C_DRV_CFG_H_PATCH                      (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include "int_drv.h"
#include "int_handler.h"
#include "gpt_busywait.h"

#include "i2c_drv.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define I2C_SAR_BIT_SVA0                         (0x0001U)
#define I2C_SAR_BIT_SVA                          (0x03feU)
#define I2C_SAR_BIT_FS                           (0x8000U)
#define I2C_SAR_BIT_CONST                        (0x83ffU)

#define I2C_SER_BIT_SAR0                         (0x01U)
#define I2C_SER_BIT_SAR1                         (0x02U)
#define I2C_SER_BIT_SAR2                         (0x04U)
#define I2C_SER_BIT_GCE                          (0x08U)
/* #define I2C_SER_BIT_DIDE                         (0x40U) */
#define I2C_SER_BIT_CONST                        (0x0fU)

/* #define I2C_MR1_BIT_BC                           (0x07U) */
/* #define I2C_MR1_BIT_BCWP                         (0x08U) */
#define I2C_MR1_BIT_CKS                          (0x70U)
/* #define I2C_MR1_BIT_MTWP                         (0x80U) */
#define I2C_MR1_BIT_CONST                        (0x70U)

#define I2C_MR2_BIT_TMOS                         (0x01U)
#define I2C_MR2_BIT_TMOL                         (0x02U)
#define I2C_MR2_BIT_TMOH                         (0x04U)
#define I2C_MR2_BIT_SDDL                         (0x70U)
#define I2C_MR2_BIT_DLCS                         (0x80U)
#define I2C_MR2_BIT_CONST                        (0xf7U)

#define I2C_MR3_BIT_NF                           (0x03U)
/* #define I2C_MR3_BIT_ACKBR                        (0x04U) */
/* #define I2C_MR3_BIT_ACKBT                        (0x08U) */
/* #define I2C_MR3_BIT_ACKWP                        (0x10U) */
/* #define I2C_MR3_BIT_RDRFS                        (0x20U) */
/* #define I2C_MR3_BIT_WAIT                         (0x40U) */
#define I2C_MR3_BIT_CONST                        (0x03U)   /* const                */

#define I2C_BRL_BIT_BRL                          (0x1fU)
#define I2C_BRL_BIT_CONST                        (0x1fU)   /* const                */

#define I2C_BRH_BIT_BRH                          (0x1fU)
#define I2C_BRH_BIT_CONST                        (0x1fU)

#define I2C_FER_BIT_TMOE                         (0x01U)
#define I2C_FER_BIT_MALE                         (0x02U)
#define I2C_FER_BIT_NALE                         (0x04U)
#define I2C_FER_BIT_SALE                         (0x08U)
/* #define I2C_FER_BIT_NACKE                        (0x10U) */
#define I2C_FER_BIT_NFE                          (0x20U)
#define I2C_FER_BIT_SCLE                         (0x40U)
#define I2C_FER_BIT_CONST                        (0x6fU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    volatile U4 *       u4p_rbase;

    U2                  u2_irq_ee;      /* INTRIICnEE  / Error or Event                        */
    U2                  u2_irq_rx;      /* INTRIICnRI  / Rx Buffer Full                        */
    U2                  u2_irq_tx;      /* INTRIICnTI  / Tx Buffer Empty                       */
    U2                  u2_irq_te;      /* INTRIICnTEI / Tx End                                */

    U2                  u2_bw_scl;      /* Gpt_BusyWait for Recovery from Sync. Lost and       */ 
                                        /*                           Stop->Start Condition Tx  */ 
                                        /* see gpt_busywait.h regarding the time resolution.   */ 

    U2                  u2_sar0;        /* RIICnSARy I2C Slave Address Register y (y = 0 to 2) */
    U2                  u2_sar1;
    U2                  u2_sar2;

    U1                  u1_ser;         /* RIICnSER   I2C Bus Status Enable Register           */
    U1                  u1_mr1;         /* RIICnMR1   I2C Bus Mode Register 1                  */
    U1                  u1_mr2;         /* RIICnMR2   I2C Bus Mode Register 2                  */
    U1                  u1_mr3;         /* RIICnMR3   I2C Bus Mode Register 3                  */

    U1                  u1_brl;         /* RIICnBRL   I2C Bus Bit Rate Low-Level Register      */
    U1                  u1_brh;         /* RIICnBRH   I2C Bus Bit Rate High-Level Register     */
    U1                  u1_fer;         /* RIICnFER   I2C Bus Function Enable Register         */

    U1                  u1_clo_max;     /* see vd_g_I2cMasReset(const U1 u1_a_I2C_CH)          */
}ST_I2C_CH;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const ST_I2C_CH             st_gp_I2C_CH_CFG[];
extern const U1                    u1_g_I2C_NUM_CH;

#endif      /* I2C_DRV_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see i2c_drv.c                                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/
