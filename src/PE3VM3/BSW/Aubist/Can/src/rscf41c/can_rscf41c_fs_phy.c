/* can_rscf41c_fs_phy_c_m10700_v2-2-2                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/RSCF41C/FS/PHYSICAL/CODE                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <can/common/can_cm_log.h>
#include <can/common/can_syscfg_ext.h>

#include <Can.h>

#include "../../cfg/common/can_cv_cfg.h"
#include "../../cfg/rscf41c/can_rscf41c_cfg_ext.h"
#include "../../cfg/rscf41c/can_rscf41c_cfg.h"

#include <can/common/can_cv_can.h>

#if (CAN_CFG_CAN == CAN_USE)
#include <can/rscf41c/can_rscf41c.h>
#include <can/rscf41c/can_rscf41c_cm_phy.h>
#include <can/common/can_memmap.h>
#include <can/rscf41c/can_rscf41c_tb_phy.h>
#include <can/rscf41c/can_rscf41c_fs.h>
#include <can/rscf41c/can_rscf41c_st.h>
#include <can/rscf41c/can_rscf41c_tx.h>
#include <can/rscf41c/can_rscf41c_rx.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define CAN_FS_u4REGCHK_PTN1            (0xAAAAAAAAUL)
#define CAN_FS_u4REGCHK_PTN2            (0x55555555UL)

#define CAN_FS_REGCHK_STS_WAIT          (0x5AU)
#define CAN_FS_REGCHK_STS_OK            (0xA5U)
#define CAN_FS_REGCHK_STS_NG            (0x96U)
#define CAN_FS_REGCHK_STS_PASS          (0x69U)

#define CAN_FS_MPUFAIL_EXIST            (0x5AU)
#define CAN_FS_MPUFAIL_NONE             (0xA5U)

#define CAN_FS_RAMTEST_OK               (0x5AU)
#define CAN_FS_RAMTEST_NG               (0xA5U)
#define CAN_FS_RAMTEST_FIN              (0x96U)

#define CAN_FS_RAMTEST_DATANUM_MAX      (64U)
#define CAN_FS_RAMTEST_PROTECT_COUNT    (26U)

#define CAN_FS_u4ERRACTIVE              (0x00000000UL)
#define CAN_FS_u4ERRPASSIVE             (0x00000008UL)
#define CAN_FS_u4CMSTSCHK_MASK_ERRSTS   (0x00000018UL)

#define CAN_FS_u4PARAMCHK_CMNCFG_MASK   (0xFFFFFFFFUL)
#define CAN_FS_u4PARAMCHK_CMDCFG_MASK   (0x0F0F1FFFUL)
#define CAN_FS_u4PARAMCHK_CMFDCFG_MASK  (0x00FF0300UL)

#define CAN_FS_ILLEGALINT_ANYCH_USE \
    ( ( (CAN_CFG_CONTROLLER_ACTIVATION_0 == CAN_TRUE) \
     || (CAN_CFG_CONTROLLER_ACTIVATION_1 == CAN_TRUE) \
     || (CAN_CFG_CONTROLLER_ACTIVATION_2 == CAN_TRUE) \
     || (CAN_CFG_CONTROLLER_ACTIVATION_3 == CAN_TRUE) \
     || (CAN_CFG_CONTROLLER_ACTIVATION_4 == CAN_TRUE) \
     || (CAN_CFG_CONTROLLER_ACTIVATION_5 == CAN_TRUE) \
     || (CAN_CFG_CONTROLLER_ACTIVATION_6 == CAN_TRUE) \
     || (CAN_CFG_CONTROLLER_ACTIVATION_7 == CAN_TRUE) ) ? CAN_USE : CAN_NOUSE )


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#if (CAN_FS_ILLEGALINT_ANYCH_USE == CAN_USE)
static void  Can_fs_IllegalInterrupt( uint8 u1Controller );
#endif /* (CAN_FS_ILLEGALINT_ANYCH_USE == CAN_USE) */
static uint8 Can_fs_RAMTest( uint8 u1Time );
static uint8 Can_fs_RAMTestPage( uint16 u2TargetPage, uint8 u1ElmNum );
static uint8 Can_fs_RAMTestEnable( void );
static uint8 Can_fs_RAMTestDisable( void );


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
static uint8 Can_fs_u1RegChkStatus[ CAN_CFG_CONTROLLERNUM_MAX ];

