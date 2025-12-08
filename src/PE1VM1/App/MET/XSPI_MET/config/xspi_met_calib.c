/* 0.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Local Communication SPI / MCUCONST Data Set                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_CALIB_C_MAJOR                    (0)
#define XSPI_CALIB_C_MINOR                    (0)
#define XSPI_CALIB_C_PATCH                    (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "xspi_met_calib.h"

#include "memfill_u4.h"
#include "memcpy_u4.h"

#include "calibration.h"
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((XSPI_CALIB_C_MAJOR != XSPI_CALIB_H_MAJOR) || \
     (XSPI_CALIB_C_MINOR != XSPI_CALIB_H_MINOR) || \
     (XSPI_CALIB_C_PATCH != XSPI_CALIB_H_PATCH))
#error "xspi_met_calib.c and xspi_met_calib.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_SIZE_U1                            (1U)
#define XSPI_SIZE_U2                            (2U)

#define XSPI_MCUID_NUM                          (21U)

#define XSPI_CALIB_SLOT_A                       (0U)
#define XSPI_CALIB_SLOT_B                       (1U)
#define XSPI_CALIB_SLOT_C                       (2U)
#define XSPI_CALIB_SLOT_D                       (3U)
#define XSPI_CALIB_SLOT_E                       (4U)
#define XSPI_CALIB_SLOT_F                       (5U)
#define XSPI_CALIB_SLOT_G                       (6U)
#define XSPI_CALIB_SLOT_H                       (7U)
#define XSPI_CALIB_SLOT_I                       (8U)
#define XSPI_CALIB_SLOT_J                       (9U)
#define XSPI_CALIB_NUM_SLOT                     (10U)


#define XSPI_MCUID_MINMAXCHK_NUM                (4U)

#define XSPI_CALIB_PAYLOAD_NUM                  (42U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    const U2                    u2_xspiid;
    const U1                    u1_bitpos;
    const U1                    u1_size;
    volatile const void *       vdp_mcuid;
    const U1                    u1_slot;
}ST_XSPI_CALIB;

typedef struct{
    const U2                    u2_xspiid;
    const U1                    u1_bitpos;
    volatile const U1 *         u1p_mcuid;
    const U4                    u4_min;
    const U4                    u4_max;
    const U4                    u4_def;
}ST_XSPI_CALIB_CHK;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1                u1_s_calib_slot;
static U4                u4_sp_calib_buf[XSPI_CALIB_PAYLOAD_NUM]    __attribute__((aligned(8)));
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_XSPI_CALIB st_sp_XSPI_CALIB[XSPI_MCUID_NUM] = {
    /* u2_xspiid ,     u1_bitpos ,                 u1_size ,                vdp_mcuid                           u1_slot      */
        {(U2) 1U,       (U1)XSPI_SHIFT_2BYTE,       (U1)XSPI_SIZE_U1,        &u1_CALIB_MCUID0219_G_GAUGE_MAX,    (U1)XSPI_CALIB_SLOT_A       },
        {(U2) 1U,       (U1)XSPI_SHIFT_3BYTE,       (U1)XSPI_SIZE_U1,        &u1_CALIB_MCUID0220_GTRAJECTORY2,   (U1)XSPI_CALIB_SLOT_A       },
        {(U2) 2U,       (U1)XSPI_SHIFT_NON,         (U1)XSPI_SIZE_U1,        &u1_CALIB_MCUID0221_G_DISP_MAX,     (U1)XSPI_CALIB_SLOT_A       },
        {(U2) 2U,       (U1)XSPI_SHIFT_3BYTE,       (U1)XSPI_SIZE_U1,        &u1_CALIB_MCUID0235_BODYSHAPE,      (U1)XSPI_CALIB_SLOT_A       },
        {(U2) 3U,       (U1)XSPI_SHIFT_2BYTE,       (U1)XSPI_SIZE_U2,        &u2_CALIB_MCUID0262_MAXSPEED_KM,    (U1)XSPI_CALIB_SLOT_A       },
        {(U2) 4U,       (U1)XSPI_SHIFT_NON,         (U1)XSPI_SIZE_U2,        &u2_CALIB_MCUID0263_MAXSPEED_MPH,   (U1)XSPI_CALIB_SLOT_A       },
        {(U2) 4U,       (U1)XSPI_SHIFT_2BYTE,       (U1)XSPI_SIZE_U1,        &u1_CALIB_MCUID0264_FSPO,           (U1)XSPI_CALIB_SLOT_A       },
        {(U2) 5U,       (U1)XSPI_SHIFT_NON,         (U1)XSPI_SIZE_U1,        &u1_CALIB_MCUID0268_SWNUM,          (U1)XSPI_CALIB_SLOT_B       },
        {(U2) 6U,       (U1)XSPI_SHIFT_3BYTE,       (U1)XSPI_SIZE_U1,        &u1_CALIB_MCUID0590_SOC_PORTPOS,    (U1)XSPI_CALIB_SLOT_B       },
        {(U2)25U,       (U1)XSPI_SHIFT_2BYTE,       (U1)XSPI_SIZE_U1,        &u2_CALIB_MCUID0738_TIMEOUT_TM,     (U1)XSPI_CALIB_SLOT_F       },
        {(U2)28U,       (U1)XSPI_SHIFT_NON,         (U1)XSPI_SIZE_U1,        &u1_CALIB_MCUID0430_RHEOSW,         (U1)XSPI_CALIB_SLOT_F       },
        {(U2)38U,       (U1)XSPI_SHIFT_2BYTE,       (U1)XSPI_SIZE_U1,        &u1_CALIB_MCUID0209_RRCYM,          (U1)XSPI_CALIB_SLOT_H       },
        {(U2)38U,       (U1)XSPI_SHIFT_3BYTE,       (U1)XSPI_SIZE_U1,        &u1_CALIB_MCUID0210_RLCYM,          (U1)XSPI_CALIB_SLOT_H       },
        {(U2)39U,       (U1)XSPI_SHIFT_NON,         (U1)XSPI_SIZE_U1,        &u1_CALIB_MCUID0211_BCTYM,          (U1)XSPI_CALIB_SLOT_H       },
        {(U2)39U,       (U1)XSPI_SHIFT_1BYTE,       (U1)XSPI_SIZE_U1,        &u1_CALIB_MCUID0212_LGCYM,          (U1)XSPI_CALIB_SLOT_H       },
        {(U2)39U,       (U1)XSPI_SHIFT_2BYTE,       (U1)XSPI_SIZE_U1,        &u1_CALIB_MCUID0213_HDCY_BDBM,      (U1)XSPI_CALIB_SLOT_H       },
        {(U2)39U,       (U1)XSPI_SHIFT_3BYTE,       (U1)XSPI_SIZE_U1,        &u1_CALIB_MCUID0214_RPSDWARNM,      (U1)XSPI_CALIB_SLOT_H       },
        {(U2)40U,       (U1)XSPI_SHIFT_NON,         (U1)XSPI_SIZE_U1,        &u1_CALIB_MCUID0215_LPSDWARNM,      (U1)XSPI_CALIB_SLOT_I       },
        {(U2)40U,       (U1)XSPI_SHIFT_1BYTE,       (U1)XSPI_SIZE_U1,        &u1_CALIB_MCUID0809_MEXICO_LOW,     (U1)XSPI_CALIB_SLOT_I       },
        {(U2)40U,       (U1)XSPI_SHIFT_2BYTE,       (U1)XSPI_SIZE_U1,        &u1_CALIB_MCUID0810_KOREA_LOW,      (U1)XSPI_CALIB_SLOT_I       },
        {(U2)41U,       (U1)XSPI_SHIFT_NON,         (U1)XSPI_SIZE_U1,        &u1_CALIB_MCUID0798_TRNLMPCLR,      (U1)XSPI_CALIB_SLOT_I       }
};

