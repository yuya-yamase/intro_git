/* Compiler_h_v1-0-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Compiler/HEADER                                           */
/*--------------------------------------------------------------------------*/
/* Notes        | Made modifications for Reprog                             */
/****************************************************************************/

#ifndef COMPILER_H                                   /* SWS_COMPILER_00047 */
#define COMPILER_H /* implementation of Compiler.h *//* SWS_COMPILER_00047 */

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include <Compiler_Cfg.h>                            /* no SWS-No */

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* AUTOSAR specification version information [SWS_BSW_00059] */
#define COMPILER_VENDOR_ID                    (0x0053U)
#define COMPILER_MODULE_ID                    (0x00C6U)
#define COMPILER_AR_RELEASE_MAJOR_VERSION     (4U)
#define COMPILER_AR_RELEASE_MINOR_VERSION     (2U)
#define COMPILER_AR_RELEASE_REVISION_VERSION  (1U)

/* File version information [SWS_BSW_00059] */
#define COMPILER_SW_MAJOR_VERSION  (1U)
#define COMPILER_SW_MINOR_VERSION  (0U)
#define COMPILER_SW_PATCH_VERSION  (0U)

/*------------------------------*/
/* Compier Definition           */
/*------------------------------*/
/*------------------------------*/
/* compiler vendor  : GreenHills*/
/* compiler version : V2013.5.5 */
/*------------------------------*/
#define AB_83_GREENHILLS_C_V2013_5_5

/*------------------------*/
/*   Definitions          */
/*------------------------*/
#define AUTOMATIC           /* 'empty' definition *//* SWS_COMPILER_00040, SWS_COMPILER_00046 */
#define TYPEDEF             /* 'empty' definition *//* SWS_COMPILER_00040, SWS_COMPILER_00059 */

#define NULL_PTR            ((void *)0)   /* Null pointer definition */            /* SWS_COMPILER_00051 */

#define INLINE              inline        /* inline or 'empty' definition */       /* SWS_COMPILER_00057 */
#define LOCAL_INLINE        static inline /* static inline or 'empty' definition *//* SWS_COMPILER_00060 */

/*------------------------*/
/*   Greenhills, RH850    */
/*------------------------*/
#define FUNC(rettype, memclass)                     memclass rettype          /* SWS_COMPILER_00001 */
#define FUNC_P2CONST(rettype, ptrclass, memclass)   memclass const rettype *  /* SWS_COMPILER_00061 */
#define FUNC_P2VAR(rettype, ptrclass, memclass)     memclass rettype *        /* SWS_COMPILER_00063 */
#define P2VAR(ptrtype, memclass, ptrclass)          ptrtype *                 /* SWS_COMPILER_00006 */
#define P2CONST(ptrtype, memclass, ptrclass)        const ptrtype *           /* SWS_COMPILER_00013 */
#define CONSTP2VAR(ptrtype, memclass, ptrclass)     ptrtype * const           /* SWS_COMPILER_00031 */
#define CONSTP2CONST(ptrtype, memclass, ptrclass)   const ptrtype * const     /* SWS_COMPILER_00032 */
#define P2FUNC(rettype, ptrclass, fctname)          rettype (*fctname)        /* SWS_COMPILER_00039 */
#define CONSTP2FUNC(rettype, ptrclass, fctname)     rettype (* const fctname) /* SWS_COMPILER_00065 */
#define CONST(type, memclass)                       const type                /* SWS_COMPILER_00023 */
#define VAR(type, memclass)                         type                      /* SWS_COMPILER_00026 */

/*---------------------------*/
/*   AUBASS, Add Definiion   */
/*---------------------------*/
#define AB_83_ConstV        volatile      /* 'volatile' definition */

/* define AB_83_<Compiler>_C_<Platform>  */
#ifndef AB_83_GREENHILLS_C_RH850
  #define AB_83_GREENHILLS_C_RH850
#endif


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


#endif /* COMPILER_H *//* SWS_COMPILER_00047 */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2017/12/05                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
