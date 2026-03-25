/* 3.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Vardef / Destination                                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef VARDEF_DEST_DBF_H
#define VARDEF_DEST_DBF_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VARDEF_DEST_DBF_H_MAJOR             (3)
#define VARDEF_DEST_DBF_H_MINOR             (0)
#define VARDEF_DEST_DBF_H_PATCH             (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
#define VDF_DEST_LAW_DBF_NBYTE          (15U)
#define VDF_DEST_LAW_DBF_DEFUNIT_SPD    (0U)
#define VDF_DEST_LAW_DBF_DEFUNIT_DST    (1U)
#define VDF_DEST_LAW_DBF_DEFUNIT_ELECO  (2U)
#define VDF_DEST_LAW_DBF_UNITSLCT_DEST  (3U)
#define VDF_DEST_LAW_DBF_BZ_SBW_SUP     (4U)
#define VDF_DEST_LAW_DBF_MDLEST_WRN     (5U)
#define VDF_DEST_LAW_DBF_INDIASPDBZR    (6U)
#define VDF_DEST_LAW_DBF_SEATBLT_CONST  (7U)
#define VDF_DEST_LAW_DBF_SUBDIGSPD      (8U)
#define VDF_DEST_LAW_DBF_SPDTLRNC       (9U)
#define VDF_DEST_LAW_DBF_CHAINAREQ      (10U)
#define VDF_DEST_LAW_DBF_TTBRAKE        (11U)
#define VDF_DEST_LAW_DBF_TTABS          (12U)
#define VDF_DEST_LAW_DBF_TTEPBPKB       (13U)
#define VDF_DEST_LAW_DBF_TTTAILHEAD     (14U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDF_DEST_DBF_NBYTE              (4U)
#define VDF_DEST_DBF_DESTINATION        (0U)
#define VDF_DEST_DBF_TIMEFMT            (1U)
#define VDF_DEST_DBF_TTTRCOFF           (2U)
#define VDF_DEST_DBF_AMBTMP             (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDF_NUM_DEST                    (15U)
#define VDF_DEST_CAN                    (0U)
#define VDF_DEST_USA                    (1U)
#define VDF_DEST_MEX                    (2U)
#define VDF_DEST_GEN                    (3U)
#define VDF_DEST_UK                     (4U)
#define VDF_DEST_EU                     (5U)
#define VDF_DEST_ZAF                    (6U)
#define VDF_DEST_MDLEST                 (7U)
#define VDF_DEST_JPN                    (8U)
#define VDF_DEST_IND                    (9U)
#define VDF_DEST_KOR                    (10U)
#define VDF_DEST_TWN                    (11U)
#define VDF_DEST_CHN                    (12U)
#define VDF_DEST_HKGMACSGP              (13U)
#define VDF_DEST_AUST                   (14U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDF_NUM_UNIT_TYPE_DEST          (4U)
#define VDF_UNIT_TYPE_NA                (0U)
#define VDF_UNIT_TYPE_JPN               (1U)
#define VDF_UNIT_TYPE_EU                (2U)
#define VDF_UNIT_TYPE_UK                (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDF_NUM_TTTRCOFF                (2U)
#define VDF_TTTRCOFF_NO8                (0U)
#define VDF_TTTRCOFF_NO155              (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDF_NUM_BZ_SBW_SUP              (2U)
#define VDF_BZ_SBW_NON                  (0U)
#define VDF_BZ_SBW_WITH                 (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDF_NUM_INDSDBZR                (2U)
#define VDF_INDSDBZR_NON                (0U)
#define VDF_INDSDBZR_WITH               (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDF_NUM_SEATBLT_CONST           (6U)
#define VDF_SEATBLT_MCUID1135           (0U)
#define VDF_SEATBLT_MCUID1136           (1U)
#define VDF_SEATBLT_MCUID0604           (2U)
#define VDF_SEATBLT_MCUID0605           (3U)
#define VDF_SEATBLT_MCUID0606           (4U)
#define VDF_SEATBLT_MCUID0607           (5U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDF_NUM_SUBDIGSPD               (4U)
#define VDF_SUBDIGSPD_NON               (0U)
#define VDF_SUBDIGSPD_KMPH              (1U)
#define VDF_SUBDIGSPD_MPH               (2U)
#define VDF_SUBDIGSPD_BOTH              (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDF_NUM_SPDTLRNC                (2U)
#define VDF_SPDTLRNC_USA_CAN            (0U)
#define VDF_SPDTLRNC_UNR_AUS            (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDF_NUM_TTBRAKE                 (2U)
#define VDF_TTBRAKE_NO3                 (0U)
#define VDF_TTBRAKE_NO4                 (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDF_NUM_TTABS                   (2U)
#define VDF_TTABS_NO6                   (0U)
#define VDF_TTABS_NO7                   (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDF_NUM_TTEPBPKB                (2U)
#define VDF_TTEPBPKB_NO9                (0U)
#define VDF_TTEPBPKB_NO10               (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDF_NUM_TTTAILHEAD              (2U)
#define VDF_TTTAILHEAD_NO11             (0U)
#define VDF_TTTAILHEAD_NO12             (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDF_NUM_SEATBLT_DEST            (3U)
#define VDF_SEATBLT_DEST_USA            (0U)
#define VDF_SEATBLT_DEST_EU             (1U)
#define VDF_SEATBLT_DEST_CHN            (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u1_g_VardefDestinationByPid()                  (u1_g_VardefDestDbfByPid((U1)VDF_DEST_DBF_DESTINATION))
#define u1_g_VardefUnitSlctDstByPid()                  (u1_g_VardefDestLawDbfByPid((U1)VDF_DEST_LAW_DBF_UNITSLCT_DEST))
#define u1_g_VardefDefTmFmtByPid()                     (u1_g_VardefDestDbfByPid((U1)VDF_DEST_DBF_TIMEFMT))
#define u1_g_VardefTtTrcoff()                          (u1_g_VardefDestDbfByPid((U1)VDF_DEST_DBF_TTTRCOFF))
#define u1_g_VardefBzSbwDiagSupByPid()                 (u1_g_VardefDestLawDbfByPid((U1)VDF_DEST_LAW_DBF_BZ_SBW_SUP))
#define u1_g_VardefMdlLEstWrnByPid()                   (u1_g_VardefDestLawDbfByPid((U1)VDF_DEST_LAW_DBF_MDLEST_WRN))
#define u1_g_VardefBltDstByPid()                       (u1_g_VardefCfgBltDst())
#define u1_g_VardefSubDigSpdByPid()                    (u1_g_VardefDestLawDbfByPid((U1)VDF_DEST_LAW_DBF_SUBDIGSPD))
#define u1_g_VardefSpdTlrncByPid()                     (u1_g_VardefDestLawDbfByPid((U1)VDF_DEST_LAW_DBF_SPDTLRNC))
#define u1_g_VardefChainaReq()                         (u1_g_VardefDestLawDbfByPid((U1)VDF_DEST_LAW_DBF_CHAINAREQ))
#define u1_g_VardefTtBrake()                           (u1_g_VardefDestLawDbfByPid((U1)VDF_DEST_LAW_DBF_TTBRAKE))
#define u1_g_VardefTtAbs()                             (u1_g_VardefDestLawDbfByPid((U1)VDF_DEST_LAW_DBF_TTABS))
#define u1_g_VardefTtEpbPkb()                          (u1_g_VardefDestLawDbfByPid((U1)VDF_DEST_LAW_DBF_TTEPBPKB))
#define u1_g_VardefTtTailHead()                        (u1_g_VardefDestLawDbfByPid((U1)VDF_DEST_LAW_DBF_TTTAILHEAD))
#define u1_g_VardefIndSpdBzr()                         (u1_g_VardefDestLawDbfByPid((U1)VDF_DEST_LAW_DBF_INDIASPDBZR))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_VardefCfgBltDst(void);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif      /* VARDEF_DEST_DBF_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  vardef_dest_cfg.c                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
