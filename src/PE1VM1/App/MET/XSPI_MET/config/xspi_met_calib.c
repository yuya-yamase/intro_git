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
#include "vardef.h"

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
#define XSPI_CALIB_PAYLOAD_NUM                  (42U)

#define XSPI_MCUID_U1_NUM                       (5U)
#define XSPI_MCUID_U2_NUM                       (1U)
#define XSPI_MCUID_OMSCHK_U1_NUM                (21U)
#define XSPI_MCUID_OMSCHK_U2_NUM                (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    const U2                    u2_xspiid;
    const U1                    u1_bitpos;
    volatile const U1 *         u1p_mcuid;
}ST_XSPI_CALIB_U1;

typedef struct{
    const U2                    u2_xspiid;
    const U1                    u1_bitpos;
    volatile const U2 *         u2p_mcuid;
}ST_XSPI_CALIB_U2;

typedef struct{
    const U2                    u2_xspiid;
    const U1                    u1_bitpos;
    U1    (* const              fp_u1_CALIB_OMS)(void);
}ST_XSPI_CALIB_OMS_U1;

typedef struct{
    const U2                    u2_xspiid;
    const U1                    u1_bitpos;
    U2    (* const              fp_u2_CALIB_OMS)(void);
}ST_XSPI_CALIB_OMS_U2;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4                u4_sp_calib_buf[XSPI_CALIB_PAYLOAD_NUM]    __attribute__((aligned(8)));
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_XSPI_CALIB_U1 st_sp_XSPI_CALIB_U1[XSPI_MCUID_U1_NUM] = {
/*  u2_xspiid ,     u1_bitpos ,                 u1p_mcuid                          */
    {(U2) 1U,       (U1)XSPI_SHIFT_2BYTE,       &u1_CALIB_MCUID0219_G_GAUGE_MAX    },
    {(U2) 1U,       (U1)XSPI_SHIFT_3BYTE,       &u1_CALIB_MCUID0220_GTRAJECTORY2   },
    {(U2) 2U,       (U1)XSPI_SHIFT_NON,         &u1_CALIB_MCUID0221_G_DISP_MAX     },
    {(U2)28U,       (U1)XSPI_SHIFT_NON,         &u1_CALIB_MCUID0430_RHEOSW         },
    {(U2)41U,       (U1)XSPI_SHIFT_2BYTE,       &u1_CALIB_MCUID1137_NEW_FMVSS208   }
};

static const ST_XSPI_CALIB_U2 st_sp_XSPI_CALIB_U2[XSPI_MCUID_U2_NUM] = {
/*  u2_xspiid ,     u1_bitpos ,                 u2p_mcuid                          */
    {(U2)25U,       (U1)XSPI_SHIFT_2BYTE,       &u2_CALIB_MCUID0738_TIMEOUT_TM     }
};

static const ST_XSPI_CALIB_OMS_U1 st_sp_XSPI_CALIB_OMS_U1[XSPI_MCUID_OMSCHK_U1_NUM] = {
/*  u2_xspiid ,     u1_bitpos ,                 fp_u1_CALIB_OMS                    */
    {(U2) 0U,       (U1)XSPI_SHIFT_1BYTE,       &u1_g_VardefOmusMCUID0024          },
    {(U2) 0U,       (U1)XSPI_SHIFT_2BYTE,       &u1_g_VardefOmusMCUID0025          },
    {(U2) 2U,       (U1)XSPI_SHIFT_1BYTE,       &u1_g_VardefOmusMCUID0233          },
    {(U2) 2U,       (U1)XSPI_SHIFT_2BYTE,       &u1_g_VardefOmusMCUID0234          },
    {(U2) 2U,       (U1)XSPI_SHIFT_3BYTE,       &u1_g_VardefOmusMCUID0235          },
    {(U2) 4U,       (U1)XSPI_SHIFT_2BYTE,       &u1_g_VardefOmusMCUID0264          },
    {(U2) 5U,       (U1)XSPI_SHIFT_NON,         &u1_g_VardefOmusMCUID0268          },
    {(U2) 6U,       (U1)XSPI_SHIFT_3BYTE,       &u1_g_VardefOmusMCUID0590          },
    {(U2)38U,       (U1)XSPI_SHIFT_2BYTE,       &u1_g_VardefOmusMCUID0209          },
    {(U2)38U,       (U1)XSPI_SHIFT_3BYTE,       &u1_g_VardefOmusMCUID0210          },
    {(U2)39U,       (U1)XSPI_SHIFT_NON,         &u1_g_VardefOmusMCUID0211          },
    {(U2)39U,       (U1)XSPI_SHIFT_1BYTE,       &u1_g_VardefOmusMCUID0212          },
    {(U2)39U,       (U1)XSPI_SHIFT_2BYTE,       &u1_g_VardefOmusMCUID0213          },
    {(U2)39U,       (U1)XSPI_SHIFT_3BYTE,       &u1_g_VardefOmusMCUID0214          },
    {(U2)40U,       (U1)XSPI_SHIFT_NON,         &u1_g_VardefOmusMCUID0215          },
    {(U2)40U,       (U1)XSPI_SHIFT_1BYTE,       &u1_g_VardefOmusMCUID0809          },
    {(U2)40U,       (U1)XSPI_SHIFT_2BYTE,       &u1_g_VardefOmusMCUID0810          },
    {(U2)40U,       (U1)XSPI_SHIFT_3BYTE,       &u1_g_VardefOmusMCUID3020          },
    {(U2)41U,       (U1)XSPI_SHIFT_NON,         &u1_g_VardefOmusMCUID0798          },
    {(U2)41U,       (U1)XSPI_SHIFT_1BYTE,       &u1_g_VardefOmusMCUID3025          },
    {(U2)41U,       (U1)XSPI_SHIFT_3BYTE,       &u1_g_VardefOmusMCUID1138          }
};

