/* 5.3.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert S_DMC                                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_S_DMC_C_MAJOR                      (5)
#define ALERT_S_DMC_C_MINOR                      (3)
#define ALERT_S_DMC_C_PATCH                      (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"

#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "oxcan_channel_STUB.h"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_S_DMC_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_S_DMC.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_S_DMC_BC_NUM_DST                   (16U)
#define ALERT_S_DMC_PD_NUM_DST                   (56U)
#define ALERT_S_DMC_TT_NUM_DST                   (32U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_AlertS_dmcBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertS_dmcPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertS_dmcTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_S_DMC_BC_DST[ALERT_S_DMC_BC_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_S_DMC_BC_SINGLE,                                             /* 01 SINGLE                                          */
    (U1)ALERT_REQ_S_DMC_BC_CYCLE,                                              /* 02 CYCLE                                           */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 09 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 15 UNKNOWN                                         */
};

static const U1  u1_sp_ALERT_S_DMC_PD_DST[ALERT_S_DMC_PD_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_S_DMC_PD_INATTENT,                                           /* 01 INATTENT                                        */
    (U1)ALERT_REQ_S_DMC_PD_CLOSE_EYES,                                         /* 02 CLOSE_EYES                                      */
    (U1)ALERT_REQ_S_DMC_PD_COND_NO_DTCT1,                                      /* 03 COND_NO_DTCT1                                   */
    (U1)ALERT_REQ_S_DMC_PD_FACE_NO_DTCT,                                       /* 04 FACE_NO_DTCT                                    */
    (U1)ALERT_REQ_S_DMC_PD_COND_NO_DTCT2,                                      /* 05 COND_NO_DTCT2                                   */
    (U1)ALERT_REQ_S_DMC_PD_COND_NO_DTCT3,                                      /* 06 COND_NO_DTCT3                                   */
    (U1)ALERT_REQ_S_DMC_PD_PHONE_USE,                                          /* 07 PHONE_USE                                       */
    (U1)ALERT_REQ_S_DMC_PD_SMOKING,                                            /* 08 SMOKING                                         */
    (U1)ALERT_REQ_S_DMC_PD_DROWSY,                                             /* 09 DROWSY                                          */
    (U1)ALERT_REQ_S_DMC_PD_YAWNING,                                            /* 10 YAWNING                                         */
    (U1)ALERT_REQ_S_DMC_PD_SUNGLASSES,                                         /* 11 SUNGLASSES                                      */
    (U1)ALERT_REQ_S_DMC_PD_FACE_COVER,                                         /* 12 FACE_COVER                                      */
    (U1)ALERT_REQ_S_DMC_PD_DMC_RESTRCT,                                        /* 13 DMC_RESTRCT                                     */
    (U1)ALERT_REQ_S_DMC_PD_FACE_OBSTRCT,                                       /* 14 FACE_OBSTRCT                                    */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 15 UNKNOWN                                         */
    (U1)ALERT_REQ_S_DMC_PD_UNAVAIL,                                            /* 16 UNAVAIL                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 17 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 18 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 19 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 20 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 21 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 22 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 23 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 24 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 25 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 26 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 27 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 28 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 29 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 30 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 31 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 32 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 33 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 34 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 35 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 36 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 37 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 38 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 39 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 40 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 41 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 42 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 43 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 44 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 45 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 46 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 47 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 48 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 49 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 50 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 51 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 52 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 53 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 54 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 55 UNKNOWN                                         */
};

