/* 2.1.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  HudDimmer Adjudt Duty Config                                                                                                     */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HDIMADJCFG_C_MAJOR               (2)
#define HDIMADJCFG_C_MINOR               (1)
#define HDIMADJCFG_C_PATCH               (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "hdimmgr_cfg_private.h"

#include "oxcan.h"

#include "veh_opemd.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((HDIMADJCFG_C_MAJOR != HDIMADJ_CFG_H_MAJOR) || \
     (HDIMADJCFG_C_MINOR != HDIMADJ_CFG_H_MINOR) || \
     (HDIMADJCFG_C_PATCH != HDIMADJ_CFG_H_PATCH))
#error "hdimmgr_adj_cfg and hdimmgr_adj_cfg_private.h are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/*  Dimming table for conlight sensor.                                       */
/*---------------------------------------------------------------------------*/
#define HDIMADJ_LX_NUM                       (21)

const U1        u1_g_HDIMADJ_DMMNGTBL_X_NUM = (U1)HDIMADJ_LX_NUM;

static const    U4 u4_sp_HDIMADJ_LX[HDIMADJ_LX_NUM] =
{
    (U4)100,        /* Table Lux Index 1 */
    (U4)200,        /* Table Lux Index 2 */
    (U4)300,        /* Table Lux Index 3 */
    (U4)400,        /* Table Lux Index 4 */
    (U4)600,        /* Table Lux Index 5 */
    (U4)1000,       /* Table Lux Index 6 */
    (U4)1500,       /* Table Lux Index 7 */
    (U4)1980,       /* Table Lux Index 8 */
    (U4)2300,       /* Table Lux Index 9 */
    (U4)3200,       /* Table Lux Index 10 */
    (U4)4200,       /* Table Lux Index 11 */
    (U4)5400,       /* Table Lux Index 12 */
    (U4)7000,       /* Table Lux Index 13 */
    (U4)30000,      /* Table Lux Index 14 */
    (U4)130000,     /* Table Lux Index 15 */
    (U4)392200,     /* Table Lux Index 16 */
    (U4)564200,     /* Table Lux Index 17 */
    (U4)811600,     /* Table Lux Index 18 */
    (U4)1167400,    /* Table Lux Index 19 */
    (U4)1679200,    /* Table Lux Index 20 */
    (U4)4600000     /* Table Lux Index 21 */
};

