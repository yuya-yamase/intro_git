/* cantp_cfg_h_v3-0-0                                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CANTP/CFG/HEADER                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef BSW_CANTP_CFG_H
#define BSW_CANTP_CFG_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*========== User define Area [Start] ==========*/
#define BSW_CANTP_CFG_DYNBSSTMIN_ADOPT      (BSW_CANTP_LATEST_BSSTMIN)          /* Dynamic BSSTmin adoption             */
#define BSW_CANTP_CFG_FIXED_BS              (0U)                                /* BS fixed value                       */
#define BSW_CANTP_CFG_FIXED_STMIN           (0U)                                /* STmin fixed value                    */
#define BSW_CANTP_CFG_STMIN_USDEF           (BSW_CANTP_USSTMIN_NORMAL)          /* Change the definition of us STmin    */

#define BSW_CANTP_CFG_FDSUPPORT             (BSW_USE)                           /* CANFD Frame Use/NoUse                */
#define BSW_CANTP_CFG_DISABLE_TX            (BSW_USE)                           /* Tx disable Func Use/NoUse            */
#define BSW_CANTP_CFG_ABORT_TX              (BSW_USE)                           /* Tx abort Func Use/NoUse              */
#define BSW_CANTP_CFG_CHANGE_RXPARAM        (BSW_USE)                           /* Change Rx Parameter Use/NoUse        */
#define BSW_CANTP_CFG_READ_RXPARAM          (BSW_NOUSE)                         /* Read Rx Parameter Use/NoUse          */
#define BSW_CANTP_CFG_LOWCOSTOPERATION      (BSW_NOUSE)                         /* Low Cost Operation Use/NoUse         */

#define BSW_CANTP_CFG_PADDINGBYTE           (0x00U)                             /* Padding Byte Data                    */
#define BSW_CANTP_CFG_MAXPDULENGTH          (BSW_CANTP_LENGTH_4K)               /* The max Length of Pdu                */

#define BSW_CANTP_CFG_CANCEL_TX             (BSW_CANTP_FALSE)                   /* Cancel transmit                      */
#define BSW_CANTP_CFG_NEWRX_IN_LASTTX       (BSW_CANTP_TX_INCOMPLETE)           /* New Msg Rx Handling In Last Msg Tx   */
#define BSW_CANTP_CFG_NEXTRX_IN_TX          (BSW_CANTP_TX_REGARD_OK)            /* Next Msg Rx Handling In Msg Tx       */

#define BSW_CANTP_CFG_FCWAIT_TXPDTIME       (0U)                                /* FC.WAIT Tx Period time               */
#define BSW_CANTP_CFG_FC_TXTIMEOUT          (0U)                                /* FC Tx wait timeout time              */
#define BSW_CANTP_CFG_CF_TXTIMEOUT          (0U)                                /* CF Tx wait timeout time              */

#define BSW_CANTP_CFG_RXPARAMPTNNUM         (0U)                                /* Rx Parameter pattern num             */
#define BSW_CANTP_CFG_TXPARAMPTNNUM         (0U)                                /* Tx Parameter pattern num             */

/* The number of Connection Channels */
#define BSW_CANTP_CFG_CHNUM                 (1U)

/* Minimum NSdu Id */
#define BSW_CANTP_CFG_MIN_RXNSDUID          (BSW_PDUR_LOCOMP_CANTP | 0x0000U)
#define BSW_CANTP_CFG_MIN_TXNSDUID          (BSW_PDUR_LOCOMP_CANTP | 0x0000U)

/* Minimum NPdu Id */
#define BSW_CANTP_CFG_MIN_RXNPDUID          (BSW_PDUR_LOCOMP_CANTP | 0x0000U)
#define BSW_CANTP_CFG_MIN_TXNPDUID          (BSW_PDUR_LOCOMP_CANTP | 0x0000U)

