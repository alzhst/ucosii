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
	while(1)
	{
		OSTimeDlyHMSM(0,0,1,0);
	}
}

void App1Task(void * p_arg)
{
	p_arg = p_arg;
	INT32U ticks;
	while(1)
	{
		ticks = OSTimeGet();
		printf("ticks: %d\n",ticks);
		if(ticks > 1000 && ticks < 1500)
		{
			while(OSTaskDelReq(App2Task_Prio) != OS_ERR_TASK_NOT_EXIST)
			{
				OSTimeDly(1);
			}
		}
		else if(ticks > 2000 && ticks < 3500)
		{
			while(OSTaskDelReq(App3Task_Prio) != OS_ERR_TASK_NOT_EXIST)
			{
				OSTimeDly(1);
			}
		}
		printf("1\n");
		OSTimeDlyHMSM(0,0,6,0);
	}
}

void App2Task(void * p_arg)
{
	p_arg = p_arg;
	while(1)
	{
		if(OSTaskDelReq(OS_PRIO_SELF) == OS_ERR_TASK_DEL_REQ)
		{
			printf("AppTask1:É¾³ýAppTask2\n");
			OSTaskDel(OS_PRIO_SELF);
		}
		else
		{
			printf("2\n");
			OSTimeDlyHMSM(0,0,1,0);
		}
	}
}


void App3Task(void * p_arg)
{
	p_arg = p_arg;
	while(1)
	{
		if(OSTaskDelReq(OS_PRIO_SELF) == OS_ERR_TASK_DEL_REQ)
		{
			printf("AppTask1:É¾³ýAppTask3\n");
			OSTaskDel(OS_PRIO_SELF);
		}
		else
		{
			printf("3\n");
			OSTimeDlyHMSM(0,0,2,0);
		}
	}
}