static const ST_XSPI_CALIB_CHK st_sp_XSPI_CALIB_MINMAXCHK[XSPI_MCUID_MINMAXCHK_NUM] = {
    /* u2_xspiid ,     u1_bitpos ,                 u1p_mcuid ,                         u4_min ,                            u4_max ,                            u4_def                             */
        {(U2) 0U,       (U1)XSPI_SHIFT_1BYTE,       &u1_CALIB_MCUID0024_BRAND,          (U4)CALIB_MCUID0024_TOYOTA,         (U4)(CALIB_MCUID0024_NUM - 1U),     (U4)CALIB_MCUID0024_DEF            },
        {(U2) 0U,       (U1)XSPI_SHIFT_2BYTE,       &u1_CALIB_MCUID0025_SPORTS,         (U4)CALIB_MCUID0025_NON,            (U4)(CALIB_MCUID0025_NUM - 1U),     (U4)CALIB_MCUID0025_DEF            },
        {(U2) 2U,       (U1)XSPI_SHIFT_1BYTE,       &u1_CALIB_MCUID0233_RDOOR,          (U4)CALIB_MCUID0233_MIN,            (U4)CALIB_MCUID0233_MAX,            (U4)CALIB_MCUID0233_DEF            },
        {(U2) 2U,       (U1)XSPI_SHIFT_2BYTE,       &u1_CALIB_MCUID0234_WALKTHROUGH,    (U4)CALIB_MCUID0234_MIN,            (U4)CALIB_MCUID0234_MAX,            (U4)CALIB_MCUID0234_DEF            }
};

