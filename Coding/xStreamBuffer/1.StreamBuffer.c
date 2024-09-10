
#include "DAVE.h"                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/portable/GCC/portmacro_mpu.h>
#include <freertos/queue.h>
#include <freertos/stream_buffer.h>

#define STREAM_BUFFER_SIZE   100U  // Size of the stream buffer in bytes
#define TRIGGER_LEVEL         5U  // Minimum number of bytes to be written to unblock the reader 

TaskHandle_t xHandle_1,xHandle_2;

StreamBufferHandle_t xStreamBuffer;  // Handle for the stream buffer


void Task_1(void *pvparameters);
void Task_2(void *pvparameters);
void DAVE_Initialsisation(void);

int main(void)
{

	DAVE_Initialsisation();

	BaseType_t status;

	status = xTaskCreate(Task_1,"Task_1",200,NULL,2,&xHandle_1);

	configASSERT(status == pdPASS);

	status = xTaskCreate(Task_2,"Task_2",200,NULL,3,&xHandle_2);

	configASSERT(status == pdPASS);

	xStreamBuffer = xStreamBufferCreate(STREAM_BUFFER_SIZE, TRIGGER_LEVEL);

	if(xStreamBuffer == NULL){

		while(1);  //Hang here if Heap memory is not sufficient
 
	}


	vTaskStartScheduler();

}

void Task_1(void *pvparameters)
{

	const char *dataToSend = "Hello__";
	size_t xBytesSent;

	while(1)
	{

		xBytesSent = xStreamBufferSend(xStreamBuffer, dataToSend, strlen(dataToSend), pdMS_TO_TICKS(1000));
		vTaskDelay(pdMS_TO_TICKS(2000));

	}

}

void Task_2(void *pvparameters)
{
	char buffer[7];
	size_t xBytesReceived;

	while(1){


		xBytesReceived = xStreamBufferReceive(xStreamBuffer, buffer, sizeof(buffer), portMAX_DELAY);
		buffer[xBytesReceived] = '\0';

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
