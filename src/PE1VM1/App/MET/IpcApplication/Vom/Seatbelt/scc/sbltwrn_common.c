/* 3.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Seatbelt reminder warning                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SBLTWRN_COMMON_C_MAJOR                         (3)
#define SBLTWRN_COMMON_C_MINOR                         (1)
#define SBLTWRN_COMMON_C_PATCH                         (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "sbltwrn_cfg_private.h"
#include "memfill_u1.h"
#include "memfill_u2.h"
#include "sbltwrn.h"
#include "sbltwrn_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((SBLTWRN_COMMON_C_MAJOR != SBLTWRN_H_MAJOR) || \
     (SBLTWRN_COMMON_C_MINOR != SBLTWRN_H_MINOR) || \
     (SBLTWRN_COMMON_C_PATCH != SBLTWRN_H_PATCH))
#error "sbltwrn_common.c and sbltwrn.h : source and header files are inconsistent!"
#endif

#if ((SBLTWRN_COMMON_C_MAJOR != SBLTWRN_CFG_PRIVATE_H_MAJOR) || \
     (SBLTWRN_COMMON_C_MINOR != SBLTWRN_CFG_PRIVATE_H_MINOR) || \
     (SBLTWRN_COMMON_C_PATCH != SBLTWRN_CFG_PRIVATE_H_PATCH))
#error "sbltwrn_common.c and sbltwrn_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((SBLTWRN_COMMON_C_MAJOR != SBLTWRN_PRIVATE_H_MAJOR) || \
     (SBLTWRN_COMMON_C_MINOR != SBLTWRN_PRIVATE_H_MINOR) || \
     (SBLTWRN_COMMON_C_PATCH != SBLTWRN_PRIVATE_H_PATCH))
#error "sbltwrn_common.c and sbltwrn_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  U1                      u1_sp_sbltwrn_stvarcfg[SBLTWRN_NUM_ALLSEAT];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static        U1      u1_s_SbltwrnMsgjdg(const U1 u1_a_MSGSTS);
static        void    vd_s_SbltwrnGetCalibRear1(void);
static        void    vd_s_SbltwrnGetCalibRear2(void);
static        void    vd_s_SbltwrnGetCalibRear3(void);
static inline U1      u1_s_SbltwrnCalibU1MaxChk(const U1 u1_a_CALIBID, const U1 u1_a_MAX, const U1 u1_a_DEF);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  U1      (* const  fp_sp_SEATFUNC[SBLTWRN_NUM_SEAT_FUNC])(const U1* u1_ap_MSGSTS, const U4 u4_a_SEATID, const U4 u4_a_VCLSTS) = {
    &u1_g_SbltDs,                                                                        /*  00 SBLTWRN_SEAT_DS                      */
    &u1_g_SbltPs,                                                                        /*  01 SBLTWRN_SEAT_PS                      */
    &u1_g_SbltFc,                                                                        /*  02 SBLTWRN_SEAT_FC                      */
    &u1_g_SbltRsRxbklpdc,                                                                /*  03 SBLTWRN_SEAT_RS_RXBKLPDC             */
    &u1_g_SbltRsRxbklpdc_Rxosw,                                                          /*  04 SBLTWRN_SEAT_RS_RXBKLPDC_RXOSW       */
    &u1_g_SbltRsXrxbkl,                                                                  /*  05 SBLTWRN_SEAT_RS_XRXBKL               */
    &u1_g_SbltRsXrxbkl_Rxxosw,                                                           /*  06 SBLTWRN_SEAT_RS_XRXBKL_RXXOSW        */
};

static const U1                 u1_sp_SBLTWRN_SEATTYP[SBLTWRN_NUM_SEAT_FUNC] = {
    (U1)SBLTWRN_SEATTYP_DS,
    (U1)SBLTWRN_SEATTYP_PS,
    (U1)SBLTWRN_SEATTYP_PS,
    (U1)SBLTWRN_SEATTYP_RS_NOSN,
    (U1)SBLTWRN_SEATTYP_RS_SNSR,
    (U1)SBLTWRN_SEATTYP_RS_NOSN,
    (U1)SBLTWRN_SEATTYP_RS_SNSR
};

static const ST_SBLTWRN_WRNPRM  st_sp_SBLTWRN_US_SB_PRM[SBLTWRN_NUM_SEATTYP] = {
    /* (Undefined) */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(1800U / SBLTWRN_TICK),  (U2)(7800U / SBLTWRN_TICK),  (U2)(18000U / SBLTWRN_TICK), (U2)(6000U / SBLTWRN_TICK), (U2)(100000U / SBLTWRN_TICK),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    },
    /* D-Seat */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(1800U / SBLTWRN_TICK),  (U2)(7800U / SBLTWRN_TICK),  (U2)(18000U / SBLTWRN_TICK), (U2)(6000U / SBLTWRN_TICK), (U2)(100000U / SBLTWRN_TICK),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    },
    /* P-Seat */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(18000U / SBLTWRN_TICK), (U2)(6000U / SBLTWRN_TICK), (U2)(100000U / SBLTWRN_TICK),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    },
    /* Rr-Seat (with occupant detection sensor) */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(18000U / SBLTWRN_TICK), (U2)(6000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK),
          (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
}
    },
    /* Rr-Seat (w/o  occupant detection sensor) */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(18000U / SBLTWRN_TICK), (U2)(6000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK),
          (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    }
};

