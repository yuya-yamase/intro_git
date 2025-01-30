/* 2.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  F-spo Sensor                                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
#ifndef FSPOSNSR_H
#define FSPOSNSR_H


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define FSPOSNSR_H_MAJOR                         (2)
#define FSPOSNSR_H_MINOR                         (1)
#define FSPOSNSR_H_PATCH                         (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include File                                                                                                                     */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define FSPOSNSR_TASK_CYCLE                      (10U)                  /*  periodic processing cycle[LSB:ms]                        */

/* Fail State  */
/* Input signal status usable bit range (b00-b07) */
#define FSPOSNSR_SET_VSC1G12FAIL                 (0x0002U)              /*  VSC1G12 Communication status FAIL                        */
#define FSPOSNSR_SET_VSC1G30FAIL                 (0x0008U)              /*  VSC1G30 Communication status FAIL                        */
#define FSPOSNSR_SET_ENG1G17FAIL                 (0x0040U)              /*  ENG1G17 Communication status FAIL                        */

#define FSPOSNSR_RST_VSC1G12FAIL                 (0xFFFDU)              /*  ~FSPOSNSR_SET_VSC1G12RCVD                                */
#define FSPOSNSR_RST_VSC1G30FAIL                 (0xFFF7U)              /*  ~FSPOSNSR_SET_VSC1G30RCVD                                */
#define FSPOSNSR_RST_ENG1G17FAIL                 (0xFFBFU)              /*  ~FSPOSNSR_SET_ENG1G17FAIL                                */

/* Custom Available Bit Range (b08-b15) */
/* Signal State */
#define FSPOSNSR_SIGSTS_INIT                     (0x0000U)              /* Initial value                                             */
#define FSPOSNSR_SIGSTS_IGONMASK                 (0xFF00U)              /* IG-ON Initialization Mask                                 */

/* Permission information  */
/* Input signal status usable bit range (b00-b07) */
#define FSPOSNSR_SET_VSC1G12RCVD                 (0x02U)                /*  VSC1G12 Receive Authorization Info.                      */
#define FSPOSNSR_SET_VSC1G30RCVD                 (0x08U)                /*  VSC1G30 Receive Authorization Info.                      */
#define FSPOSNSR_SET_ENG1G17RCVD                 (0x20U)                /*  ENG1G17 Receive Authorization Info.                      */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    S2                          s2_gxhr0;                               /* Front and back G sensor values                            */
    S2                          s2_gyhr0;                               /* Left and right G sensor values                            */
    U1                          u1_gxf;                                 /* Abnormal state of front and back G sensors                */
    U1                          u1_gyf;                                 /* Abnormal state of left and right G sensors                */
    U1                          u1_gxiv;                                /* Invalid state of front and back G sensors                 */
    U1                          u1_gyiv;                                /* Invalid state of left and right G sensors                */
}ST_FSPOSNSR_INC_VSC1G12;

typedef struct{
    U1                          u1_fbkdrsys;                            /* Brake pedal driver required acceleration effective flag   */
    S2                          s2_fbkdr_ax;                            /* Brake pedal driver required acceleration                  */
}ST_FSPOSNSR_INC_VSC1G30;

typedef struct{
    U2                          u2_bpom;                                /* Oil pressure                                              */
    U2                          u2_bthoe;                               /* Oil temperature                                           */
}ST_FSPOSNSR_INC_ENG1G17;

typedef struct{
    ST_FSPOSNSR_INC_VSC1G12     st_inc_vsc1g12;                         /* VSC1G12 signal reception information                      */
    ST_FSPOSNSR_INC_VSC1G30     st_inc_vsc1g30;                         /* VSC1G30 signal reception information                      */
    ST_FSPOSNSR_INC_ENG1G17     st_inc_eng1g17;                         /* ENG1G17 signal reception information                      */
    U2                          u2_sigfail;                             /* Interruption information                                  */
    U1                          u1_rcvd;                                /* Permission bit information                                */
}ST_FSPOSNSR_INCARG;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_FsposnsrBon(void);
void    vd_g_FsposnsrWkup(void);
void    vd_g_FsposnsrIgon(void);
void    vd_g_FsposnsrIgoff(void);
void    vd_g_Fsposnsr10msTask(void);
void    vd_g_FsposnsrCanRxEng1s98(void);
void    vd_g_FsposnsrCanRxVsc1g12(void);
void    vd_g_FsposnsrCanRxVsc1g30(void);
void    vd_g_FsposnsrCanRxEng1g17(void);
U2      u2_g_FsposnsrGetSigSts(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif      /* FSPOSNSR_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  fsposnsr.c                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
