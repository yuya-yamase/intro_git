/* -------------------------------------------------------------------------- */
/* file name	:	EthSW_Task.h											  */
/* -------------------------------------------------------------------------- */
#ifndef ETHSW_TASK_H
#define ETHSW_TASK_H

void EthSW_Sch_PowerOnInit(void);
void EthSW_MediumTask(void);
void EthSW_HighTask(void);
void EthSW_LowTask(void);
void EthSW_Sch_Stop(void);

#endif/*ETHSW_TASK_H*/