static const ST_SBLTWRN_WRNPRM  st_sp_SBLTWRN_EU_SB_PRM[SBLTWRN_NUM_SEATTYP] = {
    /* (Undefined) */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(1800U / SBLTWRN_TICK),  (U2)(7800U / SBLTWRN_TICK),  (U2)(18000U / SBLTWRN_TICK), (U2)(6000U / SBLTWRN_TICK), (U2)(100000U / SBLTWRN_TICK),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    },
    /* D-Seat */
    {
        (U4)SBLTWRN_CTLOPT_PRKWRN,
        {
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(24000U / SBLTWRN_TICK), (U2)(100000U / SBLTWRN_TICK),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    },
    /* P-Seat */
    {
        (U4)SBLTWRN_CTLOPT_PRKWRN,
        {
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(24000U / SBLTWRN_TICK), (U2)(100000U / SBLTWRN_TICK),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    },
    /* Rr-Seat (with occupant detection sensor) */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(24000U / SBLTWRN_TICK), (U2)(100000U / SBLTWRN_TICK),
          (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    },
    /* Rr-Seat (w/o  occupant detection sensor) */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(6000U / SBLTWRN_TICK), (U2)(60000U / SBLTWRN_TICK),
          (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    }
};

static const ST_SBLTWRN_WRNPRM  st_sp_SBLTWRN_CN_SB_PRM[SBLTWRN_NUM_SEATTYP] = {
    /* (Undefined) */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(1800U / SBLTWRN_TICK),  (U2)(7800U / SBLTWRN_TICK),  (U2)(18000U / SBLTWRN_TICK), (U2)(6000U / SBLTWRN_TICK), (U2)(100000U / SBLTWRN_TICK),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    },
    /* D-Seat */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(6000U / SBLTWRN_TICK), (U2)(100000U / SBLTWRN_TICK),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    },
    /* P-Seat */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(6000U / SBLTWRN_TICK), (U2)(100000U / SBLTWRN_TICK),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    },
    /* Rr-Seat (with occupant detection sensor) */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(6000U / SBLTWRN_TICK), (U2)(100000U / SBLTWRN_TICK),
          (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    },
    /* Rr-Seat (w/o  occupant detection sensor) */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(6000U / SBLTWRN_TICK), (U2)(60000U / SBLTWRN_TICK),
          (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    }
};

static const ST_SBLTWRN_WRNPRM  st_sp_SBLTWRN_US_LS_PRM[SBLTWRN_NUM_SEATTYP] = {
    /* (Undefined) */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(1800U / SBLTWRN_TICK),  (U2)(7800U / SBLTWRN_TICK),  (U2)(18000U / SBLTWRN_TICK), (U2)(6000U / SBLTWRN_TICK), (U2)(100800U / SBLTWRN_TICK),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    },
    /* D-Seat */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(1800U / SBLTWRN_TICK),  (U2)(7800U / SBLTWRN_TICK),  (U2)(18000U / SBLTWRN_TICK), (U2)(6000U / SBLTWRN_TICK), (U2)(100800U / SBLTWRN_TICK),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    },
    /* P-Seat */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(18000U / SBLTWRN_TICK), (U2)(6000U / SBLTWRN_TICK), (U2)(100800U / SBLTWRN_TICK),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    },
    /* Rr-Seat (with occupant detection sensor) */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(18000U / SBLTWRN_TICK), (U2)(6000U / SBLTWRN_TICK), (U2)(64800U / SBLTWRN_TICK),
          (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    },
    /* Rr-Seat (w/o  occupant detection sensor) */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(18000U / SBLTWRN_TICK), (U2)(6000U / SBLTWRN_TICK), (U2)(64800U / SBLTWRN_TICK),
          (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    }
};

static const ST_SBLTWRN_WRNPRM      st_sp_SBLTWRN_EU_LS_PRM[SBLTWRN_NUM_SEATTYP] = {
    /* (Undefined) */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(24000U / SBLTWRN_TICK), (U2)(100800U / SBLTWRN_TICK),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    },
    /* D-Seat */
    {
        (U4)SBLTWRN_CTLOPT_PRKWRN,
        {
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(24000U / SBLTWRN_TICK), (U2)(100800U / SBLTWRN_TICK),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    },
    /* P-Seat */
    {
        (U4)SBLTWRN_CTLOPT_PRKWRN,
        {
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(24000U / SBLTWRN_TICK), (U2)(100800U / SBLTWRN_TICK),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    },
    /* Rr-Seat (with occupant detection sensor) */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(24000U / SBLTWRN_TICK), (U2)(100800U / SBLTWRN_TICK),
          (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    },
    /* Rr-Seat (w/o  occupant detection sensor) */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(6000U / SBLTWRN_TICK),  (U2)(64800U / SBLTWRN_TICK),
          (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    }
};

static const ST_SBLTWRN_WRNPRM      st_sp_SBLTWRN_CN_LS_PRM[SBLTWRN_NUM_SEATTYP] = {
    /* (Undefined) */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(6000U / SBLTWRN_TICK), (U2)(100800U / SBLTWRN_TICK),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    },
    /* D-Seat */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(6000U / SBLTWRN_TICK), (U2)(100800U / SBLTWRN_TICK),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    },
    /* P-Seat */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(6000U / SBLTWRN_TICK), (U2)(100800U / SBLTWRN_TICK),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    },
    /* Rr-Seat (with occupant detection sensor) */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(6000U / SBLTWRN_TICK), (U2)(100800U / SBLTWRN_TICK),
          (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    },
    /* Rr-Seat (w/o  occupant detection sensor) */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(6000U / SBLTWRN_TICK),  (U2)(64800U / SBLTWRN_TICK),
          (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    }
};