/* Connection Channel Mode */
#define BSW_CANTP_CFG_CHANNELMODE_CH00      (BSW_CANTP_MODE_HALF_DUPLEX)
#define BSW_CANTP_CFG_CHANNELMODE_CH01      (BSW_CANTP_MODE_HALF_DUPLEX)
#define BSW_CANTP_CFG_CHANNELMODE_CH02      (BSW_CANTP_MODE_HALF_DUPLEX)
#define BSW_CANTP_CFG_CHANNELMODE_CH03      (BSW_CANTP_MODE_HALF_DUPLEX)
#define BSW_CANTP_CFG_CHANNELMODE_CH04      (BSW_CANTP_MODE_HALF_DUPLEX)
#define BSW_CANTP_CFG_CHANNELMODE_CH05      (BSW_CANTP_MODE_HALF_DUPLEX)
#define BSW_CANTP_CFG_CHANNELMODE_CH06      (BSW_CANTP_MODE_HALF_DUPLEX)
#define BSW_CANTP_CFG_CHANNELMODE_CH07      (BSW_CANTP_MODE_HALF_DUPLEX)
#define BSW_CANTP_CFG_CHANNELMODE_CH08      (BSW_CANTP_MODE_HALF_DUPLEX)
#define BSW_CANTP_CFG_CHANNELMODE_CH09      (BSW_CANTP_MODE_HALF_DUPLEX)
#define BSW_CANTP_CFG_CHANNELMODE_CH10      (BSW_CANTP_MODE_HALF_DUPLEX)
#define BSW_CANTP_CFG_CHANNELMODE_CH11      (BSW_CANTP_MODE_HALF_DUPLEX)
#define BSW_CANTP_CFG_CHANNELMODE_CH12      (BSW_CANTP_MODE_HALF_DUPLEX)
#define BSW_CANTP_CFG_CHANNELMODE_CH13      (BSW_CANTP_MODE_HALF_DUPLEX)
#define BSW_CANTP_CFG_CHANNELMODE_CH14      (BSW_CANTP_MODE_HALF_DUPLEX)
#define BSW_CANTP_CFG_CHANNELMODE_CH15      (BSW_CANTP_MODE_HALF_DUPLEX)
#define BSW_CANTP_CFG_CHANNELMODE_CH16      (BSW_CANTP_MODE_HALF_DUPLEX)
#define BSW_CANTP_CFG_CHANNELMODE_CH17      (BSW_CANTP_MODE_HALF_DUPLEX)
#define BSW_CANTP_CFG_CHANNELMODE_CH18      (BSW_CANTP_MODE_HALF_DUPLEX)
#define BSW_CANTP_CFG_CHANNELMODE_CH19      (BSW_CANTP_MODE_HALF_DUPLEX)
#define BSW_CANTP_CFG_CHANNELMODE_CH20      (BSW_CANTP_MODE_HALF_DUPLEX)
#define BSW_CANTP_CFG_CHANNELMODE_CH21      (BSW_CANTP_MODE_HALF_DUPLEX)
#define BSW_CANTP_CFG_CHANNELMODE_CH22      (BSW_CANTP_MODE_HALF_DUPLEX)
#define BSW_CANTP_CFG_CHANNELMODE_CH23      (BSW_CANTP_MODE_HALF_DUPLEX)
#define BSW_CANTP_CFG_CHANNELMODE_CH24      (BSW_CANTP_MODE_HALF_DUPLEX)
#define BSW_CANTP_CFG_CHANNELMODE_CH25      (BSW_CANTP_MODE_HALF_DUPLEX)
#define BSW_CANTP_CFG_CHANNELMODE_CH26      (BSW_CANTP_MODE_HALF_DUPLEX)
#define BSW_CANTP_CFG_CHANNELMODE_CH27      (BSW_CANTP_MODE_HALF_DUPLEX)
#define BSW_CANTP_CFG_CHANNELMODE_CH28      (BSW_CANTP_MODE_HALF_DUPLEX)
#define BSW_CANTP_CFG_CHANNELMODE_CH29      (BSW_CANTP_MODE_HALF_DUPLEX)
#define BSW_CANTP_CFG_CHANNELMODE_CH30      (BSW_CANTP_MODE_HALF_DUPLEX)
#define BSW_CANTP_CFG_CHANNELMODE_CH31      (BSW_CANTP_MODE_HALF_DUPLEX)

