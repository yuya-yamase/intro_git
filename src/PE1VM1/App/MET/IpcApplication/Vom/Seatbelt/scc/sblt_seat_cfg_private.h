/* 2.2.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Seatbelt reminder warning                                                                                                        */
/*  D/P/R seat information                                                                                                           */
/*===================================================================================================================================*/

#ifndef SBLT_SEAT_CFG_PRIVATE_H
#define SBLT_SEAT_CFG_PRIVATE_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SBLT_SEAT_CFG_PRIVATE_H_MAJOR           (2)
#define SBLT_SEAT_CFG_PRIVATE_H_MINOR           (2)
#define SBLT_SEAT_CFG_PRIVATE_H_PATCH           (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "sbltwrn_cfg_private.h"
#include "sblt_seat.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SBLTWRN_BKLSIG_NUM                      (5U)
#define SBLTWRN_BKLSIG_BUCKLED                  (0x00U)
#define SBLTWRN_BKLSIG_UNBUCKLED                (0x01U)
#define SBLTWRN_BKLSIG_UNKNOWN                  (0x02U)
#define SBLTWRN_BKLSIG_FAILED                   (0x03U)
#define SBLTWRN_BKLSIG_COMFAIL                  (0x04U)

#define SBLTWRN_SEATSIG_NUM                     (5U)
#define SBLTWRN_SEATSIG_NOT_EXIST               (0x00U)
#define SBLTWRN_SEATSIG_EXIST                   (0x01U)
#define SBLTWRN_SEATSIG_UNKNOWN                 (0x02U)
#define SBLTWRN_SEATSIG_FAILED                  (0x03U)
#define SBLTWRN_SEATSIG_COMFAIL                 (0x04U)


/* Rr(2nd)-Seat Type    */
#define SBLT_SEAT_RR2TYPNUM                     (2U)        /* A number of rear seat type tbl */
#define SBLT_SEAT_RR_NOSN                       (0U)        /* BCKL: R*BKLPDC / Occupant Detection: None   */
#define SBLT_SEAT_RR_RXOSW                      (1U)        /* BCKL: R*BKLPDC / Occupant Detection: R*OSW  */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void            vd_g_SbltDsCfgInit(void);
U1              u1_g_SbltDsCfgGetDBKLAB(void);
U1              u1_g_SbltDsCfgGetDBKLSW(void);
U1              u1_g_SbltPsCfgGetPBKLAB(void);
U1              u1_g_SbltPsCfgGetPBKLPDC(void);
U1              u1_g_SbltPsCfgGetPOSW(void);
U1              u1_g_SbltFcCfgGetCFBCKL(void);
U1              u1_g_SbltFcCfgGetCFOSW(void);
U1              u1_g_SbltRsCfgGetRRBKLPDC(void);
U1              u1_g_SbltRsCfgGetRCBKLPDC(void);
U1              u1_g_SbltRsCfgGetRLBKLPDC(void);
U1              u1_g_SbltRsCfgGetRR2BCKL(void);
U1              u1_g_SbltRsCfgGetCR2BCKL(void);
U1              u1_g_SbltRsCfgGetLR2BCKL(void);
U1              u1_g_SbltRsCfgGetRR3BCKL(void);
U1              u1_g_SbltRsCfgGetCR3BCKL(void);
U1              u1_g_SbltRsCfgGetLR3BCKL(void);
void            vd_g_SbltDsCfgTxDBKL_MET(const U1 u1_a_DBKL_MET, const U1 u1_a_EVENT_SEND);
void            vd_g_SbltPsCfgTxPBKL_MET(const U1 u1_a_PBKL_MET, const U1 u1_a_EVENT_SEND);
void            vd_g_SbltRsCfgTxRRBKLMET(const U1 u1_a_RRBKLMET, const U1 u1_a_EVENT_SEND);
void            vd_g_SbltRsCfgTxRCBKLMET(const U1 u1_a_RCBKLMET, const U1 u1_a_EVENT_SEND);
void            vd_g_SbltRsCfgTxRLBKLMET(const U1 u1_a_RLBKLMET, const U1 u1_a_EVENT_SEND);
void            vd_g_SbltRsCfgTxBKL3RMET(const U1 u1_a_BKL3RMET, const U1 u1_a_EVENT_SEND);
void            vd_g_SbltRsCfgTxBKL3CMET(const U1 u1_a_BKL3CMET, const U1 u1_a_EVENT_SEND);
void            vd_g_SbltRsCfgTxBKL3LMET(const U1 u1_a_BKL3LMET, const U1 u1_a_EVENT_SEND);
U1              u1_g_SbltRsCfgGetRROSW(void);
U1              u1_g_SbltRsCfgGetRCOSW(void);
U1              u1_g_SbltRsCfgGetRLOSW(void);
U1              u1_g_SbltRsCfgGetRR2OSW(void);
U1              u1_g_SbltRsCfgGetRC2OSW(void);
U1              u1_g_SbltRsCfgGetRL2OSW(void);
U1              u1_g_SbltRsCfgGetRR3OSW(void);
U1              u1_g_SbltRsCfgGetRC3OSW(void);
U1              u1_g_SbltRsCfgGetRL3OSW(void);
U1              u1_g_SbltDsCfgABGSupd(void);        /* A judgment whether to receive D-Seat signal via ABG ECU or HardWire   */
U1              u1_g_SbltPsCfgABGSupd(void);        /* A judgment whether to receive P-Seat signal via ABG ECU or PDC ECU    */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#endif /* SBLT_SEAT_CFG_PRIVATE_H */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  sblt_seat_cfg.c                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/
