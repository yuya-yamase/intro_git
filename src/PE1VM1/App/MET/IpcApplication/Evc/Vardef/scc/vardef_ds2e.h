/* 2.3.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Vardef / Diag Service 0x2E                                                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef VARDEF_DS_2E_H
#define VARDEF_DS_2E_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VARDEF_DS_2E_H_MAJOR                     (2)
#define VARDEF_DS_2E_H_MINOR                     (3)
#define VARDEF_DS_2E_H_PATCH                     (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDF_DS_2E_MAX                            (0x00ffffffU)
#define VDF_DS_2E_UNK                            (0x00000000U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDF_DS_2E_NUM_DID                        (12U)

#define VDF_DS_2E_2002                           (0U)     /* MET Customization / Odo Display-On Delay                */
#define VDF_DS_2E_2003                           (1U)     /* HUD Customization / Memory Call ...                     */
#define VDF_DS_2E_2004                           (2U)     /* MET Customization / Post-Charge Flag                    */
#define VDF_DS_2E_2021                           (3U)     /* MET XM Authentication                                   */
#define VDF_DS_2E_2041                           (4U)     /* MET Customization / Body Function                       */
#define VDF_DS_2E_2042                           (5U)     /* MET Customization / Lane Change Support                 */
#define VDF_DS_2E_2043                           (6U)     /* MET Customization / Tic-Toc Volume                      */
#define VDF_DS_2E_2045                           (7U)     /* MET Customization / Lane Change Support2                */
#define VDF_DS_2E_20C1                           (8U)     /* MET Customization / Shift-By-Wire Reverse Buzzer        */
#define VDF_DS_2E_20C2                           (9U)     /* MET Customization / Shift-By-Wire Reverse Buzzer 2      */
/* #define VDF_DS_2E_2202                                    HUD Calibration   / Trapezoidal                         */
/* #define VDF_DS_2E_2203                                    HUD Calibration   / Distortion                          */
#define VDF_DS_2E_2204                           (10U)    /* HUD Customization / Audio F/B, Master Caution  ...      */
#define VDF_DS_2E_2209                           (11U)    /* Touch display start sensitivity / Time out              */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* DID 0x2002 */
#define VDF_DS_2E_OD__30_S                       (0x00000000U)
#define VDF_DS_2E_OD__60_S                       (0x00000001U)
#define VDF_DS_2E_OD_600_S                       (0x00000002U)
#define VDF_DS_2E_OD___0_S                       (0x00000003U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* DID 0x2003 */
#define VDF_DS_2E_MEM_SYN                        (0x00000080U)
#define VDF_DS_2E_SWI_SYN                        (0x00000040U)

#define VDF_DS_2E_2003_MAX                       (0x000000c0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* DID 0x2004 */
#define VDF_DS_2E_PC_FLAG1                       (0x00000080U)
#define VDF_DS_2E_PC_FLAG2                       (0x00000040U)
#define VDF_DS_2E_PC_FLAG3                       (0x00000020U)
#define VDF_DS_2E_PC_FLAG4                       (0x00000010U)
#define VDF_DS_2E_PC_FLAG5                       (0x00000008U)
#define VDF_DS_2E_PC_FLAG6                       (0x00000004U)
#define VDF_DS_2E_PC_FLAG7                       (0x00000002U)
#define VDF_DS_2E_PC_FLAG8                       (0x00000001U)

#define VDF_DS_2E_2004_MAX                       (0x000000ffU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* DID 0x2021 */
#define VDF_DS_2E_XM_MODE                        (0x00000020U)


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* DID 0x2041 */
#define VDF_DS_2E_TRWC_EN                        (0x00000080U)  /* Tail Light Reminder                  */
#define VDF_DS_2E_SBLT_DR                        (0x00000040U)  /* Seatbelt Driver                      */
#define VDF_DS_2E_SBLT_PA                        (0x00000020U)  /* Seatbelt Passenger                   */
#define VDF_DS_2E_SBLT_CE                        (0x00000010U)  /* Seatbelt Center                      */
#define VDF_DS_2E_SBLT_RA                        (0x00000008U)  /* Seatbelt Rear All                    */
#define VDF_DS_2E_SBLT_2R                        (0x00000004U)  /* Seatbelt 2nd Row/Right               */
#define VDF_DS_2E_SBLT_2L                        (0x00000002U)  /* Seatbelt 2nd Row/Left                */
#define VDF_DS_2E_SBLT_2C                        (0x00000001U)  /* Seatbelt 2nd Row/Center              */
#define VDF_DS_2E_SBLT_3R                        (0x00008000U)  /* Seatbelt 3rd Row/Right               */
#define VDF_DS_2E_SBLT_3L                        (0x00004000U)  /* Seatbelt 3rd Row/Left                */
#define VDF_DS_2E_SBLT_3C                        (0x00002000U)  /* Seatbelt 3rd Row/Center              */
#define VDF_DS_2E_SBLT_4R                        (0x00001000U)  /* Seatbelt 4th Row/Right               */
#define VDF_DS_2E_SBLT_4L                        (0x00000800U)  /* Seatbelt 4th Row/Left                */
#define VDF_DS_2E_SBLT_4C                        (0x00000400U)  /* Seatbelt 4th Row/Center              */
#define VDF_DS_2E_STPL_EN                        (0x00000200U)  /* Stop Lamp                            */

