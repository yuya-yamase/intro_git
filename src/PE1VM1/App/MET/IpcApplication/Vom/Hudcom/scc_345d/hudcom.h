/* 0.0.19 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Hudcom                                                                                                                           */
/*===================================================================================================================================*/

#ifndef HCOM_H
#define HCOM_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HCOM_H_MAJOR                      (0)
#define HCOM_H_MINOR                      (0)
#define HCOM_H_PATCH                      (19)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HUD_ENABLE_MET
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HCOM_SET_CNTTSTS_OFF                (0)
#define HCOM_SET_CNTTSTS_ON                 (1)
#define HCOM_SET_CNTTSTS_GRY                (2)

typedef enum {
    HCOM_SETCNTT_STS_ADJUST      = 0,               /* status at "HUD position control"                     */
    HCOM_SETCNTT_STS_MNSW           ,               /* status at "HUD On/Off control"                       */
    HCOM_SETCNTT_STS_CSTM           ,               /* status at "HUD display customizing"                  */
    HCOM_SETCNTT_STS_TCSET          ,               /* status at "Tacho setting"                            */
    HCOM_SETCNTT_STS_TCSET_ECO      ,               /* status at "Tacho setting (eco bar)"                  */
    HCOM_SETCNTT_STS_TCSET_HV       ,               /* status at "Tacho setting (hybsys)"                   */
    HCOM_SETCNTT_STS_CS_NAV         ,               /* status at "Navigation customizing"                   */
    HCOM_SETCNTT_STS_CS_ADS         ,               /* status at "ADAS customizing"                         */
    HCOM_SETCNTT_STS_CS_CMP         ,               /* status at "Compass customizing"                      */
    HCOM_SETCNTT_STS_CS_AUD         ,               /* status at "Audio feedback customizing"               */
    HCOM_SETCNTT_STS_CS_LAN         ,               /* status at "Lane display customizing"                 */
    HCOM_SETCNTT_STS_ROTADJ         ,               /* status at "HUD display rotate control"               */
    EN_HCOM_SETCNTT_STS_TOTAL                       /* Number of Status ID                                  */
} EN_HCOM_SETCNTT_STS;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void	vd_g_HcomBon(void);							/* Battery First Connect Initialization					*/
void	vd_g_HcomIgon(const U4 u4_a_MDBIT, const U4 u4_a_EVTBIT);						/* Ignition Status OFF->ON Change Event					*/
void	vd_g_HcomIgoff(const U4 u4_a_MDBIT, const U4 u4_a_EVTBIT);						/* Ignition Status ON->OFF Change Event					*/
void	vd_g_HcomWakeup(void);						/* Wake Up Initialization 								*/
void	vd_g_HcomRoutine(void);						/* 20ms Task											*/
U1		u1_g_HcomNavmask(void);						/* Notificationce of navi interrupt mask request		*/
U1		u1_g_HcomGetCstmCnttSts(U1 u1_t_cntt);		/* Notification of customize contents state				*/
U1		u1_g_HcomAudioFBmask(void);					/* Notification of audio feedback interrupt mask request	*/

U1		u1_g_HcomGetPowerSts(void);					/* Notification of HUD power supply status				*/
U1		u1_g_HcomGetSwPos(void);					/* Notification of HUD position control existence		*/
U1		u1_g_HcomGetSwRot(void);					/* Notification of HUD display rotate control existence	*/
U1		u1_g_HcomGetSwDsp(void);					/* Notification of HUD display customizing existence	*/
U1		u1_g_HcomGetSwPow(void);					/* Notification of HUD On/Off control existence			*/
U1		u1_g_HcomGetBrightnessMax(void);			/* Notification of HUD brightness max					*/
U1		u1_g_HcomGetBrightness(void);				/* Notification of HUD brightness						*/
U1		u1_g_HcomGetTacExt(void);					/* Notification of HUD tachometer switchover existence	*/
U1		u1_g_HcomGetNavExt(void);					/* Notification of HUD navigation customizing existence	*/
U1		u1_g_HcomGetAdsExt(void);					/* Notification of HUD ADAS customizing existence		*/
U1		u1_g_HcomGetCmpExt(void);					/* Notification of HUD compass customizing existence	*/
U1		u1_g_HcomGetAudExt(void);					/* Notification of HUD audio feedback customizing existence	*/
U1		u1_g_HcomGetLanExt(void);					/* Notification of HUD lane display customizing existence	*/
U1		u1_g_HcomGetTacSts(void);					/* Notification of HUD tacho-area display status		*/
U1		u1_g_HcomGetNavSts(void);					/* Notification of HUD navi customizing status			*/
U1		u1_g_HcomGetAdsSts(void);					/* Notification of HUD ADAS customizing status			*/
U1		u1_g_HcomGetCmpSts(void);					/* Notification of HUD compass customizing status		*/
U1		u1_g_HcomGetAudSts(void);					/* Notification of HUD audio feedback customizing status	*/
U1		u1_g_HcomGetLanSts(void);					/* Notification of HUD lane display customizing status	*/

U1		u1_g_HcomGetCanMsgSts(void);				/* Notification of CAN message status about HUD			*/
#endif /* HCOM_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see  hudcom.c                                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/