static const U2     u2_sp_HDIMADJ_HEADONDUTY[HDIMSTEP_STEP_NUM][HDIMADJ_LX_NUM] =
{
    {    /* STEP 11 */
        (U2)423,      /* Table Lux Index 1 */
        (U2)515,      /* Table Lux Index 2 */
        (U2)578,      /* Table Lux Index 3 */
        (U2)627,      /* Table Lux Index 4 */
        (U2)704,      /* Table Lux Index 5 */
        (U2)813,      /* Table Lux Index 6 */
        (U2)912,      /* Table Lux Index 7 */
        (U2)987,      /* Table Lux Index 8 */
        (U2)1030,     /* Table Lux Index 9 */
        (U2)1131,     /* Table Lux Index 10 */
        (U2)1221,     /* Table Lux Index 11 */
        (U2)1312,     /* Table Lux Index 12 */
        (U2)1411,     /* Table Lux Index 13 */
        (U2)5652,     /* Table Lux Index 14 */
        (U2)22870,    /* Table Lux Index 15 */
        (U2)65529,    /* Table Lux Index 16 */
        (U2)65535,    /* Table Lux Index 17 */
        (U2)65535,    /* Table Lux Index 18 */
        (U2)65535,    /* Table Lux Index 19 */
        (U2)65535,    /* Table Lux Index 20 */
        (U2)65535     /* Table Lux Index 21 */
    },
    {    /* STEP 10 */
        (U2)299,      /* Table Lux Index 1 */
        (U2)364,      /* Table Lux Index 2 */
        (U2)409,      /* Table Lux Index 3 */
        (U2)444,      /* Table Lux Index 4 */
        (U2)498,      /* Table Lux Index 5 */
        (U2)575,      /* Table Lux Index 6 */
        (U2)645,      /* Table Lux Index 7 */
        (U2)698,      /* Table Lux Index 8 */
        (U2)728,      /* Table Lux Index 9 */
        (U2)800,      /* Table Lux Index 10 */
        (U2)864,      /* Table Lux Index 11 */
        (U2)927,      /* Table Lux Index 12 */
        (U2)998,      /* Table Lux Index 13 */
        (U2)3996,     /* Table Lux Index 14 */
        (U2)16171,    /* Table Lux Index 15 */
        (U2)46336,    /* Table Lux Index 16 */
        (U2)65534,    /* Table Lux Index 17 */
        (U2)65535,    /* Table Lux Index 18 */
        (U2)65535,    /* Table Lux Index 19 */
        (U2)65535,    /* Table Lux Index 20 */
        (U2)65535     /* Table Lux Index 21 */
    },
    {    /* STEP 9 */
        (U2)212,      /* Table Lux Index 1 */
        (U2)258,      /* Table Lux Index 2 */
        (U2)289,      /* Table Lux Index 3 */
        (U2)314,      /* Table Lux Index 4 */
        (U2)352,      /* Table Lux Index 5 */
        (U2)407,      /* Table Lux Index 6 */
        (U2)456,      /* Table Lux Index 7 */
        (U2)493,      /* Table Lux Index 8 */
        (U2)515,      /* Table Lux Index 9 */
        (U2)565,      /* Table Lux Index 10 */
        (U2)611,      /* Table Lux Index 11 */
        (U2)656,      /* Table Lux Index 12 */
        (U2)706,      /* Table Lux Index 13 */
        (U2)2826,     /* Table Lux Index 14 */
        (U2)11435,    /* Table Lux Index 15 */
        (U2)32765,    /* Table Lux Index 16 */
        (U2)46340,    /* Table Lux Index 17 */
        (U2)65535,    /* Table Lux Index 18 */
        (U2)65535,    /* Table Lux Index 19 */
        (U2)65535,    /* Table Lux Index 20 */
        (U2)65535     /* Table Lux Index 21 */
    },
    {    /* STEP 8 */
        (U2)150,      /* Table Lux Index 1 */
        (U2)182,      /* Table Lux Index 2 */
        (U2)204,      /* Table Lux Index 3 */
        (U2)222,      /* Table Lux Index 4 */
        (U2)249,      /* Table Lux Index 5 */
        (U2)288,      /* Table Lux Index 6 */
        (U2)323,      /* Table Lux Index 7 */
        (U2)349,      /* Table Lux Index 8 */
        (U2)364,      /* Table Lux Index 9 */
        (U2)400,      /* Table Lux Index 10 */
        (U2)432,      /* Table Lux Index 11 */
        (U2)464,      /* Table Lux Index 12 */
        (U2)499,      /* Table Lux Index 13 */
        (U2)1998,     /* Table Lux Index 14 */
        (U2)8086,     /* Table Lux Index 15 */
        (U2)23168,    /* Table Lux Index 16 */
        (U2)32767,    /* Table Lux Index 17 */
        (U2)46342,    /* Table Lux Index 18 */
        (U2)65535,    /* Table Lux Index 19 */
        (U2)65535,    /* Table Lux Index 20 */
        (U2)65535     /* Table Lux Index 21 */
    },
    {    /* STEP 7 */
        (U2)106,      /* Table Lux Index 1 */
        (U2)129,      /* Table Lux Index 2 */
        (U2)145,      /* Table Lux Index 3 */
        (U2)157,      /* Table Lux Index 4 */
        (U2)176,      /* Table Lux Index 5 */
        (U2)203,      /* Table Lux Index 6 */
        (U2)228,      /* Table Lux Index 7 */
        (U2)247,      /* Table Lux Index 8 */
        (U2)257,      /* Table Lux Index 9 */
        (U2)283,      /* Table Lux Index 10 */
        (U2)305,      /* Table Lux Index 11 */
        (U2)328,      /* Table Lux Index 12 */
        (U2)353,      /* Table Lux Index 13 */
        (U2)1413,     /* Table Lux Index 14 */
        (U2)5717,     /* Table Lux Index 15 */
        (U2)16382,    /* Table Lux Index 16 */
        (U2)23170,    /* Table Lux Index 17 */
        (U2)32769,    /* Table Lux Index 18 */
        (U2)46341,    /* Table Lux Index 19 */
        (U2)65535,    /* Table Lux Index 20 */
        (U2)65535     /* Table Lux Index 21 */
    },
    {    /* STEP 6 */
        (U2)75,       /* Table Lux Index 1 */
        (U2)91,       /* Table Lux Index 2 */
        (U2)102,      /* Table Lux Index 3 */
        (U2)111,      /* Table Lux Index 4 */
        (U2)124,      /* Table Lux Index 5 */
        (U2)144,      /* Table Lux Index 6 */
        (U2)161,      /* Table Lux Index 7 */
        (U2)174,      /* Table Lux Index 8 */
        (U2)182,      /* Table Lux Index 9 */
        (U2)200,      /* Table Lux Index 10 */
        (U2)216,      /* Table Lux Index 11 */
        (U2)232,      /* Table Lux Index 12 */
        (U2)250,      /* Table Lux Index 13 */
        (U2)999,      /* Table Lux Index 14 */
        (U2)4043,     /* Table Lux Index 15 */
        (U2)11584,    /* Table Lux Index 16 */
        (U2)16384,    /* Table Lux Index 17 */
        (U2)23171,    /* Table Lux Index 18 */
        (U2)32768,    /* Table Lux Index 19 */
        (U2)46340,    /* Table Lux Index 20 */
        (U2)46341     /* Table Lux Index 21 */
    },
    {    /* STEP 5 */
        (U2)53,       /* Table Lux Index 1 */
        (U2)64,       /* Table Lux Index 2 */
        (U2)72,       /* Table Lux Index 3 */
        (U2)78,       /* Table Lux Index 4 */
        (U2)88,       /* Table Lux Index 5 */
        (U2)102,      /* Table Lux Index 6 */
        (U2)114,      /* Table Lux Index 7 */
        (U2)123,      /* Table Lux Index 8 */
        (U2)129,      /* Table Lux Index 9 */
        (U2)141,      /* Table Lux Index 10 */
        (U2)153,      /* Table Lux Index 11 */
        (U2)164,      /* Table Lux Index 12 */
        (U2)176,      /* Table Lux Index 13 */
        (U2)706,      /* Table Lux Index 14 */
        (U2)2859,     /* Table Lux Index 15 */
        (U2)8191,     /* Table Lux Index 16 */
        (U2)11585,    /* Table Lux Index 17 */
        (U2)16384,    /* Table Lux Index 18 */
        (U2)23170,    /* Table Lux Index 19 */
        (U2)32767,    /* Table Lux Index 20 */
        (U2)32768     /* Table Lux Index 21 */
    },
    {    /* STEP 4 */
        (U2)37,       /* Table Lux Index 1 */
        (U2)46,       /* Table Lux Index 2 */
        (U2)51,       /* Table Lux Index 3 */
        (U2)55,       /* Table Lux Index 4 */
        (U2)62,       /* Table Lux Index 5 */
        (U2)72,       /* Table Lux Index 6 */
        (U2)81,       /* Table Lux Index 7 */
        (U2)87,       /* Table Lux Index 8 */
        (U2)91,       /* Table Lux Index 9 */
        (U2)100,      /* Table Lux Index 10 */
        (U2)108,      /* Table Lux Index 11 */
        (U2)116,      /* Table Lux Index 12 */
        (U2)125,      /* Table Lux Index 13 */
        (U2)500,      /* Table Lux Index 14 */
        (U2)2021,     /* Table Lux Index 15 */
        (U2)5792,     /* Table Lux Index 16 */
        (U2)8192,     /* Table Lux Index 17 */
        (U2)11585,    /* Table Lux Index 18 */
        (U2)16384,    /* Table Lux Index 19 */
        (U2)23170,    /* Table Lux Index 20 */
        (U2)23170     /* Table Lux Index 21 */
    },
    {    /* STEP 3 */
        (U2)26,       /* Table Lux Index 1 */
        (U2)32,       /* Table Lux Index 2 */
        (U2)36,       /* Table Lux Index 3 */
        (U2)39,       /* Table Lux Index 4 */
        (U2)44,       /* Table Lux Index 5 */
        (U2)51,       /* Table Lux Index 6 */
        (U2)57,       /* Table Lux Index 7 */
        (U2)62,       /* Table Lux Index 8 */
        (U2)64,       /* Table Lux Index 9 */
        (U2)71,       /* Table Lux Index 10 */
        (U2)76,       /* Table Lux Index 11 */
        (U2)82,       /* Table Lux Index 12 */
        (U2)88,       /* Table Lux Index 13 */
        (U2)353,      /* Table Lux Index 14 */
        (U2)1429,     /* Table Lux Index 15 */
        (U2)4096,     /* Table Lux Index 16 */
        (U2)5792,     /* Table Lux Index 17 */
        (U2)8192,     /* Table Lux Index 18 */
        (U2)11585,    /* Table Lux Index 19 */
        (U2)16384,    /* Table Lux Index 20 */
        (U2)16384     /* Table Lux Index 21 */
    },
    {    /* STEP 2 */
        (U2)19,       /* Table Lux Index 1 */
        (U2)23,       /* Table Lux Index 2 */
        (U2)26,       /* Table Lux Index 3 */
        (U2)28,       /* Table Lux Index 4 */
        (U2)31,       /* Table Lux Index 5 */
        (U2)36,       /* Table Lux Index 6 */
        (U2)40,       /* Table Lux Index 7 */
        (U2)44,       /* Table Lux Index 8 */
        (U2)46,       /* Table Lux Index 9 */
        (U2)50,       /* Table Lux Index 10 */
        (U2)54,       /* Table Lux Index 11 */
        (U2)58,       /* Table Lux Index 12 */
        (U2)62,       /* Table Lux Index 13 */
        (U2)250,      /* Table Lux Index 14 */
        (U2)1011,     /* Table Lux Index 15 */
        (U2)2896,     /* Table Lux Index 16 */
        (U2)4096,     /* Table Lux Index 17 */
        (U2)5793,     /* Table Lux Index 18 */
        (U2)8192,     /* Table Lux Index 19 */
        (U2)11585,    /* Table Lux Index 20 */
        (U2)11585     /* Table Lux Index 21 */
    },
    {    /* STEP 1 */
        (U2)13,       /* Table Lux Index 1 */
        (U2)16,       /* Table Lux Index 2 */
        (U2)18,       /* Table Lux Index 3 */
        (U2)20,       /* Table Lux Index 4 */
        (U2)22,       /* Table Lux Index 5 */
        (U2)25,       /* Table Lux Index 6 */
        (U2)29,       /* Table Lux Index 7 */
        (U2)31,       /* Table Lux Index 8 */
        (U2)32,       /* Table Lux Index 9 */
        (U2)35,       /* Table Lux Index 10 */
        (U2)38,       /* Table Lux Index 11 */
        (U2)41,       /* Table Lux Index 12 */
        (U2)44,       /* Table Lux Index 13 */
        (U2)177,      /* Table Lux Index 14 */
        (U2)715,      /* Table Lux Index 15 */
        (U2)2048,     /* Table Lux Index 16 */
        (U2)2896,     /* Table Lux Index 17 */
        (U2)4096,     /* Table Lux Index 18 */
        (U2)5793,     /* Table Lux Index 19 */
        (U2)8192,     /* Table Lux Index 20 */
        (U2)8192      /* Table Lux Index 21 */
    }
};