/*===================================================================================================================================*/
/*  void    vd_g_XSpiCalibInit(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_XSpiCalibInit(void)
{
    U4  u4_t_loop;
    U4  u4_t_calib_val;

    u1_s_calib_slot = (U1)0U;
    vd_g_MemfillU4(&u4_sp_calib_buf[0], (U4)0U, (U4)XSPI_CALIB_PAYLOAD_NUM);

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)XSPI_MCUID_NUM; u4_t_loop++) {
        if (st_sp_XSPI_CALIB[u4_t_loop].vdp_mcuid != vdp_PTR_NA) {
            if (st_sp_XSPI_CALIB[u4_t_loop].u1_size == (U1)XSPI_SIZE_U1) {
                u4_t_calib_val = (U4) *((const volatile U1*)st_sp_XSPI_CALIB[u4_t_loop].vdp_mcuid);

                u4_sp_calib_buf[st_sp_XSPI_CALIB[u4_t_loop].u2_xspiid] |=
                    ((u4_t_calib_val & (U4)XSPI_MSK_08BIT)
                    << st_sp_XSPI_CALIB[u4_t_loop].u1_bitpos);
            }
            else if (st_sp_XSPI_CALIB[u4_t_loop].u1_size == (U1)XSPI_SIZE_U2) {
                u4_t_calib_val = (U4) *((const volatile U2*)st_sp_XSPI_CALIB[u4_t_loop].vdp_mcuid);

                u4_sp_calib_buf[st_sp_XSPI_CALIB[u4_t_loop].u2_xspiid] |=
                    ((u4_t_calib_val & (U4)XSPI_MSK_16BIT)
                    << st_sp_XSPI_CALIB[u4_t_loop].u1_bitpos);
            }
            else {
                /* Do Nothing */
            }
        }
    }

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)XSPI_MCUID_MINMAXCHK_NUM; u4_t_loop++) {

        if (st_sp_XSPI_CALIB_MINMAXCHK[u4_t_loop].u1p_mcuid != vdp_PTR_NA) {
            u4_t_calib_val = (U4) *(st_sp_XSPI_CALIB_MINMAXCHK[u4_t_loop].u1p_mcuid);
                
            if ((u4_t_calib_val < st_sp_XSPI_CALIB_MINMAXCHK[u4_t_loop].u4_min) ||
                (u4_t_calib_val > st_sp_XSPI_CALIB_MINMAXCHK[u4_t_loop].u4_max)) {
                u4_t_calib_val = st_sp_XSPI_CALIB_MINMAXCHK[u4_t_loop].u4_def;
            }
            
            u4_sp_calib_buf[st_sp_XSPI_CALIB_MINMAXCHK[u4_t_loop].u2_xspiid] |=
                ((u4_t_calib_val & (U4)XSPI_MSK_08BIT)
                << st_sp_XSPI_CALIB_MINMAXCHK[u4_t_loop].u1_bitpos);
        }
    }

}
/*===================================================================================================================================*/
/*  void    vd_g_XSpiCalibMainTask(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_XSpiCalibMainTask(void)
{

    U4  u4_t_loop;
    U4  u4_t_calib_val;

    if(u1_s_calib_slot >= (U1)XSPI_CALIB_NUM_SLOT) {
        u1_s_calib_slot = (U1)0U;
    }

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)XSPI_MCUID_NUM; u4_t_loop++) {

        if (st_sp_XSPI_CALIB[u4_t_loop].u1_slot == u1_s_calib_slot) {
            if (st_sp_XSPI_CALIB[u4_t_loop].vdp_mcuid != vdp_PTR_NA) {
                if (st_sp_XSPI_CALIB[u4_t_loop].u1_size == (U1)XSPI_SIZE_U1) {
                    u4_t_calib_val = (U4) *((const volatile U1*)st_sp_XSPI_CALIB[u4_t_loop].vdp_mcuid);

                    /* Initialize target byte */
                    u4_sp_calib_buf[st_sp_XSPI_CALIB[u4_t_loop].u2_xspiid] &=
                        ~((U4)XSPI_MSK_08BIT << st_sp_XSPI_CALIB[u4_t_loop].u1_bitpos);

                    u4_sp_calib_buf[st_sp_XSPI_CALIB[u4_t_loop].u2_xspiid] |=
                        ((u4_t_calib_val & (U4)XSPI_MSK_08BIT)
                        << st_sp_XSPI_CALIB[u4_t_loop].u1_bitpos);
                }
                else if (st_sp_XSPI_CALIB[u4_t_loop].u1_size == (U1)XSPI_SIZE_U2) {
                    u4_t_calib_val = (U4) *((const volatile U2*)st_sp_XSPI_CALIB[u4_t_loop].vdp_mcuid);

                    /* Initialize target byte */
                    u4_sp_calib_buf[st_sp_XSPI_CALIB[u4_t_loop].u2_xspiid] &=
                        ~((U4)XSPI_MSK_16BIT << st_sp_XSPI_CALIB[u4_t_loop].u1_bitpos);

                    u4_sp_calib_buf[st_sp_XSPI_CALIB[u4_t_loop].u2_xspiid] |=
                        ((u4_t_calib_val & (U4)XSPI_MSK_16BIT)
                        << st_sp_XSPI_CALIB[u4_t_loop].u1_bitpos);

                }
                else {
                    /* Do Nothing */
                }
            }
        }
        else {
            /* Do Nothing */
        }
    }
    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)XSPI_MCUID_MINMAXCHK_NUM; u4_t_loop++) {

        if (st_sp_XSPI_CALIB_MINMAXCHK[u4_t_loop].u1p_mcuid != vdp_PTR_NA) {
            u4_t_calib_val = (U4) *(st_sp_XSPI_CALIB_MINMAXCHK[u4_t_loop].u1p_mcuid);
                
            if ((u4_t_calib_val < st_sp_XSPI_CALIB_MINMAXCHK[u4_t_loop].u4_min) ||
                (u4_t_calib_val > st_sp_XSPI_CALIB_MINMAXCHK[u4_t_loop].u4_max)) {
                u4_t_calib_val = st_sp_XSPI_CALIB_MINMAXCHK[u4_t_loop].u4_def;
            }
            
            /* Initialize target byte */
            u4_sp_calib_buf[st_sp_XSPI_CALIB_MINMAXCHK[u4_t_loop].u2_xspiid] &=
                ~((U4)XSPI_MSK_08BIT << st_sp_XSPI_CALIB_MINMAXCHK[u4_t_loop].u1_bitpos);

            u4_sp_calib_buf[st_sp_XSPI_CALIB_MINMAXCHK[u4_t_loop].u2_xspiid] |=
                ((u4_t_calib_val & (U4)XSPI_MSK_08BIT)
                << st_sp_XSPI_CALIB_MINMAXCHK[u4_t_loop].u1_bitpos);
        }
    }

    u1_s_calib_slot++;
}

