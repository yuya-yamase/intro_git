/* bsw_cannm_a_v2-0-0                                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANNM/A/PUBLIC/HEADER                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_CANNM_A_PUBLIC_H
#define BSW_CANNM_A_PUBLIC_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define    BSW_CANNM_A_PDU_NUM                    (1U)       /* Number of NM-PDU */
#define    BSW_CANNM_A_IMMTXOFFSET_NONE           (0U)       /* Immediate wakeup tx offset : 0ms   */
#define    BSW_CANNM_A_IMMTXOFFSET_300MS          (300U)     /* Immediate wakeup tx offset : 300ms */

#define    BSW_CANNM_A_NWST_RING_STABLE           (0x80U)    /* Network Status : Stable                        */
#define    BSW_CANNM_A_NWST_BUS_ERROR             (0x40U)    /* Network Status : Busoff                        */
#define    BSW_CANNM_A_NWST_NM_ACTIVE             (0x20U)    /* Network Status : NMActive                      */
#define    BSW_CANNM_A_NWST_LIMP_HOME             (0x10U)    /* Network Status : NMLimpHome                    */
#define    BSW_CANNM_A_NWST_BUS_SLEEP             (0x08U)    /* Network Status : NMBusSleep                    */
#define    BSW_CANNM_A_NWST_WAIT_BUS_SLEEP        (0x04U)    /* Network Status : NMTwbsNormal or NMTwbsLimpHome */
#define    BSW_CANNM_A_NWST_TXRINGDATA_ALLOWED    (0x02U)    /* Network Status : Access Disable for Data Field on Ring Message */
#define    BSW_CANNM_A_NWST_BUS_SLEEP_IND         (0x01U)    /* Network Status : Sleep.ind=1                   */
#define    BSW_CANNM_A_NWST_ALL_OFF               (0x00U)    /* Network Status : All Off                       */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef uint8   Bsw_CanNmA_NetworkStatusType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/*------------------------------------------*/
/* Unit: CONTROL(nm)                        */
/*------------------------------------------*/
void            bsw_cannm_a_ctrl_Init(BswConst Bsw_CanNm_ConfigType* cannmConfigPtr);
void            bsw_cannm_a_ctrl_DeInit(void);
Std_ReturnType  bsw_cannm_a_ctrl_PassiveStartUp(NetworkHandleType NetworkHandle);
Std_ReturnType  bsw_cannm_a_ctrl_NetworkRequest(NetworkHandleType NetworkHandle);
Std_ReturnType  bsw_cannm_a_ctrl_NetworkRelease(NetworkHandleType NetworkHandle);
void            bsw_cannm_a_ctrl_Wakeup(BswConst Bsw_CanNm_ConfigType* cannmConfigPtr);
uint8           bsw_cannm_a_ctrl_CheckAwake(NetworkHandleType nmChannelHandle);
void            bsw_cannm_a_ctrl_Sleep(void);
void            bsw_cannm_a_ctrl_MainFunction(void);
void            bsw_cannm_a_ctrl_SetBusOff(NetworkHandleType nmChannelHandle);
uint16          bsw_cannm_a_ctrl_ReqEvtWkup(NetworkHandleType nmNetworkHandle);
void            bsw_cannm_a_ctrl_CancelEvtWkup(NetworkHandleType nmNetworkHandle);
Std_ReturnType  bsw_cannm_a_ctrl_GetState(NetworkHandleType nmNetworkHandle, Nm_StateType* nmStatePtr, Nm_ModeType* nmModePtr);
uint8           bsw_cannm_a_ctrl_GetIPDUState( NetworkHandleType nmChannelHandle );
Std_ReturnType  bsw_cannm_a_ctrl_DisableCom( NetworkHandleType NetworkHandle );
Std_ReturnType  bsw_cannm_a_ctrl_EnableCom( NetworkHandleType NetworkHandle );
void            bsw_cannm_a_ctrl_CheckRam(void);

void            bsw_cannm_a_trans_TxConf(PduIdType TxPduId, NetworkHandleType nmChannelHandle, Std_ReturnType result );
void            bsw_cannm_a_trans_RxIndication(PduIdType RxPduId, NetworkHandleType nmChannelHandle, BswConstR PduInfoType* PduInfoPtr);

/*------------------------------------------*/
/* Unit: CONTROL(getstatus)                 */
/*------------------------------------------*/
Std_ReturnType  bsw_cannm_a_ctrl_GetNwStatus(NetworkHandleType nmChannelHandle, Bsw_CanNmA_NetworkStatusType *ptNetworkStatus);

/*------------------------------------------*/
/* Unit: CVT-NM(cvtnmch)                    */
/*------------------------------------------*/
uint16          bsw_cannm_a_cvtnm_GetBackupData(NetworkHandleType nmChannelHandle);
void            bsw_cannm_a_cvtnm_SetBackupData(NetworkHandleType nmChannelHandle, uint16 BackupData);

/*------------------------------------------*/
/* Unit: OSEK-NM(oseklibch)                 */
/*------------------------------------------*/
uint8           bsw_cannm_a_oseknm_GetTxCount(NetworkHandleType nmChannelHandle);
uint8           bsw_cannm_a_oseknm_GetRxCount(NetworkHandleType nmChannelHandle);

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif /* BSW_CANNM_A_PUBLIC_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2021/09/10                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
