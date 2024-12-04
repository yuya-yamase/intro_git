/* 1.4.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  IO Hardware Abstraction Digital Input Filter                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef IOHW_DIFLT_CFG_H
#define IOHW_DIFLT_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define IOHW_DIFLT_CFG_H_MAJOR                   (1)
#define IOHW_DIFLT_CFG_H_MINOR                   (4)
#define IOHW_DIFLT_CFG_H_PATCH                   (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "memcpy_u4.h"
#include "iohw_diflt.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define IOHW_DIFLT_DIPORT_NUM_INST               (16U)

#define IOHW_DILFT_CTRLOPT_DLYMSK_ENA            (0x0010U)
#define IOHW_DILFT_CTRLOPT_INIT_ENA              (0x0008U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{ 
    U2                    u2_sgnlbit;
    U2                    u2_sgnlact;
    U2                    u2_port;
    U2                    u2_fltr;
}ST_IOHW_DISGNL;

typedef struct{ 
    U2                    u2_sgnlbit;
    U2                    u2_port; 
}ST_IOHW_DIGR;

typedef struct{
    U2                    u2_smplgchk;
    U2                    u2_smplgena;
    U2                    u2_ctrlopt;     /* See IOHW_DILFT_CTRLOPT_XXX                                                     */

    U2                    u2_dlymask;     /* delay time to determine 1st value of signal                                    */
                                          /* ------------------------------------------------------------------------------ */
                                          /* Attention :                                                                    */
                                          /* ------------------------------------------------------------------------------ */
                                          /* if u2_dlymask > 0, IOHW_DILFT_CTRLOPT_DLYMSK_ENA shall be set to u2_ctrlopt.   */
                                          /* ------------------------------------------------------------------------------ */

    U2                    u2_cycle;       /* sampling cycle/period                                                          */
    U1                    u1_valid_init;  /* number of samples to determine 1st value of signal                             */
                                          /* ------------------------------------------------------------------------------ */
                                          /* Attention :                                                                    */
                                          /* ------------------------------------------------------------------------------ */
                                          /* if u1_valid_init >= 2, IOHW_DILFT_CTRLOPT_INIT_ENA shall be set to u2_ctrlopt. */
                                          /* ------------------------------------------------------------------------------ */

    U1                    u1_valid_nrml;  /* number of samples to determine 2nd value of signal and after                   */
}ST_IOHW_DIFLTR;

typedef struct{
    U2                     u2_tmelpsd;
    U1                     u1_validcnt;
    U1                     u1_fltrsts;
}ST_IOHW_DICTRL;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern U4                          u4_gp_iohw_diflt_fltrd[];    /* array size = # of digital port                                */
extern U2                          u2_gp_iohw_diflt_smpld[];    /* array size = # of digital port                                */

extern ST_IOHW_DICTRL              st_gp_iohw_diflt_ctrl[];     /* array size = # of di-signals, e.g. u2_g_IOHW_DIFLT_NUM_DISGNL */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_IoHwDifltCfgInit(void);
U2      u2_g_IoHwDifltCfgSmplgchk(void);
void    vd_g_IoHwDifltCfgRead(U2 * u2_ap_di_inst);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* -------------------------------------------------------------------------------------------- */
/* Attention :                                                                                  */
/* If sampling conditions are determined after executing vd_g_IoHwDifltMainTask, the conditions */
/* expect to be set to u2_g_IOHW_DIFLT_SMPLGCHK_AT_EVT in order to synchronize between          */
/* sampling conditions and di-signals in vd_g_IoHwDifltSgnlInit.                                */
/*                                                                                              */
/* Example)                                                                                     */
/* In Toyota-MET/HUD, vehicle operational mode, especially Ignition, are detemined after        */
/* executing vd_g_IoHwDifltMainTask.                                                            */
/* -------------------------------------------------------------------------------------------- */
extern const U2                    u2_g_IOHW_DIFLT_SMPLGCHK_AT_EVT;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const U2                    u2_g_IOHW_DIFLT_NUM_DIPORT;

extern const ST_IOHW_DIFLTR        st_gp_IOHW_DIFLT_FLTR[];

extern const ST_IOHW_DISGNL        st_gp_IOHW_DIFLT_DISGNL[];  /* array size = # of di-signals, e.g. u2_g_IOHW_DIFLT_NUM_DISGNL */
extern const U2                    u2_g_IOHW_DIFLT_NUM_DISGNL;

extern const ST_IOHW_DIGR          st_gp_IOHW_DIFLT_DIGR[]; 
extern const U2                    u2_g_IOHW_DIFLT_NUM_DIGR;

#endif      /* IOHW_DIFILT_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see iohw_diflt_cfg.c                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/