static const ST_SBLTWRN_WRNPRM      st_sp_SBLTWRN_US_TS_PRM[SBLTWRN_NUM_SEATTYP] = {
    /* (Undefined) */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(1800U / SBLTWRN_TICK),  (U2)(7800U / SBLTWRN_TICK),  (U2)(18000U / SBLTWRN_TICK), (U2)(6000U / SBLTWRN_TICK), (U2)(100000U / SBLTWRN_TICK),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    },
    /* D-Seat */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(1800U / SBLTWRN_TICK),  (U2)(7800U / SBLTWRN_TICK),  (U2)(18000U / SBLTWRN_TICK), (U2)(6000U / SBLTWRN_TICK), (U2)(100000U / SBLTWRN_TICK),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    },
    /* P-Seat */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(18000U / SBLTWRN_TICK), (U2)(6000U / SBLTWRN_TICK), (U2)(100000U / SBLTWRN_TICK),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    },
    /* Rr-Seat (with occupant detection sensor) */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(18000U / SBLTWRN_TICK), (U2)(6000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK),
          (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
}
    },
    /* Rr-Seat (w/o  occupant detection sensor) */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(18000U / SBLTWRN_TICK), (U2)(6000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK),
          (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    }
};

static const ST_SBLTWRN_WRNPRM      st_sp_SBLTWRN_EU_TS_PRM[SBLTWRN_NUM_SEATTYP] = {
    /* (Undefined) */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(1800U / SBLTWRN_TICK),  (U2)(7800U / SBLTWRN_TICK),  (U2)(18000U / SBLTWRN_TICK), (U2)(6000U / SBLTWRN_TICK), (U2)(100000U / SBLTWRN_TICK),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    },
    /* D-Seat */
    {
        (U4)SBLTWRN_CTLOPT_PRKWRN,
        {
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(24000U / SBLTWRN_TICK), (U2)(100000U / SBLTWRN_TICK),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    },
    /* P-Seat */
    {
        (U4)SBLTWRN_CTLOPT_PRKWRN,
        {
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(24000U / SBLTWRN_TICK), (U2)(100000U / SBLTWRN_TICK),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    },
    /* Rr-Seat (with occupant detection sensor) */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(24000U / SBLTWRN_TICK), (U2)(100000U / SBLTWRN_TICK),
          (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    },
    /* Rr-Seat (w/o  occupant detection sensor) */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(6000U / SBLTWRN_TICK), (U2)(60000U / SBLTWRN_TICK),
          (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    }

};

static const ST_SBLTWRN_WRNPRM      st_sp_SBLTWRN_CN_TS_PRM[SBLTWRN_NUM_SEATTYP] = {
    /* (Undefined) */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(1800U / SBLTWRN_TICK),  (U2)(7800U / SBLTWRN_TICK),  (U2)(18000U / SBLTWRN_TICK), (U2)(6000U / SBLTWRN_TICK), (U2)(100000U / SBLTWRN_TICK),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    },
    /* D-Seat */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(6000U / SBLTWRN_TICK), (U2)(100000U / SBLTWRN_TICK),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    },
    /* P-Seat */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(6000U / SBLTWRN_TICK), (U2)(100000U / SBLTWRN_TICK),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    },
    /* Rr-Seat (with occupant detection sensor) */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(6000U / SBLTWRN_TICK), (U2)(100000U / SBLTWRN_TICK),
          (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    },
    /* Rr-Seat (w/o  occupant detection sensor) */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(6000U / SBLTWRN_TICK), (U2)(60000U / SBLTWRN_TICK),
          (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    }
};

static const ST_SBLTWRN_WRNPRM  st_sp_SBLTWRN_FM_SB_PRM[SBLTWRN_NUM_SEATTYP] = {
    /* (Undefined) */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(1800U / SBLTWRN_TICK),  (U2)(7800U / SBLTWRN_TICK),  (U2)(18000U / SBLTWRN_TICK), (U2)(6000U / SBLTWRN_TICK),  (U2)(100000U / SBLTWRN_TICK),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    },
    /* D-Seat */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(1800U / SBLTWRN_TICK),  (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(24000U / SBLTWRN_TICK), (U2)(0U / SBLTWRN_TICK),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(U2_MAX),
          (U2)(36000U / SBLTWRN_TICK), (U2)(36000U / SBLTWRN_TICK), (U2)(36000U / SBLTWRN_TICK)
        }
    },
    /* P-Seat */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(1800U / SBLTWRN_TICK),  (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(24000U / SBLTWRN_TICK), (U2)(0U / SBLTWRN_TICK),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(U2_MAX),
          (U2)(36000U / SBLTWRN_TICK), (U2)(36000U / SBLTWRN_TICK), (U2)(36000U / SBLTWRN_TICK)
        }
    },
    /* Rr-Seat (with occupant detection sensor) */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    },
    /* Rr-Seat (w/o  occupant detection sensor) */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(1800U / SBLTWRN_TICK),  (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(24000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK),
          (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(U2_MAX),
          (U2)(36000U / SBLTWRN_TICK), (U2)(36000U / SBLTWRN_TICK), (U2)(36000U / SBLTWRN_TICK)
        }
    }
};

