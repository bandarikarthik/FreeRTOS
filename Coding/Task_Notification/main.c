/*
 * main.c
 *
 *  Created on: 2024 Jun 29 17:11:11
 *  Author: PC
 */




#include "DAVE.h"                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include <stdio.h>
#include <stdint.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/portable/GCC/portmacro_mpu.h>

TaskHandle_t xHandle_1,xHandle_2,xHandle_3,Button_Task;

TaskHandle_t volatile next_task_handle;

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
/*
status = xTaskCreate(Task_2,"Task_2",200,NULL,2,&xHandle_2);

configASSERT(status == pdPASS);

status = xTaskCreate(Task_3,"Task_3",200,NULL,1,&xHandle_3);

configASSERT(status == pdPASS);
*/
status = xTaskCreate(ButtonTask,"Button_press",200,NULL,4,&Button_Task);

configASSERT(status == pdPASS);

   vTaskStartScheduler();

}

  void Task_1(void *pvparameters)
{
	uint8_t Send_Data[] = "Notification received\r\n";

	while(1)
	{
		if(xTaskNotifyWait(0,0,NULL,portMAX_DELAY) == pdTRUE)
			UART_Transmit(&UART_0, Send_Data, sizeof(Send_Data)-1);
	}
}

 void Task_2(void *pvparameters)
{
	uint8_t Send_Data[] = "Hello Task-2\r\n";
	BaseType_t status;

	while(1)
	{
		UART_Transmit(&UART_0, Send_Data, sizeof(Send_Data)-1);
		vTaskDelay(pdMS_TO_TICKS(500));
	}

}

 void Task_3(void *pvparameters)
{
	uint8_t Send_Data[] = "Hello Task-3\r\n";
	BaseType_t status;

	while(1)
	{
		UART_Transmit(&UART_0, Send_Data, sizeof(Send_Data)-1);
		vTaskDelay(pdMS_TO_TICKS(3000));

	}
}


void ButtonTask(void *pvparameters)
{

	uint8_t btn_read = 1;
	uint8_t prev_read = 1;
	while(1)
	{

		btn_read = DIGITAL_IO_GetInput(&DIGITAL_IO_2);

//If switch is pressed then pin goes to LOW state as per circuit diagram pg:no 22
		if((!btn_read))
			if(prev_read)xTaskNotify(xHandle_1,0,eNoAction);  //Button pressed
															 //if the button is long pressed then also notification should send only once.

		/*
		if((btn_read))
					if(!prev_read)xTaskNotify(xHandle_1,0,eNoAction); //this is for understanding logic
																	//if switch is pressed then it receives 1 in btn read.
																	 The switch should not de-bouncing for first time pressed
																	 should not send notification many times.

*/
		prev_read = btn_read;
		vTaskDelay(pdMS_TO_TICKS(10));

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

