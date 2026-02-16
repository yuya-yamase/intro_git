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
#define VDF_DEST_LAW_DBF_NBYTE          (18U)
#define VDF_DEST_LAW_DBF_DEFUNIT_SPD    (0U)
#define VDF_DEST_LAW_DBF_DEFUNIT_DST    (1U)
#define VDF_DEST_LAW_DBF_DEFUNIT_FUECO  (2U)
#define VDF_DEST_LAW_DBF_DEFUNIT_ELECO  (3U)
#define VDF_DEST_LAW_DBF_UNITSLCT_FUECO (4U)
#define VDF_DEST_LAW_DBF_UNITSLCT_DEST  (5U)
#define VDF_DEST_LAW_DBF_BZ_SBW_SUP     (6U)
#define VDF_DEST_LAW_DBF_MDLEST_WRN     (7U)
#define VDF_DEST_LAW_DBF_INDIASPDBZR    (8U)
#define VDF_DEST_LAW_DBF_BZ_REV_DEST    (9U)
#define VDF_DEST_LAW_DBF_SEATBLT_CONST  (10U)
#define VDF_DEST_LAW_DBF_SUBDIGSPD      (11U)
#define VDF_DEST_LAW_DBF_SPDTLRNC       (12U)
#define VDF_DEST_LAW_DBF_CHAINAREQ      (13U)
#define VDF_DEST_LAW_DBF_TTBRAKE        (14U)
#define VDF_DEST_LAW_DBF_TTABS          (15U)
#define VDF_DEST_LAW_DBF_TTEPBPKB       (16U)
#define VDF_DEST_LAW_DBF_TTTAILHEAD     (17U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDF_DEST_DBF_NBYTE              (10U)
#define VDF_DEST_DBF_DESTINATION        (0U)
#define VDF_DEST_DBF_TIMEFMT            (1U)
#define VDF_DEST_DBF_CALDSPTYP          (2U)
#define VDF_DEST_DBF_SMASTAMID          (3U)
#define VDF_DEST_DBF_ENGUNT             (4U)
#define VDF_DEST_DBF_EUSPDSCALE         (5U)
#define VDF_DEST_DBF_TTTRCOFF           (6U)
#define VDF_DEST_DBF_TTVSCEXP           (7U)
#define VDF_DEST_DBF_STPIND             (8U)
#define VDF_DEST_DBF_AMBTMP             (9U)

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
#define VDF_UNIT_FUECO_BIT_KMPL         (0x01U)
#define VDF_UNIT_FUECO_BIT_LP100KM      (0x02U)
#define VDF_UNIT_FUECO_BIT_MPG_USA      (0x04U)
#define VDF_UNIT_FUECO_BIT_MPG_UK       (0x08U)
#define VDF_UNIT_FUECO_BIT_MPG_UKIMP    (0x10U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDF_NUM_UNIT_TYPE_DEST          (4U)
#define VDF_UNIT_TYPE_NA                (0U)
#define VDF_UNIT_TYPE_JPN               (1U)
#define VDF_UNIT_TYPE_EU                (2U)
#define VDF_UNIT_TYPE_UK                (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDF_NUM_CALDSPTYP               (3U)
#define VDF_CALDSPTYP_YYYYMMDD          (0U)
#define VDF_CALDSPTYP_MMDDYYYY          (1U)
#define VDF_CALDSPTYP_DDMMYYYY          (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDF_NUM_SMASTAMID               (2U)
#define VDF_SMASTAMID_WO_NA             (0U)
#define VDF_SMASTAMID_NA                (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDF_NUM_ENGUNT                  (3U)
#define VDF_ENGUNT_RPM                  (0U)
#define VDF_ENGUNT_RMIN                 (1U)
#define VDF_ENGUNT_NON                  (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDF_NUM_EUSPDSCALE_DST          (2U)
#define VDF_EUSPDSCALE_NML              (0U)
#define VDF_EUSPDSCALE_EU               (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDF_NUM_TTTRCOFF                (2U)
#define VDF_TTTRCOFF_NO8                (0U)
#define VDF_TTTRCOFF_NO155              (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDF_NUM_TTVSCEXP                (2U)
#define VDF_TT_VSCEXPERT1               (0U)
#define VDF_TT_VSCEXPERT2               (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDF_NUM_BZ_SBW_SUP              (2U)
#define VDF_BZ_SBW_NON                  (0U)
#define VDF_BZ_SBW_WITH                 (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDF_NUM_INDSDBZR                (2U)
#define VDF_INDSDBZR_NON                (0U)
#define VDF_INDSDBZR_WITH               (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDF_NUM_BZ_REV_DST              (2U)
#define VDF_BZ_REV_OTR                  (0U)
#define VDF_BZ_REV_JPN                  (1U)

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
#define VDF_NUM_UNIT_TYPE               (12U)
#define VDF_UNIT_TYPE_A                 (0U)
#define VDF_UNIT_TYPE_B                 (1U)
#define VDF_UNIT_TYPE_C                 (2U)
#define VDF_UNIT_TYPE_D                 (3U)
#define VDF_UNIT_TYPE_E                 (4U)
#define VDF_UNIT_TYPE_F                 (5U)
#define VDF_UNIT_TYPE_G                 (6U)
#define VDF_UNIT_TYPE_H                 (7U)
#define VDF_UNIT_TYPE_I                 (8U)
#define VDF_UNIT_TYPE_J                 (9U)
#define VDF_UNIT_TYPE_K                 (10U)
#define VDF_UNIT_TYPE_L                 (11U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDF_NUM_SEATBLT_DEST            (3U)
#define VDF_SEATBLT_DEST_USA            (0U)
#define VDF_SEATBLT_DEST_EU             (1U)
#define VDF_SEATBLT_DEST_CHN            (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u1_g_VardefDestinationByPid()                  (u1_g_VardefDestDbfByPid((U1)VDF_DEST_DBF_DESTINATION))
#define u1_g_VardefDefUnitSpdByPid()                   (u1_g_VardefDestLawDbfByPid((U1)VDF_DEST_LAW_DBF_DEFUNIT_SPD))
#define u1_g_VardefDefUnitDstByPid()                   (u1_g_VardefDestLawDbfByPid((U1)VDF_DEST_LAW_DBF_DEFUNIT_DST))
#define u1_g_VardefDefUnitFuecoByPid()                 (u1_g_VardefDestLawDbfByPid((U1)VDF_DEST_LAW_DBF_DEFUNIT_FUECO))
#define u1_g_VardefDefUnitElecoByPid()                 (u1_g_VardefDestLawDbfByPid((U1)VDF_DEST_LAW_DBF_DEFUNIT_ELECO))
#define u1_g_VardefUnitSlctFuecoByPid()                (u1_g_VardefDestLawDbfByPid((U1)VDF_DEST_LAW_DBF_UNITSLCT_FUECO))
#define u1_g_VardefUnitSlctDstByPid()                  (u1_g_VardefDestLawDbfByPid((U1)VDF_DEST_LAW_DBF_UNITSLCT_DEST))
#define u1_g_VardefUnitSlctTypeByPid()                 (u1_g_VardefCfgUnitType())
#define u1_g_VardefDefTmFmtByPid()                     (u1_g_VardefDestDbfByPid((U1)VDF_DEST_DBF_TIMEFMT))
#define u1_g_VardefCalenderDispTypeByPid()             (u1_g_VardefDestDbfByPid((U1)VDF_DEST_DBF_CALDSPTYP))
#define u1_g_VardefSmaStaMIDByPid()                    (u1_g_VardefDestDbfByPid((U1)VDF_DEST_DBF_SMASTAMID))
#define u1_g_VardefEngUnit()                           (u1_g_VardefDestDbfByPid((U1)VDF_DEST_DBF_ENGUNT))
#define u1_g_VardefEuSpdScaleByPid()                   (u1_g_VardefDestDbfByPid((U1)VDF_DEST_DBF_EUSPDSCALE))
#define u1_g_VardefTtTrcoff()                          (u1_g_VardefDestDbfByPid((U1)VDF_DEST_DBF_TTTRCOFF))
#define u1_g_VardefTTVscExp()                          (u1_g_VardefDestDbfByPid((U1)VDF_DEST_DBF_TTVSCEXP))
#define u1_g_VardefBzSbwDiagSupByPid()                 (u1_g_VardefDestLawDbfByPid((U1)VDF_DEST_LAW_DBF_BZ_SBW_SUP))
#define u1_g_VardefMdlLEstWrnByPid()                   (u1_g_VardefDestLawDbfByPid((U1)VDF_DEST_LAW_DBF_MDLEST_WRN))
#define u1_g_VardefBzRevDstByPid()                     (u1_g_VardefDestLawDbfByPid((U1)VDF_DEST_LAW_DBF_BZ_REV_DEST))
#define u1_g_VardefBltDstByPid()                       (u1_g_VardefCfgBltDst())
#define u1_g_VardefSubDigSpdByPid()                    (u1_g_VardefDestLawDbfByPid((U1)VDF_DEST_LAW_DBF_SUBDIGSPD))
#define u1_g_VardefSpdTlrncByPid()                     (u1_g_VardefDestLawDbfByPid((U1)VDF_DEST_LAW_DBF_SPDTLRNC))
#define u1_g_VardefChainaReq()                         (u1_g_VardefDestLawDbfByPid((U1)VDF_DEST_LAW_DBF_CHAINAREQ))
#define u1_g_VardefTtBrake()                           (u1_g_VardefDestLawDbfByPid((U1)VDF_DEST_LAW_DBF_TTBRAKE))
#define u1_g_VardefTtAbs()                             (u1_g_VardefDestLawDbfByPid((U1)VDF_DEST_LAW_DBF_TTABS))
#define u1_g_VardefTtEpbPkb()                          (u1_g_VardefDestLawDbfByPid((U1)VDF_DEST_LAW_DBF_TTEPBPKB))
#define u1_g_VardefTtTailHead()                        (u1_g_VardefDestLawDbfByPid((U1)VDF_DEST_LAW_DBF_TTTAILHEAD))
#define u1_g_VardefIndSpdBzr()                         (u1_g_VardefDestLawDbfByPid((U1)VDF_DEST_LAW_DBF_INDIASPDBZR))
#define u1_g_VardefStpInd()                            (u1_g_VardefDestDbfByPid((U1)VDF_DEST_DBF_STPIND))
#define u1_g_VardefUnitAmbTmpByPid()                   (u1_g_VardefDestDbfByPid((U1)VDF_DEST_DBF_AMBTMP))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_VardefCfgUnitType(void);
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