static uint8 Can_fs_u1MpuFail[ CAN_CFG_CONTROLLERNUM_MAX ];


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Can_fs_ChkBusOff                                         */
/* Description   | Controller Bus Off Detection Check                       */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/* Return Value  | uint8                                                    */
/*               |   CAN_NONE                                               */
/*               |   CAN_EXIST                                              */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
uint8
Can_fs_ChkBusOff( uint8 u1Controller )
{
    CanConst CanTbChRegType *        ptChReg;
    uint8                            u1Ret;

    u1Ret = (uint8)CAN_NONE;

    ptChReg = &Can_tb_stChReg[ u1Controller ];

    if ( ( *(ptChReg->ptu4CmERFL) & CAN_u4CMERFL_BOEF_MSK ) == CAN_u4CMERFL_BOEF_BUSOFF )
    {
        *(ptChReg->ptu4CmERFL) = CAN_u4CMERFL_BOEF_CLR;

        Can_fs_BusOffInd( u1Controller );

        u1Ret = (uint8)CAN_EXIST;
    }

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_fs_BusOffRecovery                                    */
/* Description   | Controller Bus Off Automatic Recovery                    */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
void
Can_fs_BusOffRecovery( uint8 u1Controller )
{
}


/****************************************************************************/
/* Function Name | Can_fs_ChkReg                                            */
/* Description   | MBOX Register Stuck Check                                */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/*               | uint8 u1Time                                             */
/* Return Value  | uint8                                                    */
/*               |   CAN_FS_REGCHK_NONE                                     */
/*               |   CAN_FS_REGCHK_EXIST                                    */
/*               |   CAN_FS_REGCHK_OPT_EXIST                                */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
uint8
Can_fs_ChkReg( uint8 u1Controller, uint8 u1Time )
{
    uint8  u1RAMTestResult;
    uint8  u1RegChkStatus;
    uint8  u1Idx;
    uint8  u1CtrlNum;
    uint8  u1Ret;

    u1Ret = (uint8)CAN_FS_REGCHK_EXIST;

    u1RegChkStatus = Can_fs_u1RegChkStatus[ u1Controller ];
    if ( u1RegChkStatus == (uint8)CAN_FS_REGCHK_STS_WAIT )
    {
        u1CtrlNum = Can_tb_u1CtrlNum;
        for ( u1Idx = (uint8)0U; u1Idx < u1CtrlNum; u1Idx++ )
        {
            Can_fs_u1RegChkStatus[ u1Idx ] = (uint8)CAN_FS_REGCHK_STS_PASS;
        }
        Can_fs_u1RegChkStatus[ u1Controller ] = (uint8)CAN_FS_REGCHK_STS_WAIT;

        u1RAMTestResult = Can_fs_RAMTest( u1Time );
        if ( u1RAMTestResult == (uint8)CAN_FS_RAMTEST_OK )
        {
            u1Ret = (uint8)CAN_FS_REGCHK_NONE;
        }
        else if ( u1RAMTestResult == (uint8)CAN_FS_RAMTEST_FIN )
        {
            for ( u1Idx = (uint8)0U; u1Idx < u1CtrlNum; u1Idx++ )
            {
                Can_fs_u1RegChkStatus[ u1Idx ] = (uint8)CAN_FS_REGCHK_STS_OK;
            }
            u1Ret = (uint8)CAN_FS_REGCHK_NONE;
        }
        else
        {
            for ( u1Idx = (uint8)0U; u1Idx < u1CtrlNum; u1Idx++ )
            {
                Can_fs_u1RegChkStatus[ u1Idx ] = (uint8)CAN_FS_REGCHK_STS_NG;
            }
        }
    }
    else if ( u1RegChkStatus == (uint8)CAN_FS_REGCHK_STS_PASS )
    {
        u1Ret = (uint8)CAN_FS_REGCHK_NONE;
    }
    else if ( u1RegChkStatus == (uint8)CAN_FS_REGCHK_STS_OK )
    {
        u1Ret = (uint8)CAN_FS_REGCHK_NONE;
    }
    else
    {
        u1CtrlNum = Can_tb_u1CtrlNum;
        for ( u1Idx = (uint8)0U; u1Idx < u1CtrlNum; u1Idx++ )
        {
            Can_fs_u1RegChkStatus[ u1Idx ] = (uint8)CAN_FS_REGCHK_STS_NG;
        }
    }

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_fs_CheckMpu                                          */
/* Description   | Controller MPU Fail Check                                */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/* Return Value  | uint8                                                    */
/*               |   CAN_NONE                                               */
/*               |   CAN_EXIST                                              */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
uint8
Can_fs_CheckMpu( uint8 u1Controller )
{
    uint8  u1BRSUse;
    uint8  u1CheckData;
    uint8  u1CheckDataLo;
    uint8  u1CheckDataHi;
    uint8  u1Ctrl;
    uint8  u1CtrlNum;
    uint8  u1Ret;

    u1Ret = (uint8)CAN_NONE;

    if ( Can_fs_u1MpuFail[ u1Controller ] != (uint8)CAN_FS_MPUFAIL_NONE )
    {
        Can_fs_u1MpuFail[ u1Controller ] = (uint8)CAN_FS_MPUFAIL_NONE;
        u1Ret = (uint8)CAN_EXIST;
    }

    u1BRSUse = Can_st_u1BRSUse[ u1Controller ];
    u1CheckDataLo = (uint8)( u1BRSUse & (uint8)CAN_RAMCHK_MASK_LOWERHALFBYTE );
    u1CheckDataHi = (uint8)( u1BRSUse >> CAN_SFT_4 );
    u1CheckData = u1CheckDataLo + u1CheckDataHi;
    if ( u1CheckData != (uint8)CAN_RAMCHK_VALUE_LOWERHALFBYTE )
    {
        u1Ret = (uint8)CAN_EXIST;
    }

    if ( ((*(Can_tb_stGlobalReg.ptu4GFCMC)  & CAN_u4GFCMC_USEDBIT_MSK)  != CAN_u4GFCMC_INIT )
    ||   ((*(Can_tb_stGlobalReg.ptu4GFTBAC) & CAN_u4GFTBAC_USEDBIT_MSK) != CAN_u4GFTBAC_INIT) )
    {
        u1Ret = (uint8)CAN_EXIST;

        u1CtrlNum = Can_tb_u1CtrlNum;
        for ( u1Ctrl = (uint8)0U; u1Ctrl < u1CtrlNum; u1Ctrl++ )
        {
            if ( u1Ctrl != u1Controller )
            {
                Can_st_StopInd( u1Ctrl );

                Can_fs_MpuFailInd( u1Ctrl );
            }
        }
    }

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_IllegalInterrupt_0                                   */
/* Description   | Illegal Interrupt                                        */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if (CAN_CFG_CONTROLLER_ACTIVATION_0 == CAN_TRUE)
void
Can_IllegalInterrupt_0( void )
{
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_0 );
#if (CAN_CFG_CORE != CAN_G4MH)
    #if (CAN_CFG_CONTROLLER_ACTIVATION_1 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_1 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_1 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_2 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_2 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_2 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_3 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_3 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_3 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_4 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_4 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_4 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_5 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_5 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_5 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_6 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_6 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_6 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_7 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_7 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_7 == CAN_TRUE) */
#endif /* (CAN_CFG_CORE != CAN_G4MH) */
}
#endif /* (CAN_CFG_CONTROLLER_ACTIVATION_0 == CAN_TRUE) */


/****************************************************************************/
/* Function Name | Can_IllegalInterrupt_1                                   */
/* Description   | Illegal Interrupt                                        */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if (CAN_CFG_CONTROLLER_ACTIVATION_1 == CAN_TRUE)
void
Can_IllegalInterrupt_1( void )
{
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_1 );
#if (CAN_CFG_CORE != CAN_G4MH)
    #if (CAN_CFG_CONTROLLER_ACTIVATION_0 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_0 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_0 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_2 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_2 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_2 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_3 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_3 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_3 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_4 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_4 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_4 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_5 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_5 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_5 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_6 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_6 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_6 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_7 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_7 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_7 == CAN_TRUE) */
#endif /* (CAN_CFG_CORE != CAN_G4MH) */
}
#endif /* (CAN_CFG_CONTROLLER_ACTIVATION_1 == CAN_TRUE) */


/****************************************************************************/
/* Function Name | Can_IllegalInterrupt_2                                   */
/* Description   | Illegal Interrupt                                        */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if (CAN_CFG_CONTROLLER_ACTIVATION_2 == CAN_TRUE)
void
Can_IllegalInterrupt_2( void )
{
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_2 );
#if (CAN_CFG_CORE != CAN_G4MH)
    #if (CAN_CFG_CONTROLLER_ACTIVATION_0 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_0 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_0 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_1 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_1 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_1 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_3 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_3 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_3 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_4 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_4 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_4 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_5 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_5 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_5 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_6 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_6 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_6 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_7 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_7 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_7 == CAN_TRUE) */
#endif /* (CAN_CFG_CORE != CAN_G4MH) */
}
#endif /* (CAN_CFG_CONTROLLER_ACTIVATION_2 == CAN_TRUE) */


