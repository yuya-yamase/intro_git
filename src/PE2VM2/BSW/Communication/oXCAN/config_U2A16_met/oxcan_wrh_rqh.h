/* 2.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  OEM eXtention of CAN Config Header                                                                                               */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  WARNING :                                                                                                                        */
/*  oxcan_wrh_rqh.h is included in oxcan_lib.h and oxcan.h                                                                           */
/*  DO NOT include this file in any file even though this configuration header is public.                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef OXCAN_WRH_RQH_H
#define OXCAN_WRH_RQH_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_WRH_RQH_H_MAJOR                    (1U)
#define OXCAN_WRH_RQH_H_MINOR                    (0U)
#define OXCAN_WRH_RQH_H_PATCH                    (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Return of u4_g_oXCANWrhWrqAct(void)                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_WRH_WRQBIT_H_0                     (0x00000001U)
#define OXCAN_WRH_WRQBIT_H_1                     (0x00000002U)    /* Reserved, DO NOT Delete */
#define OXCAN_WRH_WRQBIT_H_2                     (0x00000004U)    /* Reserved, DO NOT Delete */
#define OXCAN_WRH_WRQBIT_H_3                     (0x00000008U)    /* Reserved, DO NOT Delete */
#define OXCAN_WRH_WRQBIT_H_4                     (0x00000010U)    /* Reserved, DO NOT Delete */
#define OXCAN_WRH_WRQBIT_H_5                     (0x00000020U)    /* Reserved, DO NOT Delete */
#define OXCAN_WRH_WRQBIT_H_6                     (0x00000040U)    /* Reserved, DO NOT Delete */
#define OXCAN_WRH_WRQBIT_H_7                     (0x00000080U)    /* Reserved, DO NOT Delete */
#define OXCAN_WRH_WRQBIT_H_8                     (0x00000100U)    /* Reserved, DO NOT Delete */
#define OXCAN_WRH_WRQBIT_H_9                     (0x00000200U)    /* Reserved, DO NOT Delete */
#define OXCAN_WRH_WRQBIT_H10                     (0x00000400U)    /* Reserved, DO NOT Delete */
#define OXCAN_WRH_WRQBIT_H11                     (0x00000800U)    /* Reserved, DO NOT Delete */
#define OXCAN_WRH_WRQBIT_H12                     (0x00001000U)    /* Reserved, DO NOT Delete */
#define OXCAN_WRH_WRQBIT_H13                     (0x00002000U)    /* Reserved, DO NOT Delete */
#define OXCAN_WRH_WRQBIT_H14                     (0x00004000U)    /* Reserved, DO NOT Delete */
#define OXCAN_WRH_WRQBIT_H15                     (0x00008000U)    /* Reserved, DO NOT Delete */
#define OXCAN_WRH_WRQBIT_H16                     (0x00010000U)    /* Reserved, DO NOT Delete */
#define OXCAN_WRH_WRQBIT_H17                     (0x00020000U)    /* Reserved, DO NOT Delete */
#define OXCAN_WRH_WRQBIT_H18                     (0x00040000U)    /* Reserved, DO NOT Delete */
#define OXCAN_WRH_WRQBIT_H19                     (0x00080000U)    /* Reserved, DO NOT Delete */
#define OXCAN_WRH_WRQBIT_H20                     (0x00100000U)    /* Reserved, DO NOT Delete */
#define OXCAN_WRH_WRQBIT_H21                     (0x00200000U)    /* Reserved, DO NOT Delete */
#define OXCAN_WRH_WRQBIT_H22                     (0x00400000U)    /* Reserved, DO NOT Delete */
#define OXCAN_WRH_WRQBIT_H23                     (0x00800000U)    /* Reserved, DO NOT Delete */
#define OXCAN_WRH_WRQBIT_H24                     (0x01000000U)    /* Reserved, DO NOT Delete */
#define OXCAN_WRH_WRQBIT_H25                     (0x02000000U)    /* Reserved, DO NOT Delete */
#define OXCAN_WRH_WRQBIT_H26                     (0x04000000U)    /* Reserved, DO NOT Delete */
#define OXCAN_WRH_WRQBIT_H27                     (0x08000000U)    /* Reserved, DO NOT Delete */
#define OXCAN_WRH_WRQBIT_H28                     (0x10000000U)    /* Reserved, DO NOT Delete */
#define OXCAN_WRH_WRQBIT_H29                     (0x20000000U)    /* Reserved, DO NOT Delete */

#define OXCAN_WRH_WRQBIT_DCM                     (0x40000000U)    /* Reserved, DO NOT Delete */
#define OXCAN_WRH_WRQBIT_VOM                     (0x80000000U)    /* Reserved, DO NOT Delete */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_WRH_NUM_RQH                        (4U)

#define OXCAN_WRH_HCH_0                          (0U)
#define OXCAN_WRH_HCH_1                          (1U)
#define OXCAN_WRH_HCH_2                          (2U)
#define OXCAN_WRH_HCH_3                          (3U)

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

#endif /* OXCAN_WRH_RQH_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see  oxcan_wrh_cfg.c                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/
