/* 1.7.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Multi Media Gateway                                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef GATEWAY_MM_CFG_PRIVATE_H
#define GATEWAY_MM_CFG_PRIVATE_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GATEWAY_MM_CFG_PRIVATE_H_MAJOR                     (1)
#define GATEWAY_MM_CFG_PRIVATE_H_MINOR                     (7)
#define GATEWAY_MM_CFG_PRIVATE_H_PATCH                     (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include "veh_opemd.h"
#if 0   /* BEV BSW provisionally */
#else
#include "veh_opemd_xmode_STUB.h"
#endif
#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "Com_Cfg_STUB.h"
#include "oxcan_channel_STUB.h"
#endif
#include "vardef.h"

#include "gateway_mm.h"
#include "gateway_mm_swinfo.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GWMM_PWRSTS_B                                   (0x01U)                            /*  Power Status B                  */
#define GWMM_PWRSTS_BA                                  (0x02U)                            /*  Power Status BA                 */
#define GWMM_PWRSTS_ACC                                 (0x04U)                            /*  Power Status ACC                */
#define GWMM_PWRSTS_IGR                                 (0x08U)                            /*  Power Status IGR                */
#define GWMM_PWRSTS_IGP                                 (0x10U)                            /*  Power Status IGP                */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U1          u1_pwrsts;                                                                 /*  Power Status                    */
    U1          u1_mm_msgsts_idx;                                                          /*  Message Status Index(MM-SUB)    */
    U1          u1_sigmax;                                                                 /*  Signal Max                      */
    U1          u1_drvmd_idx;                                                              /*  Drive Mode Index                */
}ST_GWMM_SIGCONF;

typedef struct{
    U1          u1_idx;                                                                    /*  Message Buffer Index            */
    U1          u1_bit;                                                                    /*  Message Buffer Bit Pos          */
    U4          u4_mask;                                                                   /*  Message Buffer Mask             */
}ST_GWMM_MSGCOMVERT;

typedef struct{
    void        ( * fp_vd_send)(const U1  u1_a_SIG);                                       /*  CAN Send IF                     */
    U1          ( * fp_u1_read)(void);                                                     /*  CAN Read IF                     */
}ST_GWMM_COMIF;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern       U4                            u4_gp_gwmm_msgbuf[];                            /*  Message Buf                     */
extern       U1                            u1_gp_gwmm_strsw_drvmd[];                       /*  SteeringSw DriveMode            */
extern       U1                            u1_gp_gwmm_strsw_cnt[];                         /*  SteeringSw Tx Count             */
extern       U4                            u4_gp_gwmm_tmm_msgbuf[];                        /*  Message(toMM) Buf               */
extern       U1                            u1_g_gwmm_tmnssw_sigbak;                        /*  Message Buf(L_TMNSSW)           */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void vd_g_GwmmCfgPreTask(void);
U1   u1_g_GwmmCfgGetMMGTWEsOpt(void);
void vd_g_GwmmCfgSend_MMCKPT(const U1 u1_a_pwrsts);
void vd_g_GwmmCfgSend_L_TBC_FUNC(const U1 u1_a_pwrsts);
void vd_g_GwmmCfgSend_TMNSSW(const U1 u1_a_SIG);
U1   u1_g_GwmmCfgRead_TMNSSW(void);
U1   u1_g_GwmmCfgRead_L_TMNSSW(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const U1                           u1_g_GWMM_SIG_NUM;                               /*  Gateway Signal Number           */
extern const U1                           u1_g_GWMM_MSGBUF_NUM;                            /*  Message Buf Number              */
extern const U1                           u1_g_GWMM_MSG_MM_NUM;                            /*  Message Number(MM-SUB)          */

extern const U1                           u1_g_GWMM_DRVMD_NUM;                             /*  Drive Mode Number               */

extern const U1                           u1_g_GWMM_TMM_SIG_NUM;                           /*  Gateway Signal(toMM) Number     */
extern const U1                           u1_g_GWMM_TMM_MSGBUF_NUM;                        /*  Message Buf(toMM) Number        */
extern const U1                           u1_g_GWMM_TMM_MSG_MM_NUM;                        /*  Message Number(toMM)            */

extern const ST_GWMM_MSGCOMVERT           st_gp_GWMM_MSGCOMVERT[];                         /*  Message Convert                 */
extern const ST_GWMM_SIGCONF              st_gp_GWMM_SIGCONF[];                            /*  Signal Config                   */
extern const ST_GWMM_COMIF                st_gp_GWMM_COMIF[];                              /*  Communication IF                */

extern const U1                           u1_gp_GWMM_DRVMDPWCONF[];                        /*  Drive Mode Power Config         */

extern const ST_GWMM_MSGCOMVERT           st_gp_GWMM_TMM_MSGCOMVERT[];                     /*  Message Convert(toMM)           */
extern const ST_GWMM_SIGCONF              st_gp_GWMM_TMM_SIGCONF[];                        /*  Signal Config(toMM)             */
extern const ST_GWMM_COMIF                st_gp_GWMM_TMM_COMIF[];                          /*  Communication IF(toMM)          */

#endif      /* GATEWAY_MM_CFG_PRIVATE_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  gateway_mm.c                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/