/****************************************************************************/
/* Function Name | Can_IllegalInterrupt_3                                   */
/* Description   | Illegal Interrupt                                        */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if (CAN_CFG_CONTROLLER_ACTIVATION_3 == CAN_TRUE)
void
Can_IllegalInterrupt_3( void )
{
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_3 );
#if (CAN_CFG_CORE != CAN_G4MH)
    #if (CAN_CFG_CONTROLLER_ACTIVATION_0 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_0 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_0 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_1 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_1 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_1 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_2 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_2 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_2 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_4 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_4 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_4 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_5 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_5 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_5 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_6 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_6 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_6 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_7 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_7 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_7 == CAN_TRUE) */
#endif /* (CAN_CFG_CORE != CAN_G4MH) */
}
#endif /* (CAN_CFG_CONTROLLER_ACTIVATION_3 == CAN_TRUE) */


/****************************************************************************/
/* Function Name | Can_IllegalInterrupt_4                                   */
/* Description   | Illegal Interrupt                                        */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if (CAN_CFG_CONTROLLER_ACTIVATION_4 == CAN_TRUE)
void
Can_IllegalInterrupt_4( void )
{
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_4 );
#if (CAN_CFG_CORE != CAN_G4MH)
    #if (CAN_CFG_CONTROLLER_ACTIVATION_0 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_0 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_0 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_1 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_1 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_1 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_2 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_2 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_2 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_3 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_3 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_3 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_5 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_5 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_5 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_6 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_6 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_6 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_7 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_7 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_7 == CAN_TRUE) */
#endif /* (CAN_CFG_CORE != CAN_G4MH) */
}
#endif /* (CAN_CFG_CONTROLLER_ACTIVATION_4 == CAN_TRUE) */


/****************************************************************************/
/* Function Name | Can_IllegalInterrupt_5                                   */
/* Description   | Illegal Interrupt                                        */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if (CAN_CFG_CONTROLLER_ACTIVATION_5 == CAN_TRUE)
void
Can_IllegalInterrupt_5( void )
{
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_5 );
#if (CAN_CFG_CORE != CAN_G4MH)
    #if (CAN_CFG_CONTROLLER_ACTIVATION_0 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_0 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_0 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_1 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_1 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_1 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_2 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_2 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_2 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_3 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_3 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_3 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_4 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_4 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_4 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_6 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_6 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_6 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_7 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_7 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_7 == CAN_TRUE) */
#endif /* (CAN_CFG_CORE != CAN_G4MH) */
}
#endif /* (CAN_CFG_CONTROLLER_ACTIVATION_5 == CAN_TRUE) */


/****************************************************************************/
/* Function Name | Can_IllegalInterrupt_6                                   */
/* Description   | Illegal Interrupt                                        */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if (CAN_CFG_CONTROLLER_ACTIVATION_6 == CAN_TRUE)
void
Can_IllegalInterrupt_6( void )
{
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_6 );
#if (CAN_CFG_CORE != CAN_G4MH)
    #if (CAN_CFG_CONTROLLER_ACTIVATION_0 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_0 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_0 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_1 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_1 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_1 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_2 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_2 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_2 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_3 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_3 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_3 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_4 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_4 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_4 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_5 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_5 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_5 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_7 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_7 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_7 == CAN_TRUE) */
#endif /* (CAN_CFG_CORE != CAN_G4MH) */
}
#endif /* (CAN_CFG_CONTROLLER_ACTIVATION_6 == CAN_TRUE) */


