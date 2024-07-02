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

TaskHandle_t xHandle_1,xHandle_2;

static void sensortask_1(void *pvparameters);
static void sensortask_2(void *pvparameters);

void DAVE_Initialsisation(void);

int main(void)
{

DAVE_Initialsisation();

BaseType_t status;

status = xTaskCreate(sensortask_1,"sensortask_1",1024,NULL,5,&xHandle_1);

configASSERT(status == pdPASS);

status = xTaskCreate(sensortask_2,"sensortask_2",1024,NULL,5,&xHandle_2);

configASSERT(status == pdPASS);

   vTaskStartScheduler();

}

static  void sensortask_1(void *pvparameters)
{
	uint8_t Send_Data[] = "Task-1 from Infineon\r\n";
	while(1)
	{

		UART_Transmit(&UART_0, Send_Data, sizeof(Send_Data)-1);
            taskYIELD();
	}
}

static  void sensortask_2(void *pvparameters)
{
	uint8_t Send_Data[] = "Task-22 from Infineon\r\n";
	while(1)
	{

		UART_Transmit(&UART_0, Send_Data, sizeof(Send_Data)-1);
		taskYIELD();
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
