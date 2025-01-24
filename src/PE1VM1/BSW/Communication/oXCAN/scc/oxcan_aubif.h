/* 1.3.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Oem eXention of CAN Aubist Interface Layer                                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef OXCAN_AUBIF_H
#define OXCAN_AUBIF_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_AUBIF_H_MAJOR                      (1U)
#define OXCAN_AUBIF_H_MINOR                      (3U)
#define OXCAN_AUBIF_H_PATCH                      (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
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
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_oXCANAubIfInit(void);
void    Aubist_UsrSetWakeupEvent(const uint32 u4_a_SRC);
uint8   u1_g_oXCANAubIfGicUnk(void);

#ifdef CXPICDD_TYPES_H
void    vd_g_oXCANAubIfCxpiRecAck(const uint8 u1_a_AUB_IDX);
void    vd_g_oXCANAubIfCxpiTraAck(const uint8 u1_a_AUB_IDX);
uint8   u1_g_oXCANAubIfCxpiNmwkRqst(void);                                                   /* Return   : CXPICDD_TRUE  : Sleep NG */
                                                                                             /*            CXPICDD_FALSE : Sleep OK */
void    vd_g_oXCANAubIfCxpiNmUpdt(const uint16 u2_a_EVBIT);

void    vd_g_oXCANAubIfSetNslpHigh(void);
void    vd_g_oXCANAubIfSetNslpLow(void);
cxpi_uint8  u1_g_oXCANAubIfGetNslpSts(void);
void    vd_g_oXCANAubIfSetPortGpo(void);
void    vd_g_oXCANAubIfSetPort(void);
void    vd_g_oXCANAubIfCxpiIcStt(void);
void    vd_g_oXCANAubIfCxpiIcStp(void);
void    vd_g_oXCANAubIfIbsIfsTimerStt(void);
void    vd_g_oXCANAubIfIbsIfsTimerStp(void);
void    vd_g_oXCANAubIfIbsTimerStp(void);
void    vd_g_oXCANAubIf1stIfsTimerStt(void);
void    vd_g_oXCANAubIfPreInfoTimerStt(void);
void    vd_g_oXCANAubIfPostInfoTimerStt(void);
void    vd_g_oXCANAubIfAbnInit(void);
void    vd_g_oXCANAubIfEnableEdgeDetect(const cxpi_bool u1_a_CLRFLG);
void    vd_g_oXCANAubIfDisableEdgeDetect(void);
cxpi_uint8  u1_g_oXCANAubIfGetEdgeDetect(void);
cxpi_uint8  u1_g_oXCANAubIfGetClockDetect(void);
void    vd_g_oXCANAubIfCxpiUaEnableInt(void);
void    vd_g_oXCANAubIfCxpiUaDisableInt(void);
cxpi_bool   u1_g_oXCANAubIfCxpiUaGetIntReq(void);
cxpi_bool   u1_g_oXCANAubIfCheckWakeup(void);
cxpi_bool   u1_g_oXCANAubIfCheckSlpCancel(void);
void    vd_g_oXCANAubIfCxpiIncEdgeCnt(void);

#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif /* OXCAN_AUBIF_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see  oxcan_aubif.c                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/