static const U4  u4_sp_ALERT_S_DMC_PD_CRIT[ALERT_S_DMC_PD_NUM_DST] = {
    (U4)0x00000000U,                                                           /* 00 UNKNOWN                                         */
    (U4)0x00000001U,                                                           /* 01 INATTENT                                        */
    (U4)0x00000002U,                                                           /* 02 CLOSE_EYES                                      */
    (U4)0x00000003U,                                                           /* 03 COND_NO_DTCT1                                   */
    (U4)0x00000004U,                                                           /* 04 FACE_NO_DTCT                                    */
    (U4)0x00000005U,                                                           /* 05 COND_NO_DTCT2                                   */
    (U4)0x00000006U,                                                           /* 06 COND_NO_DTCT3                                   */
    (U4)0x00000007U,                                                           /* 07 PHONE_USE                                       */
    (U4)0x00000008U,                                                           /* 08 SMOKING                                         */
    (U4)0x00000009U,                                                           /* 09 DROWSY                                          */
    (U4)0x0000000AU,                                                           /* 10 YAWNING                                         */
    (U4)0x0000000BU,                                                           /* 11 SUNGLASSES                                      */
    (U4)0x0000000CU,                                                           /* 12 FACE_COVER                                      */
    (U4)0x0000000DU,                                                           /* 13 DMC_RESTRCT                                     */
    (U4)0x0000000EU,                                                           /* 14 FACE_OBSTRCT                                    */
    (U4)0x0000000FU,                                                           /* 15 UNKNOWN                                         */
    (U4)0x00000010U,                                                           /* 16 UNAVAIL                                         */
    (U4)0x00000011U,                                                           /* 17 UNKNOWN                                         */
    (U4)0x00000012U,                                                           /* 18 UNKNOWN                                         */
    (U4)0x00000013U,                                                           /* 19 UNKNOWN                                         */
    (U4)0x00000014U,                                                           /* 20 UNKNOWN                                         */
    (U4)0x00000015U,                                                           /* 21 UNKNOWN                                         */
    (U4)0x00000016U,                                                           /* 22 UNKNOWN                                         */
    (U4)0x00000017U,                                                           /* 23 UNKNOWN                                         */
    (U4)0x00000018U,                                                           /* 24 UNKNOWN                                         */
    (U4)0x00000019U,                                                           /* 25 UNKNOWN                                         */
    (U4)0x0000001AU,                                                           /* 26 UNKNOWN                                         */
    (U4)0x0000001BU,                                                           /* 27 UNKNOWN                                         */
    (U4)0x0000001CU,                                                           /* 28 UNKNOWN                                         */
    (U4)0x0000001DU,                                                           /* 29 UNKNOWN                                         */
    (U4)0x0000001EU,                                                           /* 30 UNKNOWN                                         */
    (U4)0x0000001FU,                                                           /* 31 UNKNOWN                                         */
    (U4)0x00000020U,                                                           /* 32 UNKNOWN                                         */
    (U4)0x0000002BU,                                                           /* 33 UNKNOWN                                         */
    (U4)0x0000002CU,                                                           /* 34 UNKNOWN                                         */
    (U4)0x0000002DU,                                                           /* 35 UNKNOWN                                         */
    (U4)0x0000002EU,                                                           /* 36 UNKNOWN                                         */
    (U4)0x0000002FU,                                                           /* 37 UNKNOWN                                         */
    (U4)0x00000030U,                                                           /* 38 UNKNOWN                                         */
    (U4)0x00000031U,                                                           /* 39 UNKNOWN                                         */
    (U4)0x00000032U,                                                           /* 40 UNKNOWN                                         */
    (U4)0x00000033U,                                                           /* 41 UNKNOWN                                         */
    (U4)0x00000034U,                                                           /* 42 UNKNOWN                                         */
    (U4)0x00000035U,                                                           /* 43 UNKNOWN                                         */
    (U4)0x00000036U,                                                           /* 44 UNKNOWN                                         */
    (U4)0x00000037U,                                                           /* 45 UNKNOWN                                         */
    (U4)0x00000038U,                                                           /* 46 UNKNOWN                                         */
    (U4)0x00000039U,                                                           /* 47 UNKNOWN                                         */
    (U4)0x0000003AU,                                                           /* 48 UNKNOWN                                         */
    (U4)0x0000003BU,                                                           /* 49 UNKNOWN                                         */
    (U4)0x0000003CU,                                                           /* 50 UNKNOWN                                         */
    (U4)0x0000003DU,                                                           /* 51 UNKNOWN                                         */
    (U4)0x0000003EU,                                                           /* 52 UNKNOWN                                         */
    (U4)0x0000003FU,                                                           /* 53 UNKNOWN                                         */
    (U4)0x00000040U,                                                           /* 54 UNKNOWN                                         */
    (U4)0x00000080U                                                            /* 55 UNKNOWN                                         */
};