/* The number of RxNSdus */
#define BSW_CANTP_CFG_RXNSDUNUM_CH00        (0U)
#define BSW_CANTP_CFG_RXNSDUNUM_CH01        (0U)
#define BSW_CANTP_CFG_RXNSDUNUM_CH02        (0U)
#define BSW_CANTP_CFG_RXNSDUNUM_CH03        (0U)
#define BSW_CANTP_CFG_RXNSDUNUM_CH04        (0U)
#define BSW_CANTP_CFG_RXNSDUNUM_CH05        (0U)
#define BSW_CANTP_CFG_RXNSDUNUM_CH06        (0U)
#define BSW_CANTP_CFG_RXNSDUNUM_CH07        (0U)
#define BSW_CANTP_CFG_RXNSDUNUM_CH08        (0U)
#define BSW_CANTP_CFG_RXNSDUNUM_CH09        (0U)
#define BSW_CANTP_CFG_RXNSDUNUM_CH10        (0U)
#define BSW_CANTP_CFG_RXNSDUNUM_CH11        (0U)
#define BSW_CANTP_CFG_RXNSDUNUM_CH12        (0U)
#define BSW_CANTP_CFG_RXNSDUNUM_CH13        (0U)
#define BSW_CANTP_CFG_RXNSDUNUM_CH14        (0U)
#define BSW_CANTP_CFG_RXNSDUNUM_CH15        (0U)
#define BSW_CANTP_CFG_RXNSDUNUM_CH16        (0U)
#define BSW_CANTP_CFG_RXNSDUNUM_CH17        (0U)
#define BSW_CANTP_CFG_RXNSDUNUM_CH18        (0U)
#define BSW_CANTP_CFG_RXNSDUNUM_CH19        (0U)
#define BSW_CANTP_CFG_RXNSDUNUM_CH20        (0U)
#define BSW_CANTP_CFG_RXNSDUNUM_CH21        (0U)
#define BSW_CANTP_CFG_RXNSDUNUM_CH22        (0U)
#define BSW_CANTP_CFG_RXNSDUNUM_CH23        (0U)
#define BSW_CANTP_CFG_RXNSDUNUM_CH24        (0U)
#define BSW_CANTP_CFG_RXNSDUNUM_CH25        (0U)
#define BSW_CANTP_CFG_RXNSDUNUM_CH26        (0U)
#define BSW_CANTP_CFG_RXNSDUNUM_CH27        (0U)
#define BSW_CANTP_CFG_RXNSDUNUM_CH28        (0U)
#define BSW_CANTP_CFG_RXNSDUNUM_CH29        (0U)
#define BSW_CANTP_CFG_RXNSDUNUM_CH30        (0U)
#define BSW_CANTP_CFG_RXNSDUNUM_CH31        (0U)

