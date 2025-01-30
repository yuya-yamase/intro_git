/* 1.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Multi-media rx multi frame message                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef MULMED_MULFR_H
#define MULMED_MULFR_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MULMED_MULFR_H_MAJOR                    (1)
#define MULMED_MULFR_H_MINOR                    (1)
#define MULMED_MULFR_H_PATCH                    (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MULMED_MULFR_STSBIT_VALID               (0x00U)                 /*  Valid                                                    */
#define MULMED_MULFR_STSBIT_UNKNOWN             (0x01U)                 /*  Unknown                                                  */
#define MULMED_MULFR_STSBIT_INVALID             (0x02U)                 /*  Invalid                                                  */

#define MULMED_MULFR_NUM_LINES                  (103U)
#define MULMED_MULFR_AVNMS01_L01                (  0U)
#define MULMED_MULFR_AVNMS02_L01                (  1U)
#define MULMED_MULFR_AVNMS03_L01                (  2U)
#define MULMED_MULFR_AVNMS04_L01                (  3U)
#define MULMED_MULFR_AVNMS05_L01                (  4U)
#define MULMED_MULFR_AVNMS06_L01                (  5U)
#define MULMED_MULFR_AVNMS07_L01                (  6U)
#define MULMED_MULFR_AVNMS08_L01                (  7U)
#define MULMED_MULFR_AVNMS09_L01                (  8U)
#define MULMED_MULFR_AVNMS10_L01                (  9U)
#define MULMED_MULFR_AVNMS13_L01                ( 10U)
#define MULMED_MULFR_AVNMS13_L02                ( 11U)
#define MULMED_MULFR_AVNMS13_L03                ( 12U)
#define MULMED_MULFR_AVNMS13_L04                ( 13U)
#define MULMED_MULFR_AVNMS13_L05                ( 14U)
#define MULMED_MULFR_AVNMS13_L06                ( 15U)
#define MULMED_MULFR_AVNMS14_L01                ( 16U)
#define MULMED_MULFR_AVNMS14_L02                ( 17U)
#define MULMED_MULFR_AVNMS14_L03                ( 18U)
#define MULMED_MULFR_AVNMS14_L04                ( 19U)
#define MULMED_MULFR_AVNMS14_L05                ( 20U)
#define MULMED_MULFR_AVNMS14_L06                ( 21U)
#define MULMED_MULFR_AVNMS15_L01                ( 22U)
#define MULMED_MULFR_AVNMS15_L02                ( 23U)
#define MULMED_MULFR_AVNMS15_L03                ( 24U)
#define MULMED_MULFR_AVNMS15_L04                ( 25U)
#define MULMED_MULFR_AVNMS15_L05                ( 26U)
#define MULMED_MULFR_AVNMS15_L06                ( 27U)
#define MULMED_MULFR_AVNMS16_L01                ( 28U)
#define MULMED_MULFR_AVNMS16_L02                ( 29U)
#define MULMED_MULFR_AVNMS16_L03                ( 30U)
#define MULMED_MULFR_AVNMS16_L04                ( 31U)
#define MULMED_MULFR_AVNMS16_L05                ( 32U)
#define MULMED_MULFR_AVNMS16_L06                ( 33U)
#define MULMED_MULFR_AVNMS18_L01                ( 34U)
#define MULMED_MULFR_AVNMS18_L02                ( 35U)
#define MULMED_MULFR_AVNMS18_L03                ( 36U)
#define MULMED_MULFR_AVNMS18_L04                ( 37U)
#define MULMED_MULFR_AVNMS18_L05                ( 38U)
#define MULMED_MULFR_AVNMS18_L06                ( 39U)
#define MULMED_MULFR_AVNMS19_L01                ( 40U)
#define MULMED_MULFR_AVNMS19_L02                ( 41U)
#define MULMED_MULFR_AVNMS19_L03                ( 42U)
#define MULMED_MULFR_AVNMS19_L04                ( 43U)
#define MULMED_MULFR_AVNMS19_L05                ( 44U)
#define MULMED_MULFR_AVNMS19_L06                ( 45U)
#define MULMED_MULFR_AVNMS20_L01                ( 46U)
#define MULMED_MULFR_AVNMS20_L02                ( 47U)
#define MULMED_MULFR_AVNMS20_L03                ( 48U)
#define MULMED_MULFR_AVNMS20_L04                ( 49U)
#define MULMED_MULFR_AVNMS20_L05                ( 50U)
#define MULMED_MULFR_AVNMS20_L06                ( 51U)
#define MULMED_MULFR_AVNMS20_L07                ( 52U)
#define MULMED_MULFR_AVNMS20_L08                ( 53U)
#define MULMED_MULFR_AVNMS20_L09                ( 54U)
#define MULMED_MULFR_AVNMS20_L10                ( 55U)
#define MULMED_MULFR_AVNMS20_L11                ( 56U)
#define MULMED_MULFR_AVNMS20_L12                ( 57U)
#define MULMED_MULFR_AVNMS20_L13                ( 58U)
#define MULMED_MULFR_AVNMS20_L14                ( 59U)
#define MULMED_MULFR_AVNMS20_L15                ( 60U)
#define MULMED_MULFR_AVNMS20_L16                ( 61U)
#define MULMED_MULFR_AVNMS20_L17                ( 62U)
#define MULMED_MULFR_AVNMS20_L18                ( 63U)
#define MULMED_MULFR_AVNMS20_L19                ( 64U)
#define MULMED_MULFR_AVNMS20_L20                ( 65U)
#define MULMED_MULFR_AVNMS20_L21                ( 66U)
#define MULMED_MULFR_AVNMS20_L22                ( 67U)
#define MULMED_MULFR_AVNMS20_L23                ( 68U)
#define MULMED_MULFR_AVNMS21_L01                ( 69U)
#define MULMED_MULFR_AVNMS21_L02                ( 70U)
#define MULMED_MULFR_AVNMS21_L03                ( 71U)
#define MULMED_MULFR_AVNMS21_L04                ( 72U)
#define MULMED_MULFR_AVNMS21_L05                ( 73U)
#define MULMED_MULFR_AVNMS22_L01                ( 74U)
#define MULMED_MULFR_AVNMS22_L02                ( 75U)
#define MULMED_MULFR_AVNMS22_L03                ( 76U)
#define MULMED_MULFR_AVNMS22_L04                ( 77U)
#define MULMED_MULFR_AVNMS22_L05                ( 78U)
#define MULMED_MULFR_AVNMS23_L01                ( 79U)
#define MULMED_MULFR_AVNMS23_L02                ( 80U)
#define MULMED_MULFR_AVNMS23_L03                ( 81U)
#define MULMED_MULFR_AVNMS23_L04                ( 82U)
#define MULMED_MULFR_AVNMS23_L05                ( 83U)
#define MULMED_MULFR_AVNMS23_L06                ( 84U)
#define MULMED_MULFR_AVNMS23_L07                ( 85U)
#define MULMED_MULFR_AVNMS23_L08                ( 86U)
#define MULMED_MULFR_AVNMS23_L09                ( 87U)
#define MULMED_MULFR_AVNMS23_L10                ( 88U)
#define MULMED_MULFR_AVNMS23_L11                ( 89U)
#define MULMED_MULFR_AVNMS23_L12                ( 90U)
#define MULMED_MULFR_AVNMS23_L13                ( 91U)
#define MULMED_MULFR_AVNMS23_L14                ( 92U)
#define MULMED_MULFR_AVNMS23_L15                ( 93U)
#define MULMED_MULFR_AVNMS23_L16                ( 94U)
#define MULMED_MULFR_AVNMS23_L17                ( 95U)
#define MULMED_MULFR_AVNMS23_L18                ( 96U)
#define MULMED_MULFR_AVNMS23_L19                ( 97U)
#define MULMED_MULFR_AVNMS23_L20                ( 98U)
#define MULMED_MULFR_AVNMS25_L01                ( 99U)
#define MULMED_MULFR_AVNMS26_L01                (100U)
#define MULMED_MULFR_AVNMS27_L01                (101U)
#define MULMED_MULFR_AVNMS79_L01                (102U)

#define MULMED_MULFR_MAX_TXTSIZE                (30U)
#define MULMED_MULFR_NUM_OPT                    (4U)

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
void            vd_g_MulmedMulfrInit(void);
void            vd_g_MulmedMulfrMainTask(void);
void            vd_g_MulmedMulfrRxTxtHk(const U2 u2_a_MSG);
void            vd_g_MulmedTextMsg(const U1 u1_a_LINEID, U1 * u1p_a_modeid, U1 * u1_ap_options, U2 * u2_ap_rxtext);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif      /* MULMED_MULFR_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  mulmed_mulfr.c                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
