/* PwrCtrl_FullInit                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name | PwrCtrl_FullInit/HEADER                                    */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/
#ifndef PWRCTRL_FULLINIT_H
#define PWRCTRL_FULLINIT_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* äÆëSèâä˙âªåãâ  */
#define PWRCTRL_FULLINIT_RESULT_NON     (0U)        /* èâä˙íl */
#define PWRCTRL_FULLINIT_RESULT_OK      (1U)        /* ê¨å˜ */
#define PWRCTRL_FULLINIT_RESULT_NG      (2U)        /* é∏îs */
#define PWRCTRL_FULLINIT_RESULT_INPRC   (3U)        /* óvãÅíÜ */

#define PWRCTRL_FULLINIT_TIME_INIT      (0U)

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void vd_g_PwrCtrlFullInitInit( void );
void vd_g_PwrCtrlFullInitSeq( void );
U1 u1_g_PwrCtrlFullInitGetResult( void );
void vd_g_PwrCtrlFullInitStartReq( void );

#endif /* PWRCTRL_FULLINIT_H */

/**** End of File ***********************************************************/
