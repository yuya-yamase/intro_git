/* bsw_bswm_cs_status_bswmlin_h_v3-0-0                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/BSWM/CS/STATUS/BSWMLIN/HEADER                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef     BSW_BSWM_CS_STATUS_BSWMLIN_H
#define     BSW_BSWM_CS_STATUS_BSWMLIN_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void bsw_bswm_cs_st_BswMLinInit( void );
void bsw_bswm_cs_st_BswMLinInitDrv( void );
void bsw_bswm_cs_st_BswMLinPreDeInit( void );
void bsw_bswm_cs_st_BswMLinDeInit( void );
void bsw_bswm_cs_st_BswMLinReset( void );
void bsw_bswm_cs_st_BswMLinMainHI( void );
void bsw_bswm_cs_st_BswMLinMainHO( void );
void bsw_bswm_cs_st_BswMLinMainMI( void );
void bsw_bswm_cs_st_BswMLinMainMC( void );
void bsw_bswm_cs_st_BswMLinMainMO( void );
void bsw_bswm_cs_st_BswMLinUpdIPDUSt( void );
void bsw_bswm_cs_st_BswMLinWakeup( void );
void bsw_bswm_cs_st_BswMLinSleep( void );
void bsw_bswm_cs_st_BswMLinCheckRam( void );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif  /* BSW_BSWM_CS_STATUS_BSWMLIN_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2018/09/26                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
