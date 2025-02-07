/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VEH_OPEMD_STUB_MDBIT_OFF                      (0x00000000U)
#define VEH_OPEMD_STUB_MDBIT_ACC                      (0x00000001U)  /* ACC        */
#define VEH_OPEMD_STUB_MDBIT_IGN                      (0x00000002U)  /* IGN(IGR)   */
#define VEH_OPEMD_STUB_MDBIT_STA                      (0x00000004U)  /* ST         */
#define VEH_OPEMD_STUB_MDBIT_BA                       (0x00000008U)  /* BA_PDC     */
#define VEH_OPEMD_STUB_MDBIT_IGNP                     (0x00000010U)  /* IGP        */
#define VEH_OPEMD_STUB_MDBIT_RDY                      (0x00000040U)  /* Ready      */
#define VEH_OPEMD_STUB_MDBIT_TST                      (0x00000080U)  /* TC         */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U4      u4_g_VehopemdConvertMdfield(void);