/****************************************************************************/
/* Function Name | Can_IllegalInterrupt_7                                   */
/* Description   | Illegal Interrupt                                        */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if (CAN_CFG_CONTROLLER_ACTIVATION_7 == CAN_TRUE)
void
Can_IllegalInterrupt_7( void )
{
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_7 );
#if (CAN_CFG_CORE != CAN_G4MH)
    #if (CAN_CFG_CONTROLLER_ACTIVATION_0 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_0 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_0 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_1 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_1 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_1 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_2 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_2 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_2 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_3 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_3 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_3 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_4 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_4 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_4 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_5 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_5 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_5 == CAN_TRUE) */
    #if (CAN_CFG_CONTROLLER_ACTIVATION_6 == CAN_TRUE)
    Can_fs_IllegalInterrupt( (uint8)CAN_CONTROLLER_6 );
    #endif /* (CAN_CFG_CONTROLLER_ACTIVATION_6 == CAN_TRUE) */
#endif /* (CAN_CFG_CORE != CAN_G4MH) */
}
#endif /* (CAN_CFG_CONTROLLER_ACTIVATION_7 == CAN_TRUE) */


/****************************************************************************/
/* Function Name | Can_IllegalInterrupt_Global                              */
/* Description   | Illegal Interrupt(Global)                                */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
void
Can_IllegalInterrupt_Global( void )
{
    volatile uint32 *   ptRFSTS;
    volatile uint32     u4DummyRead;
    uint8               u1RxFifo;
    uint8               u1Controller;
    uint8               u1CtrlNum;

    ptRFSTS = Can_tb_stGlobalReg.ptu4RFSTS;
    for ( u1RxFifo = (uint8)0U; u1RxFifo < (uint8)CAN_NUM_FIFO_RCV; u1RxFifo++ )
    {
        ptRFSTS[ u1RxFifo ] = CAN_u4RFSTS_CLEARALL;
    }

    *(Can_tb_stGlobalReg.ptu4GERFL) = CAN_u4GERFL_CLEARALL;

    u1CtrlNum = Can_tb_u1CtrlNum;
    for ( u1Controller = (uint8)0U; u1Controller < u1CtrlNum; u1Controller++ )
    {
        Can_fs_u1MpuFail[ u1Controller ] = (uint8)CAN_FS_MPUFAIL_EXIST;
    }

    u4DummyRead = *( Can_tb_stGlobalReg.ptu4GSTS );
#if (CAN_CFG_CORE == CAN_G4MH)
    Can_tb_SYNCP();
#endif /* (CAN_CFG_CORE == CAN_G4MH) */
}


