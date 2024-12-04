/* bsw_cannm_z_ctrl_h_v2-0-0                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANNM/Z/CTRL/HEADER                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_CANNM_Z_CTRL_H
#define BSW_CANNM_Z_CTRL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* NM status */
#define BSW_CANNM_Z_u2STATE_UNINIT           ((BswU2)0xFF00U)
#define BSW_CANNM_Z_u2STATE_BUSSLEEP         ((BswU2)0x01FEU)
#define BSW_CANNM_Z_u2STATE_NETMODE          ((BswU2)0x02FDU)
#define BSW_CANNM_Z_u2STATE_INVALID          ((BswU2)0x09F6U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* Structure for maintaining channel status */
typedef struct
{
    BswU2 u2NmSt;              /* NM status                           */
    BswU2 u2SendTimer;         /* Transmission enabled timer                   */
    BswU1 u1SendTimerOn;       /* Flag for transmission enabled timer start judge   */
    BswU1 u1BusAwake;          /* Bus Awake factor               */
    BswU1 u1ChPower;           /* Channel power on/off                 */
    BswU1 u1ComMsgSt;          /* Whether to send event/periodic messages  */
} Bsw_CanNmZ_ChStsType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
extern Bsw_CanNmZ_ChStsType  bsw_cannm_z_ctrl_stChSts[];         /* NM status  */

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
extern BswConst BswU1                     bsw_cannm_z_ctrl_u1MaxCh;        /* Maximum number of channels              */
extern BswConst BswU1                     bsw_cannm_z_ctrl_u1ChOffset;     /* Channel offset          */
extern BswConst BswU2                     bsw_cannm_z_ctrl_u2SndStrt[];    /* Control message transmission enable time  */
extern BswConst BswU1                     bsw_cannm_z_ctrl_u1Channel[];    /* Use/not use of CanNmZ */

#endif  /* BSW_CANNM_Z_CTRL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/02/22                                             */
/*  v2-0-0          :2021/12/02                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
