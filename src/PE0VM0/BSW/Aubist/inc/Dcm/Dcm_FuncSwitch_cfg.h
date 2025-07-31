/* Dcm_FuncSwitch_cfg_h(v5-5-0)                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/FuncSwitch/HEADER                                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_FUNCSWITCH_CFG_H
#define DCM_FUNCSWITCH_CFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_NVM_USE                          (STD_OFF)   /* Use NvM */
#define DCM_NVM_DDDID_USE                    (STD_OFF)   /* Use NvM for DynamicallyDefineDataIdentifier */
#define DCM_PAGEDBUFFER_ENABLED              (STD_OFF)   /* Use Paged Buffer in Dcm   */
#define DCM_PAGEDBUFFER_SID22_ENABLED        (STD_OFF)   /* Use Paged Buffer in SID22 */
#define DCM_PAGEDBUFFER_SID23_ENABLED        (STD_OFF)   /* Use Paged Buffer in SID23 */
#define DCM_PAGEDBUFFER_SID19_SUB02_ENABLED  (STD_OFF)   /* Use Paged Buffer in SID19_SUB02 */
#define DCM_PAGEDBUFFER_SID19_SUB04_ENABLED  (STD_OFF)   /* Use Paged Buffer in SID19_SUB04 */
#define DCM_PAGEDBUFFER_SID19_SUB0A_ENABLED  (STD_OFF)   /* Use Paged Buffer in SID19_SUB0A */
#define DCM_PAGEDBUFFER_SID19_SUB17_ENABLED  (STD_OFF)   /* Use Paged Buffer in SID19_SUB17 */
#define DCM_PAGEDBUFFER_SID19_SUB18_ENABLED  (STD_OFF)   /* Use Paged Buffer in SID19_SUB18 */
#define DCM_PAGEDBUFFER_SID19_SUB42_ENABLED  (STD_OFF)   /* Use Paged Buffer in SID19_SUB42 */
#define DCM_PAGEDBUFFER_SID31_ENABLED        (STD_OFF)   /* Use Paged Buffer in SID31 */
#define DCM_PERIODIC_SEND_USE                (STD_OFF)   /* Use Periodic Sending */
#define DCM_PERIODIC_DDDID_USE               (STD_OFF)   /* Use DynamicallyDefineDataIdentifier for Periodic Sending */
#define DCM_AUTHENTICATION_USE               (STD_OFF)   /* Use Authentication */
#define DCM_NVM_AUTHENTICATION_USE           (STD_OFF)   /* Use NvM for Authentication */
#define DCM_SID14_MEMORYSELECTION_USE        (STD_OFF)   /* Use SID14 MemorySelection */
#define DCM_SID86_ROE_USE                    (STD_OFF)   /* Use SID86 ROE */
#define DCM_SEC_PECULIAR_TYPE_WHITE          (STD_OFF)   /* Use SID27 Security Type White */
#define DCM_SEC_PECULIAR_TYPE_BLACK          (STD_ON)    /* Use SID27 Security Type Black */
#define DCM_SEC_PECULIAR_TYPE_RED            (STD_OFF)   /* Use SID27 Security Type Red */
#define DCM_SID2F_CONTROLMASK_EXTERNAL_USE   (STD_OFF)   /* Use SID2F External */
#define DCM_SID2F_CONTROLMASK_AUBIST_USE     (STD_ON)    /* Use SID2F Aubist */
#define DCM_DIAG_COM_DATA_PROVIDE_USE        (STD_OFF)   /* Use Provide Communication Data */
#define DCM_VERSION_INFO_API                 (STD_OFF)   /* Use VersionInfo API */
#define DCM_SUPPORT_SID10                    (STD_ON)    /* Use SID10     */
#define DCM_SUPPORT_SID11                    (STD_OFF)   /* Use SID11     */
#define DCM_SUPPORT_SID14                    (STD_ON)    /* Use SID14     */
#define DCM_SUPPORT_SID19_SUB01              (STD_OFF)   /* Use SID19Sf01 */
#define DCM_SUPPORT_SID19_SUB02              (STD_OFF)   /* Use SID19Sf02 */
#define DCM_SUPPORT_SID19_SUB03              (STD_OFF)   /* Use SID19Sf03 */
#define DCM_SUPPORT_SID19_SUB04              (STD_OFF)   /* Use SID19Sf04 */
#define DCM_SUPPORT_SID19_SUB05              (STD_OFF)   /* Use SID19Sf05 */
#define DCM_SUPPORT_SID19_SUB06              (STD_OFF)   /* Use SID19Sf06 */
#define DCM_SUPPORT_SID19_SUB0A              (STD_OFF)   /* Use SID19Sf0A */
#define DCM_SUPPORT_SID19_SUB0E              (STD_OFF)   /* Use SID19Sf0E */
#define DCM_SUPPORT_SID19_SUB17              (STD_OFF)   /* Use SID19Sf17 */
#define DCM_SUPPORT_SID19_SUB18              (STD_OFF)   /* Use SID19Sf18 */
#define DCM_SUPPORT_SID19_SUB19              (STD_OFF)   /* Use SID19Sf19 */
#define DCM_SUPPORT_SID19_SUB1A              (STD_OFF)   /* Use SID19Sf1A */
#define DCM_SUPPORT_SID19_SUB42              (STD_OFF)   /* Use SID19Sf42 */
#define DCM_SUPPORT_SID19_SUB55              (STD_OFF)   /* Use SID19Sf55 */
#define DCM_SUPPORT_SID19_SUB56              (STD_OFF)   /* Use SID19Sf56 */
#define DCM_SUPPORT_SID22                    (STD_OFF)   /* Use SID22     */
#define DCM_SUPPORT_SID23                    (STD_OFF)   /* Use SID23     */
#define DCM_SUPPORT_SID27                    (STD_OFF)   /* Use SID27     */
#define DCM_SUPPORT_SID28                    (STD_ON)    /* Use SID28     */
#define DCM_SUPPORT_SID29_SUB00              (STD_OFF)   /* Use SID29Sf00 */
#define DCM_SUPPORT_SID29_SUB01              (STD_OFF)   /* Use SID29Sf01 */
#define DCM_SUPPORT_SID29_SUB02              (STD_OFF)   /* Use SID29Sf02 */
#define DCM_SUPPORT_SID29_SUB03              (STD_OFF)   /* Use SID29Sf03 */
#define DCM_SUPPORT_SID29_SUB08              (STD_OFF)   /* Use SID29Sf08 */
#define DCM_SUPPORT_SID2C                    (STD_OFF)   /* Use SID2C     */
#define DCM_SUPPORT_SID2C_SUB01              (STD_OFF)   /* Use SID2CSf01 */
#define DCM_SUPPORT_SID2C_SUB02              (STD_OFF)   /* Use SID2CSf02 */
#define DCM_SUPPORT_SID2C_SUB03              (STD_OFF)   /* Use SID2CSf03 */
#define DCM_SUPPORT_SID2E                    (STD_OFF)   /* Use SID2E     */
#define DCM_SUPPORT_SID2F                    (STD_OFF)   /* Use SID2F     */
#define DCM_SUPPORT_SID31                    (STD_OFF)   /* Use SID31     */
#define DCM_SUPPORT_SID3E                    (STD_ON)    /* Use SID3E     */
#define DCM_SUPPORT_SID85                    (STD_OFF)   /* Use SID85     */
#define DCM_SUPPORT_SID85_SUB01              (STD_OFF)   /* Use SID85Sf01 */
#define DCM_SUPPORT_SID85_SUB02              (STD_OFF)   /* Use SID85Sf02 */
#define DCM_SUPPORT_SID86_SUB00              (STD_OFF)   /* Use SID86Sf00 */
#define DCM_SUPPORT_SID86_SUB01              (STD_OFF)   /* Use SID86Sf01 */
#define DCM_SUPPORT_SID86_SUB03              (STD_OFF)   /* Use SID86Sf03 */
#define DCM_SUPPORT_SID86_SUB05              (STD_OFF)   /* Use SID86Sf05 */
#define DCM_SUPPORT_SID86_SUB06              (STD_OFF)   /* Use SID86Sf06 */
#define DCM_SUPPORT_SID86_SUB07              (STD_OFF)   /* Use SID86Sf07 */
#define DCM_SUPPORT_SID86_SUB40              (STD_OFF)   /* Use SID86Sf40 */
#define DCM_SUPPORT_SID86_SUB41              (STD_OFF)   /* Use SID86Sf41 */
#define DCM_SUPPORT_SID86_SUB43              (STD_OFF)   /* Use SID86Sf43 */
#define DCM_SUPPORT_SID86_SUB45              (STD_OFF)   /* Use SID86Sf45 */
#define DCM_SUPPORT_SID86_SUB46              (STD_OFF)   /* Use SID86Sf46 */
#define DCM_SUPPORT_SID86_SUB47              (STD_OFF)   /* Use SID86Sf47 */
#define DCM_USE_PROVIDE_SERVICE              (STD_ON)    /* Use Provide Service  */

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


#endif /* DCM_FUNCSWITCH_CFG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-5-1                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