static const U4  u4_sp_ALERT_S_DMC_PD_MASK[ALERT_S_DMC_PD_NUM_DST] = {
    (U4)0x000000FFU,                                                           /* 00 UNKNOWN                                         */
    (U4)0x000000DFU,                                                           /* 01 INATTENT                                        */
    (U4)0x000000DFU,                                                           /* 02 CLOSE_EYES                                      */
    (U4)0x000000DFU,                                                           /* 03 COND_NO_DTCT1                                   */
    (U4)0x000000DFU,                                                           /* 04 FACE_NO_DTCT                                    */
    (U4)0x000000DFU,                                                           /* 05 COND_NO_DTCT2                                   */
    (U4)0x000000DFU,                                                           /* 06 COND_NO_DTCT3                                   */
    (U4)0x000000DFU,                                                           /* 07 PHONE_USE                                       */
    (U4)0x000000DFU,                                                           /* 08 SMOKING                                         */
    (U4)0x000000DFU,                                                           /* 09 DROWSY                                          */
    (U4)0x000000DFU,                                                           /* 10 YAWNING                                         */
    (U4)0x000000FFU,                                                           /* 11 SUNGLASSES                                      */
    (U4)0x000000FFU,                                                           /* 12 FACE_COVER                                      */
    (U4)0x000000FFU,                                                           /* 13 DMC_RESTRCT                                     */
    (U4)0x000000FFU,                                                           /* 14 FACE_OBSTRCT                                    */
    (U4)0x000000FFU,                                                           /* 15 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 16 UNAVAIL                                         */
    (U4)0x000000FFU,                                                           /* 17 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 18 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 19 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 20 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 21 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 22 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 23 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 24 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 25 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 26 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 27 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 28 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 29 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 30 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 31 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 32 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 33 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 34 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 35 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 36 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 37 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 38 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 39 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 40 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 41 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 42 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 43 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 44 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 45 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 46 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 47 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 48 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 49 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 50 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 51 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 52 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 53 UNKNOWN                                         */
    (U4)0x000000C0U,                                                           /* 54 UNKNOWN                                         */
    (U4)0x00000080U                                                            /* 55 UNKNOWN                                         */
};