/* The number of TxNSdus */
#define BSW_CANTP_CFG_TXNSDUNUM_CH00        (0U)
#define BSW_CANTP_CFG_TXNSDUNUM_CH01        (0U)
#define BSW_CANTP_CFG_TXNSDUNUM_CH02        (0U)
#define BSW_CANTP_CFG_TXNSDUNUM_CH03        (0U)
#define BSW_CANTP_CFG_TXNSDUNUM_CH04        (0U)
#define BSW_CANTP_CFG_TXNSDUNUM_CH05        (0U)
#define BSW_CANTP_CFG_TXNSDUNUM_CH06        (0U)
#define BSW_CANTP_CFG_TXNSDUNUM_CH07        (0U)
#define BSW_CANTP_CFG_TXNSDUNUM_CH08        (0U)
#define BSW_CANTP_CFG_TXNSDUNUM_CH09        (0U)
#define BSW_CANTP_CFG_TXNSDUNUM_CH10        (0U)
#define BSW_CANTP_CFG_TXNSDUNUM_CH11        (0U)
#define BSW_CANTP_CFG_TXNSDUNUM_CH12        (0U)
#define BSW_CANTP_CFG_TXNSDUNUM_CH13        (0U)
#define BSW_CANTP_CFG_TXNSDUNUM_CH14        (0U)
#define BSW_CANTP_CFG_TXNSDUNUM_CH15        (0U)
#define BSW_CANTP_CFG_TXNSDUNUM_CH16        (0U)
#define BSW_CANTP_CFG_TXNSDUNUM_CH17        (0U)
#define BSW_CANTP_CFG_TXNSDUNUM_CH18        (0U)
#define BSW_CANTP_CFG_TXNSDUNUM_CH19        (0U)
#define BSW_CANTP_CFG_TXNSDUNUM_CH20        (0U)
#define BSW_CANTP_CFG_TXNSDUNUM_CH21        (0U)
#define BSW_CANTP_CFG_TXNSDUNUM_CH22        (0U)
#define BSW_CANTP_CFG_TXNSDUNUM_CH23        (0U)
#define BSW_CANTP_CFG_TXNSDUNUM_CH24        (0U)
#define BSW_CANTP_CFG_TXNSDUNUM_CH25        (0U)
#define BSW_CANTP_CFG_TXNSDUNUM_CH26        (0U)
#define BSW_CANTP_CFG_TXNSDUNUM_CH27        (0U)
#define BSW_CANTP_CFG_TXNSDUNUM_CH28        (0U)
#define BSW_CANTP_CFG_TXNSDUNUM_CH29        (0U)
#define BSW_CANTP_CFG_TXNSDUNUM_CH30        (0U)
#define BSW_CANTP_CFG_TXNSDUNUM_CH31        (0U)

/* The number of RxNPdus */
#define BSW_CANTP_CFG_RXNPDUNUM_CH00        (0U)
#define BSW_CANTP_CFG_RXNPDUNUM_CH01        (0U)
#define BSW_CANTP_CFG_RXNPDUNUM_CH02        (0U)
#define BSW_CANTP_CFG_RXNPDUNUM_CH03        (0U)
#define BSW_CANTP_CFG_RXNPDUNUM_CH04        (0U)
#define BSW_CANTP_CFG_RXNPDUNUM_CH05        (0U)
#define BSW_CANTP_CFG_RXNPDUNUM_CH06        (0U)
#define BSW_CANTP_CFG_RXNPDUNUM_CH07        (0U)
#define BSW_CANTP_CFG_RXNPDUNUM_CH08        (0U)
#define BSW_CANTP_CFG_RXNPDUNUM_CH09        (0U)
#define BSW_CANTP_CFG_RXNPDUNUM_CH10        (0U)
#define BSW_CANTP_CFG_RXNPDUNUM_CH11        (0U)
#define BSW_CANTP_CFG_RXNPDUNUM_CH12        (0U)
#define BSW_CANTP_CFG_RXNPDUNUM_CH13        (0U)
#define BSW_CANTP_CFG_RXNPDUNUM_CH14        (0U)
#define BSW_CANTP_CFG_RXNPDUNUM_CH15        (0U)
#define BSW_CANTP_CFG_RXNPDUNUM_CH16        (0U)
#define BSW_CANTP_CFG_RXNPDUNUM_CH17        (0U)
#define BSW_CANTP_CFG_RXNPDUNUM_CH18        (0U)
#define BSW_CANTP_CFG_RXNPDUNUM_CH19        (0U)
#define BSW_CANTP_CFG_RXNPDUNUM_CH20        (0U)
#define BSW_CANTP_CFG_RXNPDUNUM_CH21        (0U)
#define BSW_CANTP_CFG_RXNPDUNUM_CH22        (0U)
#define BSW_CANTP_CFG_RXNPDUNUM_CH23        (0U)
#define BSW_CANTP_CFG_RXNPDUNUM_CH24        (0U)
#define BSW_CANTP_CFG_RXNPDUNUM_CH25        (0U)
#define BSW_CANTP_CFG_RXNPDUNUM_CH26        (0U)
#define BSW_CANTP_CFG_RXNPDUNUM_CH27        (0U)
#define BSW_CANTP_CFG_RXNPDUNUM_CH28        (0U)
#define BSW_CANTP_CFG_RXNPDUNUM_CH29        (0U)
#define BSW_CANTP_CFG_RXNPDUNUM_CH30        (0U)
#define BSW_CANTP_CFG_RXNPDUNUM_CH31        (0U)

