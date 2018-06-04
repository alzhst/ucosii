#include "SystemConfig.h"

OS_STK MainTaskStk[MainTask_StkSize];
OS_STK App1TaskStk[AppTask_StkSize];
OS_STK App2TaskStk[AppTask_StkSize];
OS_STK App3TaskStk[AppTask_StkSize];



int main(void)
{
	OSInit();
	OSTaskCreate(MainTask, (void*)0,&MainTaskStk[MainTask_StkSize-1],MainTask_Prio);

	OSStart();
}

void MainTask(void * p_arg)
{
	p_arg = p_arg;
	OSTaskCreate(App1Task, (void*)0, &App1TaskStk[AppTask_StkSize-1],App1Task_Prio);
	OSTaskCreate(App2Task, (void*)0, &App2TaskStk[AppTask_StkSize-1],App2Task_Prio);
	OSTaskCreate(App3Task, (void*)0, &App3TaskStk[AppTask_StkSize-1],App3Task_Prio);
	printf("IdleTcbCtr: %lu\n",(INT32U)OSTCBPrioTbl[OS_LOWEST_PRIO]);
	printf("MainTcbCtr: %lu\n",(INT32U)OSTCBPrioTbl[MainTask_Prio]);
	printf("App1TcbCtr: %lu\n",(INT32U)OSTCBPrioTbl[App1Task_Prio]);
	printf("App2TcbCtr: %lu\n",(INT32U)OSTCBPrioTbl[App2Task_Prio]);
	printf("App3TcbCtr: %lu\n",(INT32U)OSTCBPrioTbl[App3Task_Prio]);
	while(1)
	{
		OSTimeDlyHMSM(0,0,1,0);
	}
}

void App1Task(void * p_arg)
{
	p_arg = p_arg;
	while(1)
	{
		printf("1\n");
		OSTimeDlyHMSM(0,0,6,0);
	}
}

void App2Task(void * p_arg)
{
	p_arg = p_arg;
	while(1)
	{
		printf("2\n");
		OSTimeDlyHMSM(0,0,1,0);
	}
}


void App3Task(void * p_arg)
{
	p_arg = p_arg;
	while(1)
	{
		printf("3\n");
		OSTimeDlyHMSM(0,0,2,0);
	}
}






