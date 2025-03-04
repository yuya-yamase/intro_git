/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#warning "BEVCDCFD-822"
#if 0 /* BEVCDCFD-822 */
#define VEH_OPEMD_MDBIT_ACC                      (0x00000001U)  /* ACC        */
#endif /* BEVCDCFD-822 */
#define VEH_OPEMD_MDBIT_IGN                      (0x00000002U)  /* IGN(IGR)   */
#define VEH_OPEMD_MDBIT_STA                      (0x00000004U)  /* ST         */
#define VEH_OPEMD_MDBIT_BA                       (0x00000008U)  /* BA_PDC     */
#define VEH_OPEMD_MDBIT_IGNP                     (0x00000010U)  /* IGP        */
#define VEH_OPEMD_MDBIT_BAOF                     (0x00000020U)  /* BAOF_PDC   */

#define VEH_OPEMD_EVTBIT_IGN_TO_ON               (VEH_OPEMD_EVTBIT_POE_TO_ON)
#define VEH_OPEMD_EVTBIT_IGN_TO_OFF              (VEH_OPEMD_EVTBIT_POE_TO_OFF)

#define u1_g_VehopemdBaOn()                      (u1_g_VehopemdMdchk((U4)VEH_OPEMD_MDBIT_PAR, (U4)VEH_OPEMD_MDBIT_PAR))
#define u1_g_VehopemdIgnpOn()                    (u1_g_VehopemdPonNml())
#define u1_g_VehopemdBaofOn()                    (1U)
#warning "BEVCDCFD-822"
#if 0 /* BEVCDCFD-822 */
#define u1_g_VehopemdAccOn()                     (u1_g_VehopemdRiding())
#define u1_g_VehopemdIgnOn()                     (u1_g_VehopemdPonEmr())
#endif /* BEVCDCFD-822 */
#define u1_g_VehopemdStaOn()                     (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U4      u4_g_VehopemdConvertMdfield(void);