/*===================================================================================================================================*/
/*  void    vd_g_XSpiCalibGetData(U4 * u4_ap_pdu_tx)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_XSpiCalibGetData(         U4 * u4_ap_pdu_tx)
{
    vd_g_MemcpyU4(u4_ap_pdu_tx, u4_sp_calib_buf, (U4)XSPI_CALIB_PAYLOAD_NUM);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     8/08/2024  KM       New.                                                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  19PFv3-1  9/06/2024  TN       Update for MET-M_MCUCONST-CSTD-A0-017-XXXD-XX.                                                     */
/*  19PFv3-2 10/23/2024  TN       Update for MET-M_MCUCONST-CSTD-A0-019-XXXD-XX.                                                     */
/*  19PFv3-3 04/07/2025  SH       Update for MET-M_MCUCONST-CSTD-A0-023-A-XX-XXXX-X.                                                 */
/*  19PFv3-4 04/15/2025  PG       Update for MET-P_GRTFOLP-CSTD-A0-02-A-C1.                                                          */
/*                                                                                                                                   */
/*  * KM   = Keisuke Mashita, DENSO-TECHNO                                                                                           */
/*  * TN   = Tetsushi Nakano, DENSO-TECHNO                                                                                           */
/*  * SH   = Sae Hirose, DENSO-TECHNO                                                                                                */
/*  * PG   = Patrick Garcia, DTPH                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
