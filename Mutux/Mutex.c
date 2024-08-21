
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
#include <freertos/queue.h>
#include <freertos/semphr.h>

TaskHandle_t xHandle_1,xHandle_2,xHandle_3;


SemaphoreHandle_t xSemaphore;

SemaphoreHandle_t xMutex;


static void task_1(void *pvparameters);
static void task_2(void *pvparameters);
static void task_3(void *pvparameters);


void LowPriorityTask(void *pvParameters);
void MediumPriorityTask(void *pvParameters);
void HighPriorityTask(void *pvParameters);


void DAVE_Initialsisation(void);

int main(void)
{

DAVE_Initialsisation();


//xSemaphore = xSemaphoreCreateBinary();
xMutex = xSemaphoreCreateMutex();
// Initially "give" the semaphore so the first task can take it
//xSemaphoreGive(xSemaphore);

if (xMutex != NULL) {
	// Create tasks with different priorities
	xTaskCreate(LowPriorityTask, "LowPriorityTask", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	xTaskCreate(MediumPriorityTask, "MediumPriorityTask", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
	xTaskCreate(HighPriorityTask, "HighPriorityTask", configMINIMAL_STACK_SIZE, NULL, 3, NULL);

	// Start the scheduler
	vTaskStartScheduler();
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

void LowPriorityTask(void *pvParameters) {

	const char* pdata = "Low priority task working\r\n";
	const char* pdata2 = "Low priority task done\n\r";
	uint8_t size = strlen(pdata)+1;
	uint8_t size2 = strlen(pdata2)+1;
	uint8_t Send_Data[size];
	uint8_t Send_Data2[size2];



    while (1) {

        // Low-priority task takes the semaphore
    	  if (xSemaphoreTake(xMutex, portMAX_DELAY) == pdTRUE) {

        	sprintf((char*)Send_Data,"%s",pdata);
        	UART_Transmit(&UART_0,(uint8_t*) Send_Data, sizeof(Send_Data)-1);

        	//vTaskDelay(pdMS_TO_TICKS(1000)); // Simulate work
        	for(int i=0;i<0xFFFFFF;i++);

        	sprintf((char*)Send_Data2,"%s",pdata2);
        	UART_Transmit(&UART_0,(uint8_t*) Send_Data2, sizeof(Send_Data2)-1);

        	 xSemaphoreGive(xMutex);

        	vTaskDelay(pdMS_TO_TICKS(2000));

        }
    }
}

void MediumPriorityTask(void *pvParameters) {
	const char* pdata = "Medium priority task working\r\n";
	uint8_t size = strlen(pdata)+1;
	uint8_t Send_Data[size];


    while (1) {


    	sprintf((char*)Send_Data,"%s",pdata);
    	UART_Transmit(&UART_0,(uint8_t*) Send_Data, sizeof(Send_Data)-1);
    	vTaskDelay(pdMS_TO_TICKS(500)); // Simulate work

    }


}

void HighPriorityTask(void *pvParameters) {
	const char* pdata = "High priority task working\r\n";
	const char* pdata2 = "High priority task done\n\r";
	uint8_t size = strlen(pdata)+1;
	uint8_t size2 = strlen(pdata2)+1;
	uint8_t Send_Data[size];
	uint8_t Send_Data2[size2];



    while (1) {
    	//vTaskDelay(pdMS_TO_TICKS(600));

        // High-priority task tries to take the semaphore
    	if (xSemaphoreTake(xMutex, portMAX_DELAY) == pdTRUE) {

        	sprintf((char*)Send_Data,"%s",pdata);
        	UART_Transmit(&UART_0,(uint8_t*) Send_Data, sizeof(Send_Data)-1);

        	vTaskDelay(pdMS_TO_TICKS(100)); // Simulate work

        	sprintf((char*)Send_Data2,"%s",pdata2);
        	UART_Transmit(&UART_0,(uint8_t*) Send_Data2, sizeof(Send_Data2)-1);

        	 xSemaphoreGive(xMutex);

        	vTaskDelay(pdMS_TO_TICKS(1000));

        }


    	else{

    		;

    	}
    }
}