static const ST_SBLTWRN_WRNPRM  st_sp_SBLTWRN_FM_LS_PRM[SBLTWRN_NUM_SEATTYP] = {
    /* (Undefined) */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(1800U / SBLTWRN_TICK),  (U2)(7800U / SBLTWRN_TICK),  (U2)(18000U / SBLTWRN_TICK), (U2)(6000U / SBLTWRN_TICK),  (U2)(100800U / SBLTWRN_TICK),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    },
    /* D-Seat */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(1800U / SBLTWRN_TICK),  (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(24000U / SBLTWRN_TICK), (U2)(0U / SBLTWRN_TICK),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(U2_MAX),
          (U2)(36000U / SBLTWRN_TICK), (U2)(36000U / SBLTWRN_TICK), (U2)(36000U / SBLTWRN_TICK)
        }
    },
    /* P-Seat */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(1800U / SBLTWRN_TICK),  (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(24000U / SBLTWRN_TICK), (U2)(0U / SBLTWRN_TICK),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(U2_MAX),
          (U2)(36000U / SBLTWRN_TICK), (U2)(36000U / SBLTWRN_TICK), (U2)(36000U / SBLTWRN_TICK)
        }
    },
    /* Rr-Seat (with occupant detection sensor) */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    },
    /* Rr-Seat (w/o  occupant detection sensor) */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(1800U / SBLTWRN_TICK),  (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(24000U / SBLTWRN_TICK), (U2)(64800U / SBLTWRN_TICK),
          (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(U2_MAX),
          (U2)(36000U / SBLTWRN_TICK), (U2)(36000U / SBLTWRN_TICK), (U2)(36000U / SBLTWRN_TICK)
        }
    }
};

static const ST_SBLTWRN_WRNPRM  st_sp_SBLTWRN_FM_TS_PRM[SBLTWRN_NUM_SEATTYP] = {
    /* (Undefined) */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(1800U / SBLTWRN_TICK),  (U2)(7800U / SBLTWRN_TICK),  (U2)(18000U / SBLTWRN_TICK), (U2)(6000U / SBLTWRN_TICK),  (U2)(100800U / SBLTWRN_TICK),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    },
    /* D-Seat */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(1800U / SBLTWRN_TICK),  (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(24000U / SBLTWRN_TICK), (U2)(0U / SBLTWRN_TICK),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(U2_MAX),
          (U2)(36000U / SBLTWRN_TICK), (U2)(36000U / SBLTWRN_TICK), (U2)(36000U / SBLTWRN_TICK)
        }
    },
    /* P-Seat */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(1800U / SBLTWRN_TICK),  (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(24000U / SBLTWRN_TICK), (U2)(0U / SBLTWRN_TICK),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(U2_MAX),
          (U2)(36000U / SBLTWRN_TICK), (U2)(36000U / SBLTWRN_TICK), (U2)(36000U / SBLTWRN_TICK)
        }
    },
    /* Rr-Seat (with occupant detection sensor) */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(U2_MAX),
          (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK)
        }
    },
    /* Rr-Seat (w/o  occupant detection sensor) */
    {
        (U4)SBLTWRN_CTLOPT_NON,
        {
          (U2)(1800U / SBLTWRN_TICK),  (U2)(0U / SBLTWRN_TICK),     (U2)(0U / SBLTWRN_TICK),     (U2)(24000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK),
          (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(66000U / SBLTWRN_TICK), (U2)(U2_MAX),
          (U2)(36000U / SBLTWRN_TICK), (U2)(36000U / SBLTWRN_TICK), (U2)(36000U / SBLTWRN_TICK)
        }
    }
};

const ST_SBLTWRN_WRNPRM * const st_gp_SBLTWRN_WRNPRM[SBLTWRN_NUM_DEST] = {
    &st_sp_SBLTWRN_US_SB_PRM[0],
    &st_sp_SBLTWRN_EU_SB_PRM[0],
    &st_sp_SBLTWRN_CN_SB_PRM[0],
    &st_sp_SBLTWRN_US_LS_PRM[0],
    &st_sp_SBLTWRN_EU_LS_PRM[0],
    &st_sp_SBLTWRN_CN_LS_PRM[0],
    &st_sp_SBLTWRN_US_TS_PRM[0],
    &st_sp_SBLTWRN_EU_TS_PRM[0],
    &st_sp_SBLTWRN_CN_TS_PRM[0],
    &st_sp_SBLTWRN_FM_SB_PRM[0],
    &st_sp_SBLTWRN_FM_LS_PRM[0],
    &st_sp_SBLTWRN_FM_TS_PRM[0]
};