/****************************************************************************/
/* Function Name | Can_fs_ResetInterrupt                                    */
/* Description   | Interrupt Reset                                          */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if ( (CAN_TX_TXFINISH_ANYCH_USE == CAN_USE) || (CAN_RX_RXFINISH_ANYCH_USE == CAN_USE) )
void
Can_fs_ResetInterrupt( uint8 u1Controller )
{
    CanConst CanTbChRegType *        ptChReg;
    CanConst CanTbSetRSCANRegType *  ptSetRSCANReg;
    CanConst CanTbTxMbBitType *      ptTxMbBit;
    uint32                           u4TxUseBit;
    uint32                           u4TmpTxIntrBitLo;
    uint32                           u4TmpTxIntrBitHi;
    uint8                            u1Idx;

    ptChReg = &Can_tb_stChReg[ u1Controller ];
    ptSetRSCANReg = &Can_tb_stSetRSCANReg[ u1Controller ];

    ptTxMbBit = &Can_tb_stTxMbBit[ u1Controller ];
    u4TxUseBit = ptTxMbBit->u4TxIntrBit[CAN_IDX0] | ptTxMbBit->u4TxPollBit[CAN_IDX0];

    for ( u1Idx = (uint8)0U; u1Idx < (uint8)CAN_NUM_BUF_SND_PER_REG; u1Idx++ )
    {
        if( (u4TxUseBit & (uint32)(CAN_u4BIT0 << u1Idx)) == CAN_u4BIT_NONE )
        {
            ptChReg->ptu1TMSTS[ u1Idx ] = CAN_u1TMSTS_TMTRF_CLR;
        }
    }

    u4TxUseBit = ptTxMbBit->u4TxIntrBit[CAN_IDX1] | ptTxMbBit->u4TxPollBit[CAN_IDX1];
    for ( u1Idx = (uint8)CAN_NUM_BUF_SND_PER_REG; u1Idx < (uint8)CAN_NUM_BUF_SND_PER_CH; u1Idx++ )
    {
        if( (u4TxUseBit & (uint32)(CAN_u4BIT0 << (u1Idx & (uint8)CAN_MBSFT_MSK))) == CAN_u4BIT_NONE )
        {
            ptChReg->ptu1TMSTS[ u1Idx ] = CAN_u1TMSTS_TMTRF_CLR;
        }
    }

    ptChReg->ptu4CFSTS[ CAN_TRX_FIFO_0 ] = ptSetRSCANReg->u4CFSTSConf;
    ptChReg->ptu4CFSTS[ CAN_TRX_FIFO_1 ] = CAN_u4CFSTS_CLEARALL;
    ptChReg->ptu4CFSTS[ CAN_TRX_FIFO_2 ] = CAN_u4CFSTS_CLEARALL;

    *(ptChReg->ptu4TXQSTS0) = CAN_u4TXQSTS0_CLEARALL;
    *(ptChReg->ptu4TXQSTS1) = CAN_u4TXQSTS1_CLEARALL;
    *(ptChReg->ptu4TXQSTS2) = CAN_u4TXQSTS2_CLEARALL;
    *(ptChReg->ptu4TXQSTS3) = CAN_u4TXQSTS3_CLEARALL;

    *(ptChReg->ptu4THLSTS) = CAN_u4THLSTS_CLEARALL;

    *(ptChReg->ptu4CmERFL) = CAN_u4CMERFL_CLEARALL | CAN_u4CMERFL_BOEF_MSK;

    *(ptChReg->ptu4CmFDSTS) = CAN_u4CMFDSTS_CLEARALL;

    u4TmpTxIntrBitLo = Can_tb_stTxMbBit[ u1Controller ].u4TxIntrBit[CAN_IDX0];
    u4TmpTxIntrBitHi = Can_tb_stTxMbBit[ u1Controller ].u4TxIntrBit[CAN_IDX1];
    if ( ( ( ptChReg->ptu4TMIEC[CAN_IDX0])                                    != u4TmpTxIntrBitLo )
    ||   ( ( ptChReg->ptu4TMIEC[CAN_IDX1])                                    != u4TmpTxIntrBitHi )
    ||   ( ( *(ptChReg->ptu4CmCTR) & CAN_u4CMCTR_USEDBIT_MSK )                != ( ptSetRSCANReg->u4CmCTRConf | CAN_u4CMCTR_CHMDC_COMM_SET ) )
    ||   ( ( ptChReg->ptu4CFCC[ CAN_TRX_FIFO_0 ] & CAN_u4CFCC_USEDBIT_MSK )   != ptSetRSCANReg->u4CFCC0Conf )
    ||   ( ( ptChReg->ptu4CFCC[ CAN_TRX_FIFO_1 ] & CAN_u4CFCC_USEDBIT_MSK )   != ptSetRSCANReg->u4CFCC1Conf )
    ||   ( ( ptChReg->ptu4CFCC[ CAN_TRX_FIFO_2 ] & CAN_u4CFCC_USEDBIT_MSK )   != ptSetRSCANReg->u4CFCC2Conf )
    ||   ( ( ptChReg->ptu4CFCCE[ CAN_TRX_FIFO_0 ] & CAN_u4CFCCE_USEDBIT_MSK ) != CAN_u4CFCCE_INIT )
    ||   ( ( ptChReg->ptu4CFCCE[ CAN_TRX_FIFO_1 ] & CAN_u4CFCCE_USEDBIT_MSK ) != CAN_u4CFCCE_INIT )
    ||   ( ( ptChReg->ptu4CFCCE[ CAN_TRX_FIFO_2 ] & CAN_u4CFCCE_USEDBIT_MSK ) != CAN_u4CFCCE_INIT )
    ||   ( ( *(ptChReg->ptu4TXQCC0) & CAN_u4TXQCC0_USEDBIT_MSK )              != CAN_u4TXQCC0_INIT )
    ||   ( ( *(ptChReg->ptu4TXQCC1) & CAN_u4TXQCC1_USEDBIT_MSK )              != CAN_u4TXQCC1_INIT )
    ||   ( ( *(ptChReg->ptu4TXQCC2) & CAN_u4TXQCC2_USEDBIT_MSK )              != CAN_u4TXQCC2_INIT )
    ||   ( ( *(ptChReg->ptu4TXQCC3) & CAN_u4TXQCC3_USEDBIT_MSK )              != CAN_u4TXQCC3_INIT )
    ||   ( ( *(ptChReg->ptu4THLCC) & CAN_u4THLCC_USEDBIT_MSK )                != CAN_u4THLCC_INIT ) )
    {
        for ( u1Idx = (uint8)0U; u1Idx < (uint8)CAN_NUM_BUF_SND_PER_CH; u1Idx++ )
        {
#if (CAN_CFG_TXBUF_NUM == 48U)
            if ( ( u1Idx < (uint8)CAN_MB016 )
            ||   ( u1Idx > (uint8)CAN_MB031 ) )
#endif /* (CAN_CFG_TXBUF_NUM == 48U) */
            {
                ptChReg->ptu1TMSTS[ u1Idx ] = CAN_u1TMSTS_TMTRF_CLR;
            }
        }

        ptChReg->ptu4CFSTS[ CAN_TRX_FIFO_0 ] = CAN_u4CFSTS_CLEARALL;

        *(ptChReg->ptu4CmERFL) = CAN_u4CMERFL_CLEARALL;

        Can_fs_u1MpuFail[ u1Controller ] = (uint8)CAN_FS_MPUFAIL_EXIST;
    }
}
#endif /* ( (CAN_TX_TXFINISH_ANYCH_USE == CAN_USE) || (CAN_RX_RXFINISH_ANYCH_USE == CAN_USE) ) */


