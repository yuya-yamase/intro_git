/* 1.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Vehicle Status Viewer / Toyota IPC/MET GS Search                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GAGDST_GSS_C_MAJOR                       (1)
#define GAGDST_GSS_C_MINOR                       (1)
#define GAGDST_GSS_C_PATCH                       (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "gagdst_lowfuel_cfg_private.h"
#include "gagdst_gss.h"

#include "rim_ctl.h"
#if 0   /* BEV BSW provisionally */
#else
#include "rim_ctl_cfg_STUB.h"
#endif

#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "Com_Cfg_STUB.h"
#include "oxcan_channel_STUB.h"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((GAGDST_GSS_C_MAJOR != GAGDST_GSS_H_MAJOR) || \
     (GAGDST_GSS_C_MINOR != GAGDST_GSS_H_MINOR) || \
     (GAGDST_GSS_C_PATCH != GAGDST_GSS_H_PATCH))
#error "gagdst_gss.c and gagdst_gss.h : source and header files are inconsistent!"
#endif

#if ((GAGDST_GSS_C_MAJOR != GAGDST_LOWFUEL_CFG_H_MAJOR) || \
     (GAGDST_GSS_C_MINOR != GAGDST_LOWFUEL_CFG_H_MINOR) || \
     (GAGDST_GSS_C_PATCH != GAGDST_LOWFUEL_CFG_H_PATCH))
#error "gagdst_gss.c and gagdst_lowfuel_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GAGDST_GSS_RQ_GSSRC_UNDEF                (0U)                           /* RQ_GSSRC:Undetermined(Undefined)                  */
#define GAGDST_GSS_RQ_GSSRC_REQOFF               (1U)                           /* RQ_GSSRC:No search request                        */
#define GAGDST_GSS_RQ_GSSRC_REQON                (2U)                           /* RQ_GSSRC:Search requested                         */
#define GAGDST_GSS_RQ_GSSRC_UNKNOWN              (3U)                           /* RQ_GSSRC:Undetermined(Unkown)                     */

#define GAGDST_GSS_NUM_STS                       (5U)                           /* Number of GS search states                        */
#define GAGDST_GSS_STS_UNDEF                     (0U)                           /* GS Search Status:Undefined                        */
#define GAGDST_GSS_STS_UNDEFON                   (1U)                           /* GS Search Status:Undefined ON                     */
#define GAGDST_GSS_STS_ON                        (2U)                           /* GS Search Status:ON                               */
#define GAGDST_GSS_STS_ONREF                     (3U)                           /* GS Search Status:ON (refueling)                   */
#define GAGDST_GSS_STS_OFF                       (4U)                           /* GS Search Status:OFF                              */

#define GAGDST_GSS_EVT_SIGNUM                    (4U)                           /* Number of event signals                           */
#define GAGDST_GSS_EVT_REF                       (0x01U)                        /* event signal:refueling                            */
#define GAGDST_GSS_EVT_FLTT                      (0x02U)                        /* event signal:Fuel Low Waning telltale             */
#define GAGDST_GSS_EVT_INISTS                    (0x04U)                        /* event signal:Initial data I Status                */
#define GAGDST_GSS_EVT_IGON                      (0x08U)                        /* event signal:IG-ON                                */