const ST_SBLTWRN_VCLPRM      st_gp_SBLTWRN_VCLPRM[SBLTWRN_NUM_DEST] = {
    { (U4)SBLTWRN_CMNOPT_SNSR_L2CMP_ON, { (U2) 500U, (U2)2000U, (U2)175U, (U2)500U, (U2)3500U } },
    { (U4)SBLTWRN_CMNOPT_SNSR_L2CMP_ON, { (U2)1000U, (U2)2000U, (U2)175U, (U2)500U, (U2)3500U } },
    { (U4)SBLTWRN_CMNOPT_SNSR_L2CMP_ON, { (U2) 500U, (U2) 500U, (U2)175U, (U2)500U, (U2)3500U } },
    { (U4)SBLTWRN_CMNOPT_SNSR_L2CMP_ON, { (U2) 500U, (U2)2000U, (U2)175U, (U2)500U, (U2)3500U } },
    { (U4)SBLTWRN_CMNOPT_SNSR_L2CMP_ON, { (U2)1000U, (U2)2000U, (U2)175U, (U2)500U, (U2)3500U } },
    { (U4)SBLTWRN_CMNOPT_SNSR_L2CMP_ON, { (U2) 500U, (U2) 500U, (U2)175U, (U2)500U, (U2)3500U } },
    { (U4)SBLTWRN_CMNOPT_SNSR_L2CMP_ON, { (U2) 500U, (U2)2000U, (U2)175U, (U2)500U, (U2)3500U } },
    { (U4)SBLTWRN_CMNOPT_SNSR_L2CMP_ON, { (U2)1000U, (U2)2000U, (U2)175U, (U2)500U, (U2)3500U } },
    { (U4)SBLTWRN_CMNOPT_SNSR_L2CMP_ON, { (U2) 500U, (U2) 500U, (U2)175U, (U2)500U, (U2)3500U } },
    { (U4)SBLTWRN_CMNOPT_NON,           { (U2)   0U, (U2) 500U, (U2)175U, (U2)500U, (U2)3500U } },
    { (U4)SBLTWRN_CMNOPT_NON,           { (U2)   0U, (U2) 500U, (U2)175U, (U2)500U, (U2)3500U } },
    { (U4)SBLTWRN_CMNOPT_NON,           { (U2)   0U, (U2) 500U, (U2)175U, (U2)500U, (U2)3500U } }
};