/****************************************************************************/
/* Function Name | Can_fs_DisableInterrupt                                  */
/* Description   | Interrupt Disable                                        */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if ( (CAN_TX_TXFINISH_ANYCH_USE == CAN_USE) || (CAN_RX_RXFINISH_ANYCH_USE == CAN_USE) || (CAN_FS_ILLEGALINT_ANYCH_USE == CAN_USE) )
void
Can_fs_DisableInterrupt( uint8 u1Controller )
{
    CanConst CanTbChRegType *        ptChReg;
    uint8                            u1Idx;

    ptChReg = &Can_tb_stChReg[ u1Controller ];

    for ( u1Idx = (uint8)0U; u1Idx < (uint8)CAN_NUM_BUF_SND_PER_CH; u1Idx++ )
    {
#if (CAN_CFG_TXBUF_NUM == 48U)
        if ( ( u1Idx < (uint8)CAN_MB016 )
        ||   ( u1Idx > (uint8)CAN_MB031 ) )
#endif /* (CAN_CFG_TXBUF_NUM == 48U) */
        {
            ptChReg->ptu1TMSTS[ u1Idx ] = CAN_u1TMSTS_TMTRF_CLR;
        }
    }

    ptChReg->ptu4CFSTS[ CAN_TRX_FIFO_0 ] = CAN_u4CFSTS_CLEARALL;
    ptChReg->ptu4CFSTS[ CAN_TRX_FIFO_1 ] = CAN_u4CFSTS_CLEARALL;
    ptChReg->ptu4CFSTS[ CAN_TRX_FIFO_2 ] = CAN_u4CFSTS_CLEARALL;

    *(ptChReg->ptu4TXQSTS0) = CAN_u4TXQSTS0_CLEARALL;
    *(ptChReg->ptu4TXQSTS1) = CAN_u4TXQSTS1_CLEARALL;
    *(ptChReg->ptu4TXQSTS2) = CAN_u4TXQSTS2_CLEARALL;
    *(ptChReg->ptu4TXQSTS3) = CAN_u4TXQSTS3_CLEARALL;

    *(ptChReg->ptu4THLSTS) = CAN_u4THLSTS_CLEARALL;

    *(ptChReg->ptu4CmERFL) = CAN_u4CMERFL_CLEARALL;

    *(ptChReg->ptu4CmFDSTS) = CAN_u4CMFDSTS_CLEARALL;

    Can_fs_u1MpuFail[ u1Controller ] = (uint8)CAN_FS_MPUFAIL_EXIST;
}
#endif /* ( (CAN_TX_TXFINISH_ANYCH_USE == CAN_USE) || (CAN_RX_RXFINISH_ANYCH_USE == CAN_USE) || (CAN_FS_ILLEGALINT_ANYCH_USE == CAN_USE) ) */


/****************************************************************************/
/* Function Name | Can_fs_GetErrorStatus                                    */
/* Description   | Can Protocol Error Status Get                            */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/* Return Value  | uint8                                                    */
/*               |   CAN_ERRST_NOT_OK                                       */
/*               |   CAN_ERRST_ERROR_ACTIVE                                 */
/*               |   CAN_ERRST_ERROR_PASSIVE                                */
/*               |   CAN_ERRST_BUS_OFF                                      */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
uint8
Can_fs_GetErrorStatus( uint8 u1Controller )
{
    CanConst CanTbChRegType *      ptChReg;
    uint32                         u4CMSTSTmp;
    uint8                          u1Ret;

    ptChReg = &Can_tb_stChReg[ u1Controller ];
    u4CMSTSTmp = *(ptChReg->ptu4CmSTS) & CAN_FS_u4CMSTSCHK_MASK_ERRSTS;

    if ( u4CMSTSTmp == CAN_FS_u4ERRACTIVE )
    {
        u1Ret = (uint8)CAN_ERRST_ERROR_ACTIVE;
    }
    else if ( u4CMSTSTmp == CAN_FS_u4ERRPASSIVE )
    {
        u1Ret = (uint8)CAN_ERRST_ERROR_PASSIVE;
    }
    else
    {
        u1Ret = (uint8)CAN_ERRST_BUS_OFF;
    }

    return (u1Ret);
}


/****************************************************************************/
/* Function Name | Can_fs_PhyInit                                           */
/* Description   | Fail Safe Function(MPU Reliance) Initialization          */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
void
Can_fs_PhyInit( void )
{
    uint8    u1Controller;
    uint8    u1CtrlNum;

    u1CtrlNum = Can_tb_u1CtrlNum;
    for ( u1Controller = (uint8)0U; u1Controller < u1CtrlNum; u1Controller++ )
    {
        Can_fs_u1RegChkStatus[ u1Controller ] = (uint8)CAN_FS_REGCHK_STS_WAIT;

        Can_fs_u1MpuFail[ u1Controller ] = (uint8)CAN_FS_MPUFAIL_NONE;
    }
}


/****************************************************************************/
/* Function Name | Can_fs_ChkParameter                                      */
/* Description   | Communication Parameter Check                            */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/* Return Value  | uint8                                                    */
/*               |   CAN_NONE                                               */
/*               |   CAN_EXIST                                              */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
uint8
Can_fs_ChkParameter( uint8 u1Controller )
{
#if (CAN_CFG_PARAM_CHECK == CAN_USE)
    CanConst CanTbChRegType *        ptChReg;
    CanConst CanTbSetRSCANRegType *  ptSetRSCANReg;
    uint32                           u4DCS;
    uint32                           u4DCSConfTmp;
    uint32                           u4CmNCFG;
    uint32                           u4CmNCFGConfTmp;
    uint32                           u4CmDCFG;
    uint32                           u4CmDCFGConfTmp;
    uint32                           u4CmFDCFG;
    uint32                           u4CmFDCFGConfTmp;
#endif /* (CAN_CFG_PARAM_CHECK == CAN_USE) */
    uint8                            u1Ret;

    u1Ret = (uint8)CAN_NONE;

#if (CAN_CFG_PARAM_CHECK == CAN_USE)
    u4DCS        = *( Can_tb_stGlobalReg.ptu4GCFG ) & CAN_u4GCFG_DCS_MSK;
    u4DCSConfTmp = Can_tb_u4GCFGConf & CAN_u4GCFG_DCS_MSK;
    if ( u4DCS != u4DCSConfTmp )
    {
        u1Ret = (uint8)CAN_EXIST;
    }

    ptChReg       = &Can_tb_stChReg[ u1Controller ];
    ptSetRSCANReg = &Can_tb_stSetRSCANReg[ u1Controller ];

    u4CmNCFG        = *(ptChReg->ptu4CmNCFG) & CAN_FS_u4PARAMCHK_CMNCFG_MASK;
    u4CmNCFGConfTmp = ptSetRSCANReg->u4CmNCFGConf & CAN_FS_u4PARAMCHK_CMNCFG_MASK;
    if( u4CmNCFG != u4CmNCFGConfTmp )
    {
        u1Ret = (uint8)CAN_EXIST;
    }

    u4CmDCFG        = *(ptChReg->ptu4CmDCFG) & CAN_FS_u4PARAMCHK_CMDCFG_MASK;
    u4CmDCFGConfTmp = ptSetRSCANReg->u4CmDCFGConf & CAN_FS_u4PARAMCHK_CMDCFG_MASK;

    u4CmFDCFG        = *(ptChReg->ptu4CmFDCFG) & CAN_FS_u4PARAMCHK_CMFDCFG_MASK;
    u4CmFDCFGConfTmp = ptSetRSCANReg->u4CmFDCFGConf & CAN_FS_u4PARAMCHK_CMFDCFG_MASK;
    if( ( u4CmDCFG  != u4CmDCFGConfTmp  )
    ||  ( u4CmFDCFG != u4CmFDCFGConfTmp ) )
    {
        u1Ret = (uint8)CAN_EXIST;
    }
#endif /* (CAN_CFG_PARAM_CHECK == CAN_USE) */

    return (u1Ret);
}


