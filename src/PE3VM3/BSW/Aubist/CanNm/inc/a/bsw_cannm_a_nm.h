/* bsw_cannm_a_nm_h_v3-0-0                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANNM/A/NM/HEADER                                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef BSW_CANNM_A_NM_H
#define BSW_CANNM_A_NM_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/*** CONTROL STATUS ***/
#define BSW_CANNM_A_CNTR_SUSPEND            (0x21U)     /* CONTROL status:SUSPEND      */
#define BSW_CANNM_A_CNTR_DRIVE              (0x22U)     /* CONTROL status:DRIVE        */
#define BSW_CANNM_A_CNTR_WAITSHUTDOWN       (0x41U)     /* CONTROL status:WAITSHUTDOWN */
#define BSW_CANNM_A_CNTR_WAITCPUSLEEP       (0x42U)     /* CONTROL status:WAITCPUSLEEP */
#define BSW_CANNM_A_CNTR_FATAL              (0x81U)     /* CONTROL status:FATAL        */


#define BSW_CANNM_A_u1BUSAWAKE_NONE         ((BswU1)0xF0U)      /* Bus awake factor:None */
#define BSW_CANNM_A_u1BUSAWAKE_EXIST        ((BswU1)0xE1U)      /* Bus awake factor:Exist */

/*** Event Wakeup Frame Requested ***/
#define BSW_CANNM_A_u1EVTWKUP_NOREQ         ((BswU1)0xF0U) /* No request */
#define BSW_CANNM_A_u1EVTWKUP_REQ           ((BswU1)0xE1U) /* Request exists */

/*** Com Control Requested ***/
#define BSW_CANNM_A_u1COMCTRL_NOREQ         ((BswU1)0xF0U) /* No request */
#define BSW_CANNM_A_u1COMCTRL_REQ           ((BswU1)0xE1U) /* Request exists */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void  bsw_cannm_a_ctrl_SetStatus(BswU1 u1NetID, BswU1 u1NmSts);
void  bsw_cannm_a_ctrl_InitComCtrl(void);
void  bsw_cannm_a_ctrl_InitComCtrlNn(void);
void  bsw_cannm_a_ctrl_InitEvtWkup( void );
void  bsw_cannm_a_ctrl_InitEvtWkupNn( void );
void  bsw_cannm_a_ctrl_ClrEvtWkupReq( BswU1 u1NetID );
void  bsw_cannm_a_ctrl_ClrEvWkupRqNn( BswU1 u1NetID );
void  bsw_cannm_a_ctrl_TxEvtWkupFr( BswU1 u1NetID );
void  bsw_cannm_a_ctrl_TxEvtWkupFrNn( BswU1 u1NetID );
void  bsw_cannm_a_ctrl_EvWkCnfNotInd( NetworkHandleType nmNetworkHandle, uint16 DisableTime );

BswU1 bsw_cannm_a_ctrl_GetComCtrlSts( BswU1 u1CanNetID );
BswU1 bsw_cannm_a_ctrl_GetCmCtrlStsNn( BswU1 u1CanNetID );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
extern BswU1 bsw_cannm_a_ctrl_u1EvtWkupReq[];
extern BswU1 bsw_cannm_a_ctrl_u1ComCtrlReq[];

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
extern BswConst BswU2  bsw_cannm_a_ctrl_u2DisableTime;
extern void    (* BswConst bsw_cannm_a_ctrl_InitEvWkupFunc)( void );
extern void    (* BswConst bsw_cannm_a_ctrl_ClrEvWkReqFunc)( BswU1 u1NetID );
extern void    (* BswConst bsw_cannm_a_ctrl_TxEvWkReqFunc)( BswU1 u1NetID );
extern void    (* BswConst bsw_cannm_a_ctrl_EvWkCnfIndFunc)( NetworkHandleType nmNetworkHandle, uint16 DisableTime );
extern void    (* BswConst bsw_cannm_a_ctrl_InitComFunc)( void );
extern BswU1   (* BswConst bsw_cannm_a_ctrl_GetCmCtStsFunc)( BswU1 u1CanNetID );

#endif  /* BSW_CANNM_A_NM_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/06/20                                             */
/*  v2-0-0          :2021/12/03                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
