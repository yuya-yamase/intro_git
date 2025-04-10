/* Section_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Section/HEADER                                              */
/******************************************************************************/
#ifndef SECTION_H
#define SECTION_H

/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
/******************************************************************************/
/* Vector                                                                     */
/******************************************************************************/
typedef struct {
    P2VAR(uint32, TYPEDEF, SECTION_APPL_DATA) Addr;
} Section_VectorRomInfoType;

typedef struct {
    P2VAR(uint32, TYPEDEF, SECTION_APPL_DATA) DstAddr;
    P2CONST(uint32, TYPEDEF, SECTION_APPL_CONST) SrcAddr;
    P2CONST(uint32, TYPEDEF, SECTION_APPL_CONST) SrcEndAddr;
} Section_VectorRamInfoType;

typedef struct {
    P2CONST(Section_VectorRomInfoType, TYPEDEF, SECTION_APPL_CONST) Rom;
    P2CONST(Section_VectorRamInfoType, TYPEDEF, SECTION_APPL_CONST) Ram;
} Section_VectorType;

/******************************************************************************/
/* Stack                                                                      */
/******************************************************************************/
typedef struct {
    P2VAR(uint32, TYPEDEF, SECTION_APPL_DATA) Addr;
    uint32  MinSize;
    uint32  MaxSize;
    P2VAR(uint32, TYPEDEF, SECTION_APPL_DATA) LowAddr;
} Section_StackType;

/******************************************************************************/
/* .text                                                                      */
/******************************************************************************/
typedef struct {
    P2VAR(uint32, TYPEDEF, SECTION_APPL_DATA) DstAddr;
    P2CONST(uint32, TYPEDEF, SECTION_APPL_CONST) SrcAddr;
    P2CONST(uint32, TYPEDEF, SECTION_APPL_CONST) SrcEndAddr;
} Section_RomRamCopyTextInfoType;

typedef struct {
    uint32  Num;
    P2CONST(Section_RomRamCopyTextInfoType, TYPEDEF, SECTION_APPL_CONST) Info;
} Section_RomRamCopyTextType;

/******************************************************************************/
/* .rosdata, .rodata                                                          */
/******************************************************************************/
typedef Section_RomRamCopyTextInfoType  Section_RomRamCopyDataInfoType;

typedef struct {
    uint32  Num;
    P2CONST(Section_RomRamCopyDataInfoType, TYPEDEF, SECTION_APPL_CONST) Info;
} Section_RomRamCopyDataType;

/******************************************************************************/
/* .sbss, .bss                                                                */
/******************************************************************************/
typedef struct {
    P2VAR(uint32, TYPEDEF, SECTION_APPL_DATA) Addr;
    P2CONST(uint32, TYPEDEF, SECTION_APPL_CONST) EndAddr;
} Section_RomRamCopyBssInfoType;

typedef struct {
    uint32  Num;
    P2CONST(Section_RomRamCopyBssInfoType, TYPEDEF, SECTION_APPL_CONST) Info;
} Section_RomRamCopyBssType;

/******************************************************************************/
/* RAM setting                                                                */
/******************************************************************************/
typedef struct {
    P2CONST(Section_RomRamCopyTextType, TYPEDEF, SECTION_APPL_CONST) Text;
    P2CONST(Section_RomRamCopyDataType, TYPEDEF, SECTION_APPL_CONST) Data;
    P2CONST(Section_RomRamCopyBssType, TYPEDEF, SECTION_APPL_CONST) Bss;
} Section_RomRamCopyType;

/******************************************************************************/
/* SBL                                                                        */
/******************************************************************************/
typedef struct {
    P2VAR(uint32, TYPEDEF, SECTION_APPL_DATA) Addr;
    P2CONST(uint32, TYPEDEF, SECTION_APPL_CONST) EndAddr;
} Section_DlInfoType;

typedef struct {
    uint32  Num;
    P2CONST(Section_DlInfoType, TYPEDEF, SECTION_APPL_CONST) Info;
} Section_DlType;

/******************************************************************************/
/* Unused RAM                                                                 */
/******************************************************************************/
typedef struct {
    P2VAR(uint32, TYPEDEF, SECTION_APPL_DATA) Addr;
    P2CONST(uint32, TYPEDEF, SECTION_APPL_CONST) EndAddr;
} Section_UnusedRamInfoType;

typedef struct {
    uint32  Num;
    P2CONST(Section_UnusedRamInfoType, TYPEDEF, SECTION_APPL_CONST) Info;
} Section_UnusedRamType;

/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define SECTION_START_SEC_CST
#include <Section_MemMap.h>
/******************************************************************************/
/* Vector                                                                     */
/******************************************************************************/
extern CONST(Section_VectorType, SECTION_CONST) Section_VectorData;

/******************************************************************************/
/* Stack                                                                      */
/******************************************************************************/
extern CONST(Section_StackType, SECTION_CONST) Section_StackData;

/******************************************************************************/
/* RAM setting                                                                */
/******************************************************************************/
extern CONST(Section_RomRamCopyType, SECTION_CONST) Section_1stInfo;
extern CONST(Section_RomRamCopyType, SECTION_CONST) Section_2ndInfo;

/******************************************************************************/
/* SBL                                                                        */
/******************************************************************************/
extern CONST(Section_DlType, SECTION_CONST) Section_DlData;

/******************************************************************************/
/* Unused RAM                                                                 */
/******************************************************************************/
extern CONST(Section_UnusedRamType, SECTION_CONST) Section_UnusedRamData;

#define SECTION_STOP_SEC_CST
#include <Section_MemMap.h>

#endif /* SECTION_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2021/09/14 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/