/****************************************************************************/
/* Function Name | Can_fs_PhyPrepChkRegRetry                                */
/* Description   | Phy Layer Register Stuck Check Retry Preparation Process */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
void
Can_fs_PhyPrepChkRegRetry( uint8 u1Controller )
{
    uint8    u1RegChkStatus;
    uint8    u1Idx;
    uint8    u1CtrlNum;

    u1RegChkStatus = Can_fs_u1RegChkStatus[ u1Controller ];
    if ( ( u1RegChkStatus == (uint8)CAN_FS_REGCHK_STS_WAIT )
    ||   ( u1RegChkStatus == (uint8)CAN_FS_REGCHK_STS_NG   ) )
    {
        u1CtrlNum = Can_tb_u1CtrlNum;
        for ( u1Idx = (uint8)0U; u1Idx < u1CtrlNum; u1Idx++ )
        {
            Can_fs_u1RegChkStatus[ u1Idx ] = (uint8)CAN_FS_REGCHK_STS_PASS;
        }
        Can_fs_u1RegChkStatus[ u1Controller ] = (uint8)CAN_FS_REGCHK_STS_WAIT;
    }
}


/****************************************************************************/
/* Function Name | Can_fs_MpuFailInd                                        */
/* Description   | MPU Fail Detection Notification                          */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
void
Can_fs_MpuFailInd( uint8 u1Controller )
{
    Can_fs_u1MpuFail[ u1Controller ] = (uint8)CAN_FS_MPUFAIL_EXIST;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Can_fs_IllegalInterrupt                                  */
/* Description   | Illegal Interrupt Common Process                         */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Controller                                       */
/* Return Value  | void                                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
#if (CAN_FS_ILLEGALINT_ANYCH_USE == CAN_USE)
static void
Can_fs_IllegalInterrupt( uint8 u1Controller )
{
    volatile uint32                      u4DummyRead;

    Can_fs_DisableInterrupt( u1Controller );

    u4DummyRead = *( Can_tb_stGlobalReg.ptu4GSTS );
#if (CAN_CFG_CORE == CAN_G4MH)
    Can_tb_SYNCP();
#endif /* (CAN_CFG_CORE == CAN_G4MH) */
}
#endif /* (CAN_FS_ILLEGALINT_ANYCH_USE == CAN_USE) */


