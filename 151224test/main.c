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
	return;
}


void App1Task(void * p_arg)
{
	p_arg = p_arg;
	while(1)
	{
		printf("1\n");
		OSTimeDlyHMSM(0, 0, 3, 0);
	}
	
}

void App2Task(void * p_arg)
{
	p_arg = p_arg;
	while(1)
	{
		printf("2\n");
		OSTimeDlyHMSM(0, 0, 6, 0);
	}
}
void Show_OSTCB(OS_TCB * pdata)
{
	printf("OSTCB: %lu\n",(unsigned long)pdata);
	printf("OSTCBPrev: %lu\n", (unsigned long)pdata->OSTCBPrev);
	printf("OSTCBNext: %lu\n", (unsigned long)pdata->OSTCBNext);
	printf("OSTCBDly: %ul\n", pdata->OSTCBDly);
	printf("OSTCBStat: %u\n", pdata->OSTCBStat);
	printf("OSTCBStatPend: %u\n", pdata->OSTCBStatPend);
	printf("OSTCBPrio: %u\n", pdata->OSTCBPrio);
	printf("OSTCBX: %u\n", pdata->OSTCBX);
	printf("OSTCBY: %u\n", pdata->OSTCBY);
	printf("OSTCBBitX: %u\n", pdata->OSTCBBitX);
	printf("OSTCBBitY: %u\n", pdata->OSTCBBitY);
}
void App3Task(void * p_arg)
{
	OS_TCB MainPdata;
	OS_TCB App1Pdate;
	OS_TCB App2Pdata;
	p_arg = p_arg;
	while(1)
	{
		printf("3\n");
		if(OSTaskQuery(MainTask_Prio, &MainPdata) == OS_ERR_NONE)
		{
			printf("Main pdata\n");
			Show_OSTCB(&MainPdata);
		}
		if(OSTaskQuery(App1Task_Prio, &App1Pdate) == OS_ERR_NONE)
		{
			printf("App1 pdata\n");
			Show_OSTCB(&App1Pdate);
		}
		if(OSTaskQuery(App2Task_Prio, &App2Pdata) == OS_ERR_NONE)
		{
			printf("App2 pdata\n");
			Show_OSTCB(&App2Pdata);
		}
		printf("App3 pdata\n");
		Show_OSTCB(OSTCBCur);
		OSTimeDlyHMSM(0, 0, 9, 0);
	}
}







