/* bsw_cs_system_h_m10700_v3-0-0                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CS_SYSTEM/HEADER                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef BSW_CS_SYSTEM_H
#define BSW_CS_SYSTEM_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define bsw_cs_DI()                                 \
{                                                   \
    BswU4 bsw_cs_system_u4PreStat;                  \
    bsw_cs_system_u4PreStat = bsw_cs_system_DI();

#define bsw_cs_EI()                                 \
    bsw_cs_system_EI( bsw_cs_system_u4PreStat );    \
}

#define bsw_cs_ImmDI()                              \
{                                                   \
    BswU4 bsw_cs_system_u4PreStat;                  \
    bsw_cs_system_u4PreStat = bsw_cs_system_ImmDI();

#define bsw_cs_ImmEI()                              \
    bsw_cs_system_ImmEI( bsw_cs_system_u4PreStat ); \
}

#define bsw_cs_ComDI()                              \
{                                                   \
    BswU4 bsw_cs_system_u4ComPreStat;               \
    bsw_cs_system_u4ComPreStat = bsw_cs_system_ComDI();

#define bsw_cs_ComEI()                              \
    bsw_cs_system_ComEI( bsw_cs_system_u4ComPreStat ); \
}

#define BSW_CS_SYSTEM_EXCLUSIVE_CS      (0U)
#define BSW_CS_SYSTEM_EXCLUSIVE_SCHM    (1U)
#define BSW_CS_SYSTEM_EXCLUSIVE_SEPSCHM (2U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
#define BswConst    volatile const
#define BswConstR   const

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
BswU4   bsw_cs_system_DI( void );
void    bsw_cs_system_EI( BswU4 u4PreStat );
BswU4   bsw_cs_system_ImmDI( void );
void    bsw_cs_system_ImmEI( BswU4 u4PreStat );
BswU4   bsw_cs_system_ComDI( void );
void    bsw_cs_system_ComEI( BswU4 u4PreStat );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* BSW_CS_SYSTEM_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/02/22                                             */
/*  v1-1-0          :2018/09/18                                             */
/*  v2-0-0          :2020/12/01                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
