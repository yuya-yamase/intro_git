/* bsw_bswm_cs_status_bswmeth_h_v3-0-0                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/BSWM/CS/STATUS/BSWMETH/HEADER                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef     BSW_BSWM_CS_STATUS_BSWMETH_H
#define     BSW_BSWM_CS_STATUS_BSWMETH_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void bsw_bswm_cs_st_BswMEthInit( void );
void bsw_bswm_cs_st_BswMEthInitDrv( void );
void bsw_bswm_cs_st_BswMEthPreDeInit( void );
void bsw_bswm_cs_st_BswMEthDeInit( void );
void bsw_bswm_cs_st_BswMEthReset( void );
void bsw_bswm_cs_st_BswMEthMainHI( void );
void bsw_bswm_cs_st_BswMEthMainHC( void );
void bsw_bswm_cs_st_BswMEthMainHO( void );
void bsw_bswm_cs_st_BswMEthMainMI( void );
void bsw_bswm_cs_st_BswMEthMainMC( void );
void bsw_bswm_cs_st_BswMEthMainMO( void );
void bsw_bswm_cs_st_BswMEthUpdIPDUSt( void );
void bsw_bswm_cs_st_BswMEthWakeup( void );
void bsw_bswm_cs_st_BswMEthSleep( void );
void bsw_bswm_cs_st_BswMEthCheckRam( void );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif  /* BSW_BSWM_CS_STATUS_BSWMETH_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2018/09/26                                             */
/*  v2-1-0          :2022/10/25                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
