#include "delay.h"
#include "usart.h"
#include "LED.h"
#include "FreeRTOS.h"
#include "task.h"

#define  START_TASK_STK      120
#define  START_TASK_PRIO      2	
TaskHandle_t *  start_handle ;

void start_task(void *  pvParameters);	//开始任务

#define  TASK_1_STK           120
#define  TASK_1_PRIO           3 
TaskHandle_t *  task_1_handle;
void task_1(void *  pvParameters);

#define  TASK_2_STK           120
#define  TASK_2_PRIO           4		
TaskHandle_t *  task_2_handle;
void task_2(void *  pvParameters);

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置系统中断优先级分组4	 
	delay_init();	    				//延时函数初始化	  
	uart_init(115200);					//初始化串口
	LED_Init();		  					//初始化LED
	
	xTaskCreate((TaskFunction_t ) start_task,
				(char *         ) start_task,
				(uint16_t       ) START_TASK_STK,
				(void *         ) NULL,
				(UBaseType_t    ) START_TASK_PRIO,
				(TaskHandle_t * ) &start_handle );
				
	vTaskStartScheduler();
}


void start_task(void *  pvParameters)
{
	xTaskCreate((TaskFunction_t ) task_1,
				(char *         ) task_1,
				(uint16_t       ) TASK_1_STK,
				(void *         ) NULL,
				(UBaseType_t    ) TASK_1_PRIO,
				(TaskHandle_t * ) &task_1_handle );
				
	xTaskCreate((TaskFunction_t ) task_2,
				(char *         ) task_2,
				(uint16_t       ) TASK_2_STK,
				(void *         ) NULL,
				(UBaseType_t    ) TASK_2_PRIO,
				(TaskHandle_t * ) &task_2_handle );
	
	vTaskDelete(start_handle);
}

void task_1(void *  pvParameters)
{
	u8 run_count=0;
	while(1)
	{
		run_count++;
		LED0=~LED0;
		printf("task_1 run%d\r\n",run_count);
		if(run_count==15)
		{
			LED0=1;
			printf("delete task_1 \r\n");
			vTaskDelete(task_1_handle);
		}
		vTaskDelay(500);
	}
}

void task_2(void *  pvParameters)
{
	u8 run_count=0;
	while(1)
	{
		run_count++;
		LED1=~LED1;
		vTaskDelay(1000);
		printf("task_2 run%d\r\n",run_count);
	}
}