const ST_SBLTWRN_STSTBL st_gp_SBLTWRN_SBR_STSTBL[SBLTWRN_NUM_3ROWSEAT] = {
    { (U1)SBLTWRN_SBRBIT_IDX0,          (U1)SBLTWRN_DRV_SEAT_BIT_IDX0   },
    { (U1)SBLTWRN_SBRBIT_IDX0,          (U1)SBLTWRN_FRC_SEAT_BIT_IDX0   },
    { (U1)SBLTWRN_SBRBIT_IDX0,          (U1)SBLTWRN_PSG_SEAT_BIT_IDX0   },
    { (U1)SBLTWRN_SBRBIT_IDX0,          (U1)SBLTWRN_R2L_SEAT_BIT_IDX0   },
    { (U1)SBLTWRN_SBRBIT_IDX0,          (U1)SBLTWRN_R2C_SEAT_BIT_IDX0   },
    { (U1)SBLTWRN_SBRBIT_IDX0,          (U1)SBLTWRN_R2R_SEAT_BIT_IDX0   },
    { (U1)SBLTWRN_SBRBIT_IDX1,          (U1)SBLTWRN_R3L_SEAT_BIT_IDX1   },
    { (U1)SBLTWRN_SBRBIT_IDX0,          (U1)SBLTWRN_R3C_SEAT_BIT_IDX0   },
    { (U1)SBLTWRN_SBRBIT_IDX0,          (U1)SBLTWRN_R3R_SEAT_BIT_IDX0   }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* U1      u1_g_SbltwrnChmStmVldChk(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS)               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_SbltwrnChmStmVldChk(const U1 u1_a_SEATID, const U1 u1_a_SEATTYP, const ST_SBLTWRN_VCLST *stp_a_VCLSTS)
{
    U1  u1_t_valid;

    if ((stp_a_VCLSTS->u2_igontm > (U2)0U) && (u1_a_SEATTYP != (U1)SBLTWRN_SEATTYP_UNDEF) && ((stp_a_VCLSTS->u1p_bklsts[u1_a_SEATID] & (U1)SBLTWRN_BKLSTS_COMFAIL) == (U1)0U)) {
        u1_t_valid = (U1)TRUE;
    } else {
        u1_t_valid = (U1)FALSE;
    }

    return (u1_t_valid);
}

/*===================================================================================================================================*/
/* U1      u1_g_SbltwrnDrchk(const U4 u4_a_VCLSTS, const U1 u1_a_SEATTYP, const U1 u1_a_ANYDR)                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_SbltwrnDrchk(const U4 u4_a_VCLSTS, const U1 u1_a_SEATTYP, const U1 u1_a_ANYDR)
{
    static const U4     u4_sp_DROPN_CHK[SBLTWRN_NUM_SEATTYP << 3] = {
        (U4)0x00000000U,            (U4)0x00000000U,                /* SBLTWRN_SEATTYP_UNDEF */
        (U4)0x00000000U,            (U4)0x00000000U,                /* SBLTWRN_SEATTYP_UNDEF */
        (U4)0x00000000U,            (U4)0x00000000U,                /* SBLTWRN_SEATTYP_UNDEF */
        (U4)0x00000000U,            (U4)0x00000000U,                /* SBLTWRN_SEATTYP_UNDEF */
        (U4)SBLTWRN_VCLSTS_D_DR_OP, (U4)SBLTWRN_VCLSTS_D_DR_OP,     /* SBLTWRN_SEATTYP_DS */
        (U4)SBLTWRN_VCLSTS_D_DR_OP, (U4)SBLTWRN_VCLSTS_D_DR_OP,     /* SBLTWRN_SEATTYP_DS */
        (U4)SBLTWRN_VCLSTS_D_DR_OP, (U4)SBLTWRN_VCLSTS_D_DR_OP,     /* SBLTWRN_SEATTYP_DS */
        (U4)SBLTWRN_VCLSTS_D_DR_OP, (U4)SBLTWRN_VCLSTS_D_DR_OP,     /* SBLTWRN_SEATTYP_DS */
        (U4)SBLTWRN_VCLSTS_P_DR_OP, (U4)SBLTWRN_VCLSTS_P_DR_OP,     /* SBLTWRN_SEATTYP_PS */
        (U4)SBLTWRN_VCLSTS_P_DR_OP, (U4)SBLTWRN_VCLSTS_P_DR_OP,     /* SBLTWRN_SEATTYP_PS */
        (U4)SBLTWRN_VCLSTS_P_DR_OP, (U4)SBLTWRN_VCLSTS_P_DR_OP,     /* SBLTWRN_SEATTYP_PS */
        (U4)SBLTWRN_VCLSTS_P_DR_OP, (U4)SBLTWRN_VCLSTS_P_DR_OP,     /* SBLTWRN_SEATTYP_PS */
        (U4)SBLTWRN_VCLSTS_DP_DR_OP,(U4)SBLTWRN_VCLSTS_DPB_DR_OP,   /* SBLTWRN_SEATTYP_RS_SNSR */
        (U4)SBLTWRN_VCLSTS_R_DR_OP, (U4)SBLTWRN_VCLSTS_RB_DR_OP,    /* SBLTWRN_SEATTYP_RS_SNSR */
        (U4)SBLTWRN_VCLSTS_DP_DR_OP,(U4)SBLTWRN_VCLSTS_PRB_DR_OP,   /* SBLTWRN_SEATTYP_RS_SNSR */
        (U4)SBLTWRN_VCLSTS_R_DR_OP, (U4)SBLTWRN_VCLSTS_PRB_DR_OP,   /* SBLTWRN_SEATTYP_RS_SNSR */
        (U4)SBLTWRN_VCLSTS_DP_DR_OP,(U4)SBLTWRN_VCLSTS_DPB_DR_OP,   /* SBLTWRN_SEATTYP_RS_NOSN */
        (U4)SBLTWRN_VCLSTS_R_DR_OP, (U4)SBLTWRN_VCLSTS_RB_DR_OP,    /* SBLTWRN_SEATTYP_RS_NOSN */
        (U4)SBLTWRN_VCLSTS_DP_DR_OP,(U4)SBLTWRN_VCLSTS_PRB_DR_OP,   /* SBLTWRN_SEATTYP_RS_NOSN */
        (U4)SBLTWRN_VCLSTS_R_DR_OP, (U4)SBLTWRN_VCLSTS_PRB_DR_OP    /* SBLTWRN_SEATTYP_RS_NOSN */
    };
    U1  u1_t_rrdr;
    U1  u1_t_wkth;
    U1  u1_t_type;
    U4  u4_t_dropn_bit;
    U1  u1_t_dropn;

    u1_t_rrdr = u1_s_SbltwrnCalibU1MaxChk(u1_CALIB_MCUID0233_RDOOR,       (U1)CALIB_MCUID0233_MAX, (U1)CALIB_MCUID0233_DEF);
    u1_t_wkth = u1_s_SbltwrnCalibU1MaxChk(u1_CALIB_MCUID0234_WALKTHROUGH, (U1)CALIB_MCUID0234_MAX, (U1)CALIB_MCUID0234_DEF);
    u1_t_type  = u1_a_ANYDR;
    u1_t_type |= u1_t_rrdr    << 1;
    u1_t_type |= u1_t_wkth    << 2;
    u1_t_type |= u1_a_SEATTYP << 3;
    if(u1_t_type < (U1)((U1)SBLTWRN_NUM_SEATTYP << 3)){
        u4_t_dropn_bit = u4_a_VCLSTS & u4_sp_DROPN_CHK[u1_t_type];
    }
    else{
        u4_t_dropn_bit = (U4)0U;
    }

    if (u4_t_dropn_bit != (U4)0U) {
        u1_t_dropn = (U1)TRUE;
    } else {
        u1_t_dropn = (U1)FALSE;
    }
    return (u1_t_dropn);
}