static const U1  u1_sp_ALERT_S_DMC_TT_DST[ALERT_S_DMC_TT_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_S_DMC_TT_MAL_DMC,                                            /* 01 MAL_DMC                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_S_DMC_TT_WHT_DMC_OFF,                                        /* 03 WHT_DMC_OFF                                     */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 09 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 15 UNKNOWN                                         */
    (U1)ALERT_REQ_S_DMC_TT_MAL_DMC,                                            /* 16 MAL_DMC                                         */
    (U1)ALERT_REQ_S_DMC_TT_MAL_DMC,                                            /* 17 MAL_DMC                                         */
    (U1)ALERT_REQ_S_DMC_TT_MAL_DMC,                                            /* 18 MAL_DMC                                         */
    (U1)ALERT_REQ_S_DMC_TT_MAL_DMC,                                            /* 19 MAL_DMC                                         */
    (U1)ALERT_REQ_S_DMC_TT_MAL_DMC,                                            /* 20 MAL_DMC                                         */
    (U1)ALERT_REQ_S_DMC_TT_MAL_DMC,                                            /* 21 MAL_DMC                                         */
    (U1)ALERT_REQ_S_DMC_TT_MAL_DMC,                                            /* 22 MAL_DMC                                         */
    (U1)ALERT_REQ_S_DMC_TT_MAL_DMC,                                            /* 23 MAL_DMC                                         */
    (U1)ALERT_REQ_S_DMC_TT_MAL_DMC,                                            /* 24 MAL_DMC                                         */
    (U1)ALERT_REQ_S_DMC_TT_MAL_DMC,                                            /* 25 MAL_DMC                                         */
    (U1)ALERT_REQ_S_DMC_TT_MAL_DMC,                                            /* 26 MAL_DMC                                         */
    (U1)ALERT_REQ_S_DMC_TT_MAL_DMC,                                            /* 27 MAL_DMC                                         */
    (U1)ALERT_REQ_S_DMC_TT_MAL_DMC,                                            /* 28 MAL_DMC                                         */
    (U1)ALERT_REQ_S_DMC_TT_MAL_DMC,                                            /* 29 MAL_DMC                                         */
    (U1)ALERT_REQ_S_DMC_TT_MAL_DMC,                                            /* 30 MAL_DMC                                         */
    (U1)ALERT_REQ_S_DMC_TT_MAL_DMC                                             /* 31 MAL_DMC                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_S_DMC_MTRX[3] = {
    {
        &u4_s_AlertS_dmcBcSrcchk,                                              /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_S_DMC_BC_DST[0],                                          /* u1p_DST                                            */
        (U2)ALERT_S_DMC_BC_NUM_DST,                                            /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertS_dmcPdSrcchk,                                              /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        &u4_sp_ALERT_S_DMC_PD_MASK[0],                                         /* u4p_MASK                                           */
        &u4_sp_ALERT_S_DMC_PD_CRIT[0],                                         /* u4p_CRIT                                           */

        &u1_sp_ALERT_S_DMC_PD_DST[0],                                          /* u1p_DST                                            */
        (U2)ALERT_S_DMC_PD_NUM_DST,                                            /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertS_dmcTtSrcchk,                                              /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_S_DMC_TT_DST[0],                                          /* u1p_DST                                            */
        (U2)ALERT_S_DMC_TT_NUM_DST,                                            /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_dmcBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_dmcBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_S_DMC_BC_TRSH_ADU1S07 = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_S_DMC_BC_LSB_ADU1S07  = (U1)2U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_ADU1S07_CH0,
                                     (U4)OXCAN_SYS_IGR,
                                     u2_s_ALERT_S_DMC_BC_TRSH_ADU1S07) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_S_DMC_BC_LSB_ADU1S07);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_DMCBZRQ, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_dmcPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_dmcPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_S_DMC_PD_TRSH_ADU1S07 = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_S_DMC_PD_LSB_ADU1S07  = (U1)6U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_ADU1S07_CH0,
                                     (U4)OXCAN_SYS_IGR,
                                     u2_s_ALERT_S_DMC_PD_TRSH_ADU1S07) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_S_DMC_PD_LSB_ADU1S07);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_DMCDISP, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_dmcTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_dmcTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_S_DMC_TT_TRSH_ADU1S07 = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_S_DMC_TT_LSB_ADU1S07  = (U1)3U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_ADU1S07_CH0,
                                     (U4)OXCAN_SYS_IGR,
                                     u2_s_ALERT_S_DMC_TT_TRSH_ADU1S07) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_S_DMC_TT_LSB_ADU1S07);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_DMCINDI, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0    12/16/2020  RI       New.                                                                                               */
/*  5.1.0     4/ 8/2021  SO       Change BC Ch matrix table.                                                                         */
/*  5.1.1     5/13/2022  RN       Update for 050D (Version update).                                                                  */
/*  5.2.0     2/19/2024  GM       Update for 19PFv3.                                                                                 */
/*  5.3.0     4/02/2024  JM       Removal of 1 telltale item (TT02-REQ02).                                                           */           
/*                                                                                                                                   */
/*  * RI   = Ren Itou, NTTD MSE                                                                                                      */
/*  * SO   = Syuhei Ooshima, NTTD MSE                                                                                                */
/*  * RN   = Ryuga Nakanishi, NTTD MSE                                                                                               */
/*  * GM   = Glen Monteposo, DTPH                                                                                                    */
/*  * JMH  = James Michael Hilarion, DTPH                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

