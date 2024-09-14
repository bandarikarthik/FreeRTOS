#include "DAVE.h"                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/portable/GCC/portmacro_mpu.h>
#include <freertos\queue.h>

TaskHandle_t xHandle_1,xHandle_2,xHandle_3,Button_Task;

TaskHandle_t volatile next_task_handle;

QueueHandle_t myQueue;

typedef	struct student{

	char name[7];
	uint8_t roll_no;

}student_t;

void Task_1(void *pvparameters);
void Task_2(void *pvparameters);
void Task_3(void *pvparameters);
void ButtonTask(void *pvparameters);

void DAVE_Initialsisation(void);

int main(void)
{

	DAVE_Initialsisation();

	BaseType_t status;

	status = xTaskCreate(Task_1,"Task_1",200,NULL,3,&xHandle_1);

	configASSERT(status == pdPASS);

	status = xTaskCreate(Task_2,"Task_2",200,NULL,3,&xHandle_2);

	configASSERT(status == pdPASS);

	myQueue = xQueueCreate(10, sizeof( uint8_t ));  //this creation is very important it can save HEAP memory
	configASSERT(myQueue != NULL);


	vTaskStartScheduler();

}

void Task_1(void *pvparameters)
{
	uint8_t globalValue = 0;uint8_t xTBuffer[6];
	uint8_t xSend_Data[] = "queue sent:";
	BaseType_t status;
	while(1)
	{
		globalValue++;
		xQueueSend(myQueue,(void*)&globalValue,portMAX_DELAY);
		UART_Transmit(&UART_0,(uint8_t*)xSend_Data, sizeof(xSend_Data)-1);
		memset(xTBuffer,0,sizeof(xTBuffer));
		sprintf(xTBuffer,"%d\r\n",globalValue);
		UART_Transmit(&UART_0,(uint8_t*) xTBuffer, sizeof(xTBuffer)-1);
		vTaskDelay(pdMS_TO_TICKS(500));

		if(globalValue == 10){

			vTaskDelay(pdMS_TO_TICKS(15000));
			globalValue = 0;

		}

	}
}

void Task_2(void *pvparameters)
{
	uint8_t RxglobalValue = 0,rxarray[6];
	uint8_t Send_Data[] = "queue received : ";
	while(1){


		if(xQueueReceive(myQueue,(void*)&RxglobalValue ,0)){

			UART_Transmit(&UART_0,(uint8_t*) Send_Data, sizeof(Send_Data)-1);
			memset(rxarray,0,sizeof(rxarray));
			sprintf(rxarray,"%d\r\n",RxglobalValue);
			UART_Transmit(&UART_0,(uint8_t*) rxarray, sizeof(rxarray)-1);
			vTaskDelay(pdMS_TO_TICKS(1000));
		}
	}

}

void DAVE_Initialsisation(void){

	DAVE_STATUS_t status;

	status = DAVE_Init();           /* Initialization of DAVE APPs  */

	if (status != DAVE_STATUS_SUCCESS)
	{
		/* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
		XMC_DEBUG("DAVE APPs initialization failed\n");

		while(1U)
		{

		}
	}
}
