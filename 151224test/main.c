#include "SystemConfig.h"

OS_STK MainTaskStk[MainTask_StkSize];
OS_STK App1TaskStk[AppTask_StkSize];



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
	while(1)
	{
		printf("He");
		OSTimeDlyHMSM(0,0,2,0);
		printf("-II!\n");
		OSTimeDlyHMSM(0,0,0,0);
	}
}

void App1Task(void * p_arg)
{
	p_arg = p_arg;
	while(1)
	{
		printf("llo, ");
		OSTimeDlyHMSM(0,0,1,0);
		printf("uc/OS ");
		OSTimeDlyHMSM(0,0,1,0);
	}
}






