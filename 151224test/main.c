#include "SystemConfig.h"

OS_STK MainTaskStk[MainTask_StkSize];
OS_STK App1TaskStk[AppTask_StkSize];
OS_STK App2TaskStk[AppTask_StkSize];
OS_STK App3TaskStk[AppTask_StkSize];


OS_EVENT *Semp;
INT8U err;


int main(void)
{
	OSInit();
	OSTaskCreate(MainTask, (void*)0,&MainTaskStk[MainTask_StkSize-1],MainTask_Prio);
	Semp = OSMutexCreate(1,&err);
	if(Semp == (OS_EVENT*)0)
	{
		printf("OSSemCreate Error\n");
		return -1;
	}
	OSStart();
}

void MainTask(void * p_arg)
{
	p_arg = p_arg;
	OSTaskCreate(App1Task, (void*)0, &App1TaskStk[AppTask_StkSize-1],App1Task_Prio);
	OSTaskCreate(App2Task, (void*)0, &App2TaskStk[AppTask_StkSize-1],App2Task_Prio);
	OSTaskCreate(App3Task, (void*)0, &App3TaskStk[AppTask_StkSize-1],App3Task_Prio);
	while(1)
	{
		OSTimeDlyHMSM(0,0,10,0);
	}
}

void App1Task(void * p_arg)
{
	p_arg = p_arg;
	while(1)
	{
		OSTimeDly(200);
		printf("App1 Sem Pend\n");
		OSMutexPend(Semp, 0, &err);
		printf("1 \n");
		OSMutexPost(Semp);
		OSTimeDly(200);
	}
}
void App2Task(void * p_arg)
{
	p_arg = p_arg;
	while(1)
	{
		printf("2 \n");
		OSTimeDly(300);
	}
}
void App3Task(void * p_arg)
{
	p_arg = p_arg;
	while(1)
	{
		OSMutexPend(Semp,0,&err);
		printf("3 \n");
		OSTimeSet(0);
		while(OSTime < 1000)
		{
			OS_Sched();
		}
		OSMutexPost(Semp);
		OSTimeDlyHMSM(0,0,1,0);
	}
}








