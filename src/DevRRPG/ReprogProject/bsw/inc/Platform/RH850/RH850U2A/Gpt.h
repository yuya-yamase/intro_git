/* Gpt_h */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | RH850/U2Ax/Gpt/HEADER                                       */
/******************************************************************************/
#ifndef GPT_H
#define GPT_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/* Free Run Timer Information */
#define GPT_FRTC_LSB                    (1U)                            /* LSB of a free run timer              */

/* Configuration Number Type */
#define GPT_CHANNEL_NUM                 (2U)                            /* Number of Channel                    */

/* Timer Resource Type */
#define GPT_TMRSC_TAUJ0CH0              ((U4)0x00000000UL)              /* Timer Resource: TAUJ0 Channel 0      */
#define GPT_TMRSC_TAUJ0CH1              ((U4)0x00000001UL)              /* Timer Resource: TAUJ0 Channel 1      */
#define GPT_TMRSC_TAUJ0CH2              ((U4)0x00000002UL)              /* Timer Resource: TAUJ0 Channel 2      */
#define GPT_TMRSC_TAUJ0CH3              ((U4)0x00000003UL)              /* Timer Resource: TAUJ0 Channel 3      */

/* Module ID */
#define GPT_MODULE_ID                   ((U2)0x0002U)                   /* Module ID for GPT Driver             */

/* API ID */
#define GPT_API_ID_INIT                 ((U1)0x00U)                     /* API ID for Gpt_Init                  */
#define GPT_API_ID_STARTTIMER           ((U1)0x01U)                     /* API ID for Gpt_StartTimer            */
#define GPT_API_ID_STOPTIMER            ((U1)0x02U)                     /* API ID for Gpt_StopTimer             */
#define GPT_API_ID_ENABLENOTIFICATION   ((U1)0x03U)                     /* API ID for Gpt_EnableNotification    */
#define GPT_API_ID_DEINIT               ((U1)0x04U)                     /* API ID for Gpt_DeInit                */
#define GPT_API_ID_INTERRUPT            ((U1)0x05U)                     /* API ID for Gpt_Interrupt             */

/* Error Code for GPT Driver */
#define GPT_E_CONFIG                    ((U1)0x01U)                     /* Config Error                         */
#define GPT_E_PARAM                     ((U1)0x02U)                     /* Parameter Error                      */
#define GPT_E_UNINIT                    ((U1)0x03U)                     /* Non-initialization Error             */
#define GPT_E_BUSY                      ((U1)0x04U)                     /* Busy Error                           */

/* GPT Predef Timer Type */
#define GPT_PREDEF_TIMER_1US_32BIT      ((U1)0U)                        /* 32 bit timer of 1 us cycle           */


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
/* GPT Channel Type */
typedef     U1                  Gpt_ChannelType;

/* GPT Value Type */
typedef     U4                  Gpt_ValueType;

/* GPT Predef Timer Type */
typedef     U1                  Gpt_PredefTimerType;

/* GPT Predef Timer Configuration Type */
typedef struct
{
    U4      Tmrsc;                                      /* Free Run Timer Resource      */
} Gpt_PredefTimerConfigType;

/* GPT Event Timer Configuration Type */
typedef struct
{
    U4      Tmrsc;                                      /* Event Timer Resource         */
} Gpt_EventTimerConfigType;

/* GPT Configuration Type */
typedef struct
{
    const Gpt_PredefTimerConfigType*    PredefTimer;    /* Start Address of GPT Predef Timer Configuration Table    */
    const Gpt_EventTimerConfigType*     EventTimer;     /* Start Address of GPT Event Timer Configuration Table     */
} Gpt_ConfigType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
#pragma ghs callmode = far
#pragma ghs section text = ".P_GPT"
void            Gpt_Init(const Gpt_ConfigType* Config);
Std_ReturnType  Gpt_GetPredefTimerValue(Gpt_PredefTimerType PredefTimer, U4* TimerValuePtr);
void            Gpt_StartTimer(Gpt_ChannelType Channel, Gpt_ValueType Value);
void            Gpt_StopTimer(Gpt_ChannelType Channel);
void            Gpt_EnableNotification(Gpt_ChannelType Channel);
void            Gpt_DeInit(void);
void            Gpt_Interrupt(Gpt_ChannelType Channel);
#pragma ghs section text = default
#pragma ghs callmode = default


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#pragma ghs section rosdata = ".C_GPT"
extern const Gpt_ConfigType GPT_CFG_DATA;
#pragma ghs section rosdata = default


#endif  /* GPT_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/04/30 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