/****************************************************************************/
/* Function Name | Can_fs_RAMTest                                           */
/* Description   | RAM Test                                                 */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint8 u1Time                                             */
/* Return Value  | uint8                                                    */
/*               |   CAN_FS_RAMTEST_OK                                      */
/*               |   CAN_FS_RAMTEST_NG                                      */
/*               |   CAN_FS_RAMTEST_FIN                                     */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
static uint8
Can_fs_RAMTest( uint8 u1Time )
{
    uint16 u2TargetPage;
    uint16 u2StartPage;
    uint16 u2ChkPage;
    uint16 u2LastPage;
    uint16 u2Cnt;
    uint8  u1RAMTestModeChgRet;
    uint8  u1Ret;

    u1Ret = (uint8)CAN_FS_RAMTEST_OK;

    u1RAMTestModeChgRet = Can_fs_RAMTestEnable();
    if ( u1RAMTestModeChgRet == (uint8)CAN_PROC_OK )
    {
        u2StartPage = Can_tb_stCheckStuckPara[ u1Time ].u2StChkStart;
        u2ChkPage   = Can_tb_stCheckStuckPara[ u1Time ].u2StChkPage;

        for ( u2Cnt = (uint16)0U; ( ( u2Cnt < u2ChkPage ) && ( u1Ret == (uint8)CAN_FS_RAMTEST_OK ) ); u2Cnt++ )
        {
            u2TargetPage = (uint16)( u2StartPage + u2Cnt );
            u1Ret        = Can_fs_RAMTestPage( u2TargetPage, (uint8)CAN_FS_RAMTEST_DATANUM_MAX );
        }

        u2TargetPage = (uint16)( u2StartPage + u2ChkPage );
        u2LastPage   = Can_tb_u2LastTestpage;
        if ( u2TargetPage == u2LastPage )
        {
            if ( u1Ret == (uint8)CAN_FS_RAMTEST_OK )
            {
                u1Ret = Can_fs_RAMTestPage( u2TargetPage, Can_tb_u1LastTestpageRegNum );
                if ( u1Ret == (uint8)CAN_FS_RAMTEST_OK )
                {
                    u1Ret = (uint8)CAN_FS_RAMTEST_FIN;
                }
            }
        }
    }
    else
    {
        u1Ret = (uint8)CAN_FS_RAMTEST_NG;
    }

    u1RAMTestModeChgRet = Can_fs_RAMTestDisable();
    if ( u1RAMTestModeChgRet != (uint8)CAN_PROC_OK )
    {
        u1Ret = (uint8)CAN_FS_RAMTEST_NG;
    }

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_fs_RAMTestPage                                       */
/* Description   | Page Specify RAM Test                                    */
/* Preconditions | See Design Documents                                     */
/* Parameters    | uint16 u2TargetPage                                      */
/*               | uint8  u1ElmNum                                          */
/* Return Value  | uint8                                                    */
/*               |   CAN_FS_RAMTEST_OK                                      */
/*               |   CAN_FS_RAMTEST_NG                                      */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
static uint8
Can_fs_RAMTestPage( uint16 u2TargetPage, uint8 u1ElmNum )
{
    volatile uint32 *   ptRDATA;
    uint8               u1Idx;
    uint8               u1Ret;

    *(Can_tb_stGlobalReg.ptu4GTSTCFG) = (uint32)( ( (uint32)u2TargetPage << CAN_SFT_16 ) & CAN_u4GTSTCFG_RTMPS_MSK ) | CAN_u4GTSTCFG_PNFS_AFL_MRAM;

    u1Ret = (uint8)CAN_FS_RAMTEST_OK;

    for ( u1Idx = (uint8)0U; ( ( u1Idx < u1ElmNum ) && ( u1Ret == (uint8)CAN_FS_RAMTEST_OK ) ); u1Idx++ )
    {
        ptRDATA = &(Can_tb_stGlobalReg.ptu4RPGACC[ u1Idx ]);

        *ptRDATA = CAN_FS_u4REGCHK_PTN1;

        if ( *ptRDATA != CAN_FS_u4REGCHK_PTN1 )
        {
            u1Ret = (uint8)CAN_FS_RAMTEST_NG;
        }
        else
        {
            *ptRDATA = CAN_FS_u4REGCHK_PTN2;

            if ( *ptRDATA != CAN_FS_u4REGCHK_PTN2 )
            {
                u1Ret = (uint8)CAN_FS_RAMTEST_NG;
            }
            else
            {
                *ptRDATA = CAN_u4BIT_NONE;
            }
        }
    }
    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_fs_RAMTestEnable                                     */
/* Description   | RAM Test Enable Set                                      */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | uint8                                                    */
/*               |   CAN_PROC_OK                                            */
/*               |   CAN_PROC_NG                                            */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
static uint8
Can_fs_RAMTestEnable( void )
{
    uint8  u1CheckCount;
    uint8  u1Ret;

    u1Ret = (uint8)CAN_PROC_NG;

    Can_st_GlobalMode_Any2Reset();

    Can_st_GlobalMode_Reset2Test();

    if ( ( *(Can_tb_stGlobalReg.ptu4GSTS) & CAN_u4GSTS_MODEALL_MSK ) == CAN_u4GSTS_GMODE_TEST )
    {
        for ( u1CheckCount = (uint8)0U; ( ( u1CheckCount < (uint8)CAN_FS_RAMTEST_PROTECT_COUNT ) && ( u1Ret != (uint8)CAN_PROC_OK ) ); u1CheckCount++ )
        {
            *(Can_tb_stGlobalReg.ptu4GLOCKK) = CAN_u4GLOCKK_LOCK_RELKEY1;
            *(Can_tb_stGlobalReg.ptu4GLOCKK) = CAN_u4GLOCKK_LOCK_RELKEY2;

            *(Can_tb_stGlobalReg.ptu4GTSTCTR) = CAN_u4GTSTCTR_RTME_ENA;

            if ( ( *( Can_tb_stGlobalReg.ptu4GTSTCTR ) & CAN_u4GTSTCTR_RTME_MSK ) == CAN_u4GTSTCTR_RTME_ENA )
            {
                u1Ret = (uint8)CAN_PROC_OK;
            }
        }
    }

    return ( u1Ret );
}


/****************************************************************************/
/* Function Name | Can_fs_RAMTestDisable                                    */
/* Description   | RAM Test Disable Set                                     */
/* Preconditions | See Design Documents                                     */
/* Parameters    | void                                                     */
/* Return Value  | uint8                                                    */
/*               |   CAN_PROC_OK                                            */
/*               |   CAN_PROC_NG                                            */
/* Notes         | See Design Documents                                     */
/****************************************************************************/
static uint8
Can_fs_RAMTestDisable( void )
{
    uint8  u1Ret;

    u1Ret = (uint8)CAN_PROC_NG;

    *(Can_tb_stGlobalReg.ptu4GTSTCTR) = ( CAN_u4GTSTCTR_RTME_DIS | CAN_u4GTSTCTR_ICBCTME_DIS );

    Can_st_GlobalMode_Any2Reset();

    if ( ( *(Can_tb_stGlobalReg.ptu4GSTS) & CAN_u4GSTS_MODEALL_MSK ) == CAN_u4GSTS_GMODE_RESET )
    {
        u1Ret = (uint8)CAN_PROC_OK;
    }

    return ( u1Ret );
}


#endif /* (CAN_CFG_CAN == CAN_USE) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-2-1         :2022/09/19                                              */
/*  v2-2-2         :2023/05/11                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
