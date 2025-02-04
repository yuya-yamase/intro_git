/* Compiler_h_v2-0-0                                                        */
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
/*   AUBASS, Add Definition  */
/*---------------------------*/
#define AB_83_ConstV        volatile      /* 'volatile' definition */

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
/*  v2-0-0         :2022/12/06                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
