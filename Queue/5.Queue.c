/*
Enhence version of 4.Queue.c 
taken Arra of 2 with type sensordata which stores 5 elements
and tried it came

 */

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

#define ARRAY_SIZE 5U

typedef int sensorData_t[ARRAY_SIZE];

QueueHandle_t sensorQueue;

void DAVE_Initialsisation(void);

int main(void)
{

DAVE_Initialsisation();

BaseType_t status;

status = xTaskCreate(Task_1,"Task_1",200,NULL,3,&xHandle_1);

configASSERT(status == pdPASS);

status = xTaskCreate(Task_2,"Task_2",200,NULL,2,&xHandle_2);

configASSERT(status == pdPASS);

myQueue = xQueueCreate(5, sizeof( student_t* ));  //this creation is very important it can save HEAP memory
configASSERT(myQueue != NULL);

sensorQueue = xQueueCreate(2, sizeof( sensorData_t* ));  //this creation is very important it can save HEAP memory
configASSERT(sensorQueue != NULL);


   vTaskStartScheduler();

}

 void Task_1(void *pvparameters)
{

	 sensorData_t sensorData[2];
	 sensorData_t  *ptrsensorData;

	 sensorData[0][0] = 1;  //index 0 initialise all 5 elments
	 sensorData[0][1] = 2;
	 sensorData[0][2] = 3;
	 sensorData[0][3] = 4;
	 sensorData[0][4] = 5;

	 sensorData[1][0] = 6;   //index 1 initialise all 5 elments
	 sensorData[1][1] = 7;
	 sensorData[1][2] = 8;
	 sensorData[1][3] = 9;
	 sensorData[1][4] = 10;

	 ptrsensorData = &sensorData[0];  //which can hold length of 5 elements to ptrsensorData
	 xQueueSend(sensorQueue,(void*)&ptrsensorData,0);

	 ptrsensorData = &sensorData[1];
	 xQueueSend(sensorQueue,(void*)&ptrsensorData,0);

	while(1)
	{

      vTaskDelay(pdMS_TO_TICKS(1000));

	}

}

void Task_2(void *pvparameters)
{
	sensorData_t xrStudent[2],*pxrStudent;
	while(1){

		if(sensorQueue!=NULL){



			if(xQueueReceive(sensorQueue, (void*)&pxrStudent ,5)){

			/*	    xrStudent[0] = (*pxrStudent)[0];   tried for single attempt to receive its came by deference.
					xrStudent[1] = (*pxrStudent)[1];
					xrStudent[2] = (*pxrStudent)[2];
					xrStudent[3] = (*pxrStudent)[3];
					xrStudent[4] = (*pxrStudent)[4];
			 */

				memcpy(xrStudent[0], *pxrStudent, sizeof(sensorData_t));

			}
			if(xQueueReceive(sensorQueue, (void*)&pxrStudent ,5)){


				memcpy(xrStudent[1], *pxrStudent, sizeof(sensorData_t));

			}






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

