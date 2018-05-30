#include "SystemConfig.h"

/*定义堆栈*/
OS_STK MainTask_Stk[MainTask_StkSize];
OS_STK App1Task_Stk[AppTask_StkSize];
OS_STK App2Task_Stk[AppTask_StkSize];
OS_STK App3Task_Stk[AppTask_StkSize];

int main(void)
{
	OSInit(); /*系统初始化*/

	OSTaskCreate(MainTask, (void*)0, &MainTask_Stk[MainTask_StkSize-1], MainTask_Prio);/*创建主任务*/

	OSStart();/*系统启动*/
	return 0;
}

void MainTask(void *p_arg)
{
	p_arg = p_arg;
	OSTaskCreate(App1Task, (void*)0, &App1Task_Stk[AppTask_StkSize-1], App1Task_Prio);/*分别创建三个任务*/
	OSTaskCreate(App2Task, (void*)0, &App2Task_Stk[AppTask_StkSize-1], App2Task_Prio);
	OSTaskCreate(App3Task, (void*)0, &App3Task_Stk[AppTask_StkSize-1], App3Task_Prio);
	while(1)
	{
		OSTimeDlyHMSM(0, 0, 1, 0);
	}
	return 0;
}


void App1Task(void * p_arg)
{
	p_arg = p_arg;
	while(1)
	{
		printf("1 ");
		OSTimeDlyHMSM(0, 0, 3, 0);
	}
	
}

void App2Task(void * p_arg)
{
	p_arg = p_arg;
	while(1)
	{
		printf("2 ");
		OSTimeDlyHMSM(0, 0, 6, 0);
	}
}

void App3Task(void * p_arg)
{

	p_arg = p_arg;
	while(1)
	{
		printf("3 ");
		OSTimeDlyHMSM(0, 0, 9, 0);
	}
}