static const ST_XSPI_CALIB_OMS_U2 st_sp_XSPI_CALIB_OMS_U2[XSPI_MCUID_OMSCHK_U2_NUM] = {
/*  u2_xspiid ,     u1_bitpos ,                 fp_u2_CALIB_OMS                    */
    {(U2) 3U,       (U1)XSPI_SHIFT_2BYTE,       &u2_g_VardefOmusMCUID0262          },
    {(U2) 4U,       (U1)XSPI_SHIFT_NON,         &u2_g_VardefOmusMCUID0263          }
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

    vd_g_MemfillU4(&u4_sp_calib_buf[0], (U4)0U, (U4)XSPI_CALIB_PAYLOAD_NUM);

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)XSPI_MCUID_U1_NUM; u4_t_loop++) {
        if (st_sp_XSPI_CALIB_U1[u4_t_loop].u1p_mcuid != vdp_PTR_NA) {
            u4_t_calib_val = (U4) *(st_sp_XSPI_CALIB_U1[u4_t_loop].u1p_mcuid);

            u4_sp_calib_buf[st_sp_XSPI_CALIB_U1[u4_t_loop].u2_xspiid] |=
                ((u4_t_calib_val & (U4)XSPI_MSK_08BIT)
                << st_sp_XSPI_CALIB_U1[u4_t_loop].u1_bitpos);
        }
    }

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)XSPI_MCUID_U2_NUM; u4_t_loop++) {
        if (st_sp_XSPI_CALIB_U2[u4_t_loop].u2p_mcuid != vdp_PTR_NA) {
            u4_t_calib_val = (U4) *(st_sp_XSPI_CALIB_U2[u4_t_loop].u2p_mcuid);

            u4_sp_calib_buf[st_sp_XSPI_CALIB_U2[u4_t_loop].u2_xspiid] |=
                ((u4_t_calib_val & (U4)XSPI_MSK_16BIT)
                << st_sp_XSPI_CALIB_U2[u4_t_loop].u1_bitpos);
        }
    }

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)XSPI_MCUID_OMSCHK_U1_NUM; u4_t_loop++) {
        if (st_sp_XSPI_CALIB_OMS_U1[u4_t_loop].fp_u1_CALIB_OMS != vdp_PTR_NA) {
            u4_t_calib_val = (U4)(st_sp_XSPI_CALIB_OMS_U1[u4_t_loop].fp_u1_CALIB_OMS());

            u4_sp_calib_buf[st_sp_XSPI_CALIB_OMS_U1[u4_t_loop].u2_xspiid] |=
                ((u4_t_calib_val & (U4)XSPI_MSK_08BIT)
                << st_sp_XSPI_CALIB_OMS_U1[u4_t_loop].u1_bitpos);
        }
    }

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)XSPI_MCUID_OMSCHK_U2_NUM; u4_t_loop++) {
        if (st_sp_XSPI_CALIB_OMS_U2[u4_t_loop].fp_u2_CALIB_OMS != vdp_PTR_NA) {
            u4_t_calib_val = (U4)(st_sp_XSPI_CALIB_OMS_U2[u4_t_loop].fp_u2_CALIB_OMS());

            u4_sp_calib_buf[st_sp_XSPI_CALIB_OMS_U2[u4_t_loop].u2_xspiid] |=
                ((u4_t_calib_val & (U4)XSPI_MSK_16BIT)
                << st_sp_XSPI_CALIB_OMS_U2[u4_t_loop].u1_bitpos);
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

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)XSPI_MCUID_U1_NUM; u4_t_loop++) {

        if (st_sp_XSPI_CALIB_U1[u4_t_loop].u1p_mcuid != vdp_PTR_NA) {
            u4_t_calib_val = (U4) *(st_sp_XSPI_CALIB_U1[u4_t_loop].u1p_mcuid);
            /* Reset target byte */
            u4_sp_calib_buf[st_sp_XSPI_CALIB_U1[u4_t_loop].u2_xspiid] &=
                ~((U4)XSPI_MSK_08BIT << st_sp_XSPI_CALIB_U1[u4_t_loop].u1_bitpos);
            /* Set target byte   */
            u4_sp_calib_buf[st_sp_XSPI_CALIB_U1[u4_t_loop].u2_xspiid] |=
                ((u4_t_calib_val & (U4)XSPI_MSK_08BIT)
                << st_sp_XSPI_CALIB_U1[u4_t_loop].u1_bitpos);
        }
    }
    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)XSPI_MCUID_U2_NUM; u4_t_loop++) {

        if (st_sp_XSPI_CALIB_U2[u4_t_loop].u2p_mcuid != vdp_PTR_NA) {
            u4_t_calib_val = (U4) *(st_sp_XSPI_CALIB_U2[u4_t_loop].u2p_mcuid);
            /* Reset target byte */
            u4_sp_calib_buf[st_sp_XSPI_CALIB_U2[u4_t_loop].u2_xspiid] &=
                ~((U4)XSPI_MSK_16BIT << st_sp_XSPI_CALIB_U2[u4_t_loop].u1_bitpos);
            /* Set target byte   */
            u4_sp_calib_buf[st_sp_XSPI_CALIB_U2[u4_t_loop].u2_xspiid] |=
                ((u4_t_calib_val & (U4)XSPI_MSK_16BIT)
                << st_sp_XSPI_CALIB_U2[u4_t_loop].u1_bitpos);
        }
    }
    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)XSPI_MCUID_OMSCHK_U1_NUM; u4_t_loop++) {
        if (st_sp_XSPI_CALIB_OMS_U1[u4_t_loop].fp_u1_CALIB_OMS != vdp_PTR_NA) {
            u4_t_calib_val = (U4) (st_sp_XSPI_CALIB_OMS_U1[u4_t_loop].fp_u1_CALIB_OMS());

            /* Reset target byte */
            u4_sp_calib_buf[st_sp_XSPI_CALIB_OMS_U1[u4_t_loop].u2_xspiid] &=
                ~((U4)XSPI_MSK_08BIT << st_sp_XSPI_CALIB_OMS_U1[u4_t_loop].u1_bitpos);
            /* Set target byte   */
            u4_sp_calib_buf[st_sp_XSPI_CALIB_OMS_U1[u4_t_loop].u2_xspiid] |=
                ((u4_t_calib_val & (U4)XSPI_MSK_08BIT)
                << st_sp_XSPI_CALIB_OMS_U1[u4_t_loop].u1_bitpos);
        }
    }
    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)XSPI_MCUID_OMSCHK_U2_NUM; u4_t_loop++) {
        if (st_sp_XSPI_CALIB_OMS_U2[u4_t_loop].fp_u2_CALIB_OMS != vdp_PTR_NA) {
            u4_t_calib_val = (U4) (st_sp_XSPI_CALIB_OMS_U2[u4_t_loop].fp_u2_CALIB_OMS());

            /* Reset target byte */
            u4_sp_calib_buf[st_sp_XSPI_CALIB_OMS_U2[u4_t_loop].u2_xspiid] &=
                ~((U4)XSPI_MSK_16BIT << st_sp_XSPI_CALIB_OMS_U2[u4_t_loop].u1_bitpos);
            /* Set target byte   */
            u4_sp_calib_buf[st_sp_XSPI_CALIB_OMS_U2[u4_t_loop].u2_xspiid] |=
                ((u4_t_calib_val & (U4)XSPI_MSK_16BIT)
                << st_sp_XSPI_CALIB_OMS_U2[u4_t_loop].u1_bitpos);
        }
    }

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
/*  BEV-1    02/10/2026  SH       Change MCUID from Calibration to OMUSVIID and Separate MCUID tables by data size                   */
/*                                                                                                                                   */
/*  * KM   = Keisuke Mashita, DENSO-TECHNO                                                                                           */
/*  * TN   = Tetsushi Nakano, DENSO-TECHNO                                                                                           */
/*  * SH   = Sae Hirose, DENSO-TECHNO                                                                                                */
/*  * PG   = Patrick Garcia, DTPH                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