static const U2     u2_sp_HDIMADJ_HEADOFFDUTY[HDIMSTEP_STEP_NUM][HDIMADJ_LX_NUM] =
{
    {    /* STEP 11 */
        (U2)423,      /* Table Lux Index 1 */
        (U2)423,      /* Table Lux Index 2 */
        (U2)423,      /* Table Lux Index 3 */
        (U2)423,      /* Table Lux Index 4 */
        (U2)423,      /* Table Lux Index 5 */
        (U2)423,      /* Table Lux Index 6 */
        (U2)423,      /* Table Lux Index 7 */
        (U2)423,      /* Table Lux Index 8 */
        (U2)489,      /* Table Lux Index 9 */
        (U2)669,      /* Table Lux Index 10 */
        (U2)867,      /* Table Lux Index 11 */
        (U2)1102,     /* Table Lux Index 12 */
        (U2)1411,     /* Table Lux Index 13 */
        (U2)5652,     /* Table Lux Index 14 */
        (U2)22870,    /* Table Lux Index 15 */
        (U2)65529,    /* Table Lux Index 16 */
        (U2)65535,    /* Table Lux Index 17 */
        (U2)65535,    /* Table Lux Index 18 */
        (U2)65535,    /* Table Lux Index 19 */
        (U2)65535,    /* Table Lux Index 20 */
        (U2)65535     /* Table Lux Index 21 */
    },
    {    /* STEP 10 */
        (U2)299,      /* Table Lux Index 1 */
        (U2)299,      /* Table Lux Index 2 */
        (U2)299,      /* Table Lux Index 3 */
        (U2)299,      /* Table Lux Index 4 */
        (U2)299,      /* Table Lux Index 5 */
        (U2)299,      /* Table Lux Index 6 */
        (U2)299,      /* Table Lux Index 7 */
        (U2)299,      /* Table Lux Index 8 */
        (U2)345,      /* Table Lux Index 9 */
        (U2)473,      /* Table Lux Index 10 */
        (U2)613,      /* Table Lux Index 11 */
        (U2)779,      /* Table Lux Index 12 */
        (U2)998,      /* Table Lux Index 13 */
        (U2)3996,     /* Table Lux Index 14 */
        (U2)16171,    /* Table Lux Index 15 */
        (U2)46336,    /* Table Lux Index 16 */
        (U2)65534,    /* Table Lux Index 17 */
        (U2)65535,    /* Table Lux Index 18 */
        (U2)65535,    /* Table Lux Index 19 */
        (U2)65535,    /* Table Lux Index 20 */
        (U2)65535     /* Table Lux Index 21 */
    },
    {    /* STEP 9 */
        (U2)212,      /* Table Lux Index 1 */
        (U2)212,      /* Table Lux Index 2 */
        (U2)212,      /* Table Lux Index 3 */
        (U2)212,      /* Table Lux Index 4 */
        (U2)212,      /* Table Lux Index 5 */
        (U2)212,      /* Table Lux Index 6 */
        (U2)212,      /* Table Lux Index 7 */
        (U2)212,      /* Table Lux Index 8 */
        (U2)244,      /* Table Lux Index 9 */
        (U2)335,      /* Table Lux Index 10 */
        (U2)434,      /* Table Lux Index 11 */
        (U2)551,      /* Table Lux Index 12 */
        (U2)706,      /* Table Lux Index 13 */
        (U2)2826,     /* Table Lux Index 14 */
        (U2)11435,    /* Table Lux Index 15 */
        (U2)32765,    /* Table Lux Index 16 */
        (U2)46340,    /* Table Lux Index 17 */
        (U2)65535,    /* Table Lux Index 18 */
        (U2)65535,    /* Table Lux Index 19 */
        (U2)65535,    /* Table Lux Index 20 */
        (U2)65535     /* Table Lux Index 21 */
    },
    {    /* STEP 8 */
        (U2)150,      /* Table Lux Index 1 */
        (U2)150,      /* Table Lux Index 2 */
        (U2)150,      /* Table Lux Index 3 */
        (U2)150,      /* Table Lux Index 4 */
        (U2)150,      /* Table Lux Index 5 */
        (U2)150,      /* Table Lux Index 6 */
        (U2)150,      /* Table Lux Index 7 */
        (U2)150,      /* Table Lux Index 8 */
        (U2)173,      /* Table Lux Index 9 */
        (U2)237,      /* Table Lux Index 10 */
        (U2)307,      /* Table Lux Index 11 */
        (U2)390,      /* Table Lux Index 12 */
        (U2)499,      /* Table Lux Index 13 */
        (U2)1998,     /* Table Lux Index 14 */
        (U2)8086,     /* Table Lux Index 15 */
        (U2)23168,    /* Table Lux Index 16 */
        (U2)32767,    /* Table Lux Index 17 */
        (U2)46342,    /* Table Lux Index 18 */
        (U2)65535,    /* Table Lux Index 19 */
        (U2)65535,    /* Table Lux Index 20 */
        (U2)65535     /* Table Lux Index 21 */
    },
    {    /* STEP 7 */
        (U2)106,      /* Table Lux Index 1 */
        (U2)106,      /* Table Lux Index 2 */
        (U2)106,      /* Table Lux Index 3 */
        (U2)106,      /* Table Lux Index 4 */
        (U2)106,      /* Table Lux Index 5 */
        (U2)106,      /* Table Lux Index 6 */
        (U2)106,      /* Table Lux Index 7 */
        (U2)106,      /* Table Lux Index 8 */
        (U2)122,      /* Table Lux Index 9 */
        (U2)167,      /* Table Lux Index 10 */
        (U2)217,      /* Table Lux Index 11 */
        (U2)276,      /* Table Lux Index 12 */
        (U2)353,      /* Table Lux Index 13 */
        (U2)1413,     /* Table Lux Index 14 */
        (U2)5717,     /* Table Lux Index 15 */
        (U2)16382,    /* Table Lux Index 16 */
        (U2)23170,    /* Table Lux Index 17 */
        (U2)32769,    /* Table Lux Index 18 */
        (U2)46341,    /* Table Lux Index 19 */
        (U2)65535,    /* Table Lux Index 20 */
        (U2)65535     /* Table Lux Index 21 */
    },
    {    /* STEP 6 */
        (U2)75,       /* Table Lux Index 1 */
        (U2)75,       /* Table Lux Index 2 */
        (U2)75,       /* Table Lux Index 3 */
        (U2)75,       /* Table Lux Index 4 */
        (U2)75,       /* Table Lux Index 5 */
        (U2)75,       /* Table Lux Index 6 */
        (U2)75,       /* Table Lux Index 7 */
        (U2)75,       /* Table Lux Index 8 */
        (U2)86,       /* Table Lux Index 9 */
        (U2)118,      /* Table Lux Index 10 */
        (U2)153,      /* Table Lux Index 11 */
        (U2)195,      /* Table Lux Index 12 */
        (U2)250,      /* Table Lux Index 13 */
        (U2)999,      /* Table Lux Index 14 */
        (U2)4043,     /* Table Lux Index 15 */
        (U2)11584,    /* Table Lux Index 16 */
        (U2)16384,    /* Table Lux Index 17 */
        (U2)23171,    /* Table Lux Index 18 */
        (U2)32768,    /* Table Lux Index 19 */
        (U2)46340,    /* Table Lux Index 20 */
        (U2)46341     /* Table Lux Index 21 */
    },
    {    /* STEP 5 */
        (U2)53,       /* Table Lux Index 1 */
        (U2)53,       /* Table Lux Index 2 */
        (U2)53,       /* Table Lux Index 3 */
        (U2)53,       /* Table Lux Index 4 */
        (U2)53,       /* Table Lux Index 5 */
        (U2)53,       /* Table Lux Index 6 */
        (U2)53,       /* Table Lux Index 7 */
        (U2)53,       /* Table Lux Index 8 */
        (U2)61,       /* Table Lux Index 9 */
        (U2)84,       /* Table Lux Index 10 */
        (U2)108,      /* Table Lux Index 11 */
        (U2)138,      /* Table Lux Index 12 */
        (U2)176,      /* Table Lux Index 13 */
        (U2)706,      /* Table Lux Index 14 */
        (U2)2859,     /* Table Lux Index 15 */
        (U2)8191,     /* Table Lux Index 16 */
        (U2)11585,    /* Table Lux Index 17 */
        (U2)16384,    /* Table Lux Index 18 */
        (U2)23170,    /* Table Lux Index 19 */
        (U2)32767,    /* Table Lux Index 20 */
        (U2)32768     /* Table Lux Index 21 */
    },
    {    /* STEP 4 */
        (U2)37,       /* Table Lux Index 1 */
        (U2)37,       /* Table Lux Index 2 */
        (U2)37,       /* Table Lux Index 3 */
        (U2)37,       /* Table Lux Index 4 */
        (U2)37,       /* Table Lux Index 5 */
        (U2)37,       /* Table Lux Index 6 */
        (U2)37,       /* Table Lux Index 7 */
        (U2)37,       /* Table Lux Index 8 */
        (U2)43,       /* Table Lux Index 9 */
        (U2)59,       /* Table Lux Index 10 */
        (U2)77,       /* Table Lux Index 11 */
        (U2)97,       /* Table Lux Index 12 */
        (U2)125,      /* Table Lux Index 13 */
        (U2)500,      /* Table Lux Index 14 */
        (U2)2021,     /* Table Lux Index 15 */
        (U2)5792,     /* Table Lux Index 16 */
        (U2)8192,     /* Table Lux Index 17 */
        (U2)11585,    /* Table Lux Index 18 */
        (U2)16384,    /* Table Lux Index 19 */
        (U2)23170,    /* Table Lux Index 20 */
        (U2)23170     /* Table Lux Index 21 */
    },
    {    /* STEP 3 */
        (U2)26,       /* Table Lux Index 1 */
        (U2)26,       /* Table Lux Index 2 */
        (U2)26,       /* Table Lux Index 3 */
        (U2)26,       /* Table Lux Index 4 */
        (U2)26,       /* Table Lux Index 5 */
        (U2)26,       /* Table Lux Index 6 */
        (U2)26,       /* Table Lux Index 7 */
        (U2)26,       /* Table Lux Index 8 */
        (U2)31,       /* Table Lux Index 9 */
        (U2)42,       /* Table Lux Index 10 */
        (U2)54,       /* Table Lux Index 11 */
        (U2)69,       /* Table Lux Index 12 */
        (U2)88,       /* Table Lux Index 13 */
        (U2)353,      /* Table Lux Index 14 */
        (U2)1429,     /* Table Lux Index 15 */
        (U2)4096,     /* Table Lux Index 16 */
        (U2)5792,     /* Table Lux Index 17 */
        (U2)8192,     /* Table Lux Index 18 */
        (U2)11585,    /* Table Lux Index 19 */
        (U2)16384,    /* Table Lux Index 20 */
        (U2)16384     /* Table Lux Index 21 */
    },
    {    /* STEP 2 */
        (U2)19,       /* Table Lux Index 1 */
        (U2)19,       /* Table Lux Index 2 */
        (U2)19,       /* Table Lux Index 3 */
        (U2)19,       /* Table Lux Index 4 */
        (U2)19,       /* Table Lux Index 5 */
        (U2)19,       /* Table Lux Index 6 */
        (U2)19,       /* Table Lux Index 7 */
        (U2)19,       /* Table Lux Index 8 */
        (U2)22,       /* Table Lux Index 9 */
        (U2)30,       /* Table Lux Index 10 */
        (U2)38,       /* Table Lux Index 11 */
        (U2)49,       /* Table Lux Index 12 */
        (U2)62,       /* Table Lux Index 13 */
        (U2)250,      /* Table Lux Index 14 */
        (U2)1011,     /* Table Lux Index 15 */
        (U2)2896,     /* Table Lux Index 16 */
        (U2)4096,     /* Table Lux Index 17 */
        (U2)5793,     /* Table Lux Index 18 */
        (U2)8192,     /* Table Lux Index 19 */
        (U2)11585,    /* Table Lux Index 20 */
        (U2)11585     /* Table Lux Index 21 */
    },
    {    /* STEP 1 */
        (U2)13,       /* Table Lux Index 1 */
        (U2)13,       /* Table Lux Index 2 */
        (U2)13,       /* Table Lux Index 3 */
        (U2)13,       /* Table Lux Index 4 */
        (U2)13,       /* Table Lux Index 5 */
        (U2)13,       /* Table Lux Index 6 */
        (U2)13,       /* Table Lux Index 7 */
        (U2)13,       /* Table Lux Index 8 */
        (U2)15,       /* Table Lux Index 9 */
        (U2)21,       /* Table Lux Index 10 */
        (U2)27,       /* Table Lux Index 11 */
        (U2)34,       /* Table Lux Index 12 */
        (U2)44,       /* Table Lux Index 13 */
        (U2)177,      /* Table Lux Index 14 */
        (U2)715,      /* Table Lux Index 15 */
        (U2)2048,     /* Table Lux Index 16 */
        (U2)2896,     /* Table Lux Index 17 */
        (U2)4096,     /* Table Lux Index 18 */
        (U2)5793,     /* Table Lux Index 19 */
        (U2)8192,     /* Table Lux Index 20 */
        (U2)8192      /* Table Lux Index 21 */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void vd_g_HdimadjCfgInit(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/* Arguments    -                                                                                                                    */
/* Return       -                                                                                                                    */
/*===================================================================================================================================*/
void vd_g_HdimadjCfgInit(void)
{
    if(u1_CALIB_MCUID0583_ATSSAORNA != (U1)HDIMADJ_FRILL_NOTSUP){
        vd_g_HdimadjFrillInit();
    }
}

/*===================================================================================================================================*/
/*  HudDimmer Adjust Duty Action Update                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments     : -->  u1_ap_illmnsts  : Illuminance Status                                                                        */
/*                : -->  u4_ap_situat    : Situation Information                                                                     */
/*                : -->  u4_ap_step      : Step Information                                                                          */
/*                : -->  u4_ap_illmn     : Illuminance Information                                                                   */
/*  Return        : <-- u1_t_act : Target Duty Caluculation Action                                                                   */
/*===================================================================================================================================*/
U1 u1_g_HdimadjCfgActUpdt(U1 * u1_ap_illmnsts, U4 * u4_ap_situat , U4 * u4_ap_step , U4 * u4_ap_illmn)
{
    U1  u1_t_situat_sts;
    U1  u1_t_step_sts;
    U1  u1_t_illmn_sts;

    U1  u1_t_act;

    u1_t_illmn_sts = u1_g_HdimillmnGetIllmnVal(u4_ap_illmn);
    (*u1_ap_illmnsts) = u1_t_illmn_sts;
    if((u1_t_illmn_sts == (U1)HDIMMGR_INSTS_UNDET) ||
       (u1_t_illmn_sts == (U1)HDIMMGR_INSTS_ERR)){
        u1_t_act = (U1)HDIMADJ_ACTTYPE_ADJDUTY_DEF;
    }
    else if(u1_t_illmn_sts == (U1)HDIMMGR_INSTS_NML){
        u1_t_act = (U1)HDIMADJ_ACTTYPE_ADJDUTY_CAL;
    }
    else{
        u1_t_act = (U1)HDIMADJ_ACTTYPE_ADJDUTY_BLK;
    }

    u1_t_step_sts = u1_g_HdimstepGetStepVal(u4_ap_step);
    if((u1_t_step_sts == (U1)HDIMMGR_INSTS_UNDET) ||
       (u1_t_step_sts == (U1)HDIMMGR_INSTS_NML) ||
       (u1_t_step_sts == (U1)HDIMMGR_INSTS_ERR)){
        u1_t_act |= (U1)HDIMADJ_ACTTYPE_ADJDUTY_CAL;
    }
    else{
        u1_t_act |= (U1)HDIMADJ_ACTTYPE_ADJDUTY_BLK;
    }

    u1_t_situat_sts = u1_g_HdimsituatGetSituatVal(u4_ap_situat);
    if((u1_t_situat_sts == (U1)HDIMMGR_INSTS_UNDET) ||
       (u1_t_situat_sts == (U1)HDIMMGR_INSTS_NML) ||
       (u1_t_situat_sts == (U1)HDIMMGR_INSTS_ERR)){
        u1_t_act |= (U1)HDIMADJ_ACTTYPE_ADJDUTY_CAL;
    }
    else{
        u1_t_act |= (U1)HDIMADJ_ACTTYPE_ADJDUTY_BLK;
    }

    return (u1_t_act);
}

/*===================================================================================================================================*/
/*  Illuminance Rapid Change Judgment                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments     : -->  u4_a_ILLMN     : Latest Illuminance                                                                         */
/*                : -->  u4_a_PASTILLMN : Past Illuminance                                                                           */
/*  Return        : <--  u1_t_jdg  : Rapid Change Judgment(FALSE:Rapid Change None,TRUE:Rapid Change)                                */
/*===================================================================================================================================*/
U1      u1_g_HdimadjCfgJdgRpdChg(const U4 u4_a_ILLMN, const U4 u4_a_PASTILLMN)
{
    static const U4 u4_s_HDIMADJ_RPDCHG_OV  = (U4)2000 * (U4)HDIMILLMN_LXLSB;   /* Illuminance Rapid Change Judgment Value(for Brighter)     */
    static const U4 u4_s_HDIMADJ_RPDCHG_UN  = (U4)0x7fffffff;                   /* Illuminance Rapid Change Judgment Value(for Darker)       */
    static const U4 u4_s_HDIMADJ_RPDCHG_MAX = (U4)0x7fffffff;                   /* Illuminance Rapid Change Judgment Max Value:Don't Change! */

    U4          u4_t_escp_rpgchg;
    U4          u4_t_diff_illmn;
    U1          u1_t_jdg;

    if(u4_a_ILLMN > u4_a_PASTILLMN){
        u4_t_diff_illmn = u4_a_ILLMN - u4_a_PASTILLMN;                          /* PRQA S 3383 # over detection */
        u4_t_escp_rpgchg = u4_s_HDIMADJ_RPDCHG_OV;
    }
    else{
        u4_t_diff_illmn = u4_a_PASTILLMN - u4_a_ILLMN;
        u4_t_escp_rpgchg = u4_s_HDIMADJ_RPDCHG_UN;
    }

    if(u4_t_escp_rpgchg >= u4_s_HDIMADJ_RPDCHG_MAX){
        u1_t_jdg = (U1)FALSE;
    }
    else if(u4_t_diff_illmn >= u4_t_escp_rpgchg){
        u1_t_jdg = (U1)TRUE;
    }
    else{
        u1_t_jdg = (U1)FALSE;
    }

    return (u1_t_jdg);
}

/*===================================================================================================================================*/
/*  U1      (void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/* Arguments    -                                                                                                                    */
/* Return       -                                                                                                                    */
/*===================================================================================================================================*/
U1      u1_g_HdimadjCfgInMvaveNum(const U1 u1_a_ISDK2BR)
{
    U1      u1_t_num;

    if(u1_a_ISDK2BR == (U1)TRUE){
        u1_t_num = u1_CALIB_MCUID0581_ACONUPAVECNT;
    }
    else{
        u1_t_num = u1_CALIB_MCUID0582_ACONDNAVECNT;
    }
    return(u1_t_num);
}

/*===================================================================================================================================*/
/*  const Ux *  ux_gp_HdimadjCfgDmmngTbl_*(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/* Arguments    -                                                                                                                    */
/* Return       -                                                                                                                    */
/*===================================================================================================================================*/
const U4 *  u4_gp_HdimadjCfgDmmngTbl_X(void)
{
    return(&u4_sp_HDIMADJ_LX[0]);
}

const U2 *  u2_gp_HdimadjCfgDmmngTbl_Y(const U4 u4_a_SITUAT, const U4 u4_a_STEP)
{
    const U2*   u2_tp_tbl;

    u2_tp_tbl = vdp_PTR_NA;
    if(u4_a_STEP < (U4)HDIMSTEP_STEP_NUM){
        if(u4_a_SITUAT == (U4)HDIMSITUAT_HEAD_ON){
            u2_tp_tbl = &u2_sp_HDIMADJ_HEADONDUTY[u4_a_STEP][0];
        }
        else{
            u2_tp_tbl = &u2_sp_HDIMADJ_HEADOFFDUTY[u4_a_STEP][0];
        }
    }
    return(u2_tp_tbl);
}

/*===================================================================================================================================*/
/*  U2      u2_g_HdimadjCfgDtctTgtDuty(const U2 u2_a_TGTDUTY)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/* Arguments    -                                                                                                                    */
/* Return       -                                                                                                                    */
/*===================================================================================================================================*/
U2      u2_g_HdimadjCfgDtctTgtDuty(const U2 u2_a_TGTDUTY)
{
    U2      u2_t_tgtduty;
    U2      u2_t_tgtduty_frill;
    U1      u1_t_frill_valid;

    u2_t_tgtduty       = u2_a_TGTDUTY;
    if(u1_CALIB_MCUID0583_ATSSAORNA != (U1)HDIMADJ_FRILL_NOTSUP){
        u2_t_tgtduty_frill = (U2)HDIMADJ_DUTY_0PER;
        u1_t_frill_valid = u1_g_HdimadjFrilldutyUpdt(&u2_t_tgtduty_frill);
        if(u1_t_frill_valid == (U1)TRUE){
            u2_t_tgtduty = u2_t_tgtduty_frill;
        }
    }
    return(u2_t_tgtduty);
}

/*===================================================================================================================================*/
/*  U1      u1_g_HdimadjCfgAdjMvaveNum(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/* Arguments    -                                                                                                                    */
/* Return       -                                                                                                                    */
/*===================================================================================================================================*/
U1      u1_g_HdimadjCfgAdjMvaveNum(void)
{
    static const U1 u1_s_HDIMADJ_OUTMVAVE_NRMNUM = (U1) 8U;          /* Duty Average Times : Normal */
    static const U2 u2_s_HDIMADJ_STOPJDG_SPDKMH  = (U2)175U;         /* Speed value(LSB:0.01km/h) */

    U2      u2_t_spd;
    U1      u1_t_ig;
    U1      u1_t_msgsts;
    U1      u1_t_div;

    u2_t_spd = (U2)0U;
    u1_t_ig = u1_g_VehopemdIgnOn();

    if(u1_CALIB_MCUID0583_ATSSAORNA != (U1)HDIMADJ_FRILL_NOTSUP){
        if(u1_t_ig == (U1)TRUE){
            u1_t_msgsts = Com_GetIPDUStatus((PduIdType)MSG_VSC1G13_RXCH0);
            u1_t_msgsts &= (U1)(COM_TIMEOUT | COM_NO_RX);
            if(u1_t_msgsts == (U1)0U){
                (void)Com_ReceiveSignal(ComConf_ComSignal_SP1, &u2_t_spd);
            }
        }

        u1_t_div = u1_s_HDIMADJ_OUTMVAVE_NRMNUM;
        if(u2_t_spd <= u2_s_HDIMADJ_STOPJDG_SPDKMH){
            u1_t_div = u1_CALIB_MCUID0586_HUDLMAVECNT;
        }
    }
    else{
        u1_t_div = u1_s_HDIMADJ_OUTMVAVE_NRMNUM;
    }
    return(u1_t_div);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version          Date        Author  Change Description                                                                          */
/* ---------------   ----------  ------  ------------------------------------------------------------------------------------------- */
/* 1.0.0             2016.03.31  HS      New                                                                                         */
/* 1.0.1             2016.07.22  HS      HudDimmer Adjust Duty Action was revised.                                                   */
/*                                       Illuminance Rapid Change Judgment was revised.                                              */
/* 2.0.0             2020.02.27  MaO     Added LSB configuration.                                                                    */
/* 2.1.0             2023.09.27  AA      Applied calibration implementation                                                          */
/* 2.2.1             2024.07.02  His     Delete Calibration Guard Process.                                                           */
/*                                                                                                                                   */
/*  * HS = Hidenobu Suzuki, NCOS                                                                                                     */
/*  * HiS = Hidenobu Suzuki, MSE                                                                                                     */
/*  * MaO = Masayuki Okada, DENSO                                                                                                    */
/*  * AA = Anna Asuncion, DT                                                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/
