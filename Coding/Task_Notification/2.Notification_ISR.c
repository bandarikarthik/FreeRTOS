/*
 * main.c
 *
 *  Created on: 2024 Jun 29 17:11:11
 *  Author: PC
 */




#include "DAVE.h"                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/portable/GCC/portmacro_mpu.h>
#include <freertos\queue.h>


extern void UART_lReceiveHandler(const UART_t * const handle);

uint8_t ReadData[2];

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

uint8_t mainfunction[] = "Idle funtion\r\n";


int main(void)
{

DAVE_Initialsisation();

BaseType_t status;

status = xTaskCreate(Task_1,"Task_1",200,NULL,3,&xHandle_1);

configASSERT(status == pdPASS);

status = xTaskCreate(Task_2,"Task_2",200,NULL,3,&xHandle_2);

configASSERT(status == pdPASS);

myQueue = xQueueCreate(5, sizeof( student_t* ));

configASSERT(myQueue != NULL);

UART_Receive(&UART_0, ReadData,2);

   vTaskStartScheduler();

   while(1){


   }

}

 void Task_1(void *pvparameters)
{

	 uint8_t Send_Data[] = "Task-1\r\n";
	// TickType_t xLastWakeTime;
	  //xLastWakeTime = xTaskGetTickCount();
	 	while(1)
	 	{
	 		if(xTaskNotifyWait(0,0,NULL,portMAX_DELAY) == pdTRUE){
	 					UART_Transmit(&UART_0, Send_Data, sizeof(Send_Data)-1);
	 					UART_Receive(&UART_0, ReadData,2);

	 		}


	 	}

}

 void  UserButtonHandler(void)
{



}

void Task_2(void *pvparameters)
{


	while(1){

		 uint8_t Send_Data[] = "Task-2\r\n";
		 TickType_t xLastWakeTime;
		  xLastWakeTime = xTaskGetTickCount();

		 	while(1)
		 	{
		 		//	UART_Transmit(&UART_0, Send_Data, sizeof(Send_Data)-1);
		 		//	vTaskDelay(pdMS_TO_TICKS(3000));
		 			 vTaskDelayUntil( &xLastWakeTime,pdMS_TO_TICKS(1000) );


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
void vApplicationIdleHook(void){


//	UART_Transmit(&UART_0, mainfunction, sizeof(mainfunction)-1);

}

void UART_0_RX_HANDLER()
{

 BaseType_t xHigherPriorityTaskWoken = pdFALSE;

  UART_lReceiveHandler(&UART_0);
  xTaskNotifyFromISR(xHandle_1, 0, eNoAction, &xHigherPriorityTaskWoken);

  portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

}

