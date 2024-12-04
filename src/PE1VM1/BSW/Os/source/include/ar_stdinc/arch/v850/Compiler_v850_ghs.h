/*
    Copyright (C) 2016 eSOL Co.,Ltd. Tokyo, Japan

    This software is protected by the law and the agreement concerning
    a Japanese country copyright method, an international agreement,
    and other intellectual property right and may be used and copied
    only in accordance with the terms of such license and with the inclusion
    of the above copyright notice.

    This software or any other copies thereof may not be provided
    or otherwise made available to any other person.  No title to
    and ownership of the software is hereby transferred.

    The information in this software is subject to change without
    notice and should not be construed as a commitment by eSOL Co.,Ltd.
*/
/***************************************************************************
[ Compiler_v850_ghs.h ] - Compiler dependency header file
****************************************************************************/

#ifndef COMPILER_V850_GHS_H_
#define COMPILER_V850_GHS_H_

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* AUTOSAR specification version information [SWS_BSW_00059] */
#define COMPILER_VENDOR_ID                    (0x003DU)
#define COMPILER_MODULE_ID                    (0x00C6U)
#define COMPILER_AR_RELEASE_MAJOR_VERSION     (4U)
#define COMPILER_AR_RELEASE_MINOR_VERSION     (5U)
#define COMPILER_AR_RELEASE_REVISION_VERSION  (0U)

/* File version information [SWS_BSW_00059] */
#define COMPILER_SW_MAJOR_VERSION             (2U)
#define COMPILER_SW_MINOR_VERSION             (0U)
#define COMPILER_SW_PATCH_VERSION             (0U)

/*------------------------*/
/*   Definitions          */
/*------------------------*/
#define AUTOMATIC           /* 'empty' definition *//* SWS_COMPILER_00040, SWS_COMPILER_00046 */
#define TYPEDEF             /* 'empty' definition *//* SWS_COMPILER_00040, SWS_COMPILER_00059 */

#ifndef NULL_PTR
#define NULL_PTR            ((void *)0)   /* Null pointer definition */            /* SWS_COMPILER_00051 */
#endif /* NULL_PTR */

#define INLINE              inline        /* inline or 'empty' definition */       /* SWS_COMPILER_00057 */
#define LOCAL_INLINE        static inline /* static inline or 'empty' definition *//* SWS_COMPILER_00060 */

#define FUNC(rettype, memclass)  rettype                                      /* SWS_COMPILER_00001 */
#define FUNC_P2CONST(rettype, ptrclass, memclass)   const rettype *           /* SWS_COMPILER_00061 */
#define FUNC_P2VAR(rettype, ptrclass, memclass)     rettype *                 /* SWS_COMPILER_00063 */
#define P2VAR(ptrtype, memclass, ptrclass)          ptrtype *                 /* SWS_COMPILER_00006 */
#define P2CONST(ptrtype, memclass, ptrclass)        const ptrtype *           /* SWS_COMPILER_00013 */
#define CONSTP2VAR(ptrtype, memclass, ptrclass)     ptrtype * const           /* SWS_COMPILER_00031 */
#define CONSTP2CONST(ptrtype, memclass, ptrclass)   const ptrtype * const     /* SWS_COMPILER_00032 */
#define P2FUNC(rettype, ptrclass, fctname)          rettype (*fctname)        /* SWS_COMPILER_00039 */
#define CONSTP2FUNC(rettype, ptrclass, fctname)     rettype (* const fctname) /* SWS_COMPILER_00065 */
#define CONST(type, memclass)                       const type                /* SWS_COMPILER_00023 */
#define VAR(type, memclass)                         type                      /* SWS_COMPILER_00026 */

#endif /* COMPILER_V850_GHS_H_ */