/* The number of TxNPdus */
#define BSW_CANTP_CFG_TXNPDUNUM_CH00        (0U)
#define BSW_CANTP_CFG_TXNPDUNUM_CH01        (0U)
#define BSW_CANTP_CFG_TXNPDUNUM_CH02        (0U)
#define BSW_CANTP_CFG_TXNPDUNUM_CH03        (0U)
#define BSW_CANTP_CFG_TXNPDUNUM_CH04        (0U)
#define BSW_CANTP_CFG_TXNPDUNUM_CH05        (0U)
#define BSW_CANTP_CFG_TXNPDUNUM_CH06        (0U)
#define BSW_CANTP_CFG_TXNPDUNUM_CH07        (0U)
#define BSW_CANTP_CFG_TXNPDUNUM_CH08        (0U)
#define BSW_CANTP_CFG_TXNPDUNUM_CH09        (0U)
#define BSW_CANTP_CFG_TXNPDUNUM_CH10        (0U)
#define BSW_CANTP_CFG_TXNPDUNUM_CH11        (0U)
#define BSW_CANTP_CFG_TXNPDUNUM_CH12        (0U)
#define BSW_CANTP_CFG_TXNPDUNUM_CH13        (0U)
#define BSW_CANTP_CFG_TXNPDUNUM_CH14        (0U)
#define BSW_CANTP_CFG_TXNPDUNUM_CH15        (0U)
#define BSW_CANTP_CFG_TXNPDUNUM_CH16        (0U)
#define BSW_CANTP_CFG_TXNPDUNUM_CH17        (0U)
#define BSW_CANTP_CFG_TXNPDUNUM_CH18        (0U)
#define BSW_CANTP_CFG_TXNPDUNUM_CH19        (0U)
#define BSW_CANTP_CFG_TXNPDUNUM_CH20        (0U)
#define BSW_CANTP_CFG_TXNPDUNUM_CH21        (0U)
#define BSW_CANTP_CFG_TXNPDUNUM_CH22        (0U)
#define BSW_CANTP_CFG_TXNPDUNUM_CH23        (0U)
#define BSW_CANTP_CFG_TXNPDUNUM_CH24        (0U)
#define BSW_CANTP_CFG_TXNPDUNUM_CH25        (0U)
#define BSW_CANTP_CFG_TXNPDUNUM_CH26        (0U)
#define BSW_CANTP_CFG_TXNPDUNUM_CH27        (0U)
#define BSW_CANTP_CFG_TXNPDUNUM_CH28        (0U)
#define BSW_CANTP_CFG_TXNPDUNUM_CH29        (0U)
#define BSW_CANTP_CFG_TXNPDUNUM_CH30        (0U)
#define BSW_CANTP_CFG_TXNPDUNUM_CH31        (0U)

/* DL check(SF) pattern */
#define BSW_CANTP_CFG_DLCHKSF_PTN           (BSW_CANTP_DLCHKSF_PTN0)

/* DL check error action */
#define BSW_CANTP_CFG_DLCHKLCF_ERRACT       (BSW_CANTP_ERRACT_ABORT)
#define BSW_CANTP_CFG_DLCHKFC_ERRACT        (BSW_CANTP_ERRACT_ABORT)

/*========== User define Area [End] ============*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif  /* BSW_CANTP_CFG_H */


/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/09/25                                             */
/*  v1-1-0          :2019/02/22                                             */
/*  v1-2-0          :2020/02/05                                             */
/*  v2-0-0          :2021/08/06                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-2                                              */
/*  BSW plug-in        :v3-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