/*===================================================================================================================================*/
/* U1      u1_g_SbltwrnSeatTyp(const U1 u1_a_SEATID)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_SbltwrnSeatTyp(const U1 u1_a_SEATID)
{
    U1  u1_t_seattyp;
    U1  u1_t_seatfnc;

    u1_t_seatfnc = u1_sp_sbltwrn_stvarcfg[u1_a_SEATID];
    if (u1_t_seatfnc < (U1)SBLTWRN_NUM_SEAT_FUNC) {
        u1_t_seattyp = u1_sp_SBLTWRN_SEATTYP[u1_t_seatfnc];
    } else {
        u1_t_seattyp = (U1)SBLTWRN_SEATTYP_UNDEF;
    }

    return (u1_t_seattyp);
}

/*===================================================================================================================================*/
/* void    vd_g_SbltwrnSeatsts(const U4 u4_a_VCLSTS, const U1 *u1_ap_MSGSTS, U1 *u1_ap_bklsts)                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_SbltwrnSeatsts(const U4 u4_a_VCLSTS, const U1 *u1_ap_MSGSTS, U1 *u1_ap_bklsts)
{
    U4                  u4_t_loop;
    const U1            *u1_tp_STVARCFG;

    u1_tp_STVARCFG = &u1_sp_sbltwrn_stvarcfg[0];
    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)SBLTWRN_NUM_ALLSEAT; u4_t_loop++) {
        if (u1_tp_STVARCFG[u4_t_loop] != (U1)SBLTWRN_SEAT_NOTUSED) {
            u1_ap_bklsts[u4_t_loop] = (*fp_sp_SEATFUNC[u1_tp_STVARCFG[u4_t_loop]])(&u1_ap_MSGSTS[0], u4_t_loop, u4_a_VCLSTS);
        } else {
            u1_ap_bklsts[u4_t_loop] = (U1)SBLTWRN_BKLSTS_BCKL;
        }
    }
}

/*===================================================================================================================================*/
/* void    vd_g_SbltwrnMsgsts(const U1 u1_a_IGON, U1 * u1_ap_msgsts)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_SbltwrnMsgsts(const U1 u1_a_IGON, U1 *u1_ap_msgsts)
{
    U4                                          u4_t_msgindx;
    U1                                          u1_t_csmsgsts;
    U1                                          u1_t_sbltmsgsts;
    const ST_SBLTWRN_MSGCFG                     *stp_t_MSGCOND;

    for (u4_t_msgindx = (U4)0U; u4_t_msgindx < (U4)SBLTWRN_NUM_MSG; u4_t_msgindx++) {
        stp_t_MSGCOND = &st_gp_SBLTWRN_MSGCOND_CFG[u4_t_msgindx];
        u1_t_csmsgsts = u1_g_SbltwrnCanMsgstsCfg(stp_t_MSGCOND->u2_msgid);

        u1_t_sbltmsgsts = (U1)SBLTWRN_UNKNOWN;
        if ((stp_t_MSGCOND->u1_msgcond == (U1)SBLTWRN_MSGCOND_BATT) ||
            ((stp_t_MSGCOND->u1_msgcond == (U1)SBLTWRN_MSGCOND_IGON) && (u1_a_IGON == (U1)TRUE))) {
            u1_t_sbltmsgsts = u1_s_SbltwrnMsgjdg(u1_t_csmsgsts);
        }
        u1_ap_msgsts[u4_t_msgindx] = u1_t_sbltmsgsts;
    }
}

/*===================================================================================================================================*/
/* static  U1      u1_s_SbltwrnMsgjdg(const U1 u1_a_MSGSTS)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_SbltwrnMsgjdg(const U1 u1_a_MSGSTS)
{
    U1          u1_t_msgsts;

    if ((u1_a_MSGSTS & (U1)SBLTWRN_STSBIT_INVALID) != (U1)0U) {
        u1_t_msgsts = (U1)SBLTWRN_INVALID;
    } else if ((u1_a_MSGSTS & (U1)SBLTWRN_STSBIT_UNKNOWN) != (U1)0U) {
        u1_t_msgsts = (U1)SBLTWRN_UNKNOWN;
    } else {
        u1_t_msgsts = (U1)SBLTWRN_VALID;
    }

    return (u1_t_msgsts);
}

/*===================================================================================================================================*/
/* void    vd_g_SbltwrnTmcnt(U2 * u2p_a_timer)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_SbltwrnTmcnt(U2* u2p_a_timer)
{
    if ((*u2p_a_timer) < (U2)U2_MAX) {
        (*u2p_a_timer)++;
    } else {
        (*u2p_a_timer) = (U2)U2_MAX;
    }
}

/*===================================================================================================================================*/
/* void    vd_g_SbltwrnGetCalibSupd(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_SbltwrnGetCalibSupd(void)
{
    u1_sp_sbltwrn_stvarcfg[SBLTWRN_DRV_SEAT] = (U1)SBLTWRN_SEAT_DS;
    u1_sp_sbltwrn_stvarcfg[SBLTWRN_FRC_SEAT] = (U1)SBLTWRN_SEAT_FC;
    u1_sp_sbltwrn_stvarcfg[SBLTWRN_PSG_SEAT] = (U1)SBLTWRN_SEAT_PS;

    vd_s_SbltwrnGetCalibRear1();
    vd_s_SbltwrnGetCalibRear2();
    vd_s_SbltwrnGetCalibRear3();
}

/*===================================================================================================================================*/
/* static  void    vd_s_SbltwrnGetCalibRear1(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_SbltwrnGetCalibRear1(void)
{
    U1          u1_t_rl_seatsw;
    U1          u1_t_rc_seatsw;
    U1          u1_t_rr_seatsw;

    u1_t_rl_seatsw = u1_SEATBELT_CALIB_RL_SEATSW;
    u1_t_rc_seatsw = u1_SEATBELT_CALIB_RC_SEATSW;
    u1_t_rr_seatsw = u1_SEATBELT_CALIB_RR_SEATSW;

    if(u1_t_rl_seatsw == (U1)TRUE){
        u1_sp_sbltwrn_stvarcfg[SBLTWRN_R2L_SEAT] = (U1)SBLTWRN_SEAT_RS_RXBKLPDC_RXOSW;
    }
    else{
        u1_sp_sbltwrn_stvarcfg[SBLTWRN_R2L_SEAT] = (U1)SBLTWRN_SEAT_RS_RXBKLPDC;
    }

    if(u1_t_rc_seatsw == (U1)TRUE){
        u1_sp_sbltwrn_stvarcfg[SBLTWRN_R2C_SEAT] = (U1)SBLTWRN_SEAT_RS_RXBKLPDC_RXOSW;
    }
    else{
        u1_sp_sbltwrn_stvarcfg[SBLTWRN_R2C_SEAT] = (U1)SBLTWRN_SEAT_RS_RXBKLPDC;
    }

    if(u1_t_rr_seatsw == (U1)TRUE){
        u1_sp_sbltwrn_stvarcfg[SBLTWRN_R2R_SEAT] = (U1)SBLTWRN_SEAT_RS_RXBKLPDC_RXOSW;
    }
    else{
        u1_sp_sbltwrn_stvarcfg[SBLTWRN_R2R_SEAT] = (U1)SBLTWRN_SEAT_RS_RXBKLPDC;
    }
}

/*===================================================================================================================================*/
/* static  void    vd_s_SbltwrnGetCalibRear2(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_SbltwrnGetCalibRear2(void)
{
    U1          u1_t_rl2_seatsw;
    U1          u1_t_rc2_seatsw;
    U1          u1_t_rr2_seatsw;

    u1_t_rl2_seatsw = u1_SEATBELT_CALIB_RL2_SEATSW;
    u1_t_rc2_seatsw = u1_SEATBELT_CALIB_RC2_SEATSW;
    u1_t_rr2_seatsw = u1_SEATBELT_CALIB_RR2_SEATSW;

    if(u1_t_rl2_seatsw == (U1)TRUE){
        u1_sp_sbltwrn_stvarcfg[SBLTWRN_R3L_SEAT] = (U1)SBLTWRN_SEAT_RS_XRXBKL_RXXOSW;
    }
    else{
        u1_sp_sbltwrn_stvarcfg[SBLTWRN_R3L_SEAT] = (U1)SBLTWRN_SEAT_RS_XRXBKL;
    }

    if(u1_t_rc2_seatsw == (U1)TRUE){
        u1_sp_sbltwrn_stvarcfg[SBLTWRN_R3C_SEAT] = (U1)SBLTWRN_SEAT_RS_XRXBKL_RXXOSW;
    }
    else{
        u1_sp_sbltwrn_stvarcfg[SBLTWRN_R3C_SEAT] = (U1)SBLTWRN_SEAT_RS_XRXBKL;
    }

    if(u1_t_rr2_seatsw == (U1)TRUE){
        u1_sp_sbltwrn_stvarcfg[SBLTWRN_R3R_SEAT] = (U1)SBLTWRN_SEAT_RS_XRXBKL_RXXOSW;
    }
    else{
        u1_sp_sbltwrn_stvarcfg[SBLTWRN_R3R_SEAT] = (U1)SBLTWRN_SEAT_RS_XRXBKL;
    }
}

/*===================================================================================================================================*/
/* static  void    vd_s_SbltwrnGetCalibRear3(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_SbltwrnGetCalibRear3(void)
{
    U1          u1_t_rl3_seatsw;
    U1          u1_t_rc3_seatsw;
    U1          u1_t_rr3_seatsw;

    u1_t_rl3_seatsw = u1_SEATBELT_CALIB_RL3_SEATSW;
    u1_t_rc3_seatsw = u1_SEATBELT_CALIB_RC3_SEATSW;
    u1_t_rr3_seatsw = u1_SEATBELT_CALIB_RR3_SEATSW;

    if(u1_t_rl3_seatsw == (U1)TRUE){
        u1_sp_sbltwrn_stvarcfg[SBLTWRN_R4L_SEAT] = (U1)SBLTWRN_SEAT_RS_XRXBKL_RXXOSW;
    }
    else{
        u1_sp_sbltwrn_stvarcfg[SBLTWRN_R4L_SEAT] = (U1)SBLTWRN_SEAT_RS_XRXBKL;
    }

    if(u1_t_rc3_seatsw == (U1)TRUE){
        u1_sp_sbltwrn_stvarcfg[SBLTWRN_R4C_SEAT] = (U1)SBLTWRN_SEAT_RS_XRXBKL_RXXOSW;
    }
    else{
        u1_sp_sbltwrn_stvarcfg[SBLTWRN_R4C_SEAT] = (U1)SBLTWRN_SEAT_RS_XRXBKL;
    }

    if(u1_t_rr3_seatsw == (U1)TRUE){
        u1_sp_sbltwrn_stvarcfg[SBLTWRN_R4R_SEAT] = (U1)SBLTWRN_SEAT_RS_XRXBKL_RXXOSW;
    }
    else{
        u1_sp_sbltwrn_stvarcfg[SBLTWRN_R4R_SEAT] = (U1)SBLTWRN_SEAT_RS_XRXBKL;
    }
}

/*===================================================================================================================================*/
/* static  inline  U1  u1_s_SbltwrnCalibU1MaxChk(const U1 u1_a_CALIBID, const U1 u1_a_MAX, const U1 u1_a_DEF)                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  inline  U1  u1_s_SbltwrnCalibU1MaxChk(const U1 u1_a_CALIBID, const U1 u1_a_MAX, const U1 u1_a_DEF)
{
    U1 u1_t_ret;

    u1_t_ret = u1_a_CALIBID;
    if(u1_t_ret > u1_a_MAX){
        u1_t_ret = u1_a_DEF;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  3.0.0    09/02/2025  NA       New.  Legal compliance.(FMVSS208_2025 SBR regulations)                                             */
/*  3.1.0    01/22/2026  NA       Change state transition condition in FMVSS operation (Buzzer BA, Telltale ba)                      */
/*                                                                                                                                   */
/*  * NA     = Nazirul Afham, PXT                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