#define GAGDST_GSS_EVT_STMNUM                    (1U << GAGDST_GSS_EVT_SIGNUM)  /* Number of STM for GS Search                       */

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
static U1     u1_s_GagdstGssEvt(const U2 u2_a_SRC_CHK);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_GagdstGssBonInit(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GagdstGssBonInit(void)
{
    U1                       u1_t_tx;                                           /* Transmission data                                 */
    U1                       u1_t_sts;                                          /* GS Search Status                                  */

    u1_t_sts = (U1)GAGDST_GSS_STS_UNDEF;
    vd_g_Rim_WriteU1((U2)RIMID_U1_FUEL_GSS, u1_t_sts);

    u1_t_tx  = (U1)GAGDST_GSS_RQ_GSSRC_UNKNOWN;
    (void)Com_SendSignal(ComConf_ComSignal_RQ_GSSRC, &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_g_GagdstGssRstwkInit(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GagdstGssRstwkInit(void)
{
    U1                       u1_t_tx;                                           /* Transmission data                                 */

    u1_t_tx  = (U1)GAGDST_GSS_RQ_GSSRC_UNKNOWN;
    (void)Com_SendSignal(ComConf_ComSignal_RQ_GSSRC, &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_g_GagdstGssFinhk(const U2 u2_a_SRC_CHK)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const U2 u2_a_SRC_CHK                                                                                            */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_GagdstGssFinhk(const U2 u2_a_SRC_CHK)
{
    static const U1 u1_sp2_GAGDST_GSS_STM[GAGDST_GSS_EVT_STMNUM][GAGDST_GSS_NUM_STS] = {    /* GS Search STM Table                   */
    /*   GAGDST_GSS_STS_UNDEF      GAGDST_GSS_STS_UNDEFON      GAGDST_GSS_STS_ON           GAGDST_GSS_STS_ONREF      GAGDST_GSS_STS_OFF      */
        {(U1)GAGDST_GSS_STS_UNDEF, (U1)GAGDST_GSS_STS_UNDEFON, (U1)GAGDST_GSS_STS_UNDEFON, (U1)GAGDST_GSS_STS_UNDEF, (U1)GAGDST_GSS_STS_UNDEF},
        {(U1)GAGDST_GSS_STS_UNDEF, (U1)GAGDST_GSS_STS_UNDEF,   (U1)GAGDST_GSS_STS_UNDEF,   (U1)GAGDST_GSS_STS_UNDEF, (U1)GAGDST_GSS_STS_UNDEF},
        {(U1)GAGDST_GSS_STS_UNDEF, (U1)GAGDST_GSS_STS_UNDEFON, (U1)GAGDST_GSS_STS_UNDEFON, (U1)GAGDST_GSS_STS_UNDEF, (U1)GAGDST_GSS_STS_UNDEF},
        {(U1)GAGDST_GSS_STS_UNDEF, (U1)GAGDST_GSS_STS_UNDEF,   (U1)GAGDST_GSS_STS_UNDEF,   (U1)GAGDST_GSS_STS_UNDEF, (U1)GAGDST_GSS_STS_UNDEF},
        {(U1)GAGDST_GSS_STS_UNDEF, (U1)GAGDST_GSS_STS_UNDEFON, (U1)GAGDST_GSS_STS_UNDEFON, (U1)GAGDST_GSS_STS_UNDEF, (U1)GAGDST_GSS_STS_UNDEF},
        {(U1)GAGDST_GSS_STS_UNDEF, (U1)GAGDST_GSS_STS_UNDEF,   (U1)GAGDST_GSS_STS_UNDEF,   (U1)GAGDST_GSS_STS_UNDEF, (U1)GAGDST_GSS_STS_UNDEF},
        {(U1)GAGDST_GSS_STS_UNDEF, (U1)GAGDST_GSS_STS_UNDEFON, (U1)GAGDST_GSS_STS_UNDEFON, (U1)GAGDST_GSS_STS_UNDEF, (U1)GAGDST_GSS_STS_UNDEF},
        {(U1)GAGDST_GSS_STS_UNDEF, (U1)GAGDST_GSS_STS_UNDEF,   (U1)GAGDST_GSS_STS_UNDEF,   (U1)GAGDST_GSS_STS_UNDEF, (U1)GAGDST_GSS_STS_UNDEF},
        {(U1)GAGDST_GSS_STS_UNDEF, (U1)GAGDST_GSS_STS_UNDEFON, (U1)GAGDST_GSS_STS_UNDEFON, (U1)GAGDST_GSS_STS_UNDEF, (U1)GAGDST_GSS_STS_UNDEF},
        {(U1)GAGDST_GSS_STS_UNDEF, (U1)GAGDST_GSS_STS_UNDEF,   (U1)GAGDST_GSS_STS_UNDEF,   (U1)GAGDST_GSS_STS_UNDEF, (U1)GAGDST_GSS_STS_UNDEF},
        {(U1)GAGDST_GSS_STS_UNDEF, (U1)GAGDST_GSS_STS_UNDEFON, (U1)GAGDST_GSS_STS_UNDEFON, (U1)GAGDST_GSS_STS_UNDEF, (U1)GAGDST_GSS_STS_UNDEF},
        {(U1)GAGDST_GSS_STS_UNDEF, (U1)GAGDST_GSS_STS_UNDEF,   (U1)GAGDST_GSS_STS_UNDEF,   (U1)GAGDST_GSS_STS_UNDEF, (U1)GAGDST_GSS_STS_UNDEF},
        {(U1)GAGDST_GSS_STS_OFF,   (U1)GAGDST_GSS_STS_ON,      (U1)GAGDST_GSS_STS_ON,      (U1)GAGDST_GSS_STS_OFF,   (U1)GAGDST_GSS_STS_OFF  },
        {(U1)GAGDST_GSS_STS_OFF,   (U1)GAGDST_GSS_STS_OFF,     (U1)GAGDST_GSS_STS_OFF,     (U1)GAGDST_GSS_STS_OFF,   (U1)GAGDST_GSS_STS_OFF  },
        {(U1)GAGDST_GSS_STS_ON,    (U1)GAGDST_GSS_STS_ON,      (U1)GAGDST_GSS_STS_ON,      (U1)GAGDST_GSS_STS_ONREF, (U1)GAGDST_GSS_STS_ON   },
        {(U1)GAGDST_GSS_STS_ONREF, (U1)GAGDST_GSS_STS_ONREF,   (U1)GAGDST_GSS_STS_ONREF,   (U1)GAGDST_GSS_STS_ONREF, (U1)GAGDST_GSS_STS_ONREF}
    };

    static const U1 u1_sp_GAGDST_GSS_TX[GAGDST_GSS_NUM_STS] = {                 /* GS Search Sent Values Table                       */
        (U1)GAGDST_GSS_RQ_GSSRC_UNKNOWN,                                        /* GAGDST_GSS_STS_UNDEF                              */
        (U1)GAGDST_GSS_RQ_GSSRC_UNKNOWN,                                        /* GAGDST_GSS_STS_UNDEFON                            */
        (U1)GAGDST_GSS_RQ_GSSRC_REQON,                                          /* GAGDST_GSS_STS_ON                                 */
        (U1)GAGDST_GSS_RQ_GSSRC_REQON,                                          /* GAGDST_GSS_STS_ONREF                              */
        (U1)GAGDST_GSS_RQ_GSSRC_REQOFF                                          /* GAGDST_GSS_STS_OFF                                */
    };

    U1                                  u1_t_evt_bit;                           /* Event bit                                         */
    U1                                  u1_t_tx;                                /* Transmission data                                 */
    U1                                  u1_t_sts;                               /* GS Search Status                                  */
    U1                                  u1_t_data;                              /* RIM data                                          */

    u1_t_evt_bit = u1_s_GagdstGssEvt(u2_a_SRC_CHK);

    u1_t_data    = (U1)GAGDST_GSS_STS_UNDEF;
    u1_t_sts     = u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_FUEL_GSS, &u1_t_data) & (U1)RIM_RESULT_KIND_MASK;
    if(u1_t_sts != (U1)RIM_RESULT_KIND_OK){
        u1_t_data = (U1)GAGDST_GSS_STS_UNDEF;
    }
    else{
        if((u1_t_data    < (U1)GAGDST_GSS_NUM_STS   ) &&
           (u1_t_evt_bit < (U1)GAGDST_GSS_EVT_STMNUM)){
            u1_t_data = u1_sp2_GAGDST_GSS_STM[u1_t_evt_bit][u1_t_data];
        }
        else{
            u1_t_data = (U1)GAGDST_GSS_STS_UNDEF;
        }
    }

    u1_t_tx = u1_sp_GAGDST_GSS_TX[u1_t_data];

    vd_g_Rim_WriteU1((U2)RIMID_U1_FUEL_GSS, u1_t_data);

    (void)Com_SendSignal(ComConf_ComSignal_RQ_GSSRC, &u1_t_tx);
}
/*===================================================================================================================================*/
/*  static U1     u1_s_GagdstGssEvt(const U2 u2_a_SRC_CHK)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const U2 u2_a_SRC_CHK                                                                                            */
/*  Return:         U1       u1_t_evt_bit                                                                                            */
/*===================================================================================================================================*/
static U1     u1_s_GagdstGssEvt(const U2 u2_a_SRC_CHK)
{
    U1                                  u1_t_lfw;                               /* Low Fuel Warning is On                            */
    U1                                  u1_t_evt_bit;                           /* Event bit                                         */
    U2                                  u2_t_eas_chk;                           /* Result of Source check                            */

    u1_t_evt_bit = (U1)0x00U;

    u2_t_eas_chk = u2_a_SRC_CHK & u2_g_GAGDST_LOWFUEL_SRC_IGN;
    if(u2_t_eas_chk != (U2)0U){
        u1_t_evt_bit |= (U1)GAGDST_GSS_EVT_IGON;
    }

    u2_t_eas_chk = u2_a_SRC_CHK & u2_g_GAGDST_LOWFUEL_SRC_AVG_I;
    if(u2_t_eas_chk != (U2)0U){
        u1_t_evt_bit |= (U1)GAGDST_GSS_EVT_INISTS;
    }

    u1_t_lfw     = u1_g_GagdstLowFuel((U1)FALSE);
    if(u1_t_lfw == (U1)TRUE){
        u1_t_evt_bit |= (U1)GAGDST_GSS_EVT_FLTT;
    }

    u2_t_eas_chk = u2_a_SRC_CHK & u2_g_GAGDST_LOWFUEL_SRC_GFI;
    if(u2_t_eas_chk != (U2)0U){
        u1_t_evt_bit |= (U1)GAGDST_GSS_EVT_REF;
    }

    return(u1_t_evt_bit);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.1.0    07/31/2020  AM       New.                                                                                               */
/*           10/18/2021  TK       Change u1_g_Rim_ReadU1 to u1_g_Rim_ReadU1withStatus.                                               */
/*           11/01/2021  AM       Refine:vd_g_GagdstGssFinhk()                                                                       */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  19PFv3-1 09/21/2023  SN       Delete "#include "gagdst_lowfuel.h"                                                                */
/*                                                                                                                                   */
/*  * AM   = Atsushi Mizutani, DENSO TECHNO                                                                                          */
/*  * TK   = Takanori Kuno, DensoTechno                                                                                              */
/*  * SN   = Shimon Nambu, DensoTechno                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/
