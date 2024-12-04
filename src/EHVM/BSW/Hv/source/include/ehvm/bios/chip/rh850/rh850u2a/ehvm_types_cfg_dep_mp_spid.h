/*
    Copyright (C) 2022 eSOL Co.,Ltd. All rights reserved.

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
/****************************************************************************
 [ ehvm_types_cfg_dep_mp_spid.h ] - SPID module's configuration types header
****************************************************************************/

#ifndef EHVM_TYPES_CFG_DEP_MP_SPID_H
#define EHVM_TYPES_CFG_DEP_MP_SPID_H

/* type definitions */
#define SPID_BM_SPIDMSK_CPU00       (0x00U) /* BusMaster:CPU0       */
#define SPID_BM_SPIDMSK_CPU01       (0x01U) /* BusMaster:CPU1       */
#define SPID_BM_SPIDMSK_CPU02       (0x02U) /* BusMaster:CPU2       */
#define SPID_BM_SPIDMSK_CPU03       (0x03U) /* BusMaster:CPU3       */
#define SPID_BM_SPIDMSK_GB_ETHER    (0x11U) /* BusMaster:GbEther    */
#define SPID_BM_SPIDMSK_RHSIF0      (0x13U) /* BusMaster:RHSIF0     */
#define SPID_BM_SPIDMSK_FLEX_RAY1   (0x16U) /* BusMaster:FlexRay1   */
#define SPID_BM_SPIDMSK_FLEX_RAY0   (0x17U) /* BusMaster:FlexRay0   */
#define SPID_BM_SPIDMSK_FAST_ETHER  (0x18U) /* BusMaster:FastEther  */
#define SPID_BM_SPIDMSK_ICUM_AES0   (0x19U) /* BusMaster:ICUM_AES0  */
#define SPID_BM_SPIDMSK_ICUMHA      (0x1AU) /* BusMaster:ICUMHA     */
#define SPID_BM_SPIDMSK_S_DMAC1     (0x1BU) /* BusMaster:sDMAC1     */
#define SPID_BM_SPIDMSK_S_DMAC0     (0x1CU) /* BusMaster:sDMAC0     */
#define SPID_BM_SPIDMSK_DTS         (0x1DU) /* BusMaster:DTS        */
#define SPID_BM_SPIDMSK_MAU         (0x1FU) /* BusMaster:MAU        */

#define SPID_BM_SPID_GB_ETHER       (0x11U) /* BusMaster:GbEther    */
#define SPID_BM_SPID_RHSIF0         (0x13U) /* BusMaster:RHSIF0     */
#define SPID_BM_SPID_FLEX_RAY1      (0x16U) /* BusMaster:FlexRay1   */
#define SPID_BM_SPID_FLEX_RAY0      (0x17U) /* BusMaster:FlexRay0   */
#define SPID_BM_SPID_FAST_ETHER     (0x18U) /* BusMaster:FastEther  */
#define SPID_BM_SPID_ICUM_AES0      (0x19U) /* BusMaster:ICUM_AES0  */
#define SPID_BM_SPID_ICUMHA         (0x1AU) /* BusMaster:ICUMHA     */

typedef struct {
    ehvm_uint32_t                        SpidBMNumber;
    ehvm_uint32_t                        SpidBMSpidMsk;
} ehvm_spid_bm_spidmsk_t;

typedef struct {
    ehvm_uint32_t                        SpidBMNumber;
    ehvm_uint32_t                        SpidBMSpid;
} ehvm_spid_bm_spid_t;

typedef struct {
    ehvm_uint32_t                        SpidNumOfSpidMsk;
    EhvmConst ehvm_spid_bm_spidmsk_t*   SpidBMSpidMskPtr;
    ehvm_uint32_t                        SpidNumOfBMSpid;
    EhvmConst ehvm_spid_bm_spid_t*      SpidBMSpidPtr;
} ehvm_spid_config_t;

#endif /* EHVM_TYPES_CFG_DEP_MP_SPID_H */
