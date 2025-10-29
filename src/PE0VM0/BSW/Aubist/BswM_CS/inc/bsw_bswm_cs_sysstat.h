/* bsw_bswm_cs_sysstat_h_v3-0-0                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/BSWM/CS/SYSSTAT/HEADER                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef     BSW_BSWM_CS_SYSSTAT_H
#define     BSW_BSWM_CS_SYSSTAT_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_BSWM_CS_u4SS_1BITMASK        ((BswU4)0x00000001UL)            /* System state 1Bit mask */
#define BSW_BSWM_CS_u4SS_ALLBITMSK       ((BswU4)0xFFFFFFFFUL)            /* System State All Bit Mask */
#define BSW_BSWM_CS_u4SS_1BYTEMSK        ((BswU4)0x000000FFUL)            /* System State 1BYTE Mask */

#define BSW_BSWM_CS_u1UPWR_DELIMITE      ((BswU1)32U)                     /* Maximum number of power supplies(Break position) */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void   bsw_bswm_cs_sysst_Init( void );
void   bsw_bswm_cs_sysst_Wakeup( void );
void   bsw_bswm_cs_sysst_UpdtSysStat( void );
void   bsw_bswm_cs_sysst_ChkSysStatRam( void );

/* Dummy Function */
void     bsw_bswm_cs_sysst_SetSystemStatus_dummy( BswConstR uint32* Mask, BswConstR uint32* SysStatus );
void     bsw_bswm_cs_sysst_GetWuSystemStatus( uint32* SysStatus );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
extern BswU4 bsw_bswm_cs_sysst_u4SysStat[];
extern BswU4 bsw_bswm_cs_sysst_u4SysStatMrr[];
extern BswU4 bsw_bswm_cs_sysst_u4SysStTmp[];
extern BswU4 bsw_bswm_cs_sysst_u4SysStTmpMrr[];

extern BswConst BswU4 bsw_bswm_cs_sysst_u4ECUInitPw[];

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
extern void    (* BswConst bsw_bswm_cs_st_ptSetSysStatFn)( BswConstR uint32* Mask, BswConstR uint32* SysStatus );
extern void    (* BswConst bsw_bswm_cs_st_ptGetSysStatFn)( uint32* SysStatus );

#endif  /* BSW_BSWM_CS_SYSSTAT_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/02/22                                             */
/*  v2-0-0          :2021/12/03                                             */
/*  v3-0-0          :2025/02/06                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
