/*
 * main.c
 *
 *  Created on: 2024 Jun 29 17:11:11
 *  Author: PC
 */


#include "DAVE.h"                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

TaskHandle_t xHandle_1,xHandle_2,xHandle_3;

static void task_1(void *pvparameters);
static void task_2(void *pvparameters);
static void task_3(void *pvparameters);

void DAVE_Initialsisation(void);

int main(void)
{

DAVE_Initialsisation();

BaseType_t status;

status = xTaskCreate(task_1,"TASK-1",1024,NULL,2,&xHandle_1);    //lower priority

configASSERT(status == pdPASS);

status = xTaskCreate(task_2,"TASK-2",1024,NULL,2,&xHandle_2);   //medium priority

configASSERT(status == pdPASS);

status = xTaskCreate(task_3,"TASK-3",1024,NULL,1,&xHandle_3);  // higher priority

configASSERT(status == pdPASS);

   vTaskStartScheduler();

}

static void task_1(void *pvparameters)
{
		TickType_t xLastWakeTime;
	// Initialise the xLastWakeTime variable with the current time.
	    xLastWakeTime = xTaskGetTickCount();
	// const TickType_t xFrequency = 10;
	while(1)
	{

		DIGITAL_IO_ToggleOutput(&DIGITAL_IO_0);  //LED0
		vTaskDelayUntil( &xLastWakeTime,pdMS_TO_TICKS(1000) );

	}
}

static  void task_2(void *pvparameters)
{
	TickType_t xLastWakeTime;
// Initialise the xLastWakeTime variable with the current time.
  xLastWakeTime = xTaskGetTickCount();
	while(1)
	{

		DIGITAL_IO_ToggleOutput(&DIGITAL_IO_1);   //LED1
		vTaskDelayUntil( &xLastWakeTime,pdMS_TO_TICKS(100) );

	}
}

static  void task_3(void *pvparameters)
{
	TickType_t xLastWakeTime;
// Initialise the xLastWakeTime variable with the current time.
  xLastWakeTime = xTaskGetTickCount();

	uint8_t Send_Data[] = "Task-3 from Infineon\r\n";
	while(1)
	{

		UART_Transmit(&UART_0, Send_Data, sizeof(Send_Data)-1);
		vTaskDelayUntil( &xLastWakeTime,pdMS_TO_TICKS(3000) );


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