#define VDF_DS_2E_2041_MAX                       (0x0000feffU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* DID 0x2042 */
#define VDF_DS_2E_LC_C0                          (0x00000000U)  /* Turn Blinking       = 0 cycle        */
#define VDF_DS_2E_LC_C3                          (0x00000001U)  /* Turn Blinking       = 3 cycle        */
#define VDF_DS_2E_LC_C4                          (0x00000002U)  /* Turn Blinking       = 4 cycle        */
#define VDF_DS_2E_LC_C5                          (0x00000003U)  /* Turn Blinking       = 5 cycle        */
#define VDF_DS_2E_LC_C6                          (0x00000004U)  /* Turn Blinking       = 6 cycle        */
#define VDF_DS_2E_LC_C7                          (0x00000005U)  /* Turn Blinking       = 7 cycle        */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* DID 0x2043 */
#define VDF_DS_2E_TIC_TOC_ME                     (0x00000000U)  /* Tic-Toc Volume      = Medium         */
#define VDF_DS_2E_TIC_TOC_LO                     (0x00000001U)  /* Tic-Toc Volume      = Low            */
#define VDF_DS_2E_TIC_TOC_HI                     (0x00000002U)  /* Tic-Toc Volume      = High           */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* DID 0x2045 */
#define VDF_DS_2E_LC2_C0                         (0x00000000U)  /* Turn Blinking       = 0 cycle        */
#define VDF_DS_2E_LC2_C5                         (0x00000001U)  /* Turn Blinking       = 5 cycle        */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* DID 0x20C1 */
#define VDF_DS_2E_SBWC_IN                        (0x00000000U)  /* Shift-By Wire Chime = Intermittent   */
#define VDF_DS_2E_SBWC_SI                        (0x00000001U)  /* Shift-By Wire Chime = Single         */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* DID 0x20C2 */
#define VDF_DS_2E_SBWC2_NON                       (0x00000000U)  /* Shift-By Wire Chime2 = Non           */
#define VDF_DS_2E_SBWC2_IN                        (0x00000001U)  /* Shift-By Wire Chime2 = Intermittent  */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* DID 0x2204 */
#define VDF_DS_2E_AUFB_EN                        (0x00000080U)  /* Audio F/B                            */
#define VDF_DS_2E_MSCA_EN                        (0x00000040U)  /* Master Caution                       */
#define VDF_DS_2E_TSRS_EN                        (0x00000020U)  /* Traffic Sign Recognition Speed Limit */

#define VDF_DS_2E_2204_MAX                       (0x000000e0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* DID 0x2209 */
/*  Touch display start sensitivity  */
#define VDF_DS_2E_TDSS_NML                       (0x00000000U)              /*    Touch display start sensitivity : Normal           */
#define VDF_DS_2E_TDSS_HI                        (0x00000100U)              /*    Touch display start sensitivity : Hi               */
#define VDF_DS_2E_TDSS_OFF                       (0x00000200U)              /*    Touch display start sensitivity : OFF              */
#define VDF_DS_2E_TDSS_MSK                       (0x0000ff00U)

/*  Time out  */
#define VDF_DS_2E_TO_NML                         (0x00000000U)              /*    Time out : Normal                                  */
#define VDF_DS_2E_TO_SHRT                        (0x00000001U)              /*    Time out : Short                                   */
#define VDF_DS_2E_TO_LONG                        (0x00000002U)              /*    Time out : Long                                    */
#define VDF_DS_2E_TO_MSK                         (0x000000ffU)

#define VDF_DS_2E_2209_MAX                       (0x00000202U)

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
void    vd_g_VardefDs2EInit(void);
void    vd_g_VardefDs2EMainTask(void);

U4      u4_g_VardefDs2E_Las32(const U2 u2_a_DID);
U4      u4_g_VardefDs2E_Max32(const U2 u2_a_DID);
void    vd_g_VardefDs2E_Syn32(const U2 u2_a_DID);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif      /* VARDEF_DS_2E_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  vardef_ds2e.c                                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/
